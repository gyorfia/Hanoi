#pragma once
#include "Graphics.h"
#include "Colors.h"

class Rect
{
public:
	Rect(int sX, int sY, int sHW, int sH, Color sC)
		:
		x(sX),
		y(sY),
		halfWidth(sHW),
		height(sH),
		col(sC)
	{}

	Rect() = default;

	void InitRect(const Rect& sRect)
	{
		Rect(sRect.x, sRect.y, sRect.halfWidth, sRect.height, sRect.col);
	}

	void Draw(Graphics& gfx) const
	{
		for (int i = y - height; i < y; i++)
		{
			for (int j = x - halfWidth; j < x + halfWidth; j++)
			{
				gfx.PutPixel(j, i, col);
			}
		}
	}
public:
	int x;
	int y;
	int halfWidth;
	int height;
	Color col;
};