#include <iostream>
#include <sstream>
#include <iterator>
#include <random>
#include <memory>
#include <vector>
#include "network/NetworkInterface.h"

/*
    what is finished?
    There is a structure for the nodes in the production network,
    It is possible to print the different values in the console
    The production algotithm is right now implemented

    TODO: Create a transport network which accepts a resource and an adress and sends the resource to that address
    TODO: create a interface to use to make it all easier to use
    TODO: create some way to different consumers, producers.
    TODO: Use multiple resources
    TODO: Add different types of resources.
    TODO: Create a better printing methods
    TODO: Implement a refinery node which can refine resources if there is a supply
    TODO: loop may make two conuser use to more than produced, one at 51 and the other at 50
 */

#define DELTA_TIME 0.3

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
void gameloop(NetworkInterface* ni) {

    //prompt user for command
    std::string command;
    std::cout << "Enter command for what to do" << "\n";
    std::getline(std::cin, command);

    //split command by spaces
    std::istringstream iss(command);
    std::vector<std::string> args(
        (std::istream_iterator<std::string>(iss)),
         std::istream_iterator<std::string>());

    // check if no argument is added before



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
    if(args[0] == "cn") { //should not be used here. will be called when creating station
        std::cout << "cn " << args[1] << " to " << args[2] << "\n";
        ni->connectNodes(arg1, arg2);
    }
    else if (args[0] == "rn") { //should not be used here. will be called when creating station
        std::cout << "disconnect Nodes " << args[1] << " and " << args[2] << "\n";
        ni->disconnectNodes(arg1, arg2);
    }
    else if (args[0] == "cs") {
        std::cout << "connect stations " << args[1] << " to " << args[2] << "\n";
        ni->connectStations(arg1, arg2);
    }
    else if (args[0] == "rs" ) {
        std::cout << "disconnect stations " << args[1] << " and " << args[2] << "\n";
        ni->disconnectStations(arg1, arg2);
    }
    else if (args[0] == "addNode") {
        std::cout << "add node " << args[1] << " to station " << args[2] << "\n";
        ni->addNodeStation(arg1, arg2);
    }
    else if (args[0] == "removeNode") {
        std::cout << "remove node " << args[1] << " from station " << args[2] << "\n";
        ni->removeNodeStation(arg1, arg2);
    }
    else {
        std::cout << "command not found retry" << "\n";
    }
}

void update(NetworkInterface* ni) {
    ni->update(DELTA_TIME);
}

int main(int argc, char* argv[])
{
    /* -----------------old soultion--------------
    // adding Resource nodes to the system
    ResourceNetwork *rnet = new ResourceNetwork();
    for (int i = 0; i < 5; ++i)
    {
        ProducerNode *pnode = new ProducerNode(i);
        ConsumerNode *cnode = new ConsumerNode(i + 5);

        rnet->addNode(pnode);
        rnet->addNode(cnode);
    }
    */

    NetworkInterface *ni = new NetworkInterface();

    for(int i = 0; i < 15; i++) {
        if(i < 5) {
            ni->createProducer(i);
        }
        else if (i < 10) {
            ni->createConsumer(i);
        }
        else {
            ni->createStation(i);
        }
    }

    //Contains all the nodes in the network
    loop = 1;
    while(loop != 0) {
        gameloop(ni);
        update(ni);
        ni->print();
    }

    return 0;
}
