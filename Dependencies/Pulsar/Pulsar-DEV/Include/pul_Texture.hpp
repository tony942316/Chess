#pragma once

#include <string_view>

#include <EquinoxSTD.hpp>
#include <SDL.h>

namespace pul
{
	class Texture
	{
	public:
		Texture();
		Texture(SDL_Renderer* renderer, std::string_view filePath);

		~Texture();

		void setRenderer(SDL_Renderer* renderer);
		void loadFile(std::string_view filePath);
		void render(eqx::Point<double> location) const;
		void render(eqx::Rectangle<double> destination) const;

	private:
		int m_Width, m_Height;

		SDL_Texture* m_SdlTexture;
		SDL_Renderer* m_Renderer;
	};
}