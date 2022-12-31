#pragma once

#include <EquinoxSTD.h>

#include "Window.h"

namespace pulsar
{
	class Texture
	{
	public:
		Texture(const Window& window);
		Texture(const Window& window, const std::string& filePath);
		Texture(const Texture& other);
		~Texture();

		void operator= (const Texture& other);

		bool loadFile(const std::string& filePath);
		template <typename T>
		bool render(const eqx::Point<T>& point, float scale = 1.0f) const
		{
			eqx::Rectangle<int> rect = {
				static_cast<int>(point.x),
				static_cast<int>(point.y),
				m_Width,
				m_Height
			};
			return render(rect, scale);
		}
		bool render(int x, int y, float scale = 1.0f) const;

		template <typename T>
		bool render(const eqx::Rectangle<T>& dest, float scale = 1.0f) const
		{
			SDL_Rect source = {
				static_cast<int>(m_SourceRect.x),
				static_cast<int>(m_SourceRect.y),
				static_cast<int>(m_SourceRect.w),
				static_cast<int>(m_SourceRect.h) };
			SDL_Rect scaled = {
				static_cast<int>(dest.x),
				static_cast<int>(dest.y),
				static_cast<int>(dest.w * scale),
				static_cast<int>(dest.h * scale) };
			SDL_Point rotationPoint = {
				m_RotationPoint.x,
				m_RotationPoint.y };
			if (SDL_RenderCopyEx(m_Window.getRenderer(), m_SdlTexture, &source, &scaled, m_Angle, &rotationPoint, m_Flip) == -1)
			{
				eqx::Log::log(eqx::Log::Level::error, std::string("Texture Render Error! SDL Error: ") + SDL_GetError(), eqx::Log::Type::runtimeError);
				return false;
			}
			return true;
		}

		void setSourceRect(const eqx::Rectangle<int>& source);
		bool modColor(Uint8 r, Uint8 g, Uint8 b);
		void setAngle(double degrees);
		void rotate(double degrees);
		void setRotationPoint(const eqx::Point<int>& point);
		void hFlip();
		void unFlip();
		bool isFliped() const;

		const eqx::Rectangle<int>& getSourceRect() const;
		int getWidth() const;
		int getHeight() const;
		double getAngle() const;
		const eqx::Point<int>& getRotationPoint() const;
		std::string getFilepath() const;

	private:
		const Window& m_Window;
		std::string m_Filepath;
		SDL_Texture* m_SdlTexture;
		SDL_RendererFlip m_Flip;
		double m_Angle;
		int m_Width, m_Height;
		Uint8 m_Red, m_Green, m_Blue;
		eqx::Point<int> m_RotationPoint;
		eqx::Rectangle<int> m_SourceRect;
	};
}