#include "map.h"


iss::iss()
    {
        for (auto arr : is_ocean) {
            arr.fill(false);
        }
        for (auto arr : is_lake) {
            arr.fill(false);
        }
        for (auto arr : is_river) {
            arr.fill(false);
        }
        for (auto arr : is_peak) {
            arr.fill(false);
        }
        for (auto arr : is_source) {
            arr.fill(false);
        }
    }
