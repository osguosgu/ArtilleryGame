#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

#include <iostream>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include "terrain.hh"
#include "player.hh"
#include "physics.hh"
#include "cannonBall.hh"
#include "particle.hh"

#define PI 3.14159265

void drawCircle(sf::Vector2i coord, sf::RenderWindow &win, float r, sf::Color color){
    sf::CircleShape shape(r);
    shape.setPosition( (sf::Vector2f) coord);
    shape.setFillColor(color);
    win.draw(shape);
}
   
//draw player status
//from arkanoid
template <typename T>
std::string toString(const T& v)
{
  std::ostringstream oss;
  oss << v;
  return oss.str();
}

/*

void drawStatus(Player& p) 


  {
  	sf::Font font;
	font.loadFromFile("media/arial.ttf");
  	int healt = p.getHealth();
    sf::Text text(toString(healt), font, 25);
    text.setPosition(40, 40);
    win.draw(text);
  }

*/

int main()
{
    //-------------------------------INIT--------------------------------
    //
    //init rand
    srand(time(NULL));
    //set up the window
    sf::RenderWindow window(sf::VideoMode(1000, 600), "Artillery TEST");
    window.setFramerateLimit(60);
    Terrain terrain = Terrain(window.getSize());
    //make textures and terrain sprite 
    sf::Texture background;
    if(!background.loadFromFile("media/bg1.jpg")){}
        //poikkeus
    sf::Sprite bg;
    bg.setTexture(background);

    sf::Texture tex;
    sf::Sprite sTerrain;

    sf::Image img = terrain.getImage();
    img.createMaskFromColor(sf::Color::White);
    tex.loadFromImage(img);
    sTerrain.setTexture(tex, true);
    terrain.update();
    //make vector for the cannonballs and particles
    std::vector<CannonBall> balls;
    std::vector<Particle> particles;
    sf::Vector2f startLeft(100,0);
    sf::Vector2f startRight(900,0);
    //make players
    BasicCannon cannon1(false, startLeft);
    BasicCannon cannon2(true, startRight);
    
    sf::CircleShape tykki(20);
    sf::CircleShape tykki2(20);
    tykki.setFillColor(sf::Color::Black);
    tykki2.setFillColor(sf::Color::Yellow);

    Player p1 = Player(1,"Oskari", sf::Vector2f(100,0), sf::Color::Black, true, cannon1);
    Player p2 = Player(2,"Heikki", sf::Vector2f(900,0), sf::Color::Black, false, cannon2);
    bool p1Fire = false;
    bool p2Fire = false;
    
    //sf::Mouse::setPosition(sf::Vector2i(500,500), window);
    
    //get sounds into buffers
    sf::SoundBuffer exp;
    exp.loadFromFile("media/exp.ogg");
    sf::Sound explosion;
    explosion.setBuffer(exp);
    //--------------------------THE game loop---------------------------
    while  (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();

            //--------------------INPUTS---------------------------
            //PLAYER 1
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && !p1Fire){
                p1Fire = true;
                sf::Vector2f pos;
                pos.x = p1.getCoord().x;
                pos.y = p1.getCoord().y;
                CannonBall ball = CannonBall( pos, p1.getAngle(), 5, p1.getPowder());
 
                fire<CannonBall>(ball);
                balls.push_back(ball);
            }
            else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::W))   p1Fire = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))         p1.rotateLeft();  
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))         p1.rotateRight();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))         p1.moveLeft();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))         p1.moveRight();

            //PLAYER 2

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P) && !p2Fire){ 
                p2Fire = true;
                sf::Vector2f pos;
                pos.x = p2.getCoord().x;
                pos.y = p2.getCoord().y;
                CannonBall ball = CannonBall( pos, p2.getAngle(), 5, p2.getPowder());
                fire<CannonBall>(ball);
                balls.push_back(ball);
            }
            else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::P))    p2Fire = false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))        p2.rotateRight();  
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))      p2.rotateLeft();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))      p2.moveLeft();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))     p2.moveRight();
           
            
        }
        

        window.clear(sf::Color::Yellow);
        //if terrain is hit 
        if (terrain.needsUpdate()){
            sf::Image img = terrain.getImage();
            img.createMaskFromColor(sf::Color::White);
            tex.loadFromImage(img);
            sTerrain.setTexture(tex, true);
            terrain.update();
        }
        //if players doesn't touch ground
        if (!terrain.collide(p1.getCollisionList()))
            nextCoord<Player>(p1);
        else p1.setSpeed(sf::Vector2f(0,0));

        if (!terrain.collide(p2.getCollisionList()))
            nextCoord<Player>(p2);
        else p2.setSpeed(sf::Vector2f(0,0));
        
        
        //-------------WIND-------------------
        srand(time(NULL));

		int windchange = rand() % 5;
		
		if(windchange==0){
        	updateWind();
        }
       //-------------DRAWING------------------

        
        window.draw(bg);
        
        int counter = 0;
        for (CannonBall &c : balls){
            
            nextCoord<CannonBall>(c);
            if(terrain.outOfBounds(c.getCoord().x, c.getCoord().y))
                balls.erase(balls.begin() + counter );

            else if(c.getCoord().y < 0)
                continue;

            else if( terrain.hit(c.getCoord())){
                terrain.destroyTerrain(c.getCoord(), 40);
                for(int i = 0; i < rand()%500+50 ; i++){
                    float angle = rand() % 100;
                    sf::Vector2f speed = sf::Vector2f(cos(angle)*(i%4), sin(angle)*(i%4));
                    particles.push_back(Particle(speed,
                                sf::Vector2f(c.getCoord().x, c.getCoord().y)));
                }
                
                explosion.play();

                balls.erase(balls.begin() + counter );
            }
            else drawCircle(c.getCoord(), window, 3, sf::Color::Green);
            counter += 1;
             
        }
        //init counter before particle round
        counter = 0;

        for (Particle &p : particles){
            
            nextCoord<Particle>(p);
            if(terrain.outOfBounds(p.getCoord().x, p.getCoord().y))
                particles.erase(particles.begin() + counter );

            else if(p.getCoord().y < 0)
                continue;

            else if( terrain.hit(p.getCoord())){
                particles.erase(particles.begin() + counter );
            }
            else drawCircle(p.getCoord(), window, 1 , sf::Color::Black);
            counter += 1;
             
        }
        tykki.setPosition(p1.getCoord().x, p1.getCoord().y-20);
        tykki2.setPosition(p2.getCoord().x, p2.getCoord().y-20);
        window.draw(tykki);
        window.draw(tykki2);
        window.draw(sTerrain);
        window.draw(cannon2.getTurretSprite());
        window.display();
    }

    return 0;
}
