#include "stdafx.h"
#include "Snake.h"


Snake::Snake(const Point2f& pos)
	: m_Pos{ pos }
	, m_DirectionSnake{Direction::right}
{
	m_pSnake = new Texture{ "Resources/1.png" };
}

void Snake::Draw()
{
	m_pSnake->Draw({ m_Pos }, { 0, 0, m_pSnake->GetWidth(), m_pSnake->GetHeight() });
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
	}
}

void Snake::Update(float)
{
	switch (m_DirectionSnake)
	{
	case Snake::Direction::none:
		break;
	case Snake::Direction::left:
		m_Pos.x -= 16;
		break;
	case Snake::Direction::right:
		m_Pos.x += 16;
		break;
	case Snake::Direction::up:
		m_Pos.y += 16;
		break;
	case Snake::Direction::down:
		m_Pos.y -= 16;
		break;
	}
}

Point2f Snake::GetPosition()
{
	return m_Pos;
}

void Snake::SetPosition(const Point2f& pos)
{
	m_Pos = { pos };
}

void Snake::ResetDirection()
{
	m_DirectionSnake = Direction::right;
}

Snake::~Snake()
{
	delete m_pSnake;
}
