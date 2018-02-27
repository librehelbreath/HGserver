// Tile.h: interface for the CTile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TILE_H__12609161_8060_11D2_A8E6_00001C7030A6__INCLUDED_)
#define AFX_TILE_H__12609161_8060_11D2_A8E6_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>
#include "Item.h"

#define DEF_TILE_PER_ITEMS	12

class CTile  
{												  
public:
	CTile();
	virtual ~CTile();

	char  m_cOwnerClass;		// DEF_OT_PLAYER / DEF_OT_NPC
	short m_sOwner;

	char  m_cDeadOwnerClass;	// DEF_OT_PLAYER / DEF_OT_NPC 죽어있는 플레이어는 이곳에 
	short m_sDeadOwner;

	class CItem * m_pItem[DEF_TILE_PER_ITEMS];
	char  m_cTotalItem;

	WORD  m_wDynamicObjectID;
	short m_sDynamicObjectType;
	DWORD m_dwDynamicObjectRegisterTime;

	BOOL  m_bIsMoveAllowed, m_bIsTeleport, m_bIsWater, m_bIsTempMoveAllowed;
	BOOL  m_bIsFarmingAllowed; //v2.19 2002-12-16 농사 스킬 관련 :: 농작물을 심을수 있는 곳이다.

	// 점령지 표시용 
	int   m_iOccupyStatus;    // Aresden이면 -값으로, Elvine이면 +로 더해진다. 총 합이 이 지역의 경향성 
	int   m_iOccupyFlagIndex; // 이 타일 위에 서 있는 점령깃발의 인덱스 

	// Crusade
	int	  m_iAttribute;		  // 타일의 상태 비트: 첫번째 비트(마법 보호) 두번째 비트(물리 공격 보호) 세번째 비트(안전지대)
	
	
};

#endif // !defined(AFX_TILE_H__12609161_8060_11D2_A8E6_00001C7030A6__INCLUDED_)
