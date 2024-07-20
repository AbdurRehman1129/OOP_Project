#include "Enemy.h"
using namespace sf;



void Enemy::initVariales()
{
	this->pointCount = rand() % 8 + 3; //min = 3 , max = 10
	this->type = 0;
	this->hpMax = static_cast<int>(this->pointCount);
	this->hp = this->hpMax;
	this->damage = this->pointCount;
	this->points = this->pointCount;
	this->speed = static_cast<float>(this->pointCount / 3);
}
void Enemy::initShapes()
{
	this->shape.setRadius(this->pointCount * 5);
	this->shape.setPointCount(this->pointCount);
	this->shape.setFillColor(Color(rand() % 255 + 1, rand() % 255 + 1, 255));

}
Enemy::Enemy(float pos_x, float pos_y)
{
	this->initVariales();
	this->initShapes();
	this->shape.setPosition(pos_x, pos_y);

}

Enemy::~Enemy()
{

}
//accessors

const FloatRect Enemy::getBounds() const
{
	return this->shape.getGlobalBounds();
}

const int& Enemy::getPoints() const
{
	return this->points;
}

const int& Enemy::getDamage() const
{
	return this->damage;

}


void Enemy::update()
{
	this->shape.move(0.f, this->speed);
}

void Enemy::render(RenderTarget* target)
{
	target->draw(this->shape);
}
