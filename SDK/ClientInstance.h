#ifndef CLIENTINSTANCE_H
#define CLIENTINSTANCE_H

#include <entt/entt.hpp>

class ClientInstance {
public:
	class GameEngine* GameEngine;

public:
	// services cuz i dont care anymore

public:
	static ClientInstance* GetSingle();
};

#endif // CLIENTINSTANCE_H