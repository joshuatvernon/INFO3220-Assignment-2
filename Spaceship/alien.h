#ifndef ALIEN_H
#define ALIEN_H

#include "gameelement.h"
#include "swarmComponent.h"
#include "sharedmedia.h"
#include <QString>


namespace si {

    class Alien : public GameElement, public SwarmComponent
    {
    public:

        Alien();

        ~Alien(){}

        void move() override;

        void shoot();

    private:
        int var;
        int xSpeed;
        QString type;
        SharedMedia* m_media;

    };

} // end namespace si

#endif // ALIEN_H
