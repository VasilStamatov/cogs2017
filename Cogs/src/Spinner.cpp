#include "../include/Spinner.h"

namespace cogs
{
		Spinner::Spinner(const std::string & _name, const glm::vec4& _destRectPerc, const glm::vec4& _destRectPix)
		{
				m_spinner = static_cast<CEGUI::Spinner*>(GUI::createWidget(GUI::getSchemeName() + "/Spinner", _destRectPerc, _destRectPix, _name));
		}

		Spinner::~Spinner()
		{
				if (!GUI::isFreed())
				{
						destroy();
				}
				m_spinner = nullptr;
		}

		void Spinner::addEvent(std::function<bool(const CEGUI::EventArgs&)> _funcPtr)
		{
		}
		void Spinner::setMinValue(float _val)
		{
				m_spinner->setMinimumValue(_val);
		}
		void Spinner::setMaxValue(float _val)
		{
				m_spinner->setMaximumValue(_val);
		}
		void Spinner::setCurrentValue(float _val)
		{
				m_spinner->setCurrentValue(_val);
		}
		void Spinner::setStepSize(float _val)
		{
				m_spinner->setStepSize(_val);
		}
		float Spinner::getCurrentValue() const noexcept
		{
				return (float)m_spinner->getCurrentValue();
		}
		void Spinner::destroy()
		{
				GUI::destroyWidget(m_spinner);
		}
}