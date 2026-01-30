#include "MyGame.h"
std::shared_ptr<MyEngineSystem> mesfx;

MyGame::MyGame() : AbstractGame(), score(0), lives(3), numKeys(5), gameWon(false), buttonClicked(false), box(0, 0, 30, 30) {	
	loadButtons();
	TTF_Font* font = ResourceManager::loadFont("res/fonts/arial.ttf", 72);
	gfx->setWindowSize(engineSystem.xResolution, engineSystem.xResolution * 9/16);
	gfx->useFont(font);
	gfx->setVerticalSync(true);

	for (int i = 0; i < numKeys; i++) {
		std::shared_ptr<GameKey> k = std::make_shared<GameKey>();
		k->isAlive = true;
		k->pos = Point2(getRandom(0, engineSystem.xResolution * 9/16), getRandom(0, engineSystem.xResolution * 9 / 16));
		gameKeys.push_back(k);
	}
}

void MyGame::loadButtons()
{
	int xRes = engineSystem.xResolution;

	for (int i = 0; i < 4; i++)
	{
		int x = 0;
		int y = 0;
		std::string name;

		switch (i)
		{
		case 0: x = xRes * 19 / 32;  y = xRes * 7 / 32; name = "Primary Colour Setting"; break;
		case 1: x = xRes * 13 / 16;  y = xRes * 7 / 32; name = "Secondary Colour Setting"; break;
		case 2: x = xRes * 19 / 32;  y = xRes * 13 / 32; name = "Tertiary Colour Setting"; break;
		case 3: x = xRes * 13 / 16;  y = xRes * 13 / 32; name = "Resolution Setting"; break;
		}

		auto b = std::make_shared<Button>(
			x,
			y,
			xRes,
			name,
			0
		);

		buttons.push_back(b);
	}
}
void MyGame::buttonsAction()
{
	for (auto& b : buttons)
	{
		bool clicked = engineSystem.checkButtonClicked(*b, eventSystem);

		if (clicked)
		{
			bool buttonClicked = true;
			if (b->selection < 4)
			{
				b->selection++;
			}
			else
			{
				b->selection = 0;
			}
				engineSystem.applyResolutionSetting(*gfx, b->name, b->selection, &primaryColor, &secondaryColor, &tertiaryColor);
			}
	}
}

MyGame::~MyGame() {

}

void MyGame::handleKeyEvents() {
	int speed = 3;

	if (eventSystem->isPressed(Key::W)) {
		velocity.y = -speed;
	}

	if (eventSystem->isPressed(Key::S)) {
		velocity.y = speed;
	}

	if (eventSystem->isPressed(Key::A)) {
		velocity.x = -speed;
	}

	if (eventSystem->isPressed(Key::D)) {
		velocity.x = speed;
	}
}

void MyGame::update() {
	buttonsAction();
	box.x += velocity.x;
	box.y += velocity.y;

	for (auto key : gameKeys) {
		if (key->isAlive && box.contains(key->pos)) {
			score += 200;
			key->isAlive = false;
			numKeys--;
		}
	}

	velocity.x = 0;
	velocity.y = 0;

	if (numKeys == 0) {
		gameWon = true;
	}
}

void MyGame::render() {
	gfx->setDrawColor(tertiaryColor);
	gfx->drawRect(box);

	gfx->setDrawColor(secondaryColor);
	for (auto key : gameKeys)
		if (key->isAlive)
			gfx->drawCircle(key->pos, 5);
	renderButtons();

}

void MyGame::renderButtons()
{
	mesfx->setDrawColor(primaryColor);
	for (const auto& b : buttons)
	{
		gfx->drawRect(b->rect);
	}
}


void MyGame::renderUI() {
	gfx->setDrawColor(primaryColor);
	std::string scoreStr = std::to_string(score);
	gfx->drawText(scoreStr, engineSystem.xResolution*25/32 - scoreStr.length() * 50, engineSystem.xResolution*1/16);

	if (gameWon)
		gfx->drawText("YOU WON", 250, 500);
}

