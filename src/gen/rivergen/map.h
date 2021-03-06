#ifndef AGES_MAP_H
#define AGES_MAP_H

#include <array>
const int X_DIM = 1280;
const int Y_DIM = 1280;
//The existence of terrain/features is unnecessary
struct iss { 
    std::array<std::array<bool, X_DIM>, Y_DIM> is_ocean;
    std::array<std::array<bool, X_DIM>, Y_DIM> is_lake;
    std::array<std::array<bool, X_DIM>, Y_DIM> is_river;
    std::array<std::array<bool, X_DIM>, Y_DIM> is_peak;
    std::array<std::array<bool, X_DIM>, Y_DIM> is_source;

};

struct terrain {
    std::array<std::array<float, X_DIM>, Y_DIM> h_map;
    iss *features;
};
#endif // AGES_MAP_H
