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
    std::string name;
    std::string descrip;
    int key;
    levels *start=NULL;
    Dungeon *parent;
    Dungeon *left;
    Dungeon *right;
};

struct item
{
    std::string name;//name or weapon or armor
    std::string type;//type or equipment eg: weapon affects damage... armor affects defense.. necklace affects HP
    int stat;//the number it affects by
};
struct monster
{
    int hp;// health
    int att;// damage
    int def;//defence
    std::string weakness;//stat weakness

    item weapon;// info of weapon equip
    item armor;//info on armor
    item amulet;//info on amulet
};

class BSMap
{
    public:
        void createMap();
        void insertDungeon(Dungeon *root,int spot,std::string name,std::string descip);
        void printMap();
        void avalibleMoves();
        void dungeonMenu();
        monster charRandomizer();//randomly makes the character
        monster monRandomizer();//randomly makes monsters
        void monInfo();
        void charInfo();
        void moveChar();
        BSMap();
        virtual ~BSMap();
    protected:
    private:
        void printMap(Dungeon *temp);
        void setDungeonLevels(bool x,int m,Dungeon *hold);
        void combat();
        void levelDelete(Dungeon *hold);
        Dungeon *root=NULL;
        Dungeon *pos=root;
};

#endif // BSMAP_H
