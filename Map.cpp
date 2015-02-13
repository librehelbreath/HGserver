// Map.cpp: implementation of the CMap class.
//
//////////////////////////////////////////////////////////////////////

#include "Map.h"

extern void PutLogFileList(char * cStr);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMap::CMap(class CGame * pGame)
{
 int i, ix, iy;

	for (i = 0; i < DEF_MAXTELEPORTLOC; i++)
		m_pTeleportLoc[i] = NULL;

	for (i = 0; i < DEF_MAXWAYPOINTCFG; i++) {
		m_WaypointList[i].x = -1;
		m_WaypointList[i].y = -1;
	}

	for (i = 0; i < DEF_MAXMGAR; i++) {
		m_rcMobGenAvoidRect[i].top  = -1;
		m_rcMobGenAvoidRect[i].left = -1;
	}

	for (i = 0; i < DEF_MAXNMR; i++) {
		m_rcNoAttackRect[i].top  = -1;
		m_rcNoAttackRect[i].left = -1;
	}

	for (i = 0; i < DEF_MAXSPOTMOBGENERATOR; i++) {
		m_stSpotMobGenerator[i].bDefined = FALSE;
		m_stSpotMobGenerator[i].iTotalActiveMob = 0;
	}

	for (i = 0; i < DEF_MAXFISHPOINT; i++) {
		m_FishPointList[i].x = -1;
		m_FishPointList[i].y = -1;
	}

	for (i = 0; i < DEF_MAXMINERALPOINT; i++) {
		m_MineralPointList[i].x = -1;
		m_MineralPointList[i].y = -1;
	}

	for (i = 0; i < DEF_MAXINITIALPOINT; i++) {
		m_pInitialPoint[i].x = -1;
		m_pInitialPoint[i].y = -1;
	}
 
	for (i = 0; i < 1000; i++)
		m_bNamingValueUsingStatus[i] = FALSE;

	for (i = 0; i < DEF_MAXOCCUPYFLAG; i++)
		m_pOccupyFlag[i] = NULL;

	for (i = 0; i < DEF_MAXSTRATEGICPOINTS; i++)
		m_pStrategicPointList[i] = NULL;

	for (i = 0; i < DEF_MAXENERGYSPHERES; i++) {
		m_stEnergySphereCreationList[i].cType = NULL;
		m_stEnergySphereGoalList[i].cResult   = NULL;
	}
	
	m_iTotalActiveObject = 0;
	m_iTotalAliveObject  = 0;

	//m_sInitialPointX = 0;
	//m_sInitialPointY = 0;

	m_bIsFixedDayMode = FALSE;

	m_iTotalFishPoint = 0;
	m_iMaxFish = 0;
	m_iCurFish = 0;

	m_iTotalMineralPoint = 0;
	m_iMaxMineral = 0;
	m_iCurMineral = 0;

	m_pTile = NULL;

	m_cWhetherStatus = NULL;
	m_cType          = DEF_MAPTYPE_NORMAL;

	m_pGame = pGame;

	m_iLevelLimit = 0;
	m_iUpperLevelLimit = 0; // v1.4
	m_bMineralGenerator = FALSE;

	m_iTotalOccupyFlags = 0;
	
	m_bIsAttackEnabled = TRUE;
	m_cRandomMobGeneratorLevel = 0;

	m_bIsFightZone = FALSE;
	
	m_iTotalEnergySphereCreationPoint = 0;
	m_iTotalEnergySphereGoalPoint = 0;

	m_bIsEnergySphereGoalEnabled = FALSE;
	m_iCurEnergySphereGoalPointIndex = -1;

	for (ix = 0; ix < DEF_MAXSECTORS; ix++)
	for (iy = 0; iy < DEF_MAXSECTORS; iy++) {
		m_stSectorInfo[ix][iy].iNeutralActivity = 0;
		m_stSectorInfo[ix][iy].iAresdenActivity = 0;
		m_stSectorInfo[ix][iy].iElvineActivity  = 0;
		m_stSectorInfo[ix][iy].iMonsterActivity = 0;
		m_stSectorInfo[ix][iy].iPlayerActivity  = 0;

		m_stTempSectorInfo[ix][iy].iNeutralActivity = 0;
		m_stTempSectorInfo[ix][iy].iAresdenActivity = 0;
		m_stTempSectorInfo[ix][iy].iElvineActivity  = 0;
		m_stTempSectorInfo[ix][iy].iMonsterActivity = 0;
		m_stTempSectorInfo[ix][iy].iPlayerActivity  = 0;
	} 
	
	m_iMaxNx = m_iMaxNy = m_iMaxAx = m_iMaxAy = m_iMaxEx = m_iMaxEy = m_iMaxMx = m_iMaxMy = m_iMaxPx = m_iMaxPy = 0;

	for (i = 0; i < DEF_MAXSTRIKEPOINTS; i++) {
		m_stStrikePoint[i].dX  = 0;
		m_stStrikePoint[i].dY  = 0;
		m_stStrikePoint[i].iHP = 0;
		m_stStrikePoint[i].iMapIndex = -1;
		ZeroMemory(m_stStrikePoint[i].cRelatedMapName, sizeof(m_stStrikePoint[i].cRelatedMapName));
	}
	m_iTotalStrikePoints = 0;
	m_bIsDisabled = FALSE;

	for (i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++) {
		m_stCrusadeStructureInfo[i].cType = NULL;
		m_stCrusadeStructureInfo[i].cSide = NULL;
		m_stCrusadeStructureInfo[i].sX = NULL;
		m_stCrusadeStructureInfo[i].sY = NULL;
	}
	m_iTotalCrusadeStructures = 0;
}

