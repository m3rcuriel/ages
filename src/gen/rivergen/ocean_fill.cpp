#include "map.h"
#include "rivergen.h"
#include <iostream>
// TODO create output implementation

void RiverGen::edge_fill_oceans()
{
    for (auto x = 0; x < x_dim; x++) {
        if (map->h_map[0][x] <= WATER_LEVEL) {
            map->features->is_ocean[0][x] = true;
            oceans.push_back(coord(x, 0));
        }
        if (map->h_map[y_dim - 1][x] <= WATER_LEVEL) {
            map->features->is_ocean[y_dim - 1][x] = true;
            oceans.push_back(coord(x, y_dim - 1));
        }
    }

    for (auto y = 0; y < y_dim; y++) {
        if (map->h_map[y][0] <= WATER_LEVEL) {
            map->features->is_ocean[y][0] = true;
            oceans.push_back(coord(x_dim - 1, y));
        }
        if (map->h_map[y][x_dim - 1] <= WATER_LEVEL) {
            map->features->is_ocean[y][x_dim - 1] = true;
            oceans.push_back(coord(x_dim - 1, y));
        }
    }
    auto init_oceans = oceans.size();
    auto i = 0;
    while (i < oceans.size()) {
        coord ocean_coord = oceans[i];
        std::vector<coord> adjs = adj_coords(ocean_coord.x, ocean_coord.y, x_dim, y_dim);

        for (auto adj : adjs) {
            if (map->h_map[adj.y][adj.x] <= WATER_LEVEL and not(map->features->is_ocean[adj.y][adj.x])) {
                map->features->is_ocean[adj.y][adj.x] = true;
                oceans.push_back(adj);
            }
        }
        i++;
    }
    std::cout << oceans.size() - init_oceans << " oceans created\n";
}
