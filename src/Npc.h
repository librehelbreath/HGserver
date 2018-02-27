// Npc.h: interface for the CNpc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPC_H__6F7A5C80_A709_11D2_B143_00001C7030A6__INCLUDED_)
#define AFX_NPC_H__6F7A5C80_A709_11D2_B143_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include <windows.h>
#include <winbase.h>
#include "Magic.h"
#include <vector>

#define DEF_MAXWAYPOINTS			10

#define DEF_MOVETYPE_STOP			0		// 정지해 있는다. 초기화된 NPC의 기본 행동.
#define DEF_MOVETYPE_SEQWAYPOINT	1		// 이동경로를 순차적으로 이동. 맨 마지막 이동경로에서 해당 행동을 계속한다.
#define DEF_MOVETYPE_RANDOMWAYPOINT	2		// 이동경로를 랜덤하게 선택하여 움직인다.
#define DEF_MOVETYPE_FOLLOW			3		// 특정 대상을 따라 움직인다. 
#define DEF_MOVETYPE_RANDOMAREA		4		// 지정된 영역 안에서 랜덤한 곳으로 움직인다.
#define DEF_MOVETYPE_RANDOM			5		// 맵 내의 아무영역으로나 움직인다.
#define DEF_MOVETYPE_GUARD			6		// 처음 생성될 당시의 위치에 정지해 있으나 목표물 발견시는 추격한다.

#define DEF_BEHAVIOR_STOP			0
#define DEF_BEHAVIOR_MOVE			1
#define DEF_BEHAVIOR_ATTACK			2
#define DEF_BEHAVIOR_FLEE			3
#define DEF_BEHAVIOR_DEAD			4

#define DEF_ATTRIBUTE_EARTH			1
#define DEF_ATTRIBUTE_AIR			2
#define DEF_ATTRIBUTE_FIRE			3
#define DEF_ATTRIBUTE_WATER			4

// 2002-09-06 #1
class CNpcItem
{
 public :
	CNpcItem() ;

	char  m_cName[21];
	short m_sItemID;				// 2002-09-09 #1 Item ID
	short m_sFirstProbability;
	char  m_cFirstTargetValue;
	short m_sSecondProbability;
	char  m_cSecondTargetValue;
};


class CNpc  
{
public:

	CNpc(char * pName5);
	virtual ~CNpc();

	char  m_cNpcName[21]; // NPC의 이름. 사람 이름같은 것
	
	char  m_cName[6];	// 이 이름은 프로그램을 위한 식별자임
	char  m_cMapIndex;
	short m_sX, m_sY;
	short m_dX, m_dY;
	short m_vX, m_vY;
	int   m_tmp_iError;
	RECT  m_rcRandomArea;	// MOVETYPE_RANDOMAREA일때 영역좌표

	char  m_cDir;
	char  m_cAction;
	char  m_cTurn;

	short m_sType;
	short m_sOriginalType;
	short m_sAppr2;
	short m_sStatus;

	DWORD m_dwTime;
	DWORD m_dwActionTime;
	DWORD m_dwHPupTime, m_dwMPupTime;
	DWORD m_dwDeadTime, m_dwRegenTime;

	int  m_iHP;						// Hit Point 
	int  m_iExp;                    // 죽였을 경우 얻는 경험치. ExpDice에 의해 결정된다.

	int  m_iHitDice;				// 몬스터의 Hit Dice. 이것에 의해 HP가 결정된다.
	int  m_iDefenseRatio;			// Defense Ratio
	int  m_iHitRatio;				// HitRatio
	int  m_iMagicHitRatio;			// v1.4 마법 공격 Ratio
	int  m_iMinBravery;			    // 최소 용감치 
	int  m_iExpDice;				// 죽었을 경우 얻게되는 경험치 주사위 굴림 X dice 4
		
	char m_cSide;					// NPC가 속한 팀 
	char m_cActionLimit;            // 이 값이 1이면 Move만 가능하며 죽지도 않는다.  이 값이 2면 움직이지도 않으며 죽지도 않는다. 3이면 Dummy다. 맞는 역할, 
	                                // 4면 에너지 스피어, 5면 건축물   

	char m_cSize;					// 0: Small-Medium 1: Large
	char m_cAttackDiceThrow;		// 공격치 주사위 던지는 회수 
	char m_cAttackDiceRange;		// 공격치 주사위 범위 
	char m_cAttackBonus;			// 공격 보너스 
	char m_cBravery;				// NPC의 용감도 
	char m_cResistMagic;			// 마법 저항 
	char m_cMagicLevel;				// 마법 레벨 
	char m_cDayOfWeekLimit;		    // 생성시 날짜 제한 
	char m_cChatMsgPresence;		// 연결된 Chat Msg 존재유무 
	int  m_iMana;                   // 최대값은 MagicLevel*30
	int  m_iMaxMana;				// v1.4 새로 추가된 것들.
																    
