//File containing contol reladed definitions and function prototypes

//conditional header guard wrapper to avoid proccesing more than once
#ifndef CONTROLLS_H
	#define CONTROLLS_H

	//Controls
	#define IDC_TOOLBAR_PRESS 3201
	#define IDC_TOOLBAR_OTHER 3202

	#define IDC_AUTH_LABEL1	3301
	#define IDC_AUTH_LABEL2 3302
	#define IDC_AUTH_EDIT1 3303
	#define IDC_AUTH_EDIT2 3304
	#define IDC_AUTH_BUTTON1 3305
	#define IDC_AUTH_BUTTON2 3306

	#define IDC_MAIN_LABEL1 1001
	#define IDC_MAIN_EDIT1 1002
	#define IDC_MAIN_EDIT2 1003
	#define IDC_MAIN_LABEL2 1004
	#define IDC_MAIN_LISTBOX 1005
	#define IDC_MAIN_BUTTON1 1006
	#define IDC_MAIN_BUTTON2 1007
	#define IDC_MAIN_BUTTON3 1008
	#define IDC_MAIN_STATUSBAR 1009
	#define IDC_MAIN_TOOLBAR 1010

	//Command IDs for tool bar
	#define IDC_MAIN_TOOLBAR_FILE_NEW 1111
	#define IDC_MAIN_TOOLBAR_FILE_OPEN 1112
	#define IDC_MAIN_TOOLBAR_FILE_SAVEAS 1113

	//prototypes
	void CreateControls(HWND hwnd);

//end of wrapper
#endif