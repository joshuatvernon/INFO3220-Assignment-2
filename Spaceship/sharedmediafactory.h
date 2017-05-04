#ifndef SHAREDMEDIAFACTORY_H
#define SHAREDMEDIAFACTORY_H

#include <QSound>
#include <QPixmap>
#include <QHash>
#include "sharedmedia.h"

namespace si {

    class SharedMediaFactory
    {
    public:

        SharedMediaFactory();

        ~SharedMediaFactory() {}

        SharedMedia* getSharedMedia(QString name, QPixmap image, QString soundPath);

        SharedMedia* getSharedMedia(QString name, QPixmap image);

    private:

        QHash<QString, SharedMedia*> sharedMediaMap;

    };

} // end namespace si

#endif // SHAREDMEDIAFACTORY_H
