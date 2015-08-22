#include "SFML/Graphics.hpp"
#include "gen/simplex.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int MAP_WIDTH = 640;
const int MAP_HEIGHT = 480;

int main() {
    srand(time(0));
    SimplexSettings settings = {16, .6, 0.0025, MAP_WIDTH, MAP_HEIGHT};
    SimplexGenerator generator(settings);
    float** map = new float*[MAP_WIDTH];
    for(int i = 0; i < MAP_WIDTH; i++) {
        map[i] = new float[MAP_HEIGHT];
    }
    generator.generate(map);

    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "GenWindow");

    sf::Image image;
    image.create(MAP_WIDTH, MAP_HEIGHT);

    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);
    sf::Color pixel;
    sf::Event event;
    
    while(window.isOpen()) {
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
                pixel = sf::Color(red, green, blue);
                image.setPixel(x , y, pixel);
            }
        }

        texture.loadFromImage(image);

        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseWheelMoved) {
                sprite.setOrigin(event.mouseWheel.x, event.mouseWheel.y);
                sprite.setPosition(event.mouseWheel.x, event.mouseWheel.y);

                int delta = event.mouseWheel.delta;

                if(delta < 0)
                    sprite.scale( -1 * (float) delta / 1.05, -1 * (float) delta / 1.05);
                else
                    sprite.scale ((float) delta * 1.05, (float) delta * 1.05);
            }
        }

        window.clear(sf::Color::Black);
        window.draw(sprite);
        window.display();
    }

    return 0;
}


