#include "Asteroid.h"
#include <random>

int Asteroid::counter_ = 0;
sf::Texture Asteroid::texture_;
Asteroid::Asteroid()
{

	texture_.loadFromFile("Assets/Asteroid.png");
	sprite_.setTexture(texture_);
	sprite_.setOrigin(texture_.getSize().x / 2, texture_.getSize().y / 2);


	// Seed with a real random value, if available
	std::random_device rn_device;
	// Choose a random mean between min and max
	std::default_random_engine engine(rn_device());
	std::uniform_real_distribution<float> uniform_dist_x(-50, 50);
	std::uniform_real_distribution<float> uniform_dist_y(200, 300);


	hitbox.setRadius(texture_.getSize().y / 2);
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

