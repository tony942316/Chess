#pragma once

#include <string>
#include <string_view>

#include <EquinoxSTD.hpp>
#include <SDL.h>

namespace pul
{
	class Texture
	{
	public:
		struct Color
		{
			uint8_t r, g, b;
		};

		struct Config
		{
			eqx::Rectangle<double> destination;
			double angle;
			eqx::Point<double> rotationPoint;
			SDL_RendererFlip flip;
			Color rgb;
		};

		Texture() noexcept;
		Texture(SDL_Renderer* renderer, std::string_view filePath) noexcept;

		Texture(const Texture& other) noexcept;
		Texture(Texture&& other) noexcept;
		Texture& operator= (const Texture& other) noexcept;
		Texture& operator= (Texture&& other) noexcept;

		~Texture() noexcept;

		void setRenderer(SDL_Renderer* renderer) noexcept;
		void loadFile(std::string_view filePath) noexcept;

		void render(const eqx::Point<double>& location) const noexcept;
		void render(const eqx::Rectangle<double>& destination) const noexcept;
		void render(const Config& config) const noexcept;

	private:
		int m_Width, m_Height;

		std::string m_FilePath;

		SDL_Texture* m_SdlTexture;
		SDL_Renderer* m_Renderer;
	};
}