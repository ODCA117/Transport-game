#ifndef RESOURCE_NETWORK
#define RESOURCE_NETWORK

#include <vector>
#include <string>
#include <iomanip>

class ResourceNode;

 class ResourceNetwork {
 private:
     //contains all nodes in this network
     std::vector<ResourceNode*> *nodes;
     // will find the index of the node from the id of the node
     int findIndex(int id);
 public:
     ResourceNetwork();
     // create a new network with
     ResourceNetwork(std::vector<ResourceNode*> *nodes);
     // Returns the node from the id of it, needs to have a cast to which type it is
     void* getNode(int id);
     //returns the id of a node with index i
     int getId(int i);
     //adds node to the list
     void addNode(ResourceNode* node);
     //remove node with id id
     int removeNode(int id);
     //returns the size of list
     int size();
     //list all list
     void listNodes();
 };

class ResourceNode {
protected:
    //a local network connected with the node
    ResourceNetwork *rnet;
    int id;
public:
    //creates a node with id id
    ResourceNode(int id);
    //adds a node to the local network of nodes for this node
    void addNode(ResourceNode* node);
    //removes a node from the local network
    ResourceNode removeNode(int id);
    //opeator to fix how equal works on nodes
    bool operator==(const ResourceNode rhs);
    //returns id of this node
    int getId();
    std::string toString();
};

class ProducerNode : public ResourceNode {
private:
    int maxProd, currentProd, demanded;
    //update currentProd from demanded variable
    void updateCurrentProd();
    //update demanded from how much the consumers demand
    void updateDemanded();

public:
    //creates a new node
    ProducerNode(int id);
    //update the current demand and production for this node and produce this amount
    void update(double deltaTime);
    //returns current production from node;
    int getCurrentProd();
    std::string toString();
};

class ConsumerNode : public ResourceNode {
private:
    int maxCons, currentCons, supply;
    //update how much consumer consume during one tick, dependent on supply
    void updateCurrentCons();

public:
    //creates a new consumer node
    ConsumerNode(int id);
    //uppdate the curent consumtion and consume this amount
    void update(double deltaTime);
    //upgrade node to consume more
    void updateMaxCons(int val);
    //return the current demand
    int getDemand();
    //add supply from transportation
    void addSupply(int amount);
    std::string toString();
};

/*
class RefineryNode : public ResourceNode {
private:
    //producer attributes
    int maxProd, currentProd, demanded;
    //consumer attributes
    int maxCons, currentCons, supply;
    void updateCurrentProd();
    void updateCurrentCons();
    void updateDemanded();
public:
    RefineryNode(int id);
    void update(double deltaTime);
    int getCurrentProd();
    void updateMaxCons(int val);
    int getDemand();
    void addSupply(int amount);
    std::string toString();
};
*/

#endif
