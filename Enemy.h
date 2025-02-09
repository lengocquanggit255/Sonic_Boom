#ifndef ENEMY_H_
#define ENEMY_H_

#include "LTexture.h"

#define ENEMY_MAX_HEIGHT 200
#define ENEMY_MIN_HEIGHT 250

#define ENEMY_POSITION_RANGE 250

class Enemy
{
public:
	Enemy(int _type = 0);
	
	~Enemy();

	void LoadFromFile(std::string path, SDL_Renderer* gRenderer);

	void Move(const int& acceleration);

	void Render(SDL_Renderer* gRenderer, SDL_Rect* currentClip = nullptr);

	int GetType();

	int GetSpeed(const int& acceleration);

	void resetEnemy();

	int GetPosX();

	int GetPosY();

	int GetWidth();

	int GetHeight();
private:
	int posX, posY;

	int eWidth, eHeight;

	int type;

	SDL_Texture *EnemyTexture;
};

#endif // !ENEMY_H_