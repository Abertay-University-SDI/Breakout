#include "PowerupManager.h"


PowerupManager::PowerupManager(sf::RenderWindow* window, Paddle* paddle, Ball* ball)
    : _window(window), _paddle(paddle), _ball(ball)
{
}

PowerupManager::~PowerupManager()
{
    for (auto powerup : _powerups)
    {
        delete powerup;
    }
    _powerups.clear();
}

void PowerupManager::update(float dt)
{
    // tick down powerup effect time. Reset if elapsed.
    if (_powerupInEffect.size() > 0)
    {
        for (int i = 0; i < _powerupInEffect.size(); i++) { //Make all active powerups tick down
            _powerupInEffect[i].second -= dt;
        }

        _powerupInEffect.erase( //Erase all ending powerups
            std::remove_if(
                _powerupInEffect.begin(),
                _powerupInEffect.end(),
                [](std::pair<POWERUPS, float> const& p) { return p.second <= 0; }
            ),
            _powerupInEffect.end()
        );
    }


    for (auto it = _powerups.begin(); it != _powerups.end(); )
    {
        checkCollision();
        
        // Delete powerups queued for removal
        (*it)->update(dt);
        if (!(*it)->isAlive())
        {
            delete* it;
            it = _powerups.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void PowerupManager::render()
{
    for (auto& powerup : _powerups)
    {
        powerup->render();
    }
}

void PowerupManager::spawnPowerup()
{


    // TODO finish this.
    
    //Adele Addition: Powerups now have a chance to give multiple powerups at once
    
    //Temp variable to count current amount of powerups in the same one
    int powerupsToAssign = 1;

    int powerupsTotal = 1;
    bool hasMulti = false;
    std::vector<POWERUPS> multiPowers;

    while (powerupsToAssign > 0) {

        switch (rand() % 5 + maxPowerupsAtOnce - powerupsTotal) //The higher maxPowerupsAtOnce is, the higher chance of adding an extra powerup 
        { 
        case 0:
            if (!hasMulti) {
                _powerups.push_back(new PowerupBigPaddle(_window, _paddle, _ball));
            }
            else {
                multiPowers.push_back(bigPaddle);
            }
            break;
        case 1:
            if (!hasMulti) {
                _powerups.push_back(new PowerupSlowBall(_window, _paddle, _ball));
            }
            else {
                multiPowers.push_back(slowBall);
            }
            break;
        case 2:
            if (!hasMulti) {
                _powerups.push_back(new PowerupFastBall(_window, _paddle, _ball));
            }
            else {
                multiPowers.push_back(fastBall);
            }
            break;
        case 3:
            if (!hasMulti) {
                _powerups.push_back(new PowerupSmallPaddle(_window, _paddle, _ball));
            }
            else {
                multiPowers.push_back(smallPaddle);
            }
            break;
        case 4:
            if (!hasMulti) {
                _powerups.push_back(new PowerupFireBall(_window, _paddle, _ball));
            }
            else {
                multiPowers.push_back(fireBall);
            }
            break;
        default: //powerupsTotal will increase and lead to extra powerups no longer occuring
            powerupsTotal += 1;
            //Increase by 2 to counter the reduction by 1, effectively increasing the number by 1
            powerupsToAssign += 2;
            hasMulti = true;
           break;
        }

        powerupsToAssign--;
    }

    if (hasMulti) {
        _powerups.push_back(new PowerupMulti(_window, _paddle, _ball, multiPowers));
    }
}

void PowerupManager::checkCollision()
{
    for (auto& powerup : _powerups)
    {

        if (powerup->checkCollisionWithPaddle())
        {
            if (powerup->isMulti) {
                for (int i = 0; i < powerup->powers.size(); i++) {
                    if (!hasPowerup(powerup->checkMulti(i))) {
                        _powerupInEffect.push_back(powerup->applyMulti(i));
                    }
                }
            } else {
                if (!hasPowerup(powerup->checkEffect())) {
                    _powerupInEffect.push_back(powerup->applyEffect());
                }
            }
            powerup->setAlive(false);
        }
    }
}

bool PowerupManager::hasPowerup(POWERUPS powerup) {
    if (powerup == fireBall) {
        for (auto& activePowerup : _powerupInEffect)
        {
            if (powerup == activePowerup.first) {
                activePowerup.second = 5.f; //Reset the timer as well
                return true;
            }
        }
    }
    return false;
}

int PowerupManager::getPowerupsSpawned()
{
    return _powerups.size();
}

std::vector<std::pair<POWERUPS, float>> PowerupManager::getPowerupInEffect()
{
    //if (_powerupInEffect.size() == 0) return { none, 0.f };
    return _powerupInEffect; //Maybe bad to remove the *_powerupInEffect here
}
