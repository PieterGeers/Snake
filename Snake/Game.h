#pragma once
#include "Food.h"
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
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e);
	void ProcessKeyUpEvent(const SDL_KeyboardEvent& ) {}
	void ProcessMouseMotionEvent(const SDL_MouseMotionEvent& ) {}
	void ProcessMouseDownEvent(const SDL_MouseButtonEvent& ) {}
	void ProcessMouseUpEvent(const SDL_MouseButtonEvent& ) {}

private:
	// DATA MEMBERS
	Window m_Window;
	float m_AccTime;

	Snake* m_pSnake;
	Food* m_pFood;

	bool m_DrawFood, m_GameLoop;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
	void Clear( );
	void DrawBackground() const;
	void SnakeEatsFood() const;
	void LoseConditions();
};