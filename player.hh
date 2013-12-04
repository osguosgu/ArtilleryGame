#ifndef PLAYER_HH
#define PLAYER_HH

#include <vector>
#include <string>
#include <math.h>
#include <SFML/Graphics.hpp>
#include "basicCannon.hh"
#include "cannonBall.hh"
#define PI 3.14159265
class Player{
	
    public:
        Player(int num, std::string name, sf::Vector2f coords, sf::Color color) 
        :num(num),name(name), coords(coords), color(color), health(100), powder(100), charge(0){
        if (num == 1) angle = PI / 4;
        else angle = (3*PI) / 4;
        speed = sf::Vector2f(0,0);
        weapon = 1; 
        }

        /* Get the players name. */
        std::string getName() const {return name;}

        /* Get the players health. */
        int getHealth() const {return health;}
        
        /* Set the players health to zero. Used when player falls off the screen. */
        void kill() {health = 0;}
        
        /* Get powder amount. */
        int getPowder() const {return powder;}
        
        /* Get player number. */
        int getNum() const {return num;};
        
        /* Get the current charge. */
        int getCharge() const { return charge;}
        
        /* Change the powder amount. */
        void setPowder(int amount) {if (powder+charge < 100) powder += amount;}

	void resetCharge(){/*powder -= charge;*/ charge = 0;}
	
        /* Function for increasing and decreasing the charge. */
        void setCharge(bool load) // add charge if there is still powder
	{
	    	if(load)
	    	{ 
	    	    if(powder > 1){
	    	        charge += 1;
	    	        powder -= 1;
	    	        return;
	    	    }
	    	    else{
	    	        return;
	    	    }
	    }
	    else if ( charge > 1){
	    	charge -=1;
                powder +=1;
	    }
	    return;	
	}
	    
        /* Change the cannon ball to fire. */
	void changeBall(){
	    if(ballSelection == 2){ 
	    	ballSelection = 5;
	    	return;
	    }
	    
	    if(ballSelection == 5){
	    	ballSelection = 10;
	    	return;
	    }
	    if(ballSelection == 10){
	    	ballSelection = 2;
	    	return;
	    }
	}
	    
        /* Get the current select cannon ball. */
	int getballSelection(){
	    return ballSelection;
	}
	    
        /*  Get the players coordinate.  */
        sf::Vector2i getCoord() const {
                sf::Vector2<int> intcoord;
                intcoord.x = int(coords.x);
                intcoord.y = int(coords.y);
                return intcoord;
            }
	    
        /* Get the players color. */
        sf::Color getColor() const{return color;}

        /* Get the firing angle of the player. */
        float getAngle() const {return angle;}
	
        /* Update players healt according to the received damage. */    
        void updateHealth(int damage){health -= damage;}
        
        /* Update the players coordinates. */
        void updateCoord(){
            coords += speed;
        }

        /* Set the players coordinates. */
	void setCoord(sf::Vector2f newCoord){coords = newCoord;}
        
        /* Set the players speed. */
        void setSpeed(sf::Vector2<float> newspeed){  
            speed=newspeed;
	}

        /* Update the players health. Used when cannon ball hits the player or near the player. */
        void updateHealth(CannonBall& ball){
            int x = abs(coords.x - ball.getCoord().x);
            int y = abs(coords.y - ball.getCoord().y);

            if (x < ball.getMass()*10 && y < ball.getMass()*10){
                health -= (ball.getMass()*35)/(1+x+y); //Risk for division with zero without +1.
            }
        }
        
        /* Move player up one pixel. */
        void moveUp(){
            coords.y += 1;
        }

        /* Move the player right one pixel. */
        void moveRight(Terrain& terrain){
             coords.x += 1;
            if (terrain.isWall(coords)){
                coords.x -= 2;           
            }
            else if (terrain.collide(getCollisionList())){
                coords.y = terrain.getY(coords);
            }
        }

        /*  Move the player left one pixel. */
        void moveLeft(Terrain& terrain){
            coords.x -= 1;
            if (terrain.isWall(coords)){
                coords.x += 2;           
            }
            else if (terrain.collide(getCollisionList())){
                coords.y = terrain.getY(coords);
            }
        }

        /*  Rotate the firing angle right. */
        void rotateRight(){angle -= 0.05;}
        
        /*  Rotate the firing angle left. */
        void rotateLeft(){angle += 0.05;}

        /* Get the players collision coordinates. */
        std::vector<sf::Vector2u> getCollisionList(){
            std::vector<sf::Vector2u> list;
            list.push_back(sf::Vector2u(coords));
            //list.push_back(sf::Vector2u((unsigned int)cannonWheel.x, (unsigned int)cannonWheel.y));
            //list.push_back(sf::Vector2u((unsigned int)cannonLeg.x, (unsigned int)cannonLeg.y));
            //list.push_back(sf::Vector2u((unsigned int)turret.x, (unsigned int)turret.y));
            return list;
        }

        /*  Set the players speed. */
        sf::Vector2f getSpeed() const{return speed;}


        int getWeapon() const{
            return weapon;
        }
        void changeWeapon(){
            weapon = weapon + 1; // weapons: 1,2,3
            if(weapon == 4) weapon = 1;

        }
		/*
        void drawCannon(sf::RenderWindow& window){
             window.draw(cannon.getCannonSprite());
             window.draw(cannon.getTurretSprite());   
        }
                  
        
   
        BasicCannon getCannon(){return cannon;}

        bool detectHit(sf::Vector2f coords, float radius){
            
            sf::Rect<int> c(cannon.getRectShape());
            sf::CircleShape ballShape(radius);
            ballShape.setPosition(coords);
            sf::Rect<int> b(ballShape.getGlobalBounds());

            bool result = c.intersects(b);
            
            return result;
        }*/

	private:
        
	    int num;
	    std::string name;
	    sf::Vector2f coords;
	    sf::Color color;
	    //BasicCannon cannon;
        int health;
        int powder;
        int charge;
        int ballSelection; // 2= light, 5 = medium, 10 = heavy
        float angle;
        sf::Vector2f speed;
        int weapon;

};


#endif
