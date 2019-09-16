#pragma once
#include "Texture.h"
class Snake
{
public:
	Snake(const Point2f& pos);
	Snake(const Snake& other) = delete;
	Snake(Snake&& other) = delete;
	Snake& operator=(const Snake& rhs) = delete;
	Snake& operator=(Snake&& rhs) = delete;
	void Draw();
	void ProcessKeyDownEvent(const SDL_KeyboardEvent & e);
	void Update(float elapsedSec);
	Point2f GetPosition();
	void SetPosition(const Point2f& pos);
	void ResetDirection();
	~Snake();

private:
	Texture* m_pSnake;
	Point2f m_Pos;
	enum class Direction
	{
		none,
		left,
		right,
		up,
		down
	};
	Direction m_DirectionSnake;
};

