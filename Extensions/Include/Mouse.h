#pragma once

#include <SDL.h>
#include <EquinoxSTD.h>

namespace pulsar
{
	class Mouse
	{
	public:
		enum class Button
		{
			up,
			down
		};

		static void handleEvent(const SDL_Event& e);

		Mouse(const Mouse& m) = delete;
		void operator= (const Mouse& m) = delete;

		static eqx::Point<double> Location,
			LeftClickDownLocation, RightClickDownLocation,
			LeftClickUpLocation, RightClickUpLocation;
		static Button LeftButton, RightButton;

	private:
		Mouse();
		static Mouse& getInstance();

		void refresh();
	};
}