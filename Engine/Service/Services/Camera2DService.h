#ifndef CAMERA_2D_SERVICE_H
#define CAMERA_2D_SERVICE_H

#include "../ServiceBase.h"

#include <SFML/Graphics.hpp>

class Camera2DService : public ServiceBase {
public: // variables
    float zoom;
    float offsetX, offsetY;
    bool isDragging;
    sf::Vector2i lastMousePosition;

public: // utils
    void updateView() {
        Engine->Window->setView(sf::View(sf::FloatRect(offsetX, offsetY, Engine->Window->getSize().x / zoom, Engine->Window->getSize().y / zoom)));
    }

public: // .ctors
    Camera2DService(GameEngine* engine);

public: // events
    void OnMouseWheelScrolledEvent(sf::Event::MouseWheelScrollEvent& event);
    void OnMouseButtonPressedEvent(sf::Event::MouseButtonEvent& event);
    void OnMouseButtonReleasedEvent(sf::Event::MouseButtonEvent& event);
    void OnMouseMovedEvent(sf::Event::MouseMoveEvent& event);
};

#endif // CAMERA_2D_SERVICE_H