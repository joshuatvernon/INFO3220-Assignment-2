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


    /**
     * \brief: Constructor for the composite alien object
     */
    AlienComposite::AlienComposite(AlienBoss *alienBoss)
    {

        this->m_boss = alienBoss;

    }

    /**
     * \brief: Default constructor for the composite alien object
     */
    AlienComposite::AlienComposite()
    {

        this->m_boss = nullptr;
    }


    /**
     * \brief: moves all the individual and composite children aliens
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
     * \brief: speeds up all the children aliens (currently doesn't speed up boss as it's not needed yet)
     */
    void AlienComposite::speedUp()
    {

        for (auto& alien : this->m_alienComponents)
        {

            alien->speedUp();

        }

    }


    /**
     * \brief: adds an alien to the composite
     */
    void AlienComposite::add(Alien *alienComponent)
    {

        this->m_alienComponents.append(alienComponent);

    }


    /**
     * \brief: gets the boss alien
     */
    AlienBoss* AlienComposite::getBoss()
    {

        return this->m_boss;

    }


    /**
     * \brief: Removes the boss alien
     */
    void AlienComposite::removeBoss()
    {

        this->m_boss = nullptr;

    }


    /**
     * \brief: removes an alien from the composite based on the index of that alien
     */
    void AlienComposite::remove(int idx)
    {

        this->m_alienComponents.remove(idx);

    }


    /**
     * \brief: Return the list of alien components and individual aliens
     */
    QVector<Alien *> AlienComposite::getList()
    {

        return this->m_alienComponents;

    }


} // end namespace si
