#include "SFML/Graphics.hpp"
#include "gen/simplex.h"
#include "rivergen/rivergen.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using sf::Event;
using sf::Vector2f;
using sf::Vector2i;

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int MAP_HEIGHT = 480;
const int MAP_WIDTH = 640;

//Zooms window to the mouse position.
void zoomToMouse( sf::RenderWindow& window, Event event){
    int x = event.mouseWheel.x;
    int y = event.mouseWheel.y;
    int delta = event.mouseWheel.delta;
    float zoomFactor = 1.2;
    
    sf::View view = window.getView();
    Vector2i crsrPixel(x,y);
    Vector2f crsrCoords = window.mapPixelToCoords(crsrPixel);
    
    float zoom;
    if(delta < 0)
        zoom = delta*zoomFactor*-1;
    else
        zoom = 1/(delta*zoomFactor);
    
    view.setCenter(crsrCoords);
    view.zoom(zoom);
    
    Vector2f crsrCoordsNew = window.mapPixelToCoords(crsrPixel, view);//Finds new mouse coordinates
    view.move( crsrCoords.x-crsrCoordsNew.x, crsrCoords.y-crsrCoordsNew.y); //Moves view based on new mouse coords.
    window.setView(view);
}

//Transforms the map into a sfml image for rendering.
sf::Image renderMap(terrain map, sf::Image image){
    for(int y = 0; y < MAP_HEIGHT; y++) {
        for(int x = 0; x < MAP_WIDTH; x++) {
            float value = map.h_map[y][x] * 127 + 128;
            float red = value;
            float blue = value;
            float green = value;
            if (map.features->is_ocean[y][x]) {
                red = 0;
                blue = value * 0.75;
                green = value * 0.55;
            } else {
                red = 0.50 * value;
                blue = blue*blue*blue*blue / (255 * 255 * 255);
                green = value;
            }
            
            sf::Color pixel(sf::Color(red, green, blue));
            image.setPixel(x , y, pixel);
        }
    }
    return image;
}


//Generates the map
terrain genMap(){
    terrain map;
    map.features = new iss[1]();
    srand(time(0));
    SimplexSettings settings = {16, .6, 0.0025, MAP_WIDTH, MAP_HEIGHT};
    SimplexGenerator generator(settings);
    float** hmap = new float*[MAP_WIDTH];
    for(int i = 0; i < MAP_WIDTH; i++) {
        hmap[i] = new float[MAP_HEIGHT];
    }
    generator.generate(hmap);
    for (auto y = 0; y < MAP_HEIGHT; y++) {
        for (auto x = 0; x < MAP_WIDTH; x++) {
            map.h_map[y][x] = hmap[y][x];
        }
    }

    return map;
}

int main() {
    terrain map = genMap();
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "GenWindow");    
    sf::Image image;
    image.create(MAP_WIDTH, MAP_HEIGHT);
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);
    Event event;
    bool drag = false;
    Vector2f prevCrsrCoords(-1, -1);
   
    RiverGen gen = RiverGen(&map, MAP_WIDTH, MAP_HEIGHT);
    gen.edge_fill_oceans();
    /*for (auto row : map.h_map) {
        for (auto h : row) {
            if (h > 1 or h < -1)
                std::cout << "Lee did something wrong, height out of range" << std::endl;
        }
    }*/
    while(window.isOpen()) {
    
        image = renderMap(map, image);
        texture.loadFromImage(image);
        
        
        while(window.pollEvent(event)) {
            
            if(event.type == Event::Closed)
                window.close();

            if(event.type == Event::MouseWheelMoved) 
                zoomToMouse(window, event);
            
            if(event.type == Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Middle){
                if(!drag){
                    Vector2i crsrPixel(sf::Mouse::getPosition(window));
                    prevCrsrCoords = window.mapPixelToCoords(crsrPixel);
                }
                drag = true;
            }
            
            if(event.type == Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Middle){
                drag = false;
            }
            
            if(event.type == Event::MouseMoved && drag == true){
                Vector2i crsrPixel( sf::Mouse::getPosition(window));
                Vector2f crsrCoords = window.mapPixelToCoords(crsrPixel);
                float x = (prevCrsrCoords.x - crsrCoords.x);
                float y = (prevCrsrCoords.y - crsrCoords.y);
                sf::View view = window.getView();
                Vector2f shift( x, y);
                view.move(shift);
                window.setView(view);
                
            }            
        }

        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }

    return 0;
}

 


