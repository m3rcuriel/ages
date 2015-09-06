#include "map.h"
#include "rivergen.h"
#include <limits>

void RiverGen::find_peaks()
{
    for (auto y = 0u; y < y_dim; y+=PEAK_RAD) {
        for (auto x = 0u; x < x_dim; x+=PEAK_RAD) {
            std::vector<coord> region = circle(x, y, x_dim, y_dim, PEAK_RAD);
            region.push_back(coord(x, y));
            float tallest_height = -std::numeric_limits<float>::infinity();
            coord tallest_coord;
            for (auto tile : region) {
                float height = map->h_map[tile.y][tile.x];
                if (height > tallest_height) {
                    tallest_height = height;
                    tallest_coord = tile;
                }
            }

            if (tallest_height > PEAK_MIN) {
                peaks.push_back(tallest_coord);
                map->features->is_peak[tallest_coord.y][tallest_coord.x] = true;
            }
        }
    }
}

void RiverGen::find_water_sources()
{
    for (auto peak : peaks) {
        if (randf(0, 1) < WATER_SOURCE_CHANCE) {
            map->features->is_source[peak.y][peak.x] = true;
            sources.push_back(peak);
        }
    }
}
