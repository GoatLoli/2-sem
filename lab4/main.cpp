//Отобразите на экране набор фигур : N (кругов, треугольников, прямоугольников, линий)
//N - натуральное число, не превосходящее 10

#include <SFML/Graphics.hpp>
#include <figure.hpp>
#include <game.hpp>

int main()
{
    //парамерты окна и название
    sn::Game game(1000, 600, "game");
    game.Setup(4);//кол-во фигур каждого вида
    game.LifeCycle();
   
    return 0;
}
