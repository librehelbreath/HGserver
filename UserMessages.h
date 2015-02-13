
#define WM_USER_STARTGAMESIGNAL	WM_USER + 10

#define WM_USER_ACCEPT			WM_USER + 100
#define WM_ONLOGSOCKETEVENT		WM_USER + 200
#define WM_ONGATESOCKETEVENT	WM_USER + 1000

// 클라이언트가 1100번 이하를 점유하므로 이 이후로 메시지가 정의되어서는 안된다. 
#define WM_ONCLIENTSOCKETEVENT	WM_USER + 1100

												 