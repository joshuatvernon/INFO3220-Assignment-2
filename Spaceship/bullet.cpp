#include "bullet.h"

namespace si {

    /**
     * \brief: Instantiates a GameElement object
     * \param: bulletStartX, starting point for this bullet
     * \param: bulletStartY, starting point for this bullet
     */
    Bullet::Bullet(int bulletStartX, int bulletStartY)
        : GameElement(bulletStartX, bulletStartY)
    {}

    /**
     * \brief: Determines the amount of x direction motion of the bullet
     *         in each frame.
     * \param: updateAmount, the number of pixels to move in the x direction
     */
    void Bullet::updateLeftX(int updateAmount)
    {
        // Nothing, unless we want diagonal trajectory bullets
        this->setX(this->getX() - updateAmount);
    }

    /**
     * \brief: Determines the amount of x direction motion of the bullet
     *         in each frame.
     * \param: updateAmount, the number of pixels to move in the x direction
     */
    void Bullet::updateRightX(int updateAmount)
    {
        // Nothing, unless we want diagonal trajectory bullets
        this->setX(this->getX() + updateAmount);
    }

    /**
     * \brief: Determines the amount of y direction motion of the bullet
     *         in each frame.
     * \param: updateAmount, the number of pixels to move in the y direction
     */
    void Bullet::updateY(int updateAmount)
    {
        this->setY(this->getY() - updateAmount);
    }

    /**
     * \brief: Is a getter for the direction that the bullet should be
     *         fired in.
     * \return: the direction the bullet is being fired in.
     */
    QString Bullet::getDirection()
    {
        return this->direction;
    }

    /**
     * \brief: Sets the member variable to the direction the bullet should
     *         be fired in.
     * \param: the direction the bullet is being fired in.
     */
    void Bullet::setDirection(QString direction)
    {
        this->direction = direction;
    }

} // end namespace si
