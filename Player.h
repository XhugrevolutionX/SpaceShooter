#ifndef PLAYER_H
#define PLAYER_H
#include "Ship.h"

class player : public ship
{

private:
	std::string name;

public:

	void set_name(std::string name_) { name = name_; }
	std::string get_name() { return name; }

	void initialize();
};






#endif
