#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream> //Console output
#include <fstream>  //File streams, to keep track of highest score
#include <sstream>  //String streams (purpose is similar to sprintf), used for score text
#include <vector>   //Vectors to hold enemies and bullets
#include <memory>   //Smart pointers for player and background object
#include <array>    //Safer, easier to use fixed size arrays to hold textures
#include <ctime>    //time(NULL) for Rand Seed
#include <cstdlib>  //Rand
#include <map>

class Game{
    public:
        Game();
        ~Game();
    
    private:
    // use a map to count instances of entities
    map<Entity>
}