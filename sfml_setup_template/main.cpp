#include "pch.h"

#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <time.h>

#include "Particle.h"
#include "fluid.h"
#include "SpatialGrid.h"

int main()
{
	//simulation parameters
	const float dt = 0.01;
	int n = 2000;
	float kernel_radius = 4;

	//mouse coordinates
	int mouse_x = 0;
	int mouse_y = 0;
	int mouse_x_0 = 0;
	int	mouse_y_0 = 0;

	//spawns a fluid with n with an assigned radius of effect
	Fluid Water(n, kernel_radius);

	//creates a renderwindow
	sf::RenderWindow window(sf::VideoMode(600, 600), "Project");
	window.setFramerateLimit(60);

	//creating rendering tools
	sf::Image image;
	sf::CircleShape particleShape;
	particleShape.setFillColor(sf::Color::Green);
	particleShape.setRadius(10);
	
	//these arrays get used to render the particles in main function
	std::vector<float> render_x(n);
	std::vector<float> render_y(n);
	std::vector<sf::Color> render_col(n);

	while (window.isOpen())
	{
		//close window if escaped
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
		}

		mouse_x_0 = mouse_x;
		mouse_y_0 = mouse_y;
		sf::Vector2i localPosition = sf::Mouse::getPosition(window);
		mouse_x = localPosition.x;
		mouse_y = localPosition.y;
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

		}
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {

		}
		Water.mousePush(mouse_x/3.0, mouse_y/3.0, 10*(mouse_x - mouse_x_0), 10*(mouse_y - mouse_y_0));
		Water.update(dt);
		//calculate particle density

		//calculate particle pressure force

		//now draw the particles
		Water.getCoordinates(render_x, render_y);
		Water.getCol(render_col);
		particleShape.setFillColor(sf::Color::Blue);
		particleShape.setRadius(3);
		for (int i = 0; i < n; i++) {
			particleShape.setFillColor(render_col[i]);
			particleShape.setPosition(sf::Vector2f(3*render_x[i], 3*render_y[i]));
			window.draw(particleShape);
		}
		window.display();
		window.clear();
	}
	return 0;
}