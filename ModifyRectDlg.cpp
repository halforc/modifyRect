// ModifyRectDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ModifyRect.h"
#include "ModifyRectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CModifyRectDlg �Ի���




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


// CModifyRectDlg ��Ϣ�������

BOOL CModifyRectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_rectTracker.m_nStyle=CRectTracker::resizeOutside|CRectTracker::dottedLine;
	m_rect.left=0;
	m_rect.right=100;
	m_rect.bottom=100;
	m_rect.top=0;

	//SetCapture();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CModifyRectDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
		CClientDC dc(this);
		HBRUSH hBrush=(HBRUSH)GetStockObject(NULL_BRUSH);
		HBRUSH oldBrush=(HBRUSH )dc.SelectObject(hBrush);



		//���ñ߽�
		m_rectTracker.m_rect=m_rect;

		//����ӳ��;L�߼� ---> D�豸
		dc.LPtoDP(&m_rectTracker.m_rect);

		//��ͼ�εı߽�
		if(m_IsDraw) m_rectTracker.Draw(&dc);

		dc.SelectObject(oldBrush);
		DeleteObject(hBrush);
		
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CModifyRectDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CModifyRectDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//ModifyCursor(point);
	

	int ret=m_rectTracker.HitTest(point);
	if(ret>=0)//�ж��Ƿ�Ҫ�������߿�
	{
		m_IsDraw=TRUE;
		InvalidateRect(&m_rectTracker.m_rect);

		if(ret==CRectTracker::hitMiddle)//ֻ�е�������м䰴��,����������ƶ�����
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
		else//�ڵ�������ʱҲ���ܵ���������ȥ.
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

	//�˺��������ص������Ϣ,����Ҫ�������������д��굯��Ҫ������¼�.
	if(m_rectTracker.Track(this,point,false,NULL)) 
	{ 
		//��굯����ִ������ĳ���
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
		//��굯���ִ������ĳ���.
		
		ClipCursor(NULL);
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CModifyRectDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDialog::OnMouseMove(nFlags, point);
}

//�����ַ��������Զ�������״,���ǻ��й����˸.
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
	// TODO: �ڴ����ר�ô����/����û���
	
	return CDialog::PreCreateWindow(cs);
}

BOOL CModifyRectDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	//��������Ƿ�ı���.
	if(m_IsDraw && pWnd==this && m_rectTracker.SetCursor(this,nHitTest))//
	{
		return TRUE;
	}
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CModifyRectDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialog::OnLButtonUp(nFlags, point);
}
