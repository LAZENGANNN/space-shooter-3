#pragma once
#include "settings.h"
class Meteor {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float speedx, speedy;
	int damage;



public:
	void spawn() {
		speedx = rand() % 5 - 2.f;
		speedy = rand() % 6 + 2.f;
		sf::FloatRect bounds = sprite.getGlobalBounds();
		float x = rand() % (int)(WINDOW_WIDTH - bounds.width);
		float y = -(rand() % (int)(WINDOW_HEIGHT - bounds.height) + bounds.height);
		sprite.setPosition(x, y);
	}
	static std::string mFileNames[];
	static int mDamage[];
	Meteor() {
		int index = rand() % 8;
		spawn();
		damage = mDamage[index];
		texture.loadFromFile(mFileNames[index]);
		sprite.setTexture(texture);
		
	}
	void update() {
		sprite.move(speedx, speedy);
		sf::Vector2f pos = sprite.getPosition();
		sf::FloatRect bounds = sprite.getGlobalBounds();
		if (bounds.left < -bounds.width || bounds.left > WINDOW_WIDTH || bounds.top > WINDOW_HEIGHT) { spawn(); }
	}
	sf::Sprite getSprite() { return sprite; }
	sf::FloatRect getHitBox() { return sprite.getGlobalBounds(); }
	int getDamage() { return damage; }

};

std::string Meteor::mFileNames[] = { "images\\meteorBrown_big1.png", "images\\meteorBrown_big2.png", "images\\meteorBrown_med1.png",
		"images\\meteorBrown_med2.png", "images\\meteorBrown_small1.png", "images\\meteorBrown_small2.png", "images\\meteorBrown_tiny1.png",
		"images\\meteorBrown_tiny2.png"};

int Meteor::mDamage[] = { 30,30,20,20,10,10,5,5 };