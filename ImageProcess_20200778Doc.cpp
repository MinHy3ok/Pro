
// ImageProcess_20200778Doc.cpp: CImageProcess20200778Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageProcess_20200778.h"
#endif

#include "ImageProcess_20200778Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageProcess20200778Doc

IMPLEMENT_DYNCREATE(CImageProcess20200778Doc, CDocument)

BEGIN_MESSAGE_MAP(CImageProcess20200778Doc, CDocument)
END_MESSAGE_MAP()


// CImageProcess20200778Doc 생성/소멸

CImageProcess20200778Doc::CImageProcess20200778Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	inputImg = NULL;
	inputImg2 = NULL;
	resultImg = NULL;
	gResultImg = NULL;
}

CImageProcess20200778Doc::~CImageProcess20200778Doc()
{
	if (inputImg != NULL) {
		for (int i = 0; i < ImageHeight; i++) {
			free(inputImg[i]);
		}
		free(inputImg);
	}
	if (inputImg2 != NULL) {
		for (int i = 0; i < ImageHeight; i++) {
			free(inputImg2[i]);
		}
		free(inputImg2);
	}
	if (resultImg != NULL) {
		for (int i = 0; i < ImageHeight; i++) {
			free(resultImg[i]);
		}
		free(resultImg);
	}
	if (gResultImg != NULL) {
		for (int i = 0; i < gImageHeight; i++) {
			free(gResultImg[i]);
		}
		free(gResultImg);
	}
}

BOOL CImageProcess20200778Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageProcess20200778Doc serialization

void CImageProcess20200778Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
		ar.Write(resultImg, 256 * 256);
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
		/*
		CFile* fp = ar.GetFile();
		if (fp->GetLength() == 256 * 256) ar.Read(inputImg, 256 * 256);
		else AfxMessageBox("256 x 256 크기의 파일만 사용가능합니다."); */
			LoadImageFile(ar);
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageProcess20200778Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageProcess20200778Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageProcess20200778Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageProcess20200778Doc 진단

#ifdef _DEBUG
void CImageProcess20200778Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageProcess20200778Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageProcess20200778Doc 명령


void CImageProcess20200778Doc::PixelAdd()
{
	if (inputImg == NULL) { return; }

	int value;

	if (depth == 1) {
		for (int y = 0; y < ImageHeight; y++) {
			for (int x = 0; x < ImageWidth; x++) {
				value = inputImg[y][x] + 100;
				if (value > 255) {
					resultImg[y][x] = 255;
				}
				else {
					resultImg[y][x] = value;
				}
			}
		}
	}
	else {
		for (int y = 0; y < ImageHeight; y++) {
			for (int x = 0; x < ImageWidth; x++) {
				value = min(inputImg[y][3 * x] + 100, 255);
				resultImg[y][3 * x] = value;
				value = min(inputImg[y][3 * x + 1] + 100, 255);
				resultImg[y][3 * x + 1] = value;
				value = min(inputImg[y][3 * x + 2] + 100, 255);
				resultImg[y][3 * x + 2] = value;
			}
		}
	}
}


void CImageProcess20200778Doc::PixelSub()
{
	if (inputImg == NULL) { return; }

	int value;

	if (depth == 1) {
		for (int y = 0; y < ImageHeight; y++) {
			for (int x = 0; x < ImageWidth; x++) {
				value = max(0, inputImg[y][x] - 100);
				if (value < 0) {
					resultImg[y][x] = 0;
				}
				else {
					resultImg[y][x] = value;
				}
			}
		}
	}
	else {
		for (int y = 0; y < ImageHeight; y++) {
			for (int x = 0; x < ImageWidth; x++) {
				value = max(inputImg[y][3 * x] - 100, 0);
				resultImg[y][3 * x] = value;
				value = max(inputImg[y][3 * x + 1] - 100, 0);
				resultImg[y][3 * x + 1] = value;
				value = max(inputImg[y][3 * x + 2] - 100, 0);
				resultImg[y][3 * x + 2] = value;
			}
		}
	}
}


