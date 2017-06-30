#pragma once

#include "Component.h"

namespace cogs
{
		class Mesh;
		class Renderer3D;
		/**
		* \brief This component, given to an entity should submit it to a 3D renderer
		*/
		class MeshRenderer : public Component
		{
		public:
				/**
				* \brief Construct the mesh renderer by giving if a reference to the mesh it will submit,
				* the material of the mesh, and the renderer the mesh will be submitted to
				*/
				MeshRenderer(Mesh* _mesh,
						Renderer3D* _renderer);
				~MeshRenderer();

				/**
				* Getters
				*/
				Mesh* getMesh() const noexcept { return m_mesh; }

				/**
				* Setters
				*/
				void setMesh(Mesh* _mesh) { m_mesh = _mesh; }

		protected:
				void render() override;

				Mesh* m_mesh; ///< reference to the mesh rendererd
				Renderer3D* m_renderer; ///< reference to the renderer the mesh is submitted to
		};
}