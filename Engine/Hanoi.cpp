#include "Hanoi.h"

Hanoi::Hanoi(Graphics& gfx, int nDisks, Mode mode)
	:
	nDisks(nDisks),
	mode(mode)
{
	//assign pegxs
	int pegSX = int (Graphics::ScreenWidth / 6);
	for (int i = 0; i < 3; i++)
	{
		pegs[i].x = pegSX;
		pegs[i].index = i;
		pegSX += int (Graphics::ScreenWidth / 3);
	}
	//biggest disk size
	const int firstW = Graphics::ScreenWidth / 6 - 1 - gap;
	const int firstH = (Graphics::ScreenHeight - topGap + ((int)ceil(nDisks / 2) * nDisks) * heightChange) / nDisks;
	const int firstBiCH = (Graphics::ScreenHeight - topGap + (((int)ceil(nDisks / 2) * nDisks) * heightChange) / 2) / nDisks;
	assert(0 < firstW - (nDisks - 1) * widthChange);
	assert(0 < firstH - (nDisks - 1) * heightChange);
	assert(0 < firstBiCH - (nDisks / 2 - 1) * heightChange);
	//mode select
	switch (mode)
	{
	case Hanoi::Mode::normHanoi:
		SetupNormHanoi(firstW, firstH);
		NormalHanoi(nDisks, pegs[0], pegs[1], pegs[2]);
		break;
	case Hanoi::Mode::doubleHanoi:
		SetupDoubleHanoi();
		EnhancedDoubleHanoi(nDisks / 2, pegs[0], pegs[1], pegs[2]);
		break;
	case Hanoi::Mode::mergeHanoi:
		SetupMergeHanoi();
		MergeHanoi(nDisks / 2, pegs[0], pegs[1], pegs[2]);
		break;
	case Hanoi::Mode::splitHanoi:
		SetupSplitHanoi();
		SplitHanoi(nDisks / 2, pegs[0], pegs[1], pegs[2]);
		break;
	case Hanoi::Mode::baseSwapHanoi:
		SetupBaseSwapHanoi();
		BaseSwapHanoi(nDisks / 2, pegs[0], pegs[1], pegs[2]);
		break;
	case Hanoi::Mode::easyBicolorHanoi:
		SetupEasyBicolorHanoi();
		EasyBicolorHanoi(nDisks / 2, pegs[0], pegs[1], pegs[2]);
		break;
	case Hanoi::Mode::bicolorHanoi:
		SetupBicolorHanoi();
		BicolorHanoi(nDisks / 2, pegs[0], pegs[1], pegs[2]);
		break;
	default:
		break;
	}
	if (mode != Mode::normHanoi)
		BicolorDiskSetup(firstW, firstBiCH);
	LoadStep();
}

