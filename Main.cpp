#include <iostream>
#include <SDL.h>
#include <string>
using namespace std;

int main(int argc, char* argv[])
{
	string name;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
	}
	else
	{
		cout << "SDL initialization succeeded!\n";
		cin >> name;
		cout << name << endl;
		
	}

	cin.get();
	return 0;
}