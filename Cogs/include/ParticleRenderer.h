#pragma once

#include "Renderer.h"
#include "Color.h"
#include "ResourceManager.h"

#include <unordered_map>
#include <vector>
#include <glm\vec4.hpp>

namespace cogs
{
		constexpr uint PARTICLE_POSITION_ATTRIBUTE	  = 0;
		constexpr uint PARTICLE_WORLDNSIZE_ATTRIBUTE	= 1;
		constexpr uint PARTICLE_COLOR_ATTRIBUTE					 = 2;
		constexpr uint PARTICLE_TEXOFFSETS_ATTRIBUTE = 3;
		constexpr uint PARTICLE_BLEND_ATTRIBUTE					 = 4;
		constexpr uint PARTICLE_MAX_INSTANCES					 		= 10000;

		class GLSLProgram;

		class ParticleRenderer : public Renderer
		{
		public:
				ParticleRenderer(ResourceManager& _rm);
				~ParticleRenderer();

				//The first function called by the renderer
				void init() override;
				//Called at the beggining of every frame (to clear buffers of entities)
				void begin() override;
				//Submit an entity to the entities buffer
				void submit(Entity* _entity) override;
				//Called after all entities have been submitted, used for sorting/batching/culling
				void end() override;
				//Flushes the renderer, rendering everything in the buffer
				void flush() override;
				//disposes of buffer objects and data
				void dispose() override;

		private:
				void sortParticles();

				enum class BufferObjects : unsigned int
				{
						POSITION,
						INSTANCED_ATTRIBS,

						INDEX,

						NUM_BUFFERS
				};

				struct InstanceAttributes
				{
						glm::vec4 worldPosAndSize;
						glm::vec4 texOffsets;
						Color color;
						float blendFactor;
				};

				struct InstanceData
				{
						std::vector<InstanceAttributes> instanceAttribs;
						float texNumOfRows{ 0.0f };
						bool isTexAdditive{ true };
				};

		private:
				//key = texture id (all sprites of the same texture to be instanced rendered)
				//value = instance data = per instance data
				std::unordered_map<unsigned int, InstanceData> m_particlesMap;
				ResourceManager& m_rm;
				VBO m_VBOs[static_cast<unsigned char>(BufferObjects::NUM_BUFFERS)] = { 0 }; ///< the vbos
				VAO m_VAO{ 0 };
				GLSLProgram* m_shader;
		};
}