//Доработайте код так, чтобы шарики отскакивали друг от друга


#include <SFML/Graphics.hpp>
#include <circle.hpp>
#include <game.hpp>

int main()
{
    //парамерты окна и название
    sn::Game game(1000, 600, "game");
    game.Setup(5);//кол-во фигур каждого вида
    game.LifeCycle();
   
    return 0;
}
