#pragma once

#include <string>

#include <EquinoxSTD.h>

#include "Texture.h"

namespace pulsar
{
	class Entity
	{
	public:
		Entity(const Window& window);
		Entity(const Window& window, const std::string& filePath,
			eqx::Rectangle<double> drawBox, double speed);
		Entity(const Entity& other);

		void operator= (const Entity& other);

		void render() const;
		const eqx::Rectangle<double>& getLocation() const;
		const Texture& getTexture() const;
		double getSpeed() const;
		eqx::Point<double> getDirection() const;
		bool targetReached() const;
		bool targetReached(eqx::Point<double> point) const;

		void setLocation(eqx::Point<double> point);
		void setRect(eqx::Rectangle<double> rect);
		void setSpeed(double speed);
		Texture& editTexture();
		eqx::Rectangle<double>& editRect();
		void move(double dt);
		void setTarget(eqx::Point<double> point);
		void setDirection(eqx::Point<double> point);

	private:
		const Window& m_Window;
		Texture m_Texture;
		eqx::Rectangle<double> m_DrawBox;
		eqx::Point<double> m_Direction, m_Target;
		double m_Speed;
	};
}