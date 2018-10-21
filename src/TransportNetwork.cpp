#include "TransportNetwork.h"

Station::Station(int id, ResourceNetwork rnet) : id(id), rnet(rnet) {}


void Station::listNodes() {
    for(int i = 0; i < rnet.size(); i++) {
        printf("resource node id: , \n");
    }
}
