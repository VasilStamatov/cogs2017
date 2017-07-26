#pragma once

#include <string>

namespace cogs
{
		class Object
		{
		public:
				Object();
				virtual ~Object();

				void destroy();
				void setName(const std::string& _name);
				const std::string& getName() const noexcept;
				bool isAlive() const noexcept;

				static void destroy(Object* _obj);

		private:
				std::string m_name{""};
				bool m_alive{ true };
		};
}