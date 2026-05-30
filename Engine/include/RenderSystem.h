#pragma once
#include <entt/entt.hpp>
#include <Renderer.h>

namespace HEKTConsoleEngine
{
	class RenderSystem
	{
	public:
		RenderSystem(entt::registry& registry, Renderer& renderer);
		void Update();
		void RenderEntity(entt::entity entity);
	private:
		entt::registry& registry;
		Renderer& renderer;
	};
}