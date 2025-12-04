#ifndef SNAKEGAME
#define SNAKEGAME

#include "Model.h"

class SnakeGame
{
public:
	SnakeGame(); //creates state for Snake

	void Start(); //Initializes objects such as the map, 1st apple and the snake
	void Update(); //every 0.5 seconds the snake will move forward in the direction of its head
private:

};

#endif // !SNAKEGAME

