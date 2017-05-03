#include "alienbulletadapter.h"
#include <iostream>

namespace si {

    /**
     * \brief: initalises the alienBullet member variable with given alienBullet
     * \param: newAlienBullet, a pointer to an alien bullet object
     */
    AlienBulletAdapter::AlienBulletAdapter(AlienBullet *newAlienBullet)
    {
        this->theAlienBullet = newAlienBullet;
        this->setX(newAlienBullet->getX());
        this->setY(newAlienBullet->getY());
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
