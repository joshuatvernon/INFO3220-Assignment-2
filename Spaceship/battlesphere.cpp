#include "battlesphere.h"

#include <random>

namespace si {

    /**
     * \brief: Constructs BattleSphere game using the provided defender
     * \param: parent, not used here
     * \param: d, defender describing where the player position is initially
     * \param: bulletSpeed, how many pixels to move bullet in one frame
     * \param: commandCentre, stores buffer of user inputs (just file inputs initially)
     * \result: the person
     */
    BattleSphere::BattleSphere(QWidget *parent, Defender d, int bulletSpeed, CommandCentre cc)
        : QDialog(parent),
          m_bulletSpeed(bulletSpeed),
          m_commandCentre(cc),
          m_defender(d)
    {
        for (int i=0; i<m_numStars; ++i) {
            int randX = rand() % m_screenWidth;
            int randY = rand() % m_screenHeight;

            float randStartOpacity = ((double) rand() / (RAND_MAX)) + 1;
            Star curStar(randX, randY);
            curStar.setOpacity(randStartOpacity);
            m_stars.push_back(curStar);
        }

        m_size = d.getScale();

        m_alienBulletImg.load(":/images/pokeball.png");

        m_starImg.load(":/images/star.png");

        m_starImg = m_starImg.scaledToWidth(5);

        // Set the defender and defender bullet images
        if (m_size == "tiny") {
            m_defenderImg.load(":/images/charmander.png");
            m_defenderImg = m_defenderImg.scaledToWidth(50);
            m_bulletImg.load(":/images/tiny-flame.png");
            m_sharedSoundPath = ":/sounds/charmander.wav";
        } else if (m_size == "normal") {
            m_defenderImg.load(":/images/charmeleon.png");
            m_defenderImg = m_defenderImg.scaledToWidth(70);
            m_bulletImg.load(":/images/normal-flame.png");
            m_sharedSoundPath = ":/sounds/charmeleon.wav";
        } else if (m_size == "large") {
            m_defenderImg.load(":/images/charizard.png");
            m_defenderImg = m_defenderImg.scaledToWidth(100);
            m_bulletImg.load(":/images/large-flame.png");
            m_sharedSoundPath = ":/sounds/charizard.wav";
        } else if (m_size == "giant") {
            m_defenderImg.load(":/images/mega-charizard.png");
            m_defenderImg = m_defenderImg.scaledToWidth(150);
            m_bulletImg.load(":/images/giant-flame.png");
            m_sharedSoundPath = ":/sounds/mega-charizard.wav";
        }

        SharedMediaFactory* sharedMediaFactory = new SharedMediaFactory();
        m_defenderBulletSharedMedia = sharedMediaFactory->getSharedMedia("defenderBullet", m_bulletImg, m_sharedSoundPath);

        m_defender.setY(m_screenHeight - m_defenderImg.height());

        setStyleSheet("background-color: #000000;");
        this->resize(m_screenWidth, m_screenHeight);
        update();

        // Create the button, make "this" the parent
        m_button = new QPushButton("Save Screenshot!", this);
        // set size and location of the button
        m_button->setGeometry(QRect(QPoint(0, 0),
        QSize(150, 50)));
        m_button->setStyleSheet("background-color: #FFFFFF;");

        m_timer = new QTimer(this);
        connect(m_timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
        connect(m_button, SIGNAL(released()), this, SLOT(screenshot()));
        m_timer->start(50);
    }

    /**
     * \brief: Destroys dynamically allocated variables
     */
    BattleSphere::~BattleSphere() {
        delete m_defenderBulletSharedMedia;
        delete m_timer;
        delete m_button;
    }

    /**
     * \brief: called on each frame, re draws all objects
     * \param: event, description of when to perform the redraw
     */
    void BattleSphere::paintEvent(QPaintEvent *event) {
        QPainter painter(this);

        painter.drawPixmap(m_defender.getX(), m_defender.getY(), m_defenderImg);

        int bulletIDX = 0;
        QVector<int> offscreenBulletsIDX;
        // Update bullets on screen
        for (auto &curBullet : m_bullets) {
            if (curBullet.getY() < 0) {
                // Bullet has left the screen
                offscreenBulletsIDX.push_back(bulletIDX);
            }

            // Draw bullet on screen
            if (curBullet.getBulletType() == "Alien") {
                // Draw an Alien bullet
                painter.drawPixmap(curBullet.getX(), curBullet.getY(), m_alienBulletImg);
            } else {
                // Draw a Defender Bullet
                painter.drawPixmap(curBullet.getX(), curBullet.getY(), curBullet.getImage());
            }

            if (curBullet.getDirection() == "Left") {
                // Move the bullet diagonally left across the screen
                curBullet.updateLeftX(m_bulletSpeed);
            } else if (curBullet.getDirection() == "Right") {
                // Move the bullet diagonally right across the screen
                curBullet.updateRightX(m_bulletSpeed);
            }
            // Move the bullet up or down the screen
            curBullet.updateY(m_bulletSpeed);

            bulletIDX++;
        }

        // Remove the bullets that are no longer visible from the bullets vector
        for (int bulletIDX : offscreenBulletsIDX) {
            m_bullets.erase(m_bullets.begin() + bulletIDX);
        }

        // Does something with stars ???
        for (auto &curStar : m_stars) {
            if (curStar.getOpacity() > 0.6 && curStar.getOpacityDelta() > 0) {
                curStar.toggleOpacityDelta();
            } else if (curStar.getOpacity() < 0.1 && curStar.getOpacityDelta() < 0) {
                curStar.toggleOpacityDelta();
            }
            curStar.setOpacity(curStar.getOpacity() + curStar.getOpacityDelta());
            painter.setOpacity(curStar.getOpacity());
            painter.drawPixmap(curStar.getX(), curStar.getY(), m_starImg);
        }
    }

    /**
     * \brief: runs every X seconds, where X is the value sent to the timer
     *         function in the input
     */
    void BattleSphere::nextFrame() {

        // animate the defender
        int maxX = this->width() - m_defenderImg.width();

        if (m_commandCentre.hasNext()) {
            std::string nextCommand = m_commandCentre.popNext();
            if (nextCommand == "Left") {
                m_defender.setX(m_defender.getX() - m_defender.getSpeed());
                if (m_defender.getX() < 0) {
                    m_defender.setX(0);
                }
            } else if (nextCommand == "Right") {
                m_defender.setX(m_defender.getX() + m_defender.getSpeed());
                if (m_defender.getX() > maxX) {
                    m_defender.setX(maxX);
                }
            } else if (nextCommand == "Fire" ||
                       nextCommand == "FireLeft" ||
                       nextCommand == "FireRight") {
                int bx = m_defender.getX() + (m_defenderImg.width()/2) - (m_bulletImg.width()/2);
                int by = m_defender.getY() - m_bulletImg.height();

                DefenderBullet db(bx, by, "defender", m_defenderBulletSharedMedia);

                // Set bullets direction
                if (nextCommand == "FireLeft") {
                    db.setDirection("Left");
                } else if (nextCommand == "FireRight") {
                    db.setDirection("Right");
                } else {
                    db.setDirection("Straight");
                }

                db.getSound()->play();

                // Append to bullets
                m_bullets.push_back(db);
            }
        }
        update();
    }

    void BattleSphere::screenshot()
    {
        QWidget *w = QApplication::activeWindow();
        if(w) {
            QPixmap p = QPixmap::grabWidget(w);
            p.save(QString("BattleSphereScreenshot.png"));
        }
    }

} // end namespace si
