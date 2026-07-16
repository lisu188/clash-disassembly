/* Generated recovered global-state owner. */
/* CLASH95_GENERATED_INCLUDES_BEGIN -- tools/gen_subsystem_headers.py; do not edit */
#include "../recovered_layout.h"
#include "state_internal.h"
#include "state_shared.h"
#include "state_local.h"
#include "../core/core_state.h"
#include "../render/render_state.h"
#include "../world/world_state.h"
#include "../units/units_state.h"
#include "../buildings/buildings_state.h"
#include "../battle/battle_state.h"
#include "../persistence/persistence_state.h"
#include "../strategic/strategic_state.h"
#include "../clips/clips_state.h"
#include "../media/media_state.h"
#include "../runtime/runtime_state.h"
#include "../render/render_api.h"
#include "../buildings/buildings_api.h"
#include "../strategic/strategic_api.h"
#include "../clips/clips_api.h"
#include "../media/media_api.h"
#include "../runtime/runtime_api.h"
#include "../recovered_legacy_imports.h"
/* CLASH95_GENERATED_INCLUDES_END */

char aJ_0[3] = "+j";

double g_Rules_AverageRoundingBias = 0.5;

CLASH95_INTERNAL uintptr_t g_QueenMarriageProposalWidgetTableBase;

int (* CAviDecompressor_FindColorConvertRoutine(int (**a1)(), int (**a2)()))();

int (* ProcParam_PushEvaluatedArgumentFrame(_DWORD *a1, int a2, int a3, int a4, double a5, int (*a6)(void)))(void);

_UNKNOWN Rules_HostTemple;

_UNKNOWN Rules_HostDigTreasure;

_UNKNOWN Rules_HostRoadExists;

_UNKNOWN Rules_HostRoadExistsNearby;

_UNKNOWN Rules_HostRoadExistsNearCastle;

_UNKNOWN Rules_HostRoadExistsToPort;

_UNKNOWN Rules_HostRoadExistsToCastle;

_UNKNOWN Rules_HostRoadExistsToTemple;

_UNKNOWN Rules_HostTroopInArmyRange;

_UNKNOWN Rules_HostBuildingInArmyRange;

_UNKNOWN Rules_HostDistanceFromObject;

_UNKNOWN Rules_HostTempleInArmyRange;

_UNKNOWN Rules_HostTempleOk;

_UNKNOWN Rules_HostMarch;

_UNKNOWN Rules_HostMarchToTemple;

_UNKNOWN Rules_HostMarchNear;

_UNKNOWN Rules_HostAttackTroop;

_UNKNOWN Rules_HostCaptureTroop;

_UNKNOWN Rules_HostHideTroop;

_UNKNOWN Rules_HostArmyExists;

_UNKNOWN Rules_HostUnitCountInTroop;

_UNKNOWN Rules_HostAttackBuilding;

_UNKNOWN Rules_HostFordExists;

_UNKNOWN Rules_HostBuildRoad;

_UNKNOWN Rules_HostBuildTrap;

_UNKNOWN Rules_HostUnitCanMove;

_UNKNOWN Rules_HostHealing;

_UNKNOWN Rules_HostTraining;

_UNKNOWN Rules_HostBurnBuildings;

_UNKNOWN Rules_HostUpgradeWall;

_UNKNOWN Rules_HostChangeTax;

_UNKNOWN Rules_HostRemoveLicence;

_UNKNOWN Rules_HostStartHealing;

_UNKNOWN Rules_HostStartTraining;

_UNKNOWN Rules_HostStartProduction;

_UNKNOWN Rules_HostTax;

_UNKNOWN Rules_HostIsLicence;

_UNKNOWN Rules_HostBuySchool;

_UNKNOWN Rules_HostBuyForge;

_UNKNOWN Rules_HostMoney;

_UNKNOWN Rules_HostWallStrength;

_UNKNOWN Rules_HostCastleStrength;

_UNKNOWN Rules_HostTurnNumber;

_UNKNOWN Rules_HostBuildCastle;

_UNKNOWN Rules_HostBuyLicence;

_UNKNOWN Rules_HostBuyBarracks;

_UNKNOWN Rules_HostBuyHospital;

_UNKNOWN Rules_HostTechLevel;

_UNKNOWN Rules_HostBuildingType;

_UNKNOWN Rules_HostPlayerStrength;

_UNKNOWN Rules_HostBuyWorkshop;

_UNKNOWN Rules_HostHappiness;

_UNKNOWN Rules_HostIsProduction;

_UNKNOWN Rules_HostPeasantCount;

_UNKNOWN Rules_HostIsMinimal;

_UNKNOWN Rules_HostCanBuyLicence;

_UNKNOWN Rules_HostLicenceIndex;

_UNKNOWN Rules_HostLicenceInd;

_UNKNOWN Rules_HostCanUpgradeWall;

_UNKNOWN Rules_HostTroopCount;

_UNKNOWN Rules_HostIsProductionAny;

_UNKNOWN Rules_HostLeadOutPeasants;

_UNKNOWN Rules_HostUnitsToSchool;

_UNKNOWN Rules_HostMaxTroopCount;

_UNKNOWN Rules_HostUnitInCastleExists;

_UNKNOWN Rules_HostUnitsToHospital;

_UNKNOWN Rules_HostLeadOutTroop;

_UNKNOWN Rules_HostLeadOutTroops;

_UNKNOWN Rules_HostCastleName;

_UNKNOWN Rules_HostEnterCastle;

_UNKNOWN Rules_HostJoinTroop;

_UNKNOWN Rules_HostRegroupTroops;

_UNKNOWN Rules_HostRegroupCastle;

_UNKNOWN Rules_HostArmyHeadcount;

_UNKNOWN Rules_HostArmyHasUnitsOfType;

_UNKNOWN Rules_HostCastleFreeSlotCount;

_UNKNOWN Rules_HostEnemyPowerAtWalls;

_UNKNOWN Rules_HostFindRoadNearCastle;

_UNKNOWN Rules_HostHasUnitsToHeal;

_UNKNOWN Rules_HostFindCastleForHealing;

_UNKNOWN Rules_HostGoToHealing;

_UNKNOWN Rules_HostPlagueInCastleExists;

_UNKNOWN Rules_HostPlagueInTroopExists;

_UNKNOWN Rules_HostDetachWeakUnits;

_UNKNOWN Rules_HostDetachUnitsOfType;

_UNKNOWN Rules_HostMarchAlongRoad;

_UNKNOWN Rules_HostFindBest;

_UNKNOWN Audio_MixMonoVoiceDispatch;

_UNKNOWN Audio_MixPannedVoiceDispatch;

_UNKNOWN Audio_SelectMixFormat1MonoDispatch;

_UNKNOWN Audio_SelectMixFormat1StereoDispatch;

_UNKNOWN Audio_SelectMixFormat2MonoDispatch;

_UNKNOWN Audio_SelectMixFormat2StereoDispatch;

_UNKNOWN Audio_SelectMixFormat3MonoDispatch;

_UNKNOWN Audio_SelectMixFormat3StereoDispatch;

_UNKNOWN Audio_SelectMixFormat4MonoDispatch;

_UNKNOWN Audio_SelectMixFormat4StereoDispatch;

_UNKNOWN Audio_SelectMixFormat5MonoDispatch;

_UNKNOWN Audio_SelectMixFormat5StereoDispatch;

void *g_Audio_MixMonoVoiceDispatchBase = &Audio_MixMonoVoiceDispatch;

void *g_Audio_MixPannedVoiceDispatchBase = &Audio_MixPannedVoiceDispatch;

void *g_Audio_SelectMixFormat1MonoDispatchBase = &Audio_SelectMixFormat1MonoDispatch;

void *g_Audio_SelectMixFormat1StereoDispatchBase = &Audio_SelectMixFormat1StereoDispatch;

void *g_Audio_SelectMixFormat2MonoDispatchBase = &Audio_SelectMixFormat2MonoDispatch;

void *g_Audio_SelectMixFormat2StereoDispatchBase = &Audio_SelectMixFormat2StereoDispatch;

void *g_Audio_SelectMixFormat3MonoDispatchBase = &Audio_SelectMixFormat3MonoDispatch;

void *g_Audio_SelectMixFormat3StereoDispatchBase = &Audio_SelectMixFormat3StereoDispatch;

void *g_Audio_SelectMixFormat4MonoDispatchBase = &Audio_SelectMixFormat4MonoDispatch;

void *g_Audio_SelectMixFormat4StereoDispatchBase = &Audio_SelectMixFormat4StereoDispatch;

void *g_Audio_SelectMixFormat5MonoDispatchBase = &Audio_SelectMixFormat5MonoDispatch;

void *g_Audio_SelectMixFormat5StereoDispatchBase = &Audio_SelectMixFormat5StereoDispatch;

tagRECT j____wcpp_4_fs_handler_rtn_ = { 50130921, 1413568256, 1397575491, -1144944303 };

_UNKNOWN strstr_;

void *g_Class_BsaveWriteUnknownSectionFn = (void *)0x487883;

_UNKNOWN strncat_;

int g_InputBackendMouseDataFormat[5] = { 24, 16, 2, 16, 7 };

int g_InputBackendKeyboardDataFormat[5] = { 24, 16, 2, 256, 256 };

int g_InputBackendJoystickDataFormat[5] = { 24, 16, 1, 80, 44 };

char aClash[7] = "CLASH\\";

char aGetreadincrZap[49] = "GetReadIncr: zapis na ekran nie zaimplementowany";

char aGetwriteincrZa[50] = "GetWriteIncr: zapis na ekran nie zaimplementowany";

char aDrawpixZapisNa[45] = "DrawPix: zapis na ekran nie zaimplementowany";

char aGetpixZapisNaE[44] = "GetPix: zapis na ekran nie zaimplementowany";

char aDrawlineZapisN[46] = "DrawLine: zapis na ekran nie zaimplementowany";

char aDrawrectZapisN[46] = "DrawRect: zapis na ekran nie zaimplementowany";

char aDrawboxZapisNa[45] = "DrawBox: zapis na ekran nie zaimplementowany";

char aDotboxZapisNaE[44] = "DotBox: zapis na ekran nie zaimplementowany";

char a_loadpalpcxS0x[25] = "_LoadPalPCX(\"%s\",0x%08x)";

char a_loadpalcolS0x[25] = "_LoadPalCOL(\"%s\",0x%08x)";

char aPal_grey_pcx[13] = "pal_grey.pcx";

CHAR Caption[] = "Clash";

char a_loadpcxS0x08x[31] = "_LoadPCX(\"%s\",0x%08x,0x%08x,%d";

char aDlxvscreenDraw[87] = "DLXVScreen::DrawSprite Cliped sprites to screen not implemented. but they could be :-)";

char aDlxmemscreenDr[76] = "DLXMemScreen::DrawSprite type 0: unknown type - %d,%d,0x%08x,%d,%d,%d,%d,%d";

char aDlxmemscreen_0[76] = "DLXMemScreen::DrawSprite type 1: unknown type - %d,%d,0x%08x,%d,%d,%d,%d,%d";

char aNotEnoughMemor[21] = "Not enough memory=%d";

char aNotEnoughMem_0[21] = "Not enough memory=%d";

char aNotEnoughFreeM[23] = "not enough free memory";

char aRestorescreenc[18] = "RestoreScreenCopy";

char aRemsc[6] = "RemSC";

char aRb_0[3] = "rb";

char aDlxspritesetDl[33] = "DLXSpriteSet::DLXSpriteSet(\"%s\")";

char aNotEnoughMem_1[21] = "Not enough memory=%d";

char aNotEnoughMem_2[21] = "Not enough memory=%d";

char aDlxspritesetSa[23] = "DLXSpriteSet::save(%s)";

char aWb[3] = "wb";

char aNotEnoughMem_7[21] = "Not enough memory=%d";

char aNotEnoughMem_8[21] = "Not enough memory=%d";

char aNotEnoughMe_15[21] = "Not enough memory=%d";

char aNotEnoughMe_16[21] = "Not enough memory=%d";

char aCannotConform2[43] = "Cannot conform 2 pal sprite with imploding";

char aConvertsprUnsu[39] = "ConvertSpr() - unsupported sprite type";

char aS[9] = "      %s";

char asc_4EC5AC[57] = "********************************************************";

char aWrong_2[6] = "wrong";

char aWrong_3[6] = "wrong";

char aWrong_4[6] = "wrong";

char aWrong_5[6] = "wrong";

char aWrong_6[6] = "wrong";

_UNKNOWN g_Building_FootprintTemplate_Type0;

char aStruktur[9] = "struktur";

_UNKNOWN g_Building_FootprintTemplate_Type1;

char aStruktur_0[9] = "struktur";

_UNKNOWN g_Building_FootprintTemplate_Type2;

char aStruktur_1[9] = "struktur";

char aTuraD[8] = "tura %d";

char aSetrhS08x_1[14] = "SetRH %s=%08x";

char aGraczSTwojaTur[22] = "GRACZ %s - TWOJA TURA";

char aPlayerSYourTur[22] = "PLAYER %s - YOUR TURN";

char aSpielerS[11] = "SPIELER %s";

char aUnsetrh08x_0[13] = "UnsetRH %08x";

char aNextPlayer[12] = "Next player";

char aPlayerD[10] = "player %d";

char aNextTurnD[14] = "Next turn: %d";

char aClipsMemoryD[17] = "CLIPS memory: %d";

char aUsedmemD_3[12] = "UsedMem: %d";

char aUnitsCacheEntr[24] = "Units cache entries: %d";

char aBuildingsCache[28] = "Buildings cache entries: %d";

char aAutoMovesBegin[17] = "Auto moves begin";

char aAutoMovesEnd[15] = "Auto moves end";

char aMainmap[8] = "mainmap";

char aSetrhS08x_0[14] = "SetRH %s=%08x";

char aUnsetrh08x[13] = "UnsetRH %08x";

char aKon_por1[9] = "kon_por1";

char aArama1[7] = "arama1";

char aPlaygame[11] = "PlayGame()";

char aStart[7] = "START:";

char aSetrhS08x[14] = "SetRH %s=%08x";

char aComputerplay[15] = "ComputerPlay()";

char aUnsetrh08x_1[13] = "UnsetRH %08x";

char aKoniecGryPoDTu[24] = "Koniec gry po %d turach";

char aPlaygameEnd[17] = "PlayGame() - end";

char aZwy02[6] = "zwy02";

char a_conformfont2p[21] = "_ConformFont2Pal(%d)";

char a_end[5] = "_end";

char aMenuDraw[11] = "MENU: Draw";

char aD[3] = "%d";

char aDD[6] = "%d/%d";

char aSetrhS08x_2[14] = "SetRH %s=%08x";

char aUnsetrh08x_2[13] = "UnsetRH %08x";

char aMenuHide[11] = "MENU: Hide";

char aUnit_createDDD[28] = "Unit_Create(%d,%d,%d,%d,%d)";

char aUnit_createE_0[23] = "Unit_Create() - ERROR1";

char aUnit_createErr[32] = "Unit_Create() - ERROR - duch %d";

char aUnit_createE_1[23] = "Unit_Create() - ERROR2";

char aUnit_createE_2[23] = "Unit_Create() - ERROR3";

char aUnit_createOk0[32] = "Unit_Create() - OK - 0x%08x, %d";

char aUnit_kill0x08x[18] = "Unit_Kill(0x%08x)";

char aUnit_moveDD[17] = "Unit_Move(%d,%d)";

char aUnitD0x08x[86] = "                                               Unit %d(0x%08x): (%d,%d), p:%d, hid:%d";

char a15sPl1dP[94] = "                                                   %15s pl:%1d pa:%2d q:%3d t:%3d m:%2d s:%2d";

char aLogallunits[12] = "LogAllUnits";

char aUnit_checklowm[42] = "Unit_CheckLowMorale(0x%08x) - buntuje sie";

char aUnit_checklo_0[45] = "Unit_CheckLowMorale(0x%08x) - rozwiazuje sie";

char aUnit_newturn[15] = "Unit_NewTurn()";

char aUnit_capture0x[28] = "Unit_Capture(0x%08x,0x%08x)";

char aUnitCreateNearbyUnitGroup[64] = "Unit_CreateNearbyUnitGroup(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)";

char aUnit_createn_0[41] = "Unit_CreateNearbyUnitGroup(...) - Error1";

char aUnit_createn_1[54] = "Unit_CreateNearbyUnitGroup(...) - return 0x%08x,%d,%d";

char aUnitscache_cle[17] = "UnitsCache_Clear";

char aUnits_go[10] = "units_go\\";

char a_s32[5] = ".s32";

char aUnits_i[9] = "units_i\\";

char a_i[3] = "_i";

char a_s32_0[5] = ".s32";

char aUnits_i_0[9] = "units_i\\";

char a_i_0[3] = "_i";

char a_s32_4[5] = ".s32";

char aUnits_i_1[9] = "units_i\\";

char a_i_1[3] = "_i";

char a_s32_5[5] = ".s32";

char aUnits_i_2[9] = "units_i\\";

char a_i_2[3] = "_i";

char a_pal[5] = ".pal";

char aUnits_at_1[10] = "units_at\\";

char a_a[3] = "_a";

char a_s32_3[5] = ".s32";

char aUnits_at[10] = "units_at\\";

char a_s[3] = "_s";

char a_s32_1[5] = ".s32";

char aUnits_at_0[10] = "units_at\\";

char aUnitSpritePaletteSuffix[3] = "_p";

char a_s32_2[5] = ".s32";

char aBiginfo_[9] = "biginfo.";

char a_gfx_1[5] = ".gfx";

char aUcatblad[9] = "ucatblad";

char aUnit_movetrack[31] = "Unit_MoveTrack(%d,%d,%d,%d,%d)";

char aNotEnoughMem_3[21] = "Not enough memory=%d";

char aNotEnoughMem_4[21] = "Not enough memory=%d";

char aNotEnoughMem_5[21] = "Not enough memory=%d";

char aNotEnoughMem_6[21] = "Not enough memory=%d";

char aUnit_movetra_1[25] = "Unit_MoveTrackNear(%d,%d,%d)";

char aUnit_movetra_0[32] = "Unit_MoveTrackToBuilding(%d,%d)";

char aUnit_movetra_3[34] = "Unit_MoveTrackNearBuilding(%d,%d)";

char aTrack_bridgeso[18] = "Pathing_EnableBridgeCrossings()";

char aTrack_bridge_0[19] = "Pathing_DisableBridgeCrossings()";

char aRandom_initSee[29] = "Random_Init(): seed = 0x%08x";

char aD_0[3] = "%d";

char aDD_0[6] = "%d,%d";

char aClash_log[10] = "clash.log";

char aBattle_log[11] = "battle.log";

char aA[2] = "a";

char aClash_log_0[10] = "clash.log";

char aA_1[2] = "a";

char aBattle_log_0[11] = "battle.log";

char a03d02d02d[16] = "%03d:%02d:%02d ";

char asc_4EDCFF[2] = "\n";

char aD_1[3] = "%d";

char aD_2[3] = "%d";

char aD_12[3] = "%d";

char aD_13[3] = "%d";

char aD_14[3] = "%d";

char aD_15[3] = "%d";

char aD_16[3] = "%d";

char aD_17[3] = "%d";

char aD_18[3] = "%d";

char aUnit_infoDD0x0[31] = "Unit_Info(%d,%d,0x%08x,0x%08x)";

char aD_19[3] = "%d";

char aD_20[3] = "%d";

char aUnit_attackDD[19] = "Unit_Attack(%d,%d)";

char aAtak_zas[9] = "atak_zas";

char aBattle[7] = "battle";

char aMainmap_0[8] = "mainmap";

char aChlop[6] = "chlop";

char aUnit_attackbui[27] = "Unit_AttackBuilding(%d,%d)";

char aAtak_zam[9] = "atak_zam";

char aMainmap_1[8] = "mainmap";

char aSetrhS08x_3[14] = "SetRH %s=%08x";

char aD_3[3] = "%d";

char aD_4[3] = "%d";

char aMale_0[5] = "male";

char aMale[5] = "male";

char aUnsetrh08x_3[13] = "UnsetRH %08x";

char aBuilding_newDD[31] = "Building_New(%d,%d,%d,%d,\"%s\")";

char aBuilding_stop0[22] = "Building_Stop(0x%08x)";

char aBuilding_build[33] = "Building_BuildFinished() - %d,%d";

char aBuilding_produ[45] = "Building_Production(0x%08x) - nowa jednostka";

char aBuilding_check[29] = "Player_UpdateTechnologyLevelFromSettlements(%d)";

char aD0x08xDDTDPDGD[52] = "%d(0x%08x): (%d,%d), t:%d, p:%d g:%d pop:%d bpa:%d ";

char aUDDDDDDDDDD[45] = "            u:%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,";

char aLogallbuilding[16] = "LogAllBuildings";

char aBuilding_newtu[19] = "Building_NewTurn()";

char aBuilding_getin[21] = "Building_GetInto(%d)";

char aSetrhS08x_5[14] = "SetRH %s=%08x";

char aUnsetrh08x_5[13] = "UnsetRH %08x";

char aSetrhS08x_4[14] = "SetRH %s=%08x";

char aUnsetrh08x_4[13] = "UnsetRH %08x";

char aStdrh_3[6] = "StdRH";

char aKeep_redraw[12] = "Keep_Redraw";

char aBuilding_bui_4[33] = "Building_BuildWorkshop() - %d,%d";

char aBuilding_bui_2[33] = "Building_BuildBarracks() - %d,%d";

char aBuilding_bui_3[33] = "Building_BuildHospital() - %d,%d";

char aBuilding_bui_1[31] = "Building_BuildSmiths() - %d,%d";

char aBuildingFindFreePlaceNear[37] = "Building_FindFreePlaceNear() - %d,%d";

char aBuildingTransfer[31] = "Building_Transfer(%d,%d,%d,%d)";

char aUnit_capturebu[28] = "Unit_CaptureBuilding(%d,%d)";

char aBuilding_destr[25] = "Building_Destroy(0x%08x)";

char aD_21[3] = "%d";

char aD_22[3] = "%d";

char aD_23[3] = "%d";

char aD_24[3] = "%d";

char aD_25[3] = "%d";

char aD_26[3] = "%d";

char aD_27[3] = "%d";

char aD_28[3] = "%d";

char aD_29[3] = "%d";

char aD_30[3] = "%d";

char aD_31[3] = "%d";

char aBudowaSzkola[14] = "budowa\\szkola";

char aBudowaWarszt_0[16] = "budowa\\warsztat";

char aBudowaBaraki[14] = "budowa\\baraki";

char aBudowaChrzesci[16] = "budowa\\chrzesci";

char aBudowaPoganie[15] = "budowa\\poganie";

char aBudowaKuznia[14] = "budowa\\kuznia";

char aNiszcz[7] = "niszcz";

char aD_42[3] = "%d";

char aD_43[3] = "%d";

char aD_44[3] = "%d";

char aD_45[3] = "%d";

char a03[3] = "03";

char a05[3] = "05";

char a09[3] = "09";

char a11_7[3] = "11";

char a12[3] = "12";

char a10[3] = "10";

char a07[3] = "07";

char a01_3[3] = "01";

char aZ_[4] = "\\z_";

char aM_gfx[6] = "m.gfx";

char a_gfx[5] = ".gfx";

char a04[3] = "04";

char a06[3] = "06";

char a08[3] = "08";

char a02[3] = "02";

char aZ__0[4] = "\\z_";

char aM_gfx_0[6] = "m.gfx";

char a_gfx_0[5] = ".gfx";

char aZ_13_tw_gfx[13] = "\\z_13_tw.gfx";

char asc_4EE6D4[11] = "!!!!!!!!!!";

char aSetrhS08x_6[14] = "SetRH %s=%08x";

char aCastleD[11] = "Castle(%d)";

char aCastle[7] = "castle";

char aZamek_1Anim_s3[17] = "zamek_1\\anim.s32";

char aDz_info_s32[12] = "dz_info.s32";

char aMap_pal_0[8] = "map.pal";

char aMap_pal_1[8] = "map.pal";

char aSetrhS08x_7[14] = "SetRH %s=%08x";

char aUnsetrh08x_7[13] = "UnsetRH %08x";

char aMainmap_2[8] = "mainmap";

char aUnsetrh08x_6[13] = "UnsetRH %08x";

char aZniszcze[9] = "zniszcze";

char aUnit_addtogrou[26] = "Unit_AddToGroup(%d,%d,%d)";

char aUnit_movefromg[62] = "Unit_MoveFromGroup(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)";

char aD_5[3] = "%d";

char aRoad_buildDD[18] = "Road_Build(%d,%d)";

char aUnitbattle_m_0[31] = "UnitBattle_MoveTrack(%d,%d,%d)";

char aUnitbattle_mov[35] = "UnitBattle_MoveTrackNear(%d,%d,%d)";

char aUnitbattle_m_2[39] = "UnitBattle_MoveTrackNearWall(%d,%d,%d)";

char aUnitbattle_m_3[36] = "UnitBattle_MoveTrackForce(%d,%d,%d)";

char aUnitbattle_m_1[20] = "UnitBattle_Move(%d)";

char aAttackanimDD[18] = "AttackAnim(%d,%d)";

char aDeathanimD[14] = "DeathAnim(%d)";

char aUnitbattle_att[28] = "UnitBattle_Attack(%d,%d,%d)";

char a_shotanimDDDDD[29] = "_ShotAnim(%d,%d,%d,%d,%d,%d)";

char aLoaded[10] = "loaded!!!";

char aUnitbattle_a_0[32] = "UnitBattle_AttackWall(%d,%d,%d)";

char aBattleMurek[13] = "battle\\murek";

char aUnitbattle_def[23] = "UnitBattle_Defence(%d)";

char aD_46[3] = "%d";

char aD_47[3] = "%d";

char aD_D[6] = "%d.%d";

char aD_8[3] = "%d";

char aD_9[3] = "%d";

char aCastle_chrDw_1[21] = "castle.chr\\dw_15.gfx";

char aCastle_pogDw_1[21] = "castle.pog\\dw_15.gfx";

char aCastle_chrDw_0[21] = "castle.chr\\dw_15.s32";

char aCastle_pogDw_0[21] = "castle.pog\\dw_15.s32";

char aCastle_chrDw_2[17] = "castle.chr\\dw_15";

char aCastle_pogDw_2[17] = "castle.pog\\dw_15";

char aD_32[3] = "%d";

char aD_33[3] = "%d";

char Trap_HurtUnit[22] = "Trap_HurtUnit(0x%08x)";

char aWpad_pul[9] = "wpad_pul";

char aThisIsAPitfall[19] = "This is a pitfall.";

char aDoYouWantToCov[33] = "Do you want to cover it, master?";

char aDasIstDieWolfs[24] = "Das ist die Wolfsh\x94hle.";

char aWillstDuSieZus[26] = "Willst Du sie zusch\x81tten?";

char aD0x08x15sPl1dP[63] = "  %d(0x%08x):       %15s pl:%1d pa:%2d q:%3d t:%3d m:%2d s:%2d";

char aBattle_logallu[19] = "Battle_LogAllUnits";

char aGodanger[11] = "GodAnger()";

char aBattle_newturn[17] = "Battle_NewTurn()";

char aBattleSzarza[14] = "battle\\szarza";

char aSetrhS08x_9[14] = "SetRH %s=%08x";

char aUnsetrh08x_8[13] = "UnsetRH %08x";

char aHandlebattlere[42] = "HandleBattleResults(0x%08x,0x%08x,0x%08x)";

char aHandlebattle_0[32] = "HandleBattleResult() - results:";

char aBattle_0[10] = "BATTLE!!!";

char aNewBattle_0[19] = "!!!!NEW BATTLE!!!!";

char aNewBattle[] = "!!!!NEW BATTLE!!!!";

char aCalculatebattl[] = "CalculateBattleResult(0x%08x,%d,%d,0x%08x,%d,%d,0x%08x, %d";

char aJednostka1[] = "Jednostka 1:";

char aJednostka2[] = "Jednostka 2:";

char aAs1D[] = "as1 = %d";

char aAs2D[] = "as2 = %d";

char aSum_quantDAtt_[] = "sum_quant = %d, att_lost = %d";

char aJednostkaZwyci[] = "Jednostka zwycieska:";

char aUnitbattle_sho[] = "UnitBattle_Shot(%d,%d)";

char aUnitbattle_s_0[] = "UnitBattle_ShotWall(%d,%d,%d)";

char aBattleMurek_0[] = "battle\\murek";

char aPort_getsupply[] = "Port_GetSupply()";

char aQueen_newturn[] = "Queen_NewTurn()";

char aP_posla[] = "p_posla";

char aQueen_newturnN[] = "Queen_NewTurn() - nowy potomek";

char aQueen_newturnK[] = "Queen_NewTurn() - krolowa ucieka";

char aQueen_newtur_0[] = "Queen_NewTurn() - krolowa ucieka - schemat %d";

char aQueen_newtur_1[] = "Queen_NewTurn() - krolowa ucieka - schemat %d";

char aQueen_newtur_2[] = "Queen_NewTurn() - krolowa ucieka - schemat %d";

char aQueen_newtur_3[] = "Queen_NewTurn() - krolowa ucieka - schemat %d";

char aQueen_newturnZ[] = "Queen_NewTurn() - zachcianka %d";

char g_QueenDepartureEventMessageBuffer[300];

char *g_QueenDepartureTexts[3] = {
  "Krolowa rozgoryczona tym malzenstwem postanowila wrocic do swoich panienskich komnat.",
  "The Queen, utterly dissatisfied with this marriage, decided to return to her maiden chamber.",
  "Die Konigin ist bitter enttauscht von dieser Ehe und kehrt in ihre Jungfrauenkammer zuruck.",
};

char *g_QueenCastleTreasuryTheftTexts[3] = {
  "Krolowa w napadzie furii spakowala kufry i uciekla, zabierajac skarbiec zamku %s.",
  "In an act of fury the Queen packed her trunks and escaped, taking the treasury of %s.",
  "In ihrem Zorn hat die Konigin gepackt und ist geflohen, wobei sie die Schatzkammer von %s mitnahm.",
};

char *g_QueenCastleWellPoisoningTexts[3] = {
  "Twa malzonka miala dosc takiego traktowania i przed ucieczka zatrula studnie w zamku %s.",
  "Your wife would not stand this kind of treatment and poisoned the wells in %s before fleeing.",
  "Deine Frau war dieses Umgangs uberdrussig und vergiftete vor ihrer Flucht die Brunnen in %s.",
};

char *g_QueenCastleArsonTexts[3] = {
  "Twa malzonka miala po dziurki w nosie Twego postepowania i przed odejsciem spalila %s.",
  "Your wife, before parting, ordered her servants to set %s on fire.",
  "Deine Frau konnte Dich nicht langer ertragen und liess %s vor ihrer Abreise in Brand setzen.",
};

char *g_QueenSonBirthTexts[3] = {
  "Panie, krolowa urodzila Ci syna!!!! Nadworni medrcy i weterani Twoich najwiekszych bitew ksztalca go tak, by mogl rychlo sluzyc Ci jako oddany dowodca.",
  "Master, the Queen has given birth to your son!!! Your best scholars and knights train him in warcraft so that he can be your right hand soon.",
  "Herr, die Konigin hat Dir einen Sohn geschenkt! Deine besten Lehrer und Ritter unterweisen ihn in der Kriegskunst, so dass er schon bald Deine rechte Hand sein wird.",
};

char *g_QueenDaughterBirthTexts[3] = {
  "Krolu!!! Twa zona poczela corke. Nasi medrcy orzekli, ze odziedziczony po ojcu temperament i zacietosc matki uczynia z niej wspanialego dowodce Twych wojsk.",
  "Master. Your wife has given birth to your daughter. Scholars say that she has inherited your strength of character and your temperament. Soon she will become a great officer of your troops.",
  "Herr, die Konigin hat Dir eine Tochter geschenkt! Die Weisen sagen, sie habe Dein Temperament und Deine Charakterstarke geerbt. Schon bald wird sie eine grosse Anfuhrerin Eurer Truppen sein.",
};

int g_PortSpawnRingOffsetsTable[24] = { 1, 2, 0, 2, 2, 2, -1, 2, 2, 1, -1, 1, 2, 0, -1, 0, 2, -1, -1, -1, 1, -1, 0, -1 };

unit_type g_PortReinforcementUnitTypePool[12] = {
  UNIT_TYPE_PEASANT,
  UNIT_TYPE_LIGHT_INFANTRY,
  UNIT_TYPE_HEAVY_INFANTRY,
  UNIT_TYPE_PIKEMAN,
  UNIT_TYPE_HEAVY_SPEARMAN,
  UNIT_TYPE_LIGHT_CAVALRY,
  UNIT_TYPE_KNIGHTS,
  UNIT_TYPE_ARCHER,
  UNIT_TYPE_CROSSBOWER,
  UNIT_TYPE_FORESTER,
  UNIT_TYPE_GORAL,
  UNIT_TYPE_BUILDER
};

__int16 g_QueenWhimRecords_5191F0 = 30;

char aSetrhS08x_8[14] = "SetRH %s=%08x";

char aBattle_1[7] = "battle";

char aBattleBat_bkg1[20] = "battle\\bat_bkg1.s32";

char aBattleBat_bkg2[20] = "battle\\bat_bkg2.s32";

char aBattleBat_bkg3[20] = "battle\\bat_bkg3.s32";

char aBattleButtons_[19] = "battle\\buttons.s32";

char aBattleFr_anim_[20] = "battle\\fr_anim.s32";

char aBattleTrupki_s[19] = "battle\\trupki.s32";

char aBattleFrame_s3[18] = "battle\\frame.s32";

char aBattleActiveTi[35] = "Battle active tile not initialized";

char aNotEnoughMem_9[21] = "Not enough memory=%d";

char aNotEnoughMe_10[21] = "Not enough memory=%d";

char aMainmap_3[8] = "mainmap";

char aStart_0[6] = "START";

char aEndOfBattle[14] = "END OF BATTLE";

char aUnsetrh08x_9[13] = "UnsetRH %08x";

char aD_48[3] = "%d";

char aD_49[3] = "%d";

char aD_50[3] = "%d";

char aD_51[3] = "%d";

char aD_52[3] = "%d";

char aD_53[3] = "%d";

char aD_54[3] = "%d";

char aD_34[3] = "%d";

char aD_35[3] = "%d";

char aBattle_placeun[34] = "Battle_PlaceUnit(0x%08x,%d,%d,%d)";

char aD_55[3] = "%d";

char aD_56[3] = "%d";

char aD_57[3] = "%d";

char aD_58[3] = "%d";

char aD_59[3] = "%d";

char aD_60[3] = "%d";

char aD_61[3] = "%d";

char aD_62[3] = "%d";

char aD_63[3] = "%d";

char aD_64[3] = "%d";

char aD_65[3] = "%d";

char aD_66[3] = "%d";

char aD_67[3] = "%d";

char aCastle_chrD_15[21] = "castle.chr\\dw_12.gfx";

char aCastle_pogD_15[21] = "castle.pog\\dw_12.gfx";

char aCastle_chrD_16[17] = "castle.chr\\dw_12";

char aCastle_pogD_16[17] = "castle.pog\\dw_12";

char aDclose[7] = "dclose";

char aWrong_7[6] = "wrong";

char aD_68[3] = "%d";

char aD_69[3] = "%d";

char aD_70[3] = "%d";

char a0_3[2] = "0";

char aD_71[3] = "%d";

char aD_72[3] = "%d";

char aD_73[3] = "%d";

char aD_74[3] = "%d";

char aD_75[3] = "%d";

char aD_76[3] = "%d";

char aD_77[3] = "%d";

char aDZbgeBisZum[16] = "%d Z\x81ge bis zum";

char aDZugBisZum[15] = "%d Zug bis zum";

char aD_38[3] = "%d";

char aDopen[6] = "dopen";

char aDclose_0[7] = "dclose";

char aCastle_chrD_23[21] = "castle.chr\\dw_13.gfx";

char aCastle_pogD_23[21] = "castle.pog\\dw_13.gfx";

char aMarker_0[7] = "marker";

char aCastle_chrD_17[21] = "castle.chr\\dw_13.gfx";

char aCastle_pogD_17[21] = "castle.pog\\dw_13.gfx";

char aCastle_chrD_19[17] = "castle.chr\\dw_13";

char aCastle_pogD_19[17] = "castle.pog\\dw_13";

char a_mtb[5] = ".mtb";

char aWb_0[3] = "wb";

char aD_39[3] = "%d";

char aD_40[3] = "%d";

char aCas_list_s32[13] = "cas_list.s32";

char aCas_list_pal[13] = "cas_list.pal";

char aD_10[3] = "%d";

char aD_11[3] = "%d";

char aCofnij_oddzial[24] = "cofnij_oddzial %d,%d,%d";

char aRuch_oddzialem[34] = "ruch_Oddzialem_Strzelajacym %d,%d";

char aOddzial_w_zasi[27] = "oddzial_w_Zasiegu %d,%d,%d";

char aPodejdz_na_bez[38] = "podejdz_na_Bezpieczna_Odleglosc %d,%d";

double g_Battle_RoleDeployRatioHighThreshold = 1.25;

double g_Battle_RoleDeployRatioLowThreshold = 0.75;

char aCastle_chrDw_3[21] = "castle.chr\\dw_20.gfx";

char aCastle_pogDw_3[21] = "castle.pog\\dw_20.gfx";

char aCastle_chrDw_5[17] = "castle.chr\\dw_20";

char aCastle_pogDw_5[17] = "castle.pog\\dw_20";

char aS_6[3] = "%s";

char aCastle_chrDw_6[21] = "castle.chr\\dw_20.gfx";

char aCastle_pogDw_6[21] = "castle.pog\\dw_20.gfx";

char aCastle_chrDw_8[17] = "castle.chr\\dw_20";

char aCastle_pogDw_8[17] = "castle.pog\\dw_20";

char aS_7[3] = "%s";

char aCastle_chrDw_9[21] = "castle.chr\\dw_20.gfx";

char aCastle_pogDw_9[21] = "castle.pog\\dw_20.gfx";

char aCastle_chrD_11[17] = "castle.chr\\dw_20";

char aCastle_pogD_11[17] = "castle.pog\\dw_20";

char aS_8[3] = "%s";

char aCastle_chrD_12[21] = "castle.chr\\dw_20.gfx";

char aCastle_pogD_12[21] = "castle.pog\\dw_20.gfx";

char aCastle_chrD_14[17] = "castle.chr\\dw_20";

char aCastle_pogD_14[17] = "castle.pog\\dw_20";

char aS_9[3] = "%s";

char aBuildingUnitsLeave[58] = "Building_UnitsLeave(0x%08x,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d)";

char aBuildings_unit[45] = "Buildings_UnitLeave(...) - OK - 0x%08x,%d,%d";

char aBuilding_unitg[28] = "Building_UnitGetInto(%d,%d)";

char aBuildingBuyUnitLicence[35] = "Building_BuyUnitLicence(0x%08x,%d)";

char aBuildingRemoveUnitLicence[38] = "Building_RemoveUnitLicence(0x%08x,%d)";

char aBuildingSetUnitProduction[38] = "Building_SetUnitProduction(0x%08x,%d)";

char aBuildingStopUnitProduction[36] = "Building_StopUnitProduction(0x%08x)";

char aBuildingTrainUnit[30] = "Building_TrainUnit(0x%08x,%d)";

char aBuildingRepairUnit[31] = "Building_RepairUnit(0x%08x,%d)";

char aBuildin1_s32[13] = "buildin1.s32";

char aBuildin2_s32[13] = "buildin2.s32";

char aBuildin3_s32[13] = "buildin3.s32";

char aUnit_movetra_2[33] = "Unit_MoveTrackToTemple(%d,%d,%d)";

char aTemple_random[16] = "Temple_Random()";

char a__RDSum_probD[26] = "__  r = %d, sum_prob = %d";

char aTemple_process[36] = "Temple_ProcessGift(%d,0x%08x,%d,%d)";

char aTemple_unitget[29] = "Temple_UnitGetInto(%d,%d,%d)";

char aTemple_unitg_0[55] = "Temple_UnitGetInto(...) - wlazl nie do swojej swiatyni";

char aTemple_unitg_2[51] = "Temple_UnitGetInto(...) - swiatynia juz odwiedzona";

char aTemple_unitg_1[41] = "Temple_UnitGetInto() - wylosowano 0x%08x";

char aSw_chs[7] = "sw_chs";

char aSw_pog[7] = "sw_pog";

char aDclose_1[7] = "dclose";

char aD_78[3] = "%d";

char aMarker[7] = "marker";

char aBattlemapfilen[25] = "BattleMapFileName(%d,%d)";

char aMaps[6] = "maps\\";

char a_mab[5] = ".mab";

char aBattlemapfil_0[31] = "BattleMapFileName() returns %s";

char aZ[2] = "z";

char aSfxMusic[11] = "sfx\\music\\";

char a_wav_5[5] = ".wav";

char aRb[3] = "rb";

char aActiv1_wav[12] = "\\activ1.wav";

char aGo1_wav[9] = "\\go1.wav";

char aStrzal_wav[12] = "\\strzal.wav";

char aDostal_wav[12] = "\\dostal.wav";

char aDead_wav[10] = "\\dead.wav";

char aWalka_wav[11] = "\\walka.wav";

char aGothim_wav[12] = "\\gothim.wav";

char a_wav[5] = ".wav";

char a_wav_0[5] = ".wav";

char a_wav_1[5] = ".wav";

char a_wav_2[5] = ".wav";

char a_wav_3[5] = ".wav";

char a_wav_4[5] = ".wav";

char aIOCouldnTOpenF[29] = "I/O: couldn't open file '%s'";

char aRb_3[3] = "rb";

char aRb_4[3] = "rb";

char aDataMinimum_re[17] = "data\\minimum.res";

char aDot_MinimumResourcePrefix[2] = ".";

char aDataNormal_res[16] = "data\\normal.res";

char aDot_NormalResourcePrefix[2] = ".";

char aDataMaximum_re[17] = "data\\maximum.res";

char aDot_MaximumResourcePrefix[2] = ".";

char aDataMaps_res[14] = "data\\maps.res";

char aMaps_0[5] = "maps";

char aDataGfx3_res[14] = "data\\gfx3.res";

char aGfx_6[4] = "gfx";

char aDataInfopol_re[17] = "data\\infopol.res";

char aGfxBiginfo_pol[16] = "gfx\\biginfo.pol";

char aDataInfoang_re[17] = "data\\infoang.res";

char aGfxBiginfo_eng[16] = "gfx\\biginfo.eng";

char aDataInfoger_re[17] = "data\\infoger.res";

char aGfxBiginfo_ger[16] = "gfx\\biginfo.ger";

char aDataMisinfop_r[18] = "data\\misinfop.res";

char aGfxMisinfo[12] = "gfx\\misinfo";

char aDataMisinfoa_r[18] = "data\\misinfoa.res";

char aGfxMisinfo_0[12] = "gfx\\misinfo";

char aDataMiswava_re[17] = "data\\miswava.res";

char aSfxMisinfo[12] = "sfx\\misinfo";

char aDataMisinfog_r[18] = "data\\misinfog.res";

char aGfxMisinfo_1[12] = "gfx\\misinfo";

char aDataMusic_res[15] = "data\\music.res";

char aSfxMusic_0[10] = "sfx\\music";

char aGfxBackgr1_s32[16] = "gfx\\backgr1.s32";

char aNotEnoughMe_11[21] = "Not enough memory=%d";

char aNotEnoughMe_12[21] = "Not enough memory=%d";

char aBrakPlikuS[15] = "brak pliku: %s";

char aWb_2[3] = "wb";

char aPort_newturnPo[45] = "Port_NewTurn() - posilki przybyly - sztuk %d";

char aPort[5] = "Port";

char aHafen[6] = "Hafen";

char aD_36[3] = "%d";

char aWrong_0[6] = "wrong";

char aWrong_1[6] = "wrong";

char aUkrycie[8] = "ukrycie";

char aWb_4[3] = "wb";

char aRb_5[3] = "rb";

char aRb_7[3] = "rb";

char asc_4F94BB[4] = "---";

char aRb_8[3] = "rb";

char asc_4F94C2[4] = "---";

char aSetrhS08x_22[14] = "SetRH %s=%08x";

char aUnsetrh08x_22[13] = "UnsetRH %08x";

char aWindowmessageS[17] = "WindowMessage %s";

char aSetrhS08x_10[14] = "SetRH %s=%08x";

char aUnsetrh08x_10[13] = "UnsetRH %08x";

char aZaraza[7] = "zaraza";

char aMessage_buildf[25] = "Message_BuildFinished %s";

char aSetrhS08x_11[14] = "SetRH %s=%08x";

char aUnsetrh08x_11[13] = "UnsetRH %08x";

char aSetrhS08x_23[14] = "SetRH %s=%08x";

char aUnsetrh08x_23[13] = "UnsetRH %08x";

char aQueenwhimmessa[20] = "QueenWhimMessage %s";

char aSetrhS08x_18[14] = "SetRH %s=%08x";

char aD_6[3] = "%d";

char aD_7[3] = "%d";

char aUnsetrh08x_18[13] = "UnsetRH %08x";

char aYesnowindowS[16] = "YesNoWindow(%s)";

char aSetrhS08x_12[14] = "SetRH %s=%08x";

char aUnsetrh08x_12[13] = "UnsetRH %08x";

char aInfowindowS[15] = "InfoWindow(%s)";

char aSetrhS08x_13[14] = "SetRH %s=%08x";

char aUnsetrh08x_13[13] = "UnsetRH %08x";

char aNewqueenwindow[17] = "NewQueenWindow()";

char aQueen_s32_0[10] = "queen.s32";

char aSetrhS08x_17[14] = "SetRH %s=%08x";

char aUnsetrh08x_17[13] = "UnsetRH %08x";

char aQueenmessageS[17] = "QueenMessage(%s)";

char aSetrhS08x_16[14] = "SetRH %s=%08x";

char aUnsetrh08x_16[13] = "UnsetRH %08x";

char aStartanims[11] = "StartAnims";

char aSetrhS08x_14[14] = "SetRH %s=%08x";

char aNull[5] = "NULL";

char aLogo_0[5] = "logo";

char aSoft2000[9] = "soft2000";

char aInt_a[6] = "int_a";

char aInt_a_0[6] = "int_a";

char aInt_g[6] = "int_g";

char aUnsetrh08x_14[13] = "UnsetRH %08x";

char aStartanimsEnd[15] = "StartAnims-end";

char aStartmenu[10] = "StartMenu";

char aSetrhS08x_15[14] = "SetRH %s=%08x";

char aStdrh_10[6] = "StdRH";

char aMenuMain_gfx[14] = "menu\\main.gfx";

char aMenuMain[10] = "menu\\main";

char aMusicMenu[11] = "music\\menu";

char aDraw1[6] = "draw1";

char aDraw2[6] = "draw2";

char aDrawend[8] = "drawend";

char aMenuMain_gfx_0[14] = "menu\\main.gfx";

char aMenuMultipl_s32[17] = "menu\\multipl.s32";

char aMenuMultipl_gf[17] = "menu\\multipl.gfx";

char aMale_2[5] = "male";

char aW[2] = "W";

char aMale_1[5] = "male";

char aCre_an[7] = "cre_an";

char aMenuOpt_p_gfx[15] = "menu\\opt_p.gfx";

char aMenuOpt_a_gfx[15] = "menu\\opt_a.gfx";

char aMenuOpt_g_gfx[15] = "menu\\opt_g.gfx";

char aMenuOpt_s32[13] = "menu\\opt.s32";

char aMusicMenu_0[11] = "music\\menu";

char aMenuLoad_s32[14] = "menu\\load.s32";

char aMenuLoad_gfx[14] = "menu\\load.gfx";

char aUnsetrh08x_15[13] = "UnsetRH %08x";

char aOptions_cfg[12] = "options.cfg";

char aWb_1[3] = "wb";

char aOptions_cfg_0[12] = "options.cfg";

char aDoc[4] = "Doc";

char aSirArthur[11] = "Sir Arthur";

char aLester[7] = "Lester";

char aComputer[9] = "Computer";

char aTomek[6] = "Tomek";

char aSirArthur_0[11] = "Sir Arthur";

char aLester_0[7] = "Lester";

char aComputer_0[9] = "Computer";

char aTomek_0[6] = "Tomek";

char aCantbelly_3[10] = "Cantbelly";

char aKopegon[8] = "Kopegon";

char aZamek[6] = "Zamek";

char aZamek_0[6] = "Zamek";

char aCantbelly[10] = "Cantbelly";

char aCantbelly_0[10] = "Cantbelly";

char aPrisoner_addto[36] = "Prisoner_AddToInWay(%d,%d,%d,%d,%d)";

char aPrisoner_setin[24] = "Prisoner_SetInCastles()";

char aUwiezic[8] = "uwiezic";

char aBuilding_setpr[41] = "Building_SetPrisonerAction(0x%08x,%d,%d)";

char aPrisoner_kill0[25] = "Prisoner_Kill(0x%08x,%d)";

char aPrisoner_behea[27] = "Prisoner_Behead(0x%08x,%d)";

char aZciecie[8] = "zciecie";

char aPrisoner_tortu[28] = "Prisoner_Torture(0x%08x,%d)";

char aPrisoner_tor_0[26] = "Prisoner_Torture(...) - 0";

char aPrisoner_tor_1[26] = "Prisoner_Torture(...) - 1";

char aPrisoner_tor_2[26] = "Prisoner_Torture(...) - 2";

char aPrisoner_tor_3[26] = "Prisoner_Torture(...) - 3";

char aPrisoner_tor_4[26] = "Prisoner_Torture(...) - 4";

char aBuilding_creat[34] = "Building_CreateSpecial(0x%08x,%d)";

char aPrisoner_pay0x[24] = "Prisoner_Pay(0x%08x,%d)";

char aPrisoner_newtu[25] = "Prisoner_NewTurn(0x%08x)";

char aD_79[3] = "%d";

char aStat_gfx[9] = "stat.gfx";

char aStat[5] = "stat";

char aPlayer_surrend[21] = "Player_Surrender(%d)";

char aZwy01[6] = "zwy01";

char aStdrh_19[6] = "StdRH";

char aSetrhS08x_24[14] = "SetRH %s=%08x";

char aUnsetrh08x_24[13] = "UnsetRH %08x";

char aTeam1_gfx[10] = "team1.gfx";

char aHeheNoBonus[15] = "hehe, no bonus";

char aStrategClash_d[18] = "strateg\\clash.dat";

char aS_0[4] = "%s\n";

char aMkinstArmyS[17] = " mkinst/army %s\n";

char a22i_1[4] = "22i";

char aSwiatynia00[12] = "swiatynia00";

char aSwiatynia[10] = "swiatynia";

char a11i[4] = "11i";

char aKop_skarb00[12] = "kop_skarb00";

char aKop_skarb[10] = "kop_skarb";

char a00i[4] = "00i";

char aPobierz_oddzia[26] = "pobierz_oddzial_z_portu00";

char aPobierz_oddz_0[24] = "pobierz_oddzial_z_portu";

char aPelny_port00[13] = "pelny_port00";

char aPelny_port[11] = "pelny_port";

char aJest_pracownik[25] = "jest_pracownik_w_armii00";

char aJest_pracown_0[23] = "jest_pracownik_w_armii";

char aJednostka_bite[20] = "jednostka_bitewna00";

char aJednostka_bi_0[18] = "jednostka_bitewna";

char a33i[4] = "33i";

char aJest_droga00[13] = "jest_droga00";

char aJest_droga[11] = "jest_droga";

char aJest_droga_w_p[23] = "jest_droga_w_poblize00";

char aJest_droga_w_0[21] = "jest_droga_w_poblize";

char aJest_droga_w_1[29] = "jest_droga_w_poblize_zamku00";

char aJest_droga_w_2[27] = "jest_droga_w_poblize_zamku";

char aJest_droga_do_[22] = "jest_droga_do_portu00";

char aJest_droga_d_0[20] = "jest_droga_do_portu";

char aJest_droga_d_1[22] = "jest_droga_do_zamku00";

char aJest_droga_d_2[20] = "jest_droga_do_zamku";

char aJest_droga_d_3[25] = "jest_droga_do_swiatyni00";

char aJest_droga_d_4[23] = "jest_droga_do_swiatyni";

char aOddzial_w_za_0[26] = "oddzial_w_zasiegu_armii00";

char aOddzial_w_za_1[24] = "oddzial_w_zasiegu_armii";

char aBudowla_w_zasi[26] = "budowla_w_zasiegu_armii00";

char aBudowla_w_za_0[24] = "budowla_w_zasiegu_armii";

char aOdleglosc_od_o[23] = "odleglosc_od_obiektu00";

char aOdleglosc_od_0[21] = "odleglosc_od_obiektu";

char aSwiatynia_w_za[28] = "swiatynia_w_zasiegu_armii00";

char aSwiatynia_w__0[26] = "swiatynia_w_zasiegu_armii";

char aSwiatynia_ok00[15] = "swiatynia_OK00";

char aSwiatynia_ok[13] = "swiatynia_OK";

char aMaszeruj00[11] = "maszeruj00";

char aMaszeruj[9] = "maszeruj";

char aMaszeruj_do_sw[23] = "maszeruj_do_swiatyni00";

char aMaszeruj_do__0[21] = "maszeruj_do_swiatyni";

char aMaszeruj_blisk[18] = "maszeruj_blisko00";

char aMaszeruj_bli_0[16] = "maszeruj_blisko";

char aAtakuj_oddzial[17] = "atakuj_oddzial00";

char aAtakuj_oddzi_0[15] = "atakuj_oddzial";

char aPrzejmuj_oddzi[19] = "przejmuj_oddzial00";

char aPrzejmuj_odd_0[17] = "przejmuj_oddzial";

char aUkryj_oddzial0[16] = "ukryj_oddzial00";

char aUkryj_oddzial[14] = "ukryj_oddzial";

char aJest_armia00[13] = "jest_armia00";

char aJest_armia[11] = "jest_armia";

char aLiczba_jednost[30] = "liczba_jednostek_w_oddziale00";

char aLiczba_jedno_0[28] = "liczba_jednostek_w_oddziale";

char aAtakuj_budowle[17] = "atakuj_budowle00";

char aAtakuj_budow_0[15] = "atakuj_budowle";

char aJest_brod00[12] = "jest_brod00";

char aJest_brod[10] = "jest_brod";

char aBuduj_droge00[14] = "buduj_droge00";

char aBuduj_droge[12] = "buduj_droge";

char aBuduj_pulapke0[16] = "buduj_pulapke00";

char aBuduj_pulapke[14] = "buduj_pulapke";

char aUnit_canmove00[15] = "Unit_CanMove00";

char aUnit_canmove[13] = "Unit_CanMove";

char aJest_droga_w_3[32] = "jest_droga_w_poblize2(%d,%d,%d)";

char aOddzial_w_za_2[35] = "oddzial_w_zasiegu_armii2(%d,%d,%d)";

char aOdleglosc_od_1[32] = "odleglosc_od_obiektu2(%d,%d,%d)";

char aPa[3] = "PA";

char aPa_0[3] = "PA";

char aMaszeruj_bli_1[27] = "maszeruj_blisko2(%d,%d,%d)";

char aPa_1[3] = "PA";

char aBuduj_pulapke2[25] = "buduj_pulapke2(%d,%d,%d)";

char aPa_2[3] = "PA";

char aPa_3[3] = "PA";

wchar_t aXxyy[4] = L"xxyy";

char aMoc[4] = "moc";

char aMoc_0[4] = "moc";

char aGracz[6] = "gracz";

char aGracz_0[6] = "gracz";

char aKasuj_swiatyni[23] = "kasuj_swiatynie(%d,%d)";

char aNie[4] = "NIE";

char aTak[4] = "TAK";

char aNie_0[4] = "NIE";

char aTak_0[4] = "TAK";

char aNie_1[4] = "NIE";

char aTak_1[4] = "TAK";

char aNie_2[4] = "NIE";

char aTak_2[4] = "TAK";

char aNie_3[4] = "NIE";

char aTak_3[4] = "TAK";

float g_Building_MaxTaxRate = 40.0;

char aMoc_1[4] = "moc";

char aMoc_2[4] = "moc";

char a11i_3[4] = "11i";

char aLeczenie[9] = "Leczenie";

char aSzkolenie[10] = "Szkolenie";

char aPalbudowle[11] = "PalBudowle";

char aPalBudowle[12] = "Pal-Budowle";

char aUpgradewall[12] = "UpgradeWall";

char aUpgradeWall[13] = "Upgrade-Wall";

char a22iif[6] = "22iif";

char aZmienpodatek[13] = "ZmienPodatek";

char aZmienPodatek[14] = "Zmien-Podatek";

char a22i[4] = "22i";

char aRemovelicence[14] = "RemoveLicence";

char aRemoveLicence[15] = "Remove-Licence";

char aZacznijleczeni[16] = "ZacznijLeczenie";

char aZacznijLeczeni[17] = "Zacznij-Leczenie";

char aZacznijszkolen[17] = "ZacznijSzkolenie";

char aZacznijSzkolen[18] = "Zacznij-Szkolenie";

char aZacznijprodukc[17] = "ZacznijProdukcje";

char aZacznijProdukc[18] = "Zacznij-Produkcje";

char aKupszkola[10] = "KupSzkola";

char aKupSzkola[11] = "Kup-Szkola";

char aKupkuznia[10] = "KupKuznia";

char aKupKuznia[11] = "Kup-Kuznia";

char aIslicence[10] = "IsLicence";

char aIsLicence[11] = "Is-Licence";

char aBuylicence[11] = "BuyLicence";

char aBuyLicence[12] = "Buy-Licence";

char aKupszpital[11] = "KupSzpital";

char aKupSzpital[12] = "Kup-Szpital";

char a55iiiiis[9] = "55iiiiis";

char aBudujzamek[11] = "BudujZamek";

char aBudujZamek[12] = "Buduj-Zamek";

char aKupkoszary[11] = "KupKoszary";

char aKupKoszary[12] = "Kup-Koszary";

char aKupwarsztat[12] = "KupWarsztat";

char aKupWarsztat[13] = "Kup-Warsztat";

char aIsproduction[13] = "IsProduction";

char aIsProduction[14] = "Is-Production";

char a44i[4] = "44i";

char aCzyminimalny[13] = "CzyMinimalny";

char aCzyMinimalny[14] = "Czy-Minimalny";

char aCanbuylicence[14] = "CanBuyLicence";

char aCanBuyLicence[16] = "Can-Buy-Licence";

char aIsproductionan[16] = "IsProductionAny";

char aIsProductionAn[18] = "Is-Production-Any";

char aMaxiloscoddzia[18] = "MaxIloscOddzialow";

char aMaxIloscOddzia[20] = "Max-Ilosc-Oddzialow";

char aJednostkidoszk[18] = "JednostkiDoSzkoly";

char aJednostkiDoSzk[20] = "Jednostki-Do-Szkoly";

char aJednostkidoszp[20] = "JednostkiDoSzpitala";

char aJednostkiDoSzp[22] = "Jednostki-Do-Szpitala";

char aJestjednostkaw[20] = "JestJednostkaWZamku";

char aJestJednostkaW[23] = "Jest-Jednostka-W-Zamku";

char aPodatek[8] = "Podatek";

char aPieniadze[10] = "Pieniadze";

char aSilamurow[10] = "SilaMurow";

char aSilaMurow[11] = "Sila-Murow";

char aSilazamku[10] = "SilaZamku";

char aSilaZamku[11] = "Sila-Zamku";

char a00i_0[4] = "00i";

char aNumertury[10] = "NumerTury";

char aNumerTury[11] = "Numer-Tury";

char aPoziomtech[11] = "PoziomTech";

char aPoziomTech[12] = "Poziom-Tech";

char aZadowolenie[12] = "Zadowolenie";

char aTypbudowli[11] = "TypBudowli";

char aTypBudowli[12] = "Typ-Budowli";

char aSilagracza[11] = "SilaGracza";

char aSilaGracza[12] = "Sila-Gracza";

char aIloscchlopow[13] = "IloscChlopow";

char aIloscChlopow[14] = "Ilosc-Chlopow";

char aLicencjaindex[14] = "LicencjaIndex";

char aLicencjaIndex[15] = "Licencja-Index";

char aLicencjaind[12] = "LicencjaInd";

char aLicencjaInd[13] = "Licencja-Ind";

char aIloscoddzialow[15] = "IloscOddzialow";

char aIloscOddzialow[16] = "Ilosc-Oddzialow";

char aCanupgradewall[15] = "CanUpgradeWall";

char aCanUpgradeWall[17] = "Can-Upgrade-Wall";

char aWyprowadzchlop[17] = "WyprowadzChlopow";

char aWyprowadzChlop[18] = "Wyprowadz-Chlopow";

char aWyprowadzenieo[22] = "WyprowadzenieOddzialu";

char aWyprowadzenieO[23] = "Wyprowadzenie-Oddzialu";

char aWyprowadzeni_0[23] = "WyprowadzenieOddzialow";

char aWyprowadzeni_1[24] = "Wyprowadzenie-Oddzialow";

char aNazwazamku[11] = "NazwaZamku";

char aNazwaZamku[12] = "Nazwa-Zamku";

char a22i_0[4] = "22i";

char aWejdzdozamku[13] = "WejdzDoZamku";

char aWejdzDoZamku[15] = "wejdz-do-zamku";

char aDolaczdoarmii[14] = "DolaczDoArmii";

char aDolaczDoOddzia[19] = "dolacz-do-oddzialu";

char aPrzegrupujarmi[16] = "PrzegrupujArmie";

char aPrzegrupujOddz[20] = "przegrupuj-oddzialy";

char aPrzegrupujzame[16] = "PrzegrupujZamek";

char aPrzegrupujZame[17] = "przegrupuj-zamek";

char a11i_0[4] = "11i";

char aLiczbawolnychm[26] = "LiczbaWolnychMiejscWZamku";

char aLiczbaWolnychM[30] = "liczba-wolnych-miejsc-w-zamku";

char aZnajdzdrogewpo[25] = "ZnajdzDrogeWPoblizeZamku";

char aZnajdzDrogeWPo[29] = "znajdz-droge-w-poblize-zamku";

char aMocprzeciwnika[25] = "MocPrzeciwnikaPodMurami2";

char aMocPrzeciwnika[27] = "moc-przeciwnika-pod-murami";

char aStanosobarmii[14] = "StanOsobArmii";

char aStanOsobArmii[16] = "stan-osob-armii";

char aArmiamajednost[21] = "ArmiaMaJednostkiTypu";

char aArmiaMaJednost[24] = "armia-ma-jednostki-typu";

char aArmiatylkojedn[24] = "ArmiaTylkoJednostkiTypu";

char aArmiaTylkoJedn[27] = "armia-tylko-jednostki-typu";

char aMajednostkidol[22] = "MaJednostkiDoLeczenia";

char aMaJednostkiDoL[25] = "ma-jednostki-do-leczenia";

char aZnajdzzamekdol[22] = "ZnajdzZamekDoLeczenia";

char aZnajdzZamekDoL[25] = "znajdz-zamek-do-leczenia";

char aIdzdoleczenia[14] = "IdzDoLeczenia";

char aIdzDoLeczenia[16] = "idz-do-leczenia";

char aJestzarazawzam[17] = "JestZarazaWZamku";

char aJestZarazaWZam[20] = "jest-zaraza-w-zamku";

char aJestzarazawodd[20] = "JestZarazaWOddziale";

char aJestZarazaWOdd[23] = "jest-zaraza-w-oddziale";

char aOdlaczjednostk[21] = "OdlaczJednostkiSlabe";

char aOdlaczJednostk[23] = "odlacz-jednostki-slabe";

char aOdlaczjednos_0[20] = "OdlaczJednostkiTypu";

char aOdlaczJednos_0[22] = "odlacz-jednostki-typu";

char aMaszerujwzdluz[20] = "MaszerujWzdluzDrogi";

char aMaszerujWzdluz[22] = "maszeruj-wzdluz-drogi";

char a55i[4] = "55i";

char aZnajdz_najleps[17] = "Znajdz_Najlepszy";

char aZnajdzNajlepsz[17] = "znajdz-najlepszy";

char aPrzegrupujar_0[24] = "PrzegrupujArmie2(%d,%d)";

char aPrzegrupujza_0[24] = "PrzegrupujZamek2(%d,%d)";

char aR[2] = "r";

char aStrategprior[13] = "strategprior";

char aZwy01_0[6] = "zwy01";

char aMouse_speedD[15] = "Mouse_speed=%d";

char aWb_7[3] = "wb";

char aAb[3] = "ab";

char aRb_9[3] = "rb";

_UNKNOWN g_App_QuitReason_DemoSkipKey;

char aStdrhCall[11] = "StdRH-call";

char aDmessage0x08xL[68] = "Dmessage=0x%08x, lost=%d, wParam=0x%08x, lParam=0x%08x, hwnd=0x%08x";

char aWm_activateapp[18] = "WM_ACTIVATEAPP=%d";

char aAcquire[8] = "Acquire";

char aResumedSoundD[17] = "Resumed sound %d";

char aUnacquire[10] = "UnAcquire";

char aPausedSoundD[16] = "Paused sound %d";

char aWm_paint[9] = "WM_PAINT";

char aRestoreD[12] = "Restore: %d";

char aRedrawhandler0[19] = "RedrawHandler=0x%x";

char aClash_1[6] = "Clash";

CHAR WindowName[] = "Clash";

CHAR ClassName[] = "Clash";

char aAmessage0x08xL[68] = "Amessage=0x%08x, lost=%d, wParam=0x%08x, lParam=0x%08x, hwnd=0x%08x";

char aNotEnoughMe_13[21] = "Not enough memory=%d";

char aNotEnoughMe_14[21] = "Not enough memory=%d";

char aIs_filepathOpe[21] = "IS_FilePath opens %s";

char aIs_filepathO_0[21] = "IS_FilePath opens %s";

char aAvi_playIn[12] = "AVI_Play in";

char aSetrhS08x_19[14] = "SetRH %s=%08x";

char aInit16bpp[11] = "Init 16BPP";

char aClose16bpp[12] = "Close 16BPP";

char aUnsetrh08x_19[13] = "UnsetRH %08x";

char aAvi_playOut[13] = "AVI_Play out";

char aSetrhS08x_20[14] = "SetRH %s=%08x";

char aUnsetrh08x_20[13] = "UnsetRH %08x";

char aKon_por1_1[9] = "kon_por1";

char aSetrhS08x_21[14] = "SetRH %s=%08x";

char aSfxMisinfoC_02[24] = "sfx\\misinfo\\%c_%02d.WAV";

char aDataLector_w_0[16] = "data\\lector.wav";

char aMusicCampain[14] = "music\\campain";

char aDataLector_w_2[16] = "data\\lector.wav";

char aUnsetrh08x_21[13] = "UnsetRH %08x";

double g_CAviDecompressor_MillisecondsPerSecond = 1000.0;

float g_AviPlayer_MillisecondsPerSecond = 1000.0;

char aRiff[5] = "RIFF";

char aWave[5] = "WAVE";

char aFmt[5] = "fmt ";

char aData[5] = "data";

double g_CSS_MixLookupIndexScale = 22.6625;

double g_CSS_MixLookupIndexBias = 4.0;

char aMemory[7] = "MEMORY";

char aOutOfMemory_[16] = "Out of memory.\n";

char aReleaseErrorIn[27] = "Release error in genfree.\n";

char aDeallocatingMe[30] = "\n*** DEALLOCATING MEMORY ***\n";

char aMemoryDealloca[29] = "*** MEMORY  DEALLOCATED ***\n";

char aUnableToAlloca[40] = "Unable to allocate initial memory pool\n";

char aBmexit[7] = "bmexit";

char aDderr_alreadyi[25] = "DDERR_ALREADYINITIALIZED";

char aDderr_cannotat[26] = "DDERR_CANNOTATTACHSURFACE";

char aDderr_cannotde[26] = "DDERR_CANNOTDETACHSURFACE";

char aDderr_currentl[24] = "DDERR_CURRENTLYNOTAVAIL";

char aDderr_exceptio[16] = "DDERR_EXCEPTION";

char aDderr_generic[14] = "DDERR_GENERIC";

char aDderr_heightal[18] = "DDERR_HEIGHTALIGN";

char aDderr_incompat[26] = "DDERR_INCOMPATIBLEPRIMARY";

char aDderr_invalidc[18] = "DDERR_INVALIDCAPS";

char aDderr_invali_0[22] = "DDERR_INVALIDCLIPLIST";

char aDderr_invalidm[18] = "DDERR_INVALIDMODE";

char aDderr_invalido[20] = "DDERR_INVALIDOBJECT";

char aDderr_invali_2[20] = "DDERR_INVALIDPARAMS";

char aDderr_invali_1[25] = "DDERR_INVALIDPIXELFORMAT";

char aDderr_invalidr[18] = "DDERR_INVALIDRECT";

char aDderr_lockedsu[21] = "DDERR_LOCKEDSURFACES";

char aDderr_no3d[11] = "DDERR_NO3D";

char aDderr_noalphah[16] = "DDERR_NOALPHAHW";

char aDderr_noclipli[17] = "DDERR_NOCLIPLIST";

char aDderr_nocolorc[20] = "DDERR_NOCOLORCONVHW";

char aDderr_nocooper[28] = "DDERR_NOCOOPERATIVELEVELSET";

char aDderr_nocolork[17] = "DDERR_NOCOLORKEY";

char aDderr_nocolo_0[19] = "DDERR_NOCOLORKEYHW";

char aDderr_nodire_0[26] = "DDERR_NODIRECTDRAWSUPPORT";

char aDderr_noexclus[22] = "DDERR_NOEXCLUSIVEMODE";

char aDderr_nofliphw[15] = "DDERR_NOFLIPHW";

char aDderr_nogdi[12] = "DDERR_NOGDI";

char aDderr_nomirror[17] = "DDERR_NOMIRRORHW";

char aDderr_notfound[15] = "DDERR_NOTFOUND";

char aDderr_noover_0[18] = "DDERR_NOOVERLAYHW";

char aDderr_noraster[19] = "DDERR_NORASTEROPHW";

char aDderr_norotati[19] = "DDERR_NOROTATIONHW";

char aDderr_nostretc[18] = "DDERR_NOSTRETCHHW";

char aDderr_not4bitc[19] = "DDERR_NOT4BITCOLOR";

char aDderr_not4bi_0[24] = "DDERR_NOT4BITCOLORINDEX";

char aDderr_not8bitc[19] = "DDERR_NOT8BITCOLOR";

char aDderr_notextur[18] = "DDERR_NOTEXTUREHW";

char aDderr_novsynch[16] = "DDERR_NOVSYNCHW";

char aDderr_nozbuffe[18] = "DDERR_NOZBUFFERHW";

char aDderr_nozoverl[19] = "DDERR_NOZOVERLAYHW";

char aDderr_outofcap[16] = "DDERR_OUTOFCAPS";

char aDderr_outofmem[18] = "DDERR_OUTOFMEMORY";

char aDderr_outofvid[23] = "DDERR_OUTOFVIDEOMEMORY";

char aDderr_overlayc[22] = "DDERR_OVERLAYCANTCLIP";

char aDderr_overla_0[35] = "DDERR_OVERLAYCOLORKEYONLYONEACTIVE";

char aDderr_paletteb[18] = "DDERR_PALETTEBUSY";

char aDderr_colorkey[21] = "DDERR_COLORKEYNOTSET";

char aDderr_surfacea[29] = "DDERR_SURFACEALREADYATTACHED";

char aDderr_surfac_0[30] = "DDERR_SURFACEALREADYDEPENDENT";

char aDderr_surfaceb[18] = "DDERR_SURFACEBUSY";

char aDderr_cantlock[22] = "DDERR_CANTLOCKSURFACE";

char aDderr_surfacei[24] = "DDERR_SURFACEISOBSCURED";

char aDderr_surfacel[18] = "DDERR_SURFACELOST";

char aDderr_surfacen[25] = "DDERR_SURFACENOTATTACHED";

char aDderr_toobighe[19] = "DDERR_TOOBIGHEIGHT";

char aDderr_toobigsi[17] = "DDERR_TOOBIGSIZE";

char aDderr_toobigwi[18] = "DDERR_TOOBIGWIDTH";

char aDderr_unsuppor[18] = "DDERR_UNSUPPORTED";

char aDderr_unsupp_1[24] = "DDERR_UNSUPPORTEDFORMAT";

char aDderr_unsupp_2[22] = "DDERR_UNSUPPORTEDMASK";

char aDderr_vertical[30] = "DDERR_VERTICALBLANKINPROGRESS";

char aDderr_wasstill[22] = "DDERR_WASSTILLDRAWING";

char aDderr_xalign[13] = "DDERR_XALIGN";

char aDderr_invalidd[28] = "DDERR_INVALIDDIRECTDRAWGUID";

char aDderr_directdr[31] = "DDERR_DIRECTDRAWALREADYCREATED";

char aDderr_nodirect[21] = "DDERR_NODIRECTDRAWHW";

char aDderr_primarys[34] = "DDERR_PRIMARYSURFACEALREADYEXISTS";

char aDderr_noemulat[18] = "DDERR_NOEMULATION";

char aDderr_regionto[21] = "DDERR_REGIONTOOSMALL";

char aDderr_clipperi[25] = "DDERR_CLIPPERISUSINGHWND";

char aDderr_noclippe[24] = "DDERR_NOCLIPPERATTACHED";

char aDderr_nohwnd[13] = "DDERR_NOHWND";

char aDderr_hwndsubc[21] = "DDERR_HWNDSUBCLASSED";

char aDderr_hwndalre[21] = "DDERR_HWNDALREADYSET";

char aDderr_nopalett[24] = "DDERR_NOPALETTEATTACHED";

char aDderr_nopale_0[18] = "DDERR_NOPALETTEHW";

char aDderr_bltfastc[22] = "DDERR_BLTFASTCANTCLIP";

char aDderr_noblthw[14] = "DDERR_NOBLTHW";

char aDderr_noddrops[17] = "DDERR_NODDROPSHW";

char aDderr_overlayn[24] = "DDERR_OVERLAYNOTVISIBLE";

char aDderr_nooverla[20] = "DDERR_NOOVERLAYDEST";

char aDderr_invalidp[22] = "DDERR_INVALIDPOSITION";

char aDderr_notaover[25] = "DDERR_NOTAOVERLAYSURFACE";

char aDderr_exclusiv[30] = "DDERR_EXCLUSIVEMODEALREADYSET";

char aDderr_notflipp[19] = "DDERR_NOTFLIPPABLE";

char aDderr_cantdupl[20] = "DDERR_CANTDUPLICATE";

char aDderr_notlocke[16] = "DDERR_NOTLOCKED";

char aDderr_cantcrea[19] = "DDERR_CANTCREATEDC";

char aDderr_nodc[11] = "DDERR_NODC";

char aDderr_wrongmod[16] = "DDERR_WRONGMODE";

char aDderr_implicit[24] = "DDERR_IMPLICITLYCREATED";

char aDderr_notpalet[20] = "DDERR_NOTPALETTIZED";

char aDderr_unsupp_0[22] = "DDERR_UNSUPPORTEDMODE";

char aDderr_nomipmap[17] = "DDERR_NOMIPMAPHW";

char aDderr_invalids[25] = "DDERR_INVALIDSURFACETYPE";

char aDderr_dcalread[23] = "DDERR_DCALREADYCREATED";

char aDderr_cantpage[19] = "DDERR_CANTPAGELOCK";

char aDderr_cantpa_0[21] = "DDERR_CANTPAGEUNLOCK";

char aDderr_notpagel[20] = "DDERR_NOTPAGELOCKED";

char aDderr_notiniti[21] = "DDERR_NOTINITIALIZED";

char aUnknownError[14] = "Unknown Error";

char aDirectdrawEr_0[20] = "DirectDraw Error %s";

char aWt[3] = "wt";

char asc_5024B0[2] = "\\";

char asc_5024B4[2] = "\\";

char aS_15[4] = "%s\n";

char aS_2[6] = "(%s)\n";

char asc_5024C0[2] = "\\";

char aWt_0[3] = "wt";

char asc_5024C5[2] = "\\";

char asc_5024C7[2] = "\\";

char a__34[2] = ".";

char a___1[3] = "..";

char asc_5024CE[2] = "\\";

char a__35[2] = ".";

char a___2[3] = "..";

char aAb_0[3] = "ab";

char aA_3[2] = "a";

char aWb_8[3] = "wb";

char aW_7[2] = "w";

char aRb_10[3] = "rb";

char aR_7[2] = "r";

char a__31[5] = "\\*.*";

char asc_5024EA[2] = "\\";

char asc_5024EC[2] = "\\";

char asc_5024EE[2] = "\\";

char a__36[4] = "*.*";

char aLlrs[5] = "llrs";

char aWB[4] = "w+b";

char aRb_11[3] = "rb";

char aFacts_0[6] = "facts";

char asc_502524[2] = "\"";

char aFact_2[7] = "<Fact-";

char asc_502530[2] = ">";

char aDummyFact[13] = "<Dummy Fact>";

char asc_502544[2] = "(";

char asc_502548[2] = " ";

char asc_50254C[2] = ")";

char aFactmngr[9] = "FACTMNGR";

char aFactsMayNotBeR[52] = "Facts may not be retracted during pattern-matching\n";

char asc_502590[5] = "<== ";

char asc_502598[2] = "\n";

char aFactsMayNotBeA[51] = "Facts may not be asserted during pattern-matching\n";

char aNil_2[4] = "nil";

char asc_5025D4[5] = "==> ";

char a4iu[5] = "*4iu";

char aFactscommand[13] = "FactsCommand";

char aFacts_1[6] = "facts";

char aAssertcommand[14] = "AssertCommand";

char aAssert[7] = "assert";

char a1Z[4] = "1*z";

char aRetractcommand[15] = "RetractCommand";

char aRetract_0[8] = "retract";

char a11s[4] = "11s";

char aAssertstringfu[21] = "AssertStringFunction";

char aAssertString[14] = "assert-string";

char aStrAssert[11] = "str-assert";

char a00_1[3] = "00";

char aGetfactduplica[26] = "GetFactDuplicationCommand";

char aGetFactDuplica[21] = "get-fact-duplication";

char a11[3] = "11";

char aSetfactduplica[26] = "SetFactDuplicationCommand";

char aSetFactDuplica[21] = "set-fact-duplication";

char a1Wk[5] = "1*wk";

char aSavefactscomma[17] = "SaveFactsCommand";

char aSaveFacts[11] = "save-facts";

char a11k[4] = "11k";

char aLoadfactscomma[17] = "LoadFactsCommand";

char aLoadFacts[11] = "load-facts";

char a11y[4] = "11y";

char aFactindexfunct[18] = "FactIndexFunction";

char aFactIndex[11] = "fact-index";

char aFactAddressFac[42] = "fact-address, fact-index, or the symbol *";

char aFact[5] = "fact";

char asc_502790[2] = "*";

char aFactAddress_0[13] = "fact-address";

char aSymbolOrPositi[26] = "symbol or positive number";

char asc_5027CC[2] = "\n";

char aPositiveNumber[16] = "positive number";

char aLocal[6] = "local";

char aVisible[8] = "visible";

char aSymbolWithValu[35] = "symbol with value local or visible";

char aW_0[2] = "w";

char aSymbol_1[7] = "symbol";

char aLocalDeftempla[23] = "local deftemplate name";

char aDeftemplate_4[12] = "deftemplate";

char aVisibleDeftemp[25] = "visible deftemplate name";

char aR_0[2] = "r";

char aFunctionLoadFa[42] = "Function load-facts encountered an error\n";

char asc_502890[2] = " ";

char aAssertCommand[15] = "assert command";

char aW_1[2] = "w";

char a00_13[3] = "00";

char aClearcommand[13] = "ClearCommand";

char aClear[6] = "clear";

char aResetcommand[13] = "ResetCommand";

char aReset[6] = "reset";

char aCompilations[13] = "compilations";

char aMain[5] = "MAIN";

char aConstrct[9] = "CONSTRCT";

char aSomeConstructs[58] = "Some constructs are still in use. Clear cannot continue.\n";

char g_CLIPS_BsaveHeaderMagic[12] = { 1, 2, 3, 4, 'C', 'L', 'I', 'P', 'S', 0, 0, 0 };

char aBload[6] = "bload";

char aBload_0[6] = "BLOAD";

char aFile[6] = "File ";

char aIsNotABinaryCo[34] = " is not a binary construct file.\n";

char aIsAnIncompatib[44] = " is an incompatible binary construct file.\n";

char aTheClipsEnviro[45] = "The CLIPS environment could not be cleared.\n";

char aBinaryLoadCann[30] = "Binary load cannot continue.\n";

char aSkipping[11] = "\nSkipping ";

char aConstructsBeca[39] = " constructs because of unavailibility\n";

char aTheFollowingUn[39] = "The following undefined functions are ";

char aReferencedByTh[34] = "referenced by this binary image:\n";

char asc_502A88[4] = "   ";

char asc_502A8C[2] = "\n";

char aSomeConstruc_0[63] = "Some constructs are still in use by the current binary image:\n";

char aBinaryClearCan[31] = "Binary clear cannot continue.\n";

char aCannotLoad[13] = "Cannot load ";

char aConstructWithB[40] = " construct with binary load in effect.\n";

double g_Rules_MillisecondsPerSecond = 1000.0;

char aSystem_0[7] = "system";

char aRb_1[3] = "rb";

char aDepth[6] = "depth";

char aBreadth[8] = "breadth";

char aLex[4] = "lex";

char aMea[4] = "mea";

char aComplexity[11] = "complexity";

char aSimplicity[11] = "simplicity";

char aRandom_0[7] = "random";

char aSymbolWithVa_0[78] = "symbol with value depth, breadth, lex, mea, complexity, simplicity, or random";

char aUnknown_0[8] = "unknown";

char aAgenda_0[7] = "agenda";

char aActivations[12] = "activations";

char a11w[4] = "11w";

char aRefreshcommand[15] = "RefreshCommand";

char aRefresh[8] = "refresh";

char a01w[4] = "01w";

char aRefreshagendac[21] = "RefreshAgendaCommand";

char aRefreshAgenda[15] = "refresh-agenda";

char a00[3] = "00";

char aGetsalienceeva[29] = "GetSalienceEvaluationCommand";

char aGetSalienceEva[24] = "get-salience-evaluation";

char aSetsalienceeva[29] = "SetSalienceEvaluationCommand";

char aSetSalienceEva[24] = "set-salience-evaluation";

char aAgendacommand[14] = "AgendaCommand";

char aActivation_0[16] = "==> Activation ";

char asc_502D24[2] = "\n";

char aAgenda[7] = "AGENDA";

char asc_502D44[3] = ": ";

char aActivation_1[11] = "activation";

char aActivation[16] = "<== Activation ";

char aRuleName[10] = "rule name";

char aThisErrorOccur[50] = "This error occurred while evaluating the salience";

char aForRule[11] = " for rule ";

char aDotNewline_Agenda[3] = ".\n";

char aSalienceValueO[29] = "Salience value out of range ";

char aTo[5] = " to ";

char aSalienceValueM[42] = "Salience value must be an integer value.\n";

char aWhenDefined[13] = "when-defined";

char aWhenActivated[15] = "when-activated";

char aEveryCycle[12] = "every-cycle";

char aSymbolWithVa_1[63] = "symbol with value when-defined, when-activated, or every-cycle";

char aUnknown_1[8] = "unknown";

char asc_502E90[3] = ": ";

char asc_502E94[2] = "\n";

char aPrccode[8] = "PRCCODE";

char aExecutionHalte[48] = "Execution halted during the actions of defrule ";

char aDotNewline_RuleRuntime[3] = ".\n";

char aBreakingOnRule[18] = "Breaking on rule ";

char aRuleFiringLimi[27] = "rule firing limit reached\n";

char aRulesFired[13] = " rules fired";

char aRunTimeIs[21] = "        Run time is ";

char aMain_0[5] = "MAIN";

char aFocus[11] = "<== Focus ";

char aTo_0[5] = " to ";

char aFocus_0[11] = "==> Focus ";

char aFrom[7] = " from ";

char aStatistics[11] = "statistics";

char aFocus_1[6] = "focus";

char aRule[6] = "Rule ";

char aDoesNotHaveABr[34] = " does not have a breakpoint set.\n";

char aInitializeInst[20] = "initialize-instance";

char aInitializeinst[26] = "InitializeInstanceCommand";

char aActiveInitiali[27] = "active-initialize-instance";

char aMakeInstance[14] = "make-instance";

char aMakeinstanceco[20] = "MakeInstanceCommand";

char aActiveMakeInst[21] = "active-make-instance";

char a00_3[3] = "00";

char aInitSlots[11] = "init-slots";

char aDeleteinstance[22] = "DeleteInstanceCommand";

char aDeleteInstance[16] = "delete-instance";

char a1E[4] = "1*e";

char aUnmakeinstance[22] = "UnmakeInstanceCommand";

char aUnmakeInstance[16] = "unmake-instance";

char a3w[4] = "*3w";

char aInstancescomma[17] = "InstancesCommand";

char aInstances[10] = "instances";

char aPpinstancecomm[18] = "PPInstanceCommand";

char aPpinstance[11] = "ppinstance";

char a11w_4[4] = "11w";

char aSymboltoinstan[21] = "SymbolToInstanceName";

char aSymbolToInstan[24] = "symbol-to-instance-name";

char a11p[4] = "11p";

char aInstancenameto[21] = "InstanceNameToSymbol";

char aInstanceNameTo[24] = "instance-name-to-symbol";

char a12eep[6] = "12eep";

char aInstanceaddres[23] = "InstanceAddressCommand";

char aInstanceAddres[17] = "instance-address";

char a11_2[3] = "11";

char aInstanceaddr_0[24] = "InstanceAddressPCommand";

char aInstanceAddr_0[18] = "instance-addressp";

char aInstancenamepc[21] = "InstanceNamePCommand";

char aInstanceNamep[15] = "instance-namep";

char a11e[4] = "11e";

char aInstancenameco[20] = "InstanceNameCommand";

char aInstanceName[14] = "instance-name";

char aInstancepcomma[17] = "InstancePCommand";

char aInstancep[10] = "instancep";

char aInstanceexistp[22] = "InstanceExistPCommand";

char aInstanceExistp[16] = "instance-existp";

char aClasscommand_0[13] = "ClassCommand";

char aClass[6] = "class";

char asc_5033CC[2] = "*";

char aDefmoduleName[15] = "defmodule name";

char aInherit[8] = "inherit";

char aKeywordInherit[18] = "keyword \"inherit\"";

char asc_5033FC[2] = "\n";

char asc_503400[3] = ":\n";

char aInstance_1[9] = "instance";

char aMkins[12] = "***MKINS***";

char asc_503458[2] = " ";

char aInscom[7] = "INSCOM";

char aUndefinedTypeI[28] = "Undefined type in function ";

char a__32[3] = ".\n";

char aInstanceAddr_4[49] = "instance-address, instance-name, or the symbol *";

char aModuleName[12] = "module name";

char aInstanceNameIn[42] = "instance name, instance address or symbol";

char asc_5034F8[4] = "   ";

char asc_5034FC[2] = "(";

char asc_503500[2] = ")";

char aFunctionParser[60] = "Function parsers can only be added for existing functions.\n";

char aOnlyExistingFu[98] = "Only existing functions can be marked as using sequence expansion arguments/overloadable or not.\n";

char aExternalAddres[17] = "external address";

char aInstanceAddr_1[43] = "instance address, instance name, or symbol";

char aFloat_0[6] = "float";

char aIntegerFloatOr[26] = "integer, float, or symbol";

char aInstanceAddr_2[66] = "instance address, instance name, fact address, integer, or symbol";

char aSymbolString_0[33] = "symbol, string, or instance name";

char aSymbolOrString[17] = "symbol or string";

char aInteger_0[8] = "integer";

char aMultifield[11] = "multifield";

char aIntegerOrFloat[17] = "integer or float";

char aInstanceName_0[14] = "instance name";

char aInstanceNameOr[24] = "instance name or symbol";

char aMultifieldSymb[30] = "multifield, symbol, or string";

char aString_0[7] = "string";

char aSymbol_0[7] = "symbol";

char aInstanceAddr_3[17] = "instance address";

char aFactAddress[13] = "fact-address";

char aFactAddressInt[33] = "fact-address, integer, or symbol";

char aNonVoidReturnV[22] = "non-void return value";

char aUnknownArgumen[22] = "unknown argument type";

char aRtnlexeme[10] = "RtnLexeme";

char aRtndouble[10] = "RtnDouble";

char aRtnlong[8] = "RtnLong";

char aArgacces[9] = "ARGACCES";

char aFunction[10] = "Function ";

char aExpectedAtLeas[20] = " expected at least ";

char aAndNoMoreThan[19] = " and no more than ";

char aArguments_[13] = " arguments.\n";

char aFloat_1[6] = "float";

char aInteger_1[8] = "integer";

char aSymbol_2[7] = "symbol";

char aString_1[7] = "string";

char aMultifield_0[11] = "multifield";

char aIntegerOrFlo_0[17] = "integer or float";

char aSymbolOrStri_0[17] = "symbol or string";

char aInstanceName_1[14] = "instance name";

char aInstanceAddr_6[17] = "instance address";

char aInstanceAddr_5[34] = "instance address or instance name";

char aT[2] = "t";

char aT_0[2] = "T";

char aFileName[10] = "file name";

char aWasUnableToOpe[26] = " was unable to open file ";

char aDotNewline_FileError[3] = ".\n";

char aDefmoduleNam_0[15] = "defmodule name";

char aReceivedAReque[35] = " received a request from function ";

char aForArgument[16] = " for argument #";

char aWhichIsNonExis[24] = " which is non-existent\n";

char aExpectedExactl[19] = " expected exactly ";

char aExpectedNoMore[24] = " expected no more than ";

char aGeneratedAnIll[42] = " generated an illegal argument check for ";

char aArgumentS[14] = " argument(s)\n";

char aExpectedArgume[21] = " expected argument #";

char aToBeOfType[16] = " to be of type ";

char asc_503A24[2] = "\n";

char aWhichIsNotOfTy[23] = " which is not of type ";

char aTrue[5] = "TRUE";

char aFalse[6] = "FALSE";

char aOo[4] = "+oo";

char aOo_0[4] = "-oo";

char aInsfun[7] = "INSFUN";

char aCannotModifyRe[45] = "Cannot modify reactive instance slots while\n";

char aPatternMatchin[35] = "  pattern-matching is in process.\n";

char aSharedSlot[17] = "::= shared slot ";

char aLocalSlot[16] = "::= local slot ";

char aInInstance[14] = " in instance ";

char asc_503AF0[5] = " <- ";

char asc_503AF8[2] = "\n";

char aUnableToPatter[40] = "Unable to pattern-match on shared slot ";

char aInClass[11] = " in class ";

char aDotNewline_InstanceError[3] = ".\n";

char aIllegalForSing[27] = " illegal for single-field ";

char aVoidFunctionIl[33] = "Void function illegal value for ";

char aCstrnchk[9] = "CSTRNCHK";

char aFor[6] = " for ";

char aExpectedAVal_1[39] = "Expected a valid instance in function ";

char aNoSuchInstance[18] = "No such instance ";

char aInFunction[14] = " in function ";

char aNoSuchSlot[14] = "No such slot ";

char aInvalidInstanc[38] = "Invalid instance-address in function ";

char aSlot[6] = "slot ";

char aOfInstance[15] = " of instance [";

char asc_503C24[2] = "]";

char aOfClass[11] = " of class ";

char aFoundIn[11] = " found in ";

char asc_503C40[2] = "[";

char aOf[6] = "] of ";

char aStaleInstance[18] = "<stale instance [";

char asc_503C60[3] = "]>";

char aDummyInstanc_0[19] = "\"<Dummy Instance>\"";

char asc_503C78[2] = "\"";

char aDummyInstanc_1[17] = "<Dummy Instance>";

char aStaleInstanc_0[17] = "<Stale Instance-";

char asc_503CA4[2] = ">";

char aInstance_7[11] = "<Instance-";

char aViolationOfFun[47] = "violation of function exception specification!";

char asc_503EA4[2] = "\"";

char aPointer[10] = "<Pointer-";

char asc_503EB8[2] = ">";

char asc_503EBC[2] = "[";

char asc_503EC0[2] = "]";

char aUnknownAtomTyp[20] = "<unknown atom type>";

char aForATotalOf[16] = "For a total of ";

char asc_503EE8[2] = " ";

char a__14[3] = ".\n";

char asc_503EF0[2] = "\n";

char asc_503EF4[3] = "] ";

char aWarning[12] = "] WARNING: ";

char aPrntutil[9] = "PRNTUTIL";

char aUnableToFind[16] = "Unable to find ";

char aUnableToDele_3[18] = "Unable to delete ";

char aThe_0[5] = "The ";

char aHasAlreadyBeen[27] = " has already been parsed.\n";

char aSyntaxError[13] = "Syntax Error";

char aCheckAppropria[33] = ":  Check appropriate syntax for ";

char aLocalVariables[40] = "Local variables can not be accessed by ";

char aClipsSystemErr[29] = "\n*** CLIPS SYSTEM ERROR ***\n";

char aId[6] = "ID = ";

char aClipsDataStruc[66] = "CLIPS data structures are in an inconsistent or corrupted state.\n";

char aThisErrorMayHa[64] = "This error may have occurred from errors in user defined code.\n";

char asc_504060[28] = "**************************\n";

char aAttemptToDivid[30] = "Attempt to divide by zero in ";

char aFunction__0[12] = " function.\n";

char a_0[3] = ".0";

char a00_16[3] = "00";

char aExitcommand[12] = "ExitCommand";

char aExit[5] = "exit";

char aS_1[3] = "%s";

char aRouter[7] = "ROUTER";

char aLogicalName[14] = "Logical name ";

char aWasNotRecogniz[36] = " was not recognized by any routers\n";

CHAR aHandleIsNull[] = "handle is null\n";

CHAR aDdcopybitmapFa[] = "ddcopybitmap failed\n";

CHAR OutputString[] = "createcompatible dc failed\n";

CHAR aLockResourceFa[] = "lock resource failed\n";

char aCon_0[4] = "con";

_UNKNOWN g_Rules_BuiltinSentinelAddress;

char aFacts_2[6] = "facts";

char aDeftemplate_5[12] = "deftemplate";

char aDeftemplate_0[12] = "deftemplate";

char a01w_1[4] = "01w";

char aGetDeftemplate[21] = "get-deftemplate-list";

char a11w_1[4] = "11w";

char aUndeftemplatec[21] = "UndeftemplateCommand";

char aUndeftemplate[14] = "undeftemplate";

char aDeftemplatemod[26] = "DeftemplateModuleFunction";

char aDeftemplateMod[19] = "deftemplate-module";

char aListdeftemplat[24] = "ListDeftemplatesCommand";

char aListDeftemplat[18] = "list-deftemplates";

char aPpdeftemplatec[21] = "PPDeftemplateCommand";

char aPpdeftemplate[14] = "ppdeftemplate";

char aInitialFact_2[13] = "initial-fact";

char aAll_1[4] = "all";

char aWatch[6] = "watch";

char aWatchableSymbo[17] = "watchable symbol";

char aUnwatch[8] = "unwatch";

char aOn[7] = " = on\n";

char aOff[8] = " = off\n";

char aListWatchItems[17] = "list-watch-items";

char a1W[5] = "1**w";

char aWatchcommand[13] = "WatchCommand";

char aUnwatchcommand[15] = "UnwatchCommand";

char a0W[5] = "0**w";

char aListwatchitems[22] = "ListWatchItemsCommand";

char a11z[4] = "11z";

char aFactexistpfunc[19] = "FactExistpFunction";

char aFactExistp[12] = "fact-existp";

char aFactrelationfu[21] = "FactRelationFunction";

char aFactRelation[14] = "fact-relation";

char a22Zw[6] = "22*zw";

char aFactslotvaluef[22] = "FactSlotValueFunction";

char aFactSlotValue[16] = "fact-slot-value";

char aFactslotnamesf[22] = "FactSlotNamesFunction";

char aFactSlotNames[16] = "fact-slot-names";

char a01w_0[4] = "01w";

char aGetfactlistfun[20] = "GetFactListFunction";

char aGetFactList[14] = "get-fact-list";

char aImplied[8] = "implied";

char aDefmoduleNam_1[15] = "defmodule name";

char aFactAddressOrF[27] = "fact-address or fact-index";

char aFacts_3[6] = "facts";

char aFacts_4[6] = "facts";

char aIncludeFactbld[22] = "#include \"factbld.h\"\n";

char aStructFactpatt[23] = "struct factPatternNode";

char asc_504530[2] = "{";

char a0DDD[13] = ",0,%d,%d,%d,";

char aNull_14[7] = ",NULL,";

char aSD_LdLd_1[17] = ",&%s%d_%ld[%ld],";

char aNull_12[6] = "NULL,";

char aSD_LdLd_2[16] = "&%s%d_%ld[%ld],";

char aNull_13[6] = "NULL}";

char aSD_LdLd_3[16] = "&%s%d_%ld[%ld]}";

char aNull_16[5] = "NULL";

char aSD_LdLd_4[15] = "&%s%d_%ld[%ld]";

char aMultifieldStr[15] = "multifield-str";

char asc_5045B8[2] = "(";

char asc_5045BC[2] = " ";

char asc_5045C0[2] = ")";

char aTmpltdef[9] = "TMPLTDEF";

char aInvalidSlot[14] = "Invalid slot ";

char aNotDefinedInCo[43] = " not defined in corresponding deftemplate ";

char a__10[3] = ".\n";

char aTheSingleField[23] = "The single field slot ";

char aCanOnlyContain[41] = " can only contain a single field value.\n";

char aTmpltfun[9] = "TMPLTFUN";

char aAttemptedToAss[41] = "Attempted to assert a multifield value \n";

char aIntoTheSingleF[28] = "into the single field slot ";

char aUnknown_2[12] = "<<unknown>>";

char aOfDeftemplate[17] = " of deftemplate ";

char aCstrnchk_0[9] = "CSTRNCHK";

char aSlotValue[12] = "Slot value ";

char asc_5046F0[2] = " ";

char aALiteralSlotVa[21] = "A literal slot value";

char aLiteralSlotVal[20] = "Literal slot values";

char asc_504720[2] = "(";

char asc_504724[2] = ")";

char aDeftemplate_6[12] = "deftemplate";

char aFactmch[8] = "FACTMCH";

char aThisErrorOcc_0[49] = "This error occurred in the fact pattern network\n";

char aCurrentlyActiv[27] = "   Currently active fact: ";

char asc_504794[2] = "\n";

char aDrive[6] = "DRIVE";

char aThisErrorOcc_1[41] = "This error occurred in the join network\n";

char asc_504874[2] = "\n";

char aNone[6] = "None\n";

char asc_504880[2] = "\n";

char asc_504884[2] = ",";

char aDependencies_0[13] = "dependencies";

char aDependents_0[11] = "dependents";

char aEvaluatn[9] = "EVALUATN";

char aVariable[10] = "Variable ";

char aIsUnbound[13] = " is unbound\n";

char aUnknownprintty[18] = "<UnknownPrintType";

char asc_5048FC[2] = ">";

char aCreate_1[8] = "create$";

char aStdin_1[6] = "stdin";

char asc_504990[2] = "\n";

char aClips[8] = "CLIPS> ";

char aCommand_2[8] = "command";

char aStdout[7] = "stdout";

char aCommline[9] = "COMMLINE";

char aExpectedACon_0[46] = "Expected a '(', constant, or global variable\n";

char aExpectedAComma[21] = "Expected a command.\n";

char aError_1[9] = "\nERROR:\n";

char aAnd_2[4] = "and";

char aNot_2[4] = "not";

char aOr_2[3] = "or";

char aTest[5] = "test";

char aLogical[8] = "logical";

char aExists[7] = "exists";

char aForall[7] = "forall";

char aDefrules[9] = "defrules";

char aDefrule[8] = "defrule";

char aNil[4] = "nil";

char g_Rules_DefaultEmptyStringConstraint[4] = { '\0', '\0', '\0', '\0' };

char asc_504A54[2] = " ";

char aNone_0[5] = "NONE";

char aDerive[7] = "DERIVE";

char asc_504A98[2] = ")";

char aDefault_0[8] = "DEFAULT";

char aTheDefaultValu[72] = "The default value for a single field slot must be a single field value\n";

char aDefmodules[11] = "defmodules";

char aDefmodule[10] = "defmodule";

char a00_0[3] = "00";

char aGetcurrentmodu[24] = "GetCurrentModuleCommand";

char aGetCurrentModu[19] = "get-current-module";

char a11w_0[4] = "11w";

char aSetcurrentmodu[24] = "SetCurrentModuleCommand";

char aSetCurrentModu[19] = "set-current-module";

char aMain_1[5] = "MAIN";

char aModuldef[9] = "MODULDEF";

char aIllegalUseOfTh[38] = "Illegal use of the module specifier.\n";

char aString[7] = "string";

char aAssert_1[7] = "assert";

char asc_504BB8[2] = ")";

char aProgn_3[6] = "progn";

char asc_504BF4[2] = "=";

char asc_504BF8[2] = ":";

char aARelationName[16] = "a relation name";

char aDeftemplate[12] = "deftemplate";

char aImpliedDeftemp[20] = "implied deftemplate";

char asc_504C2C[2] = " ";

_BYTE g_Rules_DefaultZeroBitmapValue[4] = { 0, 0, 0, 0 };

char aAssert_str[11] = "assert_str";

char aFactrhs[8] = "FACTRHS";

char aTemplate[10] = "Template ";

char aDoesNotExistFo[29] = " does not exist for assert.\n";

char aAmbiguousRefer[24] = "Ambiguous reference to ";

char asc_504CA8[2] = " ";

char a_ItIsImportedF[45] = ".\nIt is imported from more than one module.\n";

char asc_504CDC[3] = ":\n";

char asc_504CE0[4] = "   ";

char asc_504CE4[2] = "\n";

char aDeftemplates[13] = "deftemplates";

char aDeftemplate_1[12] = "deftemplate";

char aAnd[4] = "and";

char aOr[3] = "or";

char aEq[3] = "eq";

char aNeq[4] = "neq";

char aNot[4] = "not";

char aUnknown[8] = "unknown";

char aQuestion_LexerSingleFieldVarPrefix[2] = "?";

char aQuestion_LexerMultiFieldVarPrefix[3] = "$?";

char asc_504D34[2] = "(";

char asc_504D38[2] = ")";

char asc_504D3C[2] = "~";

char asc_504D40[2] = "|";

char asc_504D44[2] = "&";

char aStop[5] = "stop";

char g_Lexer_EmptyQuotedStringBuffer[4] = { '\0', '\0', '\0', '\0' };

char aUnprintableCha[28] = "<<<unprintable character>>>";

char asc_504D70[2] = "[";

char asc_504D74[2] = "]";

char aEncounteredEnd[50] = "\nEncountered End-Of-File while scanning a string\n";

char aScanner[8] = "SCANNER";

char aOverOrUnderflo[36] = "Over or underflow of long integer.\n";

char aQuestion_PrintSingleFieldVarPrefix[2] = "?";

char aQuestion_PrintMultiFieldVarPrefix[3] = "$?";

char asc_504DE0[2] = "(";

char asc_504DE4[2] = " ";

char asc_504DE8[2] = ")";

char aCstrnbin[9] = "CSTRNBIN";

char aConstraintsAre[47] = "Constraints are not saved with a binary image\n";

char aWhenDynamicCon[49] = "  when dynamic constraint checking is disabled.\n";

char aBsave_1[6] = "BSAVE";

char aCannotPerformA[64] = "Cannot perform a binary save while a binary load is in effect.\n";

char aWb_3[3] = "wb";

char a00_14[3] = "00";

char aGdccommand[11] = "GDCCommand";

char aGetDynamicCons[32] = "get-dynamic-constraint-checking";

char a11_0[3] = "11";

char aSdccommand[11] = "SDCCommand";

char aSetDynamicCons[32] = "set-dynamic-constraint-checking";

char aGsccommand[11] = "GSCCommand";

char aGetStaticConst[31] = "get-static-constraint-checking";

char aSsccommand[11] = "SSCCommand";

char aSetStaticConst[31] = "set-static-constraint-checking";

char aDeffacts[9] = "deffacts";

char aDefgeneric[11] = "defgeneric";

char aDefgenerics[12] = "defgenerics";

char aDefmethods[11] = "defmethods";

char aDefmethod[10] = "defmethod";

char a11w_2[4] = "11w";

char aUndefgeneric[13] = "undefgeneric";

char a22Wg[6] = "22*wg";

char aUndefmethodcom[19] = "UndefmethodCommand";

char aUndefmethod[12] = "undefmethod";

char a00_2[3] = "00";

char aCallnextmethod[15] = "CallNextMethod";

char aCallNextMethod[17] = "call-next-method";

char a2Wi[6] = "2**wi";

char aCallSpecificMe[21] = "call-specific-method";

char aOverrideNextMe[21] = "override-next-method";

char aNextMethodp[13] = "next-methodp";

char aGnrcCurrentArg[19] = "(gnrc-current-arg)";

char aPpdefgenericco[20] = "PPDefgenericCommand";

char aPpdefgeneric[13] = "ppdefgeneric";

char a01[3] = "01";

char aListdefgeneric[23] = "ListDefgenericsCommand";

char aListDefgeneric[17] = "list-defgenerics";

char a22Wi[6] = "22*wi";

char aPpdefmethodcom[19] = "PPDefmethodCommand";

char aPpdefmethod[12] = "ppdefmethod";

char a01w_2[4] = "01w";

char aListdefmethods[22] = "ListDefmethodsCommand";

char aListDefmethods[16] = "list-defmethods";

char a1W_0[5] = "1**w";

char aPreviewgeneric[15] = "PreviewGeneric";

char aPreviewGeneric[16] = "preview-generic";

char aGetdefgenericl[26] = "GetDefgenericListFunction";

char aGetDefgenericL[20] = "get-defgeneric-list";

char aGetdefmethodli[24] = "GetDefmethodListCommand";

char aGetDefmethodLi[19] = "get-defmethod-list";

char a22iw[5] = "22iw";

char aGetmethodrestr[29] = "GetMethodRestrictionsCommand";

char aGetMethodRestr[24] = "get-method-restrictions";

char aGetdefgenericm[27] = "GetDefgenericModuleCommand";

char aDefgenericModu[18] = "defgeneric-module";

char a11_1[3] = "11";

char aClasscommand[13] = "ClassCommand";

char aType[5] = "type";

char aGenericFunctio[18] = "generic-functions";

char aMethods[8] = "methods";

char asc_50529C[2] = "*";

char aGenrccom[9] = "GENRCCOM";

char aNoSuchGenericF[26] = "No such generic function ";

char aInFunctionUnde[27] = " in function undefmethod.\n";

char aExpectedAVal_0[56] = "Expected a valid method index in function undefmethod.\n";

char aPrntutil_0[9] = "PRNTUTIL";

char aUnableToDelete[25] = "Unable to delete method ";

char asc_505344[3] = " #";

char a__15[3] = ".\n";

char aIncompleteMeth[47] = "Incomplete method specification for deletion.\n";

char asc_50537C[2] = "\n";

char aMethod_1[7] = "method";

char aCannotRemoveIm[68] = "Cannot remove implicit system function method for generic function ";

char aWatch_1[6] = "watch";

char aUnwatch_0[8] = "unwatch";

char aListWatchIte_1[17] = "list-watch-items";

char asc_5053F0[3] = ":\n";

char asc_5053F4[4] = "   ";

char aGenericFunct_4[22] = "generic function name";

char aMethodIndex[13] = "method index";

char asc_505420[2] = " ";

char aOn_3[7] = " = on\n";

char aOff_3[8] = " = off\n";

char aDeffunction[12] = "deffunction";

char aDeffunctions[13] = "deffunctions";

char aDeffunctionHea[20] = "deffunction-headers";

char a11w_3[4] = "11w";

char aUndeffunction[14] = "undeffunction";

char a01_0[3] = "01";

char aListdeffunctio[24] = "ListDeffunctionsCommand";

char aListDeffunctio[18] = "list-deffunctions";

char aPpdeffunctionc[21] = "PPDeffunctionCommand";

char aPpdeffunction[14] = "ppdeffunction";

char aGetdeffunction[27] = "GetDeffunctionListFunction";

char aGetDeffunction[21] = "get-deffunction-list";

char aGetdeffuncti_0[28] = "GetDeffunctionModuleCommand";

char aDeffunctionMod[19] = "deffunction-module";

char aDffnxfun[9] = "DFFNXFUN";

char aDeffunction_6[13] = "Deffunction ";

char aOnlyPartiallyD[59] = " only partially deleted due to usage by other constructs.\n";

char aDeffunction_1[14] = "(deffunction ";

char asc_5055B4[3] = " (";

char aQuestionP_DeffunctionArgumentPrefix[3] = "?p";

char asc_5055BC[2] = " ";

char a_wildargs[15] = "$?wildargs))\n\n";

char asc_5055D0[5] = "))\n\n";

char aDefglobals[11] = "defglobals";

char aDefglobal[10] = "defglobal";

char aDefglobalWatchPrefix[7] = ":== ?*";

char asc_5055F8[7] = "* ==> ";

char asc_505600[6] = " <== ";

char asc_505608[2] = "\n";

char aGlobldef[9] = "GLOBLDEF";

char aGlobalVariab_0[19] = "Global variable ?*";

char aIsUnbound_[15] = "* is unbound.\n";

char aIsA[5] = "is-a";

char aName[5] = "name";

char aInitialObject[15] = "initial-object";

char aObject_0[7] = "OBJECT";

char aPrimitive[10] = "PRIMITIVE";

char aUser[5] = "USER";

char aNumber_1[7] = "NUMBER";

char aInteger_2[8] = "INTEGER";

char aFloat_2[6] = "FLOAT";

char aLexeme_0[7] = "LEXEME";

char aSymbol_3[7] = "SYMBOL";

char aString_2[7] = "STRING";

char aMultifield_1[11] = "MULTIFIELD";

char aAddress_0[8] = "ADDRESS";

char aExternalAddr_0[17] = "EXTERNAL-ADDRESS";

char aFactAddress_1[13] = "FACT-ADDRESS";

char aInstance_3[9] = "INSTANCE";

char aInstanceAddr_7[17] = "INSTANCE-ADDRESS";

char aInstanceName_2[14] = "INSTANCE-NAME";

char aInitialObjec_0[15] = "INITIAL-OBJECT";

char aDefclass[9] = "defclass";

char aDefclasses[11] = "defclasses";

char a11w_5[4] = "11w";

char aUndefclass[11] = "undefclass";

char a01_1[3] = "01";

char aListDefclasses[16] = "list-defclasses";

char aPpdefclasscomm[18] = "PPDefclassCommand";

char aPpdefclass[11] = "ppdefclass";

char aDescribeclassc[21] = "DescribeClassCommand";

char aDescribeClass[15] = "describe-class";

char a01w_3[4] = "01w";

char aBrowseclassesc[21] = "BrowseClassesCommand";

char aBrowseClasses[15] = "browse-classes";

char aGetdefclasslis[24] = "GetDefclassListFunction";

char aGetDefclassLis[18] = "get-defclass-list";

char a22w[4] = "22w";

char aSuperclasspcom[19] = "SuperclassPCommand";

char aSuperclassp[12] = "superclassp";

char aSubclasspcomma[17] = "SubclassPCommand";

char aSubclassp[10] = "subclassp";

char aClassexistpcom[19] = "ClassExistPCommand";

char aClassExistp[13] = "class-existp";

char a23w[4] = "23w";

char aMessagehandler[28] = "MessageHandlerExistPCommand";

char aMessageHandler[23] = "message-handler-existp";

char aClassabstractp[22] = "ClassAbstractPCommand";

char aClassAbstractp[16] = "class-abstractp";

char aClassreactivep[22] = "ClassReactivePCommand";

char aClassReactivep[16] = "class-reactivep";

char a12w[4] = "12w";

char aClassslotscomm[18] = "ClassSlotsCommand";

char aClassSlots[12] = "class-slots";

char aClasssuperclas[25] = "ClassSuperclassesCommand";

char aClassSuperclas[19] = "class-superclasses";

char aClasssubclasse[23] = "ClassSubclassesCommand";

char aClassSubclasse[17] = "class-subclasses";

char a02w[4] = "02w";

char aGetdefmessageh[29] = "GetDefmessageHandlersListCmd";

char aGetDefmessageH[28] = "get-defmessage-handler-list";

char aSlotexistpcomm[18] = "SlotExistPCommand";

char aSlotExistp[12] = "slot-existp";

char aSlotfacetscomm[18] = "SlotFacetsCommand";

char aSlotFacets[12] = "slot-facets";

char aSlotsourcescom[19] = "SlotSourcesCommand";

char aSlotSources[13] = "slot-sources";

char aSlottypescomma[17] = "SlotTypesCommand";

char aSlotTypes[11] = "slot-types";

char aSlotallowedval[25] = "SlotAllowedValuesCommand";

char aSlotAllowedVal[20] = "slot-allowed-values";

char aSlotrangecomma[17] = "SlotRangeCommand";

char aSlotRange[11] = "slot-range";

char aSlotcardinalit[23] = "SlotCardinalityCommand";

char aSlotCardinalit[17] = "slot-cardinality";

char a22we[5] = "22we";

char aSlotwritablepc[21] = "SlotWritablePCommand";

char aSlotWritablep[15] = "slot-writablep";

char aSlotinitablepc[21] = "SlotInitablePCommand";

char aSlotInitablep[15] = "slot-initablep";

char aSlotpublicpcom[19] = "SlotPublicPCommand";

char aSlotPublicp[13] = "slot-publicp";

char aSlotdirectacce[25] = "SlotDirectAccessPCommand";

char aSlotDirectAcce[20] = "slot-direct-accessp";

char aGetdefclassmod[25] = "GetDefclassModuleCommand";

char aDefclassModule[16] = "defclass-module";

char aInstances_0[10] = "instances";

char aSlots[6] = "slots";

char aPrccode_0[8] = "PRCCODE";

char aDuplicatePar_0[40] = "Duplicate parameter names not allowed.\n";

char aNoParameters_0[49] = "No parameters allowed after wildcard parameter.\n";

char asc_505C54[2] = " ";

char asc_505C58[2] = ")";

char aUndefinedVaria[20] = "Undefined variable ";

char aReferencedIn[16] = " referenced in ";

char aDotNewline_ExpressionError[3] = ".\n";

char aBind_1[5] = "bind";

char aExecutionHal_0[40] = "Execution halted during the actions of ";

char asc_505CB4[3] = " (";

char asc_505CB8[3] = ")\n";

char aFunctionsWitho[49] = "Functions without a return value are illegal as ";

char aArguments__0[13] = " arguments.\n";

char aThisErrorOcc_3[48] = "This error occurred while evaluating arguments ";

char aForThe[9] = "for the ";

char aUnboundIn[13] = " unbound in ";

char aUnbound_[11] = " unbound.\n";

char a11k_4[4] = "11k";

char aBatchcommand[13] = "BatchCommand";

char aBatch[6] = "batch";

char aBatchstarcomma[17] = "BatchStarCommand";

char aBatch_0[7] = "batch*";

char aDribbleoncomma[17] = "DribbleOnCommand";

char aDribbleOn[11] = "dribble-on";

char a00_4[3] = "00";

char aDribbleoffcomm[18] = "DribbleOffCommand";

char aDribbleOff[12] = "dribble-off";

char aSavecommand[12] = "SaveCommand";

char aSave[5] = "save";

char aLoadcommand[12] = "LoadCommand";

char aLoad[5] = "load";

char aLoadstarcomman[16] = "LoadStarCommand";

char aLoad_0[6] = "load*";

char aBsavecommand[13] = "BsaveCommand";

char aBsave[6] = "bsave";

char aBloadcommand[13] = "BloadCommand";

char aBload_1[6] = "bload";

char aStdout_2[7] = "stdout";

char aStdin_2[6] = "stdin";

char aDribble[8] = "dribble";

char aS_3[3] = "%s";

char aW_3[2] = "w";

char aR_1[2] = "r";

char aR_2[2] = "r";

char aError_2[9] = "\nERROR:\n";

char asc_505E94[2] = "\n";

char aCstrcpsr[9] = "CSTRCPSR";

char aExpectedTheBeg[40] = "Expected the beginning of a construct.\n";

char aMissingNameFor[18] = "Missing name for ";

char aConstruct[12] = " construct\n";

char asc_505F2C[3] = "::";

char aCannotRedefine[17] = "Cannot redefine ";

char asc_505F44[2] = " ";

char aWhileItIsInUse[22] = " while it is in use.\n";

char aRedefining[12] = "Redefining ";

char aDefining[10] = "Defining ";

char asc_505F78[3] = ": ";

char asc_505F7C[5] = "\n   ";

char aCannotDefine[15] = "Cannot define ";

char aBecauseOfAnImp[38] = " because of an import/export conflict";

char aDotNewline_ConstructError[3] = ".\n";

char aCausedByThe[16] = " caused by the ";

char aIffunction[11] = "IfFunction";

char aIf[3] = "if";

char aWhilefunction[14] = "WhileFunction";

char aWhile[6] = "while";

char aLoopforcountfu[21] = "LoopForCountFunction";

char aLoopForCount[15] = "loop-for-count";

char aGetloopcount[13] = "GetLoopCount";

char aGetLoopCount[17] = "(get-loop-count)";

char aBindfunction[13] = "BindFunction";

char aBind[5] = "bind";

char aPrognfunction[14] = "PrognFunction";

char aProgn[6] = "progn";

char aReturnfunction[15] = "ReturnFunction";

char aReturn[7] = "return";

char aBreakfunction[14] = "BreakFunction";

char aBreak[6] = "break";

char aSwitchfunction[15] = "SwitchFunction";

char aSwitch[7] = "switch";

char a00_5[3] = "00";

char aGensymfunction[15] = "GensymFunction";

char aGensym[7] = "gensym";

char aGensymstarfunc[19] = "GensymStarFunction";

char aGensym_0[8] = "gensym*";

char a11i_1[4] = "11i";

char aSetgenfunction[15] = "SetgenFunction";

char aSetgen[7] = "setgen";

char a1K[4] = "1*k";

char aGensystem[10] = "gensystem";

char aSystem[7] = "system";

char a11q[4] = "11q";

char aLengthfunction[15] = "LengthFunction";

char aLength[7] = "length";

char aLength_0[8] = "length$";

char aGentime[8] = "gentime";

char aTime[5] = "time";

char aRandomfunction[15] = "RandomFunction";

char aRandom[7] = "random";

char aSeedfunction[13] = "SeedFunction";

char aSeed[5] = "seed";

char a11w_6[4] = "11w";

char aConservememcom[19] = "ConserveMemCommand";

char aConserveMem[13] = "conserve-mem";

char aReleasememcomm[18] = "ReleaseMemCommand";

char aReleaseMem[12] = "release-mem";

char aMemusedcommand[15] = "MemUsedCommand";

char aMemUsed[9] = "mem-used";

char aMemrequestscom[19] = "MemRequestsCommand";

char aMemRequests[13] = "mem-requests";

char aOptionscommand[15] = "OptionsCommand";

char aOptions[8] = "options";

char aExpandfunccall[15] = "ExpandFuncCall";

char aExpansionCall[17] = "(expansion-call)";

char a11m[4] = "11m";

char aDummyexpandfun[26] = "DummyExpandFuncMultifield";

char aExpand[8] = "expand$";

char aSetEvaluationE[23] = "(set-evaluation-error)";

char aSetsorcommand[14] = "SetSORCommand";

char aSetSequenceOpe[34] = "set-sequence-operator-recognition";

char aGetsequenceope[31] = "GetSequenceOperatorRecognition";

char aGetSequenceOpe[34] = "get-sequence-operator-recognition";

char aGetfunctionres[24] = "GetFunctionRestrictions";

char aGetFunctionRes[26] = "get-function-restrictions";

char aCreatefunction[15] = "CreateFunction";

char aCreate[8] = "create$";

char aMvAppend[10] = "mv-append";

char aAproposcommand[15] = "AproposCommand";

char aApropos[8] = "apropos";

char aNumberGreaterT[36] = "number (greater than or equal to 1)";

char aOn_0[3] = "on";

char aOff_0[4] = "off";

char aSymbolWithVa_2[28] = "symbol with value on or off";

char asc_5063E0[2] = "\n";

char aMachineType[15] = "Machine type: ";

char aUnixSystemIiiV[39] = "UNIX System III Version 7 or Sun Unix ";

char aAnsiCompilerIs[18] = "ANSI Compiler is ";

char aOn_1[4] = "ON\n";

char aDefruleConstru[22] = "Defrule construct is ";

char aConflictResolu[38] = "  Conflict resolution strategies are ";

char aDynamicSalienc[23] = "  Dynamic salience is ";

char aIncrementalRes[24] = "  Incremental reset is ";

char aLogicalDepende[48] = "  Logical dependencies (truth maintenance) are ";

char aDefmoduleConst[24] = "Defmodule construct is ";

char aDeftemplateCon[26] = "Deftemplate construct is ";

char aDeffactsConstr[25] = "  Deffacts construct is ";

char aDefglobalConst[24] = "Defglobal construct is ";

char aDeffunctionCon[26] = "Deffunction construct is ";

char aDefgenericDefm[37] = "Defgeneric/Defmethod constructs are ";

char aImperativeMeth[26] = "  Imperative methods are ";

char aObjectSystemIs[18] = "Object System is ";

char aDefinstancesCo[29] = "  Definstances construct is ";

char aImperativeArou[53] = "  Imperative (around/shadowed) message-handlers are ";

char aAuxiliaryBefor[49] = "  Auxiliary (before/after) message-handlers are ";

char aInstanceSetQue[28] = "  Instance-set queries are ";

char aDirectPatternM[43] = "  Direct pattern-matching on instances is ";

char aBinaryLoadingO[34] = "  Binary loading of instances is ";

char aBinarySavingOf[33] = "  Binary saving of instances is ";

char aExtendedMathPa[26] = "Extended math package is ";

char aTextProcessing[28] = "Text processing package is ";

char aHelpSystemIs[16] = "Help system is ";

char aBloadCapabilit[21] = "Bload capability is ";

char aBloadAndBsave[16] = "BLOAD AND BSAVE";

char aEmacsEditorIs[17] = "EMACS Editor is ";

char aOff_1[5] = "OFF\n";

char aConstructCompi[23] = "Construct compiler is ";

char aBasicIOIs[14] = "Basic I/O is ";

char aExtendedIOIs[17] = "Extended I/O is ";

char aStringFunction[28] = "String function package is ";

char aMultifieldFunc[32] = "Multifield function package is ";

char aDebuggingFunct[25] = "Debugging functions are ";

char aBlockMemoryIs[17] = "Block memory is ";

char aWindowInterfac[26] = "Window Interface flag is ";

char aShortLinkNames[22] = "Short link names are ";

char aDeveloperFlagI[19] = "Developer flag is ";

char aRunTimeModuleI[20] = "Run time module is ";

char aMiscfun[8] = "MISCFUN";

char aExpandMustBeUs[63] = "expand$ must be used in the argument list of a function call.\n";

_UNKNOWN g_Rules_HostFunctionErrorFallbackString;

char a0_0[4] = "0**";

char a1_0[3] = "1*";

char aPrintoutfuncti[17] = "PrintoutFunction";

char aPrintout[9] = "printout";

char a1[3] = "*1";

char aReadfunction[13] = "ReadFunction";

char aRead[5] = "read";

char a23K[5] = "23*k";

char aOpenfunction[13] = "OpenFunction";

char aOpen[5] = "open";

char aClosefunction[14] = "CloseFunction";

char aClose[6] = "close";

char a11k_0[4] = "11k";

char aRemovefunction[15] = "RemoveFunction";

char aRemove[7] = "remove";

char a22k[4] = "22k";

char aRenamefunction[15] = "RenameFunction";

char aRename[7] = "rename";

char a2Us[6] = "2**us";

char aFormatfunction[15] = "FormatFunction";

char aFormat[7] = "format";

char aReadlinefuncti[17] = "ReadlineFunction";

char aReadline[9] = "readline";

char aStdout_0[7] = "stdout";

char aCrlf[5] = "crlf";

char asc_5069B8[2] = "\n";

char aTab[4] = "tab";

char asc_5069C0[2] = "\t";

char aVtab[5] = "vtab";

char asc_5069CC[2] = "\v";

char aFf[3] = "ff";

_UNKNOWN g_Rules_PrintoutFormFeedChar;

_UNKNOWN g_Rules_PrintoutCrlfAliasName;

char aReadError[19] = "*** READ ERROR ***";

char aStdin[6] = "stdin";

char aEof[4] = "EOF";

char aIofun[6] = "IOFUN";

char aLogicalName_0[14] = "Logical name ";

char aAlreadyInUse_[18] = " already in use.\n";

char aR_3[2] = "r";

char aR_4[3] = "r+";

char aW_4[2] = "w";

char aA_2[2] = "a";

char aStringWithValu[41] = "string with value \"r\", \"r+\", \"w\", or \"a\"";

char g_Rules_HostFormatEmptyResult[4] = { '\0', '\0', '\0', '\0' };

char aNil_0[4] = "nil";

char asc_506A6C[2] = "\r";

char asc_506A70[3] = "%%";

char aErrorInFormatT[43] = " Error in format, the conversion character";

char aForFormattedOu[36] = " for formatted output is not valid\n";

char aIllegalLogical[31] = "Illegal logical name used for ";

char aFunction_[12] = " function.\n";

char a11_6[3] = "11";

char aNotfunction[12] = "NotFunction";

char aNot_0[4] = "not";

char a2[3] = "2*";

char aAndfunction[12] = "AndFunction";

char aAnd_0[4] = "and";

char aOrfunction[11] = "OrFunction";

char aOr_0[3] = "or";

char aEqfunction[11] = "EqFunction";

char aEq_0[3] = "eq";

char aNeqfunction[12] = "NeqFunction";

char aNeq_0[4] = "neq";

char a2N[4] = "2*n";

char aLessthanorequa[24] = "LessThanOrEqualFunction";

char asc_506B64[3] = "<=";

char aGreaterthanore[27] = "GreaterThanOrEqualFunction";

char asc_506B84[3] = ">=";

char aLessthanfuncti[17] = "LessThanFunction";

char asc_506B9C[2] = "<";

char aGreaterthanfun[20] = "GreaterThanFunction";

char asc_506BB4[2] = ">";

char aNumericequalfu[21] = "NumericEqualFunction";

char asc_506BD0[2] = "=";

char aNumericnotequa[24] = "NumericNotEqualFunction";

char asc_506BEC[3] = "<>";

char asc_506BF0[3] = "!=";

char aSymbolpfunctio[16] = "SymbolpFunction";

char aSymbolp[8] = "symbolp";

char aWordp[6] = "wordp";

char aStringpfunctio[16] = "StringpFunction";

char aStringp[8] = "stringp";

char aLexemepfunctio[16] = "LexemepFunction";

char aLexemep[8] = "lexemep";

char aNumberpfunctio[16] = "NumberpFunction";

char aNumberp[8] = "numberp";

char aIntegerpfuncti[17] = "IntegerpFunction";

char aIntegerp[9] = "integerp";

char aFloatpfunction[15] = "FloatpFunction";

char aFloatp[7] = "floatp";

char a11i_2[4] = "11i";

char aOddpfunction[13] = "OddpFunction";

char aOddp[5] = "oddp";

char aEvenpfunction[14] = "EvenpFunction";

char aEvenp[6] = "evenp";

char aMultifieldpfun[20] = "MultifieldpFunction";

char aMultifieldp[12] = "multifieldp";

char aSequencep[10] = "sequencep";

char aPointerpfuncti[17] = "PointerpFunction";

char aPointerp[9] = "pointerp";

char a2N_0[4] = "2*n";

char aAdditionfuncti[17] = "AdditionFunction";

char asc_506D2C[2] = "+";

char aMultiplication[23] = "MultiplicationFunction";

char asc_506D48[2] = "*";

char aSubtractionfun[20] = "SubtractionFunction";

char asc_506D60[2] = "-";

char aDivisionfuncti[17] = "DivisionFunction";

char asc_506D78[2] = "/";

char aDivfunction[12] = "DivFunction";

char aDiv[4] = "div";

char a11_3[3] = "11";

char aSetautofloatdi[28] = "SetAutoFloatDividendCommand";

char aSetAutoFloatDi[24] = "set-auto-float-dividend";

char a00_6[3] = "00";

char aGetautofloatdi[28] = "GetAutoFloatDividendCommand";

char aGetAutoFloatDi[24] = "get-auto-float-dividend";

char a11n[4] = "11n";

char aIntegerfunctio[16] = "IntegerFunction";

char aInteger[8] = "integer";

char aFloatfunction[14] = "FloatFunction";

char aFloat[6] = "float";

char aAbsfunction[12] = "AbsFunction";

char aAbs[4] = "abs";

char aMinfunction[12] = "MinFunction";

char aMin[4] = "min";

char aMaxfunction[12] = "MaxFunction";

char aMax[4] = "max";

char a11m_0[4] = "11m";

char aFirstfunction[14] = "FirstFunction";

char aFirst[7] = "first$";

char aRestfunction[13] = "RestFunction";

char aRest[6] = "rest$";

char a33im[5] = "33im";

char aSubseqfunction[15] = "SubseqFunction";

char aSubseq[8] = "subseq$";

char aDeletefunction[15] = "DeleteFunction";

char aDelete[8] = "delete$";

char a4Mii[7] = "4**mii";

char aReplacefunctio[16] = "ReplaceFunction";

char aReplace[9] = "replace$";

char a3Mi[6] = "3**mi";

char aInsertfunction[15] = "InsertFunction";

char aInsert[8] = "insert$";

char a11s_0[4] = "11s";

char aExplodefunctio[16] = "ExplodeFunction";

char aExplode[9] = "explode$";

char aImplodefunctio[16] = "ImplodeFunction";

char aImplode[9] = "implode$";

char a22Im[6] = "22*im";

char aNthfunction[12] = "NthFunction";

char aNth[5] = "nth$";

char a22Um[6] = "22*um";

char aMemberfunction[15] = "MemberFunction";

char aMember[8] = "member$";

char a22Mm[6] = "22*mm";

char aSubsetpfunctio[16] = "SubsetpFunction";

char aSubsetp[8] = "subsetp";

char aMultifieldprog[24] = "MultifieldPrognFunction";

char aProgn_0[7] = "progn$";

char aStrImplode[12] = "str-implode";

char aStrExplode[12] = "str-explode";

char aSubset[7] = "subset";

char aNth_0[4] = "nth";

char a33Im[6] = "33*im";

char aMvreplacefunct[18] = "MVReplaceFunction";

char aMvReplace[11] = "mv-replace";

char aMember_0[7] = "member";

char a33Iim[7] = "33*iim";

char aMvsubseqfuncti[17] = "MVSubseqFunction";

char aMvSubseq[10] = "mv-subseq";

char aMvdeletefuncti[17] = "MVDeleteFunction";

char aMvDelete[10] = "mv-delete";

char a00_7[3] = "00";

char aGetPrognField[19] = "(get-progn$-field)";

char aGetmvprogninde[16] = "GetMvPrognIndex";

char aGetPrognIndex[19] = "(get-progn$-index)";

char g_Rules_ImplodeEmptyResult[4] = { '\0', '\0', '\0', '\0' };

char aNil_1[4] = "nil";

char aPrimitiveDataT[20] = "primitive data type";

char asc_5070CC[2] = " ";

char aMultifun[9] = "MULTIFUN";

char aCannotRebindFi[50] = "Cannot rebind field variable in function progn$.\n";

char aIndex[7] = "-index";

char aMultifieldInde[18] = "Multifield index ";

char aRange[7] = "range ";

char a__[3] = "..";

char aOutOfRange1__[18] = " out of range 1..";

char aInFunction_0[14] = " in function ";

char a__16[3] = ".\n";

char a1_1[3] = "1*";

char aStrcatfunction[15] = "StrCatFunction";

char aStrCat[8] = "str-cat";

char aSymcatfunction[15] = "SymCatFunction";

char aSymCat[8] = "sym-cat";

char a11j[4] = "11j";

char aStrlengthfunct[18] = "StrLengthFunction";

char aStrLength[11] = "str-length";

char a23Jji[7] = "23*jji";

char aStrcomparefunc[19] = "StrCompareFunction";

char aStrCompare[12] = "str-compare";

char aUpcasefunction[15] = "UpcaseFunction";

char aUpcase[7] = "upcase";

char aLowcasefunctio[16] = "LowcaseFunction";

char aLowcase[8] = "lowcase";

char a33Iij[7] = "33*iij";

char aSubstringfunct[18] = "SubStringFunction";

char aSubString[11] = "sub-string";

char a22j[4] = "22j";

char aStrindexfuncti[17] = "StrIndexFunction";

char aStrIndex[10] = "str-index";

char a11k_1[4] = "11k";

char aEvalfunction[13] = "EvalFunction";

char aEval[5] = "eval";

char aBuildfunction[14] = "BuildFunction";

char aBuild[6] = "build";

char g_Rules_EmptyStringLiteral[4] = { '\0', '\0', '\0', '\0' };

char aNil_4[4] = "nil";

char aStringInstance[49] = "string, instance name, symbol, float, or integer";

char aMiscfun_0[8] = "MISCFUN";

char aExpandMustBe_0[63] = "expand$ must be used in the argument list of a function call.\n";

char aStrngfun[9] = "STRNGFUN";

char aSomeVariablesC[60] = "Some variables could not be accessed by the eval function.\n";

char aError_3[9] = "\nERROR:\n";

char asc_507374[2] = "\n";

char a11n_0[4] = "11n";

char aCosfunction[12] = "CosFunction";

char aCos[4] = "cos";

char aSinfunction[12] = "SinFunction";

char aSin[4] = "sin";

char aTanfunction[12] = "TanFunction";

char aTan[4] = "tan";

char aSecfunction[12] = "SecFunction";

char aSec[4] = "sec";

char aCscfunction[12] = "CscFunction";

char aCsc[4] = "csc";

char aCotfunction[12] = "CotFunction";

char aCot[4] = "cot";

char aAcosfunction[13] = "AcosFunction";

char aAcos[5] = "acos";

char aAsinfunction[13] = "AsinFunction";

char aAsin[5] = "asin";

char aAtanfunction[13] = "AtanFunction";

char aAtan[5] = "atan";

char aAsecfunction[13] = "AsecFunction";

char aAsec[5] = "asec";

char aAcscfunction[13] = "AcscFunction";

char aAcsc[5] = "acsc";

char aAcotfunction[13] = "AcotFunction";

char aAcot[5] = "acot";

char aCoshfunction[13] = "CoshFunction";

char aCosh[5] = "cosh";

char aSinhfunction[13] = "SinhFunction";

char aSinh[5] = "sinh";

char aTanhfunction[13] = "TanhFunction";

char aTanh[5] = "tanh";

char aSechfunction[13] = "SechFunction";

char aSech[5] = "sech";

char aCschfunction[13] = "CschFunction";

char aCsch[5] = "csch";

char aCothfunction[13] = "CothFunction";

char aCoth[5] = "coth";

char aAcoshfunction[14] = "AcoshFunction";

char aAcosh[6] = "acosh";

char aAsinhfunction[14] = "AsinhFunction";

char aAsinh[6] = "asinh";

char aAtanhfunction[14] = "AtanhFunction";

char aAtanh[6] = "atanh";

char aAsechfunction[14] = "AsechFunction";

char aAsech[6] = "asech";

char aAcschfunction[14] = "AcschFunction";

char aAcsch[6] = "acsch";

char aAcothfunction[14] = "AcothFunction";

char aAcoth[6] = "acoth";

char a22n[4] = "22n";

char aModfunction[12] = "ModFunction";

char aMod[4] = "mod";

char aExpfunction[12] = "ExpFunction";

char aExp[4] = "exp";

char aLogfunction[12] = "LogFunction";

char aLog[4] = "log";

char aLog10function[14] = "Log10Function";

char aLog10[6] = "log10";

char aSqrtfunction[13] = "SqrtFunction";

char aSqrt[5] = "sqrt";

char a00_8[3] = "00";

char aPifunction[11] = "PiFunction";

char aPi[3] = "pi";

char aDegradfunction[15] = "DegRadFunction";

char aDegRad[8] = "deg-rad";

char aRaddegfunction[15] = "RadDegFunction";

char aRadDeg[8] = "rad-deg";

char aDeggradfunctio[16] = "DegGradFunction";

char aDegGrad[9] = "deg-grad";

char aGraddegfunctio[16] = "GradDegFunction";

char aGradDeg[9] = "grad-deg";

char aPowfunction[12] = "PowFunction";

char asc_507678[3] = "**";

char aRoundfunction[14] = "RoundFunction";

char aRound[6] = "round";

char aEmathfun[9] = "EMATHFUN";

char aDomainErrorFor[18] = "Domain error for ";

char aFunction__1[12] = " function.\n";

char aArgumentOverfl[23] = "Argument overflow for ";

char aSingularityAtA[29] = "Singularity at asymptote in ";

double g_Rules_TanEpsilonPositive = 1.0e-15;

double g_Rules_TanEpsilonNegative = -1.0e-15;

double g_Rules_SecEpsilonPositive = 1.0e-15;

double g_Rules_SecDomainEpsilonNeg = -1.0e-15;

double g_Rules_CscDomainEpsilonPos = 1.0e-15;

double g_Rules_CscDomainEpsilonNeg = -1.0e-15;

double g_Rules_CotDomainEpsilonPos = 1.0e-15;

double g_Rules_CotDomainEpsilonNeg = -1.0e-15;

double g_Rules_AcosDomainLowerBound = -1.0;

double g_Rules_AsinDomainLowerBound = -1.0;

double g_Rules_AsecDomainLowerBound = -1.0;

double g_Rules_AcscDomainLowerBound = -1.0;

double g_Rules_AcoshDomainLowerBound = -1.0;

double g_Rules_AtanhDomainLowerBound = -1.0;

double g_Rules_AtanhHalfCoefficient = 0.5;

double g_Rules_AsechDomainLowerBound = -1.0;

double g_Rules_AcothDomainLowerBound = -1.0;

double g_Rules_AcothHalfCoefficient = 0.5;

double g_Rules_MathPiAcosArgument = -1.0;

double g_Rules_DegToRadPiConstant = 3.141592653589793;

double g_Rules_DegToRadDegreesConstant = 180.0;

double g_Rules_RadToDegDegreesConstant = 180.0;

double g_Rules_RadToDegPiConstant = 3.141592653589793;

double g_Rules_DegToGradConversionFactor = 0.9;

double g_Rules_GradToDegConversionFactor = 0.9;

double g_Rules_MathRoundHalfOffset = -0.5;

unsigned __int8 g_Help_FileOpenModeRead[4] = { 114u, 0u, 0u, 0u };

char aEndEntry[10] = "END-ENTRY";

char aBeginEntry[13] = "BEGIN-ENTRY-";

char aClips_hlp[10] = "clips.hlp";

char aLoadingHelpFil[32] = "Loading help file entries from ";

char a_PleaseWait___[18] = ".\nPlease wait...\n";

char aTextpro[8] = "TEXTPRO";

char aUnableToAccess[29] = "Unable to access help file.\n";

char asc_50797C[2] = "\n";

char aWhelp[6] = "whelp";

char aMain_2[5] = "MAIN";

char aRootEntryMainN[32] = "Root entry \"MAIN\" not found in ";

char a_SeeExternalDo[31] = ".\nSee external documentation.\n";

char aSorryNoInforma[36] = "\nSorry, no information available.\n\n";

char aPressReturnFor[26] = "PRESS <RETURN> FOR MORE. ";

char aPressAReturnTo[29] = "PRESS <A>,<RETURN> TO ABORT.";

char aTheCurrentHelp[34] = "The current help entries file is ";

char aReleasingHelpE[34] = "Releasing help entries from file ";

char a___[5] = "...\n";

char aHelpPath[10] = "help-path";

char aFetch[6] = "fetch";

char aUnableToLoadFi[22] = "Unable to load file.\n";

char aNoEntriesFound[18] = "No entries found.";

char aT_1[2] = "t";

char aStdout_3[7] = "stdout";

char aToss[5] = "toss";

char aStdin_3[6] = "stdin";

char aError_4[12] = "***ERROR***";

char aTopic_[9] = " Topic? ";

char asc_507B10[2] = "^";

char aQuestionMark_507B14[2] = "?";

char aHelpfunction[13] = "HelpFunction";

char aHelp[5] = "help";

char a1k[4] = "*1k";

char aHelppathfuncti[17] = "HelpPathFunction";

char a11k_2[4] = "11k";

char aFetchcommand[13] = "FetchCommand";

char aTosscommand[12] = "TossCommand";

char a2Wk[6] = "2**wk";

char aPrintregioncom[19] = "PrintRegionCommand";

char aPrintRegion[13] = "print-region";

char aConstructsToC[16] = "constructs-to-c";

char aConscomp[9] = "CONSCOMP";

char aBaseFileNameEx[38] = "Base file name exceeds 3 characters.\n";

char aThisMayCauseFi[62] = "  This may cause files to be overwritten if file name length\n";

char aIsLimitedOnYou[32] = "  is limited on your platform.\n";

char aPositiveIntege[17] = "positive integer";

char aW_2[2] = "w";

char aIfndef_constru[37] = "#ifndef _CONSTRUCT_COMPILER_HEADER_\n";

char aDefine_constru[38] = "#define _CONSTRUCT_COMPILER_HEADER_\n\n";

char aIncludeStdio_h[20] = "#include <stdio.h>\n";

char aIncludeSetup_h[20] = "#include \"setup.h\"\n";

char aIncludeExpress[23] = "#include \"expressn.h\"\n";

char aIncludeExtnfun[23] = "#include \"extnfunc.h\"\n";

char aIncludeClips_h[20] = "#include \"clips.h\"\n";

char aDefineVsVoid[22] = "\n#define VS (VOID *)\n";

char asc_507D2C[2] = "\n";

char aEndif[10] = "\n#endif\n\n";

char asc_507D3C[32] = "/****************************/\n";

char aExternArrayDef[32] = "/* EXTERN ARRAY DEFINITIONS */\n";

char asc_507D7C[33] = "/****************************/\n\n";

char asc_507DA0[4] = "};\n";

char asc_507DA4[40] = "/************************************/\n";

char aExternalFuncti[40] = "/* EXTERNAL FUNCTION DEFINITIONS    */\n";

char asc_507DF4[41] = "/************************************/\n\n";

char aExtern[8] = "extern ";

char aInt[5] = "int ";

char aLong[6] = "long ";

char aFloat_3[7] = "float ";

char aDouble[8] = "double ";

char aSymbol_hn[12] = "SYMBOL_HN *";

char aChar[6] = "char ";

char aVoid[8] = "VOID * ";

char aVoid_0[6] = "VOID ";

char aS_10[4] = "%s(";

char aVoid_arg[9] = "VOID_ARG";

char aData_object_pt[20] = "DATA_OBJECT_PTR_ARG";

char asc_507E90[4] = ");\n";

char asc_507E94[3] = "\n\n";

char aFunctionListDe[40] = "/* FUNCTION LIST DEFINITION         */\n";

char aStructFunction[40] = "struct FunctionDefinition P%d_%d[] = {\n";

char aExternStructFu[44] = "extern struct FunctionDefinition P%d_%d[];\n";

char asc_507F14[2] = "{";

char aS_4[7] = ",\"%s\",";

char aC[6] = "'%c',";

char aPtifS[9] = "PTIF %s,";

char aNull_0[6] = "NULL,";

char aS_5[6] = "\"%s\",";

char a000[7] = "0,0,0,";

char asc_507F4C[5] = "}};\n";

char asc_507F54[4] = "},\n";

char aNull_1[5] = "NULL";

char aPD_DD[12] = "&P%d_%d[%d]";

char aIncludeS_h[17] = "#include \"%s.h\"\n";

char aIncludeUtility[22] = "#include \"utility.h\"\n";

char aIncludeGenerat[23] = "#include \"generate.h\"\n";

char aIncludeObjrtmc[23] = "#include \"objrtmch.h\"\n";

char aIncludeRulebld[23] = "#include \"rulebld.h\"\n\n";

char aIfAnsi_compile[19] = "#if ANSI_COMPILER\n";

char aVoidInitcimage[30] = "   VOID InitCImage_%d(void);\n";

char aElse[7] = "#else\n";

char aVoidInitcima_0[26] = "   VOID InitCImage_%d();\n";

char aEndif_0[8] = "#endif\n";

char asc_508048[47] = "/*******************************************/\n";

char aConstructImage[47] = "/* CONSTRUCT IMAGE INITIALIZATION FUNCTION */\n";

char aVoidInitcima_1[23] = "\nVOID InitCImage_%d()\n";

char asc_5080C0[5] = "  {\n";

char aClear_0[13] = "   Clear();\n";

char aPeriodiccleanu[45] = "   PeriodicCleanup(CLIPS_TRUE,CLIPS_FALSE);\n";

char aSetsymboltable[27] = "   SetSymbolTable(sht%d);\n";

char aSetfloattableF[26] = "   SetFloatTable(fht%d);\n";

char aSetintegertabl[28] = "   SetIntegerTable(iht%d);\n";

char aSetbitmaptable[28] = "   SetBitMapTable(bmht%d);\n";

char aRefreshspecial[29] = "   RefreshSpecialSymbols();\n";

char aInstallfunctio[33] = "   InstallFunctionList(P%d_1);\n\n";

char aInitexpression[31] = "   InitExpressionPointers();\n\n";

char asc_5081DC[5] = "  }\n";

char aA_0[2] = "a";

char aED_LdLd[14] = "&E%d_%ld[%ld]";

char aED_DLd[13] = "&E%d_%d[%ld]";

char aStructExprED_D[26] = "struct expr E%d_%d[] = {\n";

char aExternStructEx[30] = "extern struct expr E%d_%d[];\n";

char asc_508250[3] = ",\n";

char aD_37[4] = "%d,";

char aVs[4] = "VS ";

char aDummyfact[11] = "&DummyFact";

char aDummyinstance[15] = "&DummyInstance";

char asc_508278[2] = ",";

char aED_DLd_0[14] = "&E%d_%d[%ld],";

char aNull_2[6] = "NULL}";

char aED_DLd_1[14] = "&E%d_%d[%ld]}";

char a23Kii[7] = "23*kii";

char aConstructstocc[21] = "ConstructsToCCommand";

char g_Rules_CodeGeneratorItemLetterTable[6] = { 'A', 'D', 'G', 'H', 'J', 'K' };

char g_Rules_CodeGeneratorItemPrefixTable[] = { 'M' };

char aSS_0[13] = "%s %s[] = {\n";

char aExternSS[17] = "extern %s %s[];\n";

char aNull_17[7] = ",NULL,";

char aMihsSD_DD_2[19] = "MIHS &%s%d_%d[%d],";

char a0_1[3] = "0,";

char aChsSD_LdLd[20] = "CHS &%s%d_%ld[%ld]}";

char aChsSD_LdLd_0[20] = "CHS &%s%d_%ld[%ld],";

char aChsSD_LdLd_1[19] = "CHS &%s%d_%ld[%ld]";

char asc_508384[2] = "}";

char asc_5083B0[2] = ",";

char asc_5083B4[2] = "\n";

char aDefrule_0[8] = "defrule";

char aRules[6] = "rules";

char a01w_4[4] = "01w";

char aGetdefrulelist[23] = "GetDefruleListFunction";

char aGetDefruleList[17] = "get-defrule-list";

char a11w_7[4] = "11w";

char aUndefrulecomma[17] = "UndefruleCommand";

char aUndefrule[10] = "undefrule";

char aDefrulemodulef[22] = "DefruleModuleFunction";

char aDefruleModule[15] = "defrule-module";

char aListdefrulesco[20] = "ListDefrulesCommand";

char aListDefrules[14] = "list-defrules";

char aPpdefrulecomma[17] = "PPDefruleCommand";

char aPpdefrule[10] = "ppdefrule";

char aMain_4[5] = "MAIN";

char asc_50849C[2] = "\n";

char aDefmoduleNam_2[15] = "defmodule name";

char asc_5084B0[3] = "::";

char asc_5084B4[3] = ":\n";

char asc_5084B8[4] = "   ";

char aListWatchIte_0[17] = "list-watch-items";

char aWatch_0[6] = "watch";

char aOn_2[7] = " = on\n";

char aOff_2[8] = " = off\n";

char aInitializeIn_0[20] = "initialize-instance";

char aInsmngr[8] = "INSMNGR";

char aExpectedAVal_2[41] = "Expected a valid name for new instance.\n";

char aExpectedAVal_3[47] = "Expected a valid class name for new instance.\n";

char aDummyInstance[15] = "Dummy Instance";

char aCannotCreate_0[51] = "Cannot create instances of reactive classes while\n";

char aPatternMatch_0[35] = "  pattern-matching is in process.\n";

char aCannotCreate_1[43] = "Cannot create instances of abstract class ";

char a__17[3] = ".\n";

char aInvalidModuleS[48] = "Invalid module specifier in new instance name.\n";

char aTheInstance[14] = "The instance ";

char aHasASlotValueW[61] = " has a slot-value which depends on the instance definition.\n";

char aUnableToDele_0[31] = "Unable to delete old instance ";

char aCannotDeleteIn[51] = "Cannot delete instances of reactive classes while\n";

char aCannotDelete_0[24] = "Cannot delete instance ";

char aDuringInitiali[25] = " during initialization.\n";

char asc_508714[4] = "<==";

char asc_508718[4] = "==>";

char aNil_3[4] = "nil";

char aInstance_4[10] = "Instance ";

char aIsAlreadyBeing[32] = " is already being initialized.\n";

char aAnErrorOccurre[57] = "An error occurred during the initialization of instance ";

char aExpectedAVal_4[47] = "Expected a valid slot name for slot-override.\n";

char aSlot_2[6] = "Slot ";

char aDoesNotExistIn[29] = " does not exist in instance ";

char aOverrideRequir[28] = "Override required for slot ";

char aInInstance_0[14] = " in instance ";

char aInitSlotsNotVa[39] = "init-slots not valid in this context.\n";

char aInstanceDelete[48] = " instance deleted by slot-override evaluation.\n";

char aInstance[11] = " instance ";

char aMakeInstance_0[14] = "make-instance";

char aActiveMakeIn_0[21] = "active-make-instance";

char aInitializeIn_1[20] = "initialize-instance";

char aActiveInitia_0[27] = "active-initialize-instance";

char aModifyInstan_0[16] = "modify-instance";

char aActiveModify_0[23] = "active-modify-instance";

char aMessageModif_0[24] = "message-modify-instance";

char aActiveMessag_0[31] = "active-message-modify-instance";

char asc_508954[2] = " ";

char aOf_0[3] = "of";

char aGensym_1[8] = "gensym*";

char aTo_2[3] = "to";

char aCreate_0[8] = "create$";

char aInsmngr_0[8] = "INSMNGR";

char aCannotCreateIn[43] = "Cannot create instances of abstract class ";

char a__7[3] = ".\n";

char aInactivemodify[23] = "InactiveModifyInstance";

char aModifyInstance[16] = "modify-instance";

char aModifyinstance[15] = "ModifyInstance";

char aActiveModifyIn[23] = "active-modify-instance";

char aMessageModifyI[24] = "message-modify-instance";

char aMsgmodifyinsta[18] = "MsgModifyInstance";

char aActiveMessageM[31] = "active-message-modify-instance";

char aDuplicateInsta[19] = "duplicate-instance";

char aDuplicateinsta[18] = "DuplicateInstance";

char aActiveDuplicat[26] = "active-duplicate-instance";

char aMessageDuplica[27] = "message-duplicate-instance";

char aMsgduplicatein[21] = "MsgDuplicateInstance";

char aActiveMessageD[34] = "active-message-duplicate-instance";

char aDirectModify[16] = "(direct-modify)";

char aMsgmodifymsgha[20] = "MsgModifyMsgHandler";

char aMessageModify[17] = "(message-modify)";

char aDirectduplicat[26] = "DirectDuplicateMsgHandler";

char aDirectDuplicat[19] = "(direct-duplicate)";

char aMsgduplicatems[23] = "MsgDuplicateMsgHandler";

char aMessageDupli_0[20] = "(message-duplicate)";

char aDirectModify_0[14] = "direct-modify";

char aMessageModif_1[15] = "message-modify";

char aDirectDuplic_0[17] = "direct-duplicate";

char aMessageDupli_1[18] = "message-duplicate";

char aSlotName[10] = "slot name";

char aInsmoddp[9] = "INSMODDP";

char aDirectMessageM[62] = "Direct/message-modify message valid only in modify-instance.\n";

char aDirectMessageD[68] = "Direct/message-duplicate message valid only in duplicate-instance.\n";

char aInstanceCopyMu[65] = "Instance copy must have a different name in duplicate-instance.\n";

char a1Wk_0[5] = "1*wk";

char aSaveinstancesc[21] = "SaveInstancesCommand";

char aSaveInstances[15] = "save-instances";

char a11k_3[4] = "11k";

char aLoadinstancesc[21] = "LoadInstancesCommand";

char aLoadInstances[15] = "load-instances";

char aRestoreinstanc[24] = "RestoreInstancesCommand";

char aRestoreInstanc[18] = "restore-instances";

char aBinarysaveinst[27] = "BinarySaveInstancesCommand";

char aBsaveInstances[16] = "bsave-instances";

char aBinaryloadinst[27] = "BinaryLoadInstancesCommand";

char aBloadInstances[16] = "bload-instances";

char aW_5[2] = "w";

char aWb_5[3] = "wb";

char aSymbolLocalOrV[28] = "symbol \"local\" or \"visible\"";

char aLocal_1[6] = "local";

char aVisible_0[8] = "visible";

char aInherit_3[8] = "inherit";

char aValidClassName[17] = "valid class name";

char aValidConcreteC[26] = "valid concrete class name";

char asc_508EB0[3] = "([";

char aOf_1[6] = "] of ";

char asc_508EBC[6] = "\n   (";

char asc_508EC4[2] = " ";

char asc_508EC8[2] = ")";

char asc_508ECC[4] = ")\n\n";

char aR_8[2] = "r";

char aMakeInstance_1[14] = "make-instance";

char aInsfile[8] = "INSFILE";

char aFunction_1[10] = "Function ";

char aCouldNotComple[36] = " could not completely process file ";

char a__18[3] = ".\n";

char aFileIsNotABina[39] = " file is not a binary instances file.\n";

char aFileIsNotAComp[50] = " file is not a compatible binary instances file.\n";

char aFunctionBloadI[51] = "Function bload-instances unable to load instance [";

char aOfClass_0[12] = "] of class ";

char a4Wii[7] = "4**wii";

char aDirectmvreplac[23] = "DirectMVReplaceCommand";

char aDirectMvReplac[18] = "direct-mv-replace";

char a3Wi[6] = "3**wi";

char aDirectmvinsert[22] = "DirectMVInsertCommand";

char aDirectMvInsert[17] = "direct-mv-insert";

char a33iw[5] = "33iw";

char aDirectmvdelete[22] = "DirectMVDeleteCommand";

char aDirectMvDelete[17] = "direct-mv-delete";

char a5Uewii[8] = "5*uewii";

char aMvslotreplacec[21] = "MVSlotReplaceCommand";

char aMvSlotReplace[16] = "mv-slot-replace";

char a4Uewi[7] = "4*uewi";

char aMvslotinsertco[20] = "MVSlotInsertCommand";

char aMvSlotInsert[15] = "mv-slot-insert";

char a44iew[6] = "44iew";

char aMvslotdeleteco[20] = "MVSlotDeleteCommand";

char aMvSlotDelete[15] = "mv-slot-delete";

char aSlotDirectRepl[21] = "slot-direct-replace$";

char aSlotDirectInse[20] = "slot-direct-insert$";

char aSlotDirectDele[20] = "slot-direct-delete$";

char aSlotReplace[14] = "slot-replace$";

char aSlotInsert[13] = "slot-insert$";

char aSlotDelete[13] = "slot-delete$";

char aDirectSlotRepl[21] = "direct-slot-replace$";

char aDirectSlotInse[20] = "direct-slot-insert$";

char aDirectSlotDele[20] = "direct-slot-delete$";

char aSymbol_4[7] = "symbol";

char aInsmult[8] = "INSMULT";

char aFunction_2[10] = "Function ";

char aCannotBeUsedOn[38] = " cannot be used on single-field slot ";

char aInInstance_1[14] = " in instance ";

char a__19[3] = ".\n";

char aInteger_3[8] = "integer";

char aMessageHandl_3[17] = "message-handler ";

char aMsgfun[7] = "MSGFUN";

char aNoApplicablePr[50] = "No applicable primary message-handlers found for ";

char a__20[3] = ".\n";

char aMessageHandl_4[17] = "Message-handler ";

char asc_5092EC[2] = " ";

char aInClass_0[11] = " in class ";

char aExpected[11] = " expected ";

char aAtLeast[10] = "at least ";

char aExactly[9] = "exactly ";

char aArgumentS_[15] = " argument(s).\n";

char aSlotIn[10] = " slot in ";

char aClass_1[7] = "class ";

char aWriteAccessDen[24] = ": write access denied.\n";

char aPrivateSlot[14] = "Private slot ";

char aOfClass_1[11] = " of class ";

char aCannotBeAccess[63] = " cannot be accessed directly\n   by handlers attached to class ";

char aMsgpsr_0[7] = "MSGPSR";

char aSystemMessag_0[46] = "System message-handlers may not be modified.\n";

char asc_5093F0[2] = "*";

char aUnrecognizedMe[38] = "Unrecognized message-handler type in ";

char aWerror[7] = "werror";

char aMayOnlyBeCalle[51] = " may only be called from within message-handlers.\n";

char aOperatesOnlyOn[30] = " operates only on instances.\n";

char aUnableToDele_2[48] = "Unable to delete message-handler(s) from class ";

char asc_5094A8[3] = ">>";

char asc_5094AC[3] = "<<";

char aMsg[5] = "MSG ";

char aEd_0[5] = " ED:";

char aHnd[5] = "HND ";

char aEd[11] = "       ED:";

char asc_5094D4[3] = "| ";

char aSend_0[5] = "send";

char aMsgpass[8] = "MSGPASS";

char aShadowedMessag[62] = "Shadowed message-handlers not applicable in current context.\n";

char aOverrideNext_0[22] = "override-next-handler";

char asc_509548[3] = ">>";

char asc_50954C[3] = "<<";

char aDynamicGet_0[12] = "dynamic-get";

char aSymbol_5[7] = "symbol";

char aDynamicPut_0[12] = "dynamic-put";

char aNoSuchInstan_0[18] = "No such instance ";

char aInFunctionSend[20] = " in function send.\n";

char aStaticReferenc[26] = "Static reference to slot ";

char aOfClass_2[11] = " of class ";

char aDoesNotApplyTo[20] = " does not apply to ";

char asc_509610[2] = "\n";

char aClassfun[9] = "CLASSFUN";

char aUnableToFindCl[22] = "Unable to find class ";

char aInFunction_1[14] = " in function ";

char a__21[3] = ".\n";

char asc_50964C[3] = "::";

char asc_509650[2] = "\n";

char asc_509654[2] = " ";

char aDefclass_2[9] = "defclass";

char aPut_0[5] = "put-";

char aMaximumNumberO[70] = "Maximum number of simultaneous class hierarchy\n  traversals exceeded ";

char aObjrtmch[9] = "OBJRTMCH";

char aThisErrorOcc_2[51] = "This error occurred in the object pattern network\n";

char aCurrentlyAct_0[32] = "   Currently active instance: [";

char asc_509714[3] = "]\n";

char aProblemResid_2[28] = "   Problem resides in slot ";

char aField[9] = " field #";

char asc_509740[2] = "\n";

char aOfPattern[19] = "      Of pattern #";

char aInRuleS[14] = " in rule(s):\n";

char aCstrnchk_1[9] = "CSTRNCHK";

char aTheFunctionRet[27] = "The function return value ";

char asc_50979C[2] = " ";

char aFoundIn_0[10] = "found in ";

char aThe[5] = "the ";

char aCommand_0[9] = " command";

char aFoundInCe[14] = "found in CE #";

char aDoesNotMatchTh[34] = "\ndoes not match the allowed types";

char aDoesNotFallInT[37] = "\ndoes not fall in the allowed range ";

char aDoesNotMatch_0[35] = "\ndoes not match the allowed values";

char aDoesNotSatisfy[47] = "\ndoes not satisfy the cardinality restrictions";

char aForSlot[11] = " for slot ";

char aForField[13] = " for field #";

char a__29[3] = ".\n";

char aTo_1[5] = " to ";

CHAR LibFileName[] = "USER32.DLL";

CHAR ProcName[] = "GetActiveWindow";

char aTheInstruction[81] = "The instruction at 0x00000000 caused a stack overflow floating point\nexception.\n";

char aTheInstructi_0[82] = "The instruction at 0x00000000 caused a stack underflow floating point\nexception.\n";

char aTheInstructi_1[83] = "The instruction at 0x00000000 caused a denormal operand floating point\nexception.\n";

char aTheInstructi_2[83] = "The instruction at 0x00000000 caused a division by zero floating point\nexception.\n";

char aTheInstructi_3[81] = "The instruction at 0x00000000 caused an inexact value floating point\nexception.\n";

char aTheInstructi_4[76] = "The instruction at 0x00000000 caused an overflow floating point exception.\n";

char aTheInstructi_5[77] = "The instruction at 0x00000000 caused an underflow floating point exception.\n";

char aTheInstructi_6[85] = "The instruction at 0x00000000 caused an invalid operation floating point\nexception.\n";

char aTheInstructi_7[49] = "The instruction at 0x00000000 referenced memory ";

char aAt0x00000000_T[40] = "at 0x00000000.\nThe memory could not be ";

char aRead_[7] = "read.\n";

char aWritten_[10] = "written.\n";

char aAPrivilegedIns[62] = "A privileged instruction was executed at address 0x00000000.\n";

char aAnIllegalInstr[60] = "An illegal instruction was executed at address 0x00000000.\n";

char aAnIntegerDivid[66] = "An integer divide by zero was encountered at address 0x00000000.\n";

char aAStackOverflow[57] = "A stack overflow was encountered at address 0x00000000.\n";

char aTheProgramEnco[49] = "The program encountered exception 0x00000000 at ";

char aAddress0x00000[41] = "address 0x00000000 and\ncannot continue.\n";

char aFileio[7] = "fileio";

char aStdout_1[7] = "stdout";

char aStdin_0[6] = "stdin";

char aS_13[3] = "%s";

char asc_509EB8[2] = " ";

char asc_509EEC[2] = ")";

char aInitialFact[13] = "initial-fact";

char aDeftemplate_7[12] = "deftemplate";

char aFactlhs[8] = "FACTLHS";

char aCreatingImplie[53] = "Creating implied initial-fact deftemplate in module ";

char a__22[3] = ".\n";

char aYouProbablyWan[70] = "  You probably want to import this deftemplate from the MAIN module.\n";

char aImpliedDefte_0[20] = "implied deftemplate";

char aPattern[8] = "PATTERN";

char aTheSymbol[12] = "The symbol ";

char aHasSpecialMean[22] = " has special meaning\n";

char aAndMayNotBeUse[24] = "and may not be used as ";

char a__8[3] = ".\n";

char aNullNull[12] = "{NULL,NULL,";

char aNull_15[6] = "NULL,";

char aSD_DD_4[14] = "&%s%d_%d[%d],";

char aDDD00DD[20] = "%d,%d,%d,0,0,%d,%d}";

char asc_50A02C[2] = " ";

char aSingleAndMulti[73] = "Single and multifield constraints cannot be mixed in a field constraint\n";

char asc_50A08C[2] = "=";

char asc_50A090[2] = ":";

char aFacts_6[6] = "facts";

char asc_50A0A4[2] = "(";

char aN[2] = "n";

char asc_50A0AC[2] = "l";

char asc_50A0B0[2] = "-";

char asc_50A0B4[2] = " ";

char asc_50A0B8[2] = ")";

char aTest_1[7] = "(test ";

char aLnot[7] = "(lnot ";

char aNot_3[6] = "(not ";

char aLor[6] = "(lor ";

char aOr_3[5] = "(or ";

char aLand[7] = "(land ";

char aAnd_3[6] = "(and ";

char aPrettyPrintUnknownExpressionToken[4] = "(?]";

char aDeftemplate_2[12] = "deftemplate";

char aInitialFact_0[13] = "initial-fact";

char aDeftemplate_3[12] = "deftemplate";

char aIncludeTmpltde[23] = "#include \"tmpltdef.h\"\n";

char aStructDeftempl[25] = "struct deftemplateModule";

char aStructDeftem_0[19] = "struct deftemplate";

char aStructTemplate[20] = "struct templateSlot";

char asc_50A17C[2] = "{";

char asc_50A180[2] = "}";

char asc_50A184[2] = ",";

char aNull_19[6] = "NULL,";

char aSD_DD_5[14] = "&%s%d_%d[%d],";

char aD00DLd[15] = "%d,0,0,%d,%ld,";

char aNull_3[5] = "NULL";

char aDDDD[14] = ",%d,%d,%d,%d,";

char aNull_20[6] = "NULL}";

char aSD_DD_6[14] = "&%s%d_%d[%d]}";

char aMihsSD_DD_3[18] = "MIHS &%s%d_%d[%d]";

char aSD_LdLd[15] = "&%s%d_%ld[%ld]";

char aDefrule_1[8] = "defrule";

char aDeftemplate_8[14] = "(deftemplate ";

char aDeftemplate_9[12] = "deftemplate";

char asc_50A228[2] = "%";

char aADeftemplateNa[19] = "a deftemplate name";

char asc_50A248[5] = "\n   ";

char asc_50A250[2] = "\n";

char aField_0[6] = "field";

char aMultifield_2[11] = "multifield";

char aSlot_3[5] = "slot";

char aMultislot[10] = "multislot";

char asc_50A27C[2] = " ";

char aTheDefaultDyna[30] = "the default-dynamic attribute";

char aTheDefaultAttr[22] = "the default attribute";

char aAnExpression[14] = "An expression";

char aDefault[8] = "default";

char aDefaultDynamic[16] = "default-dynamic";

char aIncrrset[9] = "INCRRSET";

char aTheIncremental[69] = "The incremental reset behavior cannot be changed with rules loaded.\n";

char aExprnpsr[9] = "EXPRNPSR";

char aAFunctionNameM[34] = "A function name must be a symbol\n";

char aMissingFunctio[34] = "Missing function declaration for ";

char aDotNewline_ParserError[3] = ".\n";

char aExpand_0[8] = "expand$";

char aExpansionCal_0[17] = "(expansion-call)";

char aSequenceOperat[46] = "$ Sequence operator not a valid argument for ";

char asc_50A444[2] = " ";

char asc_50A448[2] = ")";

char aExpectedAConst[47] = "Expected a constant, variable, or expression.\n";

char aProgn_2[6] = "progn";

char aClipsfnxargs[19] = "***CLIPSFNXARGS***";

char aCannotReadArgu[42] = "Cannot read arguments for external call.\n";

char aOnlyConstantAr[67] = "Only constant arguments allowed for external CLIPS function call.\n";

char aLoopForCount_0[15] = "loop-for-count";

char asc_50A54C[2] = " ";

char aDo[3] = "do";

char aPrcdrpsr[9] = "PRCDRPSR";

char aCannotRebindLo[57] = "Cannot rebind loop variable in function loop-for-count.\n";

char aGetLoopCount_0[17] = "(get-loop-count)";

char aThen[5] = "then";

char aElse_0[5] = "else";

char asc_50A5F4[2] = ")";

char aDefglobal_4[10] = "defglobal";

char aTheReturnFunct[51] = "The return function is not valid in this context.\n";

char aTheBreakFuncti[47] = "The break function not valid in this context.\n";

char aCase[5] = "case";

char aDuplicateCaseF[42] = "Duplicate case found in switch function.\n";

char aDefault_1[8] = "default";

char a1i[4] = "*1i";

char aRuncommand[11] = "RunCommand";

char aRun[4] = "run";

char a00_9[3] = "00";

char aHaltcommand[12] = "HaltCommand";

char aHalt[5] = "halt";

char a1W_1[4] = "1*w";

char aFocuscommand[13] = "FocusCommand";

char aFocus_2[6] = "focus";

char aClearfocusstac[23] = "ClearFocusStackCommand";

char aClearFocusStac[18] = "clear-focus-stack";

char aGetfocusstackf[22] = "GetFocusStackFunction";

char aGetFocusStack[16] = "get-focus-stack";

char aPopfocusfuncti[17] = "PopFocusFunction";

char aPopFocus[10] = "pop-focus";

char aGetfocusfuncti[17] = "GetFocusFunction";

char aGetFocus[10] = "get-focus";

char a11w_8[4] = "11w";

char aSetbreakcomman[16] = "SetBreakCommand";

char aSetBreak[10] = "set-break";

char a1w[4] = "*1w";

char aRemovebreakcom[19] = "RemoveBreakCommand";

char aRemoveBreak[13] = "remove-break";

char a01w_5[4] = "01w";

char aShowbreakscomm[18] = "ShowBreaksCommand";

char aShowBreaks[12] = "show-breaks";

char aMatchescommand[15] = "MatchesCommand";

char aMatches[8] = "matches";

char aListfocusstack[22] = "ListFocusStackCommand";

char aListFocusStack[17] = "list-focus-stack";

char a11h[4] = "11h";

char aDependenciesco[20] = "DependenciesCommand";

char aDependencies[13] = "dependencies";

char aDependentscomm[18] = "DependentsCommand";

char aDependents[11] = "dependents";

char aGetincremental[27] = "GetIncrementalResetCommand";

char aGetIncremental[22] = "get-incremental-reset";

char a11_4[3] = "11";

char aSetincremental[27] = "SetIncrementalResetCommand";

char aSetIncremental[22] = "set-incremental-reset";

char aGetstrategycom[19] = "GetStrategyCommand";

char aGetStrategy[13] = "get-strategy";

char aSetstrategycom[19] = "SetStrategyCommand";

char aSetStrategy[13] = "set-strategy";

char aRuleName_0[10] = "rule name";

char aMatchesForPatt[21] = "Matches for Pattern ";

char asc_50A998[2] = "\n";

char aNone_3[7] = " None\n";

char aPartialMatches[29] = "Partial matches for CEs 1 - ";

char aActivations_1[13] = "Activations\n";

char aDefrule_4[10] = "(defrule ";

char aDefrule_5[8] = "defrule";

char asc_50A9E8[2] = "*";

char asc_50A9EC[2] = "\n";

char aRhsOfDefrule[15] = "RHS of defrule";

char aModify_0[7] = "modify";

char aDuplicate_0[10] = "duplicate";

char asc_50AA28[5] = "\n   ";

char aRulepsr_0[8] = "RULEPSR";

char aLogicalCesMust[44] = "Logical CEs must be placed first in a rule\n";

char aGapsMayNotExis[40] = "Gaps may not exist between logical CEs\n";

char aDefrules_0[9] = "defrules";

char aIncludeRuledef[22] = "#include \"ruledef.h\"\n";

char aStructDefrulem[21] = "struct defruleModule";

char aStructDefrule[15] = "struct defrule";

char aStructJoinnode[16] = "struct joinNode";

char asc_50AAE8[2] = "{";

char aNull_22[7] = ",NULL}";

char aDDDDDDDD[26] = ",%d,%d,%d,%d,%d,%d,%d,%d,";

char asc_50AB10[2] = ",";

char aSD_LdLd_6[16] = "&%s%d_%ld[%ld],";

char aNull_23[6] = "NULL,";

char aSD_LdLd_7[16] = "&%s%d_%ld[%ld]}";

char aNull_24[6] = "NULL}";

char aDDDD00DD0[26] = "{%d,%d,%d,%d,0,0,%d,%d,0,";

char aVs_0[4] = "VS ";

char aMihsSD_DD_4[18] = "MIHS &%s%d_%d[%d]";

char aDefmodule_0[10] = "defmodule";

char a00_10[3] = "00";

char aGetDefmoduleLi[19] = "get-defmodule-list";

char aListdefmodules[22] = "ListDefmodulesCommand";

char aListDefmodules[16] = "list-defmodules";

char a11w_9[4] = "11w";

char aPpdefmodulecom[19] = "PPDefmoduleCommand";

char aPpdefmodule[12] = "ppdefmodule";

char asc_50ABFC[2] = "\n";

char aDefmoduleNam_3[15] = "defmodule name";

char aDefmodules_0[11] = "defmodules";

char aDefmodule_6[12] = "(defmodule ";

char aDefmodule_7[10] = "defmodule";

char asc_50AC34[2] = "+";

char aMain_3[5] = "MAIN";

char asc_50AC40[2] = "\n";

char aImport[7] = "import";

char aExport[7] = "export";

char asc_50AC54[2] = ")";

char asc_50AC58[2] = " ";

char aAll[4] = "ALL";

char aNone_1[5] = "NONE";

char aModulpsr[9] = "MODULPSR";

char aModule[8] = "Module ";

char aDoesNotExport[18] = " does not export ";

char aAnyConstructs[15] = "any constructs";

char aAny[5] = "any ";

char aConstructs[12] = " constructs";

char aThe_1[5] = "the ";

char a__30[3] = ".\n";

char aAssert_0[7] = "assert";

char asc_50AD10[2] = " ";

char aTmpltrhs[9] = "TMPLTRHS";

char aSlot_1[6] = "Slot ";

char aRequiresAValue[61] = " requires a value because of its (default ?NONE) attribute.\n";

_BYTE g_Rules_SlotAssertBitmapScratch[4] = { 0, 0, 0, 0 };

char aModifycommand[14] = "ModifyCommand";

char aModify[7] = "modify";

char aDuplicatecomma[17] = "DuplicateCommand";

char aDuplicate[10] = "duplicate";

char asc_50ADC8[2] = " ";

char aTmpltfun_0[9] = "TMPLTFUN";

char aFactIndexesCan[34] = "Fact-indexes can only be used by ";

char aAsATopLevelCom[26] = " as a top level command.\n";

char asc_50AE50[2] = ")";

char aDefglobal_1[10] = "defglobal";

char aGenericFunct_0[18] = "generic functions";

char aDefgeneric_2[11] = "defgeneric";

char aDeffunctions_0[13] = "deffunctions";

char aDeffunction_2[12] = "deffunction";

char aDefclass_0[9] = "defclass";

char aDeffacts_0[9] = "deffacts";

char a01w_6[4] = "01w";

char aGetDeffactsLis[18] = "get-deffacts-list";

char a11w_10[4] = "11w";

char aUndeffactscomm[18] = "UndeffactsCommand";

char aUndeffacts[11] = "undeffacts";

char aDeffactsmodule[23] = "DeffactsModuleFunction";

char aDeffactsModule[16] = "deffacts-module";

char aListdeffactsco[20] = "ListDeffactsCommand";

char aListDeffacts[14] = "list-deffacts";

char aPpdeffactscomm[18] = "PPDeffactsCommand";

char aPpdeffacts[11] = "ppdeffacts";

char aAssert_2[7] = "assert";

char aInitialFact_1[13] = "initial-fact";

char aDeffacts_3[11] = "(deffacts ";

char aDeffacts_4[9] = "deffacts";

char asc_50AFAC[2] = "$";

char asc_50AFC8[2] = "\n";

char aDeffacts_1[9] = "deffacts";

char aDeffacts_2[9] = "deffacts";

char aIncludeDffctde[23] = "#include \"dffctdef.h\"\n";

char aStructDeffacts[22] = "struct deffactsModule";

char aStructDeffac_0[16] = "struct deffacts";

char asc_50B024[2] = "{";

char asc_50B028[2] = "}";

char asc_50B02C[2] = ",";

char aMihsSD_DD_5[18] = "MIHS &%s%d_%d[%d]";

char aGenericFunct_1[17] = "generic function";

char aGenrcfun[9] = "GENRCFUN";

char aDefgeneric_0[12] = "Defgeneric ";

char aCannotBeModifi[60] = " cannot be modified while one of its methods is executing.\n";

char aUnableToFindGe[33] = "Unable to find generic function ";

char aInFunctionPrev[31] = " in function preview-generic.\n";

char aSys[4] = "SYS";

char aInFunction_2[14] = " in function ";

char a__23[3] = ".\n";

char aUnableToFindMe[23] = "Unable to find method ";

char asc_50B158[3] = " #";

char asc_50B160[2] = "\n";

char aNoApplicableMe[27] = "No applicable methods for ";

char aGenerics[9] = "generics";

char aNull_4[5] = "NULL";

char aSD_DD[13] = "&%s%d_%d[%d]";

char aMihsSD_DD[18] = "MIHS &%s%d_%d[%d]";

char aIncludeGenrcfu[23] = "#include \"genrcfun.h\"\n";

char aDefgeneric_mod[18] = "DEFGENERIC_MODULE";

char aDefgeneric_5[11] = "DEFGENERIC";

char aDefmethod_2[10] = "DEFMETHOD";

char asc_50B1FC[3] = ",\n";

char aRestriction[12] = "RESTRICTION";

char aVoid_1[7] = "VOID *";

char asc_50B214[2] = "{";

char asc_50B218[2] = "}";

char a00_15[6] = ",0,0,";

char aU0[7] = ",%u,0}";

char aU0DDDDU0[24] = "{%u,0,%d,%d,%d,%d,%u,0,";

char aNull_25[6] = "NULL,";

char aSD_DD_7[14] = "&%s%d_%d[%d],";

char aNull_26[7] = ",NULL}";

char aU[5] = ",%u}";

char aVs_1[4] = "VS ";

char aDefgeneric_3[13] = "(defgeneric ";

char aDefgeneric_1[11] = "defgeneric";

char asc_50B28C[2] = "^";

char aGenrcpsr[9] = "GENRCPSR";

char aExpectedToComp[38] = "Expected ')' to complete defgeneric.\n";

char asc_50B2C4[2] = "\n";

char aDefmethod_0[12] = "(defmethod ";

char aDefmethod_1[10] = "defmethod";

char aMethod[7] = "method";

char aCannotReplaceT[44] = "Cannot replace the implicit system method #";

char a__12[3] = ".\n";

char aNewMethod[13] = "New method #";

char aWouldBeIndisti[42] = " would be indistinguishable from method #";

char aMethod_0[12] = "   Method #";

char aDefined_[11] = " defined.\n";

char aRedefined_[13] = " redefined.\n";

char aDefgenericsAre[52] = "Defgenerics are not allowed to replace constructs.\n";

char aDeffunction_0[13] = "Deffunction ";

char aImportedFromMo[23] = " imported from module ";

char aConflictsWithT[34] = " conflicts with this defgeneric.\n";

char aDefgenericsA_0[54] = "Defgenerics are not allowed to replace deffunctions.\n";

char aTheSystemFunct[21] = "The system function ";

char aCannotBeOverlo[24] = " cannot be overloaded.\n";

char asc_50B47C[2] = "&";

char asc_50B480[2] = " ";

char aMethodIndexOut[28] = "Method index out of range.\n";

char aExpectedAToBeg[56] = "Expected a '(' to begin method parameter restrictions.\n";

char aPrccode_1[8] = "PRCCODE";

char aNoParametersAl[49] = "No parameters allowed after wildcard parameter.\n";

char aExpectedAVaria[50] = "Expected a variable for parameter specification.\n";

char aExpectedAVar_0[57] = "Expected a variable or '(' for parameter specification.\n";

char asc_50B584[2] = ")";

char aQueryMustBeLas[46] = "Query must be last in parameter restriction.\n";

char aDuplicateClass[57] = "Duplicate classes not allowed in parameter restriction.\n";

char aBindsAreNotAll[45] = "Binds are not allowed in query expressions.\n";

char aExpectedAValid[39] = "Expected a valid class name or query.\n";

char aCurrentArgumen[17] = "current-argument";

char aGnrcCurrentA_0[19] = "(gnrc-current-arg)";

char aDuplicateParam[40] = "Duplicate parameter names not allowed.\n";

char aUnknownClassIn[26] = "Unknown class in method.\n";

char aClassIsRedunda[22] = " class is redundant.\n";

char aGenrcexe[9] = "GENRCEXE";

char aMethod_2[10] = " method #";

char aIsNotApplicabl[44] = " is not applicable to the given arguments.\n";

char asc_50B73C[3] = ">>";

char asc_50B740[3] = "<<";

char aNoApplicable_0[27] = "No applicable methods for ";

char a__24[3] = ".\n";

char aGenericFunct_5[18] = "generic function ";

char aShadowedMethod[53] = "Shadowed methods not applicable in current context.\n";

char aCallSpecific_0[21] = "call-specific-method";

char aGnc[5] = "GNC ";

char asc_50B7D0[2] = " ";

char asc_50B7D4[3] = "::";

char aEd_1[5] = " ED:";

char aMth[5] = "MTH ";

char asc_50B7E8[3] = ":#";

char aSys_0[4] = "SYS";

char aUnableToDeterm[30] = "Unable to determine class of ";

char aInGenericFunct[22] = " in generic function ";

char aDeffunctions_1[13] = "deffunctions";

char aNull_5[5] = "NULL";

char aSD_DD_0[13] = "&%s%d_%d[%d]";

char aMihsSD_DD_0[18] = "MIHS &%s%d_%d[%d]";

char aIncludeDffnxfu[23] = "#include \"dffnxfun.h\"\n";

char aDeffunction_mo[19] = "DEFFUNCTION_MODULE";

char aDeffunction_8[12] = "DEFFUNCTION";

char asc_50B89C[2] = "{";

char asc_50B8A0[2] = "}";

char a000_0[8] = ",0,0,0,";

char aDDD[10] = ",%d,%d,%d";

char aDeffunction_3[14] = "(deffunction ";

char asc_50B8D8[2] = "!";

char aDeffunction_4[12] = "deffunction";

char asc_50B8E8[2] = "\n";

char aDffnxpsr[9] = "DFFNXPSR";

char aDeffunctionsAr[53] = "Deffunctions are not allowed to replace constructs.\n";

char aDeffunctions_3[61] = "Deffunctions are not allowed to replace external functions.\n";

char aDefgeneric_4[12] = "Defgeneric ";

char aImportedFrom_0[23] = " imported from module ";

char aConflictsWit_0[35] = " conflicts with this deffunction.\n";

char aDeffunctions_4[60] = "Deffunctions are not allowed to replace generic functions.\n";

char aDfnxpsr[8] = "DFNXPSR";

char aDeffunction_5[13] = "Deffunction ";

char aMayNotBeRedefi[46] = " may not be redefined while it is executing.\n";

char asc_50BA48[4] = ">> ";

char asc_50BA4C[4] = "<< ";

char aDeffunction_9[13] = "deffunction ";

char a__33[3] = ".\n";

char aDfn[5] = "DFN ";

char asc_50BA6C[3] = "::";

char aEd_2[5] = " ED:";

char aDefglobal_0[10] = "defglobal";

char a01w_7[4] = "01w";

char aGetDefglobalLi[19] = "get-defglobal-list";

char a11w_11[4] = "11w";

char aUndefglobalcom[19] = "UndefglobalCommand";

char aUndefglobal[12] = "undefglobal";

char aDefglobalmodul[24] = "DefglobalModuleFunction";

char aDefglobalModul[17] = "defglobal-module";

char aListdefglobals[22] = "ListDefglobalsCommand";

char aListDefglobals[16] = "list-defglobals";

char aPpdefglobalcom[19] = "PPDefglobalCommand";

char aPpdefglobal[12] = "ppdefglobal";

char aGlobals[8] = "globals";

char a11_5[3] = "11";

char aSetresetglobal[23] = "SetResetGlobalsCommand";

char aSetResetGlobal[18] = "set-reset-globals";

char a00_11[3] = "00";

char aGetresetglobal[23] = "GetResetGlobalsCommand";

char aGetResetGlobal[18] = "get-reset-globals";

char a01w_8[4] = "01w";

char aShowdefglobals[22] = "ShowDefglobalsCommand";

char aShowDefglobals[16] = "show-defglobals";

char asc_50BBE4[3] = ":\n";

char asc_50BBE8[4] = "   ";

char asc_50BBEC[2] = "\n";

char aDefglobalVariablePrefix[3] = "?*";

char asc_50BBF4[5] = "* = ";

char aDefglobal_5[12] = "(defglobal ";

char aDefglobal_2[10] = "defglobal";

char asc_50BC20[2] = " ";

char aRedefiningDefg[24] = "Redefining defglobal: ?";

char aDefiningDefglo[21] = "Defining defglobal: ";

char asc_50BC64[2] = "\n";

char asc_50BC68[2] = ":";

char asc_50BC6C[2] = "=";

char asc_50BC70[2] = ")";

char aGloblpsr[9] = "GLOBLPSR";

char aGlobalVariable[20] = "\nGlobal variable ?*";

char aWasReferencedB[39] = "* was referenced, but is not defined.\n";

char aDefglobal_3[10] = "defglobal";

char aIncludeGloblde[23] = "#include \"globldef.h\"\n";

char aStructDefgloba[23] = "struct defglobalModule";

char aStructDefglo_0[17] = "struct defglobal";

char asc_50BD24[2] = "{";

char asc_50BD28[2] = "}";

char asc_50BD2C[2] = ",";

char a00Ld[9] = "0,0,%ld,";

char aNullRvoid[13] = "{NULL,RVOID}";

char aMihsSD_DD_6[18] = "MIHS &%s%d_%d[%d]";

char aNull_6[5] = "NULL";

char aSD_LdLd_0[15] = "&%s%d_%ld[%ld]";

char aInit[5] = "init";

char aDelete_0[7] = "delete";

char aDefclass_1[9] = "defclass";

char aSelf[5] = "self";

char aDefmessageHand[20] = "defmessage-handlers";

char aDefmessageHa_0[19] = "defmessage-handler";

char a23w_0[4] = "23w";

char aUndefmessageha[27] = "UndefmessageHandlerCommand";

char aUndefmessageHa[21] = "undefmessage-handler";

char a2Uuw[6] = "2*uuw";

char aSendcommand[12] = "SendCommand";

char aSend[5] = "send";

char a22w_0[4] = "22w";

char aPreviewsendcom[19] = "PreviewSendCommand";

char aPreviewSend[13] = "preview-send";

char aPpdefmessageha[27] = "PPDefmessageHandlerCommand";

char aPpdefmessageHa[21] = "ppdefmessage-handler";

char a02w_0[4] = "02w";

char aListdefmessage[30] = "ListDefmessageHandlersCommand";

char aListDefmessage[25] = "list-defmessage-handlers";

char a00_12[3] = "00";

char aNexthandlerava[21] = "NextHandlerAvailable";

char aNextHandlerp[14] = "next-handlerp";

char aCallNextHandle[18] = "call-next-handler";

char aOverrideNextHa[22] = "override-next-handler";

char a11w_12[4] = "11w";

char aDynamichandler[22] = "DynamicHandlerGetSlot";

char aDynamicGet[12] = "dynamic-get";

char a1W_2[5] = "1**w";

char aDynamichandl_0[22] = "DynamicHandlerPutSlot";

char aDynamicPut[12] = "dynamic-put";

char aGet[4] = "get";

char aPut[4] = "put";

char aMessages[9] = "messages";

char aMessageHandl_0[17] = "message-handlers";

char aMsgcom[7] = "MSGCOM";

char aUnableToDele_1[36] = "Unable to delete message-handlers.\n";

char asc_50BFD4[2] = "*";

char aUnableToFind_0[32] = "Unable to find message-handler ";

char asc_50C030[2] = " ";

char aForClass[12] = " for class ";

char aInFunctionPpde[36] = " in function ppdefmessage-handler.\n";

char aMessageHandl_5[16] = "message-handler";

char aInitSlots_0[11] = "init-slots";

char aUser_0[5] = "USER";

char aDeleteInstan_0[16] = "delete-instance";

char aPpinstance_0[11] = "ppinstance";

char aPrint[6] = "print";

char aDirectModify_1[16] = "(direct-modify)";

char aDirectModify_2[14] = "direct-modify";

char aMessageModif_2[17] = "(message-modify)";

char aMessageModif_3[15] = "message-modify";

char aDirectDuplic_1[19] = "(direct-duplicate)";

char aDirectDuplic_2[17] = "direct-duplicate";

char aMessageDupli_2[20] = "(message-duplicate)";

char aMessageDupli_3[18] = "message-duplicate";

char aWatch_2[6] = "watch";

char aUnwatch_1[8] = "unwatch";

char aListWatchIte_2[17] = "list-watch-items";

char asc_50C164[3] = ":\n";

char aClassName[11] = "class name";

char aHandlerName[13] = "handler name";

char aHandlerType[13] = "handler type";

char aHandler_0[8] = "handler";

char asc_50C19C[4] = "   ";

char aOn_4[7] = " = on\n";

char aOff_4[8] = " = off\n";

char aDefinstances[13] = "definstances";

char a11w_13[4] = "11w";

char aUndefinstanc_0[15] = "undefinstances";

char aPpdefinstanc_0[15] = "ppdefinstances";

char a01_2[3] = "01";

char aListdefinstanc[24] = "ListDefinstancesCommand";

char aListDefinstanc[18] = "list-definstances";

char aGetdefinstance[28] = "GetDefinstancesListFunction";

char aGetDefinstance[22] = "get-definstances-list";

char aGetdefinstan_0[29] = "GetDefinstancesModuleCommand";

char aDefinstancesMo[20] = "definstances-module";

char aDefinstances_2[15] = "(definstances ";

char aActiveMakeIn_1[21] = "active-make-instance";

char aMakeInstance_2[14] = "make-instance";

char asc_50C2E4[3] = ")\n";

char aDefinstancesConstructMarker[2] = "@";

char aActive[7] = "active";

char asc_50C2F4[2] = " ";

char aInitialObjec_1[15] = "INITIAL-OBJECT";

char aQds[6] = "(QDS)";

char aGetqueryinstan[17] = "GetQueryInstance";

char aQueryInstance[17] = "(query-instance)";

char aGetqueryinst_0[21] = "GetQueryInstanceSlot";

char aQueryInstanceS[22] = "(query-instance-slot)";

char aAnyinstances[13] = "AnyInstances";

char aAnyInstancep[14] = "any-instancep";

char aFindInstance[14] = "find-instance";

char aFindAllInstanc[19] = "find-all-instances";

char aDoForInstance[16] = "do-for-instance";

char aDoForAllInstan[21] = "do-for-all-instances";

char aDelayedDoForAl[29] = "delayed-do-for-all-instances";

char aSymbol_6[7] = "symbol";

char aInstanceSetQ_0[19] = "instance-set query";

char aObjects[8] = "objects";

char aNull_7[5] = "NULL";

char aSD_DD_1[13] = "&%s%d_%d[%d]";

char aMihsSD_DD_1[18] = "MIHS &%s%d_%d[%d]";

char aObjectsruntime[57] = "   ObjectsRunTimeInitialize(%s%d_1,%s%d_1,%s%d_1,%s%d);\n";

char aIncludeClassco[23] = "#include \"classcom.h\"\n";

char aIncludeClassin[23] = "#include \"classini.h\"\n";

char aDefclass_modul[16] = "DEFCLASS_MODULE";

char aDefclass_6[9] = "DEFCLASS";

char aDefclass_7[11] = "DEFCLASS *";

char asc_50C57C[3] = ",\n";

char asc_50C580[5] = "};\n\n";

char aUnsignedSDU[21] = "unsigned %s%d = %u;\n";

char aExternUnsign_0[23] = "extern unsigned %s%d;\n";

char aSlot_name[12] = "SLOT_NAME *";

char aSlot_name_0[10] = "SLOT_NAME";

char aU1U[11] = "{ %u,1,%u,";

char asc_50C5DC[2] = ",";

char a0l[6] = ",0L }";

char asc_50C5E8[2] = "{";

char asc_50C5EC[2] = "}";

char a1UUU00U0U[29] = ",1,%u,%u,%u,0,0,%u,0,%u,\n   ";

char aUSD_DD[21] = "{ %u,&%s%d_%d[%d] },";

char a0Null[12] = "{ 0,NULL },";

char a0Null_0[16] = "{ 0,NULL },\n   ";

char aSD_DD_8[14] = "&%s%d_%d[%d],";

char aNull_27[6] = "NULL,";

char aUUUUNullNull[27] = "%u,%u,%u,%u,NULL,NULL,\n   ";

char aU_0[4] = "%u,";

char asc_50C67C[5] = ",\"\"}";

char aSlot_desc[10] = "SLOT_DESC";

char aUUUUUUUUUUUUUU[45] = "{ %u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,%u,";

char asc_50C6C0[6] = ",\n   ";

char aVoid_2[11] = ",(VOID *) ";

char aNull_28[6] = ",NULL";

char a00l[7] = ",0,0L,";

char aSD_UU000Null[30] = "{ &%s%d_%u[%u],0,0,0,NULL } }";

char aNull000Null[22] = "{ NULL,0,0,0,NULL } }";

char aSlot_desc_0[12] = "SLOT_DESC *";

char aSD_UU[13] = "&%s%d_%u[%u]";

char aUnsigned[9] = "unsigned";

char aU_1[3] = "%u";

char aHandler_1[8] = "HANDLER";

char aUU000[15] = "{ %u,%u,0,0,0,";

char aDDD_0[11] = ",%d,%d,%d,";

char aNull_29[8] = ",NULL }";

char aObject[7] = "object";

char aObjrtbld[9] = "OBJRTBLD";

char aObjects_0[8] = "objects";

char aObjectmatchdel[17] = "ObjectMatchDelay";

char aObjectPatternM[27] = "object-pattern-match-delay";

char aNoObjectsOfExi[53] = "No objects of existing classes can satisfy pattern.\n";

char asc_50C7F8[2] = " ";

char aNoObjectsOfE_0[44] = "No objects of existing classes can satisfy ";

char aRestrictionInO[33] = " restriction in object pattern.\n";

char aNoObjectsOfE_1[53] = "No objects of existing classes can satisfy pattern #";

char a__25[3] = ".\n";

char aMultipleRestri[36] = "Multiple restrictions on attribute ";

char aNotAllowed_[15] = " not allowed.\n";

char asc_50C928[2] = ")";

char aUndefinedClass[36] = "Undefined class in object pattern.\n";

char aIsARestriction[37] = "is-a restriction in object pattern.\n";

char aInitialObjec_2[15] = "INITIAL-OBJECT";

char aDefclass_3[11] = "(defclass ";

char aDefclass_4[9] = "defclass";

char asc_50C9A0[2] = "#";

char asc_50C9A4[2] = "(";

char aRole[5] = "role";

char aConcrete[9] = "concrete";

char aPatternMatch[14] = "pattern-match";

char aNonReactive[13] = "non-reactive";

char aSlot_6[5] = "slot";

char aSingleSlot[12] = "single-slot";

char aMultislot_0[10] = "multislot";

char aMessageHandl_6[16] = "message-handler";

char asc_50CA24[2] = "\n";

char aClasspsr[9] = "CLASSPSR";

char aAnAbstractClas[39] = "An abstract class cannot be reactive.\n";

char aCannotRedefi_0[44] = "Cannot redefine a predefined system class.\n";

char aClassCannotBeR[34] = " class cannot be redefined while\n";

char aOutstandingRef[47] = "    outstanding references to it still exist.\n";

char aClass_2[7] = "Class ";

char aAlreadyDeclare[20] = " already declared.\n";

char asc_50CAF8[2] = " ";

char asc_50CB18[2] = ")";

char aObject_1[7] = "OBJECT";

char aAbstractDirect[62] = "Abstract: direct instances of this class cannot be created.\n\n";

char aConcreteDirect[58] = "Concrete: direct instances of this class can be created.\n";

char aReactiveDirect[71] = "Reactive: direct instances of this class can match defrule patterns.\n\n";

char aNonReactiveDir[78] = "Non-reactive: direct instances of this class cannot match defrule patterns.\n\n";

char aDirectSupercla[21] = "Direct Superclasses:";

char aInheritancePre[24] = "Inheritance Precedence:";

char aDirectSubclass[19] = "Direct Subclasses:";

char aConstraintInfo[37] = "\nConstraint information for slots:\n\n";

char aRecognizedMess[30] = "Recognized message-handlers:\n";

char aRw_0[3] = "RW";

char aNil_6[4] = "NIL";

char aR_6[2] = "R";

char aW_6[2] = "W";

char aSlotExistp_0[12] = "slot-existp";

char aInherit_0[8] = "inherit";

char aKeywordInher_0[18] = "keyword \"inherit\"";

char aMessageHandl_8[23] = "message-handler-existp";

char aSlotWritable_0[15] = "slot-writablep";

char aSlotInitable_0[15] = "slot-initablep";

char aSlotPublicp_0[13] = "slot-publicp";

char aSlotDirectAc_0[20] = "slot-direct-accessp";

char aClassexm[9] = "CLASSEXM";

char aInheritedSlot[16] = "Inherited slot ";

char aFromClass[13] = " from class ";

char aIsNotValidForF[28] = " is not valid for function ";

char asc_50CE14[2] = "\n";

char asc_50CE18[3] = "  ";

char asc_50CE1C[3] = " *";

char aSlots_0[6] = "SLOTS";

char aFldDefPrpAccSt[37] = "FLD DEF PRP ACC STO MCH SRC VIS CRT ";

char aOvrdMsg[9] = "OVRD-MSG";

char aSourceS[11] = "SOURCE(S)\n";

char aMlt[5] = "MLT ";

char aSgl[5] = "SGL ";

char aNil_5[5] = "NIL ";

char aDyn[5] = "DYN ";

char aStc[5] = "STC ";

char aInh[5] = "INH ";

char aInt_0[5] = "INT ";

char aR_5[5] = " R  ";

char aRw[5] = "RW  ";

char aShr[5] = "SHR ";

char aLcl[5] = "LCL ";

char aRct[5] = "RCT ";

char aCmp[5] = "CMP ";

char aExc[5] = "EXC ";

char aPub[5] = "PUB ";

char aPrv[5] = "PRV ";

char asc_50CEE8[2] = " ";

char aDescribeClas_1[21] = "***describe-class***";

char aSymStrInnInaEx[33] = "SYM STR INN INA EXA FTA INT FLT\n";

char aRng[6] = "RNG:[";

char a___0[3] = "..";

char asc_50CF34[3] = "] ";

char aCrd[6] = "CRD:[";

char asc_50CF40[2] = "]";

char aRngOo__Oo[47] = " +   +   +   +   +   +   +   +  RNG:[-oo..+oo]";

char aCrd0__Oo[14] = " CRD:[0..+oo]";

char asc_50CF84[5] = " #  ";

char asc_50CF8C[5] = " +  ";

char asc_50CF94[5] = "    ";

char aInherit_1[8] = "inherit";

char aClassSlots_0[12] = "class-slots";

char aClassSupercl_0[19] = "class-superclasses";

char aClassSubclas_0[17] = "class-subclasses";

char aGetDefmessag_0[28] = "get-defmessage-handler-list";

char aMlt_0[4] = "MLT";

char aSgl_0[4] = "SGL";

char aNil_7[4] = "NIL";

char aDyn_0[4] = "DYN";

char aStc_0[4] = "STC";

char aInh_0[4] = "INH";

char aInt_1[4] = "INT";

char aR_9[2] = "R";

char aRw_1[3] = "RW";

char aShr_0[4] = "SHR";

char aLcl_0[4] = "LCL";

char aRct_0[4] = "RCT";

char aCmpFacet[4] = "CMP";

char aExcFacet[4] = "EXC";

char aPubFacet[4] = "PUB";

char aPrvFacet[4] = "PRV";

char aExternStructSy[40] = "extern struct symbolHashNode S%d_%d[];\n";

char aStructSymbolha[36] = "struct symbolHashNode S%d_%d[] = {\n";

char aNull_8[7] = "{NULL,";

char aSD_DD_2[14] = "{&S%d_%d[%d],";

char aLd000D[14] = "%ld,0,0,0,%d,";

char asc_50D12C[5] = "}};\n";

char asc_50D134[4] = "},\n";

char aExternStructBi[40] = "extern struct bitMapHashNode B%d_%d[];\n";

char aStructBitmapha[36] = "struct bitMapHashNode B%d_%d[] = {\n";

char aBD_DD[14] = "{&B%d_%d[%d],";

char aLd000DCharLD_D[37] = "%ld,0,0,0,%d,(char *) &L%d_%d[%d],%d";

char aExternUnsigned[32] = "extern unsigned long L%d_%d[];\n";

char aUnsignedLongLD[28] = "unsigned long L%d_%d[] = {\n";

char asc_50D1F8[2] = ",";

char a0xLxl[7] = "0x%lxL";

char asc_50D204[4] = "};\n";

char asc_50D208[3] = ",\n";

char aExternStructFl[39] = "extern struct floatHashNode F%d_%d[];\n";

char aStructFloathas[35] = "struct floatHashNode F%d_%d[] = {\n";

char aFD_DD[14] = "{&F%d_%d[%d],";

char aS_11[3] = "%s";

char aExternStructIn[41] = "extern struct integerHashNode I%d_%d[];\n";

char aStructIntegerh[37] = "struct integerHashNode I%d_%d[] = {\n";

char aID_DD[14] = "{&I%d_%d[%d],";

char aLd[4] = "%ld";

char aExternStruct_0[40] = "extern struct symbolHashNode *sht%d[];\n";

char aStructSymbol_0[38] = "struct symbolHashNode *sht%d[%d] = {\n";

char aExternStruct_1[39] = "extern struct floatHashNode *fht%d[];\n";

char aStructFloath_0[37] = "struct floatHashNode *fht%d[%d] = {\n";

char aNull_9[5] = "NULL";

char aExternStruct_2[41] = "extern struct integerHashNode *iht%d[];\n";

char aStructIntege_0[39] = "struct integerHashNode *iht%d[%d] = {\n";

char aExternStruct_3[41] = "extern struct bitMapHashNode *bmht%d[];\n";

char aStructBitmap_0[39] = "struct bitMapHashNode *bmht%d[%d] = {\n";

char aSD_DD_3[12] = "&S%d_%d[%d]";

char aFD_DD_0[12] = "&F%d_%d[%d]";

char aID_DD_0[12] = "&I%d_%d[%d]";

char aBD_DD_0[12] = "&B%d_%d[%d]";

char asc_50D454[2] = "\"";

char aCstrncmp[9] = "CSTRNCMP";

char aConstraintsA_0[56] = "Constraints are not saved with a constructs-to-c image\n";

char aWhenDynamicC_0[49] = "  when dynamic constraint checking is disabled.\n";

char aExternConstrai[36] = "extern CONSTRAINT_RECORD C%d_%d[];\n";

char aConstraint_rec[32] = "CONSTRAINT_RECORD C%d_%d[] = {\n";

char aDDDDDDDDDDDDDD[52] = "{%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d";

char a0[4] = ",0,";

char asc_50D54C[2] = ",";

char aNull_10[6] = ",NULL";

char aNull_11[7] = ",NULL,";

char aCD_DD[14] = ",&C%d_%d[%d],";

char aDD_1[6] = "%d,%d";

char asc_50D578[5] = "}};\n";

char asc_50D580[4] = "},\n";

char aNull_21[5] = "NULL";

char aCD_DD_0[12] = "&C%d_%d[%d]";

char aDefmodule_2[10] = "defmodule";

char aNull_18[5] = "NULL";

char aSD_LdLd_5[15] = "&%s%d_%ld[%ld]";

char aSetlistofdefmo[42] = "   SetListOfDefmodules((VOID *) %s%d_1);\n";

char aSetlistofdef_0[31] = "   SetListOfDefmodules(NULL);\n";

char aSetcurrentmo_0[55] = "   SetCurrentModule((VOID *) GetNextDefmodule(NULL));\n";

char aIncludeModulde[23] = "#include \"moduldef.h\"\n";

char aStructDefmodul[43] = "struct defmoduleItemHeader *%s%d_%d[] = {\n";

char aExternStructDe[47] = "extern struct defmoduleItemHeader *%s%d_%d[];\n";

char aStructDefmod_0[17] = "struct defmodule";

char asc_50D6C8[2] = "{";

char aNull_30[7] = ",NULL,";

char aSD_1D[13] = "&%s%d_1[%d],";

char asc_50D6E4[2] = ",";

char asc_50D6E8[3] = ",\n";

char aNull_31[6] = "NULL,";

char aSD_DD_9[14] = "&%s%d_%d[%d],";

char a0Ld[7] = "0,%ld,";

char aNull_32[6] = "NULL}";

char aSD_DD_10[14] = "&%s%d_%d[%d]}";

char Lexer_ArrayClose[4] = "};\n";

char aStructPortitem[16] = "struct portItem";

char asc_50D750[2] = " ";

char asc_50D754[2] = ")";

char Lexer_Token_Arrow[3] = "=>";

char asc_50D764[2] = " ";

char aSalience[9] = "salience";

char aAutoFocus[11] = "auto-focus";

char Lexer_Token_OpenParenSpace[3] = " (";

char aTrue_0[5] = "TRUE";

char aFalse_0[6] = "FALSE";

char aDeclare[8] = "declare";

char aRulelhs[8] = "RULELHS";

char aTest_0[5] = "test";

char aAnd_1[4] = "and";

char aLogical_0[8] = "logical";

char aNot_1[4] = "not";

char aExists_0[7] = "exists";

char aForall_0[7] = "forall";

char aOr_1[3] = "or";

char asc_50D870[3] = "  ";

char aTheLogicalCeCa[62] = "The logical CE cannot be used within a not/exists/forall CE.\n";

char asc_50D94C[2] = ")";

char aAPatternCeCann[67] = "A pattern CE cannot be bound to a pattern-address within a not CE\n";

char asc_50D9B0[3] = "<-";

char asc_50D9C8[2] = "=";

char asc_50D9CC[2] = ":";

char aDefmodule_3[10] = "defmodule";

char aAllowedSymbols[16] = "allowed-symbols";

char aType_0[5] = "type";

char aAllowedStrings[16] = "allowed-strings";

char aAllowedInteger[25] = "allowed-integers/numbers";

char aAllowedFloatsN[23] = "allowed-floats/numbers";

char aAllowedInstanc[23] = "allowed-instance-names";

char aAllowedValues[15] = "allowed-values";

char aRange_0[6] = "range";

char aCstrnpsr[9] = "CSTRNPSR";

char aThe_2[5] = "The ";

char aAttributeConfl[31] = " attribute conflicts with the ";

char aAttribute_[13] = " attribute.\n";

char aCardinality[12] = "cardinality";

char aAllowedLexemes[16] = "allowed-lexemes";

char aAllowedInteg_0[17] = "allowed-integers";

char aAllowedFloats[15] = "allowed-floats";

char aAllowedNumbers[16] = "allowed-numbers";

char aAttribute[11] = " attribute";

char aAllowedNumber[15] = "allowed-number";

char asc_50DB38[2] = " ";

char a_variable[10] = "?VARIABLE";

char aValueDoesNotMa[48] = "Value does not match the expected type for the ";

char aAttribute_0[12] = " attribute\n";

char asc_50DB94[2] = ")";

char aAttributeCanno[27] = " attribute cannot be used\n";

char aInConjunctionW[25] = "in conjunction with the ";

char aTheCardinality[27] = "The cardinality attribute ";

char aCanOnlyBeUsedW[41] = "can only be used with multifield slots.\n";

char aMinimumRangeVa[39] = "Minimum range value must be less than\n";

char aOrEqualToTheMa[37] = "or equal to the maximum range value\n";

char aMinimumCardina[45] = "Minimum cardinality value must be less than\n";

char aOrEqualToThe_0[43] = "or equal to the maximum cardinality value\n";

char aSymbol_7[7] = "SYMBOL";

char aString_3[7] = "STRING";

char aLexeme_1[7] = "LEXEME";

char aInteger_4[8] = "INTEGER";

char aFloat_4[6] = "FLOAT";

char aNumber_2[7] = "NUMBER";

char aInstanceName_4[14] = "INSTANCE-NAME";

char aInstanceAddr_8[17] = "INSTANCE-ADDRESS";

char aInstance_6[9] = "INSTANCE";

char aExternalAddr_1[17] = "EXTERNAL-ADDRESS";

char aFactAddress_2[13] = "FACT-ADDRESS";

char aAnalysis[9] = "ANALYSIS";

char aDuplicatePatte[28] = "Duplicate pattern-address ?";

char aFoundInCe_0[15] = " found in CE #";

char a__26[3] = ".\n";

char aPatternAddress[18] = "Pattern-address ?";

char aUsedInCe[14] = " used in CE #";

char aWasPreviouslyB[44] = " was previously bound within a pattern CE.\n";

char aALiteralRestri[28] = "A literal restriction value";

char aDefglobal_6[10] = "defglobal";

char aVariable_[11] = "Variable ?";

char asc_50DE28[2] = " ";

char aFoundInTheExpr[25] = "found in the expression ";

char asc_50DE48[2] = "\n";

char aWasReferencedI[23] = "was referenced in CE #";

char aField_1[9] = " field #";

char aSlot_8[7] = " slot ";

char aBeforeBeingDef[24] = " before being defined.\n";

char aIsUsedAsBothAS[62] = " is used as both a single and multifield variable in the LHS\n";

char aRulecstr[9] = "RULECSTR";

char aVariable__0[11] = "Variable ?";

char aInCe[9] = " in CE #";

char aPattern_0[10] = "Pattern #";

char aField_2[9] = " field #";

char aSlot_9[7] = " slot ";

char aHasConstraintC[63] = "\nhas constraint conflicts which make the pattern unmatchable.\n";

char aTheGroupOfRest[26] = "The group of restrictions";

char aPreviousVariab[32] = "Previous variable bindings of ?";

char aCausedTheTypeR[30] = " caused the type restrictions";

char aForArgument_0[16] = "\nfor argument #";

char aOfTheExpressio[20] = " of the expression ";

char asc_50DFD4[2] = "\n";

char aToBeViolated_[18] = " to be violated.\n";

char aFoundInTheRule[42] = "\nfound in the rule's RHS to be violated.\n";

char aJ[3] = "=j";

char asc_50E03C[2] = "\n";

char asc_50E04C[3] = "<=";

char aLength_1[8] = "length$";

char aLexeme[7] = "LEXEME";

char aNumber_0[7] = "NUMBER";

char aInstance_0[9] = "INSTANCE";

char aAddress[8] = "ADDRESS";

char aDefmessageHa_1[21] = "(defmessage-handler ";

char aDefmessageHa_2[19] = "defmessage-handler";

char asc_50E0A8[2] = "~";

char aMsgpsr[7] = "MSGPSR";

char aAClassMustBeDe[54] = "A class must be defined before its message-handlers.\n";

char aMessageHandl_1[50] = "Message-handlers cannot be attached to the class ";

char a__13[3] = ".\n";

char aCannotReDefine[57] = "Cannot (re)define message-handlers during execution of \n";

char aOtherMessageHa[46] = "  other message-handlers for the same class.\n";

char asc_50E190[2] = " ";

char aHandler[12] = "   Handler ";

char aDefined__0[11] = " defined.\n";

char aRedefined__0[13] = " redefined.\n";

char aSystemMessageH[46] = "System message-handlers may not be modified.\n";

char aMessageHandl_2[16] = "message-handler";

char asc_50E1FC[2] = "\n";

char aDefaultPublicH[32] = "*** Default Public Handlers ***";

char aAccessorSetterMultifieldParamPrefix[3] = "$?";

char aAccessorSetterSinglefieldParamPrefix[2] = "?";

char aSelf_0[5] = "self";

char aIllegalSlotRef[43] = "Illegal slot reference in parameter list.\n";

char aHndVar[8] = "hnd-var";

char aActiveInstance[46] = "Active instance parameter cannot be changed.\n";

char aIllegalValueFo[36] = "Illegal value for ?self reference.\n";

char aNoSuchSlot_0[14] = "No such slot ";

char aInClass_1[11] = " in class ";

char aFor_selfRefere[23] = " for ?self reference.\n";

char aCstrnchk_2[9] = "CSTRNCHK";

char aExpressionFor[16] = "Expression for ";

char aDirectSlotWrit[18] = "direct slot write";

char aDefinstances_0[13] = "definstances";

char aDefinstances_1[13] = "definstances";

char aMihsSD_DD_7[18] = "MIHS &%s%d_%d[%d]";

char aIncludeDefins_[21] = "#include \"defins.h\"\n";

char aDefinstances_m[20] = "DEFINSTANCES_MODULE";

char aDefinstances_3[13] = "DEFINSTANCES";

char asc_50E3D0[2] = "{";

char asc_50E3D4[2] = "}";

char a0_2[4] = ",0,";

char asc_50E3F8[2] = " ";

char aInsqypsr[9] = "INSQYPSR";

char aDuplicateIns_0[53] = "Duplicate instance member variable name in function ";

char a__27[3] = ".\n";

char asc_50E444[2] = ")";

char aBindsAreNotA_0[57] = "Binds are not allowed in instance-set query in function ";

char aCannotRebindIn[44] = "Cannot rebind instance-set member variable ";

char aInFunction_3[14] = " in function ";

char aQueryInstanc_0[17] = "(query-instance)";

char aQueryInstanc_1[22] = "(query-instance-slot)";

char aQueryVar[10] = "query-var";

char aObjectPatterns[16] = "object-patterns";

char aNull_33[5] = "NULL";

char aSD_DD_11[13] = "&%s%d_%d[%d]";

char aSetobjectnetwo[43] = "   SetObjectNetworkPointer(&%s%d_%d[%d]);\n";

char aSetobjectnet_0[51] = "   SetObjectNetworkTerminalPointer(&%s%d_%d[%d]);\n";

char aSetobjectnet_1[35] = "   SetObjectNetworkPointer(NULL);\n";

char aSetobjectnet_2[43] = "   SetObjectNetworkTerminalPointer(NULL);\n";

char aIncludeObjrt_0[23] = "#include \"objrtmch.h\"\n";

char aObject_pattern[35] = "OBJECT_PATTERN_NODE %s%d_%d[] = {\n";

char aExternObject_p[39] = "extern OBJECT_PATTERN_NODE %s%d_%d[];\n";

char a0UUUU0lU[22] = "{0,%u,%u,%u,%u,0L,%u,";

char asc_50E654[2] = ",";

char a0l_0[5] = ",0L}";

char asc_50E660[4] = "};\n";

char asc_50E664[3] = ",\n";

char aObject_alpha_n[33] = "OBJECT_ALPHA_NODE %s%d_%d[] = {\n";

char aExternObject_a[37] = "extern OBJECT_ALPHA_NODE %s%d_%d[];\n";

char asc_50E6B4[2] = "{";

char a0l_1[5] = ",0L,";

char aObjectPatter_0[16] = "object patterns";

char asc_50E6E8[2] = " ";

char aInherpsr[9] = "INHERPSR";

char aAClassMayNotHa[46] = "A class may not have itself as a superclass.\n";

char aAClassMayInher[50] = "A class may inherit from a superclass only once.\n";

char aAClassMustBe_0[53] = "A class must be defined after all its superclasses.\n";

char aAUserDefinedCl[46] = "A user-defined class cannot be a subclass of ";

char a__28[3] = ".\n";

char aMustHaveAtLeas[36] = "Must have at least one superclass.\n";

char asc_50E7F8[2] = ")";

char aPartialPrecede[32] = "Partial precedence list formed:";

char aPrecedenceLoop[33] = "Precedence loop in superclasses:";

char asc_50E840[2] = "\n";

char asc_50E844[2] = " ";

char asc_50E858[2] = "(";

char aDefault_2[8] = "default";

char aDefaultDynam_1[16] = "default-dynamic";

char aAccess[7] = "access";

char aInitializeOnly[16] = "initialize-only";

char aReadOnly[10] = "read-only";

char aReadWrite[11] = "read-write";

char aStorage[8] = "storage";

char aShared[7] = "shared";

char aLocal_0[6] = "local";

char aPropagation[12] = "propagation";

char aNoInherit[11] = "no-inherit";

char aInherit_2[8] = "inherit";

char aSource[7] = "source";

char aComposite[10] = "composite";

char aExclusive[10] = "exclusive";

char aPatternMatch_1[14] = "pattern-match";

char aReactive_0[9] = "reactive";

char aNonReactive_0[13] = "non-reactive";

char aVisibility[11] = "visibility";

char aPublic[7] = "public";

char aPrivate[8] = "private";

char aCreateAccessor[16] = "create-accessor";

char aNone_2[5] = "NONE";

char aWrite[6] = "write";

char aRead_0[5] = "read";

char aOverrideMessag[17] = "override-message";

char aDefault_3[8] = "DEFAULT";

char aClsltpsr[9] = "CLSLTPSR";

char aDuplicateSlots[30] = "Duplicate slots not allowed.\n";

char aFacetAlreadySp[27] = " facet already specified.\n";

char aDefaultFacetAl[34] = "default facet already specified.\n";

char aCardinalityFac[58] = "Cardinality facet can only be used with multifield slots\n";

char aReadOnlySlotsM[43] = "read-only slots must have a default value\n";

char aReadOnlySlotsC[46] = "read-only slots cannot have a write accessor\n";

char aNoInheritSlots[40] = "no-inherit slots cannot also be public\n";

char aCstrnchk_3[9] = "CSTRNCHK";

char aExpressionFo_0[16] = "Expression for ";

char aDynamicDefault[22] = "dynamic default value";

int g_CompatStringHolder_Vtable;

int g_PathEntry_Vtable;

int g_PathEntryArray_Vtable[2];

_UNKNOWN g_Runtime_PaletteArrayCtorDescriptor;

_UNKNOWN g_PathEntryArray_ElementDtorDescriptor;

_UNKNOWN g_PathEntryArray_DtorDescriptor;

_UNKNOWN g_PathEntry_DtorDescriptor;

uintptr_t g_RenderSurface_BlitCursorVtable[5];

uintptr_t g_RenderSurface_LinkedBlitCursorVtable[5];

int g_Surface_BaseVtable[17];

int g_Surface_RawBuffer8Vtable[17];

int g_ScratchSurface_Vtable[17];

int g_Surface_Vtable[21];

uintptr_t g_NullBlitCursor_Vtable[5];

_UNKNOWN g_SurfaceCursor_DtorArrayTag;

_UNKNOWN g_RenderSurface_DtorArrayTag;

_UNKNOWN g_Surface_DtorArrayTag;

_UNKNOWN g_LinkedBlitCursor_DtorArrayTag;

_UNKNOWN g_ScratchSurface_DtorArrayTag;

_UNKNOWN g_BlitCursor_DtorArrayTag;

_UNKNOWN g_SurfaceRawBuffer_DtorArrayTag;

int (*g_DLXSpriteSet_Vtable)() = &DLXSpriteSet_Destroy;

_UNKNOWN g_DLXSpriteSet_DtorArrayTag;

int (*g_WCIsvListBaseRoot_Vtable)() = &WCIsvListBase_dtorRoot;

_DWORD (*g_WCIsvListBaseDtor_Vtable)(WCIsvListBase * this) = &WCIsvListBase_dtor;

int (*g_WCIsvListBaseFreeOnly_Vtable[2])() = { &WCIsvListBase_vtblDtor, &WCIsvListBase_vtblFree };

int (__thiscall *g_WCIsvListBaseDestroyElements_Vtable)(WCIsvListBase *this) = &WCIsvListBase_DestroyElementsAndDtor;

void *g_WCIsvListBaseVariant124_Vtable = &WCIsvListBase_dtorVariant124;

void *g_WCIsvListBaseVariant134_Vtable = &WCIsvListBase_dtorVariant134;

_UNKNOWN g_WCIsvListBaseRoot_DtorArrayTag;

_UNKNOWN g_WCIsvListBaseVariant124_DtorArrayTag;

_UNKNOWN g_WCIsvListBaseVariant134_DtorArrayTag;

_UNKNOWN g_FileSystemMountTable_DtorArrayTag;

int (*g_RenderState_Vtable[6])() =
{
  &Noop_InputDeviceDoOp,
  &Noop_InputDeviceGetParamB,
  &Noop_InputDeviceSetParamA,
  &Input_Init,
  &Input_Shutdown,
  &RenderState_PollInputAndClampCursor
};

int (*g_Device_Vtable[6])() =
{
  &Device_DoOp,
  &Device_GetParamB,
  &Device_SetParamA,
  &Input_Init,
  &DD_GetSurfacePitch,
  &Device_UpdateRect
};

int (*g_IOStreamAdapter_Vtable[4])() = { &IO_StreamAdapterReadBytes, &IO_StreamAdapterIsAtEnd, &IO_StreamAdapterInvokeAtEnd, &IO_StreamAdapterReadStub };

_UNKNOWN g_IOStreamAdapter_DtorArrayTag;

_UNKNOWN g_CAviDecompressor_AllocTypeTag;

IDirectDrawSurface stru_50F60C = { NULL };

IDirectDrawSurface2 stru_50F6A0 = { NULL };

IDirectDrawSurface stru_50F734 = { NULL };

IDirectDrawSurface stru_50F740 = { NULL };

IDirectDrawSurface2 stru_50F74C = { NULL };

IDirectDrawSurface2 stru_50F758 = { NULL };

int (*g_CAviSourceInterface_Vtable)() = &CAviDecompressor_DestroySourceInterface;

int (*g_CAviDecompressor_Vtable)() = &CAviDecompressor_Destroy;

_UNKNOWN g_CAviSourceInterface_DtorArrayTag;

_UNKNOWN g_CAviDecompressor_DtorArrayTag;

_UNKNOWN g_AviExceptionMessage_EHFrame;

_UNKNOWN g_AviStreamRectDrawBegin_EHFrame;

_UNKNOWN g_AviOpenFileDecodeThread_EHFrame;

_UNKNOWN g_AviOpenVideoCodec_EHFrame;

_UNKNOWN g_AviBeginPlayback_EHFrame;

_UNKNOWN g_AviPlayerFlip_EHFrame;

_UNKNOWN g_AviUpdatePos_EHFrame;

_UNKNOWN g_AviPresentFrameForRect_EHFrame;

_UNKNOWN g_AviApplyOpenOptions_EHFrame;

_UNKNOWN g_AviPlayerCreateBackSurface_EHScopeTable;

_UNKNOWN g_AviPlayerCreatePalette_EHScopeTable;

int (*g_AviException_VTable[2])() = { &AviException_ScalarDeletingDtor, &AviException_GetMessage };

_UNKNOWN g_AviException_DtorArrayDescriptor;

int (*g_CSSFileStream_VTable[12])() =
{
  &CSS_FileStream_Read,
  &CSS_FileStream_IsFinished,
  &CSS_FileStream_QueryDone,
  &CSS_FileStream_SetLoopRange,
  &CSS_FileStream_GetLoopRange,
  &CSS_FileStream_ClearLoop,
  &CSS_FileStream_GetSourceBytesFetched,
  &CSS_FileStream_DispatchIfInRange,
  &CSS_FileStream_RefillBuffer,
  &CSS_FileStream_PreloadFully,
  &ExcString_GetErrorCodeStub,
  &CSS_FileStream_Destroy
};

_UNKNOWN g_CSSFileStream_DtorArrayDescriptor;

_UNKNOWN g_CSSCloseChannel_EHScopeTable;

_UNKNOWN g_CSSServiceStreamingChannels_EHScopeTable;

_UNKNOWN g_CSSPauseStreamReading_EHScopeTable;

_UNKNOWN g_CSSEmptySampleCache_EHScopeTable;

_UNKNOWN g_CSSStopSound_EHScopeTable;

_UNKNOWN g_CSSSetSoundPos_EHScopeTable;

_UNKNOWN g_CSSShutdownVoicePool_EHScopeTable;

_UNKNOWN g_CompatStringHolder_DtorArrayDescriptor;

int (*g_Surface_BlitFunctionTable[3])() = { &Surface_BltOntoSurface, &Surface_BltFastOpaqueTo, &Surface_BltFastKeyedTo };

int (*g_FileSystemMountTable_VTable[13])() =
{
  &Compat_FileSystemForEachMountInvokeSlot0,
  &Compat_FileSystemCloseQuery,
  &FileSystem_DestructMountTable,
  &Compat_FileSystemForEachMountPrintSearchResult,
  &Compat_FileSystemForEachMountInvokeSlot16,
  &Compat_FileSystemQueryRelease,
  &Compat_FileSystemForEachMountInvokeSlot24,
  &Compat_FileSystemForEachMountInvokeSlot28,
  &Compat_FileSystemForEachMountInvokeSlot32,
  &FileSystem_ResolveRelativeToCurrentDir,
  &Compat_FileSystemReleaseMountedPaths,
  &FileSystem_OpenViaOpenSlotAndNotify,
  &Compat_FileSystemForEachMountInvokeCallback
};

int (*g_CompatFileStream_VTable[9])() =
{
  &Compat_FileStreamSeekFromStart,
  &Compat_FileStreamTell,
  &Compat_FileStreamSeekFromEnd,
  &Compat_FileStreamRelease,
  &Compat_FileStreamIsReady,
  &Compat_FileStreamRead,
  &Compat_FileStreamWrite,
  &Compat_FileStreamReadChar,
  &Compat_FileStreamUngetChar
};

int (*g_CompatFileFinder_VTable[6])() = { &Compat_FileFinderGetName, &Compat_FileFinderGetAttributes, &Compat_FileFinderGetSize, &Compat_FileFinderHasEntry, &Compat_FileFinderAdvance, &Compat_FileFinderRelease };

int (*g_FileSystemDiskMount_VTable[4])() = { &Compat_FileFinderCreate, &Compat_FileSystemCloseQuery, &FileSystem_DiskMountScalarDeletingDtor, &Compat_FileSystemOpenIfReady };

_UNKNOWN g_CompatFileStream_DtorArrayDescriptor;

_UNKNOWN g_CompatFileFinder_DtorArrayDescriptor;

_UNKNOWN g_FileSystemDiskMount_DtorArrayDescriptor;

_UNKNOWN g_FileSystemDiskMountVariant_DtorArrayDescriptor;

int (*g_FileCacheNode_VTable[6])() = { &File_CacheNodeGetTag, &File_CacheNodeGetEntrySize, &File_CacheNodeGetChildTag, &File_CacheNodeCheckChildHeight, &File_CacheNodeRebalance, &File_CacheNodeScalarDtor };

int (*g_FileSource_VTable[4])() = { &File_CacheNodeNewValidated, &Compat_FileSystemCloseQuery, &File_SourceScalarDtor, &Compat_FileSystemOpenIfReady };

int (*g_FileArchiveEntryStream_VTable[10])() =
{
  &Compat_QuerySkipBytes,
  &Compat_QueryGetLength,
  &Compat_QuerySkipBytesFromBase,
  &Compat_QueryDestruct,
  &FileSystem_ArchiveStreamHasRemainingData,
  &FileSystem_ArchiveStreamReadBytes,
  &FileSystem_ArchiveStreamNoOpFlush,
  &FileSystem_ArchiveStreamReadByte,
  &Res_StreamPutBackDecodedByte,
  &Res_StreamSeekClamped
};

int (*g_FileDirNode_VTable[4])() = { &Compat_QuerySkipBytes, &Compat_QueryGetLength, &Compat_QuerySkipBytesFromBase, &File_DirNodeScalarDtor };

int (*g_FileSystemArchiveEntryStream_VTable[10])() =
{
  &Compat_QuerySkipBytes,
  &Compat_QueryGetLength,
  &Compat_QuerySkipBytesFromBase,
  &Noop_FatalQueryStreamDestruct,
  &Compat_TriggerFatalRuntimeErrorOnce,
  &Compat_TriggerFatalRuntimeErrorOnce,
  &Compat_TriggerFatalRuntimeErrorOnce,
  &Compat_TriggerFatalRuntimeErrorOnce,
  &Noop_FatalQueryStreamPutBackByte,
  &Res_StreamSeekClamped
};

int (*g_FileReadOnlySource_VTable[4])() = { &File_CacheNodeNewValidated, &Compat_FileSystemCloseQuery, &Compat_QueryCloseAndDestruct, &Compat_FileSystemOpenIfReady };

_UNKNOWN g_FileSystemArchiveRecordCache_CtorArrayDescriptor;

_UNKNOWN g_FileDirNode_DtorArrayDescriptor;

_UNKNOWN g_FileCacheNode_DtorArrayDescriptor;

_UNKNOWN g_FileSource_DtorArrayDescriptor;

_UNKNOWN g_CompatQuery_DtorArrayDescriptor;

_UNKNOWN g_CompatQueryCloseAndDestruct_DtorArrayDescriptor;

_UNKNOWN g_CRTWatcomEHHandleNestedException_ScopeTable;

_UNKNOWN g_CRTWatcomEHFrameHandler_ScopeTable;

_DWORD (__cdecl *g_BadException_VTable)(bad_exception *this) = &bad_exception_dtor;

int (*g_IOStreambuf_VTable[4])() = { &IO_StreambufAllocDerived, &Compat_FileSystemCloseQuery, &Rules_ConstructHandleVectorDtor, &Compat_FileSystemOpenIfReady };

int (*g_FuncTable_511094[6])() =
{
  &Rules_Builtin_1,
  &Rules_Builtin_2,
  &Rules_Builtin_3,
  &Rules_Builtin_0,
  &Noop_RulesRecordScalarDeletingDtor,
  &Rules_ConstructRecordVectorDtor
};

_UNKNOWN g_RulesHandleVector_DtorArrayDescriptor;

_UNKNOWN g_RulesRecordArrayDtorSlot;

int g_CRT_NonLeapMonthDayTable = 0;

int g_CRT_NonLeapFebMarDayThreshold = 3866655;

int g_CRT_LeapMonthDayTable = 365;

char g_LanguageIndex = '\x01';

int g_SdlTransitionAnimSkipRequested = 1;

_UNKNOWN g_CDPathTemplate;

_UNKNOWN *g_RenderDevice = &g_RenderDeviceStorage;

char (*g_BuildingTransferTargetListSurfaceBuffer)[1024] = &g_PaletteScratchSurfaceBuffer;

char aGfx_7[5] = "gfx\\";

char aGfx_0[5] = "gfx\\";

char aGfx_8[5] = "gfx\\";

char aGfx_1[5] = "gfx\\";

char aGfx_4[5] = "gfx\\";

char aGfx[5] = "gfx\\";

char aGfx_2[5] = "gfx\\";

char aGfx_3[5] = "gfx\\";

char *g_Text_LowMorale[3] =
{
  "Oddzial odmawia wykonania rozkaz\xA2w",
  "Low morale, unit denies taking orders",
  "Schlechte Moral"
};

char *g_Text_QuitConfirm[3] =
{
  "Czy chcesz zako\xA4""czy\x8D rozgrywk\x91?",
  "Do you want to quit the game?",
  "M\x94""chtest Du das Spiel verlassen?"
};

int g_UnitSearchCursor = -1;

int g_SelectedUnitIndex = -1;

int g_LastSelectedUnitIndex = -1;

int g_PendingLoadGameSlotIndex = -1;

__int16 g_WorldMapAmbientAnimFramesSetA[7] = { 0x30B, 0x313, 0x31B, 0x321, 0x327, 0x32E, 0x32E };

__int16 g_WorldMapAmbientAnimFramesSetB[2] = { 0x30B, 0x315 };

__int16 g_WorldMapAmbientAnimFramesSetC[5] = { 0x30B, 0x313, 0x31D, 0x323, 0x32A };

char aSwijtynia[] = "\x98wi\x86tynia";

char aShrine[] = "Shrine";

char aSchrein[] = "Schrein";

char aPustaSwijtynia[] = "Pusta \x98wi\x86tynia";

char aEmptyShrine[] = "Empty shrine";

char aLeererSchrein[] = "Leerer Schrein";

char aMiejsceKultu[] = "Miejsce kultu";

char aCultPlace[] = "Cult place";

char aKultstdtte[] = "Kultst\x84""tte";

char aPusteMiejsceKu[] = "Puste miejsce kultu";

char aEmptyCultPlace[] = "Empty cult place";

char aLeereKultstdtt[] = "Leere Kultst\x84""tte";

char aFundamenty[] = "Fundamenty";

char aFoundations[] = "Foundations";

char aFundamente[] = "Fundamente";

char aZakopanySkarb[] = "Zakopany skarb";

char aHiddenTreasure[] = "Hidden treasure";

char aVersteckterSch[] = "Versteckter Schatz";

char aTerenNieodkryt[17] = "Teren nieodkryty";

char aUnexploredTerr[19] = "Unexplored terrain";

char aUnerforschtesT[22] = "Unerforschtes Terrain";

char aDroga3pa[12] = "Droga - 3pa";

char aRoad3ap[11] = "Road - 3ap";

char aStrase[7] = "Stra\xE1""e";

char aLas6pa[10] = "Las - 6pa";

char aForest6ap[13] = "Forest - 6ap";

char aBaum[5] = "Baum";

char aRvwnina4pa[14] = "R\xA2wnina - 4pa";

char aPlain4ap[12] = "Plain - 4ap";

char aEbene[6] = "Ebene";

char aPustynia5pa[15] = "Pustynia - 5pa";

char aDesert5ap[13] = "Desert - 5ap";

char aWbste[6] = "W\x81""ste";

char aBagno7pa[12] = "Bagno - 7pa";

char aSwamp7ap[12] = "Swamp - 7ap";

char aSumpf[6] = "Sumpf";

char aGvryNiskie8pa[18] = "G\xA2ry niskie - 8pa";

char aHills8ap[12] = "Hills - 8ap";

char aHbgel[6] = "H\x81""gel";

char aGvryWysokie[13] = "G\xA2ry wysokie";

char aMountains[10] = "Mountains";

char aBerge[6] = "Berge";

char aWoda[5] = "Woda";

char aWater[6] = "Water";

char aWasser[7] = "Wasser";

char aBlad[5] = "Blad";

char aError[6] = "Error";

char aError_0[6] = "Error";

char *g_ShrineTexts[21] = { aSwijtynia, aShrine, aSchrein };

char *g_EmptyShrineTexts[18] = { aPustaSwijtynia, aEmptyShrine, aLeererSchrein };

char *g_CultPlaceTexts[15] = { aMiejsceKultu, aCultPlace, aKultstdtte };

char *g_EmptyCultPlaceTexts[12] = { aPusteMiejsceKu, aEmptyCultPlace, aLeereKultstdtt };

char *g_CastleFoundationTexts[9] = { aFundamenty, aFoundations, aFundamente };

char *g_HiddenTreasureTexts[6] = { aZakopanySkarb, aHiddenTreasure, aVersteckterSch };

char *g_Text_SurrenderConfirm[3] =
{
  "Czy chcesz si\x91 podda\x8D?",
  "Do you want to surrender?",
  "M\x94""chtest Du Dich ergeben?"
};

int g_UI_YesNoDims[3] = { 416, 400, 1 };

char *g_Text_NoBuilder[3] =
{
  "Brak budowniczego w oddziale!",
  "There's no builder in the army!",
  "Es befindet sich kein Pionier in der Armee."
};

_BYTE g_WorldMapActionButtonWidgetTable[WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * (WORLD_MAP_ACTION_WIDGET_COUNT + 1)] __attribute__((aligned(4)));

CLASH95_INTERNAL int g_WorldMapActionWidgetsInitialized;

int g_UITextCursorGlyphIndex = -1;

CLASH95_INTERNAL TextSpriteResourceSlotRecord g_TextSpriteResourceSlots[] =
{
  TEXT_SPRITE_RESOURCE_SLOT("system", 10, 1),
  TEXT_SPRITE_RESOURCE_SLOT("normal", 20, 1),
  TEXT_SPRITE_RESOURCE_SLOT("turn", 20, 1),
  TEXT_SPRITE_RESOURCE_SLOT("info", 10, 1),
  TEXT_SPRITE_RESOURCE_SLOT("zamek1", 10, 1),
  TEXT_SPRITE_RESOURCE_SLOT("zamek2", 10, 1),
  TEXT_SPRITE_RESOURCE_SLOT("turn2", 10, 1),
  TEXT_SPRITE_RESOURCE_SLOT("gothic_s", 13, 1),
  TEXT_SPRITE_RESOURCE_SLOT("gothic_l", 40, 1),
  TEXT_SPRITE_RESOURCE_SLOT("zamek3", 10, 1),
  TEXT_SPRITE_RESOURCE_SLOT("message", 16, 1),
  TEXT_SPRITE_RESOURCE_SLOT("red", 16, 1),
  TEXT_SPRITE_RESOURCE_SLOT("zamek2r", 10, 1),
  TEXT_SPRITE_RESOURCE_SLOT("goth_s_r", 13, 1),
  TEXT_SPRITE_RESOURCE_SLOT("bat_info", 13, 1),
  TEXT_SPRITE_RESOURCE_SLOT("bat_inf2", 13, 1),
  TEXT_SPRITE_RESOURCE_SLOT("zamek4", 13, 1),
  TEXT_SPRITE_RESOURCE_SLOT("bud_info", 20, 1),
  TEXT_SPRITE_RESOURCE_SLOT("lazur1", 13, 0),
  TEXT_SPRITE_RESOURCE_SLOT("menu", 13, 1),
  TEXT_SPRITE_RESOURCE_SLOT("zamek5", 13, 1),
  TEXT_SPRITE_RESOURCE_SLOT("lazur2", 13, 0),
  TEXT_SPRITE_RESOURCE_SLOT("big", 13, 1),
  { 0, 0, 0, 0 }
};

int g_MiniMapDrawMask = 7;

char g_MiniMapBuildingOwnerColorTable[] = { '\xF8' };

__int16 g_WorldMapTopMenuHitLeft0[] = { 30 };

__int16 g_WorldMapTopMenuHitTop0[] = { 1 };

__int16 g_WorldMapTopMenuHitRight0[] = { 121 };

__int16 g_WorldMapTopMenuHitBottom0[] = { 25 };

unsigned char g_WorldMapTopMenuHitTargetA = 0x14;

void *g_WorldMapTopMenuHitMenuPtr0 = &g_WorldMapTopMenuHitTargetA;

unsigned char g_WorldMapTopMenuHitTargetB = 0x74;

CLASH95_INTERNAL const WorldMapTopMenuHitRecord g_WorldMapTopMenuHitRecords[] =
{
  { 30, 1, 121, 25, (_WORD *)&g_WorldMapTopMenuHitTargetA },
  { 126, 1, 218, 25, (_WORD *)&g_WorldMapTopMenuHitTargetB }
};

int g_ActiveUnitMoveTileIndex = -1;

int g_UnitBattleAnimFrameCount = 8;

char *g_Text_UnitDisbandedLowMoraleMessages[3] =
{
  "Jedna z twoich jednostek uleg\x92""a rozwi\x86zaniu, Panie. Nie chcieli Ci dalej s\x92u\xA7y\x8D, gdy\xA7 wiele przegranych bitew i og\xA2lne wyczerpanie drastycznie wp\x92yn\x91\x92o na ich morale.",
  "One of your troops fell apart. They did not want to serve you anymore, their morale was very low after many lost battles and many dead.",
  "Eine Deiner Einheiten hat sich aufgel\x94st. Die M\x84nner wollten Dir nicht l\x84nger dienen, weil die vielen verlorenen Schlachten und die allgemeine Ersch\x94pfung drastisch ihre Moral untergraben haben."
};

char *g_UnitTypeMetadataRecordsStorage[102] =
{
  "Posp. ruszenie",
  "Peasant",
  "Bauern",
  0
};

char *(*g_UnitTypeMetadataRecords)[102] = &g_UnitTypeMetadataRecordsStorage;

CLASH95_INTERNAL char *g_RecoveredUnitTypeEnglishNames[UNIT_TYPE_COUNT] =
{
  "Peasant",
  "Light infantry",
  "Heavy infantry",
  "Pikeman",
  "Heavy spearman",
  "Light cavalry",
  "Heavy cavalry",
  "Knights",
  "Dragon cavalry",
  "Archer",
  "Crossbower",
  "Musketeer",
  "Catapult",
  "Ram",
  "Cannon",
  "Forester",
  "Goral",
  "Builder",
  "Worm",
  "Elephant",
  "Cyclop",
  "Troll",
  "Scorpion",
  "Skeleton",
  "Wizard",
  "Ghost",
  "Eagle",
  "Pegasus",
  "Winger",
  "Fly",
  "Dragon",
  "Gold",
  "Peasants",
  "Tactician",
  "Tactician"
};

char *g_UnitTypeResourceKeys = "peon";

CLASH95_INTERNAL const UnitTypeRuntimeCoreMetadataRecord g_UnitTypeRuntimeCoreMetadata[UNIT_TYPE_COUNT] =
{
  [0] = { 0x005123CC, 0x004ED917, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000000, 1, 1, 24, 0, 0, 0, 1, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [1] = { 0x005123F0, 0x004ED92B, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000000, 5, 4, 20, 0, 0, 0, 5, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [2] = { 0x005123FC, 0x004ED93C, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000000, 9, 6, 20, 0, 0, 0, 9, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [3] = { 0x00512438, 0x004ED94F, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000000, 3, 5, 24, 0, 0, 0, 4, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [4] = { 0x0051242C, 0x004ED960, 3, 3, 10, { 0, 0, 0, 0 }, 0, 16, 8, 0x00000000, 5, 5, 22, 0, 0, 0, 7, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [5] = { 0x0051248C, 0x004ED973, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000000, 8, 5, 36, 0, 0, 0, 8, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [6] = { 0x00512498, 0x004ED983, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000000, 14, 8, 32, 0, 0, 0, 14, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [7] = { 0x005124A4, 0x004ED995, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000000, 12, 7, 30, 0, 0, 0, 12, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [8] = { 0x005124B0, 0x004ED9A6, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000000, 10, 4, 32, 6, 3, 0, 10, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [9] = { 0x005123D8, 0x004ED9B6, 3, 3, 10, { 0, 0, 0, 0 }, 0, 10, 8, 0x00000000, 3, 1, 24, 6, 3, 0, 5, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [10] = { 0x00512414, 0x004ED9C7, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000000, 5, 2, 20, 8, 4, 0, 6, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [11] = { 0x00512420, 0x004ED9DB, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000000, 4, 3, 24, 11, 4, 0, 4, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [12] = { 0x00512408, 0x004ED9EF, 2, 4, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000000, 0, 1, 20, 16, 5, 1, 0, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [13] = { 0x00512468, 0x004ED9FB, 2, 4, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000000, 1, 10, 20, 0, 0, 0, 80, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [14] = { 0x00512444, 0x004EDA07, 2, 4, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000000, 0, 1, 16, 20, 6, 2, 0, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [15] = { 0x00512450, 0x004EDA14, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 28, 0x00000000, 8, 4, 24, 11, 3, 0, 8, 3, { 4, 4, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [16] = { 0x005123E4, 0x004EDA25, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000000, 8, 6, 26, 0, 0, 0, 8, 3, { 4, 6, 5, 0, 7, 0, 6, 0 }, { 0 } },
  [17] = { 0x0051245C, 0x004EDA39, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000000, 1, 1, 26, 0, 0, 0, 1, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [18] = { 0x005124BC, 0x004EDA4B, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000002, 14, 9, 18, 0, 0, 0, 12, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [19] = { 0x005124C8, 0x004EDA5E, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000002, 14, 10, 20, 0, 0, 0, 14, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [20] = { 0x005124D4, 0x004EDA70, 3, 3, 10, { 0, 0, 0, 0 }, 0, 10, 8, 0x00000002, 10, 6, 26, 10, 3, 0, 8, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [21] = { 0x005124E0, 0x004EDA83, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000002, 13, 10, 22, 0, 0, 0, 13, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [22] = { 0x005124EC, 0x004EDA96, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000002, 12, 8, 26, 0, 0, 0, 12, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [23] = { 0x005124F8, 0x004EDAAA, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000002, 13, 10, 22, 0, 0, 0, 13, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [24] = { 0x00512504, 0x004EDABA, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000002, 10, 10, 40, 15, 6, 0, 10, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [25] = { 0x00512510, 0x004EDACD, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000002, 10, 8, 24, 0, 0, 0, 10, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [26] = { 0x0051251C, 0x004EDAE1, 6, 4, 10, { 1, 0, 0, 0 }, 0, 8, 8, 0x00000003, 9, 6, 34, 0, 0, 0, 9, 3, { 3, 3, 3, 3, 3, 3, 3, 3 }, { 0 } },
  [27] = { 0x00512474, 0x004EDAF6, 8, 4, 10, { 1, 0, 0, 0 }, 18, 8, 8, 0x00000003, 12, 8, 30, 0, 0, 0, 12, 3, { 3, 3, 3, 3, 3, 3, 3, 3 }, { 0 } },
  [28] = { 0x00512528, 0x004EDB0B, 6, 4, 10, { 1, 0, 0, 0 }, 0, 8, 8, 0x00000003, 14, 10, 24, 10, 4, 0, 14, 3, { 3, 3, 3, 3, 3, 3, 3, 3 }, { 0 } },
  [29] = { 0x00512534, 0x004EDB21, 2, 1, 1, { 1, 0, 0, 0 }, 0, 16, 16, 0x00000003, 8, 5, 32, 0, 0, 0, 8, 3, { 3, 3, 3, 3, 3, 3, 3, 3 }, { 0 } },
  [30] = { 0x00512480, 0x004EDB36, 6, 4, 10, { 1, 0, 0, 0 }, 28, 16, 16, 0x00000003, 18, 15, 36, 15, 4, 0, 18, 3, { 3, 3, 3, 3, 3, 3, 3, 3 }, { 0 } },
  [31] = { 0x00512540, 0x004EDB49, 4, 4, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000000, 0, 0, 30, 0, 0, 0, 0, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [32] = { 0x0051254C, 0x004EDB5A, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000000, 0, 2, 30, 0, 0, 0, 0, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [33] = { 0x00512558, 0x004EDB6E, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000000, 0, 2, 36, 0, 0, 0, 0, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } },
  [34] = { 0x00512558, 0x004EDB7F, 3, 3, 10, { 0, 0, 0, 0 }, 0, 8, 8, 0x00000000, 0, 2, 36, 0, 0, 0, 0, 3, { 4, 6, 5, 0, 7, 0, 8, 0 }, { 0 } }
};

CLASH95_INTERNAL const unsigned char g_UnitTypeWorldMoveCosts[35][9] = {
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 4, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 6, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 3, 3, 3, 3, 3, 3, 3, 3 },
  { 3, 3, 3, 3, 3, 3, 3, 3, 3 },
  { 3, 3, 3, 3, 3, 3, 3, 3, 3 },
  { 3, 3, 3, 3, 3, 3, 3, 3, 3 },
  { 3, 3, 3, 3, 3, 3, 3, 3, 3 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 },
  { 3, 4, 6, 5, 0, 7, 0, 8, 0 }
};

char g_UnitTypeVisionRadius[] = { '\x03' };

char g_UnitTypeProductionTime[] = { '\x01' };

char g_UnitTypeProductionCost[] = { '\x02' };

__int16 g_UnitTypeProductionLicenceCost[] = { 0 };

char g_UnitTypeProductionRequiredTechLevelMode2[] = { '\x01' };

char g_UnitTypeProductionRequiredTechLevelOtherModes[] = { '\x01' };

char g_UnitTypeRole[] = { '\0' };

char g_UnitTypeCorpseSpriteBaseIndex[] = { '\0' };

char g_UnitTypeAttackSoundFrameIndex[] = { '\x03' };

char g_UnitTypeShotSoundFrameIndex[] = { '\0' };

char *g_UnitMoveSoundStems = "b_lekkie\\krokb";

char g_UnitMoveSoundVariantCounts[] = { '\x04' };

char g_UnitMoveSoundBaseVolumes[] = { '\n' };

char g_BuilderConstructionProgressPerTurn = '\x1A';

char *g_LanguageDirectoryNames[3] = { "pol\\", "eng\\", "ger\\" };

int Map_NeighborDX[64] =
{
  0,
  -1,
  1,
  -1,
  1,
  0,
  1,
  1,
  0,
  1,
  -1,
  1,
  -1,
  0,
  -1,
  -1,
  -1,
  -1,
  0,
  -1,
  1,
  -1,
  0,
  -1,
  1,
  -1,
  1,
  0,
  1,
  -1,
  1,
  0,
  1,
  1,
  1,
  0,
  1,
  1,
  0,
  1,
  1,
  1,
  0,
  1,
  -1,
  1,
  0,
  1,
  -1,
  1,
  -1,
  0,
  -1,
  1,
  -1,
  0,
  -1,
  -1,
  -1,
  0,
  -1,
  -1,
  0,
  -1
};

int Map_NeighborDY[63] =
{
  -1,
  1,
  -1,
  1,
  0,
  1,
  1,
  0,
  1,
  -1,
  1,
  -1,
  0,
  -1,
  -1,
  -1,
  -1,
  0,
  -1,
  1,
  -1,
  0,
  -1,
  1,
  -1,
  1,
  0,
  1,
  -1,
  1,
  0,
  1,
  1,
  1,
  0,
  1,
  1,
  0,
  1,
  1,
  1,
  0,
  1,
  -1,
  1,
  0,
  1,
  -1,
  1,
  -1,
  0,
  -1,
  1,
  -1,
  0,
  -1,
  -1,
  -1,
  0,
  -1,
  -1,
  0,
  -1
};

int g_MathSinTableQ16[363] =
{
  0,
  1143,
  2287,
  3429,
  4571,
  5711,
  6850,
  7986,
  9120,
  10252,
  11380,
  12504,
  13625,
  14742,
  15854,
  16961,
  18064,
  19160,
  20251,
  21336,
  22414,
  23486,
  24550,
  25606,
  26655,
  27696,
  28729,
  29752,
  30767,
  31772,
  32767,
  33753,
  34728,
  35693,
  36647,
  37589,
  38521,
  39440,
  40347,
  41243,
  42125,
  42995,
  43852,
  44695,
  45525,
  46340,
  47142,
  47929,
  48702,
  49460,
  50203,
  50931,
  51643,
  52339,
  53019,
  53683,
  54331,
  54963,
  55577,
  56175,
  56755,
  57319,
  57864,
  58393,
  58903,
  59395,
  59870,
  60326,
  60763,
  61183,
  61583,
  61965,
  62328,
  62672,
  62997,
  63302,
  63589,
  63856,
  64103,
  64331,
  64540,
  64729,
  64898,
  65047,
  65176,
  65286,
  65376,
  65446,
  65496,
  65526,
  65536,
  65526,
  65496,
  65446,
  65376,
  65286,
  65176,
  65047,
  64898,
  64729,
  64540,
  64331,
  64103,
  63856,
  63589,
  63302,
  62997,
  62672,
  62328,
  61965,
  61583,
  61183,
  60763,
  60326,
  59870,
  59395,
  58903,
  58393,
  57864,
  57319,
  56755,
  56175,
  55577,
  54963,
  54331,
  53683,
  53019,
  52339,
  51643,
  50931,
  50203,
  49460,
  48702,
  47929,
  47142,
  46340,
  45525,
  44695,
  43852,
  42995,
  42125,
  41243,
  40347,
  39440,
  38521,
  37589,
  36647,
  35693,
  34728,
  33753,
  32767,
  31772,
  30767,
  29752,
  28729,
  27696,
  26655,
  25606,
  24550,
  23486,
  22414,
  21336,
  20251,
  19160,
  18064,
  16961,
  15854,
  14742,
  13625,
  12504,
  11380,
  10252,
  9120,
  7986,
  6850,
  5711,
  4571,
  3429,
  2287,
  1143,
  0,
  -1143,
  -2287,
  -3429,
  -4571,
  -5711,
  -6850,
  -7986,
  -9120,
  -10252,
  -11380,
  -12504,
  -13625,
  -14742,
  -15854,
  -16961,
  -18064,
  -19160,
  -20251,
  -21336,
  -22414,
  -23486,
  -24550,
  -25606,
  -26655,
  -27696,
  -28729,
  -29752,
  -30767,
  -31772,
  -32767,
  -33753,
  -34728,
  -35693,
  -36647,
  -37589,
  -38521,
  -39440,
  -40347,
  -41243,
  -42125,
  -42995,
  -43852,
  -44695,
  -45525,
  -46340,
  -47142,
  -47929,
  -48702,
  -49460,
  -50203,
  -50931,
  -51643,
  -52339,
  -53019,
  -53683,
  -54331,
  -54963,
  -55577,
  -56175,
  -56755,
  -57319,
  -57864,
  -58393,
  -58903,
  -59395,
  -59870,
  -60326,
  -60763,
  -61183,
  -61583,
  -61965,
  -62328,
  -62672,
  -62997,
  -63302,
  -63589,
  -63856,
  -64103,
  -64331,
  -64540,
  -64729,
  -64898,
  -65047,
  -65176,
  -65286,
  -65376,
  -65446,
  -65496,
  -65526,
  -65536,
  -65526,
  -65496,
  -65446,
  -65376,
  -65286,
  -65176,
  -65047,
  -64898,
  -64729,
  -64540,
  -64331,
  -64103,
  -63856,
  -63589,
  -63302,
  -62997,
  -62672,
  -62328,
  -61965,
  -61583,
  -61183,
  -60763,
  -60326,
  -59870,
  -59395,
  -58903,
  -58393,
  -57864,
  -57319,
  -56755,
  -56175,
  -55577,
  -54963,
  -54331,
  -53683,
  -53019,
  -52339,
  -51643,
  -50931,
  -50203,
  -49460,
  -48702,
  -47929,
  -47142,
  -46340,
  -45525,
  -44695,
  -43852,
  -42995,
  -42125,
  -41243,
  -40347,
  -39440,
  -38521,
  -37589,
  -36647,
  -35693,
  -34728,
  -33753,
  -32768,
  -31772,
  -30767,
  -29752,
  -28729,
  -27696,
  -26655,
  -25606,
  -24550,
  -23486,
  -22414,
  -21336,
  -20251,
  -19160,
  -18064,
  -16961,
  -15854,
  -14742,
  -13625,
  -12504,
  -11380,
  -10252,
  -9120,
  -7986,
  -6850,
  -5711,
  -4571,
  -3429,
  -2287,
  -1143,
  0,
  0,
  0
};

char g_BuildingFlagYOffsets[19] =
{
  'L',
  '<',
  '\x1B',
  '>',
  ' ',
  'A',
  '\x13',
  'A',
  '\x17',
  '!',
  '\x04',
  '!',
  '\f',
  '!',
  '\x04',
  '#',
  '\v',
  ' ',
  '\0'
};

int g_WorldMapAttentionFlashUnitIndex = -1;

int g_UnitBlinkFlashUnitIndex = -1;

int battleLogEnabled = 1;

char *g_LeadTroopsPersonallyPromptTexts[3] =
{
  "Czy chcesz osobi\x9E""cie poprowadzi\x8D wojska?",
  "Do you want to lead the troops on your own?",
  "M\x94""chtest Du allein Deine Truppen anf\x81hren?"
};

int g_BuildingSpawnTileSearchOffsetsX[] = { 1 };

int g_BuildingSpawnTileSearchOffsetsY[23] = { 2, 0, 2, 2, 2, -1, 2, 2, 1, -1, 1, 2, 0, -1, 0, 2, -1, -1, -1, 1, -1, 0, -1 };

__int16 g_BuildingTypeMaxHitPoints[4] = { 100, 300, 300, 0 };

__int16 g_WallKindDefenseFactor[5] = { 427, 0, 341, 261, 256 };

char g_BuildingUpgradeDurationByLevel[5] = { '\x05', '\x01', '\0', '\x01', '\n' };

char g_BuildingUpgradeCostByLevel[5] = { '\x01', '\0', '\x01', '\n', '\x01' };

char *g_BuildingRandomNamePool[50] =
{
  "cantown",
  "kenstone",
  "girock",
  "ghih up",
  "histone",
  "don o ku",
  "ghondur",
  "fhur tao",
  "drakefly",
  "stormus",
  "dark town",
  "stone ring",
  "werneom",
  "guluali",
  "bokumia",
  "katha gha",
  "treg rock",
  "bodeon",
  "roahria",
  "dirt town",
  "stone bell",
  "bhua rock",
  "dragmounth",
  "canoowar",
  "thubeos",
  "defambrion",
  "gorendberg",
  "ghettan",
  "akserion",
  "totaweon",
  "bhudu",
  "leweburg",
  "black ring",
  "hopenberg",
  "timbran",
  "moon town",
  "gate stone",
  "trungeon",
  "imirdoor",
  "gatgally",
  "jolarion",
  "weghetown",
  "sarturia",
  "fraggmeon",
  "eufurhon",
  "loopenburg",
  "jereho",
  "henrion",
  "Stra\xA7nica",
  "Keep"
};

char *UI_Locale_BuildingNames_A[2] = { "Stra\xA7nica", "Keep" };

char *UI_Locale_BuildingNames_B[12] =
{
  "Twoi budowniczy wci\x86\xA7 ci\x91\xA7ko",
  "Your builders work hard",
  "Herr, Deine Baumeister",
  "pracuj\x86 nad wznoszeniem",
  "building",
  "arbeiten hart,",
  "%s, Panie.",
  "%s, Master.",
  "%s",
  "wie\xA7y",
  "a keep",
  "um Deine Turm zu bauen"
};

char *UI_Locale_BuildingNames_C[9] =
{
  "pracuj\x86 nad wznoszeniem",
  "building",
  "arbeiten hart,",
  "%s, Panie.",
  "%s, Master.",
  "%s",
  "wie\xA7y",
  "a keep",
  "um Deine Turm zu bauen"
};

char *UI_Locale_BuildingNames_D[6] =
{
  "%s, Panie.",
  "%s, Master.",
  "%s",
  "wie\xA7y",
  "a keep",
  "um Deine Turm zu bauen"
};

char *UI_Locale_BuildingNames_E[3] = { "wie\xA7y", "a keep", "um Deine Turm zu bauen" };

char *UI_Locale_BuildingNames_F[9] =
{
  "Pozosta\x92""a jeszcze %d tura.",
  "%d turn remaining.",
  "Sie ben\x94tigen %d Z\x81ge.",
  "Pozosta\x92y jeszcze %d tury.",
  "%d turns remaining.",
  "Sie ben\x94tigen %d Z\x81ge.",
  "Pozosta\x92o jeszcze %d tur.",
  "%d turns remaining.",
  "Sie ben\x94tigen %d Z\x81ge."
};

char *UI_Locale_BuildingNames_G[6] =
{
  "Pozosta\x92y jeszcze %d tury.",
  "%d turns remaining.",
  "Sie ben\x94tigen %d Z\x81ge.",
  "Pozosta\x92o jeszcze %d tur.",
  "%d turns remaining.",
  "Sie ben\x94tigen %d Z\x81ge."
};

char *UI_Locale_BuildingNames_H[3] =
{
  "Pozosta\x92o jeszcze %d tur.",
  "%d turns remaining.",
  "Sie ben\x94tigen %d Z\x81ge."
};

char *g_CastleBuildingIconTooltipNames[27] =
{
  "Dw\xA2r",
  "Court",
  "Hof",
  "Wieza",
  "Tower",
  "Turm",
  "Szpital",
  "Hospital",
  "Krankenhaus",
  "Koszary",
  "Barracks",
  "Kaserne",
  "Warsztat",
  "Workshop",
  "Werkstatt",
  "Szko\x92""a",
  "School",
  "Schule",
  "Ku\xA6nia",
  "Smiths shop",
  "Schmiede",
  "Ch\x92opi",
  "Peasants",
  "Bauern",
  "Baraki",
  "Barracks",
  "Kaserne"
};

char *UI_Locale_BuildingNames_I[26] =
{
  "Court",
  "Hof",
  "Wieza",
  "Tower",
  "Turm",
  "Szpital",
  "Hospital",
  "Krankenhaus",
  "Koszary",
  "Barracks",
  "Kaserne",
  "Warsztat",
  "Workshop",
  "Werkstatt",
  "Szko\x92""a",
  "School",
  "Schule",
  "Ku\xA6nia",
  "Smiths shop",
  "Schmiede",
  "Ch\x92opi",
  "Peasants",
  "Bauern",
  "Baraki",
  "Barracks",
  "Kaserne"
};

char *UI_Locale_BuildingNames_J[21] =
{
  "Szpital",
  "Hospital",
  "Krankenhaus",
  "Koszary",
  "Barracks",
  "Kaserne",
  "Warsztat",
  "Workshop",
  "Werkstatt",
  "Szko\x92""a",
  "School",
  "Schule",
  "Ku\xA6nia",
  "Smiths shop",
  "Schmiede",
  "Ch\x92opi",
  "Peasants",
  "Bauern",
  "Baraki",
  "Barracks",
  "Kaserne"
};

char *UI_Locale_BuildingNames_K[15] =
{
  "Warsztat",
  "Workshop",
  "Werkstatt",
  "Szko\x92""a",
  "School",
  "Schule",
  "Ku\xA6nia",
  "Smiths shop",
  "Schmiede",
  "Ch\x92opi",
  "Peasants",
  "Bauern",
  "Baraki",
  "Barracks",
  "Kaserne"
};

char *UI_Locale_BuildingNames_L[12] =
{
  "Szko\x92""a",
  "School",
  "Schule",
  "Ku\xA6nia",
  "Smiths shop",
  "Schmiede",
  "Ch\x92opi",
  "Peasants",
  "Bauern",
  "Baraki",
  "Barracks",
  "Kaserne"
};

char *UI_Locale_BuildingNames_M[9] =
{
  "Ku\xA6nia",
  "Smiths shop",
  "Schmiede",
  "Ch\x92opi",
  "Peasants",
  "Bauern",
  "Baraki",
  "Barracks",
  "Kaserne"
};

char *g_CastleBuildingIconTooltipNames_FromPeasants[6] = { "Ch\x92opi", "Peasants", "Bauern", "Baraki", "Barracks", "Kaserne" };

__int16 g_CastleAmbientLayer1_SpriteIds[] = { 251 };

__int16 g_CastleAmbientLayer1_XOffsets[] = { 254 };

__int16 g_CastleAmbientLayer2_SpriteIds[] = { 549 };

__int16 g_CastleAmbientLayer2_XOffsets[] = { 192 };

__int16 g_CastleAmbientLayer3_SpriteIds[] = { 549 };

__int16 g_CastleAmbientLayer3_XOffsets[] = { 274 };

__int16 g_CastleAmbientLayer4_SpriteIds[] = { -1 };

__int16 g_CastleAmbientLayer4_XOffsets[] = { -1 };

__int16 g_CastleAmbientLayer5_SpriteIds[] = { 292 };

__int16 g_CastleAmbientLayer5_XOffsets[] = { 101 };

__int16 g_CastleAmbientLayer6_SpriteIds[] = { 535 };

__int16 g_CastleAmbientLayer6_XOffsets[] = { 399 };

__int16 g_CastleAmbientLayer7_SpriteIds[] = { 459 };

__int16 g_CastleAmbientLayer7_XOffsets[] = { 169 };

__int16 g_CastleAmbientLayer8_SpriteIds[] = { 74 };

__int16 g_CastleAmbientLayer8_XOffsets[] = { 123 };

__int16 g_CastleAmbientLayer9_SpriteIds[] = { 154 };

__int16 g_CastleAmbientLayer9_XOffsets[] = { 409 };

__int16 g_CastleAmbientLayer10_SpriteIds[] = { 210 };

__int16 g_CastleAmbientLayer10_XOffsets[83] =
{
  390,
  259,
  193,
  466,
  163,
  465,
  253,
  440,
  221,
  347,
  129,
  608,
  389,
  412,
  177,
  -1,
  -1,
  211,
  385,
  243,
  362,
  226,
  185,
  528,
  206,
  528,
  275,
  -1,
  -1,
  367,
  117,
  583,
  401,
  458,
  165,
  74,
  155,
  155,
  409,
  210,
  389,
  -1,
  -1,
  506,
  199,
  506,
  266,
  3,
  262,
  317,
  112,
  576,
  415,
  465,
  171,
  189,
  159,
  210,
  385,
  246,
  362,
  274,
  245,
  467,
  207,
  467,
  277,
  429,
  224,
  341,
  127,
  604,
  388,
  413,
  177,
  -1,
  -1,
  211,
  385,
  242,
  362,
  0,
  0
};

__int16 g_CastleHoverTooltipZones[4] = { 5, 6, 30, 29 };

_BYTE g_CastleStatusWidgetRecord[WORLD_MAP_ACTION_WIDGET_RECORD_SIZE + 4] __attribute__((aligned(4)));

CLASH95_INTERNAL int g_CastleCompositeStatusWidgetInitialized;

_WORD g_CastleNewBuildingMenu[5] = { 500, 60, 0, 0, 3 };

int g_CastleAnyAddonMissingFlag = 1;

int g_CastleAddonSchoolMissingFlags[] = { 1 };

int g_CastleAddonHospitalMissingFlag = 1;

int g_CastleAddonBarracksMissingFlag = 1;

int g_CastleAddonWorkshopMissingFlag = 1;

int g_CastleAddonSmithsMissingFlag = 1;

char *g_CastleConfirmDestroyPrompt[3] = { "Czy jeste\x9E pewien?", "Are you sure?", "Bist Du sicher?" };

_UNKNOWN g_CastleOwnerIconPositions;

int g_CastleAmbientLayer3_DelayJitter = 10;

int g_CastleAmbientLayer6_DelayJitter = 10;

int g_UnitStackSelectionActiveUnitIndex = -1;

int g_RoadOverlaySpriteByConnectionMask[27] =
{
  0,
  0,
  0,
  870,
  0,
  867,
  868,
  869,
  0,
  876,
  866,
  873,
  874,
  875,
  871,
  872,
  0,
  0,
  385875968,
  119149848,
  117901063,
  117901063,
  151914247,
  67374091,
  67372036,
  67372036,
  263172
};

int g_BridgeApproachRoadOverlayTileIds[] = { 544 };

int g_RoadBuildModeMarkerBounceOffsets[9] = { -8, -4, 0, 4, 8, 4, 0, -4, 0 };

int g_RoadBuildModeNorthMarkerX = 416;

int g_RoadBuildModeNorthMarkerY = 400;

int g_RoadBuildModeEastMarkerX = 480;

int g_RoadBuildModeEastMarkerY = 400;

int g_RoadBuildModeSouthMarkerX = 544;

int g_RoadBuildModeSouthMarkerY = 400;

int g_RoadBuildModeWestMarkerX = 416;

int g_RoadBuildModeWestMarkerY = 432;

_DWORD g_RoadBuildModeControlWidgets[2] = { 416, 400 };

int g_RoadBuildModeControlWidgetState = 1;

int g_UnitBattleAdjacentTileDeltaX[] = { 0 };

int g_UnitBattleAdjacentTileDeltaY[] = { -1 };

_UNKNOWN g_UnitBattleShotAnimTemplate;

_BYTE g_BuildingEconomyDialogActionWidgets[WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * BUILDING_ECONOMY_DIALOG_WIDGET_COUNT + 4] __attribute__((aligned(4)));

CLASH95_INTERNAL int g_BuildingEconomyDialogWidgetsInitialized;

__int16 g_BuildingEconomyDialogTooltipZoneRect[4] = { 199, 9, 438, 69 };

char *g_TrapPitfallDiscoveryMessageStrings[2] =
{
  "To wilczy d\xA2\x92. Czy pragniesz go zasypa\x8D, Panie",
  "This is a pitfall. Do you want to cover it, master?"
};

char *g_GodAngerMessageStrings[9] =
{
  "Gniew Bozy!",
  "God's Anger!",
  "Zorn Gottes!",
  "Odwr\xA2t",
  "Retreat",
  "R\x81""ckzug",
  "Zbyt malo PA aby sie okopac",
  "Not enough AP to prepare to defence",
  "Nicht genug AP zur Verteidigung"
};

char *g_UnitBattleRetreatMessageStrings[6] =
{
  "Odwr\xA2t",
  "Retreat",
  "R\x81""ckzug",
  "Zbyt malo PA aby sie okopac",
  "Not enough AP to prepare to defence",
  "Nicht genug AP zur Verteidigung"
};

char *g_UnitBattlePrepareDefenceMessageStrings[3] =
{
  "Zbyt malo PA aby sie okopac",
  "Not enough AP to prepare to defence",
  "Nicht genug AP zur Verteidigung"
};

_BYTE g_UnitBattleActionWidgetTable[WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * (UNIT_BATTLE_ACTION_WIDGET_COUNT + 1)] __attribute__((aligned(4)));

char *g_UnitBattlePlayerLabelStrings[3] = { "Gracz", "Player", "Spieler" };

_UNKNOWN g_UnitBattlePlayerPromptDialogTemplate;

char *g_UnitBattlePlayerPromptLabelStrings[2] = { "Gracz", "Player" };

__int16 g_UnitBattlePanelStatIconX[] = { 498 };

__int16 g_UnitBattlePanelStatIconY[] = { 143 };

char g_UnitBattlePanelQuantityIconCharBase[] = { '$' };

char g_UnitBattlePanelDefenseIconChar = 'Q';

char g_UnitBattlePanelAttackIconChar = 'Z';

char g_UnitBattlePanelVolleyIconChar = '\0';

char g_UnitBattlePanelMoraleIconChar = '-';

char g_UnitPanelRow3FallbackIconChar = 'c';

char *g_UnitActionTooltipTexts[24] =
{
  "Liczebno\x9E\x8D",
  "Quantity",
  "Anzahl",
  "Punkty akcji",
  "Action points",
  "Aktionspunkte",
  "Si\x92""a ataku",
  "Attack power",
  "Angriffsst\x84rke",
  "Si\x92""a ra\xA7""enia",
  "Shot power",
  "Schu\xE1\x6B\x72""aft",
  "Si\x92""a obrony",
  "Defence power",
  "Verteidigungskraft",
  "Status",
  "Status",
  "Status",
  "Morale",
  "Morale",
  "Moral",
  "Zm\x91""czenie",
  "Tiredness",
  "M\x81""digkeit"
};

int g_UnitActionTooltipLastShownAction = -1;

char *g_BattleYourTurnBannerTexts[6] =
{
  "Tw\xA2j ruch",
  "Your turn",
  "Dein Zug",
  "Niewielkie szanse na zwyci\x91stwo zmusi\x92y Ci\x91 do wycofania rycerzy. Twe jednostki w szybkim tempie opu\x9E""ci\x92y pole bitwy, jednak wr\xA2g zdo\x92""a\x92 jeszcze zada\x8D im powa\xA7ne straty.",
  "You had to withdraw your troops from this battle for your chances were small. Your units managed to flee from the battlefield, some were wounded.",
  "Die nicht allzu gro\xE1\x65\x6E Siegeschancen zwangen Dich zum R\x81""ckzug Deiner Ritter. In schnellem Tempo verlie\xE1\x65\x6E Deine Einheiten das Schlachtfeld, trotzdem konnte der Feind ihnen noch ernste Verluste zuf\x81gen."
};

char *g_BattleForcedRetreatOutcomeTexts[3] =
{
  "Niewielkie szanse na zwyci\x91stwo zmusi\x92y Ci\x91 do wycofania rycerzy. Twe jednostki w szybkim tempie opu\x9E""ci\x92y pole bitwy, jednak wr\xA2g zdo\x92""a\x92 jeszcze zada\x8D im powa\xA7ne straty.",
  "You had to withdraw your troops from this battle for your chances were small. Your units managed to flee from the battlefield, some were wounded.",
  "Die nicht allzu gro\xE1\x65\x6E Siegeschancen zwangen Dich zum R\x81""ckzug Deiner Ritter. In schnellem Tempo verlie\xE1\x65\x6E Deine Einheiten das Schlachtfeld, trotzdem konnte der Feind ihnen noch ernste Verluste zuf\x81gen."
};

int g_UnitBattleAnimatingUnitIndex = -1;

int g_UnitFadeAnimUnitIndex = -1;

int g_UnitFadeAnimTargetOffset = 100;

int g_UnitFadeAnimStepRate = 10;

int g_UnitBattleShotProjectileTileX = -1;

int g_UnitBattleShotProjectileTileY = -1;

char *g_WallInfoPopupLabelTexts[2] = { "Mur", "Wall" };

_BYTE BuildingGarrisonDialogActions[WORLD_MAP_ACTION_WIDGET_RECORD_SIZE * (BUILDING_GARRISON_DIALOG_WIDGET_COUNT + 1)] __attribute__((aligned(4)));

_DWORD g_CastleUnitProductionWidgetTable[3] = { 311, 24, 1 };

__int16 g_CastleUnitProductionTooltipZone[4] = { 32, 23, 337, 125 };

char *UI_Locale_StatusHeader[2] = { "Do uko\xA4""czenia", "%d turns until" };

char *UI_Locale_StatusLine1[5] =
{
  "produkcji",
  "the end of",
  "Produktionsende",
  "pozosta\x92o %d tur",
  "production"
};

char *UI_Locale_StatusDetail_A[2] = { "pozosta\x92o %d tur", "production" };

char *UI_Locale_StatusDetail_B[2] = { "pozosta\x92""a %d tura", "production" };

char *UI_Locale_StatusDetail_C[2] = { "pozosta\x92y %d tury", "production" };

char *UI_Locale_StatusHeader_Full[6] =
{
  "Produkcja",
  "Production",
  "Produktion ist",
  "wstrzymana",
  "is stopped",
  "gestoppt"
};

char *UI_Locale_StatusLine1_Full[3] = { "wstrzymana", "is stopped", "gestoppt" };

char aGfx_5[5] = "gfx\\";

char *g_BuildingTransferOutsideCastleLabel[3] = { "Przed mury zamku", "Outside the castle", "Au\xE1\x65\x72halb des Schlosses" };

_UNKNOWN g_UiFormattedMessageTemplateTable;

int g_UnitBattleAiRoleScoreWeights[8] = { 0, 10, 20, 30, 50, 40, 40, 0 };

int g_UnitBattleAiCurrentPlanMode = -1;

char g_BattleRoleDeploymentBucketTable[16] =
{
  '\v',
  '\n',
  '\v',
  '\n',
  '\x15',
  '\x15',
  '\x14',
  '\v',
  '\v',
  '\v',
  '\n',
  '\x15',
  '\x15',
  '\x14',
  '\0',
  '\0'
};

_DWORD g_GateDoorDialogWidgetTable_V1[3] = { 39, 426, 1 };

_DWORD g_GateDoorDialogWidgetTable_V2[3] = { 39, 426, 1 };

_DWORD g_GateDoorDialogWidgetTable_V3[3] = { 39, 426, 1 };

_DWORD g_GateDoorDialogWidgetTable_V4[3] = { 39, 426, 1 };

char g_ProductionLicenceSmithsRequiredUnitTypes[16] =
{
  UNIT_TYPE_HEAVY_INFANTRY,
  UNIT_TYPE_HEAVY_SPEARMAN,
  UNIT_TYPE_HEAVY_CAVALRY,
  UNIT_TYPE_LIGHT_CAVALRY,
  UNIT_TYPE_KNIGHTS,
  UNIT_TYPE_DRAGON_CAVALRY,
  UNIT_TYPE_MUSKETEER,
  UNIT_TYPE_CANNON,
  -1,
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0'
};

char g_ProductionLicenceWorkshopRequiredUnitTypes[8] = {
  UNIT_TYPE_ARCHER,
  UNIT_TYPE_CROSSBOWER,
  UNIT_TYPE_CATAPULT,
  UNIT_TYPE_RAM,
  UNIT_TYPE_FORESTER,
  -1,
  '\0',
  '\0'
};

_DWORD g_LargeBuildingNeighborOffsets[24] =
{
  0, 2,
  1, 2,
  2, -1,
  2, 1,
  -1, 1,
  2, 0,
  -1, 0,
  2, -1,
  -1, -1,
  1, -1,
  0, -1,
  0, 0
};

char g_SettlementTaxBurdenThresholds[16] =
{
  '\0',
  '\x05',
  '\n',
  '\x14',
  '\x05',
  '\n',
  '\x0F',
  '\x1E',
  '\n',
  '\x0F',
  '\x14',
  '#',
  '\0',
  '\0',
  '\0',
  '\0'
};

unit_type g_TempleGiftUnitPool_MinorMonsters[5] = {
  UNIT_TYPE_FLY,
  UNIT_TYPE_CYCLOP,
  UNIT_TYPE_TROLL,
  UNIT_TYPE_SCORPION,
  UNIT_TYPE_SKELETON
};

unit_type g_TempleGiftUnitPool_HumanTroops[7] = {
  UNIT_TYPE_LIGHT_INFANTRY,
  UNIT_TYPE_HEAVY_INFANTRY,
  UNIT_TYPE_PIKEMAN,
  UNIT_TYPE_HEAVY_SPEARMAN,
  UNIT_TYPE_LIGHT_CAVALRY,
  UNIT_TYPE_KNIGHTS,
  UNIT_TYPE_DRAGON_CAVALRY
};

unit_type g_TempleGiftUnitPool_ScriptedRam[] = { UNIT_TYPE_RAM };

_UNKNOWN g_TempleGiftOutcomeTable_OwnCultActive;

_UNKNOWN g_TempleGiftOutcomeTable_ForeignCultActive;

_UNKNOWN g_TempleGiftOutcomeTable_OwnCultInactive;

_UNKNOWN g_TempleGiftOutcomeTable_ForeignCultInactive;

char *g_TempleSacrilegeUnitKilledTexts[9] =
{
  "G\x92upcze! Jak \x9Emia\x92""e\x9E zak\x92\xA2""ca\x8D spok\xA2j boskich istot. \x98wi\x91tkradcy zostali unicestwieni.",
  "Yoy fool! How dare you disturb the peace of Gods. Perpetrators of sacrilige have been annihilated!",
  "Du Unseliger! Wie kannst Du es wagen, den Frieden der G\x94tter zu st\x94ren! Die, die dieses Sakrileg begingen, wurden vernichtet!",
  "Jeste\x9E grzesznikiem, a na takich B\xA2g nie spogl\x86""da \x92""askawym okiem. Odejd\xA6 i nigdy tu nie wracaj!",
  "You're a sinner. God has no mercy on you. Leave and never come back here again!",
  "Du bist ein S\x81nder. Gott hat keine Gnade mit Dir. Gehe jetzt und la\xE1\x20\x44ich nie wieder hier sehen",
  "Twoje ofiary nie przynios\x92y po\xA7\x86""danego skutku. Bogowie zignorowali twe mod\x92y.",
  "Your sacrifice has brought nothing. Gods gave you nothing in return for your prayers.",
  "Dein Opfer war wertlos. Die G\x94tter haben Deine Gebete nicht erh\x94rt."
};

char *g_TempleGiftRewardText[6] =
{
  "Jeste\x9E grzesznikiem, a na takich B\xA2g nie spogl\x86""da \x92""askawym okiem. Odejd\xA6 i nigdy tu nie wracaj!",
  "You're a sinner. God has no mercy on you. Leave and never come back here again!",
  "Du bist ein S\x81nder. Gott hat keine Gnade mit Dir. Gehe jetzt und la\xE1\x20\x44ich nie wieder hier sehen",
  "Twoje ofiary nie przynios\x92y po\xA7\x86""danego skutku. Bogowie zignorowali twe mod\x92y.",
  "Your sacrifice has brought nothing. Gods gave you nothing in return for your prayers.",
  "Dein Opfer war wertlos. Die G\x94tter haben Deine Gebete nicht erh\x94rt."
};

char *g_TempleGiftEmptyText[3] =
{
  "Twoje ofiary nie przynios\x92y po\xA7\x86""danego skutku. Bogowie zignorowali twe mod\x92y.",
  "Your sacrifice has brought nothing. Gods gave you nothing in return for your prayers.",
  "Dein Opfer war wertlos. Die G\x94tter haben Deine Gebete nicht erh\x94rt."
};

__int16 g_DemoTextColumnXOffsets[8] = { 26, 70, 113, 156, 199, 0, 0, 0 };

_DWORD g_DemoTextHoverWidgetTable[3] = { 210, 303, 1 };

char *g_BattleMapFileSuffixByFactionTable[7] = { "nt", "nt", "nt", "nt", "np", "np", "np" };

char g_MoveSoundSurfaceClassTable[440] =
{
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x01',
  '\x02',
  '\x01',
  '\x01',
  '\x02',
  '\x01',
  '\x02',
  '\x01',
  '\x01',
  '\x01',
  '\x02',
  '\x01',
  '\x01',
  '\x02',
  '\x01',
  '\x01',
  '\x01',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x01',
  '\x01',
  '\x01',
  '\x02',
  '\x01',
  '\x01',
  '\x02',
  '\x01',
  '\x01',
  '\x01',
  '\x02',
  '\x02',
  '\x02',
  '\x01',
  '\x02',
  '\x02',
  '\x01',
  '\x02',
  '\x02',
  '\x01',
  '\x02',
  '\x02',
  '\x01',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\0',
  '\x02',
  '\0',
  '\0',
  '\x02',
  '\0',
  '\x02',
  '\0',
  '\0',
  '\0',
  '\x02',
  '\0',
  '\0',
  '\x02',
  '\0',
  '\0',
  '\0',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\0',
  '\0',
  '\0',
  '\x02',
  '\0',
  '\0',
  '\x02',
  '\0',
  '\0',
  '\0',
  '\x02',
  '\0',
  '\x02',
  '\x02',
  '\0',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\0',
  '\x02',
  '\x02',
  '\0',
  '\x02',
  '\x02',
  '\x01',
  '\x02',
  '\x01',
  '\x01',
  '\x02',
  '\x01',
  '\x02',
  '\x01',
  '\x01',
  '\x01',
  '\x02',
  '\x01',
  '\x01',
  '\x02',
  '\x01',
  '\x01',
  '\x01',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x01',
  '\x01',
  '\x01',
  '\x02',
  '\x01',
  '\x01',
  '\x02',
  '\x01',
  '\x01',
  '\x01',
  '\x02',
  '\x01',
  '\x02',
  '\x02',
  '\x01',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x01',
  '\x02',
  '\x02',
  '\x01',
  '\x02',
  '\0',
  '\x01',
  '\0',
  '\x01',
  '\x01',
  '\0',
  '\x01',
  '\0',
  '\0',
  '\0',
  '\0',
  '\x01',
  '\0',
  '\0',
  '\x01',
  '\0',
  '\x01',
  '\x01',
  '\0',
  '\0',
  '\0',
  '\0',
  '\x01',
  '\x01',
  '\0',
  '\x01',
  '\0',
  '\0',
  '\x01',
  '\0',
  '\0',
  '\0',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\x02',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0'
};

int g_Audio_ActiveSoundHandle = -1;

int g_UnitSoundsEnabled = 1;

int g_Audio_MusicActiveFlag = 1;

char aSfx_0[5] = "sfx\\";

char aSfxOddzialy[14] = "sfx\\oddzialy\\";

char aSfxOddzialy_0[14] = "sfx\\oddzialy\\";

char aSfxOddzialy_1[14] = "sfx\\oddzialy\\";

char aSfxOddzialy_2[14] = "sfx\\oddzialy\\";

char aSfxOddzialy_3[14] = "sfx\\oddzialy\\";

char aSfxOddzialy_4[14] = "sfx\\oddzialy\\";

char aSfxOddzialy_5[14] = "sfx\\oddzialy\\";

char aSfxRuchy[11] = "sfx\\ruchy\\";

char aSfxRuchy_0[11] = "sfx\\ruchy\\";

__int16 g_WorldMapUnitMoveSoundSuffixCode = 48;

char aSfxRuchy_1[11] = "sfx\\ruchy\\";

char aSfxRuchy_2[11] = "sfx\\ruchy\\";

__int16 g_BattleMapUnitMoveSoundSuffixCode = 48;

char aSfxButtons[13] = "sfx\\buttons\\";

char aSfx[5] = "sfx\\";

char aCClash[10] = "c:\\clash\\";

_UNKNOWN g_FileSystemRootMountObject;

char *g_ArchiveMountFailedErrorText[3] =
{
  "Wloz plyte z gra do napedu!",
  "Clash CD not found!",
  "Clash CD nicht gefunden"
};

char *g_StartupResourceMissingErrorText[3] =
{
  "Wloz plyte z gra do napedu!",
  "Clash CD not found!",
  "Clash CD nicht gefunden"
};

char *g_PortReinforcementArrivedTexts[3] =
{
  "Posi\x92ki przyby\x92y",
  "Extra troops came",
  "Truppen kommen"
};

char *g_PortEmptyTexts[3] = { "Port jest pusty", "Port is empty", "Hafen ist verlassen" };

char *g_UnitHideFailedLowRankText[6] =
{
  "Oddzia\x92 ma za ma\x92y status.",
  "Status of the unit is too low.",
  "Status der Einheit ist zu niedrig.",
  "Nie mog\x91 si\x91 ukry\x8D. Obiekty wroga w pobli\xA7u!",
  "I can not hide. Enemy objects nearby.",
  "Ich kann mich nicht verstecken. Feindliche Objekte in der N\x84he."
};

char *g_UnitHideFailedNoSpotText[3] =
{
  "Nie mog\x91 si\x91 ukry\x8D. Obiekty wroga w pobli\xA7u!",
  "I can not hide. Enemy objects nearby.",
  "Ich kann mich nicht verstecken. Feindliche Objekte in der N\x84he."
};

_UNKNOWN g_SaveSlotDialogWidgetTemplateBlob;

char *g_PlagueOutbreakNoticeFmtText[12] =
{
  "Na %s wybuch\x92""a zaraza. Z chat ch\x92opskich wydobywa si\x91 od\xA2r gnij\x86""cego mi\x91sa, trupy nieszcz\x91\x9Enik\xA2w walaj\x86 si\x91 po ca\x92ym dziedzi\xA4""cu. W kr\xA2tkim czasie epidemia dotkliwie zredukuje ilo\x9E\x8D wie\x9Eniak\xA2w w tym zamku.",
  "A terrible plague broke out at the castle %s. The pungent stench of rotten meat reeks out of peasants\x92 houses. Dead bodies are scattered everywhere. Soon the plague will outnumber the population of the inhabitants in the castle.",
  "Auf %s ist eine Seuche ausgebrochen. Aus den Bauernh\x84usern dringt der Gestank von verwesendem Fleisch. Die Leichen der Ungl\x81""cklichen t\x81rmen sich auf jedem Hof. In kurzer Zeit wird die Epidemie die Zahl der Dorfleute in der Burg stark dezimiert haben.",
  "Dzi\x91ki Twojej dzia\x92""alno\x9E""ci osi\x86gn\x86\x92""e\x9E wy\xA7szy poziom technologiczny. Otwieraj\x86 si\x91 przed Tob\x86 nowe mo\xA7liwo\x9E""ci rozbudowy armii.",
  "Thanks to your wise rule you have achieved a higher technological level. Now you can expand your army in new ways.",
  "Dank Deines klugen Vorgehens hast Du ein h\x94heres technologisches Niveau erreicht. Es er\x94""ffnen sich Dir neue M\x94glichkeiten zum Ausbau Deiner Armee.",
  "Panie, Twoi poddani nareszcie uko\xA4""czyli budow\x91 zamku. Jak chcesz go nazwa\x8D?",
  "Master, your builders have finally accomplished the construction of the castle. How do you want to name this building?",
  "Deine Untergebenen haben den Bau der Burg endlich beendet. Wie willst Du sie nennen?",
  "Panie, Twoi poddani nareszcie uko\xA4""czyli budow\x91 twierdzy. Jak chcesz j\x86 nazwa\x8D?",
  "Master, your builders have finally accomplished construction of the fortress. How do you want to name this building?",
  "Deine Untergebenen haben den Bau der Festung endlich beendet. Wie willst Du sie nennen?"
};

char *g_TechLevelUpNoticeText[9] =
{
  "Dzi\x91ki Twojej dzia\x92""alno\x9E""ci osi\x86gn\x86\x92""e\x9E wy\xA7szy poziom technologiczny. Otwieraj\x86 si\x91 przed Tob\x86 nowe mo\xA7liwo\x9E""ci rozbudowy armii.",
  "Thanks to your wise rule you have achieved a higher technological level. Now you can expand your army in new ways.",
  "Dank Deines klugen Vorgehens hast Du ein h\x94heres technologisches Niveau erreicht. Es er\x94""ffnen sich Dir neue M\x94glichkeiten zum Ausbau Deiner Armee.",
  "Panie, Twoi poddani nareszcie uko\xA4""czyli budow\x91 zamku. Jak chcesz go nazwa\x8D?",
  "Master, your builders have finally accomplished the construction of the castle. How do you want to name this building?",
  "Deine Untergebenen haben den Bau der Burg endlich beendet. Wie willst Du sie nennen?",
  "Panie, Twoi poddani nareszcie uko\xA4""czyli budow\x91 twierdzy. Jak chcesz j\x86 nazwa\x8D?",
  "Master, your builders have finally accomplished construction of the fortress. How do you want to name this building?",
  "Deine Untergebenen haben den Bau der Festung endlich beendet. Wie willst Du sie nennen?"
};

char *g_BuildingCompleteNoticeText[6] =
{
  "Panie, Twoi poddani nareszcie uko\xA4""czyli budow\x91 zamku. Jak chcesz go nazwa\x8D?",
  "Master, your builders have finally accomplished the construction of the castle. How do you want to name this building?",
  "Deine Untergebenen haben den Bau der Burg endlich beendet. Wie willst Du sie nennen?",
  "Panie, Twoi poddani nareszcie uko\xA4""czyli budow\x91 twierdzy. Jak chcesz j\x86 nazwa\x8D?",
  "Master, your builders have finally accomplished construction of the fortress. How do you want to name this building?",
  "Deine Untergebenen haben den Bau der Festung endlich beendet. Wie willst Du sie nennen?"
};

char *g_BuildingCompleteNoticeTextAlt[3] =
{
  "Panie, Twoi poddani nareszcie uko\xA4""czyli budow\x91 twierdzy. Jak chcesz j\x86 nazwa\x8D?",
  "Master, your builders have finally accomplished construction of the fortress. How do you want to name this building?",
  "Deine Untergebenen haben den Bau der Festung endlich beendet. Wie willst Du sie nennen?"
};

_UNKNOWN g_QueenWhimDecisionButtonWidgetsTemplate;

_UNKNOWN g_YesNoDialogButtonWidgetsTemplate;

char *g_QueenMarriageProposalTexts[3] =
{
  "Z zamorskiego kraju przyby\x92 pose\x92 z portretem pi\x91knej ksi\x91\xA7niczki. Jej ojciec, kr\xA2l Wolfgang, widz\x86""c  pot\x91g\x91 Twego kr\xA2lestwa got\xA2w jest odda\x8D Ci j\x86 za \xA7on\x91. Czy pragniesz j\x86 po\x9Elubi\x8D?",
  "An envoy arrived from a distant country with a picture of a beautiful princess. Her father, king Wolfgang, seeing your power wishes to offer you his daughter's hand. Do you want to marry her?",
  "Ein Gesandter aus einem fernen Land bringt Dir das Bild einer sch\x94nen Prinzessin. Ihr Vater, K\x94nig Wolfgang, bietet Dir ihre Hand an. M\x94""chtest Du sie zur Frau nehmen?"
};

_UNKNOWN g_QueenMarriageProposalButtonWidgetsTemplate;

char *g_MissionStatusTextsByLanguage[63] =
{
  "Zniszczy\x8D wszystkie oddzia\x92y wroga",
  "Destroy all the enemy's detachments",
  "Zerst\x94re alle Truppen des Feindes",
  "Dotrze\x8D do \x9Ewi\x86tyni stra\xA7nik\xA2w \x9Czy chrzcicieli",
  "Reach the temple of Tear of Baptists guards",
  "Besuche den Tempel \"Die Tr\x84ne des Baptisten\"",
  "Zdoby\x8D zamek przeciwnika",
  "Seize the enemy's castle",
  "Die Burg des Feindes mu\xE1\x20\x65ingenommen werden",
  "Utrzyma\x8D twierdz\x91 przez X tur",
  "Remain in possession of the fortress for X rounds",
  "Halte die Festung \x81""ber 10 Runden",
  "Uwolni\x8D uprowadzonych dworzan w ci\x86gu XX tur",
  "Rescue the captured courtiers within XX rounds",
  "Innerhalb von 20 Runden mu\xE1\x74\x20""Du deine Untertanen befreien",
  "Zniszczy\x8D poplecznik\xA2w Agordeh\xA2w",
  "Destroy the Agordehs",
  "Du mu\xE1\x74\x20""die Agordeher ausrotten",
  "Odbi\x8D kr\xA2low\x86",
  "Rescue the queen",
  "Befreie die K\x94nigin",
  "Odnale\xA6\x8D 4 diamenty Dahar'khu",
  "Find the 4 diamonds of Dahar'kh",
  "Finde die 4 Diamanten von Dahar'kh",
  "Doprowadzi\x8D wszystkich dow\xA2""dc\xA2w do zamku Gordmouth",
  "Take all the commanders to the Gordmouth castle",
  "Du mu\xE1\x74\x20""alle Gener\x84le in die Burg von Gordmouth f\x81hren",
  "Zabij wszystkich!",
  "Kill them all!",
  "Du mu\xE1\x74\x20""alle vernichten!",
  "Zniszczy\x8D \x92otr\xA2w z Gaal'aad",
  "Destroy the Gaal'aad's scoundrels",
  "Eliminiere Gaalaads H\x84scher",
  "Z\x92o\xA7y\x8D ofiar\x91 Siggowi w swi\x91tym kr\x91gu",
  "Make a sacrifice to Sigg in the holy circle",
  "Besuche das Orakel \"Dritte Inkarnation von Sigga\"",
  "Zdoby\x8D zamek przeciwnika",
  "Seize the enemy's castle",
  "Du mu\xE1\x74\x20""die feindliche Festung einnehmen",
  "Utrzyma\x8D zamek przez X tur",
  "Remain in possession of the fortress for X rounds",
  "Verteidige die Burg \x81""ber 10 Runden",
  "Odbi\x8D je\xA4""c\xA2w z zamku wroga w ci\x86gu XX tur",
  "Rescue the prisoners from enemy's castle within XX rounds",
  "Innerhalb von 20 Runden mussen Gefangene befreit werden",
  "Zniszczy\x8D znienawidzonych Agordeh\xA2w utrzymuj\x86""c pok\xA2j z pozosta\x92ymi kr\xA2lestwami.",
  "Destroy the hateful Agordehs, keeping peace with the other kingdoms",
  "Du mu\xE1\x74\x20""die Agordeher besiegen w\x84hrend Du mit anderen K\x94nigreichen Frieden schlie\xE1\x74",
  "Zdoby\x8D najbardziej zaawansowany technologicznie zamek w\x92""adcy Kalev",
  "Seize the most technologically advanced of the Kalev sovereign's castles",
  "Die Burg von Kalev - wo sich die Wissenschaftler befinden - mu\xE1\x20\x65ingenommen werden",
  "Odnale\xA6\x8D 4 diamenty Xye",
  "Find the 4 diamonds of Xye",
  "Finde die 4 Diamanten von Xye",
  "Doprowadzi\x8D 6 dow\xA2""dc\xA2w z manuskryptami do zamku Cantbelly",
  "Take the 6 commanders with manuscripts to the Cantbelly castle",
  "F\x81hre 6 Gener\x84le mit allen Manuskripten in die Cantbelly Burg",
  "Zabij wszystkich!",
  "Kill them all!",
  "Du mu\xE1\x74\x20""alle vernichten!",
  "Misja %d\n\n%s",
  "Misssion %d\n\n%s",
  "Misssion %d\n\n%s"
};

char *g_MissionStatusFormatsByLanguage[3] = { "Misja %d\n\n%s", "Misssion %d\n\n%s", "Misssion %d\n\n%s" };

_BYTE g_MainMenuButtonWidgetsTemplate[371];

_BYTE g_CampaignMenuButtonWidgetsTemplate[159];

char aKarkhan[8] = "Karkhan";

char *g_MultiplayerDefaultRulerNamesTable = &g_MultiplayerPlayerNameEditTable;

_UNKNOWN g_MultiplayerSetupWidgetTemplateBlob;

unsigned __int16 g_OptionsMenuSliderThumbPositions[6] = { 323u, 0u, 473u, 0u, 140u, 0u };

int g_Options_BrightnessSliderValue = 128;

int g_Options_ScrollSpeedSliderValue = 128;

int g_Options_MouseSpeedSliderValue = 128;

_UNKNOWN g_OptionsMenuWidgetTemplateBlob;

_BYTE g_LoadMenuButtonWidgetsTemplate[159];

int g_OptionsConfigRecordBase = 1;

int g_OptionsConfigRecordFlag0C = 0;

int g_Options_MusicEnabledFlag = 0;

int g_Options_UnitSoundsEnabledFlag = 0;

char g_OptionsMainMenuScrollSpeedRaw = '\0';

char g_OptionsMainMenuSoundVolumeRaw = '\0';

char g_OptionsMainMenuMusicVolumeRaw = '\0';

char aMapsDirectory[6] = "maps\\";

int g_MultiplayerStartRows[] = {
  14, 20, 90, 7, 60, 46, 90, 72, 47, 80,
  29, 33, 68, 69, 38, 25, 70, 23, 87, 7,
  49, 7, 91, 7, 47, 38, 38, 66, 32, 92,
  76, 51, 93, 2, 26, 8, 26, 91, 28, 52,
  79, 40, 94, 77, 12, 54, 25, 23, 39, 96,
  8, 25, 8, 67, 53, 55, 78, 30, 48, 71,
  17, 16, 58, 6, 82, 81, 92, 5, 50, 63,
  8, 18, 24, 86, 65, 66, 23, 7, 36, 36,
  15, 33, 39, 44, 70, 48, 70, 19, 74, 73,
  68, 82, 42, 78, 60, 46, 41, 44, 91, 40,
  84, 38, 91, 9, 51, 8, 38, 66, 35, 5,
  30, 23, 17, 42, 67, 14, 80, 58, 70, 43,
  43, 46, 56, 21, 72, 50, 68, 77, 13, 37,
  58, 11, 95, 16, 11, 41, 13, 3, 90, 72,
  70, 30, 36, 54, 79, 2, 95, 51, 47, 33,
  41, 27, 12, 10, 54, 20, 52, 69, 64, 3,
  49, 93, 65, 66, 92, 45, 32, 39, 66, 24,
  52, 20, 17, 11, 40, 63, 75, 78, 77, 56,
  4, 26, 37, 24, 32, 6, 9, 2, 20, 13,
  11, 11, 32, 9, 32, 28, 11, 46, 42, 40
};

char *g_RulerNameCandidatesTable[39] =
{
  "sir artur",
  "galaghan",
  "lord ruwe",
  "tubius",
  "mcgregor",
  "frederic",
  "zygfrid",
  "lord ghan",
  "wetus",
  "longhand",
  "henryk",
  "crowley",
  "ianos",
  "twogor",
  "ruryk",
  "wodar",
  "leryks x",
  "richard v",
  "sir lester",
  "unrealius",
  "glazur",
  "uraken",
  "sir mordus",
  "riludius",
  "sir wenom",
  "sir wiliam",
  "sir john",
  "sir james",
  "gordak",
  "mcdonowan",
  "sutuahi",
  "lord gorio",
  "mcdan",
  "walter",
  "august",
  "josef",
  "mieszko",
  "sir jonas",
  "drebegen"
};

_UNKNOWN g_RulerNameHistorySeed;

char *g_PrisonerCastleIntakeTexts[21] =
{
  "Panie, nasze wojska po wygranej bitwie z armi\x86 znienawidzonego wroga wzi\x91\x92y w niewol\x91 jego dow\xA2""dc\x91 i doprowadzi\x92y do zamku %s.",
  "Master, our troops, having defeated the enemy, captured the enemy's officer and brought him to the castle %s",
  "Herr, nachdem Deine Truppen den Feind besiegt haben, haben sie den Anf\x81hrer ihrer Truppen gefangengenommen und in die Burg %s gebracht.",
  "W zamku %s scieto wieznia.",
  "A captured enemy soldier was beheaded in the castle %s.",
  "Ein gefangengenommener feindlicher Soldat wurde in der Burg %s enthauptet.",
  "Twoi kaci ostro zabrali si\x91 do roboty. Wyznaczonego na %s wi\x91\xA6nia torturowali ca\x92\x86 dob\x91 zanim zacz\x86\x92 gada\x8D. Przed \x9Emierci\x86  zdo\x92""a\x92 wykrztusi\x8D, gdzie znajduje si\x91 najbogatszy zamek jego w\x92""adcy.",
  "Your persecutors did not waste time. The victim was chosen at the castle of %s. They made him betray the secrets of the whereabouts of the richest castle just before he died in pain.",
  "Deine Vollstrecker haben keine Zeit verloren. Das Opfer wurde auf Burg %s ausgew\x84hlt und gab die Lage der reichsten Burg preis, bevor er unter furchtbaren Qualen starb.",
  "Krzyki torturowanego na %s wi\x91\xA6nia trwa\x92y ca\x92\x86 noc. Nad ranem kaci poinformowali Ci\x91, \xA7""e skazaniec przed \x9Emierci\x86 wskaza\x92 po\x92o\xA7""enie jednego z zamk\xA2w jego kr\xA2la.",
  "At %s cries of the tormented man could be heard all night long. At the break of dawn your persecutors brought you the news that he had revealed all the secrets about the whereabouts of his King's castles.",
  "Die Schreie des Ungl\x81""cklichen waren die ganze Nacht hindurch auf Burg %s zu h\x94ren. Bei Tagesanbruch brachten Deine Vollstrecker Dir die Nachricht, da\xE1\x20\x65r die Lage der Burg seines K\x94nigs preisgegeben hatte.",
  "Kaci byli bardzo zadowoleni z dobrze spe\x92nionego obowi\x86zku. Od wi\x91\xA6nia osadzonego na %s wydobyli informacj\x91 o po\x92o\xA7""eniu jednej z wrogich jednostek.",
  "Persecutors were very pleased with what they had done. They had got all information about the enemy's units from the tortured victim in the castle of %s.",
  "Die Vollstrecker waren sehr zufrieden mit dem Ergebnis ihrer Arbeit. Sie hatten ihrem Opfer auf Burg %s alle Informationen \x81""ber die feindlichen Einheiten entrei\xE1\x65\x6E k\x94nnen.",
  "Kaci ca\x92\x86 noc zn\x91""cali si\x91 nad wyznaczonym  w %s wi\x91\xA6niem, ale ten tylko krzycza\x92 i \x9Emia\x92 si\x91 na przemian. Skona\x92 z imieniem swej ukochanej na ustach.",
  "Persecutors were torturing the victim all night long in the castle of %s but he only screamed and laughed. With his last breath he took his secret with him.",
  "Auf Burg %s haben Deine Vollstrecker ihr Opfer die ganze Nacht lang gefoltert, konnten ihm aber nur Schreie und irres Gel\x84""chter entlocken. Es nahm sein Geheimnis mit ins Grab.",
  "Ani obc\x91gi, ani topory nie zmusi\x92y wi\x91\xA6nia osadzonego na %s do gadania. To wyj\x86tkowo twarda sztuka, prze\xA7y\x92 najbardziej wyszukane tortury zadawane przez Twoich kat\xA2w.",
  "Neither pliers nor axe could make him talk. He survived even the most sophisticated tortures that they had inflicted on him.",
  "Weder die eisernen Zangen noch die Axt konnten ihn zum Reden bringen. Nicht einmal die schlimmsten Foltermethoden brachten ihn um."
};

char *g_PrisonerBeheadingTexts[18] =
{
  "W zamku %s scieto wieznia.",
  "A captured enemy soldier was beheaded in the castle %s.",
  "Ein gefangengenommener feindlicher Soldat wurde in der Burg %s enthauptet.",
  "Twoi kaci ostro zabrali si\x91 do roboty. Wyznaczonego na %s wi\x91\xA6nia torturowali ca\x92\x86 dob\x91 zanim zacz\x86\x92 gada\x8D. Przed \x9Emierci\x86  zdo\x92""a\x92 wykrztusi\x8D, gdzie znajduje si\x91 najbogatszy zamek jego w\x92""adcy.",
  "Your persecutors did not waste time. The victim was chosen at the castle of %s. They made him betray the secrets of the whereabouts of the richest castle just before he died in pain.",
  "Deine Vollstrecker haben keine Zeit verloren. Das Opfer wurde auf Burg %s ausgew\x84hlt und gab die Lage der reichsten Burg preis, bevor er unter furchtbaren Qualen starb.",
  "Krzyki torturowanego na %s wi\x91\xA6nia trwa\x92y ca\x92\x86 noc. Nad ranem kaci poinformowali Ci\x91, \xA7""e skazaniec przed \x9Emierci\x86 wskaza\x92 po\x92o\xA7""enie jednego z zamk\xA2w jego kr\xA2la.",
  "At %s cries of the tormented man could be heard all night long. At the break of dawn your persecutors brought you the news that he had revealed all the secrets about the whereabouts of his King's castles.",
  "Die Schreie des Ungl\x81""cklichen waren die ganze Nacht hindurch auf Burg %s zu h\x94ren. Bei Tagesanbruch brachten Deine Vollstrecker Dir die Nachricht, da\xE1\x20\x65r die Lage der Burg seines K\x94nigs preisgegeben hatte.",
  "Kaci byli bardzo zadowoleni z dobrze spe\x92nionego obowi\x86zku. Od wi\x91\xA6nia osadzonego na %s wydobyli informacj\x91 o po\x92o\xA7""eniu jednej z wrogich jednostek.",
  "Persecutors were very pleased with what they had done. They had got all information about the enemy's units from the tortured victim in the castle of %s.",
  "Die Vollstrecker waren sehr zufrieden mit dem Ergebnis ihrer Arbeit. Sie hatten ihrem Opfer auf Burg %s alle Informationen \x81""ber die feindlichen Einheiten entrei\xE1\x65\x6E k\x94nnen.",
  "Kaci ca\x92\x86 noc zn\x91""cali si\x91 nad wyznaczonym  w %s wi\x91\xA6niem, ale ten tylko krzycza\x92 i \x9Emia\x92 si\x91 na przemian. Skona\x92 z imieniem swej ukochanej na ustach.",
  "Persecutors were torturing the victim all night long in the castle of %s but he only screamed and laughed. With his last breath he took his secret with him.",
  "Auf Burg %s haben Deine Vollstrecker ihr Opfer die ganze Nacht lang gefoltert, konnten ihm aber nur Schreie und irres Gel\x84""chter entlocken. Es nahm sein Geheimnis mit ins Grab.",
  "Ani obc\x91gi, ani topory nie zmusi\x92y wi\x91\xA6nia osadzonego na %s do gadania. To wyj\x86tkowo twarda sztuka, prze\xA7y\x92 najbardziej wyszukane tortury zadawane przez Twoich kat\xA2w.",
  "Neither pliers nor axe could make him talk. He survived even the most sophisticated tortures that they had inflicted on him.",
  "Weder die eisernen Zangen noch die Axt konnten ihn zum Reden bringen. Nicht einmal die schlimmsten Foltermethoden brachten ihn um."
};

char *g_PrisonerTortureRichestCastleRevealTexts[15] =
{
  "Twoi kaci ostro zabrali si\x91 do roboty. Wyznaczonego na %s wi\x91\xA6nia torturowali ca\x92\x86 dob\x91 zanim zacz\x86\x92 gada\x8D. Przed \x9Emierci\x86  zdo\x92""a\x92 wykrztusi\x8D, gdzie znajduje si\x91 najbogatszy zamek jego w\x92""adcy.",
  "Your persecutors did not waste time. The victim was chosen at the castle of %s. They made him betray the secrets of the whereabouts of the richest castle just before he died in pain.",
  "Deine Vollstrecker haben keine Zeit verloren. Das Opfer wurde auf Burg %s ausgew\x84hlt und gab die Lage der reichsten Burg preis, bevor er unter furchtbaren Qualen starb.",
  "Krzyki torturowanego na %s wi\x91\xA6nia trwa\x92y ca\x92\x86 noc. Nad ranem kaci poinformowali Ci\x91, \xA7""e skazaniec przed \x9Emierci\x86 wskaza\x92 po\x92o\xA7""enie jednego z zamk\xA2w jego kr\xA2la.",
  "At %s cries of the tormented man could be heard all night long. At the break of dawn your persecutors brought you the news that he had revealed all the secrets about the whereabouts of his King's castles.",
  "Die Schreie des Ungl\x81""cklichen waren die ganze Nacht hindurch auf Burg %s zu h\x94ren. Bei Tagesanbruch brachten Deine Vollstrecker Dir die Nachricht, da\xE1\x20\x65r die Lage der Burg seines K\x94nigs preisgegeben hatte.",
  "Kaci byli bardzo zadowoleni z dobrze spe\x92nionego obowi\x86zku. Od wi\x91\xA6nia osadzonego na %s wydobyli informacj\x91 o po\x92o\xA7""eniu jednej z wrogich jednostek.",
  "Persecutors were very pleased with what they had done. They had got all information about the enemy's units from the tortured victim in the castle of %s.",
  "Die Vollstrecker waren sehr zufrieden mit dem Ergebnis ihrer Arbeit. Sie hatten ihrem Opfer auf Burg %s alle Informationen \x81""ber die feindlichen Einheiten entrei\xE1\x65\x6E k\x94nnen.",
  "Kaci ca\x92\x86 noc zn\x91""cali si\x91 nad wyznaczonym  w %s wi\x91\xA6niem, ale ten tylko krzycza\x92 i \x9Emia\x92 si\x91 na przemian. Skona\x92 z imieniem swej ukochanej na ustach.",
  "Persecutors were torturing the victim all night long in the castle of %s but he only screamed and laughed. With his last breath he took his secret with him.",
  "Auf Burg %s haben Deine Vollstrecker ihr Opfer die ganze Nacht lang gefoltert, konnten ihm aber nur Schreie und irres Gel\x84""chter entlocken. Es nahm sein Geheimnis mit ins Grab.",
  "Ani obc\x91gi, ani topory nie zmusi\x92y wi\x91\xA6nia osadzonego na %s do gadania. To wyj\x86tkowo twarda sztuka, prze\xA7y\x92 najbardziej wyszukane tortury zadawane przez Twoich kat\xA2w.",
  "Neither pliers nor axe could make him talk. He survived even the most sophisticated tortures that they had inflicted on him.",
  "Weder die eisernen Zangen noch die Axt konnten ihn zum Reden bringen. Nicht einmal die schlimmsten Foltermethoden brachten ihn um."
};

char *g_PrisonerTortureCastleRevealTexts[12] =
{
  "Krzyki torturowanego na %s wi\x91\xA6nia trwa\x92y ca\x92\x86 noc. Nad ranem kaci poinformowali Ci\x91, \xA7""e skazaniec przed \x9Emierci\x86 wskaza\x92 po\x92o\xA7""enie jednego z zamk\xA2w jego kr\xA2la.",
  "At %s cries of the tormented man could be heard all night long. At the break of dawn your persecutors brought you the news that he had revealed all the secrets about the whereabouts of his King's castles.",
  "Die Schreie des Ungl\x81""cklichen waren die ganze Nacht hindurch auf Burg %s zu h\x94ren. Bei Tagesanbruch brachten Deine Vollstrecker Dir die Nachricht, da\xE1\x20\x65r die Lage der Burg seines K\x94nigs preisgegeben hatte.",
  "Kaci byli bardzo zadowoleni z dobrze spe\x92nionego obowi\x86zku. Od wi\x91\xA6nia osadzonego na %s wydobyli informacj\x91 o po\x92o\xA7""eniu jednej z wrogich jednostek.",
  "Persecutors were very pleased with what they had done. They had got all information about the enemy's units from the tortured victim in the castle of %s.",
  "Die Vollstrecker waren sehr zufrieden mit dem Ergebnis ihrer Arbeit. Sie hatten ihrem Opfer auf Burg %s alle Informationen \x81""ber die feindlichen Einheiten entrei\xE1\x65\x6E k\x94nnen.",
  "Kaci ca\x92\x86 noc zn\x91""cali si\x91 nad wyznaczonym  w %s wi\x91\xA6niem, ale ten tylko krzycza\x92 i \x9Emia\x92 si\x91 na przemian. Skona\x92 z imieniem swej ukochanej na ustach.",
  "Persecutors were torturing the victim all night long in the castle of %s but he only screamed and laughed. With his last breath he took his secret with him.",
  "Auf Burg %s haben Deine Vollstrecker ihr Opfer die ganze Nacht lang gefoltert, konnten ihm aber nur Schreie und irres Gel\x84""chter entlocken. Es nahm sein Geheimnis mit ins Grab.",
  "Ani obc\x91gi, ani topory nie zmusi\x92y wi\x91\xA6nia osadzonego na %s do gadania. To wyj\x86tkowo twarda sztuka, prze\xA7y\x92 najbardziej wyszukane tortury zadawane przez Twoich kat\xA2w.",
  "Neither pliers nor axe could make him talk. He survived even the most sophisticated tortures that they had inflicted on him.",
  "Weder die eisernen Zangen noch die Axt konnten ihn zum Reden bringen. Nicht einmal die schlimmsten Foltermethoden brachten ihn um."
};

char *g_PrisonerTortureEnemyStackRevealTexts[9] =
{
  "Kaci byli bardzo zadowoleni z dobrze spe\x92nionego obowi\x86zku. Od wi\x91\xA6nia osadzonego na %s wydobyli informacj\x91 o po\x92o\xA7""eniu jednej z wrogich jednostek.",
  "Persecutors were very pleased with what they had done. They had got all information about the enemy's units from the tortured victim in the castle of %s.",
  "Die Vollstrecker waren sehr zufrieden mit dem Ergebnis ihrer Arbeit. Sie hatten ihrem Opfer auf Burg %s alle Informationen \x81""ber die feindlichen Einheiten entrei\xE1\x65\x6E k\x94nnen.",
  "Kaci ca\x92\x86 noc zn\x91""cali si\x91 nad wyznaczonym  w %s wi\x91\xA6niem, ale ten tylko krzycza\x92 i \x9Emia\x92 si\x91 na przemian. Skona\x92 z imieniem swej ukochanej na ustach.",
  "Persecutors were torturing the victim all night long in the castle of %s but he only screamed and laughed. With his last breath he took his secret with him.",
  "Auf Burg %s haben Deine Vollstrecker ihr Opfer die ganze Nacht lang gefoltert, konnten ihm aber nur Schreie und irres Gel\x84""chter entlocken. Es nahm sein Geheimnis mit ins Grab.",
  "Ani obc\x91gi, ani topory nie zmusi\x92y wi\x91\xA6nia osadzonego na %s do gadania. To wyj\x86tkowo twarda sztuka, prze\xA7y\x92 najbardziej wyszukane tortury zadawane przez Twoich kat\xA2w.",
  "Neither pliers nor axe could make him talk. He survived even the most sophisticated tortures that they had inflicted on him.",
  "Weder die eisernen Zangen noch die Axt konnten ihn zum Reden bringen. Nicht einmal die schlimmsten Foltermethoden brachten ihn um."
};

char *g_PrisonerTortureNoConfessionDeathTexts[6] =
{
  "Kaci ca\x92\x86 noc zn\x91""cali si\x91 nad wyznaczonym  w %s wi\x91\xA6niem, ale ten tylko krzycza\x92 i \x9Emia\x92 si\x91 na przemian. Skona\x92 z imieniem swej ukochanej na ustach.",
  "Persecutors were torturing the victim all night long in the castle of %s but he only screamed and laughed. With his last breath he took his secret with him.",
  "Auf Burg %s haben Deine Vollstrecker ihr Opfer die ganze Nacht lang gefoltert, konnten ihm aber nur Schreie und irres Gel\x84""chter entlocken. Es nahm sein Geheimnis mit ins Grab.",
  "Ani obc\x91gi, ani topory nie zmusi\x92y wi\x91\xA6nia osadzonego na %s do gadania. To wyj\x86tkowo twarda sztuka, prze\xA7y\x92 najbardziej wyszukane tortury zadawane przez Twoich kat\xA2w.",
  "Neither pliers nor axe could make him talk. He survived even the most sophisticated tortures that they had inflicted on him.",
  "Weder die eisernen Zangen noch die Axt konnten ihn zum Reden bringen. Nicht einmal die schlimmsten Foltermethoden brachten ihn um."
};

char *g_PrisonerTortureResistanceTexts[3] =
{
  "Ani obc\x91gi, ani topory nie zmusi\x92y wi\x91\xA6nia osadzonego na %s do gadania. To wyj\x86tkowo twarda sztuka, prze\xA7y\x92 najbardziej wyszukane tortury zadawane przez Twoich kat\xA2w.",
  "Neither pliers nor axe could make him talk. He survived even the most sophisticated tortures that they had inflicted on him.",
  "Weder die eisernen Zangen noch die Axt konnten ihn zum Reden bringen. Nicht einmal die schlimmsten Foltermethoden brachten ihn um."
};

_UNKNOWN g_SpecialPersonageLeaveMaskTemplate;

char *g_PrisonerBriberyDefectionTexts[6] =
{
  "Osadzony w zamku %s wi\x91zie\xA4 skuszony zaoferowanym przez Ciebie z\x92otem zdradzi\x92 swego w\x92""adc\x91 i stan\x86\x92 po Twojej stronie.",
  "Kept in a castle %s he was talked into joining your army, lured with gold. He betrayed his own troops.",
  "Der Gefangene auf Burg %s wurde mit Gold bestochen, in Deine Armee einzutreten, und verriet seine eigenen Truppen.",
  "W zamku %s zmar\x92 z wyczerpania jeden z wiezni\xA2w.",
  "One of the convicts died in pain in the castle.",
  "Auf der Burg %s starb einer der Gefangenen unter Schmerzen."
};

char *g_PrisonerDeathByExhaustionTexts[3] =
{
  "W zamku %s zmar\x92 z wyczerpania jeden z wiezni\xA2w.",
  "One of the convicts died in pain in the castle.",
  "Auf der Burg %s starb einer der Gefangenen unter Schmerzen."
};

__int16 g_PrisonerRowBarTopYTable[] = { 0 };

__int16 g_PrisonerRowBarBottomYTable[] = { 16 };

__int16 g_PrisonerRowTextXTable[] = { 11 };

_DWORD g_PrisonerActionButtonWidgets[2] = { 92, 362 };

int g_PrisonerActionButtonState0 = 1;

int g_PrisonerActionButtonState1 = 1;

int g_PrisonerActionButtonState2 = 1;

int g_PrisonerActionButtonState3 = 1;

int g_PrisonerActionButtonState4 = 1;

int g_PrisonerActionButtonState5 = 1;

int g_PrisonerActionButtonState6 = 1;

int g_PrisonerActionButtonState7 = 1;

int g_PrisonerActionButtonState8 = 1;

char *g_QueenRelationshipStateTexts[30] =
{
  "Nie ma kr\xA2lowej.",
  "No queen.",
  "Keine K\x94nigin",
  "Twa ma\x92\xA7onka jest w\x9E""ciek\x92""a i nie ma ochoty widywa\x8D si\x91 z Tob\x86. Dusza kobiety nie pozwala jej d\x92u\xA7""ej znosi\x8D takiego zachowania. Ma niecne plany wobec Twej osoby.",
  "Your wife is furious and she does not want to see you. Her feminine soul can't bear your strange behaviour any longer. She schemes against you.",
  "Deine Frau ist w\x81tend und weigert sich, Dich zu sehen. Ihre weibliche Seele kann Dein eigenartiges Benehmen nicht l\x84nger ertragen. Sie intrigiert gegen Dich.",
  "Kr\xA2lowa jest z\x92""a i wielce znudzona Tw\x86 postaw\x86, ma ochot\x91 wr\xA2""ci\x8D za morze do swego ojca.",
  "The Queen is angry and bored with your actions. She considers going back to her parents.",
  "Die K\x94nigin ist ver\x84rgert und hat Dein Benehmen satt. Sie spielt mit dem Gedanken, in ihr Elternhaus zur\x81""ckzukehren.",
  "Kr\xA2lowa jest zaniepokojona Twym zachowaniem, s\x86""dzi \xA7""e to ma\x92\xA7""e\xA4stwo nie ma przysz\x92o\x9E""ci.",
  "The Queen is concerned about the future of your marriage. Your behaviour puzzles her.",
  "Die K\x94nigin ist besorgt \x81""ber die Zukunft eurer Ehe. Dein seltsames Benehmen verwirrt sie.",
  "Ma\x92\xA7onka pozostaje Ci wierna jednak dowody Twej mi\x92o\x9E""ci s\x86 niewystarczaj\x86""ce.",
  "Your wife remains faithful but proofs of your love do not satisfy her.",
  "Deine Frau bleibt Dir treu, doch Deine Liebesbeweise k\x94nnen sie nicht \x81""berzeugen.",
  "Kr\xA2lowa czuje si\x91 dobrze i wiernie Ci s\x92u\xA7y jednak nie jest pewna swych uczu\x8D do Ciebie.",
  "The Queen is well and is willing to serve you, but she is not certain of her feelings towards you.",
  "Die K\x94nigin ist ausgeglichen und bereit, Dir zu dienen, doch ist sie sich unsicher \x81""ber ihre Gef\x81hle f\x81r Dich.",
  "Twa \xA7ona wdzi\x91""czna jest ojcu, \xA7""e wybra\x92 jej takiego m\x91\xA7""a. Staraj si\x91 pog\x92\x91""bi\x8D jej uczucie do Ciebie.",
  "Your wife is grateful to her father for choosing you as her husband. Try to deeper her love for you.",
  "Deine Frau ist ihrem Vater dankbar daf\x81r, da\xE1\x20\x65r Dich zu ihrem Ehemann gew\x84hlt hat. Versuche, ihr Herz zu gewinnen.",
  "Od s\x92u\xA7""ek dowiedzia\x92""e\x9E si\x91, \xA7""e kr\xA2lowa bardzo ciep\x92o wyra\xA7""a si\x91 na temat Twojej osoby.",
  "You heard from her maids that the queen speaks with reverence about you.",
  "Die Dienerinnen Deiner Frau berichten Dir, da\xE1\x20\x64ie K\x94nigin mit Bewunderung von Dir spricht.",
  "Przy wieczornych ucztach zdo\x92""a\x92""e\x9E zauwa\xA7y\x8D, \xA7""e kr\xA2lowa wykazuje coraz wi\x91ksze zainteresowanie Tob\x86 nie tylko jako m\x91\xA7""em ale i m\x91\xA7""czyzn\x86. Oby tak dalej.",
  "You have noticed that the Queen started expressing her strong interest in you as a man, not only her chosen husband. Right on.",
  "Du bemerkst, da\xE1\x20\x64ie K\x94nigin Interesse an Dir als Mann zeigt - nicht nur als ihrem ausgew\x84hlten Ehegatten. Weiter so.",
  "Kr\xA2lowa jest wniebowzi\x91ta. Pragnie codzie\xA4 dzieli\x8D z Tob\x86 \x92o\xA7""e i da\x8D Ci potomka.",
  "The Queen is in heaven. She wants to give you a baby.",
  "Die K\x94nigin ist im siebten Himmel. Sie will ein Kind von Dir."
};

char *g_AllyEliminatedNoticeTexts[3] =
{
  "Gracz %s podda\x92 si\x91.",
  "Player %s surrended.",
  "Spieler %s hat sich ergeben."
};

unsigned __int16 g_InGameSliderThumbPositions[6] = { 325u, 0u, 475u, 0u, 127u, 0u };

int g_OptionsInGameMusicVolumeRaw = 128;

int g_OptionsInGameScrollSpeedRaw = 128;

int g_OptionsInGameSoundVolumeRaw = 128;

_UNKNOWN g_InGameSettingsButtonWidgetsTemplate;

char *g_CheatTable = "VH[S^]";

int (*g_CheatCodeHandlerTable)() = &Cheat_FillSelectedSquadWithCannons;

char *g_CheatCodeStringTable = "[_\\]FP^[\\V";

int g_RulesArmyFactCreatedCount = 0;

__int16 g_DeviceRectTargetWidth = 320;

__int16 g_DeviceRectTargetHeight = 240;

__int16 g_DeviceRectLastWidth = 320;

__int16 g_RenderCursor_TweenPrevY = 240;

int g_DemoScript_TriggerTickTable[] = { 1 };

int g_DemoScript_MessageIdTable[] = { 149 };

int g_CursorDesc_Default[10] = { 2, 2, 0, 0, 0, 0, 0, 0, 0, 0 };

int g_CursorDesc_ActionBusy[10] = { 3, 3, 0, 0, 0, 0, 0, 0, 0, 0 };

int g_CursorDesc_Attack[10] = { 4, 4, 0, 0, 0, 19, 20, 0, 0, 0 };

int g_CursorDesc_GoTo[10] = { 5, 5, 0, 0, 0, 19, 20, 0, 0, 0 };

int g_CursorDesc_Blocked[10] = { 10, 10, 0, 0, 0, 0, 0, 0, 0, 0 };

int g_CursorDesc_Busy[10] = { 12, 26, 10, 0, 0, 0, 0, 0, 0, 0 };

int g_CursorDesc_EnterSite[10] = { 31, 38, 10, 0, 0, 19, 20, 0, 0, 0 };

int g_CursorDesc_CannotSelect[10] = { 39, 39, 0, 0, 0, 19, 20, 0, 0, 0 };

int g_CursorDesc_VisitBuilding[10] = { 40, 40, 0, 0, 0, 19, 20, 0, 0, 0 };

int g_CursorDesc_CannotAttack[10] = { 41, 41, 0, 0, 0, 0, 0, 0, 0, 0 };

int g_CursorDesc_DeliverCargo[10] = { 42, 42, 0, 0, 0, 19, 20, 0, 0, 0 };

int g_CursorDesc_CannotEnter[10] = { 43, 50, 10, 0, 0, 19, 20, 0, 0, 0 };

int g_CursorDesc_SelectedUnitHover[10] = { 51, 51, 0, 0, 0, 0, 0, 0, 0, 0 };

char aDefault_rec[12] = "default.rec";

char g_Input_ScanCodeChars_TopRow[2] = { 'o', 'r' };

char g_Input_ScanCodeChars_HomeRow[2] = { 'd', 'e' };

char g_Input_ScanCodeChars_BottomRow[17] =
{
  'r',
  '$',
  '$',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  'q',
  'w',
  'e',
  'r',
  't'
};

char g_KeyChar = 'y';

char g_Input_ScanCodeChar_LangSwap = 'z';

char g_Input_ScanCodeChars_NumberRow[] = { '\0' };

int g_Input_KeyRepeatCount = 1;

int g_AppIsActive = 1;

char *g_UI_CdMissingMessageByLanguage[3] =
{
  "Wloz plyte z gra do napedu!",
  "Clash CD not found!",
  "Clash CD nicht gefunden"
};

_DWORD g_Device_DefaultWindowRect[4] = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

int g_Palette_ActivePalettePtr = 268572261;

int g_Palette_BlendRatio = 34894308;

char g_Palette_ColorCubeBits = '\x05';

int (*g_AviDecompressor_PixelCopyFnTable[7])() =
{
  &CAviDecompressor_ConvertRGB888to565Row,
  (int (*)())0xFF0000,
  (int (*)())0xFF00,
  (int (*)())0xFF,
  (int (*)())0xF800,
  (int (*)())0x7E0,
  (int (*)())0x1F
};

int g_Audio_VoiceMixSampleStep = 0;

int g_Audio_CurrentVoiceRecordPtr = 0;

int g_Audio_MixVoice_LoopBoundLow = 0;

int g_Audio_MixVoice_LoopBoundHigh = 0;

int g_Audio_MixVoice_LoopMode = 0;

int g_Audio_MixVoice_LoopDirection = 0;

int g_Audio_MixVoice_LoopBoundsSwitchPending = 0;

int g_Audio_MixVoice_LoopFinalFlag = 0;

int g_Audio_MixVoice_SamplesRemaining = 0;

int g_Audio_MixVoice_AccumBufferPtr = 0;

int g_Audio_MixVoice_ResampleStep = 0;

int g_Audio_MixVoice_MaxSourceAdvance = 0;

int g_Audio_MixVoice_PositionInt = 0;

int g_Audio_MixVoice_PositionFrac = 0;

int (__fastcall *g_Audio_MixVoice_MixFunc)(_DWORD, _DWORD) = NULL;

int g_Audio_MixFormatDispatchTable = 0;

int g_Audio_MixVoice_Pan = 0;

int g_Audio_MixVoice_PanStepFracArg = 0;

int g_Audio_MixVoice_StepIntArg = 0;

int g_Audio_MixVoice_ChannelIndexArg = 0;

int (__cdecl *g_Audio_MixVoice_LoopCallback)(_DWORD) = NULL;

char g_Audio_MixVoice_LeftVolume = '\0';

char g_Audio_MixVoice_RightVolume = '\0';

int g_Audio_MixVoice_SampleHistory0 = 0;

int g_Audio_MixVoice_SampleHistory1 = 0;

int g_Audio_MixVoice_LeftVolumeStep = 0;

int g_Audio_MixVoice_RightVolumeStep = 0;

int g_Audio_MixVoice_NextChunkEndScratch = 0;

int g_CSS_NullDriverMasterVolume = 0;

_UNKNOWN g_CSS_NullDriverSentinel;

int g_CSS_ChannelPriorityWeightTable[] = { 0 };

int g_CSS_MemSoundStealBias = 0;

int g_CSS_SampleVoiceStealBias = 1073741824;

int g_CSS_StreamVoiceStealBias = 1073741824;

int g_CSS_StreamServiceRateHz = 10;

int g_CSS_VoiceSequenceCounter = 1;

int g_CSS_MixUpdateRateHz = 30;

int g_CSS_DSoundAccelDetectEnabled = 1;

void *g_CSS_DriverDescriptorTable = &g_Audio_DriverModuleTableBase;

int g_CSS_DeviceHandleCache_DriverIndex = -1;

int g_CSS_DeviceHandleCache_Param1 = -1;

int g_CSS_DeviceHandleCache_Param2 = -1;

int g_CSS_DeviceHandleCacheParam3 = -1;

int g_CSS_DeviceHandleCacheParam4 = -1;

int g_CSS_SoundDescriptorRingIndex = 0;

int g_CSS_FormatShiftTable[] = { 0 };

int g_CSS_FormatSampleSizeTable[7] = { 0, 1, 2, 2, 4, 1, 2 };

int g_CSS_FormatSilenceValueTable[8] = { 0, 128, 0, 128, 0, 0, 0, 0 };

int (__fastcall *g_CRT_ExitFinalizerCallbackA)(_DWORD, _DWORD) = &Noop_CrtExitHandlerPair;

int (__cdecl *g_CRT_ExitFinalizerCallbackB)(_DWORD) = &Noop_CrtExitHandlerPair;

int g_Mem_TotalAllocatedBytes = 0;

int g_Mem_TotalAllocationCount = 0;

int g_Mem_AllocFlag = 0;

int g_Mem_ReservedBlockListHead = 0;

int g_Mem_PoolInitializedFlag = 0;

signed int (*g_Mem_OutOfMemoryHandler)() = &Mem_FatalOutOfMemory;

int g_CRT_HeapSegmentListHead = 0;

char g_Str_RadixDigitCharacters[] = { '0' };

char g_FileSystem_CwdBufferSentinel[] = { '\0' };

char g_FileSystem_CurrentDirectoryBuffer[116] =
{
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0'
};

int g_Rules_FactListChangedFlag = 0;

void *g_Rules_DummyFactPtr = &g_Rules_FactPatternEntityRecord;

int g_Rules_WatchFactsFlag = 0;

int g_Rules_GarbageFactListHead = 0;

int g_Rules_LastFactPointer = 0;

int g_Rules_FactListHead = 0;

int g_Rules_NextFactIndex = 0;

int g_Rules_InstalledFactCount = 0;

int g_Rules_LastFactModuleCache = -1;

int g_Rules_ClearInProgressFlag = 0;

int g_Rules_ResetInProgressFlag = 0;

int g_Rules_SaveFunctionListHead = 0;

int g_Rules_LoadInProgressFlag = 0;

int g_Rules_WatchCompilationsFlag = 1;

int g_Rules_ConstructTypeListHead = 0;

int g_Rules_ResetFunctionListHead = 0;

int g_Rules_ClearFunctionListHead = 0;

int g_Rules_ClearReadyFunctionListHead = 0;

int g_Rules_ReentryGuardFlag = 0;

int (*g_Rules_BeforeResetCallback)(void) = NULL;

int g_Rules_FactsBloadedFlag = 0;

int g_Rules_BeforeBloadFunctionListHead = 0;

int g_Rules_AfterBloadCallbackListHead = 0;

int g_Rules_BloadClearReadyCallbackListHead = 0;

int g_Rules_AbortBloadCallbackListHead = 0;

void *g_Rules_BloadFileHeaderID = &g_CLIPS_BsaveHeaderMagic;

char *g_Rules_BsaveVersionID = "V6.00";

int (*g_Rules_SystemCommandPostShellHookB)(void) = NULL;

int (*g_Rules_SystemCommandPreShellHook)(void) = NULL;

int (*g_Rules_SystemCommandPostShellHookA)(void) = NULL;

int g_Rules_EngineInitializedFlag = 0;

int g_Rules_ConflictResolutionStrategy = 0;

int g_Rules_WatchActivationsFlag = 0;

int g_Rules_ActivationCount = 0;

int g_Rules_ActivationSequenceCounter = 0;

int g_Rules_AgendaChangedFlag = 0;

int g_Rules_SalienceEvaluationMode = 0;

int g_Rules_CurrentlyExecutingRule = 0;

int g_Rules_HaltRulesFlag = 0;

int g_Rules_CurrentLogicalJoin = 0;

int g_Rules_PostRuleFireCallbackListHead = 0;

int g_Rules_FocusStackTop = 0;

int g_Rules_FocusStackChangedFlag = 0;

int g_Rules_WatchStatisticsFlag = 0;

int g_Rules_WatchFocusFlag = 0;

int g_Rules_AgendaLoopRunningFlag = 0;

void *g_Instance_DummyInstanceRecord = g_Rules_ObjectPatternVTable;

int g_Rules_HostFunctionListHead = 0;

_DWORD g_Rules_EphemeralSymbolListHead = 0;

_DWORD g_Rules_EphemeralFloatListHead = 0;

_DWORD g_Rules_EphemeralIntegerListHead = 0;

_DWORD g_Rules_EphemeralBitmapListHead = 0;

int g_Instance_HashTableBase = 0;

int g_Instance_SlotInitInProgress = 0;

int g_Instance_PurgeInProgress = 0;

int g_Instance_UseMessageDispatchForInit = 1;

int g_Instance_InstancesChangedFlag = 0;

int g_Instance_DeletedListHead = 0;

_DWORD g_Rules_ObjectPatternVTable[11];

_UNKNOWN g_IO_FileGetcSentinelAddr;

char g_IO_FileGetcStreamFlags = '\x01';

_UNKNOWN g_CRT_StdoutStream;

_UNKNOWN g_CRT_StderrOutputStream;

int g_CRT_DefaultFileTranslationMode = 256;

DWORD dwTlsIndex = 4294967295u;

__int64 (__fastcall *g_CrtThreadDataAccessor)(_DWORD, _DWORD) = &CRT_GetBootstrapThreadData;

int (__thiscall *g_CRT_FileHandleLockAcquireHook)(_DWORD) = &Noop_CrtSingleThreadLockStub;

int (__fastcall *g_CRT_FileHandleLockReleaseHook)(_DWORD, _DWORD) = &Noop_CrtSingleThreadLockStub;

_DWORD (*g_CRT_AddFileHandleHook)() = &j___NTAddFileHandle_;

int (*g_CRT_FileHandleRemoveHookTable[14])() =
{
  &j___NTRemoveFileHandle_,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub
};

_DWORD (*g_CRT_StaticLock1AcquireHook)() = &Noop_CrtSingleThreadLockStub;

_DWORD (*g_CRT_StaticLock1ReleaseHook)() = &Noop_CrtSingleThreadLockStub;

_DWORD (*g_CRT_StaticLock2AcquireHook)() = &Noop_CrtSingleThreadLockStub;

int (*g_CRT_StaticLock3AcquireHookTable[10])() =
{
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub
};

_DWORD (*g_CRT_StaticLock2ReleaseHook)() = &Noop_CrtSingleThreadLockStub;

int (*g_CRT_StaticLock3ReleaseHookTable[8])() =
{
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub
};

int (*g_CRT_StaticLock4AcquireHookTable[7])() =
{
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub,
  &Noop_CrtSingleThreadLockStub
};

int (*g_CRT_StaticLock4ReleaseHookTable[6])() = { &Noop_CrtSingleThreadLockStub, &Noop_CrtSingleThreadLockStub, &Noop_CrtSingleThreadLockStub, &Noop_CrtSingleThreadLockStub, &Noop_CrtSingleThreadLockStub, &Noop_CrtSingleThreadLockStub };

int (*g_CRT_ThreadDataConstructHookTable[5])() = { &Noop_CrtSingleThreadLockStub, &Noop_CrtSingleThreadLockStub, &Noop_CrtSingleThreadLockStub, &Noop_CrtSingleThreadLockStub, &Noop_CrtSingleThreadLockStub };

int (*g_CRT_ThreadDataDestroyHookTable[4])() = { &Noop_CrtSingleThreadLockStub, &Noop_CrtSingleThreadLockStub, &Noop_CrtSingleThreadLockStub, &Noop_CrtSingleThreadLockStub };

_DWORD (*g_CRT_TlsIndexDestroyHook)() = &Noop_CrtSingleThreadLockStub;

_DWORD (*g_CRT_ThreadStartupHook)() = &Noop_CrtSingleThreadLockStub;

int (__cdecl *g_CRT_ThreadEndHook)(_DWORD, _DWORD) = &Noop_CrtSingleThreadLockStub;

int (__fastcall *g_CRT_ProcessExitThreadHook)(_DWORD, _DWORD) = NULL;

int (*g_CRT_CustomReadAvailablePredicateHook)(void) = NULL;

int (__cdecl *g_CRT_ConsoleOpenHook)(_DWORD, _DWORD, _DWORD) = NULL;

int (*g_CRT_CustomReadHook)(void) = NULL;

int (*g_CRT_ExitProcessFinalizerHook)(void) = NULL;

int g_Print_PreserveEscapedCharactersFlag = 0;

int g_Print_AddressesToStringsFlag = 0;

int g_Print_InstanceAddressesToNamesFlag = 0;

int g_IO_RouterListHead = 0;

int g_IO_FastLoadFilePtr = 0;

int g_IO_FastSaveFilePtr = 0;

char *g_IO_LogicalNameTable_WWarning[6] = { "wwarning", "werror", "wtrace", "wdialog", "wclips", "wdisplay" };

char *g_IO_LogicalNameTable_WError[5] = { "werror", "wtrace", "wdialog", "wclips", "wdisplay" };

char *g_IO_LogicalNameTable_WTrace[4] = { "wtrace", "wdialog", "wclips", "wdisplay" };

char *g_IO_LogicalNameTable_WDialog[3] = { "wdialog", "wclips", "wdisplay" };

char *g_IO_LogicalNameTable_WClips[2] = { "wclips", "wdisplay" };

char *g_IO_LogicalName_WDisplay = "wdisplay";

int g_Lexer_PendingLineCharIndex = -1;

int (*g_CRT_LockEnterHookTable[3])() = { &Noop_CrtLockEnterLeaveResetStub, &Noop_CrtLockEnterLeaveResetStub, &Noop_CrtLockEnterLeaveResetStub };

int (*g_CRT_LockLeaveHookTable[2])() = { &Noop_CrtLockEnterLeaveResetStub, &Noop_CrtLockEnterLeaveResetStub };

int (__fastcall *g_CRT_LockSlotResetHook)(_DWORD, _DWORD) = &Noop_CrtLockEnterLeaveResetStub;

__int16 g_FatalRuntimeErrorOnceGuard = 0;

int g_CrtFinalizerListHead = 0;

int g_CRT_DefaultCommitMode = 0;

int g_CRT_MaxFileDescriptor = 20;

LPSTR lpCmdLine = NULL;

int g_CRT_ExecutablePathA = 0;

int g_CRT_ModulePathA = 0;

int g_CRT_WideCommandLine = 0;

int g_CRT_ExecutablePathW = 0;

int g_CRT_ModulePathW = 0;

_UNKNOWN g_CRT_StartupThreadDataBlock;

int g_CRT_EnvironmentStringsPtr = 0;

int g_WindowsVersionDword = 0;

int g_CRT_OsBuildNumber = 0;

int g_CRT_WinMajorVersion = 0;

int g_CRT_WinMinorVersion = 0;

int g_CRT_WinVersion = 0;

int (*g_CRT_InitHookPtr)() = &Noop_CrtIoInitHook;

_UNKNOWN g_Rules_FactPatternEntityRecord;

int g_Rules_FactDuplicationEnabled = 0;

int g_CLIPS_PeriodicFunctionListHead = 0;

int g_Rules_PeriodicFunctionListHead = 0;

int g_ClipsEphemeralItemCount = 0;

int g_ClipsEphemeralItemBytes = 0;

int g_Rules_EphemeralCountGCThreshold = 1000;

int g_Rules_EphemeralSizeThreshold = 10240;

int g_Rules_LastCleanupEvalDepth = -1;

int g_Rules_DeftemplateWatchFlag = 0;

int g_WatchItemListHead = 0;

int g_ClipsEphemeralMultifieldListHead = 0;

int g_Rules_JoinOperationInProgress = 0;

int g_ClipsPendingDependencyDestructorList = 0;

int g_Rules_FlushingDependencyDestructors = 0;

int g_ClipsCurrentExpression = 0;

int g_ClipsEvaluationError = 0;

int g_ClipsHaltExecution = 0;

int g_ClipsCurrentEvaluationDepth = 0;

int g_ClipsDeferredJoinDriveListHead = 0;

int g_PartialMatchFreeListHead = 0;

int g_ReteGarbageAlphaMatchList = 0;

int g_ClipsCommandEvalInProgress = 0;

int g_Lexer_PendingTokenBuffer = 0;

int g_Lexer_TokenBufferCapacity = 0;

int g_Rules_EvaluatingTopLevelCommand = 0;

int (*g_CLIPS_AfterPromptCallback)(void) = NULL;

int g_Rules_EntityTimeTagCounter = 0;

int g_Module_ItemListTail = 0;

int g_CLIPS_AfterModuleChangeListHead = 0;

int g_Module_SavedEnumStackTop = 0;

int g_Module_ChangeNotifyEnabled = 1;

int g_DefmoduleListHead = 0;

int g_Clips_CurrentModule = 0;

int g_ClipsDefmoduleListTail = 0;

int g_ClipsModuleItemCount = 0;

int g_ModuleItemDescriptorListHead = 0;

int g_Module_ChangeGeneration = 0;

int g_Module_MainRedefinable = 1;

int g_StringRouterListHead = 0;

EvalNodeDescriptor g_EvalDescriptor_Deftemplate = { 35, 0x20, { 0 }, 0, { 0 } };

int g_ExpressionHashTable = 0;

int g_TokenBuf = 0;

int g_TokenLen = 0;

int g_TokenCap = 0;

int g_Lexer_SuppressEofError = 0;

int g_Rules_PPBufferEnabled = 0;

int g_Rules_PPIndentDepth = 0;

int g_PPBufferLength = 0;

int g_ClipsPPBufferMax = 0;

int g_ClipsPPBackupOnce = 0;

int g_Rules_PPBackupTwicePos = 0;

int g_Clips_PPBuffer = 0;

int g_Rules_BloadSymbolCount = 0;

int g_BloadFloatTableCount = 0;

int g_BloadIntegerTableCount = 0;

int g_Rules_BloadBitmapCount = 0;

int g_BinaryItemListHead = 0;

int g_ClipsConstructQueueHead = 0;

int g_CLIPS_StaticConstraintCheckingFlag = 1;

int g_CLIPS_DynamicConstraintCheckingFlag = 0;

_UNKNOWN g_EvalDescriptor_Defgeneric;

int g_Rules_WatchDeffunctions = 0;

_UNKNOWN g_EvalDescriptor_Deffunction;

int g_Defglobal_ChangedFlag = 0;

EvalNodeDescriptorCompact g_CLIPS_DefglobalEvalNodeDescriptor = { 0x0000000D };

EvalNodeDescriptorCompact g_Defglobal_PtrEntityRecord = { 0x0000003C };

_UNKNOWN g_EvalDescriptor_Defclass;

int g_ClipsProcParamArray = 0;

int g_ClipsProcParamCount = 0;

int g_Clips_ProcParamArgChain = 0;

int g_ProcParamSavedFrameStack = 0;

int g_ClipsProcParamWildcardValue = 0;

int g_ClipsProcFrameDataObjectArray = 0;

int (*g_ProcParam_ErrorContextCallback)(void) = NULL;

EvalNodeDescriptor g_EvalDescriptor_ProcArgument = { 65, 0x40, { 0 }, (void *)ProcParam_GetArgumentValue, { 0 } };

EvalNodeDescriptor g_EvalDescriptor_ProcWildcardArgument = { 66, 0x40, { 0 }, (void *)ProcParam_GetWildcardArgumentValue, { 0 } };

EvalNodeDescriptor g_EvalDescriptor_ProcBoundVariable = { 67, 0x40, { 0 }, (void *)ProcParam_GetBoundVariableValue, { 0 } };

EvalNodeDescriptor g_EvalDescriptor_ProcBindLocalVariable = { 68, 0x40, { 0 }, (void *)ProcParam_BindLocalVariable, { 0 } };

int g_ProcParamCachedWildcardArgIndex = -1;

int g_DribbleFileHandle = 0;

int g_DribbleBufferLength = 0;

int g_Dribble_BufferCapacity = 0;

int (__thiscall *g_Dribble_StatusChangeCallback)(_DWORD) = NULL;

int g_CurrentStringInputSource = 0;

int g_BatchEchoBufferLength = 0;

int g_ClipsBatchLineBufferCapacity = 0;

int g_Rules_BatchStackTop = 0;

int g_Batch_ListTail = 0;

int g_Dribble_LineStartNeedsTimestamp = 1;

__int64 g_ClipsHaltExecutionFlag = 0LL;

int g_LoopForCountBindingStack = 0;

int g_BoundVariableList = 0;

int g_ClipsGensymCounter = 1;

int g_Rules_AutoFloatDividendEnabled = 1;

int g_PrognFieldBindingStack = 0;

int g_EvalStringRouterCounter = 0;

int g_HelpLoadedTopicFileList = 0;

int g_ClipsHelpCurrentTopicNode = 0;

int g_HelpSystemInitialized = 0;

int g_ClipsHelpFilePath = 0;

int g_ClipsCodeMaxIndicesPerArray = 2000;

int g_CodeGeneratorItemList = 0;

int g_Rules_CodeGeneratorItemIndex = 0;

int g_Clips_CurrentPartialMatch = 0;

int g_Rules_GlobalRHSBinds = 0;

int g_CurrentPatternEntityPtr = 0;

int g_WatchRulesFlag = 0;

int g_Clips_InstanceListHead = 0;

int g_Rules_ActiveInstanceCount = 0;

int g_ClipsInstanceUnderConstruction = 0;

int g_Instance_GlobalListTail = 0;

int g_InstanceDirectMessageGuardActive = 0;

_UNKNOWN g_Runtime_CompactEvalClipsSignature[] = { 5, 6, 7, 'C', 'L', 'I', 'P', 'S', 0, 0 };

void *g_Bload_SignaturePtr = g_Runtime_CompactEvalClipsSignature;

char *g_Bload_VersionString = "V6.00";

int g_ClipsBloadReadBuffer = 0;

int g_Clips_BloadBufferSize = 0;

int g_BloadReadBufferOffset = 0;

int g_MessageHandler_InitSymbol = 0;

int g_ClipsDeleteMessageSymbol = 0;

char *g_MessageHandlerTypeNames[4] = { "around", "before", "primary", "after" };

char *g_MessageHandler_PrimaryAfterTypeNames[2] = { "primary", "after" };

int g_Rules_WatchMessageHandlers = 0;

int g_MessageHandler_WatchMessages = 0;

int g_CurrentMessageHandler = 0;

int g_ClipsCurrentHandlerCore = 0;

int g_MessageHandler_CurrentDispatchCore = 0;

int g_ClipsMessageHandlerCursor = 0;

int g_ClipsDefclassIdTable = 0;

int g_DefclassHashTable = 0;

__int16 g_ClipsDefclassIdCount = 0;

int g_Defclass_SlotNameHashTablePtr = 0;

int g_Rules_WatchInstances = 0;

int g_Class_WatchSlots[] = { 0 };

int g_ClipsPrimitiveTypeClassMap[] = { 0 };

int g_ClipsIntegerClass = 0;

int g_ClipsSymbolClass = 0;

int g_ClipsStringClass = 0;

int g_ClipsMultifieldClass = 0;

int g_ClipsExternalAddressClass = 0;

int g_ClipsFactAddressClass = 0;

int g_Class_InstanceAddress = 0;

int g_Class_InstanceName = 0;

char g_Class_TraversalIDCounter = '\0';

char IsTable[256] =
{
  '\0',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x03',
  '\x03',
  '\x03',
  '\x03',
  '\x03',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\x01',
  '\n',
  '\f',
  '\f',
  '\f',
  '\f',
  '\f',
  '\f',
  '\f',
  '\f',
  '\f',
  '\f',
  '\f',
  '\f',
  '\f',
  '\f',
  '\f',
  '8',
  '8',
  '8',
  '8',
  '8',
  '8',
  '8',
  '8',
  '8',
  '8',
  '\f',
  '\f',
  '\f',
  '\f',
  '\f',
  '\f',
  '\f',
  'X',
  'X',
  'X',
  'X',
  'X',
  'X',
  'H',
  'H',
  'H',
  'H',
  'H',
  'H',
  'H',
  'H',
  'H',
  'H',
  'H',
  'H',
  'H',
  'H',
  'H',
  'H',
  'H',
  'H',
  'H',
  'H',
  '\f',
  '\f',
  '\f',
  '\f',
  '\f',
  '\f',
  '\x98',
  '\x98',
  '\x98',
  '\x98',
  '\x98',
  '\x98',
  '\x88',
  '\x88',
  '\x88',
  '\x88',
  '\x88',
  '\x88',
  '\x88',
  '\x88',
  '\x88',
  '\x88',
  '\x88',
  '\x88',
  '\x88',
  '\x88',
  '\x88',
  '\x88',
  '\x88',
  '\x88',
  '\x88',
  '\x88',
  '\f',
  '\f',
  '\f',
  '\f',
  '\x01',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0',
  '\0'
};

int g_ClipsObjectMatchQueueHead = 0;

int g_Rules_ObjectPatternNetworkRoot = 0;

int g_ReactiveRuleListHead = 0;

int g_Rules_ObjectMatchDelayFlag = 0;

int g_RuleTraversalMarkCounter = 0;

int g_Rules_ObjectMatchTimeTag = 0;

char g_BitPositionMaskTable[8] = { '\x01', '\x02', '\x04', '\b', '\x10', ' ', '@', '\x80' };

int g_CRT_OsHandleTable = 0;

int (__fastcall *g_CRT_ExceptionHandlerCallback)(_DWORD, _DWORD) = NULL;

int (*g_FpuExceptionResignalFn)(void) = NULL;

char g_HexDigitCharTable[] = { '0' };

int g_IO_LogicalNameFileListHead = 0;

int g_CRT_ThreadDataBlockSize = 244;

int (*g_FloatEfgFormatFn)() = &_no_support_loaded;

int (__fastcall *g_StringToDoubleScanFn)(_DWORD, _DWORD) = &_no_support_loaded;

int g_CRT_OpenModeStripMask = 0;

_DWORD g_CRT_TzDstStartRule[9] = { 0, 0, 2, 1, 3, 0, 0, 0, 0 };

int g_CRT_TzDstEndRule = 0;

int g_CRT_TzDstEndRuleMinute = 0;

int g_CRT_TzDstEndRuleHour = 1;

char g_TzStandardNameBuffer = 'E';

char g_CRT_TzStandardNameBufEnd = '\0';

char g_TzDaylightName = 'E';

char g_CRT_TzDaylightNameBufEnd = '\0';

char *g_CRT_TzDaylightNamePtr = &g_TzDaylightName;

int g_CRT_TimezoneSeconds = 18000;

int g_TzDaylightFlag = 1;

int g_CRT_DaylightBiasSeconds = 3600;

int g_TzInitFlags = 1;

EvalNodeDescriptorCompact g_EvalDesc_FetchJoinBindingFieldRecord = { 0x0000401D };

EvalNodeDescriptorCompact g_EvalDesc_FetchJoinBindingFieldSimple = { 0x0000401E };

EvalNodeDescriptorCompact g_EvalDesc_FetchJoinBindingNestedField = { 0x0000401F };

EvalNodeDescriptorCompact g_EvalDesc_FetchPatternFieldRecord = { 0x0000401A };

EvalNodeDescriptorCompact g_EvalDesc_FetchPatternFieldSimple = { 0x0000401B };

EvalNodeDescriptorCompact g_EvalDesc_FetchPatternNestedFieldRecord = { 0x0000401C };

EvalNodeDescriptorCompact g_EvalDesc_TestJoinBindingFieldsEqual = { 0x0000C017 };

EvalNodeDescriptorCompact g_EvalDesc_TestJoinBindingFieldsEqualRanged = { 0x0000C018 };

EvalNodeDescriptorCompact g_EvalDesc_EvalPatternFieldsEqual = { 0x0000C016 };

EvalNodeDescriptorCompact g_EvalNodeDescCopyMultifieldBinding = { 0x00004022 };

EvalNodeDescriptorCompact g_EvalDesc_EvalMultifieldIndexInRange = { 0x00004019 };

EvalNodeDescriptorCompact g_EvalDesc_TestPatternFieldSimple = { 0x0000C020 };

EvalNodeDescriptorCompact g_EvalDesc_TestPatternNestedField = { 0x0000C021 };

int g_PatternParserListHead = 0;

int g_PatternParserCount = 0;

int g_Rules_ReservedPatternSymbolList = 0;

int g_IncrementalResetInProgress = 0;

int g_Rules_IncrementalResetEnabled = 1;

int g_ClipsParseContextSaveStack = 0;

int g_SequenceOperatorRecognition = 0;

int g_ClipsDefrulePreservedWatchBreakFlags = 0;

int g_Module_PortConstructList = 0;

int g_Module_AfterDefineCallbackList = 0;

int g_DefglobalBloadRecords = 0;

int g_Defglobal_Count = 0;

int g_DefgenericMethodArray = 0;

int g_DefgenericBloadCount = 0;

int g_Defgeneric_MethodRecordCount = 0;

int g_Defgeneric_RestrictionRecordCount = 0;

int g_Defgeneric_RestrictionTypeCount = 0;

int g_Defgeneric_PackedExpressionCount = 0;

int g_DefgenericBloadModuleRefArray = 0;

int g_DefgenericRestrictionRecords = 0;

int g_ClipsDefgenericBloadRestrictionTypeArray = 0;

int g_DefgenericBloadRestrictionTypeArray = 0;

int g_DeffunctionBloadRecordArray = 0;

int g_Deffunction_Count = 0;

int g_Clips_DeffunctionCount = 0;

int g_Clips_DefclassArrayBase = 0;

int g_DefclassLinkTable = 0;

int g_DefclassSlotDescriptorArrayPtr = 0;

int g_DefclassBloadSlotNameLinkArray = 0;

int g_DefclassSlotTable = 0;

int g_Class_BloadClassLinkArray = 0;

int g_DefclassBloadTemplateSlotArray = 0;

int g_Class_BloadSlotNameMapArray = 0;

int g_ClipsDeffactsBloadArray = 0;

int g_DeffactsBsaveCount = 0;

int g_ClipsCurrentGeneric = 0;

int g_ClipsCurrentMethod = 0;

int g_Method_CurrentArgParamPtr = 0;

int g_Rules_WatchGenericFunctions = 0;

int g_Rules_WatchMethods = 0;

int g_CurrentDeffunction = 0;

int g_Rules_WatchGlobals = 0;

int g_DefglobalResetGlobalsFlag = 1;

_DWORD g_EvalDesc_GetSelfSlotDirect[12] = { 0x0000C03A };

_DWORD g_EvalDesc_PutSelfSlotDirect[12] = { 0x0000C03B };

EvalNodeDescriptorCompact g_EvalNodeDescFetchJoinObjectSlotFieldRecord = { 0x0000402F };

EvalNodeDescriptorCompact g_EvalNodeDescFetchJoinObjectSlotFieldSimple = { 0x00004030 };

EvalNodeDescriptorCompact g_EvalNodeDescFetchObjectSlotFieldRecord = { 0x0000402D };

EvalNodeDescriptorCompact g_EvalNodeDescFetchObjectSlotFieldSimple = { 0x0000402E };

EvalNodeDescriptorCompact g_EvalNodeDescObjectSlotBoundVariableEqual = { 0x0000C032 };

EvalNodeDescriptorCompact g_EvalNodeDescObjectSlotIndexInRange = { 0x00004031 };

EvalNodeDescriptorCompact g_EvalNodeDescObjectSlotFieldsEqual = { 0x0000C033 };

EvalNodeDescriptorCompact g_EvalNodeDescObjectSlotElementFieldEqual = { 0x0000C035 };

EvalNodeDescriptorCompact g_EvalNodeDescObjectSlotElementsEqual = { 0x0000C037 };

EvalNodeDescriptorCompact g_EvalDescriptor_JoinObjectSlotFieldsEqual = { 0x0000C034 };

EvalNodeDescriptorCompact g_EvalDescriptor_JoinObjectSlotElementFieldEqual = { 0x0000C036 };

EvalNodeDescriptorCompact g_EvalDescriptor_JoinObjectSlotElementsEqual = { 0x0000C038 };

int g_InternedSym_Qds = 0;

int g_ClipsQueryCore = 0;

int g_ClipsInstanceQueryCoreStack = 0;

int g_InstanceQuery_AbortFlag = 0;

int g_ClipsObjectReteCurrentInstance = 0;

int g_ObjectPatternActiveClassNode = 0;

int g_ObjectPatternMatchFieldCount = 1;

int g_ObjectPatternMarkerListHead = 0;

UINT CodePage = 1u;

int g_Parser_InsideNegatedCEFlag = 0;

int g_ClipsParsedFormAst = 0;

int g_ClipsBsaveModuleCount = 0;

int g_ClipsBloadPortItemCount = 0;

int g_Defmodule_PortItemArrayPtr = 0;

int g_ClipsModuleArrayBase = 0;

int g_MessageHandler_SelfSymbol = 0;

int g_ClipsDefinstancesBloadArray = 0;

int g_Definstances_Count = 0;

int g_Clips_DefinstancesCount = 0;

int g_ReactiveRuleBloadCount = 0;

int g_ObjectPatternNetworkBloadCount = 0;

int g_ReactiveRuleArrayPtr = 0;

int g_ObjectPatternNetworkArrayPtr = 0;

char *g_StrToLongOverflowLimitTable[2] = { "mod", "cotan" };

_UNKNOWN g_AviQueryInterfaceIid;

IID stru_51CA08 = { 3014063072u, 11075u, 4559u, { 162u, 222u, 0u, 170u, 0u, 185u, 51u, 86u } };

_UNKNOWN g_InputBackendMouseDeviceGuid;

_UNKNOWN g_InputBackendKeyboardDeviceGuid;

_UNKNOWN g_InputBackendJoystickInterfaceIid;

_UNKNOWN g_RenderBackbufferScanlineBuffer;

_UNKNOWN g_RenderPaletteRemapBuffer;

int g_MousePresentAtStartup;

int g_ManualTacticalBattleEnabled;

int g_AppCommandLine;

CHAR Text[128];

_BYTE g_PaletteCrossfadeSourceBuffer[0x408];

int g_ActiveBlitCursor;

RenderPrimarySurfaceStorage g_MainRenderDevice;

RenderSurfaceStorage g_RenderDeviceStorage;

_BYTE g_DefaultPaletteTable[1024];

_BYTE g_PaletteScratchSurfaceBuffer[1024];

_BYTE g_PaletteRegionUnusedBuffer5[5];

char g_Render_BackgroundColorIndex;

char g_PaletteRemapRegionUnusedByte;

char g_PaletteShadowRemapTableMinus1[];

char g_Video_LowColorRemapTable[32];

int g_DlxDirectoryEntryStartOffsets[];

int g_DlxDirectoryEntryEndOffsets[1024];

char g_TextSprite_StyleFlag;

int g_DlxSpriteSetOffsetTable[];

int g_DlxDirEntryEndOffsetTable[1022];

int g_DlxDirTotalDataOffset;

int g_WorldMap_NextPaletteAnimTime = 0;

int g_WorldMap_NextTileStateAnimTime = 0;

int g_WorldMap_PaletteFlashStep;

int g_PaletteCrossfadeNextStepTime;

int g_WorldMapKeyScrollRepeatTime;

int g_WorldMap_CursorTileEnterTime = 0;

int g_WorldMap_LastCursorTileX = 0;

int g_WorldMap_LastCursorTileY = 0;

int g_WorldMap_HoverTooltipActiveFlag = 0;

int g_WorldMapActionHoverActive = 0;

int g_ActiveUiSpriteSet;

int g_WorldMapBackgroundSpriteSet;

int g_FogOverlaySpriteSet;

int g_MarksSpriteSet;

int g_MovePathStepSpriteSet;

int g_WhirlSpriteSet;

int g_FlagSpriteSet;

int g_TreeSpriteSet;

int g_WorldMapTurnBannerSpriteSet;

int g_PrimaryRenderSurface;

int gameData;

int g_WorldMapJoinUnitsModeActive;

int g_CurrentPlayerIndex;

int g_WorldMapViewportScrolledFlag;

int g_MapPalettePtr;

int g_WorldMapTurnLoopExitFlag;

int g_AdvanceToNextPlayerFlag;

int g_WorldMapGameLostExitFlag;

int g_TurnEndedByCompletionFlag;

int g_WorldMapBuilderMenuAction;

int g_ActionButtonSpriteSet;

int g_WorldMapFrameRedrawDisabled;

unsigned __int8 g_UiDrawTextBuffer[512];

unsigned __int8 g_UiDrawTextFmtBuffer[516];

int g_TextSpriteLastActivatedSlotIndex;

int g_ActiveTextSpriteSlot;

RenderSpriteRemapEntry g_TerrainAnimationRemapTable[1024];

unsigned char g_SpecialTileAnimFrameDuration = 0;

RenderSpriteRemapEntry g_SpriteCodeRemapTable[1024];

_WORD g_FontGlyphFallbackTable3[1528];

unsigned short g_Render_AnimatedFrameTable[1038];

__int16 g_ColorCycleDelayLookupIndex = 0;

__int16 g_MiniMapRectLeft;

__int16 g_MiniMapRectTop;

__int16 g_MiniMapRectWidth;

__int16 g_MiniMapRectHeight;

int g_MiniMapSurface;

unsigned char g_MiniMapTileColorTableTheme0[0x400];

unsigned char g_MiniMapTerrainColorTableVariant1[0x400];

unsigned char g_MiniMapTerrainColorTableVariant2[0x400];

int g_MiniMapTerrainColorTable;

char g_MiniMapPixelsPerTile;

int g_MapPanelSpriteSet;

int g_WorldMapTargetSurface;

int g_WorldMapUnitWalkStepCounter;

int g_UnitMoveAnimOffsetX;

int g_UnitMoveAnimOffsetY;

int g_ActiveUnitAnimSpriteSet;

int g_UnitAnimFrameIndex;

CLASH95_INTERNAL unsigned char g_UnitSpriteCacheRecords[UNIT_SPRITE_CACHE_BYTES];

int g_TerrainMoveProfileOffsetsMinus1;

int g_TerrainMoveProfileOffsets[1024];

int g_PathingAllowBridgeCrossings;

int g_UnitPathfindingScratchDword;

int g_RngState;

int g_MapConstructionSwayAnimLastTick;

int g_MapIdleBuildingAnimLastTick;

int (__fastcall *g_WorldMapTileOverlayDrawHook)(_DWORD, _DWORD);

int (*g_WorldMapDrawExtensionHook)(void);

int g_UnitStackSelectionModeActive;

int g_MapFlagAnimationFrame;

int g_WorldMapAttentionFlashStartTick;

int g_UnitBlinkFlashTickTime;

int g_UnitBlinkFlashFrame;

int g_BlinkFlashTileX;

int g_BlinkFlashTileY;

int g_TileBlinkFlashFrame;

_UNKNOWN g_TileBlinkFlashTickTime;

char g_BuildingSwayJitterOffsetsOdd[];

char g_BuildingSwayJitterOffsetsX[];

char g_BuildingSwayJitterOffsetsY[31];

TileHighlightSlot g_TileHighlightSlots[8];

int logEnabled;

int g_BattleInProgressFlag;

int g_TooltipCursorActive;

int g_ActiveWidgetSpriteTableIndex;

int (*g_ActiveDialogAnimationTickHook)(void);

int g_SavedCursorDescriptor;

LARGE_INTEGER Frequency;

int g_SelectedBuildingRecord;

int g_CastleScreenSurface;

_BYTE g_CastleScreenPaletteBuffer[1024];

int g_ActiveCastleOwnerIsChristian;

int g_CastleSceneIconSpriteSet;

int g_CastleAmbientSpriteSet;

int g_CastleStatusSpriteSet;

int g_CastleScreenExitRequested;

int g_CastleDestroyConfirmed;

int g_CastleAmbientLayer1_LastTick;

int g_CastleAmbientLayer1_Frame;

int g_CastleAmbientLayer2_LastTick;

int g_CastleAmbientLayer2_Frame;

int g_CastleAmbientLayer4_LastTick;

int g_CastleAmbientLayer4_Frame;

int g_CastleAmbientLayer3_NextDueTick;

int g_CastleAmbientLayer3_LastTick;

int g_CastleAmbientLayer3AnimFrame;

int g_CastleAmbientLayer5_NextDueTick;

int g_CastleAmbientLayer5_LastTick;

int g_CastleAmbientLayer5_Frame;

int g_CastleAmbientLayer6_LastTick;

int g_CastleAmbientLayer6_Frame;

int g_CastleAmbientLayer7_LastTick;

int g_CastleAmbientLayer7_Frame;

int g_CastleAmbientLayer8_NextDueTick;

int g_CastleAmbientLayer8_LastFrameTimeMs;

int g_CastleAmbientLayer8_Frame;

int g_CastleAmbientLayer9_NextPlayTimeMs;

int g_CastleAmbientLayer9_LastFrameTimeMs;

int g_CastleAmbientLayer9_Frame;

int g_CastleAmbientLayer10_NextPlayTimeMs;

int g_CastleAmbientLayer10_LastFrameTimeMs;

int g_CastleAmbientLayer10AnimFrame;

int g_TooltipBackdropSurface;

int g_TooltipTop;

int g_TooltipLeft;

int g_TooltipBottom;

int g_TooltipRight;

int g_TooltipResourceHandle;

int g_TooltipCaptureArg5;

char g_TooltipTextBuffer[0x68];

_DWORD g_UnitStackSlotSelectedFlags[10];

int g_SelectedUnitStackRecordPtr;

int g_CurrentPlayerInfoSpriteSet;

int g_RoadBuildModeLastAnimationTick;

int g_RoadBuildModeExitRequested;

int g_RoadBuildModeHasBuildTarget;

int g_RoadBuildModeAnimationFrameIndex;

int g_BattleUnitMoveAnimStepCounter;

char g_TilePassabilityMask[1023];

char g_UnitTypeBattleMoveFlagsMinus1[];

char g_UnitTypeFlatMoveCostFlags[40];

int g_MapIgnoreUnitOccupancy;

int g_UnitMoveTrackPackedNodeScratch;

int g_UnitMoveAnimTickParityCounter;

int g_UnitArrivalAnimTickParityCounter;

int g_BuildPlacementLoopDone;

int g_BuildCursorBuildingType;

__int64 g_BuildPlacementTileXY;

int g_BuildingEconomyDialogSpriteSet;

int g_BuildingEconomyDialogExitSignal;

int g_BuildingEconomyDialogPendingPeasantTransfer;

int g_BuildingEconomyDialogPendingGoldTransfer;

int g_BuildingEconomyDialogBuilding;

int g_BattleViewportScrollRepeatDelayBias;

int g_MapData;

int g_BattleHudSprites;

int g_BattleButtonsSpriteSet;

int g_BattleUnitPanelIconSpriteSet;

int g_BattleCasualtySpriteSet;

int g_Battle_ShootModeEnabled;

int g_UnitBattleChargeModeActive_532060;

int g_BattleLoopExitCode;

int g_UnitBattleActionLoopExitRequested;

int g_AttackerStartsOnLeft;

int g_DefenderStartsOnLeft;

int g_UnitBattleChargeModeStartTick_532074;

int g_UnitBattleAiTurnCounter;

int g_UnitBattlePromptDialogResult;

char g_UnitBattlePanelStatAnimCounters[];

_BYTE g_BattleUnitOrderBitsBackup[92];

int g_UnitBattleHitAnimFrame;

int g_UnitBattleAnimatingUnitSpriteSet;

int g_UnitFadeAnimCurrentOffset;

int g_UnitFadeAnimLastUpdateTime;

int g_UnitBattleProjectileSpriteSet;

int g_BattleShotAnimFrameIndex;

int g_BattleWallGateLastSpriteChar;

int g_BattlePanelUnitFatiguePercent;

_UNKNOWN g_GarrisonDialogExitScratch;

char g_BattleStateRegionUnusedByte[];

char g_BattleSavedActionPointsBySlot[24];

int g_BuildingGarrisonDialogExitCountdownLastTickMs;

int g_BuildingGarrisonDialogSelectedUnitAnimLastTickMs;

int g_BuildingGarrisonDialogUiSpriteSet;

int g_BuildingGarrisonDialogCloseRequested;

int g_BuildingGarrisonDialogUseChrTheme;

int g_BuildingGarrisonDialogActiveBuilding;

int g_BuildingGarrisonDialogResourceHandle;

int g_BuildingGarrisonDialogSelectedSlots[12];

int g_BuildingGarrisonDialogSelectedSlotIndex;

int g_BuildingGarrisonDialogSelectedUnitSpriteSet;

int g_BuildingGarrisonDialogSelectedUnitAnimFrame;

int g_BuildingGarrisonDialogSlotSpriteSets[12];

int g_BuildingGarrisonDialogSlotAnimFrames[12];

int g_BuildingGarrisonDialogPendingExitCountdown;

int g_GarrisonUnitCellSurface;

int g_CastleProductionPortraitAnimLastTickMs;

int g_CastleProductionLicenceGridAnimLastTickMs;

int g_BuildingUiDlxSpriteSet;

int g_CastleProductionExitSignal;

int g_CastleProductionUseChrTheme;

int g_CastleProductionBuildingPtr;

int g_CastleProductionPaletteBuffer;

int g_CastleProductionSelectedAvailableUnitIndex;

unit_type g_CastleProduction_AvailableUnitTypes[41];

int g_CastleProductionAvailableUnitTypesLookahead[40];

int g_ProductionGridSelectedIndex;

int g_CastleProductionUnitPortraitFrame;

int g_CastleProductionSelectedUnitSpriteSet;

int g_CastleProductionSlotAnimFrames[];

int g_CastleProduction_LicenceSlotSpriteHandles[12];

int g_LicenceGridAddAnimSlotIndex;

int g_CastleLicenceRemovalSlotIndex;

int g_CastleProductionLicenceTransitionFrame;

int g_BuildingTransferDialogExitScratch;

int g_Building_TransferAmount;

int g_BuildingTransferSourcePtr;

int g_BuildingTransferTargetListIndex;

__int16 g_BuildingTransferTargetIds[BUILDING_TRANSFER_TARGET_LIST_CAPACITY];

int g_BuildingTransferTargetListSpriteSet;

int g_BuildingTransferTargetListDrawX;

int g_BuildingTransferTargetListDrawY;

int g_UnitBattleAiReachGrid;

int g_UnitBattleAiReachGridCellSecondField;

int g_BattleCellStateGrid[];

int g_UnitBattleTileScoreGrid[17621];

int g_UnitBattleScanTileRow;

int g_BattleTargetTileCol;

int g_BattleAiActionAttemptCount;

int g_BattleShootingUnitMoveActiveFlag;

int g_UnitBattleWallScanTileRow;

int g_BattleWallScanColumn;

int g_BattleWallScanTileX;

int g_UnitBattleAiCandidateQueue;

int g_BattleAiCandidateQueue_Vtable;

int g_UnitBattleAiCandidateQueueTail;

int g_BattleAiUnitQueueCount;

int g_BattleAiCandidateQueue_AllocFn;

int g_BattleAiCandidateQueue_FreeFn;

int g_BattleDeploymentBucketStorage[48];

int g_GateDoorDialogV1SpriteSet;

int g_GateDoorDialogExitFlag_V1;

int g_GateDoorDialogV2SpriteSet;

int g_GateDoorDialogExitFlag_V2;

int g_GateDoorDialogV3SpriteSet;

int g_GateDoorDialogExitFlag_V3;

int g_GateDoorDialogV4SpriteSet;

int g_GateDoorDialogExitFlag_V4;

char g_BuildingSpriteCacheRegionBuffer13[13];

char g_BuildingSpriteCache[650];

int g_DemoTextDLXSpriteSet;

int g_BuildingUnitsPopupSlotSpriteSets[];

int g_BuildingUIRecordPtr;

int g_TempleOutcomePopupCloseFlag;

char g_BuildingUnitsPopupSelectedSlots[20];

int g_MainMapMusicHandle;

int g_LastUnitActivateSoundHandle;

int g_CurrentUnitMoveSoundHandle;

int g_CurrentUnitMoveSoundVariant;

int g_CurrentUnitMoveSoundTypeId;

int g_FileSystemMountTable[11];

int g_SaveSlotDialogDone;

int g_SaveSlotDialogSelectedRow;

int g_SaveSlotDialogIsSaveMode;

int g_SaveSlotDialogResult;

int g_TextInputCaretPos;

char g_SaveSlotNameEditBuffer[28];

int g_CheatEditCaretIndex;

char g_CheatEntryTextBuffer[12];

int g_DecisionDialogExitSignal;

int g_DecisionDialogResult;

int g_DecisionDialogConfirmDisabled;

int g_PlayGameMenuSpriteSetHandle;

int g_PlayGameMenuExitRequested;

int g_MainMenuRequestedScreen;

unsigned __int8 g_MenuScreenPaletteBuffer[1024];

int g_MainMenuMusicHandle;

int g_PlayGameMenuSelectedAction;

char g_MultiplayerPlayerSlotTypes[];

char g_MultiplayerPlayerSlot1Type;

char g_MultiplayerPlayerSlot2Type;

char g_MultiplayerPlayerSlot3Type;

int g_PlayGameMenuLaunchGameFlag;

int g_PlayerNameEditCaretPos;

int g_MpEditNameSlotIndex;

_BYTE g_MultiplayerPlayerNameEditTable[11];

int g_MultiplayerSelectedMapIndex;

int g_MultiplayerOpponentListScrollOffset;

int g_LoadMenuSelectedSlotIndex;

_UNKNOWN g_PrisonerIntakeMessageBuffer;

_UNKNOWN g_InfoWindowFormatBuffer;

int g_StatScreenSpriteSet;

int g_PrisonerDialogExitSignal;

int g_StatScreenPaletteBuffer;

int g_CurrentPrisonBuildingRecord;

int g_InGameOptionsDialogExitSignal;

int g_InGameOptionsSpriteSet;

int g_AITurnLogFactHandle_Turn;

int g_AITurnPlayerIntelligenceFactHandle;

int g_AITurnCastleCountFactHandle;

int g_AiTurnFortressCountFactHandle;

int g_CastleSiteAnchorRows[CASTLE_SITE_ANCHOR_CACHE_COUNT];

int g_CastleSiteAnchorColumns[CASTLE_SITE_ANCHOR_CACHE_COUNT];

int g_CastleSiteRegionUnusedDwordA;

int g_CastleSiteRegionUnusedDwordB;

int g_CheatForceWinMissionFlag;

int g_RenderStateNextRefreshTick;

int g_DDPageFlipWasInProgressFlag;

_UNKNOWN g_CursorSpritePalette;

__int16 g_DeviceRecordLastX;

__int16 g_DeviceRecordLastY;

char g_DeviceRecordLastFlipLostState;

int g_DeviceRectTweenTimeBase;

int g_DeviceReplaySegmentBaseTick;

int g_DeviceReplaySegmentTargetTick;

char g_DemoPlaybackCursorButtonState;

int g_DemoScriptCurrentTick;

_DWORD g_RenderState[286];

int g_CursorOverlayPresented;

int g_ActiveCursorDescriptorPtr;

char g_CursorCoordShift;

int g_WorldMap_KeyboardInputDisabled;

int g_ActiveCursorDescriptor;

_UNKNOWN g_BootstrapCursorDescriptor;

int g_Input_LastRepeatKeyCode;

int g_SoundPausedForInactiveApp;

InputBackendState g_InputBackendState;

int g_ShouldPresentOnReactivate;

HWND hWnd;

int g_VideoModeSwitchStartTick;

int g_MissionDefeatVideoPlayedGuard;

char g_Rgb15ToPaletteLut[32788];

_DWORD g_AviFrameRectInitScratch[4];

struct _RTL_CRITICAL_SECTION stru_54D350;

int g_DirectSoundDevice;

int g_DSoundStreamWriteOffset;

int g_DSoundPrimaryBuffer;

int g_CSS_DSoundPlayCursor;

int g_DSoundCoopWindowHandle;

int (__cdecl *g_Audio_MixToOutputConvertFn)(_DWORD, _DWORD, _DWORD, _DWORD);

int g_CSS_DSoundWritePrimaryMode;

int g_MixerFormatFlags;

int g_CSS_SampleFrameBytes;

int g_DSoundStreamBufferBytes;

int g_Audio_MixChunkSampleCount;

int g_CSS_MixChunkSamplesRemaining;

int g_DSoundRefillThresholdBytes;

int g_AudioSampleRateHz;

int g_CSS_AudioHadForegroundFocus;

int g_DSoundStallTickTimestamp;

int g_SampleCacheListHead;

int g_CSS_SampleCacheBytesUsed;

int g_CSS_SampleCacheByteBudget;

int g_CSS_ActiveVoiceCount;

int g_CssVoicePoolSize;

int g_CSS_StreamBufferMs;

int g_SoundChannelArrayBase;

int g_StreamServiceLockEntryCount;

struct _RTL_CRITICAL_SECTION CriticalSection;

int g_CSS_MixerLockNestingCount;

struct _RTL_CRITICAL_SECTION stru_54D3FC;

int g_CSS_StreamReadingActive;

HANDLE hThread;

int g_CSS_StreamThreadHandle;

int g_CSS_StreamReadThreadLockRefCount;

struct _RTL_CRITICAL_SECTION stru_54D424;

int g_CSS_StreamServiceThreadLockRefCount;

struct _RTL_CRITICAL_SECTION stru_54D444;

int g_CSS_StreamThreadRunning;

int g_CSS_DevicePollPending;

int g_CSS_ActiveSoundDriver;

int g_CSS_DeviceConfigDefaultZero;

int g_AudioWindowHandle;

int g_CSS_DeviceSampleRateHz;

int g_CSS_DeviceOpenParam2;

int g_CSS_DeviceConfigDefaultNegOne;

int g_CSS_VoiceCount;

int g_CSS_AudioDeviceActive;

int g_CSS_DeviceSearchIndex;

int g_CSS_FatalErrorHandler;

int g_CSS_DeviceSearchThreadRefCount;

struct _RTL_CRITICAL_SECTION stru_54D49C;

int g_CSS_DevicePollThreadRunning;

int g_MediaFileStreamProvider;

int g_CSS_WaveBufferDataPtrs[32];

int g_CSS_WaveBufferMemHandles[];

int g_CSS_WaveBufferStateArray[];

int g_CSS_WaveHeaderPreparedFlags[32];

int g_CSS_WaveHeaderMemHandles[];

LPWAVEHDR pwh[32];

int g_WaveOutBufferRingIndex;

int g_CSS_WaveBlockAlign;

int g_CSS_WaveOutChunkSampleCount;

int g_CSS_WaveOutRefillRemaining;

int (__cdecl *g_AudioMixToOutputFunc)(_DWORD, _DWORD, _DWORD, _DWORD);

_DWORD g_CSS_WaveOutFillByteOffset;

HWAVEOUT hwo;

int g_WaveOutFormatFlags;

int g_CSS_MixChannelCount;

SIZE_T dwBytes;

int g_CSS_SampleRateHz;

int g_CSS_MixLookupTable[];

int g_CSS_MixLookupTableWriteBase;

int g_CSS_MixLookupComplementTable[];

int g_CSS_MixIdleChannelFlag;

int g_CSS_MixBufferAllocBase;

int g_CSS_MixSuspendedFlag;

int g_CssMixChannelsReadyFlag;

int g_CSS_CurrentVolumeScaleLevel;

int g_CssMixChannelCount;

int g_CSS_MixBufferSampleCount;

int g_CSS_MixMasterVolume;

int g_CssMixBufferAlignedBase;

int g_CssMixChannels;

int g_CSS_QueuedSoundSlotTable;

int g_CssMixBufferSizeBytes;

int g_CSS_MixSampleRate;

_DWORD g_CSS_MixAccumBufferPtr;

int g_CSS_MixChannelCount_54DBA4;

int g_ClipsMemoryTable;

int g_ClipsMemFreeListTemp;

int g_Rules_MemPoolFreeBucketIndex;

int g_ClipsMemPoolReturnBucketIndex;

int g_HeapChunkHeaderSize;

int g_MemPoolListHead;

int g_MemPoolBlockHeaderSize;

_UNKNOWN g_DirectDrawErrorMessageBuffer;

int g_FS_ResolvedPathEntryHolder;

int g_CurrentDirPathHolder_VtablePtr;

char g_FileSystem_CwdHolderInitFlag;

int g_FileSystemStrippedPathHolderText;

int g_CurrentEntryPathHolder_VtablePtr;

int g_FileSystemMountOpenMode;

int g_FS_ArchiveRecordCacheAccessCount;

int g_FS_ArchiveRecordCacheMissCount;

int g_FS_ResolvePathByParentLeafCount;

int g_FS_PathEntryCacheMissCount;

int g_InputBackendTempJoystickDevice;

int g_Rules_BloadFunctionPtrTable;

int g_ClipsBloadFileHandle;

int g_ClipsFunctionNameHashTable;

int g_Clips_SymbolHashTable;

int g_ClipsIntegerHashTable;

int g_ClipsFloatHashTable;

int g_ClipsBitmapHashTable;

int g_Clips_NegativeInfinitySymbol;

int g_ClipsTrueSymbol;

int g_ClipsPositiveInfinitySymbol;

int g_CLIPS_IntegerZeroValueNode;

int g_ClipsFalseSymbol;

int g_CRT_OpenStreamListHead;

int g_IO_OpenStreamListHead;

_DWORD g_CrtThreadDataMgmtDisabledFlag;

LPVOID lpTlsValue;

int g_IO_RouterExitHandledFlag;

_UNKNOWN g_CRT_StaticLock1;

_UNKNOWN g_CRT_StaticLock3;

_UNKNOWN g_CRT_FileHandleLockSlots;

_UNKNOWN g_CRT_StaticLock2;

int g_CRT_LockInitCriticalSection;

int g_CRT_ThreadLockSystemInitialized;

_UNKNOWN g_CRT_StaticLock4;

int g_CRT_UsedLockSlotCount;

_UNKNOWN g_CRT_LockSlotPool;

char g_CRT_HeapCoalesceStateByte;

int g_ClipsDeftemplateBeingParsedPtr;

int g_ClipsFactHashTable;

int g_ClipsFactPatternNodeBloadArray;

int g_FactPatternNodeCount;

int g_ClipsFactPatternNetworkCodeGenItem;

int g_CurrentPatternFact;

int g_ClipsFactMatchMarkerList;

int g_Clips_PrimitiveEntityTable[70];

int g_DefruleConstructTypePtr;

int g_DefruleConstructClass;

int g_DeftemplateConstructType;

int g_ClipsDeftemplateModuleItemId;

int g_ClipsSymbolEq;

int g_Clips_SymbolAnd;

int g_ClipsNotSymbol;

int g_ClipsSymbolOr;

int g_ClipsSymbolNeq;

int g_Clips_FloatConstantTable;

int g_ClipsBloadSymbolPointerArray;

int g_Clips_IntegerConstantTable;

int g_ClipsBloadBitmapPointerTable;

int g_ClipsExpressionNodeIndex;

int g_ClipsBloadExpressionCount;

int g_ClipsPackedExpressionArray;

int g_ClipsConstraintRecordArrayBase;

int g_Clips_BloadedConstraintCount;

int g_ConstraintHashTable;

int g_ClipsDeffactsModuleItemId;

int g_ClipsDeffactsConstructType;

int g_Clips_DefgenericConstructType;

int g_DefgenericModuleItemIndex;

int g_Clips_DeffunctionModuleItemIndex;

int g_ClipsDeffunctionConstructType;

int g_ClipsDefglobalModuleItemId;

int g_ClipsDefglobalConstructType;

int g_ClipsDefclassConstructType;

int g_CLIPS_DefclassModuleItemIndex;

int g_CLIPS_DribbleClockCentisecsPtr;

int g_Clips_DribbleBuffer;

int g_ClipsBatchEchoLineBuffer;

int g_ClipsBatchSourceIsStringFlag;

int g_ConstructsToCImageId;

int g_ClipsCodeDataFile;

int g_ClipsExpressionCodeFileVersion;

int g_ClipsConstructCodeEntryIndexInFile;

int g_Rules_ExprCodeNeedNewFileFlag;

int g_Rules_ConstructsToCodeBaseName;

int g_ClipsCodeHeaderFile;

int g_ClipsBsaveInstanceDataSpace;

int g_Rules_BloadBytesConsumed;

int g_Rules_InitialObjectSymbol;

int g_Clips_NameSymbol;

int g_Symbol_IsA;

int g_RuntimeGrowableByteFlagArrayPtr;

int g_CRT_EnvVarPointerArray;

int g_CrtWideEnvironTable;

char g_CRT_FpuExceptionActiveFlag;

int g_CRT_MbcsCodePageActive;

char g_CRT_MbcsLeadByteTable[];

char g_Clips_DbcsLeadByteTable[255];

int g_Rules_PatternParserTable[];

int g_CLIPS_PatternParserTableByTypeId[];

int g_DeftemplateRecordTable;

int g_DeftemplateSlotTable;

int g_DeftemplateBsaveCount;

int g_ClipsDeftemplateModuleItemArray;

int g_DeftemplateModuleItemCount;

int g_Deftemplate_SlotCount;

int g_Clips_DeftemplateCodeGenItem;

int g_DefruleModuleBloadCount;

int g_ClipsBloadJoinArray;

int g_RuleJoinNodeBsaveCount;

int g_Clips_JoinTestCount;

int g_ClipsJoinNodeArray;

int g_ClipsJoinNetworkModuleBloadArray;

int g_DeftemplateSlotParseErrorFlag;

int g_ParserBreakContextFlag;

int g_ClipsParseReturnContext;

int g_ClipsLoopContextStackTop;

int g_ClipsDefruleCodeGenItem;

int g_Module_DefModuleCount;

int g_DefglobalModuleItemCount;

int g_ClipsDefglobalModuleItemArray;

int g_Clips_DeffunctionRecordArray;

int g_DefclassNameTableCount;

int g_ClipsBloadSlotRecordCount;

int g_ClipsDefclassBsaveIndexArrayCount;

int g_Defclass_SlotNameLinkCount;

int g_ClipsBloadClassLinkCount;

int g_Defclass_SlotRecordCount;

int g_ClipsBloadDefclassCount;

int g_ClipsDefclassBsaveHandlerCount;

int g_Class_BloadModuleArray;

int g_DeffactsModuleItemCount;

int g_Deffacts_BloadModuleArray;

int g_Clips_DeffactsCodeGeneratorItem;

int g_Defgeneric_SavedBusyCount;

int g_DefgenericCodeGenItem;

int g_ClipsMethodParserToken;

int g_Clips_CurrentTokenValue;

int g_CLIPS_GenericParseTokenPrintStr;

int g_DeffunctionCodeGeneratorItem;

_DWORD g_Rules_ParsedConstructNameComment[2];

int g_Clips_DeffunctionEchoToken;

int g_ClipsDefglobalCodeGenItem;

int g_Clips_DefinstancesModuleItemIndex;

int g_ClipsDefinstancesConstructType;

int g_ClipsConstructCompilerData;

int g_ParserCurrentTokenType;

int g_ClipsParserTokenValue;

int g_ClipsScanTokenPrintForm;

int g_ClipsDefmoduleCompilerItem;

int g_Rules_DeclaredAutoFocusFlag;

int g_CLIPS_CurrentRuleSalience;

int g_DefinstancesBloadModuleRefArray;

int g_DefinstancesCodeGenItem;

int g_ObjectPatternNetworkCodeGenItem;

_DWORD g_AviDecompressorBlitRectTemplate[440];
