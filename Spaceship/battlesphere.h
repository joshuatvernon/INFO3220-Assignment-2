#ifndef BATTLESPHERE_H
#define BATTLESPHERE_H

#include <QDialog>
#include <QPainter>
#include <QPixmap>
#include <QTimer>
#include <QApplication>
#include <QPushButton>
#include <QFont>
#include <QKeyEvent>

#include <vector>

#include "commandcentre.h"
#include "defender.h"
#include "iofile.h"
#include "bullet.h"
#include "alienbulletadapter.h"
#include "defenderbullet.h"
#include "alienbullet.h"
#include "star.h"
#include "sharedmediafactory.h"

namespace si {

    class BattleSphere : public QDialog
    {
    public:

        BattleSphere(QWidget *parent, Defender d, int bulletSpeed, CommandCentre cc, AlienComposite s);
        ~BattleSphere();

    private:

        Q_OBJECT

        // Defender images
        QPixmap m_defenderImg;

        QPixmap m_bulletImg;

        // Alien Bullet Media
        QPixmap m_tinyAlienBulletImg;
        QPixmap m_normalAlienBulletImg;
        QPixmap m_largeAlienBulletImg;
        QString m_tinyAlienSoundPath;
        QString m_normalAlienSoundPath;
        QString m_largeAlienSoundPath;
        QString m_bossAlienSoundPath;

        // Defender bullet images
        QPixmap m_tinyDefenderBulletImg;
        QPixmap m_normalDefenderBulletImg;
        QPixmap m_largeDefenderBulletImg;
        QPixmap m_giantDefenderBulletImg;
        QPixmap m_bossAlienBulletImg;

        QString m_sharedSoundPath;

        SharedMedia *m_defenderBulletSharedMedia;
        SharedMedia *m_tinyAlienBulletSharedMedia;
        SharedMedia *m_normalAlienBulletSharedMedia;
        SharedMedia *m_largeAlienBulletSharedMedia;
        SharedMedia *m_bossAlienBulletSharedMedia;

        QSound m_collisonSound;

        QPixmap m_starImg;
        QTimer* m_timer;
        QPushButton *m_button;

        QString m_size;

        std::vector<DefenderBullet> m_bullets;
        std::vector<AlienBullet> m_alienbullets;



        std::vector<Star> m_stars;

        int m_numStars = 30;

        int m_bulletSpeed;

        int m_screenWidth = 800;
        int m_screenHeight = 600;

        int m_lives;

        CommandCentre m_commandCentre;

        Defender m_defender;
        AlienComposite m_swarm;
        int m_numberOfAliens;


    protected:

        void paintEvent(QPaintEvent *event);
        int m_move;
        int m_score;

    public slots:

        void nextFrame();
        void screenshot();
        void handleCollisons(QVector<Alien *> aliens);
        static bool hasCollision(Alien *alien, DefenderBullet bullet);
        void aliensFire(QVector<Alien *> aliens);
        void isDefenderDead();
        bool isDefenderShot(AlienBullet bullet);
        void updateScore(QString alienShot);
        void paintScore();
        void gameOver();
        void keyPressEvent(QKeyEvent *event);
        void bossAlienFire();
        bool bossCollision(AlienBoss *bossAlien, DefenderBullet bullet);
        bool isDefenderHitByAlien(Alien *alien);

    };

} // end namespace si

#endif // BATTLESPHERE_H
