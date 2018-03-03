#include "stdafx.h"
#include "Astart.h"
//=====优化处理==================================================================================






//CAstar::PVIR_INFO CAstar::m_pVir;





//=====优化处理==================================================================================

CAstar::CAstar()
{
}


CAstar::~CAstar()
{
}

void CAstar::InitMapInfo(int* pMap, int nHigh, int nWidth, int nBlock)
{
	m_pMap     = pMap;
	m_MapHigh  = nHigh;
	m_MapWidth = nWidth;
	m_Block    = nBlock;
//=====优化处理==================================================================================






	//m_pVir = new VIR_INFO[m_MapHigh*m_MapWidth]{};






//=====优化处理==================================================================================

	m_bInitMapInfo = true;
}

void CAstar::InitCoord(COORD codStar, COORD codEnd)
{
	m_Start = codStar;
	m_End   = codEnd;
	m_bInitCoordInfo = true;
}

bool CAstar::FindPath()
{
	//是否初始化完毕
	if (!m_bInitCoordInfo || !m_bInitMapInfo)
	{
		return false;
	}
/*
   1.  把起点坐标保存到Open表中
   2.1 判断Open表是否为空，空了说明此路不同
   2.2 找出Open表中F值最小的点
   2.3 进行扩散
   2.4 把扩散的点保存到Close表中，从Open表中删除
   2.5 判断新扩散出来的点是否合格
      2.5.1 是否是终点，是就直接返回
	        是不是障碍物
			是不是越界
			是否在Open表中
			是否在Close表中
   2.6 把合格的点存进Open表中
   2.7 重复2.1 -- 2.6
*/

	//清空Open和Close表
	m_Open.clear();
	m_Close.clear();

	NODE_INFO nodeStar;
	nodeStar.codSelf = m_Start;
	nodeStar.g = 0;
	nodeStar.SetH_F(m_Start, m_End);

	m_Open.push_back(nodeStar);

	//开始循环查找

	while (true)
	{
		//Open表是否为空
		if (m_Open.empty())
		{
			return false;
		}
		//找Open表中F值最小的点
		int nIndex = 0;
		for (int i = 1; i < m_Open.size();i++)
		{
			//如果当前的nIndex大于 i的 交换
			if (m_Open[nIndex].f > m_Open[i].f)
			{
				nIndex = i;
			}
		}

		//这里是以最小的点扩散
		//扩散
		NODE_INFO nodeNew[4]{ };

		//上
		nodeNew[0].codSelf.X = m_Open[nIndex].codSelf.X;
		nodeNew[0].codSelf.Y = m_Open[nIndex].codSelf.Y - 1;
		//下
		nodeNew[1].codSelf.X = m_Open[nIndex].codSelf.X;
		nodeNew[1].codSelf.Y = m_Open[nIndex].codSelf.Y + 1;
		//左
		nodeNew[2].codSelf.X = m_Open[nIndex].codSelf.X - 1;
		nodeNew[2].codSelf.Y = m_Open[nIndex].codSelf.Y ;
		//右
		nodeNew[3].codSelf.X = m_Open[nIndex].codSelf.X + 1;
		nodeNew[3].codSelf.Y = m_Open[nIndex].codSelf.Y;

		for (int i = 0; i < 4;i++)
		{
			nodeNew[i].codParent = m_Open[nIndex].codSelf;
			nodeNew[i].g = m_Open[nIndex].g + 1;
			nodeNew[i].SetH_F(nodeNew[i].codSelf, m_End);
			//方向
			nodeNew[i].codSelf.d = i;
		}
//=====优化处理==================================================================================



		//int x1 = m_Open[nIndex].codSelf.X;
		//int y1 = m_Open[nIndex].codSelf.Y;
		//m_pVir[y1 * m_MapWidth + x1].isClose = true;
		//m_pVir[y1 * m_MapWidth + x1].isOpen  = false;




//=====优化处理==================================================================================

		//把扩散过的点保存到Close表，并从Open表中删除
		m_Close.push_back(m_Open[nIndex]);
		m_Open.erase(m_Open.begin() + nIndex);

		//检测扩散出来的点是否合格，是否是终点
		for (int i = 0; i < 4;i++)
		{
			int x = nodeNew[i].codSelf.X;
			int y = nodeNew[i].codSelf.Y;

			//是不是终点
			if (nodeNew[i].codSelf == m_End)
			{
				m_Close.push_back(nodeNew[i]);
				return true;
			}
			//是否越界
			if (x <= 0 || y <= 0 ||
				x >= m_MapWidth  ||
				y >= m_MapHigh)
			{
				continue;
			}
			//是否是障碍物
			if (m_pMap[y*m_MapWidth + x] == m_Block)
			{
				continue;
			}

//=====优化处理==================================================================================




			////判断是否在Open表和Close表中
			//if (m_pVir[y * m_MapWidth + x].isClose ||
			//	m_pVir[y * m_MapWidth + x].isOpen)
			//{
			//	continue;
			//}

//=====优化处理==================================================================================


			//是否在Open表中
			
			
//=====没有优化处理===========================================================================
 			bool bRet = false;
 			for (int o = 0; o < m_Open.size();o++)
 			{
 				if (nodeNew[i].codSelf == m_Open[o].codSelf)
 				{
 					bRet = true;
 					break;
 				}
 			}
 			if (bRet)
 			{
 				continue;
 			}
			//是否在Close表中
 			for (int o = 0; o < m_Close.size(); o++)
 			{
 				if (nodeNew[i].codSelf == m_Close[o].codSelf)
 				{
 					bRet = true;
 					break;
 				}
 			}
 			if (bRet)
 			{
 				continue;
 			}
//=====没有优化处理================================================================================




			//将合格的点保存到Open表中
			m_Open.push_back(nodeNew[i]);




//=====优化处理=====================================================================================



			//m_pVir[y * m_MapWidth + x].isOpen = true;




//=====优化处理=====================================================================================
		}

	}//while
}

