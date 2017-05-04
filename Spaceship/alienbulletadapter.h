#ifndef ALIENBULLETADAPTER_H
#define ALIENBULLETADAPTER_H

#include "upbullet.h"
#include "downbullet.h"
#include <QString>

namespace si {

    class AlienBulletAdapter : public UpBullet
    {
    public:

        DownBullet *theAlienBullet;

        AlienBulletAdapter(DownBullet *newAlienBullet);
        ~AlienBulletAdapter(){}

        void updateY(int updateAmount) override;

    private:

        QString direction;

    };

} // end namespace si

#endif // ALIENBULLETADAPTER_H
