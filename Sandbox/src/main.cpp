#include <Application.h>
#include <entt/entt.hpp>
#include <Components.h>
#include <EntityManager.h>

void Start();
void Update(float DeltaTime);
void MovePlayer();
HEKTConsoleEngine::Application App;

int main() {
	App.inputSystem.SetUsingKeys({ VK_LEFT , VK_RIGHT, VK_ESCAPE, VK_F3, VK_F4});

	App.DebugOn(VK_F3);
	App.QuitOn(VK_ESCAPE);

	App.OnStart = [&]()
		{
			Start();
		};
	App.OnUpdate = [&](float deltaTime)
		{
			Update(deltaTime);
		};

	App.Run();
	return 0;
}

int playerMovementSpeed = 100;

void Start()
{
	entt::entity Player = App.entityManager.CreateEntity();
	App.entityManager.AddComponent(Player, TransformComponent(5, 46));
	App.entityManager.AddComponent(Player, SpriteComponent(3, 3, "Player"));
	App.entityManager.AddComponent(Player, VelocityComponent(0, 0));
}

void Update(float DeltaTime)
{
	MovePlayer();
}

void MovePlayer()
{
	App.GetRegistry().view<VelocityComponent>().each([&](auto entity, auto& velocity) {
		if (App.inputSystem.GetKey(VK_LEFT))
			velocity.dx = -playerMovementSpeed;
		else if (App.inputSystem.GetKey(VK_RIGHT))
			velocity.dx = playerMovementSpeed;
		else
			velocity.dx = 0;
		});
}
