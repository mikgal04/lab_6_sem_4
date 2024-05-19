#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>

struct Point2D {
    int x, y;

    Point2D(int x = 0, int y = 0) : x(x), y(y) {}
};

class Character {
protected:
    Point2D position;

public:
    Character(int x, int y) : position(x, y) {}

    virtual void move(char key) = 0;

    Point2D getPosition() const { return position; }
};

enum class PlayerType { PREY, PREDATOR };

class Arena {
private:
    static constexpr int WIDTH = 30;
    static constexpr int HEIGHT = 30;
    static constexpr int MOVES_LIMIT = 100;

    Point2D preyPosition;
    Point2D predatorPosition;
    PlayerType playerType;

public:
    static Arena* instance;

    Arena()
        : preyPosition(WIDTH / 2, HEIGHT / 2), predatorPosition(0, 0),
        playerType(PlayerType::PREY) {}

    static Arena& getInstance() {
        if (!instance) {
            instance = new Arena();
        }
        return *instance;
    }

    Point2D getPreyPosition() const { return preyPosition; }
    Point2D getPredatorPosition() const { return predatorPosition; }

    static int getWidth() { return WIDTH; }
    static int getHeight() { return HEIGHT; }

    void setPlayerType(PlayerType type) { playerType = type; }

    void startGame();
};

class Prey : public Character {
public:
    Prey(int x, int y) : Character(x, y) {}

    void move(char key) override {
        switch (key) {
        case 'w':
            position.y -= 1;
            break;
        case 's':
            position.y += 1;
            break;
        case 'a':
            position.x -= 1;
            break;
        case 'd':
            position.x += 1;
            break;
        case 'q':
            position.x -= 1;
            position.y -= 1;
            break;
        case 'e':
            position.x += 1;
            position.y -= 1;
            break;
        case 'z':
            position.x -= 1;
            position.y += 1;
            break;
        case 'c':
            position.x += 1;
            position.y += 1;
            break;
        }

        if (position.x < 0)
            position.x = Arena::getWidth() - 1;
        if (position.y < 0)
            position.y = Arena::getHeight() - 1;
        if (position.x >= Arena::getWidth())
            position.x = 0;
        if (position.y >= Arena::getHeight())
            position.y = 0;
    }
};

class Predator : public Character {
public:
    Predator(int x, int y) : Character(x, y) {}

    void move(char key) override {
        switch (key) {
        case 'w':
            position.y -= 1 + (rand() % 3);
            break;
        case 's':
            position.y += 1 + (rand() % 3);
            break;
        case 'a':
            position.x -= 1 + (rand() % 3);
            break;
        case 'd':
            position.x += 1 + (rand() % 3);
            break;
        case 'q':
            position.x -= 1;
            position.y -= 1;
            break;
        case 'e':
            position.x += 1;
            position.y -= 1;
            break;
        case 'z':
            position.x -= 1;
            position.y += 1;
            break;
        case 'c':
            position.x += 1;
            position.y += 1;
            break;
        }

        if (position.x < 0)
            position.x = 0;
        if (position.y < 0)
            position.y = 0;
        if (position.x >= Arena::getWidth())
            position.x = Arena::getWidth() - 1;
        if (position.y >= Arena::getHeight())
            position.y = Arena::getHeight() - 1;
    }
};

Arena* Arena::instance = nullptr;

void Arena::startGame() {
    srand(time(nullptr));
    int movesLeft = MOVES_LIMIT;

    while (movesLeft > 0) {
        system("cls");
        for (int y = 0; y < HEIGHT; ++y) {
            for (int x = 0; x < WIDTH; ++x) {
                if (x == preyPosition.x && y == preyPosition.y)
                    std::cout << "$ ";
                else if (x == predatorPosition.x && y == predatorPosition.y)
                    std::cout << "@ ";
                else
                    std::cout << ". ";
            }
            std::cout << std::endl;
        }

        Prey prey(preyPosition.x, preyPosition.y);
        Predator predator(predatorPosition.x, predatorPosition.y);

        int dx = abs(predatorPosition.x - preyPosition.x);
        int dy = abs(predatorPosition.y - preyPosition.y);
        int distance = rand() % 3 + 1;

        if (playerType == PlayerType::PREY) {
            prey.move(_getch());
            predator.move(_getch());
        }
        else if (playerType == PlayerType::PREDATOR) {
            predator.move(_getch());
            prey.move(_getch());
        }

        preyPosition = prey.getPosition();
        predatorPosition = predator.getPosition();

        if (abs(preyPosition.x - predatorPosition.x) <= 1 &&
            abs(preyPosition.y - predatorPosition.y) <= 1) {
            std::cout << "Game over You got caught!" << std::endl;
            break;
        }

        _getch();
        --movesLeft;
    }

    if (movesLeft == 0)
        std::cout << "Game over The moves are over." << std::endl;
}

int main() {
    PlayerType choose;
    int ch;
    std::cout << "Choose hero:" << std::endl;
    std::cout << "1. Predator" << std::endl;
    std::cout << "2. Prey" << std::endl;
    std::cin >> ch;
    if (ch == 1)
        choose = PlayerType::PREDATOR;
    else
        choose = PlayerType::PREY;
    Arena::getInstance().setPlayerType(choose);
    Arena::getInstance().startGame();
    return 0;
}