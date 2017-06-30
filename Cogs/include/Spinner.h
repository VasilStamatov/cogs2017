#pragma once

#include "Component.h"
#include "GUI.h"

#include <functional>

namespace cogs
{
		class Spinner : public Component
		{
		public:
				Spinner(const std::string& _name, const glm::vec4& _destRectPerc, const glm::vec4& _destRectPix);
				~Spinner();

				void addEvent(std::function<bool(const CEGUI::EventArgs&)> _funcPtr);

				void setMinValue(float _val);
				void setMaxValue(float _val);
				void setCurrentValue(float _val);
				void setStepSize(float _val);

				float getCurrentValue() const noexcept;

				void destroy();

		private:
				CEGUI::Spinner* m_spinner;
		};
}