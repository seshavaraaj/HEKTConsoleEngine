#pragma once
#include <entt/entt.hpp>
#include <vector>
#include <Components.h>

namespace HEKTConsoleEngine
{
	class PhysicsSystem
	{
	public:
		PhysicsSystem(entt::registry& registry);
		void VelocityUpdate(float deltaTime);
		void CollisionUpdate();
		bool OnCollision(entt::entity checkingEntity, std::string targetTag);
	private:
		std::vector<CollisionInfo> collisionInfos;
		entt::registry& registry;
	};
}