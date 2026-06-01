#include <Application.h>

HEKTConsoleEngine::Application App;
entt::entity player = App.entityManager.CreateEntity();
entt::entity enemy = App.entityManager.CreateEntity();

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
	SpriteComponent playerSpriteComponent = App.spriteParser.ParseSpriteComponent("assets/sprites/SpaceShip.sprite", HEKTConsoleEngine::Color::White);
	App.entityManager.AddComponent(player, SpriteComponent(playerSpriteComponent));
	App.entityManager.AddComponent(player, TransformComponent(10, 50));
	App.entityManager.AddComponent(player, VelocityComponent(0.0f, 0.0f));
	App.entityManager.AddComponent(player, TagComponent("Player"));
	App.entityManager.AddComponent(player, ColliderComponent(
		playerSpriteComponent.height, 
		playerSpriteComponent.width, 
		playerSpriteComponent.width / 2, 
		playerSpriteComponent.height / 2,
		false));

	SpriteComponent enemySpriteComponent = App.spriteParser.ParseSpriteComponent("assets/sprites/Enemy.sprite", HEKTConsoleEngine::Color::Red);
	App.entityManager.AddComponent(enemy, SpriteComponent(enemySpriteComponent));
	App.entityManager.AddComponent(enemy, TransformComponent(50, 10));
	App.entityManager.AddComponent(enemy, VelocityComponent(0.0f, 0.0f));
	App.entityManager.AddComponent(enemy, TagComponent("Enemy"));
	App.entityManager.AddComponent(enemy, ColliderComponent(
		enemySpriteComponent.height,
		enemySpriteComponent.width,
		enemySpriteComponent.width / 2,
		enemySpriteComponent.height / 2,
		false));

}

void Update(float deltaTime) {
	if (!App.GetRegistry().valid(player))
		return;

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

	if (App.physicsSystem.OnCollision(player, "Enemy"))
	{
		App.GetRegistry().destroy(player);
	}
}
