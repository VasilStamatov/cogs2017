#include "../include/MeshRenderer.h"
#include "../include/Entity.h"

#include "../include/Mesh.h"
#include "../include/Renderer3D.h"

namespace cogs
{
		MeshRenderer::MeshRenderer(Mesh* _mesh,
				Renderer3D* _renderer) :
				m_mesh(_mesh),
				m_renderer(_renderer)
		{
		}

		MeshRenderer::~MeshRenderer()
		{
		}

		void MeshRenderer::render()
		{
				m_renderer->submit(m_entity);
		}
}