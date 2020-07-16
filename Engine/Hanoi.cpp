#include "Hanoi.h"

Hanoi::Hanoi(Graphics& gfx)
{
	int pegSX = int (Graphics::ScreenWidth / 6);
	for (int i = 0; i < 3; i++)
	{
		pegs[i].x = pegSX;
		pegSX += int (Graphics::ScreenWidth / 3);
	}

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution <int> rCol{100, 255};

	const int firstW = int(Graphics::ScreenWidth / 6 - 1 - gap);
	const int firstH = int((Graphics::ScreenHeight - topGap) / nDisks + (ceil(nDisks / 2) * nDisks) * heightChange);

	assert(0 < firstW - (nDisks - 1) * widthChange);
	assert(0 < firstH - (nDisks - 1) * heightChange);

	for (int i = 0; i < nDisks; i++)
	{
		Color c = Color(rCol(rng), rCol(rng), rCol(rng));
		disks[i].disk = Rect(0, 0, firstW - i * widthChange, firstH - i * heightChange, c);
	}
}

void Hanoi::LoadNextStep()
{
	for (int i = 0; i < nDisks; i++)
	{
		Peg& onThisPeg = pegs[steps[currentStep][i]];

		disks[i].disk.x = onThisPeg.x;
		disks[i].disk.y = Graphics::ScreenHeight - onThisPeg.currentHeight;
		onThisPeg.currentHeight += disks[i].disk.height;
	}
	currentStep++;
}

void Hanoi::Draw(Graphics& gfx) const
{
	for (int i = 0; i < nDisks; i++)
	{
		disks[i].disk.Draw(gfx);
	}
}

void Hanoi::Disk::Init(const Rect& sRect)
{
	disk = sRect;
}
