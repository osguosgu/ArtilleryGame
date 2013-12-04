//author Oskari Päivinen

#ifndef terrain_hh
#define terrain_hh


class Terrain {
      
public:
    Terrain(){};
    Terrain(sf::Vector2u winSize)
    :terrainMask(generateTerrain(winSize)), updated(false), winSize(winSize) {}
     
    sf::Image getImage() const {return terrainMask;}

    bool needsUpdate() const { return !updated;}

    void update(){updated = true;}
    
    //returns the surface if the terrain for given coordinates
    unsigned int getY(sf::Vector2f pos){
        for (unsigned int i = (unsigned int) pos.y - 5; i < winSize.y ; i++){
            if (terrainMask.getPixel(pos.x,i) != sf::Color::White) return i;
        }
        return winSize.y;
    }
    //checks if there is wall ahead that cant be passed
    bool isWall(sf::Vector2f c){
        if (terrainMask.getPixel((unsigned int) c.x, (unsigned int) c.y  -5) == sf::Color::White) return false;
        else return true;

    }
    //checks if the given coordinate hits the ground
    bool hit(sf::Vector2i c) const{
        if (terrainMask.getPixel(c.x, c.y) == sf::Color::White) return false;
        return true;
    }
    //checks if the given coordinates collide with the surface of the terrain
    bool collide(std::vector<sf::Vector2u> list){
        for (sf::Vector2u &v : list){
            if (terrainMask.getPixel(v.x, v.y+1) != sf::Color::White) return true;
        }
        return false;
    }
    //checks if coordinates are out of the screen
    bool outOfBounds(int x, int y) const {
        if (x < 0 || x > int(winSize.x) || y >= (int)winSize.y)
            return true;
        return false;
    }
    //Drawing circle in the mask image.
    void destroyTerrain(sf::Vector2i c, unsigned int r);
            
private:
    int dirr() const;
    sf::Image generateTerrain(sf::Vector2u winSize);
    sf::Image terrainMask;      
    bool updated;
    sf::Vector2u winSize;


};

#endif
