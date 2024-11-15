#ifndef POWERUPSMANAGER_H
#define POWERUPSMANAGER_H
#include "PowerUp.h"


class PowerUpsManager : public sf::Drawable
{
private:
	std::vector<PowerUp> power_ups_;
	sf::Clock timer_;
	float spawn_timer = 0;

public:
	std::vector<PowerUp>& GetEntities() { return power_ups_; }
	void Refresh(float dt_, const sf::Vector2u& window_size);


protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // POWERUPSMANAGER_H
