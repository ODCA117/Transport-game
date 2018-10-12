#include "ResourceNetwork.h"

/* -------------------------------------------------*/
/* -------------ResourceNetwork------------------------*/
/* -------------------------------------------------*/
ResourceNetwork::ResourceNetwork(std::vector<ResourceNode*> nodes) : nodes(nodes) {}
void* ResourceNetwork::getNode(int id ){
    for (unsigned int i = 0; i < nodes.size(); ++i)
    {
        if(nodes[i]->getId() == id){
            return nodes[i];
        }
    }

    return NULL;
}
std::string ResourceNode::toString() { return "NULL";}

int ResourceNetwork::size(){
    return nodes.size();
}

/* -------------------------------------------------*/
/* -------------ResourceNode------------------------*/
/* -------------------------------------------------*/

ResourceNode::ResourceNode(int id) : id(id){}

bool ResourceNode::operator==(const ResourceNode rhs) {
    bool res = id == rhs.id;
    return res;
}

void ResourceNode::addNode(ResourceNode* node) {
    nodes.push_back(node);
}

ResourceNode ResourceNode::removeNode(ResourceNode* node) {
    for(unsigned int i = 0; i < nodes.size(); i++) {
        if(*node == *nodes[i]) {
            nodes.erase(nodes.begin() +i);
        }
    }
    return *node;
}

int ResourceNode::getId(){
    return id;
}

/* |-----------------------------------------------|*/
/* |************ProducerNode***********************|*/
/* |-----------------------------------------------|*/

ProducerNode::ProducerNode(int id) : ResourceNode(id) {
    maxProd = 100;
    currentProd = 0;
    demanded = 0;
}
void ProducerNode::updateDemanded(int val) {
    demanded = val;
}
int ProducerNode::getCurrentProd(){
    return currentProd;
}

std::string ProducerNode::toString() {
    std::string str =
        "Prod:" +
        std::to_string(id) + "\t" +
        std::to_string(maxProd) + "\t" +
        std::to_string(currentProd) + "\t" +
        std::to_string(demanded) + "\t";

    if(nodes.size() == 0) {
        str += "Empty";
    }
    for (int i = 0; i < nodes.size(); ++i)
    {
        str += std::to_string((nodes[i]->getId())) + " ";
    }

    return str;
}


/* -------------------------------------------------*/
/* -------------ConsumerNode------------------------*/
/* -------------------------------------------------*/
ConsumerNode::ConsumerNode(int id) : ResourceNode(id) {
    maxCons = 100;
    currentCons = 0;
    supply = 0;
}
void ConsumerNode::updateMaxCons(int val) {
    maxCons = val;
}

std::string ConsumerNode::toString() {
    std::string str =
        "Cons:" +
        std::to_string(id) + "\t" +
        std::to_string(maxCons) + "\t" +
        std::to_string(currentCons) + "\t" +
        std::to_string(supply) + "\t";
    /* if we need the suppliers for the node we print this
    if(nodes.size() == 0) {
        str += "Empty";
    }
    for (int i = 0; i < nodes.size(); ++i)
    {
        str += std::to_string((nodes[i]->getId())) + " ";
    }
    */

    return str;
}
