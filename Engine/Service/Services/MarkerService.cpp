#include "MarkerService.h"

std::vector<sf::CircleShape> MarkerService::markers;

// .ctors
MarkerService::MarkerService(GameEngine* engine)
{
    this->Init(engine);

    engine->OnMouseButtonPressed.Hook([this](sf::Event::MouseButtonEvent event) { this->HandleMouseClick(event); });
}

// utils
const std::vector<sf::CircleShape>& MarkerService::GetMarkers() { return markers; }

// events
void MarkerService::HandleMouseClick(sf::Event::MouseButtonEvent& event)
{
    auto worldPosition = Engine->Window->mapPixelToCoords(sf::Vector2i(event.x, event.y));

    if (event.button == sf::Mouse::Left)
    {
        sf::CircleShape marker(5);
        marker.setFillColor(sf::Color::Red);
        marker.setPosition(worldPosition.x - marker.getRadius(), worldPosition.y - marker.getRadius());
        markers.push_back(marker);
    }
    else if (event.button == sf::Mouse::Right)
    {
        auto it = std::remove_if(markers.begin(), markers.end(), [&](const sf::CircleShape& marker) {
            return marker.getGlobalBounds().contains(worldPosition);
            });
        markers.erase(it, markers.end());
    }
}
