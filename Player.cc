#include "Player.h"

#include "PowerUp.h"

float player::timer_ = 0;
float player::shield_timer_ = 0;

player::player()
{
	sf::Vector2i pos = {0,0};
	sf::Vector2i size = {64,64};
	int nb_sprites = 3;
	int shield_nb_sprites = 4;

	textures_player_.resize(nb_sprites);

	for (int i = 0; i < nb_sprites; i++)
	{
		textures_player_.at(i).loadFromFile("Assets/red_ship.png", sf::IntRect(pos.x + i * size.x, pos.y, size.x, size.y));
	}
	sprite_.setTexture(textures_player_.at(state_));
	sprite_.setOrigin(size.x / 2, size.y / 2);

	hitbox.setRadius(textures_player_.at(state_).getSize().y / 4);
	hitbox.setOrigin(hitbox.getRadius(), hitbox.getRadius());
	hitbox.setScale(1.5, 2.5);
	hitbox.setFillColor(sf::Color::Red);

	textures_shield_.resize(shield_nb_sprites);

	for (int i = 0; i < shield_nb_sprites; i++)
	{
		textures_shield_.at(i).loadFromFile("Assets/shield_animation" + std::to_string(i) + ".png");
	}
	shield_sprite_.setTexture(textures_shield_.at(shield_state_));
	shield_sprite_.setOrigin(textures_shield_.at(shield_state_).getSize().x / 2, textures_shield_.at(shield_state_).getSize().y / 2);
	shield_sprite_.setScale(5, 5);
}

void player::Damage(sf::Text& player_hp_display)
{
	if (!shield_)
	{
		hp_ -= 1;
		set_isHit(true);
		if (hp_ <= 0)
		{
			SetDeath();
		}

		std::string str = std::to_string(GetHp());
		str.append(" Hp");
		player_hp_display.setString(str);
	}
	else
	{
		shield_ = !shield_;
	}
		
}
void player::Heal(int h, sf::Text& player_hp_display)
{
	hp_ += h;
	std::string str = std::to_string(GetHp());
	str.append(" Hp");
	player_hp_display.setString(str);
}

void player::CheckCollisions(std::vector<Asteroid>& asteroids_, sf::Text& player_hp_)
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

void player::CheckCollisions(std::vector<Enemies>& enemies, sf::Text& player_hp_)
{
	for (auto&e : enemies)
	{
		if (IsDead() == false && e.IsDead() == false && Intersects(e.HitBox()))
		{
			Damage(player_hp_);
			e.Damage(10);
		}
	}

}

void player::CheckCollisions(std::vector<Projectile>& projectiles, sf::Text& player_hp_)
{
	for (auto& p : projectiles)
	{
		if (IsDead() == false && p.IsDead() == false && Intersects(p.HitBox()))
		{
			Damage(player_hp_);
			p.SetDeath();
		}
	}
}

void player::CheckCollisions(std::vector<PowerUp>& power_ups_, sf::Text& player_hp_)
{
	for (auto& p : power_ups_)
	{
		if (IsDead() == false && p.IsDead() == false && Intersects(p.HitBox()))
		{
			switch (p.GetType())
			{
			case 0:
				Heal(2, player_hp_);
				break;
			case 1:
				Shield(true);
				break;
			}
			p.SetDeath();
		}
	}
}

void player::Refresh(float dt, std::vector<Asteroid>& asteroids_, std::vector<Enemies>& enemies, std::vector<Projectile>& projectiles, std::vector<PowerUp>& power_ups_,sf::Text& player_hp_)
{
	CheckCollisions(power_ups_, player_hp_);
	if (!is_hit_)
	{
		CheckCollisions(asteroids_, player_hp_);
		CheckCollisions(enemies, player_hp_);
		CheckCollisions(projectiles, player_hp_);
	}
	else
	{
		timer_ += dt * 10;
		if (timer_ > 15)
		{
			set_isHit(false);
			timer_ = 0;
		}
	}
	if (shield_)
	{
		shield_timer_ += dt;
		if (shield_timer_ > 0.2f)
		{
			if (shield_state_ >= 3)
			{
				shield_state_ = 0;
			}
			else
			{
				shield_state_++;
			}
			shield_sprite_.setTexture(textures_shield_.at(shield_state_));
			shield_timer_ = 0;
		}
	}

}


void player::movePlayer(sf::Vector2f direction, float dt, const sf::Vector2u& window_size)
{
	direction_ = direction * speed_;

	sf::Vector2f new_pos = getPosition() + direction_ * dt;

	if (!(new_pos.x > window_size.x - (sprite_.getGlobalBounds().width / 2) || new_pos.x < 0 + (sprite_.getGlobalBounds().width / 2) || new_pos.y > window_size.y - (sprite_.getGlobalBounds().height / 2) || new_pos.y < (window_size.y / 3) * 2))
	{
		Move(dt, window_size);
	}

}


void player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (!is_really_dead_)
	{
		if (!is_hit_ || static_cast<int>(timer_) % 2 == 0)
		{
			states.transform *= getTransform();
			target.draw(sprite_, states);
			if (shield_)
			{
				target.draw(shield_sprite_, states);
			}
		}
	}


	////draw the hitbox
	//target.draw(hitbox, states);

	////draw the hitbox Global bounds
	//sf::RectangleShape border({ hitbox.getGlobalBounds().width , hitbox.getGlobalBounds().height });
	//border.setOrigin(border.getSize().x / 2, border.getSize().y / 2);
	//border.setPosition(getPosition().x, getPosition().y);
	//border.setFillColor(sf::Color::Transparent);
	//border.setOutlineColor(sf::Color::Blue);
	//border.setOutlineThickness(2);
	//target.draw(border);
}
