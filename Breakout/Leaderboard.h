#pragma once
#include <vector>

struct LeaderboardEntry
{
    int session;
    int level;
    float secondsPerBlock;
};

class Leaderboard
{
public:
    Leaderboard();

    void add(int level, float secondsPerBlock);
    const std::vector<LeaderboardEntry>& getEntries() const;
    int getSessionId() const;

private:
    void load();
    void save() const;

    std::vector<LeaderboardEntry> _entries;
    int _sessionId;
};
