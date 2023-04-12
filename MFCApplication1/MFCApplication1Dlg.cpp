
// MFCApplication1Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1Dlg 대화 상자



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
    , m_iX(0)
    , m_iY(0)
    , m_nGap(5)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CMFCApplication1Dlg::~CMFCApplication1Dlg()
{
    m_ImageList.DeleteImageList();
    m_Grid.DeleteAllItems();
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_CUSTOM1, m_Grid);
    DDX_Control(pDX, IDC_EDIT_X, m_edX);
    DDX_Control(pDX, IDC_EDIT_Y, m_edY);
    DDX_Text(pDX, IDC_EDIT_X, m_iX);
    DDX_Text(pDX, IDC_EDIT_Y, m_iY);
    DDX_Control(pDX, IDC_EDIT_TEXT, m_edText);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCApplication1Dlg::OnBnClickedCancel)
    ON_BN_CLICKED(IDC_BUTTON_GET, &CMFCApplication1Dlg::OnBnClickedButtonGet)
    ON_BN_CLICKED(IDC_BUTTON_GET2, &CMFCApplication1Dlg::OnBnClickedButtonReadOnly)
    ON_BN_CLICKED(IDC_BUTTON_GET_SELECT, &CMFCApplication1Dlg::OnBnClickedButtonGetSelect)
    ON_BN_CLICKED(IDC_BUTTON_CHANGE_COLOR, &CMFCApplication1Dlg::OnBnClickedButtonChangeColor)
END_MESSAGE_MAP()


