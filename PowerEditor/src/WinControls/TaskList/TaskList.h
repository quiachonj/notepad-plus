//this file is part of notepad++
//Copyright (C)2003 Don HO ( donho@altern.org )
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#ifndef TASKLIST_H
#define TASKLIST_H

#include "Window.h"

#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL 0x020A
#endif //WM_MOUSEWHEEL

#include <commctrl.h>

class TaskList : public Window
{
public:
	TaskList() : Window(), _currentIndex(0), _hFont(NULL), _hFontSelected(NULL) {
		_rc.left = 0;
		_rc.top = 0;
		_rc.right = 150;
		_rc.bottom = 0;
	};

	virtual ~TaskList() {};

	virtual void destroy(){
		if (_hFont)
			DeleteObject(_hFont);
		if (_hFontSelected)
			DeleteObject(_hFontSelected);
		::DestroyWindow(_hSelf);
		_hSelf = NULL;
	};

	void init(HINSTANCE hInst, HWND hwnd, HIMAGELIST hImaLst, int nbItem, int index2set);

	void setFont(TCHAR *fontName, size_t fontSize) {
		if (_hFont)
			::DeleteObject(_hFont);
		if (_hFontSelected)
			::DeleteObject(_hFontSelected);

		_hFont = ::CreateFont(fontSize, 0, 0, 0,
			                   FW_NORMAL,
				               0, 0, 0, 0,
				               0, 0, 0, 0,
					           fontName);

		_hFontSelected = ::CreateFont(fontSize, 0, 0, 0,
			                   FW_BOLD,
				               0, 0, 0, 0,
				               0, 0, 0, 0,
					           fontName);

		if (_hFont)
			::SendMessage(_hSelf, WM_SETFONT, reinterpret_cast<WPARAM>(_hFont), 0);
	};


	RECT adjustSize();
	int getCurrentIndex() const {return _currentIndex;}
	int updateCurrentIndex();

	HIMAGELIST getImgLst() const {
		return ListView_GetImageList(_hSelf, LVSIL_SMALL);
	};

	HFONT GetFontSelected() {return _hFontSelected;}

protected:

	WNDPROC _defaultProc;
	LRESULT runProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK staticProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
		return (((TaskList *)(::GetWindowLongPtr(hwnd, GWL_USERDATA)))->runProc(hwnd, Message, wParam, lParam));
	};

	HFONT _hFont;
	HFONT _hFontSelected;
	int _nbItem;
	int _currentIndex;
	RECT _rc;
};


#endif // TASKLIST_H
