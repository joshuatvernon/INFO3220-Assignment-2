#include "alienbulletadapter.h"

namespace si {

    /**
     * \brief: initalises the alienBullet member variable with given alienBullet
     * \param: newAlienBullet, a pointer to an alien bullet object
     */
    AlienBulletAdapter::AlienBulletAdapter(DownBullet *newAlienBullet)
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
        theAlienBullet->updateDownY(updateAmount);
    }

} // end namespace si
