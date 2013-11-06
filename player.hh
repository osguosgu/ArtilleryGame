#ifndef CANNON_HH
#define CANNON_HH

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

class Player{
	
	public:
		Player(std::string name, sf::Vector2u coords, sf::Color color ): name(name), coords(coords), color(color), health(100){} 
		~Player();
		std::string getName(){return name;}
		int getHealth(){return health;}
		void updateHealth(int damage){health -= damage;}
		sf::Vector2u getCoordinates(){return coords;}
		void setCoordinates(sf::Vector2u newCoord){coords = newCoords;}
		sf::Color getColor(){return color;}
	
	private:
		std::string name;
		int health;
		sf::Vector2u coords;
		sf::Color color;

};


#endif
