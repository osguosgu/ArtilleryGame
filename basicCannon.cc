#include "basicCannon.hh"

#include <iostream>
#define PI 3.14159265

BasicCannon::BasicCannon(bool startRight, sf::Vector2f startPos, float startAngle) :  startPos(startPos), startRight(startRight), moveConstant(4), firingStage(0){
        
        //Load Cannon and Turret images.
        if(!cannonImg.loadFromFile("media/cannonBase.png")){
            std::cout << "Failed to load cannon image!" << std::endl;
                //throw exception HERE
        }
        //Flip image for left player.
        if(!startRight) cannonImg.flipHorizontally();

        if(!turretImg.loadFromFile("media/newTurret2.png")){
            std::cout << "Failed to load turret image!" << std::endl;
                //throw exception HERE
        }
            
            
        //add the cannon and turret images to the textures.
        if(!cannonTexture.loadFromImage(cannonImg)){
            
            std::cout << "Failed to load cannon texture!" << std::endl;
                //throw exception HERE
        }

        if(!turretTexture.loadFromImage(turretImg)){
                std::cout << "Failed to load turret texture!" << std::endl;
                //throw exception HERE
        }
        
        //image sizes used in setting the image rect.
        cannonSize.x = cannonImg.getSize().x/2;
        cannonSize.y = cannonImg.getSize().y;

        turretSize.x = turretImg.getSize().x/4;
        turretSize.y = turretImg.getSize().y;
        
        //REMOVE WHEN DON
        //std::cout << cannonSize.x << ", " << cannonSize.y << std::endl;
        //std::cout << turretSize.x << ", " << turretSize.y << std::endl;

        cannonTexture.setSmooth(true);
        turretTexture.setSmooth(true);
        //create sprites and add textures.
        cannonSprite.setTexture(cannonTexture);
        turretSprite.setTexture(turretTexture);
        //turretSprite.setTextureRect(sf::IntRect(0,0,turretSize.x,turretSize.y));
        turretSprite.setTextureRect(sf::IntRect(0,0,turretSize.x,turretSize.y));
        
        if(startRight){
            // ADD EXCEPTIONS IN CASE SOMETHING FAILS
                       
            cannonSprite.setTextureRect(sf::IntRect(0,0,cannonSize.x,cannonSize.y));
        
            
            turretSprite.setRotation(startAngle);
            //Set origin to lower middle
            turretSprite.setOrigin(turretSize.x/2, turretSize.y * (5/3));
            cannonSprite.setOrigin(cannonSize.x/2, cannonSize.y);
            cannonSprite.setPosition(startPos);
            turretSprite.setPosition(sf::Vector2f( (startPos.x-(turretSize.x/6)), (startPos.y - 2*(turretSize.y/3)) )); //CHANGE TO SET IMAGE ON RIGHT PLACE
        
        }else{
               
            // ADD EXCEPTIONS IN CASE SOMETHING FAILS
            //set textures edges to smooth
            cannonTexture.setSmooth(true);
            turretTexture.setSmooth(true);
            //create sprites and add textures.
            cannonSprite.setTexture(cannonTexture);
            cannonSprite.setTextureRect(sf::IntRect(cannonSize.x,0,cannonSize.x,cannonSize.y));
        
            turretSprite.setRotation(180-startAngle);
            //Set origin to upper middle.
            turretSprite.setOrigin(turretSize.x/2, turretSize.y*(1/3));
            cannonSprite.setOrigin(cannonSize.x/2, cannonSize.y);
            cannonSprite.setPosition(startPos);
            turretSprite.setPosition(sf::Vector2f(startPos.x + (turretSize.x/6), startPos.y - 2*(turretSize.y/3))); //CHANGE TO SET IMAGE ON RIGHT PLACE

        }
        moved = false;
}


void BasicCannon::move(sf::Vector2f v){
    cannonSprite.setPosition(v);
    if(startRight){
    	turretSprite.setPosition(sf::Vector2f(v.x-(turretSize.x/6), v.y-2*(turretSize.y/3)));//CHANGE SO THE IMAGE
    }else{
    	turretSprite.setPosition(sf::Vector2f(v.x+(turretSize.x/6), v.y-2*(turretSize.y/3)));//CHANGE SO THE IMAGE
    }
     
    if(!moved){ //Change rect sizes dynamically according to image size.
        if(startRight){
            cannonSprite.setTextureRect(sf::IntRect(cannonSize.x, 0, cannonSize.x, cannonSize.y));
        }else{
            cannonSprite.setTextureRect(sf::IntRect(0, 0, cannonSize.x, cannonSize.y));    
        }
        moved = true;    
     }else{
        if(startRight){
            cannonSprite.setTextureRect(sf::IntRect(0, 0, cannonSize.x, cannonSize.y));
        }else{
            cannonSprite.setTextureRect(sf::IntRect(cannonSize.x, 0, cannonSize.x, cannonSize.y));
        }
        moved = false;
     }     
}


void BasicCannon::rotate(int angle){
  turretSprite.setRotation(angle);
}



void BasicCannon::fireAnimation(){
	
            switch(firingStage){
		    case 0:
			    turretSprite.setTextureRect(sf::IntRect(0*turretSize.x,0,turretSize.x, turretSize.y));
			    firingStage++;
			    break;
		    case 1:
			    turretSprite.setTextureRect(sf::IntRect(1*turretSize.x,0, turretSize.x, turretSize.y));
			    firingStage++;
			    break;
		    case 2:
			    turretSprite.setTextureRect(sf::IntRect(2*turretSize.x, 0, turretSize.x, turretSize.y));
			    firingStage++;
			    break;
		    case 3:
			    turretSprite.setTextureRect(sf::IntRect(3*turretSize.x, 0, turretSize.x, turretSize.y));
			    firingStage++;
			    break;
                    case 4:
			    turretSprite.setTextureRect(sf::IntRect(0*turretSize.x, 0, turretSize.x, turretSize.y));
			    firingStage = 0;
			    firing = false;
	    		    break;
	    
                }
}

sf::Vector2f BasicCannon::getCollisionCoord(){
	
	sf::Vector2f tmp = turretSprite.getPosition();
	sf::Vector2f res(tmp.x-80, tmp.y-45);
	return res;

}


/**/
sf::Vector2f BasicCannon::getFireCoord(){
    sf::Vector2f tmp(turretSprite.getPosition());
       float rot; 
    sf::Vector2f res;
    float x, y;
    if(startRight){
        rot  = turretSprite.getRotation() + 33; //CHANGE IF TURRET SIZE CHANGES
        x = cos(rot*(PI/180)) * 17.0;
        y = sin(rot*(PI/180)) * 17.0;
        res = sf::Vector2f(tmp.x - x, tmp.y - y);
               
    }else{
        //CHANGE IF TURRET SIZE CHANGES
        rot = 180 - turretSprite.getRotation();
        x = cos(rot*(PI/180)) * 17;
        y = sin(rot*(PI/180)) * 17;
        res = sf::Vector2f(tmp.x + x, tmp.y - y);

         std::cout << "sprite rotation: (" << rot << ")" << std::endl;
        std::cout << "turret position: (" << tmp.x << ", " << tmp.y << ")" << std::endl;
        std::cout << "turret tip pos.: (" << res.x << ", " << res.y << ")" << std::endl;


    }
    return res;
}
	
/*
sf::Vector2f getLeftBottomCoord(){}
	

sf::Vector2f getRightBottomCoord(){}
*/



    
    







