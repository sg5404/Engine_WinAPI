#include "BCamera.h"

BCamera::BCamera()
{
	m_pCameraInfo = nullptr;
}

BCamera::~BCamera()
{
	
}

void BCamera::Init(int width, int height, int backWidth, int backHeight)
{
	if (m_pCameraInfo)
		Release();

	m_pCameraInfo = new CAMERA_INFO;
	m_pCameraInfo->width = width;
	m_pCameraInfo->height = height;
	m_pCameraInfo->backWidth = backWidth;
	m_pCameraInfo->backHeight = backHeight;
}

void BCamera::Release()
{
	SAFE_DELETE(m_pCameraInfo)
}

bool BCamera::CheckCameraX()
{
	if (!m_pCameraInfo)
		return false;

	if (m_pCameraInfo->x - m_pCameraInfo->width / 2 <= 0 ||
		m_pCameraInfo->x + m_pCameraInfo->width / 2 >= m_pCameraInfo->backWidth)
		return false;
	return true;
}

bool BCamera::CheckCameraY()
{
	if (!m_pCameraInfo)
		return false;

	if (m_pCameraInfo->y - m_pCameraInfo->height / 2 <= 0 ||
		m_pCameraInfo->y + m_pCameraInfo->height / 2 >= m_pCameraInfo->backHeight)
		return false;
	return true;
}
