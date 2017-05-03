#ifndef ALIENBULLETADAPTER_H
#define ALIENBULLETADAPTER_H

#include "bullet.h"
#include "alienbullet.h"
#include <QString>

namespace si {

    class AlienBulletAdapter : public Bullet
    {
    public:

        AlienBullet *theAlienBullet;

        AlienBulletAdapter(AlienBullet *newAlienBullet);
        ~AlienBulletAdapter(){}

        void updateY(int updateAmount) override;

    private:

        QString direction;

    };

} // end namespace si

#endif // ALIENBULLETADAPTER_H
