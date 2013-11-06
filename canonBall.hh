#include <SFML/Graphics.hpp>
#include <cmath>

class CanonBall
{
	public:
			CanonBall(sf::Vector2<int> coord, sf::Vector2<int> speed, float angle, int mass)
			:coord(coord),speed(0), angle(angle), mass(mass){
    		
    		physics::fire(this);
    		
			}

			setSpeed(sf::Vector2<int> speed){
			speed=speed;
			}
			
			getAngle(){
			return angle;
			}
			
			getMass(){
			return mass;
			}
			
			getCoord(){
			return coord;
			}
			
			
	private:
			sf::Vector2<int> coord;
			sf::Vector2<int> speed;
			float angle;
			int mass;
