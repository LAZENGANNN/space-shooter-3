#pragma once
#include "settings.h"
#include "laser.h"
#include <list>
#include "textObj.h"

class Player {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float speedx = 0.f;
	int lives = 3;
	std::list<Laser*> lasers;
	sf::Clock timer;
	int hp = INITIAL_HP;
	TextObj hpText;


public:
	Player() : hpText(std::to_string(hp), sf::Vector2f(0.f,0.f)){
		texture.loadFromFile(PLAYER_FILE_NAME);
		sprite.setTexture(texture);
		sprite.setPosition(PLAYER_START_POS);
		timer.restart();
	}
	void fire() {
		Laser* l = new Laser(sf::Vector2f{ sprite.getPosition().x + PLAYER_WIDTH / 2, sprite.getPosition().y });
		lasers.push_back(l);		
	}

	void update() {
		speedx = 0.f;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			speedx = -PLAYER_SPEEDX;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			speedx = PLAYER_SPEEDX;
		sprite.move(speedx, 0.f);

		float playerx = sprite.getPosition().x;
		float playery = sprite.getPosition().y;
		if (playerx <= 0) sprite.setPosition(0.f, playery);
		if (playerx >= WINDOW_WIDTH - PLAYER_WIDTH)
			sprite.setPosition(WINDOW_WIDTH - PLAYER_WIDTH, playery);
	
		float time = timer.getElapsedTime().asMilliseconds();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			if (time > 400) {
				fire();
				timer.restart();
			}
			}
		
			for (auto laser : lasers) {
				laser->update();
			}
			hpText.update("HP:" + std::to_string(hp));
	}
	/*sf::Sprite getSprite() { return sprite; }*/
	void draw(sf::RenderWindow& window) {
		window.draw(sprite);
			for (auto laser : lasers) {
				laser->getSprite();
				window.draw(laser->getSprite());
			}
			window.draw(hpText.getText());
	}
	/*void checkLives(sf::RenderWindow window) {
		if (lives <= 0) window.close();
	}*/
	bool isDead() { return hp <= 0; }

	void receveDamage(int damage) { hp -= damage;}
	int getHp() { return hp; }
	int getLives() { return lives; }
	sf::FloatRect getHitBox() {return sprite.getGlobalBounds();}
	void incLives() { lives++; }
	void decLives() { lives--; }
	

};
