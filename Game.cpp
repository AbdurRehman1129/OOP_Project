
#include "Game.h"
using namespace sf;

//private function
void Game::initWindow()
{
	this->window = new RenderWindow(VideoMode(800, 600), "Swaglords of Space", Style::Close | Style::Titlebar);
	this->window->setFramerateLimit(144);
	this->window->setVerticalSyncEnabled(false);
}
void Game::initTextures()
{
	this->textures["BULLET"] = new Texture();
	this->textures["BULLET"]->loadFromFile("Textures/bullet.png");

}
void Game::initPlayer()
{
	this->player = new Player();
}
void Game::initEnemies()
{
	this->spawnTimerMax = 50.f;

	this->spawnTimer = this->spawnTimerMax;

}
void Game::initGUI()
{
	//load fonts
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		cout << "ERROR::GAME::Failed to load font" << "\n";
	}
	//init point text
	this->pointText.setPosition(700.f, 25.f);
	this->pointText.setFont(this->font);
	this->pointText.setCharacterSize(25);
	this->pointText.setFillColor(Color::White);
	this->pointText.setString("TESTING");

	//init gameover text
	this->gameOverText.setFont(this->font);
	this->gameOverText.setCharacterSize(60);
	this->gameOverText.setFillColor(Color::Red);
	this->gameOverText.setString("Game Over!");
	this->gameOverText.setPosition(
		this->window->getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f,
		this->window->getSize().y / 2.f - this->gameOverText.getGlobalBounds().height / 2.f);

	//init player GUI
	this->playerHpBar.setSize(Vector2f(300.f, 25.f));
	this->playerHpBar.setFillColor(Color::Red);
	this->playerHpBar.setPosition(Vector2f(20.f, 20.f));
	this->playerHpBarBack = this->playerHpBar;
	this->playerHpBarBack.setFillColor(Color(25, 25, 25, 200));


}
void Game::initWorld()
{
	if (!this->worldBackgroundTex.loadFromFile("Textures/background1.jpg"))
	{
		cout << "ERROR::GAME::COULD NOT LOAD BACKGROUND TEXTURE" << "\n";
	}
	this->worldBackground.setTexture(this->worldBackgroundTex);
}
void Game::initSystems()
{
	this->points = 0;
}
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initPlayer();
	this->initEnemies();
	this->initWorld();
	this->initGUI();
	this->initSystems();

}
Game::~Game()
{
	delete this->window;
	delete this->player;
	//delete texture
	for (auto& i : this->textures)
	{
		delete i.second;
	}
	//delete bullet
	for (auto& i : this->bullets)
	{
		delete i;
	}
	//delete enemies
	for (auto& i : this->enemies)
	{
		delete i;
	}
}