CMap::~CMap()
{
	
 int i;
	
	if (m_pTile != NULL) 
		delete []m_pTile;	
 	
	for (i = 0; i < DEF_MAXTELEPORTLOC; i++)
		if (m_pTeleportLoc[i] != NULL) delete m_pTeleportLoc[i];

	for (i = 0; i < DEF_MAXOCCUPYFLAG; i++)
		if (m_pOccupyFlag[i] != NULL) delete m_pOccupyFlag[i];

	for (i = 0; i < DEF_MAXSTRATEGICPOINTS; i++)
		if (m_pStrategicPointList[i] != NULL) delete m_pStrategicPointList[i];
}

void CMap::SetOwner(short sOwner, char cOwnerClass, short sX, short sY)
{
 class CTile * pTile;	
	
	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return;
	
	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	pTile->m_sOwner      = sOwner;
	pTile->m_cOwnerClass = cOwnerClass;
}


void CMap::SetDeadOwner(short sOwner, char cOwnerClass, short sX, short sY)
{
 class CTile * pTile;	
	
	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return;
 
	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	pTile->m_sDeadOwner      = sOwner;
	pTile->m_cDeadOwnerClass = cOwnerClass;
}


void CMap::GetOwner(short * pOwner, char * pOwnerClass, short sX, short sY)
{
 class CTile * pTile;	

	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) {
		*pOwner      = NULL;	
		*pOwnerClass = NULL;
		return;	
	}

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	*pOwner      = pTile->m_sOwner;
	*pOwnerClass = pTile->m_cOwnerClass;
	
	if (pTile->m_sOwner == 0) *pOwnerClass = 0;
}


void CMap::GetDeadOwner(short * pOwner, char * pOwnerClass, short sX, short sY)
{
 class CTile * pTile;	

	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) {
		*pOwner      = NULL;	
		*pOwnerClass = NULL;
		return;	
	}

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	*pOwner      = pTile->m_sDeadOwner;
	*pOwnerClass = pTile->m_cDeadOwnerClass;
}

 								  
BOOL CMap::bGetMoveable(short dX, short dY, short * pDOtype)
{
 class CTile * pTile;	
	
	if ((dX < 20) || (dX >= m_sSizeX - 20) || (dY < 20) || (dY >= m_sSizeY - 20)) return FALSE;

	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);
	
	if (pDOtype != NULL) *pDOtype = pTile->m_sDynamicObjectType; // v1.4

	if (pTile->m_sOwner != NULL) return FALSE;
	if (pTile->m_bIsMoveAllowed == FALSE) return FALSE;
	if (pTile->m_bIsTempMoveAllowed == FALSE) return FALSE;
	
	return TRUE;
}

