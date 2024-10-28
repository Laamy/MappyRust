#include "Game.h"

Game::Game()
{
    DebugLogger::Print(LogType::Info, "Game/GameEngine : Initializing");

    instance = ClientInstance::GetSingle();
    instance->GameEngine = this;

    OnUpdate.Hook([this](sf::RenderWindow* window) { this->OnUpdateEvent(window); });

    Services.push_back(new DefaultWinBindsService(this));
    Services.push_back(new Camera2DService(this));
    Services.push_back(new MarkerService(this));

    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    std::string imagePath = "map.png";
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

    for (const auto& marker : MarkerService::GetMarkers())
        window->draw(marker);

    window->display();
}