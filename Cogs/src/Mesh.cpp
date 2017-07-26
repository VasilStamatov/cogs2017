#include "../include/Mesh.h"

#include "../include/Material.h"
#include "../include/ResourceLoader.h"
#include "../include/ResourceManager.h"

#include <glm\glm.hpp>
#include <GL\glew.h>

namespace cogs
{
		Mesh::Mesh(const std::string& _filePath, ResourceManager* _rm)
		{
				MeshData meshData;
				ResourceLoader::loadMesh(_rm, _filePath, m_subMeshes, m_materials, meshData);

				createBuffers(meshData);
		}

		Mesh::~Mesh()
		{
				dispose();
		}

		void Mesh::render() const
		{
				glBindVertexArray(m_VAO);

				glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, nullptr);

				glBindVertexArray(0);
		}

		void Mesh::dispose()
		{
				if (m_VAO != 0)
				{
						glDeleteVertexArrays(1, &m_VAO);
						m_VAO = 0;
				}

				if (m_VBOs[0] != 0)
				{
						glDeleteBuffers(static_cast<unsigned char>(BufferObject::NUM_BUFFERS), m_VBOs);
						for (size_t i = 0; i < 5; i++)
						{
								m_VBOs[i] = 0;
						}
				}
		}

		bool Mesh::isValid(const MeshData& _meshData) const
		{
				return _meshData.m_positions.size() == _meshData.m_uvs.size()
						&&		 _meshData.m_uvs.size() == _meshData.m_normals.size()
						&&		 _meshData.m_normals.size() == _meshData.m_tangents.size();
		}

		void Mesh::calcBounds(const std::vector<glm::vec3>& _positions)
		{
				float maxX{ 0.0f }, maxY{ 0.0f }, maxZ{ 0.0f };
				float minX{ 0.0f }, minY{ 0.0f }, minZ{ 0.0f };

				for (size_t i = 0; i < _positions.size(); i++)
				{
						if (_positions.at(i).x > maxX)
						{
								maxX = _positions.at(i).x;
						}
						if (_positions.at(i).x < minX)
						{
								minX = _positions.at(i).x;
						}

						if (_positions.at(i).y > maxY)
						{
								maxY = _positions.at(i).y;
						}
						if (_positions.at(i).y < minY)
						{
								minY = _positions.at(i).y;
						}

						if (_positions.at(i).z > maxZ)
						{
								maxZ = _positions.at(i).z;
						}
						if (_positions.at(i).z < minZ)
						{
								minZ = _positions.at(i).z;
						}
				}

				m_boundingBox.m_min = glm::vec3(minX, minY, minZ);
				m_boundingBox.m_max = glm::vec3(maxX, maxY, maxZ);

				m_boundingSphere.m_center = glm::vec3(
						minX + (maxX - minX) * 0.5f,
						minY + (maxY - minY) * 0.5f,
						minZ + (maxZ - minZ) * 0.5f);
				m_boundingSphere.m_radius = fmaxf((maxX - minX) * 0.5f, fmaxf((maxY - minY) * 0.5f, (maxZ - minZ) * 0.5f));
		}

		void Mesh::calcNormals(MeshData& _meshData)
		{
				_meshData.m_normals.clear();
				_meshData.m_normals.reserve(_meshData.m_positions.size());

				for (unsigned int i = 0; i < _meshData.m_positions.size(); i++)
				{
						_meshData.m_normals.push_back(glm::vec3(0, 0, 0));
				}

				for (unsigned int i = 0; i < _meshData.m_indices.size(); i += 3)
				{
						int A = _meshData.m_indices.at(i);
						int B = _meshData.m_indices.at(i + 1);
						int C = _meshData.m_indices.at(i + 2);

						glm::vec3 v1 = _meshData.m_positions.at(B) - _meshData.m_positions.at(A);
						glm::vec3 v2 = _meshData.m_positions.at(C) - _meshData.m_positions.at(A);

						glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

						_meshData.m_normals.at(A) += normal;
						_meshData.m_normals.at(B) += normal;
						_meshData.m_normals.at(C) += normal;
				}

				for (unsigned int i = 0; i < _meshData.m_normals.size(); i++)
				{
						_meshData.m_normals.at(i) = glm::normalize(_meshData.m_normals.at(i));
				}
		}

		void Mesh::calcTangents(MeshData& _meshData)
		{
				_meshData.m_tangents.clear();
				_meshData.m_tangents.reserve(_meshData.m_positions.size());

				for (unsigned int i = 0; i < _meshData.m_positions.size(); i++)
				{
						_meshData.m_tangents.push_back(glm::vec3(0, 0, 0));
				}

				for (unsigned int i = 0; i < _meshData.m_indices.size(); i += 3)
				{
						int A = _meshData.m_indices.at(i);
						int B = _meshData.m_indices.at(i + 1);
						int C = _meshData.m_indices.at(i + 2);

						glm::vec3 edge1 = _meshData.m_positions.at(B) - _meshData.m_positions.at(A);
						glm::vec3 edge2 = _meshData.m_positions.at(C) - _meshData.m_positions.at(A);

						float deltaU1 = _meshData.m_uvs.at(B).x - _meshData.m_uvs.at(A).x;
						float deltaU2 = _meshData.m_uvs.at(C).x - _meshData.m_uvs.at(A).x;
						float deltaV1 = _meshData.m_uvs.at(B).y - _meshData.m_uvs.at(A).y;
						float deltaV2 = _meshData.m_uvs.at(C).y - _meshData.m_uvs.at(A).y;

						float dividend = (deltaU1 * deltaV2 - deltaU2 * deltaV1);
						float f = dividend == 0.0f ? 0.0f : 1.0f / dividend;

						glm::vec3 tangent(0, 0, 0);

						tangent.x = (f * (deltaV2 * edge1.x - deltaV1 * edge2.x));
						tangent.y = (f * (deltaV2 * edge1.y - deltaV1 * edge2.y));
						tangent.z = (f * (deltaV2 * edge1.z - deltaV1 * edge2.z));

						_meshData.m_tangents.at(A) += tangent;
						_meshData.m_tangents.at(B) += tangent;
						_meshData.m_tangents.at(C) += tangent;
				}

				for (unsigned int i = 0; i < _meshData.m_tangents.size(); i++)
				{
						_meshData.m_tangents.at(i) = glm::normalize(_meshData.m_tangents.at(i));
				}
		}

		void Mesh::finalize(MeshData& _meshData)
		{
				calcBounds(_meshData.m_positions);

				if (isValid(_meshData))
				{
						//already valid
						return;
				}

				if (_meshData.m_uvs.size() == 0)
				{
						for (unsigned int i = _meshData.m_uvs.size(); i < _meshData.m_positions.size(); i++)
						{
								_meshData.m_uvs.push_back(glm::vec2(0.0f, 0.0f));
						}
				}

				if (_meshData.m_normals.size() == 0)
				{
						calcNormals(_meshData);
				}

				if (_meshData.m_tangents.size() == 0)
				{
						calcTangents(_meshData);
				}

				if (!isValid(_meshData))
				{
						printf("Mesh cannot be set up properly");
						assert(false);
				}
		}

		void Mesh::createBuffers(MeshData& _meshData)
		{
				finalize(_meshData);

				m_numIndices = _meshData.m_indices.size();

				glGenVertexArrays(1, &m_VAO);
				glBindVertexArray(m_VAO);

				glGenBuffers(static_cast<unsigned char>(BufferObject::NUM_BUFFERS), m_VBOs);

				// Upload position data
				glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[static_cast<unsigned char>(BufferObject::POSITION)]);
				glBufferData(GL_ARRAY_BUFFER, _meshData.m_positions.size() * sizeof(_meshData.m_positions.at(0)), _meshData.m_positions.data(), GL_STATIC_DRAW);

				glEnableVertexAttribArray(static_cast<unsigned char>(BufferObject::POSITION));
				glVertexAttribPointer(static_cast<unsigned char>(BufferObject::POSITION), 3, GL_FLOAT, GL_FALSE, 0, nullptr);

				// Upload UV data
				glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[static_cast<unsigned char>(BufferObject::TEXCOORD)]);
				glBufferData(GL_ARRAY_BUFFER, _meshData.m_uvs.size() * sizeof(_meshData.m_uvs.at(0)), _meshData.m_uvs.data(), GL_STATIC_DRAW);

				glEnableVertexAttribArray(static_cast<unsigned char>(BufferObject::TEXCOORD));
				glVertexAttribPointer(static_cast<unsigned char>(BufferObject::TEXCOORD), 2, GL_FLOAT, GL_FALSE, 0, nullptr);

				// Upload normals data
				glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[static_cast<unsigned char>(BufferObject::NORMAL)]);
				glBufferData(GL_ARRAY_BUFFER, _meshData.m_normals.size() * sizeof(_meshData.m_normals.at(0)), _meshData.m_normals.data(), GL_STATIC_DRAW);

				glEnableVertexAttribArray(static_cast<unsigned char>(BufferObject::NORMAL));
				glVertexAttribPointer(static_cast<unsigned char>(BufferObject::NORMAL), 3, GL_FLOAT, GL_FALSE, 0, nullptr);

				// Upload tangents data
				glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[static_cast<unsigned char>(BufferObject::TANGENT)]);
				glBufferData(GL_ARRAY_BUFFER, _meshData.m_tangents.size() * sizeof(_meshData.m_tangents.at(0)), _meshData.m_tangents.data(), GL_STATIC_DRAW);

				glEnableVertexAttribArray(static_cast<unsigned char>(BufferObject::TANGENT));
				glVertexAttribPointer(static_cast<unsigned char>(BufferObject::TANGENT), 3, GL_FLOAT, GL_FALSE, 0, nullptr);

				// Upload index data for indexed rendering
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_VBOs[static_cast<unsigned char>(BufferObject::INDEX)]);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, _meshData.m_indices.size() * sizeof(_meshData.m_indices.at(0)), _meshData.m_indices.data(), GL_STATIC_DRAW);

				// bind the buffer for world matrices
				glBindBuffer(GL_ARRAY_BUFFER, m_VBOs[static_cast<unsigned char>(BufferObject::WORLDMAT)]);
				// cannot upload mat4's all at once, so upload them as 4 vec4's
				for (size_t i = 0; i < 4; i++)
				{
						//enable the channel of the current matrix row (4,5,6,7)
						glEnableVertexAttribArray(static_cast<unsigned char>(BufferObject::WORLDMAT) + i);
						//tell opengl how to read it
						glVertexAttribPointer(static_cast<unsigned char>(BufferObject::WORLDMAT) + i, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4),
								(const void*)(sizeof(float) * i * 4));

						/** This function is what makes it per-instance data rather than per vertex
						* The first parameter is the attribute channel as above (4,5,6,7)
						* The second parameter tells the rate at which the attribute advanced during the rendering
						* 1 means that this data is updated after 1 instance has been rendered
						* by default it's 0 which makes it per-vertex and if it's over 1 than more than 1 instances will use this data
						*/
						glVertexAttribDivisor(static_cast<unsigned char>(BufferObject::WORLDMAT) + i, 1);
				}

				glBindVertexArray(0);
		}
}