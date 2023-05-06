#pragma once
#include "Texture.h"


class Node
{
public:
	Node(int x, int y)
	{
		X = x;
		Y = y;
	}

	int X = 0;
	int Y = 0;
	Node* m_pNext = nullptr;
	Node* m_pPrevious = nullptr;

	bool IsEqual(const Node* node) const
	{
		return node->X == X && node->Y == Y;
	}
};

class Snake
{
public:
	Snake();

	Snake(const Snake& other) = delete;
	Snake(Snake&& other) = delete;
	Snake& operator=(const Snake& rhs) = delete;
	Snake& operator=(Snake&& rhs) = delete;

	void Draw() const;
	void Update(float elapsedSec) const;

	void ProcessKeyDownEvent(const SDL_KeyboardEvent & e);

	Point2f GetPosition() const;
	int GetScore() const;
	bool HasEatenItself() const;

	void ResetDirection();
	void IncreaseSize();

	~Snake();

private:
	Texture* m_pTexture;
	Node* m_pHead;
	Node* m_pTail; //Tail is already destroyed when releasing the linked list

	int m_score = 0;

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

