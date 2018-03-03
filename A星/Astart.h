#pragma once
#include <vector>
using std::vector;
#include <windows.h>

class CAstar
{
public:
	CAstar();
	~CAstar();
	typedef struct _MY_COORD: public COORD
	{
		bool operator==(COORD cod)
		{
			return (X == cod.X) && (Y == cod.Y);
		}
		void operator=(COORD cod)
		{
			X = cod.X;
			Y = cod.Y;
		}
		int d; //方向（坦克的移动方向）
	}MY_COORD, *PMY_COORD;


	//节点的结构
	typedef struct _NODE_INFO 
	{
		int g; //移动损耗
		int h; //据终点最短距离
		int f; //g+h
		MY_COORD codSelf;  //自身坐标
		MY_COORD codParent;//父节点坐标（由谁扩散的）
		//NODE_INFO privor;
		void SetH_F(COORD cod1, COORD cod2)
		{
			h = abs(cod1.X - cod2.X) + abs(cod1.Y - cod2.Y);
			f = g + h;
		}
		/*void operator=(_NODE_INFO cod)
		{
			g = cod.g;
			h = cod.h;
			f = cod.h;
			codSelf = cod.codSelf;
			codParent = cod.codParent;
			privor = cod.privor;
		}*/

	}NODE_INFO, *PNODE_INFO;
	COORD m_Start; //起点坐标
	COORD m_End;   //终点坐标

	vector<NODE_INFO> m_Open;  //待扩散的点
	vector<NODE_INFO> m_Close; //扩散过的点
	vector<MY_COORD>  m_Path;  //最短路径

	int* m_pMap;      //地图的首地址
	int  m_MapHigh;   //地图的长
	int  m_MapWidth;  //地图的宽

	int m_Block;      //障碍物
	/*
	   1 2 3
	   4 5 6
	   7 8 9
	*/
	bool m_bInitMapInfo;    //是否初始化地图信息
	bool m_bInitCoordInfo;  //是否初始化起始坐标信息


	void InitMapInfo(int* pMap, int nHigh, int nWidth, int nBlock);
	void InitCoord(COORD codStar, COORD codEnd);

	bool FindPath(); //查找包含最短路径的点（得到Close表）
	void GetPath();  //获取最短路径


//=====优化处理==================================================================================
	//typedef struct _VIR_INFO
	//{
	//	char isOpen:  1; //表是否在Open表中
	//	char isClose: 1; //表示是否在CLose表中
	//	char rcieve:  6; //保留
	//}VIR_INFO, *PVIR_INFO;

	//static PVIR_INFO m_pVir; //指向虚拟地图的首地址

//=====优化处理==================================================================================
	void PrintWall();
	void PrintPath();
	void PrintChar(int x, int y, char* pStr, short color);
};

