#pragma once

#include <EquinoxSTD.hpp>
#include <SDL.h>

namespace pul
{
	class Mouse
	{
	public:
		enum class Button
		{
			up,
			down
		};

		Mouse() = delete;
		Mouse(const Mouse& other) = delete;
		Mouse(Mouse&& other) = delete;
		Mouse& operator= (const Mouse&& other) = delete;
		Mouse& operator= (Mouse&& other) = delete;
		~Mouse() = delete;

		static void handleEvent(const SDL_Event& e);
		static const eqx::Point<double>& getCurrentLocation();
		static const eqx::Point<double>& getLeftClickDownLocation();
		static const eqx::Point<double>& getLeftClickUpLocation();
		static const eqx::Point<double>& getRightClickDownLocation();
		static const eqx::Point<double>& getRightClickUpLocation();

	private:
		static eqx::Point<double> m_CurrentLocation,
			m_LeftClickDownLocation, m_LeftClickUpLocation,
			m_RightClickDownLocation, m_RightClickUpLocation;
		static Button m_LeftButtonState, m_RightButtonState;
	};
}
