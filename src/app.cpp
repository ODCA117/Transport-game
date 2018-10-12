#include <iostream>
#include <random>
#include <memory>
#include "ResourceNetwork.h"

/*
    what is finished?
    There is a structure for the nodes in the production network,
    It is possible to print the different values in the console

    TODO: Create a better printing methos
    TODO: Create testloop where it is possible to change the values during runtime
    TODO: Create algorithim to decide production based on the demand when there exists a tranport opportunity betweeb the nodes
    TODO: Implement a refinery node which can refine resources if there is a supply
 */

void printWorld(ResourceNetwork net) {
    std::cout << std::to_string(net.size()) << "\n";
    std::cout << "Name \t maxProd \t curProd \t demanded \t connected ID:s" << "\n";
    for (int i = 0; i < net.size()/2; ++i)
    {
        std::cout << ((ProducerNode*)net.getNode(i))->toString() << "\n";
    }

    std::cout << "\n --------------" << "\n";
    std::cout << "Name \t maxCons \t curCons \t supply \t connected ID:s" << "\n";
    for (int i = net.size()/2; i < net.size(); ++i)
    {
        std::cout << ((ConsumerNode*)net.getNode(i))->toString() << "\n";
    }
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
    printWorld(rnet);

    return 0;
}
