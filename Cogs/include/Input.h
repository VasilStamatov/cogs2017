#pragma once

#include <unordered_map>
#include <glm/vec2.hpp>
#include "KeyCode.h"

namespace cogs
{
		class Input
		{
		public:
				static void update();
				static void pressKey(unsigned int _keyID);
				static void releaseKey(unsigned int _keyID);
				static bool isKeyDown(const KeyCode& _keyID);
				static bool isKeyPressed(const KeyCode& _keyID);
				static const glm::vec2& getMouseCoords() noexcept { return m_mouseCoords; }
				static void setMouseCoords(float _x, float _y);
				static const glm::vec2& getMouseMotion() noexcept { return m_mouseMotion; }
				static void setMouseMotion(float _x, float _y);

		private:
				Input() {}
				~Input() {}

				static bool wasKeyDown(const KeyCode& _keyID);

		private:
				static std::unordered_map<KeyCode, bool> m_keyMap; ///< the map of the keys pressed this frame
				static std::unordered_map<KeyCode, bool> m_previousKeyMap; ///< the map of the keys pressed last frame
				static glm::vec2 m_mouseCoords; ///< mouse coordinates in screen space
				static glm::vec2 m_mouseMotion; ///< mouse motion
		};
}