#include <iostream>
#include "NetworkInterface.h"

NetworkInterface::NetworkInterface(){

}

void NetworkInterface::createProducer(int id) {
    ProducerNode *node = new ProducerNode(id);
    rnet.addNode(node);
    std::cout << "rnet size: " << rnet.size() << "\n";
}

void NetworkInterface::createConsumer(int id) {
    ConsumerNode *node = new ConsumerNode(id);
    rnet.addNode(node);
}

void NetworkInterface::createStation(int id) {
    Station *station = new Station(id);
    tnet.addStation(station);
}


//private
void NetworkInterface::connectNodes(int node1, int node2) {
    ResourceNode *n1 = (ResourceNode*)rnet.getNode(node1);
    ResourceNode *n2 = (ResourceNode*)rnet.getNode(node2);

    n2->addNode(n1);
    n1->addNode(n2);
}
//private
void NetworkInterface::disconnectNodes(int node1, int node2) {
    ResourceNode *n1 = (ResourceNode*)rnet.getNode(node1);
    ResourceNode *n2 = (ResourceNode*)rnet.getNode(node2);

    n2->removeNode(node1);
    n1->removeNode(node2);
}

void NetworkInterface::addNodeToStation(int nodeID, int stationID) {
    ResourceNode *node = (ResourceNode*)rnet.getNode(nodeID);
    Station *station = tnet.getStation(stationID);
    station->addNode(node);

    //connect station to the other stations
}

void NetworkInterface::removeNodeForStation(int nodeID, int stationID) {
    Station *station = tnet.getStation(stationID);
    station->removeNode(nodeID);
}


std::vector<int> NetworkInterface::getNodesAtStation(int stationID) {
    Station *station = tnet.getStation(stationID);
    return station->getNodes();
}

std::vector<int> NetworkInterface::getConnectedStations(int stationID){
    Station *station = tnet.getStation(stationID);
    return station->getStations();
}


void NetworkInterface::connectStations(int station1, int station2) {
    Station *s1 = tnet.getStation(station1);
    Station *s2 = tnet.getStation(station2);

    s1->addStation(s2);
    s2->addStation(s1);
    //connect nodes between these nodes
    //1 get a list of all the nodes within the other station
    //connect them with eachother
}

void NetworkInterface::disconnectStations(int station1, int station2 ) {
    Station *s1 = tnet.getStation(station1);
    Station *s2 = tnet.getStation(station2);

    s1->removeStation(station2);
    s2->removeStation(station1);
}

void NetworkInterface::update(double deltaTime) {

    std::cout << "Update" << "\n";
    for (int i = rnet.size()/2; i < rnet.size(); ++i)
    {
        ((ConsumerNode*)rnet.getNode(i))->update(deltaTime);
}

    for (int i = 0; i < rnet.size()/2; ++i)
    {
        ((ProducerNode*)rnet.getNode(i))->update(deltaTime);
    }
}

void NetworkInterface::print() {
    std::cout << "\n -------------- \n" << "\n";
    std::cout <<"station:id stations nodes" << "\n";
    for (int i = 10; i < 10 + tnet.size(); ++i)
    {
        std::cout << tnet.getStation(i)->toString() << "\n";
    }

    std::cout << "\n -------------- \n" << "\n";

    std::cout << "Name\t maxProd \t curProd \t demanded \t Demanders" << "\n";
    for (int i = 0; i < rnet.size()/2; ++i)
    {
        std::cout << ((ProducerNode*)rnet.getNode(i))->toString() << "\n";
    }

    std::cout << "\n -------------- \n" << "\n";
    std::cout << "Name \t maxCons \t curCons \t supply" << "\n";
    for (int i = rnet.size()/2; i < rnet.size(); ++i)
    {
        std::cout << ((ConsumerNode*)rnet.getNode(i))->toString() << "\n";
    }
}