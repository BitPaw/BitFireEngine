#include "FNTPage.h"

BF::FNTPage::FNTPage()
{
	PageID = -1;
}

BF::FNTPage::FNTPage(const unsigned int pageID, ASCIIString& pageFileName)
{
	PageID = pageID;
	PageFileName.Copy(pageFileName);
}
