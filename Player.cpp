#include <iostream>
#include "Player.h"
using namespace sf;
using namespace std;

void Player::initVariables()
{
	this->movementSpeed = 2.f;
	this->attackCooldownMax = 10.f;
	this->attackCooldown = this->attackCooldownMax;
	this->hpMax = 100;
	this->hp = this->hpMax;
}

void Player::initTexture()
{
	//load texture from files
	if (!this->texture.loadFromFile("Textures/ship.png"))
	{
		cout << "ERROR::PLAYER::INITTEXTURE::Could not load texture file." << "\n";
	}

}
void Player::initSprite()
{
	//set the texture to the sprite
	this->sprite.setTexture(this->texture);
	//resize
	this->sprite.scale(0.1f, 0.1f);
}
Player::Player()
{
	this->initVariables();
	this->initTexture();

	this->initSprite();
}
Player::~Player()
{

}
const Vector2f& Player::getPos() const
{
	return this->sprite.getPosition();
}
const FloatRect Player::getBounds() const
{
	return this->sprite.getGlobalBounds();
}
const int& Player::getHp() const
{
	return this->hp;

}
const int& Player::getHpMax() const
{
	return this->hpMax;
}
void Player::setPosition(const Vector2f pos)
{
	this->sprite.setPosition(pos);
}
void Player::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}
void Player::setHp(const int hp)
{
	this->hp = hp;
}
void Player::loseHp(const int value)
{
	this->hp -= value;
	if (this->hp < 0)
		this->hp = 0;
}
//functions

void Player::move(const float dirX, const float dirY)
{
	this->sprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

const bool Player::canAttack()
{
	if (this->attackCooldown >= this->attackCooldownMax)
	{
		this->attackCooldown = 0.f;
		return true;
	}
	return false;

}

void Player::updateAttack()
{
	if (this->attackCooldown < this->attackCooldownMax)
		this->attackCooldown += 0.5f;

}

void Player::update()
{

}
void Player::render(RenderTarget& target)
{
	target.draw(this->sprite);
}