#include "sharedmedia.h"

namespace si {

    SharedMedia::SharedMedia(QPixmap image, QString stringPath) : m_sound(stringPath)
    {
        this->m_image = image;
    }

    SharedMedia::SharedMedia(QPixmap image) : m_sound(nullptr)
    {
        this->m_image = image;
    }

    QSound* SharedMedia::getSound()
    {
        return &(this->m_sound);
    }

    QPixmap SharedMedia::getImage()
    {
        return this->m_image;
    }

    void SharedMedia::setImage(QPixmap image)
    {
        this->m_image = image;
    }

} // end namespace si
