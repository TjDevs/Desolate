#ifndef ZOMBIE_H
#define ZOMBIE_H

class Zombie {
public:
	Zombie(sf::RenderWindow* window, Player* player, TextureManager* tM) : mwindow(window), mplayer(player), mTM(tM) {
		mmovement_speed = 200.0f;
		mzombie_rotation = 0.0f;

		msprite.setTexture(mTM->getTexture("Zombie01"));
		msprite.setOrigin(12.0f, 12.0f);
		msprite.setScale(sf::Vector2f(4.0f, 4.0f));
		msprite.setPosition(sf::Vector2f(50.0f, 50.0f));
		msprite.setRotation(0.0f);

		m_last_seen_player = msprite.getPosition();
	}

	void update(float deltaTime) {
		if (getDistance(msprite.getPosition(), mplayer->msprite.getPosition()) <= 500.0f) {
			moveTo(mplayer->msprite.getPosition(), deltaTime);
			m_last_seen_player = mplayer->msprite.getPosition();
		}
		else {
			moveTo(m_last_seen_player, deltaTime);
		}
	}

	void render() {
		mwindow->draw(msprite);
	}
private:

	float getDistance(sf::Vector2f pos1, sf::Vector2f pos2) {
		return sqrt((pos1.x - pos2.x) * (pos1.x - pos2.x) + (pos1.y - pos2.y) * (pos1.y - pos2.y));
	}

	void moveTo(sf::Vector2f targetPos, float deltaTime) {
		mzombie_rotation = (atan2(msprite.getPosition().y - targetPos.y, msprite.getPosition().x - targetPos.x) * 180.0f / 3.14f);
		msprite.setRotation(mzombie_rotation - 90.0f);
		float movementX = static_cast<float>(cos(3.14 * mzombie_rotation / 180) * mmovement_speed * deltaTime);
		float movementY = static_cast<float>(sin(3.14 * mzombie_rotation / 180) * mmovement_speed * deltaTime);
		if (getDistance(msprite.getPosition(), targetPos) >= 85.0f) {
			msprite.move(-movementX, -movementY);
		}
		else {
			msprite.move(0.0f, 0.0f);
		}
	}

	sf::Sprite msprite;
	sf::Vector2f m_last_seen_player;

	float mmovement_speed;

	float mzombie_rotation;

	sf::RenderWindow* mwindow;
	TextureManager* mTM;
	Player* mplayer;
};

#endif