#include "map.h"
#include "rivergen.h"
#include <iostream>

/* Algorithm for Rivers:
 * First, some peaks are chosen to be water sources
 * Those rivers go down to the lowest adjacent point
 * If a river gets stuck, and isn't in ocean/lake/other_river
 *    if a tile is within a very small range, bulldoze that tile to a lower height
 *    if nearby tiles are all within a small range taller, make that tile
 *    and adjacent tiles into lakes
 *        if any adj tiles are lower
 *            make them lakes as well if num_tiles >= 2
 *            else make them rivers
 */
struct end_point {
    coord c;
    bool is_active;
    end_point(coord co, bool b_is_active = true)
    {
        c.x = co.x;
        c.y = co.y;
        is_active = b_is_active;
    }
};

inline bool active_river_exists(std::vector<end_point> rivers)
{
    for (auto const& river : rivers) {
        if (river.is_active)
            return true;
    }
    return false;
}

void RiverGen::river_alg() { 
    auto num_rivers = 0;
    std::vector<end_point> end_points;
    end_points.reserve(sources.size());
    for (auto const& source : sources) {
        end_points.push_back(source);
    }

    while (active_river_exists(end_points)) {
        for (auto &river : end_points) {
            if (river.is_active) {
                float lowest_height = std::numeric_limits<float>::infinity();
                coord lowest_coord;
                for (auto adj : adj_coords(river.c.x, river.c.y, x_dim, y_dim, true)) {
                    if (map->h_map[adj.y][adj.x] < lowest_height and not(map->features->is_river[adj.y][adj.x])) {
                        lowest_height = map->h_map[adj.y][adj.x];
                        lowest_coord = adj;
                    }
                }
                if (lowest_height <= map->h_map[river.c.y][river.c.x]) {
                    if (map->features->is_river[lowest_coord.y][lowest_coord.x] or
                        map->features->is_lake[lowest_coord.y][lowest_coord.x] or
                        map->features->is_ocean[lowest_coord.y][lowest_coord.x]) {
                        river.is_active = false;
                    }
                    else {
                        river.c = lowest_coord;
                        map->features->is_river[river.c.y][river.c.x] = true;
                        num_rivers++;
                    }
                }
                else if (lowest_height < map->h_map[river.c.y][river.c.x] + MAX_BULLDOZE_DIFF)
                    map->h_map[lowest_coord.y][lowest_coord.x] = map->h_map[river.c.y][river.c.x];
                else {
                    //No larger lakes yet, there's too much world flood risk
                    river.is_active = false;
                    map->features->is_river[river.c.y][river.c.x] = false;
                    map->features->is_lake[river.c.y][river.c.x] = true;
                }
            }
        }
    }
    std::cout << num_rivers << " rivers created\n";
}
