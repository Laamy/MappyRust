#ifndef GAME_H
#define GAME_H

#include "Engine/GameEngine.h"

#include "Engine/Service/Services/DefaultWinBindsService.h"
#include "Engine/Service/Services/Camera2DService.h"
#include "Engine/Service/Services/MarkerService.h"
#include "Engine/Service/Services/MapLoaderService.h"

#include "SDK/ClientInstance.h"

#include <SFML/Graphics.hpp>

#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

class Game : public GameEngine {
public:
    ClientInstance* instance;
    sf::Texture texture;
    sf::Sprite sprite;

public:
    Game();

    void OnUpdateEvent(sf::RenderWindow* window);
};

#endif // GAME_H