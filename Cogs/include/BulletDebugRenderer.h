#pragma once

#include <Bullet\LinearMath\btIDebugDraw.h>
#include <vector>
#include <memory>
#include <glm\mat4x4.hpp>
#include "ResourceManager.h"

namespace cogs
{
		class GLSLProgram;
		class Entity;

		using VBO = unsigned int;
		using VAO = unsigned int;
		using IBO = unsigned int;

		//the debug vertex struct (a vertex has a position and a color)
		struct DebugVertex
		{
				btVector3 position;
				btVector3 color;
		};

		constexpr unsigned int DEBUG_POSITION_ATTRIBUTE_INDEX = 0;
		constexpr unsigned int DEBUG_COLOR_ATTRIBUTE_INDEX = 1;

		/**
		* \brief The renderer handling bullet physics debug rendering
		*/
		class BulletDebugRenderer final : public btIDebugDraw
		{
		public:
				BulletDebugRenderer();
			 ~BulletDebugRenderer();

				void init(ResourceManager& _rm);

				void drawMeshSphereBounds(Entity* _entity);

				virtual void	drawLine(const btVector3 & _from,
						const btVector3 & _to,
						const btVector3 & _color) override;

				virtual void drawContactPoint(const btVector3 & _PointOnB,
						const btVector3 & _normalOnB,
						btScalar _distance,
						int _lifeTime,
						const btVector3 & _color) override;
				
				virtual void reportErrorWarning(const char * _warningString) override;
				
				virtual void draw3dText(const btVector3 & _location, const char * _textString) override;
				
				virtual void setDebugMode(int _debugMode) override;
				
				virtual int  getDebugMode() const override;

				void end();

				void render(const glm::mat4& _view, const glm::mat4& _projection, float _lineWidth);

		private:
				std::vector<DebugVertex> m_verts;  
				std::vector<unsigned int> m_indices; 

				unsigned int m_vbo{ 0 };
				unsigned int m_ibo{ 0 };
				unsigned int m_vao{ 0 };

				unsigned int m_numElements{ 0 };

				GLSLProgram* m_shader;
				DebugDrawModes m_debugDrawMode{ DebugDrawModes::DBG_NoDebug };
		};
}