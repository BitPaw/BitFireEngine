#include "OpenFileDialog.h"

#include <OS/OSVersion.h>
#include <Text/Text.h>
#include <Memory/Memory.h>

#include <stdio.h>

#if defined(OSUnix)
#define _MAX_PATH 260
#elif defined(OSWindows)
#include <windows.h>
#include <shobjidl.h> 
#endif

unsigned char FileOpenDialogA(char* filePathOutput)
{
    wchar_t pathW[_MAX_PATH];

    TextCopyAW(filePathOutput, _MAX_PATH, pathW, _MAX_PATH);

    return FileOpenDialogW(pathW);
}

unsigned char FileOpenDialogW(wchar_t* filePathOutput)
{
    unsigned char wasSuccesful = 0;

#if defined(OSWindows)
#if defined(OSWindowsXP)
    const wchar_t* filter = L"All Files (*.*)\0*.*\0";
    HWND owner = NULL;

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = owner;
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = filePathOutput;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = L"";

    if(GetOpenFileName(&ofn))
    {
        wasSuccesful = true;
    }
#else

    OPENFILENAMEW openFileName;

    MemorySet(&openFileName, sizeof(OPENFILENAMEW), 0);

    const BOOL result = GetOpenFileNameW(&openFileName);



#if 0 // Can only be used in C++ context
    {
        const HRESULT hResult = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
        const unsigned char sucessful = SUCCEEDED(hResult);

        if(!sucessful)
        {
            return 0;
        }
    }

    IFileOpenDialog* pFileOpen = 0;

    // Create the FileOpenDialog object.
    const HRESULT hResult = CoCreateInstance
    (
        CLSID_FileOpenDialog,
        NULL,
        CLSCTX_ALL,
        IID_IFileOpenDialog,
        &pFileOpen
    );

    if(SUCCEEDED(hResult))
    {
        // Show the Open dialog box.
        hResult = pFileOpen->Show(NULL);

        // Get the file name from the dialog box.
        if(SUCCEEDED(hResult))
        {
            IShellItem* pItem;
            hResult = pFileOpen->GetResult(&pItem);
            if(SUCCEEDED(hResult))
            {
                PWSTR pszFilePath; // wchar
                hResult = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                // Display the file name to the user.
                if(SUCCEEDED(hResult))
                {
                    lstrcpyW(filePathOutput, pszFilePath);

                    wasSuccesful = 1u;

                    CoTaskMemFree(pszFilePath);
                }
                pItem->Release();
            }
        }

        pFileOpen->Release();
    }

    CoUninitialize();
#endif
    
#endif
#elif defined(OSUnix)
#endif

    return wasSuccesful;
}
