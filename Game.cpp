#include "Game.h"


Game::Game()
{
    DebugLogger::Print(LogType::Info, "Game/GameEngine : Initializing");

    instance = ClientInstance::GetSingle();
    instance->GameEngine = this;

    // please make sure this is ALWAYS the first one
    OnUpdate.Hook([this](sf::RenderWindow* window) { this->OnUpdateEvent(window); });

    Services.push_back(new DefaultWinBindsService(this));
    Services.push_back(new Camera2DService(this));
    Services.push_back(new MapLoaderService(this));
    Services.push_back(new MarkerService(this));

    // this should always be the final hook in the list for onupdate cuz its what i use to render
    OnUpdate.Hook([this](sf::RenderWindow* window) { window->display(); });

    DebugLogger::Print(LogType::Info, "Game/GameEngine : Initialized");
}

void Game::OnUpdateEvent(sf::RenderWindow* window)
{
    window->clear(sf::Color::Black); // clear last frame
}