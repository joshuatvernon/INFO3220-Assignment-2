#ifndef BATTLESPHERE_H
#define BATTLESPHERE_H

#include <QDialog>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QApplication>
#include <QPushButton>

#include <vector>

#include "commandcentre.h"
#include "defender.h"
#include "iofile.h"
#include "bullet.h"
#include "alienbulletadapter.h"
#include "defenderbullet.h"
#include "star.h"

namespace si {

    class BattleSphere : public QDialog
    {
    public:

        BattleSphere(QWidget *parent, Defender d, int bulletSpeed, CommandCentre cc);
        ~BattleSphere();

    private:

        Q_OBJECT

        // Defender images
        QPixmap m_defenderImg;

        QPixmap m_bulletImg;

        // Alien bullet image
        QPixmap m_alienBulletImg;

        // Defender bullet images
        QPixmap m_tinyDefenderBulletImg;
        QPixmap m_normalDefenderBulletImg;
        QPixmap m_largeDefenderBulletImg;
        QPixmap m_giantDefenderBulletImg;

        QPixmap m_starImg;
        QTimer* m_timer;
        QPushButton *m_button;

        QString m_size;

        std::vector<DefenderBullet> m_bullets;

        std::vector<Star> m_stars;

        int m_numStars = 30;

        int m_bulletSpeed;

        int m_screenWidth = 600;
        int m_screenHeight = 400;

        CommandCentre m_commandCentre;

        Defender m_defender;

    protected:

        void paintEvent(QPaintEvent *event);

    public slots:

        void nextFrame();
        void screenshot();

    };

} // end namespace si

#endif // BATTLESPHERE_H
