#pragma once

#include "Transform.h"
#include "Color.h"
#include "Frustum.h"

namespace cogs
{
		class Framebuffer;
		class Skybox;

		/**
		* The camera component
		*/
		class Camera : public Component
		{
		private:
				static Camera* s_mainCamera; ///< the main camera
				static Camera* s_currentCamera; ///< current active camera
				static std::vector<Camera*> s_allCameras; ///< all cameras created

				bool m_ortho{ true };

				glm::mat4* m_perspMatrix{ nullptr }; ///< perspective matrix for perspective camera
				glm::mat4  m_viewMatrix{ 1.0f }; ///< Camera view matrix

				Transform* m_transform{ nullptr };
				Transform m_oldTransform;	///< the old transform (to be compared for view changes

				float m_size{ 5.0f }; ///< the size of the ortho camera (zoom)
				int m_fov{ 60 };				  ///< the field of view of the perspective camera

				float m_nearPlane{ 0.1f };  ///< the near clipping plane
				float m_farPlane{ 100.0f }; ///< the far clipping plane

				Framebuffer* m_renderTarget; ///< the target framebuffer this camera renders to
				Skybox* m_skybox; ///< skybox the camera renders to fill up the background colors

				Color m_backgroundColor{ Color::white }; ///< background color to clear to 

				Frustum m_frustum;

		protected:
				void updateView();

				/*
				* \brief the first function called after the constructor
				*/
				void init() override;

				/*
				* \brief function called once per frame
				*/
				void update(float _deltaTime) override;

		public:
				/**
				*	\brief Constructor for the camera component
				* \param _projType - the projection type of the camera
				* \param _screenWidth - screen width
				* \param _screenHeight - screen height
				*/
				Camera();
				~Camera();

				/**
				* \brief Changes the FoV of the perspective matrix and updates it
				* \param _value - the new FoV value
				*/
				void setFoV(int _value);

				/**
				* \brief Offsets the FoV of the perspecive matrix and updates it
				* \param _value - the value to be added to the current FoV
				*/
				void offsetFoV(int _value);

				/**
				* \brief Changes the size of the orthographic matrix and updates it
				* \param _value - the new size value
				*/
				void setSize(float _value);

				/**
				* \brief Offsets the size of the orthographic matrix and updates it
				* \param _value - the value to be added to the current size
				*/
				void offsetSize(float _value);

				/**
				* \brief Changes the near plane
				* \param _value - the new near value
				*/
				void setNearPlane(float _value);

				/**
				* \brief Changes the far plane
				* \param _value - the new far value
				*/
				void setFarPlane(float _value);

				/**
				* \brief Sets the projection type of the matrix
				*/
				void setProjectionType(bool _ortho) { m_ortho = _ortho; }

				void setProjectionMatrix(float _fov, float _width, float _height, float _nearP, float _farP);
				void resetProjectionMatrix();
				/**
				* \brief Gets the projection matrix of the camera
				* \return the projection matrix
				*/
			 glm::mat4 getProjectionMatrix() const noexcept;

				/**
				* \brief Gets the view matrix of the camera
				* \return the view matrix
				*/
				const glm::mat4& getViewMatrix() const noexcept;

				bool pointInFrustum(const glm::vec3& _pos) { return m_frustum.pointInFrustum(_pos); }

				bool sphereInFrustum(const glm::vec3& _pos, float _radius) { return m_frustum.sphereInFrustum(_pos, _radius); }

				/**
				* \brief get and set the target framebuffer this camera renders to
				*/
				void setRenderTarget(Framebuffer* _renderTarget) { m_renderTarget = _renderTarget; }
				Framebuffer* getRenderTarget() const noexcept { return m_renderTarget; }

				/**
				* \brief get and set the skybox this camera renders
				*/
				void setSkybox(Skybox* _skybox) { m_skybox = _skybox; }
				Skybox* getSkybox() const noexcept { return m_skybox; }

				void renderSkybox();

				/**
				* \brief get and set the background color
				*/
				void setBackgroundColor(const Color& _color) { m_backgroundColor = _color; }
				const Color& getBackgroundColor() const noexcept { return m_backgroundColor; }

				/**
				* Some basic getters
				*/
				float getSize() const noexcept { return m_size; }
				float getNear()	const noexcept { return m_nearPlane; }
				float getFar()		const noexcept { return m_farPlane;; }
				int getFoV()				const noexcept { return m_fov; }

				/*
				* \brief set the main camera
				*/
				static void setMain(Camera* _camera) { s_mainCamera = _camera; }

				/*
				* \brief set the current active camera
				*/
				static void setCurrent(Camera* _camera) { s_currentCamera = _camera; }

				/*
				* \brief add a camera to the camera vector
				*/
				static void addCamera(Camera* _camera) { s_allCameras.push_back(_camera); }

				/*
				* \brief get the main camera
				*/
				static Camera* getMain() { return s_mainCamera; }

				/*
				* \brief get the current active camera
				*/
				static Camera* getCurrent() { return s_currentCamera; }

				/*
				* \brief get all the existing cameras
				*/
				static std::vector<Camera*> getAllCameras() { return s_allCameras; }
		};
}