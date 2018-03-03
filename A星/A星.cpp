// A星.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Astart.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CAstar as;
	int map[40][40] = {};
	as.InitMapInfo((int*)map, 40, 40,1);
	as.InitCoord({ 10, 10 }, { 20, 20 });
	as.PrintWall();
	if (as.FindPath())
	{
		as.GetPath();
		as.PrintPath();
	}
	return 0;
}
