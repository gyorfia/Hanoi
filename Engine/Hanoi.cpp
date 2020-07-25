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
	//biggest disk size
	const int firstW = int(Graphics::ScreenWidth / 6 - 1 - gap);
	const int firstH = int((Graphics::ScreenHeight - topGap + (ceil(nDisks / 2) * nDisks) * heightChange) / nDisks);
	const int firstBiCH = int((Graphics::ScreenHeight - topGap + ((ceil(nDisks / 2) * nDisks) * heightChange) / 2) / nDisks);
	assert(0 < firstW - (nDisks - 1) * widthChange);
	assert(0 < firstH - (nDisks - 1) * heightChange);
	assert(0 < firstBiCH - (nDisks / 2 - 1) * heightChange);
	//mode select
	if (normHanoi)
	{
		SetupNormHanoi(firstW, firstH);
		NormalHanoi(nDisks, pegs[0], pegs[1], pegs[2]);
	}
	else if (doubleHanoi)
	{
		SetupDoubleHanoi();
		EnhancedDoubleHanoi(nDisks / 2, pegs[0], pegs[1], pegs[2]);
	}
	else if (mergeHanoi)
	{
		SetupMergeHanoi();
		MergeHanoi(nDisks / 2, pegs[0], pegs[1], pegs[2]);
	}
	else if (splitHanoi)
	{
		SetupSplitHanoi();
		SplitHanoi(nDisks / 2, pegs[0], pegs[1], pegs[2]);
	}
	else if (baseSwapHanoi)
	{
		SetupBaseSwapHanoi();
		BaseSwapHanoi(nDisks / 2, pegs[0], pegs[1], pegs[2]);
	}
	else if (easyBicolorHanoi)
	{
		SetupEasyBicolorHanoi();
		EasyBicolorHanoi(nDisks / 2, pegs[0], pegs[1], pegs[2]);
	}
	else if (bicolorHanoi)
	{
		SetupBicolorHanoi();
		BicolorHanoi(nDisks / 2, pegs[0], pegs[1], pegs[2]);
	}

	if (!normHanoi)
		BicolorDiskSetup(firstW, firstBiCH);
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
	Color c[2] = {Colors::Blue, Colors::Red};
	for (int i = 0; i < nDisks; i++)
	{
		disks[i].disk = Rect(0, 0, firstW - i * widthChange, firstH - i * heightChange, c[0]);
		i++;
		disks[i].disk = Rect(0, 0, firstW - (i-1) * widthChange, firstH - (i - 1) * heightChange, c[1]);
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
		disks[i].disk = Rect(0, 0, firstW - i * widthChange, firstH - i * heightChange, c);
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
