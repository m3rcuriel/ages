#include "SFML/Graphics.hpp"
#include "rivergen/rivergen.h"
#include "graphicsLoop.h"
#include <iostream>
#include <cmath>

using sf::Event;
using sf::Vector2f;
using sf::Vector2i;

const int WIN_HEIGHT = 480;
const int WIN_WIDTH = 640;


//Zooms window to the mouse position.
void zoom_to_mouse( sf::RenderWindow& window, Event event){
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
sf::Image render_map(terrain map, sf::Image image){
    for(auto y = 0; y < map.h_map.size(); y++) {       
        for(auto x = 0; x < map.h_map[0].size(); x++) {
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

void graphics_loop(terrain map){
    
    sf::RenderWindow window(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT), "ages");    
    sf::Image image;
    image.create(map.h_map[0].size(), map.h_map.size());
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);
    Event event;
    bool drag = false;
    Vector2f prevCrsrCoords(-1, -1);
    
    image = render_map(map, image);
    texture.loadFromImage(image);
    
    while(window.isOpen()) {
            
        while(window.pollEvent(event)) {
            
            if(event.type == Event::Closed)
                window.close();

            if(event.type == Event::MouseWheelMoved) 
                zoom_to_mouse(window, event);
            
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
}