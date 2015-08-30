#include "rivergen.h"


void RiverGen::edge_fill_oceans()
{
    for (auto x = 0; x < x_dim; y++) {
        if (map->h_map[0][x] <= WATER_LEVEL) {
            map->features->is_ocean[0][x] = true;
            oceans.push_back(coord(x, 0);
        }
        if (map->h_map[y_dim - 1][x] <= WATER_LEVEL) {
            map->features->is_ocean[y_dim - 1][x] = true;
            oceans.push_back(coord(x, y_dim - 1));
        }
    }

    for (auto y = 0; y < y_dim; y++) {
        if (map->h_map[y][0] <= WATER_LEVEL) {
            map->features->is_ocean[y][0] = true;
            oceans.push_back(coord(x, y_dim - 1));
            num_ocean_tiles++;
        }
        if (map->h_map[y][x_dim - 1] <= WATER_LEVEL) {
            map->features->is_ocean[y][x_dim - 1] = true;
            oceans.push_back(coord(x_dim - 1, y));
        }
    }

    for (auto ocean_coord : oceans) {
        std::vector adjs = adj_coords(ocean_coord.x, ocean_coord.y, x_dim, y_dim);

        for (auto adj : adjs) {
            if (map->h_map[adj.y][adj.x] <=  map->h_map[ocean_coord.y][ocean_coord.x]) {
                map->featuresis_ocean[adj.y][adj.x] = true;
                oceans.push_back(adj);
            }
        }
    }
}
