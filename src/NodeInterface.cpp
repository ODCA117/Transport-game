#include <iostream>
#include "NodeInterface.h"

NodeInterface::NodeInterface(){

}

void NodeInterface::createProducer(int id) {
    ProducerNode *node = new ProducerNode(id);
    net.addNode(node);
}

void NodeInterface::createConsumer(int id) {
    ConsumerNode *node = new ConsumerNode(id);
    net.addNode(node);
}

void NodeInterface::addNode(int node1, int node2) {
    ResourceNode *n1 = (ResourceNode*)net.getNode(node1);
    ResourceNode *n2 = (ResourceNode*)net.getNode(node2);

    n2->addNode(n1);
    n1->addNode(n2);
}

void NodeInterface::removeNode(int node1, int node2) {
    ResourceNode *n1 = (ResourceNode*)net.getNode(node1);
    ResourceNode *n2 = (ResourceNode*)net.getNode(node2);

    n2->removeNode(node1);
    n1->removeNode(node2);
}

void NodeInterface::update() {
    std::cout << "Update" << "\n";
    for (int i = net.size()/2; i < net.size(); ++i)
    {
        ((ConsumerNode*)net.getNode(i))->update(0.3);
    }

    for (int i = 0; i < net.size()/2; ++i)
    {
        //Producer Loop
        ((ProducerNode*)net.getNode(i))->update(0.3);

    }
}

void NodeInterface::print() {

}
