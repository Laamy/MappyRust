#include "MarkerService.h"

std::vector<sf::CircleShape> MarkerService::markers;

// utils
const std::vector<sf::CircleShape>& MarkerService::GetMarkers() { return markers; }