void CImageProcess20200778Doc::PixelDiv()
{
	if (inputImg == NULL) { return; }

	int value;

	if (depth == 1) {
		for (int y = 0; y < ImageHeight; y++) {
			for (int x = 0; x < ImageWidth; x++) {
				value = max(0, inputImg[y][x] / 1.5);
				if (value > 255) {
					resultImg[y][x] = 255;
				}
				else {
					resultImg[y][x] = value;
				}
			}
		}
	}
	else {
		for (int y = 0; y < ImageHeight; y++) {
			for (int x = 0; x < ImageWidth; x++) {
				value = max(inputImg[y][3 * x] / 1.5, 0);
				resultImg[y][3 * x] = value;
				value = max(inputImg[y][3 * x + 1] / 1.5, 0);
				resultImg[y][3 * x + 1] = value;
				value = max(inputImg[y][3 * x + 2] / 1.5, 0);
				resultImg[y][3 * x + 2] = value;
			}
		}
	}
}


void CImageProcess20200778Doc::PixelMul()
{
	if (inputImg == NULL) { return; }

	int value;

	if (depth == 1) {
		for (int y = 0; y < ImageHeight; y++) {
			for (int x = 0; x < ImageWidth; x++) {
				value = min(255, inputImg[y][x] * 1.5);
				if (value > 255) {
					resultImg[y][x] = 255;
				}
				else {
					resultImg[y][x] = value;
				}
			}
		}
	}
	else {
		for (int y = 0; y < ImageHeight; y++) {
			for (int x = 0; x < ImageWidth; x++) {
				value = min(inputImg[y][3 * x] * 1.5, 255);
				resultImg[y][3 * x] = value;
				value = min(inputImg[y][3 * x + 1] * 1.5, 255);
				resultImg[y][3 * x + 1] = value;
				value = min(inputImg[y][3 * x + 2] * 1.5, 255);
				resultImg[y][3 * x + 2] = value;
			}
		}
	}
}


void CImageProcess20200778Doc::PixelHistoEq()
{
	if (inputImg == NULL) { return; }
	if (depth != 1) { return; }

	CImageProcess20200778Doc* pDoc = this;

	int x, y, i, k;
	int acc_hist;
	int hist[256], sum[256];
	int N = ImageHeight * ImageWidth;

	for (i = 0; i < 256; i++) {
		hist[i] = 0;
	}

	for (int y = 0; y < ImageHeight; y++) {
		for (int x = 0; x < ImageWidth; x++) {
			k = pDoc->inputImg[y][x];
			hist[k]++;
		}
	}

	acc_hist = 0;
	for (i = 0; i < 256; i++) {
		acc_hist += hist[i];
		sum[i] = acc_hist;
	}

	for (y = 0; y < ImageHeight; y++) {
		for (x = 0; x < ImageWidth; x++) {
			k = pDoc->inputImg[y][x];
			pDoc->resultImg[y][x] = (float)sum[k] / N * 255;
		}
	}
}


void CImageProcess20200778Doc::PixelLsContrast()
{
	if (inputImg == NULL) { return; }

	int m = 255, M = 0;
	int x, y;

	if (depth == 1) {
		for (y = 0; y < ImageHeight; y++) {
			for (x = 0; x < ImageWidth; x++) {
				if (inputImg[y][x] < m) m = inputImg[y][x];
				if (inputImg[y][x] > M) M = inputImg[y][x];
			}
		}

		for (y = 0; y < ImageHeight; y++) {
			for (x = 0; x < ImageWidth; x++) {
				resultImg[y][x] = (float)(inputImg[y][x] - m) / (M - m) * 255;
			}
		}
	}
	else {
		for (y = 0; y < ImageHeight; y++) {
			for (x = 0; x < ImageWidth; x++) {
				if (inputImg[y][3 * x] < m) m = inputImg[y][3 * x];
				if (inputImg[y][3 * x + 1] < m) m = inputImg[y][3 * x + 1];
				if (inputImg[y][3 * x + 2] < m) m = inputImg[y][3 * x + 2];

				if (inputImg[y][3 * x] > M) M = inputImg[y][3 * x];
				if (inputImg[y][3 * x + 1] > M) M = inputImg[y][3 * x + 1];
				if (inputImg[y][3 * x + 2] > M) M = inputImg[y][3 * x + 2];
			}
		}

		for (y = 0; y < ImageHeight; y++) {
			for (x = 0; x < ImageWidth; x++) {
				resultImg[y][3 * x] = (float)(inputImg[y][3 * x] - m) / (M - m) * 255;
				resultImg[y][3 * x + 1] = (float)(inputImg[y][3 * x + 1] - m) / (M - m) * 255;
				resultImg[y][3 * x + 2] = (float)(inputImg[y][3 * x + 2] - m) / (M - m) * 255;
			}
		}
	}
}

