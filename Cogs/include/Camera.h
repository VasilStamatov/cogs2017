#pragma once

#include "Transform.h"
#include "Color.h"
#include "Frustum.h"

namespace cogs
{
		class Framebuffer;
		class Skybox;

		class Camera final : public Component
		{
		public:
				Camera();
				~Camera();

				void setFoV(int _value);
				void offsetFoV(int _value);

				void setSize(float _value);
				void offsetSize(float _value);

				void setNearPlane(float _value);
				void setFarPlane(float _value);

				void setProjectionType(bool _ortho) { m_ortho = _ortho; }

				void setProjectionMatrix(float _fov, float _width, float _height, float _nearP, float _farP);
				void resetProjectionMatrix();
			 
				glm::mat4 getProjectionMatrix() const noexcept;

				const glm::mat4& getViewMatrix() const noexcept;

				bool pointInFrustum(const glm::vec3& _pos) { return m_frustum.pointInFrustum(_pos); }

				bool sphereInFrustum(const glm::vec3& _pos, float _radius) { return m_frustum.sphereInFrustum(_pos, _radius); }
				
				void setRenderTarget(Framebuffer* _renderTarget) { m_renderTarget = _renderTarget; }
				Framebuffer* getRenderTarget() const noexcept { return m_renderTarget; }

				void setSkybox(Skybox* _skybox) { m_skybox = _skybox; }
				Skybox* getSkybox() const noexcept { return m_skybox; }

				void renderSkybox();

				void setBackgroundColor(const Color& _color) { m_backgroundColor = _color; }
				const Color& getBackgroundColor() const noexcept { return m_backgroundColor; }

				float getSize() const noexcept { return m_size; }
				float getNear()	const noexcept { return m_nearPlane; }
				float getFar()		const noexcept { return m_farPlane;; }
				int getFoV()				const noexcept { return m_fov; }

				static void setMain(Camera* _camera) { s_mainCamera = _camera; }
				static void setCurrent(Camera* _camera) { s_currentCamera = _camera; }
				static void addCamera(Camera* _camera) { s_allCameras.push_back(_camera); }
				
				static Camera* getMain() { return s_mainCamera; }
				static Camera* getCurrent() { return s_currentCamera; }
				static std::vector<Camera*> getAllCameras() { return s_allCameras; }

		private:
				void updateView();
				void refreshInternalTransform();

				void init() override;
				void update(float _deltaTime) override;

		private:
				static std::vector<Camera*> s_allCameras;
				static Camera* s_mainCamera;
				static Camera* s_currentCamera;

				Frustum m_frustum;
				Transform m_oldTransform;

				glm::mat4  m_viewMatrix{ 1.0f };
				glm::mat4* m_perspMatrix{ nullptr };

				Transform* m_transform{ nullptr };

				float m_size{ 5.0f };
				int m_fov{ 60 };

				float m_nearPlane{ 0.1f };
				float m_farPlane{ 100.0f };

				Framebuffer* m_renderTarget;
				Skybox* m_skybox;

				Color m_backgroundColor{ Color::getWhite() };
				bool m_ortho{ true };
		};
}