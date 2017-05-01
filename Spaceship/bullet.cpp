#include "bullet.h"
#include <iostream>

namespace si {

    /**
     * \brief: Instantiates a GameElement object
     * \param: bulletStartX, starting point for this bullet
     * \param: bulletStartY, starting point for this bullet
     */
    Bullet::Bullet(int bulletStartX, int bulletStartY)
        : GameElement(bulletStartX, bulletStartY)
    {}

} // end namespace si
