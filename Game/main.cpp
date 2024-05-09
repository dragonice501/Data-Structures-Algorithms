#include <SDL.h>

class Object
{
protected:
	int mX, mY;
	int mCell;

public:
	Object()
	{
		mX = 0;
		mY = 0;
		mCell = 0;
	}

	int GetCell() { return mCell; }
	int GetX() { return mX; }
	int GetY() { return mY; }

	void SetCell(const int pCell) { mCell = pCell; }
	void SetX(const int pX) { mX = pX; }
	void SetY(const int pY) { mY = pY; }
};

class Item : public Object
{
public:
	Item();


};

int main(int argv, char* argc[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	return 0;
}