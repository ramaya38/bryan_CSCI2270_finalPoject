#include "BSMap.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>
#include <vector>

using namespace std;

void BSMap::createMap()//working
{
    srand(time(NULL));
    ifstream readFile;
    readFile.open("Dungeons.txt");
    if(!readFile.good())
        cout<<"File did not open!"<<endl;

    int DunNum=rand()%10+5;

    Dungeon *home=new Dungeon;
    root=home;
    home->finished=true;
    home->name="Family Home";
    home->key=8;
    home->parent=NULL;
    home->left=NULL;
    home->right=NULL;
    pos=home;
    setDungeonLevels(true,0,home);
    for(int i=0;i<DunNum;i++)//Adds amount of dungeons randomly to a BST
    {
        int fileSpot=rand()%12;//chooses a random one from the map
        int j=0;
        while(!readFile.eof())
        {
            if(j==fileSpot)
            {
                string name="";
                getline(readFile,name);
                int spot=rand()%17;
                insertDungeon(root,spot,name);
                break;
            }
            j++;
        }
    }

    player=charRandomizer();
}

void BSMap::insertDungeon(Dungeon *root,int spot,string name)//inserts new dungeons onto the map   working
{
    Dungeon *node=new Dungeon();
    node->name=name;
    node->key=spot;
    node->left=NULL;
    node->right=NULL;
    Dungeon *temp=root;
    Dungeon *ptr=temp;

    while(temp!=NULL)
    {
        ptr=temp;
        if(temp->key<=spot)
        {
            temp=temp->right;
        }
        else
        {
            temp=temp->left;
        }
        if(temp==NULL)
                break;
    }

    if(ptr->key<=spot)
    {
        ptr->right=node;
        node->parent=ptr;
    }
    else
    {
        ptr->left=node;
        node->parent=ptr;
    }

    for(int i=0;i<(rand()%10+1);i++)
    {
        setDungeonLevels(false,rand()%3+1,node);
    }
}

void BSMap::printMap()//prints map in least to greatest key working
{
    Dungeon *temp=root;
    if(temp->left!=NULL)
        printMap(temp->left);
    cout<<"Dungeon "<<temp->name <<endl;
    if(temp->right!=NULL)
        printMap(temp->right);
}

void BSMap::printMap(Dungeon *temp)//working
{
    if(temp->left!=NULL)
        printMap(temp->left);
    cout<<"Dungeon "<<temp->name <<endl;
    //dungeonInfo(temp);
    if(temp->right!=NULL)
        printMap(temp->right);
}

void BSMap::moveChar()
{
    cout<<"Which dungeon would you like to go to?"<<endl;
    cout<<"the following dungeons are accessible:"<<endl;

    avalibleMoves();//gets vectors that have either finished parents or null parents
    for(int i=0;i<moves.size();i++)
    {
        cout<<i<<": "<<moves[i]->name<<endl;
    }
    cout<<"Which dungeon would you like to visit? Enter a number!"<<endl;
    string choices="";
    getline(cin,choices);
    int choice=atoi(choices.c_str());
    pos=moves[choice];
    cout<<"You are now at the dungeon "<<pos->name<<endl;

    for(int i=0;i<=moves.size()+1;i++)//resets the vector so we dont get repeating moves
    {
        moves.pop_back();
    }

    choice=0;
    while(choice!=2)
    {
        cout<<"Do you wish to enter?"<<endl;
        cout<<"1: Enter the Dungeon"<<endl;
        cout<<"2: Return to Main Menu"<<endl;
        getline(cin,choices);
        choice=atoi(choices.c_str());

        switch(choice)
        {
            case 1:
                if((pos->name!="Family Home")&&!(pos->finished))
                    dungeonMenu();
                else if(pos->name!="Family Home")
                {
                    cout<<"This dungeon is already complete! It can not be be explored!"<<endl;
                    cout<<"Returning to Main Menu!"<<endl;
                    choice=2;
                }
                else
                {
                    cout<<"This is family home. No adventuring to be made"<<endl;
                    cout<<"Returning to Main Menu!"<<endl;
                    choice=2;
                }
                break;
            case 2:
                cout<<"Returning to Main Menu!"<<endl;
                break;
            default:
                cout<<"Not a valid input.Try again."<<endl;
                break;
        }
    }
     if(player->hp<=0)
            return;
}

