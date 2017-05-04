#ifndef DEFENDERBULLET_H
#define DEFENDERBULLET_H

#include "upbullet.h"

namespace si {

    class DefenderBullet : public UpBullet
    {
    public:

        DefenderBullet(int bulletStartX, int bulletStartY, QString bulletType, SharedMedia *media);

        ~DefenderBullet(){}

        void updateY(int updateAmount);

    };

} // end namespace si

#endif // DEFENDERBULLET_H
