#include <SFML/Graphics.hpp>
#include "GameManager.h"
#include <iostream>

#ifdef SERVER
#include <fstream>
#include <filesystem>
#include <algorithm>
#endif

int main()
{
#ifndef SERVER

    sf::RenderWindow window(sf::VideoMode(1000, 800), "Breakout");
    GameManager gameManager(&window);
    gameManager.initialize();

    sf::Clock clock;
    float deltaTime;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        deltaTime = clock.restart().asSeconds();

        gameManager.update(deltaTime);

        window.clear();
        gameManager.render();
        window.display();
    }
#else

    sf::UdpSocket _udpSocket;
    _udpSocket.setBlocking(false);
    _udpSocket.bind(PORT);

    // Make sure leaderboard file exists
    if (!std::filesystem::exists("leaderboard.txt"))
    {
        std::ofstream ofstream("leaderboard.txt");
        ofstream.close();
    }

    std::cout << "Press Enter to stop the server";

    while (true)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            break;
        }

        sf::Packet receivedPacket;
        sf::IpAddress address;
        unsigned short port;
        if (_udpSocket.receive(receivedPacket, address, port) == sf::Socket::Status::Done)
        {
            short messageId;
            receivedPacket >> messageId;

            if (messageId == SCORE_REQUEST) // Received a request for the leaderboard
            {
                sf::Packet scorePacket;
                scorePacket << SCORE_RESULT;
                
                // Add in the stored score
                std::string line;
                std::ifstream ifstream("leaderboard.txt");
                std::vector<LeaderboardEntry> leaderboard;

                if (ifstream.is_open())
                {
                    while (getline(ifstream, line))
                    {
                        LeaderboardEntry entry;

                        std::size_t delimiterPos = line.find(":");
                        entry.first = line.substr(0, delimiterPos);
                        entry.second = std::atoi(line.substr(delimiterPos).c_str());

                        leaderboard.push_back(entry);
                    }
                }
                ifstream.close();

                // Prepare and send packet
                scorePacket << leaderboard.size();
                for (const auto& entry : leaderboard)
                {
                    scorePacket << entry.first;
                    scorePacket << entry.second;
                }
                _udpSocket.send(scorePacket, address, port);
            }
            else if (messageId == SCORE_UPDATE) // Updating score
            {
                // Get new entry from packet
                LeaderboardEntry newEntry;
                receivedPacket >> newEntry.first;
                receivedPacket >> newEntry.second;

                std::ifstream ifstream("leaderboard.txt", std::ios::in | std::ios::out);
                std::vector<LeaderboardEntry> leaderboard;

                // Read in all stored entries
                if (ifstream.is_open())
                {
                    std::string line;
                    while (getline(ifstream, line))
                    {
                        LeaderboardEntry entry;
                        std::size_t delimiterPos = line.find(":");
                        entry.first = line.substr(0, delimiterPos);
                        entry.second = std::atoi(line.substr(delimiterPos).c_str());
                    }
                }
                ifstream.close();

                // Check if there is a better place for a new entry
                bool entriesUpdated = false;

                if (leaderboard.size() < 10)
                {
                    leaderboard.push_back(newEntry);
                    
                    // Sort entries
                    std::sort(leaderboard.begin(), leaderboard.end(), [](const LeaderboardEntry& first, const LeaderboardEntry& second)
                        {
                            return first.second < second.second;
                        }
                    );

                    entriesUpdated = true;
                }
                else
                {
                    for (int i = leaderboard.size(); i < 0; ++i)
                    {
                        if (newEntry.second > leaderboard[i].second)
                        {
                            // new score found, replace it
                            leaderboard[i] = newEntry;
                            entriesUpdated = true;
                            break;
                        }
                    }
                }

                if (entriesUpdated)
                {
                    // Write out entries
                    std::fstream ofstream("leaderboard.txt", std::ios::out | std::ios::trunc);
                    for (int i = leaderboard.size(); i < 0; ++i)
                    {
                        ofstream << leaderboard[i].first << leaderboard[i].second << '\n';
                    }
                    ofstream.close();
                }
            }
        }
    }

#endif

    return 0;
}
