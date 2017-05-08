#include "iofile.h"

namespace si {

    IOFile* IOFile::instance = 0;

    /**
     * \brief: Singleton instance getter. Ensures we do not create more than one
     *         IOFile.
     * \param: fileName, the path to the file. Will work with just the name of the
     *          file if the file is placed inside the build directory created by QT.
     */
    IOFile* IOFile::getInstance(std::string fileName)
    {

        if (0 == instance)
        {

            instance = new IOFile(fileName);

        }

        return instance;
    }

    /**
     * \brief: Protected singleton constructor. End-users cannot access this.
     * \param: fileName, the path to the file. Will work with just the name of the
     *          file if the file is placed inside the build directory created by QT.
     */
    IOFile::IOFile(std::string fileName)
        : m_numberOfLines(0),
          m_fileName(fileName)
    {

        std::string line;
        std::vector<std::string> lines;
        std::ifstream inputStream (m_fileName);

        if (inputStream.is_open())
        {

            while( std::getline(inputStream, line) )
            {

                if (!line.empty())
                {

                    lines.push_back(line);
                    m_numberOfLines++;

                }

            }

            inputStream.close();
            processLines(lines);

        } else {

            std::cout << "Error opening file! Is" <<
                         " it called config.ini and is it " <<
                         "placed inside the source directory, " <<
                         "named info3220_assignment1-master?" << std::endl;
        }
    }

