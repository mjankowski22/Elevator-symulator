// draw.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "draw2.h"
#include <vector>
#include <cstdio>
#include <vector>
#include <string>
#include <time.h>

using namespace std;

#define MAX_LOADSTRING 100
#define TMR_1 1



// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

INT value;
INT x;
time_t time1, time2;
bool flag_time = true;


class Floor
{
public:

	int height;
	vector<int> passengers;
	int number;
	RECT drawArea;



	void repaint_draw_area(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps)
	{


		hdc = GetDC(hWnd);
		Graphics graphics(hdc);
		FillRect(hdc, &this->drawArea, (HBRUSH)(RGB(255, 255, 255)));
		Pen pen(Color(255, 255, 0, 0));
		Pen pen1(Color(255, 0, 0, 0));





		if (this->number == 1 || this->number == 3)
		{
			for (int i = 0; i < this->passengers.size(); i++)
			{
				graphics.DrawLine(&pen1, 900 + 65 * i, this->height + 126, 910 + 65 * i, this->height + 106);
				graphics.DrawLine(&pen1, 920 + 65 * i, this->height + 126, 910 + 65 * i, this->height + 106);
				graphics.DrawLine(&pen1, 910 + 65 * i, this->height + 106, 910 + 65 * i, this->height + 86);
				graphics.DrawLine(&pen1, 910 + 65 * i, this->height + 86, 918 + 65 * i, this->height + 105);
				graphics.DrawLine(&pen1, 910 + 65 * i, this->height + 86, 902 + 65 * i, this->height + 105);
				graphics.DrawRectangle(&pen1, 900 + 65 * i, this->height + 66, 20, 20);

				wchar_t buffer[256];
				wsprintfW(buffer, L"%d", this->passengers[i]);
				TextOut(hdc, 906 + 65 * i, this->height + 68, buffer, 1);

			}
		}
		else
		{
			for (int i = 0; i < this->passengers.size(); i++)
			{

				graphics.DrawLine(&pen1, 480 - 65 * i, this->height + 126, 490 - 65 * i, this->height + 106);
				graphics.DrawLine(&pen1, 500 - 65 * i, this->height + 126, 490 - 65 * i, this->height + 106);
				graphics.DrawLine(&pen1, 490 - 65 * i, this->height + 106, 490 - 65 * i, this->height + 86);
				graphics.DrawLine(&pen1, 490 - 65 * i, this->height + 86, 498 - 65 * i, this->height + 105);
				graphics.DrawLine(&pen1, 490 - 65 * i, this->height + 86, 482 - 65 * i, this->height + 105);
				graphics.DrawRectangle(&pen1, 480 - 65 * i, this->height + 66, 20, 20);

				wchar_t buffer[256];
				wsprintfW(buffer, L"%d", this->passengers[i]);
				TextOut(hdc, 486 - 65 * i, this->height + 68, buffer, 1);

			}
		}


		ReleaseDC(hWnd, hdc);

	}

	bool add_passenger(int x)
	{
		bool flag=false;


		if (this->passengers.size() <7)
		{
			this->passengers.push_back(x);
			flag = true;
		}
		
		return flag;
	}

	int delete_passenger()
	{
		int number = this->passengers[0];
		this->passengers.erase(this->passengers.begin());

		return number;
	}
};

vector<Floor> floors(5);

class Elevator
{
public:
	int velocity = 1;
	int floors_to_go[5] = { 0,0,0,0,0 };
	int floors_starting[5] = { 0,0,0,0,0 };
	int width = 330, height = 100;
	int person_width = 55, person_height = 55;
	int x = 535, y = 581;
	bool is_moving = false;
	int current_floor = 0;
	bool moving_up = true;
	int current_weight = 0;
	int max_weight = 600;
	vector<int> passengers;


	bool is_on_floor()
	{
		for (int i = 0; i < 5; i++)
		{
			if (this->y + this->height == floors[i].height + 127)
			{
				this->current_floor = i;
				return true;
			}


		}
		return false;
	}