// CMFCApplication1Dlg 메시지 처리기

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	InitGrid();
    SetLayout();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::InitGrid(void)
{
    // 그리드 설정
    m_Grid.SetParent(this); // 부모 설정
    //m_Grid.SetEditable(FALSE); // 그리드 전체 수정유무 설정, GVIS_READONLY 속성
    //m_Grid.SetListMode(TRUE); // 리스트 모드
    //m_Grid.EnableDragAndDrop(TRUE); // 드래그 앤 드랍 허용 유무
    m_Grid.SetBkColor(RGB(192, 192, 192)); // 배경 색상
    m_Grid.SetTextBkColor(RGB(255, 255, 255)); // 텍스트 색상
    m_Grid.EnableScrollBar(ESB_ENABLE_BOTH, TRUE); // 스크롤바 사용 유무
    //m_Grid.SetVirtualMode(TRUE); // Virtual 모드 설정

    // 이미지 설정
    int nImageCount = 7;
    m_ImageList.Create(16, 16, ILC_COLOR32 | ILC_MASK, nImageCount, 0); // 이미지리스트 생성
    m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON1));
    m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON2));
    m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON3));
    m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON4));
    m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON5));
    m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON6));
    m_ImageList.Add(AfxGetApp()->LoadIcon(IDI_ICON7));
    m_Grid.SetImageList(&m_ImageList);

    m_Grid.SetRedraw(FALSE);
    // 그리드 개수 설정
    m_Grid.SetRowCount(7);
    m_Grid.SetColumnCount(10);
    m_Grid.SetFixedRowCount(1);
    m_Grid.SetFixedColumnCount(1);

    // 그리드 Row, Col, Fixed Row, Fixed Col 개수 얻기
    int nRowCount = m_Grid.GetRowCount();
    int nColCount = m_Grid.GetColumnCount();
    int nFixedRowCount = m_Grid.GetFixedRowCount();
    int nFixedColCount = m_Grid.GetFixedColumnCount();

    // Fixed Row, Column 텍스트 설정
    // Row
    for (int nRow = nFixedRowCount ; nRow < nRowCount; nRow++)
    {
        CString strText;
        strText.Format(_T("Row %d"), nRow);
        m_Grid.SetItemText(nRow, 0, strText);
        m_Grid.SetItemFormat(nRow, 0, DT_CENTER | DT_VCENTER | DT_WORDBREAK);

        // 이미지 설정
        int nImageIndex = nRow % nImageCount;
        m_Grid.SetItemImage(nRow, 0, nImageIndex);
    }
    // Column
    for (int nCol = nFixedColCount ; nCol < nColCount; nCol++)
    {
        CString strText(_T(""));
        strText.Format(_T("Column %d"), nCol);
    
        GV_ITEM Item;
        Item.mask = GVIF_TEXT | GVIF_FORMAT;
        Item.row = 0;
        Item.col = nCol;
        Item.nFormat = DT_CENTER | DT_VCENTER | DT_WORDBREAK;
        Item.strText = strText;
        m_Grid.SetItem(&Item); 
    }

    // 셀 설정
    for (int nRow = nFixedRowCount; nRow < nRowCount; nRow++)
    {
        for (int nCol = nFixedColCount; nCol < nColCount; nCol++)
        { 
            // 셀 속성 설정
            m_Grid.SetItemFormat(nRow, nCol, DT_CENTER|DT_VCENTER|DT_SINGLELINE);

            int nCellType = nRow % (nRowCount - nFixedRowCount + 1);
            if (nCellType == 1)
            {
                // 텍스트
                CString strText;
                strText.Format(_T("(%d, %d)"), nRow, nCol);
                CGridCellBase* pCell = m_Grid.GetCell(nRow, nCol);
                pCell->SetText(strText);
            }
            else if (nCellType == 2)
            {
                // 콤보박스
                m_Grid.SetCellType(nRow, nCol, RUNTIME_CLASS(CGridCellCombo));
                CGridCellBase* pCell = m_Grid.GetCell(nRow, nCol);
                if (pCell->IsKindOf(RUNTIME_CLASS(CGridCellCombo)) == TRUE)
                {
                    ((CGridCellCombo*)pCell)->SetStyle(CBS_DROPDOWNLIST);
                    CStringArray ar;
                    ar.Add(_T("Option 1"));
                    ar.Add(_T("Option 2"));
                    ar.Add(_T("Option 3"));
                    ar.Add(_T("Option 4"));
                    ((CGridCellCombo*)pCell)->SetOptions(ar);
                    ((CGridCellCombo*)pCell)->SetText(_T("Option 1"));
                }
            }
            else if (nCellType == 3)
            {
                // 체크박스
                CString strText;
                strText.Format(_T("Check Box(%d, %d)"), nRow, nCol);
                m_Grid.SetCellType(nRow, nCol, RUNTIME_CLASS(CGridCellCheck));
                CGridCellBase* pCell = m_Grid.GetCell(nRow, nCol);
                if (pCell->IsKindOf(RUNTIME_CLASS(CGridCellCheck)) == TRUE)
                {
                    //((CGridCellCheck*)pCell)->SetCheck(TRUE);
                    ((CGridCellCheck*)pCell)->SetText(strText);
                }
            }
            else if (nCellType == 4)
            {
                // date time
                m_Grid.SetCellType(nRow, nCol, RUNTIME_CLASS(CGridCellDateTime));
                CGridCellBase* pCell = m_Grid.GetCell(nRow, nCol);
                if (pCell->IsKindOf(RUNTIME_CLASS(CGridCellDateTime)) == TRUE)
                {
                    ((CGridCellDateTime*)pCell)->SetTime(CTime::GetCurrentTime());
                }
            }
            else if (nCellType == 5)
            {
                // url
                m_Grid.SetCellType(nRow, nCol, RUNTIME_CLASS(CGridURLCell));
                CGridCellBase* pCell = m_Grid.GetCell(nRow, nCol);
                if (pCell->IsKindOf(RUNTIME_CLASS(CGridURLCell)) == TRUE)
                {
                    ((CGridURLCell*)pCell)->SetText(_T("https://3001ssw.tistory.com"));
                }
            }
            else if (nCellType == 6)
            {
                // numeric
                m_Grid.SetCellType(nRow, nCol, RUNTIME_CLASS(CGridCellNumeric));
                CGridCellBase* pCell = m_Grid.GetCell(nRow, nCol);
                if (pCell->IsKindOf(RUNTIME_CLASS(CGridCellNumeric)) == TRUE)
                {
                    ((CGridURLCell*)pCell)->SetText(_T("123"));
                }
            }
            else
            {
                CString strText;
                strText.Format(_T("(%d, %d)"), nRow, nCol);
                CGridCellBase* pCell = m_Grid.GetCell(nRow, nCol);
                pCell->SetText(strText);
            }
        }
    }

    m_Grid.AutoSize(); // 셀 사이즈 자동 변경
    int iHeight = m_Grid.GetRowHeight(0); // 높이
    int iWidth = m_Grid.GetColumnWidth(0); // 너비
    //m_Grid.SetRowHeight(0, iHeight * 3); // Fixed Row 높이 변경
    //m_Grid.SetColumnWidth(0, iWidth * 3); // Fixed Column 너비 변경
    m_Grid.SetRedraw(TRUE);
}

