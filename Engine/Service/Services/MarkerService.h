#ifndef MARKER_SERVICE_H
#define MARKER_SERVICE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../ServiceBase.h"

class MarkerService : public ServiceBase {
private: // variables
    static std::vector<sf::CircleShape> markers;

public: // .ctors
    // .ctors
    MarkerService(GameEngine* engine)
    {
        this->Init(engine);

        engine->OnMouseButtonPressed.Hook([this](sf::Event::MouseButtonEvent event) { this->HandleMouseClick(event); });

        engine->OnUpdate.Hook([this](sf::RenderWindow* window) {
            for (const auto& marker : MarkerService::GetMarkers())
                window->draw(marker);
            });
    }

public: // utils
    static const std::vector<sf::CircleShape>& GetMarkers();

private: // events
    // events
    void HandleMouseClick(sf::Event::MouseButtonEvent& event)
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
};

#endif // MARKER_SERVICE_H