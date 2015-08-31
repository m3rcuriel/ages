#ifndef GRAPHICSLOOP_H
#define GRAPHICSLOOP_H

#include "SFML/Graphics.hpp"
#include "gen/rivergen/map.h"

using sf::Event;

sf::Image render_map(const terrain* map, sf::Image image);
void zoom_to_mouse(sf::RenderWindow& window, Event event);
void zoomToCenter(sf::RenderWindow& window, const int& amount);
void moveWindowByVector(sf::RenderWindow& window, const sf::Vector2i offset);
int close_window();
int graphics_loop(const terrain* map);

#endif // GRAPHICSLOOP_H
