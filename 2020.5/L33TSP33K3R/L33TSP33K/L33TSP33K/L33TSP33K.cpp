// program that transfers english to l33tsp33k.


// Idea is to take the char values of the alphebet and
// assign them to numbers.

#include <iostream>
#include <string>
#include <Windows.h>

std::string L33TG3N(std::string input)
{
	int iCaseSelect = 0;
	for (int i = 0; i < input.length(); i++)
	{
		iCaseSelect = input[i];
		switch (iCaseSelect)
		{
		case 65: input[i] = '4'; break; // A
		case 69: input[i] = '3'; break; // E
		case 76:  input[i] = '1'; break; // L
		case 79: input[i] = '0'; break; // O
		case 97: input[i] = '4'; break; // a
		case 101: input[i] = '3'; break; // e
		case 108:  input[i] = '1'; break; // l
		case 111: input[i] = '0'; break; // o

		default: break;
		}
	}
	return input;
}

void CopyToClip(HWND hwnd, const std::string &s) {
	OpenClipboard(hwnd);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size() + 1);
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size() + 1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}



int main()
{
	start:
	std::string sPhraseInput = "";
    std::cout << "Please enter your phrase: \n";
	std::getline(std::cin, sPhraseInput);
	size_t len = strlen(sPhraseInput.c_str());
	HWND hwnd = GetDesktopWindow();
	CopyToClip(hwnd, L33TG3N(sPhraseInput));
	goto start;
}
