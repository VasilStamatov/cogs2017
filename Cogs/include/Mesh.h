#pragma once

#include <vector>
#include <string>
#include	<memory>
#include <glm\vec3.hpp>
#include <glm\vec2.hpp>

#include "Object.h"

namespace cogs
{
		class Material;
		class ResourceManager;

		struct SubMesh
		{
				unsigned int m_baseVertex{ 0 };
				unsigned int m_baseIndex{ 0 };
				unsigned int m_numIndices{ 0 };
				unsigned int m_materialIndex{ 9999 };
		};

		struct MeshData
		{
				std::vector<glm::vec3> m_positions;
				std::vector<glm::vec2> m_uvs;
				std::vector<glm::vec3> m_normals;
				std::vector<glm::vec3> m_tangents;
				std::vector<unsigned int> m_indices;
		};

		struct MeshBoundingSphere
		{
				glm::vec3 m_center;
				float m_radius;
		};

		struct MeshBoundingBox
		{
				glm::vec3 m_min;
				glm::vec3 m_max;
		};

		class Mesh : public Object
		{
				friend class Renderer3D;

		public:
				Mesh(const std::string& _filePath, ResourceManager* _rm);
				~Mesh();

				void render() const;

				void dispose();

				bool isValid(const MeshData& _meshData) const;

				inline const MeshBoundingSphere& getSphereBounds()  const noexcept { return m_boundingSphere; }
				inline const MeshBoundingBox& getBoxBounds()						  const noexcept { return m_boundingBox; }
				inline const std::vector<SubMesh>& getSubMeshes()			const noexcept { return m_subMeshes; }
				inline const std::vector<Material*>& getMaterials()	const noexcept { return m_materials; }

		private:
				void calcBounds(const std::vector<glm::vec3>& _positions);
				void calcNormals(MeshData& _meshData);
				void calcTangents(MeshData& _meshData);
				void finalize(MeshData& _meshData);
				void createBuffers(MeshData& _meshData);

				enum class BufferObject : unsigned char
				{
						POSITION,
						TEXCOORD,
						NORMAL,
						TANGENT,
						WORLDMAT,

						INDEX,

						NUM_BUFFERS
				};

		private:
				std::vector<SubMesh> m_subMeshes;
				std::vector<Material*> m_materials;

				MeshBoundingBox m_boundingBox;
				MeshBoundingSphere m_boundingSphere;

				unsigned int m_numIndices{ 0 };
				unsigned int m_VAO{ 0 };
				unsigned int m_VBOs[static_cast<unsigned char>(BufferObject::NUM_BUFFERS)] = { 0 };
		};
}