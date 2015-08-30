#include <array>
const int X_DIM = 480;
const int Y_DIM = 640;
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