	void repaint_draw_area(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps)
	{
		hdc = GetDC(hWnd);
		Graphics graphics(hdc);
		RECT draw = { 530, 15, 870, 690 };
		FillRect(hdc, &draw, (HBRUSH)(RGB(255, 255, 255)));
		draw = { 880,15,950,100 };
		FillRect(hdc, &draw, (HBRUSH)(RGB(255, 255, 255)));

		TextOut(hdc, 880, 15, L"Actual weight:", 13);

		if (this->current_weight != 0)
		{
			wchar_t buffer[256];
			wsprintfW(buffer, L"%d", this->current_weight);
			int len = 0;
			int liczba = this->current_weight;
			while (liczba > 0)
			{
				liczba = liczba / 10;
				len++;
			}
			TextOut(hdc, 920, 30, buffer, len);
		}

		else
		{
			TextOut(hdc, 920, 30, L"0", 1);
		}
		Pen pen(Color(255, 255, 0, 0));
		graphics.DrawRectangle(&pen, this->x, this->y, this->width, this->height);
		Pen pen1(Color(255, 0, 0, 0));
		for (int i = 0; i < this->passengers.size(); i++)
		{
			graphics.DrawLine(&pen1, 548 + 40 * i, this->y + 100, 558 + 40 * i, this->y + 80);
			graphics.DrawLine(&pen1, 568 + 40 * i, this->y + 100, 558 + 40 * i, this->y + 80);
			graphics.DrawLine(&pen1, 558 + 40 * i, this->y + 80, 558 + 40 * i, this->y + 60);
			graphics.DrawLine(&pen1, 558 + 40 * i, this->y + 60, 550 + 40 * i, this->y + 79);
			graphics.DrawLine(&pen1, 558 + 40 * i, this->y + 60, 566 + 40 * i, this->y + 79);
			graphics.DrawRectangle(&pen1, 548 + 40 * i, this->y + 40, 20, 20);
			wchar_t buffer[256];
			wsprintfW(buffer, L"%d", this->passengers[i]);
			TextOut(hdc, 555 + i * 40, this->y + 43, buffer, 1);
		}


		ReleaseDC(hWnd, hdc);
	}

	void move(HWND hWnd, HDC& hdc, PAINTSTRUCT& ps)
	{
		if (this->moving_up)
		{
			this->y -= velocity;
		}
		else
		{
			this->y += velocity;
		}
		this->repaint_draw_area(hWnd, hdc, ps);
	}
	void set_current_weight()
	{
		this->current_weight = 70 * this->passengers.size();
	}

	void let_passengers_in(int floor_number)
	{


		if (this->moving_up)
		{

			for (int i = 0; i < floors[floor_number].passengers.size(); i++)
			{
				if (floors[this->current_floor].passengers[i] > this->current_floor && this->current_weight < this->max_weight - 70)
				{
					this->floors_starting[floors[floor_number].passengers[i]] = 1;
					this->passengers.push_back(floors[floor_number].passengers[i]);
					floors[floor_number].passengers.erase(floors[floor_number].passengers.begin() + i);
					i--;
					this->set_current_weight();
				}
			}

		}
		else
		{

			for (int i = 0; i < floors[floor_number].passengers.size(); i++)
			{
				if (floors[this->current_floor].passengers[i] < this->current_floor && this->current_weight < this->max_weight - 70)
				{

					this->floors_starting[floors[floor_number].passengers[i]] = 1;
					this->passengers.push_back(floors[floor_number].passengers[i]);
					floors[floor_number].passengers.erase(floors[floor_number].passengers.begin() + i);
					i--;
					this->set_current_weight();

				}
			}

		}




	}

	void let_passengers_out(int floor_number)
	{
		for (int i = 0; i < this->passengers.size(); i++)
		{
			if (this->passengers[i] == floor_number)
			{
				this->passengers.erase(this->passengers.begin() + i);
				i -= 1;
			}
		}
		this->set_current_weight();
	}

	bool check_passenger_on_floor(int floor_number)
	{
		for (int i = 0; i < this->passengers.size(); i++)
		{
			if (this->passengers[i] == floor_number && this->current_weight < this->max_weight)
			{
				return true;
			}
		}
		return false;
	}
};

Elevator elevator;

// buttons
HWND hwndButton;






// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	Buttons(HWND, UINT, WPARAM, LPARAM);













