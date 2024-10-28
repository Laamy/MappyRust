#ifndef MAP_LOADER_SERVICE_H
#define MAP_LOADER_SERVICE_H

#include "../ServiceBase.h"

#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <vector>

class MapLoaderService : public ServiceBase {
private:
	sf::Texture texture;
	sf::Sprite sprite;

public:
	MapLoaderService(GameEngine* engine) {
		this->Init(engine);
		DebugLogger::Print(LogType::Info, "Initialized : MapLoaderService");

		if (!loadMapTexture("map.png", texture, sprite))
			return;

		engine->OnUpdate.Hook([this](sf::RenderWindow* window) {
			window->draw(sprite);
		});
	}

	bool loadMapTexture(const std::string& filePath, sf::Texture& texture, sf::Sprite& sprite) {
		std::ifstream file(filePath, std::ios::binary);
		
		if (!file)
			return DebugLogger::Print(LogType::Info, "Initialized : MapLoaderService", false);

		std::vector<sf::Uint8> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
		
		if (!texture.loadFromMemory(buffer.data(), buffer.size()))
			return DebugLogger::Print(LogType::Error, "Failed to load map texture from memory.", false);

		sprite.setTexture(texture);
		sprite.setScale(1.0f, 1.0f);

		return true;
	}
};

#endif // MAP_LOADER_SERVICE_H