#ifndef MARKER_SERVICE_H
#define MARKER_SERVICE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../ServiceBase.h"

class MarkerService : public ServiceBase {
private: // variables
    static std::vector<sf::CircleShape> markers;

public: // .ctors
    MarkerService(GameEngine* engine);

public: // utils
    static const std::vector<sf::CircleShape>& GetMarkers();

private: // events
    void HandleMouseClick(sf::Event::MouseButtonEvent& event);
};

#endif // MARKER_SERVICE_H