// Npc.cpp: implementation of the CNpc class.
//
//////////////////////////////////////////////////////////////////////

#include "Npc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNpc::CNpc(char * pName5)
{
 int i;
	
	ZeroMemory(m_cName, sizeof(m_cName));
	memcpy(m_cName, pName5, 5);
	
	for (i = 0; i < DEF_MAXWAYPOINTS; i++)			  
		m_iWayPointIndex[i] = -1;
	
	for (i = 0; i < DEF_MAXMAGICEFFECTS; i++) 
		m_cMagicEffectStatus[i]	= 0;

	m_bIsSummoned       = FALSE;
	m_bIsPermAttackMode = FALSE;

	m_dwRegenTime = NULL;
	m_bIsKilled   = FALSE;

	m_sOriginalType      = NULL;
	m_iSummonControlMode = NULL;
	
	m_cAttribute = NULL;
	m_iAbsDamage = NULL;
	m_sStatus    = NULL;
	m_sAppr2     = NULL;

	m_iAttackRange    = 1;
	m_cSpecialAbility = 0;

	m_iBuildCount = 0;
	m_iManaStock  = 0;

	m_bIsMaster  = FALSE;
	m_iGuildGUID = NULL;

	m_iV1 = 0;

	m_iNpcCrops = 0; //v2.19 2002-12-16 농사 스킬 관련
	m_iCropsSkillLV = 0;	//v2.19 2002-12-16 농사 스킬 관련

	// 2002-09-17 #1
	m_iNpcitemMax = 0;
}

CNpc::~CNpc()
{

}

// 2002-09-06 #1
CNpcItem::CNpcItem()
{
	ZeroMemory(m_cName, sizeof(m_cName));
	m_sItemID = 0;							// 2002-09-09 #1
	m_sFirstProbability = 0 ;
	m_cFirstTargetValue = NULL;
	m_sSecondProbability = 0 ;
	m_cSecondTargetValue = NULL;
}