BOOL CMap::bGetIsMoveAllowedTile(short dX, short dY)
{
 class CTile * pTile;	
	
	if ((dX < 20) || (dX >= m_sSizeX - 20) || (dY < 20) || (dY >= m_sSizeY - 20)) return FALSE;

	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);
	
	if (pTile->m_bIsMoveAllowed == FALSE) return FALSE;
	if (pTile->m_bIsTempMoveAllowed == FALSE) return FALSE;
	
	return TRUE;
}

BOOL CMap::bGetIsTeleport(short dX, short dY)
{
 class CTile * pTile;	
	
	if ((dX < 14) || (dX >= m_sSizeX - 16) || (dY < 12) || (dY >= m_sSizeY - 14)) return FALSE;

	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);
	
	if (pTile->m_bIsTeleport == FALSE) return FALSE;
	
	return TRUE;
}

void CMap::ClearOwner(int iDebugCode, short sOwnerH, char cOwnerType, short sX, short sY)
{
 class CTile * pTile;	
	
	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return;

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);

	// 현 위치에 핸들이 일치하면 모두 클리어한다. 
	if ((pTile->m_sOwner == sOwnerH) && (pTile->m_cOwnerClass == cOwnerType)) {
		pTile->m_sOwner      = NULL;
		pTile->m_cOwnerClass = NULL;
	}

	// 
	if ((pTile->m_sDeadOwner == sOwnerH) && (pTile->m_cDeadOwnerClass == cOwnerType)) {
		pTile->m_sDeadOwner      = NULL;
		pTile->m_cDeadOwnerClass = NULL;
	}
}

void CMap::ClearDeadOwner(short sX, short sY)
{
 class CTile * pTile;	

	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return;	

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	pTile->m_sDeadOwner      = NULL;
	pTile->m_cDeadOwnerClass = NULL;
}

BOOL CMap::bSetItem(short sX, short sY, class CItem * pItem)
{
 class CTile * pTile;	
 register int i;
	
	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return NULL; 

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);

	// v1.4 마지막 타일에 아이템이 있다면 삭제시키고 이동한다. 
	if (pTile->m_pItem[DEF_TILE_PER_ITEMS-1] != NULL) 
		delete pTile->m_pItem[DEF_TILE_PER_ITEMS-1];
	else pTile->m_cTotalItem++;
	
	for (i = DEF_TILE_PER_ITEMS-2; i >= 0; i--) 
		pTile->m_pItem[i+1] = pTile->m_pItem[i];

	pTile->m_pItem[0] = pItem;
	//pTile->m_cTotalItem++;
	return TRUE;
}


class CItem * CMap::pGetItem(short sX, short sY, short * pRemainItemSprite, short * pRemainItemSpriteFrame, char * pRemainItemColor) //v1.4 color
{
 class CTile * pTile;	
 class CItem * pItem;
 register int i;
	
	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return NULL;

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	pItem =  pTile->m_pItem[0];
	if (pTile->m_cTotalItem == 0) return NULL;

	for (i = 0; i <= DEF_TILE_PER_ITEMS-2; i++)
		pTile->m_pItem[i] = pTile->m_pItem[i+1];
	pTile->m_cTotalItem--;
	pTile->m_pItem[pTile->m_cTotalItem] = NULL;
	
	if (pTile->m_pItem[0] == NULL) {
		*pRemainItemSprite      = 0;
		*pRemainItemSpriteFrame = 0;	
		*pRemainItemColor       = 0;
	}
	else
	{
		*pRemainItemSprite      = pTile->m_pItem[0]->m_sSprite;
		*pRemainItemSpriteFrame = pTile->m_pItem[0]->m_sSpriteFrame;
		*pRemainItemColor       = pTile->m_pItem[0]->m_cItemColor;
	}

	return pItem;
}


int CMap::iCheckItem(short sX, short sY)
{
 class CTile * pTile;	
 class CItem * pItem;
	
	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return NULL;

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	pItem =  pTile->m_pItem[0];
	if (pTile->m_cTotalItem == 0) return NULL;

	return pItem->m_sIDnum;
}


BOOL CMap::bIsValidLoc(short sX, short sY)
{
	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return FALSE;
	return TRUE;
}

BOOL CMap::bInit(char * pName)
{
 int i;
	// 맵파일을 로드한다.
	ZeroMemory(m_cName, sizeof(m_cName));
	strcpy(m_cName, pName);

	ZeroMemory(m_cLocationName, sizeof(m_cLocationName));

	if (_bDecodeMapDataFileContents() == FALSE) 
		return FALSE;	

	for (i = 0; i < DEF_MAXTELEPORTLOC; i++)
		m_pTeleportLoc[i] = NULL;

	return TRUE;
}

