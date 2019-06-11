#include "init.hpp"
#include "MenuScene.hpp"
#include "GameScene.hpp"
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
        //gamescreen();
       /*else if(screenstate == GAMEOVER)
        gameover();
       else if(screenstate == VICTORY)
        victory();*/
    }

    destroy();

	return 0;
}
