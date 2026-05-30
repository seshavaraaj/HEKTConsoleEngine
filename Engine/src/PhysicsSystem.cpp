#include "PhysicsSystem.h"
#include <Components.h>

namespace HEKTConsoleEngine
{
	PhysicsSystem::PhysicsSystem(entt::registry& registry) : registry(registry)
	{
	}

	void PhysicsSystem::Update(float deltaTime)
	{
		auto view = registry.view<TransformComponent, VelocityComponent>();
		view.each([deltaTime](auto& transform, auto& velocity) {
			transform.x += velocity.dx * deltaTime;
			transform.y += velocity.dy * deltaTime;
			});
	}
}