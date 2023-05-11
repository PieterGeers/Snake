#include "stdafx.h"
#include "Game.h"
#include <iostream>

Game::Game( const Window& window ) 
	:m_Window{ window }
{
	Initialize( );
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize( )
{
	m_pSnake = new Snake{};
	m_pFood = new Food{ m_Window };

	m_AccTime = 0 ;
	m_DrawFood = true;
	m_GameLoop = true;
}

void Game::Cleanup( )
{
	delete m_pSnake;
	delete m_pFood;
	m_pFood = nullptr;
}

void Game::Update( float elapsedSec )
{
	if (m_GameLoop != false)
	{
		m_AccTime += elapsedSec;
		if (m_AccTime > 0.10f)
		{
			m_pSnake->Update(elapsedSec);
			LoseConditions();
			SnakeEatsFood();

			m_AccTime -= 0.10f;
		}
	}
}

void Game::Draw( )
{
	Clear( );
	DrawBackground();

	m_pSnake->Draw();
	m_pFood->Draw();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	if (m_GameLoop)
	{
		m_pSnake->ProcessKeyDownEvent(e);
	}
	else
	{
		if (e.keysym.sym == SDLK_r)
		{
			delete m_pSnake;
			m_pSnake = new Snake{};

			m_GameLoop = true;
			m_AccTime = 0.f;
		}
	}
}

void Game::Clear( )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::DrawBackground() const
{
	glColor4f(0.95f, 0.95f, 0.9f, 1.0f);
	glBegin(GL_POLYGON);
	{
		glVertex2f(0, 0);
		glVertex2f(m_Window.width, 0);
		glVertex2f(m_Window.width, m_Window.height);
		glVertex2f(0, m_Window.height);
	}
	glEnd();
}

void Game::SnakeEatsFood() const
{
	const Point2f headPos = m_pSnake->GetPosition();
	const Point2f foodPos = m_pFood->GetPosition();

	if (abs(headPos.x - foodPos.x) < 0.1f && abs(headPos.y - foodPos.y) < 0.1f)
	{
		m_pSnake->IncreaseSize();
		m_pFood->Reposition(m_Window, m_pSnake->GetHead());
	}
}

void Game::LoseConditions()
{
	const Point2f headPos = m_pSnake->GetPosition();

	if (headPos.x < 0 || headPos.x >= m_Window.width 
		|| headPos.y < 0 || headPos.y >= m_Window.height 
		|| m_pSnake->HasEatenItself())
	{
		m_GameLoop = false;
		std::cout << "GAME OVER" << std::endl;
		std::cout << "Score: " << m_pSnake->GetScore() << std::endl;
		std::cout << "Press 'R' to play again" << std::endl;
	}
}