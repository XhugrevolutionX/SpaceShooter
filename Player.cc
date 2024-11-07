#include "Player.h"


player::player()
{
	sf::Vector2i pos = {0,0};
	sf::Vector2i size = {64,64};
	int nb_sprites = 3;

	sprites.resize(nb_sprites);
	textures.resize(nb_sprites);

	for (int i = 0; i < nb_sprites; i++)
	{
		textures.at(i).loadFromFile("Assets/red_ship.png", sf::IntRect(pos.x + i * size.x, pos.y, size.x, size.y));

		sprites.at(i).setTexture(textures.at(i));
		sprites.at(i).setOrigin(size.x / 2, size.y / 2);
	}

	hitbox.setRadius(textures.at(0).getSize().y / 4);
	hitbox.setOrigin(hitbox.getRadius(), hitbox.getRadius());
	hitbox.setScale(1.5, 2.5);
	hitbox.setFillColor(sf::Color::Red);
}

void player::Damage(sf::Text& player_hp_display)
{
	hp -= 1;
	if (hp <= 0)
	{
		SetDeath();
	}

	std::string str = std::to_string(GetHp());
	str.append(" Hp");
	player_hp_display.setString(str);

}
void player::CheckAsteroidCollisions(std::vector<Asteroid>& asteroids_, sf::Text& player_hp_)
{
	
	for (auto& a : asteroids_)
	{
		if (IsDead() == false && a.IsDead() == false && Intersects(a.HitBox()))
		{
			Damage(player_hp_);
			a.SetDeath();
		}
	}

}

void player::movePlayer(sf::Vector2f direction, float dt, const sf::Vector2u& window_size)
{
	direction_ = direction * speed;

	sf::Vector2f new_pos = getPosition() + direction_ * dt;

	if (!(new_pos.x > window_size.x - (sprites.at(0).getGlobalBounds().width / 2) || new_pos.x < 0 + (sprites.at(0).getGlobalBounds().width / 2) || new_pos.y > window_size.y - (sprites.at(0).getGlobalBounds().height / 2) || new_pos.y < (window_size.y / 3) * 2))
	{
		Move(dt, window_size);
	}

}
void player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

	states.transform *= getTransform();
	target.draw(sprites.at(get_state()), states);
	//target.draw(hitbox, states);
}
