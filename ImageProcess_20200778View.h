
// ImageProcess_20200778View.h: CImageProcess20200778View 클래스의 인터페이스
//

#pragma once


class CImageProcess20200778View : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CImageProcess20200778View() noexcept;
	DECLARE_DYNCREATE(CImageProcess20200778View)

	// 특성입니다.
public:
	CImageProcess20200778Doc* GetDocument() const;

	// 작업입니다.
public:

	// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

	// 구현입니다.
public:
	virtual ~CImageProcess20200778View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPixelAdd();
	afx_msg void OnPixelSub();
	afx_msg void OnPixelDiv();
	afx_msg void OnPixelMul();
	afx_msg void OnPixelHistoEq();
	afx_msg void OnPixelLsContrast();
	afx_msg void OnPixelBinarization();
	afx_msg void OnPixelTwoImageAdd();
	afx_msg void OnPixelTwoImageSub();
	void LoadTwoImage();
	afx_msg void OnRegionSharpening();
	void convolve(unsigned char** inImg, unsigned char** outImg, int cols, int rows, float mask[3][3], int bias, int depth);
	afx_msg void OnRegionSmoothing();
	afx_msg void OnRegionEmbossing();
	afx_msg void OnRegionPrewitt();
	afx_msg void OnRegionRoberts();
	afx_msg void OnRegionSobel();
	afx_msg void OnRegionAverageFiltering();
	afx_msg void OnRegionMedianFiltering();
	afx_msg void OnMorphologyColorToGray();
	afx_msg void OnMorphologyBinarization();
	afx_msg void OnMorphologyErosion();
	afx_msg void OnMorphologyDilation();
	afx_msg void OnMorphologyOpening();
	void CopyResultToInput();
	afx_msg void OnMorphologyClosing();
	afx_msg void OnGeometryZoomin();
	afx_msg void OnGeometryBilinearInterpolation();
	afx_msg void OnGeometryZoomoutSubsampling();
	afx_msg void OnGeometryZoomoutAverage();
	afx_msg void OnGeometryZoomoutMedian();
	afx_msg void OnGeometryRotate();
	afx_msg void OnRotateDialog();
	afx_msg void OnGeometryMirror();
	afx_msg void OnGeometryUpsidedown();
	afx_msg void OnGeometryWarping();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnAviView();
	bool bAviMode;
	CString AVIFileName;
	void LoadAviFile(CDC* pDC);
};

#ifndef _DEBUG  // ImageProcess_20200778View.cpp의 디버그 버전
inline CImageProcess20200778Doc* CImageProcess20200778View::GetDocument() const
{ return reinterpret_cast<CImageProcess20200778Doc*>(m_pDocument); }
#endif

