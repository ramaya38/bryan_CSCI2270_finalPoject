#ifndef BSMAP_H
#define BSMAP_H
#include <iostream>

struct levels
{
    bool completed;
    int monsters;
    levels *next;
};
struct Dungeon
{
    bool finished;
    bool playerHere;
    std::string name;
    std::string descrip;
    int key;
    levels *start=NULL;
};

class BSMap
{
    public:
        void createMap();
        void printMap();
        void avalibleMoves();
        std::string dungeonInfo();
        BSMap();
        virtual ~BSMap();
    protected:
    private:
        void setDungeonLevels(bool x,int m,Dungeon *hold);
        void combat();
        void levelDelete(Dungeon *hold);
        Dungeon *root=NULL;

};

#endif // BSMAP_H
