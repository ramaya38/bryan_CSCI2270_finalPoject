#include "BSMap.h"
#include "Creature.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>

using namespace std;

void BSMap::createMap()
{
    ifstream readFile;
    readFile.open("Dungeons.txt");
    if(!readFile.good())
        cout<<"File did not open!"<<endl;

    int DunNum=rand()%10+5;
    int randomized;

    Dungeon *home=new Dungeon;
    root=home;
    home->descrip="This is your families home, but you seek glory elsewhere";
    home->finished=true;
    home->name="Family Home";
    home->playerHere=true;
    home->key=8;
    setDungeonLevels(true,0,home);

    for(int i=0;i<DunNum;i++)//Adds amount of dungeons randomly to a BST
    {
        randomized=rand()%3+1;//randomly selects how the dungeons are chosen from file
        if(randomized==1)// by order of file
        {

        }
        else if(randomized==2)//by mod %2
        {

        }
        else if(randomized==3)//by mod %3
        {

        }
    }
}

void BSMap::printMap()//prints map in least to greatest key
{

}

void BSMap::avalibleMoves()//shows possible moves to only those that are next to completed dungeons
{

}

string BSMap::dungeonInfo()
{
    return NULL;
}

void BSMap::setDungeonLevels(bool x,int m,Dungeon *hold)//sets dungeon linked list with monsters
{
    levels *node=new levels;
    node->completed=x;
    node->monsters=m;
    node->next=NULL;
    if(hold->start==NULL)
    {
        hold->start=node;
        return;
    }
    levels *temp=hold->start;
    while(temp!=NULL)
    {
        if(temp->next==NULL)
        {
            temp->next=node;
            return;
        }
        temp=temp->next;
    }
}

void levelDelete(Dungeon *hold)
{
    levels *temp=hold->start;
    hold->start=hold->start->next;
    delete temp;
    cout<<"current level has been defeated! The area suddenly disappears"<<endl;
}

void BSMap::combat()
{

}

BSMap::BSMap()
{
    createMap();
}

BSMap::~BSMap()
{

}
