#include "GameObject.hpp"
#include "texture_utils.hpp"
#include "Game.hpp"

class Chopper : public GameObject{
	public:
	Chopper(const float xpos, const float ypos, const float xvel, const float yvel): GameObject("../assets/images/chopper-single.png", xpos, ypos, xvel, yvel)
        {
        }
    Chopper(const char* x, const float xpos, const float ypos, const float xvel, const float yvel): GameObject(x, xpos, ypos, xvel, yvel)
        {
        }

    void update(const float dt);
    void render();

    private:

	
};