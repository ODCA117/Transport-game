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
    NetworkInterface *ni = new NetworkInterface();

    ni->createStation(0);
    ni->createStation(1);

    ni->connectStations(0, 1);
    REQUIRE(contains(ni->getConnectedStations(0), 1));
    REQUIRE(contains(ni->getConnectedStations(1), 0));

    ni->disconnectStations(0, 1);
    REQUIRE(contains(ni->getConnectedStations(0), 1) == 0);
    REQUIRE(contains(ni->getConnectedStations(1), 0) == 0);

}

TEST_CASE("Test connect Nodes within same station", "Multi-file:2") {
    NetworkInterface *ni = new NetworkInterface();

    ni->createProducer(1);
    ni->createProducer(3);
    ni->createConsumer(2);
    ni->createConsumer(4);

    ni->createStation(0);

    ni->addNodeToStation(1, 0);
    ni->addNodeToStation(2, 0);
    ni->addNodeToStation(3, 0);
    ni->addNodeToStation(4, 0);


    std::vector<int> nodesAt1 = ni->getNodesAtNode(1);
    REQUIRE(nodesAt1.size() == 3);
    REQUIRE(contains(nodesAt1, 2));
    REQUIRE(contains(nodesAt1, 3));
    REQUIRE(contains(nodesAt1, 4));

    std::vector<int> nodesAt2 = ni->getNodesAtNode(2);
    REQUIRE(nodesAt2.size() == 3);
    REQUIRE(contains(nodesAt2, 1) == 1);

    std::vector<int> nodesAt3 = ni->getNodesAtNode(3);
    REQUIRE(nodesAt3.size() == 3);
    REQUIRE(contains(nodesAt3, 1) == 1);

    std::vector<int> nodesAt4 = ni->getNodesAtNode(4);
    REQUIRE(nodesAt3.size() == 3);
    REQUIRE(contains(nodesAt4, 1) == 1);
}

TEST_CASE("Test disconnect Nodes within same station when station is deleted", "Multi-file:2") {
    NetworkInterface *ni = new NetworkInterface();
    ni->createStation(0);

    ni->createProducer(1);
    ni->createProducer(3);
    ni->createConsumer(2);
    ni->createConsumer(4);

    ni->addNodeToStation(1, 0);
    ni->addNodeToStation(2, 0);
    ni->addNodeToStation(3, 0);
    ni->addNodeToStation(4, 0);

    ni->removeNodeForStation(1, 0);

    std::vector<int> nodesAt1 = ni->getNodesAtNode(1);
    REQUIRE(nodesAt1.size() == 0);

    std::vector<int> nodesAt2 = ni->getNodesAtNode(2);
    REQUIRE(nodesAt2.size() == 2);
    REQUIRE(contains(nodesAt2, 1) == 0);

    std::vector<int> nodesAt3 = ni->getNodesAtNode(3);
    REQUIRE(nodesAt3.size() == 2);
    REQUIRE(contains(nodesAt3, 1) == 0);

    std::vector<int> nodesAt4 = ni->getNodesAtNode(4);
    REQUIRE(nodesAt3.size() == 2);
    REQUIRE(contains(nodesAt4, 1) == 0);

}
TEST_CASE("Test connected Nodes after station connection" , "Multi-file:2") {

    NetworkInterface *ni = setUpNetwork();

    std::vector<int> nodesAt1 = ni->getNodesAtNode(1);
    REQUIRE(nodesAt1.size() == 3);
    REQUIRE(contains(nodesAt1,2) == 1);
    REQUIRE(contains(nodesAt1,3) == 1);
    REQUIRE(contains(nodesAt1,4) == 1);

    std::vector<int> nodesAt2 = ni->getNodesAtNode(2);
    REQUIRE(nodesAt2.size() == 3);
    REQUIRE(contains(nodesAt2, 1) == 1);

    std::vector<int> nodesAt3 = ni->getNodesAtNode(3);
    REQUIRE(nodesAt3.size() == 3);
    REQUIRE(contains(nodesAt3, 1) == 1);

    std::vector<int> nodesAt4 = ni->getNodesAtNode(4);
    REQUIRE(nodesAt3.size() == 3);
    REQUIRE(contains(nodesAt4, 1) == 1);

}

TEST_CASE("Nodes does not get nodes of other type" , "Multi-file:2") {
    NetworkInterface *ni = setUpNetwork();

    ni->disconnectStations(5, 6);

    std::vector<int> nodesAt1 = ni->getNodesAtNode(1);
    REQUIRE(nodesAt1.size() == 1);
    REQUIRE(contains(nodesAt1, 3) == 1);

    std::vector<int> nodesAt2 = ni->getNodesAtNode(2);
    REQUIRE(nodesAt2.size() == 1);
    REQUIRE(contains(nodesAt2, 4) == 1);

    std::vector<int> nodesAt3 = ni->getNodesAtNode(3);
    REQUIRE(nodesAt3.size() == 1);
    REQUIRE(contains(nodesAt3, 1) == 1);

    std::vector<int> nodesAt4 = ni->getNodesAtNode(4);
    REQUIRE(nodesAt4.size() == 1);
    REQUIRE(contains(nodesAt4, 2) == 1);

}
