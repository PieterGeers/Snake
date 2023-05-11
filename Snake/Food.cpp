#include "stdafx.h"
#include "Food.h"
#include <cmath>

Food::Food(const Window& window)
{
	m_pTexture = new Texture("Resources/apple.png");
	Reposition(window, nullptr);
}

void Food::Draw() const
{
	const float width = m_pTexture->GetWidth();
	const float height = m_pTexture->GetHeight();
	const Rectf srcRect = { 0,0,width,height };

	m_pTexture->Draw({ static_cast<float>(m_x) * width, static_cast<float>(m_y) * height }, srcRect);
}

void Food::Reposition(const Window& window, Node* head)
{
	const float width = m_pTexture->GetWidth();
	const float height = m_pTexture->GetHeight();
	const int scrWidth = static_cast<int>(lround(window.width / width));
	const int scrHeight = static_cast<int>(lround(window.height / height));

	int newX = rand() % scrWidth;
	int newY = rand() % scrHeight;

	while (IsFoodOverlappingSnake(head, newX, newY))
	{
		newX = rand() % scrWidth + 1;
		newY = rand() % scrHeight + 1;
	}

	m_x = newX;
	m_y = newY;
}

Point2f Food::GetPosition() const
{
	const float width = m_pTexture->GetWidth();
	const float height = m_pTexture->GetHeight();

	return { static_cast<float>(m_x) * width, static_cast<float>(m_y) * height };

}

Food::~Food()
{
	delete m_pTexture;
}

bool Food::IsFoodOverlappingSnake(Node* head, int x, int y)
{
	Node* temp = head;

	while (temp != nullptr)
	{
		if (temp->X == x && temp->Y == y)
		{
			return true;
		}

		temp = temp->m_pNext;
	}

	return false;
}
