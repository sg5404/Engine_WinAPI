#include "BImage.h"

DWORD BImage::m_TransparentColor = RGB(255, 0, 255);

BImage::BImage() : m_BitmapHandle(nullptr)
{
	memset(&m_BitmapInfo, 0, sizeof(m_BitmapInfo));
}

BImage::BImage(TCHAR* strLoadFile) : BImage()
{
	this->Load(strLoadFile);
}

BImage::~BImage()
{
	if (!this->IsEmpty())
		DeleteObject(m_BitmapHandle);
}

bool BImage::IsEmpty() const
{
	return m_BitmapHandle == NULL;
}

bool BImage::Load(TCHAR* strLoadFile)
{
	m_BitmapHandle = (HBITMAP)LoadImage(GetModuleHandle(NULL), strLoadFile, IMAGE_BITMAP, 0, 0, 
					 LR_CREATEDIBSECTION | LR_LOADFROMFILE | LR_DEFAULTSIZE);

	if (this->IsEmpty())
		return false;

	GetObject(m_BitmapHandle, sizeof(m_BitmapInfo), &m_BitmapInfo);

	return true;
}

bool BImage::Load(HBITMAP BitmapHandle)
{
	if (!this->IsEmpty())
		DeleteObject(m_BitmapHandle);

	m_BitmapHandle = BitmapHandle;
	GetObject(m_BitmapHandle, sizeof(m_BitmapInfo), &m_BitmapInfo);

	return true;
}

bool BImage::Release()
{
	if (!this->IsEmpty())
		DeleteObject(m_BitmapHandle);

	return true;
}

HBITMAP BImage::GetBitmapHandle() const
{
	return m_BitmapHandle;
}

const BITMAP& BImage::GetBitmapInfo() const
{
	return m_BitmapInfo;
}

void BImage::DrawBitmap(HDC hdc, int x, int y, int width, int height) const
{
	if (width == 0)
		width = m_BitmapInfo.bmWidth;
	if (height == 0)
		height = m_BitmapInfo.bmHeight;

	this->drawBitmapByCropping(hdc, x, y, width, height, 0, 0, m_BitmapInfo.bmWidth, m_BitmapInfo.bmHeight);
}

void BImage::DrawAniRender(HDC hdc, int x, int y, BAnimation* ani)
{
	if (ani == nullptr)
		return;

	//x = x - ani->GetFrameWidth() / 2;
	//y = y - ani->GetFrameHeight() / 2;

	drawBitmapByCropping(hdc, x, y, ani->GetFrameWidth(), ani->GetFrameHeight(),
		ani->GetFramePos().x, ani->GetFramePos().y, ani->GetFrameWidth(), ani->GetFrameHeight());
}

void BImage::DrawLoopRender(HDC hdc, RECT drawArea, int offSetX, int offSetY)
{
	if (offSetX < 0) offSetX = 0;
	if (offSetY < 0) offSetY = 0;

	RECT rcDest = {};
	RECT rcSour = {};

	int drawAreaX = drawArea.left;					// 그려질 영역의 left
	int drawAreaY = drawArea.top;					// 그려질 영역의 top
	int drawAreaW = drawArea.right - drawAreaX;		// 그려질 영역의 넓이
	int drawAreaH = drawArea.bottom - drawAreaY;	// 그려질 영역의 높이

	int sourWidth = 0;

	rcSour.top = offSetY % m_BitmapInfo.bmHeight;
	rcSour.bottom = m_BitmapInfo.bmHeight;

	for (int x = 0; x < drawAreaW; x += sourWidth)
	{
		rcSour.left = (x + offSetX) % m_BitmapInfo.bmWidth;
		rcSour.right = m_BitmapInfo.bmWidth;

		sourWidth = rcSour.right - rcSour.left;

		if (x + sourWidth > drawAreaW)
		{
			rcSour.right -= (x + sourWidth) - drawAreaW;
			sourWidth = rcSour.right - rcSour.left;
		}

		rcDest.left = x + drawAreaX;
		rcDest.right = rcDest.left + sourWidth;

		int width = rcSour.right - rcSour.left;
		int height = rcSour.bottom - rcSour.top;

		drawBitmapByCropping(hdc, rcDest.left, rcDest.top, width, height,
								  rcSour.left, rcSour.top, width, height);
	}
}

void BImage::drawBitmapByCropping(HDC hdc, int x, int y, int width, int height, int sx, int sy, int sw, int sh) const
{
	HDC hMemDC;

	hMemDC = CreateCompatibleDC(hdc);

	SelectObject(hMemDC, m_BitmapHandle);

	GdiTransparentBlt(
		hdc, x, y, width, height,		
		hMemDC, sx, sy, sw, sh, GetTransparentColor());

	DeleteDC(hMemDC);
}

void BImage::SetTransparentColor(DWORD color)
{
	m_TransparentColor = color;
}

DWORD BImage::GetTransparentColor()
{
	return m_TransparentColor;
}