void CImageProcess20200778Doc::PixelBinarization()
{

	if (inputImg == NULL) { return; }

	int threshold = 230;
	int x, y;
	if (depth == 1) {
		for (y = 0; y < ImageHeight; y++) {
			for (x = 0; x < ImageWidth; x++) {
				if (inputImg[y][x] > threshold) resultImg[y][x] = 255;
				else resultImg[y][x] = 0;
			}
		}
	}
	else {
		for (y = 0; y < ImageHeight; y++) {
			for (x = 0; x < ImageWidth; x++) {
				if (inputImg[y][3 * x] > threshold) { resultImg[y][3 * x] = 255; }
				else { resultImg[y][3 * x] = 0; }

				if (inputImg[y][3 * x + 1] > threshold) { resultImg[y][3 * x + 1] = 255; }
				else { resultImg[y][3 * x + 1] = 0; }

				if (inputImg[y][3 * x + 2] > threshold) { resultImg[y][3 * x + 2] = 255; }
				else { resultImg[y][3 * x + 2] = 0; }

			}
		}
	}
}


void CImageProcess20200778Doc::PixelTwoImageAdd()
{
	if (inputImg == NULL) { return; }

	int value;
	int x, y;

	LoadTwoImages();

	for (y = 0; y < ImageHeight; y++) {
		for (x = 0; x < ImageWidth; x++) {
			value = inputImg[y][x] + inputImg2[y][x];
			resultImg[y][x] = min(value, 255);
		}
	}
}


void CImageProcess20200778Doc::LoadTwoImages()
{
	CFile file;
	CFileDialog dlg(TRUE);

	AfxMessageBox("Select the First Image");

	if (dlg.DoModal() == IDOK) {
		file.Open(dlg.GetPathName(), CFile::modeRead); // 파일 열기
		CArchive ar(&file, CArchive::load);
		LoadImageFile(ar);
		//file.Read(inputImg, 256 * 256);
		file.Close();
	}

	AfxMessageBox("Select the Second Image");

	if (dlg.DoModal() == IDOK) {
		file.Open(dlg.GetPathName(), CFile::modeRead); // 파일 열기
		CArchive ar(&file, CArchive::load);
		LoadSecondImageFile(ar);
		//file.Read(inputImg2, 256 * 256);
		file.Close();
	}
}


void CImageProcess20200778Doc::LoadImageFile(CArchive& ar)
{
	// TODO: 여기에 구현 코드 추가.
	int maxValue;
	char type[16], buf[256];

	boolean isbmp = false;

	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();

	if (strcmp(strchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strchr(fname, '.'), ".pgm") == 0 || strcmp(strchr(fname, '.'), ".PGM") == 0) {

		ar.ReadString(type, 15); // P5

		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &ImageWidth, &ImageHeight);

		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0) { depth = 1; }
		else { depth = 3; }

	}
	else if (strcmp(strchr(fname, '.'), ".bmp") == 0 || strcmp(strchr(fname, '.'), ".BMP") == 0) {

		// bitmap file header open
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh, sizeof(bmfh));

		//bmp vkdlfauddmf skxksosms "BM"akzjrk dlTsmswl ghkrdls
		if (bmfh.bfType != (WORD)(('M' << 8) | 'B')) {
			return;
		}

		// bitmap info header open
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));
		ImageWidth = bih.biWidth;
		ImageHeight = bih.biHeight;
		depth = bih.biBitCount / 8;

		// palette cjfl
		if (depth == 1) {

			// palette exists
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);

		}

		isbmp = true;

	}
	else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0) {

		ImageWidth = 256;
		ImageHeight = 256;
		depth = 1;

	}

	// 기억 장소 할당
	inputImg = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));
	resultImg = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));

	for (int i = 0; i < ImageHeight; i++) {
		inputImg[i] = (unsigned char*)malloc(ImageWidth * depth);
		resultImg[i] = (unsigned char*)malloc(ImageWidth * depth);
	}

	if (!isbmp) {
		// 영상 데이터 읽기
		for (int i = 0; i < ImageHeight; i++) {
			ar.Read(inputImg[i], ImageWidth * depth);
		}
	}
	else {

		BYTE nu[4];
		int widthfile;
		widthfile = (ImageWidth * 8 + 31) / 32 * 4;

		for (int i = 0; i < ImageHeight; i++) {

			if (depth == 1) {
				ar.Read(inputImg[ImageHeight - 1 - i], ImageWidth * depth);
			}
			else {
				// BGR => RGB
				BYTE r, g, b;
				for (int j = 0; j < ImageWidth; j++) {
					ar.Read(&b, 1);
					ar.Read(&g, 1);
					ar.Read(&r, 1);
					inputImg[ImageHeight - 1 - i][3 * j + 0] = r;
					inputImg[ImageHeight - 1 - i][3 * j + 1] = g;
					inputImg[ImageHeight - 1 - i][3 * j + 2] = b;
				}
			}

			if ((widthfile - ImageWidth) != 0) {
				ar.Read(nu, (widthfile - ImageWidth) * depth);
			}
		}
	}

}


