#ifndef ALIENBULLET_H
#define ALIENBULLET_H

#include "bullet.h"

namespace si {

    class AlienBullet : public Bullet
    {
    public:

        AlienBullet(int bulletStartX, int bulletStartY, QString bulletType);

        ~AlienBullet(){}

        void updateY(int updateAmount) override;

    };

} // end namespace si

#endif // ALIENBULLET_H