void CMFCApplication1Dlg::SetLayout()
{
    // 동적 레이아웃 활성화.
    this->EnableDynamicLayout();

    /* 이동 옵션 */
    // 1. 이동하지 않음.
    CMFCDynamicLayout::MoveSettings move_none = CMFCDynamicLayout::MoveSettings{};

    // 2. X,Y 방향으로 100% 비율 이동.
    CMFCDynamicLayout::MoveSettings move_both_100 = CMFCDynamicLayout::MoveSettings{};
    move_both_100.m_nXRatio = 100;
    move_both_100.m_nYRatio = 100;

    // 3. Y 방향으로만 100% 비율 이동.
    CMFCDynamicLayout::MoveSettings move_y_100 = CMFCDynamicLayout::MoveSettings{};
    move_y_100.m_nYRatio = 100;

    /* 크기 조정 옵션 */
    // 1. 크기 조정하지 않음.
    CMFCDynamicLayout::SizeSettings size_none = CMFCDynamicLayout::SizeSettings{};

    // 2. X,Y 방향으로 100% 비율 크기 조정.
    CMFCDynamicLayout::SizeSettings size_both_100 = CMFCDynamicLayout::SizeSettings{};
    size_both_100.m_nXRatio = 100;
    size_both_100.m_nYRatio = 100;

    // Dialog의 동적 레이아웃 포인터 획득.
    CMFCDynamicLayout* manager = this->GetDynamicLayout();
    // 동적 레이아웃 생성.
    manager->Create(this);

    // 동적 레이아웃에 등록할 컨트롤 추가.
    manager->AddItem(IDC_CUSTOM1, move_none, size_both_100);
    manager->AddItem(IDC_EDIT_X, move_y_100, size_none);
    manager->AddItem(IDC_EDIT_Y, move_y_100, size_none);
    manager->AddItem(IDC_EDIT_TEXT, move_y_100, size_none);
    manager->AddItem(IDC_BUTTON_SET_READ_ONLY, move_y_100, size_none);
    manager->AddItem(IDC_BUTTON_GET_SELECT, move_y_100, size_none);
    manager->AddItem(IDC_BUTTON_CHANGE_COLOR, move_y_100, size_none);
}


void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMFCApplication1Dlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}


void CMFCApplication1Dlg::OnBnClickedButtonGet()
{
    UpdateData(TRUE);

    CString strText = m_Grid.GetItemText(m_iX, m_iY);
    if (strText.IsEmpty() == TRUE)
        TRACE(_T("Get Text is Empty\n"));
    else
        TRACE(_T("strText: %s\n"), strText);

    CGridCellBase* pCell = m_Grid.GetCell(m_iX, m_iY);
    if (pCell == NULL)
        return;

    if (pCell->IsKindOf(RUNTIME_CLASS(CGridCellCheck)) == TRUE)
    {
        BOOL bCheck = ((CGridCellCheck*)pCell)->GetCheck();
        TRACE(_T("bCheck: %d\n"), bCheck);
    }

    DWORD dwState = pCell->GetState();
    TRACE(_T("dwState: %d\n"), dwState);
}

void CMFCApplication1Dlg::OnBnClickedButtonGetSelect()
{
    UpdateData(TRUE);

    CCellRange cellRange = m_Grid.GetSelectedCellRange();
    int iMinRow = cellRange.GetMinRow();
    int iMaxRow = cellRange.GetMaxRow();
    int iMinCol = cellRange.GetMinCol();
    int iMaxCol = cellRange.GetMaxCol();

    for (int iRow = iMinRow ; iRow <= iMaxRow ; iRow++)
    {
        for (int iCol = iMinCol ; iCol <= iMaxCol ; iCol++)
        {
            BOOL iIsSelected = m_Grid.IsCellSelected(iRow, iCol);
            if (iIsSelected)
                TRACE(_T("(%d, %d) is selected\n"), iRow, iCol);
        }
    }
}


void CMFCApplication1Dlg::OnBnClickedButtonChangeColor()
{
    UpdateData(TRUE);

    // 색 바꾸기
    CCellRange cellRange = m_Grid.GetSelectedCellRange();
    int iMinRow = cellRange.GetMinRow();
    int iMaxRow = cellRange.GetMaxRow();
    int iMinCol = cellRange.GetMinCol();
    int iMaxCol = cellRange.GetMaxCol();

    for (int iRow = iMinRow ; iRow <= iMaxRow ; iRow++)
    {
        for (int iCol = iMinCol ; iCol <= iMaxCol ; iCol++)
        {
            BOOL iIsSelected = m_Grid.IsCellSelected(iRow, iCol);
            if (iIsSelected)
            {
                TRACE(_T("(%d, %d) is selected\n"), iRow, iCol);
                COLORREF clr = RGB(rand() % 256, rand() % 256, rand() % 256);
                m_Grid.SetItemBkColour(iRow, iCol, clr);
                m_Grid.SetItemFgColour(iRow, iCol, RGB(0, 0, 0));

            }
        }
    }
}



