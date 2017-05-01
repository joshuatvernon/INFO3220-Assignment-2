#ifndef BULLET_H
#define BULLET_H

#include "gameelement.h"
#include <QString>

namespace si {

    class Bullet : public GameElement
    {
    public:
        Bullet(int bulletStartX, int bulletStartY);

        void updateLeftX(int updateAmount);
        void updateRightX(int updateAmount);
        void updateY(int updateAmount);
        QString getDirection();
        void setDirection(QString direction);
    private:
        QString direction;
    };

} // end namespace si

#endif // BULLET_H
