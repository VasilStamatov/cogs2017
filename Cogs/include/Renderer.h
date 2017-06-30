#pragma once

#include <memory>

namespace cogs
{
		using uint = unsigned int;
		using VBO = uint;
		using VAO = uint;

		class Entity;

		/**
		* \brief Renderer base class
		*/
		class Renderer
		{
		public:
				Renderer() {}
				virtual ~Renderer() {}

				//The first function called by the renderer
				virtual void init() = 0;
				//Called at the beggining of every frame (to clear buffers of entities)
				virtual void begin() = 0;
				//Submit an entity to the entities buffer
				virtual void submit(Entity* _entity) = 0;
				//Called after all entities have been submitted, used for sorting/batching/culling
				virtual void end() = 0;
				//Flushes the renderer, rendering everything in the buffer
				virtual void flush() = 0;
				//disposes of buffer objects and data
				virtual void dispose() = 0;
		};
}