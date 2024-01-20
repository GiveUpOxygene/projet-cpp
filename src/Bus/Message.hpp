#pragma once

class BusWriter;
class Message{
    public:
    enum class Type{BLUE_ENTITY_SHOT, RED_ENTITY_SHOT, ENTITY_DEATH};
    Message(Type messageType, BusWriter& messageCreator);
    Message(const Message& msg);
    Type getType() const;
    BusWriter& getCreator() const;

    private:
    Type type;
    BusWriter& creator;
};