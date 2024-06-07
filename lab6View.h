
// lab6View.h: Clab6View 类的接口
//

#pragma once


class Clab6View : public CView
{
protected: // 仅从序列化创建
	Clab6View() noexcept;
	DECLARE_DYNCREATE(Clab6View)

// 特性
public:
	Clab6Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~Clab6View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	BOOL m_bShowMousePos;
	CPoint m_mousePos;
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnViewMouse();
	afx_msg void OnUpdateViewMouse(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // lab6View.cpp 中的调试版本
inline Clab6Doc* Clab6View::GetDocument() const
   { return reinterpret_cast<Clab6Doc*>(m_pDocument); }
#endif

