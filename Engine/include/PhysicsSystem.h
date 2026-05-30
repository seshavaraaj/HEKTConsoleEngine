#pragma once
#include <entt/entt.hpp>

namespace HEKTConsoleEngine
{
	class PhysicsSystem
	{
	public:
		PhysicsSystem(entt::registry& registry);
		void Update(float deltaTime);
	private:
		entt::registry& registry;
	};
}