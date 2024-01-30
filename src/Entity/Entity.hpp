#pragma once

#include <vector>
#include <functional>
#include <string>
#include "../Bus/Message.hpp"
#include "../Bus/BusWriter.hpp"
#include "../helperFunctions/helperFunctions.hpp"
#include "../Animation/Animation.hpp"

enum class EntityTypes{small, base_type, pecresse, cyclistGenerator, bonusGenerator, tourist};

class Entity : public Animation, public BusWriter{
    public:
        enum class Team{ally, enemy};
        int dmg = 1;
        void damage(int dmg);
        bool isDead(){return dead;}
        void resurrect();
        void setHealth(int health);

        //Constructor with entity type
        template<std::size_t SIZE>
        Entity(Bus& pBus, EntityTypes type, Team team, float scaleMultiplier, const std::array<sf::Texture, SIZE> &entity_textures, const sf::Texture &bullet_texture);


        template<std::size_t SIZE>
        void switchEntityType(EntityTypes type, std::array<sf::Texture, SIZE> &textures);

        //Bullet Stuff
        void setBulletScale(float scale_x, float scale_y);
        void addShootingPoint(float x, float y);
        void setMsBetweenShots(int ms);
        std::vector<sf::Sprite> shoot();
        EntityTypes getEntityType();
        Team getTeam(){return (_team);};
        
        
        void AI_MoveWithinBounds(int max_x, float speed);

        bool isHitBy(sf::Sprite &collisionObj);
        
        void flipVertically() override;
        void setScale(float scale_x, float scale_y) override;
        virtual ~Entity(){}
        void onDeath();
        std::string teamToString(Team t){return(t==(Team::ally)?"ally":"enemy");};
        std::string entityToString();
        float getScaleMultiplier(){return scaleMultiplier;};
        // get shooting points
        std::vector<sf::Vector2f> getShootingPoints(){return shootingPoints;};

    private:
        Team _team;
        float scaleMultiplier = 1;
        EntityTypes entityType;
        int destination = -1;
        bool destGreaterThanX;

        sf::Sprite bulletSprite;
        sf::Int32 lastShot = -1000;
        int msBetweenShots = 1;
        std::vector<sf::Vector2f> shootingPoints;

        void initMosquito();
        void initBaseType();
        void initPecresse();
        void initCyclistGenerator();
        void initBonusGenerator();
        void initTourist();
        void initEntityType(EntityTypes type);
        bool dead = false;
        int health = 20;
        
};


//Constructor with entity type
template<std::size_t SIZE>
Entity::Entity(Bus& pBus, EntityTypes type, Team team, float scaleMultiplier, const std::array<sf::Texture, SIZE> &entity_textures, 
                         const sf::Texture &bullet_texture)
: Animation{entity_textures}, BusWriter{pBus}, _team{team}{

    //Animation Constructor + setting bullet textures
    bulletSprite.setTexture(bullet_texture);

    //Setting scaleMultiplier
    this->scaleMultiplier = scaleMultiplier;

    //Setting shooting points based on entity type
    this->initEntityType(type);
}


//Switch the entity type
template<std::size_t SIZE>
void Entity::switchEntityType(EntityTypes type, std::array<sf::Texture, SIZE> &textures){
    //Do nothing if we're already the requested entity type
    if(this->entityType == type)
        return;

    //Else get current entity center
    sf::FloatRect oldEntityRect = this->getRect();
    sf::Vector2f oldCenter{oldEntityRect.left + oldEntityRect.width / 2, oldEntityRect.top + oldEntityRect.height / 2};

    //Replace textures
    this->switchTextures(textures);

    //Clear shooting points
    this->shootingPoints.clear();

    //Add shooting points for new entity type and keep current health
    int oldHealth = health;
    this->initEntityType(type);
    health = oldHealth;

    //Get new entity center
    sf::FloatRect newEntityRect = this->getRect();
    sf::Vector2f newCenter{newEntityRect.left + newEntityRect.width / 2, newEntityRect.top + newEntityRect.height / 2};

    //Move so we're centeenemy on the old center
    this->setPos(newEntityRect.left + (oldCenter.x - newCenter.x), newEntityRect.top + (oldCenter.y - newCenter.y));
}

