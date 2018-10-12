#include <iostream>
#include <random>
#include <memory>
#include "ResourceNetwork.h"

/*
    what is finished?
    There is a structure for the nodes in the production network,
    It is possible to print the different values in the console

    TODO: Fix gameloop so that it works with both single and multiply args
    TODO: Create algorithim to decide production based on the demand when there exists a tranport opportunity betweeb the nodes
    TODO: Implement a refinery node which can refine resources if there is a supply
    TODO: Create a better printing methos
 */

int loop;

void printWorld(ResourceNetwork net) {
    std::cout << std::to_string(net.size()) << "\n";
    std::cout << "Name \t maxProd \t curProd \t demanded \t Demanders" << "\n";
    for (int i = 0; i < net.size()/2; ++i)
    {
        std::cout << ((ProducerNode*)net.getNode(i))->toString() << "\n";
    }

    std::cout << "\n -------------- \n" << "\n";
    std::cout << "Name \t maxCons \t curCons \t supply" << "\n";
    for (int i = net.size()/2; i < net.size(); ++i)
    {
        std::cout << ((ConsumerNode*)net.getNode(i))->toString() << "\n";
    }
}

int gameloop(ResourceNetwork net) {

    std::string command;
    int arg1, arg2;
    std::cout << "Enter command for what to do" << "\n";
    std::cin >> command >> arg1 >> arg2;
    std::cout << command << "\n";

    if(command == "add") {
        std::cout << "add " << std::to_string(arg1) << " to " << std::to_string(arg2) << "\n";

        ((ResourceNode*)net.getNode(arg1))->addNode(((ResourceNode*)net.getNode(arg2)));
    }
    else if ( command == "rm") {
        std::cout << "remove " << std::to_string(arg1) << " from " << std::to_string(arg2) << "\n";
        ((ResourceNode*)net.getNode(arg1))->removeNode(((ResourceNode*)net.getNode(arg2)));
    }
    else if (command == "exit") {
        std::cout << "Exit loop" << "\n";
        loop = 0;
    }
    else {
        std::cout << "command not found retry" << "\n";
    }

    printWorld(net);
}

int main(int argc, char* argv[])
{
    std::vector<ResourceNode*> nodes;
    for (int i = 0; i < 5; ++i)
    {
        ProducerNode *pnode = new ProducerNode(i);
        ConsumerNode *cnode = new ConsumerNode(i+5);

        nodes.push_back(pnode);
        nodes.push_back(cnode);
    }

    //Contains all the nodes in the network
    ResourceNetwork rnet(nodes);
    loop = 1;
    while(loop != 0) {
        gameloop(rnet);
        std::cout << std::to_string(loop) << "\n";
    }

    return 0;
}
