#ifndef CANNONBALL_HH
#define CANNONBALL_HH

#include <SFML/Graphics.hpp>
class CannonBall
{
	public:
			CannonBall(int type, sf::Vector2<float> coord, float angle, int powder)
			    :type(type), coord(coord), angle(angle),  powder(powder){
                    mass = type * 5;
                    radius = mass * 3;
                }

			sf::Vector2<float> getSpeed() const{ 
			return speed;
			}
			void setSpeed(sf::Vector2<float> newspeed){
			speed=newspeed;
			}
			float getAngle() const{
			return angle;
			}
            int getRadius() const{
            return radius;
            }
			int getMass() const{
			return mass;
			}
            int getType() const{
            return type;
            }
			sf::Vector2<int> getCoord() const{
                sf::Vector2<int> intcoord;	//palautetaan koordinaatit kokonaislukuna
                intcoord.x = int(coord.x);
                intcoord.y = int(coord.y);
                return intcoord;
			}
			int getPowder() const{
			return powder;
			}
			void updateCoord(){
			coord += speed;		//lisaa vectorien x ja y komponentteja
			}
	private:
            int type;
			sf::Vector2<float> coord;
			sf::Vector2<float> speed;
			float angle;
			int mass;
			int powder;
            int radius;
            
};
#endif
