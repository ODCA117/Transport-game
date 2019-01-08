#ifndef NODE_INTERFACE
#define NODE_INTERFACE

#include "ResourceNetwork.h"
#include "TransportNetwork.h"

//class to make the usage simpler and more inuative
//create add station and remove station
class NetworkInterface {
private:
    ResourceNetwork rnet;
    TransportNetwork tnet;
    //should probably not be needed??
    void connectNodes(int node1, int node2);
    void disconnectNodes(int node1, int node2);

public:
    NetworkInterface();
    void createProducer(int id);
    void createConsumer(int id);
    void createStation(int id);

    void addNodeToStation(int nodeID, int stationID);
    void removeNodeForStation(int nodeID, int stationID);

    std::vector<int> getNodesAtStation(int stationID);

    std::vector<int> getConnectedStations(int stationID);

    void connectStations(int station1, int station2);
    void disconnectStations(int station1, int station2);

    //update the values in loop
    void update(double deltaTime);
    void print();
};
#endif
