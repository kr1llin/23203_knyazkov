#pragma once

#include "Object.hpp"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include <string>
#include <unordered_map>

const std::string PLAYER_TEXTURE_FILE =
    "/home/krillin/code/nsu/23203_knyazkov/lab3/Assets/player.png";
const std::string ALIEN_TEXTURE_FILE =
    "/home/krillin/code/nsu/23203_knyazkov/lab3/Assets/alien2.png";
const std::string BULLET_TEXTURE_FILE =
    "/home/krillin/code/nsu/23203_knyazkov/lab3/Assets/bullet.png";

class TexturePaths {
public:
  TexturePaths() {
    texturePaths[objID::BULLET_ID] = BULLET_TEXTURE_FILE;
    texturePaths[objID::PLAYER_ID] = PLAYER_TEXTURE_FILE;
    texturePaths[objID::ALIEN_ID] = ALIEN_TEXTURE_FILE;
    texturePaths[objID::INVADERS_ID] = ALIEN_TEXTURE_FILE;
  }

  std::unordered_map<objID, std::string> getTexturePaths() const {
    return texturePaths;
  }

private:
  std::unordered_map<objID, std::string> texturePaths;
};

class SpriteManager {
public:
  SpriteManager() { initSprites(); }

  void initSprites();
  void loadSprite(const objID &id, const std::string &filePath);

  sf::Sprite *getSprite(const objID &objectName) const;

private:
  TexturePaths texturePaths;
  std::unordered_map<objID, std::unique_ptr<sf::Texture>> textures;
  std::unordered_map<objID, std::unique_ptr<sf::Sprite>> sprites;
};

class RenderModule {
public:
  void init();

  const sf::RenderWindow &getWindow() const { return m_window; }

  // just initial sprite straight from the file
  sf::Sprite *getSprite(objID id) const { return spriteManager.getSprite(id); }
  void render(const std::vector<std::shared_ptr<Object>> &objects);
  void closeWindow() { m_window.close(); }
  bool pollWindowEvent(sf::Event &event) { return m_window.pollEvent(event); }

private:
  sf::RenderWindow m_window;
  SpriteManager spriteManager;

  // based on object returns sprite and scales considering object's size
  const sf::Sprite *
  getSpriteFromObject(const std::shared_ptr<Object> &object) const;
};