void Hanoi::FromAToB(Peg& A, Peg& B)
{
	steps.emplace_back(std::array<int, 2>{ A.index, B.index });
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

void Hanoi::EnhancedDoubleHanoi(int n, Peg& A, Peg& B, Peg& Via)
{
	DoubleHanoi(n, A, Via, B);
	DoubleHanoi(n, Via, B, A);
}

void Hanoi::DoubleHanoi(int n, Peg& A, Peg& B, Peg& Via)
{
	if (n == 1)
	{
		FromAToB(A, B);
		FromAToB(A, B);
	}
	else
	{
		DoubleHanoi(n - 1, A, Via, B);
		FromAToB(A, B);
		FromAToB(A, B);
		DoubleHanoi(n - 1, Via, B, A);
	}
}

void Hanoi::MergeHanoi(int n, Peg& A, Peg& B, Peg& Via)
{
	if (n == 1)
	{
		FromAToB(B, A);
	}
	else
	{
		MergeHanoi(n - 1, A, B, Via);
		DoubleHanoi(n - 1, A, Via, B);
		FromAToB(B, A);
		DoubleHanoi(n - 1, Via, A, B);
	}
}

void Hanoi::SplitHanoi(int n, Peg& A, Peg& B, Peg& Via)
{
	if (n == 1)
	{
		FromAToB(A, B);
	}
	else
	{
		DoubleHanoi(n - 1, A, Via, B);
		FromAToB(A, B);
		DoubleHanoi(n - 1, Via, A, B);
		SplitHanoi(n - 1, A, B, Via);
	}
}

void Hanoi::BaseSwapHanoi(int n, Peg& A, Peg& B, Peg& Via)
{
	if (n == 1)
	{
		FromAToB(A, Via);
		FromAToB(B, A);
		FromAToB(Via, B);
	}
	else
	{
		MergeHanoi(n - 1, A, B, Via);
		FromAToB(B, Via);
		DoubleHanoi(n - 1, A, Via, B);
		FromAToB(A, B);
		DoubleHanoi(n - 1, Via, B, A);
		FromAToB(Via, A);
		EnhancedDoubleHanoi(n - 1, B, A, Via);
		SplitHanoi(n - 1, A, B, Via);
	}
}

void Hanoi::EasyBicolorHanoi(int n, Peg& A, Peg& B, Peg& Via)
{
	if(n == 1){}
	else
	{
		BicolorHanoi(n - 1, A, B, Via);
	}
}

void Hanoi::BicolorHanoi(int n, Peg& A, Peg& B, Peg& Via)
{
	if (n == 1)
	{
		FromAToB(A, Via);
		FromAToB(B, A);
		FromAToB(Via, B);
	}
	else
	{
		EasyBicolorHanoi(n - 1, A, B, Via);
		BaseSwapHanoi(n, A, B, Via);
	}
}

void Hanoi::BicolorDiskSetup(const int firstW, const int firstH)
{
	Color c[2] = {Colors::Red, Colors::Black};
	for (int i = 0; i < nDisks; i++)
	{
		disks.emplace_back(Rect(0, 0, firstW - i * widthChange, firstH - i * heightChange, c[0]));
		i++;
		disks.emplace_back(Rect(0, 0, firstW - (i-1) * widthChange, firstH - (i - 1) * heightChange, c[1]));
	}
}

void Hanoi::SetupNormHanoi(const int firstW, const int firstH)
{
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

	//disk size and color assigning for NormHanoi
	for (int i = 0; i < nDisks; i++)
	{
		Color c;
		if (randomColors)
			c = Color(rCol(rng), rCol(rng), rCol(rng));
		else
			c = Color(55 + cC * i, 0, 0);
		disks.emplace_back(Rect{ 0, 0, firstW - i * widthChange, firstH - i * heightChange, c });
	}
}

void Hanoi::SetupDoubleHanoi()
{
	for (int j = 0; j < nDisks; j++)
	{
		pegs[0].highestPegI.push_back(j);
	}
}

void Hanoi::SetupMergeHanoi()
{
	for (int j = 0; j < nDisks; j++)
	{
		pegs[0].highestPegI.push_back(j);
		j++;
		pegs[1].highestPegI.push_back(j);
	}
}

void Hanoi::SetupSplitHanoi()
{
	SetupDoubleHanoi();
}

void Hanoi::SetupBaseSwapHanoi()
{
	int i = 0;
	pegs[1].highestPegI.push_back(i++);
	pegs[0].highestPegI.push_back(i++);
	for (int j = 2; j < nDisks; j++)
	{
		pegs[0].highestPegI.push_back(j);
		j++;
		pegs[1].highestPegI.push_back(j);
	}
}

void Hanoi::SetupEasyBicolorHanoi()
{
	bool fLeft = false;
	for (int j = 0; j < nDisks; j++)
	{
		if (fLeft)
		{
			pegs[0].highestPegI.push_back(j);
			j++;
			pegs[1].highestPegI.push_back(j);
			fLeft = false;
		}
		else
		{
			pegs[1].highestPegI.push_back(j);
			j++;
			pegs[0].highestPegI.push_back(j);
			fLeft = true;
		}
	}
}

void Hanoi::SetupBicolorHanoi()
{
	SetupEasyBicolorHanoi();
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

int Hanoi::GetCS() const
{
	return currentStep;
}

int Hanoi::GetMaxStep() const
{
	return (int)steps.size() - 1;
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

Hanoi::Disk::Disk(const Rect& sRect)
	:
	disk(sRect)
{}
