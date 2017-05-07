#include "battlespherebuilder.h"

namespace si {


    /**
     * \brief: Constructs the player itself
     * \param: defender, an instance of a player
     */
    void BattlesphereBuilder::buildDefender(const Defender& d)
    {

        m_defender = d;

    }


    /**
     * \brief: Constructs the players enemy alien swarm
     * \param: defender, an instance of the enemey aliens
     */
    void BattlesphereBuilder::buildSwarm(const AlienComposite& s)
    {

        m_swarm = s;

    }


    /**
     * \brief: Sets number of pixels bullet should move in one frame
     * \param: movementSpeed, number of pixels for bullet to travel in one frame
     */
    void BattlesphereBuilder::buildBulletParameters(int movementSpeed)
    {
        m_bulletSpeed = movementSpeed;
    }

    /**
     * \brief: Builds the user interface buffer (an IOFile in this case
     *         but could be used to store events entered on keyboard).
     * \param: commandCentre
     */
    void BattlesphereBuilder::buildCommandCentre(const CommandCentre& commandCentre)
    {
        m_commandCentre = commandCentre;
    }

    /**
     * \brief: Returns a game instance from our builder
     * \result: an instance of the BattleSphere game
     */
    BattleSphere* BattlesphereBuilder::getBattlesphere()
    {
        si::BattleSphere* battlesphere = new si::BattleSphere(nullptr, m_defender, m_bulletSpeed, m_commandCentre, m_swarm);
        return battlesphere;
    }

} // end namespace si