// main function (exe hInstance)
int APIENTRY _tWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPTSTR    lpCmdLine,
	int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	value = 0;

	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR           gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_DRAW, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);



	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_DRAW));

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	GdiplusShutdown(gdiplusToken);

	return (int)msg.wParam;
}

void add_floor_to_queue(Elevator& elevator, int floor_starting)
{
	if (elevator.floors_to_go[0] == 0 && elevator.floors_to_go[1] == 0 && elevator.floors_to_go[2] == 0 && elevator.floors_to_go[3] == 0 && elevator.floors_to_go[4] == 0 && elevator.floors_starting[0] == 0 && elevator.floors_starting[1] == 0 && elevator.floors_starting[2] == 0 && elevator.floors_starting[3] == 0 && elevator.floors_starting[4] == 0)
	{
		elevator.floors_to_go[floor_starting] = 1;
		if (elevator.current_floor < floor_starting) elevator.moving_up = true;
		else elevator.moving_up = false;
	}
	else
	{
		elevator.floors_to_go[floor_starting] = 1;
	}
}






//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_DRAW));
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCE(IDC_DRAW);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;


	hInst = hInstance; // Store instance handle (of exe) in our global variable

	// main window
	hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	// create button and store the handle                                                       

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("3"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		10, 10,                                  // the left and top co-ordinates
		70, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON1,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 45,
		70, 25,
		hWnd,
		(HMENU)ID_BUTTON2,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 80,
		70, 25,
		hWnd,
		(HMENU)ID_BUTTON3,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("0"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 115,
		70, 25,
		hWnd,
		(HMENU)ID_BUTTON4,
		hInstance,
		NULL);

	// ------------------------------ //

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("4"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1325, 145,                                  // the left and top co-ordinates
		70, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON5,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1325, 180,
		70, 25,
		hWnd,
		(HMENU)ID_BUTTON6,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1325, 215,
		70, 25,
		hWnd,
		(HMENU)ID_BUTTON7,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("0"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1325, 250,
		70, 25,
		hWnd,
		(HMENU)ID_BUTTON8,
		hInstance,
		NULL);

	// ---------------------------------------- //

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("4"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		10, 282,                                  // the left and top co-ordinates
		70, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON9,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 317,
		70, 25,
		hWnd,
		(HMENU)ID_BUTTON10,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 352,
		70, 25,
		hWnd,
		(HMENU)ID_BUTTON11,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("0"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 387,
		70, 25,
		hWnd,
		(HMENU)ID_BUTTON12,
		hInstance,
		NULL);

	// ------------------------------------- //

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("4"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		1325, 417,                                  // the left and top co-ordinates
		70, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON13,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1325, 452,
		70, 25,
		hWnd,
		(HMENU)ID_BUTTON14,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1325, 487,
		70, 25,
		hWnd,
		(HMENU)ID_BUTTON15,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("0"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		1325, 522,
		70, 25,
		hWnd,
		(HMENU)ID_BUTTON16,
		hInstance,
		NULL);

	// ------------------------------------------------ //

	hwndButton = CreateWindow(TEXT("button"),                      // The class name required is button
		TEXT("4"),                  // the caption of the button
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,  // the styles
		10, 554,                                  // the left and top co-ordinates
		70, 25,                              // width and height
		hWnd,                                 // parent window handle
		(HMENU)ID_BUTTON17,                   // the ID of your button
		hInstance,                            // the instance of your application
		NULL);                               // extra bits you dont really need

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("3"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 589,
		70, 25,
		hWnd,
		(HMENU)ID_BUTTON18,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("2"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 624,
		70, 25,
		hWnd,
		(HMENU)ID_BUTTON19,
		hInstance,
		NULL);

	hwndButton = CreateWindow(TEXT("button"),
		TEXT("1"),
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		10, 659,
		70, 25,
		hWnd,
		(HMENU)ID_BUTTON20,
		hInstance,
		NULL);



	// Pietro 0

	floors[0].height = 554;
	floors[0].number = 0;
	floors[0].drawArea = { 80,544,525,680 };


	// Pietro 1

	floors[1].height = 418;
	floors[1].number = 1;
	floors[1].drawArea = { 880,408,1320,544 };


	// Pietro 2

	floors[2].height = 282;
	floors[2].number = 2;
	floors[2].drawArea = { 80, 272, 525, 408 };


	// Pietro 3

	floors[3].height = 146;
	floors[3].number = 3;
	floors[3].drawArea = { 880,136,1320,272 };


	// Pietro 4

	floors[4].height = 10;
	floors[4].number = 4;
	floors[4].drawArea = { 80,10,525,136 };



	// create button and store the handle                                                       





	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window (low priority)
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;


	switch (message)
	{
	case WM_COMMAND:
		wmId = LOWORD(wParam);
		wmEvent = HIWORD(wParam);

		// MENU & BUTTON messages
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
		{
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		}
		case IDM_EXIT:
		{
			DestroyWindow(hWnd);
			break;
		}
		case ID_BUTTON1:
		{
			if (floors[4].add_passenger(3) == true)
			{
				floors[4].repaint_draw_area(hWnd, hdc, ps);
				add_floor_to_queue(elevator, 4);
				
			}
			break;
		}
		case ID_BUTTON2:
		{
			if (floors[4].add_passenger(2) == true)
			{
				floors[4].repaint_draw_area(hWnd, hdc, ps);
				add_floor_to_queue(elevator, 4);
				
			}
			break;
		}
		case ID_BUTTON3:
		{
			if (floors[4].add_passenger(1)== true)
			{
				floors[4].repaint_draw_area(hWnd, hdc, ps);
				add_floor_to_queue(elevator, 4);
				
			}
			break;
		}
		case ID_BUTTON4:
		{
			if (floors[4].add_passenger(0) == true)
			{
				floors[4].repaint_draw_area(hWnd, hdc, ps);
				add_floor_to_queue(elevator, 4);
				
			}
			break;
		}
		case ID_BUTTON5:
		{
			if (floors[3].add_passenger(4) == true)
			{
				floors[3].repaint_draw_area(hWnd, hdc, ps);
				add_floor_to_queue(elevator, 3);
				
			}
			break;
		}
		case ID_BUTTON6:
		{
			if (floors[3].add_passenger(2) == true)
			{
				floors[3].repaint_draw_area(hWnd, hdc, ps);
				add_floor_to_queue(elevator, 3);
				
			}
			break;
		}
		case ID_BUTTON7:
		{
			if (floors[3].add_passenger(1) == true)
			{
				floors[3].repaint_draw_area(hWnd, hdc, ps);
				add_floor_to_queue(elevator, 3);
				
			}
			break;
		}
		case ID_BUTTON8:
		{
			if (floors[3].add_passenger(0) == true)
			{
				floors[3].repaint_draw_area(hWnd, hdc, ps);
				add_floor_to_queue(elevator, 3);
				
			}
			break;
		}
		case ID_BUTTON9:
		{
			
			if (floors[2].add_passenger(4) == true)
			{
				floors[2].repaint_draw_area(hWnd, hdc, ps);
				add_floor_to_queue(elevator, 2);
				
			}
			break;
		}
		case ID_BUTTON10:
		{
			if (floors[2].add_passenger(3) == true)
			{
				floors[2].repaint_draw_area(hWnd, hdc, ps);
				add_floor_to_queue(elevator, 2);
				
			}
			break;
		}
		case ID_BUTTON11:
		{
			if (floors[2].add_passenger(1) == true)
			{
				floors[2].repaint_draw_area(hWnd, hdc, ps);
				add_floor_to_queue(elevator, 2);
				
			}
			break;
		}
		case ID_BUTTON12:
		{
			if (floors[2].add_passenger(0) == true)
			{
				floors[2].repaint_draw_area(hWnd, hdc, ps);
				add_floor_to_queue(elevator, 2);
				
			}
			break;
		}
		case ID_BUTTON13:
		{
			if (floors[1].add_passenger(4) == true)
			{
				floors[1].repaint_draw_area(hWnd, hdc, ps);
				add_floor_to_queue(elevator, 1);
				
			}
			break;
		}
		case ID_BUTTON14:
		{
			if (floors[1].add_passenger(3) == true)
			{
				floors[1].repaint_draw_area(hWnd, hdc, ps);
				add_floor_to_queue(elevator, 1);
				
			}
			break;
		}
		case ID_BUTTON15:
		{
			if (floors[1].add_passenger(2) == true)
			{
				floors[1].repaint_draw_area(hWnd, hdc, ps);
				add_floor_to_queue(elevator, 1);
				
			}
			break;
		}
		case ID_BUTTON16:
		{

			if (floors[1].add_passenger(0) == true)
			{
				floors[1].repaint_draw_area(hWnd, hdc, ps);
				add_floor_to_queue(elevator, 1);
				
			}
			break;
		}
		case ID_BUTTON17:
		{
			if (floors[0].add_passenger(4) == true)
			{
				floors[0].repaint_draw_area(hWnd, hdc, ps);
				add_floor_to_queue(elevator, 0);
				
			}
			break;
		}
		case ID_BUTTON18:
		{
			if (floors[0].add_passenger(3) == true)
			{
				floors[0].repaint_draw_area(hWnd, hdc, ps);
				add_floor_to_queue(elevator, 0);
				
			}
			break;
		}
		case ID_BUTTON19:
		{
			if (floors[0].add_passenger(2) == true)
			{
				floors[0].repaint_draw_area(hWnd, hdc, ps);
				add_floor_to_queue(elevator, 0);
				
			}
			break;
		}
		case ID_BUTTON20:
		{
			if (floors[0].add_passenger(1) == true)
			{
				floors[0].repaint_draw_area(hWnd, hdc, ps);
				add_floor_to_queue(elevator, 0);
				
			}
			break;
		}

		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		}
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		//Rysowanie rzeczy niezmieniajacych sie

		Graphics graphics(hdc);


		Pen pen3(Color(255, 0, 0, 0));

		graphics.DrawRectangle(&pen3, 525, 10, 350, 680);
		graphics.DrawLine(&pen3, 100, 136, 525, 136);
		graphics.DrawLine(&pen3, 875, 272, 1300, 272);
		graphics.DrawLine(&pen3, 100, 408, 525, 408);
		graphics.DrawLine(&pen3, 875, 544, 1300, 544);
		graphics.DrawLine(&pen3, 100, 680, 525, 680);
		elevator.repaint_draw_area(hWnd, hdc, ps);


		EndPaint(hWnd, &ps);
		break;
	}
	case WM_DESTROY:
	{
		KillTimer(hWnd, TMR_1);
		PostQuitMessage(0);
		break;
	}
	case WM_CREATE:
	{
		SetTimer(hWnd, TMR_1, 15, 0);
		break;
	}
	case WM_TIMER:
	{
		hdc = GetDC(hWnd);
		if (elevator.floors_to_go[0] == 1 || elevator.floors_to_go[1] == 1 || elevator.floors_to_go[2] == 1 || elevator.floors_to_go[3] == 1 || elevator.floors_to_go[4] == 1 || elevator.floors_starting[0] == 1 || elevator.floors_starting[1] == 1 || elevator.floors_starting[2] == 1 || elevator.floors_starting[3] == 1 || elevator.floors_starting[4] == 1)
		{
			flag_time = true;


			if (elevator.moving_up)
			{
				bool flag = false;
				for (int i = elevator.current_floor + 1; i < 5; i++)
				{
					if (elevator.floors_to_go[i] == 1 || elevator.floors_starting[i] == 1)
					{
						flag = true;
						elevator.moving_up = true;
						break;
					}
				}
				if (!flag)
				{
					for (int i = elevator.current_floor - 1; i >= 0; i--)
					{
						if (elevator.floors_to_go[i] == 1 || elevator.floors_starting[i] == 1)
						{

							elevator.moving_up = false;
							break;
						}
					}

				}
			}
			else
			{
				bool flag = false;
				for (int i = elevator.current_floor - 1; i >= 0; i--)
				{
					if (elevator.floors_to_go[i] == 1 || elevator.floors_starting[i] == 1)
					{
						flag = true;
						elevator.moving_up = false;
						break;
					}
				}
				if (!flag)
				{
					for (int i = elevator.current_floor + 1; i < 5; i++)
					{
						if (elevator.floors_to_go[i] == 1 || elevator.floors_starting[i] == 1)
						{

							elevator.moving_up = true;
							break;
						}
					}

				}
			}


			if (elevator.is_on_floor())
			{
				if (elevator.floors_starting[elevator.current_floor] == 1)
				{
					Sleep(1000);
					elevator.let_passengers_out(elevator.current_floor);
					elevator.repaint_draw_area(hWnd, hdc, ps);
					Sleep(1000);
					floors[elevator.current_floor].repaint_draw_area(hWnd, hdc, ps);
					elevator.repaint_draw_area(hWnd, hdc, ps);
					elevator.floors_starting[elevator.current_floor] = 0;
				}
				if (elevator.moving_up)
				{
					bool flag = false;
					
						for (int i = 0; i < floors[elevator.current_floor].passengers.size(); i++)
						{
							if (floors[elevator.current_floor].passengers[i] > elevator.current_floor)
							{
								flag = true;
								break;

							}
						}
						if (!flag)
						{
							int max = elevator.current_floor;
							for (int i = max; i < 5; i++)
							{
								if (elevator.floors_to_go[i] ==1) max = i;
								if (elevator.floors_starting[i] ==1) max = i;
							}
							if (max == elevator.current_floor)
							{
								flag = true;
								elevator.moving_up = false;
							}
						}
						if (elevator.current_weight + 70 > elevator.max_weight && elevator.floors_starting[elevator.current_floor] == 0)
						{
							elevator.move(hWnd, hdc, ps);
						}
						else if (flag)
						{
							Sleep(1000);
							elevator.let_passengers_out(elevator.current_floor);
							elevator.repaint_draw_area(hWnd, hdc, ps);
							Sleep(1000);
							elevator.let_passengers_in(elevator.current_floor);
							floors[elevator.current_floor].repaint_draw_area(hWnd, hdc, ps);
							elevator.repaint_draw_area(hWnd, hdc, ps);
							if (floors[elevator.current_floor].passengers.size() == 0)
								elevator.floors_to_go[elevator.current_floor] = 0;

							

						}
						else
						{
							elevator.move(hWnd, hdc, ps);
						}
					
				}
				else
				{
					bool flag = false;
				
					for (int i = 0; i < floors[elevator.current_floor].passengers.size(); i++)
					{
						if (floors[elevator.current_floor].passengers[i] < elevator.current_floor)
						{
							flag = true;
							break;

						}
					}
					if (!flag)
					{
						int min = elevator.current_floor;
						for (int i = min; i >= 0; i--)
						{
							if (elevator.floors_to_go[i] == 1) min = i;
							if (elevator.floors_starting[i] == 1) min = i;
						}
						if (min == elevator.current_floor)
						{
							flag = true;
							elevator.moving_up =true;
						}
					}
					if (elevator.current_weight +70 > elevator.max_weight && elevator.floors_starting[elevator.current_floor] == 0)
					{
						elevator.move(hWnd, hdc, ps);
					}
					else if (flag)
					{
						Sleep(1000);
						elevator.let_passengers_out(elevator.current_floor);
						elevator.repaint_draw_area(hWnd, hdc, ps);
						Sleep(1000);
						elevator.let_passengers_in(elevator.current_floor);
						floors[elevator.current_floor].repaint_draw_area(hWnd, hdc, ps);
						elevator.repaint_draw_area(hWnd, hdc, ps);
						if (floors[elevator.current_floor].passengers.size() == 0)
							elevator.floors_to_go[elevator.current_floor] = 0;
						
						if (elevator.floors_starting[0] == 1 && floors[0].passengers.size() == 0 && elevator.passengers.size()==0) elevator.floors_starting[0] = 0;
					}
					else
					{
						elevator.move(hWnd, hdc, ps);
					}
				}
			
				



			}

			else
			{
				elevator.move(hWnd, hdc, ps);
			}
		}
		else
		{
			if (flag_time)
			{
				flag_time = false;
				time(&time1);
			}
			if (!flag_time)
			{
				time(&time2);
				if ((time2 - time1) > 4.9 && (time2 - time1) < 5.1)
				{
					elevator.floors_starting[0] = 1;
				}
			}
		}
		

		if (elevator.current_floor == 0) elevator.moving_up = true;
		else if (elevator.current_floor == 4) elevator.moving_up = false;

		ReleaseDC(hWnd, hdc);
		break;
	}



	default:
	{
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}