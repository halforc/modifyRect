// ModifyRectDlg.h : ͷ�ļ�
//

#pragma once
#include "MyRectTracker.h"

// CModifyRectDlg �Ի���
class CModifyRectDlg : public CDialog
{
// ����
public:
	CModifyRectDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MODIFYRECT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

public:
    CMyRectTracker m_rectTracker;
	CRect m_rect;
	BOOL m_IsDraw;
	//void ModifyCursor(CPoint point);
    void updateInfo(CRect rect);
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
