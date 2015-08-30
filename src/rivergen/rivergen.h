#include <vector>
#include <set>
#include <random>
#include <cmath>
#include "map.h"
const float WATER_LEVEL = 0;
const int MIN_OCEANS = 20;
const float PEAK_MIN = 0.3;
const int PEAK_RAD = 3;
const float WATER_SOURCE_CHANCE = 0.7;
const float MAX_LAKE_DEPTH = 0.1;
const float MAX_LAKE_HEIGHT = 0.5;
//^This stops a lake on a mountain from flooding the world
const float MAX_BULLDOZE_DIFF = 0.05;
//^This is how much taller and adj tile to a river can be before it is bulldozed


struct coord {
    int x;
    int y;
    coord(int a = 0, int b = 0);
};

class RiverGen {
public:
    // All is public for debugging, for now
    std::vector<coord> oceans;
    std::vector<coord> peaks;
    std::vector<coord> sources;
    void edge_fill_oceans();
    void find_peaks();
    void find_water_sources();
    void river_alg();
    int x_dim;
    int y_dim;
    terrain *map; //Not using a smart ptr because this isn't dangerous
    RiverGen(terrain *the_map, int x, int y);
    ~RiverGen();
};

template <class T>
void remove_dup(std::vector<T>& vect);
std::vector<coord> adj_coords(int x, int y, int x_dim, int y_dim, bool diag=false);
std::vector<coord> circle(int x, int y, int x_dim, int y_dim, int rad);
inline float randf();
