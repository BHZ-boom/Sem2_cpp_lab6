
// lab6View.cpp: Clab6View 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "lab6.h"
#endif

#include "lab6Doc.h"
#include "lab6View.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Clab6View

IMPLEMENT_DYNCREATE(Clab6View, CView)

BEGIN_MESSAGE_MAP(Clab6View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Clab6View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_VIEW_MOUSE, &Clab6View::OnViewMouse)
	ON_UPDATE_COMMAND_UI(ID_VIEW_MOUSE, &Clab6View::OnUpdateViewMouse)
END_MESSAGE_MAP()

// Clab6View 构造/析构

Clab6View::Clab6View() noexcept
{
	// TODO: 在此处添加构造代码
	m_bShowMousePos = false;
	m_mousePos.x = 0;
	m_mousePos.y = 0;
}

Clab6View::~Clab6View()
{
}

BOOL Clab6View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// Clab6View 绘图

void Clab6View::OnDraw(CDC* pDC)
{
	Clab6Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	// 绘制文档的代码

	//CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	if (m_bShowMousePos) {
		CString strMousePos;
		//POINT pt;
		//GetCursorPos(&pt);
		//ScreenToClient(&pt);
		strMousePos.Format(_T("Mouse Position: (%d, %d)"), m_mousePos.x, m_mousePos.y);
		pDC->TextOut(10, 10, strMousePos);
	}
}


// Clab6View 打印


void Clab6View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Clab6View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void Clab6View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void Clab6View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void Clab6View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Clab6View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Clab6View 诊断

#ifdef _DEBUG
void Clab6View::AssertValid() const
{
	CView::AssertValid();
}

void Clab6View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Clab6Doc* Clab6View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Clab6Doc)));
	return (Clab6Doc*)m_pDocument;
}
#endif //_DEBUG


// Clab6View 消息处理程序


void Clab6View::OnRButtonDown(UINT nFlags, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_MAINFRAME);
	CMenu* pSubMenu = menu.GetSubMenu(2);  // “查看”菜单

	ClientToScreen(&point);
	pSubMenu->TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, this);
}



void Clab6View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (m_bShowMousePos) {
		m_mousePos = point;
		Invalidate();  // 重新绘制用户区
	}

	CView::OnMouseMove(nFlags, point);
}


void Clab6View::OnViewMouse()
{
	m_bShowMousePos = !m_bShowMousePos;
	Invalidate();  // 重新绘制用户区
}


void Clab6View::OnUpdateViewMouse(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_bShowMousePos);
}
