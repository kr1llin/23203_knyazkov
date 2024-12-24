#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Texture Loading Test");
const std::string PLAYER_TEXTURE_FILE = "./Assets/player.png";

    // Create a texture
    sf::Texture texture;
    if (!texture.loadFromFile(PLAYER_TEXTURE_FILE)) {
        std::cerr << "Error loading texture" << std::endl;
        return -1; // Exit if texture loading fails
    }

    // Create a sprite and set the texture
    sf::Sprite sprite;
    sprite.setTexture(texture);

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear();

        // Draw the sprite
        window.draw(sprite);

        // Display the contents of the window
        window.display();
    }

    return 0;
}
