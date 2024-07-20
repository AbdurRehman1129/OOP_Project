#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"

using namespace sf;
using namespace std;
class Game
{
private:
	//windows
	RenderWindow* window;

	//resources
	map<string, Texture*> textures;
	vector<Bullet*> bullets;

	//player
	Player* player;

	//player GUI
	RectangleShape playerHpBar;
	RectangleShape playerHpBarBack;


	//GUI
	Font font;
	Text pointText;
	Text gameOverText;

	//world
	Sprite worldBackground;
	Texture worldBackgroundTex;

	//systems
	unsigned points;

	//enemies
	float spawnTimer;
	float spawnTimerMax;
	vector<Enemy*> enemies;


	//private function
	void initWindow();
	void initTextures();
	void initPlayer();
	void initEnemies();
	void initGUI();
	void initWorld();
	void initSystems();


public:
	Game();
	virtual ~Game();
	//functions
	void run();
	void updatePollEvents();
	void updateInput();
	void updateBullets();
	void updateEnemies();
	void updateCombat();
	void updateGUI();
	void renderGUI();
	void update();
	void render();
	void renderWorld();
	void updateWorld();
	void updateCollision();


};