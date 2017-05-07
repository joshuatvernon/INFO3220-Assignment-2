#ifndef ALIENCOMPONENT_H
#define ALIENCOMPONENT_H

#include "gameelement.h"

namespace si {

    class AlienComponent
    {
    public:

        virtual void move() = 0;
        virtual void speedUp() = 0;

    };

} // end namespace si

#endif // ALIENCOMPONENT_H
