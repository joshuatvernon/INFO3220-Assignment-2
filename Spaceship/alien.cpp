#include "alien.h"
#include <iostream>

namespace si {


    /**
     * \brief: Instantiates a Bullet object
     * \param: bulletStartX, starting point for this bullet
     * \param: bulletStartY, starting point for this bullet
     */
    Alien::Alien(int alienStartX, int alienStartY, SharedMedia *media)
    {

        this->setX(alienStartX);
        this->setY(alienStartY);
        this->m_media = media;
        this->m_moveStep = 0;
        this->m_xSpeed = 5;
        this->m_ySpeed = 1;

    }

    /**
     * \brief: Deconstruct alien object by deleting shared media
     */
    Alien::~Alien()
    {

        delete m_media;

    }


    /**
     * \brief: moves the individual alien
     */
    void Alien::move()
    {

        if (this->m_traj[this->m_moveStep] == 'L')
        {
            this->setX(this->getX() - this->m_xSpeed);

        } else {

            this->setX(this->getX() + this->m_xSpeed);

        }

        this->m_moveStep++;

        if (m_moveStep == this->m_traj.size()) {
            this->m_moveStep = 0;
            this->setY(this->getY() + this->m_ySpeed);
        }

    }


    /**
     * \brief: Sets the trajectory for the individual alien
     */
    void Alien::setTraj(QStringList traj)
    {

        this->m_traj = traj;

    }


    /**
     * \brief: Speeds up the descent of the individual alien
     */
    void Alien::speedUp()
    {

        this->m_ySpeed++;

    }


} // end namespace si
