#include "GameObject.hpp"
#include "texture_utils.hpp"
#include "Game.hpp"

class Tank : public GameObject{
	Tank::Tank(const float xpos, const float ypos, const float xvel, const float yvel)
: xpos(xpos), ypos(ypos), xvel(xvel), yvel(yvel)
{
   texture = texture::load_texture("../assets/images/tank-big-down.png");
}
	
	
}
