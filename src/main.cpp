#include "Random.h"
#include "Engine.h"
#include "SceneGame.h"
#include "SceneInventory.h"
#include "SceneMenu.h"
#include "ScenePause.h"

int main(int argc, char *argv[])
{
	random_init_time();

	Engine engine;

	engine.addScene(L"Menu", new SceneMenu());
	engine.addScene(L"Game", new SceneGame());
	engine.addScene(L"Pause", new ScenePause());
	engine.addScene(L"Inventory", new SceneInventory());

	engine.run();

	return 0;
}