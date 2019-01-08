#include "../catch.hpp"
#include "../../src/network/ResourceNetwork.h"
#include "../../src/network/TransportNetwork.h"
#include "../../src/network/NetworkInterface.h"
#include <algorithm>
#include <iostream>

int contains(std::vector<int> vec, int node) {
    if (std::find(vec.begin(), vec.end(), node) != vec.end()) {
        return 1;
    }
    return 0;
}

/* set up a network of nodes
    producer Nodes id 1 2
    consumer Nodes id 3 4
    Stations  5 6

    Station 5 connected nodes : 1 3
    Station 6 connected nodes : 2 4

    stations connected 5 6 */
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
    ni->addNodeToStation(1,5);
    ni->addNodeToStation(3,5);
    ni->addNodeToStation(2,6);
    ni->addNodeToStation(4,6);

    //connect stations
    ni->connectStations(5, 6);

    return ni;
}

TEST_CASE("Test addNodeToStation" , "Multi-file:2") {
    NetworkInterface *ni = new NetworkInterface();

    //station with id 0
    ni->createStation(0);


    //add first producer
    ni->createProducer(1);
    ni->addNodeToStation(1, 0);
    REQUIRE(contains(ni->getNodesAtStation(0), 1));


    //add Second producer
    ni->createProducer(2);
    ni->addNodeToStation(2, 0);
    REQUIRE(contains(ni->getNodesAtStation(0), 2));

    //add first consumer
    ni->createConsumer(3);
    ni->addNodeToStation(3, 0);
    REQUIRE(contains(ni->getNodesAtStation(0), 3));

    //add second consumer
    ni->createConsumer(4);
    ni->addNodeToStation(4, 0);
    REQUIRE(contains(ni->getNodesAtStation(0), 4));

    //add first producer again should not change size
    ni->addNodeToStation(1, 0);
    REQUIRE(ni->getNodesAtStation(0).size() == 4);

    //add first consumer again should not change size
    ni->addNodeToStation(3, 0);
    REQUIRE(ni->getNodesAtStation(0).size() == 4);

}

//Get the original set up and removes all nodes from the stations connected
TEST_CASE("Test removeNodeStation" , "Multi-file:2") {
    NetworkInterface *ni = setUpNetwork();

    //station 5
    ni->removeNodeForStation(1,5);
    REQUIRE(contains(ni->getNodesAtStation(5), 1) == 0);

    ni->removeNodeForStation(3,5);
    REQUIRE(contains(ni->getNodesAtStation(5), 3) == 0);

    //station 6
    ni->removeNodeForStation(4,6);
    REQUIRE(contains(ni->getNodesAtStation(6), 4) == 0);

    ni->removeNodeForStation(2,6);
    REQUIRE(contains(ni->getNodesAtStation(6), 2) == 0);

}

TEST_CASE("Test connectStations" , "Multi-file:2") {
    //test station connections
    NetworkInterface *ni = new NetworkInterface();

    ni->createStation(0);
    ni->createStation(1);

    ni->connectStations(0, 1);

    REQUIRE(contains(ni->getConnectedStations(0), 1));
    REQUIRE(contains(ni->getConnectedStations(1), 0));
}

TEST_CASE("Test disconnectStations" , "Multi-file:2") {
    REQUIRE(false);
}

TEST_CASE("Test connect Nodes within same station", "Multi-file:2") {
    REQUIRE(false);
}

TEST_CASE("Test disconnect Nodes within same station when station is deleted", "Multi-file:2") {
    REQUIRE(false);
}
TEST_CASE("Test connected Nodes after station connection" , "Multi-file:2") {
    REQUIRE(false);
    // NetworkInterface *ni = setUpNetwork();
    //
    // std::vector<int> p1Nodes = ni->getConnectedNodes(1);
    // std::vector<int> p2Nodes = ni->getConnectedNodes(2);
    //
    // bool test = std::find(p1Nodes.begin(), p1Nodes.end(), 3) != p1Nodes.end();
    // std::cout << p1Nodes.size()  << "\n";
    // std::vector<int>::iterator i;
    // for(i = p1Nodes.begin(); i != p1Nodes.end(); i++) {
    //     std::cout << *i << "\n";
    // }
    // std::cout << test << "\n";
    // //std::cout << *std::find(p1Nodes.begin(), p1Nodes.end(), 3) << "\n";
    // //std::cout << *p1Nodes.end() << "\n";
    //
    // //check that p1 has all consumers connected
    // REQUIRE(std::find(p1Nodes.begin(), p1Nodes.end(), 3) != p1Nodes.end());
    // REQUIRE(std::find(p1Nodes.begin(), p1Nodes.end(), 4) != p1Nodes.end());
    //
    // //check that p2 has all consumers connected
    // REQUIRE(std::find(p2Nodes.begin(), p2Nodes.end(), 3) != p2Nodes.end());
    // REQUIRE(std::find(p2Nodes.begin(), p2Nodes.end(), 4) != p2Nodes.end());
    //
    // //consumer
    // std::vector<int> c1Nodes = ni->getConnectedNodes(3);
    // std::vector<int> c2Nodes = ni->getConnectedNodes(4);
    //
    // //check that c1 has all consumers connected
    // REQUIRE(std::find(c1Nodes.begin(), c1Nodes.end(), 1) != c1Nodes.end());
    // REQUIRE(std::find(c1Nodes.begin(), c1Nodes.end(), 2) != c1Nodes.end());
    // //check that c2 has all consumers connected
    // REQUIRE(std::find(c2Nodes.begin(), c2Nodes.end(), 1) != c2Nodes.end());
    // REQUIRE(std::find(c2Nodes.begin(), c2Nodes.end(), 2) != c2Nodes.end());
}

TEST_CASE("Nodes does not get nodes of other type" , "Multi-file:2") {
    REQUIRE(false);
    // NetworkInterface *ni = setUpNetwork();
    //
    // std::vector<int> p1Nodes = ni->getConnectedNodes(1);
    // std::vector<int> p2Nodes = ni->getConnectedNodes(2);
    //
    // //check that p1 is not connected to p2
    // bool exists = std::find(p1Nodes.begin(), p1Nodes.end(), 2) != p1Nodes.end();
    // REQUIRE(!exists);
    //
    // //check that p2 is not connected to p1
    // exists = std::find(p2Nodes.begin(), p2Nodes.end(), 1) != p2Nodes.end();
    // REQUIRE(!exists);
    //
    // //consumer
    // std::vector<int> c1Nodes = ni->getConnectedNodes(3);
    // std::vector<int> c2Nodes = ni->getConnectedNodes(4);
    //
    // //check that c1 is not connected to c2
    // exists = std::find(c1Nodes.begin(), c1Nodes.end(), 4) != c1Nodes.end();
    // REQUIRE(!exists);
    //
    // //check that c2 is not connected to c1
    // exists = std::find(c2Nodes.begin(), c2Nodes.end(), 3) != c2Nodes.end();
    // REQUIRE(!exists);
}
