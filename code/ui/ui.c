#include <windows.h>
#include <commctrl.h>
#include <strsafe.h>


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CenterThis(HWND);
#define ID_PLAY 1
#define ID_PAUSE 2
#define ID_LIST 3
#define ID_LIST_STATIC 4
#define ID_DISPLAY 5
#define ID_TIMER 99
#define WINSIZE_W 800
#define WINSIZE_H 400
HINSTANCE g_hinst;
int p_flag=0;
HBITMAP hBitmap;
static HWND hwndO;
//example
typedef struct {
 
    wchar_t name[30]; 
    wchar_t singer[20]; 
    int length; 

} Songs; 

Songs songs[] = {
 
    {L"ºq1", L"Eason", 18}, 
    {L"ºq2", L"Thomas", 25}, 
    {L"ºq3", L"Joey", 26}, 
    {L"song4", L"Windows", 38}, 
    {L"song5", L"Uni", 28}, 
}; 

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    PWSTR lpCmdLine, int nCmdShow) {

    MSG  msg;
    WNDCLASSW wc = {0};
    wc.lpszClassName = L"Player";
    wc.hInstance     = hInstance;
	g_hinst = hInstance;
	//wc.hbrBackground=  CreateSolidBrush(RGB(255, 0, 0));
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc   = WndProc;
    wc.hCursor       = LoadCursor(0, IDC_ARROW);
	
    RegisterClassW(&wc);
    hwndO = CreateWindowW(wc.lpszClassName, L"Player",
                  WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                  0, 0, WINSIZE_W, WINSIZE_H, 0, 0, hInstance, 0);

    while (GetMessage(&msg, NULL, 0, 0)) {
    
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

static HWND hwndPic;
void PlayFlame(HWND hwnd){
      // while(p_flag){
	   
	    //hBitmap = (HBITMAP) LoadImageW(NULL, L"rock.bmp", 
        //        IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		int i;
		for(i=0;i<10;i++){
		hBitmap = (HBITMAP)LoadImage(NULL, (LPCSTR)"rock.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);
		SendMessage(hwndPic, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
		Sleep(100);
		hBitmap = (HBITMAP)LoadImage(NULL, (LPCSTR)"wood.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);
		SendMessage(hwndPic, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
        //if (hBitmap == NULL) {
         //   MessageBoxW(hwnd, L"Failed to load image", L"Error", MB_OK); 
        //}			
		//InvalidateRect(hwnd, NULL, TRUE);
		//Sleep(1000);
		//MessageBoxW(hwnd, L"press", L"Error", MB_OK);
		
		//Sleep(1);
		//hBitmap = LoadImage(NULL, "rock.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		SendMessage(hwndPic, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
		}
		
	   //}
}

void CenterThis(HWND hwnd) {

    RECT rc;
    
    GetWindowRect(hwnd, &rc) ;
    
    SetWindowPos(hwnd, 0, 
        (GetSystemMetrics(SM_CXSCREEN) - rc.right)/2,
        (GetSystemMetrics(SM_CYSCREEN) - rc.bottom)/2,
         0, 0, SWP_NOZORDER|SWP_NOSIZE);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, 
    WPARAM wParam, LPARAM lParam) {
    static HWND hwndList, hwndStatic;
    wchar_t buff[100];   
	static int i, j, play_flag = 0;
	HDC hdc;
	PAINTSTRUCT ps;
	BITMAP bitmap;
	HDC hdcMem;
	//HGDIOBJ oldBitmap;
	
	
    switch(msg) {

        case WM_CREATE:
			CenterThis(hwnd);
            CreateWindowW(L"Button", L"Play",
                WS_VISIBLE | WS_CHILD ,
                20, 300, 80, 25, hwnd, (HMENU) ID_PLAY, NULL, NULL);

            CreateWindowW(L"Button", L"Pause",
                WS_VISIBLE | WS_CHILD ,
                80+20, 300, 80, 25, hwnd, (HMENU) ID_PAUSE, NULL, NULL);
			
            hwndList = CreateWindowW(WC_LISTBOXW , NULL, WS_CHILD 
                | WS_VISIBLE | LBS_NOTIFY, 10, 10, 150, 120, hwnd, 
                (HMENU) ID_LIST, g_hinst, NULL);

            hwndStatic = CreateWindowW(WC_STATICW , NULL, WS_CHILD | WS_VISIBLE,
               200, 10, 120, 45, hwnd,(HMENU) ID_LIST_STATIC, g_hinst, NULL);
			for (i = 0; i <ARRAYSIZE(songs); i++){
				SendMessageW(hwndList, LB_ADDSTRING, 0, (LPARAM) songs[i].name);                               
            }
            hwndPic = CreateWindowW(L"Static", L"", 
                WS_CHILD | WS_VISIBLE | SS_BITMAP,
                WINSIZE_W/2, 5, 100, 100, hwnd, (HMENU) 1, NULL, NULL);		
/**			
       hBitmap = (HBITMAP) LoadImageW(NULL, L"wood.bmp", 
                IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        if (hBitmap == NULL) {
            MessageBoxW(hwnd, L"Failed to load image", L"Error", MB_OK); 
        }				
**/

		break;

        case WM_COMMAND:

            if (LOWORD(wParam) == ID_PLAY) {
				play_flag = 1;
				//PlayFlame(hwnd);
				SetTimer(hwnd, ID_TIMER, 5, NULL);
                MessageBeep(MB_OK);
            }

            if (LOWORD(wParam) == ID_PAUSE) {
				if(play_flag){
				play_flag = 0;
				}
				else{
					play_flag = 1;
				}
                MessageBeep(MB_OK);
            }
            if (LOWORD(wParam) == ID_LIST) {        
                if (HIWORD(wParam) == LBN_SELCHANGE) {                   
                    int sel = (int) SendMessageW(hwndList, LB_GETCURSEL, 0, 0);
                    StringCbPrintfW(buff, ARRAYSIZE(buff), L"Singer: %ls\nlength: %d\n", 
                        songs[sel].singer, songs[sel].length);
                    SetWindowTextW(hwndStatic, buff);
               }
            }			

            break;
			
		case WM_TIMER:
				if(play_flag){
				hBitmap = (HBITMAP)LoadImage(NULL, (LPCSTR)"rock.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);
				SendMessage(hwndPic, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
				Sleep(100);
				hBitmap = (HBITMAP)LoadImage(NULL, (LPCSTR)"wood.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_LOADTRANSPARENT);
				SendMessage(hwndPic, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);	
				j++;
				if(j==100){
					KillTimer(hwnd, ID_TIMER);
					MessageBoxW(hwnd, L"Finish", L"Error", MB_OK);
				}
				}
			break;			
			
		case WM_PAINT:
			
			break;
        case WM_DESTROY:

            PostQuitMessage(0);
            break;
    }

    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

