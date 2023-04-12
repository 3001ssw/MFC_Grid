
// MFCApplication1Dlg.h: 헤더 파일
//

#pragma once
#include "GridCtrl.h"

// CMFCApplication1Dlg 대화 상자
class CMFCApplication1Dlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	CGridCtrl m_Grid;

	CEdit m_edX;
	CEdit m_edY;
	CEdit m_edText;
	int m_iX;
	int m_iY;

	int m_nGap;

protected:
	void InitGrid(void);
	void SetLayout();

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonGet();
	afx_msg void OnBnClickedButtonReadOnly();
	afx_msg void OnBnClickedButtonGetSelect();
	afx_msg void OnBnClickedButtonChangeColor();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
};
