#include "../include/Object.h"

namespace cogs
{
		Object::Object()
		{
		}
		Object::~Object()
		{
		}
		void Object::destroy()
		{
				m_alive = false;
		}
		void Object::setName(const std::string & _name)
		{
				m_name = _name;
		}
		const std::string & Object::getName() const noexcept
		{
				return m_name;
		}
		bool Object::isAlive() const noexcept
		{
				return m_alive;
		}
		void Object::destroy(Object * _obj)
		{
				_obj->m_alive = false;
		}
}