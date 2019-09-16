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
	//textures
	m_pBackground = new Texture{ "Resources/0.png" };
	m_pFood = new Texture{ "Resources/2.png" };
	//x and y values for the amount of tiles
	m_X = m_Window.width / m_pBackground->GetWidth();
	m_Y = m_Window.height / m_pBackground->GetHeight();
	//initialize the arrays
	InitializeBackgroundPos();
	InitializeSnake();
	//variables
	m_AccTime = 0 ;
	m_DrawFood = true;
	m_GameLoop = true;
	m_FoodPos = { -100, -100 };
	m_SnakeLength = 1;
}

void Game::Cleanup( )
{
	delete m_pBackground;
	m_pBackground = nullptr;

	delete m_pFood;
	m_pFood = nullptr;

	for (int i{}; i < m_NrBackgroundTiles; ++i)
	{
		delete m_pBackgroundPos[i];
		delete m_pSnake[i];
		m_pBackgroundPos[i] = nullptr;
		m_pSnake[i] = nullptr;
	}
}

void Game::Update( float elapsedSec )
{
	if (m_GameLoop != false)
	{
		m_AccTime += elapsedSec;
		if (m_AccTime > 0.10f)
		{
			UpdateSnake(elapsedSec);
			m_AccTime -= 0.10f;
		}
		LoseConditions();
		SnakeEatsFood();
	}
}

void Game::Draw( )
{
	ClearBackground( );
	DrawBackground();
	DrawSnake();
	DrawFood();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{
	m_pSnake[0]->ProcessKeyDownEvent(e);
	if (m_GameLoop == false && e.keysym.sym == SDLK_r)
	{
		m_GameLoop = true;
		m_SnakeLength = 1;
		m_FoodPos = { -100, -100 };
		m_DrawFood = true;
		m_AccTime = 0;
		m_pSnake[0]->SetPosition({0, 0});
		m_pSnake[0]->ResetDirection();
		for (int i{ 1 }; i < m_NrBackgroundTiles; ++i)
		{
			m_pSnake[i]->SetPosition({ -100, -100 });
		}
	}
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent&  )
{
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent&  )
{
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent&  )
{
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent&  )
{
}

void Game::ClearBackground( )
{
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}

void Game::InitializeBackgroundPos()
{
	for (int i{}; i < m_Y; ++i)
	{
		for (int j{}; j < m_X; ++j)
		{
			m_pBackgroundPos[int(m_X)*i + j] = new Point2f{ float(0 + m_pBackground->GetWidth()*j), float(0 + m_pBackground->GetHeight()*i) };
		}
	}
}

void Game::DrawBackground()
{
	for (int i{}; i < m_NrBackgroundTiles; ++i)
	{
		m_pBackground->Draw({m_pBackgroundPos[i]->x, m_pBackgroundPos[i]->y}, { 0, 0, m_pBackground->GetWidth(), m_pBackground->GetHeight() });
	}
}

void Game::DrawFood()
{
	int Idx{ rand() % m_NrBackgroundTiles };
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
	}
	m_pFood->Draw({ m_FoodPos.x, m_FoodPos.y }, { 0, 0, m_pFood->GetWidth(), m_pFood->GetHeight() });
}

void Game::InitializeSnake()
{
	m_pSnake[0] = new Snake{ {0, 0} };
	for (int i{1}; i < m_NrBackgroundTiles; ++i)
	{
		m_pSnake[i] = new Snake{ {-100, -100} };
	}
}

void Game::DrawSnake()
{
	for (int i{}; i < m_SnakeLength; ++i)
	{
		m_pSnake[i]->Draw();
	}
}

void Game::UpdateSnake(float elapsedSec)
{
	if (m_SnakeLength >= 2)
	{
		for (int i{ m_SnakeLength }; i > 0; --i)
		{
			m_pSnake[i]->SetPosition({ m_pSnake[i - 1]->GetPosition().x,  m_pSnake[i - 1]->GetPosition().y });
		}
	}
	m_pSnake[0]->Update(elapsedSec);
}

void Game::SnakeEatsFood()
{
	if (m_pSnake[0]->GetPosition().x == m_FoodPos.x && m_pSnake[0]->GetPosition().y == m_FoodPos.y)
	{
		m_SnakeLength += 1;
		m_DrawFood = true;
	}
}

void Game::LoseConditions()
{
	if (m_pSnake[0]->GetPosition().x < 0 || m_pSnake[0]->GetPosition().x > m_Window.width 
		|| m_pSnake[0]->GetPosition().y < 0 || m_pSnake[0]->GetPosition().y > m_Window.height)
	{
		m_GameLoop = false;
		std::cout << "GAME OVER" << std::endl;
		std::cout << "Score: " << m_SnakeLength << std::endl;
		std::cout << "Press 'R' to play again" << std::endl;
	}
	for (int i{1}; i < m_SnakeLength; ++i)
	{
		if (m_pSnake[0]->GetPosition().x == m_pSnake[i]->GetPosition().x && m_pSnake[0]->GetPosition().y == m_pSnake[i]->GetPosition().y)
		{
			m_GameLoop = false;
			std::cout << "GAME OVER" << std::endl;
			std::cout << "Score: " << m_SnakeLength << std::endl;
			std::cout << "Press 'R' to play again" << std::endl;
		}
	}
}