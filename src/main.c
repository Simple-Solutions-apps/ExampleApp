//File containing main window reladed code and entry point

//standard includes
#include <windows.h>
#include <commctrl.h>

//Custom includes
#include "..\include\resource.h"
#include "..\include\callbacks.h"

//globals
const char gccClassName[] = "GenericWindowClass";

//windows main application enrtry point
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wc;
	HWND hwnd;
	MSG Msg;
	HBRUSH hBackGrnd = CreateSolidBrush(RGB(242, 242, 242)); //nice light gey color
	//HBRUSH hBackGrnd = CreateSolidBrush(RGB(30, 30, 30)); //Dark mode color?

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	//wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1); //Default color (white)
	wc.hbrBackground = hBackGrnd;
	wc.lpszClassName = gccClassName;
	//wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); //Default icon
	//wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION); //Default icon
	wc.hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_APPICON));
	wc.hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_APPICON), IMAGE_ICON, 16, 16, 0);
	//wc.lpszMenuName = NULL; //when not using a menu
	wc.lpszMenuName = MAKEINTRESOURCE(IDM_MAINMENU);

	//register main window class
	if(!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}	

	//creating the window
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, gccClassName, "Example application", WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, 400, 350, NULL, NULL, hInstance, NULL); 

	//verify window has been created correctly
	//if not bail
	if(hwnd == NULL)
	{
		MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	//https://docs.microsoft.com/en-us/windows/win32/controls/visual-styles-overview
	//https://docs.microsoft.com/en-us/windows/win32/controls/cookbook-overview	

	//initiate common controls libary >V6.00 (commctrl32.dll) for modern visual styles
	// should be located in ..\\lib folder
	INITCOMMONCONTROLSEX icex;

	icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC = ICC_STANDARD_CLASSES;

	//verify that common controls were initiated for modern visual styles
	if(InitCommonControlsEx(&icex) == FALSE)
	{
		MessageBox(hwnd, "Standard classes Not been loaded", "Common controls", MB_ICONINFORMATION | MB_OK);
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//main window nervous system
	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	
	return Msg.wParam;
}