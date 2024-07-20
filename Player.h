#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
using namespace sf;
class Player
{
private:
	Sprite sprite;
	Texture texture;

	float movementSpeed;
	float attackCooldown;
	float attackCooldownMax;

	int hp;
	int hpMax;

	//private function
	void initVariables();
	void initTexture();
	void initSprite();

public:

	Player();
	virtual ~Player();
	//accessor
	const Vector2f& getPos() const;
	const FloatRect getBounds() const;
	const int& getHp() const;
	const int& getHpMax() const;



	//modifiers
	void setPosition(const Vector2f pos);
	void setPosition(const float x, const float y);
	void setHp(const int hp);
	void loseHp(const int value);

	//functions
	void move(const float dirX, const float dirY);
	const bool canAttack();
	void updateAttack();
	void update();
	void render(RenderTarget& target);

};

