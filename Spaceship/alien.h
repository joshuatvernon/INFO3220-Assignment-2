#ifndef ALIEN_H
#define ALIEN_H

#include "gameelement.h"
#include "aliencomponent.h"
#include "sharedmedia.h"
#include <QString>


namespace si {

    class Alien : public GameElement, public AlienComponent
    {
    public:

        Alien(int alienStartX, int alienStartY, SharedMedia *media);

        ~Alien();

        void move() override;
        void speedUp() override;

        void setTraj(QStringList traj);

        void setMedia(SharedMedia* media) { this->m_media = media; }
        QPixmap getImage() { return this->m_media->getImage(); }
        QSound *getSound() { return this->m_media->getSound(); }
        QString getType() { return this->m_media->getType(); }

    private:

        SharedMedia* m_media;
        QStringList m_traj;
        int m_moveStep;
        int m_xSpeed;
        int m_ySpeed;

    };

} // end namespace si

#endif // ALIEN_H
