#ifndef ALIENBOSS_H
#define ALIENBOSS_H

#include "gameelement.h"
#include "aliencomponent.h"
#include "sharedmedia.h"
#include <QString>


namespace si {

    class AlienBoss : public GameElement, public AlienComponent
    {
    public:

        AlienBoss(int alienStartX, int alienStartY, SharedMedia *media);

        ~AlienBoss();

        void move() override;
        void speedUp() override;

        void setDirection(int defenderLocation);

        void setMedia(SharedMedia* media) { this->m_media = media; }
        QPixmap getImage() { return this->m_media->getImage(); }
        QSound * getSound() { return this->m_media->getSound(); }
        QString getType() { return this->m_media->getType(); }

    private:

        SharedMedia* m_media;
        QStringList m_traj;
        int m_moveStep;
        int m_xSpeed;
        int m_ySpeed;
        int m_direction;

    };

} // end namespace si

#endif // ALIENBOSS_H
