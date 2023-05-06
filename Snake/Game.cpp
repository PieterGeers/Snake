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
	m_pFood = new Texture{ "Resources/apple.png" };

	m_pSnake = new Snake{};

	m_AccTime = 0 ;
	m_DrawFood = true;
	m_GameLoop = true;
	m_FoodPos = { 160, 160 };
}

void Game::Cleanup( )
{
	delete m_pFood;
	delete m_pSnake;
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

	DrawFood();
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

void Game::DrawFood()
{
	/*int Idx{ rand() % m_NrBackgroundTiles };
	if (m_DrawFood == true)
	{
		for (int i{}; i < m_SnakeLength; ++i)
		{
			if (m_pSnake[i]->GetPosition().x != m_FoodPos.x && m_pSnake[i]->GetPosition().y != m_FoodPos.y)
			{
				m_FoodPos = { m_pBackgroundPos[Idx]->x, m_pBackgroundPos[Idx]->y };
				m_DrawFood = false;
			}
		}
	}*/
	m_pFood->Draw({ m_FoodPos.x, m_FoodPos.y }, { 0, 0, m_pFood->GetWidth(), m_pFood->GetHeight() });
}

void Game::SnakeEatsFood() const
{
	const Point2f headPos = m_pSnake->GetPosition();
	if (headPos.x == m_FoodPos.x && headPos.y == m_FoodPos.y)
	{
		m_pSnake->IncreaseSize();
		std::cout << "Nom" << std::endl;
	}
}

void Game::LoseConditions()
{
	const Point2f headPos = m_pSnake->GetPosition();

	if (headPos.x < 0 || headPos.x > m_Window.width 
		|| headPos.y < 0 || headPos.y > m_Window.height 
		|| m_pSnake->HasEatenItself())
	{
		m_GameLoop = false;
		std::cout << "GAME OVER" << std::endl;
		std::cout << "Score: " << m_pSnake->GetScore() << std::endl;
		std::cout << "Press 'R' to play again" << std::endl;
	}
}