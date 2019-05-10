// Education manage system.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "resource.h"

#define MAX_LOADSTRING 100
//����Ա�˻����ݴ洢����
typedef struct ACCOUNT
{
    int num;//��š���������
    char id[20];//�˺�
    char password[20];//����
    char name[20];//����
    char sex[4];//�Ա�
    char identity[10];//���
    char nation[10];//����
    char face[15];//������ò
    char birth[20];//��������
    char time[20];//��ְ��ѧ����
    char college[20];//�������š�ѧԺ
    int collegeid;//���š�ѧԺ����
    char profession[20];//���ڿ�Ŀ������רҵ
    int professionid;//ѧ�ơ�רҵ����
	char grade[50];//�ȼ�
	struct ACCOUNT *prior;//ǰһ��
    struct ACCOUNT *next;//��һ��
}account_Lnode,*account_List;
typedef struct TEACHER//��ʦ���ݴ洢����
{
    int num;//��š���������
    char id[20];//�˺�
    char password[20];//����
    char name[20];//����
    char sex[5];//�Ա�
    char identity[10];//���
    char nation[10];//����
    char face[15];//������ò
    char birth[20];//��������
    char time[20];//��ְ��ѧ����
    char college[20];//����ѧԺ
    int collegeid;//ѧԺ����
    char profession[50];//�����γ�
    char grade[50];//ְ��
    int professionid;//�γ̴���
	struct TEACHER *prior;
    struct TEACHER *next;
}teacher_Lnode,*teacher_List;
typedef struct STUDENT//ѧ�����ݴ洢����
{
    int num;//��š���������
    char id[20];//�˺�
    char password[20];//����
    char name[20];//����
    char sex[5];//�Ա�
    char identity[10];//���
    char nation[10];//����
    char face[15];//������ò
    char birth[20];//��������
    char time[20];//��ְ��ѧ����
    char college[20];//����ѧԺ
    int collegeid;//ѧԺ����
    char profession[50];//����רҵ
    char grade[50];//�༶
    int professionid;//רҵ����
	struct STUDENT *prior;
    struct STUDENT *next;
}student_Lnode,*student_List;
//ѧԺ��Ϣ�洢����
typedef struct COLLEGE
{
    int num;//ѧԺ���
    char name[30];//ѧԺ����
    int id;//ѧԺ����
    struct COLLEGE *prior;//ǰһ��
    struct COLLEGE *next;//��һ��
}college_Lnode,*college_List;
//רҵ��Ϣ�洢����
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
//�γ���Ϣ�洢����
typedef struct COURSE
{
    int num;
    char name[50];
    int id;
    struct COURSE *prior;
    struct COURSE *next;
}course_Lnode,*course_List;
//�༶��Ϣ�洢����
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
//�ɼ���Ϣ�洢����
typedef struct SCORE
{
    int num;//���ݱ���
    char id[20];//�˺�
    char name[50];//ѧ������
    char profession[30];//ѧ��רҵ
    int professionid;//רҵ����
    char college[30];//ѧ��ѧԺ
    int collegeid;//ѧԺ����
    char grade[50];//ѧ���༶
    int gradeid;//�༶����
    char subject[50];//��Ŀ����
    int subjectid;//��Ŀ����
    char term[20];//ѧ��
    int paper_score;//����ɼ�
    int usual_score;//ƽʱ�ɼ�
    int makeup_score;//�����ɼ�
    int score;//�ܳɼ�
    struct SCORE *prior;
    struct SCORE *next;
}score_Lnode,*score_List;
// ȫ�ֱ���
HINSTANCE hinst;                                                    //��ǰʵ��

TCHAR szTitle_teacher[MAX_LOADSTRING];								// ��ʦ�˱������ı�
TCHAR szTitle_student[MAX_LOADSTRING];								// ѧ���˱������ı�
TCHAR szTitle_admin[MAX_LOADSTRING];								// ����Ա�˱������ı�
TCHAR szWindowClass_teacher[MAX_LOADSTRING];								// ��ʦ������������
TCHAR szWindowClass_student[MAX_LOADSTRING];								// ѧ��������������
TCHAR szWindowClass_admin[MAX_LOADSTRING];								    // ����Ա������������

account_List account_head;             //�˻���Ϣ����
account_List account_mine;             //��ǰ�˻���Ϣ
college_List college_head;             //ѧԺ��������
profession_List profession_head;       //רҵ��������
course_List course_head;               //�γ���Ϣ��������
class_List class_head;                 //�༶��Ϣ��������
teacher_List teacher_head;             //��ʦ��Ϣ��������
student_List student_head;             //ѧ����Ϣ��������
score_List score_head;                 //�ɼ���Ϣ��������
int identity=-1;                       //״̬ʶ��1.�߼�����Ա��2.��ʦ��3.ѧ����-1.��ʼ��״̬��-2.ϵͳ��Ҫ��ʼ��

//CDatebase m_db; //���ݿ�
//CRecordSet m_TestSet;
//m_db.Open("education management");//�������ݿ�
//CrecordSet m_TestSet(&m_db);//�����¼������ʹ���ݿ�ָ��m_db
void display_admin(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow);//��ʾ����Ա����
void display_teacher(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow);//��ʾ��ʦ����
void display_student(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow);//��ʾѧ������

// Foward declarations of functions included in this code module:
//ע��Ӧ�ó���Ĵ�����
ATOM				MyRegisterClass_teacher(HINSTANCE hInstance);//ע���ʦ�˴���
ATOM				MyRegisterClass_student(HINSTANCE hInstance);//ע��ѧ���˴���
ATOM				MyRegisterClass_admin(HINSTANCE hInstance);//ע�����Ա�˴���
//������ʵ���壬������ʾ
BOOL				InitInstance_teacher(HINSTANCE, int);//��������ʾ��ʦ�˴���
BOOL				InitInstance_student(HINSTANCE, int);//��������ʾѧ���˴���
BOOL				InitInstance_admin(HINSTANCE, int);//��������ʾ����Ա�˴���
//���ڻص�����
LRESULT CALLBACK	WndProc_teacher(HWND, UINT, WPARAM, LPARAM);//��ʦ���ڻص�����
LRESULT CALLBACK	WndProc_student(HWND, UINT, WPARAM, LPARAM);//ѧ�����ڻص�����
LRESULT CALLBACK	WndProc_admin(HWND, UINT, WPARAM, LPARAM);//����Ա���ڻص�����
//about�Ի���ص�����
LRESULT CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
//loading���ڻص�����
LRESULT CALLBACK	Loading(HWND, UINT, WPARAM, LPARAM);
//IDD_a_self_check���ڻص�����
LRESULT CALLBACK	A_SELF_INFO(HWND, UINT, WPARAM, LPARAM);
//IDD_a_self_password���ڻص�����
LRESULT CALLBACK	A_SELF_PASSWORD(HWND, UINT, WPARAM, LPARAM);
//IDD_a_college_inquir���ڻص�����
LRESULT CALLBACK	A_COLLEGE_INQUIRE(HWND, UINT, WPARAM, LPARAM);
//IDD_a_college_modification���ڻص�����
LRESULT CALLBACK	A_COLLEGE_MODIFICATION(HWND, UINT, WPARAM, LPARAM);
//IDD_a_profession_inquire���ڻص�����
LRESULT CALLBACK	A_PROFESSION_INQUIRE(HWND, UINT, WPARAM, LPARAM);
//IDD_a_profession_modification���ڻص�����
LRESULT CALLBACK	A_PROFESSION_MODIFICATION(HWND, UINT, WPARAM, LPARAM);
//IDD_a_course_inquire���ڻص�����
LRESULT CALLBACK	A_COURSE_INQUIRE(HWND, UINT, WPARAM, LPARAM);
//IDD_a_course_modification���ڻص�����
LRESULT CALLBACK	A_COURSE_MODIFICATION(HWND, UINT, WPARAM, LPARAM);
//IDD_a_class_inquire���ڻص�����
LRESULT CALLBACK	A_CLASS_INQUIRE(HWND, UINT, WPARAM, LPARAM);
//IDD_a_class_modification���ڻص�����
LRESULT CALLBACK	A_CLASS_MODIFICATION(HWND, UINT, WPARAM, LPARAM);
//IDD_a_account_inquire���ڻص�����
LRESULT CALLBACK	A_ACCOUNT_INQUIRE(HWND, UINT, WPARAM, LPARAM);
//IDD_a_account_modification���ڻص�����
LRESULT CALLBACK	A_ACCOUNT_MODIFICATION(HWND, UINT, WPARAM, LPARAM);
//IDD_a_teacher_inquire���ڻص�����
LRESULT CALLBACK	A_TEACHER_INQUIRE(HWND, UINT, WPARAM, LPARAM);
//IDD_a_teacher_modification���ڻص�����
LRESULT CALLBACK	A_TEACHER_MODIFICATION(HWND, UINT, WPARAM, LPARAM);
//IDD_a_student_inquire���ڻص�����
LRESULT CALLBACK	A_STUDENT_INQUIRE(HWND, UINT, WPARAM, LPARAM);
//IDD_a_student_modification���ڻص�����
LRESULT CALLBACK	A_STUDENT_MODIFICATION(HWND, UINT, WPARAM, LPARAM);
//IDD_a_score_inquire���ڻص�����
LRESULT CALLBACK	A_SCORE_INQUIRE(HWND, UINT, WPARAM, LPARAM);
//IDD_a_score_modification���ڻص�����
LRESULT CALLBACK	A_SCORE_MODIFICATION(HWND, UINT, WPARAM, LPARAM);
//IDD_a_score_self_inquire���ڻص�����
LRESULT CALLBACK	A_SCORE_SELF_INQUIRE(HWND, UINT, WPARAM, LPARAM);
//IDD_a_score_self_inquire���ڻص�����
LRESULT CALLBACK	A_SCORE_TERM_INQUIRE(HWND, UINT, WPARAM, LPARAM);
//IDD_a_score_self_inquire���ڻص�����
LRESULT CALLBACK	A_SCORE_ENTER(HWND, UINT, WPARAM, LPARAM);
//IDD_a_score_analyse_sum���ڻص�����
LRESULT CALLBACK	A_SCORE_ANALYSE_SUM(HWND, UINT, WPARAM, LPARAM);
//IDD_a_score_analyse_average���ڻص�����
LRESULT CALLBACK	A_SCORE_ANALYSE_AVERAGE(HWND, UINT, WPARAM, LPARAM);
void Mypaint();//����������ͼ��
//���ݲ�������
void account_load(account_List account_head); //�Ӵ��������˻�����
void account_save(account_List account_head); //�����˻����ݵ�����
void college_load(college_List college_head); //�Ӵ�������ѧԺ����
void college_save(college_List college_head); //����ѧԺ���ݵ�����
void profession_load(profession_List profession_head); //�Ӵ�������רҵ����
void profession_save(profession_List profession_head); //����רҵ���ݵ�����
void course_load(course_List course_head); //�Ӵ�������γ�����
void course_save(course_List course_head); //����γ����ݵ�����
void class_load(class_List class_head); //�Ӵ�������༶����
void class_save(class_List class_head); //����༶���ݵ�����
void teacher_load(teacher_List teacher_head); //�Ӵ��������ʦ����
void teacher_save(teacher_List teacher_head); //�����ʦ���ݵ�����
void student_load(student_List student_head); //�Ӵ�������ѧ������
void student_save(student_List student_head); //����ѧ�����ݵ�����
void score_load(score_List score_head); //�Ӵ�������ɼ�����
void score_save(score_List score_head); //����ɼ����ݵ�����

int loading(char id[20],char password[20],account_List account_mine);//1.����Ա��2.��ʦ��3.ѧ����4.�˺Ŵ���5.�������
void initialize(account_List account_head);//��ʼ���˻�����
void initialize_college(college_List college_head);//��ʼ��ѧԺ����
void initialize_profession(profession_List profession_head);//��ʼ��רҵ����
void initialize_course(course_List course_head);//��ʼ���γ�����
void initialize_class(class_List class_head);//��ʼ���༶����
void initialize_teacher(teacher_List teacher_head);//��ʼ����ʦ����
void initialize_student(student_List student_head);//��ʼ��ѧ������
void initialize_score(score_List score_head);//��ʼ���ɼ�����

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;
	account_mine=(account_List)malloc(sizeof(account_Lnode));//�����˻�����ͷ��
	account_head=(account_List)malloc(sizeof(account_Lnode));//���뵱ǰ�˻�����ͷ��
	college_head=(college_List)malloc(sizeof(college_Lnode));//����ѧԺ����ͷ��
	profession_head=(profession_List)malloc(sizeof(profession_Lnode));//����רҵ����ͷ��
	course_head=(course_List)malloc(sizeof(course_Lnode));//����γ�����ͷ��
	class_head=(class_List)malloc(sizeof(class_Lnode));//����༶����ͷ��
	teacher_head=(teacher_List)malloc(sizeof(teacher_Lnode));//�����ʦ����ͷ��
	student_head=(student_List)malloc(sizeof(student_Lnode));//����ѧ������ͷ��
	score_head=(score_List)malloc(sizeof(score_Lnode));//����ɼ���Ϣ����ͷ��

	//����ȫ������
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
				if(MessageBox(NULL,"��⵽ϵͳ�״�ʹ�û������ļ���ʧ������ȷ�Ͻ���ϵͳ��ʼ����","����",MB_YESNO|MB_ICONEXCLAMATION)==6)
				{
					initialize(account_head);//��ʼ���˻�����
					account_load(account_head);//�����ʼ�˻�����
					initialize_college(college_head);//��ʼ��ѧԺ����
					college_load(college_head);//�����ʼ�˻�����
					initialize_profession(profession_head);//��ʼ��רҵ����
					profession_load(profession_head);//�����ʼרҵ����
					initialize_course(course_head);//��ʼ��רҵ����
					course_load(course_head);//�����ʼרҵ����
					initialize_class(class_head);//��ʼ���༶����
					class_load(class_head);//�����ʼ�༶����
					initialize_teacher(teacher_head);//��ʼ����ʦ����
					teacher_load(teacher_head);//�����ʼ��ʦ����
					initialize_student(student_head);//��ʼ��ѧ������
					student_load(student_head);//�����ʼѧ������
					initialize_score(score_head);//��ʼ���ɼ�����
					score_load(score_head);//�����ʼ�ɼ�����

				}
				else
				{
					return FALSE;
				}
			}
	teacher_load(teacher_head);
	student_load(student_head);
	//������ټ���
	hAccelTable = LoadAccelerators(hInstance, (LPCTSTR)IDC_EDUCATIONMANAGESYSTEM);
	DialogBox(hInstance,(LPCTSTR)IDD_LOADING,NULL,(DLGPROC)Loading);//��ʾ��¼�Ի���


	//��ʾ����Ա����
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
	
	//����Ϣѭ��
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
	//����Դ�ļ�������IDE_APP_TITTLEָ�����ַ�����Դ
	LoadString(hInstance, IDS_APP_TITLE_ADMIN, szTitle_admin, MAX_LOADSTRING);
	LoadString(hInstance, IDS_EDUCATIONMANAGESYSTEM, szWindowClass_admin, MAX_LOADSTRING);
	//ע�ᴰ��Ҫʹ�õĴ�����
	MyRegisterClass_admin(hInstance);

	//��ʼ������ʵ��
	//����InitInstance�Զ��庯��������ʵ����
	InitInstance_admin(hInstance, nCmdShow);
}
void display_teacher(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	//����Դ�ļ�������IDE_APP_TITTLEָ�����ַ�����Դ
	LoadString(hInstance, IDS_APP_TITLE_TEACHER, szTitle_teacher, MAX_LOADSTRING);
	LoadString(hInstance, IDS_EDUCATIONMANAGESYSTEM, szWindowClass_teacher, MAX_LOADSTRING);
	//ע�ᴰ��Ҫʹ�õĴ�����
	MyRegisterClass_teacher(hInstance);

	//��ʼ������ʵ��
	//����InitInstance�Զ��庯��������ʵ����
	InitInstance_teacher (hInstance, nCmdShow);
}
void display_student(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	//����Դ�ļ�������IDE_APP_TITTLEָ�����ַ�����Դ
	LoadString(hInstance, IDS_APP_TITLE_STUDENT, szTitle_student, MAX_LOADSTRING);
	LoadString(hInstance, IDS_EDUCATIONMANAGESYSTEM, szWindowClass_student, MAX_LOADSTRING);
	//ע�ᴰ��Ҫʹ�õĴ�����
	MyRegisterClass_student(hInstance);

	//��ʼ������ʵ��
	//����InitInstance�Զ��庯��������ʵ����
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
//ע��Ӧ�ó���Ĵ�����
ATOM MyRegisterClass_admin(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;//��������
	wcex.lpfnWndProc	= (WNDPROC)WndProc_admin;       //ָ�����ڻص�����
	wcex.cbClsExtra		= 0;                      //����ṹ��windows�ڲ�����Ĵ��ڽṹ��Ԥ���ռ�
	wcex.cbWndExtra		= 0;                      //����ṹ��windows�ڲ�����Ĵ��ڽṹ��Ԥ���ռ�
	wcex.hInstance		= hinst;              //ָ�����ڳ����ʵ�����
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_EDUCATIONMANAGESYSTEM);  //Ϊ���л��ڸô����ഴ���Ĵ�������һ��Ӧ�ó���ͼ��
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);                     //Ϊ���л��ڸô����ഴ���Ĵ������������״
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);                        //ָ�����ڸô����ഴ�����ڵı���ɫ
	wcex.lpszMenuName	= (LPCSTR)IDR_MENU_ADMIN;                        //ָ��������Ĳ˵�
	wcex.lpszClassName	= szWindowClass_admin;                                   //���ô�����ָ��һ������
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);    //Ϊ���л��ڸô����ഴ���Ĵ�������һ�����ڱ�����ͼ��

	return RegisterClassEx(&wcex);                                         //����RegisterClassEx����ע�����������
}
ATOM MyRegisterClass_teacher(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;//��������
	wcex.lpfnWndProc	= (WNDPROC)WndProc_admin;       //ָ�����ڻص�����
	wcex.cbClsExtra		= 0;                      //����ṹ��windows�ڲ�����Ĵ��ڽṹ��Ԥ���ռ�
	wcex.cbWndExtra		= 0;                      //����ṹ��windows�ڲ�����Ĵ��ڽṹ��Ԥ���ռ�
	wcex.hInstance		= hinst;              //ָ�����ڳ����ʵ�����
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_EDUCATIONMANAGESYSTEM);  //Ϊ���л��ڸô����ഴ���Ĵ�������һ��Ӧ�ó���ͼ��
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);                     //Ϊ���л��ڸô����ഴ���Ĵ������������״
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);                        //ָ�����ڸô����ഴ�����ڵı���ɫ
	wcex.lpszMenuName	= (LPCSTR)IDR_MENU_TEACHER;                        //ָ��������Ĳ˵�
	wcex.lpszClassName	= szWindowClass_teacher;                                   //���ô�����ָ��һ������
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);    //Ϊ���л��ڸô����ഴ���Ĵ�������һ�����ڱ�����ͼ��

	return RegisterClassEx(&wcex);                                         //����RegisterClassEx����ע�����������
}
ATOM MyRegisterClass_student(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;
	wcex.cbSize = sizeof(WNDCLASSEX); 

	wcex.style			= CS_HREDRAW | CS_VREDRAW;//��������
	wcex.lpfnWndProc	= (WNDPROC)WndProc_admin;       //ָ�����ڻص�����
	wcex.cbClsExtra		= 0;                      //����ṹ��windows�ڲ�����Ĵ��ڽṹ��Ԥ���ռ�
	wcex.cbWndExtra		= 0;                      //����ṹ��windows�ڲ�����Ĵ��ڽṹ��Ԥ���ռ�
	wcex.hInstance		= hinst;              //ָ�����ڳ����ʵ�����
	wcex.hIcon			= LoadIcon(hInstance, (LPCTSTR)IDI_EDUCATIONMANAGESYSTEM);  //Ϊ���л��ڸô����ഴ���Ĵ�������һ��Ӧ�ó���ͼ��
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);                     //Ϊ���л��ڸô����ഴ���Ĵ������������״
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);                        //ָ�����ڸô����ഴ�����ڵı���ɫ
	wcex.lpszMenuName	= (LPCSTR)IDR_MENU_STUDENT;                        //ָ��������Ĳ˵�
	wcex.lpszClassName	= szWindowClass_student;                                   //���ô�����ָ��һ������
	wcex.hIconSm		= LoadIcon(wcex.hInstance, (LPCTSTR)IDI_SMALL);    //Ϊ���л��ڸô����ഴ���Ĵ�������һ�����ڱ�����ͼ��

	return RegisterClassEx(&wcex);                                         //����RegisterClassEx����ע�����������
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
//������ʵ���壬������ʾ
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
//����Ա�����ڻص�����
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
				//��ʾ�ҵĸ�����Ϣ
				case a_self_inquire:
					MessageBox(NULL,"�������鿴����ʾ������Ϣ��","��ʾ",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_self_check, hWnd, (DLGPROC)A_SELF_INFO);
					break;
				//�޸�����
				case a_self_password:
					DialogBox(hinst, (LPCTSTR)IDD_a_self_password, hWnd, (DLGPROC)A_SELF_PASSWORD);
					break;
				//�鿴ѧԺ��Ϣ
				case a_college_inquire:
					MessageBox(NULL,"���������ض�������ʾ��һҳѧԺ��Ϣ��","��ʾ",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_college_inquire, hWnd, (DLGPROC)A_COLLEGE_INQUIRE);
					break;
				//�޸�ѧԺ��Ϣ
				case a_college_modification:
					//Ԥ����Ϣ��
					//MessageBox(NULL,"���������ض�������ʾ��һҳѧԺ��Ϣ��","��ʾ",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_college_modification, hWnd, (DLGPROC)A_COLLEGE_MODIFICATION);
					break;
				//�鿴רҵ��Ϣ
				case a_profession_inquire:
					MessageBox(NULL,"���������ض�������ʾ��һҳרҵ��Ϣ��","��ʾ",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_profession_inquire, hWnd, (DLGPROC)A_PROFESSION_INQUIRE);
					break;
				//�޸�רҵ��Ϣ
				case a_profession_modification:
					//Ԥ����Ϣ��
					//MessageBox(NULL,"���������ض�������ʾ��һҳѧԺ��Ϣ��","��ʾ",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_profession_modification, hWnd, (DLGPROC)A_PROFESSION_MODIFICATION);
					break;
				//�鿴�γ���Ϣ
				case a_course_inquire:
					MessageBox(NULL,"���������ض�������ʾ��һҳ�γ���Ϣ��","��ʾ",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_course_inquire, hWnd, (DLGPROC)A_COURSE_INQUIRE);
					break;
				//�޸Ŀγ���Ϣ
				case a_course_modification:
					//Ԥ����Ϣ��
					//MessageBox(NULL,"���������ض�������ʾ��һҳѧԺ��Ϣ��","��ʾ",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_course_modification, hWnd, (DLGPROC)A_COURSE_MODIFICATION);
					break;
				//�鿴�༶��Ϣ
				case a_class_inquire:
					MessageBox(NULL,"���������ض�������ʾ��һҳ�༶��Ϣ��","��ʾ",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_class_inquire, hWnd, (DLGPROC)A_CLASS_INQUIRE);
					break;
				//�޸İ༶��Ϣ
				case a_class_modification:
					//Ԥ����Ϣ��
					//MessageBox(NULL,"���������ض�������ʾ��һҳ�༶��Ϣ��","��ʾ",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_class_modification, hWnd, (DLGPROC)A_CLASS_MODIFICATION);
					break;
				//�鿴�˻���Ϣ
				case a_account_inquire:
					MessageBox(NULL,"���������ض�������ʾ��һҳ�˻���Ϣ��","��ʾ",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_account_inquire, hWnd, (DLGPROC)A_ACCOUNT_INQUIRE);
					break;
				//�޸��˻���Ϣ
				case a_account_modification:
					//Ԥ����Ϣ��
					//MessageBox(NULL,"���������ض�������ʾ��һҳ�˻���Ϣ��","��ʾ",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_account_modification, hWnd, (DLGPROC)A_ACCOUNT_MODIFICATION);
					break;
				//�鿴��ʦ��Ϣ
				case a_teacher_inquire:
					MessageBox(NULL,"���������ض�������ʾ��һҳ��ʦ��Ϣ��","��ʾ",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_teacher_inquire, hWnd, (DLGPROC)A_TEACHER_INQUIRE);
					break;
				//�޸Ľ�ʦ��Ϣ
				case a_teacher_modification:
					//Ԥ����Ϣ��
					//MessageBox(NULL,"���������ض�������ʾ��һҳ��ʦ��Ϣ��","��ʾ",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_teacher_modification, hWnd, (DLGPROC)A_TEACHER_MODIFICATION);
					break;
				//�鿴ѧ����Ϣ
				case a_student_inquire:
					MessageBox(NULL,"���������ض�������ʾ��һҳ��ʦ��Ϣ��","��ʾ",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_student_inquire, hWnd, (DLGPROC)A_STUDENT_INQUIRE);
					break;
				//�޸�ѧ����Ϣ
				case a_student_modification:
					//Ԥ����Ϣ��
					//MessageBox(NULL,"���������ض�������ʾ��һҳ��ʦ��Ϣ��","��ʾ",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_student_modification, hWnd, (DLGPROC)A_STUDENT_MODIFICATION);
					break;
				//�鿴�ɼ���Ϣ
				case a_score_inquire:
					MessageBox(NULL,"���������ض�������ʾ��һҳ�ɼ���Ϣ��","��ʾ",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_score_inquire, hWnd, (DLGPROC)A_SCORE_INQUIRE);
					break;
				//�޸ĳɼ���Ϣ
				case a_score_modification:
					//Ԥ����Ϣ��
					//MessageBox(NULL,"���������ض�������ʾ��һҳ��ʦ��Ϣ��","��ʾ",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_score_modification, hWnd, (DLGPROC)A_SCORE_MODIFICATION);
					break;
				//�鿴���˳ɼ���Ϣ
				case a_score_self_inquire:
					MessageBox(NULL,"���������ض�������ʾ��һҳ�ɼ���Ϣ��","��ʾ",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_score_self_inquire, hWnd, (DLGPROC)A_SCORE_SELF_INQUIRE);
					break;
				//�鿴�༶�ɼ���Ϣ
				case a_score_term_inquire:
					MessageBox(NULL,"���������ض�������ʾ��һҳ�ɼ���Ϣ��","��ʾ",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_score_term_inquire, hWnd, (DLGPROC)A_SCORE_TERM_INQUIRE);
					break;
				//�ɼ���Ϣ¼��
				case a_score_enter:
					MessageBox(NULL,"��ѡ��ѧ�ơ��༶��ѧ����Ϣ��¼��ɼ���","��ʾ",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_score_enter, hWnd, (DLGPROC)A_SCORE_ENTER);
					break;
				case a_score_analyse_sum:
					MessageBox(NULL,"��ѡ��༶���鿴�༶�ܷ֣�","��ʾ",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_score_analyse_sum, hWnd, (DLGPROC)A_SCORE_ANALYSE_SUM);
					break;
				case a_score_analyse_average:
					MessageBox(NULL,"��ѡ��༶���鿴�༶ƽ���֣�","��ʾ",MB_OK);
					DialogBox(hinst, (LPCTSTR)IDD_a_score_analyse_average, hWnd, (DLGPROC)A_SCORE_ANALYSE_AVERAGE);
					break;
				//����
				case help_about:
					DialogBox(hinst, (LPCTSTR)IDD_ABOUTBOX, hWnd, (DLGPROC)About);
					break;
				//�˳�
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

