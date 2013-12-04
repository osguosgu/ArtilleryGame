#ifndef BASICCANNON_HH
#define BASICCANNON_HH

#include <SFML/Graphics.hpp>
#include <math.h>

class BasicCannon{
    
    public:
        BasicCannon(bool, sf::Vector2f, float);
        
        /* Get cannon sprite. */
        sf::Sprite getCannonSprite(){return cannonSprite;}
        
        /* Get turret sprit. */
        sf::Sprite getTurretSprite(){return turretSprite;}
        
        /* Check if cannon is in the middle of the firing animation.  */
        bool isFiring(){return firing;}    
        
       
        //void stopFiring(){firing = false;}
        
        /* Set the flag to start the firing animation.  */
        void startFiring(){firing = true;}
        
        /* Changes the turret image according to
        *  the current stage of the firing animation.
         */
        void fireAnimation();
        
        /* Move the cannon.
        * 
        *  @param v - vector holding the new cannon position.
         */
        void move(sf::Vector2f v);
        
        /* Rotate the cannons turret.
        *
        *  @param angle - the turrets new angle.
        */
        void rotate(int angle);
        
        sf::Vector2f getCollisionCoord();
        
        /* Get the bottom coordinate of the cannon.
        *  Can be used for checking if the cannon is touching the ground.
        *
        *  return - the coordinates of the cannon at its middle bottom.
         */
        sf::Vector2f getBottomCoord(){return cannonSprite.getPosition();}
        
	/*  Get the turrets edge coordinate.
        *
        *   return - a vector with the turrets edge coordinates
        */
	sf::Vector2f getFireCoord();
	
        /*  Get the cannons wheels bottom coordinate.
        *
        *   return - a vector with the wheels bottom coordinates.
        */
        sf::Vector2f getWheelCoord(){
            sf::Vector2f tmp(cannonSprite.getPosition());
            if(startRight){
                return sf::Vector2f(ceil(tmp.x*(1/7)), tmp.y);
            }else{
                return sf::Vector2f(floor(tmp.x*(6/7)), tmp.y);
            }
        }
        
        /*  Get the coordinates of the cannons support leg.
        *
        *   return - the cannons leg coordinates.
        */
        sf::Vector2f getLegCoord(){
            sf::Vector2f tmp(cannonSprite.getPosition());
            if(startRight) return sf::Vector2f(floor(tmp.x*(98/100)), tmp.y);
            else return sf::Vector2f(ceil(tmp.x*(1/100)), tmp.y);    
        }


    private:    
        
        sf::Image cannonImg;
        sf::Image turretImg;
        sf::Texture cannonTexture;
        sf::Texture turretTexture;
        sf::Sprite cannonSprite;
        sf::Sprite turretSprite;
        bool firing;
        bool moved;       
        sf::Vector2f collisionCoord;
        sf::Vector2f bottomCoord;
        sf::Vector2f startPos;
        bool startRight;
        int moveConstant;
        int firingStage;
        sf::Vector2i cannonSize;
        sf::Vector2i turretSize;

};




#endif
