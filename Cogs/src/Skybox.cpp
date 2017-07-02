#include "../include/Skybox.h"
#include "../include/ResourceManager.h"
#include "../include/Camera.h"
#include "../include/GLSLProgram.h"
#include "../include/Mesh.h"

#include <GL\glew.h>
#include <glm\gtc\matrix_transform.hpp>

namespace cogs
{
		Skybox::Skybox(ResourceManager* _rm, GLSLProgram* _shader, GLCubemapTexture* _cubemapTex, bool _isBox) :
				m_skyboxShader(_shader), m_cubemapTex(_cubemapTex)
		{
				if (_isBox)
				{
						m_mesh = _rm->get<Mesh>("Cube", "Models/TestModels/cube.obj", _rm);
				}
				else
				{
						m_mesh = _rm->get<Mesh>("Sphere", "Models/TestModels/sphere.obj", _rm);
				}
		}

		Skybox::~Skybox()
		{
				m_skyboxShader = nullptr;
				m_cubemapTex = nullptr;
				m_mesh = nullptr;
		}

		void Skybox::render()
		{
				m_skyboxShader->use();

				GLint oldCullMode{ 0 };
				glGetIntegerv(GL_CULL_FACE_MODE, &oldCullMode);
				GLint oldDepthFunc{ 0 };
				glGetIntegerv(GL_DEPTH_FUNC, &oldDepthFunc);

				glCullFace(GL_FRONT);
				glDepthFunc(GL_LEQUAL);

				Camera* currentCamera = Camera::getCurrent();

				const glm::mat4& view = glm::mat4(glm::mat3(currentCamera->getViewMatrix())); // Remove any translation component of the view matrix

				m_skyboxShader->uploadValue("view", view);
				m_skyboxShader->uploadValue("projection", currentCamera->getProjectionMatrix());
				m_skyboxShader->uploadValue("skybox", 0, m_cubemapTex);

				m_mesh->render();

				glCullFace(oldCullMode);
				glDepthFunc(oldDepthFunc);

				m_skyboxShader->unUse();
		}
}