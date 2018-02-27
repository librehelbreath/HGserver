// TeleportLoc.h: interface for the CTeleportLoc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TELEPORTLOC_H__D4288400_F8C0_11D2_9B6C_00001C7030A6__INCLUDED_)
#define AFX_TELEPORTLOC_H__D4288400_F8C0_11D2_9B6C_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>

class CTeleportLoc  
{
public:
	CTeleportLoc(); 
	virtual ~CTeleportLoc();
												  
	short m_sSrcX, m_sSrcY;

	char  m_cDestMapName[11],  m_cDir;
	char  m_cDestMapName2[11];
	short m_sDestX,  m_sDestY;
	short m_sDestX2, m_sDestY2;

	int   m_iV1;			// Guild ID
	int	  m_iV2;			// 전면전시 소환된 건물 수

	// 2002-12-24 전면전시 소환할 수 있는 (건물 수를 제외한) NPC의 수를 제한한다.(대만 요청)
	int   m_iNumSummonNpc;	// 전면전시 소환된 NPC 수 (건물수는 제외한 것이다.)

	DWORD m_dwTime, m_dwTime2;

};

#endif // !defined(AFX_TELEPORTLOC_H__D4288400_F8C0_11D2_9B6C_00001C7030A6__INCLUDED_)
