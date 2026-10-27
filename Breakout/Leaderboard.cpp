#include "Leaderboard.h"
#include "CONSTANTS.h"
#include <algorithm>
#include <fstream>
#include <random>

Leaderboard::Leaderboard()
{
    load();

    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> distribution(0, SESSION_ID_MAX);
    bool sessionUsed = true;
    while (sessionUsed)
    {
        _sessionId = distribution(rng);
        sessionUsed = std::any_of(_entries.begin(), _entries.end(),
            [&](const LeaderboardEntry& entry) {
                return entry.session == _sessionId;
            }
        );
    }
}

void Leaderboard::add(int level, float secondsPerBlock)
{
    auto position = std::upper_bound(_entries.begin(), _entries.end(), secondsPerBlock,
        [](float value, const LeaderboardEntry& entry) {
            return value < entry.secondsPerBlock;
        }
    );
    
    size_t rank = position - _entries.begin();
    if (rank >= LEADERBOARD_SIZE)
        return;

    _entries.insert(position, { _sessionId, level, secondsPerBlock });
    if (_entries.size() > LEADERBOARD_SIZE)
        _entries.pop_back();

    save();
}

const std::vector<LeaderboardEntry>& Leaderboard::getEntries() const
{
    return _entries;
}

int Leaderboard::getSessionId() const
{
    return _sessionId;
}

void Leaderboard::load()
{
    std::ifstream file(LEADERBOARD_PATH);
    LeaderboardEntry entry;
    while (file >> entry.session >> entry.level >> entry.secondsPerBlock)
    {
        _entries.push_back(entry);
    }

    std::stable_sort(_entries.begin(), _entries.end(),
        [](const LeaderboardEntry& a, const LeaderboardEntry& b) {
            return a.secondsPerBlock < b.secondsPerBlock;
        }
    );
    if (_entries.size() > LEADERBOARD_SIZE) _entries.resize(LEADERBOARD_SIZE);
}

void Leaderboard::save() const
{
    std::ofstream file(LEADERBOARD_PATH);
    for (const LeaderboardEntry& entry : _entries)
    {
        file << entry.session << ' ' << entry.level << ' ' << entry.secondsPerBlock << '\n';
    }
}
