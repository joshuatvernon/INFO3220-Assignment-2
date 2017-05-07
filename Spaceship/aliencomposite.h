#ifndef ALIENCOMPOSITE_H
#define ALIENCOMPOSITE_H

#include "aliencomponent.h"
#include "alien.h"
#include "alienboss.h"
#include <QVector>

namespace si {

    class AlienComposite : public GameElement, public AlienComponent
    {
    public:

        AlienComposite(int alienCompositeStartX, int alienCompositeStartY);
        AlienComposite(AlienBoss *alienBoss);
        AlienComposite();

        ~AlienComposite(){};

        void move() override;

        void speedUp() override;

        void add(Alien *alienComponent);

        AlienBoss* getBoss();

        void removeBoss();

        void remove(int idx);

        QVector<Alien *> getList();

    private:

        QVector<Alien *> m_alienComponents;
        AlienBoss *m_boss;

    };

} // end namespace si

#endif // ALIENCOMPOSITE_H
