#pragma once
#include <vector>
#include <array>
#include <random>
#include <assert.h>
#include "Rect.h"
#include "Graphics.h"

class Hanoi
{
private:

	class Disk
	{
	public:
		void Init(const Rect& sRect);
	public:
		Rect disk;
	};

	class Peg
	{
	public:
		int x;
		int currentHeight = 0;
	};

public:
	Hanoi(Graphics& gfx);
	void LoadNextStep();
	void Draw(Graphics& gfx) const;

public:
	//number of disks, set position in Game.cpp
	static constexpr int nDisks = 7;
	//
	std::vector <std::array<int, nDisks>> steps;
	int currentStep = 0;

private:
	Disk disks[nDisks];
	Peg pegs[3];

	//changeable variables
	const int gap = 20; //gap between pegs
	const int topGap = 250; //gap between the top, and the top of the tower
	static constexpr int widthChange = 20;
	static constexpr int heightChange = 0;
	//
};