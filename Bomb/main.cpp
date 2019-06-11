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
		if (screenstate == MAINMENU) {
			cout << "menu" << endl;
			MenuScene menu;
			menu.start();
		}
			
		else if (screenstate == GAMESCENE) {
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