void CMFCApplication1Dlg::OnBnClickedButtonReadOnly()
{
    UpdateData(TRUE);

    UINT uiState = m_Grid.GetItemState(m_iX, m_iY);
    if ((uiState & GVIS_READONLY) == GVIS_READONLY)
        uiState = uiState & ~GVIS_READONLY;
    else
        uiState = uiState | GVIS_READONLY;
    
    m_Grid.SetItemState(m_iX, m_iY, uiState);
}


BOOL CMFCApplication1Dlg::OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
    // TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
    int nIdFrom = (int)wParam;
    NM_GRIDVIEW *nmgv = (NM_GRIDVIEW*)lParam;

    if (nmgv->hdr.idFrom != m_Grid.GetDlgCtrlID())
        return CDialogEx::OnNotify(wParam, lParam, pResult);

    // 제공하는 알림 코드
    if (nmgv->hdr.code == GVN_BEGINDRAG && (nmgv->iRow != -1 && nmgv->iColumn != -1))
        TRACE(_T("GVN_BEGINDRAG\n"));
    if (nmgv->hdr.code == GVN_BEGINLABELEDIT && (nmgv->iRow != -1 && nmgv->iColumn != -1))
        TRACE(_T("GVN_BEGINLABELEDIT\n"));
    if (nmgv->hdr.code == GVN_BEGINRDRAG     && (nmgv->iRow != -1 && nmgv->iColumn != -1))
        TRACE(_T("GVN_BEGINRDRAG\n"));
    if (nmgv->hdr.code == GVN_COLUMNCLICK    && (nmgv->iRow != -1 && nmgv->iColumn != -1))
        TRACE(_T("GVN_COLUMNCLICK\n"));
    if (nmgv->hdr.code == GVN_DELETEITEM     && (nmgv->iRow != -1 && nmgv->iColumn != -1))
        TRACE(_T("GVN_DELETEITEM\n"));
    if (nmgv->hdr.code == GVN_ENDLABELEDIT && (nmgv->iRow != -1 && nmgv->iColumn != -1))
        TRACE(_T("GVN_ENDLABELEDIT\n"));
    if (nmgv->hdr.code == GVN_SELCHANGING    && (nmgv->iRow != -1 && nmgv->iColumn != -1))
        TRACE(_T("GVN_SELCHANGING\n"));
    if (nmgv->hdr.code == GVN_SELCHANGED     && (nmgv->iRow != -1 && nmgv->iColumn != -1))
        TRACE(_T("GVN_SELCHANGED\n"));
    if (nmgv->hdr.code == GVN_GETDISPINFO    && (nmgv->iRow != -1 && nmgv->iColumn != -1))
        TRACE(_T("GVN_GETDISPINFO\n"));
    if (nmgv->hdr.code == GVN_ODCACHEHINT    && (nmgv->iRow != -1 && nmgv->iColumn != -1))
        TRACE(_T("GVN_ODCACHEHINT\n"));

    // 예제
    if (nmgv->hdr.code == NM_CLICK && (nmgv->iRow != -1 && nmgv->iColumn != -1))
    {
        // 클릭
        CString strText = m_Grid.GetItemText(nmgv->iRow, nmgv->iColumn);
        CGridCellBase* pCell = m_Grid.GetCell(nmgv->iRow, nmgv->iColumn);
        TRACE(_T("====================OnClick (%d, %d, %s)\n"), nmgv->iRow, nmgv->iColumn, strText);
        if (pCell->IsKindOf(RUNTIME_CLASS(CGridCellCheck)) == TRUE)
        {
            BOOL bCheck = ((CGridCellCheck*)pCell)->GetCheck();
            //TRACE(_T("=========CGridCellCheck strText(%s), Check(%d)\n"), strText, bCheck);
        }
        else if (pCell->IsKindOf(RUNTIME_CLASS(CGridCellCombo)) == TRUE)
        {
            //TRACE(_T("=========CGridCellCombo strText(%s)\n"), strText);
        }
        CString strX(_T("")), strY;(_T(""));
        strX.Format(_T("%d"), nmgv->iRow);
        strY.Format(_T("%d"), nmgv->iColumn);
        m_edX.SetWindowText(strX);
        m_edY.SetWindowText(strY);
        m_edText.SetWindowText(strText);
    }
    else if (nmgv->hdr.code == GVN_ENDLABELEDIT && (nmgv->iRow != -1 && nmgv->iColumn != -1))
    {
        // 수정 완료 시
        CString strText = m_Grid.GetItemText(nmgv->iRow, nmgv->iColumn);
        CGridCellBase* pCell = m_Grid.GetCell(nmgv->iRow, nmgv->iColumn);
        TRACE(_T("====================GVN_ENDLABELEDIT (%d, %d, %s)\n"), nmgv->iRow, nmgv->iColumn, strText);
        if (pCell->IsKindOf(RUNTIME_CLASS(CGridCellCheck)) == TRUE)
        {
            BOOL bCheck = ((CGridCellCheck*)pCell)->GetCheck();
            //TRACE(_T("=========CGridCellCheck strText(%s), Check(%d)\n"), strText, bCheck);
        }
        else if (pCell->IsKindOf(RUNTIME_CLASS(CGridCellCombo)) == TRUE)
        {
            //TRACE(_T("=========CGridCellCombo strText(%s)\n"), strText);
        }
    }
 
    // 그외 알람
    //if (nmgv->hdr.code == NM_OUTOFMEMORY)
    //    TRACE(_T("NM_OUTOFMEMORY\n"));
    //else if (nmgv->hdr.code == NM_CLICK)
    //    TRACE(_T("NM_CLICK\n"));
    //else if (nmgv->hdr.code == NM_DBLCLK)
    //    TRACE(_T("NM_DBLCLK\n"));
    //else if (nmgv->hdr.code == NM_RETURN)
    //    TRACE(_T("NM_RETURN\n"));
    //else if (nmgv->hdr.code == NM_RCLICK)
    //    TRACE(_T("NM_RCLICK\n"));
    //else if (nmgv->hdr.code == NM_RDBLCLK)
    //    TRACE(_T("NM_RDBLCLK\n"));
    //else if (nmgv->hdr.code == NM_SETFOCUS)
    //    TRACE(_T("NM_SETFOCUS\n"));
    //else if (nmgv->hdr.code == NM_KILLFOCUS)
    //    TRACE(_T("NM_KILLFOCUS\n"));
    //else if (nmgv->hdr.code == NM_CUSTOMDRAW)
    //    TRACE(_T("NM_CUSTOMDRAW\n"));
    //else if (nmgv->hdr.code == NM_HOVER)
    //    TRACE(_T("NM_HOVER\n"));
    //else if (nmgv->hdr.code == NM_NCHITTEST)
    //    TRACE(_T("NM_NCHITTEST\n"));
    //else if (nmgv->hdr.code == NM_KEYDOWN)
    //    TRACE(_T("NM_KEYDOWN\n"));
    //else if (nmgv->hdr.code == NM_RELEASEDCAPTURE)
    //    TRACE(_T("NM_RELEASEDCAPTURE\n"));
    //else if (nmgv->hdr.code == NM_SETCURSOR)
    //    TRACE(_T("NM_SETCURSOR\n"));
    //else if (nmgv->hdr.code == NM_CHAR)
    //    TRACE(_T("NM_CHAR\n"));
    //else if (nmgv->hdr.code == NM_TOOLTIPSCREATED)
    //    TRACE(_T("NM_TOOLTIPSCREATED\n"));
    //else if (nmgv->hdr.code == NM_LDOWN)
    //    TRACE(_T("NM_LDOWN\n"));
    //else if (nmgv->hdr.code == NM_RDOWN)
    //    TRACE(_T("NM_RDOWN\n"));
    //else if (nmgv->hdr.code == NM_THEMECHANGED)
    //    TRACE(_T("NM_THEMECHANGED\n"));
    //else if (nmgv->hdr.code == NM_FONTCHANGED)
    //    TRACE(_T("NM_FONTCHANGED\n"));
    //else if (nmgv->hdr.code == NM_CUSTOMTEXT)
    //    TRACE(_T("NM_CUSTOMTEXT\n"));
    //else if (nmgv->hdr.code == NM_TVSTATEIMAGECHANGING)
    //    TRACE(_T("NM_TVSTATEIMAGECHANGING\n"));
    //else if (nmgv->hdr.code == GVN_ENDLABELEDIT)
    //    TRACE(_T("GVN_ENDLABELEDIT\n"));

    return CDialogEx::OnNotify(wParam, lParam, pResult);
}




