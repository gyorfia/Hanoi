#pragma once
#include <vector>
#include <array>
#include <random>
#include <assert.h>
#include "Rect.h"
#include "Graphics.h"

class Hanoi
{	
public:
	enum class Mode
	{
	normHanoi,
	doubleHanoi,
	mergeHanoi,
	splitHanoi,
	baseSwapHanoi,
	easyBicolorHanoi,
	bicolorHanoi
	};
private:
	/* Variables: */
	/************************************************************/
	//Number of disks (in bicolor modes it covers col0 + col1)
	int nDisks;
	//
	const int gap = 20; //gap between pegs
	const int topGap = 250; //gap between the top of the screen, and the top of the tower
	const int widthChange = 20;
	const int heightChange = 5;
	bool randomColors = false; //only in normhanoi
	//Modes:
	Mode mode;
	/************************************************************/
private:
	class Disk
	{
	public:
		Disk(const Rect& sRect);
	public:
		Rect disk;
	};

	class Peg
	{
	public:
		int x;
		int index;
		std::vector <int> highestPegI;
		int currentHeight;
	};

public:
	Hanoi(Graphics& gfx, int nDisks = 6, Mode mode = Mode::normHanoi);
	void LoadStep();
	int GetCS() const;
	int GetMaxStep() const;
	void ChangeCurrentStep(int c);
	void Draw(Graphics& gfx) const;
private:
	void FromAToB(Peg& A, Peg& B);
	//setup functions:
	void BicolorDiskSetup(const int firstW, const int firstH);
	void SetupNormHanoi(const int firstW, const int firstH);
	void SetupDoubleHanoi();
	void SetupMergeHanoi();
	void SetupSplitHanoi();
	void SetupBaseSwapHanoi();
	void SetupEasyBicolorHanoi();
	void SetupBicolorHanoi();
	//logic functions
	void NormalHanoi(int n, Peg& A, Peg& B, Peg& Via);
	void EnhancedDoubleHanoi(int n, Peg& A, Peg& B, Peg& Via);
	void DoubleHanoi(int n, Peg& A, Peg& B, Peg& Via);
	void MergeHanoi(int n, Peg& A, Peg& B, Peg& Via);
	void SplitHanoi(int n, Peg& A, Peg& B, Peg& Via);
	void BaseSwapHanoi(int n, Peg& A, Peg& B, Peg& Via);
	void EasyBicolorHanoi(int n, Peg& A, Peg& B, Peg& Via);
	void BicolorHanoi(int n, Peg& A, Peg& B, Peg& Via);
private:
	std::vector <std::array<int, 2>> steps;
	int currentStep = -1;
	std::vector<Disk> disks;
	Peg pegs[3];
};