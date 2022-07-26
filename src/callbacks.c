//file containing all callback procedures code

//standard includes
#include <windows.h>
#include <commctrl.h>
#include <fileapi.h>

//custom includes
#include "..\include\resource.h"
#include "..\include\controls.h"
#include "..\include\callbacks.h"

//globals
HWND ghDlgToolbar;
HWND ghDlgLogIn;
HGLOBAL ghSelectedlist;

UINT giReturn;
int* giListItems;
LPCSTR gcFileSaved[MAX_PATH];
LPCSTR gcFileCurrent[MAX_PATH];
BOOL gbFileModified = FALSE;


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HWND hListBox = GetDlgItem(hwnd, IDC_MAIN_LISTBOX);

	switch(msg)
	{
		case WM_CREATE:
			{				
				CreateControls(hwnd); //function to create all controls. Review controls.h and controls.c
			}	
			break;
		case WM_SIZE:

			break;
		case WM_CLOSE:
			DestroyWindow(hwnd);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		case WM_COMMAND:
			switch(LOWORD(wParam))
				{	
					//main menu cases defined in resource.h					
					case IDMI_MAINMENU_FILE_EXIT:
						PostQuitMessage(0);
						break;
					case IDMI_MAINMENU_FILE_MIN:
						ShowWindow(hwnd, SW_MINIMIZE);
						break;
					case IDMI_MAINMENU_AUTH_LOGIN:
						//this is a Model dialog box creation (execution stops for everything else)					
						giReturn = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_AUTH), hwnd, (DLGPROC) AuthDlgProc);
						break;
					case IDMI_MAINMENU_AUTH_LOGOUT:
						{
							for(int i = 0; i < 3; i++)
							{
								Sleep(1000);
								SendMessage((HWND) GetDlgItem(hwnd, IDC_MAIN_STATUSBAR), SB_SETTEXT,  (WPARAM) 0 | 0, (LPARAM) (LPSTR) "\0");
								Sleep(1000);
								SendMessage((HWND) GetDlgItem(hwnd, IDC_MAIN_STATUSBAR), SB_SETTEXT,  (WPARAM) 0 | 0, (LPARAM) (LPSTR) "Logged in as: Guest\0");
							}
						}
						break;
					case IDMI_MAINMENU_HELP_ABOUT:
						//this is a Model dialog box creation (execution stops for everything else)					
						giReturn = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), hwnd, (DLGPROC) AboutDlgProc);

						if(giReturn == IDOK)
						{
							MessageBox(hwnd, "Dialog exited with IDOK.", "Notice", MB_OK | MB_ICONINFORMATION);
						}
						else if(giReturn == IDCANCEL)
						{
							MessageBox(hwnd, "Dialog exited with IDCANCEL.", "Notice", MB_OK | MB_ICONINFORMATION);
						}
						else if(giReturn == -1)
						{
							MessageBox(hwnd, "Dialog failed!", "Error", MB_OK | MB_ICONINFORMATION);
						}
						break;
					case IDMI_MAINMENU_DIALOG_SHOW:
						if(IsWindow(ghDlgToolbar) == 0) //confirm if dialog window already exists
						{
							//this is a Modeless dialog box creation (execution does not stop for everything else)
							ghDlgToolbar = CreateDialog(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_TOOLBAR), hwnd, (DLGPROC)ToolDlgProc);
								
							if(ghDlgToolbar != NULL)
							{
								ShowWindow(ghDlgToolbar, SW_SHOW);
							}
							else
							{
								MessageBox(hwnd, "CreateDialog returned NULL", "Warning!", MB_OK | MB_ICONINFORMATION);
							}						
						}
						else
						{
							ShowWindow(ghDlgToolbar, SW_SHOW);
						}
						break;
					case IDMI_MAINMENU_DIALOG_HIDE:
						ShowWindow(ghDlgToolbar, SW_HIDE);
						break;
					//control cases defined in controls.h
					case  IDC_MAIN_EDIT1:
						
						break;
					case  IDC_MAIN_EDIT2:
						

						break;
					case  IDC_MAIN_LISTBOX:
							switch(HIWORD(wParam))
								{
								case LBN_SELCHANGE:									
									
								break;
								}
						break;
					case  IDC_MAIN_BUTTON1:
						{
							int iText1Len = GetWindowTextLength((HWND)GetDlgItem(hwnd, IDC_MAIN_EDIT1));
							int iText2Len = GetWindowTextLength((HWND)GetDlgItem(hwnd, IDC_MAIN_EDIT2));

							char* cBuff; //buffer for the typed string in Edit 1
							cBuff = (char*) GlobalAlloc(GPTR, iText1Len + 1);

							int iText2Val = 0; //The number of times to insert string into list box

							int iListBoxIndex;

							if(iText1Len > 0)
							{
								GetWindowText((HWND) GetDlgItem(hwnd, IDC_MAIN_EDIT1), cBuff, iText1Len + 1);
							}
							else
							{
								MessageBox(hwnd, "Please type in something to multiply", "Warning!", MB_OK | MB_ICONINFORMATION);
								break;
							}

							if(iText2Len > 0)
							{
								BOOL bSuccess;
								iText2Val = GetDlgItemInt(hwnd, IDC_MAIN_EDIT2, &bSuccess, FALSE);
							}
							else
							{
								MessageBox(hwnd, "Please type in how many times to multiply", "Warning!", MB_OK | MB_ICONINFORMATION);
								break;
							}

							for(int i = 0; i < iText2Val; i++)
							{
								iListBoxIndex = SendDlgItemMessage(hwnd, IDC_MAIN_LISTBOX, LB_ADDSTRING, (WPARAM) 0, (LPARAM) cBuff);
								SendDlgItemMessage(hwnd, IDC_MAIN_LISTBOX, LB_SETITEMDATA, (WPARAM) iListBoxIndex, (LPARAM) iText2Val);
							}
							SendMessage(GetDlgItem(hwnd, IDC_MAIN_EDIT1), WM_SETTEXT, 0, (LPARAM)(LPCTSTR) "\0");
							gbFileModified = TRUE;
						}
						break;
					case  IDC_MAIN_BUTTON2:
						{
							ZeroMemory(&ghSelectedlist, lstrlen(ghSelectedlist));

							int iSelListItemCount = SendMessage(hListBox, LB_GETSELCOUNT, 0, 0);
							giListItems = (int*) GlobalAlloc(GPTR, sizeof(int) * iSelListItemCount);
																	
							SendMessage(hListBox, LB_GETSELITEMS, (WPARAM) iSelListItemCount, (LPARAM) giListItems);

							if(iSelListItemCount > 0)
							{								
								int iSelTextLen = 0;
								LPTSTR cBuff;
								int iListIndex;
								

								ghSelectedlist = GlobalAlloc(GPTR, 32);
								ghSelectedlist = lstrcat(ghSelectedlist, "Are you sure you want to remove:\r\n\r\n\0");
								cBuff = (LPTSTR) GlobalAlloc(GPTR, 1);								

								for(iListIndex = 0; iListIndex < iSelListItemCount; iListIndex++)
								{
									iSelTextLen = SendMessage(hListBox, LB_GETTEXTLEN, (WPARAM) giListItems[iListIndex], (LPARAM) 0);
									cBuff = (LPTSTR) GlobalReAlloc(cBuff, iSelTextLen + 2, GMEM_ZEROINIT | GMEM_MOVEABLE);
									SendMessage(hListBox, LB_GETTEXT, (WPARAM) giListItems[iListIndex], (LPARAM) cBuff);

									ghSelectedlist = GlobalReAlloc(ghSelectedlist, lstrlen(ghSelectedlist) + iSelTextLen + 2, GMEM_ZEROINIT | GMEM_MOVEABLE);
									ghSelectedlist = lstrcat(ghSelectedlist, cBuff);
									ghSelectedlist = lstrcat(ghSelectedlist, "\r\n");									
								}

								giReturn = MessageBox(hwnd, ghSelectedlist, "Warning!", MB_ICONEXCLAMATION | MB_YESNO);
								
								if(giReturn == IDYES)
								{
									iListIndex = 0;	

									while(SendMessage(hListBox, LB_GETSELCOUNT, 0, 0) > 0)
									{							
										if(SendMessage(hListBox, LB_GETSEL, (WPARAM) iListIndex, 0 ) > 0)
										{
											SendMessage(hListBox, LB_DELETESTRING, (WPARAM) iListIndex, 0 );
											iListIndex = 0;
										}								
										else
										{
											iListIndex++;
										}																											
									}
									gbFileModified = TRUE;		
								}
							}
							else
							{
								MessageBox(hwnd, "Please select items from the list", "Information", MB_OK | MB_ICONINFORMATION);
							}							
						}
						break;
					case IDC_MAIN_BUTTON3:
						SendMessage(hListBox, LB_RESETCONTENT, (WPARAM) 0, (LPARAM) 0);
						gbFileModified = TRUE;
						break;
					//toolbar cases defined in controls.h
					case IDC_MAIN_TOOLBAR_FILE_NEW:
						{
							int iListBoxItemCount = SendMessage(hListBox, LB_GETCOUNT , 0, 0);

						

							if(iListBoxItemCount > 0 && gbFileModified == TRUE)
							{
								if( MessageBox(hwnd, "Do you want to save changes to the current file?", "Warning!", MB_ICONQUESTION | MB_YESNO) == IDYES)
								{
									OPENFILENAME sOpenFileName;
									char cPathFileToSave[MAX_PATH] = "\0";

									ZeroMemory(&sOpenFileName, sizeof(sOpenFileName));

									

									sOpenFileName.lStructSize = sizeof(sOpenFileName);
									sOpenFileName.hwndOwner = hwnd;
									sOpenFileName.lpstrFilter = "Text Files (*.txt)\0*.txt\0All Files (*.*)\0*.*\0";
									sOpenFileName.lpstrFile = cPathFileToSave;
									sOpenFileName.nMaxFile = MAX_PATH;
									//For opening a file
									//ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
									
									//For saving a file
									sOpenFileName.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT; 
									sOpenFileName.lpstrDefExt = "txt";

									//if(GetOpenFileName(&sOpenFileName) > 0) //for opening a file

									if(GetSaveFileName(&sOpenFileName) > 0) //for saving a file
									{
										//creating the new file
										HANDLE hFileToSave;
										hFileToSave = CreateFile(cPathFileToSave, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

										int iListIndex = 0;
										int iListItemLen = 2;

										LPTSTR cpListItem;
										cpListItem = (LPTSTR) GlobalAlloc(GPTR, 1);

										for(iListIndex = 0; iListIndex < iListBoxItemCount; iListIndex++)
										{
											iListItemLen = SendMessage(hListBox, LB_GETTEXTLEN, iListIndex, 0);
											cpListItem = (LPTSTR) GlobalReAlloc(cpListItem, iListItemLen + 2, GMEM_ZEROINIT | GMEM_MOVEABLE);											
																						
											if(SendMessage(hListBox, LB_GETTEXT, iListIndex, (LPARAM) cpListItem) > 0)
											{
												lstrcat(cpListItem, "\r\n");
												WriteFile(hFileToSave, cpListItem, iListItemLen + 2, NULL, NULL);
											}
											else
											{
												MessageBox(hwnd, "Unable to retrieve list box item text", "Information", MB_OK | MB_ICONINFORMATION);
											}
										}										
										CloseHandle(hFileToSave);
										gbFileModified = FALSE;
										SendMessage((HWND) GetDlgItem(GetParent(hwnd), IDC_MAIN_STATUSBAR), SB_SETTEXT,  (WPARAM) 1 | 0, (LPARAM) (LPSTR) "Status: File Saved\0");

									}
									else
									{
										MessageBox(hwnd, "Unable to crate file", "Information", MB_OK | MB_ICONINFORMATION);
									}

								}
							}

						}
						break;
					case IDC_MAIN_TOOLBAR_FILE_OPEN:

						break;
					case IDC_MAIN_TOOLBAR_FILE_SAVEAS:

						break;					
				}
				break;
				//Other menu commands...
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
	}
		return FALSE;
}

