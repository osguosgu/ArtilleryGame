#ifndef PARTICLES_HH
#define PARTICLES_HH

class Particle{

public:
    Particle();
    Particle(sf::Vector2f speed, sf::Vector2f coord): speed(speed), coord(coord){}
    
    void setSpeed(sf::Vector2<float> newspeed){
        speed=newspeed;
        }

    void updateCoord(){
        coord += speed;	
        }

    sf::Vector2<float> getSpeed() const{ 
        return speed;
        }
	sf::Vector2<int> getCoord() const{
        sf::Vector2<int> intcoord;	//palautetaan koordinaatit kokonaislukuna
        intcoord.x = int(coord.x);
        intcoord.y = int(coord.y);
        return intcoord;
    }


private:

    sf::Vector2f speed;
    sf::Vector2f coord;
    int age;
};

#endif