void CAstar::GetPath()
{
	//回溯父节点
	m_Path.clear();//清空原来的路径
	int nSize = m_Close.size();
	int nIndex = nSize - 1;

	while (true)
	{
		for (int i = 0; i < nSize;i++)
		{
			if (m_Close[nIndex].codParent == m_Start)
			{
				return;
			}
			if (m_Close[nIndex].codParent == m_Close[i].codSelf)
			{
				m_Path.push_back(m_Close[i].codSelf);
				nIndex = i;
				break;
			}
		}
	}
}


void CAstar::PrintWall()
{
	PrintChar(m_Start.X, m_Start.Y, "S", 13);
	PrintChar(m_End.X, m_End.Y, "E", 13);
	m_pMap[m_Start.Y*m_MapWidth + m_Start.X] = 10;

	while (true)
	{
		DWORD dwRead;
		INPUT_RECORD ir;
		ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &ir, 1, &dwRead);
		if (ir.EventType == MOUSE_EVENT)
		{
			if (ir.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
			{
				if (ir.Event.MouseEvent.dwEventFlags == DOUBLE_CLICK)
				{
					break;
				}
				COORD cod = ir.Event.MouseEvent.dwMousePosition;
				m_pMap[cod.Y*m_MapWidth + cod.X / 2] = 1;
				PrintChar(cod.X / 2, cod.Y, "※", 14);
			}
		}
	}
}
void CAstar::PrintPath()
{
	for (int i = m_Path.size() - 1; i >= 0; i--)
	{
		PrintChar(m_Path[i].X, m_Path[i].Y, "@", 10);
	}
}
void CAstar::PrintChar(int x, int y, char* pStr, short color)
{
	DWORD dwWrite;
	COORD pos = { x * 2, y };
	int nLen = strlen(pStr);
	WORD* pColor = new WORD[nLen * 2];
	wmemset((wchar_t*)pColor, color, nLen * 2);
	WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE), pColor, nLen * 2, pos, &dwWrite);
	WriteConsoleOutputCharacterA(GetStdHandle(STD_OUTPUT_HANDLE), pStr, nLen, pos, &dwWrite);
	delete[] pColor;
	pColor = nullptr;
}