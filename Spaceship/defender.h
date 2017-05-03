#ifndef DEFENDER_H
#define DEFENDER_H

#include <QString>

#include "gameelement.h"

namespace si {

    class Defender : public GameElement
    {
    public:

        Defender(int xPos, int yPos, QString m_scale, int speed);
        Defender();

        ~Defender(){}

        QString getScale() const;
        int getSpeed() const;

        void setScale(QString scale);
        void setSpeed(int speed);

    private:

        QString m_scale;
        int m_speed = 10;

    };

} // end namespace si

#endif // DEFENDER_H
