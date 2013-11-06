#ifndef CANNONBALL_HH
#define CANNONBALL_HH


#include <SFML/Graphics.hpp>
#include <cmath>
#include "physics.hh"
class CannonBall
{
	public:
			CannonBall(sf::Vector2<int> coord, float angle, int mass, int powder)
			:coord(coord), angle(angle), mass(mass), powder(powder){}

			sf::Vector2<int> getSpeed(){
			return speed;
			}


			void setSpeed(sf::Vector2<int> newspeed){
			speed=newspeed;
			}
			
			
			float getAngle(){
			return angle;
			}
			
			int getMass(){
			return mass;
			}
			
			sf::Vector2<int> getCoord(){
			return coord;
			}
			
			int getPowder(){
			return powder;
			
			}
			
			void updateCoord(){
			coord += speed;
			}

			
			
	private:
			sf::Vector2<int> coord;
			sf::Vector2<int> speed;
			float angle;
			int mass;
			int powder;
            
};

#endif
