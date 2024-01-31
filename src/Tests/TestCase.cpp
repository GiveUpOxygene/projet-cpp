#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../Game/Game.hpp"
#include <fstream>
#include <string>

TEST_SUITE("Animation") {
    TEST_CASE("1. Animation init") {
        sf::Texture texture;
        std::array<sf::Texture, 1> textures = {texture};
        Animation animation(textures);
        CHECK(animation.getScale() == sf::Vector2f(1, 1));
        CHECK(animation.getPos() == sf::Vector2f(0, 0));
        CHECK(animation.getRect() == sf::FloatRect(0, 0, 0, 0));
        CHECK(animation.isInvisible() == false);
    }
    TEST_CASE("2. Animation setPos") {
        sf::Texture texture;
        texture.loadFromFile("assets/animation/pecrage/pecrage_1.png");
        std::array<sf::Texture, 1> textures = {texture};
        Animation animation(textures);
        animation.setPos(1,1);
        CHECK(animation.getPos() == sf::Vector2f(1, 1));
    }
    TEST_CASE("3. Animation setScale") {
        sf::Texture texture;
        texture.loadFromFile("assets/animation/pecrage/pecrage_1.png");
        std::array<sf::Texture, 1> textures = {texture};
        Animation animation(textures);
        animation.setScale(1,1);
        CHECK(animation.getScale() == sf::Vector2f(1, 1));
    }
}

TEST_SUITE("Difficulty") {
    TEST_CASE("1. Difficulty set with string") {
        Difficulty::Level difficulty = Difficulty::Level::normal;
        Difficulty::setDifficultyFromStr("easy", difficulty);
        CHECK(difficulty == Difficulty::Level::easy);
    }
    TEST_CASE("2. Difficulty to string") {
        Difficulty::Level difficulty = Difficulty::Level::normal;
        CHECK(Difficulty::difficultyToStr(difficulty) == "normal");
        Difficulty::setDifficultyFromStr("easy", difficulty);
        CHECK(Difficulty::difficultyToStr(difficulty) == "easy");
    }
}

TEST_SUITE("Entity") { 
    TEST_CASE("1. Entity init") {
        sf::Texture texture, bulletTexture;
        std::array<sf::Texture, 1> textures = {texture};

        Bus bus;
        Entity entity(bus, EntityTypes::base_type, Entity::Team::ally, 1, textures, bulletTexture);
        CHECK(entity.getPos() == sf::Vector2f(0, 0));
        CHECK(entity.getRect() == sf::FloatRect(0, 0, 0, 0));
        CHECK(entity.isInvisible() == false);
    }
    TEST_CASE("2. Entity setPos & move") {
        sf::Texture texture, bulletTexture;
        std::array<sf::Texture, 1> textures = {texture};

        Bus bus;
        Entity entity(bus, EntityTypes::base_type, Entity::Team::ally, 1, textures, bulletTexture);
        entity.setPos(1,1);
        sf::Vector2f formerPos = entity.getPos();
        CHECK(entity.getPos() == sf::Vector2f(1, 1));
        entity.moveUp(1, 0);
        CHECK(entity.getPos().y < formerPos.y);
        entity.moveDown(1, 100);
        CHECK(entity.getPos().y == formerPos.y);
        entity.moveLeft(1, 0);
        CHECK(entity.getPos().x < formerPos.x);
        entity.moveRight(1, 100);
        CHECK(entity.getPos().x == formerPos.x);
    }
}