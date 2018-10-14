#include "ResourceNetwork.h"
#include <iostream>

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

/* ---------------Private Functions------------------------*/

void ProducerNode::updateCurrentProd() {
    updateDemanded();
    if(demanded >= maxProd) {
        currentProd = maxProd;
    }

    else if (demanded == 0) {
        currentProd = 0;
    }

    else {
        int prodRatio = (100*demanded)/maxProd;
        currentProd = (prodRatio * maxProd)/100;
    }
}

void ProducerNode::updateDemanded() {
    demanded = 0;
    for (int i = 0; i < nodes.size(); ++i)
    {
        demanded += ((ConsumerNode*)nodes[i])->getDemand();
    }
}

/* ---------------Public Functions------------------------*/

void ProducerNode::update(double deltaTime) {
    updateCurrentProd();

    for(int i = 0; i < nodes.size(); i++) {
        int added = (currentProd/nodes.size())*deltaTime;
        ((ConsumerNode*)nodes[i])->addSupply(added);
    }

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

/* ---------------Private Functions------------------------*/

void ConsumerNode::updateCurrentCons() {
    if(supply >= maxCons) {
        currentCons = maxCons;
    }

    else if (supply == 0) {
        currentCons = 0;
    }

    else {
        int supRatio = (100*supply)/maxCons;
        currentCons = (supRatio * maxCons)/100;
    }
}

/* ---------------Public Functions------------------------*/

void ConsumerNode::update(double deltaTime) {
    updateCurrentCons();
    int consumed = currentCons*deltaTime;
    supply -= consumed;

}

void ConsumerNode::updateMaxCons(int val) {
    maxCons = val;
}


/*
    Return demand equal to max production as long as the supply is less than maxCons
    Return 0 if the supply exides 5 max cons;
    return maxCons / supply if supply is grater than maxCons
 */
int ConsumerNode::getDemand(){

    if(supply < maxCons) {
        return maxCons;
    }
    else if(supply > (5*maxCons)) {
        return 0;
    }
    else {
        return (maxCons/(double)supply) * 100;
    }
}

void ConsumerNode::addSupply(int amount) {
    supply += amount;
}

std::string ConsumerNode::toString() {
    std::string str =
        "Cons:" +
        std::to_string(id) + "\t" +
        std::to_string(maxCons) + "\t" +
        std::to_string(currentCons) + "\t" +
        std::to_string(supply) + "\t";

    return str;
}
