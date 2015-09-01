#ifndef AGES_GRAPHICSLOOP_H
#define AGES_GRAPHICSLOOP_H

struct terrain;

#include "SFML/Graphics.hpp"

using sf::Event;

sf::Image render_map(const terrain* map, sf::Image image);
//void zoomToMouse(sf::RenderWindow& window, Event event);
void zoomToCenter(sf::RenderWindow &window, const float &amount);
void moveWindowByVector(sf::RenderWindow& window, const sf::Vector2f offset);
//int close_window();
int graphicsLoop(const terrain* map);

#endif // AGES_GRAPHICSLOOP_H
