#ifndef CREATURE_H
#define CREATURE_H
#include <iostream>

struct monster
{
    int hp;
    int att;
    int def;
    std::string weakness;
};

class Creature
{
    public:
        monster charRandomizer();
        monster monRandomizer();
        void monInfo();
        void charInfo();
        void update(int hpc);
        Creature();
        virtual ~Creature();
    protected:
    private:
        void setHP(monster x);
        void getAtt(monster x);
        void getHP(monster x);
        void getDef(monster x);
};

#endif // CREATURE_H
