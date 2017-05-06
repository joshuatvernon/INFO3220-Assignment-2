#ifndef SWARMCOMPOSITE_H
#define SWARMCOMPOSITE_H

#include "swarmComponent.h"

namespace si {

    class SwarmComposite : public SwarmComponent
    {
    public:

        SwarmComposite();

        ~SwarmComposite(){}

        void move() override;

        void add();

        void remove();

        int getList();

    };

} // end namespace si

#endif // SWARMCOMPOSITE_H
