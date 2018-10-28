#ifndef TRANSPORT_NETWORK
#define TRANSPORT_NETWORK

#include <vector>
#include <string>
#include <iomanip>
#include "ResourceNetwork.h"

class Station;

class TransportNetwork {
private:
    std::vector<Station*> *stations;
    int findIndex(int id);
public:
    TransportNetwork();
    TransportNetwork(std::vector<Station*> *stations);
    Station* getStation(int id);
    int getId(int i);
    void addStation(Station* station);
    void removeStation(int id);
    int size();
    void printStations();
};

class Station {
private:
    int id;
    ResourceNetwork rnet;
    std::vector<Station*> stations;

public:
    Station (int id);
    Station (int id, ResourceNetwork nodes);
    bool operator==(const Station rhs);
    int getId();
    void addStation(Station *station);
    void removeStation(int id);
    void addNode(ResourceNode* node);
    void removeNode(int id);
    void printStations();
    void printNodes();
    std::string toString();
};

#endif
