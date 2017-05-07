#include "sharedmediafactory.h"

namespace si {

    /**
     * \brief: Default constructor for the shared media factory
     */
    SharedMediaFactory::SharedMediaFactory()
    {}

    /**
     * \brief: Return an instance of shared media with the arguments as data,
     * ensure there's only one instance of each type
     */
    SharedMedia* SharedMediaFactory::getSharedMedia(QString name, QPixmap image, QString soundPath, int speed)
    {
        if (sharedMediaMap.contains(name)) {
            // SharedMedia is already created -- return instance.
            return sharedMediaMap.value(name);
        } else {
            // SharedMedia isn't created yet -- create new instance to return
            SharedMedia *newSharedMedia = new SharedMedia(image, soundPath, name, speed);
            sharedMediaMap.insert(name, newSharedMedia);
            return newSharedMedia;
        }
    }


} // end namespace si
