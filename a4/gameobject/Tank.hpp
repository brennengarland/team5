#include "GameObject.hpp"
#include "texture_utils.hpp"
#include "Game.hpp"

class Tank : public GameObject{
	public:
    //default constructor, with own image
	Tank(const float xpos, const float ypos, const float xvel, const float yvel): GameObject("../assets/images/tank-big-down.png", xpos, ypos, xvel, yvel)
        {
        }
    //defined file constructor
    Tank(const char* x, const float xpos, const float ypos, const float xvel, const float yvel): GameObject(x, xpos, ypos, xvel, yvel)
        {
        }

    void update(const float dt);
    void render();

    private:

	
};