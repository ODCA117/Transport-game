#include <iostream>
#include <sstream>
#include <iterator>
#include <random>
#include <memory>
#include <vector>
#include "ResourceNetwork.h"
#include "TransportNetwork.h"

/*
    what is finished?
    There is a structure for the nodes in the production network,
    It is possible to print the different values in the console
    The production algotithm is right now implemented

    TODO: Separate demand between different producer, consumer knows how many producers it has
    TODO: Create a transport network which accepts a resource and an adress and sends the resource to that address
    TODO: create a interface to use to make it all easier to use
    TODO: create some way to different consumers, producers.
    TODO: Use multiple resources
    TODO: Add different types of resources.
    TODO: Create a better printing methods
    TODO: Implement a refinery node which can refine resources if there is a supply
    TODO: loop may make two conuser use to more than produced, one at 51 and the other at 50
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
void gameloop(ResourceNetwork *net) {

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
        //get consumerNode and ProducerNode
        ConsumerNode *cNode = (ConsumerNode*)net->getNode(arg2);
        ProducerNode *pNode = (ProducerNode*)net->getNode(arg1);
        //add each node to each other
        pNode->addNode(cNode);
        cNode->addNode(pNode);
    }
    else if (args[0] == "rm") {
        std::cout << "remove " << std::to_string(arg1) << " from " << std::to_string(arg2) << "\n";
        ((ResourceNode* )net->getNode(arg1))->removeNode(arg2);
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
    // adding Resource nodes to the system
    ResourceNetwork *rnet = new ResourceNetwork();
    for (int i = 0; i < 5; ++i)
    {
        ProducerNode *pnode = new ProducerNode(i);
        ConsumerNode *cnode = new ConsumerNode(i + 5);

        rnet->addNode(pnode);
        rnet->addNode(cnode);
    }

    int id = ((ProducerNode*)rnet->getNode(0))->getId();
    std::cout << id << "\n";

    // // adding transport nodes to the system
    // std::vector<ResourceNode*> stnNodes;
    // stnNodes.push_back(nodes[0]);
    // stnNodes.push_back(nodes[5]);
    // Station *stn = new Station(0, stnNodes);
    // std::vector<Station*> tnet;
    // tnet.push_back(stn);


    //Contains all the nodes in the network
    loop = 1;
    while(loop != 0) {
        gameloop(rnet);
        update(*rnet);
        printWorld(*rnet);
    }

    return 0;
}
