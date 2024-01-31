cmake_minimum_required(VERSION 2.8.9)
project(valeriePecrage.TestCase)

#C++11 Standard
set(CMAKE_CXX_STANDARD 11)

#Extended Warnings
set(CMAKE_CXX_FLAGS -Wall)

set(SOURCE_FILES ../../src/Tests/TestCase.cpp
                 ../../src/helperFunctions/helperFunctions.cpp
                 ../../src/Animation/Animation.cpp 
                 ../../src/Background/Background.cpp 
                 ../../src/Effect/Effect.cpp
                 ../../src/Entity/Entity.cpp
                 ../../src/Game/Game.cpp
                 ../../src/Resolution/Resolution.cpp
                 ../../src/Difficulty/Difficulty.cpp
                 ../../src/Bus/Bus.cpp
                 ../../src/Bus/BusListener.cpp
                 ../../src/Bus/BusWriter.cpp
                 ../../src/Bus/Message.cpp
                 ../../src/AudioManager/AudioManager.cpp
                 ../../extlibs/Collision/Collision.cpp)

add_executable(test.out ${SOURCE_FILES})
target_link_libraries(test.out -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio)