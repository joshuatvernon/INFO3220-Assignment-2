#include "sharedmedia.h"


namespace si {


    SharedMedia::SharedMedia(QPixmap image, QString stringPath, QString type, int speed) : m_sound(stringPath)
    {

        this->m_image = image;
        this->m_type = type;
        this->m_speed = speed;

    }


    QSound* SharedMedia::getSound()
    {

        return &(this->m_sound);

    }


    QPixmap SharedMedia::getImage()
    {

        return this->m_image;

    }


    QString SharedMedia::getType()
    {

        return this->m_type;

    }


    int SharedMedia::getSpeed() {

        return this->m_speed;

    }


    void SharedMedia::setImage(QPixmap image)
    {

        this->m_image = image;

    }


    void SharedMedia::setType(QString type)
    {

        this->m_type = type;

    }


    void SharedMedia::setSpeed(int speed)
    {

        this->m_speed = speed;

    }


} // end namespace si
