#include <SFML/Graphics.hpp>
#include <ctime>
#include <iostream>
//using namespace sf;

//g++ -c main.cpp -I"D:/Test game/Sources/include"
//g++ -c main.cpp -I"D:\SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit\SFML-2.6.1\include" 
//g++ main.o -o main -L "D:\SFML-2.6.1-windows-gcc-13.1.0-mingw-64-bit\SFML-2.6.1\lib" -lsfml-graphics -lsfml-window -lsfml-system
//mingw32-make

int N = 30;
int M = 20;
int size = 40;
int w = size*N;
int h = size*M;

int food_x = rand()%30*size;
int food_y = (rand()%18 + 2)*size;

int score = 0;


struct p{
    int x;
    int y;
} 
p[100];
int length = 1;

int end_x = 0;
int end_y = 0;

bool is_lose = false;

int main()
{
    sf::RenderWindow window(sf::VideoMode(w,h), "Snake1.0");
    window.setFramerateLimit(15);
    srand(time(0));

    sf::Texture t1,t2,food;
    t1.loadFromFile("whiteimg.png");
    t2.loadFromFile("redimg.png");
    food.loadFromFile("food.png");

    sf::Sprite sprite1(t1);
    sf::Sprite sprite2(t2);
    sf::Sprite sp_food(food);
    sp_food.setColor(sf::Color::Green);
    int snake_x = 10*size;
    int snake_y = 5*size;
    sprite2.setPosition(snake_x, snake_y);

    sf::Font font;
    font.loadFromFile("Arial.ttf");
    sf::Text text;
    text.setFont(font);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
        }

        window.clear();

        

        if (!is_lose)
        {
            std::string temp = "Your score: ";
            std::string res = temp + std::to_string(score);
            text.setString(res);
            text.setCharacterSize(2*size - 20);
            text.setFillColor(sf::Color::White);
            window.draw(text);


            for (int i=0;i<N;i++){
                for (int j=2;j<M;j++){
                    sprite1.setPosition(i*size,j*size);
                    window.draw(sprite1);
                }
            }

            for (int i=0;i<length;i++)
            {
                sprite2.setPosition(p[i].x, p[i].y);
                window.draw(sprite2);
            }


            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) ) 
            {   snake_x+=size; 
                end_x = p[length-1].x;
                end_y = p[length-1].y;
                for (int i=length-1;i>0;i--)
                    {
                        p[i].x = p[i-1].x;
                        p[i].y = p[i-1].y;
                    }
            }
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) ) 
            {   snake_x-=size; 
                end_x = p[length-1].x;
                end_y = p[length-1].y;
                for (int i=length-1;i>0;i--)
                    {
                        p[i].x = p[i-1].x;
                        p[i].y = p[i-1].y;
                    }
            }
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) ) 
            {   snake_y-=size; 
                end_x = p[length-1].x;
                end_y = p[length-1].y;        
                for (int i=length-1;i>0;i--)
                    {
                        p[i].x = p[i-1].x;
                        p[i].y = p[i-1].y;
                    }
            }
            if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) ) 
            {   snake_y+=size; 
                end_x = p[length-1].x;
                end_y = p[length-1].y;
                for (int i=length-1;i>0;i--)
                    {
                        p[i].x = p[i-1].x;
                        p[i].y = p[i-1].y;
                    }
            }
            if (snake_x<0) snake_x = w - size;
            if (snake_x>w-size) snake_x = 0 ;
            if (snake_y<2*size) snake_y = h - size;
            if (snake_y>h-size) snake_y = 2*size;

            p[0].x = snake_x;
            p[0].y = snake_y;


            if (snake_x ==  food_x && snake_y  ==  food_y) 
            {
                food_x = rand()%30*size;
                food_y = (rand()%18 + 2)*size;

                //Make food different snake
                bool meet = false;
                while (!meet)
                {
                    for (int i=0;i<length;i++)
                    {
                        if (p[i].x == food_x && p[i].y == food_y) 
                        {
                            food_x = rand()%30*size;
                            food_y = (rand()%18 + 2)*size;
                            break;
                        }
                    }
                    meet = true;
                }

                score++;
                p[length].x = end_x;
                p[length].y = end_y;
                length++;
            }

            sp_food.setPosition(food_x,food_y);
            window.draw(sp_food);

            if (score==15)
            {
                window.clear();
                sf::Texture win;
                win.loadFromFile("win_window.png");
                sf::Sprite win_window(win);
                win_window.setPosition(0,2*size);
                window.draw(win_window);
                window.draw(text);
            }
            for (int i=1;i<length;i++){
                if (p[0].x == p[i].x && p[0].y == p[i].y)
                {
                    is_lose = true;
                }
            }


        }
        else 
        {
            sf::Texture lose;
            lose.loadFromFile("lose_window.png");
            sf::Sprite lose_window(lose);
            lose_window.setPosition(0,2*size);
            window.clear();
            window.draw(lose_window);
            window.draw(text);

        }
        


        window.display();

    }   

}