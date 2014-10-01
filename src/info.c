/*
========================================================================

  DOOM RETRO
  The classic, refined DOOM source port. For Windows PC.
  Copyright (C) 2013-2014 Brad Harding.

  This file is part of DOOM RETRO.

  DOOM RETRO is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  DOOM RETRO is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with DOOM RETRO. If not, see <http://www.gnu.org/licenses/>.

========================================================================
*/

#include "sounds.h"
#include "info.h"
#include "p_mobj.h"
#include "p_pspr.h"
#include "r_defs.h"

char *sprnames[] =
{
    "TROO", "SHTG", "PUNG", "PISG", "PISF", "SHTF", "SHT2", "CHGG", "CHGF", "MISG",
    "MISF", "SAWG", "PLSG", "PLSF", "BFGG", "BFGF", "BLUD", "PUFF", "BAL1", "BAL2",
    "PLSS", "PLSE", "MISL", "BFS1", "BFE1", "BFE2", "TFOG", "IFOG", "PLAY", "POSS",
    "SPOS", "VILE", "FIRE", "FATB", "FBXP", "SKEL", "MANF", "FATT", "CPOS", "SARG",
    "HEAD", "BAL7", "BOSS", "BOS2", "SKUL", "SPID", "BSPI", "APLS", "APBX", "CYBR",
    "PAIN", "SSWV", "KEEN", "BBRN", "BOSF", "ARM1", "ARM2", "BAR1", "BEXP", "FCAN",
    "BON1", "BON2", "BKEY", "RKEY", "YKEY", "BSKU", "RSKU", "YSKU", "STIM", "MEDI",
    "SOUL", "PINV", "PSTR", "PINS", "MEGA", "SUIT", "PMAP", "PVIS", "CLIP", "AMMO",
    "ROCK", "BROK", "CELL", "CELP", "SHEL", "SBOX", "BPAK", "BFUG", "MGUN", "CSAW",
    "LAUN", "PLAS", "SHOT", "SGN2", "COLU", "SMT2", "GOR1", "POL2", "POL5", "POL4",
    "POL3", "POL1", "POL6", "GOR2", "GOR3", "GOR4", "GOR5", "SMIT", "COL1", "COL2",
    "COL3", "COL4", "CAND", "CBRA", "COL6", "TRE1", "TRE2", "ELEC", "CEYE", "FSKU",
    "COL5", "TBLU", "TGRN", "TRED", "SMBT", "SMGT", "SMRT", "HDB1", "HDB2", "HDB3",
    "HDB4", "HDB5", "HDB6", "POB1", "POB2", "BRS1", "TLMP", "TLP2", "BLD2", "STIB",
    "MEDB", "PODS", "SPDS", "TRDS", "SADS", "HEDS", "CPDS", "SKDS", "BDS2", "PADS",
    "BODS", "SLDS", "FADS", "BSDS", "VILS", NULL
};

void A_Light0();
void A_WeaponReady();
void A_Lower();
void A_Raise();
void A_Punch();
void A_ReFire();
void A_FirePistol();
void A_Light1();
void A_FireShotgun();
void A_Light2();
void A_FireShotgun2();
void A_CheckReload();
void A_OpenShotgun2();
void A_LoadShotgun2();
void A_CloseShotgun2();
void A_FireCGun();
void A_GunFlash();
void A_FireMissile();
void A_Saw();
void A_FirePlasma();
void A_BFGsound();
void A_FireBFG();
void A_BFGSpray();
void A_Explode();
void A_Pain();
void A_PlayerScream();
void A_Fall();
void A_XScream();
void A_Look();
void A_Chase();
void A_FaceTarget();
void A_PosAttack();
void A_Scream();
void A_SPosAttack();
void A_VileChase();
void A_VileStart();
void A_VileTarget();
void A_VileAttack();
void A_StartFire();
void A_Fire();
void A_FireCrackle();
void A_Tracer();
void A_SkelWhoosh();
void A_SkelFist();
void A_SkelMissile();
void A_FatRaise();
void A_FatAttack1();
void A_FatAttack2();
void A_FatAttack3();
void A_BossDeath();
void A_CPosAttack();
void A_CPosRefire();
void A_TroopAttack();
void A_SargAttack();
void A_HeadAttack();
void A_BruisAttack();
void A_SkullAttack();
void A_Metal();
void A_SpidRefire();
void A_BabyMetal();
void A_BspiAttack();
void A_Hoof();
void A_CyberAttack();
void A_PainAttack();
void A_PainDie();
void A_KeenDie();
void A_BrainPain();
void A_BrainScream();
void A_BrainDie();
void A_BrainAwake();
void A_BrainSpit();
void A_SpawnSound();
void A_SpawnFly();
void A_BrainExplode();

