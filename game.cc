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
#include "status.hh"
#include <string>
#include <sstream>
#define PI 3.14159265

void drawCircle(sf::Vector2i coord, sf::RenderWindow &win, float r, sf::Color color){
    sf::CircleShape shape(r);
    shape.setPosition( (sf::Vector2f) coord);
    shape.setFillColor(color);
    win.draw(shape);
}

int main(int argc, char* argv [])
{
    //-------------------------------INIT--------------------------------
    //
    //commandline arguments
    std::string p1_name = "Player 1";
    std::string p2_name = "Player 2";
    unsigned int width = 1000;
    unsigned int height = 600;
    if (argc == 3 || argc == 5){
        p1_name = argv[1];
        p2_name = argv[2];
        if (argc == 5){
            width = atoi(argv[3]);
            height = atoi(argv[4]);
        }
    }

    std::cout << width << " " << height << std::endl;

    std::vector<sf::Text> p1status;
    std::vector<sf::Text> p2status;
    sf::Font font;
	font.loadFromFile("media/arial.ttf");
	
    //init rand
    srand(time(NULL));
    //set up the window
    sf::RenderWindow window(sf::VideoMode(width, height), "Artillery Game v0.9");
    window.setFramerateLimit(60);
    Terrain terrain = Terrain(window.getSize());
    //make textures and terrain sprite, music and other stuff
    sf::Texture background;
    std::string bgs  [] = {
    "media/bg1.jpg",
    "media/bg2.jpg",
    "media/bg3.jpg",
    "media/bg4.jpg"};
    background.loadFromFile(bgs[rand()%(sizeof(bgs) / sizeof(std::string))]);
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
    //make players
    Player p1 = Player(1,p1_name, sf::Vector2f(window.getSize().x/9,10), sf::Color::Black);
    Player p2 = Player(2,p2_name, sf::Vector2f(window.getSize().x*9/10,10), sf::Color::Black);

    BasicCannon cannon1(false, sf::Vector2f(p1.getCoord()), p1.getAngle());
    BasicCannon cannon2(true,  sf::Vector2f(p2.getCoord()), p2.getAngle());

    bool p1Fire = false;
    bool p2Fire = false;
    
        
    //----------- Back ground for status ----------------
    sf::RectangleShape rectangle;		// rectangle for player data
	rectangle.setSize(sf::Vector2f(window.getSize().x-2, window.getSize().y/16));
	rectangle.setOutlineColor(sf::Color::Black);
	rectangle.setFillColor(sf::Color(255,255,255,150));
	rectangle.setOutlineThickness(1);
	rectangle.setPosition(1, 1);
    //----------- Initialize Wind text -------------------
    double wind = getWind();
    sf::Text textWind("Wind: " + toString(wind),font,0.025*window.getSize().y);
    sf::FloatRect textRectWind = textWind.getLocalBounds();
    textWind.setOrigin(textRectWind.width/2,textRectWind.height/2);

    textWind.setColor(sf::Color::Red);
    textWind.setPosition(window.getSize().x/2, window.getSize().y/32);

    //get sounds into buffers
    sf::Music music;
    music.openFromFile("media/music1.ogg");
    music.setVolume(30);
    music.setLoop(true);

    sf::SoundBuffer exp;
    exp.loadFromFile("media/exp.ogg");
    sf::Sound explosion;
    explosion.setBuffer(exp);
    
    sf::SoundBuffer s;
    s.loadFromFile("media/shot.ogg");
    sf::Sound shot;
    shot.setBuffer(s);
    initStatus(p1, window, p1status, font); // player status
    initStatus(p2, window, p2status, font);
    
    sf::SoundBuffer v1;
    v1.loadFromFile("media/victory1.ogg");
    sf::Sound vic1;
    vic1.setBuffer(v1);

    sf::SoundBuffer v2;
    v2.loadFromFile("media/victory2.ogg");
    sf::Sound vic2;
    vic2.setBuffer(v2);
    //--------------------------THE game loop---------------------------
    int powder_counter = 0;
    int wind_counter = 1;
    
    bool started = false;
    int score [2] = {0,0};
    sf::Text start("Score:\n"+ p1.getName() +": "+toString( score[0])+ " wons\n"+ p2.getName()+ ": "+toString( score[1] )+ " wons\n\nGenerate maps by pressing return.\nPress 'p' when ready to start", font, 30);
    sf::FloatRect startRect = start.getLocalBounds();
    start.setOrigin(startRect.width/2,startRect.height/2);
    start.setColor(sf::Color::Black);
    start.setPosition(window.getSize().x/2, window.getSize().y/3);
   
  
    bool exit = false;
    while  (window.isOpen())
    {
        sf::Event event;
        music.play();
        while (!started){
               
            window.pollEvent(event);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                return 0;
            }
            if (event.type == sf::Event::Closed)
                window.close();
                exit = true;
                
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
                terrain = Terrain(window.getSize());
                sf::Image img = terrain.getImage();
                img.createMaskFromColor(sf::Color::White);
                tex.loadFromImage(img);
                sTerrain.setTexture(tex, true);
                terrain.update();
                background.loadFromFile(bgs[rand()%(sizeof(bgs) / sizeof(std::string))]);
                bg.setTexture(background);

            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
                started = true;
                
            }
            window.clear();
            window.draw(bg);
            window.draw(sTerrain);
            window.draw(start);
            window.display();
        }
        music.stop();
            

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
                
    
            //--------------------INPUTS---------------------------
            if (event.type == sf::Event::KeyPressed){     
                //PLAYER 1
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
                    return 0;

                        }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && !p1Fire){
                    p1Fire = true;

                    if(p1.getCharge() >0){
                        shot.play();
                        if (p1.getWeapon() == 1){
                            CannonBall ball = CannonBall(1, sf::Vector2f(p1.getCoord().x, p1.getCoord().y-15), p1.getAngle(), p1.getCharge());
                            fire<CannonBall>(ball);
                            balls.push_back(ball);
                            //updateStatus(p1, p1status);
                        }
                        else if (p1.getWeapon() == 2){
                            CannonBall ball = CannonBall(2, sf::Vector2f(p1.getCoord().x, p1.getCoord().y-15), p1.getAngle(), p1.getCharge());
                            fire<CannonBall>(ball);
                            balls.push_back(ball);
                        }
                        else if (p1.getWeapon() == 3){
                            CannonBall ball = CannonBall(3, sf::Vector2f(p1.getCoord().x, p1.getCoord().y-15), p1.getAngle(), p1.getCharge());
                            fire<CannonBall>(ball);
                            balls.push_back(ball);
                        }             
                   
                    p1.resetCharge();
                    updateStatus(p1, p1status); 
                    
                    } 
                   
                }
                else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::E))   p1Fire = false;
                
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)){ // less charge
                         p1.setCharge(false);
                         updateStatus(p1, p1status);
                }
                         
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)){ // more charge
                         p1.setCharge(true);
                         updateStatus(p1, p1status);
                        }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)){
                         p1.changeWeapon();
                         updateStatus(p1, p1status);
                         }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){ //rotate up
                        if(p1.getAngle() + 0.05 < 1.6354) p1.rotateLeft();  
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){ //rotate down
                        if(p1.getAngle() >= -0.364602) p1.rotateRight();
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))         p1.moveLeft(terrain);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))         p1.moveRight(terrain);
                
                //PLAYER 2

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return) && !p2Fire){ 
                    p2Fire = true;
                    if(p2.getCharge() >0){
                        shot.play();
                        if (p2.getWeapon() == 1){
                            CannonBall ball = CannonBall(1, sf::Vector2f(p2.getCoord().x, p2.getCoord().y-15), p2.getAngle(), p2.getCharge());
                            fire<CannonBall>(ball);
                            balls.push_back(ball);
                        }
                        else if (p2.getWeapon() == 2){
                            CannonBall ball = CannonBall(2, sf::Vector2f(p2.getCoord().x, p2.getCoord().y-15), p2.getAngle(), p2.getCharge());
                            fire<CannonBall>(ball);
                            balls.push_back(ball);
                        }
                        else if (p2.getWeapon() == 3){
                            CannonBall ball = CannonBall(3, sf::Vector2f(p2.getCoord().x, p2.getCoord().y-15), p2.getAngle(), p2.getCharge());
                            fire<CannonBall>(ball);
                            balls.push_back(ball);
                        }
                    //p2.resetCharge();
                    updateStatus(p2, p2status);
                    p2.resetCharge();
                    }
                    
                    //updateStatus(p2, p2status);
                    
                    
                    
                }
                else if(!sf::Keyboard::isKeyPressed(sf::Keyboard::Return))    p2Fire = false;
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)){	//decrease charge	 
                        p2.setCharge(false);
                        updateStatus(p2, p2status);
                
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)){ //increase charge
                         p2.setCharge(true);
                        updateStatus(p2, p2status);
                }	
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)){ //change weapon
                         p2.changeWeapon();
                         updateStatus(p2, p2status);
                         }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){ //rotate up
                        if(p2.getAngle() > 1.5562) p2.rotateRight();
                          
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){//rotate down
                    if(p2.getAngle() <= 3.80619)p2.rotateLeft();

                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))      p2.moveLeft(terrain);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))     p2.moveRight(terrain);
               
                
            }
            
        }
        //if terrain is hit 
        if (terrain.needsUpdate()){
            sf::Image img = terrain.getImage();
            img.createMaskFromColor(sf::Color::White);
            tex.loadFromImage(img);
            sTerrain.setTexture(tex, true);
            terrain.update();
        }
        //if players doesn't touch ground
        //
       
        if (!terrain.collide(p1.getCollisionList()))
            nextCoord<Player>(p1);
        else{
            p1.setCoord(sf::Vector2f(p1.getCoord().x, terrain.getY(sf::Vector2f(p1.getCoord()))));
            p1.setSpeed(sf::Vector2f(0,0));
        }
        if (!terrain.collide(p2.getCollisionList()))
            nextCoord<Player>(p2);
        else{
            p2.setCoord(sf::Vector2f(p2.getCoord().x, terrain.getY(sf::Vector2f(p2.getCoord()))));
            p2.setSpeed(sf::Vector2f(0,0));
        }
        
        
       //-------------DRAWING------------------

        
        window.clear(sf::Color::Yellow);
        window.draw(bg);
        
        int counter = 0;
        for (CannonBall &c : balls){
            
            nextCoord<CannonBall>(c);
            if(terrain.outOfBounds(c.getCoord().x, c.getCoord().y))
                balls.erase(balls.begin() + counter );
                 

            else if(c.getCoord().y < 0)
                continue;

            else if( terrain.hit(c.getCoord())){
                if (c.getType() == 1 || c.getType() == 3){
                    terrain.destroyTerrain(c.getCoord(), c.getMass() * 5);
                    for(int i = 0; i < rand() % 300 + 100 ; i++){
                        float angle = rand() % 100;
                        sf::Vector2f speed = sf::Vector2f(cos(angle) * ((rand() % 7) /( rand() % 2 +1)),
                                sin(angle)* ((rand() % 7) /( rand() % 2 +1)));
                        particles.push_back(Particle(speed,
                                    sf::Vector2f(c.getCoord().x,c.getCoord().y)));
                    }
                    explosion.play();
                    p1.updateHealth(c);
                    p2.updateHealth(c);
                }
                else if (c.getType() == 2 && !terrain.outOfBounds(c.getCoord().x, c.getCoord().y)){
                    int uusx = c.getCoord().x;
                    int uusy = c.getCoord().y;
                    balls.erase(balls.begin() + counter);
                    for (float i = -1; i < 1; i += 0.25 ){
                        CannonBall ball = CannonBall(1 ,sf::Vector2f(uusx, uusy), PI/2 + i, 10);
                        fire<CannonBall>(ball);
                        balls.push_back(ball);
                        counter += 1;
                    
                    } 
                }
                //drawCircle(c.getCoord(), window, 10, sf::Color::Red);

                
                

                balls.erase(balls.begin() + counter );
            }
            else if (c.getType() == 1)drawCircle(c.getCoord(), window, 3, sf::Color::Black);
            else if (c.getType() == 2)drawCircle(c.getCoord(), window, 3, sf::Color::Red);
            else if (c.getType() == 3)drawCircle(c.getCoord(), window, 3, sf::Color::Green);
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
            else drawCircle(p.getCoord(), window, 1 , sf::Color(100,100,100));
            counter += 1;
             
        }
		
        //adding powder
        if (powder_counter > 10){
        	
        	
        	
            powder_counter = 0;
            p1.setPowder(1);
            p2.setPowder(1);
            updateStatus(p1, p1status);
            updateStatus(p2, p2status);
        } 
        if(wind_counter > 200){
        //-------------Change WIND randomly-----
        	// this is here to reduce computations
        	srand(time(NULL));

			int windchange = rand() % 100;
			if(windchange > 85){
        	updateWind();
       		}
       		wind_counter = 0;
		}       		
        powder_counter +=1;
        wind_counter +=1;
		
        cannon1.rotate(-1*p1.getAngle() * (180/PI) - 180);
        cannon2.rotate(-1*p2.getAngle() * (180/PI) + 180);
        cannon1.move(sf::Vector2f(p1.getCoord()));
        cannon2.move(sf::Vector2f(p2.getCoord()));
        
        //end of the game check
        if ((unsigned int)p1.getCoord().y >= window.getSize().y-1){
            p1.kill();
        }
        else if ((unsigned int)p2.getCoord().y >= window.getSize().y-1){
            p2.kill();
        }
        
        if(p1.getHealth() <= 0 || p2.getHealth() <= 0){
            music.stop();
            vic1.play();
            vic2.play();
        	updateStatus(p1, p1status);
            updateStatus(p2, p2status);
        	sf::Text text;
            if(p2.getHealth() <= 0) {
                text = sf::Text(p1.getName()+" wins!", font, 30 );
                score[0] += 1;
            }
    		else {
                text = sf::Text(p2.getName()+" wins!", font, 30 );
                score[1] += 1;
            }
            sf::FloatRect textRect = text.getLocalBounds();
            text.setOrigin(textRect.width/2,textRect.height/2);

    		text.setColor(sf::Color::Black);
    		text.setPosition(window.getSize().x/2, window.getSize().y/2);
    		window.draw(text);
        	
        	window.display();
        
	        sleep(5);
            //reset the game
            //
            p1 = Player(1,p1_name, sf::Vector2f(window.getSize().x/9,10), sf::Color::Black);
            p2 = Player(2,p2_name, sf::Vector2f(window.getSize().x*9/10,10), sf::Color::Black);

            cannon1.move(sf::Vector2f(p1.getCoord()));
            cannon1.rotate(p1.getAngle());
            cannon2.move( sf::Vector2f(p2.getCoord()));
            cannon2.rotate( p2.getAngle());

            p1Fire = false;
            p2Fire = false;

        	started = false;
            start.setString("Score:\n"+ p1.getName() +": "+toString( score[0])+ " wons\n"+ p2.getName()+ ": "+toString( score[1] )+ " wons\n\nGenerate maps by pressing return.\nPress 'p' when ready to start");
        
        }
        window.draw(cannon1.getCannonSprite());
        window.draw(cannon1.getTurretSprite());

        window.draw(cannon2.getCannonSprite());
        window.draw(cannon2.getTurretSprite());
        window.draw(rectangle);      // background for status
        drawstatus(window,p1status); // player1 status
        drawstatus(window,p2status); // player2 status
        drawWind(window,textWind);   // wind

        window.draw(sTerrain);
        window.display();
    }
    if (exit || !window.isOpen()) return 0;
}
