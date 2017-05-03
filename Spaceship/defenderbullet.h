#ifndef DEFENDERBULLET_H
#define DEFENDERBULLET_H

#include "bullet.h"

namespace si {

    class DefenderBullet : public Bullet
    {
    public:

        DefenderBullet(int bulletStartX, int bulletStartY, QString bulletType);

        ~DefenderBullet(){}

        void updateY(int updateAmount) override;

    };

} // end namespace si

#endif // DEFENDERBULLET_H
