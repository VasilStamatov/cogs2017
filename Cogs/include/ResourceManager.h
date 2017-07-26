#pragma once

#include <map>
#include <string>
#include <memory>
#include <vector>

#include <glm\vec2.hpp>
#include "Object.h"

namespace cogs
{
		class ResourceManager
		{
		public:
				ResourceManager() {}
				~ResourceManager() {}

				ResourceManager(const ResourceManager& _other) = delete;
				ResourceManager& operator=(const ResourceManager& _rhs) = delete;

				template<typename T, typename... TArgs>
				inline T* get(const std::string& _resName, TArgs&&... _constructionArgs)
				{
						for (size_t i = 0; i < m_resources.size(); i++)
						{
								if (_resName == m_resources.at(i)->getName())
								{
										return static_cast<T*>(m_resources.at(i).get());
								}
						}
						T* newRes(new T(std::forward<TArgs>(_constructionArgs)...));
						newRes->setName(_resName);
						std::unique_ptr<Object> uPtr{ newRes };
						m_resources.emplace_back(std::move(uPtr));
						return newRes;
				}

				void refresh()
				{
						for (size_t i = 0; i < m_resources.size(); i++)
						{
								if (!m_resources.at(i)->isAlive())
								{
										m_resources.erase(m_resources.begin() + i);
										i--;
								}
						}
				}

		private:
				std::vector<std::unique_ptr<Object>> m_resources;
		};
}