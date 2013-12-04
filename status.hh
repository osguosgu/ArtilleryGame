#ifndef STATUS_HH
#define STATUS_HH

#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "player.hh"
#include "physics.hh"
//from arkanoid
template <typename T>
std::string toString(const T& v)
{
  std::ostringstream oss;
  oss << v;
  return oss.str();
}

//draw player status
void initStatus(Player& p, sf::RenderWindow &win, std::vector<sf::Text>& pvector, sf::Font& font)
  {
	
  	unsigned int sizex = win.getSize().x; // size of the window
  	unsigned int sizey = win.getSize().y;
  	
  	unsigned int posCornery = 0;	// position for data,
  	unsigned int posCornerx = 0;
  	int fontsize = 0.025*sizey;	
  	
  	if(p.getNum()==1){	
  	
  	posCornery = 1;	// position for data,
  	posCornerx = 1;
  	}
  	else{
  	posCornery = 1;	// position for data,
  	posCornerx = sizex-(sizex/3)-1;
  	}
	//----------- draw healt-----------------0
  	int healt = p.getHealth(); 
    sf::Text text("Healt: " + toString(healt), font, fontsize );
    text.setColor(sf::Color::Black);
    text.setPosition(posCornerx+2, posCornery+2);
    //win.draw(text);
    pvector.push_back(text);
    
    //----------- draw powder-----------------1
  	int powder = p.getPowder(); 
    sf::Text textp("Powder: " + toString(powder), font, fontsize );
    textp.setColor(sf::Color::Black);
    textp.setPosition(posCornerx+2+(sizex/10), posCornery+2);
    //win.draw(textp);
    pvector.push_back(textp);
    
    //----------- draw charge-----------------2
  	int charge = p.getCharge(); 
    sf::Text textcharge("Charge: " + toString(charge), font, fontsize );
    textcharge.setColor(sf::Color::Black);
    textcharge.setPosition(posCornerx+2+(sizex/10), posCornery+2+fontsize);
    //win.draw(textcharge);
    pvector.push_back(textcharge);
    
    
    //----------- draw name -------------------3
    std::string name = p.getName();
    sf::Text text2(name,font,fontsize);
    text2.setColor(sf::Color::Black);
    text2.setPosition(posCornerx+2, posCornery+2+fontsize);
    //win.draw(text2);
    pvector.push_back(text2);
    
    //------------ draw ballSelection ---------4
    std::string balltype;
    int bs = p.getWeapon();
    if(bs == 1){
    	balltype = "light";}
    else if(bs == 3){
    	balltype = "medium";}
    else if(bs == 5){
    	balltype = "heavy";}
    else
    	balltype = "error";
    sf::Text textbs("Selected Ball:", font, fontsize );
    sf::Text textbsb(balltype, font, fontsize );
    textbs.setColor(sf::Color::Black);
    textbsb.setColor(sf::Color::Black);
    textbs.setPosition(posCornerx+(sizex/5), posCornery+2); 
    textbsb.setPosition(posCornerx+(sizex/5), posCornery+2+fontsize);
    //win.draw(textbs);
    pvector.push_back(textbs);
    pvector.push_back(textbsb);    
  }
  
std::string weapon2string(int bs){
		if(bs == 1){
			return "light";}
		else if(bs == 2){
			return "medium";}
		else if(bs == 3){
			return "heavy";}
		else
			return "error";
}

void updateStatus(Player p ,std::vector<sf::Text> &pv){
	pv[0].setString("Healt: " + toString(p.getHealth()));
	pv[1].setString("Powder: " + toString(p.getPowder()));
	pv[2].setString("Charge: " + toString(p.getCharge()));
	pv[5].setString(weapon2string(p.getWeapon()));
}


void drawWind(sf::RenderWindow &win, sf::Text &textW){
	float wind = 1000*getWind();
	if(wind < 0){
	textW.setString("Wind: <-- " + toString(wind));
	}
	else
		textW.setString("Wind: --> " + toString(wind));
	
	win.draw(textW);
	}

void drawstatus(sf::RenderWindow &win, std::vector<sf::Text> pvector){

	for (sf::Text &t : pvector){
		win.draw(t);
	}
}

#endif


