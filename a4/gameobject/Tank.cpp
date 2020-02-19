#include "GameObject.hpp"
#include "texture_utils.hpp"
#include "Game.hpp"

class Tank : public GameObject{
	public:
	Tank(const char* x, const float xpos, const float ypos, const float xvel, const float yvel)
: GameObject("../assets/images/tank-big-down.png", xpos, ypos, xvel, yvel)
{
	
}
	
	
};
