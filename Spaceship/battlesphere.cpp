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
    BattleSphere::BattleSphere(QWidget *parent, Defender d, int bulletSpeed, CommandCentre cc, AlienComposite s)
        : QDialog(parent),
          m_bulletSpeed(bulletSpeed),
          m_collisonSound(":/sounds/explosion.wav"),
          m_commandCentre(cc),
          m_defender(d),
          m_swarm(s)
    {

        this->m_lives = 10;
        this->m_move = 0;
        this->m_score = 0;
        this->m_numberOfAliens = m_swarm.getList().size();

        for (int i=0; i<m_numStars; ++i)
        {

            int randX = rand() % m_screenWidth;
            int randY = rand() % m_screenHeight;

            float randStartOpacity = ((double) rand() / (RAND_MAX)) + 1;
            Star curStar(randX, randY);
            curStar.setOpacity(randStartOpacity);
            m_stars.push_back(curStar);

        }

        m_size = d.getScale();

        m_starImg.load(":/images/star.png");
        m_starImg = m_starImg.scaledToWidth(5);

        // Set the defender and defender bullet images
        if (m_size == "tiny")
        {

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

        m_tinyAlienSoundPath = ":/sounds/squirtle.wav";
        m_normalAlienSoundPath = ":/sounds/wartortle.wav";
        m_largeAlienSoundPath = ":/sounds/blastoise.wav";
        m_bossAlienSoundPath = ":/sounds/venusaur.wav";

        m_tinyAlienBulletImg.load(":/images/tiny-water-pump.png");
        m_normalAlienBulletImg.load(":/images/normal-water-pump.png");
        m_largeAlienBulletImg.load(":/images/large-water-pump.png");
        m_bossAlienBulletImg.load(":/images/vine-whip.png");

        SharedMediaFactory* sharedMediaFactory = new SharedMediaFactory();
        // 10 is there as an temporary value until I implement speed properly
        m_defenderBulletSharedMedia = sharedMediaFactory->getSharedMedia("defenderBullet", m_bulletImg, m_sharedSoundPath, 10);

        m_tinyAlienBulletSharedMedia = sharedMediaFactory->getSharedMedia("tinyAlienBullet", m_tinyAlienBulletImg, m_tinyAlienSoundPath, 10);
        m_normalAlienBulletSharedMedia = sharedMediaFactory->getSharedMedia("normalAlienBullet", m_normalAlienBulletImg, m_normalAlienSoundPath, 10);
        m_largeAlienBulletSharedMedia = sharedMediaFactory->getSharedMedia("largeAlienBullet", m_largeAlienBulletImg, m_largeAlienSoundPath, 10);
        m_bossAlienBulletSharedMedia = sharedMediaFactory->getSharedMedia("bossAlienBullet", m_bossAlienBulletImg, m_bossAlienSoundPath, 10);

        m_defender.setY(m_screenHeight - m_defenderImg.height());

        setStyleSheet("background-color: #000000;");
        this->resize(m_screenWidth, m_screenHeight);
        update();

        // Create the button, make "this" the parent
        m_button = new QPushButton("SCREENSHOT", this);
        // set size and location of the button
        m_button->setGeometry(QRect(QPoint(350, 10), QSize(100, 30)));
        m_button->setStyleSheet("background-color: #FFFD38;");

        m_timer = new QTimer(this);
        connect(m_timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
        connect(m_button, SIGNAL(released()), this, SLOT(screenshot()));
        m_timer->start(50);

    }


    /**
     * \brief: Destroys dynamically allocated variables
     */
    BattleSphere::~BattleSphere()
    {

        delete m_defenderBulletSharedMedia;
        delete m_tinyAlienBulletSharedMedia;
        delete m_normalAlienBulletSharedMedia;
        delete m_largeAlienBulletSharedMedia;
        delete m_bossAlienBulletSharedMedia;

        delete m_timer;
        delete m_button;

    }


    /**
     * \brief: allows the user to pause the game by pressing the key 'p'
     */
    void BattleSphere::keyPressEvent(QKeyEvent *event)
    {

        if (event->key() == Qt::Key_P && m_timer->isActive())
        {

            m_timer->stop();

        } else {

            m_timer->start(50);

        }

    }


    /**
     * \brief: returns true if an alien has been shot and false otherwise
     */
    bool BattleSphere::hasCollision(Alien *alien, DefenderBullet bullet)
    {

        // Alien coordinates
        int alienLeftX = alien->getX();
        int alienRightX = alienLeftX + alien->getImage().width();
        int alienTopY = alien->getY();
        int alienBottomY = alienTopY + alien->getImage().height();

        // Bullet coordinates
        int bulletLeftX = bullet.getX();
        int bulletRightX = bulletLeftX + bullet.getImage().width();
        int bulletTopY = bullet.getY();
        int bulletBottomY = bulletTopY + bullet.getImage().height();

        if (alienLeftX <= bulletRightX && alienRightX >= bulletLeftX && alienTopY <= bulletBottomY && alienBottomY >= bulletTopY)
        {

            return true;

        }

        return false;

    }


    /**
     * \brief: returns true if the boss has been shot and falses otherwise
     */
    bool BattleSphere::bossCollision(AlienBoss *bossAlien, DefenderBullet bullet)
    {

        // Boss coordinates
        int bossAlienLeftX = bossAlien->getX();
        int bossAlienRightX = bossAlienLeftX + bossAlien->getImage().width();
        int bossAlienTopY = bossAlien->getY();
        int bossAlienBottomY = bossAlienTopY + bossAlien->getImage().height();

        // Bullet coordinates
        int bulletLeftX = bullet.getX();
        int bulletRightX = bulletLeftX + bullet.getImage().width();
        int bulletTopY = bullet.getY();
        int bulletBottomY = bulletTopY + bullet.getImage().height();

        if (bossAlienLeftX <= bulletRightX && bossAlienRightX >= bulletLeftX && bossAlienTopY <= bulletBottomY && bossAlienBottomY >= bulletTopY)
        {

            return true;

        }

        return false;

    }


    /**
     * \brief: returns true if the defender has been shot and false otherwise
     */
    bool BattleSphere::isDefenderShot(AlienBullet bullet)
    {

        // Alien coordinates
        int defenderLeftX = m_defender.getX();
        int defenderRightX = defenderLeftX + m_defenderImg.width();
        int defenderTopY = m_defender.getY();
        int defenderBottomY = defenderTopY +  m_defenderImg.height();

        // Bullet coordinates
        int bulletLeftX = bullet.getX();
        int bulletRightX = bulletLeftX + bullet.getImage().width();
        int bulletTopY = bullet.getY();
        int bulletBottomY = bulletTopY + bullet.getImage().height();

        if (defenderLeftX <= bulletRightX && defenderRightX >= bulletLeftX && defenderTopY <= bulletBottomY && defenderBottomY >= bulletTopY)
        {

            return true;

        }

        return false;

    }


    /**
     * \brief: stops the game immediatley if the defender comes in contact with an alien
     */
    bool BattleSphere::isDefenderHitByAlien(Alien *alien)
    {

        // Alien coordinates
        int defenderLeftX = m_defender.getX();
        int defenderRightX = defenderLeftX + m_defenderImg.width();
        int defenderTopY = m_defender.getY();
        int defenderBottomY = defenderTopY +  m_defenderImg.height();

        // Bullet coordinates
        int alienLeftX = alien->getX();
        int alienRightX = alienLeftX + alien->getImage().width();
        int alienTopY = alien->getY();
        int alienBottomY = alienTopY + alien->getImage().height();

        if (defenderLeftX <= alienRightX && defenderRightX >= alienLeftX && defenderTopY <= alienBottomY && defenderBottomY >= alienTopY)
        {

            return true;

        }

        return false;

    }


    /**
     * \brief: handles collisons and updates the dead aliens if hit by the defenders bullets
     */
    void BattleSphere::handleCollisons(QVector<Alien *> aliens)
    {

        for (int i = aliens.size() - 1; i > -1; i--)
        {

            for (int j = 0; j < m_bullets.size(); j++)
            {

                if (this->hasCollision(aliens.at(i), m_bullets.at(j)))
                {

                    m_collisonSound.play();
                    QString alienShot = m_swarm.getList().at(i)->getType();
                    this->updateScore(alienShot);
                    m_swarm.remove(i);
                    m_bullets.erase(m_bullets.begin() + j);
                    m_swarm.speedUp();

                }

            }

        }

        if (m_swarm.getBoss() != nullptr)
        {

            for (int j = 0; j < m_bullets.size(); j++)
            {

                // Check for collisions with the Alien Boss
                if (this->bossCollision(m_swarm.getBoss(), m_bullets.at(j)))
                {

                    m_collisonSound.play();
                    QString alienShot = m_swarm.getBoss()->getType();
                    this->updateScore(alienShot);
                    m_swarm.removeBoss();
                    m_bullets.erase(m_bullets.begin() + j);
                    m_swarm.speedUp();

                }

            }

        }

    }


    /**
     * \brief: checks whether the defender is dead and updates m_lives for each hit
     */
    void BattleSphere::isDefenderDead()
    {

        for (int i = 0; i < m_alienbullets.size(); i++)
        {

            if (this->isDefenderShot(m_alienbullets.at(i)))
            {

                m_collisonSound.play();

                if (m_lives >= 1) {

                    m_lives--;

                }

                m_alienbullets.erase(m_alienbullets.begin() + i);

                return;
            }

        }

        for (int i = 0; i < m_swarm.getList().size(); i++)
        {

            if (isDefenderHitByAlien(m_swarm.getList().at(i)))
            {

                m_swarm.remove(i);
                m_lives = 0;

                return;

            }

        }

        return;

    }


    /**
     * \brief: fires the bullets for the boss alien
     */
    void BattleSphere::bossAlienFire()
    {

        int bossAlienBulletX = m_swarm.getBoss()->getX();
        int bossAlienBulletY = m_swarm.getBoss()->getY() + m_swarm.getBoss()->getImage().height();

        AlienBullet bossAlienBullet (bossAlienBulletX, bossAlienBulletY, "alien", m_bossAlienBulletSharedMedia);

        int firingAngle = rand() % 3;

        if (firingAngle == 0)
        {

            bossAlienBullet.setDirection("Left");

        } else if (firingAngle == 1) {

            bossAlienBullet.setDirection("Right");

        } else {

            bossAlienBullet.setDirection("Straight");

        }

        bossAlienBullet.getSound()->play();

        m_alienbullets.push_back(bossAlienBullet);

    }


    /**
     * \brief: fires the bullets for the alien, randomly chooses an alien to fire
     * \param: the list of the aliens that are still alive to fire
     */
    void BattleSphere::aliensFire(QVector<Alien *> aliens)
    {

        int nextFiringAlien = rand() % aliens.size();
        int alienBulletX = aliens.at(nextFiringAlien)->getX();
        int alienBulletY = aliens.at(nextFiringAlien)->getY() + aliens.at(nextFiringAlien)->getImage().height();

        AlienBullet ab (alienBulletX, alienBulletY, "alien", m_tinyAlienBulletSharedMedia);

        if (aliens.at(nextFiringAlien)->getType() == "W")
        {

            ab.setMedia(m_normalAlienBulletSharedMedia);

        } else if (aliens.at(nextFiringAlien)->getType() == "B") {

            ab.setMedia(m_largeAlienBulletSharedMedia);

        }

        int firingAngle = rand() % 3;
        if (firingAngle == 0)
        {

            ab.setDirection("Left");

        } else if (firingAngle == 1) {

            ab.setDirection("Right");

        } else {

            ab.setDirection("Straight");

        }

        ab.getSound()->play();

        m_alienbullets.push_back(ab);

    }


    /**
     * \brief: called on each frame, re draws all objects
     * \param: event, description of when to perform the redraw
     */
    void BattleSphere::paintEvent(QPaintEvent *event) {
        QPainter painter(this);

        if (this->m_lives > 0)
        {

            // Update defender on the screen
            painter.drawPixmap(m_defender.getX(), m_defender.getY(), m_defenderImg);

            if (m_swarm.getBoss() != nullptr)
            {

                m_swarm.getBoss()->setDirection(m_defender.getX());
                painter.drawPixmap(m_swarm.getBoss()->getX(), m_swarm.getBoss()->getY(), m_swarm.getBoss()->getImage());

            }

            // Update the swarm on the screen
            this->handleCollisons(m_swarm.getList());

            if (this->m_move == 10) {
                this->aliensFire(m_swarm.getList());
            }

            if (m_swarm.getBoss() != nullptr)
            {

                if (this->m_move == 20) {

                    this->bossAlienFire();

                }

            }

            for (auto &alien : m_swarm.getList())
            {

                painter.drawPixmap(alien->getX(), alien->getY(), alien->getImage());

            }

            int alienBulletIDX = 0;
            QVector<int> offscreenAlienBulletsIDX;
            for(auto &curBullet : m_alienbullets)
            {

                if (curBullet.getY() > m_screenHeight) {

                    // Bullet has left the screen
                    offscreenAlienBulletsIDX.push_back(alienBulletIDX);

                }

                painter.drawPixmap(curBullet.getX(), curBullet.getY(), curBullet.getImage());

                if (curBullet.getDirection() == "Left") {

                    // Move the bullet diagonally left across the screen
                    curBullet.updateLeftX(m_bulletSpeed/4);

                } else if (curBullet.getDirection() == "Right") {

                    // Move the bullet diagonally right across the screen
                    curBullet.updateRightX(m_bulletSpeed/4);

                }

                // Move the bullet up or down the screen
                curBullet.updateDownY(m_bulletSpeed/4);

                alienBulletIDX++;
            }

            m_swarm.move();

            // Remove the alien bullets that are no longer visible from the bullets vector
            for (int alienBulletIDX : offscreenAlienBulletsIDX)
            {

                m_alienbullets.erase(m_alienbullets.begin() + alienBulletIDX);

            }

            int bulletIDX = 0;
            QVector<int> offscreenBulletsIDX;

            // Update bullets on screen
            for (auto &curBullet : m_bullets)
            {

                if (curBullet.getY() < 0)
                {

                    // Bullet has left the screen
                    offscreenBulletsIDX.push_back(bulletIDX);

                }

                painter.drawPixmap(curBullet.getX(), curBullet.getY(), curBullet.getImage());

                if (curBullet.getDirection() == "Left")
                {

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
            for (int bulletIDX : offscreenBulletsIDX)
            {

                m_bullets.erase(m_bullets.begin() + bulletIDX);

            }

        }

        // Draws the stars
        for (auto &curStar : m_stars)
        {

            if (curStar.getOpacity() > 0.6 && curStar.getOpacityDelta() > 0)
            {

                curStar.toggleOpacityDelta();

            } else if (curStar.getOpacity() < 0.1 && curStar.getOpacityDelta() < 0)
            {

                curStar.toggleOpacityDelta();

            }

            curStar.setOpacity(curStar.getOpacity() + curStar.getOpacityDelta());
            painter.setOpacity(curStar.getOpacity());
            painter.drawPixmap(curStar.getX(), curStar.getY(), m_starImg);

        }

        this->paintScore();

        if (this->m_lives <= 0)
        {

            this->gameOver();

        }

    }


    /**
     * \brief: runs every X seconds, where X is the value sent to the timer
     *         function in the input
     */
    void BattleSphere::nextFrame() {

        // animate the defender
        int maxX = this->width() - m_defenderImg.width();
        if (m_commandCentre.hasNext())
        {

            std::string nextCommand = m_commandCentre.popNext();
            if (nextCommand == "Left")
            {

                m_defender.setX(m_defender.getX() - m_defender.getSpeed());
                if (m_defender.getX() < 0)
                {

                    m_defender.setX(0);

                }

            } else if (nextCommand == "Right") {

                m_defender.setX(m_defender.getX() + m_defender.getSpeed());
                if (m_defender.getX() > maxX)
                {

                    m_defender.setX(maxX);

                }

            } else if (nextCommand == "Fire" || nextCommand == "FireLeft" || nextCommand == "FireRight") {

                int bx = m_defender.getX() + (m_defenderImg.width()/2) - (m_bulletImg.width()/2);
                int by = m_defender.getY() - m_bulletImg.height();

                DefenderBullet db(bx, by, "defender", m_defenderBulletSharedMedia);

                // Set bullets direction
                if (nextCommand == "FireLeft")
                {

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

        this->isDefenderDead();

        update();

        this->m_move++;
        if (m_move > 40)
        {

            this->m_move = 0;

        }

    }


    /**
     * \brief: updates the score each time an alien is killed
     * \param: the type of alien that was shot
     */
    void BattleSphere::updateScore(QString alienShot)
    {

        if (alienShot == "S")
        {

            m_score += 10;

        } else if (alienShot == "W") {

            m_score += 50;

        } else if (alienShot == "B") {

            m_score += 100;

        } else if (alienShot == "V") {

            m_score += 1000;

        }

    }


    /**
     * \brief: paints the current score and the current lives remaining
     */
    void BattleSphere::paintScore()
    {

        QPainter painter(this);
        QFont font = QFont("Courier New");
        font.setPixelSize(20);
        font.bold();
        painter.setPen(Qt::yellow);
        painter.setFont(font);

        QString score = QString("SCORE: %1").arg(m_score);
        painter.drawText(20, 30, score);

        QString lives = QString("LIVES: %1").arg(m_lives);
        painter.drawText(685, 30, lives);

    }


    /**
     * \brief: paints the text to the screen once the game is over, dictated by
     * no more lives remaining
     */
    void BattleSphere::gameOver()
    {

        QPainter painter(this);

        QString gameOver = "GAME OVER";
        QString score = QString("SCORE: %1").arg(m_score);
        int killedAliens = m_numberOfAliens - m_swarm.getList().size();
        QString aliens = QString("ALIENS KILLED: %1").arg(killedAliens);

        painter.setPen(Qt::yellow);
        QFont font = QFont("Courier New");
        font.setPixelSize(20);
        font.bold();
        painter.setFont(font);

        painter.drawText(335, 280, gameOver);
        painter.drawText(328, 320, score);
        painter.drawText(290, 360, aliens);

    }


    /**
     * \brief: takes a screenshot
     */
    void BattleSphere::screenshot()
    {

        QWidget *w = QApplication::activeWindow();

        if(w)
        {

            QPixmap p = QPixmap::grabWidget(w);
            p.save(QString("BattleSphereScreenshot.png"));

        }

    }


} // end namespace si
