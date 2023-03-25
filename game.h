#pragma once
#include "settings.h"
#include "Player.h"
#include "meteor.h"
#include <vector>
#include "textObj.h"
#include "laser.h"

class Game {
private:
	sf::RenderWindow window;
	Player player;
	std::vector<Meteor*> meteorSprites;
	TextObj lives;
	sf::RectangleShape rect;

	void checkEvents() {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
		}
	}
	void update() { 
	   player.update(); 
	   for (auto m : meteorSprites) {
		   m->update();
	   }
	   lives.update((std::to_string(player.getLives())));

	}
	void checkLives() {
		if (player.getLives() <= 0) {
			window.close();
		}
	}
	void rectangle() {
		rect.setFillColor(sf::Color::Black);
		rect.setSize(sf::Vector2f(600, 32));
		window.draw(rect);
	}
	void checkCollisions() {
		sf::FloatRect playerHitBox = player.getHitBox();
		for (auto& meteor : meteorSprites) {
			sf::FloatRect meteorHitBox = meteor->getHitBox();
			if (meteorHitBox.intersects(playerHitBox)) {
				meteor->spawn();
				player.receveDamage(meteor->getDamage());
			}
		}

	}
	void draw() {
		window.clear();
		for (auto m : meteorSprites) {
			window.draw(m->getSprite());
		}
		rectangle();
		player.draw(window);
		window.draw(lives.getText());
		window.display();
	};
	

public:
	Game() : lives(std::to_string(player.getLives()), sf::Vector2f{ WINDOW_WIDTH / 2,0.f }) 
	{
		window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_TITLE);
		window.setFramerateLimit(FPS);
		meteorSprites.reserve(METEOR_QTY);
		for (int i = 0; i < METEOR_QTY; i++) {
			meteorSprites.push_back(new Meteor());
		}
	}
	void play() {
		while (window.isOpen() && !player.isDead())
		{
			checkEvents();
			update();
			checkCollisions();
			draw();
		}
	}
};