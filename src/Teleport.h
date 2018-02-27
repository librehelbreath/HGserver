// Teleport.h: interface for the CTeleport class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TELEPORT_H__4DD04B3D_03E2_4B54_9AF1_7BF4ED1F9510__INCLUDED_)
#define AFX_TELEPORT_H__4DD04B3D_03E2_4B54_9AF1_7BF4ED1F9510__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*
[CONFIG]

//---------NUM--NPC_NAME--------SOURCE_MAP------TARGET_MAP------X-------Y-------COST----MinLvl--MaxLvl--Side----bHunt---bNtrl---bCrmnl--
teleport = 1	William		cityhall_1	middleland	200	200	10000	30	100	aresden	1	1	0
teleport = 2	William		cityhall_2	middleland	200	200	10000	30	100	elvine	1	1	0

[END]

Teleport ������ �η� ����

Side   : all, aresden, elvine
bHunt  : ��ɲ۵� ��������		(0,1)
bNtrl  : �߸��� ��������		(0,1)
bCrmnl : �����ڵ� ��������		(0,1)

*/

#include <windows.h>

class CTeleport  
{
public:
	CTeleport();
	virtual ~CTeleport();

	char	m_cNpcname[21];
	char	m_cSourceMap[11];
	char	m_cTargetMap[11];
	int		m_iX, m_iY;
	int		m_iCost;
	int		m_iMinLvl;
	int		m_iMaxLvl;
	int		m_iSide;
	BOOL	m_bHunter;
	BOOL	m_bNetural;
	BOOL	m_bCriminal;
};

#endif // !defined(AFX_TELEPORT_H__4DD04B3D_03E2_4B54_9AF1_7BF4ED1F9510__INCLUDED_)
