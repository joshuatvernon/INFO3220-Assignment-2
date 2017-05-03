#include "defenderbullet.h"

namespace si {


    /**
     * \brief: Instantiates a Bullet object
     * \param: bulletStartX, starting point for this bullet
     * \param: bulletStartY, starting point for this bullet
     */
    DefenderBullet::DefenderBullet(int bulletStartX, int bulletStartY, QString bulletType) {
       this->setX(bulletStartX);
       this->setY(bulletStartY);
       this->setBulletType(bulletType);
    }

    /**
     * \brief: Determines the amount of y direction motion of the bullet
     *         in each frame.
     * \param: updateAmount, the number of pixels to move in the y direction
     */
    void DefenderBullet::updateY(int updateAmount)
    {
        this->setY(this->getY() - updateAmount);
    }

} // end namespace si
