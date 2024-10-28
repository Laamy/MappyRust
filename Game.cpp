#include "Game.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>

std::vector<sf::CircleShape> markers;

Game::Game()
{
    DebugLogger::Print(LogType::Info, "Game/GameEngine : Initializing");

    instance = ClientInstance::GetSingle();
    instance->GameEngine = this;

    OnUpdate.Hook([this](sf::RenderWindow* window) { this->OnUpdateEvent(window); });
    OnMouseButtonPressed.Hook([this](sf::Event::MouseButtonEvent event) { this->OnMouseClick(event); });

    Services.push_back(new DefaultWinBindsService(this));
    Services.push_back(new Camera2DService(this));

    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    std::string imagePath = "C:/MappyRust/map.png";

    std::ifstream file(imagePath, std::ios::binary);
    if (!file)
    {
        DebugLogger::Print(LogType::Error, "Failed to open file: " + imagePath);
        return;
    }

    std::vector<sf::Uint8> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    if (!texture.loadFromMemory(buffer.data(), buffer.size()))
    {
        DebugLogger::Print(LogType::Error, "Failed to load map texture from memory.");
        return;
    }

    sprite.setTexture(texture);
    sprite.setScale(1.0f, 1.0f);

    DebugLogger::Print(LogType::Info, "Game/GameEngine : Initialized");
}

void Game::OnUpdateEvent(sf::RenderWindow* window)
{
    window->clear(sf::Color::Black);
    window->draw(sprite);

    for (const auto& marker : markers)
    {
        window->draw(marker);
    }

    window->display();
}

void Game::OnMouseClick(sf::Event::MouseButtonEvent& event)
{
    if (event.button == sf::Mouse::Left)
    {
        sf::CircleShape marker(5);
        marker.setFillColor(sf::Color::Red);
        marker.setPosition(static_cast<float>(event.x), static_cast<float>(event.y));
        markers.push_back(marker);
    }
}