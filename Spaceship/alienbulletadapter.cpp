#include "alienbulletadapter.h"
#include <iostream>

namespace si {

    /**
     * \brief: initalises the alienBullet member variable with given alienBullet
     * \param: newAlienBullet, a pointer to an alien bullet object
     */
    AlienBulletAdapter::AlienBulletAdapter(AlienBullet *newAlienBullet)
        : Bullet(newAlienBullet->getX(), newAlienBullet->getY())
    {
        this->theAlienBullet = newAlienBullet;
    }

    /**
     * \brief: Determines the amount of y direction motion of the bullet
     *         in each frame.
     * \param: updateAmount, the number of pixels to move in the y direction
     */
    void AlienBulletAdapter::updateY(int updateAmount)
    {
        theAlienBullet->updateY(updateAmount);
        std::cout << "made it here" << std::endl;
    }

} // end namespace si
