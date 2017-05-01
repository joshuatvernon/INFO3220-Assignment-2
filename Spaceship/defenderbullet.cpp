#include "defenderbullet.h"
#include <iostream>

namespace si {

    /**
     * \brief: Instantiates a GameElement object
     * \param: bulletStartX, starting point for this bullet
     * \param: bulletStartY, starting point for this bullet
     */
    DefenderBullet::DefenderBullet(int bulletStartX, int bulletStartY)
        : Bullet(bulletStartX, bulletStartY)
    {}

    /**
     * \brief: Determines the amount of y direction motion of the bullet
     *         in each frame.
     * \param: updateAmount, the number of pixels to move in the y direction
     */
    void DefenderBullet::updateY(int updateAmount)
    {
        this->setY(this->getY() - updateAmount);
        std::cout << "DEFENDER!" << std::endl;
    }

} // end namespace si