//functions
void Game::run()
{
	while (this->window->isOpen())
	{
		this->updatePollEvents();
		if (this->player->getHp() > 0)
			this->update();
		this->render();
	}
}
void Game::updatePollEvents()
{
	Event e;
	while (this->window->pollEvent(e))
	{
		if (e.Event::type == Event::Closed)
			this->window->close();
		if (e.Event::KeyPressed && e.Event::key.code == Keyboard::Escape)
			this->window->close();
	}
}
void Game::updateInput()
{
	//move player

	if (Keyboard::isKeyPressed(Keyboard::A))
		this->player->move(-1.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::D))
		this->player->move(1.f, 0.f);
	if (Keyboard::isKeyPressed(Keyboard::W))
		this->player->move(0.f, -1.f);
	if (Keyboard::isKeyPressed(Keyboard::S))
		this->player->move(0.f, 1.f);
	if (Mouse::isButtonPressed(Mouse::Left) && this->player->canAttack())
	{
		this->bullets.push_back(
			new Bullet(
				this->textures["BULLET"], this->player->getPos().x + this->player->getBounds().width / 2.f, this->player->getPos().y, 0.f, -1.f, 5.f));
	}

}
void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* bullet : this->bullets)
	{
		bullet->update();
		//bullet culling (top of screen)
		if (bullet->getBounds().top + bullet->getBounds().height < 0.f)
		{//delete bullet
			delete this->bullets.at(counter);

			this->bullets.erase(this->bullets.begin() + counter);
			--counter;
			cout << this->bullets.size() << "\n";
		}
		++counter;
	}
}
void Game::updateEnemies()
{//spawning
	this->spawnTimer += 0.5f;
	if (this->spawnTimer >= this->spawnTimerMax)
	{
		this->enemies.push_back(new Enemy(rand() % this->window->getSize().x - 20.f, -100.f));
		this->spawnTimer = 0.f;
	}

	//update
	unsigned counter = 0;
	for (auto* enemy : this->enemies)
	{
		enemy->update();
		//bullet culling (top of screen)
		if (enemy->getBounds().top > this->window->getSize().y)
		{//delete enemies
			delete this->enemies.at(counter);

			this->enemies.erase(this->enemies.begin() + counter);
			cout << this->enemies.size() << "\n";
			--counter;

		}
		else if (enemy->getBounds().intersects(this->player->getBounds()))
		{
			// delete enemies when collide with player
			this->player->loseHp(this->enemies.at(counter)->getDamage());
			delete this->enemies.at(counter);

			this->enemies.erase(this->enemies.begin() + counter);

			cout << this->enemies.size() << "\n";
			--counter;

		}
		++counter;
	}


}
void Game::updateCombat()
{
	for (int i = 0; i < this->enemies.size(); ++i)
	{
		bool enemy_deleted = false;
		for (size_t k = 0; k < this->bullets.size() && enemy_deleted == false; k++)
		{
			if (this->enemies[i]->getBounds().intersects(this->bullets[k]->getBounds()))
			{
				this->points += this->enemies[i]->getPoints();

				delete this->enemies[i];
				this->enemies.erase(this->enemies.begin() + i);

				delete this->bullets[k];
				this->bullets.erase(this->bullets.begin() + k);



				enemy_deleted = true;
			}
		}
	}
}
void Game::updateGUI()
{
	stringstream ss;
	ss << "Points: " << this->points;
	this->pointText.setString(ss.str());
	//update player GUI
	float hpPercent = static_cast<float>(this->player->getHp()) / this->player->getHpMax();
	this->playerHpBar.setSize(Vector2f(300.f * hpPercent, this->playerHpBar.getSize().y));


}
void Game::renderGUI()
{
	this->window->draw(this->pointText);
	this->window->draw(this->playerHpBarBack);
	this->window->draw(this->playerHpBar);
}
void Game::update()
{
	this->updateEnemies();
	this->updateCollision();
	this->updateWorld();

	this->updateCombat();
	this->updateBullets();
	this->updateInput();
	this->player->update();
	this->player->updateAttack();
	this->updateGUI();

}
void Game::render()
{
	this->window->clear();
	//draw world
	this->renderWorld();
	//draw all the stuffs
	this->player->render(*this->window);
	for (auto* bullet : this->bullets)
	{
		bullet->render(this->window);
	}
	for (auto* enemy : this->enemies)
	{
		enemy->render(this->window);
	}
	this->renderGUI();

	//game over sreen

	if (this->player->getHp() <= 0)
		this->window->draw(this->gameOverText);
	this->window->display();

}

void Game::renderWorld()
{
	this->window->draw(this->worldBackground);
}

void Game::updateWorld()
{

}

void Game::updateCollision()
{//left world collision
	if (this->player->getBounds().left < 0.f)
	{
		this->player->setPosition(0.f, this->player->getBounds().top);
	}
	//right world colision
	else if (this->player->getBounds().left + this->player->getBounds().width >= this->window->getSize().x)
	{
		this->player->setPosition(this->window->getSize().x - this->player->getBounds().width, this->player->getBounds().top);
	}

	//top world collision
	if (this->player->getBounds().top < 0.f)
	{
		this->player->setPosition(this->player->getBounds().left, 0.f);
	}
	//bottom world colision
	else if (this->player->getBounds().top + this->player->getBounds().height >= this->window->getSize().y)
	{
		this->player->setPosition(this->player->getBounds().left, this->window->getSize().y - this->player->getBounds().height);
	}
}