BOOL CMap::_bDecodeMapDataFileContents()
{
 HANDLE hFile;
 char  cMapFileName[256], cHeader[260], cTemp[100];
 DWORD dwFileSize, nRead;
 register int i, ix, iy;
 char * token, cReadMode;
 char seps[] = "= \t\n";
 class CStrTok * pStrTok = NULL;
 class CTile * pTile;
 short * sp;

	ZeroMemory(cMapFileName, sizeof(cMapFileName));
	strcat(cMapFileName, "mapdata\\");
	strcat(cMapFileName, m_cName);
	strcat(cMapFileName, ".amd");
	
	hFile = CreateFile(cMapFileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;
	dwFileSize = GetFileSize(hFile, NULL);
	
	ZeroMemory(cHeader, sizeof(cHeader));
	ReadFile(hFile, (char *)cHeader, 256, &nRead, NULL);

	// 헤더정보를 분석한다.

	// 먼저 널문자를 없앤다.
	for (i = 0; i < 256; i++) 
		if (cHeader[i] == NULL) cHeader[i] = ' ';

	cReadMode = 0;

	pStrTok = new class CStrTok(cHeader, seps);
	token = pStrTok->pGet();
	//token = strtok( cHeader, seps );   
	while( token != NULL )   {
			
		if (cReadMode != 0) {
			switch (cReadMode) {
			case 1:
				m_sSizeX = atoi(token);
				cReadMode = 0;
				break;
			case 2:
				m_sSizeY = atoi(token);
				cReadMode = 0;
				break;
			case 3:
				m_sTileDataSize = atoi(token);
				cReadMode = 0;
				break;
			}
		}	
		else {
			if (memcmp(token, "MAPSIZEX",8) == 0) cReadMode = 1;
			if (memcmp(token, "MAPSIZEY",8) == 0) cReadMode = 2;
			if (memcmp(token, "TILESIZE",8) == 0) cReadMode = 3; 
		}
			
		//token = strtok( NULL, seps );
		token = pStrTok->pGet();
	}

	// 크기에 맞게 타일을 생성한다.
	m_pTile = (class CTile *)new class CTile[m_sSizeX * m_sSizeY];

	// 타일의 정보를 읽어들인다.
	for (iy = 0; iy < m_sSizeY; iy++)
	for (ix = 0; ix < m_sSizeX; ix++) {
		ReadFile(hFile, (char *)cTemp, m_sTileDataSize, &nRead, NULL);	
		pTile = (class CTile *)(m_pTile + ix + iy*m_sSizeY);
		if ((cTemp[8] & 0x80) != 0) {
			// 갈수없는 속성이 세트되어 있다.
			 pTile->m_bIsMoveAllowed = FALSE;
		}
		else pTile->m_bIsMoveAllowed = TRUE;

		if ((cTemp[8] & 0x40) != 0) {
			// 텔레포트 속성이 세트되어 있다.
			 pTile->m_bIsTeleport = TRUE;
		}
		else pTile->m_bIsTeleport = FALSE;

		sp = (short *)&cTemp[0];
		if (*sp == 19) {
			// 물 타일이다. 
			 pTile->m_bIsWater = TRUE;
		}
		else pTile->m_bIsWater = FALSE;
	}

	CloseHandle(hFile);

	if (pStrTok != NULL) delete pStrTok;
	return TRUE;
}


BOOL CMap::bSearchTeleportDest(int sX, int sY, char * pMapName, int * pDx, int * pDy, char * pDir)
{
 register int i;

	for (i = 0; i < DEF_MAXTELEPORTLOC; i++)
	if ((m_pTeleportLoc[i] != NULL) && (m_pTeleportLoc[i]->m_sSrcX == sX) && (m_pTeleportLoc[i]->m_sSrcY == sY)) {
		// 같은 좌표를 갖는 텔레포트 위치를 찾았다. 	
		memcpy(pMapName, m_pTeleportLoc[i]->m_cDestMapName, 10);
		*pDx  = m_pTeleportLoc[i]->m_sDestX;
		*pDy  = m_pTeleportLoc[i]->m_sDestY;
		*pDir = m_pTeleportLoc[i]->m_cDir;
		return TRUE;
	}

	return FALSE;
}

void CMap::SetDynamicObject(WORD wID, short sType, short sX, short sY, DWORD dwRegisterTime)
{
 class CTile * pTile;	

	
	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return; 

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);

	pTile->m_wDynamicObjectID   = wID;
	pTile->m_sDynamicObjectType = sType;
	pTile->m_dwDynamicObjectRegisterTime = dwRegisterTime;
}

