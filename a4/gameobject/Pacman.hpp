#ifndef __PACMAN_HPP__
#define __PACMAN_HPP__

#include "GameObject.hpp"
#include "texture_utils.hpp"


class Pacman : public GameObject{
	public:
    //default constructor, with own image
	// Pacman(const float xpos, const float ypos, const float xvel, const float yvel): GameObject("../assets/images/pacman/pacman_32x32.png", xpos, ypos, xvel, yvel)
    //     {
    //     }
	Pacman(const char* filename_img,
                       const float xpos, const float ypos,
                       const float xvel, const float yvel): xpos(xpos), ypos(ypos), xvel(xvel), yvel(yvel)
{
   texture = texture::load_texture(filename_img);
}
    //defined file constructor
    Pacman(const char* x, const float xpos, const float ypos, const float xvel, const float yvel): GameObject(x, xpos, ypos, xvel, yvel)
        {
        }

    ~Pacman();
    //define own behavior
    virtual void update(const float dt) override;
    virtual void render() override;

    private:


	
};
#endif

