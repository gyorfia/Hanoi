#include "Hanoi.h"

Hanoi::Hanoi(Graphics& gfx)
{
	//assign pegxs
	int pegSX = int (Graphics::ScreenWidth / 6);
	for (int i = 0; i < 3; i++)
	{
		pegs[i].x = pegSX;
		pegs[i].index = i;
		pegSX += int (Graphics::ScreenWidth / 3);
	}
	//assign diskpositions for NormHanoi
	for (int j = 0; j < nDisks; j++)
	{
		pegs[0].highestPegI.push_back(j);
	}
	//colors for NormHanoi
		std::random_device rd;
		std::mt19937 rng(rd());
		std::uniform_int_distribution <int> rCol{ 60, 220 };
		int cC = int(200 / (nDisks - 1));
	//biggest disk size
	const int firstW = int(Graphics::ScreenWidth / 6 - 1 - gap);
	const int firstH = int((Graphics::ScreenHeight - topGap + (ceil(nDisks / 2) * nDisks) * heightChange) / nDisks);

	assert(0 < firstW - (nDisks - 1) * widthChange);
	assert(0 < firstH - (nDisks - 1) * heightChange);
	//disk size and color assigning for NormHanoi
	for (int i = 0; i < nDisks; i++)
	{
		Color c;
		if(randomColors)
		c = Color(rCol(rng), rCol(rng), rCol(rng));
		else
		c = Color(55 + cC * i, 0, 0);
		disks[i].disk = Rect(0, 0, firstW - i * widthChange, firstH - i * heightChange, c);
	}
	//logic
	NormalHanoi(nDisks, pegs[0], pegs[1], pegs[2]);
	LoadStep();
}

void Hanoi::FromAToB(Peg& A, Peg& B)
{
	std::array<int, 2> sS = {A.index, B.index};
	steps.push_back(sS);
}

void Hanoi::NormalHanoi(int n, Peg& A, Peg& B, Peg& Via)
{
	if (n == 1)
	{
		FromAToB(A, B);
	}
	else
	{
		NormalHanoi(n-1, A, Via, B);
		FromAToB(A, B);
		NormalHanoi(n-1, Via, B, A);
	}
}

void Hanoi::LoadStep()
{
	for (int i = 0; i < 3; i++)
	{
		auto& onThisPeg = pegs[i];
		onThisPeg.currentHeight = 0;
		for (int j = 0; j < onThisPeg.highestPegI.size(); j++)
		{
			const int curDiskI = onThisPeg.highestPegI[j];

			disks[curDiskI].disk.x = onThisPeg.x;
			disks[curDiskI].disk.y = Graphics::ScreenHeight - onThisPeg.currentHeight;
			onThisPeg.currentHeight += disks[curDiskI].disk.height;
		}
	}
}

int Hanoi::GetCS()
{
	return currentStep;
}

int Hanoi::GetMaxStep()
{
	return steps.size() - 1;
}

void Hanoi::ChangeCurrentStep(int c)
{
	currentStep += c;
	if (c > 0)
	{
		pegs[steps[currentStep][1]].highestPegI.push_back(pegs[steps[currentStep][0]].highestPegI[pegs[steps[currentStep][0]].highestPegI.size() - 1]);
		pegs[steps[currentStep][0]].highestPegI.pop_back();
	}
	else
	{
		pegs[steps[currentStep + 1][0]].highestPegI.push_back(pegs[steps[currentStep + 1][1]].highestPegI[pegs[steps[currentStep + 1][1]].highestPegI.size() - 1]);
		pegs[steps[currentStep + 1][1]].highestPegI.pop_back();
	}
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

void Hanoi::Peg::RefreshA()
{
	for (int i = 0; i < nDisks - 1; i++)
	{
		highestPegI[i] = highestPegI[i + 1];
	}
}

void Hanoi::Peg::RefreshB()
{
	for (int i = nDisks - 1; i > 0; i--)
	{
		highestPegI[i] = highestPegI[i - 1];
	}
}
