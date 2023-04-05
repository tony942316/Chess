#pragma once

#include <string_view>

#include <EquinoxSTD.hpp>

#include "pul_Texture.hpp"

namespace pul
{
	class Entity
	{
	public:
		Entity();
		Entity(SDL_Renderer* renderer, std::string_view filePath,
			eqx::Rectangle<double> drawBox, double speed);

		void render() const;
		const eqx::Rectangle<double>& getLocation() const;
		const Texture& getTexture() const;
		double getSpeed() const;
		eqx::Point<double> getDirection() const;
		bool targetReached() const;
		bool targetReached(eqx::Point<double> point) const;

		void setTexture(SDL_Renderer* renderer, std::string_view filePath);
		void setLocation(eqx::Point<double> point);
		void setRect(eqx::Rectangle<double> rect);
		void setSpeed(double speed);
		Texture& editTexture();
		eqx::Rectangle<double>& editRect();
		void move(double dt);
		void setTarget(eqx::Point<double> point);
		void setDirection(eqx::Point<double> point);

	private:
		Texture m_Texture;
		eqx::Rectangle<double> m_DrawBox;
		eqx::Point<double> m_Direction, m_Target;
		double m_Speed;
	};
}