	char  m_cMoveType;				// NPC의 이동경로 방식 
	char  m_cBehavior;				// NPC의 행동 
	short m_sBehaviorTurnCount;		// 행동 카운트 
	char  m_cTargetSearchRange;		// NPC공격목표 검색 범위 

	int   m_iFollowOwnerIndex;		// NPC가 따라가고 있는 객체 인덱스 
	char  m_cFollowOwnerType;		// 따라가는 객체의 종류 (NPC or Player)
	BOOL  m_bIsSummoned;            // 소환된 NPC라면 HP가 오르지 않는다. 
	DWORD m_dwSummonedTime;			// 소환몹이 생성시간 

	int   m_iTargetIndex;			// NPC의 공격목표 인덱스
	char  m_cTargetType;			// 공격목표의 종류 (NPC or Player)
	char  m_cCurWaypoint;			// 현재 이동위치 
	char  m_cTotalWaypoint;			// 총 이동위치 갯수 

	int   m_iSpotMobIndex;			// spot-mob-generator에서 만들어졌다면 인덱스를 저장 
	int   m_iWayPointIndex[DEF_MAXWAYPOINTS+1];
	char  m_cMagicEffectStatus[DEF_MAXMAGICEFFECTS];

	BOOL  m_bIsPermAttackMode;		// 이 플래그가 활성화 되어 있으면 공격도중 목표를 바꾸지 않는다.
   	int   m_iNoDieRemainExp;		// 죽지 않고 명중시에 얻을 수 있는 경험치 
	int   m_iAttackStrategy; 		// 전투 교리 인공지능 타입  
	int   m_iAILevel;				// 지능 레벨 

	int   m_iAttackRange;			// 공격 범위 1이상이면 원거리 공격이 가능하다는 것 
	/*
		AI-Level 
			1: 보통 행동 
			2: 에너지가 가장 낮은 목표물을 추적 
			3: 마법 보호중인 목표물 마법 공격대상에서 제외 
	*/
	int   m_iAttackCount;			// 연속 공격 동작 횟수 카운트 
	BOOL  m_bIsKilled;


	int   m_iLastDamage;			// 마지막 죽기 전에 얻은 대미지. 대미지가 너무 크면 연금술 재료가 떨어지지 않는다.
	int   m_iSummonControlMode;		// 소환몹 조정 모드: 0이면 Free, 1 Hold 2 Tgt 
	char  m_cAttribute;				// 마법 속성:  땅 1 하늘 2 불 3 물 4  
	int   m_iAbsDamage;				// 양수면 마법 대미지 절감률, 음수면 물리 대미지 절감률 

	int   m_iItemRatio;				// 특수 아이템 확률 
	int   m_iAssignedItem;			// 할당된 아이템 

	char  m_cSpecialAbility;		// 특수 능력 0: 없음  

									/*
case 0: break;
case 1:  "Penetrating Invisibility"
case 2:  "Breaking Magic Protection"
case 3:  "Absorbing Physical Damage"
case 4:  "Absorbing Magical Damage"
case 5:  "Poisonous"
case 6:  "Extremely Poisonous"
case 7:  "Explosive"
case 8:  "Hi-Explosive" 

 만약 이 값이 60보다 크면 NPC의 효과와는 무관하므로 무시한다.
									*/

	int	  m_iBuildCount;			// 가드 타워등 구조물인 경우 완성될 때까지 남은 곡괭이질 횟수를 의미. 초기값은 m_iMinBravery이다.
									// 이 값이 0이어야만 동작을 한다.
	int   m_iManaStock;				// 그랜드 매직 제네레이터의 경우 마나축적량 
	BOOL  m_bIsMaster;				// 마스터 몹인지의 여부 
	int   m_iGuildGUID;				// 전쟁용 유니트인 경우 소환자의 길드 아이디가 입력된다.

	int   m_iV1;

	// 2002-09-06 #1
	std::vector<CNpcItem>		m_vNpcItem;

	// 2002-09-17 #1
	int		m_iNpcitemType;		// 1 : 일반   (아이템이 나오지 않을 수 있다.) 
								// 2 : 특수 몬스터 (타이거웜, 헬클라우 등)

	int		m_iNpcitemMax;		// npcitem type이 2일때 dice를 돌릴 최대 값

	int		m_iNpcCrops;		//v2.19 2002-12-16 농사 스킬 ::농작물 번호 :: 0이면 농작물이 아니다.
	int		m_iCropsSkillLV;		//v2.19 2002-12-16 농사 스킬 ::농작물의 레벨
};

#endif // !defined(AFX_NPC_H__6F7A5C80_A709_11D2_B143_00001C7030A6__INCLUDED_)
