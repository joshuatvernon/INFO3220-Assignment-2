#ifndef SHAREDMEDIA_H
#define SHAREDMEDIA_H

#include <QSound>
#include <QPixmap>

namespace si {

    class SharedMedia
    {
    public:

        explicit SharedMedia(QPixmap image, QString stringPath);

        SharedMedia(QPixmap image);

        ~SharedMedia() {}

        QSound* getSound();
        QPixmap getImage();
        void setImage(QPixmap image);

    private:

        QSound m_sound;
        QPixmap m_image;

    };

} // end namespace si

#endif // SHAREDMEDIA_H