BOOL CMap::bGetDynamicObject(short sX, short sY, short *pType, DWORD *pRegisterTime, int * pIndex)
{
 class CTile * pTile;	

	
	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return FALSE; 

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);

	*pType = pTile->m_sDynamicObjectType;
	*pRegisterTime = pTile->m_dwDynamicObjectRegisterTime;
	if (pIndex != NULL) *pIndex = pTile->m_wDynamicObjectID;

	return TRUE;
}

int CMap::iGetEmptyNamingValue()
{
 register int i;

	for (i = 0; i < 1000; i++)
	if (m_bNamingValueUsingStatus[i] == FALSE) {

		m_bNamingValueUsingStatus[i] = TRUE;
		return i;
	}

	return -1;
}

void CMap::SetNamingValueEmpty(int iValue)
{
	m_bNamingValueUsingStatus[iValue] = FALSE;
}

BOOL CMap::bGetIsWater(short dX, short dY)
{
 class CTile * pTile;	
	
	if ((dX < 14) || (dX >= m_sSizeX - 16) || (dY < 12) || (dY >= m_sSizeY - 14)) return FALSE;

	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);
	
	if (pTile->m_bIsWater == FALSE) return FALSE;
	
	return TRUE;
}

int CMap::iAnalyze(char cType, int * pX, int * pY, int * pV1, int * pV2, int * pV3)
{

 
	// 현재 맵의 상황을 분석하여 쿼리에 맞는 위치를 반환한다. 
	switch (cType) {
	case 1:
		// 현재 교전이 벌어지고 있는 곳의 위치를 찾는다. 

		break;


	}

	return 0;
}

void CMap::SetTempMoveAllowedFlag(int dX, int dY, BOOL bFlag)
{
 class CTile * pTile;	
	
	if ((dX < 20) || (dX >= m_sSizeX - 20) || (dY < 20) || (dY >= m_sSizeY - 20)) return;

	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);
	pTile->m_bIsTempMoveAllowed = bFlag;
}

int CMap::iRegisterOccupyFlag(int dX, int dY, int iSide, int iEKNum, int iDOI)
{
 int i;

	if ((dX < 20) || (dX >= m_sSizeX - 20) || (dY < 20) || (dY >= m_sSizeY - 20)) return -1;
	
	for (i = 1; i < DEF_MAXOCCUPYFLAG; i++) 
	if (m_pOccupyFlag[i] == NULL) {
		// 값을 할당하고 반환.
		m_pOccupyFlag[i] = new class COccupyFlag(dX, dY, iSide, iEKNum, iDOI);
		if (m_pOccupyFlag == NULL) return -1;
		else return i;
	}
	
	return -1;
}



void CMap::ClearSectorInfo()
{
 int ix, iy;

	for (ix = 0; ix < DEF_MAXSECTORS; ix++)
	for (iy = 0; iy < DEF_MAXSECTORS; iy++) {
		m_stSectorInfo[ix][iy].iNeutralActivity = 0;
		m_stSectorInfo[ix][iy].iAresdenActivity = 0;
		m_stSectorInfo[ix][iy].iElvineActivity  = 0;
		m_stSectorInfo[ix][iy].iMonsterActivity = 0;
		m_stSectorInfo[ix][iy].iPlayerActivity  = 0;
	} 
}

void CMap::ClearTempSectorInfo()
{
 int ix, iy;

	for (ix = 0; ix < DEF_MAXSECTORS; ix++)
	for (iy = 0; iy < DEF_MAXSECTORS; iy++) {
		m_stTempSectorInfo[ix][iy].iNeutralActivity = 0;
		m_stTempSectorInfo[ix][iy].iAresdenActivity = 0;
		m_stTempSectorInfo[ix][iy].iElvineActivity  = 0;
		m_stTempSectorInfo[ix][iy].iMonsterActivity = 0;
		m_stTempSectorInfo[ix][iy].iPlayerActivity  = 0;
	} 
}

