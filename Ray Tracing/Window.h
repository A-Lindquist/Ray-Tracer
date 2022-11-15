#pragma once

#ifndef WINDOW_H
#define WINDOW_H

#include <Windows.h>
#include <stdint.h>

#define u32 uint32_t

LRESULT CALLBACK windowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
public:
	Window();
	Window(const Window&) = delete;
	Window& operator = (const Window&) = delete;
	~Window();

	bool processMessages();

	HWND m_hWnd;
	int width;
	int height;

	void* memory;
	BITMAPINFO bitmap_info;

	u32* pixel;

private:
	HINSTANCE m_hInstance;
};

#endif // !WINDOW_H