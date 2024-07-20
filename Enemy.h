#ifndef ENEMY_H
#define ENEMY_H
#include <SFML/Graphics.hpp>
using namespace sf;


class Enemy
{
private:
	unsigned pointCount;
	CircleShape shape;
	int hp;
	int hpMax;
	int damage;
	int points;
	int type;
	float speed;

	void initVariales();
	void initShapes();


public:
	Enemy(float pos_x, float pos_y);
	virtual ~Enemy();
	//accessors
	const FloatRect getBounds() const;
	const int& getPoints() const;
	const int& getDamage() const;


	//functions
	void update();
	void render(RenderTarget* target);
};
#endif //ENEMY_H
