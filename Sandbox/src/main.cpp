#include <Application.h>

HEKTConsoleEngine::Application App;
entt::entity player = App.entityManager.CreateEntity();

void Start();
void Update(float deltaTime);

int main() {
	App.inputSystem.SetUsingKeys({ VK_LEFT , VK_RIGHT, VK_ESCAPE, VK_F3, VK_F4});

	App.DebugOn(VK_F3);
	App.QuitOn(VK_ESCAPE);

	App.OnStart = Start;

	App.OnUpdate = Update;

	App.Run();
	return 0;
}

void Start() {
	SpriteComponent playerSpriteComponent = App.spriteParser.ParseSpriteComponent("assets/sprites/SpaceShip.sprite");
	App.entityManager.AddComponent(player, SpriteComponent(playerSpriteComponent));
	App.entityManager.AddComponent(player, TransformComponent(10, 50));
	App.entityManager.AddComponent(player, VelocityComponent(0.0f, 0.0f));
}

void Update(float deltaTime) {
	if (App.inputSystem.GetKey(VK_LEFT))
	{
		App.GetRegistry().get<VelocityComponent>(player).dx = -100.0f;
	}
	else if (App.inputSystem.GetKey(VK_RIGHT))
	{
		App.GetRegistry().get<VelocityComponent>(player).dx = 100.0f;
	}
	else
	{
		App.GetRegistry().get<VelocityComponent>(player).dx = 0.0f;
	}
}
