#include "PhysicsSystem.h"

namespace HEKTConsoleEngine
{
	PhysicsSystem::PhysicsSystem(entt::registry& registry) : registry(registry)
	{
	}

	void PhysicsSystem::VelocityUpdate(float deltaTime)
	{
		auto view = registry.view<TransformComponent, VelocityComponent>();
		view.each([deltaTime](auto& transform, auto& velocity) {
			transform.x += velocity.dx * deltaTime;
			transform.y += velocity.dy * deltaTime;
			});
	}

	void PhysicsSystem::CollisionUpdate()
	{
		auto view = registry.view<TransformComponent, ColliderComponent, TagComponent>();
		view.each([this](auto entity, auto& transform, auto& collider, auto& tag) {
			if (collider.isTrigger) return;
			// Check for collisions with other entities
			auto otherView = registry.view<TransformComponent, ColliderComponent, TagComponent>();
			otherView.each([this, entity, &transform, &collider](auto otherEntity, auto& otherTransform, auto& otherCollider, auto& otherTag) {
				if (otherEntity == entity || otherCollider.isTrigger) return;
				// Simple AABB collision detection
				if (transform.x < otherTransform.x + otherCollider.width &&
					transform.x + collider.width > otherTransform.x &&
					transform.y < otherTransform.y + otherCollider.height &&
					transform.y + collider.height > otherTransform.y) {
					// Collision detected
					collisionInfos.push_back({ entity, otherEntity });
				}
				});
			});
	}

	bool PhysicsSystem::OnCollision(entt::entity checkingEntity, std::string targetTag)
	{
		for (const auto& collisionInfo : collisionInfos)
		{
			if (collisionInfo.checkingEntity == checkingEntity)
			{
				auto& collidingEntity = collisionInfo.collidingEntity;
				if (auto* tagComponent = registry.try_get<TagComponent>(collidingEntity))
				{
					if (tagComponent->tag == targetTag)
					{
						return true;
					}
				}
			}
		}
		return false;
	}
}