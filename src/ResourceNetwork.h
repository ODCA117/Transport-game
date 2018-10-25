#ifndef RESOURCE_NETWORK
#define RESOURCE_NETWORK

#include <vector>
#include <string>
#include <iomanip>

class ResourceNode;

 class ResourceNetwork {
 private:
     std::vector<ResourceNode*> *nodes;
     int findIndex(int id);
 public:
     ResourceNetwork();
     ResourceNetwork(std::vector<ResourceNode*> *nodes);
     void* getNode(int id); // void* that needs to be casted when used.
     int getId(int i); 
     void addNode(ResourceNode* node);
     int removeNode(int id);
     int size();
 };

class ResourceNode {
protected:
    ResourceNetwork *rnet;
    int id;
public:
    ResourceNode(int id);
    void addNode(ResourceNode* node);
    ResourceNode removeNode(int id);
    bool operator==(const ResourceNode rhs);
    int getId();
    std::string toString();

};

class ProducerNode : public ResourceNode {
private:
    int maxProd, currentProd, demanded;
    void updateCurrentProd();
    void updateDemanded();

public:
    ProducerNode(int id);
    void update(double deltaTime);
    int getCurrentProd();
    std::string toString();
};

class ConsumerNode : public ResourceNode {
private:
    int maxCons, currentCons, supply;
    void updateCurrentCons();

public:
    ConsumerNode(int id);
    void update(double deltaTime);
    void updateMaxCons(int val);
    int getDemand();
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
