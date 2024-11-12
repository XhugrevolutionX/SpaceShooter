#include "Asteroid.h"
#include <random>

int Asteroid::counter_ = 0;
std::vector<sf::Texture> Asteroid::textures_;
Asteroid::Asteroid()
{
	// Seed with a real random value, if available
	std::random_device rn_device;
	// Choose a random mean between min and max
	std::default_random_engine engine(rn_device());
	std::uniform_real_distribution<float> uniform_dist_x(-50, 50);
 	std::uniform_real_distribution<float> uniform_dist_y(200, 300);
	std::uniform_real_distribution<float> rng_sprite_distribution(0, 2);

	int rng_sprite = static_cast<int>(rng_sprite_distribution(engine));

	textures_.resize(2);
	textures_.at(0).loadFromFile("Assets/Asteroid.png");
	textures_.at(1).loadFromFile("Assets/SmallAsteroid.png");

	sprite_.setTexture(textures_.at(rng_sprite));
	sprite_.setOrigin(textures_.at(rng_sprite).getSize().x / 2, textures_.at(rng_sprite).getSize().y / 2);

	hitbox.setRadius(textures_.at(rng_sprite).getSize().y / 2);
	hitbox.setOrigin(hitbox.getRadius(), hitbox.getRadius());
	hitbox.setFillColor(sf::Color::Red);

	direction_ = { uniform_dist_x(engine) , uniform_dist_y(engine) };
	counter_++;

}

void Asteroid::Rotate()
{
	// Seed with a real random value, if available
	std::random_device rn_device;
	// Choose a random mean between min and max
	std::default_random_engine engine(rn_device());
	std::uniform_real_distribution<float> uniform_dist_x(0.005, 0.05);

	setRotation(getRotation() + uniform_dist_x(engine));
}

