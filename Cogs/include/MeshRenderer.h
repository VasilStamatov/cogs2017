#pragma once

#include "Component.h"

namespace cogs
{
		class Mesh;
		class Renderer3D;
		
		class MeshRenderer : public Component
		{
		public:
				MeshRenderer(Mesh* _mesh, Renderer3D* _renderer);
				~MeshRenderer();

				Mesh* getMesh() const noexcept { return m_mesh; }
				
				void setMesh(Mesh* _mesh) { m_mesh = _mesh; }

		protected:
				void render() override;

		private:
				Mesh* m_mesh; ///< reference to the mesh rendererd
				Renderer3D* m_renderer; ///< reference to the renderer the mesh is submitted to
		};
}