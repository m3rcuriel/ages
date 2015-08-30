#include "SFML/Graphics.hpp"

using sf::Event;

sf::Image render_map(terrain map, sf::Image image);
void zoom_to_mouse( sf::RenderWindow& window, Event event);
int graphics_loop(terrain map);
