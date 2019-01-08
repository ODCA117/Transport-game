#include "TransportNetwork.h"
#include <iostream>

TransportNetwork::TransportNetwork() {
    stations = new std::vector<Station*>();
    stations->reserve(5);
}

TransportNetwork::TransportNetwork(std::vector<Station*> *net) {
    stations = net;
}

int TransportNetwork::findIndex(int id) {
    for (unsigned int i = 0; i < stations->size(); ++i)
    {
        if(stations->at(i)->getId() == id){
            return i;
        }
    }
    return -1;
}

Station* TransportNetwork::getStation(int id) {
    int i = findIndex(id);
    if(i >= 0) {
        return stations->at(i);
    }

    return NULL;
}

int TransportNetwork::getId(int i) {
    return stations->at(i)->getId();
}

void TransportNetwork::addStation(Station *station) {
    stations->push_back(station);
}

void TransportNetwork::removeStation(int id) {
    int i = findIndex(id);
    if (i >= 0) {
        stations->erase(stations->begin() + i);
    }
}

int TransportNetwork::size() {
    return stations->size();
}

void TransportNetwork::printStations(){
    for (unsigned int i = 0; i < stations->size(); ++i)
    {
        std::cout << "Station" << stations->at(i)->getId() << "\n";
    }
}

/*---------------------------------*/
/*-------------Station-------------*/
/*---------------------------------*/

Station::Station(int id) : id(id){}
Station::Station(int id, ResourceNetwork rnet) : id(id), rnet(rnet) {}

bool Station::operator==(Station rhs) {
    bool res = id == rhs.id;
    return res;
}

int Station::getId() {
    return id;
}

void Station::addStation(Station *station) {
    stations.push_back(station);
}

void Station::removeStation(int id) {
    for( unsigned int i = 0; i < stations.size(); i++) {
        if(stations[i]->id == id) {
            stations.erase(stations.begin() + i);
        }
    }
}

void Station::addNode(ResourceNode* node) {
    rnet.addNode(node);
}

void Station::removeNode(int id) {
    rnet.removeNode(id);
}

std::vector<int> Station::getNodes() {
    return rnet.getNodes();
}

std::vector<int> Station::getStations() {
    std::vector<int> s;
    for(unsigned int i = 0; i < stations.size(); i++) {
        s.push_back(stations.at(i)->getId());
    }
    return s;
}

void Station::printStations() {
    for (unsigned int i = 0; i < stations.size(); ++i)
    {
        std::cout << "Station:" << stations[i]->id << "\n";
    }
}

void Station::printNodes() {
    //rnet.printNodes();
    std::cout << "NULL" << "\n";
}

std::string Station::toString() {
    std::string str = "";
    str += "Station" + std::to_string(id) + "\t";
    str += std::to_string(stations.size()) + "\t";
    str += std::to_string(rnet.size());
    return str;
}
