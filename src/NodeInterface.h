#ifndef NODE_INTERFACE
#define NODE_INTERFACE

#include "ResourceNetwork.h"

//class to make the usage simpler and more inuative
class NodeInterface {
private:
    ResourceNetwork net;
public:
    NodeInterface();
    void createProducer(int id);
    void createConsumer(int id);
    void addNode(int node1, int node2);
    void removeNode(int node1, int node2);
    //update the values in loop
    void update(double deltaTime);
    void print();
};
#endif
