#include "PaddleBrain.h"
#include "json.hpp"
#include "httplib.h"
#include <string>
#include <chrono>
#include <format>
using namespace std::string_literals;

PaddleBrain::PaddleBrain(sf::RenderWindow* window)
	: Paddle(window)
{
	client = std::make_unique<httplib::Client>("http://localhost:11434/");
}

PaddleBrain::~PaddleBrain()
{

}

void PaddleBrain::SetGameState(nlohmann::json gameState)
{
	this->gameState = gameState;
}

void PaddleBrain::handleControls(float dt)
{
	if (dir < 0) moveLeft(dt);
	else if (dir > 0) moveRight(dt);

	if (thinking)
		return;

	nlohmann::json jsonDataFull;
	jsonDataFull["model"] = "d1";
	jsonDataFull["state"] =
	{
		{ "info", "You are playing atari breakout" },
		{ "boardstate", gameState }
	};
	jsonDataFull["questions"] =
	{
		{
			"left",
			{
				{ "type", "noul"},
				{ "instructions", "Save the ball! Should the paddle move in the negative direction to save the ball? Remember, you don't want the ball falling off screen." }
			}
		},
		{
			"right",
			{
				{ "type", "noul"},
				{ "instructions", "Save the ball! Should the paddle move in the positive direction to save the ball? Remember, you don't want the ball falling off screen." }
			}
		}
	};

	std::string jsonData = jsonDataFull.dump();

	thinking = true;
	std::thread worker([this, jsonData]()
	{
		auto start = std::chrono::steady_clock::now();
		auto res = client->Post("/v1/systemone", jsonData,
			"application/json");
		auto end = std::chrono::steady_clock::now();
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

		if (!res)
		{
			thinking = false;
			return;
		}

		auto j = nlohmann::json::parse(res->body);
		if (res->status == 200)
		{
			std::cout << j << std::endl;
			this->dir = j["answers"]["right"]["noul"].get<float>() - j["answers"]["left"]["noul"].get<float>();
			std::cout << "Took " << ms.count() << " ms\n";
			this->dir = j["answers"]["right"]["noul"].get<float>() - j["answers"]["left"]["noul"].get<float>();
		}
		else
		{
			std::cout << "Error: " << j << std::endl;
			std::cout << "Input was: " << jsonData << std::endl;
		}

		thinking = false;
	});


	worker.detach();
}
