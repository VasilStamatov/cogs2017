#include "../include/Renderer3D.h"

#include "../include/Camera.h"
#include "../include/GLSLProgram.h"
#include "../include/MeshRenderer.h"
#include "../include/Mesh.h"
#include "../include/Entity.h"
#include "../include/Material.h"

#include <GL\glew.h>

namespace cogs
{
		Renderer3D::Renderer3D()
		{
		}
		Renderer3D::~Renderer3D()
		{
		}
		void Renderer3D::init()
		{

		}
		void Renderer3D::submit(Entity* _entity)
		{
				Camera* currentCam = Camera::getCurrent();

				Mesh* mesh = _entity->getComponent<MeshRenderer>()->getMesh();

				Transform* transform = _entity->transform();

				//get the center vertex position in model space
				const MeshBoundingSphere& sphereBounds = mesh->getSphereBounds();

				//get the transformation matrix to world space
			 glm::mat4 toWorldMat = transform->worldTransform();

				//calculate the center vertex from model to world space
				glm::vec3 point = glm::vec3(toWorldMat * glm::vec4(sphereBounds.m_center, 1.0f));

			 glm::vec3 scale = transform->worldScale();

				//scale the radius
				float radius = sphereBounds.m_radius * glm::max(scale.x, glm::max(scale.y, scale.z));
				//submit the mesh if it's in the view frustum

				if (currentCam->sphereInFrustum(point, radius))
				{
						auto iter = m_entitiesMap.find(mesh->m_VAO);

						//check if it's not in the map
						if (iter == m_entitiesMap.end())
						{
								InstanceData instance;
								instance.mesh = mesh;
								m_entitiesMap.insert(std::make_pair(mesh->m_VAO, instance));
						}
						m_entitiesMap[mesh->m_VAO].worldmats.push_back(toWorldMat);
				}

		}
		void Renderer3D::flush()
		{
				//get the current cam that will be used for space-transforms
				Camera* currentCam = Camera::getCurrent();

				for (auto& it : m_entitiesMap)
				{
						InstanceData instances = it.second;

						const std::vector<SubMesh>& subMeshes = instances.mesh->getSubMeshes();
						const std::vector<Material*>& materials = instances.mesh->getMaterials();

						//bind the per-instance buffers
						glBindBuffer(GL_ARRAY_BUFFER, instances.mesh->m_VBOs[instances.mesh->BufferObject::WORLDMAT]);
						//upload the data
						glBufferData(GL_ARRAY_BUFFER, sizeof(glm::mat4) * instances.worldmats.size(), instances.worldmats.data(), GL_DYNAMIC_DRAW);

						glBindVertexArray(it.first);

						for (unsigned int i = 0; i < subMeshes.size(); i++)
						{
								const unsigned int materialIndex = subMeshes[i].m_materialIndex;
								assert(materialIndex < materials.size());

								Material* currMat = materials.at(materialIndex);

								currMat->bind();
								currMat->getShader()->uploadValue("projection", currentCam->getProjectionMatrix());
								currMat->getShader()->uploadValue("view", currentCam->getViewMatrix());

								glDrawElementsInstancedBaseVertex(GL_TRIANGLES, subMeshes.at(i).m_numIndices, GL_UNSIGNED_INT,
										(void*)(sizeof(unsigned int) * subMeshes.at(i).m_baseIndex), instances.worldmats.size(),
										subMeshes.at(i).m_baseVertex);

								currMat->unbind();
						}

						glBindVertexArray(0);
				}
		}

		void Renderer3D::dispose()
		{
		}

		void Renderer3D::begin()
		{
				m_entitiesMap.clear();
		}

		void Renderer3D::end()
		{
				//TODO: possibly sorting and batching/preparing for instanced rendering ?
		}
}