//  HexNode.hpp
//  HW4
//  Created by Morgan Scofield on 11/8/17.

#ifndef HexNode_hpp
#define HexNode_hpp

#include <stdio.h>
#include <iostream>

class HexNode{
private:
    int ID;
    int x;
    int y;
    //Using white/black instead of red/blue
    //Black = east/west, White = north/south
    int color;
public:
    
    HexNode(){};
    //Constructor
    HexNode(int a, int b);
    //Returns ID of node N
    int getID(HexNode &N);
    //Returns x coordinate of node N
    int getX(HexNode &N);
    //Returns y coordinate of node N
    int getY(HexNode &N);
    //Returns color of node N
    int getColor();
    //Change color of node N
    void changeColor(HexNode &N, int c);
    //Equals overload
    bool operator ==(const HexNode &N);
    void setID(int newID){
        ID = newID;
    };
};
#endif /* HexNode_hpp */
