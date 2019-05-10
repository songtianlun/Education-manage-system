// Education manage system.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#define MAX_LOADSTRING 100
//管理员账户数据存储链表
typedef struct ACCOUNT
{
    int num;//编号、数据总量
    char id[20];//账号
    char password[20];//密码
    char name[20];//姓名
    char sex[4];//性别
    char identity[10];//身份
    char nation[10];//民族
    char face[15];//政治面貌
    char birth[20];//出生日期
    char time[20];//入职、学日期
    char college[20];//所属部门、学院
    int collegeid;//部门、学院代码
    char profession[20];//教授科目、所属专业
    int professionid;//学科、专业代码
	char grade[50];//等级
	struct ACCOUNT *prior;//前一条
    struct ACCOUNT *next;//后一条
}account_Lnode,*account_List;
typedef struct TEACHER//教师数据存储链表
{
    int num;//编号、数据总量
    char id[20];//账号
    char password[20];//密码
    char name[20];//姓名
    char sex[5];//性别
    char identity[10];//身份
    char nation[10];//民族
    char face[15];//政治面貌
    char birth[20];//出生日期
    char time[20];//入职、学日期
    char college[20];//所属学院
    int collegeid;//学院代码
    char profession[50];//所属课程
    char grade[50];//职称
    int professionid;//课程代码
	struct TEACHER *prior;
    struct TEACHER *next;
}teacher_Lnode,*teacher_List;
typedef struct STUDENT//学生数据存储链表
{
    int num;//编号、数据总量
    char id[20];//账号
    char password[20];//密码
    char name[20];//姓名
    char sex[5];//性别
    char identity[10];//身份
    char nation[10];//民族
    char face[15];//政治面貌
    char birth[20];//出生日期
    char time[20];//入职、学日期
    char college[20];//所属学院
    int collegeid;//学院代码
    char profession[50];//所属专业
    char grade[50];//班级
    int professionid;//专业代码
	struct STUDENT *prior;
    struct STUDENT *next;
}student_Lnode,*student_List;
//学院信息存储链表
typedef struct COLLEGE
{
    int num;//学院编号
    char name[30];//学院名称
    int id;//学院代码
    struct COLLEGE *prior;//前一条
    struct COLLEGE *next;//后一条
}college_Lnode,*college_List;
//专业信息存储链表
typedef struct PROFESSION
{
    int num;
    char name[30];
    char college[30];
    int college_id;
    int id;
    struct PROFESSION *prior;
    struct PROFESSION *next;
}profession_Lnode,*profession_List;
//课程信息存储链表
typedef struct COURSE
{
    int num;
    char name[50];
    int id;
    struct COURSE *prior;
    struct COURSE *next;
}course_Lnode,*course_List;
//班级信息存储链表
typedef struct CLASS
{
    int num;
    char name[50];
    char profession[30];
    char college[30];
    int college_id;
    int id;
    struct CLASS *prior;
    struct CLASS *next;
}class_Lnode,*class_List;
//成绩信息存储链表
typedef struct SCORE
{
    int num;//数据编码
    char id[20];//账号
    char name[50];//学生姓名
    char profession[30];//学生专业
    int professionid;//专业代码
    char college[30];//学生学院
    int collegeid;//学院代码
    char grade[50];//学生班级
    int gradeid;//班级代码
    char subject[50];//科目名称
    int subjectid;//科目代码
    char term[20];//学期
    int paper_score;//卷面成绩
    int usual_score;//平时成绩
    int makeup_score;//补考成绩
    int score;//总成绩
    struct SCORE *prior;
    struct SCORE *next;
}score_Lnode,*score_List;
// 全局变量
HINSTANCE hinst;                                                    //当前实例

TCHAR szTitle_teacher[MAX_LOADSTRING];								// 教师端标题栏文本
TCHAR szTitle_student[MAX_LOADSTRING];								// 学生端标题栏文本
TCHAR szTitle_admin[MAX_LOADSTRING];								// 管理员端标题栏文本
TCHAR szWindowClass_teacher[MAX_LOADSTRING];								// 教师端主窗口类名
TCHAR szWindowClass_student[MAX_LOADSTRING];								// 学生端主窗口类名
TCHAR szWindowClass_admin[MAX_LOADSTRING];								    // 管理员端主窗口类名

account_List account_head;             //账户信息链表
account_List account_mine;             //当前账户信息
college_List college_head;             //学院数据链表
profession_List profession_head;       //专业数据链表
course_List course_head;               //课程信息数据链表
class_List class_head;                 //班级信息数据链表
teacher_List teacher_head;             //教师信息数据链表
student_List student_head;             //学生信息数据链表
score_List score_head;                 //成绩信息数据链表
int identity=-1;                       //状态识别：1.高级管理员，2.教师，3.学生，-1.初始化状态，-2.系统需要初始化

//CDatebase m_db; //数据库
//CRecordSet m_TestSet;
//m_db.Open("education management");//链接数据库
//CrecordSet m_TestSet(&m_db);//构造记录集对象，使数据库指向m_db
void display_admin(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow);//显示管理员窗口
void display_teacher(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow);//显示教师窗口
void display_student(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow);//显示学生窗口

// Foward declarations of functions included in this code module:
//注册应用程序的窗口类
ATOM				MyRegisterClass_teacher(HINSTANCE hInstance);//注册教师端窗口
ATOM				MyRegisterClass_student(HINSTANCE hInstance);//注册学生端窗口
ATOM				MyRegisterClass_admin(HINSTANCE hInstance);//注册管理员端窗口
//创建真实窗体，并且显示
BOOL				InitInstance_teacher(HINSTANCE, int);//创建并显示教师端窗口
BOOL				InitInstance_student(HINSTANCE, int);//创建并显示学生端窗口
BOOL				InitInstance_admin(HINSTANCE, int);//创建并显示管理员端窗口
//窗口回调函数
LRESULT CALLBACK	WndProc_teacher(HWND, UINT, WPARAM, LPARAM);//教师窗口回调函数
LRESULT CALLBACK	WndProc_student(HWND, UINT, WPARAM, LPARAM);//学生窗口回调函数
LRESULT CALLBACK	WndProc_admin(HWND, UINT, WPARAM, LPARAM);//管理员窗口回调函数
//about对话框回调函数
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
//loading窗口回调函数
LRESULT CALLBACK	Loading(HWND, UINT, WPARAM, LPARAM);
//IDD_a_self_check窗口回调函数
LRESULT CALLBACK	A_SELF_INFO(HWND, UINT, WPARAM, LPARAM);
//IDD_a_self_password窗口回调函数
LRESULT CALLBACK	A_SELF_PASSWORD(HWND, UINT, WPARAM, LPARAM);
//IDD_a_college_inquir窗口回调函数
LRESULT CALLBACK	A_COLLEGE_INQUIRE(HWND, UINT, WPARAM, LPARAM);
//IDD_a_college_modification窗口回调函数
LRESULT CALLBACK	A_COLLEGE_MODIFICATION(HWND, UINT, WPARAM, LPARAM);
//IDD_a_profession_inquire窗口回调函数
LRESULT CALLBACK	A_PROFESSION_INQUIRE(HWND, UINT, WPARAM, LPARAM);
//IDD_a_profession_modification窗口回调函数
LRESULT CALLBACK	A_PROFESSION_MODIFICATION(HWND, UINT, WPARAM, LPARAM);
//IDD_a_course_inquire窗口回调函数
LRESULT CALLBACK	A_COURSE_INQUIRE(HWND, UINT, WPARAM, LPARAM);
//IDD_a_course_modification窗口回调函数
LRESULT CALLBACK	A_COURSE_MODIFICATION(HWND, UINT, WPARAM, LPARAM);
//IDD_a_class_inquire窗口回调函数
LRESULT CALLBACK	A_CLASS_INQUIRE(HWND, UINT, WPARAM, LPARAM);
//IDD_a_class_modification窗口回调函数
LRESULT CALLBACK	A_CLASS_MODIFICATION(HWND, UINT, WPARAM, LPARAM);
//IDD_a_account_inquire窗口回调函数
LRESULT CALLBACK	A_ACCOUNT_INQUIRE(HWND, UINT, WPARAM, LPARAM);
//IDD_a_account_modification窗口回调函数
LRESULT CALLBACK	A_ACCOUNT_MODIFICATION(HWND, UINT, WPARAM, LPARAM);
//IDD_a_teacher_inquire窗口回调函数
LRESULT CALLBACK	A_TEACHER_INQUIRE(HWND, UINT, WPARAM, LPARAM);
//IDD_a_teacher_modification窗口回调函数
LRESULT CALLBACK	A_TEACHER_MODIFICATION(HWND, UINT, WPARAM, LPARAM);
//IDD_a_student_inquire窗口回调函数
LRESULT CALLBACK	A_STUDENT_INQUIRE(HWND, UINT, WPARAM, LPARAM);
//IDD_a_student_modification窗口回调函数
LRESULT CALLBACK	A_STUDENT_MODIFICATION(HWND, UINT, WPARAM, LPARAM);
//IDD_a_score_inquire窗口回调函数
LRESULT CALLBACK	A_SCORE_INQUIRE(HWND, UINT, WPARAM, LPARAM);
//IDD_a_score_modification窗口回调函数
LRESULT CALLBACK	A_SCORE_MODIFICATION(HWND, UINT, WPARAM, LPARAM);
//IDD_a_score_self_inquire窗口回调函数
LRESULT CALLBACK	A_SCORE_SELF_INQUIRE(HWND, UINT, WPARAM, LPARAM);
//IDD_a_score_self_inquire窗口回调函数
LRESULT CALLBACK	A_SCORE_TERM_INQUIRE(HWND, UINT, WPARAM, LPARAM);
//IDD_a_score_self_inquire窗口回调函数
LRESULT CALLBACK	A_SCORE_ENTER(HWND, UINT, WPARAM, LPARAM);
//IDD_a_score_analyse_sum窗口回调函数
LRESULT CALLBACK	A_SCORE_ANALYSE_SUM(HWND, UINT, WPARAM, LPARAM);
//IDD_a_score_analyse_average窗口回调函数
LRESULT CALLBACK	A_SCORE_ANALYSE_AVERAGE(HWND, UINT, WPARAM, LPARAM);
void Mypaint();//绘制主窗口图形
//数据操作函数
void account_load(account_List account_head); //从磁盘载入账户数据
void account_save(account_List account_head); //存入账户数据到磁盘
void college_load(college_List college_head); //从磁盘载入学院数据
void college_save(college_List college_head); //存入学院数据到磁盘
void profession_load(profession_List profession_head); //从磁盘载入专业数据
void profession_save(profession_List profession_head); //存入专业数据到磁盘
void course_load(course_List course_head); //从磁盘载入课程数据
void course_save(course_List course_head); //存入课程数据到磁盘
void class_load(class_List class_head); //从磁盘载入班级数据
void class_save(class_List class_head); //存入班级数据到磁盘
void teacher_load(teacher_List teacher_head); //从磁盘载入教师数据
void teacher_save(teacher_List teacher_head); //存入教师数据到磁盘
void student_load(student_List student_head); //从磁盘载入学生数据
void student_save(student_List student_head); //存入学生数据到磁盘
void score_load(score_List score_head); //从磁盘载入成绩数据
void score_save(score_List score_head); //存入成绩数据到磁盘

int loading(char id[20],char password[20],account_List account_mine);//1.管理员，2.教师，3.学生，4.账号错误，5.密码错误
void initialize(account_List account_head);//初始化账户数据
void initialize_college(college_List college_head);//初始化学院数据
void initialize_profession(profession_List profession_head);//初始化专业数据
void initialize_course(course_List course_head);//初始化课程数据
void initialize_class(class_List class_head);//初始化班级数据
void initialize_teacher(teacher_List teacher_head);//初始化教师数据
void initialize_student(student_List student_head);//初始化学生数据
void initialize_score(score_List score_head);//初始化成绩数据

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
	account_mine=(account_List)malloc(sizeof(account_Lnode));//申请账户数据头链
	account_head=(account_List)malloc(sizeof(account_Lnode));//申请当前账户数据头链
	college_head=(college_List)malloc(sizeof(college_Lnode));//申请学院数据头链
	profession_head=(profession_List)malloc(sizeof(profession_Lnode));//申请专业数据头链
	course_head=(course_List)malloc(sizeof(course_Lnode));//申请课程数据头链
	class_head=(class_List)malloc(sizeof(class_Lnode));//申请班级数据头链
	teacher_head=(teacher_List)malloc(sizeof(teacher_Lnode));//申请教师数据头链
	student_head=(student_List)malloc(sizeof(student_Lnode));//申请学生数据头链
	score_head=(score_List)malloc(sizeof(score_Lnode));//申请成绩信息数据头链

	//载入全部数据
	account_load(account_head);
	college_load(college_head);
	profession_load(profession_head);
	teacher_load(teacher_head);
	student_load(student_head);
	score_load(score_head);
	course_load(course_head);
	class_load(class_head);
	
			if(identity==-2)
			{
				if(MessageBox(NULL,"检测到系统首次使用或数据文件丢失，请点击确认进行系统初始化！","警告",MB_YESNO|MB_ICONEXCLAMATION)==6)
				{
					initialize(account_head);//初始化账户数据
					account_load(account_head);//载入初始账户数据
					initialize_college(college_head);//初始化学院数据
					college_load(college_head);//载入初始账户数据
					initialize_profession(profession_head);//初始化专业数据
					profession_load(profession_head);//载入初始专业数据
					initialize_course(course_head);//初始化专业数据
					course_load(course_head);//载入初始专业数据
					initialize_class(class_head);//初始化班级数据
					class_load(class_head);//载入初始班级数据
					initialize_teacher(teacher_head);//初始化教师数据
					teacher_load(teacher_head);//载入初始教师数据
					initialize_student(student_head);//初始化学生数据
					student_load(student_head);//载入初始学生数据
					initialize_score(score_head);//初始化成绩数据
					score_load(score_head);//载入初始成绩数据

				}
				else
				{
					return FALSE;
				}
			}
	teacher_load(teacher_head);
	student_load(student_head);
	//调入加速键表
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_EDUCATIONMANAGESYSTEM);
	DialogBox(hInstance,(LPCTSTR)IDD_LOADING,NULL,(DLGPROC)Loading);//显示登录对话框


	//显示管理员界面
	if(identity==1)
	{
		display_admin(hInstance,hPrevInstance,lpCmdLine,nCmdShow);
	}
	else if(identity==2)
		{
			display_teacher(hInstance,hPrevInstance,lpCmdLine,nCmdShow);
		}
	else if(identity==3)
		{
			display_student(hInstance,hPrevInstance,lpCmdLine,nCmdShow);
		}
	
	//主消息循环
	while (GetMessage(&msg, NULL, 0, 0)) 
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)) 
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return msg.wParam;
}

void display_admin(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	//从资源文件加载由IDE_APP_TITTLE指定的字符串资源
	LoadString(hInstance, IDS_APP_TITLE_ADMIN, szTitle_admin, MAX_LOADSTRING);
	LoadString(hInstance, IDS_EDUCATIONMANAGESYSTEM, szWindowClass_admin, MAX_LOADSTRING);
	//注册窗口要使用的窗口类
	MyRegisterClass_admin(hInstance);

	//初始化程序实例
	//调用InitInstance自定义函数创建真实窗体
	InitInstance_admin(hInstance, nCmdShow);
}
void display_teacher(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	//从资源文件加载由IDE_APP_TITTLE指定的字符串资源
	LoadString(hInstance, IDS_APP_TITLE_TEACHER, szTitle_teacher, MAX_LOADSTRING);
	LoadString(hInstance, IDS_EDUCATIONMANAGESYSTEM, szWindowClass_teacher, MAX_LOADSTRING);
	//注册窗口要使用的窗口类
	MyRegisterClass_teacher(hInstance);

	//初始化程序实例
	//调用InitInstance自定义函数创建真实窗体
	InitInstance_teacher (hInstance, nCmdShow);
}
void display_student(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	//从资源文件加载由IDE_APP_TITTLE指定的字符串资源
	LoadString(hInstance, IDS_APP_TITLE_STUDENT, szTitle_student, MAX_LOADSTRING);
	LoadString(hInstance, IDS_EDUCATIONMANAGESYSTEM, szWindowClass_student, MAX_LOADSTRING);
	//注册窗口要使用的窗口类
	MyRegisterClass_student(hInstance);

	//初始化程序实例
	//调用InitInstance自定义函数创建真实窗体
	InitInstance_student (hInstance, nCmdShow);
}

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage is only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
//注册应用程序的窗口类
ATOM MyRegisterClass_admin(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;//窗口类风格
	wcex.lpfnWndProc	= (WNDPROC)WndProc_admin;       //指定窗口回调函数
	wcex.cbClsExtra		= 0;                      //在类结构和windows内部保存的窗口结构中预留空间
	wcex.cbWndExtra		= 0;                      //在类结构和windows内部保存的窗口结构中预留空间
	wcex.hInstance		= hinst;              //指定所在程序的实例句柄
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_EDUCATIONMANAGESYSTEM);  //为所有基于该窗口类创建的窗口设置一个应用程序图标
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);                     //为所有基于该窗口类创建的窗口设置鼠标形状
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);                        //指定基于该窗口类创建窗口的背景色
	wcex.lpszMenuName	= (LPCSTR)IDR_MENU_ADMIN;                        //指定窗口类的菜单
	wcex.lpszClassName	= szWindowClass_admin;                                   //给该窗口类指定一个类名
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);    //为所有基于该窗口类创建的窗口设置一个窗口标题栏图标

	return RegisterClassEx(&wcex);                                         //调用RegisterClassEx函数注册这个窗口类
}
ATOM MyRegisterClass_teacher(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;//窗口类风格
	wcex.lpfnWndProc	= (WNDPROC)WndProc_admin;       //指定窗口回调函数
	wcex.cbClsExtra		= 0;                      //在类结构和windows内部保存的窗口结构中预留空间
	wcex.cbWndExtra		= 0;                      //在类结构和windows内部保存的窗口结构中预留空间
	wcex.hInstance		= hinst;              //指定所在程序的实例句柄
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_EDUCATIONMANAGESYSTEM);  //为所有基于该窗口类创建的窗口设置一个应用程序图标
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);                     //为所有基于该窗口类创建的窗口设置鼠标形状
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);                        //指定基于该窗口类创建窗口的背景色
	wcex.lpszMenuName	= (LPCSTR)IDR_MENU_TEACHER;                        //指定窗口类的菜单
	wcex.lpszClassName	= szWindowClass_teacher;                                   //给该窗口类指定一个类名
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);    //为所有基于该窗口类创建的窗口设置一个窗口标题栏图标

	return RegisterClassEx(&wcex);                                         //调用RegisterClassEx函数注册这个窗口类
}
ATOM MyRegisterClass_student(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;//窗口类风格
	wcex.lpfnWndProc	= (WNDPROC)WndProc_admin;       //指定窗口回调函数
	wcex.cbClsExtra		= 0;                      //在类结构和windows内部保存的窗口结构中预留空间
	wcex.cbWndExtra		= 0;                      //在类结构和windows内部保存的窗口结构中预留空间
	wcex.hInstance		= hinst;              //指定所在程序的实例句柄
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_EDUCATIONMANAGESYSTEM);  //为所有基于该窗口类创建的窗口设置一个应用程序图标
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);                     //为所有基于该窗口类创建的窗口设置鼠标形状
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);                        //指定基于该窗口类创建窗口的背景色
	wcex.lpszMenuName	= (LPCSTR)IDR_MENU_STUDENT;                        //指定窗口类的菜单
	wcex.lpszClassName	= szWindowClass_student;                                   //给该窗口类指定一个类名
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);    //为所有基于该窗口类创建的窗口设置一个窗口标题栏图标

	return RegisterClassEx(&wcex);                                         //调用RegisterClassEx函数注册这个窗口类
}

//
//   FUNCTION: InitInstance(HANDLE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
HDC hdc,mdc;
HBITMAP bmp;
void Mypaint()
{
	SelectObject(mdc,bmp);
	BitBlt(hdc,0,0,800,540,mdc,0,0,SRCCOPY);
}
//创建真实窗体，并且显示
BOOL InitInstance_admin(HINSTANCE hinstance, int nCmdShow)
{
   HWND hWnd;
   hinst = hinstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass_admin, szTitle_admin, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 800, 590, NULL, NULL, hinstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   SetWindowPos(hWnd,NULL,0,0,800,590,SWP_NOMOVE);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
	hdc=GetDC(hWnd);
	mdc=CreateCompatibleDC(hdc);
	bmp=(HBITMAP)LoadImage(hinst,MAKEINTRESOURCE(IDB_BITMAP3),IMAGE_BITMAP,800,540,LR_CREATEDIBSECTION);
	Mypaint();
   return TRUE;
}

BOOL InitInstance_teacher(HINSTANCE hinstance, int nCmdShow)
{
   HWND hWnd;
   hinst = hinstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass_teacher, szTitle_teacher, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 800, 590, NULL, NULL, hinstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   SetWindowPos(hWnd,NULL,0,0,800,590,SWP_NOMOVE);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
	hdc=GetDC(hWnd);
	mdc=CreateCompatibleDC(hdc);
	bmp=(HBITMAP)LoadImage(hinst,MAKEINTRESOURCE(IDB_BITMAP3),IMAGE_BITMAP,800,540,LR_CREATEDIBSECTION);
	Mypaint();
   return TRUE;
}

BOOL InitInstance_student(HINSTANCE hinstance, int nCmdShow)
{
   HWND hWnd;
   hinst = hinstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass_student, szTitle_student, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 800, 590, NULL, NULL, hinstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   SetWindowPos(hWnd,NULL,0,0,800,590,SWP_NOMOVE);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
	hdc=GetDC(hWnd);
	mdc=CreateCompatibleDC(hdc);
	bmp=(HBITMAP)LoadImage(hinst,MAKEINTRESOURCE(IDB_BITMAP3),IMAGE_BITMAP,800,540,LR_CREATEDIBSECTION);
	Mypaint();
   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, unsigned, WORD, LONG)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
//管理员主窗口回调函数
LRESULT CALLBACK WndProc_admin(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId;
	int wmEvent;
	PAINTSTRUCT ps;
	
	TCHAR szHello[MAX_LOADSTRING];
	LoadString(hinst, IDS_HELLO, szHello, MAX_LOADSTRING);

	switch (message) 
	{
		case WM_COMMAND:
			wmId    = LOWORD(wParam); 
			wmEvent = HIWORD(wParam); 
			// Parse the menu selections:
			switch (wmId)
			{
				//显示我的个人信息
				case a_self_inquire:
					MessageBox(NULL,"请点击“查看”显示个人信息！","提示",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_self_check, hWnd, (DLGPROC)A_SELF_INFO);
					break;
				//修改密码
				case a_self_password:
					DialogBox(hinst, (LPCTSTR)IDD_a_self_password, hWnd, (DLGPROC)A_SELF_PASSWORD);
					break;
				//查看学院信息
				case a_college_inquire:
					MessageBox(NULL,"请点击“返回顶部”显示第一页学院信息！","提示",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_college_inquire, hWnd, (DLGPROC)A_COLLEGE_INQUIRE);
					break;
				//修改学院信息
				case a_college_modification:
					//预备消息框
					//MessageBox(NULL,"请点击“返回顶部”显示第一页学院信息！","提示",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_college_modification, hWnd, (DLGPROC)A_COLLEGE_MODIFICATION);
					break;
				//查看专业信息
				case a_profession_inquire:
					MessageBox(NULL,"请点击“返回顶部”显示第一页专业信息！","提示",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_profession_inquire, hWnd, (DLGPROC)A_PROFESSION_INQUIRE);
					break;
				//修改专业信息
				case a_profession_modification:
					//预备消息框
					//MessageBox(NULL,"请点击“返回顶部”显示第一页学院信息！","提示",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_profession_modification, hWnd, (DLGPROC)A_PROFESSION_MODIFICATION);
					break;
				//查看课程信息
				case a_course_inquire:
					MessageBox(NULL,"请点击“返回顶部”显示第一页课程信息！","提示",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_course_inquire, hWnd, (DLGPROC)A_COURSE_INQUIRE);
					break;
				//修改课程信息
				case a_course_modification:
					//预备消息框
					//MessageBox(NULL,"请点击“返回顶部”显示第一页学院信息！","提示",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_course_modification, hWnd, (DLGPROC)A_COURSE_MODIFICATION);
					break;
				//查看班级信息
				case a_class_inquire:
					MessageBox(NULL,"请点击“返回顶部”显示第一页班级信息！","提示",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_class_inquire, hWnd, (DLGPROC)A_CLASS_INQUIRE);
					break;
				//修改班级信息
				case a_class_modification:
					//预备消息框
					//MessageBox(NULL,"请点击“返回顶部”显示第一页班级信息！","提示",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_class_modification, hWnd, (DLGPROC)A_CLASS_MODIFICATION);
					break;
				//查看账户信息
				case a_account_inquire:
					MessageBox(NULL,"请点击“返回顶部”显示第一页账户信息！","提示",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_account_inquire, hWnd, (DLGPROC)A_ACCOUNT_INQUIRE);
					break;
				//修改账户信息
				case a_account_modification:
					//预备消息框
					//MessageBox(NULL,"请点击“返回顶部”显示第一页账户信息！","提示",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_account_modification, hWnd, (DLGPROC)A_ACCOUNT_MODIFICATION);
					break;
				//查看教师信息
				case a_teacher_inquire:
					MessageBox(NULL,"请点击“返回顶部”显示第一页教师信息！","提示",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_teacher_inquire, hWnd, (DLGPROC)A_TEACHER_INQUIRE);
					break;
				//修改教师信息
				case a_teacher_modification:
					//预备消息框
					//MessageBox(NULL,"请点击“返回顶部”显示第一页教师信息！","提示",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_teacher_modification, hWnd, (DLGPROC)A_TEACHER_MODIFICATION);
					break;
				//查看学生信息
				case a_student_inquire:
					MessageBox(NULL,"请点击“返回顶部”显示第一页教师信息！","提示",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_student_inquire, hWnd, (DLGPROC)A_STUDENT_INQUIRE);
					break;
				//修改学生信息
				case a_student_modification:
					//预备消息框
					//MessageBox(NULL,"请点击“返回顶部”显示第一页教师信息！","提示",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_student_modification, hWnd, (DLGPROC)A_STUDENT_MODIFICATION);
					break;
				//查看成绩信息
				case a_score_inquire:
					MessageBox(NULL,"请点击“返回顶部”显示第一页成绩信息！","提示",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_score_inquire, hWnd, (DLGPROC)A_SCORE_INQUIRE);
					break;
				//修改成绩信息
				case a_score_modification:
					//预备消息框
					//MessageBox(NULL,"请点击“返回顶部”显示第一页教师信息！","提示",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_score_modification, hWnd, (DLGPROC)A_SCORE_MODIFICATION);
					break;
				//查看个人成绩信息
				case a_score_self_inquire:
					MessageBox(NULL,"请点击“返回顶部”显示第一页成绩信息！","提示",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_score_self_inquire, hWnd, (DLGPROC)A_SCORE_SELF_INQUIRE);
					break;
				//查看班级成绩信息
				case a_score_term_inquire:
					MessageBox(NULL,"请点击“返回顶部”显示第一页成绩信息！","提示",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_score_term_inquire, hWnd, (DLGPROC)A_SCORE_TERM_INQUIRE);
					break;
				//成绩信息录入
				case a_score_enter:
					MessageBox(NULL,"请选择学科、班级、学期信息以录入成绩！","提示",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_score_enter, hWnd, (DLGPROC)A_SCORE_ENTER);
					break;
				case a_score_analyse_sum:
					MessageBox(NULL,"请选择班级，查看班级总分！","提示",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_score_analyse_sum, hWnd, (DLGPROC)A_SCORE_ANALYSE_SUM);
					break;
				case a_score_analyse_average:
					MessageBox(NULL,"请选择班级，查看班级平均分！","提示",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_score_analyse_average, hWnd, (DLGPROC)A_SCORE_ANALYSE_AVERAGE);
					break;
				//关于
				case help_about:
					DialogBox(hinst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
					break;
				//退出
				case help_exit:
					DestroyWindow(hWnd);
				break;
					default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
			break;
		case WM_PAINT:
			hdc = BeginPaint(hWnd, &ps);
			Mypaint();
			EndPaint(hWnd, &ps);
			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// about窗口回调函数
LRESULT CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
	}
    return FALSE;
}

//登录窗口回调函数
LRESULT CALLBACK	Loading(HWND h_loading, UINT message, WPARAM wParam, LPARAM lParam)
{
	//#define IDC_LOADING_IDENTIFY 101
	//char identify[20];
	//HWND EXIT_identify;
	char lpszClassName[]="COMBOBOX";
	int wmId,uMax,pMax,load_state;//load_state 登录状态
	char user[20],password[20];
	HWND EXIT_user,EXIT_password;
	EXIT_user=GetDlgItem(h_loading,IDC_LOADING_USER);
	EXIT_password=GetDlgItem(h_loading,IDC_LOADING_PASSWORD);
	//EXIT_identify=GetDlgItem(h_loading,IDC_LOADING_IDENTIFY);
	switch (message)
	{
		/*case WM_CREATE:
			EXIT_identify=CreateWindow(lpszClassName,
											NULL,
											CBS_DROPDOWNLIST|WS_CHILD|WS_VISIBLE|MB_SYSTEMMODAL,
											60,50,
											120,150,
											h_loading,
											(HMENU)IDC_LOADING_IDENTIFY,
											hinst,
											NULL);
			SetFocus(EXIT_identify);
			SendMessage(EXIT_identify,CB_ADDSTRING,(WPARAM)0,(LPARAM)(LPCTSTR)TEXT("HELLO"));
			SendMessage(EXIT_identify,CB_INSERTSTRING,1,(LPARAM)"item1");
			SendMessage(EXIT_identify,CB_ADDSTRING,5,(LPARAM)"item2");
			SendMessage(EXIT_identify,CB_ADDSTRING,0,(LPARAM)"item3");
			break;*/
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			wmId=LOWORD(wParam);
			switch(wmId)
			{
			case IDC_LOADING_ENTER:
				uMax=GetWindowTextLength(EXIT_user)+1;
				pMax=GetWindowTextLength(EXIT_password)+1;
				GetWindowText(EXIT_user,user,uMax);
				GetWindowText(EXIT_password,password,pMax);
				/*switch(GetCheckedRadioButton(IDC_student,IDC_admin))
				{
				case IDC_admin:
					break;
				case IDC_teacher:
					break;
				case IDC_student:
					break;
				}*/
				//GetWindowText(EXIT_identify,identify,GetWindowTextLength(EXIT_identify)+1);
				//GetLBText(GetCurSel,identify);
				//GetWindowText(EXIT_identify,identify,GetWindowTextLength(EXIT_identify)+1);
				account_load(account_head);
				load_state=loading(user,password,account_mine);
				//MessageBox(NULL,identify,"提示",MB_OK);
				switch(load_state)
				{
				case 1:
					identity=1;
					EndDialog(h_loading, LOWORD(wParam));
					MessageBox(NULL,"登陆成功，欢迎管理员登录系统！","登录结果",MB_OK);
				    return TRUE;
				case 2:
					identity=2;
					EndDialog(h_loading, LOWORD(wParam));
					MessageBox(NULL,"登陆成功，欢迎教师登录系统！","登录结果",MB_OK);
				    return TRUE;
				case 3:
					identity=3;
					EndDialog(h_loading, LOWORD(wParam));
					MessageBox(NULL,"登陆成功，欢迎学生登录系统！","登录结果",MB_OK);
				    return TRUE;
				case 4:
					MessageBox(NULL,"登录失败，账号不存在！","登录结果",MB_OK|MB_SYSTEMMODAL);
					return FALSE;
				case 5:
					MessageBox(NULL,"登陆失败，密码错误！","登录结果",MB_OK|MB_SYSTEMMODAL);
					return FALSE;
				}
				break;
			case IDC_LOADING_EXIT:
				PostQuitMessage(0);//停止消息传送
				EndDialog(h_loading, LOWORD(wParam));
				return TRUE;
			}
			break;
		case WM_CLOSE:
			PostQuitMessage(0);//停止消息传送
				EndDialog(h_loading, LOWORD(wParam));
				return TRUE;
	}
    return FALSE;
}
//IDD_a_self_check窗口回调函数
LRESULT CALLBACK	A_SELF_INFO(HWND self_check, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId;
	HWND EDIT_id,EDIT_name,EDIT_sex,EDIT_identity,EDIT_nation,EDIT_face,EDIT_birth,EDIT_time,EDIT_college,EDIT_profession;


	EDIT_id=GetDlgItem(self_check,EDIT_a_self_info_id);
	EDIT_name=GetDlgItem(self_check,EDIT_a_self_info_name);
	EDIT_sex=GetDlgItem(self_check,EDIT_a_self_info_sex);
	EDIT_identity=GetDlgItem(self_check,EDIT_a_self_info_identity);
	EDIT_nation=GetDlgItem(self_check,EDIT_a_self_info_nation);
	EDIT_face=GetDlgItem(self_check,EDIT_a_self_info_face);
	EDIT_birth=GetDlgItem(self_check,EDIT_a_self_info_birth);
	EDIT_time=GetDlgItem(self_check,EDIT_a_self_info_time);
	EDIT_college=GetDlgItem(self_check,EDIT_a_self_info_college);
	EDIT_profession=GetDlgItem(self_check,EDIT_a_self_info_profession);
	int index;
	
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			wmId=LOWORD(wParam);
			switch(wmId)
			{
				case BUTTON_a_self_info_enter:
					SetWindowText(EDIT_id,account_mine->id);
					SetWindowText(EDIT_name,account_mine->name);
					SetWindowText(EDIT_sex,account_mine->sex);
					SetWindowText(EDIT_identity,account_mine->identity);
					SetWindowText(EDIT_nation,account_mine->nation);
					SetWindowText(EDIT_face,account_mine->face);
					SetWindowText(EDIT_birth,account_mine->birth);
					SetWindowText(EDIT_time,account_mine->time);
					SetWindowText(EDIT_college,account_mine->college);
					SetWindowText(EDIT_profession,account_mine->profession);
					break;
				case BUTTON_a_self_info_exit: 
					EndDialog(self_check, LOWORD(wParam));
					return TRUE;
					break;
			}
			break;
	}
    return FALSE;
}
//IDD_a_self_password窗口回调函数
LRESULT CALLBACK	A_SELF_PASSWORD(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i;
	account_List p;
	char old[20],new1[20],new2[20];
	int state=-1;//状态指示，-1.初始化，1.修改成功，2.旧密码错误，3.新密码不匹配，4.密码过短,5.新旧密码一致
	HWND EDIT_old,EDIT_new1,EDIT_new2;
	EDIT_old=GetDlgItem(hDlg,EDIT_a_self_password_old);
	EDIT_new1=GetDlgItem(hDlg,EDIT_a_self_password_new1);
	EDIT_new2=GetDlgItem(hDlg,EDIT_a_self_password_new2);
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case BUTTON_a_self_password_affirm:
				GetWindowText(EDIT_old,old,GetWindowTextLength(EDIT_old)+1);
				GetWindowText(EDIT_new1,new1,GetWindowTextLength(EDIT_new1)+1);
				GetWindowText(EDIT_new2,new2,GetWindowTextLength(EDIT_new2)+1);
				if(strcmp(account_mine->password,old)!=0)
				{
					state=2;
					MessageBox(NULL,"旧密码输入错误！","ERROR!",MB_OK|MB_SYSTEMMODAL);
					break;
				}
				else if(strlen(new1)<4)
				{
					state=4;
					MessageBox(NULL,"新密码过于简单！","ERROR!",MB_OK|MB_SYSTEMMODAL);
					break;
				}
				else if(strcmp(new1,old)==0)
				{
					state=5;
					MessageBox(NULL,"新旧密码一致！","ERROR!",MB_OK|MB_SYSTEMMODAL);
					break;
				}
				else if(strcmp(new1,new2)!=0)
				{
					state=3;
					MessageBox(NULL,"两次输入不一致！","ERROR!",MB_OK|MB_SYSTEMMODAL);
					break;
				}
				else
				{
					strcpy(account_mine->password,new1);
					account_load(account_head);
					p=account_head->next;
					i=account_mine->num;
					while(i--)
						p=p->next;
					strcpy(p->password,new1);
					account_save(account_head);
					MessageBox(NULL,"修改成功！","SUCCES!",MB_OK|MB_SYSTEMMODAL);
					EndDialog(hDlg, LOWORD(wParam));
				}
				break;
			case BUTTON_a_self_password_cancel:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
				break;
			}
			break;
		case WM_CLOSE:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
	}
    return FALSE;
}

//IDD_a_college_inquir窗口回调函数
	int college_ck; //标记是否初始化内容，1.是，0.否
	int college_now;
LRESULT CALLBACK	A_COLLEGE_INQUIRE(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,sum,page,print;//sum.资料总数 page.总页数 now.当前页数 print.当前页资料总数
	college_List page_head;
	//char name1[30],name2[30],name3[30],name4[30],name5[30],name6[30];
	char id1[4],id2[4],id3[4],id4[4],id5[4],id6[4];
	char char_page[30],item[10];
	HWND EDIT_id1,EDIT_id2,EDIT_id3,EDIT_id4,EDIT_id5,EDIT_id6;
	HWND EDIT_name1,EDIT_name2,EDIT_name3,EDIT_name4,EDIT_name5,EDIT_name6;
	HWND EDIT_page;
	college_head=(college_List)malloc(sizeof(college_Lnode));
	college_load(college_head);
	sum=college_head->next->num;
	page=sum/6;
	if(sum%6!=0)
		page++;
	EDIT_id1=GetDlgItem(hDlg,EDIT_a_college_inquire_id1);
	EDIT_id2=GetDlgItem(hDlg,EDIT_a_college_inquire_id2);
	EDIT_id3=GetDlgItem(hDlg,EDIT_a_college_inquire_id3);
	EDIT_id4=GetDlgItem(hDlg,EDIT_a_college_inquire_id4);
	EDIT_id5=GetDlgItem(hDlg,EDIT_a_college_inquire_id5);
	EDIT_id6=GetDlgItem(hDlg,EDIT_a_college_inquire_id6);
	EDIT_name1=GetDlgItem(hDlg,EDIT_a_college_inquire_name1);
	EDIT_name2=GetDlgItem(hDlg,EDIT_a_college_inquire_name2);
	EDIT_name3=GetDlgItem(hDlg,EDIT_a_college_inquire_name3);
	EDIT_name4=GetDlgItem(hDlg,EDIT_a_college_inquire_name4);
	EDIT_name5=GetDlgItem(hDlg,EDIT_a_college_inquire_name5);
	EDIT_name6=GetDlgItem(hDlg,EDIT_a_college_inquire_name6);
	EDIT_page=GetDlgItem(hDlg,EDIT_a_college_inquire_page);
	
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case BUTTON_a_college_inquire_top:
				college_ck=1;
				college_now=1;
				if(sum>=6)
					print=6;//若总资料数不小于6，则第一页显示6条数据
				if(sum<6)
					print=sum;//若资料总数小于6，则第一页显示全部sum条数据
				page_head=college_head->next->next;//指向第一页第一条记录
				if(print>=1)
				{
					itoa(page_head->id,id1,10);
					SetWindowText(EDIT_id1,id1);
					SetWindowText(EDIT_name1,page_head->name);
					page_head=page_head->next;
				}
				if(print>=2)
				{
					itoa(page_head->id,id2,10);
					SetWindowText(EDIT_id2,id2);
					SetWindowText(EDIT_name2,page_head->name);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					itoa(page_head->id,id3,10);
					SetWindowText(EDIT_id3,id3);
					SetWindowText(EDIT_name3,page_head->name);
					page_head=page_head->next;
				}
				if(print>=4)
				{
					itoa(page_head->id,id4,10);
					SetWindowText(EDIT_id4,id4);
					SetWindowText(EDIT_name4,page_head->name);
					page_head=page_head->next;
				}
				if(print>=5)
				{
					itoa(page_head->id,id5,10);
					SetWindowText(EDIT_id5,id5);
					SetWindowText(EDIT_name5,page_head->name);
					page_head=page_head->next;
				}
				if(print>=6)
				{
					itoa(page_head->id,id6,10);
					SetWindowText(EDIT_id6,id6);
					SetWindowText(EDIT_name6,page_head->name);
					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				itoa(college_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"页，共");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				break;
			case BUTTON_a_college_inquire_prior:
				if(college_ck!=1)
				{
					MessageBox(NULL,"请点击“返回顶部”显示第一页学院信息！","提示",MB_OK);
					break;
				}
				page_head=college_head->next->next;
				if(college_now-1<=0)
				{
					MessageBox(NULL,"已经到第一页！","提示",MB_OK);
					return FALSE;
				}
				else
					college_now--;
				for(i=0;i<(college_now-1)*6;i++)//将page_head移到当前页的第一项
					page_head=page_head->next;
				
				if(college_now==page)//如果在最后一页，则计算最后一页记录数量
					print=sum-(page-1)*6;
				else//否则，记录总数为6
					print=6;
				//清空编辑框内容
					SetWindowText(EDIT_id1,"");
					SetWindowText(EDIT_name1,"");
					SetWindowText(EDIT_id2,"");
					SetWindowText(EDIT_name2,"");
					SetWindowText(EDIT_id3,"");
					SetWindowText(EDIT_name3,"");
					SetWindowText(EDIT_id4,"");
					SetWindowText(EDIT_name4,"");
					SetWindowText(EDIT_id5,"");
					SetWindowText(EDIT_name5,"");
					SetWindowText(EDIT_id6,"");
					SetWindowText(EDIT_name6,"");
				if(print>=1)
				{
					itoa(page_head->id,id1,10);
					SetWindowText(EDIT_id1,id1);
					SetWindowText(EDIT_name1,page_head->name);
					page_head=page_head->next;
					
				}
				if(print>=2)
				{
					itoa(page_head->id,id2,10);
					SetWindowText(EDIT_id2,id2);
					SetWindowText(EDIT_name2,page_head->name);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					itoa(page_head->id,id3,10);
					SetWindowText(EDIT_id3,id3);
					SetWindowText(EDIT_name3,page_head->name);
					page_head=page_head->next;
				}
				if(print>=4)
				{
					itoa(page_head->id,id4,10);
					SetWindowText(EDIT_id4,id4);
					SetWindowText(EDIT_name4,page_head->name);
					page_head=page_head->next;
				}
				if(print>=5)
				{
					itoa(page_head->id,id5,10);
					SetWindowText(EDIT_id5,id5);
					SetWindowText(EDIT_name5,page_head->name);
					page_head=page_head->next;
				}
				if(print>=6)
				{
					itoa(page_head->id,id6,10);
					SetWindowText(EDIT_id6,id6);
					SetWindowText(EDIT_name6,page_head->name);
					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				itoa(college_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"页，共");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_college_inquire_next:
				if(college_ck!=1)
				{
					MessageBox(NULL,"请点击“返回顶部”显示第一页学院信息！","提示",MB_OK);
					break;
				}
				page_head=college_head->next->next;//移到记录第一页第一条记录
				if(college_now+1>page)//如果当前页+1等于总页数，弹出警告
				{
					MessageBox(NULL,"已经到最后一页！","提示",MB_OK);
					return FALSE;
				}
				else//否则，跳转页数
				{
					college_now++;
				}
				for(i=0;i<(college_now-1)*6;i++)//将page_head移到当前页的第一项
					page_head=page_head->next;
				
				if(college_now==page)//如果在最后一页，则计算最后一页记录数量
					print=sum-(page-1)*6;
				else//否则，记录总数为6
					print=6;
				//清空编辑框内容
					SetWindowText(EDIT_id1,"");
					SetWindowText(EDIT_name1,"");
					SetWindowText(EDIT_id2,"");
					SetWindowText(EDIT_name2,"");
					SetWindowText(EDIT_id3,"");
					SetWindowText(EDIT_name3,"");
					SetWindowText(EDIT_id4,"");
					SetWindowText(EDIT_name4,"");
					SetWindowText(EDIT_id5,"");
					SetWindowText(EDIT_name5,"");
					SetWindowText(EDIT_id6,"");
					SetWindowText(EDIT_name6,"");
				if(print>=1)
				{
					itoa(page_head->id,id1,10);
					SetWindowText(EDIT_id1,id1);
					SetWindowText(EDIT_name1,page_head->name);
					page_head=page_head->next;
					
				}
				if(print>=2)
				{
					itoa(page_head->id,id2,10);
					SetWindowText(EDIT_id2,id2);
					SetWindowText(EDIT_name2,page_head->name);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					itoa(page_head->id,id3,10);
					SetWindowText(EDIT_id3,id3);
					SetWindowText(EDIT_name3,page_head->name);
					page_head=page_head->next;
				}
				if(print>=4)
				{
					itoa(page_head->id,id4,10);
					SetWindowText(EDIT_id4,id4);
					SetWindowText(EDIT_name4,page_head->name);
					page_head=page_head->next;
				}
				if(print>=5)
				{
					itoa(page_head->id,id5,10);
					SetWindowText(EDIT_id5,id5);
					SetWindowText(EDIT_name5,page_head->name);
					page_head=page_head->next;
				}
				if(print>=6)
				{
					itoa(page_head->id,id6,10);
					SetWindowText(EDIT_id6,id6);
					SetWindowText(EDIT_name6,page_head->name);
					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				
				itoa(college_now,item,10);

				strcat(char_page,item);
				
				strcat(char_page,"页，共");
				itoa(page,item,10);//转换整形为字符型
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_college_inquire_exit:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
				break;
			}
			break;
		case WM_CLOSE:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
	}
    return FALSE;
}
//IDD_a_college_modification窗口回调函数
HWND EDIT_oldid,EDIT_oldid1,EDIT_oldname,EDIT_newid,EDIT_newname;
	int find_a_college_modification;//0.找到 1.未找到
	int state_a_college_modification;//修改状态提示
	char college_item[10];
	college_List modification_p,college_new_info,college_old_info;
	college_List college_delete;
LRESULT CALLBACK	A_COLLEGE_MODIFICATION(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	char  new_name[50];
	char message_a_college_modification[60];
	char *stop;//为strtol定义的终止字符指针
	int id;
	int i;
	college_head=(college_List)malloc(sizeof(college_Lnode));
	college_load(college_head);
	EDIT_oldid=GetDlgItem(hDlg,EDIT_a_college_modification_oldid);
	EDIT_oldid1=GetDlgItem(hDlg,EDIT_a_college_modification_oldid1);
	EDIT_oldname=GetDlgItem(hDlg,EDIT_a_college_modification_oldname);
	EDIT_newid=GetDlgItem(hDlg,EDIT_a_college_modification_newid);
	EDIT_newname=GetDlgItem(hDlg,EDIT_a_college_modification_newname);
	
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			//通过id定位学院
			case BUTTON_a_college_modification_location:
				find_a_college_modification=0;
				GetWindowText(EDIT_oldid,college_item,GetWindowTextLength(EDIT_oldid)+1);//获取oldid编辑框内容到item
				id=strtol(college_item,&stop,10);//转换内容为长整型
				modification_p=college_head->next->next;
				while(modification_p)
				{
					if(modification_p->num==id)
					{
						college_old_info=(college_List)malloc(sizeof(college_Lnode));
						strcpy(college_old_info->name,modification_p->name);
						college_old_info->id=modification_p->id;
						college_old_info->num=modification_p->num;
						find_a_college_modification=1;
						break;
					}
					else
						modification_p=modification_p->next;
				}
				if(find_a_college_modification!=1)
				{
					MessageBox(NULL,"输入有误！","ERROR!",MB_OK);
					break;
					return FALSE;
				}
				SetWindowText(EDIT_oldid1,college_item);
				SetWindowText(EDIT_newid,college_item);
				SetWindowText(EDIT_oldname,college_old_info->name);
				SetWindowText(EDIT_newname,college_old_info->name);
				state_a_college_modification=1;//修改状态为修改
				break;
			//增添学院
			case BUTTON_a_college_modification_add:
				MessageBox(NULL,"请在新信息框中输入新学院名称","提示",MB_OK);
				find_a_college_modification=0;
				state_a_college_modification=2;//修改状态为增添学院
				SetWindowText(EDIT_oldid,"");
				SetWindowText(EDIT_oldid1,"");
				SetWindowText(EDIT_newid,"");
				SetWindowText(EDIT_oldname,"");
				SetWindowText(EDIT_newname,"");
				college_new_info=(college_List)malloc(sizeof(college_Lnode));
				college_new_info->id=college_head->next->num+1;
				college_new_info->num=college_head->next->num+1;
				itoa(college_new_info->id,college_item,10);//转换整形为字符型
				SetWindowText(EDIT_newid,college_item);
				break;
			//确认修改
			case BUTTON_a_college_modification_affirm:
				GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//获取newnaeme框内容到new_name
				if(state_a_college_modification==1)//确认修改现有学院信息
				{
				if(strlen(new_name)>20)
				{
					MessageBox(NULL,"输入有误！","警告",MB_OK);
					strcpy(new_name,college_old_info->name);
					SetWindowText(EDIT_newname,college_old_info->name);
					return FALSE;
				}
				if(strcmp(new_name,college_old_info->name)==0)
				{
					MessageBox(NULL,"没有修改任何信息！","警告",MB_OK);
					return FALSE;
				}
				modification_p=college_head->next;
				for(i=0;i<college_old_info->id;i++)
					modification_p=modification_p->next;
				strcpy(modification_p->name,new_name);
				college_save(college_head);
				college_load(college_head);
				SetWindowText(EDIT_oldname,new_name);
				MessageBox(NULL,"修改成功！","警告",MB_OK);
				}
				if(state_a_college_modification==2)//确认增添学院信息
				{
					GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//获取newnaeme框内容到new_name
					strcpy(college_new_info->name,new_name);
					modification_p=college_head->next;
					if(strlen(new_name)==0||strlen(new_name)>20)
					{
						MessageBox(NULL,"学院名称非法！","警告",MB_OK);
						break;
						return FALSE;
					}
					for(i=0;i<college_head->next->num;i++)
					{
						modification_p=modification_p->next;
						if(strcmp(college_new_info->name,modification_p->name)==0)
						{
							MessageBox(NULL,"学院名称重复！","警告",MB_OK);
							return FALSE;
						}
					}
					modification_p->next=college_new_info;
					college_new_info->prior=modification_p;
					college_new_info->next=NULL;
					college_head->next->num++;
					college_save(college_head);
					college_load(college_head);
					SetWindowText(EDIT_oldid,college_item);
					SetWindowText(EDIT_oldid1,college_item);
					SetWindowText(EDIT_newid,college_item);
					SetWindowText(EDIT_oldname,college_new_info->name);
					SetWindowText(EDIT_newname,college_new_info->name);
					MessageBox(NULL,"修改成功！","提示",MB_OK);
					college_old_info=(college_List)malloc(sizeof(college_Lnode));
					strcpy(college_old_info->name,college_new_info->name);
					college_old_info->id=college_new_info->id;
					college_old_info->num=college_new_info->id;
					find_a_college_modification=1;
				}
				break;
			//删除学院
			case BUTTON_a_college_modification_delete:
				if(find_a_college_modification==1)
				{
				strcpy(message_a_college_modification,"确认删除学院：“");
				strcat(message_a_college_modification,college_old_info->name);
				strcat(message_a_college_modification,"”吗？");
				if(MessageBox(NULL,message_a_college_modification,"警告",MB_YESNO|MB_ICONEXCLAMATION)!=6)
				{
					return FALSE;
				}
				modification_p=college_head->next;
				for(i=0;i<college_old_info->id;i++)
					modification_p=modification_p->next;
				modification_p->num=-1;
				strcat(modification_p->name,"（已删除）");
				modification_p=college_head->next->next;
				college_save(college_head);
				college_load(college_head);
				SetWindowText(EDIT_oldid,"");
				SetWindowText(EDIT_oldid1,"");
				SetWindowText(EDIT_newid,"");
				SetWindowText(EDIT_oldname,"");
				SetWindowText(EDIT_newname,"");
				MessageBox(NULL,"删除成功！","警告",MB_OK);
				find_a_college_modification=0;
				break;
				}
				MessageBox(NULL,"非法操作！","警告",MB_OK);
				break;
			case BUTTON_a_college_modification_exit:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
		case WM_CLOSE:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
	}
    return FALSE;
}
//IDD_a_profession_inquir窗口回调函数
	int profession_ck; //标记是否初始化内容，1.是，0.否
	int profession_now;
LRESULT CALLBACK	A_PROFESSION_INQUIRE(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,sum,page,print;//sum.资料总数 page.总页数 now.当前页数 print.当前页资料总数
	profession_List page_head;

	char id1[4],id2[4],id3[4],id4[4],id5[4],id6[4];
	char char_page[30],item[10];
	HWND EDIT_id1,EDIT_id2,EDIT_id3,EDIT_id4,EDIT_id5,EDIT_id6;
	HWND EDIT_name1,EDIT_name2,EDIT_name3,EDIT_name4,EDIT_name5,EDIT_name6;
	HWND EDIT_college1,EDIT_college2,EDIT_college3,EDIT_college4,EDIT_college5,EDIT_college6;
	HWND EDIT_page;
	profession_head=(profession_List)malloc(sizeof(profession_Lnode));
	profession_load(profession_head);
	sum=profession_head->next->num;
	page=sum/6;
	if(sum%6!=0)
		page++;
	EDIT_id1=GetDlgItem(hDlg,EDIT_a_profession_inquire_id1);
	EDIT_id2=GetDlgItem(hDlg,EDIT_a_profession_inquire_id2);
	EDIT_id3=GetDlgItem(hDlg,EDIT_a_profession_inquire_id3);
	EDIT_id4=GetDlgItem(hDlg,EDIT_a_profession_inquire_id4);
	EDIT_id5=GetDlgItem(hDlg,EDIT_a_profession_inquire_id5);
	EDIT_id6=GetDlgItem(hDlg,EDIT_a_profession_inquire_id6);
	EDIT_name1=GetDlgItem(hDlg,EDIT_a_profession_inquire_name1);
	EDIT_name2=GetDlgItem(hDlg,EDIT_a_profession_inquire_name2);
	EDIT_name3=GetDlgItem(hDlg,EDIT_a_profession_inquire_name3);
	EDIT_name4=GetDlgItem(hDlg,EDIT_a_profession_inquire_name4);
	EDIT_name5=GetDlgItem(hDlg,EDIT_a_profession_inquire_name5);
	EDIT_name6=GetDlgItem(hDlg,EDIT_a_profession_inquire_name6);
	EDIT_college1=GetDlgItem(hDlg,EDIT_a_profession_inquire_college1);
	EDIT_college2=GetDlgItem(hDlg,EDIT_a_profession_inquire_college2);
	EDIT_college3=GetDlgItem(hDlg,EDIT_a_profession_inquire_college3);
	EDIT_college4=GetDlgItem(hDlg,EDIT_a_profession_inquire_college4);
	EDIT_college5=GetDlgItem(hDlg,EDIT_a_profession_inquire_college5);
	EDIT_college6=GetDlgItem(hDlg,EDIT_a_profession_inquire_college6);
	EDIT_page=GetDlgItem(hDlg,EDIT_a_profession_inquire_page);
	
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case BUTTON_a_profession_inquire_top:
				profession_ck=1;
				profession_now=1;
				if(sum>=6)
					print=6;//若总资料数不小于6，则第一页显示6条数据
				if(sum<6)
					print=sum;//若资料总数小于6，则第一页显示全部sum条数据
				page_head=profession_head->next->next;//指向第一页第一条记录
				if(print>=1)
				{
					itoa(page_head->id,id1,10);
					SetWindowText(EDIT_id1,id1);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_college1,page_head->college);
					page_head=page_head->next;
				}
				if(print>=2)
				{
					itoa(page_head->id,id2,10);
					SetWindowText(EDIT_id2,id2);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_college2,page_head->college);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					itoa(page_head->id,id3,10);
					SetWindowText(EDIT_id3,id3);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_college3,page_head->college);
					page_head=page_head->next;
				}
				if(print>=4)
				{
					itoa(page_head->id,id4,10);
					SetWindowText(EDIT_id4,id4);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_college4,page_head->college);
					page_head=page_head->next;
				}
				if(print>=5)
				{
					itoa(page_head->id,id5,10);
					SetWindowText(EDIT_id5,id5);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_college5,page_head->college);
					page_head=page_head->next;
				}
				if(print>=6)
				{
					itoa(page_head->id,id6,10);
					SetWindowText(EDIT_id6,id6);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_college6,page_head->college);
					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				itoa(profession_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"页，共");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				break;
			case BUTTON_a_profession_inquire_prior:
				if(profession_ck!=1)
				{
					MessageBox(NULL,"请点击“返回顶部”显示第一页学院信息！","提示",MB_OK);
					break;
				}
				page_head=profession_head->next->next;
				if(profession_now-1<=0)
				{
					MessageBox(NULL,"已经到第一页！","提示",MB_OK);
					return FALSE;
				}
				else
					profession_now--;
				for(i=0;i<(profession_now-1)*6;i++)//将page_head移到当前页的第一项
					page_head=page_head->next;
				
				if(profession_now==page)//如果在最后一页，则计算最后一页记录数量
					print=sum-(page-1)*6;
				else//否则，记录总数为6
					print=6;
				//清空编辑框内容
					SetWindowText(EDIT_id1,"");
					SetWindowText(EDIT_name1,"");
					SetWindowText(EDIT_college1,"");
					SetWindowText(EDIT_id2,"");
					SetWindowText(EDIT_name2,"");
					SetWindowText(EDIT_college2,"");
					SetWindowText(EDIT_id3,"");
					SetWindowText(EDIT_name3,"");
					SetWindowText(EDIT_college3,"");
					SetWindowText(EDIT_id4,"");
					SetWindowText(EDIT_name4,"");
					SetWindowText(EDIT_college4,"");
					SetWindowText(EDIT_id5,"");
					SetWindowText(EDIT_name5,"");
					SetWindowText(EDIT_college5,"");
					SetWindowText(EDIT_id6,"");
					SetWindowText(EDIT_name6,"");
					SetWindowText(EDIT_college6,"");
				if(print>=1)
				{
					itoa(page_head->id,id1,10);
					SetWindowText(EDIT_id1,id1);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_college1,page_head->college);
					page_head=page_head->next;
					
				}
				if(print>=2)
				{
					itoa(page_head->id,id2,10);
					SetWindowText(EDIT_id2,id2);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_college2,page_head->college);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					itoa(page_head->id,id3,10);
					SetWindowText(EDIT_id3,id3);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_college3,page_head->college);
					page_head=page_head->next;
				}
				if(print>=4)
				{
					itoa(page_head->id,id4,10);
					SetWindowText(EDIT_id4,id4);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_college4,page_head->college);
					page_head=page_head->next;
				}
				if(print>=5)
				{
					itoa(page_head->id,id5,10);
					SetWindowText(EDIT_id5,id5);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_college5,page_head->college);
					page_head=page_head->next;
				}
				if(print>=6)
				{
					itoa(page_head->id,id6,10);
					SetWindowText(EDIT_id6,id6);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_college6,page_head->college);
					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				itoa(profession_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"页，共");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_profession_inquire_next:
				if(profession_ck!=1)
				{
					MessageBox(NULL,"请点击“返回顶部”显示第一页学院信息！","提示",MB_OK);
					break;
				}
				page_head=profession_head->next->next;//移到记录第一页第一条记录
				if(profession_now+1>page)//如果当前页+1等于总页数，弹出警告
				{
					MessageBox(NULL,"已经到最后一页！","提示",MB_OK);
					return FALSE;
				}
				else//否则，跳转页数
				{
					profession_now++;
				}
				for(i=0;i<(profession_now-1)*6;i++)//将page_head移到当前页的第一项
					page_head=page_head->next;
				
				if(profession_now==page)//如果在最后一页，则计算最后一页记录数量
					print=sum-(page-1)*6;
				else//否则，记录总数为6
					print=6;
				//清空编辑框内容
					SetWindowText(EDIT_id1,"");
					SetWindowText(EDIT_name1,"");
					SetWindowText(EDIT_college1,"");
					SetWindowText(EDIT_id2,"");
					SetWindowText(EDIT_name2,"");
					SetWindowText(EDIT_college2,"");
					SetWindowText(EDIT_id3,"");
					SetWindowText(EDIT_name3,"");
					SetWindowText(EDIT_college3,"");
					SetWindowText(EDIT_id4,"");
					SetWindowText(EDIT_name4,"");
					SetWindowText(EDIT_college4,"");
					SetWindowText(EDIT_id5,"");
					SetWindowText(EDIT_name5,"");
					SetWindowText(EDIT_college5,"");
					SetWindowText(EDIT_id6,"");
					SetWindowText(EDIT_name6,"");
					SetWindowText(EDIT_college6,"");
				if(print>=1)
				{
					itoa(page_head->id,id1,10);
					SetWindowText(EDIT_id1,id1);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_college1,page_head->college);
					page_head=page_head->next;
					
				}
				if(print>=2)
				{
					itoa(page_head->id,id2,10);
					SetWindowText(EDIT_id2,id2);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_college2,page_head->college);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					itoa(page_head->id,id3,10);
					SetWindowText(EDIT_id3,id3);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_college3,page_head->college);
					page_head=page_head->next;
				}
				if(print>=4)
				{
					itoa(page_head->id,id4,10);
					SetWindowText(EDIT_id4,id4);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_college4,page_head->college);
					page_head=page_head->next;
				}
				if(print>=5)
				{
					itoa(page_head->id,id5,10);
					SetWindowText(EDIT_id5,id5);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_college5,page_head->college);
					page_head=page_head->next;
				}
				if(print>=6)
				{
					itoa(page_head->id,id6,10);
					SetWindowText(EDIT_id6,id6);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_college6,page_head->college);
					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				
				itoa(profession_now,item,10);

				strcat(char_page,item);
				
				strcat(char_page,"页，共");
				itoa(page,item,10);//转换整形为字符型
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_profession_inquire_exit:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
				break;
			}
			break;
		case WM_CLOSE:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
	}
    return FALSE;

}
//IDD_a_profession_modification窗口回调函数

	int find_a_profession_modification;//0.找到 1.未找到
	int state_a_profession_modification;//修改状态提示
	int add_profession;//增添信息合法，1.合法,other.不合法
	char profession_item[10];
	profession_List profession_modification_p,profession_new_info,profession_old_info;
	profession_List profession_delete;
LRESULT CALLBACK	A_PROFESSION_MODIFICATION(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	college_List college_p;
	HWND EDIT_oldid,EDIT_oldid1,EDIT_oldname,EDIT_oldcollege,EDIT_newid,EDIT_newname,EDIT_newcollege;
	char  new_name[50],new_college[50];
	char message_a_profession_modification[60];
	char *stop;//为strtol定义的终止字符指针
	int id;
	int i;
	profession_head=(profession_List)malloc(sizeof(profession_Lnode));
	profession_load(profession_head);
	EDIT_oldid=GetDlgItem(hDlg,EDIT_a_profession_modification_oldid);
	EDIT_oldid1=GetDlgItem(hDlg,EDIT_a_profession_modification_oldid1);
	EDIT_oldname=GetDlgItem(hDlg,EDIT_a_profession_modification_oldname);
	EDIT_oldcollege=GetDlgItem(hDlg,EDIT_a_profession_modification_oldcollege);
	EDIT_newid=GetDlgItem(hDlg,EDIT_a_profession_modification_newid);
	EDIT_newname=GetDlgItem(hDlg,EDIT_a_profession_modification_newname);
	EDIT_newcollege=GetDlgItem(hDlg,EDIT_a_profession_modification_newcollege);
	
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			//通过id定位专业
			case BUTTON_a_profession_modification_location:
				find_a_profession_modification=0;
				GetWindowText(EDIT_oldid,profession_item,GetWindowTextLength(EDIT_oldid)+1);//获取oldid编辑框内容到item
				id=strtol(profession_item,&stop,10);//转换内容为长整型
				profession_modification_p=profession_head->next->next;
				while(profession_modification_p)
				{
					if(profession_modification_p->num==id)
					{
						profession_old_info=(profession_List)malloc(sizeof(profession_Lnode));
						strcpy(profession_old_info->name,profession_modification_p->name);
						strcpy(profession_old_info->college,profession_modification_p->college);
						profession_old_info->id=profession_modification_p->id;
						profession_old_info->num=profession_modification_p->num;
						find_a_profession_modification=1;
						break;
					}
					else
						profession_modification_p=profession_modification_p->next;
				}
				if(find_a_profession_modification!=1)
				{
					MessageBox(NULL,"输入有误！","ERROR!",MB_OK);
					break;
					return FALSE;
				}
				SetWindowText(EDIT_oldid1,profession_item);
				SetWindowText(EDIT_newid,profession_item);
				SetWindowText(EDIT_oldname,profession_old_info->name);
				SetWindowText(EDIT_newname,profession_old_info->name);
				SetWindowText(EDIT_oldcollege,profession_old_info->college);
				SetWindowText(EDIT_newcollege,profession_old_info->college);
				state_a_profession_modification=1;//修改状态为修改
				break;
			//增添学院
			case BUTTON_a_profession_modification_add:
				MessageBox(NULL,"请在新信息框中输入新专业名称以及其所属学院名称","提示",MB_OK);
				find_a_profession_modification=0;
				state_a_profession_modification=2;//修改状态为增添学院
				SetWindowText(EDIT_oldid,"");
				SetWindowText(EDIT_oldid1,"");
				SetWindowText(EDIT_oldcollege,"");
				SetWindowText(EDIT_newid,"");
				SetWindowText(EDIT_oldname,"");
				SetWindowText(EDIT_newname,"");
				SetWindowText(EDIT_newcollege,"");
				profession_new_info=(profession_List)malloc(sizeof(profession_Lnode));
				profession_new_info->id=profession_head->next->num+1;
				profession_new_info->num=profession_head->next->num+1;
				itoa(profession_new_info->id,profession_item,10);//转换整形为字符型
				SetWindowText(EDIT_newid,profession_item);
				break;
			//确认修改
			case BUTTON_a_profession_modification_affirm:
				GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//获取newnaeme框内容到new_name
				GetWindowText(EDIT_newcollege,new_college,GetWindowTextLength(EDIT_newcollege)+1);//获取newcollege框内容到new_college
				if(state_a_profession_modification==1)//确认修改现有专业信息
				{
				if(strlen(new_name)>28)
				{
					MessageBox(NULL,"专业名称输入有误！","警告",MB_OK);
					strcpy(new_name,profession_old_info->name);
					SetWindowText(EDIT_newname,profession_old_info->name);
					return FALSE;
				}
				if(strcmp(new_name,profession_old_info->name)==0)
				{
					MessageBox(NULL,"没有修改任何信息！","警告",MB_OK);
					return FALSE;
				}
				if(strcmp(new_college,profession_old_info->college)==0)
				{
					MessageBox(NULL,"新的所属学院信息不会存储！\n若想修改学院请删除数据后重新规定学院！","警告",MB_OK);
					return FALSE;
				}
				profession_modification_p=profession_head->next;
				for(i=0;i<profession_old_info->id;i++)
					profession_modification_p=profession_modification_p->next;
				strcpy(profession_modification_p->name,new_name);
				profession_save(profession_head);
				profession_load(profession_head);
				SetWindowText(EDIT_oldname,new_name);
				MessageBox(NULL,"修改成功！","警告",MB_OK);
				}
				if(state_a_profession_modification==2)//确认增添学院信息
				{
					GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//获取newnaeme框内容到new_name
					GetWindowText(EDIT_newcollege,new_college,GetWindowTextLength(EDIT_newcollege)+1);//获取newcollege框内容到new_college
					strcpy(profession_new_info->name,new_name);
					strcpy(profession_new_info->college,new_college);
					profession_modification_p=profession_head->next;
					college_load(college_head);
					college_p=college_head->next;
					while(college_p)
					{
						if(strcmp(college_p->name,new_college)==0)
						{
							strcpy(profession_new_info->college,new_college);
							profession_new_info->college_id=college_p->id;
							add_profession=1;
							break;
						}
						college_p=college_p->next;
					}
					if(add_profession!=1)
					{
						MessageBox(NULL,"学院不存在！","警告",MB_OK);
						break;
						return FALSE;
					}
					if(strlen(new_name)==0||strlen(new_name)>20)
					{
						MessageBox(NULL,"专业名称非法！","警告",MB_OK);
						add_profession=0;
						break;
						return FALSE;
					}
					for(i=0;i<profession_head->next->num;i++)
					{
						profession_modification_p=profession_modification_p->next;
						if(strcmp(profession_new_info->name,profession_modification_p->name)==0)
						{
							MessageBox(NULL,"专业名称重复！","警告",MB_OK);
							add_profession=0;
							return FALSE;
						}
					}
					profession_modification_p->next=profession_new_info;
					profession_new_info->prior=profession_modification_p;
					profession_new_info->next=NULL;
					profession_head->next->num++;
					profession_save(profession_head);
					profession_load(profession_head);
					SetWindowText(EDIT_oldid,profession_item);
					SetWindowText(EDIT_oldid1,profession_item);
					SetWindowText(EDIT_newid,profession_item);
					SetWindowText(EDIT_oldname,profession_new_info->name);
					SetWindowText(EDIT_newname,profession_new_info->name);
					SetWindowText(EDIT_oldcollege,profession_new_info->college);
					SetWindowText(EDIT_newcollege,profession_new_info->college);
					MessageBox(NULL,"修改成功！","提示",MB_OK);
					profession_old_info=(profession_List)malloc(sizeof(profession_Lnode));
					strcpy(profession_old_info->name,profession_new_info->name);
					profession_old_info->id=profession_new_info->id;
					profession_old_info->num=profession_new_info->id;
					find_a_profession_modification=1;
				}
				break;
			//删除学院
			case BUTTON_a_profession_modification_delete:
				if(find_a_profession_modification==1)
				{
				strcpy(message_a_profession_modification,"确认删除专业：“");
				strcat(message_a_profession_modification,profession_old_info->name);
				strcat(message_a_profession_modification,"”吗？");
				if(MessageBox(NULL,message_a_profession_modification,"警告",MB_YESNO|MB_ICONEXCLAMATION)!=6)
				{
					return FALSE;
				}
				profession_modification_p=profession_head->next;
				for(i=0;i<profession_old_info->id;i++)
					profession_modification_p=profession_modification_p->next;
				profession_modification_p->num=-1;
				strcat(profession_modification_p->name,"（已删除）");
				profession_modification_p=profession_head->next->next;
				profession_save(profession_head);
				profession_load(profession_head);
				SetWindowText(EDIT_oldid,"");
				SetWindowText(EDIT_oldid1,"");
				SetWindowText(EDIT_newid,"");
				SetWindowText(EDIT_oldname,"");
				SetWindowText(EDIT_newname,"");
				SetWindowText(EDIT_oldcollege,"");
				SetWindowText(EDIT_newcollege,"");
				MessageBox(NULL,"删除成功！","警告",MB_OK);
				find_a_profession_modification=0;
				break;
				}
				MessageBox(NULL,"非法操作！","警告",MB_OK);
				break;
			case BUTTON_a_profession_modification_exit:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
		case WM_CLOSE:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
	}
    return FALSE;

}
//IDD_a_course_inquir窗口回调函数
	int course_ck=0; //标记是否初始化内容，1.是，0.否
	int course_now;
LRESULT CALLBACK	A_COURSE_INQUIRE(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,sum,page,print;//sum.资料总数 page.总页数 now.当前页数 print.当前页资料总数
	course_List page_head;
	//char name1[30],name2[30],name3[30],name4[30],name5[30],name6[30];
	char id1[4],id2[4],id3[4],id4[4],id5[4],id6[4];
	char char_page[30],item[10];
	HWND EDIT_id1,EDIT_id2,EDIT_id3,EDIT_id4,EDIT_id5,EDIT_id6;
	HWND EDIT_name1,EDIT_name2,EDIT_name3,EDIT_name4,EDIT_name5,EDIT_name6;
	HWND EDIT_page;
	course_head=(course_List)malloc(sizeof(course_Lnode));
	course_load(course_head);
	sum=course_head->next->num;
	page=sum/6;
	if(sum%6!=0)
		page++;
	EDIT_id1=GetDlgItem(hDlg,EDIT_a_course_inquire_id1);
	EDIT_id2=GetDlgItem(hDlg,EDIT_a_course_inquire_id2);
	EDIT_id3=GetDlgItem(hDlg,EDIT_a_course_inquire_id3);
	EDIT_id4=GetDlgItem(hDlg,EDIT_a_course_inquire_id4);
	EDIT_id5=GetDlgItem(hDlg,EDIT_a_course_inquire_id5);
	EDIT_id6=GetDlgItem(hDlg,EDIT_a_course_inquire_id6);
	EDIT_name1=GetDlgItem(hDlg,EDIT_a_course_inquire_name1);
	EDIT_name2=GetDlgItem(hDlg,EDIT_a_course_inquire_name2);
	EDIT_name3=GetDlgItem(hDlg,EDIT_a_course_inquire_name3);
	EDIT_name4=GetDlgItem(hDlg,EDIT_a_course_inquire_name4);
	EDIT_name5=GetDlgItem(hDlg,EDIT_a_course_inquire_name5);
	EDIT_name6=GetDlgItem(hDlg,EDIT_a_course_inquire_name6);
	EDIT_page=GetDlgItem(hDlg,EDIT_a_course_inquire_page);
	
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case BUTTON_a_course_inquire_top:
				course_ck=1;
				course_now=1;
				if(sum>=6)
					print=6;//若总资料数不小于6，则第一页显示6条数据
				if(sum<6)
					print=sum;//若资料总数小于6，则第一页显示全部sum条数据
				page_head=course_head->next->next;//指向第一页第一条记录
				if(print>=1)
				{
					itoa(page_head->id,id1,10);
					SetWindowText(EDIT_id1,id1);
					SetWindowText(EDIT_name1,page_head->name);
					page_head=page_head->next;
				}
				if(print>=2)
				{
					itoa(page_head->id,id2,10);
					SetWindowText(EDIT_id2,id2);
					SetWindowText(EDIT_name2,page_head->name);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					itoa(page_head->id,id3,10);
					SetWindowText(EDIT_id3,id3);
					SetWindowText(EDIT_name3,page_head->name);
					page_head=page_head->next;
				}
				if(print>=4)
				{
					itoa(page_head->id,id4,10);
					SetWindowText(EDIT_id4,id4);
					SetWindowText(EDIT_name4,page_head->name);
					page_head=page_head->next;
				}
				if(print>=5)
				{
					itoa(page_head->id,id5,10);
					SetWindowText(EDIT_id5,id5);
					SetWindowText(EDIT_name5,page_head->name);
					page_head=page_head->next;
				}
				if(print>=6)
				{
					itoa(page_head->id,id6,10);
					SetWindowText(EDIT_id6,id6);
					SetWindowText(EDIT_name6,page_head->name);
					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				itoa(course_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"页，共");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				break;
			case BUTTON_a_course_inquire_prior:
				if(course_ck!=1)
				{
					MessageBox(NULL,"请点击“返回顶部”显示第一页学院信息！","提示",MB_OK);
					break;
				}
				page_head=course_head->next->next;
				if(course_now-1<=0)
				{
					MessageBox(NULL,"已经到第一页！","提示",MB_OK);
					return FALSE;
				}
				else
					course_now--;
				for(i=0;i<(course_now-1)*6;i++)//将page_head移到当前页的第一项
					page_head=page_head->next;
				
				if(course_now==page)//如果在最后一页，则计算最后一页记录数量
					print=sum-(page-1)*6;
				else//否则，记录总数为6
					print=6;
				//清空编辑框内容
					SetWindowText(EDIT_id1,"");
					SetWindowText(EDIT_name1,"");
					SetWindowText(EDIT_id2,"");
					SetWindowText(EDIT_name2,"");
					SetWindowText(EDIT_id3,"");
					SetWindowText(EDIT_name3,"");
					SetWindowText(EDIT_id4,"");
					SetWindowText(EDIT_name4,"");
					SetWindowText(EDIT_id5,"");
					SetWindowText(EDIT_name5,"");
					SetWindowText(EDIT_id6,"");
					SetWindowText(EDIT_name6,"");
				if(print>=1)
				{
					itoa(page_head->id,id1,10);
					SetWindowText(EDIT_id1,id1);
					SetWindowText(EDIT_name1,page_head->name);
					page_head=page_head->next;
					
				}
				if(print>=2)
				{
					itoa(page_head->id,id2,10);
					SetWindowText(EDIT_id2,id2);
					SetWindowText(EDIT_name2,page_head->name);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					itoa(page_head->id,id3,10);
					SetWindowText(EDIT_id3,id3);
					SetWindowText(EDIT_name3,page_head->name);
					page_head=page_head->next;
				}
				if(print>=4)
				{
					itoa(page_head->id,id4,10);
					SetWindowText(EDIT_id4,id4);
					SetWindowText(EDIT_name4,page_head->name);
					page_head=page_head->next;
				}
				if(print>=5)
				{
					itoa(page_head->id,id5,10);
					SetWindowText(EDIT_id5,id5);
					SetWindowText(EDIT_name5,page_head->name);
					page_head=page_head->next;
				}
				if(print>=6)
				{
					itoa(page_head->id,id6,10);
					SetWindowText(EDIT_id6,id6);
					SetWindowText(EDIT_name6,page_head->name);
					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				itoa(course_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"页，共");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_course_inquire_next:
				if(course_ck!=1)
				{
					MessageBox(NULL,"请点击“返回顶部”显示第一页学院信息！","提示",MB_OK);
					break;
				}
				page_head=course_head->next->next;//移到记录第一页第一条记录
				if(course_now+1>page)//如果当前页+1等于总页数，弹出警告
				{
					MessageBox(NULL,"已经到最后一页！","提示",MB_OK);
					return FALSE;
				}
				else//否则，跳转页数
				{
					course_now++;
				}
				for(i=0;i<(course_now-1)*6;i++)//将page_head移到当前页的第一项
					page_head=page_head->next;
				
				if(course_now==page)//如果在最后一页，则计算最后一页记录数量
					print=sum-(page-1)*6;
				else//否则，记录总数为6
					print=6;
				//清空编辑框内容
					SetWindowText(EDIT_id1,"");
					SetWindowText(EDIT_name1,"");
					SetWindowText(EDIT_id2,"");
					SetWindowText(EDIT_name2,"");
					SetWindowText(EDIT_id3,"");
					SetWindowText(EDIT_name3,"");
					SetWindowText(EDIT_id4,"");
					SetWindowText(EDIT_name4,"");
					SetWindowText(EDIT_id5,"");
					SetWindowText(EDIT_name5,"");
					SetWindowText(EDIT_id6,"");
					SetWindowText(EDIT_name6,"");
				if(print>=1)
				{
					itoa(page_head->id,id1,10);
					SetWindowText(EDIT_id1,id1);
					SetWindowText(EDIT_name1,page_head->name);
					page_head=page_head->next;
					
				}
				if(print>=2)
				{
					itoa(page_head->id,id2,10);
					SetWindowText(EDIT_id2,id2);
					SetWindowText(EDIT_name2,page_head->name);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					itoa(page_head->id,id3,10);
					SetWindowText(EDIT_id3,id3);
					SetWindowText(EDIT_name3,page_head->name);
					page_head=page_head->next;
				}
				if(print>=4)
				{
					itoa(page_head->id,id4,10);
					SetWindowText(EDIT_id4,id4);
					SetWindowText(EDIT_name4,page_head->name);
					page_head=page_head->next;
				}
				if(print>=5)
				{
					itoa(page_head->id,id5,10);
					SetWindowText(EDIT_id5,id5);
					SetWindowText(EDIT_name5,page_head->name);
					page_head=page_head->next;
				}
				if(print>=6)
				{
					itoa(page_head->id,id6,10);
					SetWindowText(EDIT_id6,id6);
					SetWindowText(EDIT_name6,page_head->name);
					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				
				itoa(course_now,item,10);

				strcat(char_page,item);
				
				strcat(char_page,"页，共");
				itoa(page,item,10);//转换整形为字符型
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_course_inquire_exit:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
				break;
			}
			break;
		case WM_CLOSE:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
	}
    return FALSE;
}
//IDD_a_course_modification窗口回调函数
	int find_a_course_modification;//0.找到 1.未找到
	int state_a_course_modification;//修改状态提示
	char course_item[10];
	course_List course_modification_p,course_new_info,course_old_info;
	course_List course_delete;
LRESULT CALLBACK	A_COURSE_MODIFICATION(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND EDIT_oldid,EDIT_oldid1,EDIT_oldname,EDIT_newid,EDIT_newname;
	char  new_name[50];
	char message_a_course_modification[60];
	char *stop;//为strtol定义的终止字符指针
	int id;
	int i;
	course_head=(course_List)malloc(sizeof(course_Lnode));
	course_load(course_head);
	EDIT_oldid=GetDlgItem(hDlg,EDIT_a_course_modification_oldid);
	EDIT_oldid1=GetDlgItem(hDlg,EDIT_a_course_modification_oldid1);
	EDIT_oldname=GetDlgItem(hDlg,EDIT_a_course_modification_oldname);
	EDIT_newid=GetDlgItem(hDlg,EDIT_a_course_modification_newid);
	EDIT_newname=GetDlgItem(hDlg,EDIT_a_course_modification_newname);
	
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			//通过id定位学院
			case BUTTON_a_course_modification_location:
				find_a_course_modification=0;
				GetWindowText(EDIT_oldid,course_item,GetWindowTextLength(EDIT_oldid)+1);//获取oldid编辑框内容到item
				id=strtol(course_item,&stop,10);//转换内容为长整型
				course_modification_p=course_head->next->next;
				while(course_modification_p)
				{
					if(course_modification_p->num==id)
					{
						course_old_info=(course_List)malloc(sizeof(course_Lnode));
						strcpy(course_old_info->name,course_modification_p->name);
						course_old_info->id=course_modification_p->id;
						course_old_info->num=course_modification_p->num;
						find_a_course_modification=1;
						break;
					}
					else
						course_modification_p=course_modification_p->next;
				}
				if(find_a_course_modification!=1)
				{
					MessageBox(NULL,"输入有误！","ERROR!",MB_OK);
					break;
					return FALSE;
				}
				SetWindowText(EDIT_oldid1,course_item);
				SetWindowText(EDIT_newid,course_item);
				SetWindowText(EDIT_oldname,course_old_info->name);
				SetWindowText(EDIT_newname,course_old_info->name);
				state_a_course_modification=1;//修改状态为修改
				break;
			//增添学院
			case BUTTON_a_course_modification_add:
				MessageBox(NULL,"请在新信息框中输入新课程名称","提示",MB_OK);
				find_a_course_modification=0;
				state_a_course_modification=2;//修改状态为增添学院
				SetWindowText(EDIT_oldid,"");
				SetWindowText(EDIT_oldid1,"");
				SetWindowText(EDIT_newid,"");
				SetWindowText(EDIT_oldname,"");
				SetWindowText(EDIT_newname,"");
				course_new_info=(course_List)malloc(sizeof(course_Lnode));
				course_new_info->id=course_head->next->num+1;
				course_new_info->num=course_head->next->num+1;
				itoa(course_new_info->id,course_item,10);//转换整形为字符型
				SetWindowText(EDIT_newid,course_item);
				break;
			//确认修改
			case BUTTON_a_course_modification_affirm:
				GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//获取newnaeme框内容到new_name
				if(state_a_course_modification==1)//确认修改现有学院信息
				{
				if(strlen(new_name)>20)
				{
					MessageBox(NULL,"输入有误！","警告",MB_OK);
					strcpy(new_name,course_old_info->name);
					SetWindowText(EDIT_newname,course_old_info->name);
					return FALSE;
				}
				if(strcmp(new_name,course_old_info->name)==0)
				{
					MessageBox(NULL,"没有修改任何信息！","警告",MB_OK);
					return FALSE;
				}
				course_modification_p=course_head->next;
				for(i=0;i<course_old_info->id;i++)
					course_modification_p=course_modification_p->next;
				strcpy(course_modification_p->name,new_name);
				course_save(course_head);
				course_load(course_head);
				SetWindowText(EDIT_oldname,new_name);
				MessageBox(NULL,"修改成功！","警告",MB_OK);
				}
				if(state_a_course_modification==2)//确认增添学院信息
				{
					GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//获取newnaeme框内容到new_name
					strcpy(course_new_info->name,new_name);
					course_modification_p=course_head->next;
					if(strlen(new_name)==0||strlen(new_name)>25)
					{
						MessageBox(NULL,"课程名称非法！","警告",MB_OK);
						break;
						return FALSE;
					}
					for(i=0;i<course_head->next->num;i++)
					{
						course_modification_p=course_modification_p->next;
						if(strcmp(course_new_info->name,course_modification_p->name)==0)
						{
							MessageBox(NULL,"该课程已存在！","警告",MB_OK);
							return FALSE;
						}
					}
					course_modification_p->next=course_new_info;
					course_new_info->prior=course_modification_p;
					course_new_info->next=NULL;
					course_head->next->num++;
					course_save(course_head);
					course_load(course_head);
					SetWindowText(EDIT_oldid,course_item);
					SetWindowText(EDIT_oldid1,course_item);
					SetWindowText(EDIT_newid,course_item);
					SetWindowText(EDIT_oldname,course_new_info->name);
					SetWindowText(EDIT_newname,course_new_info->name);
					MessageBox(NULL,"修改成功！","提示",MB_OK);
					course_old_info=(course_List)malloc(sizeof(course_Lnode));
					strcpy(course_old_info->name,course_new_info->name);
					course_old_info->id=course_new_info->id;
					course_old_info->num=course_new_info->id;
					find_a_course_modification=1;
				}
				break;
			//删除学院
			case BUTTON_a_course_modification_delete:
				if(find_a_course_modification==1)
				{
				strcpy(message_a_course_modification,"确认删除课程：“");
				strcat(message_a_course_modification,course_old_info->name);
				strcat(message_a_course_modification,"”吗？");
				if(MessageBox(NULL,message_a_course_modification,"警告",MB_YESNO|MB_ICONEXCLAMATION)!=6)
				{
					return FALSE;
				}
				course_modification_p=course_head->next;
				for(i=0;i<course_old_info->id;i++)
					course_modification_p=course_modification_p->next;
				course_modification_p->num=-1;
				strcat(course_modification_p->name,"（已删除）");
				course_modification_p=course_head->next->next;
				course_save(course_head);
				course_load(course_head);
				SetWindowText(EDIT_oldid,"");
				SetWindowText(EDIT_oldid1,"");
				SetWindowText(EDIT_newid,"");
				SetWindowText(EDIT_oldname,"");
				SetWindowText(EDIT_newname,"");
				MessageBox(NULL,"删除成功！","警告",MB_OK);
				find_a_course_modification=0;
				break;
				}
				MessageBox(NULL,"非法操作！","警告",MB_OK);
				break;
			case BUTTON_a_course_modification_exit:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
		case WM_CLOSE:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
	}
    return FALSE;
}
//IDD_a_class_inquir窗口回调函数
	int class_ck; //标记是否初始化内容，1.是，0.否
	int class_now;
LRESULT CALLBACK	A_CLASS_INQUIRE(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,sum,page,print;//sum.资料总数 page.总页数 now.当前页数 print.当前页资料总数
	class_List page_head;

	char id1[4],id2[4],id3[4],id4[4],id5[4],id6[4];
	char char_page[30],item[10];
	HWND EDIT_id1,EDIT_id2,EDIT_id3,EDIT_id4,EDIT_id5,EDIT_id6;
	HWND EDIT_name1,EDIT_name2,EDIT_name3,EDIT_name4,EDIT_name5,EDIT_name6;
	HWND EDIT_college1,EDIT_college2,EDIT_college3,EDIT_college4,EDIT_college5,EDIT_college6;
	HWND EDIT_profession1,EDIT_profession2,EDIT_profession3,EDIT_profession4,EDIT_profession5,EDIT_profession6;
	HWND EDIT_page;
	class_head=(class_List)malloc(sizeof(class_Lnode));
	class_load(class_head);
	sum=class_head->next->num;
	page=sum/6;
	if(sum%6!=0)
		page++;
	EDIT_id1=GetDlgItem(hDlg,EDIT_a_class_inquire_id1);
	EDIT_id2=GetDlgItem(hDlg,EDIT_a_class_inquire_id2);
	EDIT_id3=GetDlgItem(hDlg,EDIT_a_class_inquire_id3);
	EDIT_id4=GetDlgItem(hDlg,EDIT_a_class_inquire_id4);
	EDIT_id5=GetDlgItem(hDlg,EDIT_a_class_inquire_id5);
	EDIT_id6=GetDlgItem(hDlg,EDIT_a_class_inquire_id6);
	EDIT_name1=GetDlgItem(hDlg,EDIT_a_class_inquire_name1);
	EDIT_name2=GetDlgItem(hDlg,EDIT_a_class_inquire_name2);
	EDIT_name3=GetDlgItem(hDlg,EDIT_a_class_inquire_name3);
	EDIT_name4=GetDlgItem(hDlg,EDIT_a_class_inquire_name4);
	EDIT_name5=GetDlgItem(hDlg,EDIT_a_class_inquire_name5);
	EDIT_name6=GetDlgItem(hDlg,EDIT_a_class_inquire_name6);
	EDIT_college1=GetDlgItem(hDlg,EDIT_a_class_inquire_college1);
	EDIT_college2=GetDlgItem(hDlg,EDIT_a_class_inquire_college2);
	EDIT_college3=GetDlgItem(hDlg,EDIT_a_class_inquire_college3);
	EDIT_college4=GetDlgItem(hDlg,EDIT_a_class_inquire_college4);
	EDIT_college5=GetDlgItem(hDlg,EDIT_a_class_inquire_college5);
	EDIT_college6=GetDlgItem(hDlg,EDIT_a_class_inquire_college6);
	EDIT_profession1=GetDlgItem(hDlg,EDIT_a_class_inquire_profession1);
	EDIT_profession2=GetDlgItem(hDlg,EDIT_a_class_inquire_profession2);
	EDIT_profession3=GetDlgItem(hDlg,EDIT_a_class_inquire_profession3);
	EDIT_profession4=GetDlgItem(hDlg,EDIT_a_class_inquire_profession4);
	EDIT_profession5=GetDlgItem(hDlg,EDIT_a_class_inquire_profession5);
	EDIT_profession6=GetDlgItem(hDlg,EDIT_a_class_inquire_profession6);

	EDIT_page=GetDlgItem(hDlg,EDIT_a_class_inquire_page);
	
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case BUTTON_a_class_inquire_top:
				class_ck=1;
				class_now=1;
				if(sum>=6)
					print=6;//若总资料数不小于6，则第一页显示6条数据
				if(sum<6)
					print=sum;//若资料总数小于6，则第一页显示全部sum条数据
				page_head=class_head->next->next;//指向第一页第一条记录
				if(print>=1)
				{
					itoa(page_head->id,id1,10);
					SetWindowText(EDIT_id1,id1);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_college1,page_head->college);
					SetWindowText(EDIT_profession1,page_head->profession);
					page_head=page_head->next;
				}
				if(print>=2)
				{
					itoa(page_head->id,id2,10);
					SetWindowText(EDIT_id2,id2);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_college2,page_head->college);
					SetWindowText(EDIT_profession2,page_head->profession);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					itoa(page_head->id,id3,10);
					SetWindowText(EDIT_id3,id3);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_college3,page_head->college);
					SetWindowText(EDIT_profession3,page_head->profession);
					page_head=page_head->next;
				}
				if(print>=4)
				{
					itoa(page_head->id,id4,10);
					SetWindowText(EDIT_id4,id4);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_college4,page_head->college);
					SetWindowText(EDIT_profession4,page_head->profession);
					page_head=page_head->next;
				}
				if(print>=5)
				{
					itoa(page_head->id,id5,10);
					SetWindowText(EDIT_id5,id5);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_college5,page_head->college);
					SetWindowText(EDIT_profession5,page_head->profession);
					page_head=page_head->next;
				}
				if(print>=6)
				{
					itoa(page_head->id,id6,10);
					SetWindowText(EDIT_id6,id6);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_college6,page_head->college);
					SetWindowText(EDIT_profession6,page_head->profession);
					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				itoa(class_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"页，共");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				break;
			case BUTTON_a_class_inquire_prior:
				if(class_ck!=1)
				{
					MessageBox(NULL,"请点击“返回顶部”显示第一页学院信息！","提示",MB_OK);
					break;
				}
				page_head=class_head->next->next;
				if(class_now-1<=0)
				{
					MessageBox(NULL,"已经到第一页！","提示",MB_OK);
					return FALSE;
				}
				else
					class_now--;
				for(i=0;i<(class_now-1)*6;i++)//将page_head移到当前页的第一项
					page_head=page_head->next;
				
				if(class_now==page)//如果在最后一页，则计算最后一页记录数量
					print=sum-(page-1)*6;
				else//否则，记录总数为6
					print=6;
				//清空编辑框内容
					SetWindowText(EDIT_id1,"");
					SetWindowText(EDIT_name1,"");
					SetWindowText(EDIT_college1,"");
					SetWindowText(EDIT_profession1,"");
					SetWindowText(EDIT_id2,"");
					SetWindowText(EDIT_name2,"");
					SetWindowText(EDIT_college2,"");
					SetWindowText(EDIT_profession2,"");
					SetWindowText(EDIT_id3,"");
					SetWindowText(EDIT_name3,"");
					SetWindowText(EDIT_college3,"");
					SetWindowText(EDIT_profession3,"");
					SetWindowText(EDIT_id4,"");
					SetWindowText(EDIT_name4,"");
					SetWindowText(EDIT_college4,"");
					SetWindowText(EDIT_profession4,"");
					SetWindowText(EDIT_id5,"");
					SetWindowText(EDIT_name5,"");
					SetWindowText(EDIT_college5,"");
					SetWindowText(EDIT_profession5,"");
					SetWindowText(EDIT_id6,"");
					SetWindowText(EDIT_name6,"");
					SetWindowText(EDIT_college6,"");
					SetWindowText(EDIT_profession6,"");
				if(print>=1)
				{
					itoa(page_head->id,id1,10);
					SetWindowText(EDIT_id1,id1);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_college1,page_head->college);
					SetWindowText(EDIT_profession1,page_head->profession);
					page_head=page_head->next;
					
				}
				if(print>=2)
				{
					itoa(page_head->id,id2,10);
					SetWindowText(EDIT_id2,id2);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_college2,page_head->college);
					SetWindowText(EDIT_profession2,page_head->profession);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					itoa(page_head->id,id3,10);
					SetWindowText(EDIT_id3,id3);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_college3,page_head->college);
					SetWindowText(EDIT_profession3,page_head->profession);
					page_head=page_head->next;
				}
				if(print>=4)
				{
					itoa(page_head->id,id4,10);
					SetWindowText(EDIT_id4,id4);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_college4,page_head->college);
					SetWindowText(EDIT_profession4,page_head->profession);
					page_head=page_head->next;
				}
				if(print>=5)
				{
					itoa(page_head->id,id5,10);
					SetWindowText(EDIT_id5,id5);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_college5,page_head->college);
					SetWindowText(EDIT_profession5,page_head->profession);
					page_head=page_head->next;
				}
				if(print>=6)
				{
					itoa(page_head->id,id6,10);
					SetWindowText(EDIT_id6,id6);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_college6,page_head->college);
					SetWindowText(EDIT_profession6,page_head->profession);
					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				itoa(class_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"页，共");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_class_inquire_next:
				if(class_ck!=1)
				{
					MessageBox(NULL,"请点击“返回顶部”显示第一页学院信息！","提示",MB_OK);
					break;
				}
				page_head=class_head->next->next;//移到记录第一页第一条记录
				if(class_now+1>page)//如果当前页+1等于总页数，弹出警告
				{
					MessageBox(NULL,"已经到最后一页！","提示",MB_OK);
					return FALSE;
				}
				else//否则，跳转页数
				{
					class_now++;
				}
				for(i=0;i<(class_now-1)*6;i++)//将page_head移到当前页的第一项
					page_head=page_head->next;
				
				if(class_now==page)//如果在最后一页，则计算最后一页记录数量
					print=sum-(page-1)*6;
				else//否则，记录总数为6
					print=6;
				//清空编辑框内容
					SetWindowText(EDIT_id1,"");
					SetWindowText(EDIT_name1,"");
					SetWindowText(EDIT_college1,"");
					SetWindowText(EDIT_profession1,"");
					SetWindowText(EDIT_id2,"");
					SetWindowText(EDIT_name2,"");
					SetWindowText(EDIT_college2,"");
					SetWindowText(EDIT_profession2,"");
					SetWindowText(EDIT_id3,"");
					SetWindowText(EDIT_name3,"");
					SetWindowText(EDIT_college3,"");
					SetWindowText(EDIT_profession3,"");
					SetWindowText(EDIT_id4,"");
					SetWindowText(EDIT_name4,"");
					SetWindowText(EDIT_college4,"");
					SetWindowText(EDIT_profession4,"");
					SetWindowText(EDIT_id5,"");
					SetWindowText(EDIT_name5,"");
					SetWindowText(EDIT_college5,"");
					SetWindowText(EDIT_profession5,"");
					SetWindowText(EDIT_id6,"");
					SetWindowText(EDIT_name6,"");
					SetWindowText(EDIT_college6,"");
					SetWindowText(EDIT_profession6,"");
				if(print>=1)
				{
					itoa(page_head->id,id1,10);
					SetWindowText(EDIT_id1,id1);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_college1,page_head->college);
					SetWindowText(EDIT_profession1,page_head->profession);
					page_head=page_head->next;
					
				}
				if(print>=2)
				{
					itoa(page_head->id,id2,10);
					SetWindowText(EDIT_id2,id2);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_college2,page_head->college);
					SetWindowText(EDIT_profession2,page_head->profession);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					itoa(page_head->id,id3,10);
					SetWindowText(EDIT_id3,id3);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_college3,page_head->college);
					SetWindowText(EDIT_profession3,page_head->profession);
					page_head=page_head->next;
				}
				if(print>=4)
				{
					itoa(page_head->id,id4,10);
					SetWindowText(EDIT_id4,id4);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_college4,page_head->college);
					SetWindowText(EDIT_profession4,page_head->profession);
					page_head=page_head->next;
				}
				if(print>=5)
				{
					itoa(page_head->id,id5,10);
					SetWindowText(EDIT_id5,id5);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_college5,page_head->college);
					SetWindowText(EDIT_profession5,page_head->profession);
					page_head=page_head->next;
				}
				if(print>=6)
				{
					itoa(page_head->id,id6,10);
					SetWindowText(EDIT_id6,id6);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_college6,page_head->college);
					SetWindowText(EDIT_profession6,page_head->profession);
					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				
				itoa(class_now,item,10);

				strcat(char_page,item);
				
				strcat(char_page,"页，共");
				itoa(page,item,10);//转换整形为字符型
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_class_inquire_exit:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
				break;
			}
			break;
		case WM_CLOSE:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
	}
    return FALSE;

}
//IDD_a_class_modification窗口回调函数

	int find_a_class_modification;//0.找到 1.未找到
	int state_a_class_modification;//修改状态提示
	int add_class=0;//增添信息合法，1.学院合法,2.专业合法 other.不合法-1.学院不合法 -2.专业不合法
	char class_item[10];
	class_List class_modification_p,class_new_info,class_old_info;
	class_List class_delete;
LRESULT CALLBACK	A_CLASS_MODIFICATION(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	college_List college_p;
	profession_List profession_p;
	HWND EDIT_oldid,EDIT_oldid1,EDIT_oldname,EDIT_oldcollege,EDIT_oldprofession,EDIT_newid,EDIT_newname,EDIT_newcollege,EDIT_newprofession;
	char  new_name[50],new_college[50],new_profession[50];
	char message_a_class_modification[60];
	char *stop;//为strtol定义的终止字符指针
	int id;
	int i;
	class_head=(class_List)malloc(sizeof(class_Lnode));
	class_load(class_head);
	EDIT_oldid=GetDlgItem(hDlg,EDIT_a_class_modification_oldid);
	EDIT_oldid1=GetDlgItem(hDlg,EDIT_a_class_modification_oldid1);
	EDIT_oldname=GetDlgItem(hDlg,EDIT_a_class_modification_oldname);
	EDIT_oldcollege=GetDlgItem(hDlg,EDIT_a_class_modification_oldcollege);
	EDIT_oldprofession=GetDlgItem(hDlg,EDIT_a_class_modification_oldprofession);
	EDIT_newid=GetDlgItem(hDlg,EDIT_a_class_modification_newid);
	EDIT_newname=GetDlgItem(hDlg,EDIT_a_class_modification_newname);
	EDIT_newcollege=GetDlgItem(hDlg,EDIT_a_class_modification_newcollege);
	EDIT_newprofession=GetDlgItem(hDlg,EDIT_a_class_modification_newprofession);
	
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			//通过id定位专业
			case BUTTON_a_class_modification_location:
				find_a_class_modification=0;
				GetWindowText(EDIT_oldid,class_item,GetWindowTextLength(EDIT_oldid)+1);//获取oldid编辑框内容到item
				id=strtol(class_item,&stop,10);//转换内容为长整型
				class_modification_p=class_head->next->next;
				while(class_modification_p)
				{
					if(class_modification_p->num==id)
					{
						class_old_info=(class_List)malloc(sizeof(class_Lnode));
						strcpy(class_old_info->name,class_modification_p->name);
						strcpy(class_old_info->college,class_modification_p->college);
						strcpy(class_old_info->profession,class_modification_p->profession);
						class_old_info->id=class_modification_p->id;
						class_old_info->num=class_modification_p->num;
						find_a_class_modification=1;
						break;
					}
					else
						class_modification_p=class_modification_p->next;
				}
				if(find_a_class_modification!=1)
				{
					MessageBox(NULL,"输入有误！","ERROR!",MB_OK);
					break;
					return FALSE;
				}
				SetWindowText(EDIT_oldid1,class_item);
				SetWindowText(EDIT_newid,class_item);
				SetWindowText(EDIT_oldname,class_old_info->name);
				SetWindowText(EDIT_newname,class_old_info->name);
				SetWindowText(EDIT_oldcollege,class_old_info->college);
				SetWindowText(EDIT_newcollege,class_old_info->college);
				SetWindowText(EDIT_oldprofession,class_old_info->profession);
				SetWindowText(EDIT_newprofession,class_old_info->profession);
				state_a_class_modification=1;//修改状态为修改
				break;
			//增添学院
			case BUTTON_a_class_modification_add:
				MessageBox(NULL,"请在新信息框中输入新专业名称以及其所属学院名称","提示",MB_OK);
				find_a_class_modification=0;
				state_a_class_modification=2;//修改状态为增添学院
				SetWindowText(EDIT_oldid,"");
				SetWindowText(EDIT_oldid1,"");
				SetWindowText(EDIT_oldcollege,"");
				SetWindowText(EDIT_oldprofession,"");
				SetWindowText(EDIT_newid,"");
				SetWindowText(EDIT_oldname,"");
				SetWindowText(EDIT_newname,"");
				SetWindowText(EDIT_newcollege,"");
				SetWindowText(EDIT_newprofession,"");
				class_new_info=(class_List)malloc(sizeof(class_Lnode));
				class_new_info->id=class_head->next->num+1;
				class_new_info->num=class_head->next->num+1;
				itoa(class_new_info->id,class_item,10);//转换整形为字符型
				SetWindowText(EDIT_newid,class_item);
				break;
			//确认修改
			case BUTTON_a_class_modification_affirm:
				GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//获取newnaeme框内容到new_name
				GetWindowText(EDIT_newcollege,new_college,GetWindowTextLength(EDIT_newcollege)+1);//获取newcollege框内容到new_college
				GetWindowText(EDIT_newprofession,new_profession,GetWindowTextLength(EDIT_newprofession)+1);//获取newprofession框内容到new_profession
				if(state_a_class_modification==1)//确认修改现有专业信息
				{
				if(strlen(new_name)>28)
				{
					MessageBox(NULL,"班级名称输入有误！","警告",MB_OK);
					strcpy(new_name,class_old_info->name);
					SetWindowText(EDIT_newname,class_old_info->name);
					return FALSE;
				}
				if(strcmp(new_name,class_old_info->name)==0)
				{
					MessageBox(NULL,"没有修改任何信息！","警告",MB_OK);
					return FALSE;
				}
				if((strcmp(new_college,class_old_info->college)==0)||(strcmp(new_profession,class_old_info->profession)==0))
				{
					MessageBox(NULL,"新的所属学院、专业信息不会存储！若想修改学院、专业请删除数据后重新规定学院！","警告",MB_OK);
					return FALSE;
				}
				class_modification_p=class_head->next;
				for(i=0;i<class_old_info->id;i++)
					class_modification_p=class_modification_p->next;
				strcpy(class_modification_p->name,new_name);
				class_save(class_head);
				class_load(class_head);
				SetWindowText(EDIT_oldname,new_name);
				MessageBox(NULL,"修改成功！","警告",MB_OK);
				}
				if(state_a_class_modification==2)//确认增添学院信息
				{
					GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//获取newnaeme框内容到new_name
					GetWindowText(EDIT_newcollege,new_college,GetWindowTextLength(EDIT_newcollege)+1);//获取newcollege框内容到new_college
					GetWindowText(EDIT_newprofession,new_profession,GetWindowTextLength(EDIT_newprofession)+1);//获取newprofession框内容到new_profession
					class_modification_p=class_head->next;
					college_load(college_head);
					college_p=college_head->next;
					profession_load(profession_head);
					profession_p=profession_head->next;
					while(college_p)
					{
						if(strcmp(college_p->name,new_college)==0)
						{
							add_class=1;
							while(profession_p)
							{
								if(strcmp(profession_p->name,new_profession)==0)
								{
									strcpy(class_new_info->profession,new_profession);
									strcpy(class_new_info->name,new_name);
									strcpy(class_new_info->college,new_college);
									class_new_info->college_id=college_p->id;
									add_class=2;
									break;
								}
								profession_p=profession_p->next;
							}
							break;
						}
						if(add_class==2)
							break;
						college_p=college_p->next;
					}
					if(add_class==0)
					{
						MessageBox(NULL,"学院不存在！","警告",MB_OK);
						break;
						return FALSE;
					}
					if(add_class==1)
					{
						MessageBox(NULL,"专业不存在！","警告",MB_OK);
						break;
						return FALSE;
					}
					if(strlen(new_name)==0||strlen(new_name)>40)
					{
						MessageBox(NULL,"专业名称非法！","警告",MB_OK);
						add_class=0;
						break;
						return FALSE;
					}
					for(i=0;i<class_head->next->num;i++)
					{
						class_modification_p=class_modification_p->next;
						if(strcmp(class_new_info->name,class_modification_p->name)==0)
						{
							MessageBox(NULL,"班级名称重复！","警告",MB_OK);
							add_class=0;
							return FALSE;
						}
					}
					class_modification_p->next=class_new_info;
					class_new_info->prior=class_modification_p;
					class_new_info->next=NULL;
					class_head->next->num++;
					class_save(class_head);
					class_load(class_head);
					SetWindowText(EDIT_oldid,class_item);
					SetWindowText(EDIT_oldid1,class_item);
					SetWindowText(EDIT_newid,class_item);
					SetWindowText(EDIT_oldname,class_new_info->name);
					SetWindowText(EDIT_newname,class_new_info->name);
					SetWindowText(EDIT_oldcollege,class_new_info->college);
					SetWindowText(EDIT_newcollege,class_new_info->college);
					SetWindowText(EDIT_oldprofession,class_new_info->profession);
					SetWindowText(EDIT_newprofession,class_new_info->profession);
					MessageBox(NULL,"修改成功！","提示",MB_OK);
					class_old_info=(class_List)malloc(sizeof(class_Lnode));
					strcpy(class_old_info->name,class_new_info->name);
					class_old_info->id=class_new_info->id;
					class_old_info->num=class_new_info->id;
					find_a_class_modification=1;
				}
				break;
			//删除学院
			case BUTTON_a_class_modification_delete:
				if(find_a_class_modification==1)
				{
				strcpy(message_a_class_modification,"确认删除专业：“");
				strcat(message_a_class_modification,class_old_info->name);
				strcat(message_a_class_modification,"”吗？");
				if(MessageBox(NULL,message_a_class_modification,"警告",MB_YESNO|MB_ICONEXCLAMATION)!=6)
				{
					return FALSE;
				}
				class_modification_p=class_head->next;
				for(i=0;i<class_old_info->id;i++)
					class_modification_p=class_modification_p->next;
				class_modification_p->num=-1;
				strcat(class_modification_p->name,"（已删除）");
				class_modification_p=class_head->next->next;
				class_save(class_head);
				class_load(class_head);
				SetWindowText(EDIT_oldid,"");
				SetWindowText(EDIT_oldid1,"");
				SetWindowText(EDIT_newid,"");
				SetWindowText(EDIT_oldname,"");
				SetWindowText(EDIT_newname,"");
				SetWindowText(EDIT_oldcollege,"");
				SetWindowText(EDIT_newcollege,"");
				SetWindowText(EDIT_oldprofession,"");
				SetWindowText(EDIT_newprofession,"");
				MessageBox(NULL,"删除成功！","警告",MB_OK);
				find_a_class_modification=0;
				break;
				}
				MessageBox(NULL,"非法操作！","警告",MB_OK);
				break;
			case BUTTON_a_class_modification_exit:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
		case WM_CLOSE:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
	}
    return FALSE;

}
//IDD_a_account_inquir窗口回调函数
	int account_ck; //标记是否初始化内容，1.是，0.否
	int account_now;
LRESULT CALLBACK	A_ACCOUNT_INQUIRE(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,sum,page,print;//sum.资料总数 page.总页数 now.当前页数 print.当前页资料总数
	account_List page_head;

	char char_page[30],item[10];
	HWND EDIT_id1,EDIT_id2,EDIT_id3,EDIT_id4,EDIT_id5,EDIT_id6;
	HWND EDIT_name1,EDIT_name2,EDIT_name3,EDIT_name4,EDIT_name5,EDIT_name6;
	HWND EDIT_sex1,EDIT_sex2,EDIT_sex3,EDIT_sex4,EDIT_sex5,EDIT_sex6;
	HWND EDIT_face1,EDIT_face2,EDIT_face3,EDIT_face4,EDIT_face5,EDIT_face6;
	HWND EDIT_college1,EDIT_college2,EDIT_college3,EDIT_college4,EDIT_college5,EDIT_college6;
	HWND EDIT_profession1,EDIT_profession2,EDIT_profession3,EDIT_profession4,EDIT_profession5,EDIT_profession6;
	HWND EDIT_grade1,EDIT_grade2,EDIT_grade3,EDIT_grade4,EDIT_grade5,EDIT_grade6;
	HWND EDIT_page;
	account_head=(account_List)malloc(sizeof(account_Lnode));
	account_load(account_head);
	sum=account_head->next->num;
	page=sum/6;
	if(sum%6!=0)
		page++;
	EDIT_id1=GetDlgItem(hDlg,EDIT_a_account_inquire_id1);
	EDIT_id2=GetDlgItem(hDlg,EDIT_a_account_inquire_id2);
	EDIT_id3=GetDlgItem(hDlg,EDIT_a_account_inquire_id3);
	EDIT_id4=GetDlgItem(hDlg,EDIT_a_account_inquire_id4);
	EDIT_id5=GetDlgItem(hDlg,EDIT_a_account_inquire_id5);
	EDIT_id6=GetDlgItem(hDlg,EDIT_a_account_inquire_id6);
	EDIT_name1=GetDlgItem(hDlg,EDIT_a_account_inquire_name1);
	EDIT_name2=GetDlgItem(hDlg,EDIT_a_account_inquire_name2);
	EDIT_name3=GetDlgItem(hDlg,EDIT_a_account_inquire_name3);
	EDIT_name4=GetDlgItem(hDlg,EDIT_a_account_inquire_name4);
	EDIT_name5=GetDlgItem(hDlg,EDIT_a_account_inquire_name5);
	EDIT_name6=GetDlgItem(hDlg,EDIT_a_account_inquire_name6);
	EDIT_sex1=GetDlgItem(hDlg,EDIT_a_account_inquire_sex1);
	EDIT_sex2=GetDlgItem(hDlg,EDIT_a_account_inquire_sex2);
	EDIT_sex3=GetDlgItem(hDlg,EDIT_a_account_inquire_sex3);
	EDIT_sex4=GetDlgItem(hDlg,EDIT_a_account_inquire_sex4);
	EDIT_sex5=GetDlgItem(hDlg,EDIT_a_account_inquire_sex5);
	EDIT_sex6=GetDlgItem(hDlg,EDIT_a_account_inquire_sex6);
	EDIT_face1=GetDlgItem(hDlg,EDIT_a_account_inquire_face1);
	EDIT_face2=GetDlgItem(hDlg,EDIT_a_account_inquire_face2);
	EDIT_face3=GetDlgItem(hDlg,EDIT_a_account_inquire_face3);
	EDIT_face4=GetDlgItem(hDlg,EDIT_a_account_inquire_face4);
	EDIT_face5=GetDlgItem(hDlg,EDIT_a_account_inquire_face5);
	EDIT_face6=GetDlgItem(hDlg,EDIT_a_account_inquire_face6);
	EDIT_college1=GetDlgItem(hDlg,EDIT_a_account_inquire_college1);
	EDIT_college2=GetDlgItem(hDlg,EDIT_a_account_inquire_college2);
	EDIT_college3=GetDlgItem(hDlg,EDIT_a_account_inquire_college3);
	EDIT_college4=GetDlgItem(hDlg,EDIT_a_account_inquire_college4);
	EDIT_college5=GetDlgItem(hDlg,EDIT_a_account_inquire_college5);
	EDIT_college6=GetDlgItem(hDlg,EDIT_a_account_inquire_college6);
	EDIT_profession1=GetDlgItem(hDlg,EDIT_a_account_inquire_profession1);
	EDIT_profession2=GetDlgItem(hDlg,EDIT_a_account_inquire_profession2);
	EDIT_profession3=GetDlgItem(hDlg,EDIT_a_account_inquire_profession3);
	EDIT_profession4=GetDlgItem(hDlg,EDIT_a_account_inquire_profession4);
	EDIT_profession5=GetDlgItem(hDlg,EDIT_a_account_inquire_profession5);
	EDIT_profession6=GetDlgItem(hDlg,EDIT_a_account_inquire_profession6);
	EDIT_grade1=GetDlgItem(hDlg,EDIT_a_account_inquire_grade1);
	EDIT_grade2=GetDlgItem(hDlg,EDIT_a_account_inquire_grade2);
	EDIT_grade3=GetDlgItem(hDlg,EDIT_a_account_inquire_grade3);
	EDIT_grade4=GetDlgItem(hDlg,EDIT_a_account_inquire_grade4);
	EDIT_grade5=GetDlgItem(hDlg,EDIT_a_account_inquire_grade5);
	EDIT_grade6=GetDlgItem(hDlg,EDIT_a_account_inquire_grade6);
	EDIT_page=GetDlgItem(hDlg,EDIT_a_account_inquire_page);
	
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case BUTTON_a_account_inquire_top:
				account_ck=1;
				account_now=1;
				if(sum>=6)
					print=6;//若总资料数不小于6，则第一页显示6条数据
				if(sum<6)
					print=sum;//若资料总数小于6，则第一页显示全部sum条数据
				page_head=account_head->next->next;//指向第一页第一条记录
				if(print>=1)
				{
					SetWindowText(EDIT_id1,page_head->id);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_sex1,page_head->sex);
					SetWindowText(EDIT_face1,page_head->face);
					SetWindowText(EDIT_college1,page_head->college);
					SetWindowText(EDIT_profession1,page_head->profession);
					SetWindowText(EDIT_grade1,page_head->grade);
					page_head=page_head->next;
				}
				if(print>=2)
				{
					SetWindowText(EDIT_id2,page_head->id);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_sex2,page_head->sex);
					SetWindowText(EDIT_face2,page_head->face);
					SetWindowText(EDIT_college2,page_head->college);
					SetWindowText(EDIT_profession2,page_head->profession);
					SetWindowText(EDIT_grade2,page_head->grade);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					SetWindowText(EDIT_id3,page_head->id);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_sex3,page_head->sex);
					SetWindowText(EDIT_face3,page_head->face);
					SetWindowText(EDIT_college3,page_head->college);
					SetWindowText(EDIT_profession3,page_head->profession);
					SetWindowText(EDIT_grade3,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=4)
				{
					SetWindowText(EDIT_id4,page_head->id);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_sex4,page_head->sex);
					SetWindowText(EDIT_face4,page_head->face);
					SetWindowText(EDIT_college4,page_head->college);
					SetWindowText(EDIT_profession4,page_head->profession);
					SetWindowText(EDIT_grade4,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=5)
				{
					SetWindowText(EDIT_id5,page_head->id);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_sex5,page_head->sex);
					SetWindowText(EDIT_face5,page_head->face);
					SetWindowText(EDIT_college5,page_head->college);
					SetWindowText(EDIT_profession5,page_head->profession);
					SetWindowText(EDIT_grade5,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=6)
				{
					SetWindowText(EDIT_id6,page_head->id);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_sex6,page_head->sex);
					SetWindowText(EDIT_face6,page_head->face);
					SetWindowText(EDIT_college6,page_head->college);
					SetWindowText(EDIT_profession6,page_head->profession);
					SetWindowText(EDIT_grade6,page_head->grade);

					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				itoa(account_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"页，共");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				break;
			case BUTTON_a_account_inquire_prior:
				if(account_ck!=1)
				{
					MessageBox(NULL,"请点击“返回顶部”显示第一页学院信息！","提示",MB_OK);
					break;
				}
				page_head=account_head->next->next;
				if(account_now-1<=0)
				{
					MessageBox(NULL,"已经到第一页！","提示",MB_OK);
					return FALSE;
				}
				else
					account_now--;
				for(i=0;i<(account_now-1)*6;i++)//将page_head移到当前页的第一项
					page_head=page_head->next;
				
				if(account_now==page)//如果在最后一页，则计算最后一页记录数量
					print=sum-(page-1)*6;
				else//否则，记录总数为6
					print=6;
				//清空编辑框内容
					SetWindowText(EDIT_id1,"");
					SetWindowText(EDIT_id2,"");
					SetWindowText(EDIT_id3,"");
					SetWindowText(EDIT_id4,"");
					SetWindowText(EDIT_id5,"");
					SetWindowText(EDIT_id6,"");
					SetWindowText(EDIT_name1,"");
					SetWindowText(EDIT_name2,"");
					SetWindowText(EDIT_name3,"");
					SetWindowText(EDIT_name4,"");
					SetWindowText(EDIT_name5,"");
					SetWindowText(EDIT_name6,"");
					SetWindowText(EDIT_sex1,"");
					SetWindowText(EDIT_sex2,"");
					SetWindowText(EDIT_sex3,"");
					SetWindowText(EDIT_sex4,"");
					SetWindowText(EDIT_sex5,"");
					SetWindowText(EDIT_sex6,"");
					SetWindowText(EDIT_face1,"");
					SetWindowText(EDIT_face2,"");
					SetWindowText(EDIT_face3,"");
					SetWindowText(EDIT_face4,"");
					SetWindowText(EDIT_face5,"");
					SetWindowText(EDIT_face6,"");
					SetWindowText(EDIT_college1,"");
					SetWindowText(EDIT_college2,"");
					SetWindowText(EDIT_college3,"");
					SetWindowText(EDIT_college4,"");
					SetWindowText(EDIT_college5,"");
					SetWindowText(EDIT_college6,"");
					SetWindowText(EDIT_profession1,"");
					SetWindowText(EDIT_profession2,"");
					SetWindowText(EDIT_profession3,"");
					SetWindowText(EDIT_profession4,"");
					SetWindowText(EDIT_profession5,"");
					SetWindowText(EDIT_profession6,"");
					SetWindowText(EDIT_grade1,"");
					SetWindowText(EDIT_grade2,"");
					SetWindowText(EDIT_grade3,"");
					SetWindowText(EDIT_grade4,"");
					SetWindowText(EDIT_grade5,"");
					SetWindowText(EDIT_grade6,"");
				if(print>=1)
				{
					SetWindowText(EDIT_id1,page_head->id);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_sex1,page_head->sex);
					SetWindowText(EDIT_face1,page_head->face);
					SetWindowText(EDIT_college1,page_head->college);
					SetWindowText(EDIT_profession1,page_head->profession);
					SetWindowText(EDIT_grade1,page_head->grade);
					page_head=page_head->next;
				}
				if(print>=2)
				{
					SetWindowText(EDIT_id2,page_head->id);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_sex2,page_head->sex);
					SetWindowText(EDIT_face2,page_head->face);
					SetWindowText(EDIT_college2,page_head->college);
					SetWindowText(EDIT_profession2,page_head->profession);
					SetWindowText(EDIT_grade2,page_head->grade);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					SetWindowText(EDIT_id3,page_head->id);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_sex3,page_head->sex);
					SetWindowText(EDIT_face3,page_head->face);
					SetWindowText(EDIT_college3,page_head->college);
					SetWindowText(EDIT_profession3,page_head->profession);
					SetWindowText(EDIT_grade3,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=4)
				{
					SetWindowText(EDIT_id4,page_head->id);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_sex4,page_head->sex);
					SetWindowText(EDIT_face4,page_head->face);
					SetWindowText(EDIT_college4,page_head->college);
					SetWindowText(EDIT_profession4,page_head->profession);
					SetWindowText(EDIT_grade4,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=5)
				{
					SetWindowText(EDIT_id5,page_head->id);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_sex5,page_head->sex);
					SetWindowText(EDIT_face5,page_head->face);
					SetWindowText(EDIT_college5,page_head->college);
					SetWindowText(EDIT_profession5,page_head->profession);
					SetWindowText(EDIT_grade5,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=6)
				{
					SetWindowText(EDIT_id6,page_head->id);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_sex6,page_head->sex);
					SetWindowText(EDIT_face6,page_head->face);
					SetWindowText(EDIT_college6,page_head->college);
					SetWindowText(EDIT_profession6,page_head->profession);
					SetWindowText(EDIT_grade6,page_head->grade);

					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				itoa(account_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"页，共");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_account_inquire_next:
				if(account_ck!=1)
				{
					MessageBox(NULL,"请点击“返回顶部”显示第一页学院信息！","提示",MB_OK);
					break;
				}
				page_head=account_head->next->next;//移到记录第一页第一条记录
				if(account_now+1>page)//如果当前页+1等于总页数，弹出警告
				{
					MessageBox(NULL,"已经到最后一页！","提示",MB_OK);
					return FALSE;
				}
				else//否则，跳转页数
				{
					account_now++;
				}
				for(i=0;i<(account_now-1)*6;i++)//将page_head移到当前页的第一项
					page_head=page_head->next;
				
				if(account_now==page)//如果在最后一页，则计算最后一页记录数量
					print=sum-(page-1)*6;
				else//否则，记录总数为6
					print=6;
				//清空编辑框内容
					SetWindowText(EDIT_id1,"");
					SetWindowText(EDIT_id2,"");
					SetWindowText(EDIT_id3,"");
					SetWindowText(EDIT_id4,"");
					SetWindowText(EDIT_id5,"");
					SetWindowText(EDIT_id6,"");
					SetWindowText(EDIT_name1,"");
					SetWindowText(EDIT_name2,"");
					SetWindowText(EDIT_name3,"");
					SetWindowText(EDIT_name4,"");
					SetWindowText(EDIT_name5,"");
					SetWindowText(EDIT_name6,"");
					SetWindowText(EDIT_sex1,"");
					SetWindowText(EDIT_sex2,"");
					SetWindowText(EDIT_sex3,"");
					SetWindowText(EDIT_sex4,"");
					SetWindowText(EDIT_sex5,"");
					SetWindowText(EDIT_sex6,"");
					SetWindowText(EDIT_face1,"");
					SetWindowText(EDIT_face2,"");
					SetWindowText(EDIT_face3,"");
					SetWindowText(EDIT_face4,"");
					SetWindowText(EDIT_face5,"");
					SetWindowText(EDIT_face6,"");
					SetWindowText(EDIT_college1,"");
					SetWindowText(EDIT_college2,"");
					SetWindowText(EDIT_college3,"");
					SetWindowText(EDIT_college4,"");
					SetWindowText(EDIT_college5,"");
					SetWindowText(EDIT_college6,"");
					SetWindowText(EDIT_profession1,"");
					SetWindowText(EDIT_profession2,"");
					SetWindowText(EDIT_profession3,"");
					SetWindowText(EDIT_profession4,"");
					SetWindowText(EDIT_profession5,"");
					SetWindowText(EDIT_profession6,"");
					SetWindowText(EDIT_grade1,"");
					SetWindowText(EDIT_grade2,"");
					SetWindowText(EDIT_grade3,"");
					SetWindowText(EDIT_grade4,"");
					SetWindowText(EDIT_grade5,"");
					SetWindowText(EDIT_grade6,"");
				if(print>=1)
				{
					SetWindowText(EDIT_id1,page_head->id);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_sex1,page_head->sex);
					SetWindowText(EDIT_face1,page_head->face);
					SetWindowText(EDIT_college1,page_head->college);
					SetWindowText(EDIT_profession1,page_head->profession);
					SetWindowText(EDIT_grade1,page_head->grade);
					page_head=page_head->next;
				}
				if(print>=2)
				{
					SetWindowText(EDIT_id2,page_head->id);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_sex2,page_head->sex);
					SetWindowText(EDIT_face2,page_head->face);
					SetWindowText(EDIT_college2,page_head->college);
					SetWindowText(EDIT_profession2,page_head->profession);
					SetWindowText(EDIT_grade2,page_head->grade);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					SetWindowText(EDIT_id3,page_head->id);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_sex3,page_head->sex);
					SetWindowText(EDIT_face3,page_head->face);
					SetWindowText(EDIT_college3,page_head->college);
					SetWindowText(EDIT_profession3,page_head->profession);
					SetWindowText(EDIT_grade3,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=4)
				{
					SetWindowText(EDIT_id4,page_head->id);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_sex4,page_head->sex);
					SetWindowText(EDIT_face4,page_head->face);
					SetWindowText(EDIT_college4,page_head->college);
					SetWindowText(EDIT_profession4,page_head->profession);
					SetWindowText(EDIT_grade4,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=5)
				{
					SetWindowText(EDIT_id5,page_head->id);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_sex5,page_head->sex);
					SetWindowText(EDIT_face5,page_head->face);
					SetWindowText(EDIT_college5,page_head->college);
					SetWindowText(EDIT_profession5,page_head->profession);
					SetWindowText(EDIT_grade5,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=6)
				{
					SetWindowText(EDIT_id6,page_head->id);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_sex6,page_head->sex);
					SetWindowText(EDIT_face6,page_head->face);
					SetWindowText(EDIT_college6,page_head->college);
					SetWindowText(EDIT_profession6,page_head->profession);
					SetWindowText(EDIT_grade6,page_head->grade);

					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				
				itoa(account_now,item,10);

				strcat(char_page,item);
				
				strcat(char_page,"页，共");
				itoa(page,item,10);//转换整形为字符型
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_account_inquire_exit:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
				break;
			}
			break;
		case WM_CLOSE:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
	}
    return FALSE;

}
//IDD_a_account_modification窗口回调函数

	int find_a_account_modification;//0.找到 1.未找到
	int state_a_account_modification;//修改状态提示
	int add_account;//增添信息合法，1.合法,other.不合法
	char account_item[10];
	account_List account_modification_p,account_new_info,account_old_info;
	account_List account_delete;
LRESULT CALLBACK	A_ACCOUNT_MODIFICATION(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	college_List college_p;
	HWND EDIT_oldid,EDIT_oldid1,EDIT_newid;
	HWND EDIT_oldname,EDIT_newname;
	HWND EDIT_oldsex,EDIT_newsex;
	HWND EDIT_oldnation,EDIT_newnation;
	HWND EDIT_oldface,EDIT_newface;
	HWND EDIT_oldbirth,EDIT_newbirth;
	HWND EDIT_oldtime,EDIT_newtime;
	HWND EDIT_oldcollege,EDIT_newcollege;
	HWND EDIT_oldprofession,EDIT_newprofession;
	HWND EDIT_oldgrade,EDIT_newgrade;
	char new_id[100],new_name[100],new_sex[100],new_nation[100],new_face[100],new_birth[100],new_time[100],new_college[100],new_profession[100],new_grade[100];
	char year[10],month[5],day[5];
	char year1[10],month1[5];
	char message_a_account_modification[60];
	char *stop;//为strtol定义的终止字符指针
	int id;
	int i;
	account_head=(account_List)malloc(sizeof(account_Lnode));
	account_load(account_head);
	EDIT_oldid=GetDlgItem(hDlg,EDIT_a_account_modification_oldid);
	EDIT_oldid1=GetDlgItem(hDlg,EDIT_a_account_modification_oldid1);
	EDIT_oldname=GetDlgItem(hDlg,EDIT_a_account_modification_oldname);
	EDIT_oldsex=GetDlgItem(hDlg,EDIT_a_account_modification_oldsex);
	EDIT_oldnation=GetDlgItem(hDlg,EDIT_a_account_modification_oldnation);
	EDIT_oldface=GetDlgItem(hDlg,EDIT_a_account_modification_oldface);
	EDIT_oldbirth=GetDlgItem(hDlg,EDIT_a_account_modification_oldbirth);
	EDIT_oldtime=GetDlgItem(hDlg,EDIT_a_account_modification_oldtime);
	EDIT_oldcollege=GetDlgItem(hDlg,EDIT_a_account_modification_oldcollege);
	EDIT_oldprofession=GetDlgItem(hDlg,EDIT_a_account_modification_oldprofession);
	EDIT_oldgrade=GetDlgItem(hDlg,EDIT_a_account_modification_oldgrade);
	
	EDIT_newid=GetDlgItem(hDlg,EDIT_a_account_modification_newid);
	EDIT_newname=GetDlgItem(hDlg,EDIT_a_account_modification_newname);
	EDIT_newsex=GetDlgItem(hDlg,EDIT_a_account_modification_newsex);
	EDIT_newnation=GetDlgItem(hDlg,EDIT_a_account_modification_newnation);
	EDIT_newface=GetDlgItem(hDlg,EDIT_a_account_modification_newface);
	EDIT_newbirth=GetDlgItem(hDlg,EDIT_a_account_modification_newbirth);
	EDIT_newtime=GetDlgItem(hDlg,EDIT_a_account_modification_newtime);
	EDIT_newcollege=GetDlgItem(hDlg,EDIT_a_account_modification_newcollege);
	EDIT_newprofession=GetDlgItem(hDlg,EDIT_a_account_modification_newprofession);
	EDIT_newgrade=GetDlgItem(hDlg,EDIT_a_account_modification_newgrade);
	
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			//通过id定位管理
			case BUTTON_a_account_modification_location:
				find_a_account_modification=0;
				GetWindowText(EDIT_oldid,account_item,GetWindowTextLength(EDIT_oldid)+1);//获取oldid编辑框内容到item
				account_modification_p=account_head->next->next;
				while(account_modification_p)
				{
					if(strcmp(account_modification_p->id,account_item)==0)
					{
						account_old_info=(account_List)malloc(sizeof(account_Lnode));
						strcpy(account_old_info->id,account_modification_p->id);
						strcpy(account_old_info->name,account_modification_p->name);
						strcpy(account_old_info->sex,account_modification_p->sex);
						strcpy(account_old_info->nation,account_modification_p->nation);
						strcpy(account_old_info->face,account_modification_p->face);
						strcpy(account_old_info->birth,account_modification_p->birth);
						strcpy(account_old_info->time,account_modification_p->time);
						strcpy(account_old_info->college,account_modification_p->college);
						strcpy(account_old_info->profession,account_modification_p->profession);
						strcpy(account_old_info->grade,account_modification_p->grade);
						account_old_info->num=account_modification_p->num;
						find_a_account_modification=1;
						break;
					}
					else
						account_modification_p=account_modification_p->next;
				}
				if(find_a_account_modification!=1)
				{
					MessageBox(NULL,"输入有误！","ERROR!",MB_OK);
					break;
					return FALSE;
				}
				SetWindowText(EDIT_oldid1,account_old_info->id);
				SetWindowText(EDIT_oldname,account_old_info->name);
				SetWindowText(EDIT_oldsex,account_old_info->sex);
				SetWindowText(EDIT_oldnation,account_old_info->nation);
				SetWindowText(EDIT_oldface,account_old_info->face);
				SetWindowText(EDIT_oldbirth,account_old_info->birth);
				SetWindowText(EDIT_oldtime,account_old_info->time);
				SetWindowText(EDIT_oldcollege,account_old_info->college);
				SetWindowText(EDIT_oldprofession,account_old_info->profession);
				SetWindowText(EDIT_oldgrade,account_old_info->grade);

				SetWindowText(EDIT_newid,account_old_info->id);
				SetWindowText(EDIT_newname,account_old_info->name);
				SetWindowText(EDIT_newsex,account_old_info->sex);
				SetWindowText(EDIT_newnation,account_old_info->nation);
				SetWindowText(EDIT_newface,account_old_info->face);
				SetWindowText(EDIT_newbirth,account_old_info->birth);
				SetWindowText(EDIT_newtime,account_old_info->time);
				SetWindowText(EDIT_newcollege,account_old_info->college);
				SetWindowText(EDIT_newprofession,account_old_info->profession);
				SetWindowText(EDIT_newgrade,account_old_info->grade);

				state_a_account_modification=1;//修改状态为修改
				MessageBox(NULL,"定位成功！请修改数据或删除数据。修改完毕按“确认修改”保存！","ERROR!",MB_OK);
				break;
			//增添管理
			case BUTTON_a_account_modification_add:
				MessageBox(NULL,"请在新数据信息框中输入新管理员信息,初始密码为“admin”","提示",MB_OK);
				find_a_account_modification=0;
				state_a_account_modification=2;//修改状态为增添管理

				SetWindowText(EDIT_oldid,"");
				SetWindowText(EDIT_oldid1,"");
				SetWindowText(EDIT_oldname,"");
				SetWindowText(EDIT_oldsex,"");
				SetWindowText(EDIT_oldnation,"");
				SetWindowText(EDIT_oldface,"");
				SetWindowText(EDIT_oldbirth,"");
				SetWindowText(EDIT_oldtime,"");
				SetWindowText(EDIT_oldcollege,"");
				SetWindowText(EDIT_oldprofession,"");
				SetWindowText(EDIT_oldgrade,"");

				SetWindowText(EDIT_newid,"账号字符数<20");
				SetWindowText(EDIT_newname,"姓名字数<10");
				SetWindowText(EDIT_newsex,"男or女");
				SetWindowText(EDIT_newnation,"xx族");
				SetWindowText(EDIT_newface,"群众");
				SetWindowText(EDIT_newbirth,"xxxx年xx月xx日");
				SetWindowText(EDIT_newtime,"xxxx年xx月");
				SetWindowText(EDIT_newcollege,"xxxxxxxxxxxxxx学院");
				SetWindowText(EDIT_newprofession,"");
				SetWindowText(EDIT_newgrade,"讲师");

				account_new_info=(account_List)malloc(sizeof(account_Lnode));
				account_new_info->num=account_head->next->num+1;
				itoa(account_new_info->num,account_item,10);
				strcpy(message_a_account_modification,"新管理员编码为：");
				strcat(message_a_account_modification,account_item);
				SetWindowText(EDIT_oldid,message_a_account_modification);
				break;
			//确认修改
			case BUTTON_a_account_modification_affirm:
				GetWindowText(EDIT_newid,new_id,GetWindowTextLength(EDIT_newid)+1);//获取newid框内容到new_id
				GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//获取newnaeme框内容到new_name
				GetWindowText(EDIT_newsex,new_sex,GetWindowTextLength(EDIT_newsex)+1);//获取newsex框内容到new_sex
				GetWindowText(EDIT_newnation,new_nation,GetWindowTextLength(EDIT_newnation)+1);//获取newnation框内容到new_nation
				GetWindowText(EDIT_newface,new_face,GetWindowTextLength(EDIT_newface)+1);//获取newface框内容到new_face
				GetWindowText(EDIT_newbirth,new_birth,GetWindowTextLength(EDIT_newbirth)+1);//获取newbirth框内容到new_birth
				GetWindowText(EDIT_newtime,new_time,GetWindowTextLength(EDIT_newtime)+1);//获取newtime框内容到new_time
				GetWindowText(EDIT_newcollege,new_college,GetWindowTextLength(EDIT_newcollege)+1);//获取newcollege框内容到new_college
				GetWindowText(EDIT_newprofession,new_profession,GetWindowTextLength(EDIT_newprofession)+1);//获取newprofession框内容到new_profession
				GetWindowText(EDIT_newgrade,new_grade,GetWindowTextLength(EDIT_newgrade)+1);//获取newngrade框内容到new_grade
				if(state_a_account_modification==1)//确认修改现有专业信息
				{
				if(strcmp(new_id,account_old_info->id)!=0)
				{
					MessageBox(NULL,"不允许修改账号！","警告",MB_OK);
					strcpy(new_id,account_old_info->id);
					SetWindowText(EDIT_newid,account_old_info->id);
					return FALSE;
				}
				if(strlen(new_name)>28||strlen(new_name)<2)
				{
					MessageBox(NULL,"管理员姓名输入有误！","警告",MB_OK);
					strcpy(new_name,account_old_info->name);
					SetWindowText(EDIT_newname,account_old_info->name);
					return FALSE;
				}
				if((strcmp(new_sex,"男")!=0)&&strcmp(new_sex,"女")!=0)
				{
					MessageBox(NULL,"管理员性别输入有误！","警告",MB_OK);
					strcpy(new_sex,account_old_info->sex);
					SetWindowText(EDIT_newsex,account_old_info->sex);
					return FALSE;
				}
				if(strlen(new_nation)>12||strlen(new_nation)<2)
				{
					MessageBox(NULL,"管理员民族输入有误！","警告",MB_OK);
					strcpy(new_nation,account_old_info->nation);
					SetWindowText(EDIT_newnation,account_old_info->nation);
					return FALSE;
				}
				if(strlen(new_face)>12||strlen(new_face)<2)
				{
					MessageBox(NULL,"管理员民族输入有误！","警告",MB_OK);
					strcpy(new_face,account_old_info->face);
					SetWindowText(EDIT_newface,account_old_info->face);
					return FALSE;
				}
				sscanf(new_birth,"%4s%*2s%2s%*2s%2s%*s",&year,&month,&day);
				if(strcmp(year,"1960")<0||strcmp(year,"2017")>0)
					{
					MessageBox(NULL,"管理员出生年份输入有误！","警告",MB_OK);
					strcpy(new_birth,account_old_info->birth);
					SetWindowText(EDIT_newbirth,account_old_info->birth);
					return FALSE;
				}
				if(strcmp(month,"01")<0||strcmp(month,"12")>0)
					{
					MessageBox(NULL,"管理员出生月份输入有误！","警告",MB_OK);
					strcpy(new_birth,account_old_info->birth);
					SetWindowText(EDIT_newbirth,account_old_info->birth);
					return FALSE;
				}
				if(strcmp(day,"01")<0||strcmp(day,"31")>0)
					{
					MessageBox(NULL,"管理员出生日期输入有误！","警告",MB_OK);
					strcpy(new_birth,account_old_info->birth);
					SetWindowText(EDIT_newbirth,account_old_info->birth);
					return FALSE;
				}
				sscanf(new_time,"%4s%*2s%2s%*2s%*s",&year,&month);
				if(strcmp(year,"1960")<0||strcmp(year,"2017")>0)
					{
					MessageBox(NULL,"管理员入职年份输入有误！","警告",MB_OK);
					strcpy(new_time,account_old_info->time);
					SetWindowText(EDIT_newtime,account_old_info->time);
					return FALSE;
				}
				if(strcmp(month,"01")<0||strcmp(month,"12")>0)
					{
					MessageBox(NULL,"管理员入职月份输入有误！","警告",MB_OK);
					strcpy(new_time,account_old_info->time);
					SetWindowText(EDIT_newtime,account_old_info->time);
					return FALSE;
				}

				if(strcmp(new_college,account_old_info->college)!=0)
				{
					MessageBox(NULL,"新的所属学院信息不会存储！\n若想修改学院请删除数据后重新规定学院！","警告",MB_OK);
					return FALSE;
				}
				if(strlen(new_profession)>30||strlen(new_profession)<2)
				{
					MessageBox(NULL,"管理员所属部门输入有误！","警告",MB_OK);
					strcpy(new_profession,account_old_info->profession);
					SetWindowText(EDIT_newprofession,account_old_info->profession);
					return FALSE;
				}

				if(strlen(new_grade)>20||strlen(new_grade)<2)
				{
					MessageBox(NULL,"管理员所属部门输入有误！","警告",MB_OK);
					strcpy(new_grade,account_old_info->grade);
					SetWindowText(EDIT_newgrade,account_old_info->grade);
					return FALSE;
				}
				account_modification_p=account_head->next;
				for(i=0;i<account_old_info->num;i++)
					account_modification_p=account_modification_p->next;
			    strcpy(account_modification_p->id,new_id);
				strcpy(account_modification_p->name,new_name);
				strcpy(account_modification_p->sex,new_sex);
				strcpy(account_modification_p->nation,new_nation);
				strcpy(account_modification_p->face,new_face);
				strcpy(account_modification_p->birth,new_birth);
				strcpy(account_modification_p->time,new_time);
				strcpy(account_modification_p->college,new_college);
				strcpy(account_modification_p->profession,new_profession);
				strcpy(account_modification_p->grade,new_grade);
				account_save(account_head);
				account_load(account_head);
				SetWindowText(EDIT_oldname,new_name);
				MessageBox(NULL,"修改成功！","警告",MB_OK);
				}

				
				if(state_a_account_modification==2)//确认增添学院信息
				{
					GetWindowText(EDIT_newid,new_id,GetWindowTextLength(EDIT_newid)+1);//获取newid框内容到new_id
				GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//获取newnaeme框内容到new_name
				GetWindowText(EDIT_newsex,new_sex,GetWindowTextLength(EDIT_newsex)+1);//获取newsex框内容到new_sex
				GetWindowText(EDIT_newnation,new_nation,GetWindowTextLength(EDIT_newnation)+1);//获取newnation框内容到new_nation
				GetWindowText(EDIT_newface,new_face,GetWindowTextLength(EDIT_newface)+1);//获取newface框内容到new_face
				GetWindowText(EDIT_newbirth,new_birth,GetWindowTextLength(EDIT_newbirth)+1);//获取newbirth框内容到new_birth
				GetWindowText(EDIT_newtime,new_time,GetWindowTextLength(EDIT_newtime)+1);//获取newtime框内容到new_time
				GetWindowText(EDIT_newcollege,new_college,GetWindowTextLength(EDIT_newcollege)+1);//获取newcollege框内容到new_college
				GetWindowText(EDIT_newprofession,new_profession,GetWindowTextLength(EDIT_newprofession)+1);//获取newprofession框内容到new_profession
				GetWindowText(EDIT_newgrade,new_grade,GetWindowTextLength(EDIT_newgrade)+1);//获取newngrade框内容到new_grade
				if(strlen(new_id)>28||strlen(new_id)<2)
				{
					MessageBox(NULL,"管理员账号输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newid,"");
					break;
					return FALSE;
				}	
				if(strlen(new_name)>28||strlen(new_name)<2)
				{
					MessageBox(NULL,"管理员姓名输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newname,"");
					break;
					return FALSE;
				}
				if((strcmp(new_sex,"男")!=0)&&strcmp(new_sex,"女")!=0)
				{
					MessageBox(NULL,"管理员性别输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newsex,"");
					break;
					return FALSE;
				}
				if(strlen(new_nation)>12||strlen(new_nation)<2)
				{
					MessageBox(NULL,"管理员民族输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newnation,"");
					break;
					return FALSE;
				}
				if(strlen(new_face)>12||strlen(new_face)<2)
				{
					MessageBox(NULL,"管理员政治面貌输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newface,"");
					break;
					return FALSE;
				}
				sscanf(new_birth,"%4s%*2s%2s%*2s%2s%*s",&year,&month,&day);
				if(strcmp(year,"1960")<0||strcmp(year,"2017")>0)
					{
					MessageBox(NULL,"管理员出生年份输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newbirth,"");
					break;
					return FALSE;
				}
				if(strcmp(month,"01")<0||strcmp(month,"12")>0)
					{
					MessageBox(NULL,"管理员出生月份输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newbirth,"");
					break;
					return FALSE;
				}
				if(strcmp(day,"01")<0||strcmp(day,"31")>0)
					{
					MessageBox(NULL,"管理员出生日期输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newbirth,"");
					break;
					return FALSE;
				}
				sscanf(new_time,"%4s%*2s%2s%*s",&year1,&month1);
				if(strcmp(year1,"1960")<0||strcmp(year1,"2017")>0)
					{
					MessageBox(NULL,"管理员入职年份输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newtime,"");
					break;
					return FALSE;
				}
				if(strcmp(month1,"01")<0||strcmp(month1,"12")>0)
					{
					MessageBox(NULL,"管理员入职月份输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newtime,"");
					break;
					return FALSE;
				}

				if(strlen(new_profession)>30||strlen(new_profession)<2)
				{
					MessageBox(NULL,"管理员所属部门输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newprofession,"");
					break;
					return FALSE;
				}
				if(strlen(new_grade)>20||strlen(new_grade)<2)
				{
					MessageBox(NULL,"管理员所属部门输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newgrade,"");
					break;
					return FALSE;
				}
					strcpy(account_new_info->password,"admin");
					strcpy(account_new_info->identity,"管理员");
					strcpy(account_new_info->id,new_id);
					strcpy(account_new_info->name,new_name);
					strcpy(account_new_info->sex,new_sex);
					strcpy(account_new_info->nation,new_nation);
					strcpy(account_new_info->face,new_face);
					strcpy(account_new_info->birth,new_birth);
					strcpy(account_new_info->time,new_time);
					strcpy(account_new_info->college,new_college);
					strcpy(account_new_info->profession,new_profession);
					strcpy(account_new_info->grade,new_grade);
					account_modification_p=account_head->next;
					college_load(college_head);
					college_p=college_head->next;
					while(college_p)
					{
						if(strcmp(college_p->name,new_college)==0)
						{
							strcpy(account_new_info->college,new_college);
							account_new_info->collegeid=college_p->id;
							add_account=1;
							break;
						}
						college_p=college_p->next;
					}
					if(add_account!=1)
					{
						MessageBox(NULL,"学院不存在！","警告",MB_OK);
						break;
						return FALSE;
					}
					if(strlen(new_name)==0||strlen(new_name)>20)
					{
						MessageBox(NULL,"专业名称非法！","警告",MB_OK);
						add_account=0;
						break;
						return FALSE;
					}
					for(i=0;i<account_head->next->num;i++)
					{
						account_modification_p=account_modification_p->next;
						if(strcmp(account_new_info->id,account_modification_p->id)==0)
						{
							MessageBox(NULL,"账号重复！","警告",MB_OK);
							add_account=0;
							break;
							return FALSE;
						}
					}
					account_modification_p->next=account_new_info;
					account_new_info->prior=account_modification_p;
					account_new_info->next=NULL;
					account_head->next->num++;
					account_save(account_head);
					account_load(account_head);

				SetWindowText(EDIT_oldid1,account_new_info->id);
				SetWindowText(EDIT_oldname,account_new_info->name);
				SetWindowText(EDIT_oldsex,account_new_info->sex);
				SetWindowText(EDIT_oldnation,account_new_info->nation);
				SetWindowText(EDIT_oldface,account_new_info->face);
				SetWindowText(EDIT_oldbirth,account_new_info->birth);
				SetWindowText(EDIT_oldtime,account_new_info->time);
				SetWindowText(EDIT_oldcollege,account_new_info->college);
				SetWindowText(EDIT_oldprofession,account_new_info->profession);
				SetWindowText(EDIT_oldgrade,account_new_info->grade);

				SetWindowText(EDIT_newname,account_new_info->name);
				SetWindowText(EDIT_newsex,account_new_info->sex);
				SetWindowText(EDIT_newnation,account_new_info->nation);
				SetWindowText(EDIT_newface,account_new_info->face);
				SetWindowText(EDIT_newbirth,account_new_info->birth);
				SetWindowText(EDIT_newtime,account_new_info->time);
				SetWindowText(EDIT_newcollege,account_new_info->college);
				SetWindowText(EDIT_newprofession,account_new_info->profession);
				SetWindowText(EDIT_newgrade,account_new_info->grade);

					MessageBox(NULL,"修改成功！","提示",MB_OK);
					account_old_info=(account_List)malloc(sizeof(account_Lnode));
					strcpy(account_old_info->name,account_new_info->name);
					strcpy(account_old_info->id,account_new_info->id);
					account_old_info->num=account_new_info->num;
					find_a_account_modification=1;
				}
				break;
			//删除管理
			case BUTTON_a_account_modification_delete:
				if(find_a_account_modification==1)
				{
					if(strcmp(account_old_info->id,account_mine->id)==0)
					{
						MessageBox(NULL,"不允许删除已登录账号！","警告",MB_OK|MB_ICONEXCLAMATION);
						return FALSE;
					}
				strcpy(message_a_account_modification,"确认删除管理员：“");
				strcat(message_a_account_modification,account_old_info->name);
				strcat(message_a_account_modification,"”吗？");
				if(MessageBox(NULL,message_a_account_modification,"警告",MB_YESNO|MB_ICONEXCLAMATION)!=6)
				{
					return FALSE;
				}
				account_modification_p=account_head->next;
				for(i=0;i<account_old_info->num;i++)
					account_modification_p=account_modification_p->next;
				account_modification_p->num=-1;
				strcat(account_modification_p->name,"（已删除）");
				account_modification_p=account_head->next->next;
				account_save(account_head);
				account_load(account_head);
				SetWindowText(EDIT_oldid1,"");
				SetWindowText(EDIT_oldname,"");
				SetWindowText(EDIT_oldsex,"");
				SetWindowText(EDIT_oldnation,"");
				SetWindowText(EDIT_oldface,"");
				SetWindowText(EDIT_oldbirth,"");
				SetWindowText(EDIT_oldtime,"");
				SetWindowText(EDIT_oldcollege,"");
				SetWindowText(EDIT_oldprofession,"");
				SetWindowText(EDIT_oldgrade,"");

				SetWindowText(EDIT_newname,"");
				SetWindowText(EDIT_newsex,"");
				SetWindowText(EDIT_newnation,"");
				SetWindowText(EDIT_newface,"");
				SetWindowText(EDIT_newbirth,"");
				SetWindowText(EDIT_newtime,"");
				SetWindowText(EDIT_newcollege,"");
				SetWindowText(EDIT_newprofession,"");
				SetWindowText(EDIT_newgrade,"");
				MessageBox(NULL,"删除成功！","警告",MB_OK);
				find_a_account_modification=0;
				break;
				}
				MessageBox(NULL,"非法操作！","警告",MB_OK);
				break;
			case BUTTON_a_account_modification_exit:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
		case WM_CLOSE:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
	}
    return FALSE;

}
//IDD_a_teacher_inquir窗口回调函数
	int teacher_ck; //标记是否初始化内容，1.是，0.否
	int teacher_now;
LRESULT CALLBACK	A_TEACHER_INQUIRE(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,sum,page,print;//sum.资料总数 page.总页数 now.当前页数 print.当前页资料总数
	teacher_List page_head;

	char char_page[30],item[10];
	HWND EDIT_id1,EDIT_id2,EDIT_id3,EDIT_id4,EDIT_id5,EDIT_id6;
	HWND EDIT_name1,EDIT_name2,EDIT_name3,EDIT_name4,EDIT_name5,EDIT_name6;
	HWND EDIT_sex1,EDIT_sex2,EDIT_sex3,EDIT_sex4,EDIT_sex5,EDIT_sex6;
	HWND EDIT_face1,EDIT_face2,EDIT_face3,EDIT_face4,EDIT_face5,EDIT_face6;
	HWND EDIT_college1,EDIT_college2,EDIT_college3,EDIT_college4,EDIT_college5,EDIT_college6;
	HWND EDIT_profession1,EDIT_profession2,EDIT_profession3,EDIT_profession4,EDIT_profession5,EDIT_profession6;
	HWND EDIT_grade1,EDIT_grade2,EDIT_grade3,EDIT_grade4,EDIT_grade5,EDIT_grade6;
	HWND EDIT_page;
	teacher_head=(teacher_List)malloc(sizeof(teacher_Lnode));
	teacher_load(teacher_head);
	sum=teacher_head->next->num;
	page=sum/6;
	if(sum%6!=0)
		page++;
	EDIT_id1=GetDlgItem(hDlg,EDIT_a_teacher_inquire_id1);
	EDIT_id2=GetDlgItem(hDlg,EDIT_a_teacher_inquire_id2);
	EDIT_id3=GetDlgItem(hDlg,EDIT_a_teacher_inquire_id3);
	EDIT_id4=GetDlgItem(hDlg,EDIT_a_teacher_inquire_id4);
	EDIT_id5=GetDlgItem(hDlg,EDIT_a_teacher_inquire_id5);
	EDIT_id6=GetDlgItem(hDlg,EDIT_a_teacher_inquire_id6);
	EDIT_name1=GetDlgItem(hDlg,EDIT_a_teacher_inquire_name1);
	EDIT_name2=GetDlgItem(hDlg,EDIT_a_teacher_inquire_name2);
	EDIT_name3=GetDlgItem(hDlg,EDIT_a_teacher_inquire_name3);
	EDIT_name4=GetDlgItem(hDlg,EDIT_a_teacher_inquire_name4);
	EDIT_name5=GetDlgItem(hDlg,EDIT_a_teacher_inquire_name5);
	EDIT_name6=GetDlgItem(hDlg,EDIT_a_teacher_inquire_name6);
	EDIT_sex1=GetDlgItem(hDlg,EDIT_a_teacher_inquire_sex1);
	EDIT_sex2=GetDlgItem(hDlg,EDIT_a_teacher_inquire_sex2);
	EDIT_sex3=GetDlgItem(hDlg,EDIT_a_teacher_inquire_sex3);
	EDIT_sex4=GetDlgItem(hDlg,EDIT_a_teacher_inquire_sex4);
	EDIT_sex5=GetDlgItem(hDlg,EDIT_a_teacher_inquire_sex5);
	EDIT_sex6=GetDlgItem(hDlg,EDIT_a_teacher_inquire_sex6);
	EDIT_face1=GetDlgItem(hDlg,EDIT_a_teacher_inquire_face1);
	EDIT_face2=GetDlgItem(hDlg,EDIT_a_teacher_inquire_face2);
	EDIT_face3=GetDlgItem(hDlg,EDIT_a_teacher_inquire_face3);
	EDIT_face4=GetDlgItem(hDlg,EDIT_a_teacher_inquire_face4);
	EDIT_face5=GetDlgItem(hDlg,EDIT_a_teacher_inquire_face5);
	EDIT_face6=GetDlgItem(hDlg,EDIT_a_teacher_inquire_face6);
	EDIT_college1=GetDlgItem(hDlg,EDIT_a_teacher_inquire_college1);
	EDIT_college2=GetDlgItem(hDlg,EDIT_a_teacher_inquire_college2);
	EDIT_college3=GetDlgItem(hDlg,EDIT_a_teacher_inquire_college3);
	EDIT_college4=GetDlgItem(hDlg,EDIT_a_teacher_inquire_college4);
	EDIT_college5=GetDlgItem(hDlg,EDIT_a_teacher_inquire_college5);
	EDIT_college6=GetDlgItem(hDlg,EDIT_a_teacher_inquire_college6);
	EDIT_profession1=GetDlgItem(hDlg,EDIT_a_teacher_inquire_profession1);
	EDIT_profession2=GetDlgItem(hDlg,EDIT_a_teacher_inquire_profession2);
	EDIT_profession3=GetDlgItem(hDlg,EDIT_a_teacher_inquire_profession3);
	EDIT_profession4=GetDlgItem(hDlg,EDIT_a_teacher_inquire_profession4);
	EDIT_profession5=GetDlgItem(hDlg,EDIT_a_teacher_inquire_profession5);
	EDIT_profession6=GetDlgItem(hDlg,EDIT_a_teacher_inquire_profession6);
	EDIT_grade1=GetDlgItem(hDlg,EDIT_a_teacher_inquire_grade1);
	EDIT_grade2=GetDlgItem(hDlg,EDIT_a_teacher_inquire_grade2);
	EDIT_grade3=GetDlgItem(hDlg,EDIT_a_teacher_inquire_grade3);
	EDIT_grade4=GetDlgItem(hDlg,EDIT_a_teacher_inquire_grade4);
	EDIT_grade5=GetDlgItem(hDlg,EDIT_a_teacher_inquire_grade5);
	EDIT_grade6=GetDlgItem(hDlg,EDIT_a_teacher_inquire_grade6);
	EDIT_page=GetDlgItem(hDlg,EDIT_a_teacher_inquire_page);
	
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case BUTTON_a_teacher_inquire_top:
				teacher_ck=1;
				teacher_now=1;
				if(sum>=6)
					print=6;//若总资料数不小于6，则第一页显示6条数据
				if(sum<6)
					print=sum;//若资料总数小于6，则第一页显示全部sum条数据
				page_head=teacher_head->next->next;//指向第一页第一条记录
				if(print>=1)
				{
					SetWindowText(EDIT_id1,page_head->id);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_sex1,page_head->sex);
					SetWindowText(EDIT_face1,page_head->face);
					SetWindowText(EDIT_college1,page_head->college);
					SetWindowText(EDIT_profession1,page_head->profession);
					SetWindowText(EDIT_grade1,page_head->grade);
					page_head=page_head->next;
				}
				if(print>=2)
				{
					SetWindowText(EDIT_id2,page_head->id);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_sex2,page_head->sex);
					SetWindowText(EDIT_face2,page_head->face);
					SetWindowText(EDIT_college2,page_head->college);
					SetWindowText(EDIT_profession2,page_head->profession);
					SetWindowText(EDIT_grade2,page_head->grade);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					SetWindowText(EDIT_id3,page_head->id);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_sex3,page_head->sex);
					SetWindowText(EDIT_face3,page_head->face);
					SetWindowText(EDIT_college3,page_head->college);
					SetWindowText(EDIT_profession3,page_head->profession);
					SetWindowText(EDIT_grade3,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=4)
				{
					SetWindowText(EDIT_id4,page_head->id);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_sex4,page_head->sex);
					SetWindowText(EDIT_face4,page_head->face);
					SetWindowText(EDIT_college4,page_head->college);
					SetWindowText(EDIT_profession4,page_head->profession);
					SetWindowText(EDIT_grade4,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=5)
				{
					SetWindowText(EDIT_id5,page_head->id);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_sex5,page_head->sex);
					SetWindowText(EDIT_face5,page_head->face);
					SetWindowText(EDIT_college5,page_head->college);
					SetWindowText(EDIT_profession5,page_head->profession);
					SetWindowText(EDIT_grade5,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=6)
				{
					SetWindowText(EDIT_id6,page_head->id);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_sex6,page_head->sex);
					SetWindowText(EDIT_face6,page_head->face);
					SetWindowText(EDIT_college6,page_head->college);
					SetWindowText(EDIT_profession6,page_head->profession);
					SetWindowText(EDIT_grade6,page_head->grade);

					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				itoa(teacher_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"页，共");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				break;
			case BUTTON_a_teacher_inquire_prior:
				if(teacher_ck!=1)
				{
					MessageBox(NULL,"请点击“返回顶部”显示第一页学院信息！","提示",MB_OK);
					break;
				}
				page_head=teacher_head->next->next;
				if(teacher_now-1<=0)
				{
					MessageBox(NULL,"已经到第一页！","提示",MB_OK);
					return FALSE;
				}
				else
					teacher_now--;
				for(i=0;i<(teacher_now-1)*6;i++)//将page_head移到当前页的第一项
					page_head=page_head->next;
				
				if(teacher_now==page)//如果在最后一页，则计算最后一页记录数量
					print=sum-(page-1)*6;
				else//否则，记录总数为6
					print=6;
				//清空编辑框内容
					SetWindowText(EDIT_id1,"");
					SetWindowText(EDIT_id2,"");
					SetWindowText(EDIT_id3,"");
					SetWindowText(EDIT_id4,"");
					SetWindowText(EDIT_id5,"");
					SetWindowText(EDIT_id6,"");
					SetWindowText(EDIT_name1,"");
					SetWindowText(EDIT_name2,"");
					SetWindowText(EDIT_name3,"");
					SetWindowText(EDIT_name4,"");
					SetWindowText(EDIT_name5,"");
					SetWindowText(EDIT_name6,"");
					SetWindowText(EDIT_sex1,"");
					SetWindowText(EDIT_sex2,"");
					SetWindowText(EDIT_sex3,"");
					SetWindowText(EDIT_sex4,"");
					SetWindowText(EDIT_sex5,"");
					SetWindowText(EDIT_sex6,"");
					SetWindowText(EDIT_face1,"");
					SetWindowText(EDIT_face2,"");
					SetWindowText(EDIT_face3,"");
					SetWindowText(EDIT_face4,"");
					SetWindowText(EDIT_face5,"");
					SetWindowText(EDIT_face6,"");
					SetWindowText(EDIT_college1,"");
					SetWindowText(EDIT_college2,"");
					SetWindowText(EDIT_college3,"");
					SetWindowText(EDIT_college4,"");
					SetWindowText(EDIT_college5,"");
					SetWindowText(EDIT_college6,"");
					SetWindowText(EDIT_profession1,"");
					SetWindowText(EDIT_profession2,"");
					SetWindowText(EDIT_profession3,"");
					SetWindowText(EDIT_profession4,"");
					SetWindowText(EDIT_profession5,"");
					SetWindowText(EDIT_profession6,"");
					SetWindowText(EDIT_grade1,"");
					SetWindowText(EDIT_grade2,"");
					SetWindowText(EDIT_grade3,"");
					SetWindowText(EDIT_grade4,"");
					SetWindowText(EDIT_grade5,"");
					SetWindowText(EDIT_grade6,"");
				if(print>=1)
				{
					SetWindowText(EDIT_id1,page_head->id);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_sex1,page_head->sex);
					SetWindowText(EDIT_face1,page_head->face);
					SetWindowText(EDIT_college1,page_head->college);
					SetWindowText(EDIT_profession1,page_head->profession);
					SetWindowText(EDIT_grade1,page_head->grade);
					page_head=page_head->next;
				}
				if(print>=2)
				{
					SetWindowText(EDIT_id2,page_head->id);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_sex2,page_head->sex);
					SetWindowText(EDIT_face2,page_head->face);
					SetWindowText(EDIT_college2,page_head->college);
					SetWindowText(EDIT_profession2,page_head->profession);
					SetWindowText(EDIT_grade2,page_head->grade);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					SetWindowText(EDIT_id3,page_head->id);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_sex3,page_head->sex);
					SetWindowText(EDIT_face3,page_head->face);
					SetWindowText(EDIT_college3,page_head->college);
					SetWindowText(EDIT_profession3,page_head->profession);
					SetWindowText(EDIT_grade3,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=4)
				{
					SetWindowText(EDIT_id4,page_head->id);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_sex4,page_head->sex);
					SetWindowText(EDIT_face4,page_head->face);
					SetWindowText(EDIT_college4,page_head->college);
					SetWindowText(EDIT_profession4,page_head->profession);
					SetWindowText(EDIT_grade4,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=5)
				{
					SetWindowText(EDIT_id5,page_head->id);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_sex5,page_head->sex);
					SetWindowText(EDIT_face5,page_head->face);
					SetWindowText(EDIT_college5,page_head->college);
					SetWindowText(EDIT_profession5,page_head->profession);
					SetWindowText(EDIT_grade5,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=6)
				{
					SetWindowText(EDIT_id6,page_head->id);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_sex6,page_head->sex);
					SetWindowText(EDIT_face6,page_head->face);
					SetWindowText(EDIT_college6,page_head->college);
					SetWindowText(EDIT_profession6,page_head->profession);
					SetWindowText(EDIT_grade6,page_head->grade);

					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				itoa(teacher_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"页，共");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_teacher_inquire_next:
				if(teacher_ck!=1)
				{
					MessageBox(NULL,"请点击“返回顶部”显示第一页教师信息！","提示",MB_OK);
					break;
				}
				page_head=teacher_head->next->next;//移到记录第一页第一条记录
				if(teacher_now+1>page)//如果当前页+1等于总页数，弹出警告
				{
					MessageBox(NULL,"已经到最后一页！","提示",MB_OK);
					return FALSE;
				}
				else//否则，跳转页数
				{
					teacher_now++;
				}
				for(i=0;i<(teacher_now-1)*6;i++)//将page_head移到当前页的第一项
					page_head=page_head->next;
				
				if(teacher_now==page)//如果在最后一页，则计算最后一页记录数量
					print=sum-(page-1)*6;
				else//否则，记录总数为6
					print=6;
				//清空编辑框内容
					SetWindowText(EDIT_id1,"");
					SetWindowText(EDIT_id2,"");
					SetWindowText(EDIT_id3,"");
					SetWindowText(EDIT_id4,"");
					SetWindowText(EDIT_id5,"");
					SetWindowText(EDIT_id6,"");
					SetWindowText(EDIT_name1,"");
					SetWindowText(EDIT_name2,"");
					SetWindowText(EDIT_name3,"");
					SetWindowText(EDIT_name4,"");
					SetWindowText(EDIT_name5,"");
					SetWindowText(EDIT_name6,"");
					SetWindowText(EDIT_sex1,"");
					SetWindowText(EDIT_sex2,"");
					SetWindowText(EDIT_sex3,"");
					SetWindowText(EDIT_sex4,"");
					SetWindowText(EDIT_sex5,"");
					SetWindowText(EDIT_sex6,"");
					SetWindowText(EDIT_face1,"");
					SetWindowText(EDIT_face2,"");
					SetWindowText(EDIT_face3,"");
					SetWindowText(EDIT_face4,"");
					SetWindowText(EDIT_face5,"");
					SetWindowText(EDIT_face6,"");
					SetWindowText(EDIT_college1,"");
					SetWindowText(EDIT_college2,"");
					SetWindowText(EDIT_college3,"");
					SetWindowText(EDIT_college4,"");
					SetWindowText(EDIT_college5,"");
					SetWindowText(EDIT_college6,"");
					SetWindowText(EDIT_profession1,"");
					SetWindowText(EDIT_profession2,"");
					SetWindowText(EDIT_profession3,"");
					SetWindowText(EDIT_profession4,"");
					SetWindowText(EDIT_profession5,"");
					SetWindowText(EDIT_profession6,"");
					SetWindowText(EDIT_grade1,"");
					SetWindowText(EDIT_grade2,"");
					SetWindowText(EDIT_grade3,"");
					SetWindowText(EDIT_grade4,"");
					SetWindowText(EDIT_grade5,"");
					SetWindowText(EDIT_grade6,"");
				if(print>=1)
				{
					SetWindowText(EDIT_id1,page_head->id);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_sex1,page_head->sex);
					SetWindowText(EDIT_face1,page_head->face);
					SetWindowText(EDIT_college1,page_head->college);
					SetWindowText(EDIT_profession1,page_head->profession);
					SetWindowText(EDIT_grade1,page_head->grade);
					page_head=page_head->next;
				}
				if(print>=2)
				{
					SetWindowText(EDIT_id2,page_head->id);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_sex2,page_head->sex);
					SetWindowText(EDIT_face2,page_head->face);
					SetWindowText(EDIT_college2,page_head->college);
					SetWindowText(EDIT_profession2,page_head->profession);
					SetWindowText(EDIT_grade2,page_head->grade);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					SetWindowText(EDIT_id3,page_head->id);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_sex3,page_head->sex);
					SetWindowText(EDIT_face3,page_head->face);
					SetWindowText(EDIT_college3,page_head->college);
					SetWindowText(EDIT_profession3,page_head->profession);
					SetWindowText(EDIT_grade3,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=4)
				{
					SetWindowText(EDIT_id4,page_head->id);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_sex4,page_head->sex);
					SetWindowText(EDIT_face4,page_head->face);
					SetWindowText(EDIT_college4,page_head->college);
					SetWindowText(EDIT_profession4,page_head->profession);
					SetWindowText(EDIT_grade4,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=5)
				{
					SetWindowText(EDIT_id5,page_head->id);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_sex5,page_head->sex);
					SetWindowText(EDIT_face5,page_head->face);
					SetWindowText(EDIT_college5,page_head->college);
					SetWindowText(EDIT_profession5,page_head->profession);
					SetWindowText(EDIT_grade5,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=6)
				{
					SetWindowText(EDIT_id6,page_head->id);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_sex6,page_head->sex);
					SetWindowText(EDIT_face6,page_head->face);
					SetWindowText(EDIT_college6,page_head->college);
					SetWindowText(EDIT_profession6,page_head->profession);
					SetWindowText(EDIT_grade6,page_head->grade);

					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				
				itoa(teacher_now,item,10);

				strcat(char_page,item);
				
				strcat(char_page,"页，共");
				itoa(page,item,10);//转换整形为字符型
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_teacher_inquire_exit:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
				break;
			}
			break;
		case WM_CLOSE:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
	}
    return FALSE;

}
//IDD_a_teacher_modification窗口回调函数

	int find_a_teacher_modification;//0.找到 1.未找到
	int state_a_teacher_modification;//修改状态提示
	int add_teacher;//增添信息合法，1.合法,other.不合法
	char teacher_item[10];
	teacher_List teacher_modification_p,teacher_new_info,teacher_old_info;
	teacher_List teacher_delete;
LRESULT CALLBACK	A_TEACHER_MODIFICATION(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	college_List college_p;
	HWND EDIT_oldid,EDIT_oldid1,EDIT_newid;
	HWND EDIT_oldname,EDIT_newname;
	HWND EDIT_oldsex,EDIT_newsex;
	HWND EDIT_oldnation,EDIT_newnation;
	HWND EDIT_oldface,EDIT_newface;
	HWND EDIT_oldbirth,EDIT_newbirth;
	HWND EDIT_oldtime,EDIT_newtime;
	HWND EDIT_oldcollege,EDIT_newcollege;
	HWND EDIT_oldprofession,EDIT_newprofession;
	HWND EDIT_oldgrade,EDIT_newgrade;
	char new_id[100],new_name[100],new_sex[100],new_nation[100],new_face[100],new_birth[100],new_time[100],new_college[100],new_profession[100],new_grade[100];
	char year[10],month[5],day[5];
	char year1[10],month1[5];

	char message_a_teacher_modification[60];
	char *stop;//为strtol定义的终止字符指针
	int id;
	int i;
	teacher_head=(teacher_List)malloc(sizeof(teacher_Lnode));
	teacher_load(teacher_head);
	EDIT_oldid=GetDlgItem(hDlg,EDIT_a_teacher_modification_oldid);
	EDIT_oldid1=GetDlgItem(hDlg,EDIT_a_teacher_modification_oldid1);
	EDIT_oldname=GetDlgItem(hDlg,EDIT_a_teacher_modification_oldname);
	EDIT_oldsex=GetDlgItem(hDlg,EDIT_a_teacher_modification_oldsex);
	EDIT_oldnation=GetDlgItem(hDlg,EDIT_a_teacher_modification_oldnation);
	EDIT_oldface=GetDlgItem(hDlg,EDIT_a_teacher_modification_oldface);
	EDIT_oldbirth=GetDlgItem(hDlg,EDIT_a_teacher_modification_oldbirth);
	EDIT_oldtime=GetDlgItem(hDlg,EDIT_a_teacher_modification_oldtime);
	EDIT_oldcollege=GetDlgItem(hDlg,EDIT_a_teacher_modification_oldcollege);
	EDIT_oldprofession=GetDlgItem(hDlg,EDIT_a_teacher_modification_oldprofession);
	EDIT_oldgrade=GetDlgItem(hDlg,EDIT_a_teacher_modification_oldgrade);
	
	EDIT_newid=GetDlgItem(hDlg,EDIT_a_teacher_modification_newid);
	EDIT_newname=GetDlgItem(hDlg,EDIT_a_teacher_modification_newname);
	EDIT_newsex=GetDlgItem(hDlg,EDIT_a_teacher_modification_newsex);
	EDIT_newnation=GetDlgItem(hDlg,EDIT_a_teacher_modification_newnation);
	EDIT_newface=GetDlgItem(hDlg,EDIT_a_teacher_modification_newface);
	EDIT_newbirth=GetDlgItem(hDlg,EDIT_a_teacher_modification_newbirth);
	EDIT_newtime=GetDlgItem(hDlg,EDIT_a_teacher_modification_newtime);
	EDIT_newcollege=GetDlgItem(hDlg,EDIT_a_teacher_modification_newcollege);
	EDIT_newprofession=GetDlgItem(hDlg,EDIT_a_teacher_modification_newprofession);
	EDIT_newgrade=GetDlgItem(hDlg,EDIT_a_teacher_modification_newgrade);
	
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			//通过id定位教师
			case BUTTON_a_teacher_modification_location:
				find_a_teacher_modification=0;
				GetWindowText(EDIT_oldid,teacher_item,GetWindowTextLength(EDIT_oldid)+1);//获取oldid编辑框内容到item
				teacher_modification_p=teacher_head->next->next;
				while(teacher_modification_p)
				{
					if(strcmp(teacher_modification_p->id,teacher_item)==0)
					{
						teacher_old_info=(teacher_List)malloc(sizeof(teacher_Lnode));
						strcpy(teacher_old_info->id,teacher_modification_p->id);
						strcpy(teacher_old_info->name,teacher_modification_p->name);
						strcpy(teacher_old_info->sex,teacher_modification_p->sex);
						strcpy(teacher_old_info->nation,teacher_modification_p->nation);
						strcpy(teacher_old_info->face,teacher_modification_p->face);
						strcpy(teacher_old_info->birth,teacher_modification_p->birth);
						strcpy(teacher_old_info->time,teacher_modification_p->time);
						strcpy(teacher_old_info->college,teacher_modification_p->college);
						strcpy(teacher_old_info->profession,teacher_modification_p->profession);
						strcpy(teacher_old_info->grade,teacher_modification_p->grade);
						teacher_old_info->num=teacher_modification_p->num;
						find_a_teacher_modification=1;
						break;
					}
					else
						teacher_modification_p=teacher_modification_p->next;
				}
				if(find_a_teacher_modification!=1)
				{
					MessageBox(NULL,"输入有误！","ERROR!",MB_OK);
					break;
					return FALSE;
				}
				SetWindowText(EDIT_oldid1,teacher_old_info->id);
				SetWindowText(EDIT_oldname,teacher_old_info->name);
				SetWindowText(EDIT_oldsex,teacher_old_info->sex);
				SetWindowText(EDIT_oldnation,teacher_old_info->nation);
				SetWindowText(EDIT_oldface,teacher_old_info->face);
				SetWindowText(EDIT_oldbirth,teacher_old_info->birth);
				SetWindowText(EDIT_oldtime,teacher_old_info->time);
				SetWindowText(EDIT_oldcollege,teacher_old_info->college);
				SetWindowText(EDIT_oldprofession,teacher_old_info->profession);
				SetWindowText(EDIT_oldgrade,teacher_old_info->grade);

				SetWindowText(EDIT_newid,teacher_old_info->id);
				SetWindowText(EDIT_newname,teacher_old_info->name);
				SetWindowText(EDIT_newsex,teacher_old_info->sex);
				SetWindowText(EDIT_newnation,teacher_old_info->nation);
				SetWindowText(EDIT_newface,teacher_old_info->face);
				SetWindowText(EDIT_newbirth,teacher_old_info->birth);
				SetWindowText(EDIT_newtime,teacher_old_info->time);
				SetWindowText(EDIT_newcollege,teacher_old_info->college);
				SetWindowText(EDIT_newprofession,teacher_old_info->profession);
				SetWindowText(EDIT_newgrade,teacher_old_info->grade);

				state_a_teacher_modification=1;//修改状态为修改
				MessageBox(NULL,"定位成功！请修改数据或删除数据。修改完毕按“确认修改”保存！","ERROR!",MB_OK);
				break;
			//增添教师
			case BUTTON_a_teacher_modification_add:
				MessageBox(NULL,"请在新数据信息框中输入新教师信息,初始密码为“teacher”","提示",MB_OK);
				find_a_teacher_modification=0;
				state_a_teacher_modification=2;//修改状态为增添教师

				SetWindowText(EDIT_oldid,"");
				SetWindowText(EDIT_oldid1,"");
				SetWindowText(EDIT_oldname,"");
				SetWindowText(EDIT_oldsex,"");
				SetWindowText(EDIT_oldnation,"");
				SetWindowText(EDIT_oldface,"");
				SetWindowText(EDIT_oldbirth,"");
				SetWindowText(EDIT_oldtime,"");
				SetWindowText(EDIT_oldcollege,"");
				SetWindowText(EDIT_oldprofession,"");
				SetWindowText(EDIT_oldgrade,"");

				SetWindowText(EDIT_newid,"账号字符数<20");
				SetWindowText(EDIT_newname,"姓名字数<10");
				SetWindowText(EDIT_newsex,"男or女");
				SetWindowText(EDIT_newnation,"xx族");
				SetWindowText(EDIT_newface,"群众");
				SetWindowText(EDIT_newbirth,"xxxx-xx-xx");
				SetWindowText(EDIT_newtime,"xxxx-xx");
				SetWindowText(EDIT_newcollege,"xxxxxxxxxxxxxx学院");
				SetWindowText(EDIT_newprofession,"");
				SetWindowText(EDIT_newgrade,"讲师");

				teacher_new_info=(teacher_List)malloc(sizeof(teacher_Lnode));
				teacher_new_info->num=teacher_head->next->num+1;
				itoa(teacher_new_info->num,teacher_item,10);
				strcpy(message_a_teacher_modification,"新教师编码为：");
				strcat(message_a_teacher_modification,teacher_item);
				SetWindowText(EDIT_oldid,message_a_teacher_modification);
				break;
			//确认修改
			case BUTTON_a_teacher_modification_affirm:
				GetWindowText(EDIT_newid,new_id,GetWindowTextLength(EDIT_newid)+1);//获取newid框内容到new_id
				GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//获取newnaeme框内容到new_name
				GetWindowText(EDIT_newsex,new_sex,GetWindowTextLength(EDIT_newsex)+1);//获取newsex框内容到new_sex
				GetWindowText(EDIT_newnation,new_nation,GetWindowTextLength(EDIT_newnation)+1);//获取newnation框内容到new_nation
				GetWindowText(EDIT_newface,new_face,GetWindowTextLength(EDIT_newface)+1);//获取newface框内容到new_face
				GetWindowText(EDIT_newbirth,new_birth,GetWindowTextLength(EDIT_newbirth)+1);//获取newbirth框内容到new_birth
				GetWindowText(EDIT_newtime,new_time,GetWindowTextLength(EDIT_newtime)+1);//获取newtime框内容到new_time
				GetWindowText(EDIT_newcollege,new_college,GetWindowTextLength(EDIT_newcollege)+1);//获取newcollege框内容到new_college
				GetWindowText(EDIT_newprofession,new_profession,GetWindowTextLength(EDIT_newprofession)+1);//获取newprofession框内容到new_profession
				GetWindowText(EDIT_newgrade,new_grade,GetWindowTextLength(EDIT_newgrade)+1);//获取newngrade框内容到new_grade
				if(state_a_teacher_modification==1)//确认修改现有专业信息
				{
				if(strcmp(new_id,teacher_old_info->id)!=0)
				{
					MessageBox(NULL,"不允许修改账号！","警告",MB_OK);
					strcpy(new_id,teacher_old_info->id);
					SetWindowText(EDIT_newid,teacher_old_info->id);
					return FALSE;
				}
				if(strlen(new_name)>28||strlen(new_name)<2)
				{
					MessageBox(NULL,"教师姓名输入有误！","警告",MB_OK);
					strcpy(new_name,teacher_old_info->name);
					SetWindowText(EDIT_newname,teacher_old_info->name);
					return FALSE;
				}
				if((strcmp(new_sex,"男")!=0)&&strcmp(new_sex,"女")!=0)
				{
					MessageBox(NULL,"教师性别输入有误！","警告",MB_OK);
					strcpy(new_sex,teacher_old_info->sex);
					SetWindowText(EDIT_newsex,teacher_old_info->sex);
					return FALSE;
				}
				if(strlen(new_nation)>12||strlen(new_nation)<2)
				{
					MessageBox(NULL,"教师民族输入有误！","警告",MB_OK);
					strcpy(new_nation,teacher_old_info->nation);
					SetWindowText(EDIT_newnation,teacher_old_info->nation);
					return FALSE;
				}
				if(strlen(new_face)>12||strlen(new_face)<2)
				{
					MessageBox(NULL,"教师民族输入有误！","警告",MB_OK);
					strcpy(new_face,teacher_old_info->face);
					SetWindowText(EDIT_newface,teacher_old_info->face);
					return FALSE;
				}
				sscanf(new_birth,"%4s%*1s%2s%*1s%2s%*s",&year,&month,&day);
				if(strcmp(year,"1960")<0||strcmp(year,"2017")>0)
					{
					MessageBox(NULL,"教师出生年份输入有误！","警告",MB_OK);
					strcpy(new_birth,teacher_old_info->birth);
					SetWindowText(EDIT_newbirth,teacher_old_info->birth);
					return FALSE;
				}
				if(strcmp(month,"01")<0||strcmp(month,"12")>0)
					{
					MessageBox(NULL,"教师出生月份输入有误！","警告",MB_OK);
					strcpy(new_birth,teacher_old_info->birth);
					SetWindowText(EDIT_newbirth,teacher_old_info->birth);
					return FALSE;
				}
				if(strcmp(day,"01")<0||strcmp(day,"31")>0)
					{
					MessageBox(NULL,"教师出生日期输入有误！","警告",MB_OK);
					strcpy(new_birth,teacher_old_info->birth);
					SetWindowText(EDIT_newbirth,teacher_old_info->birth);
					return FALSE;
				}
				sscanf(new_time,"%4s%*1s%2s%*1s%*s",&year,&month);
				if(strcmp(year,"1960")<0||strcmp(year,"2017")>0)
					{
					MessageBox(NULL,"教师入职年份输入有误！","警告",MB_OK);
					strcpy(new_time,teacher_old_info->time);
					SetWindowText(EDIT_newtime,teacher_old_info->time);
					return FALSE;
				}
				if(strcmp(month,"01")<0||strcmp(month,"12")>0)
					{
					MessageBox(NULL,"教师入职月份输入有误！","警告",MB_OK);
					strcpy(new_time,teacher_old_info->time);
					SetWindowText(EDIT_newtime,teacher_old_info->time);
					return FALSE;
				}

				if(strcmp(new_college,teacher_old_info->college)!=0)
				{
					MessageBox(NULL,"新的所属学院信息不会存储！\n若想修改学院请删除数据后重新规定学院！","警告",MB_OK);
					return FALSE;
				}
				if(strlen(new_profession)>30||strlen(new_profession)<2)
				{
					MessageBox(NULL,"教师所属部门输入有误！","警告",MB_OK);
					strcpy(new_profession,teacher_old_info->profession);
					SetWindowText(EDIT_newprofession,teacher_old_info->profession);
					return FALSE;
				}

				if(strlen(new_grade)>20||strlen(new_grade)<2)
				{
					MessageBox(NULL,"教师所属部门输入有误！","警告",MB_OK);
					strcpy(new_grade,teacher_old_info->grade);
					SetWindowText(EDIT_newgrade,teacher_old_info->grade);
					return FALSE;
				}
				teacher_modification_p=teacher_head->next;
				for(i=0;i<teacher_old_info->num;i++)
					teacher_modification_p=teacher_modification_p->next;
			    strcpy(teacher_modification_p->id,new_id);
				strcpy(teacher_modification_p->name,new_name);
				strcpy(teacher_modification_p->sex,new_sex);
				strcpy(teacher_modification_p->nation,new_nation);
				strcpy(teacher_modification_p->face,new_face);
				strcpy(teacher_modification_p->birth,new_birth);
				strcpy(teacher_modification_p->time,new_time);
				strcpy(teacher_modification_p->college,new_college);
				strcpy(teacher_modification_p->profession,new_profession);
				strcpy(teacher_modification_p->grade,new_grade);
				teacher_save(teacher_head);
				teacher_load(teacher_head);
				SetWindowText(EDIT_oldname,new_name);
				MessageBox(NULL,"修改成功！","警告",MB_OK);
				}

				
				if(state_a_teacher_modification==2)//确认增添学院信息
				{
					GetWindowText(EDIT_newid,new_id,GetWindowTextLength(EDIT_newid)+1);//获取newid框内容到new_id
				GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//获取newnaeme框内容到new_name
				GetWindowText(EDIT_newsex,new_sex,GetWindowTextLength(EDIT_newsex)+1);//获取newsex框内容到new_sex
				GetWindowText(EDIT_newnation,new_nation,GetWindowTextLength(EDIT_newnation)+1);//获取newnation框内容到new_nation
				GetWindowText(EDIT_newface,new_face,GetWindowTextLength(EDIT_newface)+1);//获取newface框内容到new_face
				GetWindowText(EDIT_newbirth,new_birth,GetWindowTextLength(EDIT_newbirth)+1);//获取newbirth框内容到new_birth
				GetWindowText(EDIT_newtime,new_time,GetWindowTextLength(EDIT_newtime)+1);//获取newtime框内容到new_time
				GetWindowText(EDIT_newcollege,new_college,GetWindowTextLength(EDIT_newcollege)+1);//获取newcollege框内容到new_college
				GetWindowText(EDIT_newprofession,new_profession,GetWindowTextLength(EDIT_newprofession)+1);//获取newprofession框内容到new_profession
				GetWindowText(EDIT_newgrade,new_grade,GetWindowTextLength(EDIT_newgrade)+1);//获取newngrade框内容到new_grade
				if(strlen(new_id)>28||strlen(new_id)<2)
				{
					MessageBox(NULL,"教师账号输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newid,"");
					break;
					return FALSE;
				}	
				if(strlen(new_name)>28||strlen(new_name)<2)
				{
					MessageBox(NULL,"教师姓名输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newname,"");
					break;
					return FALSE;
				}
				if((strcmp(new_sex,"男")!=0)&&strcmp(new_sex,"女")!=0)
				{
					MessageBox(NULL,"教师性别输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newsex,"");
					break;
					return FALSE;
				}
				if(strlen(new_nation)>12||strlen(new_nation)<2)
				{
					MessageBox(NULL,"教师民族输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newnation,"");
					break;
					return FALSE;
				}
				if(strlen(new_face)>12||strlen(new_face)<2)
				{
					MessageBox(NULL,"教师政治面貌输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newface,"");
					break;
					return FALSE;
				}
				sscanf(new_birth,"%4s%*1s%2s%*1s%2s%*s",&year,&month,&day);
				if(strcmp(year,"1960")<0||strcmp(year,"2017")>0)
					{
					MessageBox(NULL,"教师出生年份输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newbirth,"");
					break;
					return FALSE;
				}
				if(strcmp(month,"01")<0||strcmp(month,"12")>0)
					{
					MessageBox(NULL,"教师出生月份输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newbirth,"");
					break;
					return FALSE;
				}
				if(strcmp(day,"01")<0||strcmp(day,"31")>0)
					{
					MessageBox(NULL,"教师出生日期输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newbirth,"");
					break;
					return FALSE;
				}
				sscanf(new_time,"%4s%*1s%2s%*s",&year1,&month1);
				if(strcmp(year1,"1960")<0||strcmp(year1,"2017")>0)
					{
					MessageBox(NULL,"教师入职年份输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newtime,"");
					break;
					return FALSE;
				}
				if(strcmp(month1,"01")<0||strcmp(month1,"12")>0)
					{
					MessageBox(NULL,"教师入职月份输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newtime,"");
					break;
					return FALSE;
				}

				if(strlen(new_profession)>30||strlen(new_profession)<2)
				{
					MessageBox(NULL,"教师所属部门输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newprofession,"");
					break;
					return FALSE;
				}
				if(strlen(new_grade)>30||strlen(new_grade)<2)
				{
					MessageBox(NULL,"教师职称输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newgrade,"");
					break;
					return FALSE;
				}
					strcpy(teacher_new_info->password,"admin");
					strcpy(teacher_new_info->identity,"教师");
					strcpy(teacher_new_info->id,new_id);
					strcpy(teacher_new_info->name,new_name);
					strcpy(teacher_new_info->sex,new_sex);
					strcpy(teacher_new_info->nation,new_nation);
					strcpy(teacher_new_info->face,new_face);
					strcpy(teacher_new_info->birth,new_birth);
					strcpy(teacher_new_info->time,new_time);
					strcpy(teacher_new_info->college,new_college);
					strcpy(teacher_new_info->profession,new_profession);
					strcpy(teacher_new_info->grade,new_grade);
					teacher_modification_p=teacher_head->next;
					college_load(college_head);
					college_p=college_head->next;
					while(college_p)
					{
						if(strcmp(college_p->name,new_college)==0)
						{
							strcpy(teacher_new_info->college,new_college);
							teacher_new_info->collegeid=college_p->id;
							add_teacher=1;
							break;
						}
						college_p=college_p->next;
					}
					if(add_teacher!=1)
					{
						MessageBox(NULL,"学院不存在！","警告",MB_OK);
						break;
						return FALSE;
					}
					if(strlen(new_name)==0||strlen(new_name)>20)
					{
						MessageBox(NULL,"专业名称非法！","警告",MB_OK);
						add_teacher=0;
						break;
						return FALSE;
					}
					for(i=0;i<teacher_head->next->num;i++)
					{
						teacher_modification_p=teacher_modification_p->next;
						if(strcmp(teacher_new_info->id,teacher_modification_p->id)==0)
						{
							MessageBox(NULL,"账号重复！","警告",MB_OK);
							add_teacher=0;
							break;
							return FALSE;
						}
					}
					teacher_modification_p->next=teacher_new_info;
					teacher_new_info->prior=teacher_modification_p;
					teacher_new_info->next=NULL;
					teacher_head->next->num++;
					teacher_save(teacher_head);
					teacher_load(teacher_head);

				SetWindowText(EDIT_oldid1,teacher_new_info->id);
				SetWindowText(EDIT_oldname,teacher_new_info->name);
				SetWindowText(EDIT_oldsex,teacher_new_info->sex);
				SetWindowText(EDIT_oldnation,teacher_new_info->nation);
				SetWindowText(EDIT_oldface,teacher_new_info->face);
				SetWindowText(EDIT_oldbirth,teacher_new_info->birth);
				SetWindowText(EDIT_oldtime,teacher_new_info->time);
				SetWindowText(EDIT_oldcollege,teacher_new_info->college);
				SetWindowText(EDIT_oldprofession,teacher_new_info->profession);
				SetWindowText(EDIT_oldgrade,teacher_new_info->grade);

				SetWindowText(EDIT_newname,teacher_new_info->name);
				SetWindowText(EDIT_newsex,teacher_new_info->sex);
				SetWindowText(EDIT_newnation,teacher_new_info->nation);
				SetWindowText(EDIT_newface,teacher_new_info->face);
				SetWindowText(EDIT_newbirth,teacher_new_info->birth);
				SetWindowText(EDIT_newtime,teacher_new_info->time);
				SetWindowText(EDIT_newcollege,teacher_new_info->college);
				SetWindowText(EDIT_newprofession,teacher_new_info->profession);
				SetWindowText(EDIT_newgrade,teacher_new_info->grade);

					MessageBox(NULL,"修改成功！","提示",MB_OK);
					teacher_old_info=(teacher_List)malloc(sizeof(teacher_Lnode));
					strcpy(teacher_old_info->name,teacher_new_info->name);
					strcpy(teacher_old_info->id,teacher_new_info->id);
					teacher_old_info->num=teacher_new_info->num;
					find_a_teacher_modification=1;
				}
				break;
			//删除教师
			case BUTTON_a_teacher_modification_delete:
				if(find_a_teacher_modification==1)
				{
					if(strcmp(teacher_old_info->id,account_mine->id)==0)
					{
						MessageBox(NULL,"不允许删除已登录账号！","警告",MB_OK|MB_ICONEXCLAMATION);
						return FALSE;
					}
				strcpy(message_a_teacher_modification,"确认删除教师：“");
				strcat(message_a_teacher_modification,teacher_old_info->name);
				strcat(message_a_teacher_modification,"”吗？");
				if(MessageBox(NULL,message_a_teacher_modification,"警告",MB_YESNO|MB_ICONEXCLAMATION)!=6)
				{
					return FALSE;
				}
				teacher_modification_p=teacher_head->next;
				for(i=0;i<teacher_old_info->num;i++)
					teacher_modification_p=teacher_modification_p->next;
				teacher_modification_p->num=-1;
				strcat(teacher_modification_p->name,"（已删除）");
				teacher_modification_p=teacher_head->next->next;
				teacher_save(teacher_head);
				teacher_load(teacher_head);
				SetWindowText(EDIT_oldid1,"");
				SetWindowText(EDIT_oldname,"");
				SetWindowText(EDIT_oldsex,"");
				SetWindowText(EDIT_oldnation,"");
				SetWindowText(EDIT_oldface,"");
				SetWindowText(EDIT_oldbirth,"");
				SetWindowText(EDIT_oldtime,"");
				SetWindowText(EDIT_oldcollege,"");
				SetWindowText(EDIT_oldprofession,"");
				SetWindowText(EDIT_oldgrade,"");

				SetWindowText(EDIT_newname,"");
				SetWindowText(EDIT_newsex,"");
				SetWindowText(EDIT_newnation,"");
				SetWindowText(EDIT_newface,"");
				SetWindowText(EDIT_newbirth,"");
				SetWindowText(EDIT_newtime,"");
				SetWindowText(EDIT_newcollege,"");
				SetWindowText(EDIT_newprofession,"");
				SetWindowText(EDIT_newgrade,"");
				MessageBox(NULL,"删除成功！","警告",MB_OK);
				find_a_teacher_modification=0;
				break;
				}
				MessageBox(NULL,"非法操作！","警告",MB_OK);
				break;
			case BUTTON_a_teacher_modification_exit:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
		case WM_CLOSE:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
	}
    return FALSE;

}
//IDD_a_student_inquir窗口回调函数
	int student_ck; //标记是否初始化内容，1.是，0.否
	int student_now;
LRESULT CALLBACK	A_STUDENT_INQUIRE(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,sum,page,print;//sum.资料总数 page.总页数 now.当前页数 print.当前页资料总数
	student_List page_head;

	char char_page[30],item[10];
	HWND EDIT_id1,EDIT_id2,EDIT_id3,EDIT_id4,EDIT_id5,EDIT_id6;
	HWND EDIT_name1,EDIT_name2,EDIT_name3,EDIT_name4,EDIT_name5,EDIT_name6;
	HWND EDIT_sex1,EDIT_sex2,EDIT_sex3,EDIT_sex4,EDIT_sex5,EDIT_sex6;
	HWND EDIT_face1,EDIT_face2,EDIT_face3,EDIT_face4,EDIT_face5,EDIT_face6;
	HWND EDIT_college1,EDIT_college2,EDIT_college3,EDIT_college4,EDIT_college5,EDIT_college6;
	HWND EDIT_profession1,EDIT_profession2,EDIT_profession3,EDIT_profession4,EDIT_profession5,EDIT_profession6;
	HWND EDIT_grade1,EDIT_grade2,EDIT_grade3,EDIT_grade4,EDIT_grade5,EDIT_grade6;
	HWND EDIT_page;
	student_head=(student_List)malloc(sizeof(student_Lnode));
	student_load(student_head);
	sum=student_head->next->num;
	page=sum/6;
	if(sum%6!=0)
		page++;
	EDIT_id1=GetDlgItem(hDlg,EDIT_a_student_inquire_id1);
	EDIT_id2=GetDlgItem(hDlg,EDIT_a_student_inquire_id2);
	EDIT_id3=GetDlgItem(hDlg,EDIT_a_student_inquire_id3);
	EDIT_id4=GetDlgItem(hDlg,EDIT_a_student_inquire_id4);
	EDIT_id5=GetDlgItem(hDlg,EDIT_a_student_inquire_id5);
	EDIT_id6=GetDlgItem(hDlg,EDIT_a_student_inquire_id6);
	EDIT_name1=GetDlgItem(hDlg,EDIT_a_student_inquire_name1);
	EDIT_name2=GetDlgItem(hDlg,EDIT_a_student_inquire_name2);
	EDIT_name3=GetDlgItem(hDlg,EDIT_a_student_inquire_name3);
	EDIT_name4=GetDlgItem(hDlg,EDIT_a_student_inquire_name4);
	EDIT_name5=GetDlgItem(hDlg,EDIT_a_student_inquire_name5);
	EDIT_name6=GetDlgItem(hDlg,EDIT_a_student_inquire_name6);
	EDIT_sex1=GetDlgItem(hDlg,EDIT_a_student_inquire_sex1);
	EDIT_sex2=GetDlgItem(hDlg,EDIT_a_student_inquire_sex2);
	EDIT_sex3=GetDlgItem(hDlg,EDIT_a_student_inquire_sex3);
	EDIT_sex4=GetDlgItem(hDlg,EDIT_a_student_inquire_sex4);
	EDIT_sex5=GetDlgItem(hDlg,EDIT_a_student_inquire_sex5);
	EDIT_sex6=GetDlgItem(hDlg,EDIT_a_student_inquire_sex6);
	EDIT_face1=GetDlgItem(hDlg,EDIT_a_student_inquire_face1);
	EDIT_face2=GetDlgItem(hDlg,EDIT_a_student_inquire_face2);
	EDIT_face3=GetDlgItem(hDlg,EDIT_a_student_inquire_face3);
	EDIT_face4=GetDlgItem(hDlg,EDIT_a_student_inquire_face4);
	EDIT_face5=GetDlgItem(hDlg,EDIT_a_student_inquire_face5);
	EDIT_face6=GetDlgItem(hDlg,EDIT_a_student_inquire_face6);
	EDIT_college1=GetDlgItem(hDlg,EDIT_a_student_inquire_college1);
	EDIT_college2=GetDlgItem(hDlg,EDIT_a_student_inquire_college2);
	EDIT_college3=GetDlgItem(hDlg,EDIT_a_student_inquire_college3);
	EDIT_college4=GetDlgItem(hDlg,EDIT_a_student_inquire_college4);
	EDIT_college5=GetDlgItem(hDlg,EDIT_a_student_inquire_college5);
	EDIT_college6=GetDlgItem(hDlg,EDIT_a_student_inquire_college6);
	EDIT_profession1=GetDlgItem(hDlg,EDIT_a_student_inquire_profession1);
	EDIT_profession2=GetDlgItem(hDlg,EDIT_a_student_inquire_profession2);
	EDIT_profession3=GetDlgItem(hDlg,EDIT_a_student_inquire_profession3);
	EDIT_profession4=GetDlgItem(hDlg,EDIT_a_student_inquire_profession4);
	EDIT_profession5=GetDlgItem(hDlg,EDIT_a_student_inquire_profession5);
	EDIT_profession6=GetDlgItem(hDlg,EDIT_a_student_inquire_profession6);
	EDIT_grade1=GetDlgItem(hDlg,EDIT_a_student_inquire_grade1);
	EDIT_grade2=GetDlgItem(hDlg,EDIT_a_student_inquire_grade2);
	EDIT_grade3=GetDlgItem(hDlg,EDIT_a_student_inquire_grade3);
	EDIT_grade4=GetDlgItem(hDlg,EDIT_a_student_inquire_grade4);
	EDIT_grade5=GetDlgItem(hDlg,EDIT_a_student_inquire_grade5);
	EDIT_grade6=GetDlgItem(hDlg,EDIT_a_student_inquire_grade6);
	EDIT_page=GetDlgItem(hDlg,EDIT_a_student_inquire_page);
	
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case BUTTON_a_student_inquire_top:
				student_ck=1;
				student_now=1;
				if(sum>=6)
					print=6;//若总资料数不小于6，则第一页显示6条数据
				if(sum<6)
					print=sum;//若资料总数小于6，则第一页显示全部sum条数据
				page_head=student_head->next->next;//指向第一页第一条记录
				if(print>=1)
				{
					SetWindowText(EDIT_id1,page_head->id);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_sex1,page_head->sex);
					SetWindowText(EDIT_face1,page_head->face);
					SetWindowText(EDIT_college1,page_head->college);
					SetWindowText(EDIT_profession1,page_head->profession);
					SetWindowText(EDIT_grade1,page_head->grade);
					page_head=page_head->next;
				}
				if(print>=2)
				{
					SetWindowText(EDIT_id2,page_head->id);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_sex2,page_head->sex);
					SetWindowText(EDIT_face2,page_head->face);
					SetWindowText(EDIT_college2,page_head->college);
					SetWindowText(EDIT_profession2,page_head->profession);
					SetWindowText(EDIT_grade2,page_head->grade);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					SetWindowText(EDIT_id3,page_head->id);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_sex3,page_head->sex);
					SetWindowText(EDIT_face3,page_head->face);
					SetWindowText(EDIT_college3,page_head->college);
					SetWindowText(EDIT_profession3,page_head->profession);
					SetWindowText(EDIT_grade3,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=4)
				{
					SetWindowText(EDIT_id4,page_head->id);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_sex4,page_head->sex);
					SetWindowText(EDIT_face4,page_head->face);
					SetWindowText(EDIT_college4,page_head->college);
					SetWindowText(EDIT_profession4,page_head->profession);
					SetWindowText(EDIT_grade4,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=5)
				{
					SetWindowText(EDIT_id5,page_head->id);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_sex5,page_head->sex);
					SetWindowText(EDIT_face5,page_head->face);
					SetWindowText(EDIT_college5,page_head->college);
					SetWindowText(EDIT_profession5,page_head->profession);
					SetWindowText(EDIT_grade5,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=6)
				{
					SetWindowText(EDIT_id6,page_head->id);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_sex6,page_head->sex);
					SetWindowText(EDIT_face6,page_head->face);
					SetWindowText(EDIT_college6,page_head->college);
					SetWindowText(EDIT_profession6,page_head->profession);
					SetWindowText(EDIT_grade6,page_head->grade);

					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				itoa(student_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"页，共");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				break;
			case BUTTON_a_student_inquire_prior:
				if(student_ck!=1)
				{
					MessageBox(NULL,"请点击“返回顶部”显示第一页学院信息！","提示",MB_OK);
					break;
				}
				page_head=student_head->next->next;
				if(student_now-1<=0)
				{
					MessageBox(NULL,"已经到第一页！","提示",MB_OK);
					return FALSE;
				}
				else
					student_now--;
				for(i=0;i<(student_now-1)*6;i++)//将page_head移到当前页的第一项
					page_head=page_head->next;
				
				if(student_now==page)//如果在最后一页，则计算最后一页记录数量
					print=sum-(page-1)*6;
				else//否则，记录总数为6
					print=6;
				//清空编辑框内容
					SetWindowText(EDIT_id1,"");
					SetWindowText(EDIT_id2,"");
					SetWindowText(EDIT_id3,"");
					SetWindowText(EDIT_id4,"");
					SetWindowText(EDIT_id5,"");
					SetWindowText(EDIT_id6,"");
					SetWindowText(EDIT_name1,"");
					SetWindowText(EDIT_name2,"");
					SetWindowText(EDIT_name3,"");
					SetWindowText(EDIT_name4,"");
					SetWindowText(EDIT_name5,"");
					SetWindowText(EDIT_name6,"");
					SetWindowText(EDIT_sex1,"");
					SetWindowText(EDIT_sex2,"");
					SetWindowText(EDIT_sex3,"");
					SetWindowText(EDIT_sex4,"");
					SetWindowText(EDIT_sex5,"");
					SetWindowText(EDIT_sex6,"");
					SetWindowText(EDIT_face1,"");
					SetWindowText(EDIT_face2,"");
					SetWindowText(EDIT_face3,"");
					SetWindowText(EDIT_face4,"");
					SetWindowText(EDIT_face5,"");
					SetWindowText(EDIT_face6,"");
					SetWindowText(EDIT_college1,"");
					SetWindowText(EDIT_college2,"");
					SetWindowText(EDIT_college3,"");
					SetWindowText(EDIT_college4,"");
					SetWindowText(EDIT_college5,"");
					SetWindowText(EDIT_college6,"");
					SetWindowText(EDIT_profession1,"");
					SetWindowText(EDIT_profession2,"");
					SetWindowText(EDIT_profession3,"");
					SetWindowText(EDIT_profession4,"");
					SetWindowText(EDIT_profession5,"");
					SetWindowText(EDIT_profession6,"");
					SetWindowText(EDIT_grade1,"");
					SetWindowText(EDIT_grade2,"");
					SetWindowText(EDIT_grade3,"");
					SetWindowText(EDIT_grade4,"");
					SetWindowText(EDIT_grade5,"");
					SetWindowText(EDIT_grade6,"");
				if(print>=1)
				{
					SetWindowText(EDIT_id1,page_head->id);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_sex1,page_head->sex);
					SetWindowText(EDIT_face1,page_head->face);
					SetWindowText(EDIT_college1,page_head->college);
					SetWindowText(EDIT_profession1,page_head->profession);
					SetWindowText(EDIT_grade1,page_head->grade);
					page_head=page_head->next;
				}
				if(print>=2)
				{
					SetWindowText(EDIT_id2,page_head->id);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_sex2,page_head->sex);
					SetWindowText(EDIT_face2,page_head->face);
					SetWindowText(EDIT_college2,page_head->college);
					SetWindowText(EDIT_profession2,page_head->profession);
					SetWindowText(EDIT_grade2,page_head->grade);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					SetWindowText(EDIT_id3,page_head->id);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_sex3,page_head->sex);
					SetWindowText(EDIT_face3,page_head->face);
					SetWindowText(EDIT_college3,page_head->college);
					SetWindowText(EDIT_profession3,page_head->profession);
					SetWindowText(EDIT_grade3,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=4)
				{
					SetWindowText(EDIT_id4,page_head->id);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_sex4,page_head->sex);
					SetWindowText(EDIT_face4,page_head->face);
					SetWindowText(EDIT_college4,page_head->college);
					SetWindowText(EDIT_profession4,page_head->profession);
					SetWindowText(EDIT_grade4,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=5)
				{
					SetWindowText(EDIT_id5,page_head->id);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_sex5,page_head->sex);
					SetWindowText(EDIT_face5,page_head->face);
					SetWindowText(EDIT_college5,page_head->college);
					SetWindowText(EDIT_profession5,page_head->profession);
					SetWindowText(EDIT_grade5,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=6)
				{
					SetWindowText(EDIT_id6,page_head->id);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_sex6,page_head->sex);
					SetWindowText(EDIT_face6,page_head->face);
					SetWindowText(EDIT_college6,page_head->college);
					SetWindowText(EDIT_profession6,page_head->profession);
					SetWindowText(EDIT_grade6,page_head->grade);

					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				itoa(student_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"页，共");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_student_inquire_next:
				if(student_ck!=1)
				{
					MessageBox(NULL,"请点击“返回顶部”显示第一页学院信息！","提示",MB_OK);
					break;
				}
				page_head=student_head->next->next;//移到记录第一页第一条记录
				if(student_now+1>page)//如果当前页+1等于总页数，弹出警告
				{
					MessageBox(NULL,"已经到最后一页！","提示",MB_OK);
					return FALSE;
				}
				else//否则，跳转页数
				{
					student_now++;
				}
				for(i=0;i<(student_now-1)*6;i++)//将page_head移到当前页的第一项
					page_head=page_head->next;
				
				if(student_now==page)//如果在最后一页，则计算最后一页记录数量
					print=sum-(page-1)*6;
				else//否则，记录总数为6
					print=6;
				//清空编辑框内容
					SetWindowText(EDIT_id1,"");
					SetWindowText(EDIT_id2,"");
					SetWindowText(EDIT_id3,"");
					SetWindowText(EDIT_id4,"");
					SetWindowText(EDIT_id5,"");
					SetWindowText(EDIT_id6,"");
					SetWindowText(EDIT_name1,"");
					SetWindowText(EDIT_name2,"");
					SetWindowText(EDIT_name3,"");
					SetWindowText(EDIT_name4,"");
					SetWindowText(EDIT_name5,"");
					SetWindowText(EDIT_name6,"");
					SetWindowText(EDIT_sex1,"");
					SetWindowText(EDIT_sex2,"");
					SetWindowText(EDIT_sex3,"");
					SetWindowText(EDIT_sex4,"");
					SetWindowText(EDIT_sex5,"");
					SetWindowText(EDIT_sex6,"");
					SetWindowText(EDIT_face1,"");
					SetWindowText(EDIT_face2,"");
					SetWindowText(EDIT_face3,"");
					SetWindowText(EDIT_face4,"");
					SetWindowText(EDIT_face5,"");
					SetWindowText(EDIT_face6,"");
					SetWindowText(EDIT_college1,"");
					SetWindowText(EDIT_college2,"");
					SetWindowText(EDIT_college3,"");
					SetWindowText(EDIT_college4,"");
					SetWindowText(EDIT_college5,"");
					SetWindowText(EDIT_college6,"");
					SetWindowText(EDIT_profession1,"");
					SetWindowText(EDIT_profession2,"");
					SetWindowText(EDIT_profession3,"");
					SetWindowText(EDIT_profession4,"");
					SetWindowText(EDIT_profession5,"");
					SetWindowText(EDIT_profession6,"");
					SetWindowText(EDIT_grade1,"");
					SetWindowText(EDIT_grade2,"");
					SetWindowText(EDIT_grade3,"");
					SetWindowText(EDIT_grade4,"");
					SetWindowText(EDIT_grade5,"");
					SetWindowText(EDIT_grade6,"");
				if(print>=1)
				{
					SetWindowText(EDIT_id1,page_head->id);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_sex1,page_head->sex);
					SetWindowText(EDIT_face1,page_head->face);
					SetWindowText(EDIT_college1,page_head->college);
					SetWindowText(EDIT_profession1,page_head->profession);
					SetWindowText(EDIT_grade1,page_head->grade);
					page_head=page_head->next;
				}
				if(print>=2)
				{
					SetWindowText(EDIT_id2,page_head->id);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_sex2,page_head->sex);
					SetWindowText(EDIT_face2,page_head->face);
					SetWindowText(EDIT_college2,page_head->college);
					SetWindowText(EDIT_profession2,page_head->profession);
					SetWindowText(EDIT_grade2,page_head->grade);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					SetWindowText(EDIT_id3,page_head->id);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_sex3,page_head->sex);
					SetWindowText(EDIT_face3,page_head->face);
					SetWindowText(EDIT_college3,page_head->college);
					SetWindowText(EDIT_profession3,page_head->profession);
					SetWindowText(EDIT_grade3,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=4)
				{
					SetWindowText(EDIT_id4,page_head->id);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_sex4,page_head->sex);
					SetWindowText(EDIT_face4,page_head->face);
					SetWindowText(EDIT_college4,page_head->college);
					SetWindowText(EDIT_profession4,page_head->profession);
					SetWindowText(EDIT_grade4,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=5)
				{
					SetWindowText(EDIT_id5,page_head->id);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_sex5,page_head->sex);
					SetWindowText(EDIT_face5,page_head->face);
					SetWindowText(EDIT_college5,page_head->college);
					SetWindowText(EDIT_profession5,page_head->profession);
					SetWindowText(EDIT_grade5,page_head->grade);

					page_head=page_head->next;
				}
				if(print>=6)
				{
					SetWindowText(EDIT_id6,page_head->id);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_sex6,page_head->sex);
					SetWindowText(EDIT_face6,page_head->face);
					SetWindowText(EDIT_college6,page_head->college);
					SetWindowText(EDIT_profession6,page_head->profession);
					SetWindowText(EDIT_grade6,page_head->grade);

					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				
				itoa(student_now,item,10);

				strcat(char_page,item);
				
				strcat(char_page,"页，共");
				itoa(page,item,10);//转换整形为字符型
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_student_inquire_exit:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
				break;
			}
			break;
		case WM_CLOSE:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
	}
    return FALSE;

}
//IDD_a_student_modification窗口回调函数

	int find_a_student_modification;//0.找到 1.未找到
	int state_a_student_modification;//修改状态提示
	int add_student;//增添信息合法，1.学院合法,2.班级合法other.不合法
	char student_item[10];
	student_List student_modification_p,student_new_info,student_old_info;
	student_List student_delete;
LRESULT CALLBACK	A_STUDENT_MODIFICATION(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	college_List college_p;
	class_List class_p;
	HWND EDIT_oldid,EDIT_oldid1,EDIT_newid;
	HWND EDIT_oldname,EDIT_newname;
	HWND EDIT_oldsex,EDIT_newsex;
	HWND EDIT_oldnation,EDIT_newnation;
	HWND EDIT_oldface,EDIT_newface;
	HWND EDIT_oldbirth,EDIT_newbirth;
	HWND EDIT_oldtime,EDIT_newtime;
	HWND EDIT_oldcollege,EDIT_newcollege;
	HWND EDIT_oldprofession,EDIT_newprofession;
	HWND EDIT_oldgrade,EDIT_newgrade;
	char new_id[100],new_name[100],new_sex[100],new_nation[100],new_face[100],new_birth[100],new_time[100],new_college[100],new_profession[100],new_grade[100];
	char year[10],month[5],day[5];
	char year1[10],month1[5];
	char message_a_student_modification[60];
	char *stop;//为strtol定义的终止字符指针
	int id;
	int i;
	add_student=0;
	student_head=(student_List)malloc(sizeof(student_Lnode));
	student_load(student_head);
	EDIT_oldid=GetDlgItem(hDlg,EDIT_a_student_modification_oldid);
	EDIT_oldid1=GetDlgItem(hDlg,EDIT_a_student_modification_oldid1);
	EDIT_oldname=GetDlgItem(hDlg,EDIT_a_student_modification_oldname);
	EDIT_oldsex=GetDlgItem(hDlg,EDIT_a_student_modification_oldsex);
	EDIT_oldnation=GetDlgItem(hDlg,EDIT_a_student_modification_oldnation);
	EDIT_oldface=GetDlgItem(hDlg,EDIT_a_student_modification_oldface);
	EDIT_oldbirth=GetDlgItem(hDlg,EDIT_a_student_modification_oldbirth);
	EDIT_oldtime=GetDlgItem(hDlg,EDIT_a_student_modification_oldtime);
	EDIT_oldcollege=GetDlgItem(hDlg,EDIT_a_student_modification_oldcollege);
	EDIT_oldprofession=GetDlgItem(hDlg,EDIT_a_student_modification_oldprofession);
	EDIT_oldgrade=GetDlgItem(hDlg,EDIT_a_student_modification_oldgrade);
	
	EDIT_newid=GetDlgItem(hDlg,EDIT_a_student_modification_newid);
	EDIT_newname=GetDlgItem(hDlg,EDIT_a_student_modification_newname);
	EDIT_newsex=GetDlgItem(hDlg,EDIT_a_student_modification_newsex);
	EDIT_newnation=GetDlgItem(hDlg,EDIT_a_student_modification_newnation);
	EDIT_newface=GetDlgItem(hDlg,EDIT_a_student_modification_newface);
	EDIT_newbirth=GetDlgItem(hDlg,EDIT_a_student_modification_newbirth);
	EDIT_newtime=GetDlgItem(hDlg,EDIT_a_student_modification_newtime);
	EDIT_newcollege=GetDlgItem(hDlg,EDIT_a_student_modification_newcollege);
	EDIT_newprofession=GetDlgItem(hDlg,EDIT_a_student_modification_newprofession);
	EDIT_newgrade=GetDlgItem(hDlg,EDIT_a_student_modification_newgrade);
	
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			//通过id定位学生
			case BUTTON_a_student_modification_location:
				find_a_student_modification=0;
				GetWindowText(EDIT_oldid,student_item,GetWindowTextLength(EDIT_oldid)+1);//获取oldid编辑框内容到item
				student_modification_p=student_head->next->next;
				while(student_modification_p)
				{
					if(strcmp(student_modification_p->id,student_item)==0)
					{
						student_old_info=(student_List)malloc(sizeof(student_Lnode));
						strcpy(student_old_info->id,student_modification_p->id);
						strcpy(student_old_info->name,student_modification_p->name);
						strcpy(student_old_info->sex,student_modification_p->sex);
						strcpy(student_old_info->nation,student_modification_p->nation);
						strcpy(student_old_info->face,student_modification_p->face);
						strcpy(student_old_info->birth,student_modification_p->birth);
						strcpy(student_old_info->time,student_modification_p->time);
						strcpy(student_old_info->college,student_modification_p->college);
						strcpy(student_old_info->profession,student_modification_p->profession);
						strcpy(student_old_info->grade,student_modification_p->grade);
						student_old_info->num=student_modification_p->num;
						find_a_student_modification=1;
						break;
					}
					else
						student_modification_p=student_modification_p->next;
				}
				if(find_a_student_modification!=1)
				{
					MessageBox(NULL,"输入有误！","ERROR!",MB_OK);
					break;
					return FALSE;
				}
				SetWindowText(EDIT_oldid1,student_old_info->id);
				SetWindowText(EDIT_oldname,student_old_info->name);
				SetWindowText(EDIT_oldsex,student_old_info->sex);
				SetWindowText(EDIT_oldnation,student_old_info->nation);
				SetWindowText(EDIT_oldface,student_old_info->face);
				SetWindowText(EDIT_oldbirth,student_old_info->birth);
				SetWindowText(EDIT_oldtime,student_old_info->time);
				SetWindowText(EDIT_oldcollege,student_old_info->college);
				SetWindowText(EDIT_oldprofession,student_old_info->profession);
				SetWindowText(EDIT_oldgrade,student_old_info->grade);

				SetWindowText(EDIT_newid,student_old_info->id);
				SetWindowText(EDIT_newname,student_old_info->name);
				SetWindowText(EDIT_newsex,student_old_info->sex);
				SetWindowText(EDIT_newnation,student_old_info->nation);
				SetWindowText(EDIT_newface,student_old_info->face);
				SetWindowText(EDIT_newbirth,student_old_info->birth);
				SetWindowText(EDIT_newtime,student_old_info->time);
				SetWindowText(EDIT_newcollege,student_old_info->college);
				SetWindowText(EDIT_newprofession,student_old_info->profession);
				SetWindowText(EDIT_newgrade,student_old_info->grade);

				state_a_student_modification=1;//修改状态为修改
				MessageBox(NULL,"定位成功！请修改数据或删除数据。修改完毕按“确认修改”保存！","ERROR!",MB_OK);
				break;
			//增添学生
			case BUTTON_a_student_modification_add:
				MessageBox(NULL,"请在新数据信息框中输入新学生信息,初始密码为“student”","提示",MB_OK);
				find_a_student_modification=0;
				state_a_student_modification=2;//修改状态为增添学生

				SetWindowText(EDIT_oldid,"");
				SetWindowText(EDIT_oldid1,"");
				SetWindowText(EDIT_oldname,"");
				SetWindowText(EDIT_oldsex,"");
				SetWindowText(EDIT_oldnation,"");
				SetWindowText(EDIT_oldface,"");
				SetWindowText(EDIT_oldbirth,"");
				SetWindowText(EDIT_oldtime,"");
				SetWindowText(EDIT_oldcollege,"");
				SetWindowText(EDIT_oldprofession,"");
				SetWindowText(EDIT_oldgrade,"");

				SetWindowText(EDIT_newid,"账号字符数<20");
				SetWindowText(EDIT_newname,"姓名字数<10");
				SetWindowText(EDIT_newsex,"男or女");
				SetWindowText(EDIT_newnation,"xx族");
				SetWindowText(EDIT_newface,"群众");
				SetWindowText(EDIT_newbirth,"xxxx-xx-xx");
				SetWindowText(EDIT_newtime,"xxxx-xx");
				SetWindowText(EDIT_newcollege,"xxxxxxxxxxxxxx学院");
				SetWindowText(EDIT_newprofession,"");
				SetWindowText(EDIT_newgrade,"讲师");

				student_new_info=(student_List)malloc(sizeof(student_Lnode));
				student_new_info->num=student_head->next->num+1;
				itoa(student_new_info->num,student_item,10);
				strcpy(message_a_student_modification,"新学生编码为：");
				strcat(message_a_student_modification,student_item);
				SetWindowText(EDIT_oldid,message_a_student_modification);
				break;
			//确认修改
			case BUTTON_a_student_modification_affirm:
				GetWindowText(EDIT_newid,new_id,GetWindowTextLength(EDIT_newid)+1);//获取newid框内容到new_id
				GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//获取newnaeme框内容到new_name
				GetWindowText(EDIT_newsex,new_sex,GetWindowTextLength(EDIT_newsex)+1);//获取newsex框内容到new_sex
				GetWindowText(EDIT_newnation,new_nation,GetWindowTextLength(EDIT_newnation)+1);//获取newnation框内容到new_nation
				GetWindowText(EDIT_newface,new_face,GetWindowTextLength(EDIT_newface)+1);//获取newface框内容到new_face
				GetWindowText(EDIT_newbirth,new_birth,GetWindowTextLength(EDIT_newbirth)+1);//获取newbirth框内容到new_birth
				GetWindowText(EDIT_newtime,new_time,GetWindowTextLength(EDIT_newtime)+1);//获取newtime框内容到new_time
				GetWindowText(EDIT_newcollege,new_college,GetWindowTextLength(EDIT_newcollege)+1);//获取newcollege框内容到new_college
				GetWindowText(EDIT_newprofession,new_profession,GetWindowTextLength(EDIT_newprofession)+1);//获取newprofession框内容到new_profession
				GetWindowText(EDIT_newgrade,new_grade,GetWindowTextLength(EDIT_newgrade)+1);//获取newngrade框内容到new_grade
				if(state_a_student_modification==1)//确认修改现有专业信息
				{
				if(strcmp(new_id,student_old_info->id)!=0)
				{
					MessageBox(NULL,"不允许修改账号！","警告",MB_OK);
					strcpy(new_id,student_old_info->id);
					SetWindowText(EDIT_newid,student_old_info->id);
					return FALSE;
				}
				if(strlen(new_name)>28||strlen(new_name)<2)
				{
					MessageBox(NULL,"学生姓名输入有误！","警告",MB_OK);
					strcpy(new_name,student_old_info->name);
					SetWindowText(EDIT_newname,student_old_info->name);
					return FALSE;
				}
				if((strcmp(new_sex,"男")!=0)&&strcmp(new_sex,"女")!=0)
				{
					MessageBox(NULL,"学生性别输入有误！","警告",MB_OK);
					strcpy(new_sex,student_old_info->sex);
					SetWindowText(EDIT_newsex,student_old_info->sex);
					return FALSE;
				}
				if(strlen(new_nation)>12||strlen(new_nation)<2)
				{
					MessageBox(NULL,"学生民族输入有误！","警告",MB_OK);
					strcpy(new_nation,student_old_info->nation);
					SetWindowText(EDIT_newnation,student_old_info->nation);
					return FALSE;
				}
				if(strlen(new_face)>12||strlen(new_face)<2)
				{
					MessageBox(NULL,"学生民族输入有误！","警告",MB_OK);
					strcpy(new_face,student_old_info->face);
					SetWindowText(EDIT_newface,student_old_info->face);
					return FALSE;
				}
				sscanf(new_birth,"%4s%*1s%2s%*1s%2s%*s",&year,&month,&day);
				if(strcmp(year,"1960")<0||strcmp(year,"2017")>0)
					{
					MessageBox(NULL,"学生出生年份输入有误！","警告",MB_OK);
					strcpy(new_birth,student_old_info->birth);
					SetWindowText(EDIT_newbirth,student_old_info->birth);
					return FALSE;
				}
				if(strcmp(month,"01")<0||strcmp(month,"12")>0)
					{
					MessageBox(NULL,"学生出生月份输入有误！","警告",MB_OK);
					strcpy(new_birth,student_old_info->birth);
					SetWindowText(EDIT_newbirth,student_old_info->birth);
					return FALSE;
				}
				if(strcmp(day,"01")<0||strcmp(day,"31")>0)
					{
					MessageBox(NULL,"学生出生日期输入有误！","警告",MB_OK);
					strcpy(new_birth,student_old_info->birth);
					SetWindowText(EDIT_newbirth,student_old_info->birth);
					return FALSE;
				}
				sscanf(new_time,"%4s%*1s%2s%*1s%*s",&year,&month);
				if(strcmp(year,"1960")<0||strcmp(year,"2017")>0)
					{
					MessageBox(NULL,"学生入职年份输入有误！","警告",MB_OK);
					strcpy(new_time,student_old_info->time);
					SetWindowText(EDIT_newtime,student_old_info->time);
					return FALSE;
				}
				if(strcmp(month,"01")<0||strcmp(month,"12")>0)
					{
					MessageBox(NULL,"学生入职月份输入有误！","警告",MB_OK);
					strcpy(new_time,student_old_info->time);
					SetWindowText(EDIT_newtime,student_old_info->time);
					return FALSE;
				}

				if(strcmp(new_college,student_old_info->college)!=0)
				{
					MessageBox(NULL,"新的所属学院信息不会存储！\n若想修改学院请删除数据后重新规定学院！","警告",MB_OK);
				}
				if(strlen(new_profession)>30||strlen(new_profession)<2)
				{
					MessageBox(NULL,"学生所属部门输入有误！","警告",MB_OK);
					strcpy(new_profession,student_old_info->profession);
					SetWindowText(EDIT_newprofession,student_old_info->profession);
					return FALSE;
				}

				if(strlen(new_grade)>30||strlen(new_grade)<2)
				{
					MessageBox(NULL,"学生所属班级输入有误！","警告",MB_OK);
					strcpy(new_grade,student_old_info->grade);
					SetWindowText(EDIT_newgrade,student_old_info->grade);
					return FALSE;
				}
				student_modification_p=student_head->next;

				for(i=0;i<student_old_info->num;i++)
					student_modification_p=student_modification_p->next;
			    strcpy(student_modification_p->id,new_id);
				strcpy(student_modification_p->name,new_name);
				strcpy(student_modification_p->sex,new_sex);
				strcpy(student_modification_p->nation,new_nation);
				strcpy(student_modification_p->face,new_face);
				strcpy(student_modification_p->birth,new_birth);
				strcpy(student_modification_p->time,new_time);
				strcpy(student_modification_p->college,new_college);
				strcpy(student_modification_p->profession,new_profession);
				strcpy(student_modification_p->grade,new_grade);
				student_save(student_head);
				student_load(student_head);
				SetWindowText(EDIT_oldname,new_name);
				MessageBox(NULL,"修改成功！","警告",MB_OK);
				}

				
				if(state_a_student_modification==2)//确认增添学院信息
				{
					GetWindowText(EDIT_newid,new_id,GetWindowTextLength(EDIT_newid)+1);//获取newid框内容到new_id
				GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//获取newnaeme框内容到new_name
				GetWindowText(EDIT_newsex,new_sex,GetWindowTextLength(EDIT_newsex)+1);//获取newsex框内容到new_sex
				GetWindowText(EDIT_newnation,new_nation,GetWindowTextLength(EDIT_newnation)+1);//获取newnation框内容到new_nation
				GetWindowText(EDIT_newface,new_face,GetWindowTextLength(EDIT_newface)+1);//获取newface框内容到new_face
				GetWindowText(EDIT_newbirth,new_birth,GetWindowTextLength(EDIT_newbirth)+1);//获取newbirth框内容到new_birth
				GetWindowText(EDIT_newtime,new_time,GetWindowTextLength(EDIT_newtime)+1);//获取newtime框内容到new_time
				GetWindowText(EDIT_newcollege,new_college,GetWindowTextLength(EDIT_newcollege)+1);//获取newcollege框内容到new_college
				GetWindowText(EDIT_newprofession,new_profession,GetWindowTextLength(EDIT_newprofession)+1);//获取newprofession框内容到new_profession
				GetWindowText(EDIT_newgrade,new_grade,GetWindowTextLength(EDIT_newgrade)+1);//获取newngrade框内容到new_grade
				
				student_modification_p=student_head->next;
				for(i=0;i<student_head->next->num;i++)
					{
						student_modification_p=student_modification_p->next;
						if(strcmp(student_new_info->id,student_modification_p->id)==0)
						{
							MessageBox(NULL,"账号重复！","警告",MB_OK);
							add_student=0;
							//break;
							return FALSE;
						}
					}
				if(strlen(new_id)>28||strlen(new_id)<2)
				{
					MessageBox(NULL,"学生账号输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newid,"");
					break;
					return FALSE;
				}	
				if(strlen(new_name)>28||strlen(new_name)<2)
				{
					MessageBox(NULL,"学生姓名输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newname,"");
					break;
					return FALSE;
				}
				if((strcmp(new_sex,"男")!=0)&&strcmp(new_sex,"女")!=0)
				{
					MessageBox(NULL,"学生性别输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newsex,"");
					break;
					return FALSE;
				}
				if(strlen(new_nation)>12||strlen(new_nation)<2)
				{
					MessageBox(NULL,"学生民族输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newnation,"");
					break;
					return FALSE;
				}
				if(strlen(new_face)>12||strlen(new_face)<2)
				{
					MessageBox(NULL,"学生政治面貌输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newface,"");
					break;
					return FALSE;
				}
				sscanf(new_birth,"%4s%*1s%2s%*1s%2s%*s",&year,&month,&day);
				if(strcmp(year,"1960")<0||strcmp(year,"2017")>0)
					{
					MessageBox(NULL,"学生出生年份输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newbirth,"");
					break;
					return FALSE;
				}
				if(strcmp(month,"01")<0||strcmp(month,"12")>0)
					{
					MessageBox(NULL,"学生出生月份输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newbirth,"");
					break;
					return FALSE;
				}
				if(strcmp(day,"01")<0||strcmp(day,"31")>0)
					{
					MessageBox(NULL,"学生出生日期输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newbirth,"");
					break;
					return FALSE;
				}
				sscanf(new_time,"%4s%*1s%2s%*s",&year1,&month1);
				if(strcmp(year1,"1960")<0||strcmp(year1,"2017")>0)
					{
					MessageBox(NULL,"学生入职年份输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newtime,"");
					break;
					return FALSE;
				}
				if(strcmp(month1,"01")<0||strcmp(month1,"12")>0)
					{
					MessageBox(NULL,"学生入职月份输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newtime,"");
					break;
					return FALSE;
				}

				if(strlen(new_profession)>30||strlen(new_profession)<2)
				{
					MessageBox(NULL,"学生所属部门输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newprofession,"");
					break;
					return FALSE;
				}
				if(strlen(new_grade)>30||strlen(new_grade)<2)
				{
					MessageBox(NULL,"学生班级输入有误！","警告",MB_OK);
					SetWindowText(EDIT_newgrade,"");
					break;
					return FALSE;
				}
					strcpy(student_new_info->password,"admin");
					strcpy(student_new_info->identity,"学生");
					strcpy(student_new_info->id,new_id);
					strcpy(student_new_info->name,new_name);
					strcpy(student_new_info->sex,new_sex);
					strcpy(student_new_info->nation,new_nation);
					strcpy(student_new_info->face,new_face);
					strcpy(student_new_info->birth,new_birth);
					strcpy(student_new_info->time,new_time);
					strcpy(student_new_info->college,new_college);
					strcpy(student_new_info->profession,new_profession);
					strcpy(student_new_info->grade,new_grade);
					student_modification_p=student_head->next;
					college_load(college_head);
					college_p=college_head->next;
					class_load(class_head);
					class_p=class_head->next;
					//增添信息合法，1.学院合法,2.班级合法other.不合法
					add_student=0;
					while(college_p)
					{
						if(strcmp(college_p->name,new_college)==0)
						{
							add_student=1;
							while(class_p)
							{
								if(strcmp(new_grade,class_p->name)==0)
								{
									strcpy(student_new_info->college,new_college);
									student_new_info->collegeid=college_p->id;
									add_student=2;
									break;
								}
								class_p=class_p->next;
							}
						}
						if(add_student==0)
							college_p=college_p->next;
						else
							break;
					}
					if(add_student==0)
					{
						MessageBox(NULL,"学院不存在！","警告",MB_OK);
						break;
						return FALSE;
					}
					if(add_student==1&&add_student!=2)
					{
						MessageBox(NULL,"班级不存在！","警告",MB_OK);
						break;
						return FALSE;
					}
					if(strlen(new_name)==0||strlen(new_name)>20)
					{
						MessageBox(NULL,"专业名称非法！","警告",MB_OK);
						add_student=0;
						break;
						return FALSE;
					}
					student_modification_p=student_head->next;
					for(i=0;i<student_head->next->num;i++)
						student_modification_p=student_modification_p->next;
					student_modification_p->next=student_new_info;
					student_new_info->prior=student_modification_p;
					student_new_info->next=NULL;
					student_head->next->num++;
					student_save(student_head);
					student_load(student_head);

				SetWindowText(EDIT_oldid1,student_new_info->id);
				SetWindowText(EDIT_oldname,student_new_info->name);
				SetWindowText(EDIT_oldsex,student_new_info->sex);
				SetWindowText(EDIT_oldnation,student_new_info->nation);
				SetWindowText(EDIT_oldface,student_new_info->face);
				SetWindowText(EDIT_oldbirth,student_new_info->birth);
				SetWindowText(EDIT_oldtime,student_new_info->time);
				SetWindowText(EDIT_oldcollege,student_new_info->college);
				SetWindowText(EDIT_oldprofession,student_new_info->profession);
				SetWindowText(EDIT_oldgrade,student_new_info->grade);

				SetWindowText(EDIT_newname,student_new_info->name);
				SetWindowText(EDIT_newsex,student_new_info->sex);
				SetWindowText(EDIT_newnation,student_new_info->nation);
				SetWindowText(EDIT_newface,student_new_info->face);
				SetWindowText(EDIT_newbirth,student_new_info->birth);
				SetWindowText(EDIT_newtime,student_new_info->time);
				SetWindowText(EDIT_newcollege,student_new_info->college);
				SetWindowText(EDIT_newprofession,student_new_info->profession);
				SetWindowText(EDIT_newgrade,student_new_info->grade);

					MessageBox(NULL,"修改成功！","提示",MB_OK);
					student_old_info=(student_List)malloc(sizeof(student_Lnode));
					strcpy(student_old_info->name,student_new_info->name);
					strcpy(student_old_info->id,student_new_info->id);
					student_old_info->num=student_new_info->num;
					find_a_student_modification=1;
				}
				break;
			//删除学生
			case BUTTON_a_student_modification_delete:
				if(find_a_student_modification==1)
				{
					if(strcmp(student_old_info->id,account_mine->id)==0)
					{
						MessageBox(NULL,"不允许删除已登录账号！","警告",MB_OK|MB_ICONEXCLAMATION);
						return FALSE;
					}
				strcpy(message_a_student_modification,"确认删除学生：“");
				strcat(message_a_student_modification,student_old_info->name);
				strcat(message_a_student_modification,"”吗？");
				if(MessageBox(NULL,message_a_student_modification,"警告",MB_YESNO|MB_ICONEXCLAMATION)!=6)
				{
					return FALSE;
				}
				student_modification_p=student_head->next;
				for(i=0;i<student_old_info->num;i++)
					student_modification_p=student_modification_p->next;
				student_modification_p->num=-1;
				strcat(student_modification_p->name,"（已删除）");
				student_modification_p=student_head->next->next;
				student_save(student_head);
				student_load(student_head);
				SetWindowText(EDIT_oldid1,"");
				SetWindowText(EDIT_oldname,"");
				SetWindowText(EDIT_oldsex,"");
				SetWindowText(EDIT_oldnation,"");
				SetWindowText(EDIT_oldface,"");
				SetWindowText(EDIT_oldbirth,"");
				SetWindowText(EDIT_oldtime,"");
				SetWindowText(EDIT_oldcollege,"");
				SetWindowText(EDIT_oldprofession,"");
				SetWindowText(EDIT_oldgrade,"");

				SetWindowText(EDIT_newname,"");
				SetWindowText(EDIT_newsex,"");
				SetWindowText(EDIT_newnation,"");
				SetWindowText(EDIT_newface,"");
				SetWindowText(EDIT_newbirth,"");
				SetWindowText(EDIT_newtime,"");
				SetWindowText(EDIT_newcollege,"");
				SetWindowText(EDIT_newprofession,"");
				SetWindowText(EDIT_newgrade,"");
				MessageBox(NULL,"删除成功！","警告",MB_OK);
				find_a_student_modification=0;
				break;
				}
				MessageBox(NULL,"非法操作！","警告",MB_OK);
				break;
			case BUTTON_a_student_modification_exit:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
		case WM_CLOSE:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
	}
    return FALSE;

}
//IDD_a_score_inquir窗口回调函数
	int score_ck; //标记是否初始化内容，1.是，0.否
	int score_now;
LRESULT CALLBACK	A_SCORE_INQUIRE(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,sum,page,print;//sum.资料总数 page.总页数 now.当前页数 print.当前页资料总数
	score_List page_head;
	char paper_score1[10],paper_score2[10],paper_score3[10],paper_score4[10],paper_score5[10],paper_score6[10];
	char usual_score1[10],usual_score2[10],usual_score3[10],usual_score4[10],usual_score5[10],usual_score6[10];
	char makeup_score1[10],makeup_score2[10],makeup_score3[10],makeup_score4[10],makeup_score5[10],makeup_score6[10];
	char score1[10],score2[10],score3[10],score4[10],score5[10],score6[10];
	char char_page[30],item[10];
	HWND EDIT_id1,EDIT_id2,EDIT_id3,EDIT_id4,EDIT_id5,EDIT_id6;
	HWND EDIT_name1,EDIT_name2,EDIT_name3,EDIT_name4,EDIT_name5,EDIT_name6;
	HWND EDIT_paper_score1,EDIT_paper_score2,EDIT_paper_score3,EDIT_paper_score4,EDIT_paper_score5,EDIT_paper_score6;
	HWND EDIT_usual_score1,EDIT_usual_score2,EDIT_usual_score3,EDIT_usual_score4,EDIT_usual_score5,EDIT_usual_score6;
	HWND EDIT_makeup_score1,EDIT_makeup_score2,EDIT_makeup_score3,EDIT_makeup_score4,EDIT_makeup_score5,EDIT_makeup_score6;
	HWND EDIT_score1,EDIT_score2,EDIT_score3,EDIT_score4,EDIT_score5,EDIT_score6;
	HWND EDIT_subject1,EDIT_subject2,EDIT_subject3,EDIT_subject4,EDIT_subject5,EDIT_subject6;
	HWND EDIT_term1,EDIT_term2,EDIT_term3,EDIT_term4,EDIT_term5,EDIT_term6;
	HWND EDIT_grade1,EDIT_grade2,EDIT_grade3,EDIT_grade4,EDIT_grade5,EDIT_grade6;
	HWND EDIT_page;
	score_head=(score_List)malloc(sizeof(score_Lnode));
	score_load(score_head);
	sum=score_head->next->num;
	page=sum/6;
	if(sum%6!=0)
		page++;
	
	EDIT_id1=GetDlgItem(hDlg,EDIT_a_score_inquire_id1);
	EDIT_id2=GetDlgItem(hDlg,EDIT_a_score_inquire_id2);
	EDIT_id3=GetDlgItem(hDlg,EDIT_a_score_inquire_id3);
	EDIT_id4=GetDlgItem(hDlg,EDIT_a_score_inquire_id4);
	EDIT_id5=GetDlgItem(hDlg,EDIT_a_score_inquire_id5);
	EDIT_id6=GetDlgItem(hDlg,EDIT_a_score_inquire_id6);
	EDIT_name1=GetDlgItem(hDlg,EDIT_a_score_inquire_name1);
	EDIT_name2=GetDlgItem(hDlg,EDIT_a_score_inquire_name2);
	EDIT_name3=GetDlgItem(hDlg,EDIT_a_score_inquire_name3);
	EDIT_name4=GetDlgItem(hDlg,EDIT_a_score_inquire_name4);
	EDIT_name5=GetDlgItem(hDlg,EDIT_a_score_inquire_name5);
	EDIT_name6=GetDlgItem(hDlg,EDIT_a_score_inquire_name6);
	EDIT_paper_score1=GetDlgItem(hDlg,EDIT_a_score_inquire_paper_score1);
	EDIT_paper_score2=GetDlgItem(hDlg,EDIT_a_score_inquire_paper_score2);
	EDIT_paper_score3=GetDlgItem(hDlg,EDIT_a_score_inquire_paper_score3);
	EDIT_paper_score4=GetDlgItem(hDlg,EDIT_a_score_inquire_paper_score4);
	EDIT_paper_score5=GetDlgItem(hDlg,EDIT_a_score_inquire_paper_score5);
	EDIT_paper_score6=GetDlgItem(hDlg,EDIT_a_score_inquire_paper_score6);
	EDIT_usual_score1=GetDlgItem(hDlg,EDIT_a_score_inquire_usual_score1);
	EDIT_usual_score2=GetDlgItem(hDlg,EDIT_a_score_inquire_usual_score2);
	EDIT_usual_score3=GetDlgItem(hDlg,EDIT_a_score_inquire_usual_score3);
	EDIT_usual_score4=GetDlgItem(hDlg,EDIT_a_score_inquire_usual_score4);
	EDIT_usual_score5=GetDlgItem(hDlg,EDIT_a_score_inquire_usual_score5);
	EDIT_usual_score6=GetDlgItem(hDlg,EDIT_a_score_inquire_usual_score6);
	EDIT_subject1=GetDlgItem(hDlg,EDIT_a_score_inquire_subject1);
	EDIT_subject2=GetDlgItem(hDlg,EDIT_a_score_inquire_subject2);
	EDIT_subject3=GetDlgItem(hDlg,EDIT_a_score_inquire_subject3);
	EDIT_subject4=GetDlgItem(hDlg,EDIT_a_score_inquire_subject4);
	EDIT_subject5=GetDlgItem(hDlg,EDIT_a_score_inquire_subject5);
	EDIT_subject6=GetDlgItem(hDlg,EDIT_a_score_inquire_subject6);
	EDIT_makeup_score1=GetDlgItem(hDlg,EDIT_a_score_inquire_makeup_score1);
	EDIT_makeup_score2=GetDlgItem(hDlg,EDIT_a_score_inquire_makeup_score2);
	EDIT_makeup_score3=GetDlgItem(hDlg,EDIT_a_score_inquire_makeup_score3);
	EDIT_makeup_score4=GetDlgItem(hDlg,EDIT_a_score_inquire_makeup_score4);
	EDIT_makeup_score5=GetDlgItem(hDlg,EDIT_a_score_inquire_makeup_score5);
	EDIT_makeup_score6=GetDlgItem(hDlg,EDIT_a_score_inquire_makeup_score6);
	EDIT_score1=GetDlgItem(hDlg,EDIT_a_score_inquire_score1);
	EDIT_score2=GetDlgItem(hDlg,EDIT_a_score_inquire_score2);
	EDIT_score3=GetDlgItem(hDlg,EDIT_a_score_inquire_score3);
	EDIT_score4=GetDlgItem(hDlg,EDIT_a_score_inquire_score4);
	EDIT_score5=GetDlgItem(hDlg,EDIT_a_score_inquire_score5);
	EDIT_score6=GetDlgItem(hDlg,EDIT_a_score_inquire_score6);
	EDIT_grade1=GetDlgItem(hDlg,EDIT_a_score_inquire_grade1);
	EDIT_grade2=GetDlgItem(hDlg,EDIT_a_score_inquire_grade2);
	EDIT_grade3=GetDlgItem(hDlg,EDIT_a_score_inquire_grade3);
	EDIT_grade4=GetDlgItem(hDlg,EDIT_a_score_inquire_grade4);
	EDIT_grade5=GetDlgItem(hDlg,EDIT_a_score_inquire_grade5);
	EDIT_grade6=GetDlgItem(hDlg,EDIT_a_score_inquire_grade6);
	EDIT_term1=GetDlgItem(hDlg,EDIT_a_score_inquire_term1);
	EDIT_term2=GetDlgItem(hDlg,EDIT_a_score_inquire_term2);
	EDIT_term3=GetDlgItem(hDlg,EDIT_a_score_inquire_term3);
	EDIT_term4=GetDlgItem(hDlg,EDIT_a_score_inquire_term4);
	EDIT_term5=GetDlgItem(hDlg,EDIT_a_score_inquire_term5);
	EDIT_term6=GetDlgItem(hDlg,EDIT_a_score_inquire_term6);
	EDIT_page=GetDlgItem(hDlg,EDIT_a_score_inquire_page);
	
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case BUTTON_a_score_inquire_top:
				if(sum==0)
				{
					MessageBox(NULL,"数据库为空！","ERROR!",MB_OK);
					return FALSE;
				}
				score_ck=1;
				score_now=1;
				if(sum>=6)
					print=6;//若总资料数不小于6，则第一页显示6条数据
				if(sum<6)
					print=sum;//若资料总数小于6，则第一页显示全部sum条数据
				page_head=score_head->next->next;//指向第一页第一条记录
				if(print>=1)
				{
					itoa(page_head->paper_score,paper_score1,10);
					itoa(page_head->usual_score,usual_score1,10);
					itoa(page_head->makeup_score,makeup_score1,10);
					itoa(page_head->score,score1,10);
					SetWindowText(EDIT_id1,page_head->id);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_subject1,page_head->subject);
					SetWindowText(EDIT_grade1,page_head->grade);
					SetWindowText(EDIT_term1,page_head->term);
					SetWindowText(EDIT_paper_score1,paper_score1);
					SetWindowText(EDIT_usual_score1,usual_score1);
					SetWindowText(EDIT_makeup_score1,makeup_score1);
					SetWindowText(EDIT_score1,score1);
					page_head=page_head->next;
				}
				if(print>=2)
				{
					itoa(page_head->paper_score,paper_score2,10);
					itoa(page_head->usual_score,usual_score2,10);
					itoa(page_head->makeup_score,makeup_score2,10);
					itoa(page_head->score,score2,10);
					SetWindowText(EDIT_id2,page_head->id);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_subject2,page_head->subject);
					SetWindowText(EDIT_grade2,page_head->grade);
					SetWindowText(EDIT_term2,page_head->term);
					SetWindowText(EDIT_paper_score2,paper_score2);
					SetWindowText(EDIT_usual_score2,usual_score2);
					SetWindowText(EDIT_makeup_score2,makeup_score2);
					SetWindowText(EDIT_score2,score2);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					itoa(page_head->paper_score,paper_score3,10);
					itoa(page_head->usual_score,usual_score3,10);
					itoa(page_head->makeup_score,makeup_score3,10);
					itoa(page_head->score,score3,10);
					SetWindowText(EDIT_id3,page_head->id);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_subject3,page_head->subject);
					SetWindowText(EDIT_grade3,page_head->grade);
					SetWindowText(EDIT_term3,page_head->term);
					SetWindowText(EDIT_paper_score3,paper_score3);
					SetWindowText(EDIT_usual_score3,usual_score3);
					SetWindowText(EDIT_makeup_score3,makeup_score3);
					SetWindowText(EDIT_score3,score3);
					page_head=page_head->next;
				}
				if(print>=4)
				{
					itoa(page_head->paper_score,paper_score4,10);
					itoa(page_head->usual_score,usual_score4,10);
					itoa(page_head->makeup_score,makeup_score4,10);
					itoa(page_head->score,score4,10);
					SetWindowText(EDIT_id4,page_head->id);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_subject4,page_head->subject);
					SetWindowText(EDIT_grade4,page_head->grade);
					SetWindowText(EDIT_term4,page_head->term);
					SetWindowText(EDIT_paper_score4,paper_score4);
					SetWindowText(EDIT_usual_score4,usual_score4);
					SetWindowText(EDIT_makeup_score4,makeup_score4);
					SetWindowText(EDIT_score4,score4);
					page_head=page_head->next;
				}
				if(print>=5)
				{
					itoa(page_head->paper_score,paper_score5,10);
					itoa(page_head->usual_score,usual_score5,10);
					itoa(page_head->makeup_score,makeup_score5,10);
					itoa(page_head->score,score5,10);
					SetWindowText(EDIT_id5,page_head->id);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_subject5,page_head->subject);
					SetWindowText(EDIT_grade5,page_head->grade);
					SetWindowText(EDIT_term5,page_head->term);
					SetWindowText(EDIT_paper_score5,paper_score5);
					SetWindowText(EDIT_usual_score5,usual_score5);
					SetWindowText(EDIT_makeup_score5,makeup_score5);
					SetWindowText(EDIT_score5,score5);
					page_head=page_head->next;
				}
				if(print>=6)
				{
					itoa(page_head->paper_score,paper_score6,10);
					itoa(page_head->usual_score,usual_score6,10);
					itoa(page_head->makeup_score,makeup_score6,10);
					itoa(page_head->score,score6,10);
					SetWindowText(EDIT_id6,page_head->id);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_subject6,page_head->subject);
					SetWindowText(EDIT_grade6,page_head->grade);
					SetWindowText(EDIT_term6,page_head->term);
					SetWindowText(EDIT_paper_score6,paper_score6);
					SetWindowText(EDIT_usual_score6,usual_score6);
					SetWindowText(EDIT_makeup_score6,makeup_score6);
					SetWindowText(EDIT_score6,score6);
					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				itoa(score_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"页，共");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				break;
			case BUTTON_a_score_inquire_prior:
				if(score_ck!=1)
				{
					MessageBox(NULL,"请点击“返回顶部”显示第一页成绩信息！","提示",MB_OK);
					break;
				}
				page_head=score_head->next->next;
				if(score_now-1<=0)
				{
					MessageBox(NULL,"已经到第一页！","提示",MB_OK);
					return FALSE;
				}
				else
					score_now--;
				for(i=0;i<(score_now-1)*6;i++)//将page_head移到当前页的第一项
					page_head=page_head->next;
				
				if(score_now==page)//如果在最后一页，则计算最后一页记录数量
					print=sum-(page-1)*6;
				else//否则，记录总数为6
					print=6;
				//清空编辑框内容
					SetWindowText(EDIT_id1,"");
					SetWindowText(EDIT_id2,"");
					SetWindowText(EDIT_id3,"");
					SetWindowText(EDIT_id4,"");
					SetWindowText(EDIT_id5,"");
					SetWindowText(EDIT_id6,"");
					SetWindowText(EDIT_name1,"");
					SetWindowText(EDIT_name2,"");
					SetWindowText(EDIT_name3,"");
					SetWindowText(EDIT_name4,"");
					SetWindowText(EDIT_name5,"");
					SetWindowText(EDIT_name6,"");
					SetWindowText(EDIT_paper_score1,"");
					SetWindowText(EDIT_paper_score2,"");
					SetWindowText(EDIT_paper_score3,"");
					SetWindowText(EDIT_paper_score4,"");
					SetWindowText(EDIT_paper_score5,"");
					SetWindowText(EDIT_paper_score6,"");
					SetWindowText(EDIT_usual_score1,"");
					SetWindowText(EDIT_usual_score2,"");
					SetWindowText(EDIT_usual_score3,"");
					SetWindowText(EDIT_usual_score4,"");
					SetWindowText(EDIT_usual_score5,"");
					SetWindowText(EDIT_usual_score6,"");
					SetWindowText(EDIT_subject1,"");
					SetWindowText(EDIT_subject2,"");
					SetWindowText(EDIT_subject3,"");
					SetWindowText(EDIT_subject4,"");
					SetWindowText(EDIT_subject5,"");
					SetWindowText(EDIT_subject6,"");
					SetWindowText(EDIT_makeup_score1,"");
					SetWindowText(EDIT_makeup_score2,"");
					SetWindowText(EDIT_makeup_score3,"");
					SetWindowText(EDIT_makeup_score4,"");
					SetWindowText(EDIT_makeup_score5,"");
					SetWindowText(EDIT_makeup_score6,"");
					SetWindowText(EDIT_score1,"");
					SetWindowText(EDIT_score2,"");
					SetWindowText(EDIT_score3,"");
					SetWindowText(EDIT_score4,"");
					SetWindowText(EDIT_score5,"");
					SetWindowText(EDIT_score6,"");
					SetWindowText(EDIT_grade1,"");
					SetWindowText(EDIT_grade2,"");
					SetWindowText(EDIT_grade3,"");
					SetWindowText(EDIT_grade4,"");
					SetWindowText(EDIT_grade5,"");
					SetWindowText(EDIT_grade6,"");
					SetWindowText(EDIT_term1,"");
					SetWindowText(EDIT_term2,"");
					SetWindowText(EDIT_term3,"");
					SetWindowText(EDIT_term4,"");
					SetWindowText(EDIT_term5,"");
					SetWindowText(EDIT_term6,"");
				if(print>=1)
				{
					itoa(page_head->paper_score,paper_score1,10);
					itoa(page_head->usual_score,usual_score1,10);
					itoa(page_head->makeup_score,makeup_score1,10);
					itoa(page_head->score,score1,10);
					SetWindowText(EDIT_id1,page_head->id);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_subject1,page_head->subject);
					SetWindowText(EDIT_grade1,page_head->grade);
					SetWindowText(EDIT_term1,page_head->term);
					SetWindowText(EDIT_paper_score1,paper_score1);
					SetWindowText(EDIT_usual_score1,usual_score1);
					SetWindowText(EDIT_makeup_score1,makeup_score1);
					SetWindowText(EDIT_score1,score1);
					page_head=page_head->next;
				}
				if(print>=2)
				{
					itoa(page_head->paper_score,paper_score2,10);
					itoa(page_head->usual_score,usual_score2,10);
					itoa(page_head->makeup_score,makeup_score2,10);
					itoa(page_head->score,score2,10);
					SetWindowText(EDIT_id2,page_head->id);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_subject2,page_head->subject);
					SetWindowText(EDIT_grade2,page_head->grade);
					SetWindowText(EDIT_term2,page_head->term);
					SetWindowText(EDIT_paper_score2,paper_score2);
					SetWindowText(EDIT_usual_score2,usual_score2);
					SetWindowText(EDIT_makeup_score2,makeup_score2);
					SetWindowText(EDIT_score2,score2);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					itoa(page_head->paper_score,paper_score3,10);
					itoa(page_head->usual_score,usual_score3,10);
					itoa(page_head->makeup_score,makeup_score3,10);
					itoa(page_head->score,score3,10);
					SetWindowText(EDIT_id3,page_head->id);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_subject3,page_head->subject);
					SetWindowText(EDIT_grade3,page_head->grade);
					SetWindowText(EDIT_term3,page_head->term);
					SetWindowText(EDIT_paper_score3,paper_score3);
					SetWindowText(EDIT_usual_score3,usual_score3);
					SetWindowText(EDIT_makeup_score3,makeup_score3);
					SetWindowText(EDIT_score3,score3);
					page_head=page_head->next;
				}
				if(print>=4)
				{
					itoa(page_head->paper_score,paper_score4,10);
					itoa(page_head->usual_score,usual_score4,10);
					itoa(page_head->makeup_score,makeup_score4,10);
					itoa(page_head->score,score4,10);
					SetWindowText(EDIT_id4,page_head->id);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_subject4,page_head->subject);
					SetWindowText(EDIT_grade4,page_head->grade);
					SetWindowText(EDIT_term4,page_head->term);
					SetWindowText(EDIT_paper_score4,paper_score4);
					SetWindowText(EDIT_usual_score4,usual_score4);
					SetWindowText(EDIT_makeup_score4,makeup_score4);
					SetWindowText(EDIT_score4,score4);
					page_head=page_head->next;
				}
				if(print>=5)
				{
					itoa(page_head->paper_score,paper_score5,10);
					itoa(page_head->usual_score,usual_score5,10);
					itoa(page_head->makeup_score,makeup_score5,10);
					itoa(page_head->score,score5,10);
					SetWindowText(EDIT_id5,page_head->id);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_subject5,page_head->subject);
					SetWindowText(EDIT_grade5,page_head->grade);
					SetWindowText(EDIT_term5,page_head->term);
					SetWindowText(EDIT_paper_score5,paper_score5);
					SetWindowText(EDIT_usual_score5,usual_score5);
					SetWindowText(EDIT_makeup_score5,makeup_score5);
					SetWindowText(EDIT_score5,score5);
					page_head=page_head->next;
				}
				if(print>=6)
				{
					itoa(page_head->paper_score,paper_score6,10);
					itoa(page_head->usual_score,usual_score6,10);
					itoa(page_head->makeup_score,makeup_score6,10);
					itoa(page_head->score,score6,10);
					SetWindowText(EDIT_id6,page_head->id);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_subject6,page_head->subject);
					SetWindowText(EDIT_grade6,page_head->grade);
					SetWindowText(EDIT_term6,page_head->term);
					SetWindowText(EDIT_paper_score6,paper_score6);
					SetWindowText(EDIT_usual_score6,usual_score6);
					SetWindowText(EDIT_makeup_score6,makeup_score6);
					SetWindowText(EDIT_score6,score6);
					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				itoa(score_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"页，共");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_score_inquire_next:
				if(score_ck!=1)
				{
					MessageBox(NULL,"请点击“返回顶部”显示第一页学院信息！","提示",MB_OK);
					break;
				}
				page_head=score_head->next->next;//移到记录第一页第一条记录
				if(score_now+1>page)//如果当前页+1等于总页数，弹出警告
				{
					MessageBox(NULL,"已经到最后一页！","提示",MB_OK);
					return FALSE;
				}
				else//否则，跳转页数
				{
					score_now++;
				}
				for(i=0;i<(score_now-1)*6;i++)//将page_head移到当前页的第一项
					page_head=page_head->next;
				
				if(score_now==page)//如果在最后一页，则计算最后一页记录数量
					print=sum-(page-1)*6;
				else//否则，记录总数为6
					print=6;
				//清空编辑框内容
					SetWindowText(EDIT_id1,"");
					SetWindowText(EDIT_id2,"");
					SetWindowText(EDIT_id3,"");
					SetWindowText(EDIT_id4,"");
					SetWindowText(EDIT_id5,"");
					SetWindowText(EDIT_id6,"");
					SetWindowText(EDIT_name1,"");
					SetWindowText(EDIT_name2,"");
					SetWindowText(EDIT_name3,"");
					SetWindowText(EDIT_name4,"");
					SetWindowText(EDIT_name5,"");
					SetWindowText(EDIT_name6,"");
					SetWindowText(EDIT_paper_score1,"");
					SetWindowText(EDIT_paper_score2,"");
					SetWindowText(EDIT_paper_score3,"");
					SetWindowText(EDIT_paper_score4,"");
					SetWindowText(EDIT_paper_score5,"");
					SetWindowText(EDIT_paper_score6,"");
					SetWindowText(EDIT_usual_score1,"");
					SetWindowText(EDIT_usual_score2,"");
					SetWindowText(EDIT_usual_score3,"");
					SetWindowText(EDIT_usual_score4,"");
					SetWindowText(EDIT_usual_score5,"");
					SetWindowText(EDIT_usual_score6,"");
					SetWindowText(EDIT_subject1,"");
					SetWindowText(EDIT_subject2,"");
					SetWindowText(EDIT_subject3,"");
					SetWindowText(EDIT_subject4,"");
					SetWindowText(EDIT_subject5,"");
					SetWindowText(EDIT_subject6,"");
					SetWindowText(EDIT_makeup_score1,"");
					SetWindowText(EDIT_makeup_score2,"");
					SetWindowText(EDIT_makeup_score3,"");
					SetWindowText(EDIT_makeup_score4,"");
					SetWindowText(EDIT_makeup_score5,"");
					SetWindowText(EDIT_makeup_score6,"");
					SetWindowText(EDIT_score1,"");
					SetWindowText(EDIT_score2,"");
					SetWindowText(EDIT_score3,"");
					SetWindowText(EDIT_score4,"");
					SetWindowText(EDIT_score5,"");
					SetWindowText(EDIT_score6,"");
					SetWindowText(EDIT_grade1,"");
					SetWindowText(EDIT_grade2,"");
					SetWindowText(EDIT_grade3,"");
					SetWindowText(EDIT_grade4,"");
					SetWindowText(EDIT_grade5,"");
					SetWindowText(EDIT_grade6,"");
					SetWindowText(EDIT_term1,"");
					SetWindowText(EDIT_term2,"");
					SetWindowText(EDIT_term3,"");
					SetWindowText(EDIT_term4,"");
					SetWindowText(EDIT_term5,"");
					SetWindowText(EDIT_term6,"");
				if(print>=1)
				{
					itoa(page_head->paper_score,paper_score1,10);
					itoa(page_head->usual_score,usual_score1,10);
					itoa(page_head->makeup_score,makeup_score1,10);
					itoa(page_head->score,score1,10);
					SetWindowText(EDIT_id1,page_head->id);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_subject1,page_head->subject);
					SetWindowText(EDIT_grade1,page_head->grade);
					SetWindowText(EDIT_term1,page_head->term);
					SetWindowText(EDIT_paper_score1,paper_score1);
					SetWindowText(EDIT_usual_score1,usual_score1);
					SetWindowText(EDIT_makeup_score1,makeup_score1);
					SetWindowText(EDIT_score1,score1);
					page_head=page_head->next;
				}
				if(print>=2)
				{
					itoa(page_head->paper_score,paper_score2,10);
					itoa(page_head->usual_score,usual_score2,10);
					itoa(page_head->makeup_score,makeup_score2,10);
					itoa(page_head->score,score2,10);
					SetWindowText(EDIT_id2,page_head->id);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_subject2,page_head->subject);
					SetWindowText(EDIT_grade2,page_head->grade);
					SetWindowText(EDIT_term2,page_head->term);
					SetWindowText(EDIT_paper_score2,paper_score2);
					SetWindowText(EDIT_usual_score2,usual_score2);
					SetWindowText(EDIT_makeup_score2,makeup_score2);
					SetWindowText(EDIT_score2,score2);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					itoa(page_head->paper_score,paper_score3,10);
					itoa(page_head->usual_score,usual_score3,10);
					itoa(page_head->makeup_score,makeup_score3,10);
					itoa(page_head->score,score3,10);
					SetWindowText(EDIT_id3,page_head->id);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_subject3,page_head->subject);
					SetWindowText(EDIT_grade3,page_head->grade);
					SetWindowText(EDIT_term3,page_head->term);
					SetWindowText(EDIT_paper_score3,paper_score3);
					SetWindowText(EDIT_usual_score3,usual_score3);
					SetWindowText(EDIT_makeup_score3,makeup_score3);
					SetWindowText(EDIT_score3,score3);
					page_head=page_head->next;
				}
				if(print>=4)
				{
					itoa(page_head->paper_score,paper_score4,10);
					itoa(page_head->usual_score,usual_score4,10);
					itoa(page_head->makeup_score,makeup_score4,10);
					itoa(page_head->score,score4,10);
					SetWindowText(EDIT_id4,page_head->id);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_subject4,page_head->subject);
					SetWindowText(EDIT_grade4,page_head->grade);
					SetWindowText(EDIT_term4,page_head->term);
					SetWindowText(EDIT_paper_score4,paper_score4);
					SetWindowText(EDIT_usual_score4,usual_score4);
					SetWindowText(EDIT_makeup_score4,makeup_score4);
					SetWindowText(EDIT_score4,score4);
					page_head=page_head->next;
				}
				if(print>=5)
				{
					itoa(page_head->paper_score,paper_score5,10);
					itoa(page_head->usual_score,usual_score5,10);
					itoa(page_head->makeup_score,makeup_score5,10);
					itoa(page_head->score,score5,10);
					SetWindowText(EDIT_id5,page_head->id);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_subject5,page_head->subject);
					SetWindowText(EDIT_grade5,page_head->grade);
					SetWindowText(EDIT_term5,page_head->term);
					SetWindowText(EDIT_paper_score5,paper_score5);
					SetWindowText(EDIT_usual_score5,usual_score5);
					SetWindowText(EDIT_makeup_score5,makeup_score5);
					SetWindowText(EDIT_score5,score5);
					page_head=page_head->next;
				}
				if(print>=6)
				{
					itoa(page_head->paper_score,paper_score6,10);
					itoa(page_head->usual_score,usual_score6,10);
					itoa(page_head->makeup_score,makeup_score6,10);
					itoa(page_head->score,score6,10);
					SetWindowText(EDIT_id6,page_head->id);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_subject6,page_head->subject);
					SetWindowText(EDIT_grade6,page_head->grade);
					SetWindowText(EDIT_term6,page_head->term);
					SetWindowText(EDIT_paper_score6,paper_score6);
					SetWindowText(EDIT_usual_score6,usual_score6);
					SetWindowText(EDIT_makeup_score6,makeup_score6);
					SetWindowText(EDIT_score6,score6);
					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				
				itoa(score_now,item,10);

				strcat(char_page,item);
				
				strcat(char_page,"页，共");
				itoa(page,item,10);//转换整形为字符型
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_score_inquire_exit:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
				break;
			}
			break;
		case WM_CLOSE:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
	}
    return FALSE;

}
//IDD_a_score_modification窗口回调函数

	int find_a_score_modification;//1.找到=2.找到学科，3.找到学期，4.找到账号，5.未找到
	int state_a_score_modification;//修改状态提示
	//int add_score;//增添信息合法，1.学院合法,2.班级合法other.不合法
	char score_item[50];
	char score_term[50];
	char score_subject[50];
	score_List score_modification_p,score_new_info,score_old_info;
	score_List score_delete;
LRESULT CALLBACK	A_SCORE_MODIFICATION(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	college_List college_p;
	class_List class_p;
	HWND EDIT_oldid,EDIT_newid;
	HWND EDIT_oldname,EDIT_newname;
	HWND EDIT_oldterm,EDIT_newterm;
	HWND EDIT_oldmakeup_score,EDIT_newmakeup_score;
	HWND EDIT_oldsubject,EDIT_newsubject;
	HWND EDIT_oldpaper_score,EDIT_newpaper_score;
	HWND EDIT_oldusual_score,EDIT_newusual_score;
	HWND EDIT_oldscore,EDIT_newscore;
	HWND EDIT_oldcollege,EDIT_newcollege;
	HWND EDIT_oldprofession,EDIT_newprofession;
	HWND EDIT_oldgrade,EDIT_newgrade;
	char old_paper_score[10],old_usual_score[10],old_makeup_score[10],oldscore[10];
	char new_paper_score[10],new_usual_score[10],new_makeup_score[10],newscore[10];
	char message_a_score_modification[60];
	char *stop;//为strtol定义的终止字符指针
	int id;
	int i;
	double paper_score,usual_score,makeup_score,score;
	score_head=(score_List)malloc(sizeof(score_Lnode));
	score_load(score_head);

	EDIT_oldid=GetDlgItem(hDlg,EDIT_a_score_modification_oldid);
	EDIT_oldname=GetDlgItem(hDlg,EDIT_a_score_modification_oldname);
	EDIT_oldterm=GetDlgItem(hDlg,EDIT_a_score_modification_oldterm);
	EDIT_oldmakeup_score=GetDlgItem(hDlg,EDIT_a_score_modification_oldmakeup_score);
	EDIT_oldsubject=GetDlgItem(hDlg,EDIT_a_score_modification_oldsubject);
	EDIT_oldpaper_score=GetDlgItem(hDlg,EDIT_a_score_modification_oldpaper_score);
	EDIT_oldusual_score=GetDlgItem(hDlg,EDIT_a_score_modification_oldusual_score);
	EDIT_oldscore=GetDlgItem(hDlg,EDIT_a_score_modification_oldscore);
	EDIT_oldcollege=GetDlgItem(hDlg,EDIT_a_score_modification_oldcollege);
	EDIT_oldprofession=GetDlgItem(hDlg,EDIT_a_score_modification_oldprofession);
	EDIT_oldgrade=GetDlgItem(hDlg,EDIT_a_score_modification_oldgrade);
	
	EDIT_newid=GetDlgItem(hDlg,EDIT_a_score_modification_newid);
	EDIT_newname=GetDlgItem(hDlg,EDIT_a_score_modification_newname);
	EDIT_newterm=GetDlgItem(hDlg,EDIT_a_score_modification_newterm);
	EDIT_newmakeup_score=GetDlgItem(hDlg,EDIT_a_score_modification_newmakeup_score);
	EDIT_newsubject=GetDlgItem(hDlg,EDIT_a_score_modification_newsubject);
	EDIT_newpaper_score=GetDlgItem(hDlg,EDIT_a_score_modification_newpaper_score);
	EDIT_newusual_score=GetDlgItem(hDlg,EDIT_a_score_modification_newusual_score);
 	EDIT_newscore=GetDlgItem(hDlg,EDIT_a_score_modification_newscore);
	EDIT_newcollege=GetDlgItem(hDlg,EDIT_a_score_modification_newcollege);
	EDIT_newprofession=GetDlgItem(hDlg,EDIT_a_score_modification_newprofession);
	EDIT_newgrade=GetDlgItem(hDlg,EDIT_a_score_modification_newgrade);
	
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			//通过信息定位成绩
			case BUTTON_a_score_modification_location:
				find_a_score_modification=5;
				GetWindowText(EDIT_oldid,score_item,GetWindowTextLength(EDIT_oldid)+1);
				GetWindowText(EDIT_oldterm,score_term,GetWindowTextLength(EDIT_oldterm)+1);
				GetWindowText(EDIT_oldsubject,score_subject,GetWindowTextLength(EDIT_oldsubject)+1);
				score_modification_p=score_head->next->next;
				while(score_modification_p)
				{
					if(strcmp(score_modification_p->id,score_item)==0)
					{
						find_a_score_modification=4;
						if(strcmp(score_modification_p->term,score_term)==0)
						{
							find_a_score_modification=3;
							if(strcmp(score_modification_p->subject,score_subject)==0)
							{
								find_a_score_modification=2;
								score_old_info=(score_List)malloc(sizeof(score_Lnode));
								strcpy(score_old_info->id,score_modification_p->id);
								strcpy(score_old_info->name,score_modification_p->name);
								strcpy(score_old_info->term,score_modification_p->term);
								score_old_info->makeup_score=score_modification_p->makeup_score;
								strcpy(score_old_info->subject,score_modification_p->subject);
								score_old_info->paper_score=score_modification_p->paper_score;
								score_old_info->score=score_modification_p->score;
								score_old_info->usual_score=score_modification_p->usual_score;
								strcpy(score_old_info->college,score_modification_p->college);
								strcpy(score_old_info->profession,score_modification_p->profession);
								strcpy(score_old_info->grade,score_modification_p->grade);
								score_old_info->num=score_modification_p->num;
								find_a_score_modification=1;
								break;
							}
							if(find_a_score_modification==3)
							{
								score_modification_p=score_modification_p->next;
								//find_a_score_modification=5;
								continue;
							}
						}
						if(find_a_score_modification==4)
						{
								score_modification_p=score_modification_p->next;
								//find_a_score_modification=5;
								continue;
						}
					}
					if(find_a_score_modification==5)
						{
								score_modification_p=score_modification_p->next;
								//find_a_score_modification=5;
								continue;
						}
				}
				if(find_a_score_modification==5)
				{
					MessageBox(NULL,"账号输入有误！","ERROR!",MB_OK);
					break;
					return FALSE;
				}
				if(find_a_score_modification==4)
				{
					MessageBox(NULL,"学期输入有误！","ERROR!",MB_OK);
					break;
					return FALSE;
				}
				if(find_a_score_modification==3)
				{
					MessageBox(NULL,"科目输入有误！","ERROR!",MB_OK);
					break;
					return FALSE;
				}
				SetWindowText(EDIT_oldid,score_old_info->id);
				SetWindowText(EDIT_oldname,score_old_info->name);
				SetWindowText(EDIT_oldterm,score_old_info->term);			
				SetWindowText(EDIT_oldsubject,score_old_info->subject);	
				SetWindowText(EDIT_oldcollege,score_old_info->college);
				SetWindowText(EDIT_oldprofession,score_old_info->profession);
				SetWindowText(EDIT_oldgrade,score_old_info->grade);
				itoa(score_old_info->paper_score,old_paper_score,10);
				itoa(score_old_info->usual_score,old_usual_score,10);
				itoa(score_old_info->makeup_score,old_makeup_score,10);
				itoa(score_old_info->score,oldscore,10);
				SetWindowText(EDIT_oldmakeup_score,old_makeup_score);
				SetWindowText(EDIT_oldpaper_score,old_paper_score);
				SetWindowText(EDIT_oldusual_score,old_usual_score);
				SetWindowText(EDIT_oldscore,oldscore);

				SetWindowText(EDIT_newid,score_old_info->id);
				SetWindowText(EDIT_newname,score_old_info->name);
				SetWindowText(EDIT_newterm,score_old_info->term);			
				SetWindowText(EDIT_newsubject,score_old_info->subject);	
				SetWindowText(EDIT_newcollege,score_old_info->college);
				SetWindowText(EDIT_newprofession,score_old_info->profession);
				SetWindowText(EDIT_newgrade,score_old_info->grade);
				itoa(score_old_info->paper_score,old_paper_score,10);
				itoa(score_old_info->usual_score,old_usual_score,10);
				itoa(score_old_info->makeup_score,old_makeup_score,10);
				itoa(score_old_info->score,oldscore,10);
				SetWindowText(EDIT_newmakeup_score,old_makeup_score);
				SetWindowText(EDIT_newpaper_score,old_paper_score);
				SetWindowText(EDIT_newusual_score,old_usual_score);
				SetWindowText(EDIT_newscore,oldscore);

				state_a_score_modification=1;//修改状态为修改
				MessageBox(NULL,"定位成功！请修改数据或删除数据。修改完毕按“确认修改”保存！","ERROR!",MB_OK);
				break;
			case BUTTON_a_score_modification_prior:
				if(find_a_score_modification!=1)
				{
					MessageBox(NULL,"记录定位失败！操作非法！","ERROR!",MB_OK);
					return FALSE;
				}
				if(score_modification_p->num==1)
				{
					MessageBox(NULL,"前方没有更多记录！","ERROR!",MB_OK);
					return FALSE;
				}
				score_modification_p=score_modification_p->prior;
				SetWindowText(EDIT_oldid,score_modification_p->id);
				SetWindowText(EDIT_oldname,score_modification_p->name);
				SetWindowText(EDIT_oldterm,score_modification_p->term);			
				SetWindowText(EDIT_oldsubject,score_modification_p->subject);	
				SetWindowText(EDIT_oldcollege,score_modification_p->college);
				SetWindowText(EDIT_oldprofession,score_modification_p->profession);
				SetWindowText(EDIT_oldgrade,score_modification_p->grade);
				itoa(score_modification_p->paper_score,old_paper_score,10);
				itoa(score_modification_p->usual_score,old_usual_score,10);
				itoa(score_modification_p->makeup_score,old_makeup_score,10);
				itoa(score_modification_p->score,oldscore,10);
				SetWindowText(EDIT_oldmakeup_score,old_makeup_score);
				SetWindowText(EDIT_oldpaper_score,old_paper_score);
				SetWindowText(EDIT_oldusual_score,old_usual_score);
				SetWindowText(EDIT_oldscore,oldscore);

				SetWindowText(EDIT_newid,score_modification_p->id);
				SetWindowText(EDIT_newname,score_modification_p->name);
				SetWindowText(EDIT_newterm,score_modification_p->term);			
				SetWindowText(EDIT_newsubject,score_modification_p->subject);	
				SetWindowText(EDIT_newcollege,score_modification_p->college);
				SetWindowText(EDIT_newprofession,score_modification_p->profession);
				SetWindowText(EDIT_newgrade,score_modification_p->grade);
				itoa(score_modification_p->paper_score,old_paper_score,10);
				itoa(score_modification_p->usual_score,old_usual_score,10);
				itoa(score_modification_p->makeup_score,old_makeup_score,10);
				itoa(score_modification_p->score,oldscore,10);
				SetWindowText(EDIT_newmakeup_score,old_makeup_score);
				SetWindowText(EDIT_newpaper_score,old_paper_score);
				SetWindowText(EDIT_newusual_score,old_usual_score);
				SetWindowText(EDIT_newscore,oldscore);
				score_old_info->num=score_modification_p->num;
				break;
			case BUTTON_a_score_modification_next:
				if(find_a_score_modification!=1)
				{
					MessageBox(NULL,"记录定位失败！操作非法！","ERROR!",MB_OK);
					return FALSE;
				}
				if(score_modification_p->num==score_head->next->num)
				{
					MessageBox(NULL,"后方没有更多记录！","ERROR!",MB_OK);
					return FALSE;
				}
				score_modification_p=score_modification_p->next;
				SetWindowText(EDIT_oldid,score_modification_p->id);
				SetWindowText(EDIT_oldname,score_modification_p->name);
				SetWindowText(EDIT_oldterm,score_modification_p->term);			
				SetWindowText(EDIT_oldsubject,score_modification_p->subject);	
				SetWindowText(EDIT_oldcollege,score_modification_p->college);
				SetWindowText(EDIT_oldprofession,score_modification_p->profession);
				SetWindowText(EDIT_oldgrade,score_modification_p->grade);
				itoa(score_modification_p->paper_score,old_paper_score,10);
				itoa(score_modification_p->usual_score,old_usual_score,10);
				itoa(score_modification_p->makeup_score,old_makeup_score,10);
				itoa(score_modification_p->score,oldscore,10);
				SetWindowText(EDIT_oldmakeup_score,old_makeup_score);
				SetWindowText(EDIT_oldpaper_score,old_paper_score);
				SetWindowText(EDIT_oldusual_score,old_usual_score);
				SetWindowText(EDIT_oldscore,oldscore);

				SetWindowText(EDIT_newid,score_modification_p->id);
				SetWindowText(EDIT_newname,score_modification_p->name);
				SetWindowText(EDIT_newterm,score_modification_p->term);			
				SetWindowText(EDIT_newsubject,score_modification_p->subject);	
				SetWindowText(EDIT_newcollege,score_modification_p->college);
				SetWindowText(EDIT_newprofession,score_modification_p->profession);
				SetWindowText(EDIT_newgrade,score_modification_p->grade);
				itoa(score_modification_p->paper_score,old_paper_score,10);
				itoa(score_modification_p->usual_score,old_usual_score,10);
				itoa(score_modification_p->makeup_score,old_makeup_score,10);
				itoa(score_modification_p->score,oldscore,10);
				SetWindowText(EDIT_newmakeup_score,old_makeup_score);
				SetWindowText(EDIT_newpaper_score,old_paper_score);
				SetWindowText(EDIT_newusual_score,old_usual_score);
				SetWindowText(EDIT_newscore,oldscore);
				score_old_info->num=score_modification_p->num;
				break;
			//确认修改
			case BUTTON_a_score_modification_affirm:
				if(find_a_score_modification!=1)
				{
					MessageBox(NULL,"记录定位失败！操作非法！","ERROR!",MB_OK);
					return FALSE;
				}
				score_new_info=(score_List)malloc(sizeof(score_Lnode));
				GetWindowText(EDIT_newpaper_score,new_paper_score,GetWindowTextLength(EDIT_newpaper_score)+1);
				GetWindowText(EDIT_newusual_score,new_usual_score,GetWindowTextLength(EDIT_newusual_score)+1);
				GetWindowText(EDIT_newmakeup_score,new_makeup_score,GetWindowTextLength(EDIT_newmakeup_score)+1);
				if((strcmp(new_paper_score,"100")!=0)&&(strcmp(new_paper_score,"00")<0||strcmp(new_paper_score,"99")>0))
				{
					MessageBox(NULL,"请以百分制输入卷面成绩！","警告",MB_OK);
					itoa(score_old_info->paper_score,new_paper_score,10);
					SetWindowText(EDIT_newpaper_score,new_paper_score);
					return FALSE;
				}
				if((strcmp(new_paper_score,"100")!=0)&&(strcmp(new_usual_score,"00")<0||strcmp(new_usual_score,"99")>0))
				{
					MessageBox(NULL,"请以百分制输入平时成绩！","警告",MB_OK);
					itoa(score_old_info->usual_score,new_usual_score,10);
					SetWindowText(EDIT_newusual_score,new_usual_score);
					return FALSE;
				}
				if((strcmp(new_makeup_score,"100")!=0)&&(strcmp(new_makeup_score,"-1")!=0)&&((strcmp(new_makeup_score,"00")<0||strcmp(new_makeup_score,"99")>0)))
				{
					MessageBox(NULL,"请以百分制输入补考成绩！\n无补考记录记为“-1”","警告",MB_OK);
					itoa(score_old_info->makeup_score,new_makeup_score,10);
					SetWindowText(EDIT_newmakeup_score,new_makeup_score);
					return FALSE;
				}
				score_modification_p=score_head->next;
				for(i=0;i<score_old_info->num;i++)
					score_modification_p=score_modification_p->next;
				paper_score=strtod(new_paper_score,NULL);
				usual_score=strtod(new_usual_score,NULL);
				makeup_score=strtod(new_makeup_score,NULL);

			    score_modification_p->paper_score=atoi(new_paper_score);
				score_modification_p->usual_score=atoi(new_usual_score);
				score_modification_p->makeup_score=atoi(new_makeup_score);
				if(score_modification_p->makeup_score==-1)
				{
					score_modification_p->score=paper_score*0.7+usual_score*0.3;
				}
				else
				{
					score_modification_p->score=makeup_score*0.7+usual_score*0.3;
				}
				score_save(score_head);
				score_load(score_head);
				MessageBox(NULL,"修改成功！","警告",MB_OK);
				SetWindowText(EDIT_oldid,score_modification_p->id);
				SetWindowText(EDIT_oldname,score_modification_p->name);
				SetWindowText(EDIT_oldterm,score_modification_p->term);			
				SetWindowText(EDIT_oldsubject,score_modification_p->subject);	
				SetWindowText(EDIT_oldcollege,score_modification_p->college);
				SetWindowText(EDIT_oldprofession,score_modification_p->profession);
				SetWindowText(EDIT_oldgrade,score_modification_p->grade);
				itoa(score_modification_p->paper_score,old_paper_score,10);
				itoa(score_modification_p->usual_score,old_usual_score,10);
				itoa(score_modification_p->makeup_score,old_makeup_score,10);
				itoa(score_modification_p->score,oldscore,10);
				SetWindowText(EDIT_oldmakeup_score,old_makeup_score);
				SetWindowText(EDIT_oldpaper_score,old_paper_score);
				SetWindowText(EDIT_oldusual_score,old_usual_score);
				SetWindowText(EDIT_oldscore,oldscore);

				SetWindowText(EDIT_newid,score_modification_p->id);
				SetWindowText(EDIT_newname,score_modification_p->name);
				SetWindowText(EDIT_newterm,score_modification_p->term);			
				SetWindowText(EDIT_newsubject,score_modification_p->subject);	
				SetWindowText(EDIT_newcollege,score_modification_p->college);
				SetWindowText(EDIT_newprofession,score_modification_p->profession);
				SetWindowText(EDIT_newgrade,score_modification_p->grade);
				itoa(score_modification_p->paper_score,old_paper_score,10);
				itoa(score_modification_p->usual_score,old_usual_score,10);
				itoa(score_modification_p->makeup_score,old_makeup_score,10);
				itoa(score_modification_p->score,oldscore,10);
				SetWindowText(EDIT_newmakeup_score,old_makeup_score);
				SetWindowText(EDIT_newpaper_score,old_paper_score);
				SetWindowText(EDIT_newusual_score,old_usual_score);
				SetWindowText(EDIT_newscore,oldscore);
				break;
			//删除学生
			case BUTTON_a_score_modification_delete:
				if(find_a_score_modification==1)
				{
				strcpy(message_a_score_modification,"确认删除学生：“");
				strcat(message_a_score_modification,score_old_info->name);
				strcat(message_a_score_modification,"”的本次成绩记录吗？");
				if(MessageBox(NULL,message_a_score_modification,"警告",MB_YESNO|MB_ICONEXCLAMATION)!=6)
				{
					return FALSE;
				}
				score_modification_p=score_head->next;
				for(i=0;i<score_old_info->num;i++)
					score_modification_p=score_modification_p->next;
				score_delete=score_modification_p;
				while(score_delete)
				{
					score_delete->num--;
					score_delete=score_delete->next;
				}
				if(score_head->next->num==1)
				{
					score_head->next=NULL;
					free(score_modification_p);
				}
				else if(score_modification_p->num==score_head->next->num-1)
				{
					score_modification_p->prior->next=score_modification_p->next;
				}
				else if(score_modification_p->num==1)
				{
					score_modification_p->next->prior=score_modification_p->prior;
				}
				else
				{
					score_modification_p->next->prior=score_modification_p->prior;
					score_modification_p->prior->next=score_modification_p->next;
				}
				free(score_modification_p);
				score_head->next->num--;
				score_save(score_head);
				score_load(score_head);
				SetWindowText(EDIT_oldid,"");
				SetWindowText(EDIT_oldname,"");
				SetWindowText(EDIT_oldterm,"");
				SetWindowText(EDIT_oldmakeup_score,"");
				SetWindowText(EDIT_oldsubject,"");
				SetWindowText(EDIT_oldpaper_score,"");
				SetWindowText(EDIT_oldusual_score,"");
				SetWindowText(EDIT_oldscore,"");
				SetWindowText(EDIT_oldcollege,"");
				SetWindowText(EDIT_oldprofession,"");
				SetWindowText(EDIT_oldgrade,"");

				SetWindowText(EDIT_newid,"");
				SetWindowText(EDIT_newname,"");
				SetWindowText(EDIT_newterm,"");
				SetWindowText(EDIT_newmakeup_score,"");
				SetWindowText(EDIT_newsubject,"");
				SetWindowText(EDIT_newpaper_score,"");
				SetWindowText(EDIT_newusual_score,"");
				SetWindowText(EDIT_newcollege,"");
				SetWindowText(EDIT_newprofession,"");
				SetWindowText(EDIT_newgrade,"");
				SetWindowText(EDIT_newscore,"");
				MessageBox(NULL,"删除成功！","警告",MB_OK);
				find_a_score_modification=0;
				break;
				}
				MessageBox(NULL,"非法操作！","警告",MB_OK);
				break;
			case BUTTON_a_score_modification_exit:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}
			break;
		case WM_CLOSE:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
	}
    return FALSE;

}
//IDD_a_score_self_inquir窗口回调函数
	int score_self_ck; //标记是否初始化内容，1.是，0.否
	int score_self_now;
LRESULT CALLBACK	A_SCORE_SELF_INQUIRE(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,sum,page,print;//sum.资料总数 page.总页数 now.当前页数 print.当前页资料总数
	score_List page_head;
	char paper_score1[10],paper_score2[10],paper_score3[10],paper_score4[10],paper_score5[10],paper_score6[10];
	char usual_score1[10],usual_score2[10],usual_score3[10],usual_score4[10],usual_score5[10],usual_score6[10];
	char makeup_score1[10],makeup_score2[10],makeup_score3[10],makeup_score4[10],makeup_score5[10],makeup_score6[10];
	char score1[10],score2[10],score3[10],score4[10],score5[10],score6[10];
	char char_page[30],item[10];
	char id[50];
	HWND EDIT_id;
	HWND EDIT_id1,EDIT_id2,EDIT_id3,EDIT_id4,EDIT_id5,EDIT_id6;
	HWND EDIT_name1,EDIT_name2,EDIT_name3,EDIT_name4,EDIT_name5,EDIT_name6;
	HWND EDIT_paper_score1,EDIT_paper_score2,EDIT_paper_score3,EDIT_paper_score4,EDIT_paper_score5,EDIT_paper_score6;
	HWND EDIT_usual_score1,EDIT_usual_score2,EDIT_usual_score3,EDIT_usual_score4,EDIT_usual_score5,EDIT_usual_score6;
	HWND EDIT_makeup_score1,EDIT_makeup_score2,EDIT_makeup_score3,EDIT_makeup_score4,EDIT_makeup_score5,EDIT_makeup_score6;
	HWND EDIT_score1,EDIT_score2,EDIT_score3,EDIT_score4,EDIT_score5,EDIT_score6;
	HWND EDIT_subject1,EDIT_subject2,EDIT_subject3,EDIT_subject4,EDIT_subject5,EDIT_subject6;
	HWND EDIT_term1,EDIT_term2,EDIT_term3,EDIT_term4,EDIT_term5,EDIT_term6;
	HWND EDIT_grade1,EDIT_grade2,EDIT_grade3,EDIT_grade4,EDIT_grade5,EDIT_grade6;
	HWND EDIT_page;
	
	EDIT_id=GetDlgItem(hDlg,EDIT_a_score_self_inquire_id);
	EDIT_id1=GetDlgItem(hDlg,EDIT_a_score_self_inquire_id1);
	EDIT_id2=GetDlgItem(hDlg,EDIT_a_score_self_inquire_id2);
	EDIT_id3=GetDlgItem(hDlg,EDIT_a_score_self_inquire_id3);
	EDIT_id4=GetDlgItem(hDlg,EDIT_a_score_self_inquire_id4);
	EDIT_id5=GetDlgItem(hDlg,EDIT_a_score_self_inquire_id5);
	EDIT_id6=GetDlgItem(hDlg,EDIT_a_score_self_inquire_id6);
	EDIT_name1=GetDlgItem(hDlg,EDIT_a_score_self_inquire_name1);
	EDIT_name2=GetDlgItem(hDlg,EDIT_a_score_self_inquire_name2);
	EDIT_name3=GetDlgItem(hDlg,EDIT_a_score_self_inquire_name3);
	EDIT_name4=GetDlgItem(hDlg,EDIT_a_score_self_inquire_name4);
	EDIT_name5=GetDlgItem(hDlg,EDIT_a_score_self_inquire_name5);
	EDIT_name6=GetDlgItem(hDlg,EDIT_a_score_self_inquire_name6);
	EDIT_paper_score1=GetDlgItem(hDlg,EDIT_a_score_self_inquire_paper_score1);
	EDIT_paper_score2=GetDlgItem(hDlg,EDIT_a_score_self_inquire_paper_score2);
	EDIT_paper_score3=GetDlgItem(hDlg,EDIT_a_score_self_inquire_paper_score3);
	EDIT_paper_score4=GetDlgItem(hDlg,EDIT_a_score_self_inquire_paper_score4);
	EDIT_paper_score5=GetDlgItem(hDlg,EDIT_a_score_self_inquire_paper_score5);
	EDIT_paper_score6=GetDlgItem(hDlg,EDIT_a_score_self_inquire_paper_score6);
	EDIT_usual_score1=GetDlgItem(hDlg,EDIT_a_score_self_inquire_usual_score1);
	EDIT_usual_score2=GetDlgItem(hDlg,EDIT_a_score_self_inquire_usual_score2);
	EDIT_usual_score3=GetDlgItem(hDlg,EDIT_a_score_self_inquire_usual_score3);
	EDIT_usual_score4=GetDlgItem(hDlg,EDIT_a_score_self_inquire_usual_score4);
	EDIT_usual_score5=GetDlgItem(hDlg,EDIT_a_score_self_inquire_usual_score5);
	EDIT_usual_score6=GetDlgItem(hDlg,EDIT_a_score_self_inquire_usual_score6);
	EDIT_subject1=GetDlgItem(hDlg,EDIT_a_score_self_inquire_subject1);
	EDIT_subject2=GetDlgItem(hDlg,EDIT_a_score_self_inquire_subject2);
	EDIT_subject3=GetDlgItem(hDlg,EDIT_a_score_self_inquire_subject3);
	EDIT_subject4=GetDlgItem(hDlg,EDIT_a_score_self_inquire_subject4);
	EDIT_subject5=GetDlgItem(hDlg,EDIT_a_score_self_inquire_subject5);
	EDIT_subject6=GetDlgItem(hDlg,EDIT_a_score_self_inquire_subject6);
	EDIT_makeup_score1=GetDlgItem(hDlg,EDIT_a_score_self_inquire_makeup_score1);
	EDIT_makeup_score2=GetDlgItem(hDlg,EDIT_a_score_self_inquire_makeup_score2);
	EDIT_makeup_score3=GetDlgItem(hDlg,EDIT_a_score_self_inquire_makeup_score3);
	EDIT_makeup_score4=GetDlgItem(hDlg,EDIT_a_score_self_inquire_makeup_score4);
	EDIT_makeup_score5=GetDlgItem(hDlg,EDIT_a_score_self_inquire_makeup_score5);
	EDIT_makeup_score6=GetDlgItem(hDlg,EDIT_a_score_self_inquire_makeup_score6);
	EDIT_score1=GetDlgItem(hDlg,EDIT_a_score_self_inquire_score1);
	EDIT_score2=GetDlgItem(hDlg,EDIT_a_score_self_inquire_score2);
	EDIT_score3=GetDlgItem(hDlg,EDIT_a_score_self_inquire_score3);
	EDIT_score4=GetDlgItem(hDlg,EDIT_a_score_self_inquire_score4);
	EDIT_score5=GetDlgItem(hDlg,EDIT_a_score_self_inquire_score5);
	EDIT_score6=GetDlgItem(hDlg,EDIT_a_score_self_inquire_score6);
	EDIT_grade1=GetDlgItem(hDlg,EDIT_a_score_self_inquire_grade1);
	EDIT_grade2=GetDlgItem(hDlg,EDIT_a_score_self_inquire_grade2);
	EDIT_grade3=GetDlgItem(hDlg,EDIT_a_score_self_inquire_grade3);
	EDIT_grade4=GetDlgItem(hDlg,EDIT_a_score_self_inquire_grade4);
	EDIT_grade5=GetDlgItem(hDlg,EDIT_a_score_self_inquire_grade5);
	EDIT_grade6=GetDlgItem(hDlg,EDIT_a_score_self_inquire_grade6);
	EDIT_term1=GetDlgItem(hDlg,EDIT_a_score_self_inquire_term1);
	EDIT_term2=GetDlgItem(hDlg,EDIT_a_score_self_inquire_term2);
	EDIT_term3=GetDlgItem(hDlg,EDIT_a_score_self_inquire_term3);
	EDIT_term4=GetDlgItem(hDlg,EDIT_a_score_self_inquire_term4);
	EDIT_term5=GetDlgItem(hDlg,EDIT_a_score_self_inquire_term5);
	EDIT_term6=GetDlgItem(hDlg,EDIT_a_score_self_inquire_term6);
	EDIT_page=GetDlgItem(hDlg,EDIT_a_score_self_inquire_page);
	
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case BUTTON_a_score_self_inquire_top:
				score_head=(score_List)malloc(sizeof(score_Lnode));
				score_load(score_head);
				GetWindowText(EDIT_id,id,GetWindowTextLength(EDIT_id)+1);
				page_head=score_head->next;
				sum=0;
				while(page_head)
				{
					if(strcmp(page_head->id,id)==0)
						sum++;
					page_head=page_head->next;
				}
				page=sum/6;
				if(sum%6!=0)
					page++;
				if(sum==0)
				{
					MessageBox(NULL,"未找到该学生任何成绩记录！","ERROR!",MB_OK);
					return FALSE;
				}
				score_self_ck=1;
				score_self_now=1;
				if(sum>=6)
					print=6;//若总资料数不小于6，则第一页显示6条数据
				if(sum<6)
					print=sum;//若资料总数小于6，则第一页显示全部sum条数据
				page_head=score_head->next;//指向第一页第一条记录
				if(print>=1)
				{
					while(page_head)
					{
						if(strcmp(page_head->id,id)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score1,10);
					itoa(page_head->usual_score,usual_score1,10);
					itoa(page_head->makeup_score,makeup_score1,10);
					itoa(page_head->score,score1,10);
					SetWindowText(EDIT_id1,page_head->id);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_subject1,page_head->subject);
					SetWindowText(EDIT_grade1,page_head->grade);
					SetWindowText(EDIT_term1,page_head->term);
					SetWindowText(EDIT_paper_score1,paper_score1);
					SetWindowText(EDIT_usual_score1,usual_score1);
					SetWindowText(EDIT_makeup_score1,makeup_score1);
					SetWindowText(EDIT_score1,score1);
					page_head=page_head->next;
				}
				if(print>=2)
				{
					while(page_head)
					{
						if(strcmp(page_head->id,id)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score2,10);
					itoa(page_head->usual_score,usual_score2,10);
					itoa(page_head->makeup_score,makeup_score2,10);
					itoa(page_head->score,score2,10);
					SetWindowText(EDIT_id2,page_head->id);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_subject2,page_head->subject);
					SetWindowText(EDIT_grade2,page_head->grade);
					SetWindowText(EDIT_term2,page_head->term);
					SetWindowText(EDIT_paper_score2,paper_score2);
					SetWindowText(EDIT_usual_score2,usual_score2);
					SetWindowText(EDIT_makeup_score2,makeup_score2);
					SetWindowText(EDIT_score2,score2);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					while(page_head)
					{
						if(strcmp(page_head->id,id)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score3,10);
					itoa(page_head->usual_score,usual_score3,10);
					itoa(page_head->makeup_score,makeup_score3,10);
					itoa(page_head->score,score3,10);
					SetWindowText(EDIT_id3,page_head->id);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_subject3,page_head->subject);
					SetWindowText(EDIT_grade3,page_head->grade);
					SetWindowText(EDIT_term3,page_head->term);
					SetWindowText(EDIT_paper_score3,paper_score3);
					SetWindowText(EDIT_usual_score3,usual_score3);
					SetWindowText(EDIT_makeup_score3,makeup_score3);
					SetWindowText(EDIT_score3,score3);
					page_head=page_head->next;
				}
				if(print>=4)
				{
					while(page_head)
					{
						if(strcmp(page_head->id,id)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score4,10);
					itoa(page_head->usual_score,usual_score4,10);
					itoa(page_head->makeup_score,makeup_score4,10);
					itoa(page_head->score,score4,10);
					SetWindowText(EDIT_id4,page_head->id);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_subject4,page_head->subject);
					SetWindowText(EDIT_grade4,page_head->grade);
					SetWindowText(EDIT_term4,page_head->term);
					SetWindowText(EDIT_paper_score4,paper_score4);
					SetWindowText(EDIT_usual_score4,usual_score4);
					SetWindowText(EDIT_makeup_score4,makeup_score4);
					SetWindowText(EDIT_score4,score4);
					page_head=page_head->next;
				}
				if(print>=5)
				{
					while(page_head)
					{
						if(strcmp(page_head->id,id)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score5,10);
					itoa(page_head->usual_score,usual_score5,10);
					itoa(page_head->makeup_score,makeup_score5,10);
					itoa(page_head->score,score5,10);
					SetWindowText(EDIT_id5,page_head->id);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_subject5,page_head->subject);
					SetWindowText(EDIT_grade5,page_head->grade);
					SetWindowText(EDIT_term5,page_head->term);
					SetWindowText(EDIT_paper_score5,paper_score5);
					SetWindowText(EDIT_usual_score5,usual_score5);
					SetWindowText(EDIT_makeup_score5,makeup_score5);
					SetWindowText(EDIT_score5,score5);
					page_head=page_head->next;
				}
				if(print>=6)
				{
					while(page_head)
					{
						if(strcmp(page_head->id,id)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score6,10);
					itoa(page_head->usual_score,usual_score6,10);
					itoa(page_head->makeup_score,makeup_score6,10);
					itoa(page_head->score,score6,10);
					SetWindowText(EDIT_id6,page_head->id);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_subject6,page_head->subject);
					SetWindowText(EDIT_grade6,page_head->grade);
					SetWindowText(EDIT_term6,page_head->term);
					SetWindowText(EDIT_paper_score6,paper_score6);
					SetWindowText(EDIT_usual_score6,usual_score6);
					SetWindowText(EDIT_makeup_score6,makeup_score6);
					SetWindowText(EDIT_score6,score6);
					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				itoa(score_self_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"页，共");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				break;
			case BUTTON_a_score_self_inquire_prior:
				if(score_self_ck!=1)
				{
					MessageBox(NULL,"请点击“返回顶部”显示第一页成绩信息！","提示",MB_OK);
					break;
				}
				page_head=score_head->next->next;
				if(score_self_now-1<=0)
				{
					MessageBox(NULL,"已经到第一页！","提示",MB_OK);
					return FALSE;
				}
				else
					score_self_now--;
				for(i=0;i<(score_self_now-1)*6;i++)//将page_head移到当前页的第一项
					page_head=page_head->next;
				
				if(score_self_now==page)//如果在最后一页，则计算最后一页记录数量
					print=sum-(page-1)*6;
				else//否则，记录总数为6
					print=6;
				//清空编辑框内容
					SetWindowText(EDIT_id1,"");
					SetWindowText(EDIT_id2,"");
					SetWindowText(EDIT_id3,"");
					SetWindowText(EDIT_id4,"");
					SetWindowText(EDIT_id5,"");
					SetWindowText(EDIT_id6,"");
					SetWindowText(EDIT_name1,"");
					SetWindowText(EDIT_name2,"");
					SetWindowText(EDIT_name3,"");
					SetWindowText(EDIT_name4,"");
					SetWindowText(EDIT_name5,"");
					SetWindowText(EDIT_name6,"");
					SetWindowText(EDIT_paper_score1,"");
					SetWindowText(EDIT_paper_score2,"");
					SetWindowText(EDIT_paper_score3,"");
					SetWindowText(EDIT_paper_score4,"");
					SetWindowText(EDIT_paper_score5,"");
					SetWindowText(EDIT_paper_score6,"");
					SetWindowText(EDIT_usual_score1,"");
					SetWindowText(EDIT_usual_score2,"");
					SetWindowText(EDIT_usual_score3,"");
					SetWindowText(EDIT_usual_score4,"");
					SetWindowText(EDIT_usual_score5,"");
					SetWindowText(EDIT_usual_score6,"");
					SetWindowText(EDIT_subject1,"");
					SetWindowText(EDIT_subject2,"");
					SetWindowText(EDIT_subject3,"");
					SetWindowText(EDIT_subject4,"");
					SetWindowText(EDIT_subject5,"");
					SetWindowText(EDIT_subject6,"");
					SetWindowText(EDIT_makeup_score1,"");
					SetWindowText(EDIT_makeup_score2,"");
					SetWindowText(EDIT_makeup_score3,"");
					SetWindowText(EDIT_makeup_score4,"");
					SetWindowText(EDIT_makeup_score5,"");
					SetWindowText(EDIT_makeup_score6,"");
					SetWindowText(EDIT_score1,"");
					SetWindowText(EDIT_score2,"");
					SetWindowText(EDIT_score3,"");
					SetWindowText(EDIT_score4,"");
					SetWindowText(EDIT_score5,"");
					SetWindowText(EDIT_score6,"");
					SetWindowText(EDIT_grade1,"");
					SetWindowText(EDIT_grade2,"");
					SetWindowText(EDIT_grade3,"");
					SetWindowText(EDIT_grade4,"");
					SetWindowText(EDIT_grade5,"");
					SetWindowText(EDIT_grade6,"");
					SetWindowText(EDIT_term1,"");
					SetWindowText(EDIT_term2,"");
					SetWindowText(EDIT_term3,"");
					SetWindowText(EDIT_term4,"");
					SetWindowText(EDIT_term5,"");
					SetWindowText(EDIT_term6,"");
				if(print>=1)
				{
					while(page_head)
					{
						if(strcmp(page_head->id,id)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score1,10);
					itoa(page_head->usual_score,usual_score1,10);
					itoa(page_head->makeup_score,makeup_score1,10);
					itoa(page_head->score,score1,10);
					SetWindowText(EDIT_id1,page_head->id);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_subject1,page_head->subject);
					SetWindowText(EDIT_grade1,page_head->grade);
					SetWindowText(EDIT_term1,page_head->term);
					SetWindowText(EDIT_paper_score1,paper_score1);
					SetWindowText(EDIT_usual_score1,usual_score1);
					SetWindowText(EDIT_makeup_score1,makeup_score1);
					SetWindowText(EDIT_score1,score1);
					page_head=page_head->next;
				}
				if(print>=2)
				{
					while(page_head)
					{
						if(strcmp(page_head->id,id)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score2,10);
					itoa(page_head->usual_score,usual_score2,10);
					itoa(page_head->makeup_score,makeup_score2,10);
					itoa(page_head->score,score2,10);
					SetWindowText(EDIT_id2,page_head->id);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_subject2,page_head->subject);
					SetWindowText(EDIT_grade2,page_head->grade);
					SetWindowText(EDIT_term2,page_head->term);
					SetWindowText(EDIT_paper_score2,paper_score2);
					SetWindowText(EDIT_usual_score2,usual_score2);
					SetWindowText(EDIT_makeup_score2,makeup_score2);
					SetWindowText(EDIT_score2,score2);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					while(page_head)
					{
						if(strcmp(page_head->id,id)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score3,10);
					itoa(page_head->usual_score,usual_score3,10);
					itoa(page_head->makeup_score,makeup_score3,10);
					itoa(page_head->score,score3,10);
					SetWindowText(EDIT_id3,page_head->id);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_subject3,page_head->subject);
					SetWindowText(EDIT_grade3,page_head->grade);
					SetWindowText(EDIT_term3,page_head->term);
					SetWindowText(EDIT_paper_score3,paper_score3);
					SetWindowText(EDIT_usual_score3,usual_score3);
					SetWindowText(EDIT_makeup_score3,makeup_score3);
					SetWindowText(EDIT_score3,score3);
					page_head=page_head->next;
				}
				if(print>=4)
				{
					while(page_head)
					{
						if(strcmp(page_head->id,id)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score4,10);
					itoa(page_head->usual_score,usual_score4,10);
					itoa(page_head->makeup_score,makeup_score4,10);
					itoa(page_head->score,score4,10);
					SetWindowText(EDIT_id4,page_head->id);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_subject4,page_head->subject);
					SetWindowText(EDIT_grade4,page_head->grade);
					SetWindowText(EDIT_term4,page_head->term);
					SetWindowText(EDIT_paper_score4,paper_score4);
					SetWindowText(EDIT_usual_score4,usual_score4);
					SetWindowText(EDIT_makeup_score4,makeup_score4);
					SetWindowText(EDIT_score4,score4);
					page_head=page_head->next;
				}
				if(print>=5)
				{
					while(page_head)
					{
						if(strcmp(page_head->id,id)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score5,10);
					itoa(page_head->usual_score,usual_score5,10);
					itoa(page_head->makeup_score,makeup_score5,10);
					itoa(page_head->score,score5,10);
					SetWindowText(EDIT_id5,page_head->id);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_subject5,page_head->subject);
					SetWindowText(EDIT_grade5,page_head->grade);
					SetWindowText(EDIT_term5,page_head->term);
					SetWindowText(EDIT_paper_score5,paper_score5);
					SetWindowText(EDIT_usual_score5,usual_score5);
					SetWindowText(EDIT_makeup_score5,makeup_score5);
					SetWindowText(EDIT_score5,score5);
					page_head=page_head->next;
				}
				if(print>=6)
				{
					while(page_head)
					{
						if(strcmp(page_head->id,id)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score6,10);
					itoa(page_head->usual_score,usual_score6,10);
					itoa(page_head->makeup_score,makeup_score6,10);
					itoa(page_head->score,score6,10);
					SetWindowText(EDIT_id6,page_head->id);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_subject6,page_head->subject);
					SetWindowText(EDIT_grade6,page_head->grade);
					SetWindowText(EDIT_term6,page_head->term);
					SetWindowText(EDIT_paper_score6,paper_score6);
					SetWindowText(EDIT_usual_score6,usual_score6);
					SetWindowText(EDIT_makeup_score6,makeup_score6);
					SetWindowText(EDIT_score6,score6);
					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				itoa(score_self_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"页，共");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_score_self_inquire_next:
				if(score_self_ck!=1)
				{
					MessageBox(NULL,"请点击“返回顶部”显示第一页学院信息！","提示",MB_OK);
					break;
				}
				page_head=score_head->next->next;//移到记录第一页第一条记录
				if(score_self_now+1>page)//如果当前页+1等于总页数，弹出警告
				{
					MessageBox(NULL,"已经到最后一页！","提示",MB_OK);
					return FALSE;
				}
				else//否则，跳转页数
				{
					score_self_now++;
				}
				for(i=0;i<(score_self_now-1)*6;i++)//将page_head移到当前页的第一项
					page_head=page_head->next;
				
				if(score_self_now==page)//如果在最后一页，则计算最后一页记录数量
					print=sum-(page-1)*6;
				else//否则，记录总数为6
					print=6;
				//清空编辑框内容
					SetWindowText(EDIT_id1,"");
					SetWindowText(EDIT_id2,"");
					SetWindowText(EDIT_id3,"");
					SetWindowText(EDIT_id4,"");
					SetWindowText(EDIT_id5,"");
					SetWindowText(EDIT_id6,"");
					SetWindowText(EDIT_name1,"");
					SetWindowText(EDIT_name2,"");
					SetWindowText(EDIT_name3,"");
					SetWindowText(EDIT_name4,"");
					SetWindowText(EDIT_name5,"");
					SetWindowText(EDIT_name6,"");
					SetWindowText(EDIT_paper_score1,"");
					SetWindowText(EDIT_paper_score2,"");
					SetWindowText(EDIT_paper_score3,"");
					SetWindowText(EDIT_paper_score4,"");
					SetWindowText(EDIT_paper_score5,"");
					SetWindowText(EDIT_paper_score6,"");
					SetWindowText(EDIT_usual_score1,"");
					SetWindowText(EDIT_usual_score2,"");
					SetWindowText(EDIT_usual_score3,"");
					SetWindowText(EDIT_usual_score4,"");
					SetWindowText(EDIT_usual_score5,"");
					SetWindowText(EDIT_usual_score6,"");
					SetWindowText(EDIT_subject1,"");
					SetWindowText(EDIT_subject2,"");
					SetWindowText(EDIT_subject3,"");
					SetWindowText(EDIT_subject4,"");
					SetWindowText(EDIT_subject5,"");
					SetWindowText(EDIT_subject6,"");
					SetWindowText(EDIT_makeup_score1,"");
					SetWindowText(EDIT_makeup_score2,"");
					SetWindowText(EDIT_makeup_score3,"");
					SetWindowText(EDIT_makeup_score4,"");
					SetWindowText(EDIT_makeup_score5,"");
					SetWindowText(EDIT_makeup_score6,"");
					SetWindowText(EDIT_score1,"");
					SetWindowText(EDIT_score2,"");
					SetWindowText(EDIT_score3,"");
					SetWindowText(EDIT_score4,"");
					SetWindowText(EDIT_score5,"");
					SetWindowText(EDIT_score6,"");
					SetWindowText(EDIT_grade1,"");
					SetWindowText(EDIT_grade2,"");
					SetWindowText(EDIT_grade3,"");
					SetWindowText(EDIT_grade4,"");
					SetWindowText(EDIT_grade5,"");
					SetWindowText(EDIT_grade6,"");
					SetWindowText(EDIT_term1,"");
					SetWindowText(EDIT_term2,"");
					SetWindowText(EDIT_term3,"");
					SetWindowText(EDIT_term4,"");
					SetWindowText(EDIT_term5,"");
					SetWindowText(EDIT_term6,"");
				if(print>=1)
				{
					while(page_head)
					{
						if(strcmp(page_head->id,id)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score1,10);
					itoa(page_head->usual_score,usual_score1,10);
					itoa(page_head->makeup_score,makeup_score1,10);
					itoa(page_head->score,score1,10);
					SetWindowText(EDIT_id1,page_head->id);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_subject1,page_head->subject);
					SetWindowText(EDIT_grade1,page_head->grade);
					SetWindowText(EDIT_term1,page_head->term);
					SetWindowText(EDIT_paper_score1,paper_score1);
					SetWindowText(EDIT_usual_score1,usual_score1);
					SetWindowText(EDIT_makeup_score1,makeup_score1);
					SetWindowText(EDIT_score1,score1);
					page_head=page_head->next;
				}
				if(print>=2)
				{
					while(page_head)
					{
						if(strcmp(page_head->id,id)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score2,10);
					itoa(page_head->usual_score,usual_score2,10);
					itoa(page_head->makeup_score,makeup_score2,10);
					itoa(page_head->score,score2,10);
					SetWindowText(EDIT_id2,page_head->id);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_subject2,page_head->subject);
					SetWindowText(EDIT_grade2,page_head->grade);
					SetWindowText(EDIT_term2,page_head->term);
					SetWindowText(EDIT_paper_score2,paper_score2);
					SetWindowText(EDIT_usual_score2,usual_score2);
					SetWindowText(EDIT_makeup_score2,makeup_score2);
					SetWindowText(EDIT_score2,score2);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					while(page_head)
					{
						if(strcmp(page_head->id,id)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score3,10);
					itoa(page_head->usual_score,usual_score3,10);
					itoa(page_head->makeup_score,makeup_score3,10);
					itoa(page_head->score,score3,10);
					SetWindowText(EDIT_id3,page_head->id);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_subject3,page_head->subject);
					SetWindowText(EDIT_grade3,page_head->grade);
					SetWindowText(EDIT_term3,page_head->term);
					SetWindowText(EDIT_paper_score3,paper_score3);
					SetWindowText(EDIT_usual_score3,usual_score3);
					SetWindowText(EDIT_makeup_score3,makeup_score3);
					SetWindowText(EDIT_score3,score3);
					page_head=page_head->next;
				}
				if(print>=4)
				{
					while(page_head)
					{
						if(strcmp(page_head->id,id)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score4,10);
					itoa(page_head->usual_score,usual_score4,10);
					itoa(page_head->makeup_score,makeup_score4,10);
					itoa(page_head->score,score4,10);
					SetWindowText(EDIT_id4,page_head->id);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_subject4,page_head->subject);
					SetWindowText(EDIT_grade4,page_head->grade);
					SetWindowText(EDIT_term4,page_head->term);
					SetWindowText(EDIT_paper_score4,paper_score4);
					SetWindowText(EDIT_usual_score4,usual_score4);
					SetWindowText(EDIT_makeup_score4,makeup_score4);
					SetWindowText(EDIT_score4,score4);
					page_head=page_head->next;
				}
				if(print>=5)
				{
					while(page_head)
					{
						if(strcmp(page_head->id,id)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score5,10);
					itoa(page_head->usual_score,usual_score5,10);
					itoa(page_head->makeup_score,makeup_score5,10);
					itoa(page_head->score,score5,10);
					SetWindowText(EDIT_id5,page_head->id);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_subject5,page_head->subject);
					SetWindowText(EDIT_grade5,page_head->grade);
					SetWindowText(EDIT_term5,page_head->term);
					SetWindowText(EDIT_paper_score5,paper_score5);
					SetWindowText(EDIT_usual_score5,usual_score5);
					SetWindowText(EDIT_makeup_score5,makeup_score5);
					SetWindowText(EDIT_score5,score5);
					page_head=page_head->next;
				}
				if(print>=6)
				{
					while(page_head)
					{
						if(strcmp(page_head->id,id)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score6,10);
					itoa(page_head->usual_score,usual_score6,10);
					itoa(page_head->makeup_score,makeup_score6,10);
					itoa(page_head->score,score6,10);
					SetWindowText(EDIT_id6,page_head->id);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_subject6,page_head->subject);
					SetWindowText(EDIT_grade6,page_head->grade);
					SetWindowText(EDIT_term6,page_head->term);
					SetWindowText(EDIT_paper_score6,paper_score6);
					SetWindowText(EDIT_usual_score6,usual_score6);
					SetWindowText(EDIT_makeup_score6,makeup_score6);
					SetWindowText(EDIT_score6,score6);
					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				
				itoa(score_self_now,item,10);

				strcat(char_page,item);
				
				strcat(char_page,"页，共");
				itoa(page,item,10);//转换整形为字符型
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_score_self_inquire_exit:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
				break;
			}
			break;
		case WM_CLOSE:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
	}
    return FALSE;

}
//IDD_a_score_term_inquir窗口回调函数
	int score_term_ck; //标记是否初始化内容，1.是，0.否
	int score_term_now;
LRESULT CALLBACK	A_SCORE_TERM_INQUIRE(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,sum,page,print;//sum.资料总数 page.总页数 now.当前页数 print.当前页资料总数
	score_List page_head;
	char paper_score1[10],paper_score2[10],paper_score3[10],paper_score4[10],paper_score5[10],paper_score6[10];
	char usual_score1[10],usual_score2[10],usual_score3[10],usual_score4[10],usual_score5[10],usual_score6[10];
	char makeup_score1[10],makeup_score2[10],makeup_score3[10],makeup_score4[10],makeup_score5[10],makeup_score6[10];
	char score1[10],score2[10],score3[10],score4[10],score5[10],score6[10];
	char char_page[30],item[10];
	char grade[50];
	HWND EDIT_grade;
	HWND EDIT_id1,EDIT_id2,EDIT_id3,EDIT_id4,EDIT_id5,EDIT_id6;
	HWND EDIT_name1,EDIT_name2,EDIT_name3,EDIT_name4,EDIT_name5,EDIT_name6;
	HWND EDIT_paper_score1,EDIT_paper_score2,EDIT_paper_score3,EDIT_paper_score4,EDIT_paper_score5,EDIT_paper_score6;
	HWND EDIT_usual_score1,EDIT_usual_score2,EDIT_usual_score3,EDIT_usual_score4,EDIT_usual_score5,EDIT_usual_score6;
	HWND EDIT_makeup_score1,EDIT_makeup_score2,EDIT_makeup_score3,EDIT_makeup_score4,EDIT_makeup_score5,EDIT_makeup_score6;
	HWND EDIT_score1,EDIT_score2,EDIT_score3,EDIT_score4,EDIT_score5,EDIT_score6;
	HWND EDIT_subject1,EDIT_subject2,EDIT_subject3,EDIT_subject4,EDIT_subject5,EDIT_subject6;
	HWND EDIT_term1,EDIT_term2,EDIT_term3,EDIT_term4,EDIT_term5,EDIT_term6;
	HWND EDIT_grade1,EDIT_grade2,EDIT_grade3,EDIT_grade4,EDIT_grade5,EDIT_grade6;
	HWND EDIT_page;
	
	EDIT_grade=GetDlgItem(hDlg,EDIT_a_score_term_inquire_grade);
	EDIT_id1=GetDlgItem(hDlg,EDIT_a_score_term_inquire_id1);
	EDIT_id2=GetDlgItem(hDlg,EDIT_a_score_term_inquire_id2);
	EDIT_id3=GetDlgItem(hDlg,EDIT_a_score_term_inquire_id3);
	EDIT_id4=GetDlgItem(hDlg,EDIT_a_score_term_inquire_id4);
	EDIT_id5=GetDlgItem(hDlg,EDIT_a_score_term_inquire_id5);
	EDIT_id6=GetDlgItem(hDlg,EDIT_a_score_term_inquire_id6);
	EDIT_name1=GetDlgItem(hDlg,EDIT_a_score_term_inquire_name1);
	EDIT_name2=GetDlgItem(hDlg,EDIT_a_score_term_inquire_name2);
	EDIT_name3=GetDlgItem(hDlg,EDIT_a_score_term_inquire_name3);
	EDIT_name4=GetDlgItem(hDlg,EDIT_a_score_term_inquire_name4);
	EDIT_name5=GetDlgItem(hDlg,EDIT_a_score_term_inquire_name5);
	EDIT_name6=GetDlgItem(hDlg,EDIT_a_score_term_inquire_name6);
	EDIT_paper_score1=GetDlgItem(hDlg,EDIT_a_score_term_inquire_paper_score1);
	EDIT_paper_score2=GetDlgItem(hDlg,EDIT_a_score_term_inquire_paper_score2);
	EDIT_paper_score3=GetDlgItem(hDlg,EDIT_a_score_term_inquire_paper_score3);
	EDIT_paper_score4=GetDlgItem(hDlg,EDIT_a_score_term_inquire_paper_score4);
	EDIT_paper_score5=GetDlgItem(hDlg,EDIT_a_score_term_inquire_paper_score5);
	EDIT_paper_score6=GetDlgItem(hDlg,EDIT_a_score_term_inquire_paper_score6);
	EDIT_usual_score1=GetDlgItem(hDlg,EDIT_a_score_term_inquire_usual_score1);
	EDIT_usual_score2=GetDlgItem(hDlg,EDIT_a_score_term_inquire_usual_score2);
	EDIT_usual_score3=GetDlgItem(hDlg,EDIT_a_score_term_inquire_usual_score3);
	EDIT_usual_score4=GetDlgItem(hDlg,EDIT_a_score_term_inquire_usual_score4);
	EDIT_usual_score5=GetDlgItem(hDlg,EDIT_a_score_term_inquire_usual_score5);
	EDIT_usual_score6=GetDlgItem(hDlg,EDIT_a_score_term_inquire_usual_score6);
	EDIT_subject1=GetDlgItem(hDlg,EDIT_a_score_term_inquire_subject1);
	EDIT_subject2=GetDlgItem(hDlg,EDIT_a_score_term_inquire_subject2);
	EDIT_subject3=GetDlgItem(hDlg,EDIT_a_score_term_inquire_subject3);
	EDIT_subject4=GetDlgItem(hDlg,EDIT_a_score_term_inquire_subject4);
	EDIT_subject5=GetDlgItem(hDlg,EDIT_a_score_term_inquire_subject5);
	EDIT_subject6=GetDlgItem(hDlg,EDIT_a_score_term_inquire_subject6);
	EDIT_makeup_score1=GetDlgItem(hDlg,EDIT_a_score_term_inquire_makeup_score1);
	EDIT_makeup_score2=GetDlgItem(hDlg,EDIT_a_score_term_inquire_makeup_score2);
	EDIT_makeup_score3=GetDlgItem(hDlg,EDIT_a_score_term_inquire_makeup_score3);
	EDIT_makeup_score4=GetDlgItem(hDlg,EDIT_a_score_term_inquire_makeup_score4);
	EDIT_makeup_score5=GetDlgItem(hDlg,EDIT_a_score_term_inquire_makeup_score5);
	EDIT_makeup_score6=GetDlgItem(hDlg,EDIT_a_score_term_inquire_makeup_score6);
	EDIT_score1=GetDlgItem(hDlg,EDIT_a_score_term_inquire_score1);
	EDIT_score2=GetDlgItem(hDlg,EDIT_a_score_term_inquire_score2);
	EDIT_score3=GetDlgItem(hDlg,EDIT_a_score_term_inquire_score3);
	EDIT_score4=GetDlgItem(hDlg,EDIT_a_score_term_inquire_score4);
	EDIT_score5=GetDlgItem(hDlg,EDIT_a_score_term_inquire_score5);
	EDIT_score6=GetDlgItem(hDlg,EDIT_a_score_term_inquire_score6);
	EDIT_grade1=GetDlgItem(hDlg,EDIT_a_score_term_inquire_grade1);
	EDIT_grade2=GetDlgItem(hDlg,EDIT_a_score_term_inquire_grade2);
	EDIT_grade3=GetDlgItem(hDlg,EDIT_a_score_term_inquire_grade3);
	EDIT_grade4=GetDlgItem(hDlg,EDIT_a_score_term_inquire_grade4);
	EDIT_grade5=GetDlgItem(hDlg,EDIT_a_score_term_inquire_grade5);
	EDIT_grade6=GetDlgItem(hDlg,EDIT_a_score_term_inquire_grade6);
	EDIT_term1=GetDlgItem(hDlg,EDIT_a_score_term_inquire_term1);
	EDIT_term2=GetDlgItem(hDlg,EDIT_a_score_term_inquire_term2);
	EDIT_term3=GetDlgItem(hDlg,EDIT_a_score_term_inquire_term3);
	EDIT_term4=GetDlgItem(hDlg,EDIT_a_score_term_inquire_term4);
	EDIT_term5=GetDlgItem(hDlg,EDIT_a_score_term_inquire_term5);
	EDIT_term6=GetDlgItem(hDlg,EDIT_a_score_term_inquire_term6);
	EDIT_page=GetDlgItem(hDlg,EDIT_a_score_term_inquire_page);
	
	switch (message)
	{
		case WM_INITDIALOG:
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case BUTTON_a_score_term_inquire_top:
				score_head=(score_List)malloc(sizeof(score_Lnode));
				score_load(score_head);
				GetWindowText(EDIT_grade,grade,GetWindowTextLength(EDIT_grade)+1);
				page_head=score_head->next;
				sum=0;
				while(page_head)
				{
					if(strcmp(page_head->grade,grade)==0)
						sum++;
					page_head=page_head->next;
				}
				page=sum/6;
				if(sum%6!=0)
					page++;
				if(sum==0)
				{
					MessageBox(NULL,"未找到该学生任何成绩记录！","ERROR!",MB_OK);
					return FALSE;
				}
				score_term_ck=1;
				score_term_now=1;
				if(sum>=6)
					print=6;//若总资料数不小于6，则第一页显示6条数据
				if(sum<6)
					print=sum;//若资料总数小于6，则第一页显示全部sum条数据
				page_head=score_head->next;//指向第一页第一条记录
				if(print>=1)
				{
					while(page_head)
					{
						if(strcmp(page_head->grade,grade)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score1,10);
					itoa(page_head->usual_score,usual_score1,10);
					itoa(page_head->makeup_score,makeup_score1,10);
					itoa(page_head->score,score1,10);
					SetWindowText(EDIT_id1,page_head->id);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_subject1,page_head->subject);
					SetWindowText(EDIT_grade1,page_head->grade);
					SetWindowText(EDIT_term1,page_head->term);
					SetWindowText(EDIT_paper_score1,paper_score1);
					SetWindowText(EDIT_usual_score1,usual_score1);
					SetWindowText(EDIT_makeup_score1,makeup_score1);
					SetWindowText(EDIT_score1,score1);
					page_head=page_head->next;
				}
				if(print>=2)
				{
					while(page_head)
					{
						if(strcmp(page_head->grade,grade)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score2,10);
					itoa(page_head->usual_score,usual_score2,10);
					itoa(page_head->makeup_score,makeup_score2,10);
					itoa(page_head->score,score2,10);
					SetWindowText(EDIT_id2,page_head->id);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_subject2,page_head->subject);
					SetWindowText(EDIT_grade2,page_head->grade);
					SetWindowText(EDIT_term2,page_head->term);
					SetWindowText(EDIT_paper_score2,paper_score2);
					SetWindowText(EDIT_usual_score2,usual_score2);
					SetWindowText(EDIT_makeup_score2,makeup_score2);
					SetWindowText(EDIT_score2,score2);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					while(page_head)
					{
						if(strcmp(page_head->grade,grade)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score3,10);
					itoa(page_head->usual_score,usual_score3,10);
					itoa(page_head->makeup_score,makeup_score3,10);
					itoa(page_head->score,score3,10);
					SetWindowText(EDIT_id3,page_head->id);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_subject3,page_head->subject);
					SetWindowText(EDIT_grade3,page_head->grade);
					SetWindowText(EDIT_term3,page_head->term);
					SetWindowText(EDIT_paper_score3,paper_score3);
					SetWindowText(EDIT_usual_score3,usual_score3);
					SetWindowText(EDIT_makeup_score3,makeup_score3);
					SetWindowText(EDIT_score3,score3);
					page_head=page_head->next;
				}
				if(print>=4)
				{
					while(page_head)
					{
						if(strcmp(page_head->grade,grade)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score4,10);
					itoa(page_head->usual_score,usual_score4,10);
					itoa(page_head->makeup_score,makeup_score4,10);
					itoa(page_head->score,score4,10);
					SetWindowText(EDIT_id4,page_head->id);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_subject4,page_head->subject);
					SetWindowText(EDIT_grade4,page_head->grade);
					SetWindowText(EDIT_term4,page_head->term);
					SetWindowText(EDIT_paper_score4,paper_score4);
					SetWindowText(EDIT_usual_score4,usual_score4);
					SetWindowText(EDIT_makeup_score4,makeup_score4);
					SetWindowText(EDIT_score4,score4);
					page_head=page_head->next;
				}
				if(print>=5)
				{
					while(page_head)
					{
						if(strcmp(page_head->grade,grade)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score5,10);
					itoa(page_head->usual_score,usual_score5,10);
					itoa(page_head->makeup_score,makeup_score5,10);
					itoa(page_head->score,score5,10);
					SetWindowText(EDIT_id5,page_head->id);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_subject5,page_head->subject);
					SetWindowText(EDIT_grade5,page_head->grade);
					SetWindowText(EDIT_term5,page_head->term);
					SetWindowText(EDIT_paper_score5,paper_score5);
					SetWindowText(EDIT_usual_score5,usual_score5);
					SetWindowText(EDIT_makeup_score5,makeup_score5);
					SetWindowText(EDIT_score5,score5);
					page_head=page_head->next;
				}
				if(print>=6)
				{
					while(page_head)
					{
						if(strcmp(page_head->grade,grade)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score6,10);
					itoa(page_head->usual_score,usual_score6,10);
					itoa(page_head->makeup_score,makeup_score6,10);
					itoa(page_head->score,score6,10);
					SetWindowText(EDIT_id6,page_head->id);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_subject6,page_head->subject);
					SetWindowText(EDIT_grade6,page_head->grade);
					SetWindowText(EDIT_term6,page_head->term);
					SetWindowText(EDIT_paper_score6,paper_score6);
					SetWindowText(EDIT_usual_score6,usual_score6);
					SetWindowText(EDIT_makeup_score6,makeup_score6);
					SetWindowText(EDIT_score6,score6);
					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				itoa(score_term_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"页，共");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				break;
			case BUTTON_a_score_term_inquire_prior:
				if(score_term_ck!=1)
				{
					MessageBox(NULL,"请点击“返回顶部”显示第一页成绩信息！","提示",MB_OK);
					break;
				}
				page_head=score_head->next->next;
				if(score_term_now-1<=0)
				{
					MessageBox(NULL,"已经到第一页！","提示",MB_OK);
					return FALSE;
				}
				else
					score_term_now--;
				for(i=0;i<(score_term_now-1)*6;i++)//将page_head移到当前页的第一项
					page_head=page_head->next;
				
				if(score_term_now==page)//如果在最后一页，则计算最后一页记录数量
					print=sum-(page-1)*6;
				else//否则，记录总数为6
					print=6;
				//清空编辑框内容
					SetWindowText(EDIT_id1,"");
					SetWindowText(EDIT_id2,"");
					SetWindowText(EDIT_id3,"");
					SetWindowText(EDIT_id4,"");
					SetWindowText(EDIT_id5,"");
					SetWindowText(EDIT_id6,"");
					SetWindowText(EDIT_name1,"");
					SetWindowText(EDIT_name2,"");
					SetWindowText(EDIT_name3,"");
					SetWindowText(EDIT_name4,"");
					SetWindowText(EDIT_name5,"");
					SetWindowText(EDIT_name6,"");
					SetWindowText(EDIT_paper_score1,"");
					SetWindowText(EDIT_paper_score2,"");
					SetWindowText(EDIT_paper_score3,"");
					SetWindowText(EDIT_paper_score4,"");
					SetWindowText(EDIT_paper_score5,"");
					SetWindowText(EDIT_paper_score6,"");
					SetWindowText(EDIT_usual_score1,"");
					SetWindowText(EDIT_usual_score2,"");
					SetWindowText(EDIT_usual_score3,"");
					SetWindowText(EDIT_usual_score4,"");
					SetWindowText(EDIT_usual_score5,"");
					SetWindowText(EDIT_usual_score6,"");
					SetWindowText(EDIT_subject1,"");
					SetWindowText(EDIT_subject2,"");
					SetWindowText(EDIT_subject3,"");
					SetWindowText(EDIT_subject4,"");
					SetWindowText(EDIT_subject5,"");
					SetWindowText(EDIT_subject6,"");
					SetWindowText(EDIT_makeup_score1,"");
					SetWindowText(EDIT_makeup_score2,"");
					SetWindowText(EDIT_makeup_score3,"");
					SetWindowText(EDIT_makeup_score4,"");
					SetWindowText(EDIT_makeup_score5,"");
					SetWindowText(EDIT_makeup_score6,"");
					SetWindowText(EDIT_score1,"");
					SetWindowText(EDIT_score2,"");
					SetWindowText(EDIT_score3,"");
					SetWindowText(EDIT_score4,"");
					SetWindowText(EDIT_score5,"");
					SetWindowText(EDIT_score6,"");
					SetWindowText(EDIT_grade1,"");
					SetWindowText(EDIT_grade2,"");
					SetWindowText(EDIT_grade3,"");
					SetWindowText(EDIT_grade4,"");
					SetWindowText(EDIT_grade5,"");
					SetWindowText(EDIT_grade6,"");
					SetWindowText(EDIT_term1,"");
					SetWindowText(EDIT_term2,"");
					SetWindowText(EDIT_term3,"");
					SetWindowText(EDIT_term4,"");
					SetWindowText(EDIT_term5,"");
					SetWindowText(EDIT_term6,"");
				if(print>=1)
				{
					while(page_head)
					{
						if(strcmp(page_head->grade,grade)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score1,10);
					itoa(page_head->usual_score,usual_score1,10);
					itoa(page_head->makeup_score,makeup_score1,10);
					itoa(page_head->score,score1,10);
					SetWindowText(EDIT_id1,page_head->id);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_subject1,page_head->subject);
					SetWindowText(EDIT_grade1,page_head->grade);
					SetWindowText(EDIT_term1,page_head->term);
					SetWindowText(EDIT_paper_score1,paper_score1);
					SetWindowText(EDIT_usual_score1,usual_score1);
					SetWindowText(EDIT_makeup_score1,makeup_score1);
					SetWindowText(EDIT_score1,score1);
					page_head=page_head->next;
				}
				if(print>=2)
				{
					while(page_head)
					{
						if(strcmp(page_head->grade,grade)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score2,10);
					itoa(page_head->usual_score,usual_score2,10);
					itoa(page_head->makeup_score,makeup_score2,10);
					itoa(page_head->score,score2,10);
					SetWindowText(EDIT_id2,page_head->id);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_subject2,page_head->subject);
					SetWindowText(EDIT_grade2,page_head->grade);
					SetWindowText(EDIT_term2,page_head->term);
					SetWindowText(EDIT_paper_score2,paper_score2);
					SetWindowText(EDIT_usual_score2,usual_score2);
					SetWindowText(EDIT_makeup_score2,makeup_score2);
					SetWindowText(EDIT_score2,score2);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					while(page_head)
					{
						if(strcmp(page_head->grade,grade)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score3,10);
					itoa(page_head->usual_score,usual_score3,10);
					itoa(page_head->makeup_score,makeup_score3,10);
					itoa(page_head->score,score3,10);
					SetWindowText(EDIT_id3,page_head->id);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_subject3,page_head->subject);
					SetWindowText(EDIT_grade3,page_head->grade);
					SetWindowText(EDIT_term3,page_head->term);
					SetWindowText(EDIT_paper_score3,paper_score3);
					SetWindowText(EDIT_usual_score3,usual_score3);
					SetWindowText(EDIT_makeup_score3,makeup_score3);
					SetWindowText(EDIT_score3,score3);
					page_head=page_head->next;
				}
				if(print>=4)
				{
					while(page_head)
					{
						if(strcmp(page_head->grade,grade)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score4,10);
					itoa(page_head->usual_score,usual_score4,10);
					itoa(page_head->makeup_score,makeup_score4,10);
					itoa(page_head->score,score4,10);
					SetWindowText(EDIT_id4,page_head->id);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_subject4,page_head->subject);
					SetWindowText(EDIT_grade4,page_head->grade);
					SetWindowText(EDIT_term4,page_head->term);
					SetWindowText(EDIT_paper_score4,paper_score4);
					SetWindowText(EDIT_usual_score4,usual_score4);
					SetWindowText(EDIT_makeup_score4,makeup_score4);
					SetWindowText(EDIT_score4,score4);
					page_head=page_head->next;
				}
				if(print>=5)
				{
					while(page_head)
					{
						if(strcmp(page_head->grade,grade)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score5,10);
					itoa(page_head->usual_score,usual_score5,10);
					itoa(page_head->makeup_score,makeup_score5,10);
					itoa(page_head->score,score5,10);
					SetWindowText(EDIT_id5,page_head->id);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_subject5,page_head->subject);
					SetWindowText(EDIT_grade5,page_head->grade);
					SetWindowText(EDIT_term5,page_head->term);
					SetWindowText(EDIT_paper_score5,paper_score5);
					SetWindowText(EDIT_usual_score5,usual_score5);
					SetWindowText(EDIT_makeup_score5,makeup_score5);
					SetWindowText(EDIT_score5,score5);
					page_head=page_head->next;
				}
				if(print>=6)
				{
					while(page_head)
					{
						if(strcmp(page_head->grade,grade)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score6,10);
					itoa(page_head->usual_score,usual_score6,10);
					itoa(page_head->makeup_score,makeup_score6,10);
					itoa(page_head->score,score6,10);
					SetWindowText(EDIT_id6,page_head->id);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_subject6,page_head->subject);
					SetWindowText(EDIT_grade6,page_head->grade);
					SetWindowText(EDIT_term6,page_head->term);
					SetWindowText(EDIT_paper_score6,paper_score6);
					SetWindowText(EDIT_usual_score6,usual_score6);
					SetWindowText(EDIT_makeup_score6,makeup_score6);
					SetWindowText(EDIT_score6,score6);
					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				itoa(score_term_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"页，共");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_score_term_inquire_next:
				if(score_term_ck!=1)
				{
					MessageBox(NULL,"请点击“返回顶部”显示第一页学院信息！","提示",MB_OK);
					break;
				}
				page_head=score_head->next->next;//移到记录第一页第一条记录
				if(score_term_now+1>page)//如果当前页+1等于总页数，弹出警告
				{
					MessageBox(NULL,"已经到最后一页！","提示",MB_OK);
					return FALSE;
				}
				else//否则，跳转页数
				{
					score_term_now++;
				}
				for(i=0;i<(score_term_now-1)*6;i++)//将page_head移到当前页的第一项
					page_head=page_head->next;
				
				if(score_term_now==page)//如果在最后一页，则计算最后一页记录数量
					print=sum-(page-1)*6;
				else//否则，记录总数为6
					print=6;
				//清空编辑框内容
					SetWindowText(EDIT_id1,"");
					SetWindowText(EDIT_id2,"");
					SetWindowText(EDIT_id3,"");
					SetWindowText(EDIT_id4,"");
					SetWindowText(EDIT_id5,"");
					SetWindowText(EDIT_id6,"");
					SetWindowText(EDIT_name1,"");
					SetWindowText(EDIT_name2,"");
					SetWindowText(EDIT_name3,"");
					SetWindowText(EDIT_name4,"");
					SetWindowText(EDIT_name5,"");
					SetWindowText(EDIT_name6,"");
					SetWindowText(EDIT_paper_score1,"");
					SetWindowText(EDIT_paper_score2,"");
					SetWindowText(EDIT_paper_score3,"");
					SetWindowText(EDIT_paper_score4,"");
					SetWindowText(EDIT_paper_score5,"");
					SetWindowText(EDIT_paper_score6,"");
					SetWindowText(EDIT_usual_score1,"");
					SetWindowText(EDIT_usual_score2,"");
					SetWindowText(EDIT_usual_score3,"");
					SetWindowText(EDIT_usual_score4,"");
					SetWindowText(EDIT_usual_score5,"");
					SetWindowText(EDIT_usual_score6,"");
					SetWindowText(EDIT_subject1,"");
					SetWindowText(EDIT_subject2,"");
					SetWindowText(EDIT_subject3,"");
					SetWindowText(EDIT_subject4,"");
					SetWindowText(EDIT_subject5,"");
					SetWindowText(EDIT_subject6,"");
					SetWindowText(EDIT_makeup_score1,"");
					SetWindowText(EDIT_makeup_score2,"");
					SetWindowText(EDIT_makeup_score3,"");
					SetWindowText(EDIT_makeup_score4,"");
					SetWindowText(EDIT_makeup_score5,"");
					SetWindowText(EDIT_makeup_score6,"");
					SetWindowText(EDIT_score1,"");
					SetWindowText(EDIT_score2,"");
					SetWindowText(EDIT_score3,"");
					SetWindowText(EDIT_score4,"");
					SetWindowText(EDIT_score5,"");
					SetWindowText(EDIT_score6,"");
					SetWindowText(EDIT_grade1,"");
					SetWindowText(EDIT_grade2,"");
					SetWindowText(EDIT_grade3,"");
					SetWindowText(EDIT_grade4,"");
					SetWindowText(EDIT_grade5,"");
					SetWindowText(EDIT_grade6,"");
					SetWindowText(EDIT_term1,"");
					SetWindowText(EDIT_term2,"");
					SetWindowText(EDIT_term3,"");
					SetWindowText(EDIT_term4,"");
					SetWindowText(EDIT_term5,"");
					SetWindowText(EDIT_term6,"");
				if(print>=1)
				{
					while(page_head)
					{
						if(strcmp(page_head->grade,grade)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score1,10);
					itoa(page_head->usual_score,usual_score1,10);
					itoa(page_head->makeup_score,makeup_score1,10);
					itoa(page_head->score,score1,10);
					SetWindowText(EDIT_id1,page_head->id);
					SetWindowText(EDIT_name1,page_head->name);
					SetWindowText(EDIT_subject1,page_head->subject);
					SetWindowText(EDIT_grade1,page_head->grade);
					SetWindowText(EDIT_term1,page_head->term);
					SetWindowText(EDIT_paper_score1,paper_score1);
					SetWindowText(EDIT_usual_score1,usual_score1);
					SetWindowText(EDIT_makeup_score1,makeup_score1);
					SetWindowText(EDIT_score1,score1);
					page_head=page_head->next;
				}
				if(print>=2)
				{
					while(page_head)
					{
						if(strcmp(page_head->grade,grade)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score2,10);
					itoa(page_head->usual_score,usual_score2,10);
					itoa(page_head->makeup_score,makeup_score2,10);
					itoa(page_head->score,score2,10);
					SetWindowText(EDIT_id2,page_head->id);
					SetWindowText(EDIT_name2,page_head->name);
					SetWindowText(EDIT_subject2,page_head->subject);
					SetWindowText(EDIT_grade2,page_head->grade);
					SetWindowText(EDIT_term2,page_head->term);
					SetWindowText(EDIT_paper_score2,paper_score2);
					SetWindowText(EDIT_usual_score2,usual_score2);
					SetWindowText(EDIT_makeup_score2,makeup_score2);
					SetWindowText(EDIT_score2,score2);
					page_head=page_head->next;
				}
				if(print>=3)
				{
					while(page_head)
					{
						if(strcmp(page_head->grade,grade)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score3,10);
					itoa(page_head->usual_score,usual_score3,10);
					itoa(page_head->makeup_score,makeup_score3,10);
					itoa(page_head->score,score3,10);
					SetWindowText(EDIT_id3,page_head->id);
					SetWindowText(EDIT_name3,page_head->name);
					SetWindowText(EDIT_subject3,page_head->subject);
					SetWindowText(EDIT_grade3,page_head->grade);
					SetWindowText(EDIT_term3,page_head->term);
					SetWindowText(EDIT_paper_score3,paper_score3);
					SetWindowText(EDIT_usual_score3,usual_score3);
					SetWindowText(EDIT_makeup_score3,makeup_score3);
					SetWindowText(EDIT_score3,score3);
					page_head=page_head->next;
				}
				if(print>=4)
				{
					while(page_head)
					{
						if(strcmp(page_head->grade,grade)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score4,10);
					itoa(page_head->usual_score,usual_score4,10);
					itoa(page_head->makeup_score,makeup_score4,10);
					itoa(page_head->score,score4,10);
					SetWindowText(EDIT_id4,page_head->id);
					SetWindowText(EDIT_name4,page_head->name);
					SetWindowText(EDIT_subject4,page_head->subject);
					SetWindowText(EDIT_grade4,page_head->grade);
					SetWindowText(EDIT_term4,page_head->term);
					SetWindowText(EDIT_paper_score4,paper_score4);
					SetWindowText(EDIT_usual_score4,usual_score4);
					SetWindowText(EDIT_makeup_score4,makeup_score4);
					SetWindowText(EDIT_score4,score4);
					page_head=page_head->next;
				}
				if(print>=5)
				{
					while(page_head)
					{
						if(strcmp(page_head->grade,grade)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score5,10);
					itoa(page_head->usual_score,usual_score5,10);
					itoa(page_head->makeup_score,makeup_score5,10);
					itoa(page_head->score,score5,10);
					SetWindowText(EDIT_id5,page_head->id);
					SetWindowText(EDIT_name5,page_head->name);
					SetWindowText(EDIT_subject5,page_head->subject);
					SetWindowText(EDIT_grade5,page_head->grade);
					SetWindowText(EDIT_term5,page_head->term);
					SetWindowText(EDIT_paper_score5,paper_score5);
					SetWindowText(EDIT_usual_score5,usual_score5);
					SetWindowText(EDIT_makeup_score5,makeup_score5);
					SetWindowText(EDIT_score5,score5);
					page_head=page_head->next;
				}
				if(print>=6)
				{
					while(page_head)
					{
						if(strcmp(page_head->grade,grade)==0)
							break;
						page_head=page_head->next;
					}
					itoa(page_head->paper_score,paper_score6,10);
					itoa(page_head->usual_score,usual_score6,10);
					itoa(page_head->makeup_score,makeup_score6,10);
					itoa(page_head->score,score6,10);
					SetWindowText(EDIT_id6,page_head->id);
					SetWindowText(EDIT_name6,page_head->name);
					SetWindowText(EDIT_subject6,page_head->subject);
					SetWindowText(EDIT_grade6,page_head->grade);
					SetWindowText(EDIT_term6,page_head->term);
					SetWindowText(EDIT_paper_score6,paper_score6);
					SetWindowText(EDIT_usual_score6,usual_score6);
					SetWindowText(EDIT_makeup_score6,makeup_score6);
					SetWindowText(EDIT_score6,score6);
					page_head=page_head->next;
				}
				strcpy(char_page,"第");
				
				itoa(score_term_now,item,10);

				strcat(char_page,item);
				
				strcat(char_page,"页，共");
				itoa(page,item,10);//转换整形为字符型
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_score_term_inquire_exit:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
				break;
			}
			break;
		case WM_CLOSE:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
	}
    return FALSE;

}
//IDD_a_score_enter窗口回调函数
	int score_enter_ck; //标记是否初始化内容，1.是，0.否
	int score_enter_now;
	int find_enter;//查找结果 -1.该班级数据已录入，-2.改班级该学科数据已录入 ，-3.该班级该学科该学期数据已录入，0.数据未录入
	int sum,page;
	int score_display;
	char subject[255];
	char grade[50],term[50];
	int enter_1,enter_2,enter_3,enter_4,enter_5,enter_6;
LRESULT CALLBACK	A_SCORE_ENTER(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT index;
	student_List student_p;
	course_List course_p;
	class_List class_p;
	int repetition;//查重结果 0.未重复 -1.有重复
	int i,j,print;//sum.资料总数 page.总页数 now.当前页数 print.当前页资料总数
	score_List page_head,score_p;
	char paper_score1[10],paper_score2[10],paper_score3[10],paper_score4[10],paper_score5[10],paper_score6[10];
	char usual_score1[10],usual_score2[10],usual_score3[10],usual_score4[10],usual_score5[10],usual_score6[10];
	char makeup_score1[10],makeup_score2[10],makeup_score3[10],makeup_score4[10],makeup_score5[10],makeup_score6[10];
	char score1[10],score2[10],score3[10],score4[10],score5[10],score6[10];
	char char_page[30],item[10];
	TCHAR szItem[3][10] = {TEXT("第一学期"), TEXT("第二学期"), TEXT("第三学期")};
	HWND EDIT_grade,EDIT_course,EDIT_term;
	HWND EDIT_name1,EDIT_name2,EDIT_name3,EDIT_name4,EDIT_name5,EDIT_name6;
	HWND EDIT_paper_score1,EDIT_paper_score2,EDIT_paper_score3,EDIT_paper_score4,EDIT_paper_score5,EDIT_paper_score6;
	HWND EDIT_usual_score1,EDIT_usual_score2,EDIT_usual_score3,EDIT_usual_score4,EDIT_usual_score5,EDIT_usual_score6;
	HWND EDIT_makeup_score1,EDIT_makeup_score2,EDIT_makeup_score3,EDIT_makeup_score4,EDIT_makeup_score5,EDIT_makeup_score6;
	HWND EDIT_score1,EDIT_score2,EDIT_score3,EDIT_score4,EDIT_score5,EDIT_score6;
	HWND EDIT_id1,EDIT_id2,EDIT_id3,EDIT_id4,EDIT_id5,EDIT_id6;
	HWND EDIT_page;
	EDIT_course=GetDlgItem(hDlg,EDIT_a_score_enter_subject);
	EDIT_grade=GetDlgItem(hDlg,EDIT_a_score_enter_grade);
	EDIT_term=GetDlgItem(hDlg,EDIT_a_score_enter_term);
	EDIT_name1=GetDlgItem(hDlg,EDIT_a_score_enter_name1);
	EDIT_name2=GetDlgItem(hDlg,EDIT_a_score_enter_name2);
	EDIT_name3=GetDlgItem(hDlg,EDIT_a_score_enter_name3);
	EDIT_name4=GetDlgItem(hDlg,EDIT_a_score_enter_name4);
	EDIT_name5=GetDlgItem(hDlg,EDIT_a_score_enter_name5);
	EDIT_name6=GetDlgItem(hDlg,EDIT_a_score_enter_name6);
	EDIT_paper_score1=GetDlgItem(hDlg,EDIT_a_score_enter_paper_score1);
	EDIT_paper_score2=GetDlgItem(hDlg,EDIT_a_score_enter_paper_score2);
	EDIT_paper_score3=GetDlgItem(hDlg,EDIT_a_score_enter_paper_score3);
	EDIT_paper_score4=GetDlgItem(hDlg,EDIT_a_score_enter_paper_score4);
	EDIT_paper_score5=GetDlgItem(hDlg,EDIT_a_score_enter_paper_score5);
	EDIT_paper_score6=GetDlgItem(hDlg,EDIT_a_score_enter_paper_score6);
	EDIT_usual_score1=GetDlgItem(hDlg,EDIT_a_score_enter_usual_score1);
	EDIT_usual_score2=GetDlgItem(hDlg,EDIT_a_score_enter_usual_score2);
	EDIT_usual_score3=GetDlgItem(hDlg,EDIT_a_score_enter_usual_score3);
	EDIT_usual_score4=GetDlgItem(hDlg,EDIT_a_score_enter_usual_score4);
	EDIT_usual_score5=GetDlgItem(hDlg,EDIT_a_score_enter_usual_score5);
	EDIT_usual_score6=GetDlgItem(hDlg,EDIT_a_score_enter_usual_score6);
	EDIT_id1=GetDlgItem(hDlg,EDIT_a_score_enter_id1);
	EDIT_id2=GetDlgItem(hDlg,EDIT_a_score_enter_id2);
	EDIT_id3=GetDlgItem(hDlg,EDIT_a_score_enter_id3);
	EDIT_id4=GetDlgItem(hDlg,EDIT_a_score_enter_id4);
	EDIT_id5=GetDlgItem(hDlg,EDIT_a_score_enter_id5);
	EDIT_id6=GetDlgItem(hDlg,EDIT_a_score_enter_id6);
	EDIT_makeup_score1=GetDlgItem(hDlg,EDIT_a_score_enter_makeup_score1);
	EDIT_makeup_score2=GetDlgItem(hDlg,EDIT_a_score_enter_makeup_score2);
	EDIT_makeup_score3=GetDlgItem(hDlg,EDIT_a_score_enter_makeup_score3);
	EDIT_makeup_score4=GetDlgItem(hDlg,EDIT_a_score_enter_makeup_score4);
	EDIT_makeup_score5=GetDlgItem(hDlg,EDIT_a_score_enter_makeup_score5);
	EDIT_makeup_score6=GetDlgItem(hDlg,EDIT_a_score_enter_makeup_score6);
	EDIT_score1=GetDlgItem(hDlg,EDIT_a_score_enter_score1);
	EDIT_score2=GetDlgItem(hDlg,EDIT_a_score_enter_score2);
	EDIT_score3=GetDlgItem(hDlg,EDIT_a_score_enter_score3);
	EDIT_score4=GetDlgItem(hDlg,EDIT_a_score_enter_score4);
	EDIT_score5=GetDlgItem(hDlg,EDIT_a_score_enter_score5);
	EDIT_score6=GetDlgItem(hDlg,EDIT_a_score_enter_score6);
	EDIT_page=GetDlgItem(hDlg,EDIT_a_score_enter_page);
	
	switch (message)
	{
		case WM_INITDIALOG:
			//添加课程组合框内容
			course_load(course_head);
			course_p=course_head->next;
			sum=course_head->next->num;
			course_p=course_p->next;
			for(i=0;i<sum;i++)
			{
				SendMessage(EDIT_course, CB_INSERTSTRING, (WPARAM)i, (LPARAM)(LPCTSTR)course_p->name);
				course_p=course_p->next;
			}
			//添加班级组合框内容
			class_load(class_head);
			class_p=class_head->next;
			sum=class_head->next->num;
			class_p=class_p->next;
			for(i=0;i<sum;i++)
			{
				SendMessage(EDIT_grade, CB_INSERTSTRING, (WPARAM)i, (LPARAM)(LPCTSTR)class_p->name);
				class_p=class_p->next;
			}
			//添加学期信息组合框内容
			for(i=0;i<3;i++)
			{
				SendMessage(EDIT_term, CB_INSERTSTRING, (WPARAM)i, (LPARAM)(LPCTSTR)szItem[i]);
			}
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case BUTTON_a_score_enter_location:
				//获取课程信息，存入course
				score_load(score_head);
				index=SendMessage(EDIT_course, CB_GETCURSEL, 0, 0);
				if(index<0)
				{
					MessageBox(NULL,"请选择录入学科","ERROR!",MB_OK);
					return FALSE;
				}
				course_p=course_head->next->next;
				sum=index;
				for(i=0;i<index;i++)
					course_p=course_p->next;
				strcpy(subject,course_p->name);
				//获取班级信息，存入grade
				class_load(class_head);
				index=SendMessage(EDIT_grade, CB_GETCURSEL, 0, 0);
				if(index<0)
				{
					MessageBox(NULL,"请选择录入学科","ERROR!",MB_OK);
					return FALSE;
				}
				sum=index;
				class_p=class_head->next->next;
				for(i=0;i<index;i++)
					class_p=class_p->next;
				strcpy(grade,class_p->name);
				//获取学期信息，存入term
				index=SendMessage(EDIT_term, CB_GETCURSEL, 0, 0);
				if(index<0)
				{
					MessageBox(NULL,"请选择录入学科","ERROR!",MB_OK);
					return FALSE;
				}
				if(index==0)
					strcpy(term,"第一学期");
				else if(index==1)
					strcpy(term,"第二学期");
				else if(index==2)
					strcpy(term,"第三学期");
				//数据查重
				//查找结果 -1.该班级数据已录入，-2.改班级该学科数据已录入 ，-3.该班级该学科该学期数据已录入，0.数据未录入
				score_load(score_head);
				page_head=score_head->next->next;
				find_enter=0;//初始化查找状态爱为无重复
				while(page_head)
				{
					if(strcmp(page_head->grade,grade)==0)
					{
						find_enter=-1;//已录入班级
					}
					if(find_enter==-1&&(strcmp(page_head->subject,subject)==0))
					{
						find_enter=-2;//已录入学科
					}
					if(find_enter==-2&&(strcmp(page_head->term,term)==0))
					{
						find_enter=-3;//已录入该班级该学科该学期数据
						break;
					}
					find_enter=0;
					page_head=page_head->next;
				}
				if(find_enter==-3)
				{
					MessageBox(NULL,"检测到该班该学科该学期成绩已录入，正在为您检测漏录数据！","提示",MB_OK);
					//数据检漏，未完成
					student_load(student_head);
					student_p=student_head->next->next;
					sum=0;
					while(student_p)
					{
						if(strcmp(student_p->grade,grade)==0)
							sum++;
						student_p=student_p->next;
					}
					page=sum/6;
				}
				else
				{
					student_load(student_head);
					student_p=student_head->next->next;
					sum=0;
					while(student_p)
					{
						if(strcmp(student_p->grade,grade)==0)
						sum++;
						student_p=student_p->next;
					}
					page=sum/6;
				}

				if(sum%6!=0)
					page++;
				if(sum==0)
				{
					MessageBox(NULL,"未找到该班级学生任何成绩记录！","ERROR!",MB_OK);
					return FALSE;
				}
				
				score_enter_ck=1;//已点击返回顶部
				score_enter_now=1;//当前页数
				score_display=0;//上一个显示编号为0
				if(sum>=6)
					print=6;//若总资料数不小于6，则第一页显示6条数据
				if(sum<6)
					print=sum;//若资料总数小于6，则第一页显示全部sum条数据
				student_p=student_head->next->next;//指向第一页第一条记录
				if(print>=1)
				{
					while(student_p)
					{
						if(strcmp(student_p->grade,grade)==0)
							break;
						student_p=student_p->next;
					}
					score_display=student_p->num;
					enter_1=student_p->num;
					SetWindowText(EDIT_name1,student_p->name);
					SetWindowText(EDIT_id1,student_p->id);
					SetWindowText(EDIT_makeup_score1,"-1");
					student_p=student_p->next;
				}
				if(print>=2)
				{
					while(student_p)
					{
						if(strcmp(student_p->grade,grade)==0)
							break;
						student_p=student_p->next;
					}
					score_display=student_p->num;
					enter_2=student_p->num;
					SetWindowText(EDIT_name2,student_p->name);
					SetWindowText(EDIT_id2,student_p->id);
					SetWindowText(EDIT_makeup_score2,"-1");
					student_p=student_p->next;
				}
				if(print>=3)
				{
					while(student_p)
					{
						if(strcmp(student_p->grade,grade)==0)
							break;
						student_p=student_p->next;
					}
					score_display=student_p->num;
					enter_3=student_p->num;
					SetWindowText(EDIT_name3,student_p->name);
					SetWindowText(EDIT_id3,student_p->id);
					SetWindowText(EDIT_makeup_score3,"-1");
					student_p=student_p->next;
				}
				if(print>=4)
				{
					while(student_p)
					{
						if(strcmp(student_p->grade,grade)==0)
							break;
						student_p=student_p->next;
					}
					score_display=student_p->num;
					enter_4=student_p->num;
					SetWindowText(EDIT_name4,student_p->name);
					SetWindowText(EDIT_id4,student_p->id);
					SetWindowText(EDIT_makeup_score4,"-1");
					student_p=student_p->next;
				}
				if(print>=5)
				{
					while(student_p)
					{
						if(strcmp(student_p->grade,grade)==0)
							break;
						student_p=student_p->next;
					}
					score_display=student_p->num;
					enter_5=student_p->num;
					SetWindowText(EDIT_name5,student_p->name);
					SetWindowText(EDIT_id5,student_p->id);
					SetWindowText(EDIT_makeup_score5,"-1");
					student_p=student_p->next;
				}
				if(print>=6)
				{
					while(student_p)
					{
						if(strcmp(student_p->grade,grade)==0)
							break;
						student_p=student_p->next;
					}
					score_display=student_p->num;
					enter_6=student_p->num;
					SetWindowText(EDIT_name6,student_p->name);
					SetWindowText(EDIT_id6,student_p->id);
					SetWindowText(EDIT_makeup_score6,"-1");
					student_p=student_p->next;
				}
				strcpy(char_page,"第");
				itoa(score_enter_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"页，共");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				
				break;
			case BUTTON_a_score_enter_prior:
				if(score_enter_ck!=1)
				{
					MessageBox(NULL,"请点击“返回顶部”显示第一页成绩信息！","提示",MB_OK);
					break;
				}
				if(score_enter_now-1<=0)
				{
					MessageBox(NULL,"已经到第一页！","提示",MB_OK);
					return FALSE;
				}
				else
					score_enter_now--;
				student_load(student_head);
				student_p=student_head->next;//指向第一页第一条记录
				for(j=0;j<(score_enter_now-1)*6;)
				{
					if(strcmp(student_p->grade,grade)==0)
							j++;
						student_p=student_p->next;
				}
				if(score_enter_now==page)//如果在最后一页，则计算最后一页记录数量
					print=sum-(page-1)*6;
				else//否则，记录总数为6
					print=6;
				//清空编辑框内容
					SetWindowText(EDIT_name1,"");
					SetWindowText(EDIT_name2,"");
					SetWindowText(EDIT_name3,"");
					SetWindowText(EDIT_name4,"");
					SetWindowText(EDIT_name5,"");
					SetWindowText(EDIT_name6,"");
					SetWindowText(EDIT_paper_score1,"");
					SetWindowText(EDIT_paper_score2,"");
					SetWindowText(EDIT_paper_score3,"");
					SetWindowText(EDIT_paper_score4,"");
					SetWindowText(EDIT_paper_score5,"");
					SetWindowText(EDIT_paper_score6,"");
					SetWindowText(EDIT_usual_score1,"");
					SetWindowText(EDIT_usual_score2,"");
					SetWindowText(EDIT_usual_score3,"");
					SetWindowText(EDIT_usual_score4,"");
					SetWindowText(EDIT_usual_score5,"");
					SetWindowText(EDIT_usual_score6,"");
					SetWindowText(EDIT_id1,"");
					SetWindowText(EDIT_id2,"");
					SetWindowText(EDIT_id3,"");
					SetWindowText(EDIT_id4,"");
					SetWindowText(EDIT_id5,"");
					SetWindowText(EDIT_id6,"");
					SetWindowText(EDIT_makeup_score1,"");
					SetWindowText(EDIT_makeup_score2,"");
					SetWindowText(EDIT_makeup_score3,"");
					SetWindowText(EDIT_makeup_score4,"");
					SetWindowText(EDIT_makeup_score5,"");
					SetWindowText(EDIT_makeup_score6,"");
					SetWindowText(EDIT_score1,"");
					SetWindowText(EDIT_score2,"");
					SetWindowText(EDIT_score3,"");
					SetWindowText(EDIT_score4,"");
					SetWindowText(EDIT_score5,"");
					SetWindowText(EDIT_score6,"");
				if(print>=1)
				{
					while(student_p)
					{
						if(strcmp(student_p->grade,grade)==0)
							break;
						student_p=student_p->next;
					}
					score_display=student_p->num;
					enter_1=student_p->num;
					SetWindowText(EDIT_name1,student_p->name);
					SetWindowText(EDIT_id1,student_p->id);
					SetWindowText(EDIT_makeup_score1,"-1");
					student_p=student_p->next;
				}
				if(print>=2)
				{
					while(student_p)
					{
						if(strcmp(student_p->grade,grade)==0)
							break;
						student_p=student_p->next;
					}
					score_display=student_p->num;
					enter_2=student_p->num;
					SetWindowText(EDIT_name2,student_p->name);
					SetWindowText(EDIT_id2,student_p->id);
					SetWindowText(EDIT_makeup_score2,"-1");
					student_p=student_p->next;
				}
				if(print>=3)
				{
					while(student_p)
					{
						if(strcmp(student_p->grade,grade)==0)
							break;
						student_p=student_p->next;
					}
					score_display=student_p->num;
					enter_3=student_p->num;
					SetWindowText(EDIT_name3,student_p->name);
					SetWindowText(EDIT_id3,student_p->id);
					SetWindowText(EDIT_makeup_score3,"-1");
					student_p=student_p->next;
				}
				if(print>=4)
				{
					while(student_p)
					{
						if(strcmp(student_p->grade,grade)==0)
							break;
						student_p=student_p->next;
					}
					score_display=student_p->num;
					enter_4=student_p->num;
					SetWindowText(EDIT_name4,student_p->name);
					SetWindowText(EDIT_id4,student_p->id);
					SetWindowText(EDIT_makeup_score4,"-1");
					student_p=student_p->next;
				}
				if(print>=5)
				{
					while(student_p)
					{
						if(strcmp(student_p->grade,grade)==0)
							break;
						student_p=student_p->next;
					}
					score_display=student_p->num;
					enter_5=student_p->num;
					SetWindowText(EDIT_name5,student_p->name);
					SetWindowText(EDIT_id5,student_p->id);
					SetWindowText(EDIT_makeup_score5,"-1");
					student_p=student_p->next;
				}
				if(print>=6)
				{
					while(student_p)
					{
						if(strcmp(student_p->grade,grade)==0)
							break;
						student_p=student_p->next;
					}
					score_display=student_p->num;
					enter_6=student_p->num;
					SetWindowText(EDIT_name6,student_p->name);
					SetWindowText(EDIT_id6,student_p->id);
					SetWindowText(EDIT_makeup_score6,"-1");
					student_p=student_p->next;
				}


				strcpy(char_page,"第");
				itoa(score_enter_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"页，共");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_score_enter_next:
				if(score_enter_ck!=1)
				{
					MessageBox(NULL,"请点击“返回顶部”显示第一页学院信息！","提示",MB_OK);
					break;
				}
				if(score_enter_now+1>page)//如果当前页+1等于总页数，弹出警告
				{
					MessageBox(NULL,"已经到最后一页！","提示",MB_OK);
					return FALSE;
				}
				else//否则，跳转页数
				{
					score_enter_now++;
				}
				
				student_load(student_head);
				student_p=student_head->next->next;//指向第一页第一条记录
				for(i=0;i<enter_6;i++)
					student_p=student_p->next;
				if(score_enter_now==page)//如果在最后一页，则计算最后一页记录数量
					print=sum-(page-1)*6;
				else//否则，记录总数为6
					print=6;
				//清空编辑框内容
					SetWindowText(EDIT_name1,"");
					SetWindowText(EDIT_name2,"");
					SetWindowText(EDIT_name3,"");
					SetWindowText(EDIT_name4,"");
					SetWindowText(EDIT_name5,"");
					SetWindowText(EDIT_name6,"");
					SetWindowText(EDIT_paper_score1,"");
					SetWindowText(EDIT_paper_score2,"");
					SetWindowText(EDIT_paper_score3,"");
					SetWindowText(EDIT_paper_score4,"");
					SetWindowText(EDIT_paper_score5,"");
					SetWindowText(EDIT_paper_score6,"");
					SetWindowText(EDIT_usual_score1,"");
					SetWindowText(EDIT_usual_score2,"");
					SetWindowText(EDIT_usual_score3,"");
					SetWindowText(EDIT_usual_score4,"");
					SetWindowText(EDIT_usual_score5,"");
					SetWindowText(EDIT_usual_score6,"");
					SetWindowText(EDIT_id1,"");
					SetWindowText(EDIT_id2,"");
					SetWindowText(EDIT_id3,"");
					SetWindowText(EDIT_id4,"");
					SetWindowText(EDIT_id5,"");
					SetWindowText(EDIT_id6,"");
					SetWindowText(EDIT_makeup_score1,"");
					SetWindowText(EDIT_makeup_score2,"");
					SetWindowText(EDIT_makeup_score3,"");
					SetWindowText(EDIT_makeup_score4,"");
					SetWindowText(EDIT_makeup_score5,"");
					SetWindowText(EDIT_makeup_score6,"");
					SetWindowText(EDIT_score1,"");
					SetWindowText(EDIT_score2,"");
					SetWindowText(EDIT_score3,"");
					SetWindowText(EDIT_score4,"");
					SetWindowText(EDIT_score5,"");
					SetWindowText(EDIT_score6,"");
				if(print>=1)
				{
					while(student_p)
					{
						if(strcmp(student_p->grade,grade)==0)
							break;
						student_p=student_p->next;
					}
					score_display=student_p->num;
					enter_1=student_p->num;
					SetWindowText(EDIT_name1,student_p->name);
					SetWindowText(EDIT_id1,student_p->id);
					SetWindowText(EDIT_makeup_score1,"-1");
					student_p=student_p->next;
				}
				if(print>=2)
				{
					while(student_p)
					{
						if(strcmp(student_p->grade,grade)==0)
							break;
						student_p=student_p->next;
					}
					score_display=student_p->num;
					enter_2=student_p->num;
					SetWindowText(EDIT_name2,student_p->name);
					SetWindowText(EDIT_id2,student_p->id);
					SetWindowText(EDIT_makeup_score2,"-1");
					student_p=student_p->next;
				}
				if(print>=3)
				{
					while(student_p)
					{
						if(strcmp(student_p->grade,grade)==0)
							break;
						student_p=student_p->next;
					}
					score_display=student_p->num;
					enter_3=student_p->num;
					SetWindowText(EDIT_name3,student_p->name);
					SetWindowText(EDIT_id3,student_p->id);
					SetWindowText(EDIT_makeup_score3,"-1");
					student_p=student_p->next;
				}
				if(print>=4)
				{
					while(student_p)
					{
						if(strcmp(student_p->grade,grade)==0)
							break;
						student_p=student_p->next;
					}
					score_display=student_p->num;
					enter_4=student_p->num;
					SetWindowText(EDIT_name4,student_p->name);
					SetWindowText(EDIT_id4,student_p->id);
					SetWindowText(EDIT_makeup_score4,"-1");
					student_p=student_p->next;
				}
				if(print>=5)
				{
					while(student_p)
					{
						if(strcmp(student_p->grade,grade)==0)
							break;
						student_p=student_p->next;
					}
					score_display=student_p->num;
					enter_5=student_p->num;
					SetWindowText(EDIT_name5,student_p->name);
					SetWindowText(EDIT_id5,student_p->id);
					SetWindowText(EDIT_makeup_score5,"-1");
					student_p=student_p->next;
				}
				if(print>=6)
				{
					while(student_p)
					{
						if(strcmp(student_p->grade,grade)==0)
							break;
						student_p=student_p->next;
					}
					score_display=student_p->num;
					enter_6=student_p->num;
					SetWindowText(EDIT_name6,student_p->name);
					SetWindowText(EDIT_id6,student_p->id);
					SetWindowText(EDIT_makeup_score6,"-1");
					student_p=student_p->next;
				}

				strcpy(char_page,"第");
				
				itoa(score_enter_now,item,10);

				strcat(char_page,item);
				
				strcat(char_page,"页，共");
				itoa(page,item,10);//转换整形为字符型
				strcat(char_page,item);
				strcat(char_page,"页");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_score_enter_affirm:
				//获取该页第一条数据输入成绩
				//获取该学生的个人信息汇入成绩数据库
				student_load(student_head);
				student_p=student_head->next;
				for(i=0;i<enter_1;i++)
					student_p=student_p->next;
				//数据查重
				repetition=0;
				score_load(score_head);
				page_head=score_head->next;
				while(page_head)
				{
					if(strcmp(page_head->id,student_p->id)==0)
						if(strcmp(page_head->subject,subject)==0)
							if(strcmp(page_head->term,term)==0)
							{
								MessageBox(NULL,"已存在该生该科目该学期成绩，该条成绩数据不会保存！","ERROR",MB_OK);
								repetition=-1;
								break;
							}
					page_head=page_head->next;
				}
				if(repetition==0)
				{
					page_head=score_head->next;
					while(page_head->next)
						page_head=page_head->next;
					score_p=(score_List)malloc(sizeof(score_Lnode));
					score_p->num=score_head->next->num+1;
					strcpy(score_p->id,student_p->id);
					strcpy(score_p->name,student_p->name);
					strcpy(score_p->college,student_p->college);
					strcpy(score_p->profession,student_p->profession);
					strcpy(score_p->grade,student_p->grade);
					strcpy(score_p->subject,subject);
					strcpy(score_p->term,term);
					GetWindowText(EDIT_paper_score1,paper_score1,GetWindowTextLength(EDIT_paper_score1)+1);
					GetWindowText(EDIT_usual_score1,usual_score1,GetWindowTextLength(EDIT_usual_score1)+1);
					GetWindowText(EDIT_makeup_score1,makeup_score1,GetWindowTextLength(EDIT_makeup_score1)+1);
					if((strcmp(paper_score1,"100")!=0)&&(strcmp(paper_score1,"00")<0||strcmp(paper_score1,"99")>0))
					{
						MessageBox(NULL,"请以百分制输入卷面成绩！","警告",MB_OK);
						SetWindowText(EDIT_paper_score1,"");
						return FALSE;
					}
					if((strcmp(paper_score1,"100")!=0)&&(strcmp(usual_score1,"00")<0||strcmp(usual_score1,"99")>0))
					{
						MessageBox(NULL,"请以百分制输入平时成绩！","警告",MB_OK);
						SetWindowText(EDIT_usual_score1,"");
						return FALSE;
					}
					if((strcmp(makeup_score1,"100")!=0)&&(strcmp(makeup_score1,"-1")!=0)&&((strcmp(makeup_score1,"00")<0||strcmp(makeup_score1,"99")>0)))
					{
						MessageBox(NULL,"请以百分制输入补考成绩！\n无补考记录记为“-1”","警告",MB_OK);
						SetWindowText(EDIT_makeup_score1,"-1");
						return FALSE;
					}
					score_p->paper_score=atoi(paper_score1);
					score_p->usual_score=atoi(usual_score1);
					score_p->makeup_score=atoi(makeup_score1);
					if(score_p->makeup_score==-1)
					{
						score_p->score=score_p->paper_score*0.7+score_p->usual_score*0.3;
					}
					else
					{
						score_p->score=score_p->makeup_score*0.7+score_p->usual_score*0.3;
					}
					itoa(score_p->score,item,10);
					SetWindowText(EDIT_score1,item);
					page_head->next=score_p;
					page_head=page_head->next;
					score_head->next->num++;
					score_save(score_head);
					score_load(score_head);
				}
				//获取该页第一条数据输入成绩
				//获取该学生的个人信息汇入成绩数据库
				student_load(student_head);
				student_p=student_head->next;
				for(i=0;i<enter_2;i++)
					student_p=student_p->next;
				//数据查重
				repetition=0;
				score_load(score_head);
				page_head=score_head->next;
				while(page_head)
				{
					if(strcmp(page_head->id,student_p->id)==0)
						if(strcmp(page_head->subject,subject)==0)
							if(strcmp(page_head->term,term)==0)
							{
								MessageBox(NULL,"已存在该生该科目该学期成绩，该条成绩数据不会保存！","ERROR",MB_OK);
								repetition=-1;
								break;
							}
					page_head=page_head->next;
				}
				if(repetition==0)
				{
					page_head=score_head->next;
					while(page_head->next)
						page_head=page_head->next;
					score_p=(score_List)malloc(sizeof(score_Lnode));
					score_p->num=score_head->next->num+2;
					strcpy(score_p->id,student_p->id);
					strcpy(score_p->name,student_p->name);
					strcpy(score_p->college,student_p->college);
					strcpy(score_p->profession,student_p->profession);
					strcpy(score_p->grade,student_p->grade);
					strcpy(score_p->subject,subject);
					strcpy(score_p->term,term);
					GetWindowText(EDIT_paper_score2,paper_score2,GetWindowTextLength(EDIT_paper_score2)+2);
					GetWindowText(EDIT_usual_score2,usual_score2,GetWindowTextLength(EDIT_usual_score2)+2);
					GetWindowText(EDIT_makeup_score2,makeup_score2,GetWindowTextLength(EDIT_makeup_score2)+2);
					if((strcmp(paper_score2,"100")!=0)&&(strcmp(paper_score2,"00")<0||strcmp(paper_score2,"99")>0))
					{
						MessageBox(NULL,"请以百分制输入卷面成绩！","警告",MB_OK);
						SetWindowText(EDIT_paper_score2,"");
						return FALSE;
					}
					if((strcmp(paper_score2,"100")!=0)&&(strcmp(usual_score2,"00")<0||strcmp(usual_score2,"99")>0))
					{
						MessageBox(NULL,"请以百分制输入平时成绩！","警告",MB_OK);
						SetWindowText(EDIT_usual_score2,"");
						return FALSE;
					}
					if((strcmp(makeup_score2,"100")!=0)&&(strcmp(makeup_score2,"-1")!=0)&&((strcmp(makeup_score2,"00")<0||strcmp(makeup_score2,"99")>0)))
					{
						MessageBox(NULL,"请以百分制输入补考成绩！\n无补考记录记为“-1”","警告",MB_OK);
						SetWindowText(EDIT_makeup_score2,"-1");
						return FALSE;
					}
					score_p->paper_score=atoi(paper_score2);
					score_p->usual_score=atoi(usual_score2);
					score_p->makeup_score=atoi(makeup_score2);
					if(score_p->makeup_score==-1)
					{
						score_p->score=score_p->paper_score*0.7+score_p->usual_score*0.3;
					}
					else
					{
						score_p->score=score_p->makeup_score*0.7+score_p->usual_score*0.3;
					}
					itoa(score_p->score,item,10);
					SetWindowText(EDIT_score2,item);
					page_head->next=score_p;
					page_head=page_head->next;
					score_head->next->num++;
					score_save(score_head);
					score_load(score_head);
				}
				//获取该页第一条数据输入成绩
				//获取该学生的个人信息汇入成绩数据库
				student_load(student_head);
				student_p=student_head->next;
				for(i=0;i<enter_3;i++)
					student_p=student_p->next;
				//数据查重
				repetition=0;
				score_load(score_head);
				page_head=score_head->next;
				while(page_head)
				{
					if(strcmp(page_head->id,student_p->id)==0)
						if(strcmp(page_head->subject,subject)==0)
							if(strcmp(page_head->term,term)==0)
							{
								MessageBox(NULL,"已存在该生该科目该学期成绩，该条成绩数据不会保存！","ERROR",MB_OK);
								repetition=-1;
								break;
							}
					page_head=page_head->next;
				}
				if(repetition==0)
				{
					page_head=score_head->next;
					while(page_head->next)
						page_head=page_head->next;
					score_p=(score_List)malloc(sizeof(score_Lnode));
					score_p->num=score_head->next->num+3;
					strcpy(score_p->id,student_p->id);
					strcpy(score_p->name,student_p->name);
					strcpy(score_p->college,student_p->college);
					strcpy(score_p->profession,student_p->profession);
					strcpy(score_p->grade,student_p->grade);
					strcpy(score_p->subject,subject);
					strcpy(score_p->term,term);
					GetWindowText(EDIT_paper_score3,paper_score3,GetWindowTextLength(EDIT_paper_score3)+3);
					GetWindowText(EDIT_usual_score3,usual_score3,GetWindowTextLength(EDIT_usual_score3)+3);
					GetWindowText(EDIT_makeup_score3,makeup_score3,GetWindowTextLength(EDIT_makeup_score3)+3);
					if((strcmp(paper_score3,"100")!=0)&&(strcmp(paper_score3,"00")<0||strcmp(paper_score3,"99")>0))
					{
						MessageBox(NULL,"请以百分制输入卷面成绩！","警告",MB_OK);
						SetWindowText(EDIT_paper_score3,"");
						return FALSE;
					}
					if((strcmp(paper_score3,"100")!=0)&&(strcmp(usual_score3,"00")<0||strcmp(usual_score3,"99")>0))
					{
						MessageBox(NULL,"请以百分制输入平时成绩！","警告",MB_OK);
						SetWindowText(EDIT_usual_score3,"");
						return FALSE;
					}
					if((strcmp(makeup_score3,"100")!=0)&&(strcmp(makeup_score3,"-1")!=0)&&((strcmp(makeup_score3,"00")<0||strcmp(makeup_score3,"99")>0)))
					{
						MessageBox(NULL,"请以百分制输入补考成绩！\n无补考记录记为“-1”","警告",MB_OK);
						SetWindowText(EDIT_makeup_score3,"-1");
						return FALSE;
					}
					score_p->paper_score=atoi(paper_score3);
					score_p->usual_score=atoi(usual_score3);
					score_p->makeup_score=atoi(makeup_score3);
					if(score_p->makeup_score==-1)
					{
						score_p->score=score_p->paper_score*0.7+score_p->usual_score*0.3;
					}
					else
					{
						score_p->score=score_p->makeup_score*0.7+score_p->usual_score*0.3;
					}
					itoa(score_p->score,item,10);
					SetWindowText(EDIT_score3,item);
					page_head->next=score_p;
					page_head=page_head->next;
					score_head->next->num++;
					score_save(score_head);
					score_load(score_head);
				}
				//获取该页第一条数据输入成绩
				//获取该学生的个人信息汇入成绩数据库
				student_load(student_head);
				student_p=student_head->next;
				for(i=0;i<enter_4;i++)
					student_p=student_p->next;
				//数据查重
				repetition=0;
				score_load(score_head);
				page_head=score_head->next;
				while(page_head)
				{
					if(strcmp(page_head->id,student_p->id)==0)
						if(strcmp(page_head->subject,subject)==0)
							if(strcmp(page_head->term,term)==0)
							{
								MessageBox(NULL,"已存在该生该科目该学期成绩，该条成绩数据不会保存！","ERROR",MB_OK);
								repetition=-1;
								break;
							}
					page_head=page_head->next;
				}
				if(repetition==0)
				{
					page_head=score_head->next;
					while(page_head->next)
						page_head=page_head->next;
					score_p=(score_List)malloc(sizeof(score_Lnode));
					score_p->num=score_head->next->num+4;
					strcpy(score_p->id,student_p->id);
					strcpy(score_p->name,student_p->name);
					strcpy(score_p->college,student_p->college);
					strcpy(score_p->profession,student_p->profession);
					strcpy(score_p->grade,student_p->grade);
					strcpy(score_p->subject,subject);
					strcpy(score_p->term,term);
					GetWindowText(EDIT_paper_score4,paper_score4,GetWindowTextLength(EDIT_paper_score4)+4);
					GetWindowText(EDIT_usual_score4,usual_score4,GetWindowTextLength(EDIT_usual_score4)+4);
					GetWindowText(EDIT_makeup_score4,makeup_score4,GetWindowTextLength(EDIT_makeup_score4)+4);
					if((strcmp(paper_score4,"100")!=0)&&(strcmp(paper_score4,"00")<0||strcmp(paper_score4,"99")>0))
					{
						MessageBox(NULL,"请以百分制输入卷面成绩！","警告",MB_OK);
						SetWindowText(EDIT_paper_score4,"");
						return FALSE;
					}
					if((strcmp(paper_score4,"100")!=0)&&(strcmp(usual_score4,"00")<0||strcmp(usual_score4,"99")>0))
					{
						MessageBox(NULL,"请以百分制输入平时成绩！","警告",MB_OK);
						SetWindowText(EDIT_usual_score4,"");
						return FALSE;
					}
					if((strcmp(makeup_score4,"100")!=0)&&(strcmp(makeup_score4,"-1")!=0)&&((strcmp(makeup_score4,"00")<0||strcmp(makeup_score4,"99")>0)))
					{
						MessageBox(NULL,"请以百分制输入补考成绩！\n无补考记录记为“-1”","警告",MB_OK);
						SetWindowText(EDIT_makeup_score4,"-1");
						return FALSE;
					}
					score_p->paper_score=atoi(paper_score4);
					score_p->usual_score=atoi(usual_score4);
					score_p->makeup_score=atoi(makeup_score4);
					if(score_p->makeup_score==-1)
					{
						score_p->score=score_p->paper_score*0.7+score_p->usual_score*0.3;
					}
					else
					{
						score_p->score=score_p->makeup_score*0.7+score_p->usual_score*0.3;
					}
					itoa(score_p->score,item,10);
					SetWindowText(EDIT_score4,item);
					page_head->next=score_p;
					page_head=page_head->next;
					score_head->next->num++;
					score_save(score_head);
					score_load(score_head);
				}
				//获取该页第一条数据输入成绩
				//获取该学生的个人信息汇入成绩数据库
				student_load(student_head);
				student_p=student_head->next;
				for(i=0;i<enter_5;i++)
					student_p=student_p->next;
				//数据查重
				repetition=0;
				score_load(score_head);
				page_head=score_head->next;
				while(page_head)
				{
					if(strcmp(page_head->id,student_p->id)==0)
						if(strcmp(page_head->subject,subject)==0)
							if(strcmp(page_head->term,term)==0)
							{
								MessageBox(NULL,"已存在该生该科目该学期成绩，该条成绩数据不会保存！","ERROR",MB_OK);
								repetition=-1;
								break;
							}
					page_head=page_head->next;
				}
				if(repetition==0)
				{
					page_head=score_head->next;
					while(page_head->next)
						page_head=page_head->next;
					score_p=(score_List)malloc(sizeof(score_Lnode));
					score_p->num=score_head->next->num+5;
					strcpy(score_p->id,student_p->id);
					strcpy(score_p->name,student_p->name);
					strcpy(score_p->college,student_p->college);
					strcpy(score_p->profession,student_p->profession);
					strcpy(score_p->grade,student_p->grade);
					strcpy(score_p->subject,subject);
					strcpy(score_p->term,term);
					GetWindowText(EDIT_paper_score5,paper_score5,GetWindowTextLength(EDIT_paper_score5)+5);
					GetWindowText(EDIT_usual_score5,usual_score5,GetWindowTextLength(EDIT_usual_score5)+5);
					GetWindowText(EDIT_makeup_score5,makeup_score5,GetWindowTextLength(EDIT_makeup_score5)+5);
					if((strcmp(paper_score5,"100")!=0)&&(strcmp(paper_score5,"00")<0||strcmp(paper_score5,"99")>0))
					{
						MessageBox(NULL,"请以百分制输入卷面成绩！","警告",MB_OK);
						SetWindowText(EDIT_paper_score5,"");
						return FALSE;
					}
					if((strcmp(paper_score5,"100")!=0)&&(strcmp(usual_score5,"00")<0||strcmp(usual_score5,"99")>0))
					{
						MessageBox(NULL,"请以百分制输入平时成绩！","警告",MB_OK);
						SetWindowText(EDIT_usual_score5,"");
						return FALSE;
					}
					if((strcmp(makeup_score5,"100")!=0)&&(strcmp(makeup_score5,"-1")!=0)&&((strcmp(makeup_score5,"00")<0||strcmp(makeup_score5,"99")>0)))
					{
						MessageBox(NULL,"请以百分制输入补考成绩！\n无补考记录记为“-1”","警告",MB_OK);
						SetWindowText(EDIT_makeup_score5,"-1");
						return FALSE;
					}
					score_p->paper_score=atoi(paper_score5);
					score_p->usual_score=atoi(usual_score5);
					score_p->makeup_score=atoi(makeup_score5);
					if(score_p->makeup_score==-1)
					{
						score_p->score=score_p->paper_score*0.7+score_p->usual_score*0.3;
					}
					else
					{
						score_p->score=score_p->makeup_score*0.7+score_p->usual_score*0.3;
					}
					itoa(score_p->score,item,10);
					SetWindowText(EDIT_score5,item);
					page_head->next=score_p;
					page_head=page_head->next;
					score_head->next->num++;
					score_save(score_head);
					score_load(score_head);
				}
				//获取该页第一条数据输入成绩
				//获取该学生的个人信息汇入成绩数据库
				student_load(student_head);
				student_p=student_head->next;
				for(i=0;i<enter_6;i++)
					student_p=student_p->next;
				//数据查重
				repetition=0;
				score_load(score_head);
				page_head=score_head->next;
				while(page_head)
				{
					if(strcmp(page_head->id,student_p->id)==0)
						if(strcmp(page_head->subject,subject)==0)
							if(strcmp(page_head->term,term)==0)
							{
								MessageBox(NULL,"已存在该生该科目该学期成绩，该条成绩数据不会保存！","ERROR",MB_OK);
								repetition=-1;
								break;
							}
					page_head=page_head->next;
				}
				if(repetition==0)
				{
					page_head=score_head->next;
					while(page_head->next)
						page_head=page_head->next;
					score_p=(score_List)malloc(sizeof(score_Lnode));
					score_p->num=score_head->next->num+6;
					strcpy(score_p->id,student_p->id);
					strcpy(score_p->name,student_p->name);
					strcpy(score_p->college,student_p->college);
					strcpy(score_p->profession,student_p->profession);
					strcpy(score_p->grade,student_p->grade);
					strcpy(score_p->subject,subject);
					strcpy(score_p->term,term);
					GetWindowText(EDIT_paper_score6,paper_score6,GetWindowTextLength(EDIT_paper_score6)+6);
					GetWindowText(EDIT_usual_score6,usual_score6,GetWindowTextLength(EDIT_usual_score6)+6);
					GetWindowText(EDIT_makeup_score6,makeup_score6,GetWindowTextLength(EDIT_makeup_score6)+6);
					if((strcmp(paper_score6,"100")!=0)&&(strcmp(paper_score6,"00")<0||strcmp(paper_score6,"99")>0))
					{
						MessageBox(NULL,"请以百分制输入卷面成绩！","警告",MB_OK);
						SetWindowText(EDIT_paper_score6,"");
						return FALSE;
					}
					if((strcmp(paper_score6,"100")!=0)&&(strcmp(usual_score6,"00")<0||strcmp(usual_score6,"99")>0))
					{
						MessageBox(NULL,"请以百分制输入平时成绩！","警告",MB_OK);
						SetWindowText(EDIT_usual_score6,"");
						return FALSE;
					}
					if((strcmp(makeup_score6,"100")!=0)&&(strcmp(makeup_score6,"-1")!=0)&&((strcmp(makeup_score6,"00")<0||strcmp(makeup_score6,"99")>0)))
					{
						MessageBox(NULL,"请以百分制输入补考成绩！\n无补考记录记为“-1”","警告",MB_OK);
						SetWindowText(EDIT_makeup_score6,"-1");
						return FALSE;
					}
					score_p->paper_score=atoi(paper_score6);
					score_p->usual_score=atoi(usual_score6);
					score_p->makeup_score=atoi(makeup_score6);
					if(score_p->makeup_score==-1)
					{
						score_p->score=score_p->paper_score*0.7+score_p->usual_score*0.3;
					}
					else
					{
						score_p->score=score_p->makeup_score*0.7+score_p->usual_score*0.3;
					}
					itoa(score_p->score,item,10);
					SetWindowText(EDIT_score6,item);
					page_head->next=score_p;
					page_head=page_head->next;
					score_head->next->num++;
					score_save(score_head);
					score_load(score_head);
				}
				break;
			case BUTTON_a_score_enter_exit:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
				break;
			}
			break;
		case WM_CLOSE:
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
	}
    return FALSE;
}

LRESULT CALLBACK	A_SCORE_ANALYSE_SUM(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT index;
	class_List class_p;
	int i,sum;
	char gread[50],item[10];
	score_List score_p;
	HWND EDIT_grade,EDIT_score;
	EDIT_grade=GetDlgItem(hDlg,EDIT_a_score_analyse_sum_gread);
	EDIT_score=GetDlgItem(hDlg,EDIT_a_score_analyse_sum_score);
	
	switch (message)
	{
		case WM_INITDIALOG:
			//添加班级组合框内容
			class_load(class_head);
			class_p=class_head->next;
			sum=class_head->next->num;
			class_p=class_p->next;
			for(i=0;i<sum;i++)
			{
				SendMessage(EDIT_grade, CB_INSERTSTRING, (WPARAM)i, (LPARAM)(LPCTSTR)class_p->name);
				class_p=class_p->next;
			}
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case BUTTON_a_score_analyse_sum_enter:
				//获取班级信息，存入grade
				class_load(class_head);
				index=SendMessage(EDIT_grade, CB_GETCURSEL, 0, 0);
				if(index<0)
				{
					MessageBox(NULL,"请选择录入学科","ERROR!",MB_OK);
					return FALSE;
				}
				class_p=class_head->next->next;
				for(i=0;i<index;i++)
					class_p=class_p->next;
				strcpy(grade,class_p->name);
				score_load(score_head);
				score_p=score_head->next->next;
				sum=0;
				while(score_p)
				{
					if(strcmp(score_p->grade,grade)==0)
						sum+=score_p->score;
					score_p=score_p->next;
				}
				if(sum==0)
				{
					MessageBox(NULL,"该班级成绩为空！","警告",MB_OK);
					return FALSE;
				}
				itoa(sum,item,10);
				SetWindowText(EDIT_score,item);
				break;
			case BUTTON_a_score_analyse_sum_exit:
				EndDialog(hDlg, LOWORD(wParam));
				break;
			}
			break;
			return FALSE;
		case WM_CLOSE:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
	}
	return FALSE;

}
LRESULT CALLBACK	A_SCORE_ANALYSE_AVERAGE(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	LRESULT index;
	class_List class_p;
	int i,sum,num;
	char gread[50],item[10];
	score_List score_p;
	HWND EDIT_grade,EDIT_score;
	EDIT_grade=GetDlgItem(hDlg,EDIT_a_score_analyse_average_gread);
	EDIT_score=GetDlgItem(hDlg,EDIT_a_score_analyse_average_score);
	
	switch (message)
	{
		case WM_INITDIALOG:
			//添加班级组合框内容
			class_load(class_head);
			class_p=class_head->next;
			sum=class_head->next->num;
			class_p=class_p->next;
			for(i=0;i<sum;i++)
			{
				SendMessage(EDIT_grade, CB_INSERTSTRING, (WPARAM)i, (LPARAM)(LPCTSTR)class_p->name);
				class_p=class_p->next;
			}
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case BUTTON_a_score_analyse_average_enter:
				//获取班级信息，存入grade
				class_load(class_head);
				index=SendMessage(EDIT_grade, CB_GETCURSEL, 0, 0);
				if(index<0)
				{
					MessageBox(NULL,"请选择录入学科","ERROR!",MB_OK);
					return FALSE;
				}
				class_p=class_head->next->next;
				for(i=0;i<index;i++)
					class_p=class_p->next;
				strcpy(grade,class_p->name);
				score_load(score_head);
				score_p=score_head->next->next;
				sum=0;
				num=0;
				while(score_p)
				{
					if(strcmp(score_p->grade,grade)==0)
					{
						sum+=score_p->score;
						num++;
					}
					score_p=score_p->next;
				}
				if(sum==0)
				{
					MessageBox(NULL,"该班级成绩为空！","警告",MB_OK);
					return FALSE;
				}
				itoa(sum/num,item,10);
				SetWindowText(EDIT_score,item);
				break;
			case BUTTON_a_score_analyse_average_exit:
				EndDialog(hDlg, LOWORD(wParam));
				break;
			}
			break;
			return FALSE;
		case WM_CLOSE:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
	}
	return FALSE;

}
void account_load(account_List account_head) //载入账户数据,双向链表
{
    account_List rear = account_head,p,prior;
    FILE *fp;
    int i=0,sum;

    fp = fopen("Account information.dat","rb");
    if(fp == NULL)
    {
        identity=-2;
        return;
    }
    p = (account_List)malloc(sizeof(account_Lnode));
    fread(p,sizeof(account_Lnode),1,fp);i++;
    sum = p->num;
	prior=rear;
    rear->next = p;
	p->prior=prior;
    rear = p;
	if(sum==0)
		rear->next=NULL;
    while(i<=sum)
    {
        p = (account_List)malloc(sizeof(account_Lnode));
        if(fread(p,sizeof(account_Lnode),1,fp)==0)
        break;
		prior = rear;
        rear->next = p;
		p->prior=prior;
        rear = p;
        i++;
    }
    rear->next = NULL;
    fclose(fp);
    return;
}
void account_save(account_List account_head)//存入账户数据到磁盘
{
    account_List rear = account_head->next;
    FILE *fp;
    int sum,i=1;
    sum = rear->num+1;
    fp = fopen("Account information.dat","wb");
    while(i<=sum)
    {
        fwrite(rear,sizeof(account_Lnode),1,fp);
        rear = rear->next;
        i++;
    }
    fclose(fp);
    return;
}

void college_load(college_List college_head) //载入学院数据，双向链表
{
    college_List rear = college_head,p,prior;
    FILE *fp;
    int i=0,sum;

    fp = fopen("College information.dat","rb");
	if(fp == NULL)
    {
        identity=-2;
        return;
    }
    p = (college_List)malloc(sizeof(college_Lnode));
    fread(p,sizeof(college_Lnode),1,fp);i++;
    sum = p->num;
	prior=rear;
    rear->next = p;
	p->prior=prior;
    rear = p;
	if(sum==0)
		rear->next=NULL;
    while(i<=sum)
    {
        p = (college_List)malloc(sizeof(college_Lnode));
        if(fread(p,sizeof(college_Lnode),1,fp)==0)
        break;
		prior = rear;
        rear->next = p;
		p->prior=prior;
        rear = p;
        i++;
    }
    rear->next = NULL;
    fclose(fp);
    return;
}
void college_save(college_List college_head)//存入学院数据到磁盘
{
    college_List rear = college_head->next;
    FILE *fp;
    int sum,i=1;
    sum = rear->num+1;
    fp = fopen("College information.dat","wb");
    while(i<=sum)
    {
        fwrite(rear,sizeof(college_Lnode),1,fp);
        rear = rear->next;
        i++;
    }
    fclose(fp);
    return;
}
void profession_load(profession_List profession_head) //载入专业数据
{
    profession_List rear = profession_head,p,prior;
    FILE *fp;
    int i=0,sum;

    fp = fopen("Profession information.dat","rb");
	if(fp == NULL)
    {
        identity=-2;
        return;
    }
    p = (profession_List)malloc(sizeof(profession_Lnode));
    fread(p,sizeof(profession_Lnode),1,fp);i++;
    sum = p->num;
	prior=rear;
    rear->next = p;
	p->prior=prior;
    rear = p;
	if(sum==0)
		rear->next=NULL;
    while(i<=sum)
    {
        p = (profession_List)malloc(sizeof(profession_Lnode));
        if(fread(p,sizeof(profession_Lnode),1,fp)==0)
        break;
		prior = rear;
        rear->next = p;
		p->prior=prior;
        rear = p;
        i++;
    }
    rear->next = NULL;
    fclose(fp);
    return;
}
void profession_save(profession_List profession_head)//存入专业数据到磁盘
{
    profession_List rear = profession_head->next;
    FILE *fp;
    int sum,i=1;
    sum = rear->num+1;
    fp = fopen("Profession information.dat","wb");
    while(i<=sum)
    {
        fwrite(rear,sizeof(profession_Lnode),1,fp);
        rear = rear->next;
        i++;
    }
    fclose(fp);
    return;
}
void course_load(course_List course_head) //载入课程数据
{
    course_List rear = course_head,p,prior;
    FILE *fp;
    int i=0,sum;

    fp = fopen("Course information.dat","rb");
	if(fp == NULL)
    {
        identity=-2;
        return;
    }
    p = (course_List)malloc(sizeof(course_Lnode));
    fread(p,sizeof(course_Lnode),1,fp);i++;
    sum = p->num;
	prior=rear;
    rear->next = p;
	p->prior=prior;
    rear = p;
	if(sum==0)
		rear->next=NULL;
    while(i<=sum)
    {
        p = (course_List)malloc(sizeof(course_Lnode));
        if(fread(p,sizeof(course_Lnode),1,fp)==0)
        break;
		prior = rear;
        rear->next = p;
		p->prior=prior;
        rear = p;
        i++;
    }
    rear->next = NULL;
    fclose(fp);
    return;
}
void course_save(course_List course_head)//存入课程数据到磁盘
{
    course_List rear = course_head->next;
    FILE *fp;
    int sum,i=1;
    sum = rear->num+1;
    fp = fopen("Course information.dat","wb");
    while(i<=sum)
    {
        fwrite(rear,sizeof(course_Lnode),1,fp);
        rear = rear->next;
        i++;
    }
    fclose(fp);
    return;
}
void class_load(class_List class_head) //载入班级数据
{
    class_List rear = class_head,p,prior;
    FILE *fp;
    int i=0,sum;

    fp = fopen("Class information.dat","rb");
	if(fp == NULL)
    {
        identity=-2;
        return;
    }
    p = (class_List)malloc(sizeof(class_Lnode));
    fread(p,sizeof(class_Lnode),1,fp);i++;
    sum = p->num;
	prior=rear;
    rear->next = p;
	p->prior=prior;
    rear = p;
	if(sum==0)
		rear->next=NULL;
    while(i<=sum)
    {
        p = (class_List)malloc(sizeof(class_Lnode));
        if(fread(p,sizeof(class_Lnode),1,fp)==0)
        break;
		prior = rear;
        rear->next = p;
		p->prior=prior;
        rear = p;
        i++;
    }
    rear->next = NULL;
    fclose(fp);
    return;
}
void class_save(class_List class_head)//存入班级数据到磁盘
{
    class_List rear = class_head->next;
    FILE *fp;
    int sum,i=1;
    sum = rear->num+1;
    fp = fopen("Class information.dat","wb");
    while(i<=sum)
    {
        fwrite(rear,sizeof(class_Lnode),1,fp);
        rear = rear->next;
        i++;
    }
    fclose(fp);
    return;
}
void teacher_load(teacher_List teacher_head) //载入教师数据
{
    {
    teacher_List rear = teacher_head,p,prior;
    FILE *fp;
    int i=0,sum;

    fp = fopen("Teacher information.dat","rb");
	if(fp == NULL)
    {
        identity=-2;
        return;
    }
    p = (teacher_List)malloc(sizeof(teacher_Lnode));
    fread(p,sizeof(teacher_Lnode),1,fp);i++;
    sum = p->num;
	prior=rear;
    rear->next = p;
	p->prior=prior;
    rear = p;
	if(sum==0)
		rear->next=NULL;
    while(i<=sum)
    {
        p = (teacher_List)malloc(sizeof(teacher_Lnode));
        if(fread(p,sizeof(teacher_Lnode),1,fp)==0)
        break;
		prior = rear;
        rear->next = p;
		p->prior=prior;
        rear = p;
        i++;
    }
    rear->next = NULL;
    fclose(fp);
    return;
}

}
void teacher_save(teacher_List teacher_head)//存入教师数据到磁盘
{
    teacher_List rear = teacher_head->next;
    FILE *fp;
    int sum,i=1;
    sum = rear->num+1;
    fp = fopen("Teacher information.dat","wb");
    while(i<=sum)
    {
        fwrite(rear,sizeof(teacher_Lnode),1,fp);
        rear = rear->next;
        i++;
    }
    fclose(fp);
    return;
}
void student_load(student_List student_head) //载入学生数据
{
    {
    student_List rear = student_head,p,prior;
    FILE *fp;
    int i=0,sum;

    fp = fopen("Student information.dat","rb");
	if(fp == NULL)
    {
        identity=-2;
        return;
    }
    p = (student_List)malloc(sizeof(student_Lnode));
    fread(p,sizeof(student_Lnode),1,fp);i++;
    sum = p->num;
	prior=rear;
    rear->next = p;
	p->prior=prior;
    rear = p;
	if(sum==0)
		rear->next=NULL;
    while(i<=sum)
    {
        p = (student_List)malloc(sizeof(student_Lnode));
        if(fread(p,sizeof(student_Lnode),1,fp)==0)
        break;
		prior = rear;
        rear->next = p;
		p->prior=prior;
        rear = p;
        i++;
    }
    rear->next = NULL;
    fclose(fp);
    return;
}

}
void student_save(student_List student_head)//存入学生数据到磁盘
{
    student_List rear = student_head->next;
    FILE *fp;
    int sum,i=1;
    sum = rear->num+1;
    fp = fopen("Student information.dat","wb");
    while(i<=sum)
    {
        fwrite(rear,sizeof(student_Lnode),1,fp);
        rear = rear->next;
        i++;
    }
    fclose(fp);
    return;
}
void score_load(score_List score_head) //载入成绩数据
{
    score_List rear = score_head,p,prior;
    FILE *fp;
    int i=0,sum;

    fp = fopen("Score information.dat","rb");
	if(fp == NULL)
    {
        identity=-2;
        return;
    }
    p = (score_List)malloc(sizeof(score_Lnode));
    fread(p,sizeof(score_Lnode),1,fp);i++;
    sum = p->num;
	prior=rear;
    rear->next = p;
	p->prior=prior;
    rear = p;
	if(sum==0)
		rear->next=NULL;
    while(i<=sum)
    {
        p = (score_List)malloc(sizeof(score_Lnode));
        if(fread(p,sizeof(score_Lnode),1,fp)==0)
        break;
		prior = rear;
        rear->next = p;
		p->prior=prior;
        rear = p;
        i++;
    }
    rear->next = NULL;
    fclose(fp);
    return;
}
void score_save(score_List score_head)//存入班级数据到磁盘
{
    score_List rear = score_head->next;
    FILE *fp;
    int sum,i=1;
    sum = rear->num+1;
    fp = fopen("Score information.dat","wb");
    while(i<=sum)
    {
        fwrite(rear,sizeof(score_Lnode),1,fp);
        rear = rear->next;
        i++;
    }
    fclose(fp);
    return;
}
int loading(char id[20],char password[20],account_List account_mine)//1.管理员，2.教师，3.学生，4.账号错误，5.密码错误,-1.初始，-2.初始化
{
    account_List p;
	teacher_List p_teacher;
	student_List p_student;

    int sum,i,j;
    j=4;
    p = account_head->next;
    sum = p->num;
    for(i=0;i<sum;i++)
    {
        p=p->next;
        if(strcmp(p->id,id)==0)
        {
            j=5;
            if(strcmp(p->password,password)==0)
            {
                if(strcmp(p->identity,"管理员")==0)
				    j=1;
				account_mine->num=p->num;
				strcpy(account_mine->id,p->id);
				strcpy(account_mine->password,p->password);
				strcpy(account_mine->name,p->name);
				strcpy(account_mine->sex,p->sex);
				strcpy(account_mine->identity,p->identity);
				strcpy(account_mine->nation,p->nation);
				strcpy(account_mine->face,p->face);
				strcpy(account_mine->birth,p->birth);
				strcpy(account_mine->time,p->time);
				strcpy(account_mine->college,p->college);
				account_mine->collegeid=p->collegeid;
				strcpy(account_mine->profession,p->profession);
				account_mine->professionid=p->professionid;
                break;
            }
        }
    }
	if(j!=1&&j!=3)
	{
		p_teacher = teacher_head->next;
    sum = p_teacher->num;
    for(i=0;i<sum;i++)
    {
        p_teacher=p_teacher->next;
        if(strcmp(p_teacher->id,id)==0)
        {
            j=5;
			
            if(strcmp(p_teacher->password,password)==0)
            {
                if(strcmp(p_teacher->identity,"教师")==0)
				    j=2;
				account_mine->num=p_teacher->num;
				strcpy(account_mine->id,p_teacher->id);
				strcpy(account_mine->password,p_teacher->password);
				strcpy(account_mine->name,p_teacher->name);
				strcpy(account_mine->sex,p_teacher->sex);
				strcpy(account_mine->identity,p_teacher->identity);
				strcpy(account_mine->nation,p_teacher->nation);
				strcpy(account_mine->face,p_teacher->face);
				strcpy(account_mine->birth,p_teacher->birth);
				strcpy(account_mine->time,p_teacher->time);
				strcpy(account_mine->college,p_teacher->college);
				account_mine->collegeid=p_teacher->collegeid;
				strcpy(account_mine->profession,p_teacher->profession);
				account_mine->professionid=p_teacher->professionid;
                break;
            }
        }
    }
	}
	if(j!=1&&j!=2)
	{
		p_student = student_head->next;
    sum = p_student->num;
    for(i=0;i<sum;i++)
    {
        p_student=p_student->next;
        if(strcmp(p_student->id,id)==0)
        {
            j=5;
            if(strcmp(p_student->password,password)==0)
            {
                if(strcmp(p_student->identity,"学生")==0)
				    j=3;
				account_mine->num=p_student->num;
				strcpy(account_mine->id,p_student->id);
				strcpy(account_mine->password,p_student->password);
				strcpy(account_mine->name,p_student->name);
				strcpy(account_mine->sex,p_student->sex);
				strcpy(account_mine->identity,p_student->identity);
				strcpy(account_mine->nation,p_student->nation);
				strcpy(account_mine->face,p_student->face);
				strcpy(account_mine->birth,p_student->birth);
				strcpy(account_mine->time,p_student->time);
				strcpy(account_mine->college,p_student->college);
				account_mine->collegeid=p_student->collegeid;
				strcpy(account_mine->profession,p_student->profession);
				account_mine->professionid=p_student->professionid;
                break;
            }
        }
    }
	}
    return j;
}

void initialize_college(college_List college_head)//初始化学院数据
{
    college_List p,prior,rear;
    rear=college_head;
    p=(college_List)malloc(sizeof(college_Lnode));
    prior=college_head;
    rear->next=p;
    //令数据条数为1
    p->num=17;
    p->prior=prior;
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=1;
    p->num=1;
    strcpy(p->name,"粮油食品学院");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=2;
    p->num=2;
    strcpy(p->name,"机电工程学院");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=3;
    p->num=3;
    strcpy(p->name,"土木建筑学院");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=4;
    p->num=4;
    strcpy(p->name,"信息科学与工程学院");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=5;
    p->num=5;
    strcpy(p->name,"化学化工与环境学院");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=6;
    p->num=6;
    strcpy(p->name,"生物工程学院");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=7;
    p->num=7;
    strcpy(p->name,"材料科学与工程学院");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=8;
    p->num=8;
    strcpy(p->name,"电气工程学院");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=9;
    p->num=9;
    strcpy(p->name,"管理学院");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=10;
    p->num=10;
    strcpy(p->name,"经济贸易学院");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=11;
    p->num=11;
    strcpy(p->name,"理学院");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=12;
    p->num=12;
    strcpy(p->name,"外语学院");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=13;
    p->num=13;
    strcpy(p->name,"法学院");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=14;
    p->num=14;
    strcpy(p->name,"新闻与传播学院");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=15;
    p->num=15;
    strcpy(p->name,"设计艺术学院");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=16;
    p->num=16;
    strcpy(p->name,"国际教育学院");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=17;
    p->num=17;
    strcpy(p->name,"中英国际学院");
    rear=p;

    rear->next=NULL;
    college_save(college_head);
}
void initialize_profession(profession_List profession_head)//初始化专业数据
{
    profession_List p,prior,rear;
    rear=profession_head;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    prior=profession_head;
    rear->next=p;
    //令数据条数为1
    p->num=76;
    p->prior=prior;
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=1;//指定专业代码
    p->num=1;//制定记录代码
    strcpy(p->name,"粮食工程专业");
    strcpy(p->college,"粮油食品学院");
    p->college_id=1;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=2;
    p->num=2;
    strcpy(p->name,"食品科学与工程专业");
    strcpy(p->college,"粮油食品学院");
    p->college_id=1;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=3;
    p->num=3;
    strcpy(p->name,"食品质量与安全专业");
    strcpy(p->college,"粮油食品学院");
    p->college_id=1;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=4;
    p->num=4;
    strcpy(p->name,"食品营养与检验教育专业");
    strcpy(p->college,"粮油食品学院");
    p->college_id=1;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=5;
    p->num=5;
    strcpy(p->name,"机械设计制造及其自动化专业");
    strcpy(p->college,"机电工程学院");
    p->college_id=2;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=6;
    p->num=6;
    strcpy(p->name,"过程装备与控制工程专业");
    strcpy(p->college,"机电工程学院");
    p->college_id=2;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=7;
    p->num=7;
    strcpy(p->name,"材料成型及控制工程专业");
    strcpy(p->college,"机电工程学院");
    p->college_id=2;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=8;
    p->num=8;
    strcpy(p->name,"车辆工程专业");
    strcpy(p->college,"机电工程学院");
    p->college_id=2;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=9;
    p->num=9;
    strcpy(p->name,"包装工程工程专业");
    strcpy(p->college,"机电工程学院");
    p->college_id=2;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=10;
    p->num=10;
    strcpy(p->name,"土木工程");
    strcpy(p->college,"土木建筑学院");
    p->college_id=3;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=11;
    p->num=11;
    strcpy(p->name,"道路桥梁与渡河工程");
    strcpy(p->college,"土木建筑学院");
    p->college_id=3;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=12;
    p->num=12;
    strcpy(p->name,"建筑环境与能源应用工程");
    strcpy(p->college,"土木建筑学院");
    p->college_id=3;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=13;
    p->num=13;
    strcpy(p->name,"工程管理");
    strcpy(p->college,"土木建筑学院");
    p->college_id=3;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=14;
    p->num=14;
    strcpy(p->name,"建筑学专业");
    strcpy(p->college,"土木建筑学院");
    p->college_id=3;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=15;
    p->num=15;
    strcpy(p->name,"交通工程专业");
    strcpy(p->college,"土木建筑学院");
    p->college_id=3;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=16;
    p->num=16;
    strcpy(p->name,"物联网工程专业");
    strcpy(p->college,"信息科学与工程学院");
    p->college_id=4;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=17;
    p->num=17;
    strcpy(p->name,"计算机科学与技术专业");
    strcpy(p->college,"信息科学与工程学院");
    p->college_id=4;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=18;
    p->num=18;
    strcpy(p->name,"电子信息工程专业");
    strcpy(p->college,"信息科学与工程学院");
    p->college_id=4;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=19;
    p->num=19;
    strcpy(p->name,"空间信息与数字技术");
    strcpy(p->college,"信息科学与工程学院");
    p->college_id=4;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=20;
    p->num=20;
    strcpy(p->name,"软件工程专业");
    strcpy(p->college,"信息科学与工程学院");
    p->college_id=4;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=21;
    p->num=21;
    strcpy(p->name,"通信工程专业");
    strcpy(p->college,"信息科学与工程学院");
    p->college_id=4;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=22;
    p->num=22;
    strcpy(p->name,"化学工程与工艺专业");
    strcpy(p->college,"化学化工与环境学院");
    p->college_id=5;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=23;
    p->num=23;
    strcpy(p->name,"应用化学专业");
    strcpy(p->college,"化学化工与环境学院");
    p->college_id=5;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=24;
    p->num=24;
    strcpy(p->name,"环境工程专业");
    strcpy(p->college,"化学化工与环境学院");
    p->college_id=5;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=25;
    p->num=25;
    strcpy(p->name,"化学专业");
    strcpy(p->college,"化学化工与环境学院");
    p->college_id=5;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=26;
    p->num=26;
    strcpy(p->name,"生物工程专业");
    strcpy(p->college,"生物工程学院");
    p->college_id=6;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=27;
    p->num=27;
    strcpy(p->name,"动物科学专业");
    strcpy(p->college,"生物工程学院");
    p->college_id=6;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=28;
    p->num=28;
    strcpy(p->name,"生物技术专业");
    strcpy(p->college,"生物工程学院");
    p->college_id=6;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=29;
    p->num=29;
    strcpy(p->name,"制药工程专业");
    strcpy(p->college,"生物工程学院");
    p->college_id=6;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=30;
    p->num=30;
    strcpy(p->name,"材料科学与工程专业");
    strcpy(p->college,"材料科学与工程学院");
    p->college_id=7;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=31;
    p->num=31;
    strcpy(p->name,"高分子材料与工程专业");
    strcpy(p->college,"材料科学与工程学院");
    p->college_id=7;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=32;
    p->num=32;
    strcpy(p->name,"无机非金属材料工程专业");
    strcpy(p->college,"材料科学与工程学院");
    p->college_id=7;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=33;
    p->num=33;
    strcpy(p->name,"自动化");
    strcpy(p->college,"电气工程学院");
    p->college_id=8;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=34;
    p->num=34;
    strcpy(p->name,"电气工程及其自动化");
    strcpy(p->college,"电气工程学院");
    p->college_id=8;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=35;
    p->num=35;
    strcpy(p->name,"测控技术与仪器");
    strcpy(p->college,"电气工程学院");
    p->college_id=8;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=36;
    p->num=36;
    strcpy(p->name,"轨道交通信号与控制");
    strcpy(p->college,"电气工程学院");
    p->college_id=8;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=37;
    p->num=37;
    strcpy(p->name,"电子商务专业");
    strcpy(p->college,"管理学院");
    p->college_id=9;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=38;
    p->num=38;
    strcpy(p->name,"物流管理专业");
    strcpy(p->college,"管理学院");
    p->college_id=9;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=39;
    p->num=39;
    strcpy(p->name,"工商管理专业");
    strcpy(p->college,"管理学院");
    p->college_id=9;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=40;
    p->num=40;
    strcpy(p->name,"旅游管理专业");
    strcpy(p->college,"管理学院");
    p->college_id=9;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=41;
    p->num=41;
    strcpy(p->name,"财务管理专业");
    strcpy(p->college,"管理学院");
    p->college_id=9;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=42;
    p->num=42;
    strcpy(p->name,"金融学专业");
    strcpy(p->college,"经济贸易学院");
    p->college_id=10;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=43;
    p->num=43;
    strcpy(p->name,"国际经济与贸易专业");
    strcpy(p->college,"经济贸易学院");
    p->college_id=10;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=44;
    p->num=44;
    strcpy(p->name,"财政学专业");
    strcpy(p->college,"经济贸易学院");
    p->college_id=10;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=45;
    p->num=45;
    strcpy(p->name,"经济学专业");
    strcpy(p->college,"经济贸易学院");
    p->college_id=10;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=46;
    p->num=46;
    strcpy(p->name,"数学与应用数学专业");
    strcpy(p->college,"理学院");
    p->college_id=11;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=47;
    p->num=47;
    strcpy(p->name,"信息与计算科学专业");
    strcpy(p->college,"理学院");
    p->college_id=11;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=48;
    p->num=48;
    strcpy(p->name,"应用统计学专业");
    strcpy(p->college,"理学院");
    p->college_id=11;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=49;
    p->num=49;
    strcpy(p->name,"应用物理学专业");
    strcpy(p->college,"理学院");
    p->college_id=11;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=50;
    p->num=50;
    strcpy(p->name,"英语专业");
    strcpy(p->college,"外语学院");
    p->college_id=12;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=51;
    p->num=51;
    strcpy(p->name,"翻译专业");
    strcpy(p->college,"外语学院");
    p->college_id=12;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=52;
    p->num=52;
    strcpy(p->name,"法学");
    strcpy(p->college,"法学院");
    p->college_id=13;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=53;
    p->num=53;
    strcpy(p->name,"广告学专业");
    strcpy(p->college,"新闻与传播学院");
    p->college_id=14;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=54;
    p->num=54;
    strcpy(p->name,"广播电视学专业");
    strcpy(p->college,"新闻与传播学院");
    p->college_id=14;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=55;
    p->num=55;
    strcpy(p->name,"网络与新媒体专业");
    strcpy(p->college,"新闻与传播学院");
    p->college_id=14;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=56;
    p->num=56;
    strcpy(p->name,"播音与主持艺术专业");
    strcpy(p->college,"新闻与传播学院");
    p->college_id=14;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=57;
    p->num=57;
    strcpy(p->name,"产品设计专业");
    strcpy(p->college,"设计艺术学院");
    p->college_id=15;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=58;
    p->num=58;
    strcpy(p->name,"视觉传达设计专业");
    strcpy(p->college,"设计艺术学院");
    p->college_id=15;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=59;
    p->num=59;
    strcpy(p->name,"环境设计专业");
    strcpy(p->college,"设计艺术学院");
    p->college_id=15;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=60;
    p->num=60;
    strcpy(p->name,"数字媒体艺术专业");
    strcpy(p->college,"设计艺术学院");
    p->college_id=15;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=61;
    p->num=61;
    strcpy(p->name,"动画");
    strcpy(p->college,"设计艺术学院");
    p->college_id=15;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=62;
    p->num=62;
    strcpy(p->name,"食品科学与工程专业");
    strcpy(p->college,"国际教育学院");
    p->college_id=16;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=63;
    p->num=63;
    strcpy(p->name,"生物技术专业");
    strcpy(p->college,"国际教育学院");
    p->college_id=16;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=64;
    p->num=64;
    strcpy(p->name,"人力资源管理专业");
    strcpy(p->college,"国际教育学院");
    p->college_id=16;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=65;
    p->num=65;
    strcpy(p->name,"市场营销专业");
    strcpy(p->college,"国际教育学院");
    p->college_id=16;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=66;
    p->num=66;
    strcpy(p->name,"会计学专业");
    strcpy(p->college,"国际教育学院");
    p->college_id=16;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=67;
    p->num=67;
    strcpy(p->name,"食品营养与检测专业");
    strcpy(p->college,"国际教育学院");
    p->college_id=16;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=68;
    p->num=68;
    strcpy(p->name,"机械制造与自动化专业");
    strcpy(p->college,"中英国际学院");
    p->college_id=17;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=69;
    p->num=69;
    strcpy(p->name,"汽车营销与服务专业");
    strcpy(p->college,"中英国际学院");
    p->college_id=17;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=70;
    p->num=70;
    strcpy(p->name,"工程造价专业");
    strcpy(p->college,"中英国际学院");
    p->college_id=17;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=71;
    p->num=71;
    strcpy(p->name,"会计专业");
    strcpy(p->college,"中英国际学院");
    p->college_id=17;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=72;
    p->num=72;
    strcpy(p->name,"证券与期货专业");
    strcpy(p->college,"中英国际学院");
    p->college_id=17;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=73;
    p->num=73;
    strcpy(p->name,"艺术设计专业");
    strcpy(p->college,"中英国际学院");
    p->college_id=17;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=74;
    p->num=74;
    strcpy(p->name,"播音与主持专业");
    strcpy(p->college,"中英国际学院");
    p->college_id=17;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=75;
    p->num=75;
    strcpy(p->name,"软件技术专业");
    strcpy(p->college,"中英国际学院");
    p->college_id=17;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=76;
    p->num=76;
    strcpy(p->name,"信息安全与管理专业");
    strcpy(p->college,"中英国际学院");
    p->college_id=17;//指定所属学院代码
    rear=p;

    rear->next=NULL;
    profession_save(profession_head);
}
void initialize_course(course_List course_head)//初始化课程数据
{
    course_List p,prior,rear;
    rear=course_head;
    p=(course_List)malloc(sizeof(course_Lnode));
    prior=course_head;
    rear->next=p;
    //令数据条数为1
    p->num=25;
    p->prior=prior;
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=1;
    p->num=1;
    strcpy(p->name,"大学英语");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=2;
    p->num=2;
    strcpy(p->name,"高等数学");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=3;
    p->num=3;
    strcpy(p->name,"思想道德与法律修养");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=4;
    p->num=4;
    strcpy(p->name,"职业发展教育与就业指导");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=5;
    p->num=5;
    strcpy(p->name,"形式与政策");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=6;
    p->num=6;
    strcpy(p->name,"大学物理");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=7;
    p->num=7;
    strcpy(p->name,"线性代数");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=8;
    p->num=8;
    strcpy(p->name,"程序设计基础");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=9;
    p->num=9;
    strcpy(p->name,"概率论与数理统计");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=10;
    p->num=10;
    strcpy(p->name,"马克思主义基本原理概论");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=11;
    p->num=11;
    strcpy(p->name,"毛泽东思想和中国特色社会主义理论体系概论");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=12;
    p->num=12;
    strcpy(p->name,"计算机导论");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=13;
    p->num=13;
    strcpy(p->name,"数据结构与算法");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=14;
    p->num=14;
    strcpy(p->name,"卫星导航定位系统");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=15;
    p->num=15;
    strcpy(p->name,"计算机图形学");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=16;
    p->num=16;
    strcpy(p->name," 地图学");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=17;
    p->num=17;
    strcpy(p->name,"遥感影像处理与应用");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=18;
    p->num=18;
    strcpy(p->name,"GIS开发与应用");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=19;
    p->num=19;
    strcpy(p->name,"软件工程");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=20;
    p->num=20;
    strcpy(p->name,"智能粮仓技术");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=21;
    p->num=21;
    strcpy(p->name,"虚拟地理环境与仿真");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=22;
    p->num=22;
    strcpy(p->name,"地理学导论");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=23;
    p->num=23;
    strcpy(p->name," C#编程和.NET框架");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=24;
    p->num=24;
    strcpy(p->name," 物联网技术导论");
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=25;
    p->num=25;
    strcpy(p->name,"音乐鉴赏");
    rear=p;

    rear->next=NULL;
    course_save(course_head);
}
void initialize_class(class_List class_head)//初始化专业数据
{
    class_List p,prior,rear;
    rear=class_head;
    p=(class_List)malloc(sizeof(class_Lnode));
    prior=class_head;
    rear->next=p;
    //令数据条数为1
    p->num=76;
    p->prior=prior;
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=1;//指定专业代码
    p->num=1;//制定记录代码
    strcpy(p->profession,"粮食工程专业");
    strcpy(p->college,"粮油食品学院");
    strcpy(p->name,"粮食工程专业1601");
    p->college_id=1;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=2;
    p->num=2;
    strcpy(p->profession,"食品科学与工程专业");
    strcpy(p->college,"粮油食品学院");
    strcpy(p->name,"食品科学与工程专业1601");
    p->college_id=1;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=3;
    p->num=3;
    strcpy(p->profession,"食品质量与安全专业");
    strcpy(p->college,"粮油食品学院");
    strcpy(p->name,"食品质量与安全专业1601");
    p->college_id=1;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=4;
    p->num=4;
    strcpy(p->profession,"食品营养与检验教育专业");
    strcpy(p->college,"粮油食品学院");
    strcpy(p->name,"食品营养与检验教育专业1601");
    p->college_id=1;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=5;
    p->num=5;
    strcpy(p->profession,"机械设计制造及其自动化专业");
    strcpy(p->college,"机电工程学院");
    strcpy(p->name,"机械设计制造及其自动化专业1601");
    p->college_id=2;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=6;
    p->num=6;
    strcpy(p->profession,"过程装备与控制工程专业");
    strcpy(p->college,"机电工程学院");
    strcpy(p->name,"过程装备与控制工程专业1601");
    p->college_id=2;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=7;
    p->num=7;
    strcpy(p->profession,"材料成型及控制工程专业");
    strcpy(p->college,"机电工程学院");
    strcpy(p->name,"材料成型及控制工程专业1601");
    p->college_id=2;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=8;
    p->num=8;
    strcpy(p->profession,"车辆工程专业");
    strcpy(p->college,"机电工程学院");
    strcpy(p->name,"车辆工程专业1601");
    p->college_id=2;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=9;
    p->num=9;
    strcpy(p->profession,"包装工程工程专业");
    strcpy(p->college,"机电工程学院");
    strcpy(p->name,"包装工程工程专业1601");
    p->college_id=2;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=10;
    p->num=10;
    strcpy(p->profession,"土木工程");
    strcpy(p->college,"土木建筑学院");
    strcpy(p->name,"土木工程1601");
    p->college_id=3;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=11;
    p->num=11;
    strcpy(p->profession,"道路桥梁与渡河工程");
    strcpy(p->college,"土木建筑学院");
    strcpy(p->name,"道路桥梁与渡河工程1601");
    p->college_id=3;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=12;
    p->num=12;
    strcpy(p->profession,"建筑环境与能源应用工程");
    strcpy(p->college,"土木建筑学院");
    strcpy(p->name,"建筑环境与能源应用工程1601");
    p->college_id=3;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=13;
    p->num=13;
    strcpy(p->profession,"工程管理");
    strcpy(p->college,"土木建筑学院");
    strcpy(p->name,"工程管理1601");
    p->college_id=3;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=14;
    p->num=14;
    strcpy(p->profession,"建筑学专业");
    strcpy(p->college,"土木建筑学院");
    strcpy(p->name,"建筑学专业1601");
    p->college_id=3;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=15;
    p->num=15;
    strcpy(p->profession,"交通工程专业");
    strcpy(p->college,"土木建筑学院");
    strcpy(p->name,"交通工程专业1601");
    p->college_id=3;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=16;
    p->num=16;
    strcpy(p->profession,"物联网工程专业");
    strcpy(p->college,"信息科学与工程学院");
    strcpy(p->name,"物联网工程专业1601");
    p->college_id=4;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=17;
    p->num=17;
    strcpy(p->profession,"计算机科学与技术专业");
    strcpy(p->college,"信息科学与工程学院");
    strcpy(p->name,"计算机科学与技术专业1601");
    p->college_id=4;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=18;
    p->num=18;
    strcpy(p->profession,"电子信息工程专业");
    strcpy(p->college,"信息科学与工程学院");
    strcpy(p->name,"电子信息工程专业1601");
    p->college_id=4;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=19;
    p->num=19;
    strcpy(p->profession,"空间信息与数字技术");
    strcpy(p->college,"信息科学与工程学院");
    strcpy(p->name,"空间信息与数字技术1601");
    p->college_id=4;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=20;
    p->num=20;
    strcpy(p->profession,"软件工程专业");
    strcpy(p->college,"信息科学与工程学院");
    strcpy(p->name,"软件工程专业1601");
    p->college_id=4;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=21;
    p->num=21;
    strcpy(p->profession,"通信工程专业");
    strcpy(p->college,"信息科学与工程学院");
    strcpy(p->name,"通信工程专业1601");
    p->college_id=4;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=22;
    p->num=22;
    strcpy(p->profession,"化学工程与工艺专业");
    strcpy(p->college,"化学化工与环境学院");
    strcpy(p->name,"化学工程与工艺专业1601");
    p->college_id=5;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=23;
    p->num=23;
    strcpy(p->profession,"应用化学专业");
    strcpy(p->college,"化学化工与环境学院");
    strcpy(p->name,"应用化学专业1601");
    p->college_id=5;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=24;
    p->num=24;
    strcpy(p->profession,"环境工程专业");
    strcpy(p->college,"化学化工与环境学院");
    strcpy(p->name,"环境工程专业1601");
    p->college_id=5;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=25;
    p->num=25;
    strcpy(p->profession,"化学专业");
    strcpy(p->college,"化学化工与环境学院");
    strcpy(p->name,"化学专业1601");
    p->college_id=5;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=26;
    p->num=26;
    strcpy(p->profession,"生物工程专业");
    strcpy(p->college,"生物工程学院");
    strcpy(p->name,"生物工程专业1601");
    p->college_id=6;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=27;
    p->num=27;
    strcpy(p->profession,"动物科学专业");
    strcpy(p->college,"生物工程学院");
    strcpy(p->name,"动物科学专业1601");
    p->college_id=6;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=28;
    p->num=28;
    strcpy(p->profession,"生物技术专业");
    strcpy(p->college,"生物工程学院");
    strcpy(p->name,"生物技术专业1601");
    p->college_id=6;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=29;
    p->num=29;
    strcpy(p->profession,"制药工程专业");
    strcpy(p->college,"生物工程学院");
    strcpy(p->name,"制药工程专业1601");
    p->college_id=6;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=30;
    p->num=30;
    strcpy(p->profession,"材料科学与工程专业");
    strcpy(p->college,"材料科学与工程学院");
    strcpy(p->name,"材料科学与工程专业1601");
    p->college_id=7;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=31;
    p->num=31;
    strcpy(p->profession,"高分子材料与工程专业");
    strcpy(p->college,"材料科学与工程学院");
    strcpy(p->name,"高分子材料与工程专业1601");
    p->college_id=7;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=32;
    p->num=32;
    strcpy(p->profession,"无机非金属材料工程专业");
    strcpy(p->college,"材料科学与工程学院");
    strcpy(p->name,"无机非金属材料工程专业1601");
    p->college_id=7;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=33;
    p->num=33;
    strcpy(p->profession,"自动化");
    strcpy(p->college,"电气工程学院");
    strcpy(p->name,"自动化1601");
    p->college_id=8;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=34;
    p->num=34;
    strcpy(p->profession,"电气工程及其自动化");
    strcpy(p->college,"电气工程学院");
    strcpy(p->name,"电气工程及其自动化1601");
    p->college_id=8;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=35;
    p->num=35;
    strcpy(p->profession,"测控技术与仪器");
    strcpy(p->college,"电气工程学院");
    strcpy(p->name,"测控技术与仪器1601");
    p->college_id=8;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=36;
    p->num=36;
    strcpy(p->profession,"轨道交通信号与控制");
    strcpy(p->college,"电气工程学院");
    strcpy(p->name,"轨道交通信号与控制1601");
    p->college_id=8;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=37;
    p->num=37;
    strcpy(p->profession,"电子商务专业");
    strcpy(p->college,"管理学院");
    strcpy(p->name,"电子商务专业1601");
    p->college_id=9;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=38;
    p->num=38;
    strcpy(p->profession,"物流管理专业");
    strcpy(p->college,"管理学院");
    strcpy(p->name,"物流管理专业1601");
    p->college_id=9;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=39;
    p->num=39;
    strcpy(p->profession,"工商管理专业");
    strcpy(p->college,"管理学院");
    strcpy(p->name,"工商管理专业1601");
    p->college_id=9;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=40;
    p->num=40;
    strcpy(p->profession,"旅游管理专业");
    strcpy(p->college,"管理学院");
    strcpy(p->name,"旅游管理专业1601");
    p->college_id=9;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=41;
    p->num=41;
    strcpy(p->profession,"财务管理专业");
    strcpy(p->college,"管理学院");
    strcpy(p->name,"财务管理专业1601");
    p->college_id=9;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=42;
    p->num=42;
    strcpy(p->profession,"金融学专业");
    strcpy(p->college,"经济贸易学院");
    strcpy(p->name,"金融学专业1601");
    p->college_id=10;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=43;
    p->num=43;
    strcpy(p->profession,"国际经济与贸易专业");
    strcpy(p->college,"经济贸易学院");
    strcpy(p->name,"国际经济与贸易专业1601");
    p->college_id=10;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=44;
    p->num=44;
    strcpy(p->profession,"财政学专业");
    strcpy(p->college,"经济贸易学院");
    strcpy(p->name,"财政学专业1601");
    p->college_id=10;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=45;
    p->num=45;
    strcpy(p->profession,"经济学专业");
    strcpy(p->college,"经济贸易学院");
    strcpy(p->name,"经济学专业1601");
    p->college_id=10;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=46;
    p->num=46;
    strcpy(p->profession,"数学与应用数学专业");
    strcpy(p->college,"理学院");
    strcpy(p->name,"数学与应用数学专业1601");
    p->college_id=11;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=47;
    p->num=47;
    strcpy(p->profession,"信息与计算科学专业");
    strcpy(p->college,"理学院");
    strcpy(p->name,"信息与计算科学专业1601");
    p->college_id=11;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=48;
    p->num=48;
    strcpy(p->profession,"应用统计学专业");
    strcpy(p->college,"理学院");
    strcpy(p->name,"应用统计学专业1601");
    p->college_id=11;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=49;
    p->num=49;
    strcpy(p->profession,"应用物理学专业");
    strcpy(p->college,"理学院");
    strcpy(p->name,"应用物理学专业1601");
    p->college_id=11;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=50;
    p->num=50;
    strcpy(p->profession,"英语专业");
    strcpy(p->college,"外语学院");
    strcpy(p->name,"英语专业1601");
    p->college_id=12;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=51;
    p->num=51;
    strcpy(p->profession,"翻译专业");
    strcpy(p->college,"外语学院");
    strcpy(p->name,"翻译专业1601");
    p->college_id=12;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=52;
    p->num=52;
    strcpy(p->profession,"法学");
    strcpy(p->college,"法学院");
    strcpy(p->name,"法学1601");
    p->college_id=13;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=53;
    p->num=53;
    strcpy(p->profession,"广告学专业");
    strcpy(p->college,"新闻与传播学院");
    strcpy(p->name,"广告学专业1601");
    p->college_id=14;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=54;
    p->num=54;
    strcpy(p->profession,"广播电视学专业");
    strcpy(p->college,"新闻与传播学院");
    strcpy(p->name,"广播电视学专业1601");
    p->college_id=14;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=55;
    p->num=55;
    strcpy(p->profession,"网络与新媒体专业");
    strcpy(p->college,"新闻与传播学院");
    strcpy(p->name,"网络与新媒体专业1601");
    p->college_id=14;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=56;
    p->num=56;
    strcpy(p->profession,"播音与主持艺术专业");
    strcpy(p->college,"新闻与传播学院");
    strcpy(p->name,"播音与主持艺术专业1601");
    p->college_id=14;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=57;
    p->num=57;
    strcpy(p->profession,"产品设计专业");
    strcpy(p->college,"设计艺术学院");
    strcpy(p->name,"产品设计专业1601");
    p->college_id=15;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=58;
    p->num=58;
    strcpy(p->profession,"视觉传达设计专业");
    strcpy(p->college,"设计艺术学院");
    strcpy(p->name,"视觉传达设计专业1601");
    p->college_id=15;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=59;
    p->num=59;
    strcpy(p->profession,"环境设计专业");
    strcpy(p->college,"设计艺术学院");
    strcpy(p->name,"环境设计专业1601");
    p->college_id=15;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=60;
    p->num=60;
    strcpy(p->profession,"数字媒体艺术专业");
    strcpy(p->college,"设计艺术学院");
    strcpy(p->name,"数字媒体艺术专业1601");
    p->college_id=15;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=61;
    p->num=61;
    strcpy(p->profession,"动画");
    strcpy(p->college,"设计艺术学院");
    strcpy(p->name,"动画1601");
    p->college_id=15;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=62;
    p->num=62;
    strcpy(p->profession,"食品科学与工程专业");
    strcpy(p->college,"国际教育学院");
    strcpy(p->name,"食品科学与工程专业1601");
    p->college_id=16;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=63;
    p->num=63;
    strcpy(p->profession,"生物技术专业");
    strcpy(p->college,"国际教育学院");
    strcpy(p->name,"生物技术专业1601");
    p->college_id=16;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=64;
    p->num=64;
    strcpy(p->profession,"人力资源管理专业");
    strcpy(p->college,"国际教育学院");
    strcpy(p->name,"人力资源管理专业1601");
    p->college_id=16;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=65;
    p->num=65;
    strcpy(p->profession,"市场营销专业");
    strcpy(p->college,"国际教育学院");
    strcpy(p->name,"市场营销专业1601");
    p->college_id=16;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=66;
    p->num=66;
    strcpy(p->profession,"会计学专业");
    strcpy(p->college,"国际教育学院");
    strcpy(p->name,"会计学专业1601");
    p->college_id=16;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=67;
    p->num=67;
    strcpy(p->profession,"食品营养与检测专业");
    strcpy(p->college,"国际教育学院");
    strcpy(p->name,"食品营养与检测专业1601");
    p->college_id=16;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=68;
    p->num=68;
    strcpy(p->profession,"机械制造与自动化专业");
    strcpy(p->college,"中英国际学院");
    strcpy(p->name,"机械制造与自动化专业1601");
    p->college_id=17;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=69;
    p->num=69;
    strcpy(p->profession,"汽车营销与服务专业");
    strcpy(p->college,"中英国际学院");
    strcpy(p->name,"汽车营销与服务专业1601");
    p->college_id=17;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=70;
    p->num=70;
    strcpy(p->profession,"工程造价专业");
    strcpy(p->college,"中英国际学院");
    strcpy(p->name,"工程造价专业1601");
    p->college_id=17;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=71;
    p->num=71;
    strcpy(p->profession,"会计专业");
    strcpy(p->college,"中英国际学院");
    strcpy(p->name,"会计专业1601");
    p->college_id=17;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=72;
    p->num=72;
    strcpy(p->profession,"证券与期货专业");
    strcpy(p->college,"中英国际学院");
    strcpy(p->name,"证券与期货专业1601");
    p->college_id=17;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=73;
    p->num=73;
    strcpy(p->profession,"艺术设计专业");
    strcpy(p->college,"中英国际学院");
    strcpy(p->name,"艺术设计专业1601");
    p->college_id=17;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=74;
    p->num=74;
    strcpy(p->profession,"播音与主持专业");
    strcpy(p->college,"中英国际学院");
    strcpy(p->name,"播音与主持专业1601");
    p->college_id=17;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=75;
    p->num=75;
    strcpy(p->profession,"软件技术专业");
    strcpy(p->college,"中英国际学院");
    strcpy(p->name,"软件技术专业1601");
    p->college_id=17;//指定所属学院代码
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=76;
    p->num=76;
    strcpy(p->profession,"信息安全与管理专业");
    strcpy(p->college,"中英国际学院");
    strcpy(p->name,"信息安全与管理专业1601");
    p->college_id=17;//指定所属学院代码
    rear=p;

    rear->next=NULL;
    class_save(class_head);
}
void initialize(account_List account_head)//初始化管理员数据
{
    account_List p,rear;
    account_head=(account_List)malloc(sizeof(account_Lnode));
    p=(account_List)malloc(sizeof(account_Lnode));
    account_head->next=p;
	p->prior=account_head;
    //令数据条数为1
    p->num=1;
    //申请内存，填充第一条管理员数据
    p=(account_List)malloc(sizeof(account_Lnode));
    account_head->next->next=p;
	p->prior=account_head->next;
	p->num=1;
    strcpy(p->id,"admin");
    strcpy(p->password,"admin");
    strcpy(p->name,"宋天伦");
    strcpy(p->sex,"男");
    strcpy(p->identity,"管理员");
    strcpy(p->nation,"汉族");
    strcpy(p->face,"少先队员");
    strcpy(p->birth,"1997年10月29日");
    strcpy(p->time,"2016年09月");
    strcpy(p->college,"信息科学与工程学院");
    p->collegeid=4;
    strcpy(p->profession,"高级管理员");
	strcpy(p->grade,"讲师");
    p->professionid=1;
	rear=p;
	p->next=NULL;

	identity=-1;
    account_save(account_head);
}
void initialize_teacher(teacher_List teacher_head)//初始化
{
    teacher_List p;
    teacher_head=(teacher_List)malloc(sizeof(teacher_Lnode));
    p=(teacher_List)malloc(sizeof(teacher_Lnode));
    teacher_head->next=p;
    //令数据条数为1
    p->num=1;
    //申请内存，填充第一条数据
    p=(teacher_List)malloc(sizeof(teacher_Lnode));
    teacher_head->next->next=p;
    strcpy(p->id,"teacher");
    strcpy(p->password,"teacher");
    strcpy(p->name,"宋天伦");
    strcpy(p->sex,"男");
    strcpy(p->identity,"教师");
    strcpy(p->nation,"汉族");
    strcpy(p->face,"党员");
    strcpy(p->birth,"1997年10月29日");
    strcpy(p->time,"2016年09月");
    strcpy(p->college,"信息科学与工程学院");
    p->collegeid=4;
    strcpy(p->profession,"职业发展教育与就业指导");
    strcpy(p->grade,"讲师");
    p->professionid=4;
    p->next=NULL;
    teacher_save(teacher_head);
}
void initialize_student(student_List student_head)//初始化
{
    student_List p;
    student_head=(student_List)malloc(sizeof(student_Lnode));
    p=(student_List)malloc(sizeof(student_Lnode));
    student_head->next=p;
    //令数据条数为1
    p->num=1;
    //申请内存，填充第一条数据
    p=(student_List)malloc(sizeof(student_Lnode));
    student_head->next->next=p;
    strcpy(p->id,"student");
    strcpy(p->password,"student");
    strcpy(p->name,"宋天伦");
    strcpy(p->sex,"男");
    strcpy(p->identity,"学生");
    strcpy(p->nation,"汉族");
    strcpy(p->face,"团员");
    strcpy(p->birth,"1997年10月29日");
    strcpy(p->time,"2016年09月");
    strcpy(p->college,"信息科学与工程学院");
    p->collegeid=4;
    strcpy(p->profession,"空间信息与数字技术");
    p->professionid=19;
    strcpy(p->grade,"空间信息与数字技术1601");
    p->next=NULL;
    student_save(student_head);
}
void initialize_score(score_List score_head)//初始化成绩数据
{
    score_List p,prior,rear;
    rear=score_head;
    p=(score_List)malloc(sizeof(score_Lnode));
    prior=score_head;
    rear->next=p;
    //令数据条数为1
    p->num=3;
    p->prior=prior;
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(score_List)malloc(sizeof(score_Lnode));
    rear->next=p;
    p->prior=prior;
    p->num=1;//制定记录代码
    strcpy(p->id,"201616060110");
    strcpy(p->name,"宋天伦");
    strcpy(p->profession,"空间信息与数字技术");
    p->professionid=19;//专业代码
    strcpy(p->college,"信息科学与工程学院");
    p->collegeid=4;//专业代码
    strcpy(p->grade,"空间信息与数字技术1601");
    p->gradeid=19;//班级代码
    strcpy(p->subject,"大学英语");
    p->subjectid=1;//班级代码
	strcpy(p->term,"第一学期");
    p->paper_score=100;
    p->usual_score=100;
    p->makeup_score=-1;
    p->score=100;
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(score_List)malloc(sizeof(score_Lnode));
    rear->next=p;
    p->prior=prior;
    p->num=2;
    strcpy(p->id,"201616060110");
    strcpy(p->name,"宋天伦");
    strcpy(p->profession,"空间信息与数字技术");
    p->professionid=19;//专业代码
    strcpy(p->college,"信息科学与工程学院");
    p->collegeid=4;//专业代码
    strcpy(p->grade,"空间信息与数字技术1601");
    p->gradeid=19;//班级代码
    strcpy(p->subject,"高等数学");
    p->subjectid=2;//班级代码
	strcpy(p->term,"第一学期");
    p->paper_score=100;
    p->usual_score=100;
    p->makeup_score=-1;
    p->score=100;
    rear=p;
    //申请内存，填充数据
    prior=rear;
    p=(score_List)malloc(sizeof(score_Lnode));
    rear->next=p;
    p->prior=prior;
    p->num=3;
    strcpy(p->id,"201616060110");
    strcpy(p->name,"宋天伦");
    strcpy(p->profession,"空间信息与数字技术");
    p->professionid=19;//专业代码
    strcpy(p->college,"信息科学与工程学院");
    p->collegeid=4;//专业代码
    strcpy(p->grade,"空间信息与数字技术1601");
    p->gradeid=19;//班级代码
    strcpy(p->subject,"思想道德与法律修养");
    p->subjectid=3;//班级代码
	strcpy(p->term,"第一学期");
    p->paper_score=100;
    p->usual_score=100;
    p->makeup_score=-1;
    p->score=100;
    rear=p;

    rear->next=NULL;
    score_save(score_head);
}
