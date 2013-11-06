#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

#include "terrain.hh"
//#include "player.hh"
#include "physics.hh"
#include "cannonBall.hh"

#define PI 3.14159265

void drawCircle(CannonBall c, sf::RenderWindow &win){
    sf::CircleShape shape(10.f);
    shape.setPosition( (sf::Vector2f) c.getCoord());
    shape.setFillColor(sf::Color::Green);
    win.draw(shape);
    

}
int main()
{

    sf::RenderWindow window(sf::VideoMode(1000, 600), "Artillery TEST");
    window.setFramerateLimit(60);
    Terrain terrain = Terrain(window.getSize());
    
    sf::Texture tex;
    sf::Sprite spr;

    sf::Image img = terrain.getImage();
    img.createMaskFromColor(sf::Color::White);
    tex.loadFromImage(img);
    spr.setTexture(tex, true);
    terrain.update();

    std::vector<CannonBall> balls;

    bool mouseDown = false;
    sf::Mouse::setPosition(sf::Vector2i(500,500), window);
    while  (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();

            //mouse events-------------------

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !mouseDown){
                mouseDown = true;
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                float angle = PI/6;
                int mass = 5;
                int powder = 100;

                CannonBall ball(pos, angle, mass, powder);

                fire(ball);

                balls.push_back(ball);
                //terrain.destroyTerrain(sf::Vector2u(pos.x, pos.y), 30);
            }
            else if (! sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                mouseDown = false;
            }
        }
        

        window.clear(sf::Color::Yellow);
        if (terrain.needsUpdate()){
            sf::Image img = terrain.getImage();
            img.createMaskFromColor(sf::Color::White);
            tex.loadFromImage(img);
            spr.setTexture(tex, true);
            terrain.update();
        }
        int counter = 0;
        for (CannonBall &c : balls){
            
            nextCoord(c);
            if( terrain.hit(c.getCoord() )){
                terrain.destroyTerrain(c.getCoord(), 40);
                balls.erase(balls.begin() + counter );
            }
            else drawCircle(c, window);
            counter += 1;
             
        }
        window.draw(spr);
        window.display();
    }

    return 0;
}
