#pragma once
#include "settings.h"
class Laser {
private:
	sf::Sprite sprite;
	sf::Texture texture;
	float speedy;

public:
Laser(sf::Vector2f pos) {
	texture.loadFromFile("images\\LaserGreen11.png");
	sprite.setTexture(texture);
	sf::FloatRect bounds = sprite.getLocalBounds();
	sprite.setOrigin(bounds.width / 2, bounds.height / 2);
	sprite.setPosition(pos);
	speedy = 15;
}

void update() {
	sprite.move(0, -speedy);
}

sf::Sprite getSprite() { return sprite; }
sf::FloatRect getHitBox() {return sprite.getGlobalBounds();}
};