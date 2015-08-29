#include "SFML/Graphics.hpp"
#include "gen/simplex.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int MAP_WIDTH = 640;
const int MAP_HEIGHT = 480;

//Zooms window to the mouse position.
void zoomToMouse( sf::RenderWindow& window, sf::Event event){
    int x = event.mouseWheel.x;
    int y = event.mouseWheel.y;
    int delta = event.mouseWheel.delta;
    float zoomFactor = 1.2;
    
    sf::View view = window.getView();
    sf::Vector2i crsrPixel(x,y);
    sf::Vector2f crsrCoords = window.mapPixelToCoords(crsrPixel);
    
    float zoom;
    if(delta < 0)
        zoom = delta*zoomFactor*-1;
    else
        zoom = 1/(delta*zoomFactor);
    
    view.setCenter(crsrCoords);
    view.zoom(zoom);
    
    sf::Vector2f crsrCoordsNew = window.mapPixelToCoords(crsrPixel, view);//Finds new mouse coordinates
    view.move( crsrCoords.x-crsrCoordsNew.x, crsrCoords.y-crsrCoordsNew.y); //Moves view based on new mouse coords.
    window.setView(view);
}

//Transforms the map into a sfml image for rendering.
sf::Image renderMap(float** map, sf::Image image){
    for(int y = 0; y < MAP_HEIGHT; y++) {
        for(int x = 0; x < MAP_WIDTH; x++) {
            float value = map[x][y] * 127 + 128;
            float red = value;
            float blue = value;
            float green = value;
            if(value < 130) {
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
float** genMap(){
    srand(time(0));
    SimplexSettings settings = {16, .6, 0.0025, MAP_WIDTH, MAP_HEIGHT};
    SimplexGenerator generator(settings);
    float** map = new float*[MAP_WIDTH];
    for(int i = 0; i < MAP_WIDTH; i++) {
        map[i] = new float[MAP_HEIGHT];
    }
    generator.generate(map);
    return map;
}

int main() {
    float** map = genMap();

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "GenWindow");    
    sf::Image image;
    image.create(MAP_WIDTH, MAP_HEIGHT);
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);
    sf::Event event;
    bool drag = false;
    bool oldDrag = false;
    sf::Vector2f prevCrsrCoords(-1, -1);
    
    while(window.isOpen()) {
    
        image = renderMap(map, image);
        texture.loadFromImage(image);
        
        
        while(window.pollEvent(event)) {
            
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseWheelMoved) 
                zoomToMouse(window, event);
            
            if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Button::Middle){
                if(!drag){
                    sf::Vector2i crsrPixel(sf::Mouse::getPosition(window));
                    prevCrsrCoords = window.mapPixelToCoords(crsrPixel);
                }
                drag = true;
            }
            
            
            if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Middle){
                drag = false;
            }
            
            if(event.type == sf::Event::MouseMoved && drag == true){
                sf::Vector2i crsrPixel( sf::Mouse::getPosition(window));
                sf::Vector2f crsrCoords = window.mapPixelToCoords(crsrPixel);
                float x = (prevCrsrCoords.x - crsrCoords.x);
                float y = (prevCrsrCoords.y - crsrCoords.y);
                sf::View view = window.getView();
                sf::Vector2f shift( x, y);
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

 


