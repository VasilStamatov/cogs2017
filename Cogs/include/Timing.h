#pragma once

#include <chrono>

namespace cogs
{
		using HRTimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
		
		class HRTimer
		{
		public:
				HRTimer();
				~HRTimer();

				void start(bool _reset = true);
				void stop();
				float seconds() const;
				float milli() const;
				
				bool isActive() const noexcept { return m_isActive; }

		private:
				HRTimePoint m_start;
				HRTimePoint m_stop;

				bool m_isActive{ false };
		};

		class FpsLimiter
		{
		public:
				FpsLimiter(float _maxFPS);
				~FpsLimiter();

				void setMaxFPS(float _maxFPS);
				void beginFrame();
				float endFrame();

				float fps()						 const noexcept { return m_fps; }
				float deltaTime() const noexcept { return m_deltaTime; }

		private:
				void sleep(float _millis);

		private:
				HRTimer m_timer;
				float m_fps{ 0.0f };				
				float m_deltaTime{ 0.0f };
				float m_desiredMillis{ 0.0f };
		};
}