    /**
     * \brief: Used to vet the lines returned from the config.ini file.
     * \param: lines, each element is a line in the input file (config.ini)
     * \result: true if the file format is valid, false if there is a problem.
     *          This function will also print to stdout if there is a problem.
     */
    bool IOFile::processLines(const std::vector<std::string>& lines)
    {

        int lineNumber = 0;

        if (lines.size() < 5)
        {

            std::cout << "ERROR: Not enought lines in input file" << std::endl;
            return false;

        }

        if (lines.at(lineNumber) != "[ Defender ]")
        {

            std::cout << "ERROR: First line must read [ Defender ]" << std::endl;
            return false;

        }

        lineNumber++;

        // Defender X coordinate check
        if (isValidCoordinateCommand(lines.at(lineNumber), true))
        {

            int xCoordinate = getCoordinate(lines.at(lineNumber));
            m_defender.setX(xCoordinate);
            std::cout << "Defender X coord is: " << xCoordinate << std::endl;

        } else {

            return false;

        }

        lineNumber++;

        // Defender Y coordinate check
        if (isValidCoordinateCommand(lines.at(lineNumber), false))
        {

            int yCoordinate = getCoordinate(lines.at(lineNumber));
            m_defender.setY(yCoordinate);
            std::cout << "Defender Y coord is: " << yCoordinate << std::endl;

        } else {

            return false;

        }

        lineNumber++;

        // Scale check
        if (isValidScaleCommand((lines.at(lineNumber))))
        {

            QString scale = QString::fromStdString(getScale(lines.at(lineNumber)));
            m_defender.setScale(scale);

        } else {

            return false;

        }

        lineNumber++;

        // Aliens check
        if (lines.at(lineNumber) != "[ Aliens ]")
        {

            std::cout << "ERROR: 4th line must read [ Aliens ]" << std::endl;
            return false;

        }

        lineNumber++;

        SharedMediaFactory *sharedMediaFactory = new SharedMediaFactory();

        QRegExp alienBossRegex("AlienBoss\\s=\\s(On|Off)");
        QString alienBossLine = QString::fromStdString(lines.at(lineNumber));

        if (alienBossRegex.exactMatch(alienBossLine))
        {

            QRegExp alienBossOnRegex("AlienBoss\\s=\\sOn");

            if (alienBossOnRegex.exactMatch(alienBossLine))
            {

                QPixmap bossImg = QPixmap(":/images/venusaur.png");
                bossImg = bossImg.scaledToWidth(100);
                SharedMedia *media = sharedMediaFactory->getSharedMedia("V", bossImg, nullptr, 10);
                AlienBoss *bossAlien = new AlienBoss(350, 60, media);
                m_swarm = AlienComposite(bossAlien);

            }

        } else {

            std::cout << alienBossLine.toStdString() << std::endl;
            std::cout << "ERROR: alien boss must be either 'On' or 'Off'" << std::endl;
            return false;

        }

        lineNumber++;

        // Number of swarms
        if (isValidNumberOfSwarms(lines.at(lineNumber)))
        {

            int numberOfSwarms = getNumberOfSwarms(lines.at(lineNumber));
            std::cout << "Number of Swarms: " << numberOfSwarms << std::endl;

        } else {

            return false;

        }

        lineNumber++;

        // Aliens X coordinate check
        if (isValidCoordinateCommand(lines.at(lineNumber), true))
        {

            int xCoordinate = getCoordinate(lines.at(lineNumber));
            m_swarm.setX(xCoordinate);
            std::cout << "Alien Swarm X coord is: " << xCoordinate << std::endl;

        } else {

            return false;

        }

        lineNumber++;

        // Aliens Y coordinate check
        if (isValidCoordinateCommand(lines.at(lineNumber), false))
        {

            int yCoordinate = getCoordinate(lines.at(lineNumber));
            m_swarm.setY(yCoordinate);
            std::cout << "Alien Swarm Y coord is: " << yCoordinate << std::endl;

        } else {

            return false;

        }

        lineNumber++;

        QMap<QString, QPixmap> alienPictures;
        alienPictures["S"] = QPixmap(":/images/squirtle.png");
        alienPictures["W"] = QPixmap(":/images/wartortle.png");
        alienPictures["B"] = QPixmap(":/images/blastoise.png");

        for (auto &alienPic : alienPictures)
        {

            alienPic = alienPic.scaledToWidth(45);

        }

        std::regex alienLineRegex("([SWB]\\s)*[SWB]");
        int swarmCount = lineNumber;
        while (true)
        {

            if (!std::regex_match(lines.at(swarmCount), alienLineRegex))
            {

                break;

            }

            swarmCount++;

        }

        std::vector<std::string> swarm(lines.begin()+lineNumber,lines.begin()+swarmCount);

        QRegExp alienTypeRegex("S|W|B");
        int alienStartX = m_swarm.getX();
        int alienStartY = m_swarm.getY();
        int alienWidth = alienPictures["S"].width();
        int alienHeight = alienPictures["S"].height();

        for (auto& line : swarm)
        {

            if (!std::regex_match(line, alienLineRegex))
            {

                std::cout << line << std::endl;
                std::cout << "Error: Alien Swarm Line must only be of type ' ', 'S', 'W', or 'B'" << std::endl;
                return false;

            }

            QString l = QString::fromStdString(line);
            QStringList aliens = l.split(QRegExp("\\s"));
            int buffer = 15;

            for (auto& alienType : aliens)
            {

                if (!alienTypeRegex.exactMatch(alienType))
                {

                    std::cout << alienType.toStdString() << std::endl;
                    std::cout << "Error: Alien must only be of type 'S', 'W', or 'B'" << std::endl;
                    return false;

                }

                SharedMedia *media = sharedMediaFactory->getSharedMedia(alienType, alienPictures[alienType], nullptr, 10);
                Alien *alien = new Alien(alienStartX, alienStartY, media);
                m_swarm.add(alien);

                alienStartX = alienStartX + alienWidth + buffer;

            }

            alienStartY = alienStartY + alienHeight + buffer;
            alienStartX = m_swarm.getX();
            lineNumber++;

        }

        if (lines.at(lineNumber) != "[ AlienMovements ]")
        {

            std::cout << "ERROR: 7th line must read [ AlienMovements ]" << std::endl;
            return false;

        }

        lineNumber++;

        QString alienMovementsLine = QString::fromStdString(lines.at(lineNumber));

        QRegExp alienMovementsRegex("([LR]\\s)*[LR]");

        if (!alienMovementsRegex.exactMatch(alienMovementsLine))
        {

            std::cout << alienMovementsLine.toStdString() << std::endl;
            std::cout << "ERROR: alien movements must be a pattern of L or R follwed by a space repeated e.g. L L R L R" << std::endl;

        }

        QStringList alienMovements = QString::fromStdString(lines.at(lineNumber)).split(QRegExp("\\s"));

        QRegExp movementsRegex("L|R");

        for (auto &alienMovement : alienMovements)
        {

            if (!movementsRegex.exactMatch(alienMovement))
            {

                std::cout << alienMovement.toStdString() << std::endl;
                std::cout << "Error: Alien movements must only be 'L' or 'R'" << std::endl;
                return false;

            }

        }

        for (auto &alien : m_swarm.getList())
        {

            alien->setTraj(alienMovements);

        }

        lineNumber++;

        if (lines.at(lineNumber) != "[ Commands ]") {
            std::cout << "ERROR: 24th line must read [ Commands ]" << std::endl;
            return false;
        }

        lineNumber++;

        std::vector<std::string> commands(lines.begin()+lineNumber, lines.end());

        std::regex commandsRegex("Left|Right|FireLeft|FireRight|Fire");

        for (auto &curLine : commands)
        {

            if (!std::regex_match(curLine, commandsRegex))
            {

                std::cout << curLine << std::endl;
                std::cout << "Error: Commands must only be 'Left', 'Right', 'Fire', 'FireLeft', or 'FireRight'" << std::endl;
                return false;

            }

            m_commandCentre.addToBuffer(curLine);

        }

        return true;
    }


