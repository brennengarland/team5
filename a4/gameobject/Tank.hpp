#ifndef __TANK_HPP__
#define __TANK_HPP__

#include "GameObject.hpp"
#include "texture_utils.hpp"


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

    virtual void update(const float dt) override;
    virtual void render() override;

    private:

	
};
#endif

