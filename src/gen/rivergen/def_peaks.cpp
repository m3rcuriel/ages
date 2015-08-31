#include "map.h"
#include "rivergen.h"

void RiverGen::find_peaks()
{
    for (auto y = 0u; y < y_dim; y++) {
        for (auto x = 0u; x < x_dim; x++) {
            std::vector<coord> circle_coords = circle(x, y, x_dim, y_dim, PEAK_RAD);
            float tallest_height = -1;
            coord tallest_coord;
            for (auto tile : circle_coords) {
                if (float height = map->h_map[tile.y][tile.x] > tallest_height) {
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
