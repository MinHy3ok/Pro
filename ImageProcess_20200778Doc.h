﻿
// ImageProcess_20200778Doc.h: CImageProcess20200778Doc 클래스의 인터페이스
//


#pragma once


class CImageProcess20200778Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CImageProcess20200778Doc() noexcept;
	DECLARE_DYNCREATE(CImageProcess20200778Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CImageProcess20200778Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	unsigned char** inputImg;
	unsigned char** inputImg2;
	unsigned char** resultImg;

	int ImageWidth;
	int ImageHeight;
	int depth;					// 1 - 흑백, 3 - 컬러

	int gImageWidth;
	int gImageHeight;
	unsigned char** gResultImg;

	void PixelAdd();
	void PixelSub();
	void PixelDiv();
	void PixelMul();
	void PixelHistoEq();
	void PixelLsContrast();
	void PixelBinarization();
	void PixelTwoImageAdd();
	void LoadTwoImages();

	void LoadImageFile(CArchive& ar);
	void LoadSecondImageFile(CArchive& ar);
};
