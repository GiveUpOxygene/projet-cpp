#include "Entity.hpp"
#include "../../extlibs/Collision/Collision.h"

//****************
//*PUBLIC METHODS*
//****************


void Entity::setHealth(int health){
    this->health = health;

    if(health <= 0)
        dead = true;
    else dead = false;
}


void Entity::damage(int dmg){
    if(dead == false){
        health -= dmg;

        if(health <= 0){
            dead = true;
            sendMessage(Message{Message::Type::ENTITY_DEATH, *this});
        }
    }
}


//Shoot method. Returns vector of bullets
std::vector<sf::Sprite> Entity::shoot(){
    sf::Time elapsed = clock.getElapsedTime();
    std::vector<sf::Sprite> shots;

    //If enough time has passed
    if(elapsed.asMilliseconds() - lastShot >= msBetweenShots){
        sf::FloatRect bulletRect = bulletSprite.getGlobalBounds();
        sf::Vector2f entityPos = getPos();

        //Place a bullet on each shooting point
        for(sf::Vector2f shootingPoint : shootingPoints){
            bulletSprite.setPosition(shootingPoint.x - bulletRect.width / 2, shootingPoint.y - bulletRect.height);
            bulletSprite.move(entityPos);
            shots.push_back(bulletSprite);
        }

        //Update time of last shot
        lastShot = elapsed.asMilliseconds();

        //Generator is destroyed when shooting
        if(getEntityType() == EntityTypes::cyclistGenerator){
            dead = true;
        }

        //Send Shot Event
        Message::Type type = (_team == Entity::Team::ally) ? Message::Type::BLUE_ENTITY_SHOT : Message::Type::RED_ENTITY_SHOT;
        sendMessage(Message{type, *this});
    }

    //Return vector of bullets
    return shots;
}


void Entity::initEntityType(EntityTypes type){
    switch(type){
        default:
        case EntityTypes::base_type:
        initBaseType();
        break;

        case EntityTypes::player:
        initPlayer();
        break;

        case EntityTypes::small:
        initMosquito();
        break;

        case EntityTypes::pecrage:
        initpecrage();
        break;

        case EntityTypes::cyclistGenerator:
        initCyclistGenerator();
        break;

        case EntityTypes::tourist:
        initTourist();
        break; 
    }
}

void Entity::flipVertically(){
    Animation::flipVertically();    //Do default Animation flip

    //Get center of the entity
    sf::FloatRect entityRect = getRect();
    sf::Vector2f entityCenter = {entityRect.width / 2, entityRect.height / 2};

    //Flip shooting points around center of the entity
    for(sf::Vector2f &shootingPoint : shootingPoints){
        shootingPoint = Helpers::flipPointVertically(shootingPoint, entityCenter);
    }
}


void Entity::setScale(float scale_x, float scale_y){
    Animation::setScale(scale_x, scale_y);
    //In addition to the setScale provided by Animation,
    //scale shooting points as well

    for(sf::Vector2f &shootingPoint : shootingPoints){
        shootingPoint.x *= scale_x;
        shootingPoint.y *= scale_y;
    }
}


bool Entity::isHitBy(sf::Sprite &collisionObj){
    bool hit = false;

    if(getRect().intersects(collisionObj.getGlobalBounds())){
        hit = Collision::PixelPerfectTest(frames[0], collisionObj);
    }

    return hit;
}


void Entity::AI_MoveWithinBounds(int max_x, float speed){
    sf::FloatRect entityRect = getRect();

    //If no destination, find one
    if(destination == -1){
        destination = rand() % (int)(max_x - entityRect.width);
        destGreaterThanX = destination >= entityRect.left;
    }

    //Move left or right based on the destination
    if(destGreaterThanX)
        move(speed, 0);

    else move(-speed, 0);

    //Check if we have reached or surpassed the destination
    //If so, reset it
    if(destGreaterThanX != (destination >= entityRect.left))
        destination = -1;
}