void BSMap::avalibleMoves()//shows possible moves to only those that are next to completed dungeons
{
    //cout<<"public start"<<endl;
    Dungeon *temp=root;
    if(temp->left!=NULL)
        avalibleMoves(temp->left);
    //cout<<"public after left"<<endl;
    if((temp->parent==NULL)||(temp->parent->finished==true))
        moves.push_back(temp);
    //cout<<"public after insert"<<endl;
    if(temp->right!=NULL)
        avalibleMoves(temp->right);
    //cout<<"public after right"<<endl;
}

void BSMap::avalibleMoves(Dungeon *temp)
{
     if(temp->left!=NULL)
        avalibleMoves(temp->left);

    if(temp->parent->finished==true||temp->parent==NULL)
        moves.push_back(temp);

    if(temp->right!=NULL)
        avalibleMoves(temp->right);
}

void BSMap::dungeonMenu()
{
    string choices="";
    int choice=0;

    while(choice!=4)
    {
        cout<<"you are in the dungeon! What will you do?"<<endl;
        cout<<"1. Fight a level"<<endl;
        cout<<"2. heal wounds"<<endl;
        cout<<"3. Dungeon Information"<<endl;
        cout<<"4. Leave Dungeon"<<endl;

        getline(cin,choices);
        choice=atoi(choices.c_str());

        switch(choice)
        {
            case 1:
                combat();
                break;
            case 2:
                player->hp=player->maxHP;
                cout<<"You hear the Pokemon center jingle"<<endl;
                cout<<"You rest for a few hours and are fully healed"<<endl;
                break;
            case 3:
                dungeonInfo(pos);
                break;
            case 4:
                cout<<"you leave the dungeon and are now at its entrance."<<endl;
                break;
            default:
                cout<<"Danger will robinson danger! This was not a valid input! try again."<<endl;
                break;
        }
        if(pos->finished==true)
            return;
        if(player->hp<=0)
            return;
    }
}

void BSMap::dungeonInfo(Dungeon *hold)
{
    levels *temp=hold->start;
    int l=1;
    while(temp!=NULL)
    {
        cout<<"Floor: "<<l<<endl;
        cout<<"     "<<temp->monsters<<" monsters"<<endl;
        l+=1;
        temp=temp->next;
    }
}

void BSMap::setDungeonLevels(bool x,int m,Dungeon *hold)//sets dungeon linked list with monsters working
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

void BSMap::levelDelete(Dungeon *hold)//needs testing
{
    levels *temp=hold->start;
    hold->start=hold->start->next;
    delete temp;
    cout<<"current level has been defeated! The area suddenly disappears. You enter are outside the dungeon, but it looks to me smaller now."<<endl;
}

void BSMap::charInfo()
{
    cout<<"====================================="<<endl;
    cout<<"Player Statistics"<<endl;
    cout<<"Max Health: "<<player->maxHP<<endl;
    cout<<"Current Health: "<<player->hp<<endl;
    cout<<"Attack Modifier: "<<player->att<<endl;
    cout<<"Defense Modifier: "<<player->def<<endl;
    cout<<"Weapon: "<<player->weapon.name<<endl;
    cout<<"Armor: "<<player->armor.name<<endl;
    cout<<"====================================="<<endl;
}

void BSMap::monInfo(vector<monster*> mons)
{
    for(int i=0;i<mons.size();i++)
    {
        cout<<"====================================="<<endl;
        cout<<mons[i]->name<<" Statistics!"<<endl;
        cout<<"Max Health: "<<mons[i]->maxHP<<endl;
        cout<<"Current Health: "<<mons[i]->hp<<endl;
        cout<<"Attack Modifier: "<<mons[i]->att<<endl;
        cout<<"Defense Modifier: "<<mons[i]->def<<endl;
        cout<<"Weapon: "<<mons[i]->weapon.name<<endl;
        cout<<"Armor: "<<mons[i]->armor.name<<endl;
        cout<<"====================================="<<endl;
    }
}

