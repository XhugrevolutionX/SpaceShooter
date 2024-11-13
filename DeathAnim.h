#ifndef DEATHANIM_H
#define DEATHANIM_H
#include <vector>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


class DeathAnim : public sf::Drawable
{
private:
	std::vector<sf::Texture> death_anim_;
	sf::Sprite sprite_;
	int nb_textures = 0;
	int state = 0;
	bool is_finished = false;
	float delay = 0;


public:
	void Init(std::string path, int nb_textures, float rotation);

	int GetNbTextures() const { return nb_textures; }

	void SetState(int i) {sprite_.setTexture(death_anim_.at(i)); state = i;}
	void SetPosition(sf::Vector2f pos) { sprite_.setPosition(pos); }
	void SetDelay(float d) { delay = d; }
	float GetDelay() const { return delay; }
	int GetState() const { return state; }
	bool IsFinished() const {return is_finished;}
	void End() { is_finished = true; }


protected:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif // DEATHANIM_H