state_t states[NUMSTATES] =
{
  //  sprite1   sprite2    frame                           tics               action           nextstate        misc1  misc2       state
    { SPR_TROO, SPR_TROO,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_NULL

    { SPR_SHTG, SPR_SHTG,  4,                                0,               A_Light0,        S_NULL,          0,     0     }, // S_LIGHTDONE

    // Fist
    { SPR_PUNG, SPR_PUNG,  0,                                1,               A_WeaponReady,   S_PUNCH,         0,     0     }, // S_PUNCH
    { SPR_PUNG, SPR_PUNG,  0,                                1,               A_Lower,         S_PUNCHDOWN,     0,     0     }, // S_PUNCHDOWN
    { SPR_PUNG, SPR_PUNG,  0,                                1,               A_Raise,         S_PUNCHUP,       0,     0     }, // S_PUNCHUP
    { SPR_PUNG, SPR_PUNG,  1,                                4,               NULL,            S_PUNCH2,        0,     0     }, // S_PUNCH1
    { SPR_PUNG, SPR_PUNG,  2,                                4,               A_Punch,         S_PUNCH3,        0,     0     }, // S_PUNCH2
    { SPR_PUNG, SPR_PUNG,  3,                                5,               NULL,            S_PUNCH4,        0,     0     }, // S_PUNCH3
    { SPR_PUNG, SPR_PUNG,  2,                                4,               NULL,            S_PUNCH5,        0,     0     }, // S_PUNCH4
    { SPR_PUNG, SPR_PUNG,  1,                                5,               A_ReFire,        S_PUNCH,         0,     0     }, // S_PUNCH5

    // Pistol
    { SPR_PISG, SPR_PISG,  0,                                1,               A_WeaponReady,   S_PISTOL,        0,     0     }, // S_PISTOL
    { SPR_PISG, SPR_PISG,  0,                                1,               A_Lower,         S_PISTOLDOWN,    0,     0     }, // S_PISTOLDOWN
    { SPR_PISG, SPR_PISG,  0,                                1,               A_Raise,         S_PISTOLUP,      0,     0     }, // S_PISTOLUP
    { SPR_PISG, SPR_PISG,  0,                                4,               NULL,            S_PISTOL2,       0,     0     }, // S_PISTOL1
    { SPR_PISG, SPR_PISG,  1,                                6,               A_FirePistol,    S_PISTOL3,       0,     0     }, // S_PISTOL2
    { SPR_PISG, SPR_PISG,  2,                                4,               NULL,            S_PISTOL4,       0,     0     }, // S_PISTOL3
    { SPR_PISG, SPR_PISG,  1,                                5,               A_ReFire,        S_PISTOL,        0,     0     }, // S_PISTOL4
    { SPR_PISF, SPR_PISF,  0 | FF_FULLBRIGHT,                7,               A_Light1,        S_LIGHTDONE,     0,     0     }, // S_PISTOLFLASH

    // Shotgun
    { SPR_SHTG, SPR_SHTG,  0,                                1,               A_WeaponReady,   S_SGUN,          0,     0     }, // S_SGUN
    { SPR_SHTG, SPR_SHTG,  0,                                1,               A_Lower,         S_SGUNDOWN,      0,     0     }, // S_SGUNDOWN
    { SPR_SHTG, SPR_SHTG,  0,                                1,               A_Raise,         S_SGUNUP,        0,     0     }, // S_SGUNUP
    { SPR_SHTG, SPR_SHTG,  0,                                3,               NULL,            S_SGUN2,         0,     0     }, // S_SGUN1
    { SPR_SHTG, SPR_SHTG,  0,                                7,               A_FireShotgun,   S_SGUN3,         0,     0     }, // S_SGUN2
    { SPR_SHTG, SPR_SHTG,  1,                                5,               NULL,            S_SGUN4,         0,     0     }, // S_SGUN3
    { SPR_SHTG, SPR_SHTG,  2,                                5,               NULL,            S_SGUN5,         0,     0     }, // S_SGUN4
    { SPR_SHTG, SPR_SHTG,  3,                                4,               NULL,            S_SGUN6,         0,     0     }, // S_SGUN5
    { SPR_SHTG, SPR_SHTG,  2,                                5,               NULL,            S_SGUN7,         0,     0     }, // S_SGUN6
    { SPR_SHTG, SPR_SHTG,  1,                                5,               NULL,            S_SGUN8,         0,     0     }, // S_SGUN7
    { SPR_SHTG, SPR_SHTG,  0,                                3,               NULL,            S_SGUN9,         0,     0     }, // S_SGUN8
    { SPR_SHTG, SPR_SHTG,  0,                                7,               A_ReFire,        S_SGUN,          0,     0     }, // S_SGUN9
    { SPR_SHTF, SPR_SHTF,  0 | FF_FULLBRIGHT,                4,               A_Light1,        S_SGUNFLASH2,    0,     0     }, // S_SGUNFLASH1
    { SPR_SHTF, SPR_SHTF,  1 | FF_FULLBRIGHT,                3,               A_Light2,        S_LIGHTDONE,     0,     0     }, // S_SGUNFLASH2

    // Super Shotgun
    { SPR_SHT2, SPR_SHT2,  0,                                1,               A_WeaponReady,   S_DSGUN,         0,     0     }, // S_DSGUN
    { SPR_SHT2, SPR_SHT2,  0,                                1,               A_Lower,         S_DSGUNDOWN,     0,     0     }, // S_DSGUNDOWN
    { SPR_SHT2, SPR_SHT2,  0,                                1,               A_Raise,         S_DSGUNUP,       0,     0     }, // S_DSGUNUP
    { SPR_SHT2, SPR_SHT2,  0,                                3,               NULL,            S_DSGUN2,        0,     0     }, // S_DSGUN1
    { SPR_SHT2, SPR_SHT2,  0 | FF_FULLBRIGHT,                7,               A_FireShotgun2,  S_DSGUN3,        0,     0     }, // S_DSGUN2
    { SPR_SHT2, SPR_SHT2,  1,                                7,               NULL,            S_DSGUN4,        0,     0     }, // S_DSGUN3
    { SPR_SHT2, SPR_SHT2,  2,                                7,               A_CheckReload,   S_DSGUN5,        0,     0     }, // S_DSGUN4
    { SPR_SHT2, SPR_SHT2,  3,                                7,               A_OpenShotgun2,  S_DSGUN6,        0,     0     }, // S_DSGUN5
    { SPR_SHT2, SPR_SHT2,  4,                                7,               NULL,            S_DSGUN7,        0,     0     }, // S_DSGUN6
    { SPR_SHT2, SPR_SHT2,  5,                                7,               A_LoadShotgun2,  S_DSGUN8,        0,     0     }, // S_DSGUN7
    { SPR_SHT2, SPR_SHT2,  6,                                6,               NULL,            S_DSGUN9,        0,     0     }, // S_DSGUN8
    { SPR_SHT2, SPR_SHT2,  7,                                6,               A_CloseShotgun2, S_DSGUN10,       0,     0     }, // S_DSGUN9
    { SPR_SHT2, SPR_SHT2,  0,                                5,               A_ReFire,        S_DSGUN,         0,     0     }, // S_DSGUN10
    { SPR_SHT2, SPR_SHT2,  1,                                7,               NULL,            S_DSNR2,         0,     0     }, // S_DSNR1
    { SPR_SHT2, SPR_SHT2,  0,                                3,               NULL,            S_DSGUNDOWN,     0,     0     }, // S_DSNR2
    { SPR_SHT2, SPR_SHT2,  8 | FF_FULLBRIGHT,                4,               A_Light1,        S_DSGUNFLASH2,   0,     0     }, // S_DSGUNFLASH1
    { SPR_SHT2, SPR_SHT2,  9 | FF_FULLBRIGHT,                4,               A_Light2,        S_LIGHTDONE,     0,     0     }, // S_DSGUNFLASH2

    // Chaingun
    { SPR_CHGG, SPR_CHGG,  0,                                1,               A_WeaponReady,   S_CHAIN,         0,     0     }, // S_CHAIN
    { SPR_CHGG, SPR_CHGG,  0,                                1,               A_Lower,         S_CHAINDOWN,     0,     0     }, // S_CHAINDOWN
    { SPR_CHGG, SPR_CHGG,  0,                                1,               A_Raise,         S_CHAINUP,       0,     0     }, // S_CHAINUP
    { SPR_CHGG, SPR_CHGG,  0,                                4,               A_FireCGun,      S_CHAIN2,        0,     0     }, // S_CHAIN1
    { SPR_CHGG, SPR_CHGG,  1,                                4,               A_FireCGun,      S_CHAIN3,        0,     0     }, // S_CHAIN2
    { SPR_CHGG, SPR_CHGG,  1,                                0,               A_ReFire,        S_CHAIN,         0,     0     }, // S_CHAIN3
    { SPR_CHGF, SPR_CHGF,  0 | FF_FULLBRIGHT,                5,               A_Light1,        S_LIGHTDONE,     0,     0     }, // S_CHAINFLASH1
    { SPR_CHGF, SPR_CHGF,  1 | FF_FULLBRIGHT,                5,               A_Light2,        S_LIGHTDONE,     0,     0     }, // S_CHAINFLASH2

    // Rocket Launcher
    { SPR_MISG, SPR_MISG,  0,                                1,               A_WeaponReady,   S_MISSILE,       0,     0     }, // S_MISSILE
    { SPR_MISG, SPR_MISG,  0,                                1,               A_Lower,         S_MISSILEDOWN,   0,     0     }, // S_MISSILEDOWN
    { SPR_MISG, SPR_MISG,  0,                                1,               A_Raise,         S_MISSILEUP,     0,     0     }, // S_MISSILEUP
    { SPR_MISG, SPR_MISG,  1,                                8,               A_GunFlash,      S_MISSILE2,      0,     0     }, // S_MISSILE1
    { SPR_MISG, SPR_MISG,  1,                               12,               A_FireMissile,   S_MISSILE3,      0,     0     }, // S_MISSILE2
    { SPR_MISG, SPR_MISG,  1,                                0,               A_ReFire,        S_MISSILE,       0,     0     }, // S_MISSILE3
    { SPR_MISF, SPR_MISF,  0 | FF_FULLBRIGHT,                3,               A_Light1,        S_MISSILEFLASH2, 0,     0     }, // S_MISSILEFLASH1
    { SPR_MISF, SPR_MISF,  1 | FF_FULLBRIGHT,                4,               NULL,            S_MISSILEFLASH3, 0,     0     }, // S_MISSILEFLASH2
    { SPR_MISF, SPR_MISF,  2 | FF_FULLBRIGHT,                4,               A_Light2,        S_MISSILEFLASH4, 0,     0     }, // S_MISSILEFLASH3
    { SPR_MISF, SPR_MISF,  3 | FF_FULLBRIGHT,                4,               A_Light2,        S_LIGHTDONE,     0,     0     }, // S_MISSILEFLASH4

    // Chainsaw
    { SPR_SAWG, SPR_SAWG,  2,                                4,               A_WeaponReady,   S_SAWB,          0,     0     }, // S_SAW
    { SPR_SAWG, SPR_SAWG,  3,                                4,               A_WeaponReady,   S_SAW,           0,     0     }, // S_SAWB
    { SPR_SAWG, SPR_SAWG,  2,                                1,               A_Lower,         S_SAWDOWN,       0,     0     }, // S_SAWDOWN
    { SPR_SAWG, SPR_SAWG,  2,                                1,               A_Raise,         S_SAWUP,         0,     0     }, // S_SAWUP
    { SPR_SAWG, SPR_SAWG,  0,                                4,               A_Saw,           S_SAW2,          0,     0     }, // S_SAW1
    { SPR_SAWG, SPR_SAWG,  1,                                4,               A_Saw,           S_SAW3,          0,     0     }, // S_SAW2
    { SPR_SAWG, SPR_SAWG,  1,                                0,               A_ReFire,        S_SAW,           0,     0     }, // S_SAW3

    // Plasma Rifle
    { SPR_PLSG, SPR_PLSG,  0,                                1,               A_WeaponReady,   S_PLASMA,        0,     0     }, // S_PLASMA
    { SPR_PLSG, SPR_PLSG,  0,                                1,               A_Lower,         S_PLASMADOWN,    0,     0     }, // S_PLASMADOWN
    { SPR_PLSG, SPR_PLSG,  0,                                1,               A_Raise,         S_PLASMAUP,      0,     0     }, // S_PLASMAUP
    { SPR_PLSG, SPR_PLSG,  0,                                3,               A_FirePlasma,    S_PLASMA2,       0,     0     }, // S_PLASMA1
    { SPR_PLSG, SPR_PLSG,  1,                               20,               A_ReFire,        S_PLASMA,        0,     0     }, // S_PLASMA2
    { SPR_PLSF, SPR_PLSF,  0 | FF_FULLBRIGHT,                4,               A_Light1,        S_LIGHTDONE,     0,     0     }, // S_PLASMAFLASH1
    { SPR_PLSF, SPR_PLSF,  1 | FF_FULLBRIGHT,                4,               A_Light1,        S_LIGHTDONE,     0,     0     }, // S_PLASMAFLASH2

    // BFG 9000
    { SPR_BFGG, SPR_BFGG,  0,                                1,               A_WeaponReady,   S_BFG,           0,     0     }, // S_BFG
    { SPR_BFGG, SPR_BFGG,  0,                                1,               A_Lower,         S_BFGDOWN,       0,     0     }, // S_BFGDOWN
    { SPR_BFGG, SPR_BFGG,  0,                                1,               A_Raise,         S_BFGUP,         0,     0     }, // S_BFGUP
    { SPR_BFGG, SPR_BFGG,  0,                               20,               A_BFGsound,      S_BFG2,          0,     0     }, // S_BFG1
    { SPR_BFGG, SPR_BFGG,  1,                               10,               A_GunFlash,      S_BFG3,          0,     0     }, // S_BFG2
    { SPR_BFGG, SPR_BFGG,  1,                               10,               A_FireBFG,       S_BFG4,          0,     0     }, // S_BFG3
    { SPR_BFGG, SPR_BFGG,  1,                               20,               A_ReFire,        S_BFG,           0,     0     }, // S_BFG4
    { SPR_BFGF, SPR_BFGF,  0 | FF_FULLBRIGHT,               11,               A_Light1,        S_BFGFLASH2,     0,     0     }, // S_BFGFLASH1
    { SPR_BFGF, SPR_BFGF,  1 | FF_FULLBRIGHT,                6,               A_Light2,        S_LIGHTDONE,     0,     0     }, // S_BFGFLASH2

    // Blood (MT_BLOOD)
    { SPR_BLUD, SPR_BLUD,  2,                                8,               NULL,            S_BLOOD2,        0,     0     }, // S_BLOOD1
    { SPR_BLUD, SPR_BLUD,  1,                                8,               NULL,            S_BLOOD3,        0,     0     }, // S_BLOOD2
    { SPR_BLUD, SPR_BLUD,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_BLOOD3

    // Bullet Puff (MT_PUFF)
    { SPR_PUFF, SPR_PUFF,  0 | FF_FULLBRIGHT,                4,               NULL,            S_PUFF2,         0,     0     }, // S_PUFF1
    { SPR_PUFF, SPR_PUFF,  1,                                4,               NULL,            S_PUFF3,         0,     0     }, // S_PUFF2
    { SPR_PUFF, SPR_PUFF,  2,                                4,               NULL,            S_PUFF4,         0,     0     }, // S_PUFF3
    { SPR_PUFF, SPR_PUFF,  3,                                4,               NULL,            S_NULL,          0,     0     }, // S_PUFF4

    // Imp Projectile (MT_TROOPSHOT)
    { SPR_BAL1, SPR_BAL1,  0 | FF_FULLBRIGHT,                4,               NULL,            S_TBALL2,        0,     0     }, // S_TBALL1
    { SPR_BAL1, SPR_BAL1,  1 | FF_FULLBRIGHT,                4,               NULL,            S_TBALL1,        0,     0     }, // S_TBALL2
    { SPR_BAL1, SPR_BAL1,  2 | FF_FULLBRIGHT,                6,               NULL,            S_TBALLX2,       0,     0     }, // S_TBALLX1
    { SPR_BAL1, SPR_BAL1,  3 | FF_FULLBRIGHT,                6,               NULL,            S_TBALLX3,       0,     0     }, // S_TBALLX2
    { SPR_BAL1, SPR_BAL1,  4 | FF_FULLBRIGHT,                6,               NULL,            S_NULL,          0,     0     }, // S_TBALLX3

    // Cacodemon Projectile (MT_HEADSHOT)
    { SPR_BAL2, SPR_BAL2,  0 | FF_FULLBRIGHT,                4,               NULL,            S_RBALL2,        0,     0     }, // S_RBALL1
    { SPR_BAL2, SPR_BAL2,  1 | FF_FULLBRIGHT,                4,               NULL,            S_RBALL1,        0,     0     }, // S_RBALL2
    { SPR_BAL2, SPR_BAL2,  2 | FF_FULLBRIGHT,                6,               NULL,            S_RBALLX2,       0,     0     }, // S_RBALLX1
    { SPR_BAL2, SPR_BAL2,  3 | FF_FULLBRIGHT,                6,               NULL,            S_RBALLX3,       0,     0     }, // S_RBALLX2
    { SPR_BAL2, SPR_BAL2,  4 | FF_FULLBRIGHT,                6,               NULL,            S_NULL,          0,     0     }, // S_RBALLX3

    // Plasma Rifle Projectile (MT_PLASMA)
    { SPR_PLSS, SPR_PLSS,  0 | FF_FULLBRIGHT,                6,               NULL,            S_PLASBALL2,     0,     0     }, // S_PLASBALL
    { SPR_PLSS, SPR_PLSS,  1 | FF_FULLBRIGHT,                6,               NULL,            S_PLASBALL,      0,     0     }, // S_PLASBALL2
    { SPR_PLSE, SPR_PLSE,  0 | FF_FULLBRIGHT,                4,               NULL,            S_PLASEXP2,      0,     0     }, // S_PLASEXP
    { SPR_PLSE, SPR_PLSE,  1 | FF_FULLBRIGHT,                4,               NULL,            S_PLASEXP3,      0,     0     }, // S_PLASEXP2
    { SPR_PLSE, SPR_PLSE,  2 | FF_FULLBRIGHT,                4,               NULL,            S_PLASEXP4,      0,     0     }, // S_PLASEXP3
    { SPR_PLSE, SPR_PLSE,  3 | FF_FULLBRIGHT,                4,               NULL,            S_PLASEXP5,      0,     0     }, // S_PLASEXP4
    { SPR_PLSE, SPR_PLSE,  4 | FF_FULLBRIGHT,                4,               NULL,            S_NULL,          0,     0     }, // S_PLASEXP5

    // Rocket Launcher Projectile (MT_ROCKET)
    { SPR_MISL, SPR_MISL,  0 | FF_FULLBRIGHT,                1,               NULL,            S_ROCKET,        0,     0     }, // S_ROCKET

    // BFG 9000 Projectile (MT_BFG)
    { SPR_BFS1, SPR_BFS1,  0 | FF_FULLBRIGHT,                4,               NULL,            S_BFGSHOT2,      0,     0     }, // S_BFGSHOT
    { SPR_BFS1, SPR_BFS1,  1 | FF_FULLBRIGHT,                4,               NULL,            S_BFGSHOT,       0,     0     }, // S_BFGSHOT2
    { SPR_BFE1, SPR_BFE1,  0 | FF_FULLBRIGHT,                8,               NULL,            S_BFGLAND2,      0,     0     }, // S_BFGLAND
    { SPR_BFE1, SPR_BFE1,  1 | FF_FULLBRIGHT,                8,               NULL,            S_BFGLAND3,      0,     0     }, // S_BFGLAND2
    { SPR_BFE1, SPR_BFE1,  2 | FF_FULLBRIGHT,                8,               A_BFGSpray,      S_BFGLAND4,      0,     0     }, // S_BFGLAND3
    { SPR_BFE1, SPR_BFE1,  3 | FF_FULLBRIGHT,                8,               NULL,            S_BFGLAND5,      0,     0     }, // S_BFGLAND4
    { SPR_BFE1, SPR_BFE1,  4 | FF_FULLBRIGHT,                8,               NULL,            S_BFGLAND6,      0,     0     }, // S_BFGLAND5
    { SPR_BFE1, SPR_BFE1,  5 | FF_FULLBRIGHT,                8,               NULL,            S_NULL,          0,     0     }, // S_BFGLAND6

    // BFG 9000 Secondary Projectile (MT_EXTRABFG)
    { SPR_BFE2, SPR_BFE2,  0 | FF_FULLBRIGHT,                8,               NULL,            S_BFGEXP2,       0,     0     }, // S_BFGEXP
    { SPR_BFE2, SPR_BFE2,  1 | FF_FULLBRIGHT,                8,               NULL,            S_BFGEXP3,       0,     0     }, // S_BFGEXP2
    { SPR_BFE2, SPR_BFE2,  2 | FF_FULLBRIGHT,                8,               NULL,            S_BFGEXP4,       0,     0     }, // S_BFGEXP3
    { SPR_BFE2, SPR_BFE2,  3 | FF_FULLBRIGHT,                8,               NULL,            S_NULL,          0,     0     }, // S_BFGEXP4
    { SPR_MISL, SPR_MISL,  1 | FF_FULLBRIGHT,                8,               A_Explode,       S_EXPLODE2,      0,     0     }, // S_EXPLODE1
    { SPR_MISL, SPR_MISL,  2 | FF_FULLBRIGHT,                6,               NULL,            S_EXPLODE3,      0,     0     }, // S_EXPLODE2
    { SPR_MISL, SPR_MISL,  3 | FF_FULLBRIGHT,                4,               NULL,            S_NULL,          0,     0     }, // S_EXPLODE3

    // Teleport Fog (MT_TFOG)
    { SPR_TFOG, SPR_TFOG,  0 | FF_FULLBRIGHT,                6,               NULL,            S_TFOG01,        0,     0     }, // S_TFOG
    { SPR_TFOG, SPR_TFOG,  1 | FF_FULLBRIGHT,                6,               NULL,            S_TFOG02,        0,     0     }, // S_TFOG01
    { SPR_TFOG, SPR_TFOG,  0 | FF_FULLBRIGHT,                6,               NULL,            S_TFOG2,         0,     0     }, // S_TFOG02
    { SPR_TFOG, SPR_TFOG,  1 | FF_FULLBRIGHT,                6,               NULL,            S_TFOG3,         0,     0     }, // S_TFOG2
    { SPR_TFOG, SPR_TFOG,  2 | FF_FULLBRIGHT,                6,               NULL,            S_TFOG4,         0,     0     }, // S_TFOG3
    { SPR_TFOG, SPR_TFOG,  3 | FF_FULLBRIGHT,                6,               NULL,            S_TFOG5,         0,     0     }, // S_TFOG4
    { SPR_TFOG, SPR_TFOG,  4 | FF_FULLBRIGHT,                6,               NULL,            S_TFOG6,         0,     0     }, // S_TFOG5
    { SPR_TFOG, SPR_TFOG,  5 | FF_FULLBRIGHT,                6,               NULL,            S_TFOG7,         0,     0     }, // S_TFOG6
    { SPR_TFOG, SPR_TFOG,  6 | FF_FULLBRIGHT,                6,               NULL,            S_TFOG8,         0,     0     }, // S_TFOG7
    { SPR_TFOG, SPR_TFOG,  7 | FF_FULLBRIGHT,                6,               NULL,            S_TFOG9,         0,     0     }, // S_TFOG8
    { SPR_TFOG, SPR_TFOG,  8 | FF_FULLBRIGHT,                6,               NULL,            S_TFOG10,        0,     0     }, // S_TFOG9
    { SPR_TFOG, SPR_TFOG,  9 | FF_FULLBRIGHT,                6,               NULL,            S_NULL,          0,     0     }, // S_TFOG10

    // Item Fog  Item Fog (MT_IFOG)
    { SPR_IFOG, SPR_IFOG,  0 | FF_FULLBRIGHT,                6,               NULL,            S_IFOG01,        0,     0     }, // S_IFOG
    { SPR_IFOG, SPR_IFOG,  1 | FF_FULLBRIGHT,                6,               NULL,            S_IFOG02,        0,     0     }, // S_IFOG01
    { SPR_IFOG, SPR_IFOG,  0 | FF_FULLBRIGHT,                6,               NULL,            S_IFOG2,         0,     0     }, // S_IFOG02
    { SPR_IFOG, SPR_IFOG,  1 | FF_FULLBRIGHT,                6,               NULL,            S_IFOG3,         0,     0     }, // S_IFOG2
    { SPR_IFOG, SPR_IFOG,  2 | FF_FULLBRIGHT,                6,               NULL,            S_IFOG4,         0,     0     }, // S_IFOG3
    { SPR_IFOG, SPR_IFOG,  3 | FF_FULLBRIGHT,                6,               NULL,            S_IFOG5,         0,     0     }, // S_IFOG4
    { SPR_IFOG, SPR_IFOG,  4 | FF_FULLBRIGHT,                6,               NULL,            S_NULL,          0,     0     }, // S_IFOG5

    // Player (MT_PLAYER)
    { SPR_PLAY, SPR_PLAY,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_PLAY
    { SPR_PLAY, SPR_PLAY,  0,                                4,               NULL,            S_PLAY_RUN2,     0,     0     }, // S_PLAY_RUN1
    { SPR_PLAY, SPR_PLAY,  1,                                4,               NULL,            S_PLAY_RUN3,     0,     0     }, // S_PLAY_RUN2
    { SPR_PLAY, SPR_PLAY,  2,                                4,               NULL,            S_PLAY_RUN4,     0,     0     }, // S_PLAY_RUN3
    { SPR_PLAY, SPR_PLAY,  3,                                4,               NULL,            S_PLAY_RUN1,     0,     0     }, // S_PLAY_RUN4
    { SPR_PLAY, SPR_PLAY,  4,                               12,               NULL,            S_PLAY,          0,     0     }, // S_PLAY_ATK1
    { SPR_PLAY, SPR_PLAY,  5 | FF_FULLBRIGHT,                6,               NULL,            S_PLAY_ATK1,     0,     0     }, // S_PLAY_ATK2
    { SPR_PLAY, SPR_PLAY,  6,                                4,               NULL,            S_PLAY_PAIN2,    0,     0     }, // S_PLAY_PAIN
    { SPR_PLAY, SPR_PLAY,  6,                                4,               A_Pain,          S_PLAY,          0,     0     }, // S_PLAY_PAIN2
    { SPR_PLAY, SPR_PLAY,  7,                               10,               NULL,            S_PLAY_DIE2,     0,     0     }, // S_PLAY_DIE1
    { SPR_PLAY, SPR_PLAY,  8,                               10,               A_PlayerScream,  S_PLAY_DIE3,     0,     0     }, // S_PLAY_DIE2
    { SPR_PLAY, SPR_PLAY,  9,                               10,               A_Fall,          S_PLAY_DIE4,     0,     0     }, // S_PLAY_DIE3
    { SPR_PLAY, SPR_PLAY, 10,                               10,               NULL,            S_PLAY_DIE5,     0,     0     }, // S_PLAY_DIE4
    { SPR_PLAY, SPR_PLAY, 11,                               10,               NULL,            S_PLAY_DIE6,     0,     0     }, // S_PLAY_DIE5
    { SPR_PLAY, SPR_PLAY, 12,                               10,               NULL,            S_PLAY_DIE7,     0,     0     }, // S_PLAY_DIE6

    // Player Death (MT_MISC62)
    { SPR_PLAY, SPR_PLAY, 13,                               -1,               NULL,            S_NULL,          0,     0     }, // S_PLAY_DIE7
    { SPR_PLAY, SPR_PLAY, 14,                                5,               NULL,            S_PLAY_XDIE2,    0,     0     }, // S_PLAY_XDIE1
    { SPR_PLAY, SPR_PLAY, 15,                                5,               A_XScream,       S_PLAY_XDIE3,    0,     0     }, // S_PLAY_XDIE2
    { SPR_PLAY, SPR_PLAY, 16,                                5,               A_Fall,          S_PLAY_XDIE4,    0,     0     }, // S_PLAY_XDIE3
    { SPR_PLAY, SPR_PLAY, 17,                                5,               NULL,            S_PLAY_XDIE5,    0,     0     }, // S_PLAY_XDIE4
    { SPR_PLAY, SPR_PLAY, 18,                                5,               NULL,            S_PLAY_XDIE6,    0,     0     }, // S_PLAY_XDIE5
    { SPR_PLAY, SPR_PLAY, 19,                                5,               NULL,            S_PLAY_XDIE7,    0,     0     }, // S_PLAY_XDIE6
    { SPR_PLAY, SPR_PLAY, 20,                                5,               NULL,            S_PLAY_XDIE8,    0,     0     }, // S_PLAY_XDIE7
    { SPR_PLAY, SPR_PLAY, 21,                                5,               NULL,            S_PLAY_XDIE9,    0,     0     }, // S_PLAY_XDIE8

    // Player Corpse (MT_MISC68 and MT_MISC69)
    { SPR_PLAY, SPR_PLAY, 22,                               -1,               NULL,            S_NULL,          0,     0     }, // S_PLAY_XDIE9

    // Zombieman (MT_POSSESSED)
    { SPR_POSS, SPR_PODS,  0,                               10,               A_Look,          S_POSS_STND2,    0,     0     }, // S_POSS_STND
    { SPR_POSS, SPR_PODS,  1,                               10,               A_Look,          S_POSS_STND,     0,     0     }, // S_POSS_STND2
    { SPR_POSS, SPR_PODS,  0,                                4,               A_Chase,         S_POSS_RUN2,     0,     0     }, // S_POSS_RUN1
    { SPR_POSS, SPR_PODS,  0,                                4,               A_Chase,         S_POSS_RUN3,     0,     0     }, // S_POSS_RUN2
    { SPR_POSS, SPR_PODS,  1,                                4,               A_Chase,         S_POSS_RUN4,     0,     0     }, // S_POSS_RUN3
    { SPR_POSS, SPR_PODS,  1,                                4,               A_Chase,         S_POSS_RUN5,     0,     0     }, // S_POSS_RUN4
    { SPR_POSS, SPR_PODS,  2,                                4,               A_Chase,         S_POSS_RUN6,     0,     0     }, // S_POSS_RUN5
    { SPR_POSS, SPR_PODS,  2,                                4,               A_Chase,         S_POSS_RUN7,     0,     0     }, // S_POSS_RUN6
    { SPR_POSS, SPR_PODS,  3,                                4,               A_Chase,         S_POSS_RUN8,     0,     0     }, // S_POSS_RUN7
    { SPR_POSS, SPR_PODS,  3,                                4,               A_Chase,         S_POSS_RUN1,     0,     0     }, // S_POSS_RUN8
    { SPR_POSS, SPR_PODS,  4,                               10,               A_FaceTarget,    S_POSS_ATK2,     0,     0     }, // S_POSS_ATK1
    { SPR_POSS, SPR_PODS,  5 | FF_FULLBRIGHT,                8,               A_PosAttack,     S_POSS_ATK3,     0,     0     }, // S_POSS_ATK2
    { SPR_POSS, SPR_PODS,  4,                                8,               NULL,            S_POSS_RUN1,     0,     0     }, // S_POSS_ATK3
    { SPR_POSS, SPR_PODS,  6,                                3,               NULL,            S_POSS_PAIN2,    0,     0     }, // S_POSS_PAIN
    { SPR_POSS, SPR_PODS,  6,                                3,               A_Pain,          S_POSS_RUN1,     0,     0     }, // S_POSS_PAIN2
    { SPR_POSS, SPR_PODS,  7,                                5,               NULL,            S_POSS_DIE2,     0,     0     }, // S_POSS_DIE1
    { SPR_POSS, SPR_PODS,  8,                                5,               A_Scream,        S_POSS_DIE3,     0,     0     }, // S_POSS_DIE2
    { SPR_POSS, SPR_PODS,  9,                                5,               A_Fall,          S_POSS_DIE4,     0,     0     }, // S_POSS_DIE3
    { SPR_POSS, SPR_PODS, 10,                                5,               NULL,            S_POSS_DIE5,     0,     0     }, // S_POSS_DIE4

    // Zombieman Death (MT_MISC63)
    { SPR_POSS, SPR_PODS, 11,                               -1,               NULL,            S_NULL,          0,     0     }, // S_POSS_DIE5
    { SPR_POSS, SPR_PODS, 12,                                5,               NULL,            S_POSS_XDIE2,    0,     0     }, // S_POSS_XDIE1
    { SPR_POSS, SPR_PODS, 13,                                5,               A_XScream,       S_POSS_XDIE3,    0,     0     }, // S_POSS_XDIE2
    { SPR_POSS, SPR_PODS, 14,                                5,               A_Fall,          S_POSS_XDIE4,    0,     0     }, // S_POSS_XDIE3
    { SPR_POSS, SPR_PODS, 15,                                5,               NULL,            S_POSS_XDIE5,    0,     0     }, // S_POSS_XDIE4
    { SPR_POSS, SPR_PODS, 16,                                5,               NULL,            S_POSS_XDIE6,    0,     0     }, // S_POSS_XDIE5
    { SPR_POSS, SPR_PODS, 17,                                5,               NULL,            S_POSS_XDIE7,    0,     0     }, // S_POSS_XDIE6
    { SPR_POSS, SPR_PODS, 18,                                5,               NULL,            S_POSS_XDIE8,    0,     0     }, // S_POSS_XDIE7
    { SPR_POSS, SPR_PODS, 19,                                5,               NULL,            S_POSS_XDIE9,    0,     0     }, // S_POSS_XDIE8
    { SPR_POSS, SPR_PODS, 20,                               -1,               NULL,            S_NULL,          0,     0     }, // S_POSS_XDIE9
    { SPR_POSS, SPR_PODS, 10,                                5,               NULL,            S_POSS_RAISE2,   0,     0     }, // S_POSS_RAISE1
    { SPR_POSS, SPR_PODS,  9,                                5,               NULL,            S_POSS_RAISE3,   0,     0     }, // S_POSS_RAISE2
    { SPR_POSS, SPR_PODS,  8,                                5,               NULL,            S_POSS_RAISE4,   0,     0     }, // S_POSS_RAISE3
    { SPR_POSS, SPR_PODS,  7,                                5,               NULL,            S_POSS_RUN1,     0,     0     }, // S_POSS_RAISE4

    // Shotgun Guy (MT_SHOTGUY)
    { SPR_SPOS, SPR_SPDS,  0,                               10,               A_Look,          S_SPOS_STND2,    0,     0     }, // S_SPOS_STND
    { SPR_SPOS, SPR_SPDS,  1,                               10,               A_Look,          S_SPOS_STND,     0,     0     }, // S_SPOS_STND2
    { SPR_SPOS, SPR_SPDS,  0,                                3,               A_Chase,         S_SPOS_RUN2,     0,     0     }, // S_SPOS_RUN1
    { SPR_SPOS, SPR_SPDS,  0,                                3,               A_Chase,         S_SPOS_RUN3,     0,     0     }, // S_SPOS_RUN2
    { SPR_SPOS, SPR_SPDS,  1,                                3,               A_Chase,         S_SPOS_RUN4,     0,     0     }, // S_SPOS_RUN3
    { SPR_SPOS, SPR_SPDS,  1,                                3,               A_Chase,         S_SPOS_RUN5,     0,     0     }, // S_SPOS_RUN4
    { SPR_SPOS, SPR_SPDS,  2,                                3,               A_Chase,         S_SPOS_RUN6,     0,     0     }, // S_SPOS_RUN5
    { SPR_SPOS, SPR_SPDS,  2,                                3,               A_Chase,         S_SPOS_RUN7,     0,     0     }, // S_SPOS_RUN6
    { SPR_SPOS, SPR_SPDS,  3,                                3,               A_Chase,         S_SPOS_RUN8,     0,     0     }, // S_SPOS_RUN7
    { SPR_SPOS, SPR_SPDS,  3,                                3,               A_Chase,         S_SPOS_RUN1,     0,     0     }, // S_SPOS_RUN8
    { SPR_SPOS, SPR_SPDS,  4,                               10,               A_FaceTarget,    S_SPOS_ATK2,     0,     0     }, // S_SPOS_ATK1
    { SPR_SPOS, SPR_SPDS,  5 | FF_FULLBRIGHT,               10,               A_SPosAttack,    S_SPOS_ATK3,     0,     0     }, // S_SPOS_ATK2
    { SPR_SPOS, SPR_SPDS,  4,                               10,               NULL,            S_SPOS_RUN1,     0,     0     }, // S_SPOS_ATK3
    { SPR_SPOS, SPR_SPDS,  6,                                3,               NULL,            S_SPOS_PAIN2,    0,     0     }, // S_SPOS_PAIN
    { SPR_SPOS, SPR_SPDS,  6,                                3,               A_Pain,          S_SPOS_RUN1,     0,     0     }, // S_SPOS_PAIN2
    { SPR_SPOS, SPR_SPDS,  7,                                5,               NULL,            S_SPOS_DIE2,     0,     0     }, // S_SPOS_DIE1
    { SPR_SPOS, SPR_SPDS,  8,                                5,               A_Scream,        S_SPOS_DIE3,     0,     0     }, // S_SPOS_DIE2
    { SPR_SPOS, SPR_SPDS,  9,                                5,               A_Fall,          S_SPOS_DIE4,     0,     0     }, // S_SPOS_DIE3
    { SPR_SPOS, SPR_SPDS, 10,                                5,               NULL,            S_SPOS_DIE5,     0,     0     }, // S_SPOS_DIE4

    // Shotgun Guy Death (MT_MISC67)
    { SPR_SPOS, SPR_SPDS, 11,                               -1,               NULL,            S_NULL,          0,     0     }, // S_SPOS_DIE5
    { SPR_SPOS, SPR_SPDS, 12,                                5,               NULL,            S_SPOS_XDIE2,    0,     0     }, // S_SPOS_XDIE1
    { SPR_SPOS, SPR_SPDS, 13,                                5,               A_XScream,       S_SPOS_XDIE3,    0,     0     }, // S_SPOS_XDIE2
    { SPR_SPOS, SPR_SPDS, 14,                                5,               A_Fall,          S_SPOS_XDIE4,    0,     0     }, // S_SPOS_XDIE3
    { SPR_SPOS, SPR_SPDS, 15,                                5,               NULL,            S_SPOS_XDIE5,    0,     0     }, // S_SPOS_XDIE4
    { SPR_SPOS, SPR_SPDS, 16,                                5,               NULL,            S_SPOS_XDIE6,    0,     0     }, // S_SPOS_XDIE5
    { SPR_SPOS, SPR_SPDS, 17,                                5,               NULL,            S_SPOS_XDIE7,    0,     0     }, // S_SPOS_XDIE6
    { SPR_SPOS, SPR_SPDS, 18,                                5,               NULL,            S_SPOS_XDIE8,    0,     0     }, // S_SPOS_XDIE7
    { SPR_SPOS, SPR_SPDS, 19,                                5,               NULL,            S_SPOS_XDIE9,    0,     0     }, // S_SPOS_XDIE8
    { SPR_SPOS, SPR_SPDS, 20,                               -1,               NULL,            S_NULL,          0,     0     }, // S_SPOS_XDIE9
    { SPR_SPOS, SPR_SPDS, 11,                                5,               NULL,            S_SPOS_RAISE2,   0,     0     }, // S_SPOS_RAISE1
    { SPR_SPOS, SPR_SPDS, 10,                                5,               NULL,            S_SPOS_RAISE3,   0,     0     }, // S_SPOS_RAISE2
    { SPR_SPOS, SPR_SPDS,  9,                                5,               NULL,            S_SPOS_RAISE4,   0,     0     }, // S_SPOS_RAISE3
    { SPR_SPOS, SPR_SPDS,  8,                                5,               NULL,            S_SPOS_RAISE5,   0,     0     }, // S_SPOS_RAISE4
    { SPR_SPOS, SPR_SPDS,  7,                                5,               NULL,            S_SPOS_RUN1,     0,     0     }, // S_SPOS_RAISE5

    // Arch-vile (MT_VILE)
    { SPR_VILE, SPR_VILS,  0,                               10,               A_Look,          S_VILE_STND2,    0,     0     }, // S_VILE_STND
    { SPR_VILE, SPR_VILS,  1,                               10,               A_Look,          S_VILE_STND,     0,     0     }, // S_VILE_STND2
    { SPR_VILE, SPR_VILS,  0,                                2,               A_VileChase,     S_VILE_RUN2,     0,     0     }, // S_VILE_RUN1
    { SPR_VILE, SPR_VILS,  0,                                2,               A_VileChase,     S_VILE_RUN3,     0,     0     }, // S_VILE_RUN2
    { SPR_VILE, SPR_VILS,  1,                                2,               A_VileChase,     S_VILE_RUN4,     0,     0     }, // S_VILE_RUN3
    { SPR_VILE, SPR_VILS,  1,                                2,               A_VileChase,     S_VILE_RUN5,     0,     0     }, // S_VILE_RUN4
    { SPR_VILE, SPR_VILS,  2,                                2,               A_VileChase,     S_VILE_RUN6,     0,     0     }, // S_VILE_RUN5
    { SPR_VILE, SPR_VILS,  2,                                2,               A_VileChase,     S_VILE_RUN7,     0,     0     }, // S_VILE_RUN6
    { SPR_VILE, SPR_VILS,  3,                                2,               A_VileChase,     S_VILE_RUN8,     0,     0     }, // S_VILE_RUN7
    { SPR_VILE, SPR_VILS,  3,                                2,               A_VileChase,     S_VILE_RUN9,     0,     0     }, // S_VILE_RUN8
    { SPR_VILE, SPR_VILS,  4,                                2,               A_VileChase,     S_VILE_RUN10,    0,     0     }, // S_VILE_RUN9
    { SPR_VILE, SPR_VILS,  4,                                2,               A_VileChase,     S_VILE_RUN11,    0,     0     }, // S_VILE_RUN10
    { SPR_VILE, SPR_VILS,  5,                                2,               A_VileChase,     S_VILE_RUN12,    0,     0     }, // S_VILE_RUN11
    { SPR_VILE, SPR_VILS,  5,                                2,               A_VileChase,     S_VILE_RUN1,     0,     0     }, // S_VILE_RUN12
    { SPR_VILE, SPR_VILS,  6 | FF_FULLBRIGHT,                0,               A_VileStart,     S_VILE_ATK2,     0,     0     }, // S_VILE_ATK1
    { SPR_VILE, SPR_VILS,  6 | FF_FULLBRIGHT,               10,               A_FaceTarget,    S_VILE_ATK3,     0,     0     }, // S_VILE_ATK2
    { SPR_VILE, SPR_VILS,  7 | FF_FULLBRIGHT,                8,               A_VileTarget,    S_VILE_ATK4,     0,     0     }, // S_VILE_ATK3
    { SPR_VILE, SPR_VILS,  8 | FF_FULLBRIGHT,                8,               A_FaceTarget,    S_VILE_ATK5,     0,     0     }, // S_VILE_ATK4
    { SPR_VILE, SPR_VILS,  9 | FF_FULLBRIGHT,                8,               A_FaceTarget,    S_VILE_ATK6,     0,     0     }, // S_VILE_ATK5
    { SPR_VILE, SPR_VILS, 10 | FF_FULLBRIGHT,                8,               A_FaceTarget,    S_VILE_ATK7,     0,     0     }, // S_VILE_ATK6
    { SPR_VILE, SPR_VILS, 11 | FF_FULLBRIGHT,                8,               A_FaceTarget,    S_VILE_ATK8,     0,     0     }, // S_VILE_ATK7
    { SPR_VILE, SPR_VILS, 12 | FF_FULLBRIGHT,                8,               A_FaceTarget,    S_VILE_ATK9,     0,     0     }, // S_VILE_ATK8
    { SPR_VILE, SPR_VILS, 13 | FF_FULLBRIGHT,                8,               A_FaceTarget,    S_VILE_ATK10,    0,     0     }, // S_VILE_ATK9
    { SPR_VILE, SPR_VILS, 14 | FF_FULLBRIGHT,                8,               A_VileAttack,    S_VILE_ATK11,    0,     0     }, // S_VILE_ATK10
    { SPR_VILE, SPR_VILS, 15 | FF_FULLBRIGHT,               20,               NULL,            S_VILE_RUN1,     0,     0     }, // S_VILE_ATK11
    { SPR_VILE, SPR_VILS, 26 | FF_FULLBRIGHT,               10,               NULL,            S_VILE_HEAL2,    0,     0     }, // S_VILE_HEAL1
    { SPR_VILE, SPR_VILS, 27 | FF_FULLBRIGHT,               10,               NULL,            S_VILE_HEAL3,    0,     0     }, // S_VILE_HEAL2
    { SPR_VILE, SPR_VILS, 28 | FF_FULLBRIGHT,               10,               NULL,            S_VILE_RUN1,     0,     0     }, // S_VILE_HEAL3
    { SPR_VILE, SPR_VILS, 16,                                5,               NULL,            S_VILE_PAIN2,    0,     0     }, // S_VILE_PAIN
    { SPR_VILE, SPR_VILS, 16,                                5,               A_Pain,          S_VILE_RUN1,     0,     0     }, // S_VILE_PAIN2
    { SPR_VILE, SPR_VILS, 16,                                7,               NULL,            S_VILE_DIE2,     0,     0     }, // S_VILE_DIE1
    { SPR_VILE, SPR_VILS, 17,                                7,               A_Scream,        S_VILE_DIE3,     0,     0     }, // S_VILE_DIE2
    { SPR_VILE, SPR_VILS, 18,                                7,               A_Fall,          S_VILE_DIE4,     0,     0     }, // S_VILE_DIE3
    { SPR_VILE, SPR_VILS, 19,                                7,               NULL,            S_VILE_DIE5,     0,     0     }, // S_VILE_DIE4
    { SPR_VILE, SPR_VILS, 20,                                7,               NULL,            S_VILE_DIE6,     0,     0     }, // S_VILE_DIE5
    { SPR_VILE, SPR_VILS, 21,                                7,               NULL,            S_VILE_DIE7,     0,     0     }, // S_VILE_DIE6
    { SPR_VILE, SPR_VILS, 22,                                7,               NULL,            S_VILE_DIE8,     0,     0     }, // S_VILE_DIE7
    { SPR_VILE, SPR_VILS, 23,                                5,               NULL,            S_VILE_DIE9,     0,     0     }, // S_VILE_DIE8
    { SPR_VILE, SPR_VILS, 24,                                5,               NULL,            S_VILE_DIE10,    0,     0     }, // S_VILE_DIE9
    { SPR_VILE, SPR_VILS, 25,                               -1,               NULL,            S_NULL,          0,     0     }, // S_VILE_DIE10

    // Arch-vile Fire Attack (MT_FIRE)
    { SPR_FIRE, SPR_FIRE,  0 | FF_FULLBRIGHT,                2,               A_StartFire,     S_FIRE2,         0,     0     }, // S_FIRE1
    { SPR_FIRE, SPR_FIRE,  1 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE3,         0,     0     }, // S_FIRE2
    { SPR_FIRE, SPR_FIRE,  0 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE4,         0,     0     }, // S_FIRE3
    { SPR_FIRE, SPR_FIRE,  1 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE5,         0,     0     }, // S_FIRE4
    { SPR_FIRE, SPR_FIRE,  2 | FF_FULLBRIGHT,                2,               A_FireCrackle,   S_FIRE6,         0,     0     }, // S_FIRE5
    { SPR_FIRE, SPR_FIRE,  1 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE7,         0,     0     }, // S_FIRE6
    { SPR_FIRE, SPR_FIRE,  2 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE8,         0,     0     }, // S_FIRE7
    { SPR_FIRE, SPR_FIRE,  1 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE9,         0,     0     }, // S_FIRE8
    { SPR_FIRE, SPR_FIRE,  2 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE10,        0,     0     }, // S_FIRE9
    { SPR_FIRE, SPR_FIRE,  3 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE11,        0,     0     }, // S_FIRE10
    { SPR_FIRE, SPR_FIRE,  2 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE12,        0,     0     }, // S_FIRE11
    { SPR_FIRE, SPR_FIRE,  3 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE13,        0,     0     }, // S_FIRE12
    { SPR_FIRE, SPR_FIRE,  2 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE14,        0,     0     }, // S_FIRE13
    { SPR_FIRE, SPR_FIRE,  3 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE15,        0,     0     }, // S_FIRE14
    { SPR_FIRE, SPR_FIRE,  4 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE16,        0,     0     }, // S_FIRE15
    { SPR_FIRE, SPR_FIRE,  3 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE17,        0,     0     }, // S_FIRE16
    { SPR_FIRE, SPR_FIRE,  4 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE18,        0,     0     }, // S_FIRE17
    { SPR_FIRE, SPR_FIRE,  3 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE19,        0,     0     }, // S_FIRE18
    { SPR_FIRE, SPR_FIRE,  4 | FF_FULLBRIGHT,                2,               A_FireCrackle,   S_FIRE20,        0,     0     }, // S_FIRE19
    { SPR_FIRE, SPR_FIRE,  5 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE21,        0,     0     }, // S_FIRE20
    { SPR_FIRE, SPR_FIRE,  4 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE22,        0,     0     }, // S_FIRE21
    { SPR_FIRE, SPR_FIRE,  5 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE23,        0,     0     }, // S_FIRE22
    { SPR_FIRE, SPR_FIRE,  4 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE24,        0,     0     }, // S_FIRE23
    { SPR_FIRE, SPR_FIRE,  5 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE25,        0,     0     }, // S_FIRE24
    { SPR_FIRE, SPR_FIRE,  6 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE26,        0,     0     }, // S_FIRE25
    { SPR_FIRE, SPR_FIRE,  7 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE27,        0,     0     }, // S_FIRE26
    { SPR_FIRE, SPR_FIRE,  6 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE28,        0,     0     }, // S_FIRE27
    { SPR_FIRE, SPR_FIRE,  7 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE29,        0,     0     }, // S_FIRE28
    { SPR_FIRE, SPR_FIRE,  6 | FF_FULLBRIGHT,                2,               A_Fire,          S_FIRE30,        0,     0     }, // S_FIRE29
    { SPR_FIRE, SPR_FIRE,  7 | FF_FULLBRIGHT,                2,               A_Fire,          S_NULL,          0,     0     }, // S_FIRE30

    // Smoke (MT_SMOKE)
    { SPR_PUFF, SPR_PUFF,  1,                                4,               NULL,            S_SMOKE2,        0,     0     }, // S_SMOKE1
    { SPR_PUFF, SPR_PUFF,  2,                                4,               NULL,            S_SMOKE3,        0,     0     }, // S_SMOKE2
    { SPR_PUFF, SPR_PUFF,  1,                                4,               NULL,            S_SMOKE4,        0,     0     }, // S_SMOKE3
    { SPR_PUFF, SPR_PUFF,  2,                                4,               NULL,            S_SMOKE5,        0,     0     }, // S_SMOKE4
    { SPR_PUFF, SPR_PUFF,  3,                                4,               NULL,            S_NULL,          0,     0     }, // S_SMOKE5

    // Revenant Projectile (MT_TRACER)
    { SPR_FATB, SPR_FATB,  0 | FF_FULLBRIGHT,                2,               A_Tracer,        S_TRACER2,       0,     0     }, // S_TRACER
    { SPR_FATB, SPR_FATB,  1 | FF_FULLBRIGHT,                2,               A_Tracer,        S_TRACER,        0,     0     }, // S_TRACER2
    { SPR_FBXP, SPR_FBXP,  0 | FF_FULLBRIGHT,                8,               NULL,            S_TRACEEXP2,     0,     0     }, // S_TRACEEXP1
    { SPR_FBXP, SPR_FBXP,  1 | FF_FULLBRIGHT,                6,               NULL,            S_TRACEEXP3,     0,     0     }, // S_TRACEEXP2
    { SPR_FBXP, SPR_FBXP,  2 | FF_FULLBRIGHT,                4,               NULL,            S_NULL,          0,     0     }, // S_TRACEEXP3

    // Revenant (MT_UNDEAD)
    { SPR_SKEL, SPR_SLDS,  0,                               10,               A_Look,          S_SKEL_STND2,    0,     0     }, // S_SKEL_STND
    { SPR_SKEL, SPR_SLDS,  1,                               10,               A_Look,          S_SKEL_STND,     0,     0     }, // S_SKEL_STND2
    { SPR_SKEL, SPR_SLDS,  0,                                2,               A_Chase,         S_SKEL_RUN2,     0,     0     }, // S_SKEL_RUN1
    { SPR_SKEL, SPR_SLDS,  0,                                2,               A_Chase,         S_SKEL_RUN3,     0,     0     }, // S_SKEL_RUN2
    { SPR_SKEL, SPR_SLDS,  1,                                2,               A_Chase,         S_SKEL_RUN4,     0,     0     }, // S_SKEL_RUN3
    { SPR_SKEL, SPR_SLDS,  1,                                2,               A_Chase,         S_SKEL_RUN5,     0,     0     }, // S_SKEL_RUN4
    { SPR_SKEL, SPR_SLDS,  2,                                2,               A_Chase,         S_SKEL_RUN6,     0,     0     }, // S_SKEL_RUN5
    { SPR_SKEL, SPR_SLDS,  2,                                2,               A_Chase,         S_SKEL_RUN7,     0,     0     }, // S_SKEL_RUN6
    { SPR_SKEL, SPR_SLDS,  3,                                2,               A_Chase,         S_SKEL_RUN8,     0,     0     }, // S_SKEL_RUN7
    { SPR_SKEL, SPR_SLDS,  3,                                2,               A_Chase,         S_SKEL_RUN9,     0,     0     }, // S_SKEL_RUN8
    { SPR_SKEL, SPR_SLDS,  4,                                2,               A_Chase,         S_SKEL_RUN10,    0,     0     }, // S_SKEL_RUN9
    { SPR_SKEL, SPR_SLDS,  4,                                2,               A_Chase,         S_SKEL_RUN11,    0,     0     }, // S_SKEL_RUN10
    { SPR_SKEL, SPR_SLDS,  5,                                2,               A_Chase,         S_SKEL_RUN12,    0,     0     }, // S_SKEL_RUN11
    { SPR_SKEL, SPR_SLDS,  5,                                2,               A_Chase,         S_SKEL_RUN1,     0,     0     }, // S_SKEL_RUN12
    { SPR_SKEL, SPR_SLDS,  6,                                0,               A_FaceTarget,    S_SKEL_FIST2,    0,     0     }, // S_SKEL_FIST1
    { SPR_SKEL, SPR_SLDS,  6,                                6,               A_SkelWhoosh,    S_SKEL_FIST3,    0,     0     }, // S_SKEL_FIST2
    { SPR_SKEL, SPR_SLDS,  7,                                6,               A_FaceTarget,    S_SKEL_FIST4,    0,     0     }, // S_SKEL_FIST3
    { SPR_SKEL, SPR_SLDS,  8,                                6,               A_SkelFist,      S_SKEL_RUN1,     0,     0     }, // S_SKEL_FIST4
    { SPR_SKEL, SPR_SLDS,  9 | FF_FULLBRIGHT,                0,               A_FaceTarget,    S_SKEL_MISS2,    0,     0     }, // S_SKEL_MISS1
    { SPR_SKEL, SPR_SLDS,  9 | FF_FULLBRIGHT,               10,               A_FaceTarget,    S_SKEL_MISS3,    0,     0     }, // S_SKEL_MISS2
    { SPR_SKEL, SPR_SLDS, 10,                               10,               A_SkelMissile,   S_SKEL_MISS4,    0,     0     }, // S_SKEL_MISS3
    { SPR_SKEL, SPR_SLDS, 10,                               10,               A_FaceTarget,    S_SKEL_RUN1,     0,     0     }, // S_SKEL_MISS4
    { SPR_SKEL, SPR_SLDS, 11,                                5,               NULL,            S_SKEL_PAIN2,    0,     0     }, // S_SKEL_PAIN
    { SPR_SKEL, SPR_SLDS, 11,                                5,               A_Pain,          S_SKEL_RUN1,     0,     0     }, // S_SKEL_PAIN2
    { SPR_SKEL, SPR_SLDS, 11,                                7,               NULL,            S_SKEL_DIE2,     0,     0     }, // S_SKEL_DIE1
    { SPR_SKEL, SPR_SLDS, 12,                                7,               NULL,            S_SKEL_DIE3,     0,     0     }, // S_SKEL_DIE2
    { SPR_SKEL, SPR_SLDS, 13,                                7,               A_Scream,        S_SKEL_DIE4,     0,     0     }, // S_SKEL_DIE3
    { SPR_SKEL, SPR_SLDS, 14,                                7,               A_Fall,          S_SKEL_DIE5,     0,     0     }, // S_SKEL_DIE4
    { SPR_SKEL, SPR_SLDS, 15,                                7,               NULL,            S_SKEL_DIE6,     0,     0     }, // S_SKEL_DIE5
    { SPR_SKEL, SPR_SLDS, 16,                               -1,               NULL,            S_NULL,          0,     0     }, // S_SKEL_DIE6
    { SPR_SKEL, SPR_SLDS, 16,                                5,               NULL,            S_SKEL_RAISE2,   0,     0     }, // S_SKEL_RAISE1
    { SPR_SKEL, SPR_SLDS, 15,                                5,               NULL,            S_SKEL_RAISE3,   0,     0     }, // S_SKEL_RAISE2
    { SPR_SKEL, SPR_SLDS, 14,                                5,               NULL,            S_SKEL_RAISE4,   0,     0     }, // S_SKEL_RAISE3
    { SPR_SKEL, SPR_SLDS, 13,                                5,               NULL,            S_SKEL_RAISE5,   0,     0     }, // S_SKEL_RAISE4
    { SPR_SKEL, SPR_SLDS, 12,                                5,               NULL,            S_SKEL_RAISE6,   0,     0     }, // S_SKEL_RAISE5
    { SPR_SKEL, SPR_SLDS, 11,                                5,               NULL,            S_SKEL_RUN1,     0,     0     }, // S_SKEL_RAISE6

    // Mancubus Projectile (MT_FATSHOT)
    { SPR_MANF, SPR_MANF,  0 | FF_FULLBRIGHT,                4,               NULL,            S_FATSHOT2,      0,     0     }, // S_FATSHOT1
    { SPR_MANF, SPR_MANF,  1 | FF_FULLBRIGHT,                4,               NULL,            S_FATSHOT1,      0,     0     }, // S_FATSHOT2
    { SPR_MISL, SPR_MISL,  1 | FF_FULLBRIGHT,                8,               NULL,            S_FATSHOTX2,     0,     0     }, // S_FATSHOTX1
    { SPR_MISL, SPR_MISL,  2 | FF_FULLBRIGHT,                6,               NULL,            S_FATSHOTX3,     0,     0     }, // S_FATSHOTX2
    { SPR_MISL, SPR_MISL,  3 | FF_FULLBRIGHT,                4,               NULL,            S_NULL,          0,     0     }, // S_FATSHOTX3

    // Mancubus (MT_FATSO)
    { SPR_FATT, SPR_FADS,  0,                               15,               A_Look,          S_FATT_STND2,    0,     0     }, // S_FATT_STND
    { SPR_FATT, SPR_FADS,  1,                               15,               A_Look,          S_FATT_STND,     0,     0     }, // S_FATT_STND2
    { SPR_FATT, SPR_FADS,  0,                                4,               A_Chase,         S_FATT_RUN2,     0,     0     }, // S_FATT_RUN1
    { SPR_FATT, SPR_FADS,  0,                                4,               A_Chase,         S_FATT_RUN3,     0,     0     }, // S_FATT_RUN2
    { SPR_FATT, SPR_FADS,  1,                                4,               A_Chase,         S_FATT_RUN4,     0,     0     }, // S_FATT_RUN3
    { SPR_FATT, SPR_FADS,  1,                                4,               A_Chase,         S_FATT_RUN5,     0,     0     }, // S_FATT_RUN4
    { SPR_FATT, SPR_FADS,  2,                                4,               A_Chase,         S_FATT_RUN6,     0,     0     }, // S_FATT_RUN5
    { SPR_FATT, SPR_FADS,  2,                                4,               A_Chase,         S_FATT_RUN7,     0,     0     }, // S_FATT_RUN6
    { SPR_FATT, SPR_FADS,  3,                                4,               A_Chase,         S_FATT_RUN8,     0,     0     }, // S_FATT_RUN7
    { SPR_FATT, SPR_FADS,  3,                                4,               A_Chase,         S_FATT_RUN9,     0,     0     }, // S_FATT_RUN8
    { SPR_FATT, SPR_FADS,  4,                                4,               A_Chase,         S_FATT_RUN10,    0,     0     }, // S_FATT_RUN9
    { SPR_FATT, SPR_FADS,  4,                                4,               A_Chase,         S_FATT_RUN11,    0,     0     }, // S_FATT_RUN10
    { SPR_FATT, SPR_FADS,  5,                                4,               A_Chase,         S_FATT_RUN12,    0,     0     }, // S_FATT_RUN11
    { SPR_FATT, SPR_FADS,  5,                                4,               A_Chase,         S_FATT_RUN1,     0,     0     }, // S_FATT_RUN12
    { SPR_FATT, SPR_FADS,  6,                               20,               A_FatRaise,      S_FATT_ATK2,     0,     0     }, // S_FATT_ATK1
    { SPR_FATT, SPR_FADS,  7 | FF_FULLBRIGHT,               10,               A_FatAttack1,    S_FATT_ATK3,     0,     0     }, // S_FATT_ATK2
    { SPR_FATT, SPR_FADS,  8,                                5,               A_FaceTarget,    S_FATT_ATK4,     0,     0     }, // S_FATT_ATK3
    { SPR_FATT, SPR_FADS,  6,                                5,               A_FaceTarget,    S_FATT_ATK5,     0,     0     }, // S_FATT_ATK4
    { SPR_FATT, SPR_FADS,  7 | FF_FULLBRIGHT,               10,               A_FatAttack2,    S_FATT_ATK6,     0,     0     }, // S_FATT_ATK5
    { SPR_FATT, SPR_FADS,  8,                                5,               A_FaceTarget,    S_FATT_ATK7,     0,     0     }, // S_FATT_ATK6
    { SPR_FATT, SPR_FADS,  6,                                5,               A_FaceTarget,    S_FATT_ATK8,     0,     0     }, // S_FATT_ATK7
    { SPR_FATT, SPR_FADS,  7 | FF_FULLBRIGHT,               10,               A_FatAttack3,    S_FATT_ATK9,     0,     0     }, // S_FATT_ATK8
    { SPR_FATT, SPR_FADS,  8,                                5,               A_FaceTarget,    S_FATT_ATK10,    0,     0     }, // S_FATT_ATK9
    { SPR_FATT, SPR_FADS,  6,                                5,               A_FaceTarget,    S_FATT_RUN1,     0,     0     }, // S_FATT_ATK10
    { SPR_FATT, SPR_FADS,  9,                                3,               NULL,            S_FATT_PAIN2,    0,     0     }, // S_FATT_PAIN
    { SPR_FATT, SPR_FADS,  9,                                3,               A_Pain,          S_FATT_RUN1,     0,     0     }, // S_FATT_PAIN2
    { SPR_FATT, SPR_FADS, 10,                                6,               NULL,            S_FATT_DIE2,     0,     0     }, // S_FATT_DIE1
    { SPR_FATT, SPR_FADS, 11,                                6,               A_Scream,        S_FATT_DIE3,     0,     0     }, // S_FATT_DIE2
    { SPR_FATT, SPR_FADS, 12,                                6,               A_Fall,          S_FATT_DIE4,     0,     0     }, // S_FATT_DIE3
    { SPR_FATT, SPR_FADS, 13,                                6,               NULL,            S_FATT_DIE5,     0,     0     }, // S_FATT_DIE4
    { SPR_FATT, SPR_FADS, 14,                                6,               NULL,            S_FATT_DIE6,     0,     0     }, // S_FATT_DIE5
    { SPR_FATT, SPR_FADS, 15,                                6,               NULL,            S_FATT_DIE7,     0,     0     }, // S_FATT_DIE6
    { SPR_FATT, SPR_FADS, 16,                                6,               NULL,            S_FATT_DIE8,     0,     0     }, // S_FATT_DIE7
    { SPR_FATT, SPR_FADS, 17,                                6,               NULL,            S_FATT_DIE9,     0,     0     }, // S_FATT_DIE8
    { SPR_FATT, SPR_FADS, 18,                                6,               NULL,            S_FATT_DIE10,    0,     0     }, // S_FATT_DIE9
    { SPR_FATT, SPR_FADS, 19,                               -1,               A_BossDeath,     S_NULL,          0,     0     }, // S_FATT_DIE10
    { SPR_FATT, SPR_FADS, 17,                                5,               NULL,            S_FATT_RAISE2,   0,     0     }, // S_FATT_RAISE1
    { SPR_FATT, SPR_FADS, 16,                                5,               NULL,            S_FATT_RAISE3,   0,     0     }, // S_FATT_RAISE2
    { SPR_FATT, SPR_FADS, 15,                                5,               NULL,            S_FATT_RAISE4,   0,     0     }, // S_FATT_RAISE3
    { SPR_FATT, SPR_FADS, 14,                                5,               NULL,            S_FATT_RAISE5,   0,     0     }, // S_FATT_RAISE4
    { SPR_FATT, SPR_FADS, 13,                                5,               NULL,            S_FATT_RAISE6,   0,     0     }, // S_FATT_RAISE5
    { SPR_FATT, SPR_FADS, 12,                                5,               NULL,            S_FATT_RAISE7,   0,     0     }, // S_FATT_RAISE6
    { SPR_FATT, SPR_FADS, 11,                                5,               NULL,            S_FATT_RAISE8,   0,     0     }, // S_FATT_RAISE7
    { SPR_FATT, SPR_FADS, 10,                                5,               NULL,            S_FATT_RUN1,     0,     0     }, // S_FATT_RAISE8

    // Chaingunner (MT_CHAINGUY)
    { SPR_CPOS, SPR_CPDS,  0,                               10,               A_Look,          S_CPOS_STND2,    0,     0     }, // S_CPOS_STND
    { SPR_CPOS, SPR_CPDS,  1,                               10,               A_Look,          S_CPOS_STND,     0,     0     }, // S_CPOS_STND2
    { SPR_CPOS, SPR_CPDS,  0,                                3,               A_Chase,         S_CPOS_RUN2,     0,     0     }, // S_CPOS_RUN1
    { SPR_CPOS, SPR_CPDS,  0,                                3,               A_Chase,         S_CPOS_RUN3,     0,     0     }, // S_CPOS_RUN2
    { SPR_CPOS, SPR_CPDS,  1,                                3,               A_Chase,         S_CPOS_RUN4,     0,     0     }, // S_CPOS_RUN3
    { SPR_CPOS, SPR_CPDS,  1,                                3,               A_Chase,         S_CPOS_RUN5,     0,     0     }, // S_CPOS_RUN4
    { SPR_CPOS, SPR_CPDS,  2,                                3,               A_Chase,         S_CPOS_RUN6,     0,     0     }, // S_CPOS_RUN5
    { SPR_CPOS, SPR_CPDS,  2,                                3,               A_Chase,         S_CPOS_RUN7,     0,     0     }, // S_CPOS_RUN6
    { SPR_CPOS, SPR_CPDS,  3,                                3,               A_Chase,         S_CPOS_RUN8,     0,     0     }, // S_CPOS_RUN7
    { SPR_CPOS, SPR_CPDS,  3,                                3,               A_Chase,         S_CPOS_RUN1,     0,     0     }, // S_CPOS_RUN8
    { SPR_CPOS, SPR_CPDS,  4,                               10,               A_FaceTarget,    S_CPOS_ATK2,     0,     0     }, // S_CPOS_ATK1
    { SPR_CPOS, SPR_CPDS,  5 | FF_FULLBRIGHT,                4,               A_CPosAttack,    S_CPOS_ATK3,     0,     0     }, // S_CPOS_ATK2
    { SPR_CPOS, SPR_CPDS,  4 | FF_FULLBRIGHT,                4,               A_CPosAttack,    S_CPOS_ATK4,     0,     0     }, // S_CPOS_ATK3
    { SPR_CPOS, SPR_CPDS,  5,                                1,               A_CPosRefire,    S_CPOS_ATK2,     0,     0     }, // S_CPOS_ATK4
    { SPR_CPOS, SPR_CPDS,  6,                                3,               NULL,            S_CPOS_PAIN2,    0,     0     }, // S_CPOS_PAIN
    { SPR_CPOS, SPR_CPDS,  6,                                3,               A_Pain,          S_CPOS_RUN1,     0,     0     }, // S_CPOS_PAIN2
    { SPR_CPOS, SPR_CPDS,  7,                                5,               NULL,            S_CPOS_DIE2,     0,     0     }, // S_CPOS_DIE1
    { SPR_CPOS, SPR_CPDS,  8,                                5,               A_Scream,        S_CPOS_DIE3,     0,     0     }, // S_CPOS_DIE2
    { SPR_CPOS, SPR_CPDS,  9,                                5,               A_Fall,          S_CPOS_DIE4,     0,     0     }, // S_CPOS_DIE3
    { SPR_CPOS, SPR_CPDS, 10,                                5,               NULL,            S_CPOS_DIE5,     0,     0     }, // S_CPOS_DIE4
    { SPR_CPOS, SPR_CPDS, 11,                                5,               NULL,            S_CPOS_DIE6,     0,     0     }, // S_CPOS_DIE5
    { SPR_CPOS, SPR_CPDS, 12,                                5,               NULL,            S_CPOS_DIE7,     0,     0     }, // S_CPOS_DIE6
    { SPR_CPOS, SPR_CPDS, 13,                               -1,               NULL,            S_NULL,          0,     0     }, // S_CPOS_DIE7
    { SPR_CPOS, SPR_CPDS, 14,                                5,               NULL,            S_CPOS_XDIE2,    0,     0     }, // S_CPOS_XDIE1
    { SPR_CPOS, SPR_CPDS, 15,                                5,               A_XScream,       S_CPOS_XDIE3,    0,     0     }, // S_CPOS_XDIE2
    { SPR_CPOS, SPR_CPDS, 16,                                5,               A_Fall,          S_CPOS_XDIE4,    0,     0     }, // S_CPOS_XDIE3
    { SPR_CPOS, SPR_CPDS, 17,                                5,               NULL,            S_CPOS_XDIE5,    0,     0     }, // S_CPOS_XDIE4
    { SPR_CPOS, SPR_CPDS, 18,                                5,               NULL,            S_CPOS_XDIE6,    0,     0     }, // S_CPOS_XDIE5
    { SPR_CPOS, SPR_CPDS, 19,                               -1,               NULL,            S_NULL,          0,     0     }, // S_CPOS_XDIE6
    { SPR_CPOS, SPR_CPDS, 13,                                5,               NULL,            S_CPOS_RAISE2,   0,     0     }, // S_CPOS_RAISE1
    { SPR_CPOS, SPR_CPDS, 12,                                5,               NULL,            S_CPOS_RAISE3,   0,     0     }, // S_CPOS_RAISE2
    { SPR_CPOS, SPR_CPDS, 11,                                5,               NULL,            S_CPOS_RAISE4,   0,     0     }, // S_CPOS_RAISE3
    { SPR_CPOS, SPR_CPDS, 10,                                5,               NULL,            S_CPOS_RAISE5,   0,     0     }, // S_CPOS_RAISE4
    { SPR_CPOS, SPR_CPDS,  9,                                5,               NULL,            S_CPOS_RAISE6,   0,     0     }, // S_CPOS_RAISE5
    { SPR_CPOS, SPR_CPDS,  8,                                5,               NULL,            S_CPOS_RAISE7,   0,     0     }, // S_CPOS_RAISE6
    { SPR_CPOS, SPR_CPDS,  7,                                5,               NULL,            S_CPOS_RUN1,     0,     0     }, // S_CPOS_RAISE7

    // Imp (MT_TROOP)
    { SPR_TROO, SPR_TRDS,  0,                               10,               A_Look,          S_TROO_STND2,    0,     0     }, // S_TROO_STND
    { SPR_TROO, SPR_TRDS,  1,                               10,               A_Look,          S_TROO_STND,     0,     0     }, // S_TROO_STND2
    { SPR_TROO, SPR_TRDS,  0,                                3,               A_Chase,         S_TROO_RUN2,     0,     0     }, // S_TROO_RUN1
    { SPR_TROO, SPR_TRDS,  0,                                3,               A_Chase,         S_TROO_RUN3,     0,     0     }, // S_TROO_RUN2
    { SPR_TROO, SPR_TRDS,  1,                                3,               A_Chase,         S_TROO_RUN4,     0,     0     }, // S_TROO_RUN3
    { SPR_TROO, SPR_TRDS,  1,                                3,               A_Chase,         S_TROO_RUN5,     0,     0     }, // S_TROO_RUN4
    { SPR_TROO, SPR_TRDS,  2,                                3,               A_Chase,         S_TROO_RUN6,     0,     0     }, // S_TROO_RUN5
    { SPR_TROO, SPR_TRDS,  2,                                3,               A_Chase,         S_TROO_RUN7,     0,     0     }, // S_TROO_RUN6
    { SPR_TROO, SPR_TRDS,  3,                                3,               A_Chase,         S_TROO_RUN8,     0,     0     }, // S_TROO_RUN7
    { SPR_TROO, SPR_TRDS,  3,                                3,               A_Chase,         S_TROO_RUN1,     0,     0     }, // S_TROO_RUN8
    { SPR_TROO, SPR_TRDS,  4,                                8,               A_FaceTarget,    S_TROO_ATK2,     0,     0     }, // S_TROO_ATK1
    { SPR_TROO, SPR_TRDS,  5,                                8,               A_FaceTarget,    S_TROO_ATK3,     0,     0     }, // S_TROO_ATK2
    { SPR_TROO, SPR_TRDS,  6,                                6,               A_TroopAttack,   S_TROO_RUN1,     0,     0     }, // S_TROO_ATK3
    { SPR_TROO, SPR_TRDS,  7,                                2,               NULL,            S_TROO_PAIN2,    0,     0     }, // S_TROO_PAIN
    { SPR_TROO, SPR_TRDS,  7,                                2,               A_Pain,          S_TROO_RUN1,     0,     0     }, // S_TROO_PAIN2
    { SPR_TROO, SPR_TRDS,  8,                                8,               NULL,            S_TROO_DIE2,     0,     0     }, // S_TROO_DIE1
    { SPR_TROO, SPR_TRDS,  9,                                8,               A_Scream,        S_TROO_DIE3,     0,     0     }, // S_TROO_DIE2
    { SPR_TROO, SPR_TRDS, 10,                                6,               NULL,            S_TROO_DIE4,     0,     0     }, // S_TROO_DIE3
    { SPR_TROO, SPR_TRDS, 11,                                6,               A_Fall,          S_TROO_DIE5,     0,     0     }, // S_TROO_DIE4

    // Imp Death (MT_MISC66)
    { SPR_TROO, SPR_TRDS, 12,                               -1,               NULL,            S_NULL,          0,     0     }, // S_TROO_DIE5
    { SPR_TROO, SPR_TRDS, 13,                                5,               NULL,            S_TROO_XDIE2,    0,     0     }, // S_TROO_XDIE1
    { SPR_TROO, SPR_TRDS, 14,                                5,               A_XScream,       S_TROO_XDIE3,    0,     0     }, // S_TROO_XDIE2
    { SPR_TROO, SPR_TRDS, 15,                                5,               NULL,            S_TROO_XDIE4,    0,     0     }, // S_TROO_XDIE3
    { SPR_TROO, SPR_TRDS, 16,                                5,               A_Fall,          S_TROO_XDIE5,    0,     0     }, // S_TROO_XDIE4
    { SPR_TROO, SPR_TRDS, 17,                                5,               NULL,            S_TROO_XDIE6,    0,     0     }, // S_TROO_XDIE5
    { SPR_TROO, SPR_TRDS, 18,                                5,               NULL,            S_TROO_XDIE7,    0,     0     }, // S_TROO_XDIE6
    { SPR_TROO, SPR_TRDS, 19,                                5,               NULL,            S_TROO_XDIE8,    0,     0     }, // S_TROO_XDIE7
    { SPR_TROO, SPR_TRDS, 20,                               -1,               NULL,            S_NULL,          0,     0     }, // S_TROO_XDIE8
    { SPR_TROO, SPR_TRDS, 12,                                8,               NULL,            S_TROO_RAISE2,   0,     0     }, // S_TROO_RAISE1
    { SPR_TROO, SPR_TRDS, 11,                                8,               NULL,            S_TROO_RAISE3,   0,     0     }, // S_TROO_RAISE2
    { SPR_TROO, SPR_TRDS, 10,                                6,               NULL,            S_TROO_RAISE4,   0,     0     }, // S_TROO_RAISE3
    { SPR_TROO, SPR_TRDS,  9,                                6,               NULL,            S_TROO_RAISE5,   0,     0     }, // S_TROO_RAISE4
    { SPR_TROO, SPR_TRDS,  8,                                6,               NULL,            S_TROO_RUN1,     0,     0     }, // S_TROO_RAISE5

    // Demon (MT_SERGEANT) and Spectre (MT_SHADOWS)
    { SPR_SARG, SPR_SADS,  0,                               10,               A_Look,          S_SARG_STND2,    0,     0     }, // S_SARG_STND
    { SPR_SARG, SPR_SADS,  1,                               10,               A_Look,          S_SARG_STND,     0,     0     }, // S_SARG_STND2
    { SPR_SARG, SPR_SADS,  0,                                2,               A_Chase,         S_SARG_RUN2,     0,     0     }, // S_SARG_RUN1
    { SPR_SARG, SPR_SADS,  0,                                2,               A_Chase,         S_SARG_RUN3,     0,     0     }, // S_SARG_RUN2
    { SPR_SARG, SPR_SADS,  1,                                2,               A_Chase,         S_SARG_RUN4,     0,     0     }, // S_SARG_RUN3
    { SPR_SARG, SPR_SADS,  1,                                2,               A_Chase,         S_SARG_RUN5,     0,     0     }, // S_SARG_RUN4
    { SPR_SARG, SPR_SADS,  2,                                2,               A_Chase,         S_SARG_RUN6,     0,     0     }, // S_SARG_RUN5
    { SPR_SARG, SPR_SADS,  2,                                2,               A_Chase,         S_SARG_RUN7,     0,     0     }, // S_SARG_RUN6
    { SPR_SARG, SPR_SADS,  3,                                2,               A_Chase,         S_SARG_RUN8,     0,     0     }, // S_SARG_RUN7
    { SPR_SARG, SPR_SADS,  3,                                2,               A_Chase,         S_SARG_RUN1,     0,     0     }, // S_SARG_RUN8
    { SPR_SARG, SPR_SADS,  4,                                8,               A_FaceTarget,    S_SARG_ATK2,     0,     0     }, // S_SARG_ATK1
    { SPR_SARG, SPR_SADS,  5,                                8,               A_FaceTarget,    S_SARG_ATK3,     0,     0     }, // S_SARG_ATK2
    { SPR_SARG, SPR_SADS,  6,                                8,               A_SargAttack,    S_SARG_RUN1,     0,     0     }, // S_SARG_ATK3
    { SPR_SARG, SPR_SADS,  7,                                2,               NULL,            S_SARG_PAIN2,    0,     0     }, // S_SARG_PAIN
    { SPR_SARG, SPR_SADS,  7,                                2,               A_Pain,          S_SARG_RUN1,     0,     0     }, // S_SARG_PAIN2
    { SPR_SARG, SPR_SADS,  8,                                8,               NULL,            S_SARG_DIE2,     0,     0     }, // S_SARG_DIE1
    { SPR_SARG, SPR_SADS,  9,                                8,               A_Scream,        S_SARG_DIE3,     0,     0     }, // S_SARG_DIE2
    { SPR_SARG, SPR_SADS, 10,                                4,               NULL,            S_SARG_DIE4,     0,     0     }, // S_SARG_DIE3
    { SPR_SARG, SPR_SADS, 11,                                4,               A_Fall,          S_SARG_DIE5,     0,     0     }, // S_SARG_DIE4
    { SPR_SARG, SPR_SADS, 12,                                4,               NULL,            S_SARG_DIE6,     0,     0     }, // S_SARG_DIE5

    // Demon Death (MT_MISC64)
    { SPR_SARG, SPR_SADS, 13,                               -1,               NULL,            S_NULL,          0,     0     }, // S_SARG_DIE6
    { SPR_SARG, SPR_SADS, 13,                                5,               NULL,            S_SARG_RAISE2,   0,     0     }, // S_SARG_RAISE1
    { SPR_SARG, SPR_SADS, 12,                                5,               NULL,            S_SARG_RAISE3,   0,     0     }, // S_SARG_RAISE2
    { SPR_SARG, SPR_SADS, 11,                                5,               NULL,            S_SARG_RAISE4,   0,     0     }, // S_SARG_RAISE3
    { SPR_SARG, SPR_SADS, 10,                                5,               NULL,            S_SARG_RAISE5,   0,     0     }, // S_SARG_RAISE4
    { SPR_SARG, SPR_SADS,  9,                                5,               NULL,            S_SARG_RAISE6,   0,     0     }, // S_SARG_RAISE5
    { SPR_SARG, SPR_SADS,  8,                                5,               NULL,            S_SARG_RUN1,     0,     0     }, // S_SARG_RAISE6

    // Cacodemon (MT_HEAD)
    { SPR_HEAD, SPR_HEDS,  0,                               10,               A_Look,          S_HEAD_STND,     0,     0     }, // S_HEAD_STND
    { SPR_HEAD, SPR_HEDS,  0,                                3,               A_Chase,         S_HEAD_RUN1,     0,     0     }, // S_HEAD_RUN1
    { SPR_HEAD, SPR_HEDS,  1,                                5,               A_FaceTarget,    S_HEAD_ATK2,     0,     0     }, // S_HEAD_ATK1
    { SPR_HEAD, SPR_HEDS,  2,                                5,               A_FaceTarget,    S_HEAD_ATK3,     0,     0     }, // S_HEAD_ATK2
    { SPR_HEAD, SPR_HEDS,  3,                                5,               A_HeadAttack,    S_HEAD_RUN1,     0,     0     }, // S_HEAD_ATK3
    { SPR_HEAD, SPR_HEDS,  4,                                3,               NULL,            S_HEAD_PAIN2,    0,     0     }, // S_HEAD_PAIN
    { SPR_HEAD, SPR_HEDS,  4,                                3,               A_Pain,          S_HEAD_PAIN3,    0,     0     }, // S_HEAD_PAIN2
    { SPR_HEAD, SPR_HEDS,  5,                                6,               NULL,            S_HEAD_RUN1,     0,     0     }, // S_HEAD_PAIN3
    { SPR_HEAD, SPR_HEDS,  6,                                8,               NULL,            S_HEAD_DIE2,     0,     0     }, // S_HEAD_DIE1
    { SPR_HEAD, SPR_HEDS,  7,                                8,               A_Scream,        S_HEAD_DIE3,     0,     0     }, // S_HEAD_DIE2
    { SPR_HEAD, SPR_HEDS,  8,                                8,               NULL,            S_HEAD_DIE4,     0,     0     }, // S_HEAD_DIE3
    { SPR_HEAD, SPR_HEDS,  9,                                8,               NULL,            S_HEAD_DIE5,     0,     0     }, // S_HEAD_DIE4
    { SPR_HEAD, SPR_HEDS, 10,                                8,               A_Fall,          S_HEAD_DIE6,     0,     0     }, // S_HEAD_DIE5

    // Cacodemon Death (MT_MISC61)
    { SPR_HEAD, SPR_HEDS, 11,                               -1,               NULL,            S_NULL,          0,     0     }, // S_HEAD_DIE6
    { SPR_HEAD, SPR_HEDS, 11,                                8,               NULL,            S_HEAD_RAISE2,   0,     0     }, // S_HEAD_RAISE1
    { SPR_HEAD, SPR_HEDS, 10,                                8,               NULL,            S_HEAD_RAISE3,   0,     0     }, // S_HEAD_RAISE2
    { SPR_HEAD, SPR_HEDS,  9,                                8,               NULL,            S_HEAD_RAISE4,   0,     0     }, // S_HEAD_RAISE3
    { SPR_HEAD, SPR_HEDS,  8,                                8,               NULL,            S_HEAD_RAISE5,   0,     0     }, // S_HEAD_RAISE4
    { SPR_HEAD, SPR_HEDS,  7,                                8,               NULL,            S_HEAD_RAISE6,   0,     0     }, // S_HEAD_RAISE5
    { SPR_HEAD, SPR_HEDS,  6,                                8,               NULL,            S_HEAD_RUN1,     0,     0     }, // S_HEAD_RAISE6

    // Baron of Hell and Hell Knight Projectiles (MT_BRUISERSHOT)
    { SPR_BAL7, SPR_BAL7,  0 | FF_FULLBRIGHT,                4,               NULL,            S_BRBALL2,       0,     0     }, // S_BRBALL1
    { SPR_BAL7, SPR_BAL7,  1 | FF_FULLBRIGHT,                4,               NULL,            S_BRBALL1,       0,     0     }, // S_BRBALL2
    { SPR_BAL7, SPR_BAL7,  2 | FF_FULLBRIGHT,                6,               NULL,            S_BRBALLX2,      0,     0     }, // S_BRBALLX1
    { SPR_BAL7, SPR_BAL7,  3 | FF_FULLBRIGHT,                6,               NULL,            S_BRBALLX3,      0,     0     }, // S_BRBALLX2
    { SPR_BAL7, SPR_BAL7,  4 | FF_FULLBRIGHT,                6,               NULL,            S_NULL,          0,     0     }, // S_BRBALLX3

    // Baron of Hell (MT_BRUISER)
    { SPR_BOSS, SPR_BODS,  0,                               10,               A_Look,          S_BOSS_STND2,    0,     0     }, // S_BOSS_STND
    { SPR_BOSS, SPR_BODS,  1,                               10,               A_Look,          S_BOSS_STND,     0,     0     }, // S_BOSS_STND2
    { SPR_BOSS, SPR_BODS,  0,                                3,               A_Chase,         S_BOSS_RUN2,     0,     0     }, // S_BOSS_RUN1
    { SPR_BOSS, SPR_BODS,  0,                                3,               A_Chase,         S_BOSS_RUN3,     0,     0     }, // S_BOSS_RUN2
    { SPR_BOSS, SPR_BODS,  1,                                3,               A_Chase,         S_BOSS_RUN4,     0,     0     }, // S_BOSS_RUN3
    { SPR_BOSS, SPR_BODS,  1,                                3,               A_Chase,         S_BOSS_RUN5,     0,     0     }, // S_BOSS_RUN4
    { SPR_BOSS, SPR_BODS,  2,                                3,               A_Chase,         S_BOSS_RUN6,     0,     0     }, // S_BOSS_RUN5
    { SPR_BOSS, SPR_BODS,  2,                                3,               A_Chase,         S_BOSS_RUN7,     0,     0     }, // S_BOSS_RUN6
    { SPR_BOSS, SPR_BODS,  3,                                3,               A_Chase,         S_BOSS_RUN8,     0,     0     }, // S_BOSS_RUN7
    { SPR_BOSS, SPR_BODS,  3,                                3,               A_Chase,         S_BOSS_RUN1,     0,     0     }, // S_BOSS_RUN8
    { SPR_BOSS, SPR_BODS,  4,                                8,               A_FaceTarget,    S_BOSS_ATK2,     0,     0     }, // S_BOSS_ATK1
    { SPR_BOSS, SPR_BODS,  5,                                8,               A_FaceTarget,    S_BOSS_ATK3,     0,     0     }, // S_BOSS_ATK2
    { SPR_BOSS, SPR_BODS,  6,                                8,               A_BruisAttack,   S_BOSS_RUN1,     0,     0     }, // S_BOSS_ATK3
    { SPR_BOSS, SPR_BODS,  7,                                2,               NULL,            S_BOSS_PAIN2,    0,     0     }, // S_BOSS_PAIN
    { SPR_BOSS, SPR_BODS,  7,                                2,               A_Pain,          S_BOSS_RUN1,     0,     0     }, // S_BOSS_PAIN2
    { SPR_BOSS, SPR_BODS,  8,                                8,               NULL,            S_BOSS_DIE2,     0,     0     }, // S_BOSS_DIE1
    { SPR_BOSS, SPR_BODS,  9,                                8,               A_Scream,        S_BOSS_DIE3,     0,     0     }, // S_BOSS_DIE2
    { SPR_BOSS, SPR_BODS, 10,                                8,               NULL,            S_BOSS_DIE4,     0,     0     }, // S_BOSS_DIE3
    { SPR_BOSS, SPR_BODS, 11,                                8,               A_Fall,          S_BOSS_DIE5,     0,     0     }, // S_BOSS_DIE4
    { SPR_BOSS, SPR_BODS, 12,                                8,               NULL,            S_BOSS_DIE6,     0,     0     }, // S_BOSS_DIE5
    { SPR_BOSS, SPR_BODS, 13,                                8,               NULL,            S_BOSS_DIE7,     0,     0     }, // S_BOSS_DIE6
    { SPR_BOSS, SPR_BODS, 14,                               -1,               A_BossDeath,     S_NULL,          0,     0     }, // S_BOSS_DIE7
    { SPR_BOSS, SPR_BODS, 14,                                8,               NULL,            S_BOSS_RAISE2,   0,     0     }, // S_BOSS_RAISE1
    { SPR_BOSS, SPR_BODS, 13,                                8,               NULL,            S_BOSS_RAISE3,   0,     0     }, // S_BOSS_RAISE2
    { SPR_BOSS, SPR_BODS, 12,                                8,               NULL,            S_BOSS_RAISE4,   0,     0     }, // S_BOSS_RAISE3
    { SPR_BOSS, SPR_BODS, 11,                                8,               NULL,            S_BOSS_RAISE5,   0,     0     }, // S_BOSS_RAISE4
    { SPR_BOSS, SPR_BODS, 10,                                8,               NULL,            S_BOSS_RAISE6,   0,     0     }, // S_BOSS_RAISE5
    { SPR_BOSS, SPR_BODS,  9,                                8,               NULL,            S_BOSS_RAISE7,   0,     0     }, // S_BOSS_RAISE6
    { SPR_BOSS, SPR_BODS,  8,                                8,               NULL,            S_BOSS_RUN1,     0,     0     }, // S_BOSS_RAISE7

    // Hell Knight (MT_KNIGHT)
    { SPR_BOS2, SPR_BDS2,  0,                               10,               A_Look,          S_BOS2_STND2,    0,     0     }, // S_BOS2_STND
    { SPR_BOS2, SPR_BDS2,  1,                               10,               A_Look,          S_BOS2_STND,     0,     0     }, // S_BOS2_STND2
    { SPR_BOS2, SPR_BDS2,  0,                                3,               A_Chase,         S_BOS2_RUN2,     0,     0     }, // S_BOS2_RUN1
    { SPR_BOS2, SPR_BDS2,  0,                                3,               A_Chase,         S_BOS2_RUN3,     0,     0     }, // S_BOS2_RUN2
    { SPR_BOS2, SPR_BDS2,  1,                                3,               A_Chase,         S_BOS2_RUN4,     0,     0     }, // S_BOS2_RUN3
    { SPR_BOS2, SPR_BDS2,  1,                                3,               A_Chase,         S_BOS2_RUN5,     0,     0     }, // S_BOS2_RUN4
    { SPR_BOS2, SPR_BDS2,  2,                                3,               A_Chase,         S_BOS2_RUN6,     0,     0     }, // S_BOS2_RUN5
    { SPR_BOS2, SPR_BDS2,  2,                                3,               A_Chase,         S_BOS2_RUN7,     0,     0     }, // S_BOS2_RUN6
    { SPR_BOS2, SPR_BDS2,  3,                                3,               A_Chase,         S_BOS2_RUN8,     0,     0     }, // S_BOS2_RUN7
    { SPR_BOS2, SPR_BDS2,  3,                                3,               A_Chase,         S_BOS2_RUN1,     0,     0     }, // S_BOS2_RUN8
    { SPR_BOS2, SPR_BDS2,  4,                                8,               A_FaceTarget,    S_BOS2_ATK2,     0,     0     }, // S_BOS2_ATK1
    { SPR_BOS2, SPR_BDS2,  5,                                8,               A_FaceTarget,    S_BOS2_ATK3,     0,     0     }, // S_BOS2_ATK2
    { SPR_BOS2, SPR_BDS2,  6,                                8,               A_BruisAttack,   S_BOS2_RUN1,     0,     0     }, // S_BOS2_ATK3
    { SPR_BOS2, SPR_BDS2,  7,                                2,               NULL,            S_BOS2_PAIN2,    0,     0     }, // S_BOS2_PAIN
    { SPR_BOS2, SPR_BDS2,  7,                                2,               A_Pain,          S_BOS2_RUN1,     0,     0     }, // S_BOS2_PAIN2
    { SPR_BOS2, SPR_BDS2,  8,                                8,               NULL,            S_BOS2_DIE2,     0,     0     }, // S_BOS2_DIE1
    { SPR_BOS2, SPR_BDS2,  9,                                8,               A_Scream,        S_BOS2_DIE3,     0,     0     }, // S_BOS2_DIE2
    { SPR_BOS2, SPR_BDS2, 10,                                8,               NULL,            S_BOS2_DIE4,     0,     0     }, // S_BOS2_DIE3
    { SPR_BOS2, SPR_BDS2, 11,                                8,               A_Fall,          S_BOS2_DIE5,     0,     0     }, // S_BOS2_DIE4
    { SPR_BOS2, SPR_BDS2, 12,                                8,               NULL,            S_BOS2_DIE6,     0,     0     }, // S_BOS2_DIE5
    { SPR_BOS2, SPR_BDS2, 13,                                8,               NULL,            S_BOS2_DIE7,     0,     0     }, // S_BOS2_DIE6
    { SPR_BOS2, SPR_BDS2, 14,                               -1,               NULL,            S_NULL,          0,     0     }, // S_BOS2_DIE7
    { SPR_BOS2, SPR_BDS2, 14,                                8,               NULL,            S_BOS2_RAISE2,   0,     0     }, // S_BOS2_RAISE1
    { SPR_BOS2, SPR_BDS2, 13,                                8,               NULL,            S_BOS2_RAISE3,   0,     0     }, // S_BOS2_RAISE2
    { SPR_BOS2, SPR_BDS2, 12,                                8,               NULL,            S_BOS2_RAISE4,   0,     0     }, // S_BOS2_RAISE3
    { SPR_BOS2, SPR_BDS2, 11,                                8,               NULL,            S_BOS2_RAISE5,   0,     0     }, // S_BOS2_RAISE4
    { SPR_BOS2, SPR_BDS2, 10,                                8,               NULL,            S_BOS2_RAISE6,   0,     0     }, // S_BOS2_RAISE5
    { SPR_BOS2, SPR_BDS2,  9,                                8,               NULL,            S_BOS2_RAISE7,   0,     0     }, // S_BOS2_RAISE6
    { SPR_BOS2, SPR_BDS2,  8,                                8,               NULL,            S_BOS2_RUN1,     0,     0     }, // S_BOS2_RAISE7

    // Lost Soul (MT_SKULL)
    { SPR_SKUL, SPR_SKDS,  0 | FF_FULLBRIGHT,               10,               A_Look,          S_SKULL_STND2,   0,     0     }, // S_SKULL_STND
    { SPR_SKUL, SPR_SKDS,  1 | FF_FULLBRIGHT,               10,               A_Look,          S_SKULL_STND,    0,     0     }, // S_SKULL_STND2
    { SPR_SKUL, SPR_SKDS,  0 | FF_FULLBRIGHT,                6,               A_Chase,         S_SKULL_RUN2,    0,     0     }, // S_SKULL_RUN1
    { SPR_SKUL, SPR_SKDS,  1 | FF_FULLBRIGHT,                6,               A_Chase,         S_SKULL_RUN1,    0,     0     }, // S_SKULL_RUN2
    { SPR_SKUL, SPR_SKDS,  2 | FF_FULLBRIGHT,               10,               A_FaceTarget,    S_SKULL_ATK2,    0,     0     }, // S_SKULL_ATK1
    { SPR_SKUL, SPR_SKDS,  3 | FF_FULLBRIGHT,                4,               A_SkullAttack,   S_SKULL_ATK3,    0,     0     }, // S_SKULL_ATK2
    { SPR_SKUL, SPR_SKDS,  2 | FF_FULLBRIGHT,                4,               NULL,            S_SKULL_ATK4,    0,     0     }, // S_SKULL_ATK3
    { SPR_SKUL, SPR_SKDS,  3 | FF_FULLBRIGHT,                4,               NULL,            S_SKULL_ATK3,    0,     0     }, // S_SKULL_ATK4
    { SPR_SKUL, SPR_SKDS,  4 | FF_FULLBRIGHT,                3,               NULL,            S_SKULL_PAIN2,   0,     0     }, // S_SKULL_PAIN
    { SPR_SKUL, SPR_SKDS,  4 | FF_FULLBRIGHT,                3,               A_Pain,          S_SKULL_RUN1,    0,     0     }, // S_SKULL_PAIN2
    { SPR_SKUL, SPR_SKDS,  5 | FF_FULLBRIGHT,                6,               NULL,            S_SKULL_DIE2,    0,     0     }, // S_SKULL_DIE1
    { SPR_SKUL, SPR_SKDS,  6 | FF_FULLBRIGHT,                6,               A_Scream,        S_SKULL_DIE3,    0,     0     }, // S_SKULL_DIE2
    { SPR_SKUL, SPR_SKDS,  7 | FF_FULLBRIGHT,                6,               NULL,            S_SKULL_DIE4,    0,     0     }, // S_SKULL_DIE3
    { SPR_SKUL, SPR_SKDS,  8 | FF_FULLBRIGHT,                6,               A_Fall,          S_SKULL_DIE5,    0,     0     }, // S_SKULL_DIE4
    { SPR_SKUL, SPR_SKDS,  9,                                6,               NULL,            S_SKULL_DIE6,    0,     0     }, // S_SKULL_DIE5

    // Lost Soul Death (MT_MISC65)
    { SPR_SKUL, SPR_SKDS, 10,                                6,               NULL,            S_NULL,          0,     0     }, // S_SKULL_DIE6

    // Spiderdemon (MT_SPIDER)
    { SPR_SPID, SPR_SPID,  0,                               10,               A_Look,          S_SPID_STND2,    0,     0     }, // S_SPID_STND
    { SPR_SPID, SPR_SPID,  1,                               10,               A_Look,          S_SPID_STND,     0,     0     }, // S_SPID_STND2
    { SPR_SPID, SPR_SPID,  0,                                3,               A_Metal,         S_SPID_RUN2,     0,     0     }, // S_SPID_RUN1
    { SPR_SPID, SPR_SPID,  0,                                3,               A_Chase,         S_SPID_RUN3,     0,     0     }, // S_SPID_RUN2
    { SPR_SPID, SPR_SPID,  1,                                3,               A_Chase,         S_SPID_RUN4,     0,     0     }, // S_SPID_RUN3
    { SPR_SPID, SPR_SPID,  1,                                3,               A_Chase,         S_SPID_RUN5,     0,     0     }, // S_SPID_RUN4
    { SPR_SPID, SPR_SPID,  2,                                3,               A_Metal,         S_SPID_RUN6,     0,     0     }, // S_SPID_RUN5
    { SPR_SPID, SPR_SPID,  2,                                3,               A_Chase,         S_SPID_RUN7,     0,     0     }, // S_SPID_RUN6
    { SPR_SPID, SPR_SPID,  3,                                3,               A_Chase,         S_SPID_RUN8,     0,     0     }, // S_SPID_RUN7
    { SPR_SPID, SPR_SPID,  3,                                3,               A_Chase,         S_SPID_RUN9,     0,     0     }, // S_SPID_RUN8
    { SPR_SPID, SPR_SPID,  4,                                3,               A_Metal,         S_SPID_RUN10,    0,     0     }, // S_SPID_RUN9
    { SPR_SPID, SPR_SPID,  4,                                3,               A_Chase,         S_SPID_RUN11,    0,     0     }, // S_SPID_RUN10
    { SPR_SPID, SPR_SPID,  5,                                3,               A_Chase,         S_SPID_RUN12,    0,     0     }, // S_SPID_RUN11
    { SPR_SPID, SPR_SPID,  5,                                3,               A_Chase,         S_SPID_RUN1,     0,     0     }, // S_SPID_RUN12
    { SPR_SPID, SPR_SPID,  0,                               20,               A_FaceTarget,    S_SPID_ATK2,     0,     0     }, // S_SPID_ATK1
    { SPR_SPID, SPR_SPID,  6 | FF_FULLBRIGHT,                4,               A_SPosAttack,    S_SPID_ATK3,     0,     0     }, // S_SPID_ATK2
    { SPR_SPID, SPR_SPID,  7 | FF_FULLBRIGHT,                4,               A_SPosAttack,    S_SPID_ATK4,     0,     0     }, // S_SPID_ATK3
    { SPR_SPID, SPR_SPID,  7 | FF_FULLBRIGHT,                1,               A_SpidRefire,    S_SPID_ATK2,     0,     0     }, // S_SPID_ATK4
    { SPR_SPID, SPR_SPID,  8,                                3,               NULL,            S_SPID_PAIN2,    0,     0     }, // S_SPID_PAIN
    { SPR_SPID, SPR_SPID,  8,                                3,               A_Pain,          S_SPID_RUN1,     0,     0     }, // S_SPID_PAIN2
    { SPR_SPID, SPR_SPID,  9,                               20,               A_Scream,        S_SPID_DIE2,     0,     0     }, // S_SPID_DIE1
    { SPR_SPID, SPR_SPID, 10,                               10,               A_Fall,          S_SPID_DIE3,     0,     0     }, // S_SPID_DIE2
    { SPR_SPID, SPR_SPID, 11,                               10,               NULL,            S_SPID_DIE4,     0,     0     }, // S_SPID_DIE3
    { SPR_SPID, SPR_SPID, 12 | FF_FULLBRIGHT,               10,               NULL,            S_SPID_DIE5,     0,     0     }, // S_SPID_DIE4
    { SPR_SPID, SPR_SPID, 13 | FF_FULLBRIGHT,               10,               NULL,            S_SPID_DIE6,     0,     0     }, // S_SPID_DIE5
    { SPR_SPID, SPR_SPID, 14 | FF_FULLBRIGHT,               10,               NULL,            S_SPID_DIE7,     0,     0     }, // S_SPID_DIE6
    { SPR_SPID, SPR_SPID, 15 | FF_FULLBRIGHT,               10,               NULL,            S_SPID_DIE8,     0,     0     }, // S_SPID_DIE7
    { SPR_SPID, SPR_SPID, 16 | FF_FULLBRIGHT,               10,               NULL,            S_SPID_DIE9,     0,     0     }, // S_SPID_DIE8
    { SPR_SPID, SPR_SPID, 17 | FF_FULLBRIGHT,               10,               NULL,            S_SPID_DIE10,    0,     0     }, // S_SPID_DIE9
    { SPR_SPID, SPR_SPID, 18,                               30,               NULL,            S_SPID_DIE11,    0,     0     }, // S_SPID_DIE10
    { SPR_SPID, SPR_SPID, 18,                               -1,               A_BossDeath,     S_NULL,          0,     0     }, // S_SPID_DIE11

    // Arachnotron (MT_BABY)
    { SPR_BSPI, SPR_BSDS,  0,                               10,               A_Look,          S_BSPI_STND2,    0,     0     }, // S_BSPI_STND
    { SPR_BSPI, SPR_BSDS,  1,                               10,               A_Look,          S_BSPI_STND,     0,     0     }, // S_BSPI_STND2
    { SPR_BSPI, SPR_BSDS,  0,                               20,               NULL,            S_BSPI_RUN1,     0,     0     }, // S_BSPI_SIGHT
    { SPR_BSPI, SPR_BSDS,  0,                                3,               A_BabyMetal,     S_BSPI_RUN2,     0,     0     }, // S_BSPI_RUN1
    { SPR_BSPI, SPR_BSDS,  0,                                3,               A_Chase,         S_BSPI_RUN3,     0,     0     }, // S_BSPI_RUN2
    { SPR_BSPI, SPR_BSDS,  1,                                3,               A_Chase,         S_BSPI_RUN4,     0,     0     }, // S_BSPI_RUN3
    { SPR_BSPI, SPR_BSDS,  1,                                3,               A_Chase,         S_BSPI_RUN5,     0,     0     }, // S_BSPI_RUN4
    { SPR_BSPI, SPR_BSDS,  2,                                3,               A_Chase,         S_BSPI_RUN6,     0,     0     }, // S_BSPI_RUN5
    { SPR_BSPI, SPR_BSDS,  2,                                3,               A_Chase,         S_BSPI_RUN7,     0,     0     }, // S_BSPI_RUN6
    { SPR_BSPI, SPR_BSDS,  3,                                3,               A_BabyMetal,     S_BSPI_RUN8,     0,     0     }, // S_BSPI_RUN7
    { SPR_BSPI, SPR_BSDS,  3,                                3,               A_Chase,         S_BSPI_RUN9,     0,     0     }, // S_BSPI_RUN8
    { SPR_BSPI, SPR_BSDS,  4,                                3,               A_Chase,         S_BSPI_RUN10,    0,     0     }, // S_BSPI_RUN9
    { SPR_BSPI, SPR_BSDS,  4,                                3,               A_Chase,         S_BSPI_RUN11,    0,     0     }, // S_BSPI_RUN10
    { SPR_BSPI, SPR_BSDS,  5,                                3,               A_Chase,         S_BSPI_RUN12,    0,     0     }, // S_BSPI_RUN11
    { SPR_BSPI, SPR_BSDS,  5,                                3,               A_Chase,         S_BSPI_RUN1,     0,     0     }, // S_BSPI_RUN12
    { SPR_BSPI, SPR_BSDS,  0,                               20,               A_FaceTarget,    S_BSPI_ATK2,     0,     0     }, // S_BSPI_ATK1
    { SPR_BSPI, SPR_BSDS,  6 | FF_FULLBRIGHT,                4,               A_BspiAttack,    S_BSPI_ATK3,     0,     0     }, // S_BSPI_ATK2
    { SPR_BSPI, SPR_BSDS,  7 | FF_FULLBRIGHT,                4,               NULL,            S_BSPI_ATK4,     0,     0     }, // S_BSPI_ATK3
    { SPR_BSPI, SPR_BSDS,  7 | FF_FULLBRIGHT,                1,               A_SpidRefire,    S_BSPI_ATK2,     0,     0     }, // S_BSPI_ATK4
    { SPR_BSPI, SPR_BSDS,  8,                                3,               NULL,            S_BSPI_PAIN2,    0,     0     }, // S_BSPI_PAIN
    { SPR_BSPI, SPR_BSDS,  8,                                3,               A_Pain,          S_BSPI_RUN1,     0,     0     }, // S_BSPI_PAIN2
    { SPR_BSPI, SPR_BSDS,  9,                               20,               A_Scream,        S_BSPI_DIE2,     0,     0     }, // S_BSPI_DIE1
    { SPR_BSPI, SPR_BSDS, 10,                                7,               A_Fall,          S_BSPI_DIE3,     0,     0     }, // S_BSPI_DIE2
    { SPR_BSPI, SPR_BSDS, 11,                                7,               NULL,            S_BSPI_DIE4,     0,     0     }, // S_BSPI_DIE3
    { SPR_BSPI, SPR_BSDS, 12,                                7,               NULL,            S_BSPI_DIE5,     0,     0     }, // S_BSPI_DIE4
    { SPR_BSPI, SPR_BSDS, 13,                                7,               NULL,            S_BSPI_DIE6,     0,     0     }, // S_BSPI_DIE5
    { SPR_BSPI, SPR_BSDS, 14,                                7,               NULL,            S_BSPI_DIE7,     0,     0     }, // S_BSPI_DIE6
    { SPR_BSPI, SPR_BSDS, 15,                               -1,               A_BossDeath,     S_NULL,          0,     0     }, // S_BSPI_DIE7
    { SPR_BSPI, SPR_BSDS, 15,                                5,               NULL,            S_BSPI_RAISE2,   0,     0     }, // S_BSPI_RAISE1
    { SPR_BSPI, SPR_BSDS, 14,                                5,               NULL,            S_BSPI_RAISE3,   0,     0     }, // S_BSPI_RAISE2
    { SPR_BSPI, SPR_BSDS, 13,                                5,               NULL,            S_BSPI_RAISE4,   0,     0     }, // S_BSPI_RAISE3
    { SPR_BSPI, SPR_BSDS, 12,                                5,               NULL,            S_BSPI_RAISE5,   0,     0     }, // S_BSPI_RAISE4
    { SPR_BSPI, SPR_BSDS, 11,                                5,               NULL,            S_BSPI_RAISE6,   0,     0     }, // S_BSPI_RAISE5
    { SPR_BSPI, SPR_BSDS, 10,                                5,               NULL,            S_BSPI_RAISE7,   0,     0     }, // S_BSPI_RAISE6
    { SPR_BSPI, SPR_BSDS,  9,                                5,               NULL,            S_BSPI_RUN1,     0,     0     }, // S_BSPI_RAISE7

    // Arachnotron Projectile (MT_ARACHPLAZ)
    { SPR_APLS, SPR_APLS,  0 | FF_FULLBRIGHT,                5,               NULL,            S_ARACH_PLAZ2,   0,     0     }, // S_ARACH_PLAZ
    { SPR_APLS, SPR_APLS,  1 | FF_FULLBRIGHT,                5,               NULL,            S_ARACH_PLAZ,    0,     0     }, // S_ARACH_PLAZ2
    { SPR_APBX, SPR_APBX,  0 | FF_FULLBRIGHT,                5,               NULL,            S_ARACH_PLEX2,   0,     0     }, // S_ARACH_PLEX
    { SPR_APBX, SPR_APBX,  1 | FF_FULLBRIGHT,                5,               NULL,            S_ARACH_PLEX3,   0,     0     }, // S_ARACH_PLEX2
    { SPR_APBX, SPR_APBX,  2 | FF_FULLBRIGHT,                5,               NULL,            S_ARACH_PLEX4,   0,     0     }, // S_ARACH_PLEX3
    { SPR_APBX, SPR_APBX,  3 | FF_FULLBRIGHT,                5,               NULL,            S_ARACH_PLEX5,   0,     0     }, // S_ARACH_PLEX4
    { SPR_APBX, SPR_APBX,  4 | FF_FULLBRIGHT,                5,               NULL,            S_NULL,          0,     0     }, // S_ARACH_PLEX5

    // Cyberdemon (MT_CYBORG)
    { SPR_CYBR, SPR_CYBR,  0,                               10,               A_Look,          S_CYBER_STND2,   0,     0     }, // S_CYBER_STND
    { SPR_CYBR, SPR_CYBR,  1,                               10,               A_Look,          S_CYBER_STND,    0,     0     }, // S_CYBER_STND2
    { SPR_CYBR, SPR_CYBR,  0,                                3,               A_Hoof,          S_CYBER_RUN2,    0,     0     }, // S_CYBER_RUN1
    { SPR_CYBR, SPR_CYBR,  0,                                3,               A_Chase,         S_CYBER_RUN3,    0,     0     }, // S_CYBER_RUN2
    { SPR_CYBR, SPR_CYBR,  1,                                3,               A_Chase,         S_CYBER_RUN4,    0,     0     }, // S_CYBER_RUN3
    { SPR_CYBR, SPR_CYBR,  1,                                3,               A_Chase,         S_CYBER_RUN5,    0,     0     }, // S_CYBER_RUN4
    { SPR_CYBR, SPR_CYBR,  2,                                3,               A_Chase,         S_CYBER_RUN6,    0,     0     }, // S_CYBER_RUN5
    { SPR_CYBR, SPR_CYBR,  2,                                3,               A_Chase,         S_CYBER_RUN7,    0,     0     }, // S_CYBER_RUN6
    { SPR_CYBR, SPR_CYBR,  3,                                3,               A_Metal,         S_CYBER_RUN8,    0,     0     }, // S_CYBER_RUN7
    { SPR_CYBR, SPR_CYBR,  3,                                3,               A_Chase,         S_CYBER_RUN1,    0,     0     }, // S_CYBER_RUN8
    { SPR_CYBR, SPR_CYBR,  4,                                6,               A_FaceTarget,    S_CYBER_ATK2,    0,     0     }, // S_CYBER_ATK1
    { SPR_CYBR, SPR_CYBR,  5 | FF_FULLBRIGHT,               12,               A_CyberAttack,   S_CYBER_ATK3,    0,     0     }, // S_CYBER_ATK2
    { SPR_CYBR, SPR_CYBR,  4,                               12,               A_FaceTarget,    S_CYBER_ATK4,    0,     0     }, // S_CYBER_ATK3
    { SPR_CYBR, SPR_CYBR,  5 | FF_FULLBRIGHT,               12,               A_CyberAttack,   S_CYBER_ATK5,    0,     0     }, // S_CYBER_ATK4
    { SPR_CYBR, SPR_CYBR,  4,                               12,               A_FaceTarget,    S_CYBER_ATK6,    0,     0     }, // S_CYBER_ATK5
    { SPR_CYBR, SPR_CYBR,  5 | FF_FULLBRIGHT,               12,               A_CyberAttack,   S_CYBER_RUN1,    0,     0     }, // S_CYBER_ATK6
    { SPR_CYBR, SPR_CYBR,  6,                               10,               A_Pain,          S_CYBER_RUN1,    0,     0     }, // S_CYBER_PAIN
    { SPR_CYBR, SPR_CYBR,  7,                               10,               NULL,            S_CYBER_DIE2,    0,     0     }, // S_CYBER_DIE1
    { SPR_CYBR, SPR_CYBR,  8,                               10,               A_Scream,        S_CYBER_DIE3,    0,     0     }, // S_CYBER_DIE2
    { SPR_CYBR, SPR_CYBR,  9 | FF_FULLBRIGHT,               10,               NULL,            S_CYBER_DIE4,    0,     0     }, // S_CYBER_DIE3
    { SPR_CYBR, SPR_CYBR, 10 | FF_FULLBRIGHT,               10,               NULL,            S_CYBER_DIE5,    0,     0     }, // S_CYBER_DIE4
    { SPR_CYBR, SPR_CYBR, 11 | FF_FULLBRIGHT,               10,               NULL,            S_CYBER_DIE6,    0,     0     }, // S_CYBER_DIE5
    { SPR_CYBR, SPR_CYBR, 12 | FF_FULLBRIGHT,               10,               A_Fall,          S_CYBER_DIE7,    0,     0     }, // S_CYBER_DIE6
    { SPR_CYBR, SPR_CYBR, 13 | FF_FULLBRIGHT,               10,               NULL,            S_CYBER_DIE8,    0,     0     }, // S_CYBER_DIE7
    { SPR_CYBR, SPR_CYBR, 14,                               10,               NULL,            S_CYBER_DIE9,    0,     0     }, // S_CYBER_DIE8
    { SPR_CYBR, SPR_CYBR, 15,                               30,               NULL,            S_CYBER_DIE10,   0,     0     }, // S_CYBER_DIE9
    { SPR_CYBR, SPR_CYBR, 15,                               -1,               A_BossDeath,     S_NULL,          0,     0     }, // S_CYBER_DIE10

    // Pain Elemental (MT_PAIN)
    { SPR_PAIN, SPR_PADS,  0,                               10,               A_Look,          S_PAIN_STND,     0,     0     }, // S_PAIN_STND
    { SPR_PAIN, SPR_PADS,  0,                                3,               A_Chase,         S_PAIN_RUN2,     0,     0     }, // S_PAIN_RUN1
    { SPR_PAIN, SPR_PADS,  0,                                3,               A_Chase,         S_PAIN_RUN3,     0,     0     }, // S_PAIN_RUN2
    { SPR_PAIN, SPR_PADS,  1,                                3,               A_Chase,         S_PAIN_RUN4,     0,     0     }, // S_PAIN_RUN3
    { SPR_PAIN, SPR_PADS,  1,                                3,               A_Chase,         S_PAIN_RUN5,     0,     0     }, // S_PAIN_RUN4
    { SPR_PAIN, SPR_PADS,  2,                                3,               A_Chase,         S_PAIN_RUN6,     0,     0     }, // S_PAIN_RUN5
    { SPR_PAIN, SPR_PADS,  2,                                3,               A_Chase,         S_PAIN_RUN1,     0,     0     }, // S_PAIN_RUN6
    { SPR_PAIN, SPR_PADS,  3,                                5,               A_FaceTarget,    S_PAIN_ATK2,     0,     0     }, // S_PAIN_ATK1
    { SPR_PAIN, SPR_PADS,  4,                                5,               A_FaceTarget,    S_PAIN_ATK3,     0,     0     }, // S_PAIN_ATK2
    { SPR_PAIN, SPR_PADS,  5 | FF_FULLBRIGHT,                5,               A_FaceTarget,    S_PAIN_ATK4,     0,     0     }, // S_PAIN_ATK3
    { SPR_PAIN, SPR_PADS,  5 | FF_FULLBRIGHT,                0,               A_PainAttack,    S_PAIN_RUN1,     0,     0     }, // S_PAIN_ATK4
    { SPR_PAIN, SPR_PADS,  6,                                6,               NULL,            S_PAIN_PAIN2,    0,     0     }, // S_PAIN_PAIN
    { SPR_PAIN, SPR_PADS,  6,                                6,               A_Pain,          S_PAIN_RUN1,     0,     0     }, // S_PAIN_PAIN2
    { SPR_PAIN, SPR_PADS,  7 | FF_FULLBRIGHT,                8,               NULL,            S_PAIN_DIE2,     0,     0     }, // S_PAIN_DIE1
    { SPR_PAIN, SPR_PADS,  8 | FF_FULLBRIGHT,                8,               A_Scream,        S_PAIN_DIE3,     0,     0     }, // S_PAIN_DIE2
    { SPR_PAIN, SPR_PADS,  9 | FF_FULLBRIGHT,                8,               NULL,            S_PAIN_DIE4,     0,     0     }, // S_PAIN_DIE3
    { SPR_PAIN, SPR_PADS, 10 | FF_FULLBRIGHT,                8,               NULL,            S_PAIN_DIE5,     0,     0     }, // S_PAIN_DIE4
    { SPR_PAIN, SPR_PADS, 11 | FF_FULLBRIGHT,                8,               A_PainDie,       S_PAIN_DIE6,     0,     0     }, // S_PAIN_DIE5
    { SPR_PAIN, SPR_PADS, 12 | FF_FULLBRIGHT,                8,               NULL,            S_NULL,          0,     0     }, // S_PAIN_DIE6
    { SPR_PAIN, SPR_PADS, 12,                                8,               NULL,            S_PAIN_RAISE2,   0,     0     }, // S_PAIN_RAISE1
    { SPR_PAIN, SPR_PADS, 11,                                8,               NULL,            S_PAIN_RAISE3,   0,     0     }, // S_PAIN_RAISE2
    { SPR_PAIN, SPR_PADS, 10,                                8,               NULL,            S_PAIN_RAISE4,   0,     0     }, // S_PAIN_RAISE3
    { SPR_PAIN, SPR_PADS,  9,                                8,               NULL,            S_PAIN_RAISE5,   0,     0     }, // S_PAIN_RAISE4
    { SPR_PAIN, SPR_PADS,  8,                                8,               NULL,            S_PAIN_RAISE6,   0,     0     }, // S_PAIN_RAISE5
    { SPR_PAIN, SPR_PADS,  7,                                8,               NULL,            S_PAIN_RUN1,     0,     0     }, // S_PAIN_RAISE6

    // Wolfenstein SS (MT_WOLFSS)
    { SPR_SSWV, SPR_SSWV,  0,                               10,               A_Look,          S_SSWV_STND2,    0,     0     }, // S_SSWV_STND
    { SPR_SSWV, SPR_SSWV,  1,                               10,               A_Look,          S_SSWV_STND,     0,     0     }, // S_SSWV_STND2
    { SPR_SSWV, SPR_SSWV,  0,                                3,               A_Chase,         S_SSWV_RUN2,     0,     0     }, // S_SSWV_RUN1
    { SPR_SSWV, SPR_SSWV,  0,                                3,               A_Chase,         S_SSWV_RUN3,     0,     0     }, // S_SSWV_RUN2
    { SPR_SSWV, SPR_SSWV,  1,                                3,               A_Chase,         S_SSWV_RUN4,     0,     0     }, // S_SSWV_RUN3
    { SPR_SSWV, SPR_SSWV,  1,                                3,               A_Chase,         S_SSWV_RUN5,     0,     0     }, // S_SSWV_RUN4
    { SPR_SSWV, SPR_SSWV,  2,                                3,               A_Chase,         S_SSWV_RUN6,     0,     0     }, // S_SSWV_RUN5
    { SPR_SSWV, SPR_SSWV,  2,                                3,               A_Chase,         S_SSWV_RUN7,     0,     0     }, // S_SSWV_RUN6
    { SPR_SSWV, SPR_SSWV,  3,                                3,               A_Chase,         S_SSWV_RUN8,     0,     0     }, // S_SSWV_RUN7
    { SPR_SSWV, SPR_SSWV,  3,                                3,               A_Chase,         S_SSWV_RUN1,     0,     0     }, // S_SSWV_RUN8
    { SPR_SSWV, SPR_SSWV,  4,                               10,               A_FaceTarget,    S_SSWV_ATK2,     0,     0     }, // S_SSWV_ATK1
    { SPR_SSWV, SPR_SSWV,  5,                               10,               A_FaceTarget,    S_SSWV_ATK3,     0,     0     }, // S_SSWV_ATK2
    { SPR_SSWV, SPR_SSWV,  6 | FF_FULLBRIGHT,                4,               A_CPosAttack,    S_SSWV_ATK4,     0,     0     }, // S_SSWV_ATK3
    { SPR_SSWV, SPR_SSWV,  5,                                6,               A_FaceTarget,    S_SSWV_ATK5,     0,     0     }, // S_SSWV_ATK4
    { SPR_SSWV, SPR_SSWV,  6 | FF_FULLBRIGHT,                4,               A_CPosAttack,    S_SSWV_ATK6,     0,     0     }, // S_SSWV_ATK5
    { SPR_SSWV, SPR_SSWV,  5,                                1,               A_CPosRefire,    S_SSWV_ATK2,     0,     0     }, // S_SSWV_ATK6
    { SPR_SSWV, SPR_SSWV,  7,                                3,               NULL,            S_SSWV_PAIN2,    0,     0     }, // S_SSWV_PAIN
    { SPR_SSWV, SPR_SSWV,  7,                                3,               A_Pain,          S_SSWV_RUN1,     0,     0     }, // S_SSWV_PAIN2
    { SPR_SSWV, SPR_SSWV,  8,                                5,               NULL,            S_SSWV_DIE2,     0,     0     }, // S_SSWV_DIE1
    { SPR_SSWV, SPR_SSWV,  9,                                5,               A_Scream,        S_SSWV_DIE3,     0,     0     }, // S_SSWV_DIE2
    { SPR_SSWV, SPR_SSWV, 10,                                5,               A_Fall,          S_SSWV_DIE4,     0,     0     }, // S_SSWV_DIE3
    { SPR_SSWV, SPR_SSWV, 11,                                5,               NULL,            S_SSWV_DIE5,     0,     0     }, // S_SSWV_DIE4
    { SPR_SSWV, SPR_SSWV, 12,                               -1,               NULL,            S_NULL,          0,     0     }, // S_SSWV_DIE5
    { SPR_SSWV, SPR_SSWV, 13,                                5,               NULL,            S_SSWV_XDIE2,    0,     0     }, // S_SSWV_XDIE1
    { SPR_SSWV, SPR_SSWV, 14,                                5,               A_XScream,       S_SSWV_XDIE3,    0,     0     }, // S_SSWV_XDIE2
    { SPR_SSWV, SPR_SSWV, 15,                                5,               A_Fall,          S_SSWV_XDIE4,    0,     0     }, // S_SSWV_XDIE3
    { SPR_SSWV, SPR_SSWV, 16,                                5,               NULL,            S_SSWV_XDIE5,    0,     0     }, // S_SSWV_XDIE4
    { SPR_SSWV, SPR_SSWV, 17,                                5,               NULL,            S_SSWV_XDIE6,    0,     0     }, // S_SSWV_XDIE5
    { SPR_SSWV, SPR_SSWV, 18,                                5,               NULL,            S_SSWV_XDIE7,    0,     0     }, // S_SSWV_XDIE6
    { SPR_SSWV, SPR_SSWV, 19,                                5,               NULL,            S_SSWV_XDIE8,    0,     0     }, // S_SSWV_XDIE7
    { SPR_SSWV, SPR_SSWV, 20,                                5,               NULL,            S_SSWV_XDIE9,    0,     0     }, // S_SSWV_XDIE8
    { SPR_SSWV, SPR_SSWV, 21,                               -1,               NULL,            S_NULL,          0,     0     }, // S_SSWV_XDIE9
    { SPR_SSWV, SPR_SSWV, 12,                                5,               NULL,            S_SSWV_RAISE2,   0,     0     }, // S_SSWV_RAISE1
    { SPR_SSWV, SPR_SSWV, 11,                                5,               NULL,            S_SSWV_RAISE3,   0,     0     }, // S_SSWV_RAISE2
    { SPR_SSWV, SPR_SSWV, 10,                                5,               NULL,            S_SSWV_RAISE4,   0,     0     }, // S_SSWV_RAISE3
    { SPR_SSWV, SPR_SSWV,  9,                                5,               NULL,            S_SSWV_RAISE5,   0,     0     }, // S_SSWV_RAISE4
    { SPR_SSWV, SPR_SSWV,  8,                                5,               NULL,            S_SSWV_RUN1,     0,     0     }, // S_SSWV_RAISE5

    // Commander Keen (MT_KEEN)
    { SPR_KEEN, SPR_KEEN,  0,                               -1,               NULL,            S_KEENSTND,      0,     0     }, // S_KEENSTND
    { SPR_KEEN, SPR_KEEN,  0,                                6,               NULL,            S_COMMKEEN2,     0,     0     }, // S_COMMKEEN
    { SPR_KEEN, SPR_KEEN,  1,                                6,               NULL,            S_COMMKEEN3,     0,     0     }, // S_COMMKEEN2
    { SPR_KEEN, SPR_KEEN,  2,                                6,               A_Scream,        S_COMMKEEN4,     0,     0     }, // S_COMMKEEN3
    { SPR_KEEN, SPR_KEEN,  3,                                6,               NULL,            S_COMMKEEN5,     0,     0     }, // S_COMMKEEN4
    { SPR_KEEN, SPR_KEEN,  4,                                6,               NULL,            S_COMMKEEN6,     0,     0     }, // S_COMMKEEN5
    { SPR_KEEN, SPR_KEEN,  5,                                6,               NULL,            S_COMMKEEN7,     0,     0     }, // S_COMMKEEN6
    { SPR_KEEN, SPR_KEEN,  6,                                6,               NULL,            S_COMMKEEN8,     0,     0     }, // S_COMMKEEN7
    { SPR_KEEN, SPR_KEEN,  7,                                6,               NULL,            S_COMMKEEN9,     0,     0     }, // S_COMMKEEN8
    { SPR_KEEN, SPR_KEEN,  8,                                6,               NULL,            S_COMMKEEN10,    0,     0     }, // S_COMMKEEN9
    { SPR_KEEN, SPR_KEEN,  9,                                6,               NULL,            S_COMMKEEN11,    0,     0     }, // S_COMMKEEN10
    { SPR_KEEN, SPR_KEEN, 10,                                6,               A_KeenDie,       S_COMMKEEN12,    0,     0     }, // S_COMMKEEN11
    { SPR_KEEN, SPR_KEEN, 11,                               -1,               NULL,            S_NULL,          0,     0     }, // S_COMMKEEN12
    { SPR_KEEN, SPR_KEEN, 12,                                4,               NULL,            S_KEENPAIN2,     0,     0     }, // S_KEENPAIN
    { SPR_KEEN, SPR_KEEN, 12,                                8,               A_Pain,          S_KEENSTND,      0,     0     }, // S_KEENPAIN2

    // Boss Brain (MT_BOSSBRAIN)
    { SPR_BBRN, SPR_BBRN,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_BRAIN
    { SPR_BBRN, SPR_BBRN,  1,                               36,               A_BrainPain,     S_BRAIN,         0,     0     }, // S_BRAIN_PAIN
    { SPR_BBRN, SPR_BBRN,  0,                              100,               A_BrainScream,   S_BRAIN_DIE2,    0,     0     }, // S_BRAIN_DIE1
    { SPR_BBRN, SPR_BBRN,  0,                               10,               NULL,            S_BRAIN_DIE3,    0,     0     }, // S_BRAIN_DIE2
    { SPR_BBRN, SPR_BBRN,  0,                               10,               NULL,            S_BRAIN_DIE4,    0,     0     }, // S_BRAIN_DIE3
    { SPR_BBRN, SPR_BBRN,  0,                               -1,               A_BrainDie,      S_NULL,          0,     0     }, // S_BRAIN_DIE4

    // MT_BOSSSPIT
    { SPR_SSWV, SPR_SSWV,  0,                               10,               A_Look,          S_BRAINEYE,      0,     0     }, // S_BRAINEYE
    { SPR_SSWV, SPR_SSWV,  0,                              181,               A_BrainAwake,    S_BRAINEYE1,     0,     0     }, // S_BRAINEYESEE
    { SPR_SSWV, SPR_SSWV,  0,                              150,               A_BrainSpit,     S_BRAINEYE1,     0,     0     }, // S_BRAINEYE1

    // Boss Brain Projectile (MT_SPAWNSHOT)
    { SPR_BOSF, SPR_BOSF,  0 | FF_FULLBRIGHT,                3,               A_SpawnSound,    S_SPAWN2,        0,     0     }, // S_SPAWN1
    { SPR_BOSF, SPR_BOSF,  1 | FF_FULLBRIGHT,                3,               A_SpawnFly,      S_SPAWN3,        0,     0     }, // S_SPAWN2
    { SPR_BOSF, SPR_BOSF,  2 | FF_FULLBRIGHT,                3,               A_SpawnFly,      S_SPAWN4,        0,     0     }, // S_SPAWN3
    { SPR_BOSF, SPR_BOSF,  3 | FF_FULLBRIGHT,                3,               A_SpawnFly,      S_SPAWN1,        0,     0     }, // S_SPAWN4

    // Boss Brain Teleport Fog (MT_SPAWNFIRE)
    { SPR_FIRE, SPR_FIRE,  0 | FF_FULLBRIGHT,                4,               A_Fire,          S_SPAWNFIRE2,    0,     0     }, // S_SPAWNFIRE1
    { SPR_FIRE, SPR_FIRE,  1 | FF_FULLBRIGHT,                4,               A_Fire,          S_SPAWNFIRE3,    0,     0     }, // S_SPAWNFIRE2
    { SPR_FIRE, SPR_FIRE,  2 | FF_FULLBRIGHT,                4,               A_Fire,          S_SPAWNFIRE4,    0,     0     }, // S_SPAWNFIRE3
    { SPR_FIRE, SPR_FIRE,  3 | FF_FULLBRIGHT,                4,               A_Fire,          S_SPAWNFIRE5,    0,     0     }, // S_SPAWNFIRE4
    { SPR_FIRE, SPR_FIRE,  4 | FF_FULLBRIGHT,                4,               A_Fire,          S_SPAWNFIRE6,    0,     0     }, // S_SPAWNFIRE5
    { SPR_FIRE, SPR_FIRE,  5 | FF_FULLBRIGHT,                4,               A_Fire,          S_SPAWNFIRE7,    0,     0     }, // S_SPAWNFIRE6
    { SPR_FIRE, SPR_FIRE,  6 | FF_FULLBRIGHT,                4,               A_Fire,          S_SPAWNFIRE8,    0,     0     }, // S_SPAWNFIRE7
    { SPR_FIRE, SPR_FIRE,  7 | FF_FULLBRIGHT,                4,               A_Fire,          S_NULL,          0,     0     }, // S_SPAWNFIRE8
    { SPR_MISL, SPR_MISL,  1 | FF_FULLBRIGHT,               10,               NULL,            S_BRAINEXPLODE2, 0,     0     }, // S_BRAINEXPLODE1
    { SPR_MISL, SPR_MISL,  2 | FF_FULLBRIGHT,               10,               NULL,            S_BRAINEXPLODE3, 0,     0     }, // S_BRAINEXPLODE2
    { SPR_MISL, SPR_MISL,  3 | FF_FULLBRIGHT,               10,               A_BrainExplode,  S_NULL,          0,     0     }, // S_BRAINEXPLODE3

    // Green Armor (MT_MISC0)
    { SPR_ARM1, SPR_ARM1,  0,                                6,               NULL,            S_ARM1A,         0,     0     }, // S_ARM1
    { SPR_ARM1, SPR_ARM1,  1 | FF_FULLBRIGHT,                6,               NULL,            S_ARM1,          0,     0     }, // S_ARM1A

    // Blue Armor (MT_MISC1)
    { SPR_ARM2, SPR_ARM2,  0,                                6,               NULL,            S_ARM2A,         0,     0     }, // S_ARM2
    { SPR_ARM2, SPR_ARM2,  1 | FF_FULLBRIGHT,                6,               NULL,            S_ARM2,          0,     0     }, // S_ARM2A

    // Barrel (MT_BARREL)
    { SPR_BAR1, SPR_BAR1,  0,                                6,               NULL,            S_BAR3,          0,     0     }, // S_BAR2
    { SPR_BAR1, SPR_BAR1,  1,                                6,               NULL,            S_BAR1,          0,     0     }, // S_BAR3
    { SPR_BEXP, SPR_BEXP,  0 | FF_FULLBRIGHT,                5,               NULL,            S_BEXP2,         0,     0     }, // S_BEXP
    { SPR_BEXP, SPR_BEXP,  1 | FF_FULLBRIGHT,                5,               A_Scream,        S_BEXP3,         0,     0     }, // S_BEXP2
    { SPR_BEXP, SPR_BEXP,  2 | FF_FULLBRIGHT,                5,               NULL,            S_BEXP4,         0,     0     }, // S_BEXP3
    { SPR_BEXP, SPR_BEXP,  3 | FF_FULLBRIGHT,               10,               A_Explode,       S_BEXP5,         0,     0     }, // S_BEXP4
    { SPR_BEXP, SPR_BEXP,  4 | FF_FULLBRIGHT,               10,               NULL,            S_NULL,          0,     0     }, // S_BEXP5

    // Burning Barrel (MT_MISC77)
    { SPR_FCAN, SPR_FCAN,  0 | FF_FULLBRIGHT,                4,               NULL,            S_BBAR2,         0,     0     }, // S_BBAR1
    { SPR_FCAN, SPR_FCAN,  1 | FF_FULLBRIGHT,                4,               NULL,            S_BBAR3,         0,     0     }, // S_BBAR2
    { SPR_FCAN, SPR_FCAN,  2 | FF_FULLBRIGHT,                4,               NULL,            S_BBAR1,         0,     0     }, // S_BBAR3

    // Health Bonus (MT_MISC2)
    { SPR_BON1, SPR_BON1,  0,                                6,               NULL,            S_BON1A,         0,     0     }, // S_BON1
    { SPR_BON1, SPR_BON1,  1,                                6,               NULL,            S_BON1B,         0,     0     }, // S_BON1A
    { SPR_BON1, SPR_BON1,  2,                                6,               NULL,            S_BON1C,         0,     0     }, // S_BON1B
    { SPR_BON1, SPR_BON1,  3,                                6,               NULL,            S_BON1D,         0,     0     }, // S_BON1C
    { SPR_BON1, SPR_BON1,  2,                                6,               NULL,            S_BON1E,         0,     0     }, // S_BON1D
    { SPR_BON1, SPR_BON1,  1,                                6,               NULL,            S_BON1,          0,     0     }, // S_BON1E

    // Armor Bonus (MT_MISC3)
    { SPR_BON2, SPR_BON2,  0,                                6,               NULL,            S_BON2A,         0,     0     }, // S_BON2
    { SPR_BON2, SPR_BON2,  1,                                6,               NULL,            S_BON2B,         0,     0     }, // S_BON2A
    { SPR_BON2, SPR_BON2,  2,                                6,               NULL,            S_BON2C,         0,     0     }, // S_BON2B
    { SPR_BON2, SPR_BON2,  3,                                6,               NULL,            S_BON2D,         0,     0     }, // S_BON2C
    { SPR_BON2, SPR_BON2,  2,                                6,               NULL,            S_BON2E,         0,     0     }, // S_BON2D
    { SPR_BON2, SPR_BON2,  1,                                6,               NULL,            S_BON2,          0,     0     }, // S_BON2E

    // Blue Keycard (MT_MISC4)
    { SPR_BKEY, SPR_BKEY,  0,                               10,               NULL,            S_BKEY2,         0,     0     }, // S_BKEY
    { SPR_BKEY, SPR_BKEY,  1 | FF_FULLBRIGHT,               10,               NULL,            S_BKEY,          0,     0     }, // S_BKEY2

    // Red Keycard (MT_MISC5)
    { SPR_RKEY, SPR_RKEY,  0,                               10,               NULL,            S_RKEY2,         0,     0     }, // S_RKEY
    { SPR_RKEY, SPR_RKEY,  1 | FF_FULLBRIGHT,               10,               NULL,            S_RKEY,          0,     0     }, // S_RKEY2

    // Yellow Keycard (MT_MISC6)
    { SPR_YKEY, SPR_YKEY,  0,                               10,               NULL,            S_YKEY2,         0,     0     }, // S_YKEY
    { SPR_YKEY, SPR_YKEY,  1 | FF_FULLBRIGHT,               10,               NULL,            S_YKEY,          0,     0     }, // S_YKEY2

    // Blue Skull Key (MT_MISC9)
    { SPR_BSKU, SPR_BSKU,  0,                               10,               NULL,            S_BSKULL2,       0,     0     }, // S_BSKULL
    { SPR_BSKU, SPR_BSKU,  1 | FF_FULLBRIGHT,               10,               NULL,            S_BSKULL,        0,     0     }, // S_BSKULL2

    // Red Skull Key (MT_MISC8)
    { SPR_RSKU, SPR_RSKU,  0,                               10,               NULL,            S_RSKULL2,       0,     0     }, // S_RSKULL
    { SPR_RSKU, SPR_RSKU,  1 | FF_FULLBRIGHT,               10,               NULL,            S_RSKULL,        0,     0     }, // S_RSKULL2

    // Yellow Skull Key (MT_MISC7)
    { SPR_YSKU, SPR_YSKU,  0,                               10,               NULL,            S_YSKULL2,       0,     0     }, // S_YSKULL
    { SPR_YSKU, SPR_YSKU,  1 | FF_FULLBRIGHT,               10,               NULL,            S_YSKULL,        0,     0     }, // S_YSKULL2

    // Stimpack (MT_MISC10)
    { SPR_STIM, SPR_STIM,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_STIM

    // Medikit (MT_MISC11)
    { SPR_MEDI, SPR_MEDI,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_MEDI

    // SoulSphere (MT_MISC12)
    { SPR_SOUL, SPR_SOUL,  0 | FF_FULLBRIGHT,                6,               NULL,            S_SOUL2,         0,     0     }, // S_SOUL
    { SPR_SOUL, SPR_SOUL,  1 | FF_FULLBRIGHT,                6,               NULL,            S_SOUL3,         0,     0     }, // S_SOUL2
    { SPR_SOUL, SPR_SOUL,  2 | FF_FULLBRIGHT,                6,               NULL,            S_SOUL4,         0,     0     }, // S_SOUL3
    { SPR_SOUL, SPR_SOUL,  3 | FF_FULLBRIGHT,                6,               NULL,            S_SOUL5,         0,     0     }, // S_SOUL4
    { SPR_SOUL, SPR_SOUL,  2 | FF_FULLBRIGHT,                6,               NULL,            S_SOUL6,         0,     0     }, // S_SOUL5
    { SPR_SOUL, SPR_SOUL,  1 | FF_FULLBRIGHT,                6,               NULL,            S_SOUL,          0,     0     }, // S_SOUL6

    // Invulnerability (MT_INV)
    { SPR_PINV, SPR_PINV,  0 | FF_FULLBRIGHT,                6,               NULL,            S_PINV2,         0,     0     }, // S_PINV
    { SPR_PINV, SPR_PINV,  1 | FF_FULLBRIGHT,                6,               NULL,            S_PINV3,         0,     0     }, // S_PINV2
    { SPR_PINV, SPR_PINV,  2 | FF_FULLBRIGHT,                6,               NULL,            S_PINV4,         0,     0     }, // S_PINV3
    { SPR_PINV, SPR_PINV,  3 | FF_FULLBRIGHT,                6,               NULL,            S_PINV,          0,     0     }, // S_PINV4

    // Berserk (MT_MISC13)
    { SPR_PSTR, SPR_PSTR,  0 | FF_FULLBRIGHT,               -1,               NULL,            S_NULL,          0,     0     }, // S_PSTR

    // Partial Invisibility (MT_INS)
    { SPR_PINS, SPR_PINS,  0 | FF_FULLBRIGHT,                6,               NULL,            S_PINS2,         0,     0     }, // S_PINS
    { SPR_PINS, SPR_PINS,  1 | FF_FULLBRIGHT,                6,               NULL,            S_PINS3,         0,     0     }, // S_PINS2
    { SPR_PINS, SPR_PINS,  2 | FF_FULLBRIGHT,                6,               NULL,            S_PINS4,         0,     0     }, // S_PINS3
    { SPR_PINS, SPR_PINS,  3 | FF_FULLBRIGHT,                6,               NULL,            S_PINS,          0,     0     }, // S_PINS4

    // MegaSphere (MT_MEGA)
    { SPR_MEGA, SPR_MEGA,  0 | FF_FULLBRIGHT,                6,               NULL,            S_MEGA2,         0,     0     }, // S_MEGA
    { SPR_MEGA, SPR_MEGA,  1 | FF_FULLBRIGHT,                6,               NULL,            S_MEGA3,         0,     0     }, // S_MEGA2
    { SPR_MEGA, SPR_MEGA,  2 | FF_FULLBRIGHT,                6,               NULL,            S_MEGA4,         0,     0     }, // S_MEGA3
    { SPR_MEGA, SPR_MEGA,  3 | FF_FULLBRIGHT,                6,               NULL,            S_MEGA,          0,     0     }, // S_MEGA4

    // Radiation Shielding Suit (MT_MISC14)
    { SPR_SUIT, SPR_SUIT,  0 | FF_FULLBRIGHT,               -1,               NULL,            S_NULL,          0,     0     }, // S_SUIT

    // Computer Area Map (MT_MISC15)
    { SPR_PMAP, SPR_PMAP,  0 | FF_FULLBRIGHT,                6,               NULL,            S_PMAP2,         0,     0     }, // S_PMAP
    { SPR_PMAP, SPR_PMAP,  1 | FF_FULLBRIGHT,                6,               NULL,            S_PMAP3,         0,     0     }, // S_PMAP2
    { SPR_PMAP, SPR_PMAP,  2 | FF_FULLBRIGHT,                6,               NULL,            S_PMAP4,         0,     0     }, // S_PMAP3
    { SPR_PMAP, SPR_PMAP,  3 | FF_FULLBRIGHT,                6,               NULL,            S_PMAP5,         0,     0     }, // S_PMAP4
    { SPR_PMAP, SPR_PMAP,  2 | FF_FULLBRIGHT,                6,               NULL,            S_PMAP6,         0,     0     }, // S_PMAP5
    { SPR_PMAP, SPR_PMAP,  1 | FF_FULLBRIGHT,                6,               NULL,            S_PMAP,          0,     0     }, // S_PMAP6

    // Light Amplification Visor (MT_MISC16)
    { SPR_PVIS, SPR_PVIS,  0 | FF_FULLBRIGHT,                6,               NULL,            S_PVIS2,         0,     0     }, // S_PVIS
    { SPR_PVIS, SPR_PVIS,  1,                                6,               NULL,            S_PVIS,          0,     0     }, // S_PVIS2

    // Clip (MT_CLIP)
    { SPR_CLIP, SPR_CLIP,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_CLIP

    // Box of Bullets (MT_MISC17)
    { SPR_AMMO, SPR_AMMO,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_AMMO

    // Rocket (MT_MISC18)
    { SPR_ROCK, SPR_ROCK,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_ROCK

    // Box of Rockets (MT_MISC19)
    { SPR_BROK, SPR_BROK,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_BROK

    // Cell (MT_MISC20)
    { SPR_CELL, SPR_CELL,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_CELL

    // Cell Pack (MT_MISC21)
    { SPR_CELP, SPR_CELP,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_CELP

    // Shotgun Shells (MT_MISC22)
    { SPR_SHEL, SPR_SHEL,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_SHEL

    // Box of Shotgun Shells (MT_MISC23)
    { SPR_SBOX, SPR_SBOX,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_SBOX

    // Backpack (MT_MISC24)
    { SPR_BPAK, SPR_BPAK,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_BPAK

    // BFG 9000 (MT_MISC25)
    { SPR_BFUG, SPR_BFUG,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_BFUG

    // Chaingun (MT_CHAINGUN)
    { SPR_MGUN, SPR_MGUN,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_MGUN

    // Chainsaw (MT_MISC26)
    { SPR_CSAW, SPR_CSAW,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_CSAW

    // Rocket Launcher (MT_MISC27)
    { SPR_LAUN, SPR_LAUN,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_LAUN

    // Plasma Rifle (MT_MISC28)
    { SPR_PLAS, SPR_PLAS,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_PLAS

    // Shotgun (MT_SHOTGUN)
    { SPR_SHOT, SPR_SHOT,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_SHOT

    // Super Shotgun (MT_SUPERSHOTGUN)
    { SPR_SGN2, SPR_SGN2,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_SHOT2

    // Floor Lamp (MT_MISC31)
    { SPR_COLU, SPR_COLU,  0 | FF_FULLBRIGHT,               -1,               NULL,            S_NULL,          0,     0     }, // S_COLU

    // Grey Stalagmite (unused)
    { SPR_SMT2, SPR_SMT2,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_STALAG

    // Hanging victim, twitching (MT_MISC51 and MT_MISC60)
    { SPR_GOR1, SPR_GOR1,  0,                               10,               NULL,            S_BLOODYTWITCH2, 0,     0     }, // S_BLOODYTWITCH
    { SPR_GOR1, SPR_GOR1,  1,                               15,               NULL,            S_BLOODYTWITCH3, 0,     0     }, // S_BLOODYTWITCH2
    { SPR_GOR1, SPR_GOR1,  2,                                8,               NULL,            S_BLOODYTWITCH4, 0,     0     }, // S_BLOODYTWITCH3
    { SPR_GOR1, SPR_GOR1,  1,                                6,               NULL,            S_BLOODYTWITCH,  0,     0     }, // S_BLOODYTWITCH4

    { SPR_PLAY, SPR_PLAY, 13,                               -1,               NULL,            S_NULL,          0,     0     }, // S_DEADTORSO
    { SPR_PLAY, SPR_PLAY, 18,                               -1,               NULL,            S_NULL,          0,     0     }, // S_DEADBOTTOM

    // Five skulls shishkebab
    { SPR_POL2, SPR_POL2,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_HEADSONSTICK

    // Pool of blood and flesh (MT_MISC71)
    { SPR_POL5, SPR_POL5,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_GIBS

    // Skull on a pole (MT_MISC70 and MT_MISC72)
    { SPR_POL4, SPR_POL4,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_HEADONASTICK

    // Pile of skulls and candles (MT_MISC73)
    { SPR_POL3, SPR_POL3,  0 | FF_FULLBRIGHT,                6,               NULL,            S_HEADCANDLES2,  0,     0     }, // S_HEADCANDLES
    { SPR_POL3, SPR_POL3,  1 | FF_FULLBRIGHT,                6,               NULL,            S_HEADCANDLES,   0,     0     }, // S_HEADCANDLES2

    // Impaled human (MT_MISC74)
    { SPR_POL1, SPR_POL1,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_DEADSTICK

    // Twitching impaled human (MT_MISC75)
    { SPR_POL6, SPR_POL6,  0,                                6,               NULL,            S_LIVESTICK2,    0,     0     }, // S_LIVESTICK
    { SPR_POL6, SPR_POL6,  1,                                8,               NULL,            S_LIVESTICK,     0,     0     }, // S_LIVESTICK2

    // Hanging victim, arms out (MT_MISC52 and MT_MISC56)
    { SPR_GOR2, SPR_GOR2,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_MEAT2

    // Hanging victim, one-legged (MT_MISC53 and MT_MISC58)
    { SPR_GOR3, SPR_GOR3,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_MEAT3

    // Hanging pair of legs (MT_MISC54 and MT_MISC57)
    { SPR_GOR4, SPR_GOR4,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_MEAT4

    // Hanging leg (MT_MISC55 and MT_MISC59)
    { SPR_GOR5, SPR_GOR5,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_MEAT5

    // Stalagmite (MT_MISC47)
    { SPR_SMIT, SPR_SMIT,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_STALAGTITE

    // Tall green pillar (MT_MISC32)
    { SPR_COL1, SPR_COL1,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_TALLGRNCOL

    // Short green pillar (MT_MISC33)
    { SPR_COL2, SPR_COL2,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_SHRTGRNCOL

    // Tall red pillar (MT_MISC34)
    { SPR_COL3, SPR_COL3,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_TALLREDCOL

    // Short red pillar (MT_MISC35)
    { SPR_COL4, SPR_COL4,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_SHRTREDCOL

    // Candle (MT_MISC49)
    { SPR_CAND, SPR_CAND,  0 | FF_FULLBRIGHT,               -1,               NULL,            S_NULL,          0,     0     }, // S_CANDLESTIK

    // Candelabra (MT_MISC50)
    { SPR_CBRA, SPR_CBRA,  0 | FF_FULLBRIGHT,               -1,               NULL,            S_NULL,          0,     0     }, // S_CANDELABRA

    // Short red pillar with skull (MT_MISC36)
    { SPR_COL6, SPR_COL6,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_SKULLCOL

    // Burnt tree (MT_MISC40)
    { SPR_TRE1, SPR_TRE1,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_TORCHTREE

    // Large brown tree (MT_MISC76)
    { SPR_TRE2, SPR_TRE2,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_BIGTREE

    // Tall techno pillar (MT_MISC48)
    { SPR_ELEC, SPR_ELEC,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_TECHPILLAR

    // Evil eye (MT_MISC38)
    { SPR_CEYE, SPR_CEYE,  0 | FF_FULLBRIGHT,                6,               NULL,            S_EVILEYE2,      0,     0     }, // S_EVILEYE
    { SPR_CEYE, SPR_CEYE,  1 | FF_FULLBRIGHT,                6,               NULL,            S_EVILEYE3,      0,     0     }, // S_EVILEYE2
    { SPR_CEYE, SPR_CEYE,  2 | FF_FULLBRIGHT,                6,               NULL,            S_EVILEYE4,      0,     0     }, // S_EVILEYE3
    { SPR_CEYE, SPR_CEYE,  1 | FF_FULLBRIGHT,                6,               NULL,            S_EVILEYE,       0,     0     }, // S_EVILEYE4

    // Floating skull (MT_MISC39)
    { SPR_FSKU, SPR_FSKU,  0 | FF_FULLBRIGHT,                6,               NULL,            S_FLOATSKULL2,   0,     0     }, // S_FLOATSKULL
    { SPR_FSKU, SPR_FSKU,  1 | FF_FULLBRIGHT,                6,               NULL,            S_FLOATSKULL3,   0,     0     }, // S_FLOATSKULL2
    { SPR_FSKU, SPR_FSKU,  2 | FF_FULLBRIGHT,                6,               NULL,            S_FLOATSKULL,    0,     0     }, // S_FLOATSKULL3

    // Short green pillar with beating heart (MT_MISC37)
    { SPR_COL5, SPR_COL5,  0,                               14,               NULL,            S_HEARTCOL2,     0,     0     }, // S_HEARTCOL
    { SPR_COL5, SPR_COL5,  1,                               14,               NULL,            S_HEARTCOL,      0,     0     }, // S_HEARTCOL2

    // Tall blue firestick (MT_MISC41)
    { SPR_TBLU, SPR_TBLU,  0 | FF_FULLBRIGHT,                4,               NULL,            S_BLUETORCH2,    0,     0     }, // S_BLUETORCH
    { SPR_TBLU, SPR_TBLU,  1 | FF_FULLBRIGHT,                4,               NULL,            S_BLUETORCH3,    0,     0     }, // S_BLUETORCH2
    { SPR_TBLU, SPR_TBLU,  2 | FF_FULLBRIGHT,                4,               NULL,            S_BLUETORCH4,    0,     0     }, // S_BLUETORCH3
    { SPR_TBLU, SPR_TBLU,  3 | FF_FULLBRIGHT,                4,               NULL,            S_BLUETORCH,     0,     0     }, // S_BLUETORCH4

    // Tall green firestick (MT_MISC42)
    { SPR_TGRN, SPR_TGRN,  0 | FF_FULLBRIGHT,                4,               NULL,            S_GREENTORCH2,   0,     0     }, // S_GREENTORCH
    { SPR_TGRN, SPR_TGRN,  1 | FF_FULLBRIGHT,                4,               NULL,            S_GREENTORCH3,   0,     0     }, // S_GREENTORCH2
    { SPR_TGRN, SPR_TGRN,  2 | FF_FULLBRIGHT,                4,               NULL,            S_GREENTORCH4,   0,     0     }, // S_GREENTORCH3
    { SPR_TGRN, SPR_TGRN,  3 | FF_FULLBRIGHT,                4,               NULL,            S_GREENTORCH,    0,     0     }, // S_GREENTORCH4

    // Tall red firestick (MT_MISC43)
    { SPR_TRED, SPR_TRED,  0 | FF_FULLBRIGHT,                4,               NULL,            S_REDTORCH2,     0,     0     }, // S_REDTORCH
    { SPR_TRED, SPR_TRED,  1 | FF_FULLBRIGHT,                4,               NULL,            S_REDTORCH3,     0,     0     }, // S_REDTORCH2
    { SPR_TRED, SPR_TRED,  2 | FF_FULLBRIGHT,                4,               NULL,            S_REDTORCH4,     0,     0     }, // S_REDTORCH3
    { SPR_TRED, SPR_TRED,  3 | FF_FULLBRIGHT,                4,               NULL,            S_REDTORCH,      0,     0     }, // S_REDTORCH4

    // Short blue firestick (MT_MISC44)
    { SPR_SMBT, SPR_SMBT,  0 | FF_FULLBRIGHT,                4,               NULL,            S_BTORCHSHRT2,   0,     0     }, // S_BTORCHSHRT
    { SPR_SMBT, SPR_SMBT,  1 | FF_FULLBRIGHT,                4,               NULL,            S_BTORCHSHRT3,   0,     0     }, // S_BTORCHSHRT2
    { SPR_SMBT, SPR_SMBT,  2 | FF_FULLBRIGHT,                4,               NULL,            S_BTORCHSHRT4,   0,     0     }, // S_BTORCHSHRT3
    { SPR_SMBT, SPR_SMBT,  3 | FF_FULLBRIGHT,                4,               NULL,            S_BTORCHSHRT,    0,     0     }, // S_BTORCHSHRT4

    // Short green firestick (MT_MISC45)
    { SPR_SMGT, SPR_SMGT,  0 | FF_FULLBRIGHT,                4,               NULL,            S_GTORCHSHRT2,   0,     0     }, // S_GTORCHSHRT
    { SPR_SMGT, SPR_SMGT,  1 | FF_FULLBRIGHT,                4,               NULL,            S_GTORCHSHRT3,   0,     0     }, // S_GTORCHSHRT2
    { SPR_SMGT, SPR_SMGT,  2 | FF_FULLBRIGHT,                4,               NULL,            S_GTORCHSHRT4,   0,     0     }, // S_GTORCHSHRT3
    { SPR_SMGT, SPR_SMGT,  3 | FF_FULLBRIGHT,                4,               NULL,            S_GTORCHSHRT,    0,     0     }, // S_GTORCHSHRT4

    // Short red firestick (MT_MISC46)
    { SPR_SMRT, SPR_SMRT,  0 | FF_FULLBRIGHT,                4,               NULL,            S_RTORCHSHRT2,   0,     0     }, // S_RTORCHSHRT
    { SPR_SMRT, SPR_SMRT,  1 | FF_FULLBRIGHT,                4,               NULL,            S_RTORCHSHRT3,   0,     0     }, // S_RTORCHSHRT2
    { SPR_SMRT, SPR_SMRT,  2 | FF_FULLBRIGHT,                4,               NULL,            S_RTORCHSHRT4,   0,     0     }, // S_RTORCHSHRT3
    { SPR_SMRT, SPR_SMRT,  3 | FF_FULLBRIGHT,                4,               NULL,            S_RTORCHSHRT,    0,     0     }, // S_RTORCHSHRT4

    // Hanging victim, guts removed (MT_MISC78)
    { SPR_HDB1, SPR_HDB1,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_HANGNOGUTS

    // Hanging victim, guts and brain removed (MT_MISC79)
    { SPR_HDB2, SPR_HDB2,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_HANGBNOBRAIN

    // Hanging torso, looking down (MT_MISC80)
    { SPR_HDB3, SPR_HDB3,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_HANGTLOOKDN

    // Hanging torso, open skull (MT_MISC81)
    { SPR_HDB4, SPR_HDB4,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_HANGTSKULL

    // Hanging torso, looking up (MT_MISC82)
    { SPR_HDB5, SPR_HDB5,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_HANGTLOOKUP

    // Hanging torso, brain removed (MT_MISC83)
    { SPR_HDB6, SPR_HDB6,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_HANGTNOBRAIN

    // Pool of blood (MT_MISC84)
    { SPR_POB1, SPR_POB1,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_COLONGIBS

    // Pool of blood (MT_MISC85)
    { SPR_POB2, SPR_POB2,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_SMALLPOOL

    // Pool of brains (MT_MISC86)
    { SPR_BRS1, SPR_BRS1,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_BRAINSTEM

    // Tall techno floor lamp (MT_MISC29)
    { SPR_TLMP, SPR_TLMP,  0 | FF_FULLBRIGHT,                4,               NULL,            S_TECHLAMP2 ,    0,     0     }, // S_TECHLAMP
    { SPR_TLMP, SPR_TLMP,  1 | FF_FULLBRIGHT,                4,               NULL,            S_TECHLAMP3 ,    0,     0     }, // S_TECHLAMP2
    { SPR_TLMP, SPR_TLMP,  2 | FF_FULLBRIGHT,                4,               NULL,            S_TECHLAMP4,     0,     0     }, // S_TECHLAMP3
    { SPR_TLMP, SPR_TLMP,  3 | FF_FULLBRIGHT,                4,               NULL,            S_TECHLAMP,      0,     0     }, // S_TECHLAMP4

    // Short techno floor lamp (MT_MISC30)
    { SPR_TLP2, SPR_TLP2,  0 | FF_FULLBRIGHT,                4,               NULL,            S_TECH2LAMP2,    0,     0     }, // S_TECH2LAMP
    { SPR_TLP2, SPR_TLP2,  1 | FF_FULLBRIGHT,                4,               NULL,            S_TECH2LAMP3,    0,     0     }, // S_TECH2LAMP2
    { SPR_TLP2, SPR_TLP2,  2 | FF_FULLBRIGHT,                4,               NULL,            S_TECH2LAMP4,    0,     0     }, // S_TECH2LAMP3
    { SPR_TLP2, SPR_TLP2,  3 | FF_FULLBRIGHT,                4,               NULL,            S_TECH2LAMP,     0,     0     }, // S_TECH2LAMP4

    // Barrel (MT_BARREL)
    { SPR_BEXP, SPR_BEXP,  0,                                6,               NULL,            S_BAR2,          0,     0     }, // S_BAR1

    // Blood Splat (MT_BLOODSPLAT)
    { SPR_BLD2, SPR_BLD2,  0,                               -1,               NULL,            S_NULL,          0,     0     }, // S_BLOODSPLAT
    { SPR_BLD2, SPR_BLD2,  1,                               -1,               NULL,            S_NULL,          0,     0     }, // S_BLOODSPLAT2
    { SPR_BLD2, SPR_BLD2,  2,                               -1,               NULL,            S_NULL,          0,     0     }, // S_BLOODSPLAT3
    { SPR_BLD2, SPR_BLD2,  3,                               -1,               NULL,            S_NULL,          0,     0     }, // S_BLOODSPLAT4
    { SPR_BLD2, SPR_BLD2,  4,                               -1,               NULL,            S_NULL,          0,     0     }, // S_BLOODSPLAT5
    { SPR_BLD2, SPR_BLD2,  5,                               -1,               NULL,            S_NULL,          0,     0     }, // S_BLOODSPLAT6
    { SPR_BLD2, SPR_BLD2,  6,                               -1,               NULL,            S_NULL,          0,     0     }, // S_BLOODSPLAT7
    { SPR_BLD2, SPR_BLD2,  7,                               -1,               NULL,            S_NULL,          0,     0     }, // S_BLOODSPLAT8

    // Smoke Trail (MT_TRAIL)
    { SPR_PUFF, SPR_PUFF,  0 | FF_FULLBRIGHT,                4,               NULL,            S_TRAIL2,        0,     0     }, // S_TRAIL
    { SPR_PUFF, SPR_PUFF,  1,                                4,               NULL,            S_TRAIL3,        0,     0     }, // S_TRAIL2
    { SPR_PUFF, SPR_PUFF,  2,                                8,               NULL,            S_TRAIL4,        0,     0     }, // S_TRAIL3
    { SPR_PUFF, SPR_PUFF,  3,                               12,               NULL,            S_NULL,          0,     0     }  // S_TRAIL4
};

mobjinfo_t mobjinfo[NUMMOBJTYPES] =
{
    // Player (MT_PLAYER)
    {
        /* doomednum            */ -1,
        /* description          */ "you",
        /* spawnstate           */ S_PLAY,
        /* spawnhealth          */ 100,
        /* seestate             */ S_PLAY_RUN1,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 0,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_PLAY_PAIN,
        /* painchance           */ 255,
        /* painsound            */ sfx_plpain,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_PLAY_ATK1,
        /* deathstate           */ S_PLAY_DIE1,
        /* xdeathstate          */ S_PLAY_XDIE1,
        /* deathsound           */ sfx_pldeth,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 56 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 200,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID | MF_SHOOTABLE | MF_DROPOFF | MF_PICKUP | MF_NOTDMATCH,
        /* flags2               */ MF2_PASSMOBJ,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Zombieman (MT_POSSESSED)
    {
        /* doomednum            */ Zombieman,
        /* description          */ "a Zombieman",
        /* spawnstate           */ S_POSS_STND,
        /* spawnhealth          */ 20,
        /* seestate             */ S_POSS_RUN1,
        /* seesound             */ sfx_posit1,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_pistol,
        /* painstate            */ S_POSS_PAIN,
        /* painchance           */ 200,
        /* painsound            */ sfx_popain,
        /* meleestate           */ 0,
        /* missilestate         */ S_POSS_ATK1,
        /* deathstate           */ S_POSS_DIE1,
        /* xdeathstate          */ S_POSS_XDIE1,
        /* deathsound           */ sfx_podth1,
        /* speed                */ 8,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 56 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 200,
        /* damage               */ 0,
        /* activesound          */ sfx_posact,
        /* flags                */ MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL,
        /* flags2               */ MF2_SHADOW,
        /* raisestate           */ S_POSS_RAISE1,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Shotgun Guy (MT_SHOTGUY)
    {
        /* doomednum            */ ShotgunGuy,
        /* description          */ "a Shotgun Guy",
        /* spawnstate           */ S_SPOS_STND,
        /* spawnhealth          */ 30,
        /* seestate             */ S_SPOS_RUN1,
        /* seesound             */ sfx_posit2,
        /* reactiontime         */ 8,
        /* attacksound          */ 0,
        /* painstate            */ S_SPOS_PAIN,
        /* painchance           */ 170,
        /* painsound            */ sfx_popain,
        /* meleestate           */ 0,
        /* missilestate         */ S_SPOS_ATK1,
        /* deathstate           */ S_SPOS_DIE1,
        /* xdeathstate          */ S_SPOS_XDIE1,
        /* deathsound           */ sfx_podth2,
        /* speed                */ 8,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 56 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 200,
        /* damage               */ 0,
        /* activesound          */ sfx_posact,
        /* flags                */ MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL,
        /* flags2               */ MF2_SHADOW,
        /* raisestate           */ S_SPOS_RAISE1,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Arch-vile (MT_VILE)
    {
        /* doomednum            */ ArchVile,
        /* description          */ "an Arch-vile",
        /* spawnstate           */ S_VILE_STND,
        /* spawnhealth          */ 700,
        /* seestate             */ S_VILE_RUN1,
        /* seesound             */ sfx_vilsit,
        /* reactiontime         */ 8,
        /* attacksound          */ 0,
        /* painstate            */ S_VILE_PAIN,
        /* painchance           */ 10,
        /* painsound            */ sfx_vipain,
        /* meleestate           */ 0,
        /* missilestate         */ S_VILE_ATK1,
        /* deathstate           */ S_VILE_DIE1,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_vildth,
        /* speed                */ 15,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 56 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 500,
        /* damage               */ 0,
        /* activesound          */ sfx_vilact,
        /* flags                */ MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL,
        /* flags2               */ MF2_SHADOW,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Arch-vile Fire (MT_FIRE)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_FIRE1,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_NOBLOCKMAP | MF_NOGRAVITY,
        /* flags2               */ MF2_TRANSLUCENT,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Revenant (MT_UNDEAD)
    {
        /* doomednum            */ Revenant,
        /* description          */ "a Revenant",
        /* spawnstate           */ S_SKEL_STND,
        /* spawnhealth          */ 300,
        /* seestate             */ S_SKEL_RUN1,
        /* seesound             */ sfx_skesit,
        /* reactiontime         */ 8,
        /* attacksound          */ 0,
        /* painstate            */ S_SKEL_PAIN,
        /* painchance           */ 100,
        /* painsound            */ sfx_popain,
        /* meleestate           */ S_SKEL_FIST1,
        /* missilestate         */ S_SKEL_MISS1,
        /* deathstate           */ S_SKEL_DIE1,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_skedth,
        /* speed                */ 10,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 56 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 500,
        /* damage               */ 0,
        /* activesound          */ sfx_skeact,
        /* flags                */ MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL,
        /* flags2               */ MF2_SHADOW,
        /* raisestate           */ S_SKEL_RAISE1,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Revenant Projectile (MT_TRACER)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_TRACER,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_skeatk,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_TRACEEXP1,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_barexp,
        /* speed                */ 10 * FRACUNIT,
        /* radius               */ 11 * FRACUNIT,
        /* height               */ 8 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 10,
        /* activesound          */ sfx_None,
        /* flags                */ MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY,
        /* flags2               */ MF2_TRANSLUCENT,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Smoke (MT_SMOKE)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_SMOKE1,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_NOBLOCKMAP | MF_NOGRAVITY,
        /* flags2               */ MF2_TRANSLUCENT,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Mancubus (MT_FATSO)
    {
        /* doomednum            */ Mancubus,
        /* description          */ "a Mancubus",
        /* spawnstate           */ S_FATT_STND,
        /* spawnhealth          */ 600,
        /* seestate             */ S_FATT_RUN1,
        /* seesound             */ sfx_mansit,
        /* reactiontime         */ 8,
        /* attacksound          */ 0,
        /* painstate            */ S_FATT_PAIN,
        /* painchance           */ 80,
        /* painsound            */ sfx_mnpain,
        /* meleestate           */ 0,
        /* missilestate         */ S_FATT_ATK1,
        /* deathstate           */ S_FATT_DIE1,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_mandth,
        /* speed                */ 8,
        /* radius               */ 48 * FRACUNIT,
        /* height               */ 64 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 1000,
        /* damage               */ 0,
        /* activesound          */ sfx_posact,
        /* flags                */ MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL,
        /* flags2               */ MF2_SHADOW,
        /* raisestate           */ S_FATT_RAISE1,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Mancubus Projectile (MT_FATSHOT)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_FATSHOT1,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_firsht,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_FATSHOTX1,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_firxpl,
        /* speed                */ 20 * FRACUNIT,
        /* radius               */ 6 * FRACUNIT,
        /* height               */ 8 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 8,
        /* activesound          */ sfx_None,
        /* flags                */ MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY,
        /* flags2               */ MF2_TRANSLUCENT,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Heavy Weapon Dude (MT_CHAINGUY)
    {
        /* doomednum            */ HeavyWeaponDude,
        /* description          */ "a Heavy Weapon Dude",
        /* spawnstate           */ S_CPOS_STND,
        /* spawnhealth          */ 70,
        /* seestate             */ S_CPOS_RUN1,
        /* seesound             */ sfx_posit2,
        /* reactiontime         */ 8,
        /* attacksound          */ 0,
        /* painstate            */ S_CPOS_PAIN,
        /* painchance           */ 170,
        /* painsound            */ sfx_popain,
        /* meleestate           */ 0,
        /* missilestate         */ S_CPOS_ATK1,
        /* deathstate           */ S_CPOS_DIE1,
        /* xdeathstate          */ S_CPOS_XDIE1,
        /* deathsound           */ sfx_podth2,
        /* speed                */ 8,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 56 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 200,
        /* damage               */ 0,
        /* activesound          */ sfx_posact,
        /* flags                */ MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL,
        /* flags2               */ MF2_SHADOW,
        /* raisestate           */ S_CPOS_RAISE1,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Imp (MT_TROOP)
    {
        /* doomednum            */ Imp,
        /* description          */ "an Imp",
        /* spawnstate           */ S_TROO_STND,
        /* spawnhealth          */ 60,
        /* seestate             */ S_TROO_RUN1,
        /* seesound             */ sfx_bgsit1,
        /* reactiontime         */ 8,
        /* attacksound          */ 0,
        /* painstate            */ S_TROO_PAIN,
        /* painchance           */ 200,
        /* painsound            */ sfx_popain,
        /* meleestate           */ S_TROO_ATK1,
        /* missilestate         */ S_TROO_ATK1,
        /* deathstate           */ S_TROO_DIE1,
        /* xdeathstate          */ S_TROO_XDIE1,
        /* deathsound           */ sfx_bgdth1,
        /* speed                */ 8,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 56 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 200,
        /* damage               */ 0,
        /* activesound          */ sfx_bgact,
        /* flags                */ MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL,
        /* flags2               */ MF2_SHADOW,
        /* raisestate           */ S_TROO_RAISE1,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Demon (MT_SERGEANT)
    {
        /* doomednum            */ Demon,
        /* description          */ "a Demon",
        /* spawnstate           */ S_SARG_STND,
        /* spawnhealth          */ 150,
        /* seestate             */ S_SARG_RUN1,
        /* seesound             */ sfx_sgtsit,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_sgtatk,
        /* painstate            */ S_SARG_PAIN,
        /* painchance           */ 180,
        /* painsound            */ sfx_dmpain,
        /* meleestate           */ S_SARG_ATK1,
        /* missilestate         */ 0,
        /* deathstate           */ S_SARG_DIE1,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_sgtdth,
        /* speed                */ 10,
        /* radius               */ 30 * FRACUNIT,
        /* height               */ 56 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 400,
        /* damage               */ 0,
        /* activesound          */ sfx_dmact,
        /* flags                */ MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL,
        /* flags2               */ MF2_SHADOW,
        /* raisestate           */ S_SARG_RAISE1,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Spectre (MT_SHADOWS)
    {
        /* doomednum            */ Spectre,
        /* description          */ "a Spectre",
        /* spawnstate           */ S_SARG_STND,
        /* spawnhealth          */ 150,
        /* seestate             */ S_SARG_RUN1,
        /* seesound             */ sfx_sgtsit,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_sgtatk,
        /* painstate            */ S_SARG_PAIN,
        /* painchance           */ 180,
        /* painsound            */ sfx_dmpain,
        /* meleestate           */ S_SARG_ATK1,
        /* missilestate         */ 0,
        /* deathstate           */ S_SARG_DIE1,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_sgtdth,
        /* speed                */ 10,
        /* radius               */ 30 * FRACUNIT,
        /* height               */ 56 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 400,
        /* damage               */ 0,
        /* activesound          */ sfx_dmact,
        /* flags                */ MF_SOLID | MF_SHOOTABLE | MF_SHADOW | MF_COUNTKILL,
        /* flags2               */ MF2_SHADOW,
        /* raisestate           */ S_SARG_RAISE1,
        /* frames               */ 0,
        /* blood                */ MT_FUZZYBLOOD
    },

    // Cacodemon (MT_HEAD)
    {
        /* doomednum            */ Cacodemon,
        /* description          */ "a Cacodemon",
        /* spawnstate           */ S_HEAD_STND,
        /* spawnhealth          */ 400,
        /* seestate             */ S_HEAD_RUN1,
        /* seesound             */ sfx_cacsit,
        /* reactiontime         */ 8,
        /* attacksound          */ 0,
        /* painstate            */ S_HEAD_PAIN,
        /* painchance           */ 128,
        /* painsound            */ sfx_dmpain,
        /* meleestate           */ 0,
        /* missilestate         */ S_HEAD_ATK1,
        /* deathstate           */ S_HEAD_DIE1,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_cacdth,
        /* speed                */ 8,
        /* radius               */ 31 * FRACUNIT,
        /* height               */ 56 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 400,
        /* damage               */ 0,
        /* activesound          */ sfx_dmact,
        /* flags                */ MF_SOLID | MF_SHOOTABLE | MF_FLOAT | MF_NOGRAVITY | MF_COUNTKILL,
        /* flags2               */ MF2_PASSMOBJ | MF2_SHADOW,
        /* raisestate           */ S_HEAD_RAISE1,
        /* frames               */ 0,
        /* blood                */ MT_BLUEBLOOD
    },

    // Baron of Hell (MT_BRUISER)
    {
        /* doomednum            */ BaronOfHell,
        /* description          */ "a Baron of Hell",
        /* spawnstate           */ S_BOSS_STND,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_BOSS_RUN1,
        /* seesound             */ sfx_brssit,
        /* reactiontime         */ 8,
        /* attacksound          */ 0,
        /* painstate            */ S_BOSS_PAIN,
        /* painchance           */ 50,
        /* painsound            */ sfx_dmpain,
        /* meleestate           */ S_BOSS_ATK1,
        /* missilestate         */ S_BOSS_ATK1,
        /* deathstate           */ S_BOSS_DIE1,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_brsdth,
        /* speed                */ 8,
        /* radius               */ 24 * FRACUNIT,
        /* height               */ 64 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 1000,
        /* damage               */ 0,
        /* activesound          */ sfx_dmact,
        /* flags                */ MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL,
        /* flags2               */ MF2_SHADOW,
        /* raisestate           */ S_BOSS_RAISE1,
        /* frames               */ 0,
        /* blood                */ MT_GREENBLOOD
    },

    // Baron of Hell and Hell Knight Projectile (MT_BRUISERSHOT)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_BRBALL1,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_firsht,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_BRBALLX1,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_firxpl,
        /* speed                */ 15 * FRACUNIT,
        /* radius               */ 6 * FRACUNIT,
        /* height               */ 8 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 8,
        /* activesound          */ sfx_None,
        /* flags                */ MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY,
        /* flags2               */ MF2_TRANSLUCENT,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Hell Knight (MT_KNIGHT)
    {
        /* doomednum            */ HellKnight,
        /* description          */ "a Hell Knight",
        /* spawnstate           */ S_BOS2_STND,
        /* spawnhealth          */ 500,
        /* seestate             */ S_BOS2_RUN1,
        /* seesound             */ sfx_kntsit,
        /* reactiontime         */ 8,
        /* attacksound          */ 0,
        /* painstate            */ S_BOS2_PAIN,
        /* painchance           */ 50,
        /* painsound            */ sfx_dmpain,
        /* meleestate           */ S_BOS2_ATK1,
        /* missilestate         */ S_BOS2_ATK1,
        /* deathstate           */ S_BOS2_DIE1,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_kntdth,
        /* speed                */ 8,
        /* radius               */ 24 * FRACUNIT,
        /* height               */ 64 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 1000,
        /* damage               */ 0,
        /* activesound          */ sfx_dmact,
        /* flags                */ MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL,
        /* flags2               */ MF2_SHADOW,
        /* raisestate           */ S_BOS2_RAISE1,
        /* frames               */ 0,
        /* blood                */ MT_GREENBLOOD
    },

    // Lost Soul (MT_SKULL)
    {
        /* doomednum            */ LostSoul,
        /* description          */ "a Lost Soul",
        /* spawnstate           */ S_SKULL_STND,
        /* spawnhealth          */ 100,
        /* seestate             */ S_SKULL_RUN1,
        /* seesound             */ 0,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_sklatk,
        /* painstate            */ S_SKULL_PAIN,
        /* painchance           */ 256,
        /* painsound            */ sfx_dmpain,
        /* meleestate           */ 0,
        /* missilestate         */ S_SKULL_ATK1,
        /* deathstate           */ S_SKULL_DIE1,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_firxpl,
        /* speed                */ 8,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 56 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 50,
        /* damage               */ 3,
        /* activesound          */ sfx_dmact,
        /* flags                */ MF_SOLID | MF_SHOOTABLE | MF_FLOAT | MF_NOGRAVITY | MF_COUNTKILL,
        /* flags2               */ MF2_PASSMOBJ | MF2_SHADOW | MF2_TRANSLUCENT_REDONLY,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Spider Mastermind (MT_SPIDER)
    {
        /* doomednum            */ SpiderMastermind,
        /* description          */ "a Spider Mastermind",
        /* spawnstate           */ S_SPID_STND,
        /* spawnhealth          */ 3000,
        /* seestate             */ S_SPID_RUN1,
        /* seesound             */ sfx_spisit,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_shotgn,
        /* painstate            */ S_SPID_PAIN,
        /* painchance           */ 40,
        /* painsound            */ sfx_dmpain,
        /* meleestate           */ 0,
        /* missilestate         */ S_SPID_ATK1,
        /* deathstate           */ S_SPID_DIE1,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_spidth,
        /* speed                */ 12,
        /* radius               */ 128 * FRACUNIT,
        /* height               */ 100 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 1000,
        /* damage               */ 0,
        /* activesound          */ sfx_dmact,
        /* flags                */ MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Arachnotron (MT_BABY)
    {
        /* doomednum            */ Arachnotron,
        /* description          */ "an Arachnotron",
        /* spawnstate           */ S_BSPI_STND,
        /* spawnhealth          */ 500,
        /* seestate             */ S_BSPI_SIGHT,
        /* seesound             */ sfx_bspsit,
        /* reactiontime         */ 8,
        /* attacksound          */ 0,
        /* painstate            */ S_BSPI_PAIN,
        /* painchance           */ 128,
        /* painsound            */ sfx_dmpain,
        /* meleestate           */ 0,
        /* missilestate         */ S_BSPI_ATK1,
        /* deathstate           */ S_BSPI_DIE1,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_bspdth,
        /* speed                */ 12,
        /* radius               */ 64 * FRACUNIT,
        /* height               */ 64 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 600,
        /* damage               */ 0,
        /* activesound          */ sfx_bspact,
        /* flags                */ MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL,
        /* flags2               */ MF2_SHADOW,
        /* raisestate           */ S_BSPI_RAISE1,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Cyberdemon (MT_CYBORG)
    {
        /* doomednum            */ Cyberdemon,
        /* description          */ "a Cyberdemon",
        /* spawnstate           */ S_CYBER_STND,
        /* spawnhealth          */ 4000,
        /* seestate             */ S_CYBER_RUN1,
        /* seesound             */ sfx_cybsit,
        /* reactiontime         */ 8,
        /* attacksound          */ 0,
        /* painstate            */ S_CYBER_PAIN,
        /* painchance           */ 20,
        /* painsound            */ sfx_dmpain,
        /* meleestate           */ 0,
        /* missilestate         */ S_CYBER_ATK1,
        /* deathstate           */ S_CYBER_DIE1,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_cybdth,
        /* speed                */ 16,
        /* radius               */ 40 * FRACUNIT,
        /* height               */ 110 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 1000,
        /* damage               */ 0,
        /* activesound          */ sfx_dmact,
        /* flags                */ MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Pain Elemental (MT_PAIN)
    {
        /* doomednum            */ PainElemental,
        /* description          */ "a Pain Elemental",
        /* spawnstate           */ S_PAIN_STND,
        /* spawnhealth          */ 400,
        /* seestate             */ S_PAIN_RUN1,
        /* seesound             */ sfx_pesit,
        /* reactiontime         */ 8,
        /* attacksound          */ 0,
        /* painstate            */ S_PAIN_PAIN,
        /* painchance           */ 128,
        /* painsound            */ sfx_pepain,
        /* meleestate           */ 0,
        /* missilestate         */ S_PAIN_ATK1,
        /* deathstate           */ S_PAIN_DIE1,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_pedth,
        /* speed                */ 8,
        /* radius               */ 31 * FRACUNIT,
        /* height               */ 56 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 400,
        /* damage               */ 0,
        /* activesound          */ sfx_dmact,
        /* flags                */ MF_SOLID | MF_SHOOTABLE | MF_FLOAT | MF_NOGRAVITY | MF_COUNTKILL,
        /* flags2               */ MF2_SHADOW,
        /* raisestate           */ S_PAIN_RAISE1,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Wolfenstein SS (MT_WOLFSS)
    {
        /* doomednum            */ WolfensteinSS,
        /* description          */ "a Wolfenstein SS",
        /* spawnstate           */ S_SSWV_STND,
        /* spawnhealth          */ 50,
        /* seestate             */ S_SSWV_RUN1,
        /* seesound             */ sfx_sssit,
        /* reactiontime         */ 8,
        /* attacksound          */ 0,
        /* painstate            */ S_SSWV_PAIN,
        /* painchance           */ 170,
        /* painsound            */ sfx_popain,
        /* meleestate           */ 0,
        /* missilestate         */ S_SSWV_ATK1,
        /* deathstate           */ S_SSWV_DIE1,
        /* xdeathstate          */ S_SSWV_XDIE1,
        /* deathsound           */ sfx_ssdth,
        /* speed                */ 8,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 56 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_posact,
        /* flags                */ MF_SOLID | MF_SHOOTABLE | MF_COUNTKILL,
        /* flags2               */ 0,
        /* raisestate           */ S_SSWV_RAISE1,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Commander Keen (MT_KEEN)
    {
        /* doomednum            */ CommanderKeen,
        /* description          */ "Commander Keen",
        /* spawnstate           */ S_KEENSTND,
        /* spawnhealth          */ 100,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_KEENPAIN,
        /* painchance           */ 256,
        /* painsound            */ sfx_keenpn,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_COMMKEEN,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_keendt,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 67 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 10000000,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY | MF_SHOOTABLE | MF_COUNTKILL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Boss Brain (MT_BOSSBRAIN)
    {
        /* doomednum            */ BossBrain,
        /* description          */ "",
        /* spawnstate           */ S_BRAIN,
        /* spawnhealth          */ 250,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_BRAIN_PAIN,
        /* painchance           */ 255,
        /* painsound            */ sfx_bospn,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_BRAIN_DIE1,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_bosdth,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 10000000,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID | MF_SHOOTABLE,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Monsters Spawner (MT_BOSSSPIT)
    {
        /* doomednum            */ MonstersSpawner,
        /* description          */ "",
        /* spawnstate           */ S_BRAINEYE,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_BRAINEYESEE,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 32 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_NOBLOCKMAP | MF_NOSECTOR,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Monsters Target (MT_BOSSTARGET)
    {
        /* doomednum            */ MonstersTarget,
        /* description          */ "",
        /* spawnstate           */ S_NULL,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 32 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_NOBLOCKMAP | MF_NOSECTOR,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Boss Brain Projectile (MT_SPAWNSHOT)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_SPAWN1,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_bospit,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_firxpl,
        /* speed                */ 10 * FRACUNIT,
        /* radius               */ 6 * FRACUNIT,
        /* height               */ 32 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 3,
        /* activesound          */ sfx_None,
        /* flags                */ MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY | MF_NOCLIP,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Boss Brain Teleport Fog (MT_SPAWNFIRE)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_SPAWNFIRE1,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_NOBLOCKMAP | MF_NOGRAVITY,
        /* flags2               */ MF2_TRANSLUCENT,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Barrel (MT_BARREL)
    {
        /* doomednum            */ Barrel,
        /* description          */ "a barrel",
        /* spawnstate           */ S_BAR1,
        /* spawnhealth          */ 20,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_BEXP,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_barexp,
        /* speed                */ 0,
        /* radius               */ 10 * FRACUNIT,
        /* height               */ 42 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID | MF_SHOOTABLE | MF_NOBLOOD,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 3,
        /* blood                */ 0
    },

    // Imp Projectile (MT_TROOPSHOT)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_TBALL1,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_firsht,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_TBALLX1,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_firxpl,
        /* speed                */ 10 * FRACUNIT,
        /* radius               */ 6 * FRACUNIT,
        /* height               */ 8 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 3,
        /* activesound          */ sfx_None,
        /* flags                */ MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY,
        /* flags2               */ MF2_TRANSLUCENT,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Cacodemon Projectile (MT_HEADSHOT)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_RBALL1,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_firsht,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_RBALLX1,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_firxpl,
        /* speed                */ 10 * FRACUNIT,
        /* radius               */ 6 * FRACUNIT,
        /* height               */ 8 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 5,
        /* activesound          */ sfx_None,
        /* flags                */ MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY,
        /* flags2               */ MF2_TRANSLUCENT,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Rocket Launcher Projectile (MT_ROCKET)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_ROCKET,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_rlaunc,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_EXPLODE1,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_barexp,
        /* speed                */ 20 * FRACUNIT,
        /* radius               */ 11 * FRACUNIT,
        /* height               */ 8 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 20,
        /* activesound          */ sfx_None,
        /* flags                */ MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Plasma Rifle Projectile (MT_PLASMA)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_PLASBALL,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_plasma,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_PLASEXP,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_firxpl,
        /* speed                */ 25 * FRACUNIT,
        /* radius               */ 13 * FRACUNIT,
        /* height               */ 8 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 5,
        /* activesound          */ sfx_None,
        /* flags                */ MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY,
        /* flags2               */ MF2_TRANSLUCENT,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // BFG 9000 Projectile (MT_BFG)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_BFGSHOT,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ 0,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_BFGLAND,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_rxplod,
        /* speed                */ 25 * FRACUNIT,
        /* radius               */ 13 * FRACUNIT,
        /* height               */ 8 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 100,
        /* activesound          */ sfx_None,
        /* flags                */ MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY,
        /* flags2               */ MF2_TRANSLUCENT,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Arachnotron Projectile (MT_ARACHPLAZ)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_ARACH_PLAZ,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_plasma,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_ARACH_PLEX,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_firxpl,
        /* speed                */ 25 * FRACUNIT,
        /* radius               */ 13 * FRACUNIT,
        /* height               */ 8 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 5,
        /* activesound          */ sfx_None,
        /* flags                */ MF_NOBLOCKMAP | MF_MISSILE | MF_DROPOFF | MF_NOGRAVITY,
        /* flags2               */ MF2_TRANSLUCENT,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Bullet Puff (MT_PUFF)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_PUFF1,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_NOBLOCKMAP | MF_NOGRAVITY,
        /* flags2               */ MF2_TRANSLUCENT,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Blood (MT_BLOOD)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_BLOOD1,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 0 * FRACUNIT,
        /* height               */ 0 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ 0,
        /* flags2               */ MF2_BLOOD | MF2_TRANSLUCENT_50,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ REDBLOOD
    },

    // Teleport Fog (MT_TFOG)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_TFOG,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_NOBLOCKMAP | MF_NOGRAVITY,
        /* flags2               */ MF2_TRANSLUCENT,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Item Fog (MT_IFOG)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_IFOG,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_NOBLOCKMAP | MF_NOGRAVITY,
        /* flags2               */ MF2_TRANSLUCENT,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        
        /* blood                */ 0
    },

    // Teleport Destination (MT_TELEPORTMAN)
    {
        /* doomednum            */ TeleportDestination,
        /* description          */ "",
        /* spawnstate           */ S_NULL,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_NOBLOCKMAP | MF_NOSECTOR,
        /* flags2               */ MF2_TRANSLUCENT,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // BFG 9000 Secondary Projectile (MT_EXTRABFG)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_BFGEXP,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_NOBLOCKMAP | MF_NOGRAVITY,
        /* flags2               */ MF2_TRANSLUCENT,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Green Armor (MT_MISC0)
    {
        /* doomednum            */ GreenArmor,
        /* description          */ "some green armor",
        /* spawnstate           */ S_ARM1,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 15 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 2,
        /* blood                */ 0
    },

    // Blue Armor (MT_MISC1)
    {
        /* doomednum            */ BlueArmor,
        /* description          */ "some blue armor",
        /* spawnstate           */ S_ARM2,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 15 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 2,
        /* blood                */ 0
    },

    // Health Bonus (MT_MISC2)
    {
        /* doomednum            */ HealthBonus,
        /* description          */ "a health bonus",
        /* spawnstate           */ S_BON1,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 7 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL | MF_COUNTITEM,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 4,
        /* blood                */ 0
    },

    // Armor Bonus (MT_MISC3)
    {
        /* doomednum            */ ArmorBonus,
        /* description          */ "an armor bonus",
        /* spawnstate           */ S_BON2,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 8 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL | MF_COUNTITEM,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 4,
        /* blood                */ 0
    },

    // Blue Keycard (MT_MISC4)
    {
        /* doomednum            */ BlueKeycard,
        /* description          */ "a blue keycard",
        /* spawnstate           */ S_BKEY,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 7 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL | MF_NOTDMATCH,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 2,
        /* blood                */ 0
    },

    // Red Keycard (MT_MISC5)
    {
        /* doomednum            */ RedKeycard,
        /* description          */ "a red keycard",
        /* spawnstate           */ S_RKEY,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 7 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL | MF_NOTDMATCH,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 2,
        /* blood                */ 0
    },

    // Yellow Keycard (MT_MISC6)
    {
        /* doomednum            */ YellowKeycard,
        /* description          */ "a yellow keycard",
        /* spawnstate           */ S_YKEY,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 7 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL | MF_NOTDMATCH,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 2,
        /* blood                */ 0
    },

    // Yellow Skull Key (MT_MISC7)
    {
        /* doomednum            */ YellowSkullKey,
        /* description          */ "a yellow skull key",
        /* spawnstate           */ S_YSKULL,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 6 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* mass                 */ 100,
        /* projectilepassheight */ 0,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL | MF_NOTDMATCH,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 2,
        /* blood                */ 0
    },

    // Red Skull Key (MT_MISC8)
    {
        /* doomednum            */ RedSkullKey,
        /* description          */ "a red skull key",
        /* spawnstate           */ S_RSKULL,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 6 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL | MF_NOTDMATCH,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 2,
        /* blood                */ 0
    },

    // Blue Skull Key (MT_MISC9)
    {
        /* doomednum            */ BlueSkullKey,
        /* description          */ "a blue skull key",
        /* spawnstate           */ S_BSKULL,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 6 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL | MF_NOTDMATCH,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 2,
        /* blood                */ 0
    },

    // Stimpack (MT_MISC10)
    {
        /* doomednum            */ Stimpack,
        /* description          */ "a stimpack",
        /* spawnstate           */ S_STIM,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 7 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Medikit (MT_MISC11)
    {
        /* doomednum            */ Medikit,
        /* description          */ "a medikit",
        /* spawnstate           */ S_MEDI,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 14 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // SoulSphere (MT_MISC12)
    {
        /* doomednum            */ SoulSphere,
        /* description          */ "a SoulSphere",
        /* spawnstate           */ S_SOUL,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 12 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL | MF_COUNTITEM,
        /* flags2               */ MF2_TRANSLUCENT_33 | MF2_FLOATBOB,
        /* raisestate           */ S_NULL,
        /* frames               */ 4,
        /* blood                */ 0
    },

    // Invulnerability (MT_INV)
    {
        /* doomednum            */ Invulnerability,
        /* description          */ "an invulnerability power-up",
        /* spawnstate           */ S_PINV,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 12 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL | MF_COUNTITEM,
        /* flags2               */ MF2_TRANSLUCENT_33 | MF2_FLOATBOB,
        /* raisestate           */ S_NULL,
        /* frames               */ 4,
        /* blood                */ 0
    },

    // Berserk (MT_MISC13)
    {
        /* doomednum            */ Berserk,
        /* description          */ "a berserk power-up",
        /* spawnstate           */ S_PSTR,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 14 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL | MF_COUNTITEM,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Partial Invisibility (MT_INS)
    {
        /* doomednum            */ PartialInvisibility,
        /* description          */ "a partial invisibility power-up",
        /* spawnstate           */ S_PINS,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 12 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL | MF_COUNTITEM,
        /* flags2               */ MF2_TRANSLUCENT_33 | MF2_FLOATBOB,
        /* raisestate           */ S_NULL,
        /* frames               */ 4,
        /* blood                */ 0
    },

    // Radiation Shielding Suit (MT_MISC14)
    {
        /* doomednum            */ RadiationShieldingSuit,
        /* description          */ "a radiation shielding suit power-up",
        /* spawnstate           */ S_SUIT,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 12 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL,
        /* flags2               */ MF2_FLOATBOB,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Computer Area Map (MT_MISC15)
    {
        /* doomednum            */ ComputerAreaMap,
        /* description          */ "a computer area map power-up",
        /* spawnstate           */ S_PMAP,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 14 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL | MF_COUNTITEM,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 4,
        /* blood                */ 0
    },

    // Light Amplification Visor (MT_MISC16)
    {
        /* doomednum            */ LightAmplificationVisor,
        /* description          */ "a light amplification visor power-up",
        /* spawnstate           */ S_PVIS,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 14 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL | MF_COUNTITEM,
        /* flags2               */ MF2_TRANSLUCENT_REDONLY,
        /* raisestate           */ S_NULL,
        /* frames               */ 2,
        /* blood                */ 0
    },

    // MegaSphere (MT_MEGA)
    {
        /* doomednum            */ MegaSphere,
        /* description          */ "a MegaSphere",
        /* spawnstate           */ S_MEGA,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 12 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL | MF_COUNTITEM,
        /* flags2               */ MF2_TRANSLUCENT_33 | MF2_FLOATBOB,
        /* raisestate           */ S_NULL,
        /* frames               */ 4,
        /* blood                */ 0
    },

    // Clip (MT_CLIP)
    {
        /* doomednum            */ Clip,
        /* description          */ "a clip",
        /* spawnstate           */ S_CLIP,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 4 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Box of Bullets (MT_MISC17)
    {
        /* doomednum            */ BoxOfBullets,
        /* description          */ "a box of bullets",
        /* spawnstate           */ S_AMMO,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 14 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Rocket (MT_MISC18)
    {
        /* doomednum            */ Rocket,
        /* description          */ "a rocket",
        /* spawnstate           */ S_ROCK,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 6 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Box of Rockets (MT_MISC19)
    {
        /* doomednum            */ BoxOfRockets,
        /* description          */ "a box of rockets",
        /* spawnstate           */ S_BROK,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Cell (MT_MISC20)
    {
        /* doomednum            */ Cell,
        /* description          */ "a cell",
        /* spawnstate           */ S_CELL,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 8 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Cell Pack (MT_MISC21)
    {
        /* doomednum            */ CellPack,
        /* description          */ "a cell pack",
        /* spawnstate           */ S_CELP,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Shotgun Shells (MT_MISC22)
    {
        /* doomednum            */ ShotgunShells,
        /* description          */ "some shotgun shells",
        /* spawnstate           */ S_SHEL,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 7 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Box of Shells (MT_MISC23)
    {
        /* doomednum            */ BoxOfShells,
        /* description          */ "a box of shells",
        /* spawnstate           */ S_SBOX,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Backpack (MT_MISC24)
    {
        /* doomednum            */ Backpack,
        /* description          */ "a backpack",
        /* spawnstate           */ S_BPAK,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 11 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // BFG 9000 (MT_MISC25)
    {
        /* doomednum            */ BFG9000,
        /* description          */ "a BFG 9000",
        /* spawnstate           */ S_BFUG,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Chaingun (MT_CHAINGUN)
    {
        /* doomednum            */ Chaingun,
        /* description          */ "a chaingun",
        /* spawnstate           */ S_MGUN,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Chainsaw (MT_MISC26)
    {
        /* doomednum            */ Chainsaw,
        /* description          */ "a chainsaw",
        /* spawnstate           */ S_CSAW,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Rocket Launcher (MT_MISC27)
    {
        /* doomednum            */ RocketLauncher,
        /* description          */ "a rocket launcher",
        /* spawnstate           */ S_LAUN,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Plasma Rifle (MT_MISC28)
    {
        /* doomednum            */ PlasmaRifle,
        /* description          */ "a plasma rifle",
        /* spawnstate           */ S_PLAS,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Shotgun (MT_SHOTGUN)
    {
        /* doomednum            */ Shotgun,
        /* description          */ "a shotgun",
        /* spawnstate           */ S_SHOT,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Super Shotgun (MT_SUPERSHOTGUN)
    {
        /* doomednum            */ SuperShotgun,
        /* description          */ "a super shotgun",
        /* spawnstate           */ S_SHOT2,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPECIAL,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Tall techno floor lamp (MT_MISC29)
    {
        /* doomednum            */ TallTechnoFloorLamp,
        /* description          */ "",
        /* spawnstate           */ S_TECHLAMP,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 80 * FRACUNIT,
        /* projectilepassheight */ 16 * FRACUNIT,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ MF2_TRANSLUCENT_BLUEONLY,
        /* raisestate           */ S_NULL,
        /* frames               */ 4,
        /* blood                */ 0
    },

    // Short techno floor lamp (MT_MISC30)
    {
        /* doomednum            */ ShortTechnoFloorLamp,
        /* description          */ "",
        /* spawnstate           */ S_TECH2LAMP,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 60 * FRACUNIT,
        /* projectilepassheight */ 16 * FRACUNIT,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ MF2_TRANSLUCENT_BLUEONLY,
        /* raisestate           */ S_NULL,
        /* frames               */ 4,
        /* blood                */ 0
    },

    // Floor lamp (MT_MISC31)
    {
        /* doomednum            */ FloorLamp,
        /* description          */ "",
        /* spawnstate           */ S_COLU,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 48 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ MF2_TRANSLUCENT_REDONLY,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Tall green column (MT_MISC32)
    {
        /* doomednum            */ TallGreenColumn,
        /* description          */ "",
        /* spawnstate           */ S_TALLGRNCOL,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 52 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Short green column (MT_MISC33)
    {
        /* doomednum            */ ShortGreenColumn,
        /* description          */ "",
        /* spawnstate           */ S_SHRTGRNCOL,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 40 * FRACUNIT,
        /* projectilepassheight */ 16 * FRACUNIT,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Tall red column (MT_MISC34)
    {
        /* doomednum            */ TallRedColumn,
        /* description          */ "",
        /* spawnstate           */ S_TALLREDCOL,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 52 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Short red column (MT_MISC35)
    {
        /* doomednum            */ ShortRedColumn,
        /* description          */ "",
        /* spawnstate           */ S_SHRTREDCOL,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 40 * FRACUNIT,
        /* projectilepassheight */ 16 * FRACUNIT,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Short red column with skull (MT_MISC36)
    {
        /* doomednum            */ ShortRedColumnWithSkull,
        /* description          */ "",
        /* spawnstate           */ S_SKULLCOL,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 40 * FRACUNIT,
        /* projectilepassheight */ 16 * FRACUNIT,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Short green column with beating heart (MT_MISC37)
    {
        /* doomednum            */ ShortGreenColumnWithBeatingHeart,
        /* description          */ "",
        /* spawnstate           */ S_HEARTCOL,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 40 * FRACUNIT,
        /* projectilepassheight */ 16 * FRACUNIT,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 2,
        /* blood                */ 0
    },

    // Evil eye (MT_MISC38)
    {
        /* doomednum            */ EvilEye,
        /* description          */ "",
        /* spawnstate           */ S_EVILEYE,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 54 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ MF2_TRANSLUCENT_GREENONLY,
        /* raisestate           */ S_NULL,
        /* frames               */ 3,
        /* blood                */ 0
    },

    // Floating skull (MT_MISC39)
    {
        /* doomednum            */ FloatingSkull,
        /* description          */ "",
        /* spawnstate           */ S_FLOATSKULL,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 26 * FRACUNIT,
        /* projectilepassheight */ 16 * FRACUNIT,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 3,
        /* blood                */ 0
    },

    // Torched tree (MT_MISC40)
    {
        /* doomednum            */ TorchedTree,
        /* description          */ "",
        /* spawnstate           */ S_TORCHTREE,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 56 * FRACUNIT,
        /* projectilepassheight */ 16 * FRACUNIT,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Tall blue firestick (MT_MISC41)
    {
        /* doomednum            */ TallBlueFirestick,
        /* description          */ "",
        /* spawnstate           */ S_BLUETORCH,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 68 * FRACUNIT,
        /* projectilepassheight */ 16 * FRACUNIT,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ MF2_TRANSLUCENT_BLUEONLY,
        /* raisestate           */ S_NULL,
        /* frames               */ 4,
        /* blood                */ 0
    },

    // Tall green firestick (MT_MISC42)
    {
        /* doomednum            */ TallGreenFirestick,
        /* description          */ "",
        /* spawnstate           */ S_GREENTORCH,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 68 * FRACUNIT,
        /* projectilepassheight */ 16 * FRACUNIT,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ MF2_TRANSLUCENT_GREENONLY,
        /* raisestate           */ S_NULL,
        /* frames               */ 4,
        /* blood                */ 0
    },

    // Tall red firestick (MT_MISC43)
    {
        /* doomednum            */ TallRedFirestick,
        /* description          */ "",
        /* spawnstate           */ S_REDTORCH,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 68 * FRACUNIT,
        /* projectilepassheight */ 16 * FRACUNIT,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ MF2_TRANSLUCENT_REDONLY,
        /* raisestate           */ S_NULL,
        /* frames               */ 4,
        /* blood                */ 0
    },

    // Short blue firestick (MT_MISC44)
    {
        /* doomednum            */ ShortBlueFirestick,
        /* description          */ "",
        /* spawnstate           */ S_BTORCHSHRT,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 37 * FRACUNIT,
        /* projectilepassheight */ 16 * FRACUNIT,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ MF2_TRANSLUCENT_BLUEONLY,
        /* raisestate           */ S_NULL,
        /* frames               */ 4,
        /* blood                */ 0
    },

    // Short green firestick (MT_MISC45)
    {
        /* doomednum            */ ShortGreenFirestick,
        /* description          */ "",
        /* spawnstate           */ S_GTORCHSHRT,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 37 * FRACUNIT,
        /* projectilepassheight */ 16 * FRACUNIT,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ MF2_TRANSLUCENT_GREENONLY,
        /* raisestate           */ S_NULL,
        /* frames               */ 4,
        /* blood                */ 0
    },

    // Short red firestick (MT_MISC46)
    {
        /* doomednum            */ ShortRedFirestick,
        /* description          */ "",
        /* spawnstate           */ S_RTORCHSHRT,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 37 * FRACUNIT,
        /* projectilepassheight */ 16 * FRACUNIT,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ MF2_TRANSLUCENT_REDONLY,
        /* raisestate           */ S_NULL,
        /* frames               */ 4,
        /* blood                */ 0
    },

    // Stalagmite (MT_MISC47)
    {
        /* doomednum            */ Stalagmite,
        /* description          */ "",
        /* spawnstate           */ S_STALAGTITE,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 40 * FRACUNIT,
        /* projectilepassheight */ 16 * FRACUNIT,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Tall techno pillar (MT_MISC48)
    {
        /* doomednum            */ TallTechnoPillar,
        /* description          */ "",
        /* spawnstate           */ S_TECHPILLAR,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 128 * FRACUNIT,
        /* projectilepassheight */ 16 * FRACUNIT,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Candlestick (MT_MISC49)
    {
        /* doomednum            */ Candlestick,
        /* description          */ "",
        /* spawnstate           */ S_CANDLESTIK,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 14 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ 0,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Candelabra (MT_MISC50)
    {
        /* doomednum            */ Candelabra,
        /* description          */ "",
        /* spawnstate           */ S_CANDELABRA,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 60 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Hanging victim, twitching, blocking (MT_MISC51)
    {
        /* doomednum            */ HangingVictimTwitchingBlocking,
        /* description          */ "",
        /* spawnstate           */ S_BLOODYTWITCH,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 67 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 3,
        /* blood                */ MT_BLOOD
    },

    // Hanging victim, arms out, blocking (MT_MISC52)
    {
        /* doomednum            */ HangingVictimArmsOutBlocking,
        /* description          */ "",
        /* spawnstate           */ S_MEAT2,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 83 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Hanging victim, one-legged, blocking (MT_MISC53)
    {
        /* doomednum            */ HangingVictimOneLeggedBlocking,
        /* description          */ "",
        /* spawnstate           */ S_MEAT3,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 83 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Hanging pair of legs, blocking (MT_MISC54)
    {
        /* doomednum            */ HangingPairOfLegsBlocking,
        /* description          */ "",
        /* spawnstate           */ S_MEAT4,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 67 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Hanging leg, blocking (MT_MISC55, MT_MISC59)
    {
        /* doomednum            */ HangingLegBlocking,
        /* description          */ "",
        /* spawnstate           */ S_MEAT5,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 51 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Hanging victim, arms out (MT_MISC56)
    {
        /* doomednum            */ HangingVictimArmsOut,
        /* description          */ "",
        /* spawnstate           */ S_MEAT2,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 83 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPAWNCEILING | MF_NOGRAVITY,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Hanging pair of legs (MT_MISC57)
    {
        /* doomednum            */ HangingPairOfLegs,
        /* description          */ "",
        /* spawnstate           */ S_MEAT4,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 67 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPAWNCEILING | MF_NOGRAVITY,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Hanging victim, one-legged (MT_MISC58)
    {
        /* doomednum            */ HangingVictimOneLegged,
        /* description          */ "",
        /* spawnstate           */ S_MEAT3,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 83 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPAWNCEILING | MF_NOGRAVITY,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Hanging leg (MT_MISC59)
    {
        /* doomednum            */ HangingLeg,
        /* description          */ "",
        /* spawnstate           */ S_MEAT5,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 51 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPAWNCEILING | MF_NOGRAVITY,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Hanging victim, twitching (MT_MISC60)
    {
        /* doomednum            */ HangingVictimTwitching,
        /* description          */ "",
        /* spawnstate           */ S_BLOODYTWITCH,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 67 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SPAWNCEILING | MF_NOGRAVITY,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Dead Cacodemon (MT_MISC61)
    {
        /* doomednum            */ DeadCacodemon,
        /* description          */ "",
        /* spawnstate           */ S_HEAD_DIE6,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 400,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_CORPSE,
        /* flags2               */ MF2_SHADOW,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLUEBLOOD
    },

    // Dead Player (MT_MISC62)
    {
        /* doomednum            */ DeadPlayer,
        /* description          */ "",
        /* spawnstate           */ S_PLAY_DIE7,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 200,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_CORPSE,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Dead Zombieman (MT_MISC63)
    {
        /* doomednum            */ DeadZombieman,
        /* description          */ "",
        /* spawnstate           */ S_POSS_DIE5,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 200,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_CORPSE,
        /* flags2               */ MF2_SHADOW,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Dead Demon (MT_MISC64)
    {
        /* doomednum            */ DeadDemon,
        /* description          */ "",
        /* spawnstate           */ S_SARG_DIE6,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 400,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_CORPSE,
        /* flags2               */ MF2_SHADOW,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Dead Lost Soul, invisible (MT_MISC65)
    {
        /* doomednum            */ DeadLostSoulInvisible,
        /* description          */ "",
        /* spawnstate           */ S_SKULL_DIE6,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ 0,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Dead Imp (MT_MISC66)
    {
        /* doomednum            */ DeadImp,
        /* description          */ "",
        /* spawnstate           */ S_TROO_DIE5,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 200,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_CORPSE,
        /* flags2               */ MF2_SHADOW,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Dead Shotgun Guy (MT_MISC67)
    {
        /* doomednum            */ DeadShotgunGuy,
        /* description          */ "",
        /* spawnstate           */ S_SPOS_DIE5,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 200,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_CORPSE,
        /* flags2               */ MF2_SHADOW,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Bloody Mess 1 (MT_MISC68)
    {
        /* doomednum            */ BloodyMess1,
        /* description          */ "",
        /* spawnstate           */ S_PLAY_XDIE9,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 200,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_CORPSE,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Bloody Mess 2 (MT_MISC69)
    {
        /* doomednum            */ BloodyMess2,
        /* description          */ "",
        /* spawnstate           */ S_PLAY_XDIE9,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 200,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_CORPSE,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Skulls on a pole (MT_MISC70, MT_MISC72)
    {
        /* doomednum            */ FiveSkullsShishKebab,
        /* description          */ "",
        /* spawnstate           */ S_HEADSONSTICK,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 64 * FRACUNIT,
        /* projectilepassheight */ 16 * FRACUNIT,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Pool of blood and bones (MT_MISC71)
    {
        /* doomednum            */ PoolOfBloodAndBones,
        /* description          */ "",
        /* spawnstate           */ S_GIBS,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ 0,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Skull on a pole (MT_MISC72)
    {
        /* doomednum            */ SkullOnAPole,
        /* description          */ "",
        /* spawnstate           */ S_HEADONASTICK,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 56 * FRACUNIT,
        /* projectilepassheight */ 16 * FRACUNIT,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Pile of skulls and candles (MT_MISC73)
    {
        /* doomednum            */ PileOfSkullsAndCandles,
        /* description          */ "",
        /* spawnstate           */ S_HEADCANDLES,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 42 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 2,
        /* blood                */ 0
    },

    // Impaled human (MT_MISC74)
    {
        /* doomednum            */ ImpaledHuman,
        /* description          */ "",
        /* spawnstate           */ S_DEADSTICK,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 64 * FRACUNIT,
        /* projectilepassheight */ 16 * FRACUNIT,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Twitching impaled human (MT_MISC75)
    {
        /* doomednum            */ TwitchingImpaledHuman,
        /* description          */ "",
        /* spawnstate           */ S_LIVESTICK,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 64 * FRACUNIT,
        /* projectilepassheight */ 16 * FRACUNIT,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 2,
        /* blood                */ MT_BLOOD
    },

    // Large brown tree (MT_MISC76)
    {
        /* doomednum            */ LargeBrownTree,
        /* description          */ "",
        /* spawnstate           */ S_BIGTREE,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 32 * FRACUNIT,
        /* height               */ 108 * FRACUNIT,
        /* projectilepassheight */ 16 * FRACUNIT,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Burning Barrel (MT_MISC77)
    {
        /* doomednum            */ BurningBarrel,
        /* description          */ "",
        /* spawnstate           */ S_BBAR1,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 32 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID,
        /* flags2               */ MF2_TRANSLUCENT_REDONLY,
        /* raisestate           */ S_NULL,
        /* frames               */ 3,
        /* blood                */ 0
    },

    // Hanging victim, guts removed (MT_MISC78)
    {
        /* doomednum            */ HangingVictimGutsRemoved,
        /* description          */ "",
        /* spawnstate           */ S_HANGNOGUTS,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 83 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Hanging victim, guts and brain removed (MT_MISC79)
    {
        /* doomednum            */ HangingVictimGutsAndBrainRemoved,
        /* description          */ "",
        /* spawnstate           */ S_HANGBNOBRAIN,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 83 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Hanging torso, looking down (MT_MISC80)
    {
        /* doomednum            */ HangingTorsoLookingDown,
        /* description          */ "",
        /* spawnstate           */ S_HANGTLOOKDN,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 59 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Hanging torso, open skull (MT_MISC81)
    {
        /* doomednum            */ HangingTorsoOpenSkull,
        /* description          */ "",
        /* spawnstate           */ S_HANGTSKULL,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 59 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Hanging torso, looking up (MT_MISC82)
    {
        /* doomednum            */ HangingTorsoLookingUp,
        /* description          */ "",
        /* spawnstate           */ S_HANGTLOOKUP,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 59 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Hanging torso, brain removed (MT_MISC83)
    {
        /* doomednum            */ HangingTorsoBrainRemoved,
        /* description          */ "",
        /* spawnstate           */ S_HANGTNOBRAIN,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 16 * FRACUNIT,
        /* height               */ 59 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SOLID | MF_SPAWNCEILING | MF_NOGRAVITY,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Pool of blood and guts (MT_MISC84)
    {
        /* doomednum            */ PoolOfBloodAndGuts,
        /* description          */ "",
        /* spawnstate           */ S_COLONGIBS,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 4 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ 0,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Pool of blood (MT_MISC85)
    {
        /* doomednum            */ PoolOfBlood,
        /* description          */ "",
        /* spawnstate           */ S_SMALLPOOL,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 1 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ 0,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Pool of brains (MT_MISC86)
    {
        /* doomednum            */ PoolOfBrains,
        /* description          */ "",
        /* spawnstate           */ S_BRAINSTEM,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 4 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ 0,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ MT_BLOOD
    },

    // Blue Blood (MT_BLUEBLOOD)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_BLOOD1,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 0 * FRACUNIT,
        /* height               */ 0 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ 0,
        /* flags2               */ MF2_BLOOD | MF2_TRANSLUCENT_REDTOBLUE_33,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ BLUEBLOOD
    },

    // Green Blood (MT_GREENBLOOD)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_BLOOD1,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 0 * FRACUNIT,
        /* height               */ 0 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ 0,
        /* flags2               */ MF2_BLOOD | MF2_TRANSLUCENT_REDTOGREEN_33,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ GREENBLOOD
    },

    // Fuzzy Blood (MT_MT_FUZZYBLOOD)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_BLOOD1,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 0 * FRACUNIT,
        /* height               */ 0 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_SHADOW,
        /* flags2               */ MF2_BLOOD,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ FUZZYBLOOD
    },

    // Blood Splat (MT_BLOODSPLAT)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_BLOODSPLAT,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 0 * FRACUNIT,
        /* height               */ 0 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ 0,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Smoke Trail (MT_TRAIL)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_TRAIL,
        /* spawnhealth          */ 1000,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 8,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 20 * FRACUNIT,
        /* height               */ 16 * FRACUNIT,
        /* projectilepassheight */ 0,
        /* mass                 */ 100,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ MF_NOBLOCKMAP | MF_NOGRAVITY,
        /* flags2               */ MF2_TRANSLUCENT,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    },

    // Shadow (MT_SHADOW)
    {
        /* doomednum            */ -1,
        /* description          */ "",
        /* spawnstate           */ S_NULL,
        /* spawnhealth          */ 0,
        /* seestate             */ S_NULL,
        /* seesound             */ sfx_None,
        /* reactiontime         */ 0,
        /* attacksound          */ sfx_None,
        /* painstate            */ S_NULL,
        /* painchance           */ 0,
        /* painsound            */ sfx_None,
        /* meleestate           */ S_NULL,
        /* missilestate         */ S_NULL,
        /* deathstate           */ S_NULL,
        /* xdeathstate          */ S_NULL,
        /* deathsound           */ sfx_None,
        /* speed                */ 0,
        /* radius               */ 0,
        /* height               */ 0,
        /* projectilepassheight */ 0,
        /* mass                 */ 0,
        /* damage               */ 0,
        /* activesound          */ sfx_None,
        /* flags                */ 0,
        /* flags2               */ 0,
        /* raisestate           */ S_NULL,
        /* frames               */ 0,
        /* blood                */ 0
    }
};

// [BH] Override offsets in wad file to provide better animation and positioning.
//  Many of these offsets are taken from the DOOM 2 Minor Sprite Fixing Project v1.4
//  by Revenant100, and then further refined by me.
offset_t sproffsets[] =
{
    { "AMMOA0",     14,   14, true }, //   12,   16
    { "APBXA0",     12,   12, true }, //   12,   15
    { "APBXB0",     19,   17, true }, //   19,   18
    { "APBXC0",     16,   15, true }, //   17,   17
    { "APBXD0",     10,   11, true }, //   10,   13
    { "APBXE0",      3,    4, true }, //    4,    6
    { "APLSA0",      7,   10, true }, //    7,   10
    { "APLSB0",      6,    9, true }, //    6,    8
    { "ARM1A0",     15,   15, true }, //   15,   17
    { "ARM1B0",     15,   15, true }, //   15,   17
    { "ARM2A0",     15,   15, true }, //   15,   17
    { "ARM2B0",     15,   15, true }, //   15,   17
    { "BAL2A0",      8,    8, true }, //    7,    8
    { "BAL2B0",      8,    7, true }, //    7,    7
    { "BAL2C0",     23,   25, true }, //   23,   24
    { "BAL2D0",     25,   23, true }, //   25,   21
    { "BAL2E0",     26,   25, true }, //   26,   23
    { "BAL7C0",     17,   17, true }, //   20,    5
    { "BAL7D0",     21,   18, true }, //   23,    6
    { "BAL7E0",     22,   21, true }, //   23,    8
    { "BAR1A0",     11,   30, true }, //   10,   28
    { "BAR1B0",     11,   30, true }, //   10,   28
    { "BEXPA0",     11,   30, true }, //   10,   28
    { "BEXPB0",     11,   29, true }, //   10,   27
    { "BEXPC0",     20,   34, true }, //   19,   32
    { "BEXPD0",     28,   48, true }, //   27,   46
    { "BEXPE0",     30,   51, true }, //   29,   49
    { "BFE1A0",     30,   25, true }, //   30,   27
    { "BFE1B0",     41,   36, true }, //   40,   36
    { "BFE1C0",     72,   59, true }, //   71,   58
    { "BFE1D0",     67,   14, true }, //   68,   14
    { "BFE2A0",     32,   25, true }, //   32,   24
    { "BFE2B0",     19,   23, true }, //   18,   22
    { "BFE2C0",     16,   17, true }, //   19,   17
    { "BFE2D0",      6,    5, true }, //    5,    4
    { "BFGFA0",   -119,  -98, true }, // -125,  -98
    { "BFGFB0",    -91,  -77, true }, //  -97,  -77
    { "BFGGA0",    -75, -116, true }, //  -81, -116
    { "BFGGB0",    -75, -116, true }, //  -81, -116
    { "BFGGC0",    -82, -117, true }, //  -88, -117
    { "BFS1A0",     22,   23, true }, //   24,   37
    { "BFS1B0",     22,   23, true }, //   24,   37
    { "BFUGA0",     31,   34, true }, //   31,   38
    { "BKEYA0",      7,   14, true }, //    7,   19
    { "BKEYB0",      7,   14, true }, //    7,   19
    { "BLUDC0",      6,    6, true }, //    7,    6
    { "BON1A0",      7,   16, true }, //    7,   14
    { "BON1B0",      7,   16, true }, //    7,   14
    { "BON1C0",      7,   16, true }, //    7,   14
    { "BON1D0",      7,   16, true }, //    7,   14
    { "BON2A0",      8,   13, true }, //    7,   13
    { "BON2B0",      8,   13, true }, //    7,   13
    { "BON2C0",      8,   13, true }, //    7,   13
    { "BON2D0",      8,   13, true }, //    7,   13
    { "BOS2E1",     39,   66, true }, //   30,   65
    { "BOS2E2",     13,   68, true }, //   12,   67
    { "BOS2E5",     19,   69, true }, //   28,   69
    { "BOS2E6",     19,   73, true }, //   22,   73
    { "BOS2E7",     21,   73, true }, //   20,   73
    { "BOS2E8",     34,   74, true }, //   30,   74
    { "BOS2F1",     43,   66, true }, //   34,   65
    { "BOS2F2",     38,   66, true }, //   29,   65
    { "BOS2F5",     22,   62, true }, //   28,   62
    { "BOS2F6",     17,   63, true }, //   29,   63
    { "BOS2F7",     22,   64, true }, //   21,   64
    { "BOS2F8",     22,   65, true }, //   26,   65
    { "BOS2G1",     21,   60, true }, //   14,   59
    { "BOS2G2",     22,   60, true }, //   29,   59
    { "BOS2G3",     24,   58, true }, //   26,   58
    { "BOS2G4",     24,   56, true }, //   25,   56
    { "BOS2G5",     37,   55, true }, //   30,   55
    { "BOS2G6",     32,   55, true }, //   24,   55
    { "BOS2G7",     19,   57, true }, //   22,   57
    { "BOS2G8",     22,   55, true }, //   28,   56
    { "BOS2H3",     21,   67, true }, //   25,   67
    { "BOS2H4",     24,   64, true }, //   26,   64
    { "BOS2H5",     22,   62, true }, //   23,   63
    { "BOS2H6",     19,   63, true }, //   15,   62
    { "BOS2H7",     21,   66, true }, //   17,   66
    { "BOS2H8",     19,   67, true }, //   18,   68
    { "BOS2I0",     21,   69, true }, //   20,   69
    { "BOS2J0",     27,   60, true }, //   26,   60
    { "BOS2K0",     27,   50, true }, //   26,   50
    { "BOS2L0",     30,   32, true }, //   29,   32
    { "BOS2M0",     31,   26, true }, //   30,   26
    { "BOS2N0",     31,   26, true }, //   30,   26
    { "BOS2O0",     31,   26, true }, //   30,   26
    { "BOSFA0",     17,   35, true }, //   15,   35
    { "BOSFB0",     16,   37, true }, //   16,   35
    { "BOSFD0",     18,   37, true }, //   17,   37
    { "BOSSE1",     39,   66, true }, //   30,   65
    { "BOSSE2",     13,   68, true }, //   12,   67
    { "BOSSE5",     19,   69, true }, //   26,   69
    { "BOSSE6",     19,   73, true }, //   22,   73
    { "BOSSE7",     21,   73, true }, //   20,   73
    { "BOSSE8",     34,   74, true }, //   30,   74
    { "BOSSF1",     43,   66, true }, //   34,   65
    { "BOSSF2",     38,   66, true }, //   29,   65
    { "BOSSF5",     22,   62, true }, //   29,   62
    { "BOSSF6",     17,   63, true }, //   29,   63
    { "BOSSF7",     22,   64, true }, //   21,   64
    { "BOSSF8",     22,   65, true }, //   26,   65
    { "BOSSG1",     21,   60, true }, //   14,   59
    { "BOSSG2",     20,   59, true }, //   29,   59
    { "BOSSG3",     24,   58, true }, //   26,   58
    { "BOSSG4",     24,   56, true }, //   25,   56
    { "BOSSG5",     37,   55, true }, //   30,   55
    { "BOSSG6",     32,   55, true }, //   24,   55
    { "BOSSG7",     19,   57, true }, //   22,   57
    { "BOSSG8",     22,   55, true }, //   28,   56
    { "BOSSH3",     21,   67, true }, //   25,   67
    { "BOSSH4",     24,   64, true }, //   26,   64
    { "BOSSH5",     22,   62, true }, //   23,   63
    { "BOSSH6",     15,   62, true }, //   19,   63
    { "BOSSH7",     21,   66, true }, //   17,   66
    { "BOSSH8",     19,   67, true }, //   18,   68
    { "BOSSI0",     21,   69, true }, //   20,   69
    { "BOSSJ0",     27,   60, true }, //   26,   60
    { "BOSSK0",     27,   50, true }, //   26,   50
    { "BOSSL0",     30,   32, true }, //   29,   32
    { "BOSSM0",     31,   26, true }, //   30,   26
    { "BOSSN0",     31,   26, true }, //   30,   26
    { "BOSSO0",     31,   26, true }, //   30,   26
    { "BPAKA0",     11,   27, true }, //    8,   25
    { "BROKA0",     27,   19, true }, //   27,   20
    { "BRS1A0",     14,    6, true }, //   13,    3
    { "BSKUA0",      7,   14, true }, //    7,   18
    { "BSKUB0",      7,   14, true }, //    7,   18
    { "BSPIA2A8",   58,   51, true }, //   59,   51
    { "BSPIA4A6",   57,   51, true }, //   57,   52
    { "BSPIA5D5",   54,   48, true }, //   53,   47
    { "BSPIB2B8",   67,   50, true }, //   65,   50
    { "BSPIB3B7",   55,   48, true }, //   55,   46
    { "BSPIB4B6",   56,   49, true }, //   57,   45
    { "BSPIC4C6",   58,   50, true }, //   59,   51
    { "BSPIC5F5",   53,   48, true }, //   52,   47
    { "BSPID2D8",   53,   50, true }, //   51,   51
    { "BSPIE2E8",   52,   50, true }, //   51,   45
    { "BSPIE4E6",   65,   49, true }, //   65,   50
    { "BSPIF2F8",   53,   50, true }, //   54,   52
    { "BSPIF3F7",   63,   48, true }, //   62,   48
    { "BSPIF4F6",   59,   51, true }, //   55,   51
    { "BSPIG1",     50,   49, true }, //   50,   48
    { "BSPIG2G8",   62,   50, true }, //   61,   50
    { "BSPIG3G7",   55,   50, true }, //   56,   50
    { "BSPIG4G6",   61,   51, true }, //   62,   52
    { "BSPIG5",     55,   49, true }, //   56,   49
    { "BSPIH1",     50,   49, true }, //   50,   48
    { "BSPIH2H8",   62,   50, true }, //   61,   50
    { "BSPIH3H7",   55,   50, true }, //   56,   50
    { "BSPIH4H6",   61,   51, true }, //   62,   52
    { "BSPIH5",     55,   49, true }, //   56,   49
    { "BSPIJ0",     47,   50, true }, //   50,   50
    { "BSPIK0",     47,   53, true }, //   50,   53
    { "BSPIL0",     44,   48, true }, //   47,   48
    { "BSPIM0",     42,   42, true }, //   45,   42
    { "BSPIN0",     42,   40, true }, //   45,   40
    { "BSPIO0",     42,   28, true }, //   45,   28
    { "BSPIP0",     42,   26, true }, //   45,   26
    { "CANDA0",      8,   14, true }, //    8,   15
    { "CBRAA0",     14,   58, true }, //   15,   57
    { "CELLA0",      8,   10, true }, //    8,   12
    { "CELPA0",     16,   19, true }, //   15,   20
    { "CEYEA0",     22,   59, true }, //   21,   56
    { "CEYEB0",     22,   58, true }, //   21,   55
    { "CEYEC0",     22,   59, true }, //   21,   56
    { "CHGFA0",   -116,  -98, true }, // -118,  -98
    { "CHGFB0",   -118,  -97, true }, // -120,  -97
    { "CHGGA0",   -102, -117, true }, // -104, -117
    { "CHGGB0",   -102, -119, true }, // -104, -119
    { "CLIPA0",      4,    9, true }, //    2,   11
    { "COL1A0",     17,   50, true }, //   16,   48
    { "COL2A0",     17,   37, true }, //   16,   35
    { "COL3A0",     17,   50, true }, //   16,   48
    { "COL4A0",     17,   37, true }, //   17,   35
    { "COL5A0",     17,   42, true }, //   16,   40
    { "COL5B0",     17,   43, true }, //   16,   41
    { "COL6A0",     17,   46, true }, //   17,   44
    { "COLUA0",     11,   46, true }, //    9,   43
    { "CPOSE2",     26,   53, true }, //   25,   53
    { "CPOSE3",     31,   53, true }, //   27,   53
    { "CPOSE6",     17,   51, true }, //   18,   51
    { "CPOSE7",     22,   53, true }, //   25,   53
    { "CPOSE8",     23,   53, true }, //   18,   53
    { "CPOSF2",     31,   53, true }, //   29,   53
    { "CPOSF3",     35,   53, true }, //   31,   53
    { "CPOSF6",     16,   51, true }, //   21,   51
    { "CPOSF7",     25,   53, true }, //   22,   53
    { "CPOSF8",     23,   53, true }, //   22,   53
    { "CPOSG7",     19,   54, true }, //   20,   54
    { "CPOSH0",     21,   56, true }, //   20,   56
    { "CPOSI0",     24,   59, true }, //   23,   59
    { "CPOSJ0",     29,   54, true }, //   28,   54
    { "CPOSK0",     30,   44, true }, //   31,   44
    { "CPOSL0",     32,   32, true }, //   31,   32
    { "CPOSM0",     33,   20, true }, //   32,   20
    { "CPOSN0",     33,   16, true }, //   32,   16
    { "CPOSP0",     28,   55, true }, //   28,   56
    { "CPOSQ0",     34,   45, true }, //   30,   45
    { "CPOSR0",     40,   36, true }, //   32,   36
    { "CPOSS0",     40,   27, true }, //   32,   27
    { "CPOST0",     40,   15, true }, //   32,   15
    { "CSAWA0",     31,   22, true }, //   31,   23
    { "CYBRE3",     56,  105, true }, //   52,  105
    { "CYBRE4",     51,  104, true }, //   50,  104
    { "CYBRE6",     40,  105, true }, //   39,  105
    { "CYBRE7",     39,  105, true }, //   46,  105
    { "CYBRF3",     72,  105, true }, //   60,  105
    { "CYBRF4",     64,  104, true }, //   59,  104
    { "CYBRF6",     40,  105, true }, //   47,  105
    { "CYBRF7",     39,  105, true }, //   54,  105
    { "CYBRF8",     55,  105, true }, //   63,  105
    { "CYBRG1",     45,  105, true }, //   61,  105
    { "CYBRG2",     38,  106, true }, //   46,  106
    { "CYBRG4",     71,  105, true }, //   58,  105
    { "CYBRG5",     62,  104, true }, //   54,  104
    { "CYBRG6",     43,  105, true }, //   46,  105
    { "CYBRG7",     40,  105, true }, //   47,  105
    { "CYBRH0",     45,  106, true }, //   60,  106
    { "CYBRI0",     43,  108, true }, //   55,  108
    { "CYBRJ0",     45,  111, true }, //   49,  111
    { "CYBRK0",     51,  112, true }, //   56,  112
    { "CYBRL0",     55,  119, true }, //   62,  119
    { "CYBRM0",     62,  126, true }, //   67,  126
    { "CYBRN0",     65,  129, true }, //   70,  129
    { "CYBRO0",     64,  129, true }, //   69,  129
    { "CYBRP0",     55,   25, true }, //   60,   25
    { "ELECA0",     19,  125, true }, //   19,  123
    { "FATBA1",      9,    8, true }, //    9,   11
    { "FATBA2A8",   18,    7, true }, //   18,   10
    { "FATBA3A7",   22,    6, true }, //   22,    9
    { "FATBA4A6",   18,    6, true }, //   18,    9
    { "FATBA5",      9,    8, true }, //    9,   11
    { "FATBB1",      9,    8, true }, //    9,   11
    { "FATBB2B8",   18,    7, true }, //   18,   10
    { "FATBB3B7",   22,    6, true }, //   21,    9
    { "FATBB4B6",   18,    6, true }, //   18,    9
    { "FATBB5",      9,    8, true }, //    9,   11
    { "FATTA1",     40,   60, true }, //   39,   60
    { "FATTA2A8",   51,   61, true }, //   39,   61
    { "FATTA3A7",   41,   60, true }, //   38,   60
    { "FATTA5",     35,   59, true }, //   39,   59
    { "FATTB1",     43,   64, true }, //   43,   65
    { "FATTB2B8",   43,   64, true }, //   43,   65
    { "FATTB3B7",   41,   61, true }, //   43,   61
    { "FATTB5",     45,   58, true }, //   43,   58
    { "FATTC5",     37,   59, true }, //   36,   58
    { "FATTD1",     33,   60, true }, //   38,   60
    { "FATTE1",     45,   64, true }, //   43,   65
    { "FATTE2E8",   43,   62, true }, //   43,   61
    { "FATTE3E7",   41,   62, true }, //   43,   62
    { "FATTF1",     39,   65, true }, //   42,   65
    { "FATTF3F7",   41,   61, true }, //   43,   61
    { "FATTF4F6",   34,   59, true }, //   43,   59
    { "FATTG1",     44,   61, true }, //   42,   60
    { "FATTG2G8",   54,   59, true }, //   51,   59
    { "FATTG5",     41,   61, true }, //   42,   61
    { "FATTH1",     43,   61, true }, //   42,   60
    { "FATTH2H8",   53,   59, true }, //   50,   59
    { "FATTH4H6",   32,   61, true }, //   42,   61
    { "FATTH5",     43,   60, true }, //   42,   60
    { "FATTI1",     44,   64, true }, //   42,   63
    { "FATTI2I8",   54,   64, true }, //   51,   64
    { "FATTJ1",     35,   59, true }, //   32,   62
    { "FATTJ2",     36,   60, true }, //   47,   62
    { "FATTJ3",     40,   58, true }, //   39,   59
    { "FATTJ4",     30,   59, true }, //   30,   61
    { "FATTJ5",     42,   59, true }, //   32,   59
    { "FATTJ6",     31,   59, true }, //   29,   61
    { "FATTJ7",     35,   58, true }, //   37,   59
    { "FATTJ8",     52,   60, true }, //   46,   62
    { "FATTK0",     51,   73, true }, //   50,   73
    { "FATTL0",     51,   75, true }, //   50,   75
    { "FATTM0",     46,   66, true }, //   45,   66
    { "FATTN0",     38,   51, true }, //   37,   53
    { "FATTO0",     37,   41, true }, //   35,   41
    { "FATTP0",     38,   40, true }, //   36,   40
    { "FATTQ0",     38,   39, true }, //   36,   39
    { "FATTR0",     38,   39, true }, //   36,   39
    { "FATTS0",     38,   38, true }, //   36,   38
    { "FATTT0",     38,   36, true }, //   36,   36
    { "FBXPA0",     17,   17, true }, //   19,   32
    { "FBXPB0",     20,   17, true }, //   19,   31
    { "FBXPC0",     22,   20, true }, //   22,   35
    { "FCANA0",     12,   51, true }, //   19,   49
    { "FCANB0",     12,   51, true }, //   19,   49
    { "FCANC0",     12,   49, true }, //   19,   47
    { "GOR1A0",     11,   67, true }, //   17,   67
    { "GOR1B0",     12,   67, true }, //   18,   67
    { "GOR1C0",     11,   67, true }, //   17,   67
    { "GOR2A0",     20,   83, true }, //   22,   83
    { "GOR3A0",     17,   83, true }, //   19,   83
    { "GOR4A0",      8,   67, true }, //    6,   67
    { "GOR5A0",      5,   51, true }, //    6,   51
    { "HDB1A0",     11,   83, true }, //   10,   83
    { "HDB2A0",     11,   83, true }, //   10,   83
    { "HDB3A0",     11,   59, true }, //   10,   59
    { "HDB4A0",     11,   59, true }, //   10,   59
    { "HDB5A0",     11,   59, true }, //   10,   59
    { "HDB6A0",     11,   59, true }, //   10,   59
    { "HEADA3A7",   29,   66, true }, //   27,   68
    { "HEADA4A6",   29,   68, true }, //   32,   68
    { "HEADA5",     31,   67, true }, //   28,   66
    { "HEADB1",     31,   66, true }, //   31,   70
    { "HEADB2B8",   26,   66, true }, //   29,   69
    { "HEADB3B7",   29,   66, true }, //   30,   68
    { "HEADB4B6",   29,   66, true }, //   32,   67
    { "HEADB5",     31,   67, true }, //   32,   68
    { "HEADC1",     31,   67, true }, //   31,   71
    { "HEADC2C8",   26,   68, true }, //   29,   72
    { "HEADC3C7",   29,   66, true }, //   30,   68
    { "HEADC4C6",   29,   67, true }, //   32,   67
    { "HEADC5",     31,   68, true }, //   32,   68
    { "HEADD1",     31,   68, true }, //   31,   72
    { "HEADD2D8",   26,   69, true }, //   29,   72
    { "HEADD3D7",   29,   70, true }, //   30,   72
    { "HEADD4D6",   29,   69, true }, //   32,   70
    { "HEADD5",     31,   68, true }, //   32,   68
    { "HEADE2E8",   28,   65, true }, //   30,   67
    { "HEADE3E7",   29,   67, true }, //   29,   68
    { "HEADE4E6",   30,   69, true }, //   31,   69
    { "HEADE5",     31,   69, true }, //   30,   68
    { "HEADF2F8",   28,   64, true }, //   31,   66
    { "HEADF3F7",   30,   67, true }, //   31,   67
    { "HEADF4F6",   30,   69, true }, //   31,   69
    { "HEADF5",     31,   69, true }, //   30,   68
    { "HEADK0",     37,   61, true }, //   35,   63
    { "HEADL0",     39,   41, true }, //   37,   47
    { "IFOGA0",     19,   33, true }, //   18,   33
    { "IFOGB0",     16,   27, true }, //   16,   26
    { "IFOGC0",      8,   20, true }, //    6,   15
    { "IFOGD0",      4,   13, true }, //    2,   10
    { "IFOGE0",      1,   11, true }, //    0,    7
    { "KEENA0",      7,   67, true }, //    6,   67
    { "KEENB0",     10,   67, true }, //    8,   67
    { "KEENC0",     11,   67, true }, //    9,   67
    { "KEEND0",     13,   67, true }, //   11,   67
    { "KEENE0",     14,   67, true }, //   13,   67
    { "KEENF0",     14,   67, true }, //   13,   67
    { "KEENG0",     15,   67, true }, //   14,   67
    { "KEENH0",     18,   67, true }, //   17,   67
    { "KEENI0",     18,   67, true }, //   17,   67
    { "KEENJ0",     18,   67, true }, //   17,   67
    { "KEENK0",     18,   67, true }, //   17,   67
    { "KEENL0",     18,   67, true }, //   17,   67
    { "KEENM0",      9,   67, true }, //    8,   67
    { "LAUNA0",     31,   14, true }, //   31,   18
    { "MANFA1",     17,   19, true }, //   19,   17
    { "MANFA6A4",   25,   14, true }, //   25,   19
    { "MANFA7A3",   34,   11, true }, //   34,   16
    { "MANFA8A2",   33,   12, true }, //   33,   17
    { "MANFB1",     17,   19, true }, //   19,   17
    { "MANFB6B4",   18,   15, true }, //   18,   19
    { "MANFB7B3",   30,   13, true }, //   30,   17
    { "MANFB8B2",   27,   14, true }, //   27,   17
    { "MEDIA0",     14,   17, true }, //   13,   19
    { "MEGAA0",     12,   35, true }, //   12,   32
    { "MEGAB0",     12,   35, true }, //   12,   32
    { "MEGAC0",     12,   35, true }, //   12,   32
    { "MEGAD0",     12,   35, true }, //   12,   32
    { "MGUNA0",     27,   14, true }, //   25,   18
    { "MISFA0",   -134, -105, true }, // -136, -105
    { "MISFB0",   -123, -101, true }, // -126, -101
    { "MISFC0",   -114,  -94, true }, // -117,  -94
    { "MISFD0",   -109,  -81, true }, // -112,  -81
    { "MISGA0",   -117, -121, true }, // -119, -121
    { "MISGB0",   -109, -125, true }, // -112, -125
    { "MISLA1",      7,    8, true }, //    7,   13
    { "MISLA5",      7,    8, true }, //    7,   13
    { "MISLA6A4",   12,    8, true }, //   12,   13
    { "MISLA7A3",   25,    8, true }, //   25,   13
    { "MISLA8A2",   16,    8, true }, //   16,   13
    { "MISLC0",     44,   36, true }, //   42,   34
    { "MISLD0",     52,   46, true }, //   50,   43
    { "PAINA2A8",   30,   58, true }, //   34,   58
    { "PAINA3A7",   37,   58, true }, //   35,   60
    { "PAINA4A6",   32,   59, true }, //   35,   59
    { "PAINA5",     36,   59, true }, //   37,   58
    { "PAINB2B8",   34,   58, true }, //   38,   58
    { "PAINB3B7",   37,   58, true }, //   35,   60
    { "PAINB4B6",   32,   59, true }, //   35,   59
    { "PAINB5",     37,   59, true }, //   38,   58
    { "PAINC2C8",   35,   58, true }, //   39,   58
    { "PAINC3C7",   37,   58, true }, //   35,   60
    { "PAINC4C6",   32,   59, true }, //   35,   59
    { "PAINC5",     38,   59, true }, //   36,   58
    { "PAIND1",     44,   61, true }, //   44,   62
    { "PAIND2D8",   41,   59, true }, //   40,   61
    { "PAIND3D7",   38,   59, true }, //   35,   61
    { "PAIND4D6",   36,   59, true }, //   35,   59
    { "PAIND5",     36,   59, true }, //   37,   58
    { "PAINE2E8",   42,   60, true }, //   41,   62
    { "PAINE3E7",   37,   59, true }, //   34,   61
    { "PAINE4E6",   36,   60, true }, //   35,   60
    { "PAINE5",     35,   60, true }, //   36,   59
    { "PAINF2F8",   47,   61, true }, //   38,   62
    { "PAINF3F7",   33,   61, true }, //   30,   63
    { "PAINF4F6",   41,   61, true }, //   36,   69
    { "PAINF5",     36,   62, true }, //   37,   68
    { "PAING1",     42,   61, true }, //   38,   60
    { "PAING2G8",   31,   59, true }, //   35,   60
    { "PAING3G7",   36,   59, true }, //   34,   62
    { "PAING4G6",   41,   59, true }, //   36,   59
    { "PAING5",     45,   58, true }, //   47,   57
    { "PAINH0",     42,   61, true }, //   41,   57
    { "PAINI0",     38,   58, true }, //   36,   54
    { "PAINJ0",     41,   57, true }, //   39,   54
    { "PAINK0",     47,   66, true }, //   46,   71
    { "PAINL0",     43,   66, true }, //   43,   71
    { "PAINM0",     52,   76, true }, //   49,   88
    { "PINSA0",     12,   35, true }, //   11,   39
    { "PINSB0",     12,   35, true }, //   11,   39
    { "PINSC0",     12,   35, true }, //   11,   39
    { "PINSD0",     12,   35, true }, //   11,   39
    { "PINVA0",     12,   35, true }, //   11,   23
    { "PINVB0",     12,   35, true }, //   11,   23
    { "PINVC0",     12,   35, true }, //   11,   23
    { "PINVD0",     12,   35, true }, //   11,   23
    { "PLASA0",     27,   14, true }, //   27,   19
    { "PLSEA0",     11,   12, true }, //   12,   11
    { "PLSEB0",     18,   20, true }, //   19,   18
    { "PLSEC0",     19,   18, true }, //   17,   18
    { "PLSED0",     15,   16, true }, //   13,   13
    { "PLSEE0",      3,    3, true }, //    0,    2
    { "PLSFA0",   -119,  -93, true }, // -123,  -93
    { "PLSFB0",   -118,  -95, true }, // -122,  -95
    { "PLSGA0",   -119, -107, true }, // -123, -107
    { "PLSGB0",    -60,  -57, true }, //  -64,  -57
    { "PMAPA0",     14,   25, true }, //   13,   23
    { "PMAPB0",     14,   25, true }, //   13,   23
    { "PMAPC0",     14,   25, true }, //   13,   23
    { "PMAPD0",     14,   25, true }, //   13,   23
    { "POB1A0",     20,    5, true }, //   16,    2
    { "POB2A0",     16,    1, true }, //   14,   -2
    { "POL1A0",     23,   64, true }, //   22,   62
    { "POL2A0",     19,   62, true }, //   19,   62
    { "POL3A0",     19,   41, true }, //   19,   38
    { "POL3B0",     19,   41, true }, //   19,   38
    { "POL4A0",     19,   54, true }, //   19,   51
    { "POL5A0",     27,    6, true }, //   27,    5
    { "POL6A0",     17,   65, true }, //   17,   62
    { "POL6B0",     19,   65, true }, //   19,   62
    { "POSSC4C6",   22,   51, true }, //   20,   51
    { "POSSD4D6",   24,   52, true }, //   22,   52
    { "POSSE1",     13,   50, true }, //   12,   50
    { "POSSE2E8",   25,   50, true }, //   21,   50
    { "POSSE3E7",   28,   50, true }, //   26,   50
    { "POSSE5",     11,   47, true }, //   12,   46
    { "POSSF1",     14,   50, true }, //   13,   50
    { "POSSF2F8",   27,   50, true }, //   23,   50
    { "POSSF3F7",   29,   50, true }, //   27,   50
    { "POSSF5",     10,   47, true }, //   11,   46
    { "POSSG2G8",   19,   53, true }, //   16,   53
    { "POSSG3G7",   22,   53, true }, //   21,   53
    { "POSSG4G6",   21,   50, true }, //   20,   50
    { "POSSG5",     16,   49, true }, //   17,   49
    { "POSSO0",     21,   58, true }, //   25,   58
    { "POSSQ0",     23,   47, true }, //   27,   47
    { "PSTRA0",     14,   17, true }, //   12,   15
    { "PVISA0",     14,   11, true }, //   13,    9
    { "PVISB0",     14,   11, true }, //   13,    9
    { "RKEYA0",      7,   14, true }, //    8,   19
    { "RKEYB0",      7,   14, true }, //    8,   19
    { "ROCKA0",      6,   25, true }, //    6,   27
    { "RSKUA0",      7,   14, true }, //    7,   18
    { "RSKUB0",      7,   14, true }, //    7,   18
    { "SARGA3A7",   28,   49, true }, //   28,   48
    { "SARGB3B7",   28,   52, true }, //   28,   51
    { "SARGB5",     20,   51, true }, //   20,   48
    { "SARGC3C7",   29,   49, true }, //   29,   48
    { "SARGD3D7",   29,   54, true }, //   29,   53
    { "SARGD5",     20,   51, true }, //   20,   48
    { "SARGE3",     31,   48, true }, //   23,   48
    { "SARGE6",     23,   47, true }, //   25,   47
    { "SARGE7",     30,   46, true }, //   33,   46
    { "SARGF3",     38,   48, true }, //   30,   48
    { "SARGF6",     23,   47, true }, //   25,   47
    { "SARGF7",     30,   47, true }, //   34,   47
    { "SARGG3",     41,   50, true }, //   33,   50
    { "SARGG6",     24,   47, true }, //   26,   47
    { "SARGG7",     30,   48, true }, //   34,   48
    { "SARGH2",     25,   48, true }, //   27,   48
    { "SARGH3",     30,   48, true }, //   29,   46
    { "SARGH4",     24,   45, true }, //   23,   44
    { "SARGH6",     21,   45, true }, //   20,   45
    { "SARGH7",     29,   46, true }, //   25,   46
    { "SARGH8",     29,   47, true }, //   30,   47
    { "SARGK0",     21,   55, true }, //   21,   57
    { "SARGL0",     30,   52, true }, //   29,   55
    { "SARGM0",     31,   36, true }, //   33,   41
    { "SARGN0",     31,   22, true }, //   33,   27
    { "SAWGA0",    -81, -113, true }, //  -75, -113
    { "SAWGB0",    -81, -113, true }, //  -75, -113
    { "SAWGC0",    -72,  -79, true }, //  -68,  -79
    { "SAWGD0",    -73,  -79, true }, //  -67,  -79
    { "SBOXA0",     16,   10, true }, //   16,   12
    { "SGN2A0",     27,   12, true }, //   27,   15
    { "SHELA0",      7,    5, true }, //    5,    7
    { "SHOTA0",     31,   10, true }, //   31,   17
    { "SHT2A0",   -130, -113, true }, // -134, -113
    { "SHT2B0",    -97,  -65, true }, // -100,  -65
    { "SHT2C0",    -23,  -38, true }, //  -25,  -38
    { "SHT2D0",   -117,  -88, true }, // -118,  -88
    { "SHT2E0",      4, -105, true }, //    0, -105
    { "SHT2F0",   -101, -117, true }, // -105, -117
    { "SHT2G0",   -116,  -88, true }, // -118,  -88
    { "SHT2H0",   -120,  -83, true }, // -123,  -83
    { "SHT2I0",   -133,  -99, true }, // -137,  -99
    { "SHT2J0",   -127,  -90, true }, // -131,  -90
    { "SHTFA0",   -138,  -95, true }, // -141,  -95
    { "SHTFB0",   -133,  -86, true }, // -136,  -86
    { "SHTGA0",   -118, -108, true }, // -121, -108
    { "SHTGB0",    -40,  -47, true }, //  -43,  -47
    { "SHTGC0",    -27,  -17, true }, //  -30,  -17
    { "SHTGD0",    -26,  -37, true }, //  -29,  -37
    { "SKELA5D5",   19,   71, true }, //   13,   71
    { "SKELB1E1",   26,   81, true }, //   27,   81
    { "SKELB5E5",   25,   74, true }, //   19,   74
    { "SKELC1F1",   27,   83, true }, //   30,   83
    { "SKELC5F5",   34,   81, true }, //   28,   81
    { "SKELG1",     29,   68, true }, //   25,   67
    { "SKELG2",      5,   69, true }, //   25,   69
    { "SKELG3",     16,   69, true }, //   33,   68
    { "SKELG4",     12,   70, true }, //   37,   72
    { "SKELG5",     20,   71, true }, //   31,   72
    { "SKELG6",     41,   68, true }, //   26,   70
    { "SKELG7",     54,   67, true }, //   36,   67
    { "SKELG8",     60,   68, true }, //   37,   68
    { "SKELH1",     39,   78, true }, //   30,   78
    { "SKELH2",     41,   78, true }, //   35,   78
    { "SKELH3",     34,   77, true }, //   30,   77
    { "SKELH4",     22,   76, true }, //   20,   76
    { "SKELH5",     18,   76, true }, //   24,   76
    { "SKELH6",     25,   73, true }, //   37,   72
    { "SKELH7",     29,   74, true }, //   36,   74
    { "SKELH8",     19,   76, true }, //   23,   76
    { "SKELI1",     17,   61, true }, //   20,   61
    { "SKELI2",     29,   63, true }, //   31,   62
    { "SKELI3",     45,   61, true }, //   36,   60
    { "SKELI4",     42,   60, true }, //   29,   60
    { "SKELI5",     23,   61, true }, //   14,   60
    { "SKELI6",     24,   59, true }, //   28,   59
    { "SKELI7",     32,   59, true }, //   39,   59
    { "SKELI8",     17,   61, true }, //   29,   61
    { "SKELJ1",     23,   67, true }, //   25,   67
    { "SKELK1",     25,   76, true }, //   27,   76
    { "SKELK2",     16,   75, true }, //   23,   75
    { "SKELK3",     17,   74, true }, //   23,   74
    { "SKELK4",     14,   74, true }, //   20,   75
    { "SKELK5",     23,   76, true }, //   27,   75
    { "SKELK6",     31,   75, true }, //   27,   75
    { "SKELK7",     31,   73, true }, //   18,   75
    { "SKELK8",     30,   75, true }, //   17,   75
    { "SKELL2",     12,   67, true }, //   18,   67
    { "SKELL3",     16,   67, true }, //   24,   67
    { "SKELL4",     30,   68, true }, //   34,   68
    { "SKELL5",     29,   69, true }, //   32,   69
    { "SKELL6",     26,   68, true }, //   21,   68
    { "SKELL7",     39,   68, true }, //   25,   68
    { "SKELL8",     38,   69, true }, //   33,   69
    { "SKELM0",     30,   74, true }, //   27,   74
    { "SKELN0",     30,   68, true }, //   38,   65
    { "SKELO0",     27,   51, true }, //   28,   51
    { "SKELP0",     23,   33, true }, //   28,   33
    { "SKELQ0",     29,   17, true }, //   40,   19
    { "SKULA1",     22,   50, true }, //   20,   50
    { "SKULA5",     22,   49, true }, //   21,   48
    { "SKULA6A4",   13,   56, true }, //   13,   53
    { "SKULA7A3",   14,   57, true }, //   14,   54
    { "SKULA8A2",   15,   50, true }, //   15,   47
    { "SKULB1",     22,   49, true }, //   20,   49
    { "SKULB5",     22,   49, true }, //   21,   48
    { "SKULB6B4",   13,   56, true }, //   13,   53
    { "SKULB7B3",   14,   57, true }, //   14,   54
    { "SKULB8B2",   15,   56, true }, //   15,   53
    { "SKULC1",     22,   47, true }, //   23,   47
    { "SKULC5",     22,   31, true }, //   20,   30
    { "SKULC7C3",   33,   37, true }, //   33,   36
    { "SKULC8C2",   32,   38, true }, //   32,   37
    { "SKULD1",     22,   46, true }, //   23,   46
    { "SKULD5",     22,   32, true }, //   20,   31
    { "SKULD7D3",   33,   37, true }, //   33,   36
    { "SKULD8D2",   25,   38, true }, //   25,   37
    { "SKULE1",     15,   53, true }, //   14,   53
    { "SKULE6E4",   11,   54, true }, //   11,   53
    { "SKULE7E3",   15,   55, true }, //   15,   54
    { "SKULE8E2",   15,   55, true }, //   15,   54
    { "SKULF0",     15,   53, true }, //   17,   53
    { "SKULG0",     17,   53, true }, //   15,   53
    { "SKULH0",     23,   48, true }, //   24,   48
    { "SKULI0",     35,   52, true }, //   35,   58
    { "SKULJ0",     44,   59, true }, //   45,   75
    { "SKULK0",     51,   67, true }, //   49,   85
    { "SMBTA0",      8,   72, true }, //   10,   72
    { "SMBTB0",      8,   67, true }, //   10,   67
    { "SMBTC0",      8,   67, true }, //   10,   67
    { "SMBTD0",      8,   73, true }, //   10,   73
    { "SMGTA0",      8,   72, true }, //   10,   72
    { "SMGTB0",      8,   67, true }, //   10,   67
    { "SMGTC0",      8,   67, true }, //   10,   67
    { "SMGTD0",      8,   73, true }, //   10,   73
    { "SMRTA0",      8,   72, true }, //   10,   72
    { "SMRTB0",      8,   67, true }, //   10,   67
    { "SMRTC0",      8,   67, true }, //   10,   67
    { "SMRTD0",      8,   73, true }, //   10,   73
    { "SOULA0",     12,   35, true }, //   14,   39
    { "SOULB0",     12,   35, true }, //   14,   39
    { "SOULC0",     12,   35, true }, //   14,   39
    { "SOULD0",     12,   35, true }, //   14,   39
    { "SPIDA1D1",  103,  105, true }, //  107,  105
    { "SPIDA2A8",  116,  107, true }, //  110,  107
    { "SPIDA3A7",  106,  106, true }, //   99,  106
    { "SPIDA4A6",  113,  107, true }, //  111,  111
    { "SPIDB1E1",  125,  104, true }, //  130,  104
    { "SPIDB2B8",  134,  106, true }, //  130,  106
    { "SPIDB3B7",  108,  102, true }, //  101,   99
    { "SPIDB4B6",  112,  105, true }, //  110,   99
    { "SPIDC1F1",  102,  103, true }, //  108,  103
    { "SPIDC3C7",  107,  105, true }, //  103,  105
    { "SPIDC4C6",  115,  107, true }, //  114,  110
    { "SPIDD2D8",  105,  104, true }, //  113,  107
    { "SPIDD3D7",  104,  103, true }, //   99,  103
    { "SPIDD4D6",  111,  104, true }, //  107,  106
    { "SPIDE2E8",  103,  103, true }, //  113,   94
    { "SPIDE3E7",  127,  101, true }, //  122,  101
    { "SPIDE4E6",  131,  105, true }, //  128,  106
    { "SPIDF2F8",  105,  104, true }, //  114,  109
    { "SPIDF3F7",  126,  101, true }, //  122,  102
    { "SPIDF4F6",  117,  105, true }, //  114,  106
    { "SPIDG1",    101,  102, true }, //   95,  101
    { "SPIDG3G7",  111,  108, true }, //  113,  108
    { "SPIDG4G6",  123,  109, true }, //  120,  112
    { "SPIDG5",    109,  104, true }, //  106,  105
    { "SPIDH1",    101,  102, true }, //   95,  101
    { "SPIDH2H8",  123,  107, true }, //  123,  108
    { "SPIDH3H7",  111,  108, true }, //  113,  108
    { "SPIDH4H6",  123,  109, true }, //  120,  112
    { "SPIDH5",    109,  104, true }, //  106,  105
    { "SPIDI1",     95,  101, true }, //  102,  102
    { "SPIDI3",    118,  100, true }, //  122,  100
    { "SPIDI5",    105,  100, true }, //   95,  100
    { "SPIDI6",    117,  105, true }, //  106,  107
    { "SPIDI7",     96,  102, true }, //   88,  102
    { "SPIDI8",    120,  103, true }, //  115,  105
    { "SPOSE1",     13,   50, true }, //   12,   50
    { "SPOSE2E8",   21,   50, true }, //   17,   50
    { "SPOSE3E7",   19,   50, true }, //   19,   49
    { "SPOSE5",     11,   47, true }, //   12,   46
    { "SPOSF1",     14,   50, true }, //   13,   50
    { "SPOSF2F8",   25,   50, true }, //   21,   50
    { "SPOSF3F7",   26,   50, true }, //   24,   49
    { "SPOSF5",     10,   47, true }, //   11,   46
    { "SPOSG2G8",   16,   52, true }, //   13,   51
    { "SPOSG3G7",   22,   52, true }, //   21,   50
    { "SPOSG4G6",   21,   49, true }, //   20,   50
    { "SPOSG5",     16,   49, true }, //   17,   49
    { "SPOSO0",     21,   58, true }, //   25,   58
    { "SPOSQ0",     23,   47, true }, //   27,   47
    { "SSWVB3",     18,   51, true }, //   14,   51
    { "SSWVB4",     16,   51, true }, //   12,   51
    { "SSWVC7",     19,   49, true }, //   15,   49
    { "SSWVC8",     15,   48, true }, //   11,   48
    { "SSWVD3",     19,   51, true }, //   15,   51
    { "SSWVD4",     16,   51, true }, //   12,   51
    { "SSWVI0",     14,   49, true }, //   18,   49
    { "SSWVJ0",     11,   41, true }, //   15,   41
    { "SSWVN0",     19,   54, true }, //   15,   54
    { "SSWVP0",     25,   56, true }, //   25,   57
    { "SSWVQ0",     28,   50, true }, //   24,   51
    { "SSWVS0",     28,   37, true }, //   24,   37
    { "SSWVT0",     28,   30, true }, //   24,   30
    { "SSWVU0",     28,   20, true }, //   24,   20
    { "SSWVV0",     28,   15, true }, //   24,   15
    { "STIMA0",      7,   13, true }, //    7,   15
    { "SUITA0",     12,   51, true }, //   11,   51
    { "TBLUA0",     13,   92, true }, //   14,   92
    { "TBLUB0",     13,   92, true }, //   14,   92
    { "TBLUC0",     13,   92, true }, //   14,   92
    { "TBLUD0",     13,   93, true }, //   14,   93
    { "TFOGA0",     19,   58, true }, //   21,   56
    { "TFOGI0",      6,   32, true }, //    6,   28
    { "TFOGJ0",      8,   34, true }, //    8,   30
    { "TGRNA0",     13,   92, true }, //   14,   92
    { "TGRNB0",     13,   87, true }, //   14,   87
    { "TGRNC0",     13,   87, true }, //   14,   87
    { "TGRND0",     13,   93, true }, //   14,   93
    { "TLMPA0",     11,   78, true }, //   11,   77
    { "TLMPB0",     11,   78, true }, //   11,   77
    { "TLMPC0",     11,   78, true }, //   11,   77
    { "TLMPD0",     11,   78, true }, //   11,   77
    { "TLP2A0",     10,   58, true }, //   10,   57
    { "TLP2B0",     10,   58, true }, //   10,   57
    { "TLP2C0",     10,   58, true }, //   10,   57
    { "TLP2D0",     10,   58, true }, //   10,   57
    { "TRE1A0",     28,   65, true }, //   25,   65
    { "TRE2A0",     62,  120, true }, //   63,  120
    { "TREDA0",     13,   92, true }, //   14,   92
    { "TREDB0",     13,   87, true }, //   14,   87
    { "TREDC0",     13,   87, true }, //   14,   87
    { "TREDD0",     13,   93, true }, //   14,   93
    { "TROOA1",     21,   52, true }, //   19,   52
    { "TROOA2A8",   24,   50, true }, //   17,   50
    { "TROOA3A7",   21,   47, true }, //   15,   44
    { "TROOA4A6",   17,   47, true }, //   20,   42
    { "TROOA5",     18,   46, true }, //   21,   44
    { "TROOB1",     19,   51, true }, //   17,   51
    { "TROOB2B8",   21,   52, true }, //   13,   52
    { "TROOB3B7",   22,   48, true }, //   16,   46
    { "TROOB4B6",   18,   45, true }, //   19,   42
    { "TROOB5",     17,   43, true }, //   20,   41
    { "TROOC1",     19,   55, true }, //   17,   55
    { "TROOC2C8",   21,   53, true }, //   14,   53
    { "TROOC3C7",   19,   50, true }, //   13,   48
    { "TROOC4C6",   14,   49, true }, //   12,   46
    { "TROOC5",     18,   46, true }, //   22,   44
    { "TROOD1",     18,   52, true }, //   16,   52
    { "TROOD2D8",   24,   50, true }, //   17,   50
    { "TROOD3D7",   22,   45, true }, //   19,   43
    { "TROOD4D6",   17,   44, true }, //   17,   41
    { "TROOD5",     18,   43, true }, //   21,   41
    { "TROOE1",     33,   55, true }, //   30,   55
    { "TROOE2E8",   14,   51, true }, //   11,   51
    { "TROOE3E7",   20,   46, true }, //   23,   44
    { "TROOE4E6",   13,   45, true }, //   20,   42
    { "TROOE5",     12,   45, true }, //   17,   43
    { "TROOF1",     21,   50, true }, //   18,   50
    { "TROOF2F8",   28,   49, true }, //   25,   49
    { "TROOF3F7",   27,   46, true }, //   18,   44
    { "TROOF4F6",   23,   45, true }, //   16,   42
    { "TROOF5",     18,   43, true }, //   12,   41
    { "TROOG1",      8,   50, true }, //    5,   50
    { "TROOG2G8",   32,   50, true }, //   25,   50
    { "TROOG3G7",   47,   48, true }, //   27,   46
    { "TROOG4G6",   33,   45, true }, //   23,   42
    { "TROOG5",     22,   46, true }, //   16,   44
    { "TROOH1",     21,   50, true }, //   18,   50
    { "TROOH2H8",   12,   51, true }, //    6,   51
    { "TROOH3H7",   15,   54, true }, //   12,   52
    { "TROOH4H6",   15,   53, true }, //    9,   51
    { "TROOH5",     17,   52, true }, //   21,   52
    { "TROOM0",     27,   16, true }, //   29,   19
    { "TROOO0",     28,   56, true }, //   20,   56
    { "TROOP0",     28,   56, true }, //   24,   56
    { "TROOQ0",     28,   56, true }, //   24,   56
    { "TROOR0",     28,   39, true }, //   24,   39
    { "VILEA3D7",   44,   68, true }, //   41,   68
    { "VILEA4D6",   35,   67, true }, //   31,   67
    { "VILEA5D5",   15,   65, true }, //   11,   65
    { "VILEA6D4",   32,   66, true }, //   30,   66
    { "VILEA7D3",   37,   67, true }, //   36,   67
    { "VILEA8D2",   31,   70, true }, //   35,   70
    { "VILEB4E6",   18,   67, true }, //   22,   67
    { "VILEB5E5",   23,   67, true }, //   18,   67
    { "VILEB6E4",   27,   67, true }, //   25,   67
    { "VILEB7E3",   34,   70, true }, //   31,   70
    { "VILEB8E2",   25,   72, true }, //   23,   72
    { "VILEC4F6",   31,   71, true }, //   26,   71
    { "VILEC6F4",   25,   70, true }, //   22,   70
    { "VILEC7F3",   24,   72, true }, //   21,   72
    { "VILEC8F2",   21,   74, true }, //   25,   74
    { "VILEG2",      3,   91, true }, //   27,   91
    { "VILEG3",     24,   97, true }, //   36,   97
    { "VILEG4",     36,   97, true }, //   39,   97
    { "VILEG5",     44,   99, true }, //   40,   99
    { "VILEG6",     54,   99, true }, //   30,   99
    { "VILEG7",     40,   98, true }, //   28,   98
    { "VILEH2",      4,   93, true }, //   28,   93
    { "VILEH3",     24,   99, true }, //   36,   99
    { "VILEH4",     36,   99, true }, //   43,   99
    { "VILEH5",     45,   99, true }, //   41,   99
    { "VILEH6",     55,   99, true }, //   31,   99
    { "VILEH7",     41,   99, true }, //   29,   99
    { "VILEI2",      4,   94, true }, //   28,   94
    { "VILEI3",     24,   99, true }, //   36,   99
    { "VILEI4",     36,   99, true }, //   43,   99
    { "VILEI5",     45,  101, true }, //   41,  101
    { "VILEI6",     56,   99, true }, //   32,   99
    { "VILEI7",     42,   99, true }, //   30,   99
    { "VILEJ6",     22,   85, true }, //   18,   85
    { "VILEJ8",     30,   78, true }, //   34,   78
    { "VILEK7",     31,   59, true }, //   27,   59
    { "VILEL3",     24,   58, true }, //   28,   58
    { "VILEL5",     23,   57, true }, //   27,   57
    { "VILEL7",     31,   56, true }, //   27,   56
    { "VILEM3",     24,   58, true }, //   28,   58
    { "VILEM5",     23,   57, true }, //   27,   57
    { "VILEM6",     19,   57, true }, //   15,   57
    { "VILEM7",     31,   56, true }, //   27,   56
    { "VILEN2",     57,   65, true }, //   35,   65
    { "VILEN3",     67,   64, true }, //   51,   64
    { "VILEN4",     52,   61, true }, //   43,   61
    { "VILEN5",     23,   64, true }, //   27,   64
    { "VILEN6",     15,   63, true }, //   26,   63
    { "VILEN7",     30,   63, true }, //   45,   63
    { "VILEN8",     31,   63, true }, //   48,   63
    { "VILEO2",     56,   71, true }, //   34,   71
    { "VILEO3",     67,   65, true }, //   51,   65
    { "VILEO4",     52,   62, true }, //   43,   62
    { "VILEO5",     23,   64, true }, //   27,   64
    { "VILEO6",     15,   63, true }, //   26,   63
    { "VILEO7",     30,   63, true }, //   45,   63
    { "VILEO8",     31,   66, true }, //   48,   66
    { "VILEP2",     56,   83, true }, //   34,   83
    { "VILEP3",     67,   85, true }, //   51,   85
    { "VILEP4",     51,   77, true }, //   42,   77
    { "VILEP5",     23,   77, true }, //   27,   77
    { "VILEP6",     15,   77, true }, //   26,   77
    { "VILEP7",     30,   76, true }, //   45,   76
    { "VILEP8",     31,   79, true }, //   48,   79
    { "VILEQ2",     20,   69, true }, //   22,   69
    { "VILEQ3",     36,   67, true }, //   32,   67
    { "VILEQ4",     29,   69, true }, //   27,   69
    { "VILEQ7",     29,   68, true }, //   30,   68
    { "VILEQ8",     31,   66, true }, //   33,   66
    { "VILES0",     21,   71, true }, //   23,   71
    { "VILET0",     26,   66, true }, //   27,   66
    { "VILEU0",     31,   54, true }, //   35,   54
    { "VILE[1",     50,   68, true }, //   53,   68
    { "VILE[2",     53,   69, true }, //   49,   69
    { "VILE[3",     31,   72, true }, //   26,   72
    { "VILE[4",     49,   71, true }, //   37,   71
    { "VILE[5",     52,   71, true }, //   44,   71
    { "VILE[6",     32,   71, true }, //   43,   73
    { "VILE[7",     19,   70, true }, //   30,   73
    { "VILE[8",     29,   69, true }, //   36,   73
    { "VILE\\1",    50,   69, true }, //   53,   69
    { "VILE\\2",    53,   70, true }, //   49,   70
    { "VILE\\3",    31,   73, true }, //   26,   73
    { "VILE\\4",    49,   71, true }, //   37,   71
    { "VILE\\5",    52,   72, true }, //   44,   72
    { "VILE\\6",    32,   72, true }, //   43,   74
    { "VILE\\7",    19,   69, true }, //   30,   72
    { "VILE\\8",    29,   69, true }, //   32,   73
    { "VILE]1",     50,   68, true }, //   53,   68
    { "VILE]2",     53,   69, true }, //   49,   69
    { "VILE]3",     31,   71, true }, //   26,   71
    { "VILE]4",     49,   70, true }, //   37,   70
    { "VILE]5",     52,   70, true }, //   44,   70
    { "VILE]6",     32,   70, true }, //   43,   72
    { "VILE]7",     19,   71, true }, //   30,   74
    { "VILE]8",     29,   67, true }, //   32,   71
    { "YKEYA0",      7,   14, true }, //    8,   19
    { "YKEYB0",      7,   14, true }, //    8,   19
    { "YSKUA0",      7,   14, true }, //    7,   18
    { "YSKUB0",      7,   14, true }, //    7,   18
    { "",            0,    0, true }
};
