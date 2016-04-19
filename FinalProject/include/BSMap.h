#ifndef BSMAP_H
#define BSMAP_H
#include <iostream>

struct levels
{
    bool completed;
    int monsters;
    levels *next;
    levels *previous;
};
struct Dungeon
{
    bool finished;
    bool playerHere;
    std::string name;
    levels *start;
};

class BSMap
{
    public:
        void createMap();
        void printMap();
        void avalibleMoves();
        void numberOfDungeons();
        std::string dungeonInfo();
        BSMap();
        virtual ~BSMap();
    protected:
    private:
        void setDungeonLevels();
        void combat();

};

#endif // BSMAP_H
