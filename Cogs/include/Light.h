#pragma once

#include "Component.h"

#include <vector>

namespace cogs
{
		class Transform;

		enum class LightType : unsigned char
		{
				DIRECTIONAL,
				POINT,
				SPOT
		};

		struct Attenuation
		{
				Attenuation() {}
				Attenuation(float _constant, float _linear, float _quadratic) :
						m_constant(_constant), m_linear(_linear), m_quadratic(_quadratic) {}

				float m_constant{ 0.0f };
				float m_linear{ 0.0f };
				float m_quadratic{ 0.0f };
		};

		class Light : public Component
		{
		public:
				Light();
				~Light();

				void setLightType(const LightType& _lightType) { m_lightType = _lightType; }
				void setAttenuation(const Attenuation& _attenuation) { m_attenuation = _attenuation; }
				void setColor(const glm::vec3& _color) { m_lightColor = _color; }
				void setAmbientIntensity(float _intensity) { m_ambientIntensity = _intensity; }
				void setDiffuseIntensity(float _intensity) { m_diffuseIntensity = _intensity; }
				void setSpecularIntensity(float _intensity) { m_specularIntensity = _intensity; }
				void setCutOff(float _cutOff) { m_cutOff = _cutOff; }
				void setOuterCutOff(float _outerCutOff) { m_outerCutOff = _outerCutOff; }

				const LightType& getLightType()		   const noexcept { return m_lightType; }
				const Attenuation& getAttenuation()	const noexcept { return m_attenuation; }
				const glm::vec3& getColor()  const noexcept { return m_lightColor; }
				float getAmbientIntensity()  const noexcept { return m_ambientIntensity; }
				float getDiffuseIntensity()  const noexcept { return m_diffuseIntensity; }
				float getSpecularIntensity() const noexcept { return m_specularIntensity; }
				float getCutOff()											 const noexcept { return m_cutOff; }
				float getOuterCutOff()							const noexcept { return m_outerCutOff; }
				glm::vec3 getPosition();
				glm::vec3 getDirection();

				static std::vector<Light*> getAllLights() { return s_allLights; }

		private:
				static std::vector<Light*> s_allLights;

				glm::vec3			m_lightColor{ 1.0f, 1.0f, 1.0f };
				Attenuation m_attenuation;
				float					  m_ambientIntensity{ 1.0f };
				float					  m_diffuseIntensity{ 1.0f };
				float					  m_specularIntensity{ 1.0f };
				float					  m_cutOff{ 0.0f };
				float					  m_outerCutOff{ 0.0f };
				LightType			m_lightType{ LightType::POINT };
		};
}