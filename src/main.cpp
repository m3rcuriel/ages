#include "gen/simplex.h"
#include "gen/rivergen/rivergen.h"
#include "graphicsLoop.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

const int MAP_HEIGHT = 480;
const int MAP_WIDTH = 640;

const int REGEN_MAP = 2;

//Generates the map
void genMap(terrain &map)
{
    map.features = new iss[1]();
    srand(time(0));
    SimplexSettings settings = {16, .6, 0.0025, MAP_WIDTH, MAP_HEIGHT};
    SimplexGenerator generator(settings);
    float** hmap = new float*[MAP_HEIGHT];
    for(int i = 0; i < MAP_HEIGHT; i++) {
        hmap[i] = new float[MAP_WIDTH];
    }
    generator.generate(hmap);
    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_WIDTH; x++) {
            map.h_map[y][x] = hmap[y][x];
        }
    }
    for (int i = 0; i < MAP_HEIGHT; i++) {
        delete[] hmap[i];
        hmap[i] = NULL;
    }

    delete[] hmap;
}

int main() 
{
    terrain map;
    genMap( map);
    
    RiverGen gen = RiverGen(&map, MAP_WIDTH, MAP_HEIGHT);
    gen.edge_fill_oceans();
    
    int out = 1;
    
    do{
        if(out == REGEN_MAP){
            genMap( map);
    
            gen = RiverGen(&map, MAP_WIDTH, MAP_HEIGHT);
            gen.edge_fill_oceans();
        }
        
        out = graphics_loop(map);
        
    }while(out == 2);
    
    return 0;
}
