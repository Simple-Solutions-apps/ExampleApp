//File containing contol reladed code

/*	https://docs.microsoft.com/en-us/windows/win32/winmsg/about-window-classes#application-global-classes
	https://docs.microsoft.com/en-us/windows/win32/controls/individual-control-info
*/

//standard includes
#include <windows.h>
#include <commctrl.h> //https://docs.microsoft.com/en-us/windows/win32/api/commctrl/

//custom includes
#include "..\include\controls.h"

//globals
HFONT hDefaultFont;

//control handels
HWND hListbox;
HWND hLabel1;
HWND hEdit1;
HWND hEdit2;
HWND hLabel2;
HWND hButton1;
HWND hButton2;
HWND hButton3;
HWND hStatusBar;
HWND hToolBar;

//image list handel for toolbar
HIMAGELIST hImageList;

void CreateControls(HWND hwnd)
{
	hDefaultFont = GetStockObject(DEFAULT_GUI_FONT);

	//creating label 1
	hLabel1 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_RIGHT, 5, 37, 50, 20, hwnd, (HMENU) IDC_MAIN_LABEL1, GetModuleHandle(NULL), NULL);
	if(hLabel1 == NULL)
	{
		MessageBox(hwnd, "Could not create Label 1.", "Error", MB_OK | MB_ICONERROR);
	}
	//Adding text to label 1
	SendMessage(hLabel1, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(0, 0));
	SendMessage(hLabel1, WM_SETTEXT, (WPARAM)hDefaultFont, (LPARAM) "Insert:");

	//creating Edit box 1
	hEdit1 = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE , 60, 35, 250, 20, hwnd, (HMENU) IDC_MAIN_EDIT1, GetModuleHandle(NULL), NULL);
	if(hEdit1 == NULL)
	{
		MessageBox(hwnd, "Could not create Edit box 1.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(hEdit1, WM_SETFONT, (WPARAM) hDefaultFont, MAKELPARAM(0, 0));

	//creating Edit Numer box 2
	hEdit2 = CreateWindowEx(WS_EX_CLIENTEDGE | ES_NUMBER, "EDIT", NULL, WS_CHILD | WS_VISIBLE , 315, 35, 20, 20, hwnd, (HMENU) IDC_MAIN_EDIT2, GetModuleHandle(NULL), NULL);
	if(hEdit2 == NULL)
	{
		MessageBox(hwnd, "Could not create Edit box 1.", "Error", MB_OK | MB_ICONERROR);
	}
	//Adding text to Edit 2
	SendMessage(hEdit2, WM_SETFONT, (WPARAM) hDefaultFont, MAKELPARAM(0, 0));
	SendMessage(hEdit2, WM_SETTEXT, (WPARAM) hDefaultFont, (LPARAM) "1");

	//creating label 2
	hLabel2 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, 340, 37, 100, 20, hwnd, (HMENU) IDC_MAIN_LABEL1, GetModuleHandle(NULL), NULL);
	if(hLabel2 == NULL)
	{
		MessageBox(hwnd, "Could not create Label 2.", "Error", MB_OK | MB_ICONERROR);
	}
	//Adding text to label 2
	SendMessage(hLabel2, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(0, 0));
	SendMessage(hLabel2, WM_SETTEXT, (WPARAM)hDefaultFont, (LPARAM) "times");

	//creating Listbox 
	hListbox = CreateWindowEx(WS_EX_CLIENTEDGE, "LISTBOX", NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | LBS_MULTIPLESEL, 60, 60, 250, 200, hwnd, (HMENU) IDC_MAIN_LISTBOX, GetModuleHandle(NULL), NULL);
	if(hListbox == NULL)
	{
		MessageBox(hwnd, "Could not create list box.", "Error", MB_OK | MB_ICONERROR);
	}
	SendMessage(hListbox, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(0, 0));

	//creating button 1
	hButton1 = CreateWindowEx(0, "BUTTON", NULL, BS_DEFPUSHBUTTON | WS_CHILD | WS_VISIBLE , 315, 60, 50, 30, hwnd, (HMENU) IDC_MAIN_BUTTON1, GetModuleHandle(NULL), NULL);
	if(hButton1 == NULL)
	{
		MessageBox(hwnd, "Could not create button 1.", "Error", MB_OK | MB_ICONERROR);
	}
	//Adding text to button 1
	SendMessage(hButton1, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(0, 0));
	SendMessage(hButton1, WM_SETTEXT, (WPARAM)hDefaultFont, (LPARAM) "Insert");

	hButton2 = CreateWindowEx(0, "BUTTON", NULL, BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE , 315, 95, 50, 30, hwnd, (HMENU) IDC_MAIN_BUTTON2, GetModuleHandle(NULL), NULL);
	if(hButton2 == NULL)
	{
		MessageBox(hwnd, "Could not create button 2.", "Error", MB_OK | MB_ICONERROR);
	}
	//Adding text to button 2
	SendMessage(hButton2, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(0, 0));
	SendMessage(hButton2, WM_SETTEXT, (WPARAM)hDefaultFont, (LPARAM) "Remove");

	//creating button 3
	hButton3 = CreateWindowEx(0, "BUTTON", NULL, BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE , 315, 130, 50, 30, hwnd, (HMENU) IDC_MAIN_BUTTON3, GetModuleHandle(NULL), NULL);
	if(hButton1 == NULL)
	{
		MessageBox(hwnd, "Could not create button 3.", "Error", MB_OK | MB_ICONERROR);
	}
	//Adding text to button 3
	SendMessage(hButton3, WM_SETFONT, (WPARAM)hDefaultFont, MAKELPARAM(0, 0));
	SendMessage(hButton3, WM_SETTEXT, (WPARAM)hDefaultFont, (LPARAM) "Clear");

	//creating Status Bar https://docs.microsoft.com/en-us/windows/win32/controls/status-bar-reference
	hStatusBar = CreateWindowEx(0, "msctls_statusbar32", NULL, WS_BORDER | WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hwnd, (HMENU) IDC_MAIN_STATUSBAR, GetModuleHandle(NULL), NULL);
	if(hStatusBar == NULL)
	{
		MessageBox(hwnd, "Could not create Status bar.", "Error", MB_OK | MB_ICONERROR);
	}
	//Deviding status bar into parts
	RECT rcClient; 
    HLOCAL hloc;
    LPINT lpParts;
	char* TempBuff;
    int i, nWidth, nParts;

	GetClientRect(hwnd, &rcClient);

	 //2 parts for the status bar
	nParts = 2;

	// Allocate an array for storing the right edge coordinates of each part.
    hloc = LocalAlloc(LHND, sizeof(int) * nParts);
    lpParts = LocalLock(hloc);

	// Calculate the right edge coordinate for each part, and
    nWidth = rcClient.right/nParts; 

	// copy the coordinates to the array.
    for (i = 0; i < nParts; i++)
	{
		lpParts[i] = nWidth;
        nWidth += nWidth;
    } 

	if(SendMessage(hStatusBar, SB_SETPARTS, (WPARAM) nParts, (LPARAM) (LPINT) lpParts) == TRUE)
	{
		//Adding text to Status Bar parts
		SendMessage(hStatusBar, SB_SETTEXT,  (WPARAM) 0 | 0, (LPARAM) (LPSTR) "Logged in as: Guest\0");
		SendMessage(hStatusBar, SB_SETTEXT,  (WPARAM) 1 | 0, (LPARAM) (LPSTR) "Status: ready\0");
	}
	else
	{
		MessageBox(hwnd, "Could not create Status bar parts.", "Error", MB_OK | MB_ICONERROR);
	}	

	// Free the memory no longer needed
    LocalUnlock(hloc);
    LocalFree(hloc);

	//creating toolbar https://docs.microsoft.com/en-us/windows/win32/controls/bumper-toolbar-toolbar-control-overviews
	hToolBar = CreateWindowEx(0, "ToolbarWindow32", NULL, CCS_ADJUSTABLE | WS_BORDER | WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hwnd, (HMENU) IDC_MAIN_TOOLBAR, GetModuleHandle(NULL), NULL);
	if(hToolBar == NULL)
	{
		MessageBox(hwnd, "Could not create Tool bar.", "Error", MB_OK | MB_ICONERROR);
	}

	// Send the TB_BUTTONSTRUCTSIZE message, which is required for backward compatibility.
	SendMessage(hToolBar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);

	const int iButtonsCount = 3;

	//first you add a list of images to use
	//add a list of buttons
	TBBUTTON tbButtonsToAdd[iButtonsCount]; //Container for three buttons
	TBADDBITMAP tbaBitMap;

	//add the standard bitmaps to the toolbar
	tbaBitMap.hInst = HINST_COMMCTRL;
	tbaBitMap.nID = IDB_STD_SMALL_COLOR;
	
	SendMessage(hToolBar, TB_ADDBITMAP, 0, (LPARAM) &tbaBitMap);
	//add functionality for buttons
	ZeroMemory(tbButtonsToAdd, sizeof(tbButtonsToAdd));
    tbButtonsToAdd[0].iBitmap = STD_FILENEW;
    tbButtonsToAdd[0].fsState = TBSTATE_ENABLED;
    tbButtonsToAdd[0].fsStyle = TBSTYLE_BUTTON;
    tbButtonsToAdd[0].idCommand = IDC_MAIN_TOOLBAR_FILE_NEW;

    tbButtonsToAdd[1].iBitmap = STD_FILEOPEN;
    tbButtonsToAdd[1].fsState = TBSTATE_ENABLED;
    tbButtonsToAdd[1].fsStyle = TBSTYLE_BUTTON;
    tbButtonsToAdd[1].idCommand = IDC_MAIN_TOOLBAR_FILE_OPEN;

    tbButtonsToAdd[2].iBitmap = STD_FILESAVE;
    tbButtonsToAdd[2].fsState = TBSTATE_ENABLED;
    tbButtonsToAdd[2].fsStyle = TBSTYLE_BUTTON;
    tbButtonsToAdd[2].idCommand = IDC_MAIN_TOOLBAR_FILE_SAVEAS;

	// Add buttons.
	SendMessage(hToolBar, TB_ADDBUTTONS, sizeof(tbButtonsToAdd)/sizeof(TBBUTTON), (LPARAM) &tbButtonsToAdd);
	//resize buttons
	SendMessage(hToolBar, TB_AUTOSIZE, 0, 0);
	//show buttons
	ShowWindow(hToolBar, TRUE);
}