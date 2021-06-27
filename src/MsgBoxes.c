//File containing custom message boxes reladed code

//Standard includes
#include <windows.h>
#include <stddef.h>
#include <stdio.h>

//custom includes
#include "..\include\MsgBoxes.h"

void InfoBox(char* FormatText, char* Var)
{
	char *DisplayPrompt;
	size_t DisplayPromptLen = strlen(FormatText) + strlen(Var) + 1;

	DisplayPrompt = calloc(DisplayPromptLen, sizeof(DisplayPrompt));

	if(DisplayPrompt != NULL && snprintf(DisplayPrompt, DisplayPromptLen * sizeof(DisplayPrompt), FormatText, Var) > 0)
	{
		MessageBox(NULL, DisplayPrompt, "Information", MB_ICONINFORMATION | MB_OK | MB_TOPMOST);
	}

	free(DisplayPrompt);

}
void ErrorBox(char* FormatText, char * Var)
{
	char *DisplayPrompt;
	size_t DisplayPromptLen = strlen(FormatText) + strlen(Var) + 1;

	DisplayPrompt = calloc(DisplayPromptLen, sizeof(DisplayPrompt));

	if(DisplayPrompt != NULL && snprintf(DisplayPrompt, DisplayPromptLen * sizeof(DisplayPrompt), FormatText, Var) > 0)
	{
		MessageBox(NULL, DisplayPrompt, "Error", MB_ICONERROR | MB_OK | MB_TOPMOST);
	}

	free(DisplayPrompt);

}
void NumBox(char* FormatText, int Var)
{
	char *DisplayPrompt;
	size_t DisplayPromptLen = strlen(FormatText) + sizeof(Var) + 1;

	DisplayPrompt = calloc(DisplayPromptLen, sizeof(DisplayPrompt));

	if(DisplayPrompt != NULL && snprintf(DisplayPrompt, DisplayPromptLen * sizeof(DisplayPrompt), FormatText, Var) > 0)
	{
		MessageBox(NULL, DisplayPrompt, "Information", MB_ICONINFORMATION | MB_OK | MB_TOPMOST);
	}

	free(DisplayPrompt);

}
