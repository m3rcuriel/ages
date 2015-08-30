#include "rivergen.h"

RiverGen::find_peaks()
{
    for (auto y = 0; y < y_dim; y++) {
        for (auto x = 0; x < x_dim; x++) {
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

RiverGen::find_water_sources()
{
    for (auto peak : peaks) {
        if (randf() < WATER_SOURCE_CHANCE) {
            map->features->is_source[peak.y][peak.x] = true;
            sources.push_back(peak);
        }
    }
}
