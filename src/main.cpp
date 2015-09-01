#include <cstdlib>

#include "main.h"

#include "gen/rivergen/map.h"
#include "gen/rivergen/rivergen.h"
#include "gen/simplex.h"
#include "graphicsLoop.h"

const int MAP_HEIGHT = 1280;
const int MAP_WIDTH = 1280;

const int REGEN_MAP = 2;

int main() {
    srand(time(0));

    terrain* map = new terrain;
    genMap(map);
    
    RiverGen gen = RiverGen(map, MAP_WIDTH, MAP_HEIGHT);
    gen.edge_fill_oceans();
    
    int out = 1;
    
    do{
        if (out == REGEN_MAP){
            genMap( map);
    
            gen = RiverGen(map, MAP_WIDTH, MAP_HEIGHT);
            gen.edge_fill_oceans();
        }
        
        out = graphicsLoop(map);
        
    } while (out == 2);
    
    return 0;
}

//Generates the map
void genMap(terrain *map){
    map->features = new iss[1]();
    SimplexSettings settings = {8, .6, 0.001, MAP_WIDTH, MAP_HEIGHT};
    SimplexGenerator generator(settings);
    float** hmap = new float*[MAP_HEIGHT];
    for (int i = 0; i < MAP_HEIGHT; i++) {
        hmap[i] = new float[MAP_WIDTH];
    }
    generator.generate(hmap);
    for (auto y = 0u; y < MAP_HEIGHT; y++) {
        for (auto x = 0u; x < MAP_WIDTH; x++) {
            map->h_map[y][x] = hmap[y][x];
        }
    }
    for (int i = 0; i < MAP_HEIGHT; i++) {
        delete[] hmap[i];
        hmap[i] = NULL;
    }

    delete[] hmap;
}
