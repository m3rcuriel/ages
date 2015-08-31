#include "rivergen.h"
#include <set>

RiverGen::RiverGen(terrain *the_map, int x, int y)
{
    map = the_map;
    x_dim = x;
    y_dim = y;
    std::vector<coord> oceans;
    oceans.reserve(0.66 * x_dim * y_dim); // Guessed how many there'll be
    std::vector<coord> peaks;
    peaks.reserve(0.1 * x_dim * y_dim);
    std::vector<coord> sources;
    sources.reserve(0.1 * WATER_SOURCE_CHANCE * x_dim * y_dim);
}

RiverGen::~RiverGen()
{
}

coord::coord(int a, int b)
{
    x = a;
    y = b;
}

bool operator<(const coord &a, const coord &b)
{
    return (a.x < b.x and a.y < b.y);
}
bool operator==(const coord &a, const coord &b)
{
    return (a.x == b.x and a.y == b.y);
}

template <class T>
void remove_dup(std::vector<T>& vect)
{
    //According to SO, this is the fastest way for large vects
    std::set<T> uniques;
    for (auto elem : vect) {uniques.insert(elem);}
    vect.assign(uniques.begin(), uniques.end());
}

std::vector<coord> adj_coords(int x, int y, int x_dim, int y_dim, bool diag)
{
    std::vector<coord> adj;
    constexpr int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        /*constexpr int dirs[8][2] = {{-1, -1}, {0, -1}, {1, -1},
                                    {-1,  0},          {1,  0},
                                    {-1,  1}, {0,  1}, {1,  1}};*/

    for (auto dir : dirs) {
        if (dir[0] + x >= 0 and dir[0] + x < x_dim and
            dir[1] + y >= 0 and dir[1] + y < y_dim) {
            coord temp (dir[0] + x, dir[1] + y);
            adj.push_back(temp);
        }
    }

    return adj;
}


std::vector<coord> circle(int x, int y, int x_dim, int y_dim, int rad)
{
    //This is probably very memory inefficient
    //But so convenient for writing, will fix later
    std::vector<coord> circle;
    coord center; center.x = x; center.y = y;
    circle.push_back(center);

    for (auto i = 0; i < rad; i++) {
        for (auto elem : circle) {
            std::vector<coord> adjs = adj_coords(elem.x, elem.y, x_dim, y_dim);
            circle.reserve(circle.size() + adjs.size());
            circle.insert(circle.end(), adjs.begin(), adjs.end());
            remove_dup<coord>(circle);
        }
    }

    return circle;
}

inline float randf()
{
    std::random_device rd;
    std::mt19937 eng(rd());
    std::uniform_real_distribution<> dist(0, 1);
    return dist(eng);
}

inline float dist(coord a, coord b) {return abs(a.x - b.x) + abs(a.y - b.y);}
