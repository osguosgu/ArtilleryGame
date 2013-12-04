#ifndef physics_hh
#define physics_hh
#include <iostream>
#include <SFML/Graphics.hpp>
#define PI 3.14159265

const float gravity = 0.05;
float wind = 0.001;

void updateWind(){
	
	srand(time(NULL));
	int num = (rand() % 11); //0-11
		//std::cout << "wind" << num << std::endl;
		if(num >= 6 ) num = num*(-1)+5;
		wind = float(num)/500;
		
	}

float getWind(){return wind;}


// Lahtonopeus, tata voidaan kutsua kun ammutaan, 
//impulssi = kappaleen liikemaaran muutos. eli ruudin yksikko on [kg*m/s] joten ammuksen nopeus 
// saadaan jakamalla ruudin maara ammuksen massalla, ammuksen massa kg
// parametrit: piipun kulma, ruudin maara, ammuksen massa
// palauttaa uudet koordinaatit sdt::vector<double> panoksen kulman (0-2Pi) seka nopeuden m/s (tai pikselia / frame) tjsp


//physics::fire() palauttaa itemin x ja y nopeudet vaatii getPowder(), getMass(), getAngle() funktiot


template <typename T1>
void fire(T1& item){ 
	
	
    float vx1 = (item.getPowder()/item.getMass())*cos(item.getAngle()); // alkunopeus x-suunnassa
    float vy1 = (item.getPowder()/item.getMass())*sin(item.getAngle());// alkunopeus y-suunnassa

	sf::Vector2<float> pal(vx1,-vy1);	
	item.setSpeed(pal);
	
}

//palauttaa seuraavan pisteen, vaatii nopeuden seka nykyisen paikan( updateCoord + getSpeed functiot)

template <typename T1>
void nextCoord(T1& item){ 

	item.updateCoord();
    //std::cout << ball.getSpeed().x << std::endl;
    
    //float dif = item.getSpeed().x + wind; // tuulen ja nopeuden ero
    //if(dif > item.getSpeed()){ //myotatuuli
    
    //float x = d
    
    
    //std::cout << item.getSpeed().x << std::endl;
    float x = (item.getSpeed().x + wind); //nopeuden x-komponentti + tuulen vaikutus
    
    
    float y = item.getSpeed().y + gravity; // nopeuden y-komponentti + gravitaation vaikutus
    item.setSpeed(sf::Vector2<float>(x,y));

}

#endif
