#include "../include/Renderer2D.h"

#include "../include/Entity.h"
#include "../include/Sprite.h"
#include "../include/Material.h"
#include "../include/SpriteRenderer.h"
#include "../include/Camera.h"
#include "../include/GLSLProgram.h"

#include <GL\glew.h>

namespace cogs
{
		Renderer2D::Renderer2D()
		{
		}
		Renderer2D::~Renderer2D()
		{
				dispose();
		}
		void Renderer2D::init()
		{
				//generate the vertex array buffer
				glGenVertexArrays(1, &m_VAO);

				//generate the vertex buffer objects
				glGenBuffers(static_cast<unsigned char>(BufferObjects::NUM_BUFFERS), m_VBOs);

				//bind the vao and continue working on the vbos under it
				glBindVertexArray(m_VAO);

				//bind the position buffer
				glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[static_cast<unsigned char>(BufferObjects::POSITION)]);

				float vertices[] =
				{ -0.5f,  0.5f, 0.0f,	 // top left corner
					-0.5f, -0.5f, 0.0f,		// bottom left corner
						0.5f, -0.5f, 0.0f, // bottom right corner
						0.5f,  0.5f, 0.0f };			// top right corner

				glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

				glEnableVertexAttribArray(static_cast<unsigned char>(BufferObjects::POSITION));
				glVertexAttribPointer(static_cast<unsigned char>(BufferObjects::POSITION), 3, GL_FLOAT, GL_FALSE, 0, nullptr);

				unsigned int indices[] = { 0,1,2,			// first triangle (bottom left - top left - top right)
																															0,2,3 }; // second triangle (bottom left - top right - bottom right)

				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VBOs[static_cast<unsigned char>(BufferObjects::INDEX)]);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

				// bind the color buffer
				glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[static_cast<unsigned char>(BufferObjects::COLOR)]);

				glEnableVertexAttribArray(static_cast<unsigned char>(BufferObjects::COLOR));
				glVertexAttribPointer(static_cast<unsigned char>(BufferObjects::COLOR), 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, nullptr);
				glVertexAttribDivisor(static_cast<unsigned char>(BufferObjects::COLOR), 1);

				// bind the color buffer
				glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[static_cast<unsigned char>(BufferObjects::SIZE)]);
				glEnableVertexAttribArray(static_cast<unsigned char>(BufferObjects::SIZE));
				glVertexAttribPointer(static_cast<unsigned char>(BufferObjects::SIZE), 2, GL_FLOAT, GL_FALSE, 0, nullptr);
				glVertexAttribDivisor(static_cast<unsigned char>(BufferObjects::SIZE), 1);

				glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[static_cast<unsigned char>(BufferObjects::WORLDMAT)]);
				// cannot upload mat4's all at once, so upload them as 4 vec4's
				for (size_t i = 0; i < 4; i++)
				{
						//enable the channel of the current matrix row (4,5,6,7)
						glEnableVertexAttribArray(static_cast<unsigned char>(BufferObjects::WORLDMAT) + i);
						//tell opengl how to read it
						glVertexAttribPointer(static_cast<unsigned char>(BufferObjects::WORLDMAT) + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),
								(const void*)(sizeof(float) * i * 4));

						/** This function is what makes it per-instance data rather than per vertex
						* The first parameter is the attribute channel as above (4,5,6,7)
						* The second parameter tells the rate at which the attribute advanced during the rendering
						* 1 means that this data is updated after 1 instance has been rendered
						* by default it's 0 which makes it per-vertex and if it's over 1 than more than 1 instances will use this data
						*/
						glVertexAttribDivisor(static_cast<unsigned char>(BufferObjects::WORLDMAT) + i, 1);
				}

				// unbind the vao after the setup is done
				glBindVertexArray(0);
		}

		void Renderer2D::submit(Entity* _entity)
		{
				Sprite* sprite = _entity->getComponent<SpriteRenderer>()->getSprite();
			 Material* material = sprite->getMaterial();

				//The transform values of the sprite
				Transform* transform = _entity->transform();

				uint texID = material->getDiffuseMap()->getTextureID();

				auto iter = m_spritesMap.find(texID);

				//check if it's not in the map
				if (iter == m_spritesMap.end())
				{
						InstancedAttributes newInstance;
						newInstance.material = material;
						m_spritesMap.insert(std::make_pair(texID, newInstance));
				}
				m_spritesMap[texID].worldMat.push_back(transform->worldTransform());
				m_spritesMap[texID].color.push_back(sprite->getColor());
				m_spritesMap[texID].size.push_back(sprite->getSize());
		}

		void Renderer2D::flush()
		{
				Camera* currentCam = Camera::getCurrent();

				glBindVertexArray(m_VAO);

				for (auto& it : m_spritesMap)
				{
						InstancedAttributes instances = it.second;
						instances.material->bind();

						instances.material->getShader()->uploadValue("projection", currentCam->getProjectionMatrix());
						instances.material->getShader()->uploadValue("view", currentCam->getViewMatrix());

						//bind the per-instance buffers
						glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[static_cast<unsigned char>(BufferObjects::COLOR)]);
						//upload the data
						glBufferData(GL_ARRAY_BUFFER, sizeof(Color) * instances.color.size(), instances.color.data(), GL_DYNAMIC_DRAW);

						//bind the per-instance buffers
						glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[static_cast<unsigned char>(BufferObjects::SIZE)]);
						//upload the data
						glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * instances.size.size(), instances.size.data(), GL_DYNAMIC_DRAW);

						//bind the per-instance buffers
						glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[static_cast<unsigned char>(BufferObjects::WORLDMAT)]);
						//upload the data
						glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * instances.worldMat.size(), instances.worldMat.data(), GL_DYNAMIC_DRAW);

						glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, instances.worldMat.size());

						instances.material->unbind();
				}
				glBindVertexArray(0);
		}

		void Renderer2D::begin()
		{
				m_spritesMap.clear();
		}

		void Renderer2D::end()
		{
		}

		void Renderer2D::dispose()
		{
				//Dispose of all the buffest if they have't been disposed already

				if (m_VAO != 0)
				{
						glDeleteVertexArrays(1, &m_VAO);
						m_VAO = 0;
				}

				if (m_VBOs[0] != 0)
				{
						glDeleteBuffers(static_cast<unsigned char>(BufferObjects::NUM_BUFFERS), m_VBOs);

						for (size_t i = 0; i < static_cast<unsigned char>(BufferObjects::NUM_BUFFERS); i++)
						{
								m_VBOs[i] = 0;
						}
				}
		}
}
