#include "BSMap.h"
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

    Dungeon *home=new Dungeon;
    root=home;
    home->descrip="This is your families home, but you seek glory elsewhere";
    home->finished=true;
    home->name="Family Home";
    home->playerHere=true;
    home->key=8;
    home->parent=NULL;
    home->left=NULL;
    home->right=NULL;
    setDungeonLevels(true,0,home);

    for(int i=0;i<DunNum;i++)//Adds amount of dungeons randomly to a BST
    {
        int fileSpot=rand()%12;//chooses a random one from the map

        while(!readFile.eof())
        {
            int i=0;
            if(i==fileSpot)
            {
                string line="";
                string name="";
                string descrip="";
                getline(readFile,line);
                stringstream ss(line);
                getline(ss,name,',');
                getline(ss,descrip,',');
                insertDungeon(root,rand()%16+1,name,descrip);//the root will always be built beforehand
                break;
            }
            i++;
        }
    }
}

void BSMap::insertDungeon(Dungeon *root,int spot,string name,string descrip)//inserts new dungeons onto the map
{
    Dungeon *node=new Dungeon();
    node->name=name;
    node->descrip=descrip;
    node->key=spot;
    node->left=NULL;
    node->right=NULL;

    Dungeon *temp=root;
    Dungeon *ptr=temp;
    while(temp!=NULL)
    {
        ptr=temp;
        if(temp->key<spot)
            temp=temp->right;
        else
            temp=temp->left;
    }
    if(temp->key<spot)
    {
        ptr->right=node;
        node->parent=ptr;
    }
    else
    {
        ptr->left=node;
        node->parent=ptr;
    }

    setDungeonLevels(false,rand()%3+1,node);
}

void BSMap::printMap()//prints map in least to greatest key
{
    Dungeon *temp=root;
    if(temp->left!=NULL)
        printMap(temp->left);
    cout<<"Dungeon "<<temp->name <<endl;
    if(temp->right!=NULL)
        printMap(temp->right);
}

void BSMap::printMap(Dungeon *temp)
{
    if(temp->left!=NULL)
        printMap(temp->left);
    cout<<"Dungeon "<<temp->name <<endl;
    if(temp->right!=NULL)
        printMap(temp->right);
}

void BSMap::avalibleMoves()//shows possible moves to only those that are next to completed dungeons
{

}

void BSMap::dungeonMenu()
{

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
