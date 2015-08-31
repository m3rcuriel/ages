#ifndef AGES_GRAPHICSLOOP_H
#define AGES_GRAPHICSLOOP_H

struct terrain;

#include "SFML/Graphics.hpp"

using sf::Event;

sf::Image render_map(const terrain* map, sf::Image image);
void zoom_to_mouse(sf::RenderWindow& window, Event event);
void zoomToCenter(sf::RenderWindow &window, const float &amount);
void moveWindowByVector(sf::RenderWindow& window, const sf::Vector2i offset);
int close_window();
int graphics_loop(const terrain* map);

#endif // AGES_GRAPHICSLOOP_H
