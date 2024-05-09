#include <iostream>

#include "../Array2D.h"
#include "../Heap.h"

const size_t QUEUE_SIZE = 1024;

const int DIRTABLE[8][2] =
{
	{ 0, -1 },
	{ 1, 0 },
	{ 0, 1 },
	{ -1, 0 },
	{ 1, -1 },
	{ 1, 1 },
	{ -1, 1 },
	{ -1, -1 }
};

const float DISTTABLE[8] =
{
	1.0f, 1.0f, 1.0f, 1.0f,
	1.414214f, 1.414214f, 1.414214f, 1.414214f
};

class Cell
{
public:
	bool mMarked;
	float mDistance;
	int mLastX;
	int mLastY;
	bool mPassable;
	float mWeight;
};

class Coordinate
{
public:
	int x;
	int y;
	float heuristic;
};

int CompareCoordinatesDescending(Coordinate left, Coordinate right)
{
	if (left.heuristic < right.heuristic) return 1;
	if (left.heuristic > right.heuristic) return -1;

	return 0;
}

void ClearCells(Array2D<Cell>& map)
{
	int x;
	int y;
	for (size_t y = 0; y < map.Height(); y++)
	{
		for (size_t x = 0; x < map.Width(); x++)
		{
			map.Get(x, y).mMarked = false;
			map.Get(x, y).mDistance = 0.0f;
			map.Get(x, y).mLastX = -1;
			map.Get(x, y).mLastY = 1;
		}
	}
}

float CellDistance(int x1, int y1, int x2, int y2)
{
	int dx = x1 - x2;
	int dy = y1 - y2;
	dx = dx * dx;
	dy = dy * dy;
	return (float)sqrt((double)dx + (double)dy);
}

void PathDistanceFirst(Array2D<Cell>& map, int px, int py, int gx, int gy)
{
	Coordinate c;
	int x, y;
	int ax, ay;
	int dir;
	float distance;

	Heap<Coordinate> queue(QUEUE_SIZE, CompareCoordinatesDescending);

	ClearCells(map);
	c.x = px;
	c.y = py;
	c.heuristic = 0.0f;
	queue.Enqueue(c);

	while (queue.mCount != 0)
	{
		x = queue.Item().x;
		y = queue.Item().y;
		queue.Dequeue();

		if (!map.Get(x, y).mMarked)
		{
			map.Get(x, y).mMarked = true;

			if (x == gx && y == gx) break;

			for (dir = 0; dir < 8; dir++)
			{
				ax = x + DIRTABLE[dir][0];
				ay = y + DIRTABLE[dir][1];

				if (ax >= 0 && ax < map.Width() &&
					ay >= 0 && ay < map.Height() &&
					map.Get(ax, ay).mPassable == true &&
					map.Get(ax, ay).mMarked == false)
				{
					distance = map.Get(x, y).mDistance + map.Get(ax, ay).mWeight * DISTTABLE[dir];

					if (map.Get(ax, ay).mLastX != -1)
					{
						if (distance < map.Get(ax, ay).mDistance)
						{
							map.Get(ax, ay).mLastX = x;
							map.Get(ax, ay).mLastY = y;
							map.Get(ax, ay).mDistance = distance;
							c.x = ax;
							c.y = ay;
							c.heuristic = ComplexHeuristic(x, y, gx, gy, dir) + distance;
							queue.Enqueue(c);
						}
					}
					else
					{
						map.Get(ax, ay).mLastX = x;
						map.Get(ax, ay).mLastY = y;
						map.Get(ax, ay).mDistance = distance;
						c.x = ax;
						c.y = ay;
						c.heuristic = ComplexHeuristic(x, y, gx, gy, dir) + distance;
						queue.Enqueue(c);
					}
				}
			}
		}
	}
}

float SimpleHeuristic(int x, int y, int gx, int gy, int dir)
{
	float h = 0.0f;
	int diff1;
	int diff2;

	diff1 = gx - x;
	diff2 = gx - (x + DIRTABLE[dir][0]);
	if (diff1 < 0) diff1 = -diff1;
	if (diff2 < 0) diff2 = -diff2;

	if (diff1 > diff2) h -= 1.0f;
	else if (diff1 < diff2) h += 1.0f;

	diff1 = gy - y;
	diff2 = gy - (y + DIRTABLE[dir][0]);
	if (diff1 < 0) diff1 = -diff1;
	if (diff2 < 0) diff2 = -diff2;

	if (diff1 > diff2) h -= 1.0f;
	else if (diff1 < diff2) h += 1.0f;

	return h;
}

float ComplexHeuristic(int x, int y, int gx, int gy, int dir)
{
	x = x + DIRTABLE[dir][0];
	y = y + DIRTABLE[dir][1];

	return CellDistance(x, y, gx, gy);
}

int main()
{


	return 0;
}