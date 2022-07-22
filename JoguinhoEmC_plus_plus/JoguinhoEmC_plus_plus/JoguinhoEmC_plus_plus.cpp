// JoguinhoEmC_plus_plus.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//
#include "Game.h"
int main()
{
    Game game;
    while (game.running())
    {
        game.update();
        game.render();
    }
    return 0;
};