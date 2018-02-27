// Tile.cpp: implementation of the CTile class.
//
//////////////////////////////////////////////////////////////////////

#include "Tile.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTile::CTile()
{ 
 int i;

	m_bIsMoveAllowed = TRUE;
	m_bIsTeleport    = FALSE;
	m_bIsWater       = FALSE;
	m_bIsFarmingAllowed = FALSE; //v2.19 2002-12-16 농사 스킬 관련
												   
	m_sOwner      = NULL;
	m_cOwnerClass = NULL;
	
	m_sDeadOwner      = NULL;
	m_cDeadOwnerClass = NULL;
	
	for (i = 0; i < DEF_TILE_PER_ITEMS; i++) 
		m_pItem[i] = NULL;
	m_cTotalItem = 0;

	m_wDynamicObjectID   = NULL;
	m_sDynamicObjectType = NULL;

	m_bIsTempMoveAllowed = TRUE;

	m_iOccupyStatus    = NULL;
	m_iOccupyFlagIndex = NULL;
	
	m_iAttribute  = NULL;
}

CTile::~CTile()
{
 int i;
	for (i = 0; i < DEF_TILE_PER_ITEMS; i++) 
	if (m_pItem[i] != NULL) delete m_pItem[i];
}
