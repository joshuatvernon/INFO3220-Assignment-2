#include "alienbullet.h"
#include <iostream>

namespace si {


    /**
     * \brief: Instantiates a Bullet object
     * \param: bulletStartX, starting point for this bullet
     * \param: bulletStartY, starting point for this bullet
     */
    AlienBullet::AlienBullet(int bulletStartX, int bulletStartY, QString bulletType, SharedMedia *media)
    {

        this->setX(bulletStartX);
        this->setY(bulletStartY);
        this->setBulletType(bulletType);
        this->setMedia(media);

    }


    /**
     * \brief: Determines the amount of y direction motion of the bullet
     *         in each frame.
     * \param: updateAmount, the number of pixels to move in the y direction
     */
    void AlienBullet::updateDownY(int updateAmount)
    {

        this->setY(this->getY() + updateAmount);

    }

} // end namespace si
