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
    void* getStation(int id);
    int getId(int i);
    void addStation(Station* station);
    void removeStation(int id);
    int size();
    void listStations();
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
    void listStations();
    void listNodes();
    std::string toString();
};

#endif
