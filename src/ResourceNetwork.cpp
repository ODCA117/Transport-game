#include "ResourceNetwork.h"
#include <iostream>

/* -------------------------------------------------*/
/* -------------ResourceNetwork---------------------*/
/* -------------------------------------------------*/
ResourceNetwork::ResourceNetwork() {
    nodes = new std::vector<ResourceNode*>();
}
ResourceNetwork::ResourceNetwork(std::vector<ResourceNode*> net){
    nodes->insert(nodes->end(),net.begin(), net.end());
}
void* ResourceNetwork::getNode(int id ){
    for (unsigned int i = 0; i < nodes->size(); ++i)
    {
        if(nodes->at(i)->getId() == id){
            return nodes->at(i);
        }
    }

    return NULL;
}

void ResourceNetwork::addNode(ResourceNode *node){
    nodes->push_back(node);

}

int ResourceNetwork::removeNode(int id) {
    for (unsigned int i = 0; i < nodes->size(); ++i)
    {
        if(nodes->at(i)->getId() == id){
            nodes->erase(nodes->begin() + i);
            return 0;
        }
    }
    return 1;
}

int ResourceNetwork::size(){
    return nodes->size();
}

std::string ResourceNode::toString() { return "NULL";}

/* -------------------------------------------------*/
/* -------------ResourceNode------------------------*/
/* -------------------------------------------------*/

ResourceNode::ResourceNode(int id) : id(id){
    rnet = new ResourceNetwork();
}

bool ResourceNode::operator==(const ResourceNode rhs) {
    bool res = id == rhs.id;
    return res;
}

void ResourceNode::addNode(ResourceNode *node) {
    rnet->addNode(node);
}

ResourceNode ResourceNode::removeNode(int id) {
    rnet->removeNode(id);
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

void ProducerNode::updateDemanded() {
    demanded = 0;
    printf("size of rnet: %d \n", rnet->size());
    for (int i = 0; i < rnet->size(); ++i)
    {
        printf("before demanded\n" );
        printf("%x\n", rnet->getNode(id));
        //demanded += ((ConsumerNode*)rnet.getNode(i))->getDemand();
    }
}

/* ---------------Private Functions------------------------*/

void ProducerNode::updateCurrentProd() {
    std::cout << std::to_string(maxProd) << "\n";
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

    for(int i = 0; i < rnet->size(); i++) {
        int added = (currentProd/rnet->size())*deltaTime;
        ((ConsumerNode*)rnet->getNode(i))->addSupply(added);
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
    for (int i = 0; i < rnet->size(); ++i)
    {
        str += std::to_string(((ResourceNode*)rnet->getNode(id))->getId()) + " ";
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



int ConsumerNode::getDemand(){
    std::cout << "in getDemand" << std::to_string(maxCons) << "\n";
    std::cout << "in getDemand: " << std::to_string(supply) << "\n";

    if(supply < maxCons) {
        std::cout << "supply < maxCons" << "\n";
        return maxCons;
    }
    else if(supply > (5*maxCons)) {
        std::cout << "supply > 5maxCons" << "\n";
        return 0;
    }
    else {
        std::cout << "else" << "\n";
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
