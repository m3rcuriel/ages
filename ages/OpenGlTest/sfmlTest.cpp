#include <SFML/Graphics.hpp>


int main() {
	
	
	sf::RenderWindow window(sf::VideoMode(640, 480), "GenericWindow");
	sf::RectangleShape rectangle(sf::Vector2f(640, 480));
	//rectangle.setFillColor(sf::Color::Green);
	
	
	sf::Image image;
	image.create(640, 480);
	
	for (int x = 0; x < 640; x++) {
		for (int y = 0; y < 480; y++) {
			sf::Color red(255,255,0);
			image.setPixel(x, y, red);
		}
	}

	
	sf::Texture texture;
	texture.loadFromImage( image);
	sf::Sprite sprite(texture);
	
	while (window.isOpen()) {

		sf::Event event;
		
		while (window.pollEvent(event)) {
			
			if (event.type == sf::Event::Closed)
			window.close();
			if (event.type == sf::Event::MouseWheelEvent){
				fprintf(stderr, event.delta());
				
			}
		}
		
		
		window.clear(sf::Color::Black);
		window.draw(sprite);
		window.display();
		
	}

	return 0;
}
