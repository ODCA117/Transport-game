#include <vector>
#include <string>
#include <iomanip>
#include "ResourceNetwork.h"

class Station {
private:
    int id;
    std::vector<ResourceNetwork*> connectedNodes;
    std::vector<Station*> connectedStations;

public:
    Station ();
    Station (int id, std::vector<ResourceNode*> nodes);
    void addStation();
    void removeStations(int id);
    void addNodes();
    void removeNodes(int id);

};
