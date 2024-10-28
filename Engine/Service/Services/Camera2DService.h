#ifndef CAMERA_2D_SERVICE_H
#define CAMERA_2D_SERVICE_H

#include "Engine/Service/ServiceBase.h"
#include <SFML/Graphics.hpp>

class Camera2DService : public ServiceBase {
public:
    float zoom;
    float offsetX, offsetY;
    bool isDragging;
    sf::Vector2i lastMousePosition;

    Camera2DService(GameEngine* engine) {
        this->Init(engine);
        zoom = 1.0f;
        offsetX = 0.0f;
        offsetY = 0.0f;
        isDragging = false;

        Engine->OnMouseWheelScrolled.Hook([this](sf::Event::MouseWheelScrollEvent event) { this->OnMouseWheelScrolledEvent(event); });
        Engine->OnMouseButtonPressed.Hook([this](sf::Event::MouseButtonEvent event) { this->OnMouseButtonPressedEvent(event); });
        Engine->OnMouseButtonReleased.Hook([this](sf::Event::MouseButtonEvent event) { this->OnMouseButtonReleasedEvent(event); });
        Engine->OnMouseMoved.Hook([this](sf::Event::MouseMoveEvent event) { this->OnMouseMovedEvent(event); });
        Engine->OnResized.Hook([this](sf::Event::SizeEvent event) { updateView(); });
    }

    void OnMouseWheelScrolledEvent(sf::Event::MouseWheelScrollEvent& event) {
        float zoomFactor = 0.1f;
        float previousZoom = zoom;

        if (event.delta > 0)
            zoom += zoomFactor;
        else
            zoom = std::max(zoom - zoomFactor, 0.1f);

        sf::Vector2i mousePosition = sf::Mouse::getPosition(*Engine->Window);
        float mouseWorldX = (mousePosition.x - offsetX) / previousZoom;
        float mouseWorldY = (mousePosition.y - offsetY) / previousZoom;

        offsetX += (mouseWorldX - (mousePosition.x - offsetX) / zoom) * zoom;
        offsetY += (mouseWorldY - (mousePosition.y - offsetY) / zoom) * zoom;

        updateView();
    }

    void OnMouseButtonPressedEvent(sf::Event::MouseButtonEvent& event) {
        if (event.button == sf::Mouse::Right) {
            isDragging = true;
            lastMousePosition = sf::Mouse::getPosition(*Engine->Window);
        }
    }

    void OnMouseButtonReleasedEvent(sf::Event::MouseButtonEvent& event) {
        if (event.button == sf::Mouse::Right) {
            isDragging = false;
        }
    }

    void OnMouseMovedEvent(sf::Event::MouseMoveEvent& event) {
        if (isDragging) {
            sf::Vector2i currentMousePosition = sf::Mouse::getPosition(*Engine->Window);
            offsetX -= (currentMousePosition.x - lastMousePosition.x) / zoom;
            offsetY -= (currentMousePosition.y - lastMousePosition.y) / zoom;
            lastMousePosition = currentMousePosition;
            updateView();
        }
    }

    void updateView() {
        Engine->Window->setView(sf::View(sf::FloatRect(offsetX, offsetY, Engine->Window->getSize().x / zoom, Engine->Window->getSize().y / zoom)));
    }
};

#endif // CAMERA_2D_SERVICE_H