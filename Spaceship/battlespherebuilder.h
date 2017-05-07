#ifndef BATTLESPHEREBUILDER_H
#define BATTLESPHEREBUILDER_H

#include <string>

#include "battlesphere.h"
#include "defender.h"
#include "commandcentre.h"

namespace si {

    class BattlesphereBuilder
    {
    public:

        BattlesphereBuilder(){}

        void buildDefender(const Defender &d);

        void buildSwarm(const AlienComposite &s);

        void buildBulletParameters(int movementSpeed);

        void buildCommandCentre(const CommandCentre& commandCentre);

        si::BattleSphere* getBattlesphere();

    private:

        Defender m_defender;
        AlienComposite m_swarm;
        int m_bulletSpeed;
        CommandCentre m_commandCentre;

    };

} // end namespace si

#endif // BATTLESPHEREBUILDER_H
