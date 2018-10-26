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

void NodeInterface::update(double deltaTime) {

    std::cout << "Update" << "\n";
    for (int i = net.size()/2; i < net.size(); ++i)
    {
        ((ConsumerNode*)net.getNode(i))->update(deltaTime);
    }

    for (int i = 0; i < net.size()/2; ++i)
    {
        ((ProducerNode*)net.getNode(i))->update(deltaTime);
    }
}

void NodeInterface::print() {
    std::cout << net.size() << "\n";
    std::cout << "Name\t maxProd \t curProd \t demanded \t Demanders" << "\n";
    for (int i = 0; i < net.size()/2; ++i)
    {
        std::cout << ((ProducerNode*)net.getNode(i))->toString() << "\n";
    }

    std::cout << "\n -------------- \n" << "\n";
    std::cout << "Name \t maxCons \t curCons \t supply" << "\n";
    for (int i = net.size()/2; i < net.size(); ++i)
    {
        std::cout << ((ConsumerNode*)net.getNode(i))->toString() << "\n";
    }
}
