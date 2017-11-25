//  HexGraph.hpp
//  HW4
//  Created by Morgan Scofield on 11/8/17.

#ifndef HexGraph_hpp
#define HexGraph_hpp

#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include <deque>
#include <stack>
#include <random>
#include <iterator>
#include <ctime>
#include "HexNode.hpp"

using namespace std;

class HexGraph{
private:
    const int nodeCount = 121;
    int edgeCount;
    std::vector<std::deque<int> > edgeList;
public:
    //Constructor
    HexGraph();
    //Initializes the nodes randomly
    void playGame(HexGraph &G);
    //Runs DFS on black or white nodes
    void DFS(std::vector<HexNode> input);
    //DFS helper function
    void dfsHelper(std::vector<HexNode> input, std::vector<bool> v, int s, std::vector<int>& stack, int index);
    //Creates black and white vector trees
    std::vector<HexNode> createTree(HexGraph &G, std::vector<HexNode> input);
    //Returns degree of edges
    int E(HexGraph &G);
    //Returns degree of edges
    int V(HexGraph &G);
    //Print graph
    void printGraph(HexGraph &G);
    
    //Player turn: Black = 1, White = 0
    int pTurn;
    //State of game
    bool isOver = false;;
    //List of nodes
    std::vector<HexNode> nodeList;
    //Black Nodes
    std::vector<HexNode> blackList;
    //White Nodes
    std::vector<HexNode> whiteList;
};

#endif /* HexGraph_hpp */
