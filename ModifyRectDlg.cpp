// ModifyRectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ModifyRect.h"
#include "ModifyRectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CModifyRectDlg 对话框




CModifyRectDlg::CModifyRectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModifyRectDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_IsDraw=TRUE;
}

void CModifyRectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CModifyRectDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_BN_CLICKED(IDC_BUTTON1, &CModifyRectDlg::OnBnClickedButton1)
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CModifyRectDlg 消息处理程序

BOOL CModifyRectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_rectTracker.m_nStyle=CRectTracker::resizeOutside|CRectTracker::dottedLine;
	m_rect.left=0;
	m_rect.right=100;
	m_rect.bottom=100;
	m_rect.top=0;

	//SetCapture();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CModifyRectDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CModifyRectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
		CClientDC dc(this);
		HBRUSH hBrush=(HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush=(HBRUSH )dc.SelectObject(hBrush);



		//设置边界
		m_rectTracker.m_rect=m_rect;

		//坐标映射;L逻辑 ---> D设备
		dc.LPtoDP(&m_rectTracker.m_rect);

		//画图形的边界
		if(m_IsDraw) m_rectTracker.Draw(&dc);

		dc.SelectObject(oldBrush);
		DeleteObject(hBrush);
		
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CModifyRectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CModifyRectDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//ModifyCursor(point);
	

	int ret=m_rectTracker.HitTest(point);
	if(ret>=0)//判断是否要画调整边框
	{
		m_IsDraw=TRUE;
		InvalidateRect(&m_rectTracker.m_rect);

		if(ret==CRectTracker::hitMiddle)//只有当鼠标在中间按下,才限制鼠标移动区域
		{
			POINT pos;
			GetCursorPos(&pos);
			ScreenToClient(&pos);
			CRect ClientRect;
			GetClientRect(&ClientRect);
			ClientRect.left+=pos.x-m_rect.left;
			ClientRect.top+=pos.y-m_rect.top;
			ClientRect.right-=m_rect.right-pos.x;
			ClientRect.bottom-=m_rect.bottom-pos.y;
			ClientToScreen(&ClientRect);
			ClipCursor(&ClientRect);
		}
		else//在调整矩形时也不能调整到外面去.
		{
			POINT pos;
			GetCursorPos(&pos);
			ScreenToClient(&pos);
			CRect ClientRect;
			GetClientRect(&ClientRect);
			ClientToScreen(&ClientRect);
			ClipCursor(&ClientRect);
		}
	}
	else
	{
		m_IsDraw=FALSE;
		CRect rect=m_rectTracker.m_rect;
		rect.left-=4;
		rect.right+=4;
		rect.top-=4;
		rect.bottom+=4;
		InvalidateRect(&rect);
	}

	//此函数会拦截掉鼠标消息,所以要在这个函数后面写鼠标弹起要处理的事件.
	if(m_rectTracker.Track(this,point,false,NULL)) 
	{ 
		//鼠标弹起后才执行下面的程序
		CClientDC   dc(this); 
		CRect rect=m_rect;
		m_rect=m_rectTracker.m_rect; 
		rect.left-=4;
		rect.right+=4;
		rect.top-=4;
		rect.bottom+=4;
		InvalidateRect(&rect);
		
		ClipCursor(NULL);
	}
	else
	{
		//鼠标弹起后执行下面的程序.
		
		ClipCursor(NULL);
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CModifyRectDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CDialog::OnMouseMove(nFlags, point);
}

//用这种方法可以自定义光标形状,但是会有光标闪烁.
void CModifyRectDlg::ModifyCursor(CPoint point)
{
	static int CurStyle=-2;
	int ret=m_rectTracker.HitTest(point);
	switch(ret)
	{
	case CRectTracker::hitTopLeft:
	case CRectTracker::hitBottomRight:
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENWSE));
		break;

	case CRectTracker::hitTopRight:
	case CRectTracker::hitBottomLeft:
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENESW));
		break;

	case CRectTracker::hitRight:
	case CRectTracker::hitLeft:
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZEWE));
		break;

	case CRectTracker::hitBottom:
	case CRectTracker::hitTop:
		SetCursor(AfxGetApp()->LoadStandardCursor(IDC_SIZENS));
		break;

	case CRectTracker::hitMiddle:	
			
			SetCursor(LoadCursor(NULL,IDC_SIZEALL));
		
		break;
	default:
		break;
	}
}
BOOL CModifyRectDlg::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此添加专用代码和/或调用基类
	
	return CDialog::PreCreateWindow(cs);
}

BOOL CModifyRectDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//这里控制是否改变光标.
	if(m_IsDraw && pWnd==this && m_rectTracker.SetCursor(this,nHitTest))//
	{
		return TRUE;
	}
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CModifyRectDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	srand(time(NULL)+rand());
	CString Str;
	for(int i=0;i<10;i++)
	{
		Str.Format(TEXT("%d"),rand());
		OutputDebugString(Str);
	}
}

void CModifyRectDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialog::OnLButtonUp(nFlags, point);
}
