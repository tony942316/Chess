#pragma once

#include <EquinoxSTD.hpp>

#include "pul_Texture.hpp"

namespace pul
{
	class Entity
	{
	public:
		Entity() noexcept;
		Entity(Texture& texture, const eqx::Rectangle<double>& location,
			double speed) noexcept;

		void render() const noexcept;

		[[nodiscard]] bool targetReached() const noexcept;
		[[nodiscard]] bool rotationTargetReached() const noexcept;
		void move(double dt) noexcept;
		void rotate(double dt) noexcept;

		void setRotationDirection(int direction) noexcept;
		void setSpeed(double speed) noexcept;
		void setRotationSpeed(double speed) noexcept;
		void setRotationTarget(double target) noexcept;
		void setDirection(const eqx::Point<double>& direction) noexcept;
		void setTarget(const eqx::Point<double>& target) noexcept;
		void setRotationPoint(const eqx::Point<double>& point) noexcept;
		void setTexture(Texture& texture) noexcept;
		void setLocation(const eqx::Point<double>& point) noexcept;
		void setDrawBox(const eqx::Rectangle<double>& rect) noexcept;
		void setColor(const Texture::Color& rgb) noexcept;

		[[nodiscard]] eqx::Rectangle<double>& editDrawBox() noexcept;

		[[nodiscard]] int getRotationDirection() const noexcept;
		[[nodiscard]] double getSpeed() const noexcept;
		[[nodiscard]] double getRotationSpeed() const noexcept;
		[[nodiscard]] double getRotationTarget() const noexcept;
		[[nodiscard]] const eqx::Point<double>& getDirection() const noexcept;
		[[nodiscard]] const eqx::Point<double>& getTarget() const noexcept;
		[[nodiscard]] const eqx::Point<double>& 
			getRotationPoint() const noexcept;
		[[nodiscard]] eqx::Point<double> getLocation() const noexcept;
		[[nodiscard]] const eqx::Rectangle<double>& 
			getDrawBox() const noexcept;
		[[nodiscard]] double getAngle() const noexcept;
		[[nodiscard]] const Texture::Color& getColor() const noexcept;

		static constexpr inline auto c_MaxSpeed = 1'000'000.0;

	private:
		int m_RotationDirection;
		double m_Speed, m_RotationSpeed, m_RotationTarget;

		eqx::Point<double> m_Direction, m_Target;

		Texture* m_Texture;
		Texture::Config m_RenderConfiguration;
	};
}