#include "GameObject.hpp"
#include "texture_utils.hpp"
#include "Game.hpp"

class Pacman : public GameObject{
	public:
	Pacman(const float xpos, const float ypos, const float xvel, const float yvel): GameObject("../assets/images/pacman/pacman_32x32.png", xpos, ypos, xvel, yvel)
        {
        }
    Pacman(const char* x, const float xpos, const float ypos, const float xvel, const float yvel): GameObject(x, xpos, ypos, xvel, yvel)
        {
        }

    void update(const float dt);
    void render();

    private:

	
};