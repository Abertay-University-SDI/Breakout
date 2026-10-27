#include "Particles.h"
#include "Raymarch.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>

static float randomRange(float min, float max)
{
    return min + (max - min) * (rand() / static_cast<float>(RAND_MAX));
}

Particles::Particles(sf::RenderWindow* window, Paddle* paddle)
    : _window(window), _paddle(paddle)
{
}

void Particles::splash(sf::Vector2f position, sf::Color colour, int count)
{
    for (int i = 0; i < count; ++i)
    {
        // oldest drops make room for new ones
        if (_drops.size() == MAX_DROPS)
            _drops.erase(_drops.begin());

        Drop drop;
        drop.position = position + sf::Vector2f(randomRange(-30.f, 30.f), randomRange(-5.f, 5.f));
        // launched in a wide upward fan, so the splash rises and spreads before gravity brings it down
        float angle = randomRange(-SPLASH_ANGLE, SPLASH_ANGLE);
        float speed = randomRange(600.f, 950.f);
        drop.velocity = { std::sin(angle) * speed, -std::cos(angle) * speed };
        drop.radius = randomRange(6.f, 10.f);
        drop.maxLife = drop.life = randomRange(1.2f, 2.0f);
        drop.colour = colour;
        _drops.push_back(drop);
    }
}

void Particles::update(float dt)
{
    // Cohesion: nearby drops pull towards each other so splashes hold together like liquid,
    // but push apart when overlapping so they don't collapse into a single point.
    for (size_t i = 0; i < _drops.size(); ++i)
    {
        for (size_t j = i + 1; j < _drops.size(); ++j)
        {
            sf::Vector2f offset = _drops[j].position - _drops[i].position;
            float distance = std::sqrt(offset.x * offset.x + offset.y * offset.y);
            if (distance < 0.01f || distance > COHESION_RANGE) continue;

            float pull = COHESION * distance * (1.f - distance / COHESION_RANGE);
            float overlap = (_drops[i].radius + _drops[j].radius) * 0.8f - distance;
            if (overlap > 0.f) pull -= SEPARATION * overlap;

            sf::Vector2f change = offset / distance * (pull * dt);
            _drops[i].velocity += change;
            _drops[j].velocity -= change;
        }
    }

    sf::FloatRect paddle = _paddle->getBounds();
    float windowWidth = static_cast<float>(_window->getSize().x);
    float windowHeight = static_cast<float>(_window->getSize().y);

    for (auto it = _drops.begin(); it != _drops.end(); )
    {
        Drop& drop = *it;
        drop.velocity.y += GRAVITY * dt;
        drop.velocity -= drop.velocity * std::min(DRAG * dt, 1.f);
        drop.position += drop.velocity * dt;

        // bounce off the side walls
        if ((drop.position.x < drop.radius && drop.velocity.x < 0) ||
            (drop.position.x > windowWidth - drop.radius && drop.velocity.x > 0))
        {
            drop.velocity.x *= -BOUNCE;
        }

        // land on the paddle and slide off
        bool overPaddle = drop.position.x > paddle.left && drop.position.x < paddle.left + paddle.width;
        float paddleTop = paddle.top - drop.radius * 0.5f;
        if (overPaddle && drop.velocity.y > 0 && drop.position.y > paddleTop && drop.position.y < paddle.top + paddle.height)
        {
            drop.position.y = paddleTop;
            drop.velocity.y *= -BOUNCE;
            drop.velocity.x *= 0.9f;
        }

        drop.life -= dt;
        if (drop.life <= 0.f || drop.position.y - drop.radius > windowHeight)
            it = _drops.erase(it);
        else
            ++it;
    }
}

void Particles::render()
{
    for (const Drop& drop : _drops)
    {
        // shrink away over the last third of their life
        float scale = std::min(drop.life / (drop.maxLife * 0.33f), 1.f);
        Raymarch::addParticle(drop.position, drop.radius * scale, drop.colour);
    }
}
