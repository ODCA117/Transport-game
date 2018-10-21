#ifndef TRANSPORT_NETWORK
#define TRANSPORT_NETWORK

#include <vector>
#include <string>
#include <iomanip>
#include "ResourceNetwork.h"

class Station;


class TransportNetwork {
private:
    std::vector<Station*> stations;
public:
    TransportNetwork ();
};

class Station {
private:
    int id;
    ResourceNetwork rnet;
    std::vector<Station*> connectedStations;

public:
    Station ();
    Station (int id, ResourceNetwork nodes);
    void addStation();
    void removeStations(int id);
    void addNodes();
    void removeNodes(int id);
    void listStations();
    void listNodes();

};

#endif
