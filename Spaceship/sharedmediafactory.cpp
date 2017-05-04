#include "sharedmediafactory.h"

namespace si {

    SharedMediaFactory::SharedMediaFactory()
    {}

    SharedMedia* SharedMediaFactory::getSharedMedia(QString name, QPixmap image, QString soundPath)
    {
        if (sharedMediaMap.contains(name)) {
            // SharedMedia is already created -- return instance.
            return sharedMediaMap.value(name);
        } else {
            // SharedMedia isn't created yet -- create new instance to return
            SharedMedia *newSharedMedia = new SharedMedia(image, soundPath);
            sharedMediaMap.insert(name, newSharedMedia);
            return newSharedMedia;
        }
    }

    SharedMedia* SharedMediaFactory::getSharedMedia(QString name, QPixmap image)
    {
        if (sharedMediaMap.contains(name)) {
            // SharedMedia is already created -- return instance.
            return sharedMediaMap.value(name);
        } else {
            // SharedMedia isn't created yet -- create new instance to return
            SharedMedia *newSharedMedia = new SharedMedia(image);
            sharedMediaMap.insert(name, newSharedMedia);
            return newSharedMedia;
        }
    }

} // end namespace si
