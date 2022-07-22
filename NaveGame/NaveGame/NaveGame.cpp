// NaveGame.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include "Game.h"

int main()
{
    std::srand(static_cast<unsigned>(time(NULL)));

    Game game;
    std::cout << "Por favor, insira a dificuldade." << std::endl;
    std::cout << "Podes selecionar oque quiser, porem para evitar problemas de travamento, recomendamos que coloque estas velocidades:\n\n";
    std::cout << "2 para velocidade e 15 para tempo de spawn\nSe quiser algo mais complicado, coloque 3 de velocidade e 10 de tempo de spawn\n";
    std::cout << "Se quiser algo EXTREMO, coloque 4 de velocidade 5 de tempo de spawn\n\n";
    unsigned short number;
    std::cout << "Velocidade do jogo: ";
    std::cin >> number;
    std::cout << "Tempo de spawn: ";
    game.setDificuldade(number);

    while (game.running())
    {
        game.update();
        game.render();
    }
    game.savePoints();
    return 0;
};