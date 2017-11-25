//  HexNode.cpp
//  HW4
//  Created by Morgan Scofield on 11/8/17.


#include "HexNode.hpp"

HexNode::HexNode(int a, int b){
    x = a;
    y = b;
    ID = (a * 11 + b);
    color = 2;  //Gray --> undefined
}

int HexNode::getID(HexNode &N){
    return N.ID;
}

int HexNode::getX(HexNode &N){
    return N.x;
}

int HexNode::getY(HexNode &N){
    return N.y;
}

int HexNode::getColor(){
    return color;
}

void HexNode::changeColor(HexNode &N, int c){
    N.color = c;
}

bool HexNode::operator==(const HexNode &N){
    return (this->ID == N.ID);
}
