#ifndef BULLET_H
#define BULLET_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
using namespace sf;

class Bullet
{
private:
	Sprite shape;

	Vector2f direction;
	float movementSpeed;

public:
	Bullet(Texture* texture, float pos_x, float pos_y, float dir_X, float dir_Y, float movement_speed);
	virtual~Bullet();

	//accessor
	const FloatRect getBounds() const;
	void update();
	void render(RenderTarget* target);
};
#endif // !BULLET_H	
