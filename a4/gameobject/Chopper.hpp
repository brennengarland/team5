#ifndef __CHOPPER_HPP__
#define __CHOPPER_HPP__

#include "GameObject.hpp"
#include "texture_utils.hpp"


class Chopper : public GameObject{
	public:
    //default constructor, with own image
	Chopper(const float xpos, const float ypos, const float xvel, const float yvel): GameObject("../assets/images/chopper-single.png", xpos, ypos, xvel, yvel)
        {
        }
    //defined file constructor
    Chopper(const char* x, const float xpos, const float ypos, const float xvel, const float yvel): GameObject(x, xpos, ypos, xvel, yvel)
        {
        }

    void update(const float dt) override;
    void render() override;

    private:

	
};
#endif