//Adds a point on the entity to shoot from
void Entity::addShootingPoint(float x, float y){
    sf::Vector2f entityScale = getScale();
    sf::Vector2f point;

    //Scale the point to match the entity's scale before adding it
    point.x = x * entityScale.x;
    point.y = y * entityScale.y;
    shootingPoints.push_back(point);
}



void Entity::setMsBetweenShots(int ms){
    msBetweenShots = ms;
}

EntityTypes Entity::getEntityType(){
    return entityType;
}


void Entity::setBulletScale(float scale_x, float scale_y){
    bulletSprite.setScale(scale_x, scale_y);
}


void Entity::initMosquito(){

    //Adding shooting points inside the original texture
    addShootingPoint(310, 0);

    setMsBetweenFrames(60);
    setMsBetweenShots(100);
    dmg = 2;

    setScale(0.10 * scaleMultiplier, 0.10 * scaleMultiplier);
    setBulletScale(0.3 * scaleMultiplier, 0.35 * scaleMultiplier);
    entityType = EntityTypes::small;
    health = 15;
}


void Entity::initpecrage(){
    //addShootingPoint(180, 200);
    addShootingPoint(253, 125);
    //addShootingPoint(324, 202);

    setMsBetweenFrames(20);
    setMsBetweenShots(80);
    dmg = 1;

    setScale(0.18 * scaleMultiplier, 0.18 * scaleMultiplier);
    setBulletScale(0.1 * scaleMultiplier, 0.1 * scaleMultiplier);
    entityType = EntityTypes::pecrage;
    health = 15;
}

void Entity::initTourist(){
    addShootingPoint(180, 200);
    addShootingPoint(253, 125);
    addShootingPoint(324, 202);

    setMsBetweenFrames(30);
    setMsBetweenShots(70);
    dmg = 1;

    setScale(0.18 * scaleMultiplier, 0.18 * scaleMultiplier);
    setBulletScale(0.1 * scaleMultiplier, 0.1 * scaleMultiplier);
    entityType = EntityTypes::tourist;
    health = 4;
}


void Entity::initBaseType(){
    addShootingPoint(100, 25);


    setMsBetweenFrames(100);
    setMsBetweenShots(100);
    dmg = 1;

    //Adding shooting points inside the original texture

    // addShootingPoint(380, 200);
    setScale(0.3*scaleMultiplier, 0.3*scaleMultiplier);
    setBulletScale(0.45 * scaleMultiplier, 0.45 * scaleMultiplier);
    entityType = EntityTypes::base_type;
    health = 20;
}

void Entity::initPlayer(){
    setMsBetweenFrames(100);
    setMsBetweenShots(200);
    dmg = 1;

    //Adding shooting points inside the original texture
    addShootingPoint(310, 0);
    setScale(0.3*scaleMultiplier, 0.3*scaleMultiplier);
    setBulletScale(0.01 * scaleMultiplier, 0.01 * scaleMultiplier);
    entityType = EntityTypes::player;
    health = 20;
}

void Entity::initCyclistGenerator(){
    setMsBetweenFrames(40);
    setMsBetweenShots(100);
    dmg=1;
    addShootingPoint(225, 200);
    setScale(0.14 * scaleMultiplier, 0.14 * scaleMultiplier);
    setBulletScale(0.3 * scaleMultiplier, 0.3 * scaleMultiplier);
    entityType = EntityTypes::cyclistGenerator;
    health = 20;
}

void Entity::onDeath(){
    std::cout << "équipe : " << teamToString(_team) << ", type : " << entityToString() << std::endl;
}

void Entity::resurrect(){
    dead = true;
}

std::string Entity::entityToString(){
    switch (getEntityType())
    {
    case EntityTypes::pecrage:
        return ("pecrage");

    case EntityTypes::small:
        return ("small");
    
    case EntityTypes::cyclistGenerator:
        return ("cyclistGenerator");
    
    case EntityTypes::tourist:
        return ("tourist");
        
    case EntityTypes::base_type:
    default:
        return ("base_type");
    }
};