    /**
     * \brief: Uses regex to check that defender coordinates are written in config.ini
     *         in the format XPos = 120 or YPos = 100 (of course the user can pick their
     *         own values for XPos and YPos, the numbers above are only illustrative.
     * \param: line, a line of the input file to be checked (config.ini)
     * \param: isX, true if we are checking whether this is a valid x coordinate command,
     *              false if we are checking whether this is a valid y coordinate command.
     * \result: true if the regex matches the line in the file, false otherwise
     */
    bool IOFile::isValidCoordinateCommand(std::string line, bool isX)
    {
        std::string label = "XPos";
        if (!isX)
        {

            label = "YPos";

        }
        std::regex e (label + "\\s*=\\s*\\d+$");
        if (std::regex_match(line, e))
        {

            return true;

        } else {

            return false;

        }
    }


    /**
     * \brief: Checks that the scale command is written in the file as Scale = tiny
     *          (for example)
     * \param: line, a line in our input file
     * \result: true if the regex matches the scale line in the input file (config.ini)
     */
    bool IOFile::isValidScaleCommand(std::string line)
    {
        std::regex e ("Scale\\s*=\\s*[a-z]+$");
        if (std::regex_match(line, e))
        {

            return true;

        } else {

            return false;

        }

    }


    /**
     * \brief: Uses regex to check the number of swarms is valid.
     * \param: line, a line of the input file to be checked (config.ini)
     * \result: true if the regex matches the line in the file, false otherwise
     */
    bool IOFile::isValidNumberOfSwarms(std::string line)
    {
        std::string label = "Swarms";
        std::regex e (label + "\\s*=\\s*\\d+$");
        if (std::regex_match(line, e))
        {

            return true;

        } else {

            return false;

        }

    }


    /**
     * \brief: Extracts the integer value from a line such as "XPos = 123". Would
     *         return 123 in this case.
     * \param: line, a coordinate line in our input file (config.ini)
     * \result: the integer value extracted from that line
     */
    int IOFile::getCoordinate(std::string line)
    {
        // Match numbers
        std::regex e ("\\d+");
        std::smatch m;
        if (std::regex_search (line, m, e))
        {

          return std::stoi(m[0]);

        } else {

            // Do some error handling and return 0
            std::cout << "Could not parse: " << line << std::endl;
            std::cout << "Using default value of 0" << std::endl;
            return 0;

        }

    }


    /**
     * \brief: Extracts the integer value from a line such as "Swarms = 3". Would
     *         return 3 in this case.
     * \param: line, a line in our input file (config.ini)
     * \result: the integer value extracted from that line
     */
    int IOFile::getNumberOfSwarms(std::string line)
    {
        // Match numbers
        std::regex e ("\\d+");
        std::smatch m;
        if (std::regex_search (line, m, e))
        {

          return std::stoi(m[0]);

        } else {

            // Do some error handling and return 0
            std::cout << "Could not parse: " << line << std::endl;
            std::cout << "Using default value of 0" << std::endl;
            return 0;

        }

    }


    /**
     * \brief: Extracts the scale string from a line in the input file, such as
     *         "Scale = tiny".
     * \param: line, a line in the input (config.ini) file
     * \result: the scale as a string, would return "tiny" in the above example
     */
    std::string IOFile::getScale(std::string line)
    {
        // Match numbers
        std::regex e ("tiny|normal|large|giant");
        std::smatch m;
        if (std::regex_search (line, m, e))
        {

          return m[0];

        } else {

            // Do some error handling and return "tiny"
            std::cout << "Could not parse: " << line << std::endl;
            std::cout << "Using default value of tiny" << std::endl;
            return "tiny";

        }
    }

    /**
     * \brief: Returns a buffer of commands obtained from config.ini
     * \result: a command centre instance
     */
    const CommandCentre& IOFile::getCommandCentre() const
    {

        return m_commandCentre;

    }


    /**
     * \brief: Returns a player (Defender) object based on information supplied in config.ini
     * \result: a defender instance, ready to be used in a BattleSphere
     */
    const Defender& IOFile::getDefender() const
    {

        return m_defender;

    }


    /**
     * \brief: Returns an ememy swarm object based on information supplied in config.ini
     * \result: a swarm instance, ready to be used in a BattleSphere
     */
    const AlienComposite& IOFile::getSwarm() const
    {

        return m_swarm;

    }


} // end namespace si
