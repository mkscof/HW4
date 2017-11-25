//  HexGraph.cpp
//  HW4
//  Created by Morgan Scofield on 11/8/17.

#include "HexGraph.hpp"

HexGraph::HexGraph(){
    int count = 0;
    edgeCount = 0;
    edgeList.resize(121);
    for(int i = 0; i < 11; i++){
        for(int j = 0; j < 11; j++){
            nodeList.push_back(HexNode(i, j));
            if(i == 0){
                //top left corner
                if(j == 0){
                    edgeList[count].push_front(i * 11 + j + 1);
                    edgeList[count].push_front((i + 1) * 11 + j);
                    edgeCount = edgeCount + 2;
                }
                //top right corner
                else if(j == 10){
                    edgeList[count].push_front(i * 11 + j - 1);
                    edgeList[count].push_front((i + 1) * 11 + j);
                    edgeList[count].push_front((i + 1) * 11 + j - 1);
                    edgeCount = edgeCount + 3;
                }
                //top edge
                else if(j != 0 && j != 10){
                    edgeList[count].push_front(i * 11 + j + 1);
                    edgeList[count].push_front((i + 1) * 11 + j);
                    edgeList[count].push_front(i * 11 + j - 1);
                    edgeList[count].push_front((i + 1) * 11 + j - 1);
                    edgeCount = edgeCount + 4;
                }
            }
            else if(i == 10){
                //bottom left corner
                if(j == 0){
                    edgeList[count].push_front((i - 1) * 11 + j);
                    edgeList[count].push_front((i - 1) * 11 + j + 1);
                    edgeList[count].push_front(i * 11 + j + 1);
                    edgeCount = edgeCount + 3;
                }
                //bottom right corner
                else if(j == 10){
                    edgeList[count].push_front((i - 1) * 11 + j);
                    edgeList[count].push_front(i * 11 + j - 1);
                    edgeCount = edgeCount + 2;
                }
                //bottom edge
                else if(j != 0 && j != 10){
                    edgeList[count].push_front((i - 1) * 11 + j);
                    edgeList[count].push_front(i * 11 + j - 1);
                    edgeList[count].push_front((i - 1) * 11 + j + 1);
                    edgeList[count].push_front(i * 11 + j + 1);
                    edgeCount = edgeCount + 4;
                }
            }
            else if(i != 0 && i != 10){
                //left edge
                if(j == 0){
                    edgeList[count].push_front(i * 11 + j + 1);
                    edgeList[count].push_front((i + 1) * 11 + j);
                    edgeList[count].push_front((i - 1) * 11 + j);
                    edgeList[count].push_front((i - 1) * 11 + j + 1);
                    edgeCount = edgeCount + 4;
                }
                //right edge
                else if(j == 10){
                    edgeList[count].push_front(i * 11 + j - 1);
                    edgeList[count].push_front((i + 1) * 11 + j);
                    edgeList[count].push_front((i + 1) * 11 + j - 1);
                    edgeList[count].push_front((i - 1) * 11 + j);
                    edgeCount = edgeCount + 4;
                }
                //inner node
                else{
                    edgeList[count].push_front(i * 11 + j + 1);
                    edgeList[count].push_front((i + 1) * 11 + j);
                    edgeList[count].push_front(i * 11 + j - 1);
                    edgeList[count].push_front((i + 1) * 11 + j - 1);
                    edgeList[count].push_front((i - 1) * 11 + j);
                    edgeList[count].push_front((i - 1) * 11 + j + 1);
                    edgeCount = edgeCount + 6;
                }
            }
            count++;
        }
    }
}

