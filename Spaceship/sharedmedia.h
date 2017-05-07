#ifndef SHAREDMEDIA_H
#define SHAREDMEDIA_H

#include <QSound>
#include <QPixmap>

namespace si {

    class SharedMedia
    {
    public:

        explicit SharedMedia(QPixmap image, QString stringPath, QString type, int speed);

        ~SharedMedia() {}

        QSound* getSound();
        QPixmap getImage();
        QString getType();
        int getSpeed();
        void setImage(QPixmap image);
        void setType(QString type);
        void setSpeed(int speed);

    private:

        QSound m_sound;
        QPixmap m_image;
        QString m_type;
        int m_speed;

    };

} // end namespace si

#endif // SHAREDMEDIA_H
