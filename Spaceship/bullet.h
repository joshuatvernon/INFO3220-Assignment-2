#ifndef BULLET_H
#define BULLET_H

#include "gameelement.h"
#include <QString>

namespace si {

    class Bullet : public GameElement
    {
    public:

        void updateLeftX(int updateAmount) { setX(getX() - updateAmount); }
        void updateRightX(int updateAmount) { setX(getX() + updateAmount); }

        QString getDirection() { return m_direction; }
        void setDirection(QString d) { m_direction = d; }

        QString getBulletType() { return this->m_bulletType; }
        void setBulletType(QString bulletType) { this->m_bulletType = bulletType; }
        virtual void updateY(int updateAmount) = 0;

    private:

        QString m_direction;
        QString m_bulletType;

    };

} // end namespace si

#endif // BULLET_H
