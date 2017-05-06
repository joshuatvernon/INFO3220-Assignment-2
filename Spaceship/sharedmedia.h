#ifndef SHAREDMEDIA_H
#define SHAREDMEDIA_H

#include <QSound>
#include <QPixmap>

namespace si {

    class SharedMedia
    {
    public:

        explicit SharedMedia(QPixmap image, QString stringPath, QString type);

        SharedMedia(QPixmap image);

        ~SharedMedia() {}

        QSound* getSound();
        QPixmap getImage();
        QString getType();
        void setImage(QPixmap image);
        void setType(QString type);

    private:

        QSound m_sound;
        QPixmap m_image;
        QString m_type;

    };

} // end namespace si

#endif // SHAREDMEDIA_H
