// fysiikka funktioita
#include <SFML/Graphics.hpp>
#include <cmath>
#include "physics.hh"
#include "cannonBall.hh"

//#include <vector>

//#include "/u/94/hkaikkon/unix/Desktop/kurssit/c++/artillery7/src/SFML-2.1/include/SFML/Graphics.hpp"
#include <iostream>



#define PI 3.14159265
//wind 
//#define M 10
const int M = 10;


const int g = 1;
// Lahtonopeus, tata voidaan kutsua kun ammutaan, 
//impulssi = kappaleen liikemaaran muutos. eli ruudin yksikko on [kg*m/s] joten ammuksen nopeus 
// saadaan jakamalla ruudin maara ammuksen massalla, ammuksen massa kg

// parametrit: piipun kulma, ruudin maara, ammuksen massa
// palauttaa uudet koordinaatit sdt::vector<double> panoksen kulman (0-2Pi) seka nopeuden m/s (tai pikselia / frame) tjsp


//physics::fire() palauttaa morkulan x ja y nopeudet

//sf::Vector2<int> fire(canonBall_olio&);


void fire(CannonBall& ball){ 

    float vx1 = (ball.getPowder()/ball.getMass())*cos(ball.getAngle()); // alkunopeus x-suunnassa
    float vy1 = (ball.getPowder()/ball.getMass())*sin(ball.getAngle());// alkunopeus y-suunnassa

	//std::cout << std::endl << "Start Y speed: " << vy1 << std::endl << std::endl;

	int x = int(vx1+0.5);
	int y = int(vy1+0.5);

	sf::Vector2<int> pal(x,-y);
	
	//std::cout << pal.x <<std::endl;
	
	ball.setSpeed(pal);
	
	//std::cout << ball.getSpeed().x <<std::endl;
	
	//pal.push_back(vx1);
	//pal.push_back(vy1);
	
	
}


//palauttaa seuraavan pisteen, vaatii nopeuden, nykyisen paikan, sekä ehkä massan.

//sf::Vector2<int> fire(canonBall_olio&);



void nextCoord(CannonBall& ball){ 

	ball.updateCoord();
    //std::cout << ball.getSpeed().x << std::endl;
    float w = 0;
    int x = ball.getSpeed().x - w; //nopeuden x-komponentti + tuulen vaikutus
    int y = ball.getSpeed().y + g; // nopeuden y-komponentti + gravitaation vaikutus
    ball.setSpeed(sf::Vector2<int>(x,y));

}

/*

int main()
{

//sf::Vector2<int> testi;
//testi = physics::fire(3*PI/2, 1, 2);
sf::Vector2<int> coord(0,200);
float angle = PI/6;
int mass = 2;
int powder = 2000;

//CannonBall kanuuna = new CannonBall::CannonBall(coord, angle, mass, powder);
CannonBall kanuuna(coord, angle, mass, powder);

std::cout << kanuuna.getCoord().x <<std::endl;
std::cout << kanuuna.getCoord().y <<std::endl;

fire(kanuuna);
std::cout << "Y speed: " << kanuuna.getSpeed().y << std::endl << std::endl;

for(int i=0; i<10; i++){
	nextCoord(kanuuna);
	//std::cout << kanuuna.getCoord().x <<std::endl;
	std::cout << kanuuna.getCoord().y <<std::endl;
	}
return 0;
}
*/
