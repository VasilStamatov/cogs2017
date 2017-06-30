#pragma once

#include "Component.h"
#include "GUI.h"

#include <functional>

namespace cogs
{
		class Button : public Component
		{
		private:
				CEGUI::PushButton* m_button;
		public:
				Button(const std::string& _name, const glm::vec4& _destRectPerc, const glm::vec4& _destRectPix);
				~Button();

				void setText(const std::string& _text);
				void addEvent(std::function<bool(const CEGUI::EventArgs&)> _funcPtr);

				void destroy();
		};
}