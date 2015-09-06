#ifndef AGES_GEN_RIVERGEN_H
#define AGES_GEN_RIVERGEN_H

struct terrain;

#include <vector>
#include <random>

//All values found through experimentation
const float WATER_LEVEL = 0;
const int MIN_OCEANS = 20;
const float PEAK_MIN = .35;
const int PEAK_RAD = 8;
const float WATER_SOURCE_CHANCE = 0.1;
const float MAX_LAKE_DEPTH = 0.1;
const float MAX_LAKE_HEIGHT = 0.5;
//^This stops a lake on a mountain from flooding the world
const float MAX_BULLDOZE_DIFF = .1;
//^This is how much taller and adj tile to a river can be before it is bulldozed


struct coord {
    unsigned int x;
    unsigned int y;
    coord(unsigned int a = 0, unsigned int b = 0);
    friend bool operator==(const coord& a, const coord& b);
    friend bool operator<(const coord& a, const coord& b);
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
    unsigned int x_dim;
    unsigned int y_dim;
    terrain *map; //Not using a smart ptr because this isn't dangerous
    RiverGen(terrain *the_map, unsigned int x, unsigned int y);
    ~RiverGen();
};

template <class T>
void remove_dup(std::vector<T>& vect);
std::vector<coord> adj_coords(unsigned int x, unsigned int y, unsigned int x_dim, unsigned int y_dim, bool diag = false);
std::vector<coord> circle(unsigned int x, unsigned int y, unsigned int x_dim, unsigned int y_dim, int rad);
inline float randf(int low, int high) {
    return low + static_cast<float>(rand()) / static_cast<float>(RAND_MAX/(high - low));
}

#endif // GEN_RIVERGEN_H
