#ifndef NODE_INTERFACE
#define NODE_INTERFACE

#include "ResourceNetwork.h"
#include "TransportNetwork.h"

//class to make the usage simpler and more inuative
class NetworkInterface {
private:
    ResourceNetwork rnet;
    TransportNetwork tnet;
public:
    NetworkInterface();
    void createProducer(int id);
    void createConsumer(int id);
    void createStation(int id);

    void connectNodes(int node1, int node2);
    void disconnectNodes(int node1, int node2);

    void addNodeStation(int nodeID, int stationID);
    void removeNodeStation(int nodeID, int stationID);

    void connectStations(int station1, int station2);
    void disconnectStations(int station1, int station2);

    std::vector<int> getConnectedNodes(int id);
    //update the values in loop
    void update(double deltaTime);
    void print();
};
#endif
