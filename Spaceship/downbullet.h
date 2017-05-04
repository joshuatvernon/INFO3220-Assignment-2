#ifndef DOWNBULLET_H
#define DOWNBULLET_H

#include "bullet.h"
#include <QString>

namespace si {

    class DownBullet : public Bullet
    {
    public:

        virtual void updateDownY(int updateAmount) = 0;

    };

} // end namespace si

#endif // DOWNBULLET_H
