// ModifyRectDlg.h : 头文件
//

#pragma once
#include "MyRectTracker.h"

// CModifyRectDlg 对话框
class CModifyRectDlg : public CDialog
{
// 构造
public:
	CModifyRectDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MODIFYRECT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
    CMyRectTracker m_rectTracker;
	CRect m_rect;
	BOOL m_IsDraw;
	//void ModifyCursor(CPoint point);
    void updateInfo(CRect rect);
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
