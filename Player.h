#ifndef PLAYER_H
#define PLAYER_H
#include "Asteroid.h"
#include "Enemies.h"
#include "PowerUp.h"
#include "Projectile.h"

class player : public Entity
{

private:
	int hp_ = 10;
	int score_ = 0;
	int state_ = 0;
	std::vector<sf::Texture> textures_player_;
	const float speed_ = 500.0f;
	bool is_hit_ = false;
	bool death_end_ = false;
	static float timer_;

	bool shield_ = false;
	std::vector<sf::Texture> textures_shield_;
	sf::Sprite shield_sprite_;
	static float shield_timer_;
	int shield_state_ = 0;
public:

	player();
	void set_isHit(bool hit_) { is_hit_ = hit_; }
	bool get_isHit() const { return is_hit_; }
	void set_EndDeath() { death_end_ = true; }
	bool is_death_ended() const { return death_end_; }
	void set_state(int state) { sprite_.setTexture(textures_player_.at(state_)); state_ = state; }
	int get_state() const { return state_; }
	int GetHp() const { return hp_; }
	void SetScore(int s) { score_ += s; }
	int GetScore() const { return score_; }
	void Damage(sf::Text& player_hp_);
	void CheckCollisions(std::vector<Asteroid>& asteroids_, sf::Text& player_hp_);
	void CheckCollisions(std::vector<Enemies>& enemies, sf::Text& player_hp_);
	void CheckCollisions(std::vector<Projectile>& projectiles, sf::Text& player_hp_);
	void CheckCollisions(std::vector<PowerUp>& power_ups_, sf::Text& player_hp_);
	void Refresh(float dt, std::vector<Asteroid>& asteroids_, std::vector<Enemies>& enemies, std::vector<Projectile>& projectiles, std::vector<PowerUp>& power_ups_,sf::Text& player_hp_);
	void movePlayer(sf::Vector2f direction, float dt, const sf::Vector2u& window_size);

	void Heal(int h, sf::Text& player_hp_display);
	void Shield(bool s) { shield_ = s; }
protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;


};
#endif