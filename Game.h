#ifndef GAME_H
#define GAME_H

#include "Engine/GameEngine.h"
#include "Engine/Service/Services/DefaultWinBindsService.h"
#include "Engine/Service/Services/Camera2DService.h"
#include "SDK/ClientInstance.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Game : public GameEngine {
public:
    ClientInstance* instance;
    sf::Texture texture;
    sf::Sprite sprite;
    std::vector<sf::CircleShape> markers;

public:
    Game();

    void OnUpdateEvent(sf::RenderWindow* window);
    void OnMouseClick(sf::Event::MouseButtonEvent& event);
};

#endif // GAME_H