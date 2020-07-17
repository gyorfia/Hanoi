#pragma once
#include <vector>
#include <array>
#include <random>
#include <assert.h>
#include "Rect.h"
#include "Graphics.h"

class Hanoi
{
	//number of disks
	static constexpr int nDisks = 7;
	//

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
		void RefreshA();
		void RefreshB();
	public:
		int x;
		int index;
		std::array <int, nDisks> highestPegI;
		int currentHeight = 0;
	};

public:
	Hanoi(Graphics& gfx);
	void LoadStep();
	int GetCS();
	int GetMaxStep();
	void ChangeCurrentStep(int c);
	void Draw(Graphics& gfx) const;
private:
	void FromAToB(Peg& A, Peg& B);
	void NormalHanoi(int n, Peg& A, Peg& B, Peg& Via);
private:
	std::vector <std::array<int, nDisks>> steps;
	int currentStep = 0;
	Disk disks[nDisks];
	Peg pegs[3];

	//changeable variables
	const int gap = 20; //gap between pegs
	const int topGap = 250; //gap between the top of the screen, and the top of the tower
	const int widthChange = 20;
	const int heightChange = 5;
	bool randomColors = false;
	//
};