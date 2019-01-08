#include "ResourceNetwork.h"
#include <iostream>

/* -------------------------------------------------*/
/* -------------ResourceNetwork---------------------*/
/* -------------------------------------------------*/

ResourceNetwork::ResourceNetwork() {
    nodes = new std::vector<ResourceNode*>();
    nodes->reserve(20);
}
ResourceNetwork::ResourceNetwork(std::vector<ResourceNode*> *net){
    nodes = net;
}

/* -------------private---------------------*/
int ResourceNetwork::findIndex(int id) {
    for (unsigned int i = 0; i < nodes->size(); ++i)
    {
        if(nodes->at(i)->getId() == id){
            return i;
        }
    }
    return -1;
}

/* -------------public---------------------*/

//bad return when failing
void* ResourceNetwork::getNode(int id ){
    int i = findIndex(id);
    if(i >= 0) {
        return nodes->at(i);
    }

    return NULL;
}

int ResourceNetwork::getId(int i) {
    return nodes->at(i)->getId();
}

void ResourceNetwork::addNode(ResourceNode *node){
    int i = findIndex(node->getId());

    if(i < 0) {
        nodes->push_back(node);

    }
}

int ResourceNetwork::removeNode(int id) {
    int i = findIndex(id);
    if(i >= 0) {
        nodes->erase(nodes->begin() + i);
        return 0;
    }
    return 1;
}

std::vector<int> ResourceNetwork::getNodes() {
    std::vector<int> ids;

    for(unsigned int i = 0; i < nodes->size(); i++) {
        ids.push_back(getId(i));
    }

    return ids;
}

int ResourceNetwork::size(){
    return nodes->size();
}

std::string ResourceNetwork::toString() {
    std::string str;

    for(unsigned int i = 0; i < nodes->size(); i++) {
        str += "node" + std::to_string(nodes->at(i)->getId());
        //std::cout << "resource node id:" << nodes->at(i)->getId() << "\n";
    }
    return str;
}

//std::string ResourceNode::toString() { return "NULL";}

/* -------------------------------------------------*/
/* -------------ResourceNode------------------------*/
/* -------------------------------------------------*/

ResourceNode::ResourceNode(int id, int type) : id(id), type(type){
    rnet = new ResourceNetwork();
}

bool ResourceNode::operator==(const ResourceNode rhs) {
    bool res = id == rhs.id;
    return res;
}

void ResourceNode::addNode(ResourceNode *node) {
    rnet->addNode(node);
}

void ResourceNode::removeNode(int id) {
    rnet->removeNode(id);
}

int ResourceNode::getId(){
    return id;
}

/* |-----------------------------------------------|*/
/* |************ProducerNode***********************|*/
/* |-----------------------------------------------|*/

ProducerNode::ProducerNode(int id) : ResourceNode(id, 1) {
    maxProd = 100;
    currentProd = 0;
    demanded = 0;
}

void ProducerNode::updateDemanded() {
    demanded = 0;

    for(int i = 0; i < rnet->size(); i++) {
        int id = rnet->getId(i);
        demanded += ((ConsumerNode*)rnet->getNode(id))->getDemand();
    }
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

/* ---------------Public Functions------------------------*/

void ProducerNode::update(double deltaTime) {
    updateCurrentProd();

    int id;
    for(int i = 0; i < rnet->size(); i++) {
        id = rnet->getId(i);
        int added = (currentProd/rnet->size())*deltaTime;
        ((ConsumerNode*)rnet->getNode(id))->addSupply(added);
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

    if(rnet->size() == 0) {
        str += "Empty";
    }
    int id;
    for (int i = 0; i < rnet->size(); ++i)
    {
        id = rnet->getId(i);
        str += std::to_string(((ResourceNode*)rnet->getNode(id))->getId()) + " ";
    }

    return str;
}


/* -------------------------------------------------*/
/* -------------ConsumerNode------------------------*/
/* -------------------------------------------------*/
ConsumerNode::ConsumerNode(int id) : ResourceNode(id, 2) {
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

int ConsumerNode::getDemand(){

    if(supply < maxCons) {
        return maxCons / rnet->size();
    }
    else if(supply > (5*maxCons)) {
        return 0;
    }
    else {
        return ((maxCons/(double)supply) * 100)/rnet->size();
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





/* this can be implemended in a daimond way when I learn about that*/
/* -------------------------------------------------*/
/* -------------RefineryNode------------------------*/
/* -------------------------------------------------*/
//
// RefineryNode::RefineryNode(int id) : ResourceNode(id)  {
//     maxProd = 100;
//     currentProd = 0;
//     demanded = 0;
//     maxCons = 100;
//     currentCons = 0;
//     supply = 0;
// }
//
// /* -------------private------------------------*/
// void RefineryNode::updateCurrentProd(){
//     updateDemanded();
//     if(demanded >= maxProd) {
//         currentProd = maxProd;
//     }
//
//     else if (demanded == 0) {
//         currentProd = 0;
//     }
//
//     else {
//         int prodRatio = (100*demanded)/maxProd;
//         currentProd = (prodRatio * maxProd)/100;
//     }
//
// }
// void RefineryNode::updateCurrentCons(){
//     if(supply >= maxCons) {
//         currentCons = maxCons;
//     }
//
//     else if (supply == 0) {
//         currentCons = 0;
//     }
//
//     else {
//         int supRatio = (100*supply)/maxCons;
//         currentCons = (supRatio * maxCons)/100;
//     }
// }
// void RefineryNode::updateDemanded(){
//     demanded = 0;
//     for (int i = 0; i < nodes.size(); ++i)
//     {
//         demanded += ((ConsumerNode*)nodes[i])->getDemand();
//     }
// }
//
// /* -------------public------------------------*/
// void RefineryNode::update(double deltaTime) {
//     updateCurrentCons();
//     updateCurrentProd();
// }
