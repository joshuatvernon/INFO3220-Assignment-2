#include "alienboss.h"
#include <iostream>

namespace si {


    /**
     * \brief: Instantiates a Bullet object
     * \param: bulletStartX, starting point for this bullet
     * \param: bulletStartY, starting point for this bullet
     * \param: media, the images and sounds for the object
     */
    AlienBoss::AlienBoss(int alienStartX, int alienStartY, SharedMedia *media)
    {

        this->setX(alienStartX);
        this->setY(alienStartY);
        this->m_media = media;
        this->m_direction = 1;
        this->m_moveStep = 0;
        this->m_xSpeed = 3;
        this->m_ySpeed = 1;

    }

    /**
     * \brief: Deconstruct the boss alien object by deleting shared media
     */
    AlienBoss::~AlienBoss()
    {

        delete m_media;

    }


    /**
     * \brief: moves the boss alien in the direction of the defender object
     */
    void AlienBoss::move()
    {

        this->setX(this->getX() + (this->m_direction * this->m_xSpeed));

    }


    /**
     * \brief: sets the direction in which the boss alien needs to move so as to
     * follow the defender
     */
    void AlienBoss::setDirection(int defenderLocation)
    {

        if (this->getX() < defenderLocation) {
            this->m_direction = 1;
        } else {
            this->m_direction = -1;
        }

    }


    /**
     * \brief: Speeds up the descent of the boss alien
     */
    void AlienBoss::speedUp()
    {

        this->m_ySpeed++;

    }


} // end namespace si
