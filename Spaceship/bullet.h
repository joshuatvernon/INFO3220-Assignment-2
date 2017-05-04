#ifndef BULLET_H
#define BULLET_H

#include "gameelement.h"
#include "sharedmedia.h"
#include <QString>
#include <QPixmap>
#include <QSound>

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

        void setMedia(SharedMedia* media) { this->m_media = media; }
        QPixmap getImage() { return this->m_media->getImage(); }
        QSound * getSound() { return this->m_media->getSound(); }

    private:

        QString m_direction;
        QString m_bulletType;
        SharedMedia* m_media;

    };

} // end namespace si

#endif // BULLET_H
