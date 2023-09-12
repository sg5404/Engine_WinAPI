#ifndef	  BBASIS_STD
#define	  BBASIS_STD

//-----------------------------------------------------------------------------
// Name: BBasisStd 
// Desc: 기본적으로 사용되는 헤더, 디파인
//-----------------------------------------------------------------------------

#include <windows.h>
#include <tchar.h>
#include <math.h>  
#include <string>
#include <map>
#include <list>
#include <vector>
#include <ctime>

using namespace std;

#define BASIS_WINDOW_NAME	TEXT("RaphaelFrameWork")
#define PI					3.141592654   

#pragma comment(lib, "winmm.lib") 

#define SCREEN_WIDTH	960
#define SCREEN_HEIGHT	720

#define SAFE_DELETE(p) { if(p) { delete(p); (p)=nullptr;}}

typedef struct tagFPOINT
{
	float x;
	float y;
}FPOINT;

typedef struct tagOBJSIZE
{
	int width;
	int height;
}OBJSIZE;

enum STAGE
{
	STAGE1,
	STAGE2,
	STAGE3,
	STAGE_COUNT
};

#endif // BBASIS_STD