#include "init.hpp"
#include "MenuScene.hpp"
#include "GameScene.hpp"
#include "LoseScene.hpp"
#include "WinScene.hpp"
#include <iostream>

using namespace std;

int main()
{
    init();

    while(!exit_program)
    {
		if (scenestate == MAINMENU) {
			cout << "menu" << endl;
			MenuScene menu;
			menu.start();
		}		
		else if (scenestate == GAMESCENE) {
			cout << "game" << endl;
			GameScene game;
			game.start();
		}
		else if (scenestate == GAMEOVER) {
			LoseScene gameover;
			gameover.start();
		}
		else if (scenestate == VICTORY) {
			WinScene victory;
			victory.start();
		}
    }

    destroy();

	return 0;
}
