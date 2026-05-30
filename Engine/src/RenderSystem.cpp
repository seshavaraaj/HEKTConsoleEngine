#include "RenderSystem.h"
#include <Components.h>

namespace HEKTConsoleEngine
{
	RenderSystem::RenderSystem(entt::registry& registry, Renderer& renderer) : registry(registry), renderer(renderer)
	{
	}

	void RenderSystem::Update()
	{
		auto view = registry.view<TransformComponent, SpriteComponent>();
		
		view.each([this](auto entity, auto& transform, auto& sprite) {
			RenderEntity(entity);
			});
	}

	void RenderSystem::RenderEntity(entt::entity entity)
	{
		auto& transform = registry.get<TransformComponent>(entity);
		auto& sprite = registry.get<SpriteComponent>(entity);
		renderer.SetBufferString((int)transform.x, (int)transform.y, sprite.width, sprite.height, sprite.spriteData, Color::White);
	}
}