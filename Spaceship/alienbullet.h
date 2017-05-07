#ifndef ALIENBULLET_H
#define ALIENBULLET_H

#include "downbullet.h"

namespace si {

    class AlienBullet : public DownBullet
    {
    public:

        AlienBullet(int bulletStartX, int bulletStartY, QString bulletType, SharedMedia *media);

        ~AlienBullet(){}

        void updateDownY(int updateAmount);

    };

} // end namespace si

#endif // ALIENBULLET_H
