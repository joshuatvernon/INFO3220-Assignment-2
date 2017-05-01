#ifndef BULLET_H
#define BULLET_H

#include "gameelement.h"
#include <QString>

namespace si {

    class Bullet : public GameElement
    {
    public:
        Bullet(int bulletStartX, int bulletStartY);

        virtual ~Bullet(){}

        virtual void updateLeftX(int updateAmount) { setX(getX() - updateAmount); }
        virtual void updateRightX(int updateAmount) { setX(getX() + updateAmount); }

        virtual QString getDirection() { return direction; }
        virtual void setDirection(QString d) { direction = d; }

        virtual void updateY(int updateAmount);
    private:
        QString direction;
    };

} // end namespace si

#endif // BULLET_H
