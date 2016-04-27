#ifndef BSMAP_H
#define BSMAP_H
#include <iostream>
#include <vector>

struct item
{
    std::string name;//name or weapon or armor
    std::string type;//type or equipment eg: weapon affects damage... armor affects defense.. necklace affects HP
    int stat;//the number it affects by
};

struct monster
{
    std::string name;
    int maxHP;
    int hp;// health
    int att;// damage
    int def;//defence

    item weapon;// info of weapon equip
    item armor;//info on armor
};

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
    int key;
    levels *start=NULL;
    Dungeon *parent;
    Dungeon *left;
    Dungeon *right;
};

class BSMap
{
    public:
        void createMap();
        void insertDungeon(Dungeon *root,int spot,std::string name);
        void printMap();
        void avalibleMoves();
        void dungeonMenu();
        void dungeonInfo(Dungeon *hold);
        monster *charRandomizer();//randomly makes the character
        monster *monRandomizer();//randomly makes monsters
        void monInfo(std::vector<monster*> mons);
        void charInfo();
        void moveChar();
        monster *player;
        BSMap();
        virtual ~BSMap();
    protected:
    private:
        std::vector<monster*> damageTurns(int playerDam, std::vector<monster* > mons);
        void printMap(Dungeon *temp);
        void setDungeonLevels(bool x,int m,Dungeon *hold);
        void combat();
        void levelDelete(Dungeon *hold);
        void avalibleMoves(Dungeon *temp);
        Dungeon *root=NULL;
        Dungeon *pos=root;
        std::vector<Dungeon*> moves;
};

#endif // BSMAP_H
