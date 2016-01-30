#include <SFML/Graphics.hpp>
#include "GameManager.h"

int main()
{
	GameManager* gameManager = new GameManager();
	gameManager->run();
	delete gameManager;
	return 0;
}