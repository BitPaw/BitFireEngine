#include "OpenFileDialog.h"

#include "../OSDefine.h"

#include <stdio.h>

#if defined(OSWindows)
#include <windows.h>
#include <shobjidl.h> 
#elif defined(OSUnix)
#endif

bool BF::OpenFileDialog::Open(char* filePathOutput)
{
    wchar_t pathW[_MAX_PATH];

    bool succesful = OpenFileDialog::Open(pathW);

    if (succesful)
    {
        sprintf(filePathOutput, "%ws", pathW);
    }

    return succesful;
}

bool BF::OpenFileDialog::Open(wchar_t* filePathOutput)
{
    bool wasSuccesful = false;

#if defined(OSWindows)
#if defined(OSWindowsXP)
    const wchar_t* filter = L"All Files (*.*)\0*.*\0";
    HWND owner = NULL;

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = owner;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = L"";

    if (GetOpenFileName(&ofn))
    {
        wasSuccesful = true;
    }
#else
    HRESULT hResult = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

    if (SUCCEEDED(hResult))
    {
        IFileOpenDialog* pFileOpen = nullptr;

        // Create the FileOpenDialog object.
        hResult = CoCreateInstance
        (
            CLSID_FileOpenDialog,
            NULL,
            CLSCTX_ALL,
            IID_IFileOpenDialog,
            reinterpret_cast<void**>(&pFileOpen)
        );

        if (SUCCEEDED(hResult))
        {
            // Show the Open dialog box.
            hResult = pFileOpen->Show(NULL);

            // Get the file name from the dialog box.
            if (SUCCEEDED(hResult))
            {
                IShellItem* pItem;
                hResult = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hResult))
                {
                    PWSTR pszFilePath; // wchar
                    hResult = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                    // Display the file name to the user.
                    if (SUCCEEDED(hResult))
                    {
                        lstrcpyW(filePathOutput, pszFilePath);
                    
                        wasSuccesful = true;

                        CoTaskMemFree(pszFilePath);
                    }
                    pItem->Release();
                }
            }

            pFileOpen->Release();
        }
        
        CoUninitialize();
    }
#endif
#elif defined(OSUnix)
#endif

    return wasSuccesful;
}