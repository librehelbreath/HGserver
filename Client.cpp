// Client.cpp: implementation of the CClient class.
//
//////////////////////////////////////////////////////////////////////

#include "Client.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClient::CClient(HWND hWnd)
{
 register int i;
	
	m_pXSock = NULL;
	m_pXSock = new class XSocket(hWnd, DEF_CLIENTSOCKETBLOCKLIMIT);
	m_pXSock->bInitBufferSize(DEF_MSGBUFFERSIZE);

	ZeroMemory(m_cProfile, sizeof(m_cProfile));
	strcpy(m_cProfile, "__________");

	ZeroMemory(m_cCharName, sizeof(m_cCharName));
	ZeroMemory(m_cAccountName, sizeof(m_cAccountName));
	ZeroMemory(m_cAccountPassword, sizeof(m_cAccountPassword));

	ZeroMemory(m_cGuildName, sizeof(m_cGuildName));
	ZeroMemory(m_cLocation, sizeof(m_cLocation));
	ZeroMemory(m_cMapName, sizeof(m_cMapName));
	
	strcpy(m_cLocation, "NONE");
	m_iGuildRank = -1;
	m_iGuildGUID = -1;

	m_bIsInitComplete = FALSE;

	m_cLU_Str = m_cLU_Int = m_cLU_Vit = m_cLU_Dex = m_cLU_Mag = m_cLU_Char = 0;

	// v1.432 사용하지 않는다.
	//m_iHitRatio_ItemEffect_SM = 0;
	//m_iHitRatio_ItemEffect_L  = 0;

	m_iEnemyKillCount = 0;
	m_iPKCount = 0;
	m_iRewardGold = 0;
	m_iCurWeightLoad = 0;

	m_bIsSafeAttackMode  = FALSE;

	// 아이템 장착 상태 초기화한 후 설정한다.
	for (i = 0; i < DEF_MAXITEMEQUIPPOS; i++) 
		m_sItemEquipmentStatus[i] = -1;
	
	// 아이템 리스트 초기화 
	for (i = 0; i < DEF_MAXITEMS; i++) {
		m_pItemList[i]       = NULL;
		m_ItemPosList[i].x   = 40;
		m_ItemPosList[i].y   = 30;
		m_bIsItemEquipped[i] = FALSE;
	}
	m_cArrowIndex = -1;	// 화살 아이템 인덱스는 할당되지 않은 상태 

	// 맡겨논 아이템 리스트 초기화.
	for (i = 0; i < DEF_MAXBANKITEMS; i++) {
		m_pItemInBankList[i] = NULL;
	}

	// Magic - Skill 숙련도 리스트 초기화 
	for (i = 0; i < DEF_MAXMAGICTYPE; i++)
		m_cMagicMastery[i] = NULL;
	
	for (i = 0; i < DEF_MAXSKILLTYPE; i++)
		m_cSkillMastery[i] = NULL;

	for (i = 0; i < DEF_MAXSKILLTYPE; i++) {
		m_bSkillUsingStatus[i] = FALSE;
		m_iSkillUsingTimeID[i] = NULL;
	}

	// testcode
	m_cMapIndex = -1;
	m_sX = -1;
	m_sY = -1;
	m_cDir = 5;
	m_sType   = 0;
	m_sOriginalType = 0;
	m_sAppr1  = 0;
	m_sAppr2  = 0;
	m_sAppr3  = 0;
	m_sAppr4  = 0;
	m_iApprColor = 0; // v1.4
	m_sStatus = 0;

	m_cSex  = 0;
	m_cSkin = 0;
	m_cHairStyle  = 0;
	m_cHairColor  = 0;
	m_cUnderwear  = 0;

	m_cAttackDiceThrow_SM = 0;	// 공격치 주사위 던지는 회수 @@@@@@@@@@@@@
	m_cAttackDiceRange_SM = 0;
	m_cAttackDiceThrow_L = 0;	// 공격치 주사위 던지는 회수 @@@@@@@@@@@@@
	m_cAttackDiceRange_L = 0;
	m_cAttackBonus_SM    = 0;
	m_cAttackBonus_L     = 0;
	
	// 플레이어의 소속 마을에 따라서 사이드가 결정되며 이것을 보고 NPC가 공격여부를 결정할 것이다. 
	m_cSide = 0;

	m_iHitRatio = 0;
	m_iDefenseRatio = 0;
	
	for (i = 0; i < DEF_MAXITEMEQUIPPOS; i++) m_iDamageAbsorption_Armor[i]  = 0;
	m_iDamageAbsorption_Shield = 0;

	// v2.20 2002-12-28 3주년 기념반지 버그 수정 
	m_iHPstock = 0;
	m_iHPStatic_stock = 0 ;

	m_bIsKilled = FALSE;

	for (i = 0; i < DEF_MAXMAGICEFFECTS; i++) 
		m_cMagicEffectStatus[i]	= 0;

	m_iWhisperPlayerIndex = -1;
	ZeroMemory(m_cWhisperPlayerName, sizeof(m_cWhisperPlayerName));
	
	m_iHungerStatus  = 100;  // 최대값은 100
	
	m_bIsWarLocation = FALSE;
	
	m_bIsPoisoned    = FALSE;
	m_iPoisonLevel   = NULL;

	m_iAdminUserLevel  = 0;
	m_iRating          = 0;
	m_iTimeLeft_ShutUp = 0;
	m_iTimeLeft_Rating = 0;
	m_iTimeLeft_ForceRecall  = 0;
	m_iTimeLeft_FirmStaminar = 0;

	m_bIsOnServerChange  = FALSE;

	m_iExpStock = 0;

	m_iAllocatedFish = NULL;
	m_iFishChance    = 0;

	ZeroMemory(m_cIPaddress, sizeof(m_cIPaddress)); 
	m_bIsOnWaitingProcess = FALSE;

	m_iSuperAttackLeft  = 0;
	m_iSuperAttackCount = 0;

	m_sUsingWeaponSkill = 5; // 기본적으로 맨손격투 

	m_iManaSaveRatio   = 0;
	m_iAddResistMagic  = 0;
	m_iAddPhysicalDamage = 0;
	m_iAddMagicalDamage  = 0;
	m_bIsLuckyEffect     = FALSE;
	m_iSideEffect_MaxHPdown = 0;

	m_iAddAbsAir   = 0;	// 속성별 대미지 흡수
	m_iAddAbsEarth = 0;
	m_iAddAbsFire  = 0;
	m_iAddAbsWater = 0;

	m_iComboAttackCount = 0;
	m_iDownSkillIndex   = -1;

	m_iMagicDamageSaveItemIndex = -1;

	m_sCharIDnum1 = m_sCharIDnum2 = m_sCharIDnum3 = 0;
	
	m_iPartyRank = -1; // v1.42
	m_iPartyMemberCount = 0;
	m_iPartyGUID        = 0;

	for (i = 0; i < DEF_MAXPARTYMEMBERS; i++) {
		m_stPartyMemberName[i].iIndex = 0;
		ZeroMemory(m_stPartyMemberName[i].cName, sizeof(m_stPartyMemberName[i].cName));
	}

	m_iAbuseCount     = 0;
	m_bIsBWMonitor    = FALSE;
	m_bIsExchangeMode = FALSE;

	// v1.4311-3 추가 변수 초기화 사투장 예약 관련 변수 
    m_iFightZoneTicketNumber =	m_iFightzoneNumber = m_iReserveTime = 0 ;            

	m_iPenaltyBlockYear = m_iPenaltyBlockMonth = m_iPenaltyBlockDay = 0; // v1.4

	m_iExchangeH = NULL;											// 교환할 대상의 인덱스 
	ZeroMemory(m_cExchangeName, sizeof(m_cExchangeName));			// 교환할 대상의 이름 
	ZeroMemory(m_cExchangeItemName, sizeof(m_cExchangeItemName));	// 교환할 아이템 이름 

	m_cExchangeItemIndex  = -1; // 교환할 아이템 인덱스 
	m_iExchangeItemAmount = 0;  // 교환할 아이템 갯수 

	m_bIsExchangeConfirm = FALSE;

	m_iQuest		 = NULL; // 현재 할당된 Quest 
	m_iQuestID       = NULL; // QuestID
	m_iAskedQuest	 = NULL; // 물어본 퀘스트 
	m_iCurQuestCount = NULL; // 현재 퀘스트 상태 

	m_iQuestRewardType	 = NULL; // 퀘스트 해결시 상품 종류 -> 아이템의 ID값이다.
	m_iQuestRewardAmount = NULL; // 상품 갯수 

	m_iContribution = NULL;			// 공헌도 
	m_bQuestMatchFlag_Loc = FALSE;  // 퀘스트 장소 확인용 플래그.
	m_bIsQuestCompleted   = FALSE;

	m_bIsNeutral      = FALSE;
	m_bIsObserverMode = FALSE;

	// 2000.8.1 이벤트 상품 수여 확인용 
	m_iSpecialEventID = 200081;

	m_iSpecialWeaponEffectType  = 0;	// 희귀 아이템 효과 종류: 0-None 1-필살기대미지추가 2-중독효과 3-정의의 4-저주의
	m_iSpecialWeaponEffectValue = 0;	// 희귀 아이템 효과 값

	m_iAddHP = m_iAddSP = m_iAddMP = 0; 
	m_iAddAR = m_iAddPR = m_iAddDR = 0;
	m_iAddAbsPD = m_iAddAbsMD = 0;
	m_iAddCD = m_iAddExp = m_iAddGold = 0;
		
	m_iSpecialAbilityTime = DEF_SPECABLTYTIMESEC;		// DEF_SPECABLTYTIMESEC 초마다 한번씩 특수 능력을 쓸 수 있다.
	m_iSpecialAbilityType = NULL;
	m_bIsSpecialAbilityEnabled = FALSE;
	m_iSpecialAbilityLastSec   = 0;

	m_iSpecialAbilityEquipPos  = 0;

	m_iMoveMsgRecvCount   = 0;
	m_iAttackMsgRecvCount = 0;
	m_iRunMsgRecvCount    = 0;
	m_iSkillMsgRecvCount  = 0;

	m_bIsAdminCreateItemEnabled = FALSE;
	m_bIsAdminCommandEnabled = FALSE;   // v2.18 2002-10-15 중요 GM 명령어에 패스워드 추가 
	m_iAlterItemDropIndex = -1;

	m_iAutoExpAmount = 0;
	m_iWarContribution = 0;

	m_dwMoveLAT = m_dwRunLAT = m_dwAttackLAT = 0;

	m_dwInitCCTimeRcv = 0;
	m_dwInitCCTime = 0;

	ZeroMemory(m_cLockedMapName, sizeof(m_cLockedMapName));
	strcpy(m_cLockedMapName, "NONE");
	m_iLockedMapTime   = NULL;
	m_iDeadPenaltyTime = NULL;

	m_iCrusadeDuty  = NULL;
	m_dwCrusadeGUID = NULL;

	for (i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++) {
		m_stCrusadeStructureInfo[i].cType = NULL;
		m_stCrusadeStructureInfo[i].cSide = NULL;
		m_stCrusadeStructureInfo[i].sX = NULL;
		m_stCrusadeStructureInfo[i].sY = NULL;
	}
	m_iCSIsendPoint = NULL;

	m_bIsSendingMapStatus = FALSE;
	ZeroMemory(m_cSendingMapName, sizeof(m_cSendingMapName));

	m_iConstructionPoint = NULL;

	ZeroMemory(m_cConstructMapName, sizeof(m_cConstructMapName));
	m_iConstructLocX = m_iConstructLocY = -1;

	m_dwFightzoneDeadTime = NULL;

	m_iPartyID = NULL;
	m_iPartyStatus = DEF_PARTYSTATUS_NULL;

	m_iReqJoinPartyClientH = NULL;
	ZeroMemory(m_cReqJoinPartyName, sizeof(m_cReqJoinPartyName));

	m_dwLastActionTime = NULL;
	m_bIsCheckingWhisperPlayer = FALSE;

	// v2.13 성후니 추가 DB 부하를 줄이기 위한 변수
	m_bIsBankModified = FALSE ;

	m_iGizonItemUpgradeLeft = 0;

	m_dwAttackFreqTime = m_dwMagicFreqTime = m_dwMoveFreqTime = NULL; // v2.171
	m_bIsMoveBlocked = FALSE; // v2.171
	m_bIsAttackModeChange = FALSE; // v2.172 2002-7-2
	m_iIsOnTown = FALSE;
	m_bIsOnShop = FALSE ; // v2.182 2002-11-15 사고 팔수 있는 곳인지 체크하는 변수 추가 
	m_bIsOnTower = FALSE ; // v2.20 2002-12-23 마법을 배울수 있는곳인지 체크 한다.
	m_bIsOnWarehouse = FALSE ; // v2.20 2002-12-23 창고인지 체크 한다.
	m_bIsHunter = FALSE ; // v2.182 2002-11-15 사냥군인지 체크하는 변수 추가 
	m_dwWarmEffectTime = NULL; // v2.172 
	m_bIsInBuilding = FALSE ;
}

CClient::~CClient()
{
 int i;
	
	if (m_pXSock != NULL) delete m_pXSock;
	for (i = 0; i < DEF_MAXITEMS; i++)
	if (m_pItemList[i] != NULL) {
		delete m_pItemList[i];
		m_pItemList[i] = NULL;
	}
}


BOOL CClient::bCreateNewParty()
{
 int i;

	if (m_iPartyRank != -1) return FALSE;

	m_iPartyRank = 0;
	m_iPartyMemberCount = 0;
	m_iPartyGUID = (rand() % 999999) + timeGetTime();

	for (i = 0; i < DEF_MAXPARTYMEMBERS; i++) {
		m_stPartyMemberName[i].iIndex = 0;
		ZeroMemory(m_stPartyMemberName[i].cName, sizeof(m_stPartyMemberName[i].cName));
	}

	return TRUE;
}
