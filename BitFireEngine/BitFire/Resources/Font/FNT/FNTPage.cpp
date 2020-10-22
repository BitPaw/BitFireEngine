#include "FNTPage.h"

BF::FNTPage::FNTPage() : FNTPage(0, "[N/A]")
{

}

BF::FNTPage::FNTPage(const unsigned int pageID, std::string pageFileName)
{
	PageID = pageID;
	PageFileName = pageFileName;
}