// about���ڻص�����
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

//��¼���ڻص�����
LRESULT CALLBACK	Loading(HWND h_loading, UINT message, WPARAM wParam, LPARAM lParam)
{
	//#define IDC_LOADING_IDENTIFY 101
	//char identify[20];
	//HWND EXIT_identify;
	char lpszClassName[]="COMBOBOX";
	int wmId,uMax,pMax,load_state;//load_state ��¼״̬
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
				//MessageBox(NULL,identify,"��ʾ",MB_OK);
				switch(load_state)
				{
				case 1:
					identity=1;
					EndDialog(h_loading, LOWORD(wParam));
					MessageBox(NULL,"��½�ɹ�����ӭ����Ա��¼ϵͳ��","��¼���",MB_OK);
				    return TRUE;
				case 2:
					identity=2;
					EndDialog(h_loading, LOWORD(wParam));
					MessageBox(NULL,"��½�ɹ�����ӭ��ʦ��¼ϵͳ��","��¼���",MB_OK);
				    return TRUE;
				case 3:
					identity=3;
					EndDialog(h_loading, LOWORD(wParam));
					MessageBox(NULL,"��½�ɹ�����ӭѧ����¼ϵͳ��","��¼���",MB_OK);
				    return TRUE;
				case 4:
					MessageBox(NULL,"��¼ʧ�ܣ��˺Ų����ڣ�","��¼���",MB_OK|MB_SYSTEMMODAL);
					return FALSE;
				case 5:
					MessageBox(NULL,"��½ʧ�ܣ��������","��¼���",MB_OK|MB_SYSTEMMODAL);
					return FALSE;
				}
				break;
			case IDC_LOADING_EXIT:
				PostQuitMessage(0);//ֹͣ��Ϣ����
				EndDialog(h_loading, LOWORD(wParam));
				return TRUE;
			}
			break;
		case WM_CLOSE:
			PostQuitMessage(0);//ֹͣ��Ϣ����
				EndDialog(h_loading, LOWORD(wParam));
				return TRUE;
	}
    return FALSE;
}
//IDD_a_self_check���ڻص�����
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
//IDD_a_self_password���ڻص�����
LRESULT CALLBACK	A_SELF_PASSWORD(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i;
	account_List p;
	char old[20],new1[20],new2[20];
	int state=-1;//״ָ̬ʾ��-1.��ʼ����1.�޸ĳɹ���2.���������3.�����벻ƥ�䣬4.�������,5.�¾�����һ��
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
					MessageBox(NULL,"�������������","ERROR!",MB_OK|MB_SYSTEMMODAL);
					break;
				}
				else if(strlen(new1)<4)
				{
					state=4;
					MessageBox(NULL,"��������ڼ򵥣�","ERROR!",MB_OK|MB_SYSTEMMODAL);
					break;
				}
				else if(strcmp(new1,old)==0)
				{
					state=5;
					MessageBox(NULL,"�¾�����һ�£�","ERROR!",MB_OK|MB_SYSTEMMODAL);
					break;
				}
				else if(strcmp(new1,new2)!=0)
				{
					state=3;
					MessageBox(NULL,"�������벻һ�£�","ERROR!",MB_OK|MB_SYSTEMMODAL);
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
					MessageBox(NULL,"�޸ĳɹ���","SUCCES!",MB_OK|MB_SYSTEMMODAL);
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

//IDD_a_college_inquir���ڻص�����
	int college_ck; //����Ƿ��ʼ�����ݣ�1.�ǣ�0.��
	int college_now;
LRESULT CALLBACK	A_COLLEGE_INQUIRE(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,sum,page,print;//sum.�������� page.��ҳ�� now.��ǰҳ�� print.��ǰҳ��������
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
					print=6;//������������С��6�����һҳ��ʾ6������
				if(sum<6)
					print=sum;//����������С��6�����һҳ��ʾȫ��sum������
				page_head=college_head->next->next;//ָ���һҳ��һ����¼
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
				strcpy(char_page,"��");
				itoa(college_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ����");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				break;
			case BUTTON_a_college_inquire_prior:
				if(college_ck!=1)
				{
					MessageBox(NULL,"���������ض�������ʾ��һҳѧԺ��Ϣ��","��ʾ",MB_OK);
					break;
				}
				page_head=college_head->next->next;
				if(college_now-1<=0)
				{
					MessageBox(NULL,"�Ѿ�����һҳ��","��ʾ",MB_OK);
					return FALSE;
				}
				else
					college_now--;
				for(i=0;i<(college_now-1)*6;i++)//��page_head�Ƶ���ǰҳ�ĵ�һ��
					page_head=page_head->next;
				
				if(college_now==page)//��������һҳ����������һҳ��¼����
					print=sum-(page-1)*6;
				else//���򣬼�¼����Ϊ6
					print=6;
				//��ձ༭������
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
				strcpy(char_page,"��");
				itoa(college_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ����");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_college_inquire_next:
				if(college_ck!=1)
				{
					MessageBox(NULL,"���������ض�������ʾ��һҳѧԺ��Ϣ��","��ʾ",MB_OK);
					break;
				}
				page_head=college_head->next->next;//�Ƶ���¼��һҳ��һ����¼
				if(college_now+1>page)//�����ǰҳ+1������ҳ������������
				{
					MessageBox(NULL,"�Ѿ������һҳ��","��ʾ",MB_OK);
					return FALSE;
				}
				else//������תҳ��
				{
					college_now++;
				}
				for(i=0;i<(college_now-1)*6;i++)//��page_head�Ƶ���ǰҳ�ĵ�һ��
					page_head=page_head->next;
				
				if(college_now==page)//��������һҳ����������һҳ��¼����
					print=sum-(page-1)*6;
				else//���򣬼�¼����Ϊ6
					print=6;
				//��ձ༭������
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
				strcpy(char_page,"��");
				
				itoa(college_now,item,10);

				strcat(char_page,item);
				
				strcat(char_page,"ҳ����");
				itoa(page,item,10);//ת������Ϊ�ַ���
				strcat(char_page,item);
				strcat(char_page,"ҳ");
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
//IDD_a_college_modification���ڻص�����
HWND EDIT_oldid,EDIT_oldid1,EDIT_oldname,EDIT_newid,EDIT_newname;
	int find_a_college_modification;//0.�ҵ� 1.δ�ҵ�
	int state_a_college_modification;//�޸�״̬��ʾ
	char college_item[10];
	college_List modification_p,college_new_info,college_old_info;
	college_List college_delete;
LRESULT CALLBACK	A_COLLEGE_MODIFICATION(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	char  new_name[50];
	char message_a_college_modification[60];
	char *stop;//Ϊstrtol�������ֹ�ַ�ָ��
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
			//ͨ��id��λѧԺ
			case BUTTON_a_college_modification_location:
				find_a_college_modification=0;
				GetWindowText(EDIT_oldid,college_item,GetWindowTextLength(EDIT_oldid)+1);//��ȡoldid�༭�����ݵ�item
				id=strtol(college_item,&stop,10);//ת������Ϊ������
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
					MessageBox(NULL,"��������","ERROR!",MB_OK);
					break;
					return FALSE;
				}
				SetWindowText(EDIT_oldid1,college_item);
				SetWindowText(EDIT_newid,college_item);
				SetWindowText(EDIT_oldname,college_old_info->name);
				SetWindowText(EDIT_newname,college_old_info->name);
				state_a_college_modification=1;//�޸�״̬Ϊ�޸�
				break;
			//����ѧԺ
			case BUTTON_a_college_modification_add:
				MessageBox(NULL,"��������Ϣ����������ѧԺ����","��ʾ",MB_OK);
				find_a_college_modification=0;
				state_a_college_modification=2;//�޸�״̬Ϊ����ѧԺ
				SetWindowText(EDIT_oldid,"");
				SetWindowText(EDIT_oldid1,"");
				SetWindowText(EDIT_newid,"");
				SetWindowText(EDIT_oldname,"");
				SetWindowText(EDIT_newname,"");
				college_new_info=(college_List)malloc(sizeof(college_Lnode));
				college_new_info->id=college_head->next->num+1;
				college_new_info->num=college_head->next->num+1;
				itoa(college_new_info->id,college_item,10);//ת������Ϊ�ַ���
				SetWindowText(EDIT_newid,college_item);
				break;
			//ȷ���޸�
			case BUTTON_a_college_modification_affirm:
				GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//��ȡnewnaeme�����ݵ�new_name
				if(state_a_college_modification==1)//ȷ���޸�����ѧԺ��Ϣ
				{
				if(strlen(new_name)>20)
				{
					MessageBox(NULL,"��������","����",MB_OK);
					strcpy(new_name,college_old_info->name);
					SetWindowText(EDIT_newname,college_old_info->name);
					return FALSE;
				}
				if(strcmp(new_name,college_old_info->name)==0)
				{
					MessageBox(NULL,"û���޸��κ���Ϣ��","����",MB_OK);
					return FALSE;
				}
				modification_p=college_head->next;
				for(i=0;i<college_old_info->id;i++)
					modification_p=modification_p->next;
				strcpy(modification_p->name,new_name);
				college_save(college_head);
				college_load(college_head);
				SetWindowText(EDIT_oldname,new_name);
				MessageBox(NULL,"�޸ĳɹ���","����",MB_OK);
				}
				if(state_a_college_modification==2)//ȷ������ѧԺ��Ϣ
				{
					GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//��ȡnewnaeme�����ݵ�new_name
					strcpy(college_new_info->name,new_name);
					modification_p=college_head->next;
					if(strlen(new_name)==0||strlen(new_name)>20)
					{
						MessageBox(NULL,"ѧԺ���ƷǷ���","����",MB_OK);
						break;
						return FALSE;
					}
					for(i=0;i<college_head->next->num;i++)
					{
						modification_p=modification_p->next;
						if(strcmp(college_new_info->name,modification_p->name)==0)
						{
							MessageBox(NULL,"ѧԺ�����ظ���","����",MB_OK);
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
					MessageBox(NULL,"�޸ĳɹ���","��ʾ",MB_OK);
					college_old_info=(college_List)malloc(sizeof(college_Lnode));
					strcpy(college_old_info->name,college_new_info->name);
					college_old_info->id=college_new_info->id;
					college_old_info->num=college_new_info->id;
					find_a_college_modification=1;
				}
				break;
			//ɾ��ѧԺ
			case BUTTON_a_college_modification_delete:
				if(find_a_college_modification==1)
				{
				strcpy(message_a_college_modification,"ȷ��ɾ��ѧԺ����");
				strcat(message_a_college_modification,college_old_info->name);
				strcat(message_a_college_modification,"����");
				if(MessageBox(NULL,message_a_college_modification,"����",MB_YESNO|MB_ICONEXCLAMATION)!=6)
				{
					return FALSE;
				}
				modification_p=college_head->next;
				for(i=0;i<college_old_info->id;i++)
					modification_p=modification_p->next;
				modification_p->num=-1;
				strcat(modification_p->name,"����ɾ����");
				modification_p=college_head->next->next;
				college_save(college_head);
				college_load(college_head);
				SetWindowText(EDIT_oldid,"");
				SetWindowText(EDIT_oldid1,"");
				SetWindowText(EDIT_newid,"");
				SetWindowText(EDIT_oldname,"");
				SetWindowText(EDIT_newname,"");
				MessageBox(NULL,"ɾ���ɹ���","����",MB_OK);
				find_a_college_modification=0;
				break;
				}
				MessageBox(NULL,"�Ƿ�������","����",MB_OK);
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
//IDD_a_profession_inquir���ڻص�����
	int profession_ck; //����Ƿ��ʼ�����ݣ�1.�ǣ�0.��
	int profession_now;
LRESULT CALLBACK	A_PROFESSION_INQUIRE(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,sum,page,print;//sum.�������� page.��ҳ�� now.��ǰҳ�� print.��ǰҳ��������
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
					print=6;//������������С��6�����һҳ��ʾ6������
				if(sum<6)
					print=sum;//����������С��6�����һҳ��ʾȫ��sum������
				page_head=profession_head->next->next;//ָ���һҳ��һ����¼
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
				strcpy(char_page,"��");
				itoa(profession_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ����");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				break;
			case BUTTON_a_profession_inquire_prior:
				if(profession_ck!=1)
				{
					MessageBox(NULL,"���������ض�������ʾ��һҳѧԺ��Ϣ��","��ʾ",MB_OK);
					break;
				}
				page_head=profession_head->next->next;
				if(profession_now-1<=0)
				{
					MessageBox(NULL,"�Ѿ�����һҳ��","��ʾ",MB_OK);
					return FALSE;
				}
				else
					profession_now--;
				for(i=0;i<(profession_now-1)*6;i++)//��page_head�Ƶ���ǰҳ�ĵ�һ��
					page_head=page_head->next;
				
				if(profession_now==page)//��������һҳ����������һҳ��¼����
					print=sum-(page-1)*6;
				else//���򣬼�¼����Ϊ6
					print=6;
				//��ձ༭������
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
				strcpy(char_page,"��");
				itoa(profession_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ����");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_profession_inquire_next:
				if(profession_ck!=1)
				{
					MessageBox(NULL,"���������ض�������ʾ��һҳѧԺ��Ϣ��","��ʾ",MB_OK);
					break;
				}
				page_head=profession_head->next->next;//�Ƶ���¼��һҳ��һ����¼
				if(profession_now+1>page)//�����ǰҳ+1������ҳ������������
				{
					MessageBox(NULL,"�Ѿ������һҳ��","��ʾ",MB_OK);
					return FALSE;
				}
				else//������תҳ��
				{
					profession_now++;
				}
				for(i=0;i<(profession_now-1)*6;i++)//��page_head�Ƶ���ǰҳ�ĵ�һ��
					page_head=page_head->next;
				
				if(profession_now==page)//��������һҳ����������һҳ��¼����
					print=sum-(page-1)*6;
				else//���򣬼�¼����Ϊ6
					print=6;
				//��ձ༭������
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
				strcpy(char_page,"��");
				
				itoa(profession_now,item,10);

				strcat(char_page,item);
				
				strcat(char_page,"ҳ����");
				itoa(page,item,10);//ת������Ϊ�ַ���
				strcat(char_page,item);
				strcat(char_page,"ҳ");
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
//IDD_a_profession_modification���ڻص�����

	int find_a_profession_modification;//0.�ҵ� 1.δ�ҵ�
	int state_a_profession_modification;//�޸�״̬��ʾ
	int add_profession;//������Ϣ�Ϸ���1.�Ϸ�,other.���Ϸ�
	char profession_item[10];
	profession_List profession_modification_p,profession_new_info,profession_old_info;
	profession_List profession_delete;
LRESULT CALLBACK	A_PROFESSION_MODIFICATION(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	college_List college_p;
	HWND EDIT_oldid,EDIT_oldid1,EDIT_oldname,EDIT_oldcollege,EDIT_newid,EDIT_newname,EDIT_newcollege;
	char  new_name[50],new_college[50];
	char message_a_profession_modification[60];
	char *stop;//Ϊstrtol�������ֹ�ַ�ָ��
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
			//ͨ��id��λרҵ
			case BUTTON_a_profession_modification_location:
				find_a_profession_modification=0;
				GetWindowText(EDIT_oldid,profession_item,GetWindowTextLength(EDIT_oldid)+1);//��ȡoldid�༭�����ݵ�item
				id=strtol(profession_item,&stop,10);//ת������Ϊ������
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
					MessageBox(NULL,"��������","ERROR!",MB_OK);
					break;
					return FALSE;
				}
				SetWindowText(EDIT_oldid1,profession_item);
				SetWindowText(EDIT_newid,profession_item);
				SetWindowText(EDIT_oldname,profession_old_info->name);
				SetWindowText(EDIT_newname,profession_old_info->name);
				SetWindowText(EDIT_oldcollege,profession_old_info->college);
				SetWindowText(EDIT_newcollege,profession_old_info->college);
				state_a_profession_modification=1;//�޸�״̬Ϊ�޸�
				break;
			//����ѧԺ
			case BUTTON_a_profession_modification_add:
				MessageBox(NULL,"��������Ϣ����������רҵ�����Լ�������ѧԺ����","��ʾ",MB_OK);
				find_a_profession_modification=0;
				state_a_profession_modification=2;//�޸�״̬Ϊ����ѧԺ
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
				itoa(profession_new_info->id,profession_item,10);//ת������Ϊ�ַ���
				SetWindowText(EDIT_newid,profession_item);
				break;
			//ȷ���޸�
			case BUTTON_a_profession_modification_affirm:
				GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//��ȡnewnaeme�����ݵ�new_name
				GetWindowText(EDIT_newcollege,new_college,GetWindowTextLength(EDIT_newcollege)+1);//��ȡnewcollege�����ݵ�new_college
				if(state_a_profession_modification==1)//ȷ���޸�����רҵ��Ϣ
				{
				if(strlen(new_name)>28)
				{
					MessageBox(NULL,"רҵ������������","����",MB_OK);
					strcpy(new_name,profession_old_info->name);
					SetWindowText(EDIT_newname,profession_old_info->name);
					return FALSE;
				}
				if(strcmp(new_name,profession_old_info->name)==0)
				{
					MessageBox(NULL,"û���޸��κ���Ϣ��","����",MB_OK);
					return FALSE;
				}
				if(strcmp(new_college,profession_old_info->college)==0)
				{
					MessageBox(NULL,"�µ�����ѧԺ��Ϣ����洢��\n�����޸�ѧԺ��ɾ�����ݺ����¹涨ѧԺ��","����",MB_OK);
					return FALSE;
				}
				profession_modification_p=profession_head->next;
				for(i=0;i<profession_old_info->id;i++)
					profession_modification_p=profession_modification_p->next;
				strcpy(profession_modification_p->name,new_name);
				profession_save(profession_head);
				profession_load(profession_head);
				SetWindowText(EDIT_oldname,new_name);
				MessageBox(NULL,"�޸ĳɹ���","����",MB_OK);
				}
				if(state_a_profession_modification==2)//ȷ������ѧԺ��Ϣ
				{
					GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//��ȡnewnaeme�����ݵ�new_name
					GetWindowText(EDIT_newcollege,new_college,GetWindowTextLength(EDIT_newcollege)+1);//��ȡnewcollege�����ݵ�new_college
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
						MessageBox(NULL,"ѧԺ�����ڣ�","����",MB_OK);
						break;
						return FALSE;
					}
					if(strlen(new_name)==0||strlen(new_name)>20)
					{
						MessageBox(NULL,"רҵ���ƷǷ���","����",MB_OK);
						add_profession=0;
						break;
						return FALSE;
					}
					for(i=0;i<profession_head->next->num;i++)
					{
						profession_modification_p=profession_modification_p->next;
						if(strcmp(profession_new_info->name,profession_modification_p->name)==0)
						{
							MessageBox(NULL,"רҵ�����ظ���","����",MB_OK);
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
					MessageBox(NULL,"�޸ĳɹ���","��ʾ",MB_OK);
					profession_old_info=(profession_List)malloc(sizeof(profession_Lnode));
					strcpy(profession_old_info->name,profession_new_info->name);
					profession_old_info->id=profession_new_info->id;
					profession_old_info->num=profession_new_info->id;
					find_a_profession_modification=1;
				}
				break;
			//ɾ��ѧԺ
			case BUTTON_a_profession_modification_delete:
				if(find_a_profession_modification==1)
				{
				strcpy(message_a_profession_modification,"ȷ��ɾ��רҵ����");
				strcat(message_a_profession_modification,profession_old_info->name);
				strcat(message_a_profession_modification,"����");
				if(MessageBox(NULL,message_a_profession_modification,"����",MB_YESNO|MB_ICONEXCLAMATION)!=6)
				{
					return FALSE;
				}
				profession_modification_p=profession_head->next;
				for(i=0;i<profession_old_info->id;i++)
					profession_modification_p=profession_modification_p->next;
				profession_modification_p->num=-1;
				strcat(profession_modification_p->name,"����ɾ����");
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
				MessageBox(NULL,"ɾ���ɹ���","����",MB_OK);
				find_a_profession_modification=0;
				break;
				}
				MessageBox(NULL,"�Ƿ�������","����",MB_OK);
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
//IDD_a_course_inquir���ڻص�����
	int course_ck=0; //����Ƿ��ʼ�����ݣ�1.�ǣ�0.��
	int course_now;
LRESULT CALLBACK	A_COURSE_INQUIRE(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,sum,page,print;//sum.�������� page.��ҳ�� now.��ǰҳ�� print.��ǰҳ��������
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
					print=6;//������������С��6�����һҳ��ʾ6������
				if(sum<6)
					print=sum;//����������С��6�����һҳ��ʾȫ��sum������
				page_head=course_head->next->next;//ָ���һҳ��һ����¼
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
				strcpy(char_page,"��");
				itoa(course_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ����");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				break;
			case BUTTON_a_course_inquire_prior:
				if(course_ck!=1)
				{
					MessageBox(NULL,"���������ض�������ʾ��һҳѧԺ��Ϣ��","��ʾ",MB_OK);
					break;
				}
				page_head=course_head->next->next;
				if(course_now-1<=0)
				{
					MessageBox(NULL,"�Ѿ�����һҳ��","��ʾ",MB_OK);
					return FALSE;
				}
				else
					course_now--;
				for(i=0;i<(course_now-1)*6;i++)//��page_head�Ƶ���ǰҳ�ĵ�һ��
					page_head=page_head->next;
				
				if(course_now==page)//��������һҳ����������һҳ��¼����
					print=sum-(page-1)*6;
				else//���򣬼�¼����Ϊ6
					print=6;
				//��ձ༭������
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
				strcpy(char_page,"��");
				itoa(course_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ����");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_course_inquire_next:
				if(course_ck!=1)
				{
					MessageBox(NULL,"���������ض�������ʾ��һҳѧԺ��Ϣ��","��ʾ",MB_OK);
					break;
				}
				page_head=course_head->next->next;//�Ƶ���¼��һҳ��һ����¼
				if(course_now+1>page)//�����ǰҳ+1������ҳ������������
				{
					MessageBox(NULL,"�Ѿ������һҳ��","��ʾ",MB_OK);
					return FALSE;
				}
				else//������תҳ��
				{
					course_now++;
				}
				for(i=0;i<(course_now-1)*6;i++)//��page_head�Ƶ���ǰҳ�ĵ�һ��
					page_head=page_head->next;
				
				if(course_now==page)//��������һҳ����������һҳ��¼����
					print=sum-(page-1)*6;
				else//���򣬼�¼����Ϊ6
					print=6;
				//��ձ༭������
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
				strcpy(char_page,"��");
				
				itoa(course_now,item,10);

				strcat(char_page,item);
				
				strcat(char_page,"ҳ����");
				itoa(page,item,10);//ת������Ϊ�ַ���
				strcat(char_page,item);
				strcat(char_page,"ҳ");
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
//IDD_a_course_modification���ڻص�����
	int find_a_course_modification;//0.�ҵ� 1.δ�ҵ�
	int state_a_course_modification;//�޸�״̬��ʾ
	char course_item[10];
	course_List course_modification_p,course_new_info,course_old_info;
	course_List course_delete;
LRESULT CALLBACK	A_COURSE_MODIFICATION(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HWND EDIT_oldid,EDIT_oldid1,EDIT_oldname,EDIT_newid,EDIT_newname;
	char  new_name[50];
	char message_a_course_modification[60];
	char *stop;//Ϊstrtol�������ֹ�ַ�ָ��
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
			//ͨ��id��λѧԺ
			case BUTTON_a_course_modification_location:
				find_a_course_modification=0;
				GetWindowText(EDIT_oldid,course_item,GetWindowTextLength(EDIT_oldid)+1);//��ȡoldid�༭�����ݵ�item
				id=strtol(course_item,&stop,10);//ת������Ϊ������
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
					MessageBox(NULL,"��������","ERROR!",MB_OK);
					break;
					return FALSE;
				}
				SetWindowText(EDIT_oldid1,course_item);
				SetWindowText(EDIT_newid,course_item);
				SetWindowText(EDIT_oldname,course_old_info->name);
				SetWindowText(EDIT_newname,course_old_info->name);
				state_a_course_modification=1;//�޸�״̬Ϊ�޸�
				break;
			//����ѧԺ
			case BUTTON_a_course_modification_add:
				MessageBox(NULL,"��������Ϣ���������¿γ�����","��ʾ",MB_OK);
				find_a_course_modification=0;
				state_a_course_modification=2;//�޸�״̬Ϊ����ѧԺ
				SetWindowText(EDIT_oldid,"");
				SetWindowText(EDIT_oldid1,"");
				SetWindowText(EDIT_newid,"");
				SetWindowText(EDIT_oldname,"");
				SetWindowText(EDIT_newname,"");
				course_new_info=(course_List)malloc(sizeof(course_Lnode));
				course_new_info->id=course_head->next->num+1;
				course_new_info->num=course_head->next->num+1;
				itoa(course_new_info->id,course_item,10);//ת������Ϊ�ַ���
				SetWindowText(EDIT_newid,course_item);
				break;
			//ȷ���޸�
			case BUTTON_a_course_modification_affirm:
				GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//��ȡnewnaeme�����ݵ�new_name
				if(state_a_course_modification==1)//ȷ���޸�����ѧԺ��Ϣ
				{
				if(strlen(new_name)>20)
				{
					MessageBox(NULL,"��������","����",MB_OK);
					strcpy(new_name,course_old_info->name);
					SetWindowText(EDIT_newname,course_old_info->name);
					return FALSE;
				}
				if(strcmp(new_name,course_old_info->name)==0)
				{
					MessageBox(NULL,"û���޸��κ���Ϣ��","����",MB_OK);
					return FALSE;
				}
				course_modification_p=course_head->next;
				for(i=0;i<course_old_info->id;i++)
					course_modification_p=course_modification_p->next;
				strcpy(course_modification_p->name,new_name);
				course_save(course_head);
				course_load(course_head);
				SetWindowText(EDIT_oldname,new_name);
				MessageBox(NULL,"�޸ĳɹ���","����",MB_OK);
				}
				if(state_a_course_modification==2)//ȷ������ѧԺ��Ϣ
				{
					GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//��ȡnewnaeme�����ݵ�new_name
					strcpy(course_new_info->name,new_name);
					course_modification_p=course_head->next;
					if(strlen(new_name)==0||strlen(new_name)>25)
					{
						MessageBox(NULL,"�γ����ƷǷ���","����",MB_OK);
						break;
						return FALSE;
					}
					for(i=0;i<course_head->next->num;i++)
					{
						course_modification_p=course_modification_p->next;
						if(strcmp(course_new_info->name,course_modification_p->name)==0)
						{
							MessageBox(NULL,"�ÿγ��Ѵ��ڣ�","����",MB_OK);
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
					MessageBox(NULL,"�޸ĳɹ���","��ʾ",MB_OK);
					course_old_info=(course_List)malloc(sizeof(course_Lnode));
					strcpy(course_old_info->name,course_new_info->name);
					course_old_info->id=course_new_info->id;
					course_old_info->num=course_new_info->id;
					find_a_course_modification=1;
				}
				break;
			//ɾ��ѧԺ
			case BUTTON_a_course_modification_delete:
				if(find_a_course_modification==1)
				{
				strcpy(message_a_course_modification,"ȷ��ɾ���γ̣���");
				strcat(message_a_course_modification,course_old_info->name);
				strcat(message_a_course_modification,"����");
				if(MessageBox(NULL,message_a_course_modification,"����",MB_YESNO|MB_ICONEXCLAMATION)!=6)
				{
					return FALSE;
				}
				course_modification_p=course_head->next;
				for(i=0;i<course_old_info->id;i++)
					course_modification_p=course_modification_p->next;
				course_modification_p->num=-1;
				strcat(course_modification_p->name,"����ɾ����");
				course_modification_p=course_head->next->next;
				course_save(course_head);
				course_load(course_head);
				SetWindowText(EDIT_oldid,"");
				SetWindowText(EDIT_oldid1,"");
				SetWindowText(EDIT_newid,"");
				SetWindowText(EDIT_oldname,"");
				SetWindowText(EDIT_newname,"");
				MessageBox(NULL,"ɾ���ɹ���","����",MB_OK);
				find_a_course_modification=0;
				break;
				}
				MessageBox(NULL,"�Ƿ�������","����",MB_OK);
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
//IDD_a_class_inquir���ڻص�����
	int class_ck; //����Ƿ��ʼ�����ݣ�1.�ǣ�0.��
	int class_now;
LRESULT CALLBACK	A_CLASS_INQUIRE(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,sum,page,print;//sum.�������� page.��ҳ�� now.��ǰҳ�� print.��ǰҳ��������
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
					print=6;//������������С��6�����һҳ��ʾ6������
				if(sum<6)
					print=sum;//����������С��6�����һҳ��ʾȫ��sum������
				page_head=class_head->next->next;//ָ���һҳ��һ����¼
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
				strcpy(char_page,"��");
				itoa(class_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ����");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				break;
			case BUTTON_a_class_inquire_prior:
				if(class_ck!=1)
				{
					MessageBox(NULL,"���������ض�������ʾ��һҳѧԺ��Ϣ��","��ʾ",MB_OK);
					break;
				}
				page_head=class_head->next->next;
				if(class_now-1<=0)
				{
					MessageBox(NULL,"�Ѿ�����һҳ��","��ʾ",MB_OK);
					return FALSE;
				}
				else
					class_now--;
				for(i=0;i<(class_now-1)*6;i++)//��page_head�Ƶ���ǰҳ�ĵ�һ��
					page_head=page_head->next;
				
				if(class_now==page)//��������һҳ����������һҳ��¼����
					print=sum-(page-1)*6;
				else//���򣬼�¼����Ϊ6
					print=6;
				//��ձ༭������
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
				strcpy(char_page,"��");
				itoa(class_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ����");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_class_inquire_next:
				if(class_ck!=1)
				{
					MessageBox(NULL,"���������ض�������ʾ��һҳѧԺ��Ϣ��","��ʾ",MB_OK);
					break;
				}
				page_head=class_head->next->next;//�Ƶ���¼��һҳ��һ����¼
				if(class_now+1>page)//�����ǰҳ+1������ҳ������������
				{
					MessageBox(NULL,"�Ѿ������һҳ��","��ʾ",MB_OK);
					return FALSE;
				}
				else//������תҳ��
				{
					class_now++;
				}
				for(i=0;i<(class_now-1)*6;i++)//��page_head�Ƶ���ǰҳ�ĵ�һ��
					page_head=page_head->next;
				
				if(class_now==page)//��������һҳ����������һҳ��¼����
					print=sum-(page-1)*6;
				else//���򣬼�¼����Ϊ6
					print=6;
				//��ձ༭������
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
				strcpy(char_page,"��");
				
				itoa(class_now,item,10);

				strcat(char_page,item);
				
				strcat(char_page,"ҳ����");
				itoa(page,item,10);//ת������Ϊ�ַ���
				strcat(char_page,item);
				strcat(char_page,"ҳ");
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
//IDD_a_class_modification���ڻص�����

	int find_a_class_modification;//0.�ҵ� 1.δ�ҵ�
	int state_a_class_modification;//�޸�״̬��ʾ
	int add_class=0;//������Ϣ�Ϸ���1.ѧԺ�Ϸ�,2.רҵ�Ϸ� other.���Ϸ�-1.ѧԺ���Ϸ� -2.רҵ���Ϸ�
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
	char *stop;//Ϊstrtol�������ֹ�ַ�ָ��
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
			//ͨ��id��λרҵ
			case BUTTON_a_class_modification_location:
				find_a_class_modification=0;
				GetWindowText(EDIT_oldid,class_item,GetWindowTextLength(EDIT_oldid)+1);//��ȡoldid�༭�����ݵ�item
				id=strtol(class_item,&stop,10);//ת������Ϊ������
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
					MessageBox(NULL,"��������","ERROR!",MB_OK);
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
				state_a_class_modification=1;//�޸�״̬Ϊ�޸�
				break;
			//����ѧԺ
			case BUTTON_a_class_modification_add:
				MessageBox(NULL,"��������Ϣ����������רҵ�����Լ�������ѧԺ����","��ʾ",MB_OK);
				find_a_class_modification=0;
				state_a_class_modification=2;//�޸�״̬Ϊ����ѧԺ
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
				itoa(class_new_info->id,class_item,10);//ת������Ϊ�ַ���
				SetWindowText(EDIT_newid,class_item);
				break;
			//ȷ���޸�
			case BUTTON_a_class_modification_affirm:
				GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//��ȡnewnaeme�����ݵ�new_name
				GetWindowText(EDIT_newcollege,new_college,GetWindowTextLength(EDIT_newcollege)+1);//��ȡnewcollege�����ݵ�new_college
				GetWindowText(EDIT_newprofession,new_profession,GetWindowTextLength(EDIT_newprofession)+1);//��ȡnewprofession�����ݵ�new_profession
				if(state_a_class_modification==1)//ȷ���޸�����רҵ��Ϣ
				{
				if(strlen(new_name)>28)
				{
					MessageBox(NULL,"�༶������������","����",MB_OK);
					strcpy(new_name,class_old_info->name);
					SetWindowText(EDIT_newname,class_old_info->name);
					return FALSE;
				}
				if(strcmp(new_name,class_old_info->name)==0)
				{
					MessageBox(NULL,"û���޸��κ���Ϣ��","����",MB_OK);
					return FALSE;
				}
				if((strcmp(new_college,class_old_info->college)==0)||(strcmp(new_profession,class_old_info->profession)==0))
				{
					MessageBox(NULL,"�µ�����ѧԺ��רҵ��Ϣ����洢�������޸�ѧԺ��רҵ��ɾ�����ݺ����¹涨ѧԺ��","����",MB_OK);
					return FALSE;
				}
				class_modification_p=class_head->next;
				for(i=0;i<class_old_info->id;i++)
					class_modification_p=class_modification_p->next;
				strcpy(class_modification_p->name,new_name);
				class_save(class_head);
				class_load(class_head);
				SetWindowText(EDIT_oldname,new_name);
				MessageBox(NULL,"�޸ĳɹ���","����",MB_OK);
				}
				if(state_a_class_modification==2)//ȷ������ѧԺ��Ϣ
				{
					GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//��ȡnewnaeme�����ݵ�new_name
					GetWindowText(EDIT_newcollege,new_college,GetWindowTextLength(EDIT_newcollege)+1);//��ȡnewcollege�����ݵ�new_college
					GetWindowText(EDIT_newprofession,new_profession,GetWindowTextLength(EDIT_newprofession)+1);//��ȡnewprofession�����ݵ�new_profession
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
						MessageBox(NULL,"ѧԺ�����ڣ�","����",MB_OK);
						break;
						return FALSE;
					}
					if(add_class==1)
					{
						MessageBox(NULL,"רҵ�����ڣ�","����",MB_OK);
						break;
						return FALSE;
					}
					if(strlen(new_name)==0||strlen(new_name)>40)
					{
						MessageBox(NULL,"רҵ���ƷǷ���","����",MB_OK);
						add_class=0;
						break;
						return FALSE;
					}
					for(i=0;i<class_head->next->num;i++)
					{
						class_modification_p=class_modification_p->next;
						if(strcmp(class_new_info->name,class_modification_p->name)==0)
						{
							MessageBox(NULL,"�༶�����ظ���","����",MB_OK);
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
					MessageBox(NULL,"�޸ĳɹ���","��ʾ",MB_OK);
					class_old_info=(class_List)malloc(sizeof(class_Lnode));
					strcpy(class_old_info->name,class_new_info->name);
					class_old_info->id=class_new_info->id;
					class_old_info->num=class_new_info->id;
					find_a_class_modification=1;
				}
				break;
			//ɾ��ѧԺ
			case BUTTON_a_class_modification_delete:
				if(find_a_class_modification==1)
				{
				strcpy(message_a_class_modification,"ȷ��ɾ��רҵ����");
				strcat(message_a_class_modification,class_old_info->name);
				strcat(message_a_class_modification,"����");
				if(MessageBox(NULL,message_a_class_modification,"����",MB_YESNO|MB_ICONEXCLAMATION)!=6)
				{
					return FALSE;
				}
				class_modification_p=class_head->next;
				for(i=0;i<class_old_info->id;i++)
					class_modification_p=class_modification_p->next;
				class_modification_p->num=-1;
				strcat(class_modification_p->name,"����ɾ����");
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
				MessageBox(NULL,"ɾ���ɹ���","����",MB_OK);
				find_a_class_modification=0;
				break;
				}
				MessageBox(NULL,"�Ƿ�������","����",MB_OK);
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
//IDD_a_account_inquir���ڻص�����
	int account_ck; //����Ƿ��ʼ�����ݣ�1.�ǣ�0.��
	int account_now;
LRESULT CALLBACK	A_ACCOUNT_INQUIRE(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,sum,page,print;//sum.�������� page.��ҳ�� now.��ǰҳ�� print.��ǰҳ��������
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
					print=6;//������������С��6�����һҳ��ʾ6������
				if(sum<6)
					print=sum;//����������С��6�����һҳ��ʾȫ��sum������
				page_head=account_head->next->next;//ָ���һҳ��һ����¼
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
				strcpy(char_page,"��");
				itoa(account_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ����");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				break;
			case BUTTON_a_account_inquire_prior:
				if(account_ck!=1)
				{
					MessageBox(NULL,"���������ض�������ʾ��һҳѧԺ��Ϣ��","��ʾ",MB_OK);
					break;
				}
				page_head=account_head->next->next;
				if(account_now-1<=0)
				{
					MessageBox(NULL,"�Ѿ�����һҳ��","��ʾ",MB_OK);
					return FALSE;
				}
				else
					account_now--;
				for(i=0;i<(account_now-1)*6;i++)//��page_head�Ƶ���ǰҳ�ĵ�һ��
					page_head=page_head->next;
				
				if(account_now==page)//��������һҳ����������һҳ��¼����
					print=sum-(page-1)*6;
				else//���򣬼�¼����Ϊ6
					print=6;
				//��ձ༭������
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
				strcpy(char_page,"��");
				itoa(account_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ����");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_account_inquire_next:
				if(account_ck!=1)
				{
					MessageBox(NULL,"���������ض�������ʾ��һҳѧԺ��Ϣ��","��ʾ",MB_OK);
					break;
				}
				page_head=account_head->next->next;//�Ƶ���¼��һҳ��һ����¼
				if(account_now+1>page)//�����ǰҳ+1������ҳ������������
				{
					MessageBox(NULL,"�Ѿ������һҳ��","��ʾ",MB_OK);
					return FALSE;
				}
				else//������תҳ��
				{
					account_now++;
				}
				for(i=0;i<(account_now-1)*6;i++)//��page_head�Ƶ���ǰҳ�ĵ�һ��
					page_head=page_head->next;
				
				if(account_now==page)//��������һҳ����������һҳ��¼����
					print=sum-(page-1)*6;
				else//���򣬼�¼����Ϊ6
					print=6;
				//��ձ༭������
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
				strcpy(char_page,"��");
				
				itoa(account_now,item,10);

				strcat(char_page,item);
				
				strcat(char_page,"ҳ����");
				itoa(page,item,10);//ת������Ϊ�ַ���
				strcat(char_page,item);
				strcat(char_page,"ҳ");
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
//IDD_a_account_modification���ڻص�����

	int find_a_account_modification;//0.�ҵ� 1.δ�ҵ�
	int state_a_account_modification;//�޸�״̬��ʾ
	int add_account;//������Ϣ�Ϸ���1.�Ϸ�,other.���Ϸ�
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
	char *stop;//Ϊstrtol�������ֹ�ַ�ָ��
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
			//ͨ��id��λ����
			case BUTTON_a_account_modification_location:
				find_a_account_modification=0;
				GetWindowText(EDIT_oldid,account_item,GetWindowTextLength(EDIT_oldid)+1);//��ȡoldid�༭�����ݵ�item
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
					MessageBox(NULL,"��������","ERROR!",MB_OK);
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

				state_a_account_modification=1;//�޸�״̬Ϊ�޸�
				MessageBox(NULL,"��λ�ɹ������޸����ݻ�ɾ�����ݡ��޸���ϰ���ȷ���޸ġ����棡","ERROR!",MB_OK);
				break;
			//�������
			case BUTTON_a_account_modification_add:
				MessageBox(NULL,"������������Ϣ���������¹���Ա��Ϣ,��ʼ����Ϊ��admin��","��ʾ",MB_OK);
				find_a_account_modification=0;
				state_a_account_modification=2;//�޸�״̬Ϊ�������

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

				SetWindowText(EDIT_newid,"�˺��ַ���<20");
				SetWindowText(EDIT_newname,"��������<10");
				SetWindowText(EDIT_newsex,"��orŮ");
				SetWindowText(EDIT_newnation,"xx��");
				SetWindowText(EDIT_newface,"Ⱥ��");
				SetWindowText(EDIT_newbirth,"xxxx��xx��xx��");
				SetWindowText(EDIT_newtime,"xxxx��xx��");
				SetWindowText(EDIT_newcollege,"xxxxxxxxxxxxxxѧԺ");
				SetWindowText(EDIT_newprofession,"");
				SetWindowText(EDIT_newgrade,"��ʦ");

				account_new_info=(account_List)malloc(sizeof(account_Lnode));
				account_new_info->num=account_head->next->num+1;
				itoa(account_new_info->num,account_item,10);
				strcpy(message_a_account_modification,"�¹���Ա����Ϊ��");
				strcat(message_a_account_modification,account_item);
				SetWindowText(EDIT_oldid,message_a_account_modification);
				break;
			//ȷ���޸�
			case BUTTON_a_account_modification_affirm:
				GetWindowText(EDIT_newid,new_id,GetWindowTextLength(EDIT_newid)+1);//��ȡnewid�����ݵ�new_id
				GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//��ȡnewnaeme�����ݵ�new_name
				GetWindowText(EDIT_newsex,new_sex,GetWindowTextLength(EDIT_newsex)+1);//��ȡnewsex�����ݵ�new_sex
				GetWindowText(EDIT_newnation,new_nation,GetWindowTextLength(EDIT_newnation)+1);//��ȡnewnation�����ݵ�new_nation
				GetWindowText(EDIT_newface,new_face,GetWindowTextLength(EDIT_newface)+1);//��ȡnewface�����ݵ�new_face
				GetWindowText(EDIT_newbirth,new_birth,GetWindowTextLength(EDIT_newbirth)+1);//��ȡnewbirth�����ݵ�new_birth
				GetWindowText(EDIT_newtime,new_time,GetWindowTextLength(EDIT_newtime)+1);//��ȡnewtime�����ݵ�new_time
				GetWindowText(EDIT_newcollege,new_college,GetWindowTextLength(EDIT_newcollege)+1);//��ȡnewcollege�����ݵ�new_college
				GetWindowText(EDIT_newprofession,new_profession,GetWindowTextLength(EDIT_newprofession)+1);//��ȡnewprofession�����ݵ�new_profession
				GetWindowText(EDIT_newgrade,new_grade,GetWindowTextLength(EDIT_newgrade)+1);//��ȡnewngrade�����ݵ�new_grade
				if(state_a_account_modification==1)//ȷ���޸�����רҵ��Ϣ
				{
				if(strcmp(new_id,account_old_info->id)!=0)
				{
					MessageBox(NULL,"�������޸��˺ţ�","����",MB_OK);
					strcpy(new_id,account_old_info->id);
					SetWindowText(EDIT_newid,account_old_info->id);
					return FALSE;
				}
				if(strlen(new_name)>28||strlen(new_name)<2)
				{
					MessageBox(NULL,"����Ա������������","����",MB_OK);
					strcpy(new_name,account_old_info->name);
					SetWindowText(EDIT_newname,account_old_info->name);
					return FALSE;
				}
				if((strcmp(new_sex,"��")!=0)&&strcmp(new_sex,"Ů")!=0)
				{
					MessageBox(NULL,"����Ա�Ա���������","����",MB_OK);
					strcpy(new_sex,account_old_info->sex);
					SetWindowText(EDIT_newsex,account_old_info->sex);
					return FALSE;
				}
				if(strlen(new_nation)>12||strlen(new_nation)<2)
				{
					MessageBox(NULL,"����Ա������������","����",MB_OK);
					strcpy(new_nation,account_old_info->nation);
					SetWindowText(EDIT_newnation,account_old_info->nation);
					return FALSE;
				}
				if(strlen(new_face)>12||strlen(new_face)<2)
				{
					MessageBox(NULL,"����Ա������������","����",MB_OK);
					strcpy(new_face,account_old_info->face);
					SetWindowText(EDIT_newface,account_old_info->face);
					return FALSE;
				}
				sscanf(new_birth,"%4s%*2s%2s%*2s%2s%*s",&year,&month,&day);
				if(strcmp(year,"1960")<0||strcmp(year,"2017")>0)
					{
					MessageBox(NULL,"����Ա���������������","����",MB_OK);
					strcpy(new_birth,account_old_info->birth);
					SetWindowText(EDIT_newbirth,account_old_info->birth);
					return FALSE;
				}
				if(strcmp(month,"01")<0||strcmp(month,"12")>0)
					{
					MessageBox(NULL,"����Ա�����·���������","����",MB_OK);
					strcpy(new_birth,account_old_info->birth);
					SetWindowText(EDIT_newbirth,account_old_info->birth);
					return FALSE;
				}
				if(strcmp(day,"01")<0||strcmp(day,"31")>0)
					{
					MessageBox(NULL,"����Ա����������������","����",MB_OK);
					strcpy(new_birth,account_old_info->birth);
					SetWindowText(EDIT_newbirth,account_old_info->birth);
					return FALSE;
				}
				sscanf(new_time,"%4s%*2s%2s%*2s%*s",&year,&month);
				if(strcmp(year,"1960")<0||strcmp(year,"2017")>0)
					{
					MessageBox(NULL,"����Ա��ְ�����������","����",MB_OK);
					strcpy(new_time,account_old_info->time);
					SetWindowText(EDIT_newtime,account_old_info->time);
					return FALSE;
				}
				if(strcmp(month,"01")<0||strcmp(month,"12")>0)
					{
					MessageBox(NULL,"����Ա��ְ�·���������","����",MB_OK);
					strcpy(new_time,account_old_info->time);
					SetWindowText(EDIT_newtime,account_old_info->time);
					return FALSE;
				}

				if(strcmp(new_college,account_old_info->college)!=0)
				{
					MessageBox(NULL,"�µ�����ѧԺ��Ϣ����洢��\n�����޸�ѧԺ��ɾ�����ݺ����¹涨ѧԺ��","����",MB_OK);
					return FALSE;
				}
				if(strlen(new_profession)>30||strlen(new_profession)<2)
				{
					MessageBox(NULL,"����Ա����������������","����",MB_OK);
					strcpy(new_profession,account_old_info->profession);
					SetWindowText(EDIT_newprofession,account_old_info->profession);
					return FALSE;
				}

				if(strlen(new_grade)>20||strlen(new_grade)<2)
				{
					MessageBox(NULL,"����Ա����������������","����",MB_OK);
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
				MessageBox(NULL,"�޸ĳɹ���","����",MB_OK);
				}

				
				if(state_a_account_modification==2)//ȷ������ѧԺ��Ϣ
				{
					GetWindowText(EDIT_newid,new_id,GetWindowTextLength(EDIT_newid)+1);//��ȡnewid�����ݵ�new_id
				GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//��ȡnewnaeme�����ݵ�new_name
				GetWindowText(EDIT_newsex,new_sex,GetWindowTextLength(EDIT_newsex)+1);//��ȡnewsex�����ݵ�new_sex
				GetWindowText(EDIT_newnation,new_nation,GetWindowTextLength(EDIT_newnation)+1);//��ȡnewnation�����ݵ�new_nation
				GetWindowText(EDIT_newface,new_face,GetWindowTextLength(EDIT_newface)+1);//��ȡnewface�����ݵ�new_face
				GetWindowText(EDIT_newbirth,new_birth,GetWindowTextLength(EDIT_newbirth)+1);//��ȡnewbirth�����ݵ�new_birth
				GetWindowText(EDIT_newtime,new_time,GetWindowTextLength(EDIT_newtime)+1);//��ȡnewtime�����ݵ�new_time
				GetWindowText(EDIT_newcollege,new_college,GetWindowTextLength(EDIT_newcollege)+1);//��ȡnewcollege�����ݵ�new_college
				GetWindowText(EDIT_newprofession,new_profession,GetWindowTextLength(EDIT_newprofession)+1);//��ȡnewprofession�����ݵ�new_profession
				GetWindowText(EDIT_newgrade,new_grade,GetWindowTextLength(EDIT_newgrade)+1);//��ȡnewngrade�����ݵ�new_grade
				if(strlen(new_id)>28||strlen(new_id)<2)
				{
					MessageBox(NULL,"����Ա�˺���������","����",MB_OK);
					SetWindowText(EDIT_newid,"");
					break;
					return FALSE;
				}	
				if(strlen(new_name)>28||strlen(new_name)<2)
				{
					MessageBox(NULL,"����Ա������������","����",MB_OK);
					SetWindowText(EDIT_newname,"");
					break;
					return FALSE;
				}
				if((strcmp(new_sex,"��")!=0)&&strcmp(new_sex,"Ů")!=0)
				{
					MessageBox(NULL,"����Ա�Ա���������","����",MB_OK);
					SetWindowText(EDIT_newsex,"");
					break;
					return FALSE;
				}
				if(strlen(new_nation)>12||strlen(new_nation)<2)
				{
					MessageBox(NULL,"����Ա������������","����",MB_OK);
					SetWindowText(EDIT_newnation,"");
					break;
					return FALSE;
				}
				if(strlen(new_face)>12||strlen(new_face)<2)
				{
					MessageBox(NULL,"����Ա������ò��������","����",MB_OK);
					SetWindowText(EDIT_newface,"");
					break;
					return FALSE;
				}
				sscanf(new_birth,"%4s%*2s%2s%*2s%2s%*s",&year,&month,&day);
				if(strcmp(year,"1960")<0||strcmp(year,"2017")>0)
					{
					MessageBox(NULL,"����Ա���������������","����",MB_OK);
					SetWindowText(EDIT_newbirth,"");
					break;
					return FALSE;
				}
				if(strcmp(month,"01")<0||strcmp(month,"12")>0)
					{
					MessageBox(NULL,"����Ա�����·���������","����",MB_OK);
					SetWindowText(EDIT_newbirth,"");
					break;
					return FALSE;
				}
				if(strcmp(day,"01")<0||strcmp(day,"31")>0)
					{
					MessageBox(NULL,"����Ա����������������","����",MB_OK);
					SetWindowText(EDIT_newbirth,"");
					break;
					return FALSE;
				}
				sscanf(new_time,"%4s%*2s%2s%*s",&year1,&month1);
				if(strcmp(year1,"1960")<0||strcmp(year1,"2017")>0)
					{
					MessageBox(NULL,"����Ա��ְ�����������","����",MB_OK);
					SetWindowText(EDIT_newtime,"");
					break;
					return FALSE;
				}
				if(strcmp(month1,"01")<0||strcmp(month1,"12")>0)
					{
					MessageBox(NULL,"����Ա��ְ�·���������","����",MB_OK);
					SetWindowText(EDIT_newtime,"");
					break;
					return FALSE;
				}

				if(strlen(new_profession)>30||strlen(new_profession)<2)
				{
					MessageBox(NULL,"����Ա����������������","����",MB_OK);
					SetWindowText(EDIT_newprofession,"");
					break;
					return FALSE;
				}
				if(strlen(new_grade)>20||strlen(new_grade)<2)
				{
					MessageBox(NULL,"����Ա����������������","����",MB_OK);
					SetWindowText(EDIT_newgrade,"");
					break;
					return FALSE;
				}
					strcpy(account_new_info->password,"admin");
					strcpy(account_new_info->identity,"����Ա");
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
						MessageBox(NULL,"ѧԺ�����ڣ�","����",MB_OK);
						break;
						return FALSE;
					}
					if(strlen(new_name)==0||strlen(new_name)>20)
					{
						MessageBox(NULL,"רҵ���ƷǷ���","����",MB_OK);
						add_account=0;
						break;
						return FALSE;
					}
					for(i=0;i<account_head->next->num;i++)
					{
						account_modification_p=account_modification_p->next;
						if(strcmp(account_new_info->id,account_modification_p->id)==0)
						{
							MessageBox(NULL,"�˺��ظ���","����",MB_OK);
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

					MessageBox(NULL,"�޸ĳɹ���","��ʾ",MB_OK);
					account_old_info=(account_List)malloc(sizeof(account_Lnode));
					strcpy(account_old_info->name,account_new_info->name);
					strcpy(account_old_info->id,account_new_info->id);
					account_old_info->num=account_new_info->num;
					find_a_account_modification=1;
				}
				break;
			//ɾ������
			case BUTTON_a_account_modification_delete:
				if(find_a_account_modification==1)
				{
					if(strcmp(account_old_info->id,account_mine->id)==0)
					{
						MessageBox(NULL,"������ɾ���ѵ�¼�˺ţ�","����",MB_OK|MB_ICONEXCLAMATION);
						return FALSE;
					}
				strcpy(message_a_account_modification,"ȷ��ɾ������Ա����");
				strcat(message_a_account_modification,account_old_info->name);
				strcat(message_a_account_modification,"����");
				if(MessageBox(NULL,message_a_account_modification,"����",MB_YESNO|MB_ICONEXCLAMATION)!=6)
				{
					return FALSE;
				}
				account_modification_p=account_head->next;
				for(i=0;i<account_old_info->num;i++)
					account_modification_p=account_modification_p->next;
				account_modification_p->num=-1;
				strcat(account_modification_p->name,"����ɾ����");
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
				MessageBox(NULL,"ɾ���ɹ���","����",MB_OK);
				find_a_account_modification=0;
				break;
				}
				MessageBox(NULL,"�Ƿ�������","����",MB_OK);
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
//IDD_a_teacher_inquir���ڻص�����
	int teacher_ck; //����Ƿ��ʼ�����ݣ�1.�ǣ�0.��
	int teacher_now;
LRESULT CALLBACK	A_TEACHER_INQUIRE(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,sum,page,print;//sum.�������� page.��ҳ�� now.��ǰҳ�� print.��ǰҳ��������
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
					print=6;//������������С��6�����һҳ��ʾ6������
				if(sum<6)
					print=sum;//����������С��6�����һҳ��ʾȫ��sum������
				page_head=teacher_head->next->next;//ָ���һҳ��һ����¼
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
				strcpy(char_page,"��");
				itoa(teacher_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ����");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				break;
			case BUTTON_a_teacher_inquire_prior:
				if(teacher_ck!=1)
				{
					MessageBox(NULL,"���������ض�������ʾ��һҳѧԺ��Ϣ��","��ʾ",MB_OK);
					break;
				}
				page_head=teacher_head->next->next;
				if(teacher_now-1<=0)
				{
					MessageBox(NULL,"�Ѿ�����һҳ��","��ʾ",MB_OK);
					return FALSE;
				}
				else
					teacher_now--;
				for(i=0;i<(teacher_now-1)*6;i++)//��page_head�Ƶ���ǰҳ�ĵ�һ��
					page_head=page_head->next;
				
				if(teacher_now==page)//��������һҳ����������һҳ��¼����
					print=sum-(page-1)*6;
				else//���򣬼�¼����Ϊ6
					print=6;
				//��ձ༭������
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
				strcpy(char_page,"��");
				itoa(teacher_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ����");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_teacher_inquire_next:
				if(teacher_ck!=1)
				{
					MessageBox(NULL,"���������ض�������ʾ��һҳ��ʦ��Ϣ��","��ʾ",MB_OK);
					break;
				}
				page_head=teacher_head->next->next;//�Ƶ���¼��һҳ��һ����¼
				if(teacher_now+1>page)//�����ǰҳ+1������ҳ������������
				{
					MessageBox(NULL,"�Ѿ������һҳ��","��ʾ",MB_OK);
					return FALSE;
				}
				else//������תҳ��
				{
					teacher_now++;
				}
				for(i=0;i<(teacher_now-1)*6;i++)//��page_head�Ƶ���ǰҳ�ĵ�һ��
					page_head=page_head->next;
				
				if(teacher_now==page)//��������һҳ����������һҳ��¼����
					print=sum-(page-1)*6;
				else//���򣬼�¼����Ϊ6
					print=6;
				//��ձ༭������
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
				strcpy(char_page,"��");
				
				itoa(teacher_now,item,10);

				strcat(char_page,item);
				
				strcat(char_page,"ҳ����");
				itoa(page,item,10);//ת������Ϊ�ַ���
				strcat(char_page,item);
				strcat(char_page,"ҳ");
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
//IDD_a_teacher_modification���ڻص�����

	int find_a_teacher_modification;//0.�ҵ� 1.δ�ҵ�
	int state_a_teacher_modification;//�޸�״̬��ʾ
	int add_teacher;//������Ϣ�Ϸ���1.�Ϸ�,other.���Ϸ�
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
	char *stop;//Ϊstrtol�������ֹ�ַ�ָ��
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
			//ͨ��id��λ��ʦ
			case BUTTON_a_teacher_modification_location:
				find_a_teacher_modification=0;
				GetWindowText(EDIT_oldid,teacher_item,GetWindowTextLength(EDIT_oldid)+1);//��ȡoldid�༭�����ݵ�item
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
					MessageBox(NULL,"��������","ERROR!",MB_OK);
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

				state_a_teacher_modification=1;//�޸�״̬Ϊ�޸�
				MessageBox(NULL,"��λ�ɹ������޸����ݻ�ɾ�����ݡ��޸���ϰ���ȷ���޸ġ����棡","ERROR!",MB_OK);
				break;
			//�����ʦ
			case BUTTON_a_teacher_modification_add:
				MessageBox(NULL,"������������Ϣ���������½�ʦ��Ϣ,��ʼ����Ϊ��teacher��","��ʾ",MB_OK);
				find_a_teacher_modification=0;
				state_a_teacher_modification=2;//�޸�״̬Ϊ�����ʦ

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

				SetWindowText(EDIT_newid,"�˺��ַ���<20");
				SetWindowText(EDIT_newname,"��������<10");
				SetWindowText(EDIT_newsex,"��orŮ");
				SetWindowText(EDIT_newnation,"xx��");
				SetWindowText(EDIT_newface,"Ⱥ��");
				SetWindowText(EDIT_newbirth,"xxxx-xx-xx");
				SetWindowText(EDIT_newtime,"xxxx-xx");
				SetWindowText(EDIT_newcollege,"xxxxxxxxxxxxxxѧԺ");
				SetWindowText(EDIT_newprofession,"");
				SetWindowText(EDIT_newgrade,"��ʦ");

				teacher_new_info=(teacher_List)malloc(sizeof(teacher_Lnode));
				teacher_new_info->num=teacher_head->next->num+1;
				itoa(teacher_new_info->num,teacher_item,10);
				strcpy(message_a_teacher_modification,"�½�ʦ����Ϊ��");
				strcat(message_a_teacher_modification,teacher_item);
				SetWindowText(EDIT_oldid,message_a_teacher_modification);
				break;
			//ȷ���޸�
			case BUTTON_a_teacher_modification_affirm:
				GetWindowText(EDIT_newid,new_id,GetWindowTextLength(EDIT_newid)+1);//��ȡnewid�����ݵ�new_id
				GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//��ȡnewnaeme�����ݵ�new_name
				GetWindowText(EDIT_newsex,new_sex,GetWindowTextLength(EDIT_newsex)+1);//��ȡnewsex�����ݵ�new_sex
				GetWindowText(EDIT_newnation,new_nation,GetWindowTextLength(EDIT_newnation)+1);//��ȡnewnation�����ݵ�new_nation
				GetWindowText(EDIT_newface,new_face,GetWindowTextLength(EDIT_newface)+1);//��ȡnewface�����ݵ�new_face
				GetWindowText(EDIT_newbirth,new_birth,GetWindowTextLength(EDIT_newbirth)+1);//��ȡnewbirth�����ݵ�new_birth
				GetWindowText(EDIT_newtime,new_time,GetWindowTextLength(EDIT_newtime)+1);//��ȡnewtime�����ݵ�new_time
				GetWindowText(EDIT_newcollege,new_college,GetWindowTextLength(EDIT_newcollege)+1);//��ȡnewcollege�����ݵ�new_college
				GetWindowText(EDIT_newprofession,new_profession,GetWindowTextLength(EDIT_newprofession)+1);//��ȡnewprofession�����ݵ�new_profession
				GetWindowText(EDIT_newgrade,new_grade,GetWindowTextLength(EDIT_newgrade)+1);//��ȡnewngrade�����ݵ�new_grade
				if(state_a_teacher_modification==1)//ȷ���޸�����רҵ��Ϣ
				{
				if(strcmp(new_id,teacher_old_info->id)!=0)
				{
					MessageBox(NULL,"�������޸��˺ţ�","����",MB_OK);
					strcpy(new_id,teacher_old_info->id);
					SetWindowText(EDIT_newid,teacher_old_info->id);
					return FALSE;
				}
				if(strlen(new_name)>28||strlen(new_name)<2)
				{
					MessageBox(NULL,"��ʦ������������","����",MB_OK);
					strcpy(new_name,teacher_old_info->name);
					SetWindowText(EDIT_newname,teacher_old_info->name);
					return FALSE;
				}
				if((strcmp(new_sex,"��")!=0)&&strcmp(new_sex,"Ů")!=0)
				{
					MessageBox(NULL,"��ʦ�Ա���������","����",MB_OK);
					strcpy(new_sex,teacher_old_info->sex);
					SetWindowText(EDIT_newsex,teacher_old_info->sex);
					return FALSE;
				}
				if(strlen(new_nation)>12||strlen(new_nation)<2)
				{
					MessageBox(NULL,"��ʦ������������","����",MB_OK);
					strcpy(new_nation,teacher_old_info->nation);
					SetWindowText(EDIT_newnation,teacher_old_info->nation);
					return FALSE;
				}
				if(strlen(new_face)>12||strlen(new_face)<2)
				{
					MessageBox(NULL,"��ʦ������������","����",MB_OK);
					strcpy(new_face,teacher_old_info->face);
					SetWindowText(EDIT_newface,teacher_old_info->face);
					return FALSE;
				}
				sscanf(new_birth,"%4s%*1s%2s%*1s%2s%*s",&year,&month,&day);
				if(strcmp(year,"1960")<0||strcmp(year,"2017")>0)
					{
					MessageBox(NULL,"��ʦ���������������","����",MB_OK);
					strcpy(new_birth,teacher_old_info->birth);
					SetWindowText(EDIT_newbirth,teacher_old_info->birth);
					return FALSE;
				}
				if(strcmp(month,"01")<0||strcmp(month,"12")>0)
					{
					MessageBox(NULL,"��ʦ�����·���������","����",MB_OK);
					strcpy(new_birth,teacher_old_info->birth);
					SetWindowText(EDIT_newbirth,teacher_old_info->birth);
					return FALSE;
				}
				if(strcmp(day,"01")<0||strcmp(day,"31")>0)
					{
					MessageBox(NULL,"��ʦ����������������","����",MB_OK);
					strcpy(new_birth,teacher_old_info->birth);
					SetWindowText(EDIT_newbirth,teacher_old_info->birth);
					return FALSE;
				}
				sscanf(new_time,"%4s%*1s%2s%*1s%*s",&year,&month);
				if(strcmp(year,"1960")<0||strcmp(year,"2017")>0)
					{
					MessageBox(NULL,"��ʦ��ְ�����������","����",MB_OK);
					strcpy(new_time,teacher_old_info->time);
					SetWindowText(EDIT_newtime,teacher_old_info->time);
					return FALSE;
				}
				if(strcmp(month,"01")<0||strcmp(month,"12")>0)
					{
					MessageBox(NULL,"��ʦ��ְ�·���������","����",MB_OK);
					strcpy(new_time,teacher_old_info->time);
					SetWindowText(EDIT_newtime,teacher_old_info->time);
					return FALSE;
				}

				if(strcmp(new_college,teacher_old_info->college)!=0)
				{
					MessageBox(NULL,"�µ�����ѧԺ��Ϣ����洢��\n�����޸�ѧԺ��ɾ�����ݺ����¹涨ѧԺ��","����",MB_OK);
					return FALSE;
				}
				if(strlen(new_profession)>30||strlen(new_profession)<2)
				{
					MessageBox(NULL,"��ʦ����������������","����",MB_OK);
					strcpy(new_profession,teacher_old_info->profession);
					SetWindowText(EDIT_newprofession,teacher_old_info->profession);
					return FALSE;
				}

				if(strlen(new_grade)>20||strlen(new_grade)<2)
				{
					MessageBox(NULL,"��ʦ����������������","����",MB_OK);
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
				MessageBox(NULL,"�޸ĳɹ���","����",MB_OK);
				}

				
				if(state_a_teacher_modification==2)//ȷ������ѧԺ��Ϣ
				{
					GetWindowText(EDIT_newid,new_id,GetWindowTextLength(EDIT_newid)+1);//��ȡnewid�����ݵ�new_id
				GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//��ȡnewnaeme�����ݵ�new_name
				GetWindowText(EDIT_newsex,new_sex,GetWindowTextLength(EDIT_newsex)+1);//��ȡnewsex�����ݵ�new_sex
				GetWindowText(EDIT_newnation,new_nation,GetWindowTextLength(EDIT_newnation)+1);//��ȡnewnation�����ݵ�new_nation
				GetWindowText(EDIT_newface,new_face,GetWindowTextLength(EDIT_newface)+1);//��ȡnewface�����ݵ�new_face
				GetWindowText(EDIT_newbirth,new_birth,GetWindowTextLength(EDIT_newbirth)+1);//��ȡnewbirth�����ݵ�new_birth
				GetWindowText(EDIT_newtime,new_time,GetWindowTextLength(EDIT_newtime)+1);//��ȡnewtime�����ݵ�new_time
				GetWindowText(EDIT_newcollege,new_college,GetWindowTextLength(EDIT_newcollege)+1);//��ȡnewcollege�����ݵ�new_college
				GetWindowText(EDIT_newprofession,new_profession,GetWindowTextLength(EDIT_newprofession)+1);//��ȡnewprofession�����ݵ�new_profession
				GetWindowText(EDIT_newgrade,new_grade,GetWindowTextLength(EDIT_newgrade)+1);//��ȡnewngrade�����ݵ�new_grade
				if(strlen(new_id)>28||strlen(new_id)<2)
				{
					MessageBox(NULL,"��ʦ�˺���������","����",MB_OK);
					SetWindowText(EDIT_newid,"");
					break;
					return FALSE;
				}	
				if(strlen(new_name)>28||strlen(new_name)<2)
				{
					MessageBox(NULL,"��ʦ������������","����",MB_OK);
					SetWindowText(EDIT_newname,"");
					break;
					return FALSE;
				}
				if((strcmp(new_sex,"��")!=0)&&strcmp(new_sex,"Ů")!=0)
				{
					MessageBox(NULL,"��ʦ�Ա���������","����",MB_OK);
					SetWindowText(EDIT_newsex,"");
					break;
					return FALSE;
				}
				if(strlen(new_nation)>12||strlen(new_nation)<2)
				{
					MessageBox(NULL,"��ʦ������������","����",MB_OK);
					SetWindowText(EDIT_newnation,"");
					break;
					return FALSE;
				}
				if(strlen(new_face)>12||strlen(new_face)<2)
				{
					MessageBox(NULL,"��ʦ������ò��������","����",MB_OK);
					SetWindowText(EDIT_newface,"");
					break;
					return FALSE;
				}
				sscanf(new_birth,"%4s%*1s%2s%*1s%2s%*s",&year,&month,&day);
				if(strcmp(year,"1960")<0||strcmp(year,"2017")>0)
					{
					MessageBox(NULL,"��ʦ���������������","����",MB_OK);
					SetWindowText(EDIT_newbirth,"");
					break;
					return FALSE;
				}
				if(strcmp(month,"01")<0||strcmp(month,"12")>0)
					{
					MessageBox(NULL,"��ʦ�����·���������","����",MB_OK);
					SetWindowText(EDIT_newbirth,"");
					break;
					return FALSE;
				}
				if(strcmp(day,"01")<0||strcmp(day,"31")>0)
					{
					MessageBox(NULL,"��ʦ����������������","����",MB_OK);
					SetWindowText(EDIT_newbirth,"");
					break;
					return FALSE;
				}
				sscanf(new_time,"%4s%*1s%2s%*s",&year1,&month1);
				if(strcmp(year1,"1960")<0||strcmp(year1,"2017")>0)
					{
					MessageBox(NULL,"��ʦ��ְ�����������","����",MB_OK);
					SetWindowText(EDIT_newtime,"");
					break;
					return FALSE;
				}
				if(strcmp(month1,"01")<0||strcmp(month1,"12")>0)
					{
					MessageBox(NULL,"��ʦ��ְ�·���������","����",MB_OK);
					SetWindowText(EDIT_newtime,"");
					break;
					return FALSE;
				}

				if(strlen(new_profession)>30||strlen(new_profession)<2)
				{
					MessageBox(NULL,"��ʦ����������������","����",MB_OK);
					SetWindowText(EDIT_newprofession,"");
					break;
					return FALSE;
				}
				if(strlen(new_grade)>30||strlen(new_grade)<2)
				{
					MessageBox(NULL,"��ʦְ����������","����",MB_OK);
					SetWindowText(EDIT_newgrade,"");
					break;
					return FALSE;
				}
					strcpy(teacher_new_info->password,"admin");
					strcpy(teacher_new_info->identity,"��ʦ");
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
						MessageBox(NULL,"ѧԺ�����ڣ�","����",MB_OK);
						break;
						return FALSE;
					}
					if(strlen(new_name)==0||strlen(new_name)>20)
					{
						MessageBox(NULL,"רҵ���ƷǷ���","����",MB_OK);
						add_teacher=0;
						break;
						return FALSE;
					}
					for(i=0;i<teacher_head->next->num;i++)
					{
						teacher_modification_p=teacher_modification_p->next;
						if(strcmp(teacher_new_info->id,teacher_modification_p->id)==0)
						{
							MessageBox(NULL,"�˺��ظ���","����",MB_OK);
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

					MessageBox(NULL,"�޸ĳɹ���","��ʾ",MB_OK);
					teacher_old_info=(teacher_List)malloc(sizeof(teacher_Lnode));
					strcpy(teacher_old_info->name,teacher_new_info->name);
					strcpy(teacher_old_info->id,teacher_new_info->id);
					teacher_old_info->num=teacher_new_info->num;
					find_a_teacher_modification=1;
				}
				break;
			//ɾ����ʦ
			case BUTTON_a_teacher_modification_delete:
				if(find_a_teacher_modification==1)
				{
					if(strcmp(teacher_old_info->id,account_mine->id)==0)
					{
						MessageBox(NULL,"������ɾ���ѵ�¼�˺ţ�","����",MB_OK|MB_ICONEXCLAMATION);
						return FALSE;
					}
				strcpy(message_a_teacher_modification,"ȷ��ɾ����ʦ����");
				strcat(message_a_teacher_modification,teacher_old_info->name);
				strcat(message_a_teacher_modification,"����");
				if(MessageBox(NULL,message_a_teacher_modification,"����",MB_YESNO|MB_ICONEXCLAMATION)!=6)
				{
					return FALSE;
				}
				teacher_modification_p=teacher_head->next;
				for(i=0;i<teacher_old_info->num;i++)
					teacher_modification_p=teacher_modification_p->next;
				teacher_modification_p->num=-1;
				strcat(teacher_modification_p->name,"����ɾ����");
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
				MessageBox(NULL,"ɾ���ɹ���","����",MB_OK);
				find_a_teacher_modification=0;
				break;
				}
				MessageBox(NULL,"�Ƿ�������","����",MB_OK);
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
//IDD_a_student_inquir���ڻص�����
	int student_ck; //����Ƿ��ʼ�����ݣ�1.�ǣ�0.��
	int student_now;
LRESULT CALLBACK	A_STUDENT_INQUIRE(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,sum,page,print;//sum.�������� page.��ҳ�� now.��ǰҳ�� print.��ǰҳ��������
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
					print=6;//������������С��6�����һҳ��ʾ6������
				if(sum<6)
					print=sum;//����������С��6�����һҳ��ʾȫ��sum������
				page_head=student_head->next->next;//ָ���һҳ��һ����¼
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
				strcpy(char_page,"��");
				itoa(student_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ����");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				break;
			case BUTTON_a_student_inquire_prior:
				if(student_ck!=1)
				{
					MessageBox(NULL,"���������ض�������ʾ��һҳѧԺ��Ϣ��","��ʾ",MB_OK);
					break;
				}
				page_head=student_head->next->next;
				if(student_now-1<=0)
				{
					MessageBox(NULL,"�Ѿ�����һҳ��","��ʾ",MB_OK);
					return FALSE;
				}
				else
					student_now--;
				for(i=0;i<(student_now-1)*6;i++)//��page_head�Ƶ���ǰҳ�ĵ�һ��
					page_head=page_head->next;
				
				if(student_now==page)//��������һҳ����������һҳ��¼����
					print=sum-(page-1)*6;
				else//���򣬼�¼����Ϊ6
					print=6;
				//��ձ༭������
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
				strcpy(char_page,"��");
				itoa(student_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ����");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_student_inquire_next:
				if(student_ck!=1)
				{
					MessageBox(NULL,"���������ض�������ʾ��һҳѧԺ��Ϣ��","��ʾ",MB_OK);
					break;
				}
				page_head=student_head->next->next;//�Ƶ���¼��һҳ��һ����¼
				if(student_now+1>page)//�����ǰҳ+1������ҳ������������
				{
					MessageBox(NULL,"�Ѿ������һҳ��","��ʾ",MB_OK);
					return FALSE;
				}
				else//������תҳ��
				{
					student_now++;
				}
				for(i=0;i<(student_now-1)*6;i++)//��page_head�Ƶ���ǰҳ�ĵ�һ��
					page_head=page_head->next;
				
				if(student_now==page)//��������һҳ����������һҳ��¼����
					print=sum-(page-1)*6;
				else//���򣬼�¼����Ϊ6
					print=6;
				//��ձ༭������
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
				strcpy(char_page,"��");
				
				itoa(student_now,item,10);

				strcat(char_page,item);
				
				strcat(char_page,"ҳ����");
				itoa(page,item,10);//ת������Ϊ�ַ���
				strcat(char_page,item);
				strcat(char_page,"ҳ");
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
//IDD_a_student_modification���ڻص�����

	int find_a_student_modification;//0.�ҵ� 1.δ�ҵ�
	int state_a_student_modification;//�޸�״̬��ʾ
	int add_student;//������Ϣ�Ϸ���1.ѧԺ�Ϸ�,2.�༶�Ϸ�other.���Ϸ�
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
	char *stop;//Ϊstrtol�������ֹ�ַ�ָ��
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
			//ͨ��id��λѧ��
			case BUTTON_a_student_modification_location:
				find_a_student_modification=0;
				GetWindowText(EDIT_oldid,student_item,GetWindowTextLength(EDIT_oldid)+1);//��ȡoldid�༭�����ݵ�item
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
					MessageBox(NULL,"��������","ERROR!",MB_OK);
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

				state_a_student_modification=1;//�޸�״̬Ϊ�޸�
				MessageBox(NULL,"��λ�ɹ������޸����ݻ�ɾ�����ݡ��޸���ϰ���ȷ���޸ġ����棡","ERROR!",MB_OK);
				break;
			//����ѧ��
			case BUTTON_a_student_modification_add:
				MessageBox(NULL,"������������Ϣ����������ѧ����Ϣ,��ʼ����Ϊ��student��","��ʾ",MB_OK);
				find_a_student_modification=0;
				state_a_student_modification=2;//�޸�״̬Ϊ����ѧ��

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

				SetWindowText(EDIT_newid,"�˺��ַ���<20");
				SetWindowText(EDIT_newname,"��������<10");
				SetWindowText(EDIT_newsex,"��orŮ");
				SetWindowText(EDIT_newnation,"xx��");
				SetWindowText(EDIT_newface,"Ⱥ��");
				SetWindowText(EDIT_newbirth,"xxxx-xx-xx");
				SetWindowText(EDIT_newtime,"xxxx-xx");
				SetWindowText(EDIT_newcollege,"xxxxxxxxxxxxxxѧԺ");
				SetWindowText(EDIT_newprofession,"");
				SetWindowText(EDIT_newgrade,"��ʦ");

				student_new_info=(student_List)malloc(sizeof(student_Lnode));
				student_new_info->num=student_head->next->num+1;
				itoa(student_new_info->num,student_item,10);
				strcpy(message_a_student_modification,"��ѧ������Ϊ��");
				strcat(message_a_student_modification,student_item);
				SetWindowText(EDIT_oldid,message_a_student_modification);
				break;
			//ȷ���޸�
			case BUTTON_a_student_modification_affirm:
				GetWindowText(EDIT_newid,new_id,GetWindowTextLength(EDIT_newid)+1);//��ȡnewid�����ݵ�new_id
				GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//��ȡnewnaeme�����ݵ�new_name
				GetWindowText(EDIT_newsex,new_sex,GetWindowTextLength(EDIT_newsex)+1);//��ȡnewsex�����ݵ�new_sex
				GetWindowText(EDIT_newnation,new_nation,GetWindowTextLength(EDIT_newnation)+1);//��ȡnewnation�����ݵ�new_nation
				GetWindowText(EDIT_newface,new_face,GetWindowTextLength(EDIT_newface)+1);//��ȡnewface�����ݵ�new_face
				GetWindowText(EDIT_newbirth,new_birth,GetWindowTextLength(EDIT_newbirth)+1);//��ȡnewbirth�����ݵ�new_birth
				GetWindowText(EDIT_newtime,new_time,GetWindowTextLength(EDIT_newtime)+1);//��ȡnewtime�����ݵ�new_time
				GetWindowText(EDIT_newcollege,new_college,GetWindowTextLength(EDIT_newcollege)+1);//��ȡnewcollege�����ݵ�new_college
				GetWindowText(EDIT_newprofession,new_profession,GetWindowTextLength(EDIT_newprofession)+1);//��ȡnewprofession�����ݵ�new_profession
				GetWindowText(EDIT_newgrade,new_grade,GetWindowTextLength(EDIT_newgrade)+1);//��ȡnewngrade�����ݵ�new_grade
				if(state_a_student_modification==1)//ȷ���޸�����רҵ��Ϣ
				{
				if(strcmp(new_id,student_old_info->id)!=0)
				{
					MessageBox(NULL,"�������޸��˺ţ�","����",MB_OK);
					strcpy(new_id,student_old_info->id);
					SetWindowText(EDIT_newid,student_old_info->id);
					return FALSE;
				}
				if(strlen(new_name)>28||strlen(new_name)<2)
				{
					MessageBox(NULL,"ѧ��������������","����",MB_OK);
					strcpy(new_name,student_old_info->name);
					SetWindowText(EDIT_newname,student_old_info->name);
					return FALSE;
				}
				if((strcmp(new_sex,"��")!=0)&&strcmp(new_sex,"Ů")!=0)
				{
					MessageBox(NULL,"ѧ���Ա���������","����",MB_OK);
					strcpy(new_sex,student_old_info->sex);
					SetWindowText(EDIT_newsex,student_old_info->sex);
					return FALSE;
				}
				if(strlen(new_nation)>12||strlen(new_nation)<2)
				{
					MessageBox(NULL,"ѧ��������������","����",MB_OK);
					strcpy(new_nation,student_old_info->nation);
					SetWindowText(EDIT_newnation,student_old_info->nation);
					return FALSE;
				}
				if(strlen(new_face)>12||strlen(new_face)<2)
				{
					MessageBox(NULL,"ѧ��������������","����",MB_OK);
					strcpy(new_face,student_old_info->face);
					SetWindowText(EDIT_newface,student_old_info->face);
					return FALSE;
				}
				sscanf(new_birth,"%4s%*1s%2s%*1s%2s%*s",&year,&month,&day);
				if(strcmp(year,"1960")<0||strcmp(year,"2017")>0)
					{
					MessageBox(NULL,"ѧ�����������������","����",MB_OK);
					strcpy(new_birth,student_old_info->birth);
					SetWindowText(EDIT_newbirth,student_old_info->birth);
					return FALSE;
				}
				if(strcmp(month,"01")<0||strcmp(month,"12")>0)
					{
					MessageBox(NULL,"ѧ�������·���������","����",MB_OK);
					strcpy(new_birth,student_old_info->birth);
					SetWindowText(EDIT_newbirth,student_old_info->birth);
					return FALSE;
				}
				if(strcmp(day,"01")<0||strcmp(day,"31")>0)
					{
					MessageBox(NULL,"ѧ������������������","����",MB_OK);
					strcpy(new_birth,student_old_info->birth);
					SetWindowText(EDIT_newbirth,student_old_info->birth);
					return FALSE;
				}
				sscanf(new_time,"%4s%*1s%2s%*1s%*s",&year,&month);
				if(strcmp(year,"1960")<0||strcmp(year,"2017")>0)
					{
					MessageBox(NULL,"ѧ����ְ�����������","����",MB_OK);
					strcpy(new_time,student_old_info->time);
					SetWindowText(EDIT_newtime,student_old_info->time);
					return FALSE;
				}
				if(strcmp(month,"01")<0||strcmp(month,"12")>0)
					{
					MessageBox(NULL,"ѧ����ְ�·���������","����",MB_OK);
					strcpy(new_time,student_old_info->time);
					SetWindowText(EDIT_newtime,student_old_info->time);
					return FALSE;
				}

				if(strcmp(new_college,student_old_info->college)!=0)
				{
					MessageBox(NULL,"�µ�����ѧԺ��Ϣ����洢��\n�����޸�ѧԺ��ɾ�����ݺ����¹涨ѧԺ��","����",MB_OK);
				}
				if(strlen(new_profession)>30||strlen(new_profession)<2)
				{
					MessageBox(NULL,"ѧ������������������","����",MB_OK);
					strcpy(new_profession,student_old_info->profession);
					SetWindowText(EDIT_newprofession,student_old_info->profession);
					return FALSE;
				}

				if(strlen(new_grade)>30||strlen(new_grade)<2)
				{
					MessageBox(NULL,"ѧ�������༶��������","����",MB_OK);
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
				MessageBox(NULL,"�޸ĳɹ���","����",MB_OK);
				}

				
				if(state_a_student_modification==2)//ȷ������ѧԺ��Ϣ
				{
					GetWindowText(EDIT_newid,new_id,GetWindowTextLength(EDIT_newid)+1);//��ȡnewid�����ݵ�new_id
				GetWindowText(EDIT_newname,new_name,GetWindowTextLength(EDIT_newname)+1);//��ȡnewnaeme�����ݵ�new_name
				GetWindowText(EDIT_newsex,new_sex,GetWindowTextLength(EDIT_newsex)+1);//��ȡnewsex�����ݵ�new_sex
				GetWindowText(EDIT_newnation,new_nation,GetWindowTextLength(EDIT_newnation)+1);//��ȡnewnation�����ݵ�new_nation
				GetWindowText(EDIT_newface,new_face,GetWindowTextLength(EDIT_newface)+1);//��ȡnewface�����ݵ�new_face
				GetWindowText(EDIT_newbirth,new_birth,GetWindowTextLength(EDIT_newbirth)+1);//��ȡnewbirth�����ݵ�new_birth
				GetWindowText(EDIT_newtime,new_time,GetWindowTextLength(EDIT_newtime)+1);//��ȡnewtime�����ݵ�new_time
				GetWindowText(EDIT_newcollege,new_college,GetWindowTextLength(EDIT_newcollege)+1);//��ȡnewcollege�����ݵ�new_college
				GetWindowText(EDIT_newprofession,new_profession,GetWindowTextLength(EDIT_newprofession)+1);//��ȡnewprofession�����ݵ�new_profession
				GetWindowText(EDIT_newgrade,new_grade,GetWindowTextLength(EDIT_newgrade)+1);//��ȡnewngrade�����ݵ�new_grade
				
				student_modification_p=student_head->next;
				for(i=0;i<student_head->next->num;i++)
					{
						student_modification_p=student_modification_p->next;
						if(strcmp(student_new_info->id,student_modification_p->id)==0)
						{
							MessageBox(NULL,"�˺��ظ���","����",MB_OK);
							add_student=0;
							//break;
							return FALSE;
						}
					}
				if(strlen(new_id)>28||strlen(new_id)<2)
				{
					MessageBox(NULL,"ѧ���˺���������","����",MB_OK);
					SetWindowText(EDIT_newid,"");
					break;
					return FALSE;
				}	
				if(strlen(new_name)>28||strlen(new_name)<2)
				{
					MessageBox(NULL,"ѧ��������������","����",MB_OK);
					SetWindowText(EDIT_newname,"");
					break;
					return FALSE;
				}
				if((strcmp(new_sex,"��")!=0)&&strcmp(new_sex,"Ů")!=0)
				{
					MessageBox(NULL,"ѧ���Ա���������","����",MB_OK);
					SetWindowText(EDIT_newsex,"");
					break;
					return FALSE;
				}
				if(strlen(new_nation)>12||strlen(new_nation)<2)
				{
					MessageBox(NULL,"ѧ��������������","����",MB_OK);
					SetWindowText(EDIT_newnation,"");
					break;
					return FALSE;
				}
				if(strlen(new_face)>12||strlen(new_face)<2)
				{
					MessageBox(NULL,"ѧ��������ò��������","����",MB_OK);
					SetWindowText(EDIT_newface,"");
					break;
					return FALSE;
				}
				sscanf(new_birth,"%4s%*1s%2s%*1s%2s%*s",&year,&month,&day);
				if(strcmp(year,"1960")<0||strcmp(year,"2017")>0)
					{
					MessageBox(NULL,"ѧ�����������������","����",MB_OK);
					SetWindowText(EDIT_newbirth,"");
					break;
					return FALSE;
				}
				if(strcmp(month,"01")<0||strcmp(month,"12")>0)
					{
					MessageBox(NULL,"ѧ�������·���������","����",MB_OK);
					SetWindowText(EDIT_newbirth,"");
					break;
					return FALSE;
				}
				if(strcmp(day,"01")<0||strcmp(day,"31")>0)
					{
					MessageBox(NULL,"ѧ������������������","����",MB_OK);
					SetWindowText(EDIT_newbirth,"");
					break;
					return FALSE;
				}
				sscanf(new_time,"%4s%*1s%2s%*s",&year1,&month1);
				if(strcmp(year1,"1960")<0||strcmp(year1,"2017")>0)
					{
					MessageBox(NULL,"ѧ����ְ�����������","����",MB_OK);
					SetWindowText(EDIT_newtime,"");
					break;
					return FALSE;
				}
				if(strcmp(month1,"01")<0||strcmp(month1,"12")>0)
					{
					MessageBox(NULL,"ѧ����ְ�·���������","����",MB_OK);
					SetWindowText(EDIT_newtime,"");
					break;
					return FALSE;
				}

				if(strlen(new_profession)>30||strlen(new_profession)<2)
				{
					MessageBox(NULL,"ѧ������������������","����",MB_OK);
					SetWindowText(EDIT_newprofession,"");
					break;
					return FALSE;
				}
				if(strlen(new_grade)>30||strlen(new_grade)<2)
				{
					MessageBox(NULL,"ѧ���༶��������","����",MB_OK);
					SetWindowText(EDIT_newgrade,"");
					break;
					return FALSE;
				}
					strcpy(student_new_info->password,"admin");
					strcpy(student_new_info->identity,"ѧ��");
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
					//������Ϣ�Ϸ���1.ѧԺ�Ϸ�,2.�༶�Ϸ�other.���Ϸ�
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
						MessageBox(NULL,"ѧԺ�����ڣ�","����",MB_OK);
						break;
						return FALSE;
					}
					if(add_student==1&&add_student!=2)
					{
						MessageBox(NULL,"�༶�����ڣ�","����",MB_OK);
						break;
						return FALSE;
					}
					if(strlen(new_name)==0||strlen(new_name)>20)
					{
						MessageBox(NULL,"רҵ���ƷǷ���","����",MB_OK);
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

					MessageBox(NULL,"�޸ĳɹ���","��ʾ",MB_OK);
					student_old_info=(student_List)malloc(sizeof(student_Lnode));
					strcpy(student_old_info->name,student_new_info->name);
					strcpy(student_old_info->id,student_new_info->id);
					student_old_info->num=student_new_info->num;
					find_a_student_modification=1;
				}
				break;
			//ɾ��ѧ��
			case BUTTON_a_student_modification_delete:
				if(find_a_student_modification==1)
				{
					if(strcmp(student_old_info->id,account_mine->id)==0)
					{
						MessageBox(NULL,"������ɾ���ѵ�¼�˺ţ�","����",MB_OK|MB_ICONEXCLAMATION);
						return FALSE;
					}
				strcpy(message_a_student_modification,"ȷ��ɾ��ѧ������");
				strcat(message_a_student_modification,student_old_info->name);
				strcat(message_a_student_modification,"����");
				if(MessageBox(NULL,message_a_student_modification,"����",MB_YESNO|MB_ICONEXCLAMATION)!=6)
				{
					return FALSE;
				}
				student_modification_p=student_head->next;
				for(i=0;i<student_old_info->num;i++)
					student_modification_p=student_modification_p->next;
				student_modification_p->num=-1;
				strcat(student_modification_p->name,"����ɾ����");
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
				MessageBox(NULL,"ɾ���ɹ���","����",MB_OK);
				find_a_student_modification=0;
				break;
				}
				MessageBox(NULL,"�Ƿ�������","����",MB_OK);
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
//IDD_a_score_inquir���ڻص�����
	int score_ck; //����Ƿ��ʼ�����ݣ�1.�ǣ�0.��
	int score_now;
LRESULT CALLBACK	A_SCORE_INQUIRE(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,sum,page,print;//sum.�������� page.��ҳ�� now.��ǰҳ�� print.��ǰҳ��������
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
					MessageBox(NULL,"���ݿ�Ϊ�գ�","ERROR!",MB_OK);
					return FALSE;
				}
				score_ck=1;
				score_now=1;
				if(sum>=6)
					print=6;//������������С��6�����һҳ��ʾ6������
				if(sum<6)
					print=sum;//����������С��6�����һҳ��ʾȫ��sum������
				page_head=score_head->next->next;//ָ���һҳ��һ����¼
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
				strcpy(char_page,"��");
				itoa(score_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ����");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				break;
			case BUTTON_a_score_inquire_prior:
				if(score_ck!=1)
				{
					MessageBox(NULL,"���������ض�������ʾ��һҳ�ɼ���Ϣ��","��ʾ",MB_OK);
					break;
				}
				page_head=score_head->next->next;
				if(score_now-1<=0)
				{
					MessageBox(NULL,"�Ѿ�����һҳ��","��ʾ",MB_OK);
					return FALSE;
				}
				else
					score_now--;
				for(i=0;i<(score_now-1)*6;i++)//��page_head�Ƶ���ǰҳ�ĵ�һ��
					page_head=page_head->next;
				
				if(score_now==page)//��������һҳ����������һҳ��¼����
					print=sum-(page-1)*6;
				else//���򣬼�¼����Ϊ6
					print=6;
				//��ձ༭������
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
				strcpy(char_page,"��");
				itoa(score_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ����");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_score_inquire_next:
				if(score_ck!=1)
				{
					MessageBox(NULL,"���������ض�������ʾ��һҳѧԺ��Ϣ��","��ʾ",MB_OK);
					break;
				}
				page_head=score_head->next->next;//�Ƶ���¼��һҳ��һ����¼
				if(score_now+1>page)//�����ǰҳ+1������ҳ������������
				{
					MessageBox(NULL,"�Ѿ������һҳ��","��ʾ",MB_OK);
					return FALSE;
				}
				else//������תҳ��
				{
					score_now++;
				}
				for(i=0;i<(score_now-1)*6;i++)//��page_head�Ƶ���ǰҳ�ĵ�һ��
					page_head=page_head->next;
				
				if(score_now==page)//��������һҳ����������һҳ��¼����
					print=sum-(page-1)*6;
				else//���򣬼�¼����Ϊ6
					print=6;
				//��ձ༭������
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
				strcpy(char_page,"��");
				
				itoa(score_now,item,10);

				strcat(char_page,item);
				
				strcat(char_page,"ҳ����");
				itoa(page,item,10);//ת������Ϊ�ַ���
				strcat(char_page,item);
				strcat(char_page,"ҳ");
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
//IDD_a_score_modification���ڻص�����

	int find_a_score_modification;//1.�ҵ�=2.�ҵ�ѧ�ƣ�3.�ҵ�ѧ�ڣ�4.�ҵ��˺ţ�5.δ�ҵ�
	int state_a_score_modification;//�޸�״̬��ʾ
	//int add_score;//������Ϣ�Ϸ���1.ѧԺ�Ϸ�,2.�༶�Ϸ�other.���Ϸ�
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
	char *stop;//Ϊstrtol�������ֹ�ַ�ָ��
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
			//ͨ����Ϣ��λ�ɼ�
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
					MessageBox(NULL,"�˺���������","ERROR!",MB_OK);
					break;
					return FALSE;
				}
				if(find_a_score_modification==4)
				{
					MessageBox(NULL,"ѧ����������","ERROR!",MB_OK);
					break;
					return FALSE;
				}
				if(find_a_score_modification==3)
				{
					MessageBox(NULL,"��Ŀ��������","ERROR!",MB_OK);
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

				state_a_score_modification=1;//�޸�״̬Ϊ�޸�
				MessageBox(NULL,"��λ�ɹ������޸����ݻ�ɾ�����ݡ��޸���ϰ���ȷ���޸ġ����棡","ERROR!",MB_OK);
				break;
			case BUTTON_a_score_modification_prior:
				if(find_a_score_modification!=1)
				{
					MessageBox(NULL,"��¼��λʧ�ܣ������Ƿ���","ERROR!",MB_OK);
					return FALSE;
				}
				if(score_modification_p->num==1)
				{
					MessageBox(NULL,"ǰ��û�и����¼��","ERROR!",MB_OK);
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
					MessageBox(NULL,"��¼��λʧ�ܣ������Ƿ���","ERROR!",MB_OK);
					return FALSE;
				}
				if(score_modification_p->num==score_head->next->num)
				{
					MessageBox(NULL,"��û�и����¼��","ERROR!",MB_OK);
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
			//ȷ���޸�
			case BUTTON_a_score_modification_affirm:
				if(find_a_score_modification!=1)
				{
					MessageBox(NULL,"��¼��λʧ�ܣ������Ƿ���","ERROR!",MB_OK);
					return FALSE;
				}
				score_new_info=(score_List)malloc(sizeof(score_Lnode));
				GetWindowText(EDIT_newpaper_score,new_paper_score,GetWindowTextLength(EDIT_newpaper_score)+1);
				GetWindowText(EDIT_newusual_score,new_usual_score,GetWindowTextLength(EDIT_newusual_score)+1);
				GetWindowText(EDIT_newmakeup_score,new_makeup_score,GetWindowTextLength(EDIT_newmakeup_score)+1);
				if((strcmp(new_paper_score,"100")!=0)&&(strcmp(new_paper_score,"00")<0||strcmp(new_paper_score,"99")>0))
				{
					MessageBox(NULL,"���԰ٷ����������ɼ���","����",MB_OK);
					itoa(score_old_info->paper_score,new_paper_score,10);
					SetWindowText(EDIT_newpaper_score,new_paper_score);
					return FALSE;
				}
				if((strcmp(new_paper_score,"100")!=0)&&(strcmp(new_usual_score,"00")<0||strcmp(new_usual_score,"99")>0))
				{
					MessageBox(NULL,"���԰ٷ�������ƽʱ�ɼ���","����",MB_OK);
					itoa(score_old_info->usual_score,new_usual_score,10);
					SetWindowText(EDIT_newusual_score,new_usual_score);
					return FALSE;
				}
				if((strcmp(new_makeup_score,"100")!=0)&&(strcmp(new_makeup_score,"-1")!=0)&&((strcmp(new_makeup_score,"00")<0||strcmp(new_makeup_score,"99")>0)))
				{
					MessageBox(NULL,"���԰ٷ������벹���ɼ���\n�޲�����¼��Ϊ��-1��","����",MB_OK);
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
				MessageBox(NULL,"�޸ĳɹ���","����",MB_OK);
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
			//ɾ��ѧ��
			case BUTTON_a_score_modification_delete:
				if(find_a_score_modification==1)
				{
				strcpy(message_a_score_modification,"ȷ��ɾ��ѧ������");
				strcat(message_a_score_modification,score_old_info->name);
				strcat(message_a_score_modification,"���ı��γɼ���¼��");
				if(MessageBox(NULL,message_a_score_modification,"����",MB_YESNO|MB_ICONEXCLAMATION)!=6)
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
				MessageBox(NULL,"ɾ���ɹ���","����",MB_OK);
				find_a_score_modification=0;
				break;
				}
				MessageBox(NULL,"�Ƿ�������","����",MB_OK);
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
//IDD_a_score_self_inquir���ڻص�����
	int score_self_ck; //����Ƿ��ʼ�����ݣ�1.�ǣ�0.��
	int score_self_now;
LRESULT CALLBACK	A_SCORE_SELF_INQUIRE(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,sum,page,print;//sum.�������� page.��ҳ�� now.��ǰҳ�� print.��ǰҳ��������
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
					MessageBox(NULL,"δ�ҵ���ѧ���κγɼ���¼��","ERROR!",MB_OK);
					return FALSE;
				}
				score_self_ck=1;
				score_self_now=1;
				if(sum>=6)
					print=6;//������������С��6�����һҳ��ʾ6������
				if(sum<6)
					print=sum;//����������С��6�����һҳ��ʾȫ��sum������
				page_head=score_head->next;//ָ���һҳ��һ����¼
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
				strcpy(char_page,"��");
				itoa(score_self_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ����");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				break;
			case BUTTON_a_score_self_inquire_prior:
				if(score_self_ck!=1)
				{
					MessageBox(NULL,"���������ض�������ʾ��һҳ�ɼ���Ϣ��","��ʾ",MB_OK);
					break;
				}
				page_head=score_head->next->next;
				if(score_self_now-1<=0)
				{
					MessageBox(NULL,"�Ѿ�����һҳ��","��ʾ",MB_OK);
					return FALSE;
				}
				else
					score_self_now--;
				for(i=0;i<(score_self_now-1)*6;i++)//��page_head�Ƶ���ǰҳ�ĵ�һ��
					page_head=page_head->next;
				
				if(score_self_now==page)//��������һҳ����������һҳ��¼����
					print=sum-(page-1)*6;
				else//���򣬼�¼����Ϊ6
					print=6;
				//��ձ༭������
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
				strcpy(char_page,"��");
				itoa(score_self_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ����");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_score_self_inquire_next:
				if(score_self_ck!=1)
				{
					MessageBox(NULL,"���������ض�������ʾ��һҳѧԺ��Ϣ��","��ʾ",MB_OK);
					break;
				}
				page_head=score_head->next->next;//�Ƶ���¼��һҳ��һ����¼
				if(score_self_now+1>page)//�����ǰҳ+1������ҳ������������
				{
					MessageBox(NULL,"�Ѿ������һҳ��","��ʾ",MB_OK);
					return FALSE;
				}
				else//������תҳ��
				{
					score_self_now++;
				}
				for(i=0;i<(score_self_now-1)*6;i++)//��page_head�Ƶ���ǰҳ�ĵ�һ��
					page_head=page_head->next;
				
				if(score_self_now==page)//��������һҳ����������һҳ��¼����
					print=sum-(page-1)*6;
				else//���򣬼�¼����Ϊ6
					print=6;
				//��ձ༭������
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
				strcpy(char_page,"��");
				
				itoa(score_self_now,item,10);

				strcat(char_page,item);
				
				strcat(char_page,"ҳ����");
				itoa(page,item,10);//ת������Ϊ�ַ���
				strcat(char_page,item);
				strcat(char_page,"ҳ");
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
//IDD_a_score_term_inquir���ڻص�����
	int score_term_ck; //����Ƿ��ʼ�����ݣ�1.�ǣ�0.��
	int score_term_now;
LRESULT CALLBACK	A_SCORE_TERM_INQUIRE(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	int i,sum,page,print;//sum.�������� page.��ҳ�� now.��ǰҳ�� print.��ǰҳ��������
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
					MessageBox(NULL,"δ�ҵ���ѧ���κγɼ���¼��","ERROR!",MB_OK);
					return FALSE;
				}
				score_term_ck=1;
				score_term_now=1;
				if(sum>=6)
					print=6;//������������С��6�����һҳ��ʾ6������
				if(sum<6)
					print=sum;//����������С��6�����һҳ��ʾȫ��sum������
				page_head=score_head->next;//ָ���һҳ��һ����¼
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
				strcpy(char_page,"��");
				itoa(score_term_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ����");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				break;
			case BUTTON_a_score_term_inquire_prior:
				if(score_term_ck!=1)
				{
					MessageBox(NULL,"���������ض�������ʾ��һҳ�ɼ���Ϣ��","��ʾ",MB_OK);
					break;
				}
				page_head=score_head->next->next;
				if(score_term_now-1<=0)
				{
					MessageBox(NULL,"�Ѿ�����һҳ��","��ʾ",MB_OK);
					return FALSE;
				}
				else
					score_term_now--;
				for(i=0;i<(score_term_now-1)*6;i++)//��page_head�Ƶ���ǰҳ�ĵ�һ��
					page_head=page_head->next;
				
				if(score_term_now==page)//��������һҳ����������һҳ��¼����
					print=sum-(page-1)*6;
				else//���򣬼�¼����Ϊ6
					print=6;
				//��ձ༭������
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
				strcpy(char_page,"��");
				itoa(score_term_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ����");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_score_term_inquire_next:
				if(score_term_ck!=1)
				{
					MessageBox(NULL,"���������ض�������ʾ��һҳѧԺ��Ϣ��","��ʾ",MB_OK);
					break;
				}
				page_head=score_head->next->next;//�Ƶ���¼��һҳ��һ����¼
				if(score_term_now+1>page)//�����ǰҳ+1������ҳ������������
				{
					MessageBox(NULL,"�Ѿ������һҳ��","��ʾ",MB_OK);
					return FALSE;
				}
				else//������תҳ��
				{
					score_term_now++;
				}
				for(i=0;i<(score_term_now-1)*6;i++)//��page_head�Ƶ���ǰҳ�ĵ�һ��
					page_head=page_head->next;
				
				if(score_term_now==page)//��������һҳ����������һҳ��¼����
					print=sum-(page-1)*6;
				else//���򣬼�¼����Ϊ6
					print=6;
				//��ձ༭������
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
				strcpy(char_page,"��");
				
				itoa(score_term_now,item,10);

				strcat(char_page,item);
				
				strcat(char_page,"ҳ����");
				itoa(page,item,10);//ת������Ϊ�ַ���
				strcat(char_page,item);
				strcat(char_page,"ҳ");
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
//IDD_a_score_enter���ڻص�����
	int score_enter_ck; //����Ƿ��ʼ�����ݣ�1.�ǣ�0.��
	int score_enter_now;
	int find_enter;//���ҽ�� -1.�ð༶������¼�룬-2.�İ༶��ѧ��������¼�� ��-3.�ð༶��ѧ�Ƹ�ѧ��������¼�룬0.����δ¼��
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
	int repetition;//���ؽ�� 0.δ�ظ� -1.���ظ�
	int i,j,print;//sum.�������� page.��ҳ�� now.��ǰҳ�� print.��ǰҳ��������
	score_List page_head,score_p;
	char paper_score1[10],paper_score2[10],paper_score3[10],paper_score4[10],paper_score5[10],paper_score6[10];
	char usual_score1[10],usual_score2[10],usual_score3[10],usual_score4[10],usual_score5[10],usual_score6[10];
	char makeup_score1[10],makeup_score2[10],makeup_score3[10],makeup_score4[10],makeup_score5[10],makeup_score6[10];
	char score1[10],score2[10],score3[10],score4[10],score5[10],score6[10];
	char char_page[30],item[10];
	TCHAR szItem[3][10] = {TEXT("��һѧ��"), TEXT("�ڶ�ѧ��"), TEXT("����ѧ��")};
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
			//��ӿγ���Ͽ�����
			course_load(course_head);
			course_p=course_head->next;
			sum=course_head->next->num;
			course_p=course_p->next;
			for(i=0;i<sum;i++)
			{
				SendMessage(EDIT_course, CB_INSERTSTRING, (WPARAM)i, (LPARAM)(LPCTSTR)course_p->name);
				course_p=course_p->next;
			}
			//��Ӱ༶��Ͽ�����
			class_load(class_head);
			class_p=class_head->next;
			sum=class_head->next->num;
			class_p=class_p->next;
			for(i=0;i<sum;i++)
			{
				SendMessage(EDIT_grade, CB_INSERTSTRING, (WPARAM)i, (LPARAM)(LPCTSTR)class_p->name);
				class_p=class_p->next;
			}
			//���ѧ����Ϣ��Ͽ�����
			for(i=0;i<3;i++)
			{
				SendMessage(EDIT_term, CB_INSERTSTRING, (WPARAM)i, (LPARAM)(LPCTSTR)szItem[i]);
			}
				return TRUE;
		case WM_COMMAND:
			switch(LOWORD(wParam))
			{
			case BUTTON_a_score_enter_location:
				//��ȡ�γ���Ϣ������course
				score_load(score_head);
				index=SendMessage(EDIT_course, CB_GETCURSEL, 0, 0);
				if(index<0)
				{
					MessageBox(NULL,"��ѡ��¼��ѧ��","ERROR!",MB_OK);
					return FALSE;
				}
				course_p=course_head->next->next;
				sum=index;
				for(i=0;i<index;i++)
					course_p=course_p->next;
				strcpy(subject,course_p->name);
				//��ȡ�༶��Ϣ������grade
				class_load(class_head);
				index=SendMessage(EDIT_grade, CB_GETCURSEL, 0, 0);
				if(index<0)
				{
					MessageBox(NULL,"��ѡ��¼��ѧ��","ERROR!",MB_OK);
					return FALSE;
				}
				sum=index;
				class_p=class_head->next->next;
				for(i=0;i<index;i++)
					class_p=class_p->next;
				strcpy(grade,class_p->name);
				//��ȡѧ����Ϣ������term
				index=SendMessage(EDIT_term, CB_GETCURSEL, 0, 0);
				if(index<0)
				{
					MessageBox(NULL,"��ѡ��¼��ѧ��","ERROR!",MB_OK);
					return FALSE;
				}
				if(index==0)
					strcpy(term,"��һѧ��");
				else if(index==1)
					strcpy(term,"�ڶ�ѧ��");
				else if(index==2)
					strcpy(term,"����ѧ��");
				//���ݲ���
				//���ҽ�� -1.�ð༶������¼�룬-2.�İ༶��ѧ��������¼�� ��-3.�ð༶��ѧ�Ƹ�ѧ��������¼�룬0.����δ¼��
				score_load(score_head);
				page_head=score_head->next->next;
				find_enter=0;//��ʼ������״̬��Ϊ���ظ�
				while(page_head)
				{
					if(strcmp(page_head->grade,grade)==0)
					{
						find_enter=-1;//��¼��༶
					}
					if(find_enter==-1&&(strcmp(page_head->subject,subject)==0))
					{
						find_enter=-2;//��¼��ѧ��
					}
					if(find_enter==-2&&(strcmp(page_head->term,term)==0))
					{
						find_enter=-3;//��¼��ð༶��ѧ�Ƹ�ѧ������
						break;
					}
					find_enter=0;
					page_head=page_head->next;
				}
				if(find_enter==-3)
				{
					MessageBox(NULL,"��⵽�ð��ѧ�Ƹ�ѧ�ڳɼ���¼�룬����Ϊ�����©¼���ݣ�","��ʾ",MB_OK);
					//���ݼ�©��δ���
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
					MessageBox(NULL,"δ�ҵ��ð༶ѧ���κγɼ���¼��","ERROR!",MB_OK);
					return FALSE;
				}
				
				score_enter_ck=1;//�ѵ�����ض���
				score_enter_now=1;//��ǰҳ��
				score_display=0;//��һ����ʾ���Ϊ0
				if(sum>=6)
					print=6;//������������С��6�����һҳ��ʾ6������
				if(sum<6)
					print=sum;//����������С��6�����һҳ��ʾȫ��sum������
				student_p=student_head->next->next;//ָ���һҳ��һ����¼
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
				strcpy(char_page,"��");
				itoa(score_enter_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ����");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				
				break;
			case BUTTON_a_score_enter_prior:
				if(score_enter_ck!=1)
				{
					MessageBox(NULL,"���������ض�������ʾ��һҳ�ɼ���Ϣ��","��ʾ",MB_OK);
					break;
				}
				if(score_enter_now-1<=0)
				{
					MessageBox(NULL,"�Ѿ�����һҳ��","��ʾ",MB_OK);
					return FALSE;
				}
				else
					score_enter_now--;
				student_load(student_head);
				student_p=student_head->next;//ָ���һҳ��һ����¼
				for(j=0;j<(score_enter_now-1)*6;)
				{
					if(strcmp(student_p->grade,grade)==0)
							j++;
						student_p=student_p->next;
				}
				if(score_enter_now==page)//��������һҳ����������һҳ��¼����
					print=sum-(page-1)*6;
				else//���򣬼�¼����Ϊ6
					print=6;
				//��ձ༭������
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


				strcpy(char_page,"��");
				itoa(score_enter_now,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ����");
				itoa(page,item,10);
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_score_enter_next:
				if(score_enter_ck!=1)
				{
					MessageBox(NULL,"���������ض�������ʾ��һҳѧԺ��Ϣ��","��ʾ",MB_OK);
					break;
				}
				if(score_enter_now+1>page)//�����ǰҳ+1������ҳ������������
				{
					MessageBox(NULL,"�Ѿ������һҳ��","��ʾ",MB_OK);
					return FALSE;
				}
				else//������תҳ��
				{
					score_enter_now++;
				}
				
				student_load(student_head);
				student_p=student_head->next->next;//ָ���һҳ��һ����¼
				for(i=0;i<enter_6;i++)
					student_p=student_p->next;
				if(score_enter_now==page)//��������һҳ����������һҳ��¼����
					print=sum-(page-1)*6;
				else//���򣬼�¼����Ϊ6
					print=6;
				//��ձ༭������
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

				strcpy(char_page,"��");
				
				itoa(score_enter_now,item,10);

				strcat(char_page,item);
				
				strcat(char_page,"ҳ����");
				itoa(page,item,10);//ת������Ϊ�ַ���
				strcat(char_page,item);
				strcat(char_page,"ҳ");
				SetWindowText(EDIT_page,char_page);
				return TRUE;
				break;
			case BUTTON_a_score_enter_affirm:
				//��ȡ��ҳ��һ����������ɼ�
				//��ȡ��ѧ���ĸ�����Ϣ����ɼ����ݿ�
				student_load(student_head);
				student_p=student_head->next;
				for(i=0;i<enter_1;i++)
					student_p=student_p->next;
				//���ݲ���
				repetition=0;
				score_load(score_head);
				page_head=score_head->next;
				while(page_head)
				{
					if(strcmp(page_head->id,student_p->id)==0)
						if(strcmp(page_head->subject,subject)==0)
							if(strcmp(page_head->term,term)==0)
							{
								MessageBox(NULL,"�Ѵ��ڸ����ÿ�Ŀ��ѧ�ڳɼ��������ɼ����ݲ��ᱣ�棡","ERROR",MB_OK);
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
						MessageBox(NULL,"���԰ٷ����������ɼ���","����",MB_OK);
						SetWindowText(EDIT_paper_score1,"");
						return FALSE;
					}
					if((strcmp(paper_score1,"100")!=0)&&(strcmp(usual_score1,"00")<0||strcmp(usual_score1,"99")>0))
					{
						MessageBox(NULL,"���԰ٷ�������ƽʱ�ɼ���","����",MB_OK);
						SetWindowText(EDIT_usual_score1,"");
						return FALSE;
					}
					if((strcmp(makeup_score1,"100")!=0)&&(strcmp(makeup_score1,"-1")!=0)&&((strcmp(makeup_score1,"00")<0||strcmp(makeup_score1,"99")>0)))
					{
						MessageBox(NULL,"���԰ٷ������벹���ɼ���\n�޲�����¼��Ϊ��-1��","����",MB_OK);
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
				//��ȡ��ҳ��һ����������ɼ�
				//��ȡ��ѧ���ĸ�����Ϣ����ɼ����ݿ�
				student_load(student_head);
				student_p=student_head->next;
				for(i=0;i<enter_2;i++)
					student_p=student_p->next;
				//���ݲ���
				repetition=0;
				score_load(score_head);
				page_head=score_head->next;
				while(page_head)
				{
					if(strcmp(page_head->id,student_p->id)==0)
						if(strcmp(page_head->subject,subject)==0)
							if(strcmp(page_head->term,term)==0)
							{
								MessageBox(NULL,"�Ѵ��ڸ����ÿ�Ŀ��ѧ�ڳɼ��������ɼ����ݲ��ᱣ�棡","ERROR",MB_OK);
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
						MessageBox(NULL,"���԰ٷ����������ɼ���","����",MB_OK);
						SetWindowText(EDIT_paper_score2,"");
						return FALSE;
					}
					if((strcmp(paper_score2,"100")!=0)&&(strcmp(usual_score2,"00")<0||strcmp(usual_score2,"99")>0))
					{
						MessageBox(NULL,"���԰ٷ�������ƽʱ�ɼ���","����",MB_OK);
						SetWindowText(EDIT_usual_score2,"");
						return FALSE;
					}
					if((strcmp(makeup_score2,"100")!=0)&&(strcmp(makeup_score2,"-1")!=0)&&((strcmp(makeup_score2,"00")<0||strcmp(makeup_score2,"99")>0)))
					{
						MessageBox(NULL,"���԰ٷ������벹���ɼ���\n�޲�����¼��Ϊ��-1��","����",MB_OK);
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
				//��ȡ��ҳ��һ����������ɼ�
				//��ȡ��ѧ���ĸ�����Ϣ����ɼ����ݿ�
				student_load(student_head);
				student_p=student_head->next;
				for(i=0;i<enter_3;i++)
					student_p=student_p->next;
				//���ݲ���
				repetition=0;
				score_load(score_head);
				page_head=score_head->next;
				while(page_head)
				{
					if(strcmp(page_head->id,student_p->id)==0)
						if(strcmp(page_head->subject,subject)==0)
							if(strcmp(page_head->term,term)==0)
							{
								MessageBox(NULL,"�Ѵ��ڸ����ÿ�Ŀ��ѧ�ڳɼ��������ɼ����ݲ��ᱣ�棡","ERROR",MB_OK);
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
						MessageBox(NULL,"���԰ٷ����������ɼ���","����",MB_OK);
						SetWindowText(EDIT_paper_score3,"");
						return FALSE;
					}
					if((strcmp(paper_score3,"100")!=0)&&(strcmp(usual_score3,"00")<0||strcmp(usual_score3,"99")>0))
					{
						MessageBox(NULL,"���԰ٷ�������ƽʱ�ɼ���","����",MB_OK);
						SetWindowText(EDIT_usual_score3,"");
						return FALSE;
					}
					if((strcmp(makeup_score3,"100")!=0)&&(strcmp(makeup_score3,"-1")!=0)&&((strcmp(makeup_score3,"00")<0||strcmp(makeup_score3,"99")>0)))
					{
						MessageBox(NULL,"���԰ٷ������벹���ɼ���\n�޲�����¼��Ϊ��-1��","����",MB_OK);
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
				//��ȡ��ҳ��һ����������ɼ�
				//��ȡ��ѧ���ĸ�����Ϣ����ɼ����ݿ�
				student_load(student_head);
				student_p=student_head->next;
				for(i=0;i<enter_4;i++)
					student_p=student_p->next;
				//���ݲ���
				repetition=0;
				score_load(score_head);
				page_head=score_head->next;
				while(page_head)
				{
					if(strcmp(page_head->id,student_p->id)==0)
						if(strcmp(page_head->subject,subject)==0)
							if(strcmp(page_head->term,term)==0)
							{
								MessageBox(NULL,"�Ѵ��ڸ����ÿ�Ŀ��ѧ�ڳɼ��������ɼ����ݲ��ᱣ�棡","ERROR",MB_OK);
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
						MessageBox(NULL,"���԰ٷ����������ɼ���","����",MB_OK);
						SetWindowText(EDIT_paper_score4,"");
						return FALSE;
					}
					if((strcmp(paper_score4,"100")!=0)&&(strcmp(usual_score4,"00")<0||strcmp(usual_score4,"99")>0))
					{
						MessageBox(NULL,"���԰ٷ�������ƽʱ�ɼ���","����",MB_OK);
						SetWindowText(EDIT_usual_score4,"");
						return FALSE;
					}
					if((strcmp(makeup_score4,"100")!=0)&&(strcmp(makeup_score4,"-1")!=0)&&((strcmp(makeup_score4,"00")<0||strcmp(makeup_score4,"99")>0)))
					{
						MessageBox(NULL,"���԰ٷ������벹���ɼ���\n�޲�����¼��Ϊ��-1��","����",MB_OK);
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
				//��ȡ��ҳ��һ����������ɼ�
				//��ȡ��ѧ���ĸ�����Ϣ����ɼ����ݿ�
				student_load(student_head);
				student_p=student_head->next;
				for(i=0;i<enter_5;i++)
					student_p=student_p->next;
				//���ݲ���
				repetition=0;
				score_load(score_head);
				page_head=score_head->next;
				while(page_head)
				{
					if(strcmp(page_head->id,student_p->id)==0)
						if(strcmp(page_head->subject,subject)==0)
							if(strcmp(page_head->term,term)==0)
							{
								MessageBox(NULL,"�Ѵ��ڸ����ÿ�Ŀ��ѧ�ڳɼ��������ɼ����ݲ��ᱣ�棡","ERROR",MB_OK);
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
						MessageBox(NULL,"���԰ٷ����������ɼ���","����",MB_OK);
						SetWindowText(EDIT_paper_score5,"");
						return FALSE;
					}
					if((strcmp(paper_score5,"100")!=0)&&(strcmp(usual_score5,"00")<0||strcmp(usual_score5,"99")>0))
					{
						MessageBox(NULL,"���԰ٷ�������ƽʱ�ɼ���","����",MB_OK);
						SetWindowText(EDIT_usual_score5,"");
						return FALSE;
					}
					if((strcmp(makeup_score5,"100")!=0)&&(strcmp(makeup_score5,"-1")!=0)&&((strcmp(makeup_score5,"00")<0||strcmp(makeup_score5,"99")>0)))
					{
						MessageBox(NULL,"���԰ٷ������벹���ɼ���\n�޲�����¼��Ϊ��-1��","����",MB_OK);
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
				//��ȡ��ҳ��һ����������ɼ�
				//��ȡ��ѧ���ĸ�����Ϣ����ɼ����ݿ�
				student_load(student_head);
				student_p=student_head->next;
				for(i=0;i<enter_6;i++)
					student_p=student_p->next;
				//���ݲ���
				repetition=0;
				score_load(score_head);
				page_head=score_head->next;
				while(page_head)
				{
					if(strcmp(page_head->id,student_p->id)==0)
						if(strcmp(page_head->subject,subject)==0)
							if(strcmp(page_head->term,term)==0)
							{
								MessageBox(NULL,"�Ѵ��ڸ����ÿ�Ŀ��ѧ�ڳɼ��������ɼ����ݲ��ᱣ�棡","ERROR",MB_OK);
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
						MessageBox(NULL,"���԰ٷ����������ɼ���","����",MB_OK);
						SetWindowText(EDIT_paper_score6,"");
						return FALSE;
					}
					if((strcmp(paper_score6,"100")!=0)&&(strcmp(usual_score6,"00")<0||strcmp(usual_score6,"99")>0))
					{
						MessageBox(NULL,"���԰ٷ�������ƽʱ�ɼ���","����",MB_OK);
						SetWindowText(EDIT_usual_score6,"");
						return FALSE;
					}
					if((strcmp(makeup_score6,"100")!=0)&&(strcmp(makeup_score6,"-1")!=0)&&((strcmp(makeup_score6,"00")<0||strcmp(makeup_score6,"99")>0)))
					{
						MessageBox(NULL,"���԰ٷ������벹���ɼ���\n�޲�����¼��Ϊ��-1��","����",MB_OK);
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
			//��Ӱ༶��Ͽ�����
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
				//��ȡ�༶��Ϣ������grade
				class_load(class_head);
				index=SendMessage(EDIT_grade, CB_GETCURSEL, 0, 0);
				if(index<0)
				{
					MessageBox(NULL,"��ѡ��¼��ѧ��","ERROR!",MB_OK);
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
					MessageBox(NULL,"�ð༶�ɼ�Ϊ�գ�","����",MB_OK);
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
			//��Ӱ༶��Ͽ�����
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
				//��ȡ�༶��Ϣ������grade
				class_load(class_head);
				index=SendMessage(EDIT_grade, CB_GETCURSEL, 0, 0);
				if(index<0)
				{
					MessageBox(NULL,"��ѡ��¼��ѧ��","ERROR!",MB_OK);
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
					MessageBox(NULL,"�ð༶�ɼ�Ϊ�գ�","����",MB_OK);
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
void account_load(account_List account_head) //�����˻�����,˫������
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
void account_save(account_List account_head)//�����˻����ݵ�����
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

void college_load(college_List college_head) //����ѧԺ���ݣ�˫������
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
void college_save(college_List college_head)//����ѧԺ���ݵ�����
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
void profession_load(profession_List profession_head) //����רҵ����
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
void profession_save(profession_List profession_head)//����רҵ���ݵ�����
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
void course_load(course_List course_head) //����γ�����
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
void course_save(course_List course_head)//����γ����ݵ�����
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
void class_load(class_List class_head) //����༶����
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
void class_save(class_List class_head)//����༶���ݵ�����
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
void teacher_load(teacher_List teacher_head) //�����ʦ����
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
void teacher_save(teacher_List teacher_head)//�����ʦ���ݵ�����
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
void student_load(student_List student_head) //����ѧ������
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
void student_save(student_List student_head)//����ѧ�����ݵ�����
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
void score_load(score_List score_head) //����ɼ�����
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
void score_save(score_List score_head)//����༶���ݵ�����
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
int loading(char id[20],char password[20],account_List account_mine)//1.����Ա��2.��ʦ��3.ѧ����4.�˺Ŵ���5.�������,-1.��ʼ��-2.��ʼ��
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
                if(strcmp(p->identity,"����Ա")==0)
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
                if(strcmp(p_teacher->identity,"��ʦ")==0)
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
                if(strcmp(p_student->identity,"ѧ��")==0)
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

void initialize_college(college_List college_head)//��ʼ��ѧԺ����
{
    college_List p,prior,rear;
    rear=college_head;
    p=(college_List)malloc(sizeof(college_Lnode));
    prior=college_head;
    rear->next=p;
    //����������Ϊ1
    p->num=17;
    p->prior=prior;
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=1;
    p->num=1;
    strcpy(p->name,"����ʳƷѧԺ");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=2;
    p->num=2;
    strcpy(p->name,"���繤��ѧԺ");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=3;
    p->num=3;
    strcpy(p->name,"��ľ����ѧԺ");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=4;
    p->num=4;
    strcpy(p->name,"��Ϣ��ѧ�빤��ѧԺ");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=5;
    p->num=5;
    strcpy(p->name,"��ѧ�����뻷��ѧԺ");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=6;
    p->num=6;
    strcpy(p->name,"���﹤��ѧԺ");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=7;
    p->num=7;
    strcpy(p->name,"���Ͽ�ѧ�빤��ѧԺ");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=8;
    p->num=8;
    strcpy(p->name,"��������ѧԺ");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=9;
    p->num=9;
    strcpy(p->name,"����ѧԺ");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=10;
    p->num=10;
    strcpy(p->name,"����ó��ѧԺ");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=11;
    p->num=11;
    strcpy(p->name,"��ѧԺ");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=12;
    p->num=12;
    strcpy(p->name,"����ѧԺ");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=13;
    p->num=13;
    strcpy(p->name,"��ѧԺ");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=14;
    p->num=14;
    strcpy(p->name,"�����봫��ѧԺ");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=15;
    p->num=15;
    strcpy(p->name,"�������ѧԺ");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=16;
    p->num=16;
    strcpy(p->name,"���ʽ���ѧԺ");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(college_List)malloc(sizeof(college_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=17;
    p->num=17;
    strcpy(p->name,"��Ӣ����ѧԺ");
    rear=p;

    rear->next=NULL;
    college_save(college_head);
}
void initialize_profession(profession_List profession_head)//��ʼ��רҵ����
{
    profession_List p,prior,rear;
    rear=profession_head;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    prior=profession_head;
    rear->next=p;
    //����������Ϊ1
    p->num=76;
    p->prior=prior;
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=1;//ָ��רҵ����
    p->num=1;//�ƶ���¼����
    strcpy(p->name,"��ʳ����רҵ");
    strcpy(p->college,"����ʳƷѧԺ");
    p->college_id=1;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=2;
    p->num=2;
    strcpy(p->name,"ʳƷ��ѧ�빤��רҵ");
    strcpy(p->college,"����ʳƷѧԺ");
    p->college_id=1;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=3;
    p->num=3;
    strcpy(p->name,"ʳƷ�����밲ȫרҵ");
    strcpy(p->college,"����ʳƷѧԺ");
    p->college_id=1;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=4;
    p->num=4;
    strcpy(p->name,"ʳƷӪ����������רҵ");
    strcpy(p->college,"����ʳƷѧԺ");
    p->college_id=1;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=5;
    p->num=5;
    strcpy(p->name,"��е������켰���Զ���רҵ");
    strcpy(p->college,"���繤��ѧԺ");
    p->college_id=2;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=6;
    p->num=6;
    strcpy(p->name,"����װ������ƹ���רҵ");
    strcpy(p->college,"���繤��ѧԺ");
    p->college_id=2;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=7;
    p->num=7;
    strcpy(p->name,"���ϳ��ͼ����ƹ���רҵ");
    strcpy(p->college,"���繤��ѧԺ");
    p->college_id=2;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=8;
    p->num=8;
    strcpy(p->name,"��������רҵ");
    strcpy(p->college,"���繤��ѧԺ");
    p->college_id=2;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=9;
    p->num=9;
    strcpy(p->name,"��װ���̹���רҵ");
    strcpy(p->college,"���繤��ѧԺ");
    p->college_id=2;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=10;
    p->num=10;
    strcpy(p->name,"��ľ����");
    strcpy(p->college,"��ľ����ѧԺ");
    p->college_id=3;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=11;
    p->num=11;
    strcpy(p->name,"��·������ɺӹ���");
    strcpy(p->college,"��ľ����ѧԺ");
    p->college_id=3;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=12;
    p->num=12;
    strcpy(p->name,"������������ԴӦ�ù���");
    strcpy(p->college,"��ľ����ѧԺ");
    p->college_id=3;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=13;
    p->num=13;
    strcpy(p->name,"���̹���");
    strcpy(p->college,"��ľ����ѧԺ");
    p->college_id=3;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=14;
    p->num=14;
    strcpy(p->name,"����ѧרҵ");
    strcpy(p->college,"��ľ����ѧԺ");
    p->college_id=3;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=15;
    p->num=15;
    strcpy(p->name,"��ͨ����רҵ");
    strcpy(p->college,"��ľ����ѧԺ");
    p->college_id=3;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=16;
    p->num=16;
    strcpy(p->name,"����������רҵ");
    strcpy(p->college,"��Ϣ��ѧ�빤��ѧԺ");
    p->college_id=4;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=17;
    p->num=17;
    strcpy(p->name,"�������ѧ�뼼��רҵ");
    strcpy(p->college,"��Ϣ��ѧ�빤��ѧԺ");
    p->college_id=4;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=18;
    p->num=18;
    strcpy(p->name,"������Ϣ����רҵ");
    strcpy(p->college,"��Ϣ��ѧ�빤��ѧԺ");
    p->college_id=4;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=19;
    p->num=19;
    strcpy(p->name,"�ռ���Ϣ�����ּ���");
    strcpy(p->college,"��Ϣ��ѧ�빤��ѧԺ");
    p->college_id=4;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=20;
    p->num=20;
    strcpy(p->name,"�������רҵ");
    strcpy(p->college,"��Ϣ��ѧ�빤��ѧԺ");
    p->college_id=4;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=21;
    p->num=21;
    strcpy(p->name,"ͨ�Ź���רҵ");
    strcpy(p->college,"��Ϣ��ѧ�빤��ѧԺ");
    p->college_id=4;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=22;
    p->num=22;
    strcpy(p->name,"��ѧ�����빤��רҵ");
    strcpy(p->college,"��ѧ�����뻷��ѧԺ");
    p->college_id=5;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=23;
    p->num=23;
    strcpy(p->name,"Ӧ�û�ѧרҵ");
    strcpy(p->college,"��ѧ�����뻷��ѧԺ");
    p->college_id=5;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=24;
    p->num=24;
    strcpy(p->name,"��������רҵ");
    strcpy(p->college,"��ѧ�����뻷��ѧԺ");
    p->college_id=5;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=25;
    p->num=25;
    strcpy(p->name,"��ѧרҵ");
    strcpy(p->college,"��ѧ�����뻷��ѧԺ");
    p->college_id=5;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=26;
    p->num=26;
    strcpy(p->name,"���﹤��רҵ");
    strcpy(p->college,"���﹤��ѧԺ");
    p->college_id=6;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=27;
    p->num=27;
    strcpy(p->name,"�����ѧרҵ");
    strcpy(p->college,"���﹤��ѧԺ");
    p->college_id=6;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=28;
    p->num=28;
    strcpy(p->name,"���＼��רҵ");
    strcpy(p->college,"���﹤��ѧԺ");
    p->college_id=6;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=29;
    p->num=29;
    strcpy(p->name,"��ҩ����רҵ");
    strcpy(p->college,"���﹤��ѧԺ");
    p->college_id=6;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=30;
    p->num=30;
    strcpy(p->name,"���Ͽ�ѧ�빤��רҵ");
    strcpy(p->college,"���Ͽ�ѧ�빤��ѧԺ");
    p->college_id=7;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=31;
    p->num=31;
    strcpy(p->name,"�߷��Ӳ����빤��רҵ");
    strcpy(p->college,"���Ͽ�ѧ�빤��ѧԺ");
    p->college_id=7;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=32;
    p->num=32;
    strcpy(p->name,"�޻��ǽ������Ϲ���רҵ");
    strcpy(p->college,"���Ͽ�ѧ�빤��ѧԺ");
    p->college_id=7;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=33;
    p->num=33;
    strcpy(p->name,"�Զ���");
    strcpy(p->college,"��������ѧԺ");
    p->college_id=8;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=34;
    p->num=34;
    strcpy(p->name,"�������̼����Զ���");
    strcpy(p->college,"��������ѧԺ");
    p->college_id=8;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=35;
    p->num=35;
    strcpy(p->name,"��ؼ���������");
    strcpy(p->college,"��������ѧԺ");
    p->college_id=8;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=36;
    p->num=36;
    strcpy(p->name,"�����ͨ�ź������");
    strcpy(p->college,"��������ѧԺ");
    p->college_id=8;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=37;
    p->num=37;
    strcpy(p->name,"��������רҵ");
    strcpy(p->college,"����ѧԺ");
    p->college_id=9;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=38;
    p->num=38;
    strcpy(p->name,"��������רҵ");
    strcpy(p->college,"����ѧԺ");
    p->college_id=9;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=39;
    p->num=39;
    strcpy(p->name,"���̹���רҵ");
    strcpy(p->college,"����ѧԺ");
    p->college_id=9;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=40;
    p->num=40;
    strcpy(p->name,"���ι���רҵ");
    strcpy(p->college,"����ѧԺ");
    p->college_id=9;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=41;
    p->num=41;
    strcpy(p->name,"�������רҵ");
    strcpy(p->college,"����ѧԺ");
    p->college_id=9;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=42;
    p->num=42;
    strcpy(p->name,"����ѧרҵ");
    strcpy(p->college,"����ó��ѧԺ");
    p->college_id=10;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=43;
    p->num=43;
    strcpy(p->name,"���ʾ�����ó��רҵ");
    strcpy(p->college,"����ó��ѧԺ");
    p->college_id=10;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=44;
    p->num=44;
    strcpy(p->name,"����ѧרҵ");
    strcpy(p->college,"����ó��ѧԺ");
    p->college_id=10;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=45;
    p->num=45;
    strcpy(p->name,"����ѧרҵ");
    strcpy(p->college,"����ó��ѧԺ");
    p->college_id=10;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=46;
    p->num=46;
    strcpy(p->name,"��ѧ��Ӧ����ѧרҵ");
    strcpy(p->college,"��ѧԺ");
    p->college_id=11;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=47;
    p->num=47;
    strcpy(p->name,"��Ϣ������ѧרҵ");
    strcpy(p->college,"��ѧԺ");
    p->college_id=11;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=48;
    p->num=48;
    strcpy(p->name,"Ӧ��ͳ��ѧרҵ");
    strcpy(p->college,"��ѧԺ");
    p->college_id=11;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=49;
    p->num=49;
    strcpy(p->name,"Ӧ������ѧרҵ");
    strcpy(p->college,"��ѧԺ");
    p->college_id=11;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=50;
    p->num=50;
    strcpy(p->name,"Ӣ��רҵ");
    strcpy(p->college,"����ѧԺ");
    p->college_id=12;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=51;
    p->num=51;
    strcpy(p->name,"����רҵ");
    strcpy(p->college,"����ѧԺ");
    p->college_id=12;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=52;
    p->num=52;
    strcpy(p->name,"��ѧ");
    strcpy(p->college,"��ѧԺ");
    p->college_id=13;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=53;
    p->num=53;
    strcpy(p->name,"���ѧרҵ");
    strcpy(p->college,"�����봫��ѧԺ");
    p->college_id=14;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=54;
    p->num=54;
    strcpy(p->name,"�㲥����ѧרҵ");
    strcpy(p->college,"�����봫��ѧԺ");
    p->college_id=14;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=55;
    p->num=55;
    strcpy(p->name,"��������ý��רҵ");
    strcpy(p->college,"�����봫��ѧԺ");
    p->college_id=14;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=56;
    p->num=56;
    strcpy(p->name,"��������������רҵ");
    strcpy(p->college,"�����봫��ѧԺ");
    p->college_id=14;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=57;
    p->num=57;
    strcpy(p->name,"��Ʒ���רҵ");
    strcpy(p->college,"�������ѧԺ");
    p->college_id=15;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=58;
    p->num=58;
    strcpy(p->name,"�Ӿ��������רҵ");
    strcpy(p->college,"�������ѧԺ");
    p->college_id=15;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=59;
    p->num=59;
    strcpy(p->name,"�������רҵ");
    strcpy(p->college,"�������ѧԺ");
    p->college_id=15;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=60;
    p->num=60;
    strcpy(p->name,"����ý������רҵ");
    strcpy(p->college,"�������ѧԺ");
    p->college_id=15;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=61;
    p->num=61;
    strcpy(p->name,"����");
    strcpy(p->college,"�������ѧԺ");
    p->college_id=15;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=62;
    p->num=62;
    strcpy(p->name,"ʳƷ��ѧ�빤��רҵ");
    strcpy(p->college,"���ʽ���ѧԺ");
    p->college_id=16;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=63;
    p->num=63;
    strcpy(p->name,"���＼��רҵ");
    strcpy(p->college,"���ʽ���ѧԺ");
    p->college_id=16;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=64;
    p->num=64;
    strcpy(p->name,"������Դ����רҵ");
    strcpy(p->college,"���ʽ���ѧԺ");
    p->college_id=16;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=65;
    p->num=65;
    strcpy(p->name,"�г�Ӫ��רҵ");
    strcpy(p->college,"���ʽ���ѧԺ");
    p->college_id=16;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=66;
    p->num=66;
    strcpy(p->name,"���ѧרҵ");
    strcpy(p->college,"���ʽ���ѧԺ");
    p->college_id=16;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=67;
    p->num=67;
    strcpy(p->name,"ʳƷӪ������רҵ");
    strcpy(p->college,"���ʽ���ѧԺ");
    p->college_id=16;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=68;
    p->num=68;
    strcpy(p->name,"��е�������Զ���רҵ");
    strcpy(p->college,"��Ӣ����ѧԺ");
    p->college_id=17;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=69;
    p->num=69;
    strcpy(p->name,"����Ӫ�������רҵ");
    strcpy(p->college,"��Ӣ����ѧԺ");
    p->college_id=17;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=70;
    p->num=70;
    strcpy(p->name,"�������רҵ");
    strcpy(p->college,"��Ӣ����ѧԺ");
    p->college_id=17;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=71;
    p->num=71;
    strcpy(p->name,"���רҵ");
    strcpy(p->college,"��Ӣ����ѧԺ");
    p->college_id=17;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=72;
    p->num=72;
    strcpy(p->name,"֤ȯ���ڻ�רҵ");
    strcpy(p->college,"��Ӣ����ѧԺ");
    p->college_id=17;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=73;
    p->num=73;
    strcpy(p->name,"�������רҵ");
    strcpy(p->college,"��Ӣ����ѧԺ");
    p->college_id=17;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=74;
    p->num=74;
    strcpy(p->name,"����������רҵ");
    strcpy(p->college,"��Ӣ����ѧԺ");
    p->college_id=17;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=75;
    p->num=75;
    strcpy(p->name,"�������רҵ");
    strcpy(p->college,"��Ӣ����ѧԺ");
    p->college_id=17;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(profession_List)malloc(sizeof(profession_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=76;
    p->num=76;
    strcpy(p->name,"��Ϣ��ȫ�����רҵ");
    strcpy(p->college,"��Ӣ����ѧԺ");
    p->college_id=17;//ָ������ѧԺ����
    rear=p;

    rear->next=NULL;
    profession_save(profession_head);
}
void initialize_course(course_List course_head)//��ʼ���γ�����
{
    course_List p,prior,rear;
    rear=course_head;
    p=(course_List)malloc(sizeof(course_Lnode));
    prior=course_head;
    rear->next=p;
    //����������Ϊ1
    p->num=25;
    p->prior=prior;
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=1;
    p->num=1;
    strcpy(p->name,"��ѧӢ��");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=2;
    p->num=2;
    strcpy(p->name,"�ߵ���ѧ");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=3;
    p->num=3;
    strcpy(p->name,"˼������뷨������");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=4;
    p->num=4;
    strcpy(p->name,"ְҵ��չ�������ҵָ��");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=5;
    p->num=5;
    strcpy(p->name,"��ʽ������");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=6;
    p->num=6;
    strcpy(p->name,"��ѧ����");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=7;
    p->num=7;
    strcpy(p->name,"���Դ���");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=8;
    p->num=8;
    strcpy(p->name,"������ƻ���");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=9;
    p->num=9;
    strcpy(p->name,"������������ͳ��");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=10;
    p->num=10;
    strcpy(p->name,"���˼�������ԭ�����");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=11;
    p->num=11;
    strcpy(p->name,"ë��˼����й���ɫ�������������ϵ����");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=12;
    p->num=12;
    strcpy(p->name,"���������");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=13;
    p->num=13;
    strcpy(p->name,"���ݽṹ���㷨");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=14;
    p->num=14;
    strcpy(p->name,"���ǵ�����λϵͳ");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=15;
    p->num=15;
    strcpy(p->name,"�����ͼ��ѧ");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=16;
    p->num=16;
    strcpy(p->name," ��ͼѧ");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=17;
    p->num=17;
    strcpy(p->name,"ң��Ӱ������Ӧ��");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=18;
    p->num=18;
    strcpy(p->name,"GIS������Ӧ��");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=19;
    p->num=19;
    strcpy(p->name,"�������");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=20;
    p->num=20;
    strcpy(p->name,"�������ּ���");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=21;
    p->num=21;
    strcpy(p->name,"��������������");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=22;
    p->num=22;
    strcpy(p->name,"����ѧ����");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=23;
    p->num=23;
    strcpy(p->name," C#��̺�.NET���");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=24;
    p->num=24;
    strcpy(p->name," ��������������");
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(course_List)malloc(sizeof(course_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=25;
    p->num=25;
    strcpy(p->name,"���ּ���");
    rear=p;

    rear->next=NULL;
    course_save(course_head);
}
void initialize_class(class_List class_head)//��ʼ��רҵ����
{
    class_List p,prior,rear;
    rear=class_head;
    p=(class_List)malloc(sizeof(class_Lnode));
    prior=class_head;
    rear->next=p;
    //����������Ϊ1
    p->num=76;
    p->prior=prior;
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=1;//ָ��רҵ����
    p->num=1;//�ƶ���¼����
    strcpy(p->profession,"��ʳ����רҵ");
    strcpy(p->college,"����ʳƷѧԺ");
    strcpy(p->name,"��ʳ����רҵ1601");
    p->college_id=1;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=2;
    p->num=2;
    strcpy(p->profession,"ʳƷ��ѧ�빤��רҵ");
    strcpy(p->college,"����ʳƷѧԺ");
    strcpy(p->name,"ʳƷ��ѧ�빤��רҵ1601");
    p->college_id=1;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=3;
    p->num=3;
    strcpy(p->profession,"ʳƷ�����밲ȫרҵ");
    strcpy(p->college,"����ʳƷѧԺ");
    strcpy(p->name,"ʳƷ�����밲ȫרҵ1601");
    p->college_id=1;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=4;
    p->num=4;
    strcpy(p->profession,"ʳƷӪ����������רҵ");
    strcpy(p->college,"����ʳƷѧԺ");
    strcpy(p->name,"ʳƷӪ����������רҵ1601");
    p->college_id=1;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=5;
    p->num=5;
    strcpy(p->profession,"��е������켰���Զ���רҵ");
    strcpy(p->college,"���繤��ѧԺ");
    strcpy(p->name,"��е������켰���Զ���רҵ1601");
    p->college_id=2;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=6;
    p->num=6;
    strcpy(p->profession,"����װ������ƹ���רҵ");
    strcpy(p->college,"���繤��ѧԺ");
    strcpy(p->name,"����װ������ƹ���רҵ1601");
    p->college_id=2;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=7;
    p->num=7;
    strcpy(p->profession,"���ϳ��ͼ����ƹ���רҵ");
    strcpy(p->college,"���繤��ѧԺ");
    strcpy(p->name,"���ϳ��ͼ����ƹ���רҵ1601");
    p->college_id=2;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=8;
    p->num=8;
    strcpy(p->profession,"��������רҵ");
    strcpy(p->college,"���繤��ѧԺ");
    strcpy(p->name,"��������רҵ1601");
    p->college_id=2;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=9;
    p->num=9;
    strcpy(p->profession,"��װ���̹���רҵ");
    strcpy(p->college,"���繤��ѧԺ");
    strcpy(p->name,"��װ���̹���רҵ1601");
    p->college_id=2;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=10;
    p->num=10;
    strcpy(p->profession,"��ľ����");
    strcpy(p->college,"��ľ����ѧԺ");
    strcpy(p->name,"��ľ����1601");
    p->college_id=3;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=11;
    p->num=11;
    strcpy(p->profession,"��·������ɺӹ���");
    strcpy(p->college,"��ľ����ѧԺ");
    strcpy(p->name,"��·������ɺӹ���1601");
    p->college_id=3;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=12;
    p->num=12;
    strcpy(p->profession,"������������ԴӦ�ù���");
    strcpy(p->college,"��ľ����ѧԺ");
    strcpy(p->name,"������������ԴӦ�ù���1601");
    p->college_id=3;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=13;
    p->num=13;
    strcpy(p->profession,"���̹���");
    strcpy(p->college,"��ľ����ѧԺ");
    strcpy(p->name,"���̹���1601");
    p->college_id=3;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=14;
    p->num=14;
    strcpy(p->profession,"����ѧרҵ");
    strcpy(p->college,"��ľ����ѧԺ");
    strcpy(p->name,"����ѧרҵ1601");
    p->college_id=3;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=15;
    p->num=15;
    strcpy(p->profession,"��ͨ����רҵ");
    strcpy(p->college,"��ľ����ѧԺ");
    strcpy(p->name,"��ͨ����רҵ1601");
    p->college_id=3;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=16;
    p->num=16;
    strcpy(p->profession,"����������רҵ");
    strcpy(p->college,"��Ϣ��ѧ�빤��ѧԺ");
    strcpy(p->name,"����������רҵ1601");
    p->college_id=4;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=17;
    p->num=17;
    strcpy(p->profession,"�������ѧ�뼼��רҵ");
    strcpy(p->college,"��Ϣ��ѧ�빤��ѧԺ");
    strcpy(p->name,"�������ѧ�뼼��רҵ1601");
    p->college_id=4;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=18;
    p->num=18;
    strcpy(p->profession,"������Ϣ����רҵ");
    strcpy(p->college,"��Ϣ��ѧ�빤��ѧԺ");
    strcpy(p->name,"������Ϣ����רҵ1601");
    p->college_id=4;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=19;
    p->num=19;
    strcpy(p->profession,"�ռ���Ϣ�����ּ���");
    strcpy(p->college,"��Ϣ��ѧ�빤��ѧԺ");
    strcpy(p->name,"�ռ���Ϣ�����ּ���1601");
    p->college_id=4;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=20;
    p->num=20;
    strcpy(p->profession,"�������רҵ");
    strcpy(p->college,"��Ϣ��ѧ�빤��ѧԺ");
    strcpy(p->name,"�������רҵ1601");
    p->college_id=4;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=21;
    p->num=21;
    strcpy(p->profession,"ͨ�Ź���רҵ");
    strcpy(p->college,"��Ϣ��ѧ�빤��ѧԺ");
    strcpy(p->name,"ͨ�Ź���רҵ1601");
    p->college_id=4;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=22;
    p->num=22;
    strcpy(p->profession,"��ѧ�����빤��רҵ");
    strcpy(p->college,"��ѧ�����뻷��ѧԺ");
    strcpy(p->name,"��ѧ�����빤��רҵ1601");
    p->college_id=5;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=23;
    p->num=23;
    strcpy(p->profession,"Ӧ�û�ѧרҵ");
    strcpy(p->college,"��ѧ�����뻷��ѧԺ");
    strcpy(p->name,"Ӧ�û�ѧרҵ1601");
    p->college_id=5;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=24;
    p->num=24;
    strcpy(p->profession,"��������רҵ");
    strcpy(p->college,"��ѧ�����뻷��ѧԺ");
    strcpy(p->name,"��������רҵ1601");
    p->college_id=5;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=25;
    p->num=25;
    strcpy(p->profession,"��ѧרҵ");
    strcpy(p->college,"��ѧ�����뻷��ѧԺ");
    strcpy(p->name,"��ѧרҵ1601");
    p->college_id=5;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=26;
    p->num=26;
    strcpy(p->profession,"���﹤��רҵ");
    strcpy(p->college,"���﹤��ѧԺ");
    strcpy(p->name,"���﹤��רҵ1601");
    p->college_id=6;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=27;
    p->num=27;
    strcpy(p->profession,"�����ѧרҵ");
    strcpy(p->college,"���﹤��ѧԺ");
    strcpy(p->name,"�����ѧרҵ1601");
    p->college_id=6;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=28;
    p->num=28;
    strcpy(p->profession,"���＼��רҵ");
    strcpy(p->college,"���﹤��ѧԺ");
    strcpy(p->name,"���＼��רҵ1601");
    p->college_id=6;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=29;
    p->num=29;
    strcpy(p->profession,"��ҩ����רҵ");
    strcpy(p->college,"���﹤��ѧԺ");
    strcpy(p->name,"��ҩ����רҵ1601");
    p->college_id=6;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=30;
    p->num=30;
    strcpy(p->profession,"���Ͽ�ѧ�빤��רҵ");
    strcpy(p->college,"���Ͽ�ѧ�빤��ѧԺ");
    strcpy(p->name,"���Ͽ�ѧ�빤��רҵ1601");
    p->college_id=7;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=31;
    p->num=31;
    strcpy(p->profession,"�߷��Ӳ����빤��רҵ");
    strcpy(p->college,"���Ͽ�ѧ�빤��ѧԺ");
    strcpy(p->name,"�߷��Ӳ����빤��רҵ1601");
    p->college_id=7;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=32;
    p->num=32;
    strcpy(p->profession,"�޻��ǽ������Ϲ���רҵ");
    strcpy(p->college,"���Ͽ�ѧ�빤��ѧԺ");
    strcpy(p->name,"�޻��ǽ������Ϲ���רҵ1601");
    p->college_id=7;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=33;
    p->num=33;
    strcpy(p->profession,"�Զ���");
    strcpy(p->college,"��������ѧԺ");
    strcpy(p->name,"�Զ���1601");
    p->college_id=8;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=34;
    p->num=34;
    strcpy(p->profession,"�������̼����Զ���");
    strcpy(p->college,"��������ѧԺ");
    strcpy(p->name,"�������̼����Զ���1601");
    p->college_id=8;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=35;
    p->num=35;
    strcpy(p->profession,"��ؼ���������");
    strcpy(p->college,"��������ѧԺ");
    strcpy(p->name,"��ؼ���������1601");
    p->college_id=8;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=36;
    p->num=36;
    strcpy(p->profession,"�����ͨ�ź������");
    strcpy(p->college,"��������ѧԺ");
    strcpy(p->name,"�����ͨ�ź������1601");
    p->college_id=8;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=37;
    p->num=37;
    strcpy(p->profession,"��������רҵ");
    strcpy(p->college,"����ѧԺ");
    strcpy(p->name,"��������רҵ1601");
    p->college_id=9;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=38;
    p->num=38;
    strcpy(p->profession,"��������רҵ");
    strcpy(p->college,"����ѧԺ");
    strcpy(p->name,"��������רҵ1601");
    p->college_id=9;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=39;
    p->num=39;
    strcpy(p->profession,"���̹���רҵ");
    strcpy(p->college,"����ѧԺ");
    strcpy(p->name,"���̹���רҵ1601");
    p->college_id=9;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=40;
    p->num=40;
    strcpy(p->profession,"���ι���רҵ");
    strcpy(p->college,"����ѧԺ");
    strcpy(p->name,"���ι���רҵ1601");
    p->college_id=9;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=41;
    p->num=41;
    strcpy(p->profession,"�������רҵ");
    strcpy(p->college,"����ѧԺ");
    strcpy(p->name,"�������רҵ1601");
    p->college_id=9;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=42;
    p->num=42;
    strcpy(p->profession,"����ѧרҵ");
    strcpy(p->college,"����ó��ѧԺ");
    strcpy(p->name,"����ѧרҵ1601");
    p->college_id=10;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=43;
    p->num=43;
    strcpy(p->profession,"���ʾ�����ó��רҵ");
    strcpy(p->college,"����ó��ѧԺ");
    strcpy(p->name,"���ʾ�����ó��רҵ1601");
    p->college_id=10;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=44;
    p->num=44;
    strcpy(p->profession,"����ѧרҵ");
    strcpy(p->college,"����ó��ѧԺ");
    strcpy(p->name,"����ѧרҵ1601");
    p->college_id=10;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=45;
    p->num=45;
    strcpy(p->profession,"����ѧרҵ");
    strcpy(p->college,"����ó��ѧԺ");
    strcpy(p->name,"����ѧרҵ1601");
    p->college_id=10;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=46;
    p->num=46;
    strcpy(p->profession,"��ѧ��Ӧ����ѧרҵ");
    strcpy(p->college,"��ѧԺ");
    strcpy(p->name,"��ѧ��Ӧ����ѧרҵ1601");
    p->college_id=11;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=47;
    p->num=47;
    strcpy(p->profession,"��Ϣ������ѧרҵ");
    strcpy(p->college,"��ѧԺ");
    strcpy(p->name,"��Ϣ������ѧרҵ1601");
    p->college_id=11;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=48;
    p->num=48;
    strcpy(p->profession,"Ӧ��ͳ��ѧרҵ");
    strcpy(p->college,"��ѧԺ");
    strcpy(p->name,"Ӧ��ͳ��ѧרҵ1601");
    p->college_id=11;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=49;
    p->num=49;
    strcpy(p->profession,"Ӧ������ѧרҵ");
    strcpy(p->college,"��ѧԺ");
    strcpy(p->name,"Ӧ������ѧרҵ1601");
    p->college_id=11;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=50;
    p->num=50;
    strcpy(p->profession,"Ӣ��רҵ");
    strcpy(p->college,"����ѧԺ");
    strcpy(p->name,"Ӣ��רҵ1601");
    p->college_id=12;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=51;
    p->num=51;
    strcpy(p->profession,"����רҵ");
    strcpy(p->college,"����ѧԺ");
    strcpy(p->name,"����רҵ1601");
    p->college_id=12;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=52;
    p->num=52;
    strcpy(p->profession,"��ѧ");
    strcpy(p->college,"��ѧԺ");
    strcpy(p->name,"��ѧ1601");
    p->college_id=13;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=53;
    p->num=53;
    strcpy(p->profession,"���ѧרҵ");
    strcpy(p->college,"�����봫��ѧԺ");
    strcpy(p->name,"���ѧרҵ1601");
    p->college_id=14;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=54;
    p->num=54;
    strcpy(p->profession,"�㲥����ѧרҵ");
    strcpy(p->college,"�����봫��ѧԺ");
    strcpy(p->name,"�㲥����ѧרҵ1601");
    p->college_id=14;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=55;
    p->num=55;
    strcpy(p->profession,"��������ý��רҵ");
    strcpy(p->college,"�����봫��ѧԺ");
    strcpy(p->name,"��������ý��רҵ1601");
    p->college_id=14;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=56;
    p->num=56;
    strcpy(p->profession,"��������������רҵ");
    strcpy(p->college,"�����봫��ѧԺ");
    strcpy(p->name,"��������������רҵ1601");
    p->college_id=14;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=57;
    p->num=57;
    strcpy(p->profession,"��Ʒ���רҵ");
    strcpy(p->college,"�������ѧԺ");
    strcpy(p->name,"��Ʒ���רҵ1601");
    p->college_id=15;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=58;
    p->num=58;
    strcpy(p->profession,"�Ӿ��������רҵ");
    strcpy(p->college,"�������ѧԺ");
    strcpy(p->name,"�Ӿ��������רҵ1601");
    p->college_id=15;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=59;
    p->num=59;
    strcpy(p->profession,"�������רҵ");
    strcpy(p->college,"�������ѧԺ");
    strcpy(p->name,"�������רҵ1601");
    p->college_id=15;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=60;
    p->num=60;
    strcpy(p->profession,"����ý������רҵ");
    strcpy(p->college,"�������ѧԺ");
    strcpy(p->name,"����ý������רҵ1601");
    p->college_id=15;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=61;
    p->num=61;
    strcpy(p->profession,"����");
    strcpy(p->college,"�������ѧԺ");
    strcpy(p->name,"����1601");
    p->college_id=15;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=62;
    p->num=62;
    strcpy(p->profession,"ʳƷ��ѧ�빤��רҵ");
    strcpy(p->college,"���ʽ���ѧԺ");
    strcpy(p->name,"ʳƷ��ѧ�빤��רҵ1601");
    p->college_id=16;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=63;
    p->num=63;
    strcpy(p->profession,"���＼��רҵ");
    strcpy(p->college,"���ʽ���ѧԺ");
    strcpy(p->name,"���＼��רҵ1601");
    p->college_id=16;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=64;
    p->num=64;
    strcpy(p->profession,"������Դ����רҵ");
    strcpy(p->college,"���ʽ���ѧԺ");
    strcpy(p->name,"������Դ����רҵ1601");
    p->college_id=16;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=65;
    p->num=65;
    strcpy(p->profession,"�г�Ӫ��רҵ");
    strcpy(p->college,"���ʽ���ѧԺ");
    strcpy(p->name,"�г�Ӫ��רҵ1601");
    p->college_id=16;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=66;
    p->num=66;
    strcpy(p->profession,"���ѧרҵ");
    strcpy(p->college,"���ʽ���ѧԺ");
    strcpy(p->name,"���ѧרҵ1601");
    p->college_id=16;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=67;
    p->num=67;
    strcpy(p->profession,"ʳƷӪ������רҵ");
    strcpy(p->college,"���ʽ���ѧԺ");
    strcpy(p->name,"ʳƷӪ������רҵ1601");
    p->college_id=16;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=68;
    p->num=68;
    strcpy(p->profession,"��е�������Զ���רҵ");
    strcpy(p->college,"��Ӣ����ѧԺ");
    strcpy(p->name,"��е�������Զ���רҵ1601");
    p->college_id=17;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=69;
    p->num=69;
    strcpy(p->profession,"����Ӫ�������רҵ");
    strcpy(p->college,"��Ӣ����ѧԺ");
    strcpy(p->name,"����Ӫ�������רҵ1601");
    p->college_id=17;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=70;
    p->num=70;
    strcpy(p->profession,"�������רҵ");
    strcpy(p->college,"��Ӣ����ѧԺ");
    strcpy(p->name,"�������רҵ1601");
    p->college_id=17;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=71;
    p->num=71;
    strcpy(p->profession,"���רҵ");
    strcpy(p->college,"��Ӣ����ѧԺ");
    strcpy(p->name,"���רҵ1601");
    p->college_id=17;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=72;
    p->num=72;
    strcpy(p->profession,"֤ȯ���ڻ�רҵ");
    strcpy(p->college,"��Ӣ����ѧԺ");
    strcpy(p->name,"֤ȯ���ڻ�רҵ1601");
    p->college_id=17;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=73;
    p->num=73;
    strcpy(p->profession,"�������רҵ");
    strcpy(p->college,"��Ӣ����ѧԺ");
    strcpy(p->name,"�������רҵ1601");
    p->college_id=17;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=74;
    p->num=74;
    strcpy(p->profession,"����������רҵ");
    strcpy(p->college,"��Ӣ����ѧԺ");
    strcpy(p->name,"����������רҵ1601");
    p->college_id=17;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=75;
    p->num=75;
    strcpy(p->profession,"�������רҵ");
    strcpy(p->college,"��Ӣ����ѧԺ");
    strcpy(p->name,"�������רҵ1601");
    p->college_id=17;//ָ������ѧԺ����
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(class_List)malloc(sizeof(class_Lnode));
    rear->next=p;
    p->prior=prior;
    p->id=76;
    p->num=76;
    strcpy(p->profession,"��Ϣ��ȫ�����רҵ");
    strcpy(p->college,"��Ӣ����ѧԺ");
    strcpy(p->name,"��Ϣ��ȫ�����רҵ1601");
    p->college_id=17;//ָ������ѧԺ����
    rear=p;

    rear->next=NULL;
    class_save(class_head);
}
void initialize(account_List account_head)//��ʼ������Ա����
{
    account_List p,rear;
    account_head=(account_List)malloc(sizeof(account_Lnode));
    p=(account_List)malloc(sizeof(account_Lnode));
    account_head->next=p;
	p->prior=account_head;
    //����������Ϊ1
    p->num=1;
    //�����ڴ棬����һ������Ա����
    p=(account_List)malloc(sizeof(account_Lnode));
    account_head->next->next=p;
	p->prior=account_head->next;
	p->num=1;
    strcpy(p->id,"admin");
    strcpy(p->password,"admin");
    strcpy(p->name,"������");
    strcpy(p->sex,"��");
    strcpy(p->identity,"����Ա");
    strcpy(p->nation,"����");
    strcpy(p->face,"���ȶ�Ա");
    strcpy(p->birth,"1997��10��29��");
    strcpy(p->time,"2016��09��");
    strcpy(p->college,"��Ϣ��ѧ�빤��ѧԺ");
    p->collegeid=4;
    strcpy(p->profession,"�߼�����Ա");
	strcpy(p->grade,"��ʦ");
    p->professionid=1;
	rear=p;
	p->next=NULL;

	identity=-1;
    account_save(account_head);
}
void initialize_teacher(teacher_List teacher_head)//��ʼ��
{
    teacher_List p;
    teacher_head=(teacher_List)malloc(sizeof(teacher_Lnode));
    p=(teacher_List)malloc(sizeof(teacher_Lnode));
    teacher_head->next=p;
    //����������Ϊ1
    p->num=1;
    //�����ڴ棬����һ������
    p=(teacher_List)malloc(sizeof(teacher_Lnode));
    teacher_head->next->next=p;
    strcpy(p->id,"teacher");
    strcpy(p->password,"teacher");
    strcpy(p->name,"������");
    strcpy(p->sex,"��");
    strcpy(p->identity,"��ʦ");
    strcpy(p->nation,"����");
    strcpy(p->face,"��Ա");
    strcpy(p->birth,"1997��10��29��");
    strcpy(p->time,"2016��09��");
    strcpy(p->college,"��Ϣ��ѧ�빤��ѧԺ");
    p->collegeid=4;
    strcpy(p->profession,"ְҵ��չ�������ҵָ��");
    strcpy(p->grade,"��ʦ");
    p->professionid=4;
    p->next=NULL;
    teacher_save(teacher_head);
}
void initialize_student(student_List student_head)//��ʼ��
{
    student_List p;
    student_head=(student_List)malloc(sizeof(student_Lnode));
    p=(student_List)malloc(sizeof(student_Lnode));
    student_head->next=p;
    //����������Ϊ1
    p->num=1;
    //�����ڴ棬����һ������
    p=(student_List)malloc(sizeof(student_Lnode));
    student_head->next->next=p;
    strcpy(p->id,"student");
    strcpy(p->password,"student");
    strcpy(p->name,"������");
    strcpy(p->sex,"��");
    strcpy(p->identity,"ѧ��");
    strcpy(p->nation,"����");
    strcpy(p->face,"��Ա");
    strcpy(p->birth,"1997��10��29��");
    strcpy(p->time,"2016��09��");
    strcpy(p->college,"��Ϣ��ѧ�빤��ѧԺ");
    p->collegeid=4;
    strcpy(p->profession,"�ռ���Ϣ�����ּ���");
    p->professionid=19;
    strcpy(p->grade,"�ռ���Ϣ�����ּ���1601");
    p->next=NULL;
    student_save(student_head);
}
void initialize_score(score_List score_head)//��ʼ���ɼ�����
{
    score_List p,prior,rear;
    rear=score_head;
    p=(score_List)malloc(sizeof(score_Lnode));
    prior=score_head;
    rear->next=p;
    //����������Ϊ1
    p->num=3;
    p->prior=prior;
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(score_List)malloc(sizeof(score_Lnode));
    rear->next=p;
    p->prior=prior;
    p->num=1;//�ƶ���¼����
    strcpy(p->id,"201616060110");
    strcpy(p->name,"������");
    strcpy(p->profession,"�ռ���Ϣ�����ּ���");
    p->professionid=19;//רҵ����
    strcpy(p->college,"��Ϣ��ѧ�빤��ѧԺ");
    p->collegeid=4;//רҵ����
    strcpy(p->grade,"�ռ���Ϣ�����ּ���1601");
    p->gradeid=19;//�༶����
    strcpy(p->subject,"��ѧӢ��");
    p->subjectid=1;//�༶����
	strcpy(p->term,"��һѧ��");
    p->paper_score=100;
    p->usual_score=100;
    p->makeup_score=-1;
    p->score=100;
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(score_List)malloc(sizeof(score_Lnode));
    rear->next=p;
    p->prior=prior;
    p->num=2;
    strcpy(p->id,"201616060110");
    strcpy(p->name,"������");
    strcpy(p->profession,"�ռ���Ϣ�����ּ���");
    p->professionid=19;//רҵ����
    strcpy(p->college,"��Ϣ��ѧ�빤��ѧԺ");
    p->collegeid=4;//רҵ����
    strcpy(p->grade,"�ռ���Ϣ�����ּ���1601");
    p->gradeid=19;//�༶����
    strcpy(p->subject,"�ߵ���ѧ");
    p->subjectid=2;//�༶����
	strcpy(p->term,"��һѧ��");
    p->paper_score=100;
    p->usual_score=100;
    p->makeup_score=-1;
    p->score=100;
    rear=p;
    //�����ڴ棬�������
    prior=rear;
    p=(score_List)malloc(sizeof(score_Lnode));
    rear->next=p;
    p->prior=prior;
    p->num=3;
    strcpy(p->id,"201616060110");
    strcpy(p->name,"������");
    strcpy(p->profession,"�ռ���Ϣ�����ּ���");
    p->professionid=19;//רҵ����
    strcpy(p->college,"��Ϣ��ѧ�빤��ѧԺ");
    p->collegeid=4;//רҵ����
    strcpy(p->grade,"�ռ���Ϣ�����ּ���1601");
    p->gradeid=19;//�༶����
    strcpy(p->subject,"˼������뷨������");
    p->subjectid=3;//�༶����
	strcpy(p->term,"��һѧ��");
    p->paper_score=100;
    p->usual_score=100;
    p->makeup_score=-1;
    p->score=100;
    rear=p;

    rear->next=NULL;
    score_save(score_head);
}
