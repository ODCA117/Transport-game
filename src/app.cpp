#include <iostream>
#include <sstream>
#include <iterator>
#include <random>
#include <memory>
#include <vector>
#include "ResourceNetwork.h"

/*
    what is finished?
    There is a structure for the nodes in the production network,
    It is possible to print the different values in the console
    The production algotithm is right now implemented


    TODO: Implement a refinery node which can refine resources if there is a supply
    TODO: Create a transport network which accepts a resource and an adress and sends the resource to that address
    TODO: Transport multiple resources at the same time but with higher time interval
    TODO: Separate demand between different producer, consumer knows how many producers it has
    TODO: Add different types of resources.
    TODO: Create a better printing methos
 */

int loop;

void printWorld(ResourceNetwork net) {
    std::cout << std::to_string(net.size()) << "\n";
    std::cout << "Name\t maxProd \t curProd \t demanded \t Demanders" << "\n";
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

//simulation for the program in current state
void gameloop(ResourceNetwork net) {

    //prompt user for command
    std::string command;
    std::cout << "Enter command for what to do" << "\n";
    std::getline(std::cin, command);

    //split command by spaces
    std::istringstream iss(command);
    std::vector<std::string> args(
        (std::istream_iterator<std::string>(iss)),
         std::istream_iterator<std::string>());

    if (args[0] == "loop") {
        std::cout << "loop one time" << "\n";
        return;
    }
    else if (args[0] == "exit") {
        //user wants to quit
        std::cout << "Exit loop" << "\n";
        loop = 0;
        return;
    }

    else if (args.size() < 3) {
        //not enough arguments try again
        std::cout << "not enough arguments" << "\n";
        return;
    }

    //arguments after
    int arg1 = std::stoi(args[1]);
    int arg2 = std::stoi(args[2]);
    if(args[0] == "add") {
        std::cout << "add " << args[1] << " to " << args[2] << "\n";

        ((ResourceNode*)net.getNode(arg1))->addNode(((ResourceNode*)net.getNode(arg2)));
    }
    else if (args[0] == "rm") {
        std::cout << "remove " << std::to_string(arg1) << " from " << std::to_string(arg2) << "\n";
        ((ResourceNode*)net.getNode(arg1))->removeNode(((ResourceNode*)net.getNode(arg2)));
    }
    else {
        std::cout << "command not found retry" << "\n";
    }
}

void update(ResourceNetwork net) {

    //first loop through all Consumers then all the producers
    std::cout << "Update" << "\n";
    for (int i = net.size()/2; i < net.size(); ++i)
    {
        //Consumer Loop
        ((ConsumerNode*)net.getNode(i))->update(0.3);

    }

    for (int i = 0; i < net.size()/2; ++i)
    {
        //Producer Loop
        ((ProducerNode*)net.getNode(i))->update(0.3);

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
    loop = 1;
    while(loop != 0) {
        gameloop(rnet);
        update(rnet);
        printWorld(rnet);
    }

    return 0;
}
