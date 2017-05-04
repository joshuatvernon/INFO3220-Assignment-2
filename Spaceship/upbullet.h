#ifndef UPBULLET_H
#define UPBULLET_H

#include "bullet.h"
#include <QString>

namespace si {

    class UpBullet : public Bullet
    {
    public:

        virtual void updateY(int updateAmount) = 0;

    };

} // end namespace si

#endif // UPBULLET_H
