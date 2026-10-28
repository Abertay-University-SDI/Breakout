#pragma once

#include <string>
class Thing
{
public:
	int width;
	int height;
	std::string name;

private:

	auto operator<=>(const Thing& rhs)
	{
		return width <=> rhs.width;
	}


};


int main()
{
	Thing a();
	Thing b();

	return a < b;

}

