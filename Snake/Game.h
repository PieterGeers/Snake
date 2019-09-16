#pragma once
#include "Texture.h"
#include "Snake.h"
class Game
{
public:
	explicit Game( const Window& window );
	Game( const Game& other ) = delete;
	Game& operator=( const Game& other ) = delete;
	~Game();

	void Update( float elapsedSec);
	void Draw( );

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e );
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e );
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e );
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e );
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e );

private:
	// DATA MEMBERS
	Window m_Window;
	float m_X, m_Y, m_AccTime;
	Texture* m_pBackground;
	Texture* m_pFood;
	static const int m_NrBackgroundTiles{ 900 };
	Point2f* m_pBackgroundPos[m_NrBackgroundTiles];
	bool m_DrawFood, m_GameLoop;
	Point2f m_FoodPos;
	Snake* m_pSnake[m_NrBackgroundTiles];
	int m_SnakeLength;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void ClearBackground( );
	void InitializeBackgroundPos();
	void DrawBackground();
	void DrawFood();
	void InitializeSnake();
	void DrawSnake();
	void UpdateSnake(float elapsedSec);
	void SnakeEatsFood();
	void LoseConditions();

};