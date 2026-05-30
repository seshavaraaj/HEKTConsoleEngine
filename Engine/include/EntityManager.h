#pragma once
#include <entt/entt.hpp>
#include <Components.h>

namespace HEKTConsoleEngine
{
	class EntityManager
	{
	public:
		EntityManager(entt::registry& registry) : registry(registry) {}
		entt::entity CreateEntity();
		template<typename T>
		T& AddComponent(entt::entity entity, T&& component);
	private:
		entt::registry& registry;
	};

	inline entt::entity EntityManager::CreateEntity()
	{
		entt::entity entityCreated = registry.create();
		return entityCreated;
	}

	template<typename T>
	T& EntityManager::AddComponent(entt::entity entity, T&& component)
	{
		return registry.emplace<T>(entity, std::forward<T>(component));
	}
}