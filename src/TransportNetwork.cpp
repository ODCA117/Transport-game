#include "TransportNetwork.h"

Station::Station(int id, std::vector<ResourceNode*> nodes) : id(id) {
    std::vector<ResourceNode*> connectedNodes(nodes.begin(), nodes.end());

}
