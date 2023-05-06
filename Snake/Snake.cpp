#include "stdafx.h"
#include "Snake.h"


Snake::Snake()
	: m_DirectionSnake{Direction::right}
{
	m_pTexture = new Texture{ "Resources/snake.png" };
	m_pHead = new Node(0, 0);
	m_pTail = m_pHead;
}

void Snake::Draw() const
{
	const Node* temp = m_pHead;
	const float width = m_pTexture->GetWidth();
	const float height = m_pTexture->GetHeight();
	const Rectf srcRect = { 0, 0, width, height };

	while (temp != nullptr)
	{
		m_pTexture->Draw({ static_cast<float>(temp->X) * width, static_cast<float>(temp->Y) * height }, srcRect);
		temp = temp->m_pNext;
	}
}

void Snake::ProcessKeyDownEvent(const SDL_KeyboardEvent & e)
{
	switch (e.keysym.sym)
	{
	case SDLK_UP:
		if (m_DirectionSnake != Direction::down)
		{
			m_DirectionSnake = Direction::up;
		}
		break;
	case SDLK_DOWN:
		if (m_DirectionSnake != Direction::up)
		{
			m_DirectionSnake = Direction::down;
		}
		break;
	case SDLK_LEFT:
		if (m_DirectionSnake != Direction::right)
		{
			m_DirectionSnake = Direction::left;
		}
		break;
	case SDLK_RIGHT:
		if (m_DirectionSnake != Direction::left)
		{
			m_DirectionSnake = Direction::right;
		}
		break;
	default: ;
	}
}

void Snake::Update(float) const
{
	Node* temp = m_pTail;

	while (temp->m_pPrevious != nullptr)
	{
		if (!temp->IsEqual(temp->m_pPrevious))
		{
			temp->X = temp->m_pPrevious->X;
			temp->Y = temp->m_pPrevious->Y;
		}
		temp = temp->m_pPrevious;
	}

	switch (m_DirectionSnake)
	{
	case Snake::Direction::none:
		break;
	case Snake::Direction::left:
		m_pHead->X -= 1;
		break;
	case Snake::Direction::right:
		m_pHead->X += 1;
		break;
	case Snake::Direction::up:
		m_pHead->Y += 1;
		break;
	case Snake::Direction::down:
		m_pHead->Y -= 1;
		break;
	}
}

Point2f Snake::GetPosition() const
{
	const float width = m_pTexture->GetWidth();
	const float height = m_pTexture->GetHeight();

	return { static_cast<float>(m_pHead->X) * width, static_cast<float>(m_pHead->Y) * height };
}

int Snake::GetScore() const
{
	return m_score;
}

bool Snake::HasEatenItself() const
{
	const Node* temp = m_pHead->m_pNext;
	while (temp)
	{
		if (temp->IsEqual(m_pHead))
		{
			return true;
		}
		temp = temp->m_pNext;
	}

	return false;
}

void Snake::ResetDirection()
{
	m_DirectionSnake = Direction::right;
}

void Snake::IncreaseSize()
{
	m_score++;
	m_pTail->m_pNext = new Node(m_pTail->X, m_pTail->Y);
	m_pTail->m_pNext->m_pPrevious = m_pTail;
	m_pTail = m_pTail->m_pNext;
}

Snake::~Snake()
{
	delete m_pTexture;

	Node* temp = m_pHead;
	while (m_pHead)
	{
		m_pHead = m_pHead->m_pNext;
		temp->m_pPrevious = nullptr;
		delete temp;
		temp = m_pHead;
	}
}
