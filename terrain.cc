//author Oskari Päivinen

#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<vector>
#include<iostream>

#include"terrain.hh"

void Terrain::destroyTerrain(sf::Vector2i c, unsigned int r){
    for (unsigned int y = 0; y < r; y++){
        for (unsigned int x = 0; x < r; x++){
            //if ()
            if (sqrt(x*x + y*y) > r) break;
            
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
    updated = false;
}
int Terrain::dirr() const{
    switch(rand()%2){
        case 0:
            return 1;
        case 1:
            return -1;
            
        }
    return 1;


}
sf::Image Terrain::generateTerrain(sf::Vector2u winSize){
    sf::Image mask;
    mask.create(winSize.x ,winSize.y , sf::Color(255,255,255)); 
    
    srand(time(NULL));
    unsigned int height = rand() % (winSize.y / 2) + winSize.y * 0.1; //the starting height of the terrain
    unsigned int smoothness = rand() % 50; // how often direction is changed
    unsigned int maxDiff = rand() % 2 + 2;
    int dir = 1;
    int mapArr[winSize.x]; // array of the map pixel-column heights
    mapArr[0] = height;
    std::cout << height << std::endl;
    for (unsigned int x = 1; x < winSize.x ; x++){
        if (smoothness == 0) {
            dir = dirr();
        }
        smoothness = rand() % 50;
        if (mapArr[x-1] < 0.1*winSize.y || mapArr[x-1] > 0.9*winSize.y )
            dir = dirr();
        mapArr[x] = mapArr[x-1] + (rand() % maxDiff) * dir;
    }
    
    for (unsigned int x = 0 ; x < winSize.x ; x++){
        for(unsigned int y = winSize.y - mapArr[x]; y < winSize.y; y++){
            mask.setPixel(x,y, sf::Color(50,50,50) );
        }
    }
    std::cout << mapArr[1] << ' ' << dir<< std::endl;
    return mask;
}


