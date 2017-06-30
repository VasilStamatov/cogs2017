#include "../include/ParticleSystem.h"

#include "../include/Entity.h"
#include "../include/Camera.h"
#include "../include/Random.h"
#include "../include/GLTexture2D.h"
#include "../include/ParticleRenderer.h"
#include "../include/BulletDebugRenderer.h"

#include <glm\gtx\norm.hpp>

namespace cogs
{
		ParticleSystem::ParticleSystem(ParticleRenderer* _renderer,
				int _maxParticles,
				float _particlePerSec,
				float _initialSpeed,
				float _width,
				float _decayRate,
				bool _additive,
				bool _playOnInit,
				const glm::vec3& _worldGravity,
				const Color& _color,
				GLTexture2D* _texture,
				std::function<void(Particle&, const glm::vec3&, float)> _updateFunc) :
				m_maxParticles(_maxParticles),
				m_particlesPerFrame(1.0f / _particlePerSec),
				m_initialSpeed(_initialSpeed),
				m_particlesRadius(_width * 0.5f),
				m_decayRate(_decayRate),
				m_additive(_additive),
				m_playOnInit(_playOnInit),
				m_worldGravity(_worldGravity),
				m_particlesColor(_color),
				m_renderer(_renderer),
				m_texture(_texture),
				m_updateFunc(_updateFunc)
		{
				m_particles = new Particle[m_maxParticles];
		}
		ParticleSystem::~ParticleSystem()
		{
				delete[] m_particles;
		}

		void ParticleSystem::init()
		{
				if (m_playOnInit)
				{
						play();
				}
		}

		void ParticleSystem::update(float _deltaTime)
		{
				if (m_isPlaying)
				{
						if (!m_isStopped)
						{
								generateParticles(_deltaTime);
						}
						for (int i = 0; i < m_numActiveParticles; ++i)
						{
								// Update using function pointer
								m_updateFunc(m_particles[i], m_worldGravity, _deltaTime);

								//reduce its life by decay amount with frame independence
								m_particles[i].m_life -= (m_decayRate * _deltaTime);

								if (m_particles[i].m_life <= 0.0f)
								{
										freeParticle(i);
								}
						}
				}
		}

		void ParticleSystem::render()
		{
				m_renderer->submit(m_entity);
		}

		void ParticleSystem::play()
		{
				m_isPlaying = true;
		}

		void ParticleSystem::pause()
		{
				m_isPlaying = false;
		}

		void ParticleSystem::continueEmitting()
		{
				m_isStopped = false;
		}

		void ParticleSystem::togglePlayOnInit()
		{
				m_playOnInit = !m_playOnInit;
		}

		void ParticleSystem::stopEmitting()
		{
				m_isStopped = true;
		}

		bool ParticleSystem::isPlaying()
		{
				return m_isPlaying;
		}

		bool ParticleSystem::isStopped()
		{
				return m_isStopped;
		}

		void ParticleSystem::setTexture(GLTexture2D* _texture)
		{
				m_texture = _texture;
		}

		void ParticleSystem::setDecayRate(float _decayRate)
		{
				m_decayRate = _decayRate;
		}

		void ParticleSystem::setParticlesWidth(float _width)
		{
				m_particlesRadius = _width * 0.5f;
		}

		void ParticleSystem::setInitialSpeed(float _initialSpeed)
		{
				m_initialSpeed = _initialSpeed;
		}

		void ParticleSystem::setAdditive(bool _flag)
		{
				m_additive = m_additive;
		}

		void ParticleSystem::setWorldGravity(const glm::vec3 & _gravity)
		{
				m_worldGravity = _gravity;
		}

		void ParticleSystem::setUpdateFunc(std::function<void(Particle&, const glm::vec3&, float)> _updateFunc)
		{
				m_updateFunc = _updateFunc;
		}

		void ParticleSystem::setRenderer(ParticleRenderer* _renderer)
		{
				m_renderer = _renderer;
		}

		void ParticleSystem::generateParticles(float _deltaTime)
		{
				// limit the particles per sec accumulation to 60 fps minimum
				// otherwise if it goes too low it will start spawning massive amounts at once
				// and make it even slower
				if (_deltaTime > 0.016f)
				{
						_deltaTime = 0.016f;
				}
				m_accumulator += _deltaTime;
				while (m_accumulator > m_particlesPerFrame)
				{
						spawnParticle();
						m_accumulator -= m_particlesPerFrame;
				}
		}

		void ParticleSystem::spawnParticle()
		{
				if (m_numActiveParticles == m_maxParticles)
				{
						//no more free particles (range is 0 to max - 1)
						return;
				}
				//generate random directions in the x,y and z axis
				float dirX = Random::getRandFloat(-1.0f, 1.0f);
				float dirY = Random::getRandFloat(-1.0f, 1.0f);
				float dirZ = Random::getRandFloat(-1.0f, 1.0f);
				glm::vec3 vel = glm::normalize(glm::vec3(dirX, dirY, dirZ));
				vel *= m_initialSpeed;

				auto& particle = m_particles[m_numActiveParticles];

				//give it a full life as it's being spawned
				particle.m_life = 1.0f;

				//set its world position to the position of the entity, but with a little random offset
				particle.m_position = m_entity->transform()->worldPosition() + (Random::getRandFloat(-2.0f, 2.0f));

				//set its velocity to the emitting velocity
				particle.m_velocity = vel;

				//set its color to the set color for all particles
				particle.m_color = m_particlesColor;

				//set the particle radius
				particle.m_radius = m_particlesRadius;

				//set the particle mass
				//particle.m_mass = m_particlesMass;

				//increment the number of active particles as a new one has spawned
				m_numActiveParticles++;
		}

		void ParticleSystem::freeParticle(int _particleIndex)
		{
				//decrement the num active particles as 1 is being freed
				m_numActiveParticles--;
				//set the particle to be freed to the last active particle (acts as deleting)
				m_particles[_particleIndex] = m_particles[m_numActiveParticles];
		}
}