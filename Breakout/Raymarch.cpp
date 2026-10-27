#include "Raymarch.h"
#include <vector>
#include <algorithm>
#include <iostream>

namespace Raymarch
{
    // Must match MAX_BOXES / MAX_SPHERES / MAX_PARTICLES in shaders/raymarch.frag.
    static const size_t MAX_BOXES = 64;
    static const size_t MAX_SPHERES = 16;
    static const size_t MAX_PARTICLES = 48;

    static sf::Shader _shader;
    static std::vector<sf::Glsl::Vec4> _boxes;
    static std::vector<sf::Glsl::Vec3> _boxColours;
    static std::vector<sf::Glsl::Vec3> _spheres;
    static std::vector<sf::Glsl::Vec3> _sphereColours;
    static std::vector<sf::Glsl::Vec3> _particles;
    static std::vector<sf::Glsl::Vec3> _particleColours;
    static sf::Glsl::Vec4 _particleBounds;  // (left, top, right, bottom)

    static sf::Glsl::Vec3 toVec3(sf::Color c)
    {
        return { c.r / 255.f, c.g / 255.f, c.b / 255.f };
    }

    bool init()
    {
        if (!_shader.loadFromFile("shaders/raymarch.frag", sf::Shader::Fragment))
        {
            std::cerr << "Failed to load shaders/raymarch.frag" << std::endl;
            return false;
        }
        return true;
    }

    void add(const sf::RectangleShape& box)
    {
        if (_boxes.size() == MAX_BOXES || box.getFillColor().a == 0) return;
        sf::FloatRect bounds = box.getGlobalBounds();
        _boxes.emplace_back(bounds.left, bounds.top, bounds.width, bounds.height);
        _boxColours.push_back(toVec3(box.getFillColor()));
    }

    void add(const sf::CircleShape& sphere)
    {
        if (_spheres.size() == MAX_SPHERES || sphere.getFillColor().a == 0) return;
        sf::FloatRect bounds = sphere.getGlobalBounds();
        _spheres.emplace_back(bounds.left + bounds.width / 2, bounds.top + bounds.height / 2, bounds.width / 2);
        _sphereColours.push_back(toVec3(sphere.getFillColor()));
    }

    void addParticle(sf::Vector2f position, float radius, sf::Color colour)
    {
        if (_particles.size() == MAX_PARTICLES || radius <= 0.f) return;
        sf::Glsl::Vec4 bounds(position.x - radius, position.y - radius, position.x + radius, position.y + radius);
        if (!_particles.empty())
        {
            bounds.x = std::min(bounds.x, _particleBounds.x);
            bounds.y = std::min(bounds.y, _particleBounds.y);
            bounds.z = std::max(bounds.z, _particleBounds.z);
            bounds.w = std::max(bounds.w, _particleBounds.w);
        }
        _particleBounds = bounds;
        _particles.emplace_back(position.x, position.y, radius);
        _particleColours.push_back(toVec3(colour));
    }

    void draw(sf::RenderWindow& window)
    {
        _shader.setUniform("BoxCount", static_cast<int>(_boxes.size()));
        if (!_boxes.empty())
        {
            _shader.setUniformArray("Boxes", _boxes.data(), _boxes.size());
            _shader.setUniformArray("BoxColours", _boxColours.data(), _boxColours.size());
        }
        _shader.setUniform("SphereCount", static_cast<int>(_spheres.size()));
        if (!_spheres.empty())
        {
            _shader.setUniformArray("Spheres", _spheres.data(), _spheres.size());
            _shader.setUniformArray("SphereColours", _sphereColours.data(), _sphereColours.size());
        }
        _shader.setUniform("ParticleCount", static_cast<int>(_particles.size()));
        if (!_particles.empty())
        {
            _shader.setUniformArray("Particles", _particles.data(), _particles.size());
            _shader.setUniformArray("ParticleColours", _particleColours.data(), _particleColours.size());
            _shader.setUniform("ParticleBounds", _particleBounds);
        }

        const sf::View& view = window.getView();
        const sf::Vector2f viewOrigin = view.getCenter() - view.getSize() / 2.f;
        _shader.setUniform("iResolution", sf::Glsl::Vec2(window.getSize()));
        _shader.setUniform("ViewSize", sf::Glsl::Vec2(view.getSize()));
        _shader.setUniform("ViewOrigin", sf::Glsl::Vec2(viewOrigin));

        sf::RectangleShape quad(view.getSize());
        quad.setPosition(viewOrigin);
        window.draw(quad, &_shader);

        _boxes.clear();
        _boxColours.clear();
        _spheres.clear();
        _sphereColours.clear();
        _particles.clear();
        _particleColours.clear();
    }
}
