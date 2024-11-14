#include "Particle.h"
#include <SFML/Graphics.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode(800, 600), "Particle Filter");

  ParticleFilter p;

  sf::Clock clock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    p.update();

    window.clear();
    p.draw(window);
    window.display();

    sf::sleep(sf::milliseconds(1000));
  }

  return 0;
}
