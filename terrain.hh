//author Oskari Päivinen

#ifndef terrain_hh
#define terrain_hh

#include<SFML/Graphics.hpp>

class Terrain {
      
public:
    Terrain(){};
    Terrain(sf::Vector2u winSize)
    :terrainMask(generateTerrain(winSize)), updated(false), winSize(winSize) {}
    
    sf::Image getImage() const {return terrainMask;}
    bool needsUpdate() const { return !updated;}
    void update(){updated = true;}
    
    bool hit(sf::Vector2i c) const{
        if (terrainMask.getPixel(c.x, c.y) == sf::Color::White) return false;
        return true;
    }
    bool outOfBounds(int x,int y) const {
        if (x < 0 || x > int(winSize.x) || y < 0 || y >= (int)winSize.y)
            return true;
        return false;
    }
    //Drawing circle in the mask image.
    void destroyTerrain(sf::Vector2i c, unsigned int r);
            
private:
    int dirr() const;
    sf::Image  generateTerrain(sf::Vector2u winSize);
        
private:
    sf::Image terrainMask;      
    bool updated;
    sf::Vector2u winSize;


};

#endif