void CMap::_SetupNoAttackArea()
{
 int i, ix, iy;
 class CTile * pTile;	

	for (i = 0; i < DEF_MAXNMR; i++) {
		if ((m_rcNoAttackRect[i].top > 0)) {
			// No-Magic-Area가 정의되어 있다.
			for (ix = m_rcNoAttackRect[i].left; ix <= m_rcNoAttackRect[i].right; ix++)
			for (iy = m_rcNoAttackRect[i].top; iy <= m_rcNoAttackRect[i].bottom; iy++) {
				pTile = (class CTile *)(m_pTile + ix + iy*m_sSizeY);
				pTile->m_iAttribute = pTile->m_iAttribute | 0x00000004;		// 3번째 비트를 세팅한다. 안전지대 
			}
		}
		else if (m_rcNoAttackRect[i].top == -10) {
			// 전 영역 공격 금지다.	
			for (ix = 0; ix < m_sSizeX; ix++)
			for (iy = 0; iy < m_sSizeY; iy++) {
				pTile = (class CTile *)(m_pTile + ix + iy*m_sSizeY);
				pTile->m_iAttribute = pTile->m_iAttribute | 0x00000004;		// 3번째 비트를 세팅한다. 안전지대
			}
		}
	}
}

int CMap::iGetAttribute(int dX, int dY, int iBitMask)
{
 class CTile * pTile;

	if ((dX < 20) || (dX >= m_sSizeX - 20) || (dY < 20) || (dY >= m_sSizeY - 20)) return -1;

	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);
	return (pTile->m_iAttribute & iBitMask);
}

BOOL CMap::bAddCrusadeStructureInfo(char cType, short sX, short sY, char cSide)
{
 register int i;

	for (i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++)
	if (m_stCrusadeStructureInfo[i].cType == NULL) {
		m_stCrusadeStructureInfo[i].cType = cType;
		m_stCrusadeStructureInfo[i].cSide = cSide;
		m_stCrusadeStructureInfo[i].sX = sX;
		m_stCrusadeStructureInfo[i].sY = sY;

		m_iTotalCrusadeStructures++;
		return TRUE;
	}

	return FALSE;
}

BOOL CMap::bRemoveCrusadeStructureInfo(short sX, short sY)
{
 register int i;

	for (i = 0; i < DEF_MAXCRUSADESTRUCTURES; i++)
	if ((m_stCrusadeStructureInfo[i].sX == sX) && (m_stCrusadeStructureInfo[i].sY == sY)) {
		m_stCrusadeStructureInfo[i].cType = NULL;
		m_stCrusadeStructureInfo[i].cSide = NULL;
		m_stCrusadeStructureInfo[i].sX = NULL;
		m_stCrusadeStructureInfo[i].sY = NULL;
		goto RCSI_REARRANGE;
	}

	return FALSE;

RCSI_REARRANGE:;

	for (i = 0; i < DEF_MAXCRUSADESTRUCTURES-1; i++)
	if ((m_stCrusadeStructureInfo[i].cType == NULL) && (m_stCrusadeStructureInfo[i+1].cType != NULL)) {
		m_stCrusadeStructureInfo[i].cType = m_stCrusadeStructureInfo[i+1].cType;
		m_stCrusadeStructureInfo[i].cSide = m_stCrusadeStructureInfo[i+1].cSide;
		m_stCrusadeStructureInfo[i].sX = m_stCrusadeStructureInfo[i+1].sX;
		m_stCrusadeStructureInfo[i].sY = m_stCrusadeStructureInfo[i+1].sY;

		m_stCrusadeStructureInfo[i+1].cType = NULL;
		m_stCrusadeStructureInfo[i+1].cSide = NULL;
		m_stCrusadeStructureInfo[i+1].sX = NULL;
		m_stCrusadeStructureInfo[i+1].sY = NULL;
	}

	m_iTotalCrusadeStructures--;
	return TRUE;
}



void CMap::RestoreStrikePoints()
{
 int i;

	for (i = 0; i < DEF_MAXSTRIKEPOINTS; i++) {
		m_stStrikePoint[i].iInitHP = m_stStrikePoint[i].iHP;
	}
}
