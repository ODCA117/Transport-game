#include <vector>
#include <string>
#include <iomanip>

class ResourceNode;

 class ResourceNetwork {
 private:
     std::vector<ResourceNode*> nodes;
 public:
     ResourceNetwork(std::vector<ResourceNode*> nodes);
     void* getNode(int id); // void* that needs to be casted when used.
     int size();
 };

class ResourceNode {
protected:
    std::vector<ResourceNode*> nodes;
    int id;
public:
    ResourceNode(int id);
    void addNode(ResourceNode* node);
    ResourceNode removeNode(ResourceNode* node);
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
