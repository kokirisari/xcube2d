#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__

#include "../engine/AbstractGame.h"
#include <string>

struct GameKey {
	Point2 pos;
	bool isAlive;
};


class MyGame : public AbstractGame {
private:
	Rect box;
	Vector2i velocity;

	std::vector<std::shared_ptr<Button>> buttons;
	std::vector<std::shared_ptr<GameKey>> gameKeys;

	MyEngineSystem engineSystem;

	/* GAMEPLAY */
	int score, numKeys, lives;
	bool gameWon, buttonClicked;

	void handleKeyEvents();
	void update();
	void render();
	void renderUI();
	void renderButtons();
	void loadButtons();
	void buttonsAction();
public:
	MyGame();
	~MyGame();
	SDL_Color primaryColor = { 255, 255, 255 };
	SDL_Color secondaryColor = { 255, 255, 255 };
	SDL_Color tertiaryColor = { 255, 255, 255 };
};

#endif
