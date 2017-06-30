#include "../include/Light.h"
#include "../include/Entity.h"

namespace cogs
{
		std::vector<Light*> Light::s_allLights;

		Light::Light()
		{
				s_allLights.push_back(this);
		}
		Light::~Light()
		{
				for (size_t i = 0; i < s_allLights.size(); i++)
				{
						if (s_allLights.at(i) == this)
						{
								s_allLights.erase(s_allLights.begin() + i);
						}
				}
		}
		
		glm::vec3 Light::getPosition()
		{
				return m_entity->transform()->worldPosition();
		}
		glm::vec3 Light::getDirection()
		{
				return m_entity->transform()->worldForwardAxis();
		}
}