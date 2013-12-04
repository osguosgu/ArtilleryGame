//author Oskari Päivinen

#include <stdlib.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include"terrain.hh"

/*this function sets all the destructed terrain as a air so that cannons
 * and cannonballs can move there and the terrain is not drawd there*/
void Terrain::destroyTerrain(sf::Vector2i c, unsigned int r){
    for (unsigned int y = 0; y < r; y++){
        for (unsigned int x = 0; x < r; x++){
            if (sqrt(x*x + y*y) > r) break;
            //these four sections draw whole circle shape to the mask picture
            if (outOfBounds(c.x + x, c.y + y)){}
            else if (terrainMask.getPixel(c.x + x, c.y + y) == sf::Color::White){}
            else terrainMask.setPixel(c.x + x, c.y + y, sf::Color::White);
            
            if (outOfBounds(c.x - x, c.y - y)){}
            else if (terrainMask.getPixel(c.x - x, c.y - y) == sf::Color::White){}
            else terrainMask.setPixel(c.x - x, c.y - y, sf::Color::White);

            if (outOfBounds(c.x - x, c.y + y)){}
            else if (terrainMask.getPixel(c.x - x, c.y + y) == sf::Color::White){}
            else terrainMask.setPixel(c.x - x, c.y + y, sf::Color::White);

            if (outOfBounds(c.x + x, c.y - y)){}
            else if (terrainMask.getPixel(c.x + x, c.y - y) == sf::Color::White ){}
            else terrainMask.setPixel(c.x + x, c.y - y, sf::Color::White);
        }
    }
    //set the terrain sprite to be updated
    updated = false;
}

//this is just helper function for generateTerrain
//it just randomly pics 1 or -1
int Terrain::dirr() const{
    switch(rand()%2){
        case 0:
            return 1;
        case 1:
            return -1;
            
        }
    return 1;
}

//generating the terrain for a new game
sf::Image Terrain::generateTerrain(sf::Vector2u winSize){
    sf::Image mask; //the image to return
    sf::Image texImage; //the texture image
    std::string soils [] = {
    "media/soil1.jpg",
    "media/soil2.jpg",
    "media/soil3.jpg",
    "media/soil4.jpg"};
    texImage.loadFromFile(soils[rand() % (sizeof(soils) / sizeof(std::string))]); // randomply pics the terrain texture image
    mask.create(winSize.x ,winSize.y , sf::Color(255,255,255)); //init all pixels to white
    
    srand(time(NULL));
    unsigned int height = rand() % (winSize.y / 2) + winSize.y * 0.1; //the starting height of the terrain
    unsigned int smoothness = rand() % 100; // how often direction is changed
    unsigned int maxDiff = rand() % 3 + 2; //how much can the height different between side by side pixel columns
    int dir = 0; // direction multiplier of the terrain drawing -1,1 or 1 
    int* mapArr = new int[winSize.x]; // array of the map pixel-column heights
    mapArr[0] = height;
    for (unsigned int x = 1; x < winSize.x ; x++){
        if (smoothness < 2) {
            dir = dirr();
        }
        if (smoothness == 3){
            dir = 0;
        }
        smoothness = rand() % 100;
        //the terrain can't reach bottom or top of the screen
        if (mapArr[x-1] < 0.1*winSize.y) {dir = 1;}
        else if (mapArr[x-1] > 0.9*winSize.y ){ dir = -1;}
        //calculate the next pixel column height
        mapArr[x] = mapArr[x-1] + (rand() % maxDiff) * dir;
    }
    //sets the texture in the mask image with the help of mapArr
    for (unsigned int x = 0 ; x < winSize.x ; x++){
        for(unsigned int y = winSize.y - mapArr[x]; y < winSize.y; y++){
            mask.setPixel(x,y, texImage.getPixel(x % texImage.getSize().x,
                        y % texImage.getSize().y) );
        }
    }
    delete mapArr;
    return mask;
}
