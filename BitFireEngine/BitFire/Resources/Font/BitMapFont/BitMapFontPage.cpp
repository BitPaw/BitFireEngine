#include "BitMapFontPage.h"

BitMapFontPage::BitMapFontPage() : BitMapFontPage(0, "[N/A]")
{

}

BitMapFontPage::BitMapFontPage(const unsigned int pageID, std::string pageFileName)
{
	PageID = pageID;
	PageFileName = pageFileName;
}
