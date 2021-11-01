#include "FNTPage.h"

BF::FNTPage::FNTPage()
{
	PageID = -1;
	PageFileName[0] = 0;
	CharacteListSize = 0;
	CharacteList = 0;
}

BF::FNTPage::~FNTPage()
{
	delete[] CharacteList;
}
