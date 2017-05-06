#ifndef SWARMCOMPONENT_H
#define SWARMCOMPONENT_H

namespace si {

    class SwarmComponent
    {
    public:

        SwarmComponent();

        ~SwarmComponent(){}

        virtual void move() = 0;

    };

} // end namespace si

#endif // SWARMCOMPONENT_H
