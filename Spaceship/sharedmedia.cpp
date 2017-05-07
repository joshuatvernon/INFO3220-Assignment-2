#include "sharedmedia.h"


namespace si {

    /**
     * \brief: Constructs the shared media for an object
     */
    SharedMedia::SharedMedia(QPixmap image, QString stringPath, QString type, int speed) : m_sound(stringPath)
    {

        this->m_image = image;
        this->m_type = type;
        this->m_speed = speed;

    }


    /**
     * \brief: returns the sound item the shared media holds
     */
    QSound* SharedMedia::getSound()
    {

        return &(this->m_sound);

    }


    /**
     * \brief: Returns the image item the shared media holds
     */
    QPixmap SharedMedia::getImage()
    {

        return this->m_image;

    }


    /**
     * \brief: Returns what type of shared media this is stored as
     */
    QString SharedMedia::getType()
    {

        return this->m_type;

    }


    /**
     * \brief: returns the speed variable from within the shared media
     */
    int SharedMedia::getSpeed() {

        return this->m_speed;

    }


    /**
     * \brief: Sets the shared medias image variable
     */
    void SharedMedia::setImage(QPixmap image)
    {

        this->m_image = image;

    }


    /**
     * \brief: Sets the shared medias type variable
     */
    void SharedMedia::setType(QString type)
    {

        this->m_type = type;

    }


    /**
     * \brief: Sets the shared medias speed variable
     */
    void SharedMedia::setSpeed(int speed)
    {

        this->m_speed = speed;

    }


} // end namespace si
