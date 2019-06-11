#include "init.hpp"
#include "mainmenu.hpp"

int main()
{
    init();

    while(!exit_program)
    {
		if (screenstate == MAINMENU) {
			MenuScene menu;
			menu.start();
		}
			
       /*else if(screenstate == GAMESCREEN)
        gamescreen();
       else if(screenstate == GAMEOVER)
        gameover();
       else if(screenstate == VICTORY)
        victory();*/
    }

    destroy();

	return 0;
}
