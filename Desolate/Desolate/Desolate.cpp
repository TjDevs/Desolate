#include <iostream>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Entity.h"
#include "Player.h"
#include "Zombie.h"
#include "Scene.h"
#include "Pawn.h"

/* short form
	dT = delta_time
	tM = texture_manager
*/

void loadTextures(TextureManager& tM) {
	tM.addTexture("Human01", "Data/Human01.png");
	tM.addTexture("Zombie01", "Data/Zombie01.png");
	tM.addTexture("Zombie02", "Data/Zombie02.png");
	tM.addTexture("Zombie03", "Data/Zombie03.png");
	tM.addTexture("Zombie04", "Data/Zombie04.png");
	tM.addTexture("Bullet01", "Data/Bullet01.png");
	tM.addTexture("Background01", "Data/background01.png");
}

void ZombieMain() {
	sf::RenderWindow gWindow(sf::VideoMode(1280, 960), "Derilict v1.0");
	sf::Event gEvent;
	sf::Clock deltaClock;
	TextureManager gtM;
	loadTextures(gtM);

	Player* player = new Player(&gWindow, &gtM);

	Scene scene(&gWindow, &gtM);
	scene.setSceneBackground("Background01");
	scene.addPlayer(player);
	for (int i = 0; i < 1; ++i) {
		scene.addZombie(new Zombie(&gWindow, &gtM, player, NORMAL));
	}

	while (gWindow.isOpen()) {
		sf::Time dT = deltaClock.restart();
		// Input Code
		while (gWindow.pollEvent(gEvent)) {
			if (gEvent.type == sf::Event::Closed)
				gWindow.close();
			if (gEvent.type == sf::Event::KeyPressed) {
				player->changeDirection(gEvent);
				if (gEvent.key.code == sf::Keyboard::Escape)
					gWindow.close();
			}
			if (gEvent.type == sf::Event::KeyReleased) {
				player->changeDirection(gEvent);
			}
		}
		// Update Code
		sf::View view = gWindow.getView();
		view.setCenter(player->getPosition());
		gWindow.setView(view);
		scene.update(dT.asSeconds());
		// Render Code
		gWindow.clear(sf::Color(13, 39, 38, 255));
		scene.render();
		gWindow.display();
	}

}

int RTSMain() {
	sf::RenderWindow gWindow(sf::VideoMode(1280, 960), "RTS Game");
	sf::Event gEvent;
	sf::Clock delta_clock;

	TextureManager gtM;
	loadTextures(gtM);

	srand(time(NULL));

	std::vector<Pawn> pawns;

	for (int i = 0; i != 5; i++) {
		pawns.push_back(Pawn(&gWindow, &gtM));
	}

	while (gWindow.isOpen()) {

		float dT = delta_clock.restart().asSeconds();

		while (gWindow.pollEvent(gEvent)) {
			if (gEvent.type == sf::Event::Closed)
				gWindow.close();
			if (gEvent.type == sf::Event::KeyPressed)
				if (gEvent.key.code == sf::Keyboard::Escape)
					gWindow.close();
			if (gEvent.type == sf::Event::MouseButtonPressed) {
				if (gEvent.mouseButton.button == sf::Mouse::Left) {
					for (int i = 0; i != pawns.size(); i++) {
						pawns[i].mpawn_state = MOVING;
						pawns[i].target_ = sf::Vector2f(sf::Mouse::getPosition(gWindow));
					}
				}
			}
		}

		for (int i = 0; i != pawns.size(); i++) {
			pawns[i].update(dT);
		}


		gWindow.clear(sf::Color(50, 50, 50, 255));
		for (int i = 0; i != pawns.size(); i++) {
			pawns[i].render();
		}
		gWindow.display();
	}

	return 0;
}

int main() {
	ZombieMain();
	return 0;
}

//void auraEffect(Player* player) {
//	sf::CircleShape circle;
//	sf::CircleShape circle1;
//	sf::CircleShape circle2;
//
//	circle.setFillColor(sf::Color::Red);
//	circle.setRadius(5.0f);
//	circle.setOrigin(circle.getRadius() / 2.0f, circle.getRadius() / 2.0f);
//	circle.setPosition(sf::Vector2f(player.msprite.getPosition().x + sinf(clock.getElapsedTime().asSeconds() * 5.0f) * 100.0f, player.msprite.getPosition().y + cosf(clock.getElapsedTime().asSeconds() * 5.0f) * 100.0f));
//
//	circle1.setFillColor(sf::Color::Green);
//	circle1.setRadius(5.0f);
//	circle1.setOrigin(circle1.getRadius() / 2.0f, circle1.getRadius() / 2.0f);
//	circle1.setPosition(sf::Vector2f(player.msprite.getPosition().x + sinf(clock.getElapsedTime().asSeconds() * 5.0f + 90.0f) * 100.0f, player.msprite.getPosition().y + cosf(clock.getElapsedTime().asSeconds() * 7.0f + 90.0f) * 100.0f));
//
//	circle2.setFillColor(sf::Color::Blue);
//	circle2.setRadius(5.0f);
//	circle2.setOrigin(circle2.getRadius() / 2.0f, circle2.getRadius() / 2.0f);
//	circle2.setPosition(sf::Vector2f(player.msprite.getPosition().x + sinf(clock.getElapsedTime().asSeconds() * 5.0f + 180.0f) * 100.0f, player.msprite.getPosition().y + cosf(clock.getElapsedTime().asSeconds() * 3.0f + 180.0f) * 100.0f));
//
//	gWindow.draw(circle);
//	gWindow.draw(circle1);
//	gWindow.draw(circle2);
//}