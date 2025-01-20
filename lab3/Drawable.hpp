// #include <SFML/Graphics.hpp>

// class IDrawable {
// public:
//     virtual ~IDrawable() {}
//     virtual void draw(sf::RenderWindow& window) = 0; // Pure virtual function
// };

// class CustomObject : public IDrawable {
// public:
//     CustomObject() {
//         // Initialize your custom object (e.g., set up a sprite)
//     }

//     void draw(sf::RenderWindow& window) override {
//         // Draw your custom object, e.g., window.draw(sprite);
//     }
// };

// class DrawableRectangle : public IDrawable {
// public:
//     DrawableRectangle(float width, float height) {
//         rectangle.setSize(sf::Vector2f(width, height));
//         // Set other properties like position, color, etc.
//     }

//     void draw(sf::RenderWindow& window) override {
//         window.draw(rectangle);
//     }

// private:
//     sf::RectangleShape rectangle;
// };

// class DrawableText : public IDrawable {
// public:
//     DrawableText(const std::string& text, const sf::Font& font) {
//         textObject.setFont(font);
//         textObject.setString(text);
//         // Set other properties like position, color, etc.
//     }

//     void draw(sf::RenderWindow& window) override {
//         window.draw(textObject);
//     }

// private:
//     sf::Text textObject;
// };
