#ifndef GAMEELEMENT_H
#define GAMEELEMENT_H

namespace si {
    class GameElement
    {
    public:

        virtual int getX() { return m_xPos; }
        virtual int getY() { return m_yPos; }

        virtual void setX(int x) { m_xPos = x; }
        virtual void setY(int y) { m_yPos = y; }

    private:

        int m_xPos;
        int m_yPos;

    };
} // end namespace si

#endif // GAMEELEMENT_H