void CImageProcess20200778Doc::LoadSecondImageFile(CArchive& ar)
{
	// TODO: 여기에 구현 코드 추가.
	int maxValue;
	char type[16], buf[256];

	boolean isbmp = false;

	CFile* fp = ar.GetFile();
	CString fname = fp->GetFilePath();

	if (strcmp(strchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strchr(fname, '.'), ".pgm") == 0 || strcmp(strchr(fname, '.'), ".PGM") == 0) {

		ar.ReadString(type, 15); // P5

		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &ImageWidth, &ImageHeight);

		do {
			ar.ReadString(buf, 255);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0) { depth = 1; }
		else { depth = 3; }

	}
	else if (strcmp(strchr(fname, '.'), ".bmp") == 0 || strcmp(strchr(fname, '.'), ".BMP") == 0) {

		// bitmap file header open
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh, sizeof(bmfh));

		//bmp vkdlfauddmf skxksosms "BM"akzjrk dlTsmswl ghkrdls
		if (bmfh.bfType != (WORD)(('M' << 8) | 'B')) {
			return;
		}

		// bitmap info header open
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));
		ImageWidth = bih.biWidth;
		ImageHeight = bih.biHeight;
		depth = bih.biBitCount / 8;

		// palette cjfl
		if (depth == 1) {

			// palette exists
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);

		}

		isbmp = true;

	}
	else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0) {

		if (fp->GetLength() != 256 * 256) {
			AfxMessageBox("256 x 256 크기의 파일만 사용가능합니다.");
			return;
		}

		ImageWidth = 256;
		ImageHeight = 256;
		depth = 1;

	}

	// 기억 장소 할당
	inputImg2 = (unsigned char**)malloc(ImageHeight * sizeof(unsigned char*));

	for (int i = 0; i < ImageHeight; i++) {
		inputImg2[i] = (unsigned char*)malloc(ImageWidth * depth);
	}

	// 영상 데이터 읽기
	for (int i = 0; i < ImageHeight; i++) {
		ar.Read(inputImg2[i], ImageWidth * depth);
	}

	if (!isbmp) {
		// 영상 데이터 읽기
		for (int i = 0; i < ImageHeight; i++) {
			ar.Read(inputImg2[i], ImageWidth * depth);
		}
	}
	else {

		BYTE nu[4];
		int widthfile;
		widthfile = (ImageWidth * 8 + 31) / 32 * 4;

		for (int i = 0; i < ImageHeight; i++) {

			if (depth == 1) {
				ar.Read(inputImg2[ImageHeight - 1 - i], ImageWidth * depth);
			}
			else {
				// BGR => RGB
				BYTE r, g, b;
				for (int j = 0; j < ImageWidth; j++) {
					ar.Read(&b, 1);
					ar.Read(&g, 1);
					ar.Read(&r, 1);
					inputImg2[ImageHeight - 1 - i][3 * j + 0] = r;
					inputImg2[ImageHeight - 1 - i][3 * j + 1] = g;
					inputImg2[ImageHeight - 1 - i][3 * j + 2] = b;
				}
			}

			if ((widthfile - ImageWidth) != 0) {
				ar.Read(nu, (widthfile - ImageWidth) * depth);
			}
		}
	}

}