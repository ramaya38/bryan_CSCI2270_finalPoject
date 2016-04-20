#include <iostream>
#include <stdlib.h>
#include "BSMap.h"
#include "Creature.h"

using namespace std;

int main()
{
    bool start=false;
    string response="";
    int choice=0;
    cout<<"You begin your quest for fame and fortune!"<<endl;
    cout<<"You heard rumor of treasure and glory to be had in the elemental dungeons"<<endl;
    cout<<"You grab the gear your family owns and set out"<<endl;
    cout<<"=============================================="<<endl;
    cout<<"begin a new adventure? hit 1"<<endl;

    getline(cin,response);
    if(response=="1")
    {
        start=true;
        //start new character here
        //set world map
        //set dungeon layout

    }
    else
        cout<<"Game has been turned off! No adventure started!"<<endl;

    while(start)
    {
        cout<<"You are resting. What would you like to do next?"<<endl;
        cout<<"1. Go to a dungeon"<<endl;
        cout<<"2. Look at map"<<endl;
        cout<<"3. Check inventory"<<endl;
        cout<<"4. Rest over night"<<endl;
        cout<<"5. Quit the game"<<endl;

        getline(cin,response);
        choice=atoi(response.c_str());

        switch(choice)
        {
            case 1:
                //go to dungeon
                break;
            case 2:
                //look at map
                break;
            case 3:
                //check inventory
                break;
            case 4:
                //heal character and reset dungeons
                break;
            case 5:
                start=false;
                cout<<"Game has been turned off! Restart program to play again!"<<endl;
                break;
        }
    }
    return 0;
}
