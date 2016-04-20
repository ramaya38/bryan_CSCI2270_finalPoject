#ifndef CREATURE_H
#define CREATURE_H
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
    int hp;// health
    int att;// damage
    int def;//defence
    std::string weakness;//stat weakness

    item weapon;// info of weapon equip
    item armor;//info on armor
    item amulet;//info on amulet
};

class Creature
{
    public:
        monster charRandomizer();//randomly makes the character
        monster monRandomizer();//randomly makes monsters
        void monInfo();
        void charInfo();
        void update(int hpc);
        void inventory();
        Creature();
        virtual ~Creature();
    protected:
    private:
        int setHP(monster x);
        int setAtt(monster x);
        int setDef(monster x);
        int getAtt(monster x);
        int getHP(monster x);
        int getDef(monster x);
        void equipItem(item x);
        std::vector<item> equipment;
};
#endif // CREATURE_H