monster *BSMap::charRandomizer()//randomly makes the character
{
    monster *x=new monster;

    x->maxHP=rand()%15+5;
    x->hp=x->maxHP;

    item wp;
    wp.name="Long Sword";
    wp.stat=8;
    wp.type="weapon";
    x->weapon=wp;

    item ar;
    ar.name="leather vest";
    ar.stat=4;
    ar.type="armor";
    x->armor=ar;

    x->att=rand()%3+2;
    x->def=rand()%4+2;

    return x;
}

monster *BSMap::monRandomizer()
{
    monster *x=new monster;

    x->name="monster";
    x->maxHP=rand()%10+1;
    x->hp=x->maxHP;

    item wp;
    wp.name="club";
    wp.stat=6;
    wp.type="weapon";
    x->weapon=wp;

    item ar;
    ar.name="mail";
    ar.stat=6;
    ar.type="armor";
    x->armor=ar;

    x->att=rand()%2+2;
    x->def=rand()%3+2;

    return x;
}

std::vector<monster*> BSMap::damageTurns(int playerDam,vector<monster*> mons)
{
    if(playerDam!=0)
    {
        cout<<"Who do you attack?"<<endl;
        for(int i=0;i<mons.size();i++)
        {
            cout<<i<<": "<<mons[i]->name<<endl;
        }
        string mon="";
        int moni=0;
        getline(cin,mon);
        moni=atoi(mon.c_str());
        int dam=(playerDam)-(mons[moni]->def);
        cout<<"You did "<<dam<<" damage!"<<endl;
        mons[moni]->hp=(mons[moni]->hp)-(dam);
        if(mons[moni]->hp<=0)
        {
            cout<<mons[moni]->name<<" has died!"<<endl;
            mons.erase(mons.begin()+moni);
            pos->start->monsters-=1;
        }
    }

    int action=0;
    for(int i=0;i<mons.size();i++)
    {
        action=rand()%3+1;
        if(action==1)
        {
            int dam=(mons[i]->att+rand()%mons[i]->weapon.stat+1)-(player->def);
            player->hp=(player->hp)-dam;
            cout<<"You took "<<dam<<" damage from "<<mons[i]->name<<endl;
        }
        else if(action==2)
            cout<<mons[i]->name<<" missed you!"<<endl;
        else
            cout<<mons[i]->name<<" does nothing..."<<endl;
    }
    return mons;
}

void BSMap::combat()
{
    cout<<endl;
    cout<<"You enter the level and encounter "<<pos->start->monsters<<" monsters!"<<endl;
    cout<<"you sneak up and get first action!"<<endl;
    vector<monster*> mons;

    for(int i=0;i<pos->start->monsters;i++)
    {
        mons.push_back(monRandomizer());
    }

    string choices="";
    int choice=0;
    int dam=0;
    int heal=0;

    while(choice!=5&&player->hp>0&&!mons.empty())
    {
        cout<<"!!!!!!Combat Menu!!!!!!"<<endl;
        cout<<"1.Attack a monster!"<<endl;
        cout<<"2.Attempt to heal a bit"<<endl;
        cout<<"3.Monster info"<<endl;
        cout<<"4.Player info"<<endl;
        cout<<"5.Run from combat"<<endl;
        getline(cin,choices);
        choice=atoi(choices.c_str());

        switch(choice)
        {
            case 1:
                dam=((player->att)+(rand()%(player->weapon.stat)+1));
                mons=damageTurns(dam,mons);
                break;
            case 2:
                cout<<"You attempt to heal!"<<endl;
                heal=rand()%8;
                player->hp+=heal;
                cout<<"you healed "<<heal<<"!"<<endl;
                if (player->hp>player->maxHP)
                {
                    cout<<"You are at full HP"<<endl;
                    player->hp=player->maxHP;
                }
                cout<<"your new health is "<<player->hp<<"!"<<endl;
                mons=damageTurns(0,mons);
                break;
            case 3:
                monInfo(mons);
                break;
            case 4:
                charInfo();
                break;
            case 5:
                cout<<"You run out of the dungeon!"<<endl;
                return;
        }
    }
    if(pos->start->monsters==0)
    {
        levelDelete(pos);
        if(pos->start==NULL)
        {
            pos->finished=true;
            return;
        }
    }
    if(player->hp<=0)
            return;
}

BSMap::BSMap()
{
    createMap();
}

BSMap::~BSMap()
{

}