BOOL CALLBACK AboutDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_INITDIALOG:
			return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDOK:
					EndDialog(hwnd, IDOK);
					break;
				case IDCANCEL:
					EndDialog(hwnd, IDCANCEL);
					break;
			}
			break;
		default:
			return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK AuthDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_CLOSE:
			EndDialog(hwnd, Message);
			break;
		case WM_DESTROY:
			EndDialog(hwnd, Message);
			break;
		case WM_INITDIALOG:
			return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDC_AUTH_BUTTON1:
					{						
						int iTextLen1 = GetWindowTextLength((HWND) GetDlgItem(hwnd, IDC_AUTH_EDIT1));
						int iTextLen2 = GetWindowTextLength((HWND) GetDlgItem(hwnd, IDC_AUTH_EDIT2));

						if(iTextLen1 > 0 && iTextLen2 > 0)
						{
							PSTR cBuff1; //buffer for the pre string 
							cBuff1 = LocalAlloc(GPTR, iTextLen1 + 13);
							ZeroMemory(cBuff1, iTextLen1 + 13);
							lstrcat(cBuff1, "Logged in as: ");

							PSTR cBuff2; //buffer for the typed string in Edit 1
							cBuff2 = LocalAlloc(GPTR, iTextLen1 + 1);
							ZeroMemory(cBuff2, iTextLen1 + 1);
							
							GetWindowText((HWND) GetDlgItem(hwnd, IDC_AUTH_EDIT1), cBuff2, iTextLen1 + 1);
							lstrcat(cBuff1, cBuff2);
							SendMessage((HWND) GetDlgItem(GetParent(hwnd), IDC_MAIN_STATUSBAR), SB_SETTEXT,  (WPARAM) 0 | 0, (LPARAM) (LPSTR) cBuff1);

							LocalFree(cBuff1);
							LocalFree(cBuff2);
						}
						else
						{
							MessageBox(hwnd, "User name and password are required", "Information", MB_OK | MB_ICONINFORMATION);

							if(iTextLen1 < 1)
							{								
								SendMessage(GetDlgItem(hwnd, IDC_AUTH_EDIT1), WM_SETTEXT, 0, (LPARAM)(LPCTSTR) "type user name here\0");
							}																				
							break;
						}
					}
					EndDialog(hwnd, IDC_AUTH_BUTTON1);
					break;
				case IDC_AUTH_EDIT1:
					switch(HIWORD(wParam))
						{ 
							case EN_SETFOCUS:
							{	
								int iTextLen1 = GetWindowTextLength((HWND) GetDlgItem(hwnd, IDC_AUTH_EDIT1));					

								if(iTextLen1 > 0)
								{									
									SendMessage(GetDlgItem(hwnd, IDC_AUTH_EDIT1), WM_SETTEXT, 0, (LPARAM)(LPCTSTR) "\0");
								}
							}
						}
					break;
				case IDC_AUTH_BUTTON2:
					EndDialog(hwnd, IDC_AUTH_BUTTON2);
					break;
			}
			break;
		default:
			return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK ToolDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
				case IDC_TOOLBAR_PRESS:
					MessageBox(hwnd, "Button A clicked", "Button press", MB_OK | MB_ICONEXCLAMATION);
					break;
				case IDC_TOOLBAR_OTHER:
					MessageBox(hwnd, "Button B clicked", "Button press", MB_OK | MB_ICONEXCLAMATION);
					break;
			}
			break;
		default:
			return FALSE;
	}
	return TRUE;
}