#include "aliencomposite.h"
#include <iostream>

namespace si {


    /**
     * \brief: Instantiates a Bullet object
     * \param: bulletStartX, starting point for this bullet
     * \param: bulletStartY, starting point for this bullet
     */
    AlienComposite::AlienComposite(int alienCompositeStartX, int alienCompositeStartY)
    {

        this->setX(alienCompositeStartX);
        this->setY(alienCompositeStartY);

    }


    AlienComposite::AlienComposite(AlienBoss *alienBoss)
    {

        this->m_boss = alienBoss;

    }

    /**
     * \brief: Default constructor
     */
    AlienComposite::AlienComposite()
    {

        this->m_boss = nullptr;
    }


    /**
     * \brief: move
     */
    void AlienComposite::move()
    {

        for (auto& alien : this->m_alienComponents)
        {
            alien->move();
        }

        if (m_boss != nullptr)
        {

            m_boss->move();

        }
    }


    /**
     * \brief: speed up
     */
    void AlienComposite::speedUp()
    {

        for (auto& alien : this->m_alienComponents)
        {
            alien->speedUp();
        }

    }


    /**
     * \brief: add
     */
    void AlienComposite::add(Alien *alienComponent)
    {

        this->m_alienComponents.append(alienComponent);

    }


    /**
     * \brief: get boss
     */
    AlienBoss* AlienComposite::getBoss()
    {

        return this->m_boss;

    }

    void AlienComposite::removeBoss()
    {

        this->m_boss = nullptr;

    }

    /**
     * \brief: remove
     */
    void AlienComposite::remove(int idx)
    {

        this->m_alienComponents.remove(idx);

    }


    /**
     * \brief: Return the list of alien components
     */
    QVector<Alien *> AlienComposite::getList()
    {

        return this->m_alienComponents;

    }


} // end namespace si
