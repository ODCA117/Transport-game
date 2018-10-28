#include "catch.hpp"
#include "../src/ResourceNetwork.h"
#include "../src/TransportNetwork.h"
#include "../src/NetworkInterface.h"

//Set up network
NetworkInterface* setUpNetwork() {
    NetworkInterface *ni = new NetworkInterface();

    //create nodes and stations
    ni->createProducer(1);
    ni->createProducer(2);
    ni->createConsumer(3);
    ni->createConsumer(4);
    ni->createStation(5);
    ni->createStation(6);

    //add nodes to stations
    ni->addNodeStation(1,5);
    ni->addNodeStation(3,5);
    ni->addNodeStation(2,6);
    ni->addNodeStation(4,6);

    //connect stations
    ni->connectStations(5, 6);
}

TEST_CASE("Nodes get nodes from other station" , "Multi-file:2") {
    NetworkInterface *ni = setUpNetwork();

    std::vector<int> p1Nodes = ni->getConnectedNodes(1);
    std::vector<int> p2Nodes = ni->getConnectedNodes(2);

    //check that p1 has all consumers connected
    REQUIRE(std::find(p1Nodes.begin(), p1Nodes.end(), 3) != p1Nodes.end());
    REQUIRE(std::find(p1Nodes.begin(), p1Nodes.end(), 4) != p1Nodes.end());

    //check that p2 has all consumers connected
    REQUIRE(std::find(p2Nodes.begin(), p2Nodes.end(), 3) != p2Nodes.end());
    REQUIRE(std::find(p2Nodes.begin(), p2Nodes.end(), 4) != p2Nodes.end());

    //consumer
    std::vector<int> c1Nodes = ni->getConnectedNodes(3);
    std::vector<int> c2Nodes = ni->getConnectedNodes(4);

    //check that c1 has all consumers connected
    REQUIRE(std::find(c1Nodes.begin(), c1Nodes.end(), 1) != c1Nodes.end());
    REQUIRE(std::find(c1Nodes.begin(), c1Nodes.end(), 2) != c1Nodes.end());
    //check that c2 has all consumers connected
    REQUIRE(std::find(c2Nodes.begin(), c2Nodes.end(), 1) != c2Nodes.end());
    REQUIRE(std::find(c2Nodes.begin(), c2Nodes.end(), 2) != c2Nodes.end());
}

TEST_CASE("Nodes does not get nodes of other type" , "Multi-file:2") {
    NetworkInterface *ni = setUpNetwork();

    std::vector<int> p1Nodes = ni->getConnectedNodes(1);
    std::vector<int> p2Nodes = ni->getConnectedNodes(2);

    //check that p1 is not connected to p2
    bool exists = std::find(p1Nodes.begin(), p1Nodes.end(), 2) != p1Nodes.end();
    REQUIRE(!exists);

    //check that p2 is not connected to p1
    exists = std::find(p2Nodes.begin(), p2Nodes.end(), 1) != p2Nodes.end();
    REQUIRE(!exists);

    //consumer
    std::vector<int> c1Nodes = ni->getConnectedNodes(3);
    std::vector<int> c2Nodes = ni->getConnectedNodes(4);

    //check that c1 is not connected to c2
    exists = std::find(c1Nodes.begin(), c1Nodes.end(), 4) != c1Nodes.end();
    REQUIRE(!exists);

    //check that c2 is not connected to c1
    exists = std::find(c2Nodes.begin(), c2Nodes.end(), 3) != c2Nodes.end();
    REQUIRE(!exists);
}
