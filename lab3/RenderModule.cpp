#include "RenderModule.hpp"

void RenderModule::render(const std::vector<std::shared_ptr<Object>> &objects) {
  m_window.clear(sf::Color::Black);
  for (const auto &obj : objects) {
      m_window.draw(*getSpriteFromObject(obj));
  }
  m_window.display();
}

void RenderModule::init() {
  sf::Vector2f resolution;
  resolution.x = sf::VideoMode::getDesktopMode().width;
  resolution.y = sf::VideoMode::getDesktopMode().height;
  m_window.create(sf::VideoMode(), "Space Invaders", sf::Style::Fullscreen);
}

const sf::Sprite *
RenderModule::getSpriteFromObject(const std::shared_ptr<Object> &object) const {
  if (object) {
    objID id = object->getID();
    // wrap around
    auto *sprite = getSprite(id);
    if (!sprite) {
      throw std::runtime_error("Sprite not found for object ID: " +
                               std::to_string(static_cast<int>(id)));
    }
    float scaleX = object->getSize().x / sprite->getLocalBounds().width;
    float scaleY = object->getSize().y / sprite->getLocalBounds().height;
    sprite->setScale(scaleX, scaleY);
    sprite->setPosition(object->getPosition());

    return sprite;
  }
  return nullptr;
}

sf::Sprite *SpriteManager::getSprite(const objID &objectName) const {
  auto it = sprites.find(objectName);
  if (it != sprites.end()) {
    return it->second.get();
  }
  return nullptr;
}

void SpriteManager::loadSprite(const objID &id, const std::string &filePath) {
  auto texture = std::make_unique<sf::Texture>();
  if (texture->loadFromFile(filePath)) {
    textures[id] = std::move(texture);
    sprites[id] = std::make_unique<sf::Sprite>(*textures[id]);
  } else {
    throw std::runtime_error("Failed to load texture from " + filePath);
  }
}

 void SpriteManager::initSprites() {
    for (const auto &it : texturePaths.getTexturePaths()) {
      loadSprite(it.first, it.second);
    }
  }
