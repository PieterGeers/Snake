#pragma once
#include "Texture.h"
#include "Snake.h"

class Food
{
public:
	Food(const Window& window);

	Food(const Food& other) = delete;
	Food(Food&& other) = delete;
	Food& operator=(const Food& rhs) = delete;
	Food& operator=(Food&& rhs) = delete;

	void Draw() const;
	void Reposition(const Window& window, Node* head);

	Point2f GetPosition() const;

	~Food();

private:
	Texture* m_pTexture;
	int m_x, m_y;

	bool IsFoodOverlappingSnake(Node* head, int x, int y);
};