void HexGraph::playGame(HexGraph &G){
    std::vector<int> shuffled;
    for(int i = 0; i < 121; i++){
        shuffled.push_back(i);
    }
    pTurn = 1;
    
    //Seed random generator and shuffle nodes
    unsigned seed = static_cast<int>(time(0));
    std::mt19937 gen(seed);
    std::shuffle(shuffled.begin(), shuffled.end(), gen);
    
    for(auto i = shuffled.begin(); i != shuffled.end(); i++){
        int curr = *i;
        //Change to black
        if(pTurn % 2 == 1){
            nodeList.at(curr).changeColor(nodeList.at(curr), 1);
            blackList.push_back(nodeList.at(curr));
            DFS(blackList);
            if(isOver){
                std::cout << "Black Wins" << std::endl;
                break;
            }
            pTurn++;
        }
        //Change to white
        else if(pTurn % 2 == 0){
            nodeList.at(curr).changeColor(nodeList.at(curr), 0);
            whiteList.push_back(nodeList.at(curr));
            DFS(whiteList);
            if(isOver){
                std::cout << "White Wins" << std::endl;
                break;
            }
            pTurn++;
        }
    }
}

void HexGraph::DFS(std::vector<HexNode> input){
    std::vector<bool> visited(input.size(), false);
    std::vector<HexNode> startOptsB;
    std::vector<HexNode> startOptsW;
    std::vector<int> stack;

    //If turn = white
    if(pTurn % 2 == 0){
        //Add nodes on top edge of graph to vector
        for(int i = 0; i < input.size(); i++){
            if(input.at(i).getX(input.at(i)) == 0){
                dfsHelper(input, visited, input.at(i).getID(input.at(i)), stack, i);
            }
            if(isOver == true){
                break;
            }
        }
    }
    //If turn = black
    else if(pTurn % 2 == 1){
        //Add nodes on left edge of graph to vector
        for(int i = 0; i < input.size(); i++){
            if(input.at(i).getY(input.at(i)) == 0){
                dfsHelper(input, visited, input.at(i).getID(input.at(i)), stack, i);
            }
            if(isOver == true){
                break;
            }
        }
    }
    return;
}

void HexGraph::dfsHelper(std::vector<HexNode> input, std::vector<bool> v, int s, std::vector<int>& stack, int index){
    stack.push_back(s);
    v[index] = true;

    //If path has been found end game
    if(pTurn % 2 == 0){
        if(s / 11 == 10){
            isOver = true;
            return;
        }
        else{
            //Recursively add adjacent nodes until game ends or no path is available
            for(int i = 0; i < edgeList[s].size(); i++){
                if(isOver == true){
                    break;
                }
                HexNode node;
                node.setID(edgeList[s].at(i));
                vector<HexNode>::iterator p = find(input.begin(),input.end(),node);
                int dIndex = distance(input.begin(), p);
                if (p != input.end() && v[dIndex] != true){
                    dfsHelper(input, v, edgeList[s].at(i), stack, dIndex);
                }
            }
        }
        return;
    }
    else{
        if(s % 11 == 10){
            isOver = true;
            return;
        }
        else{
            for(int i = 0; i < edgeList[s].size(); i++){
                if(isOver == true){
                    break;
                }
                HexNode node;
                node.setID(edgeList[s].at(i));
                vector<HexNode> :: iterator p = find(input.begin(),input.end(),node);
                int distancep = distance(input.begin(), p);
                if (p != input.end() && v[distancep] != true) {
                    dfsHelper(input, v, edgeList[s].at(i), stack, distancep);
                }
            }
        }
        return;
    }
}

std::vector<HexNode> HexGraph::createTree(HexGraph &G, std::vector<HexNode> input){
    return input;
}

int HexGraph::E(HexGraph &G){
    return G.edgeCount;
}

int HexGraph::V(HexGraph &G){
    return G.nodeCount;
}

void HexGraph::printGraph(HexGraph &G){
    std::string indent = " ";
    int count = 0;
    for(int i = 0; i < nodeList.size(); i++){
        if(nodeList.at(i).getColor() == 0){       //White
            std::cout << "◦ ";
            count++;
        }
        else if(nodeList.at(i).getColor() == 1){  //Black
            std::cout << "● ";
            count++;
        }
        else if(nodeList.at(i).getColor() == 2){  //Gray
            std::cout << "# ";
            count++;
        }
        if(count % 11 == 0){
            std::cout << std::endl;
            std::cout << indent;
            indent.append(" ");
        }
    }
}
