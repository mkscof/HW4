//  main.cpp
//  HW4
//  Created by Morgan Scofield on 11/8/17.

#include <iostream>
#include <ctime>
#include "HexGraph.hpp"

int main(int argc, const char * argv[]) {
    HexGraph H = HexGraph();
    H.printGraph(H);
    std::cout << std::endl;
    H.playGame(H);
    H.printGraph(H);
    return 0;
}
