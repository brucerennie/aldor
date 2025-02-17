/*****************************************************************************
 *
 * of_util.h: Foam-to-foam optimizaion utililities.
 *
 * Copyright (c) 1990-2007 Aldor Software Organization Ltd (Aldor.org).
 *
 ****************************************************************************/

#ifndef _OF_UTIL_H_
#define _OF_UTIL_H_

#include "axlobs.h"
#include "priq.h"

typedef enum {
	INL_NotInlined,
	INL_BeingInlined,
	INL_Inlined
} InlineState;

typedef enum {
	DV_NotChecked,
	DV_Checked
} DeadVarState;

typedef enum usageState {
	DV_Unused,
	DV_DefinedNoSdEfx, 
	DV_DefinedSdEfx,
	DV_Keep,
	DV_Used
} UsageState;

typedef struct dvUsageStruct {
	UsageState	used;
	int		newIndex;
} *DvUsage;


typedef struct varPool {
	FoamBox		fbox;
	AIntList	vars[FOAM_LIMIT];
} *VarPool;




/* Functions for temporary variable pools. */
extern  VarPool	  	vpNew		(FoamBox);
extern  void	  	vpFree	  	(VarPool);
extern  int	  	vpNewVarDecl	(VarPool, Foam);
extern  int	  	vpNewVar0	(VarPool, FoamTag, int);
extern  void	  	vpFreeVar	(VarPool, int);

# define vpNewVar(pool, type)  vpNewVar0((pool), (type), (emptyFormatSlot))
# define fboxSize(fbox)		((fbox)->argc)

/*****************************************************************************
 *
 * :: Flags for -W runtime.
 *
 ****************************************************************************/

extern Bool		gen0IsRuntime;

#define			genIsRuntime()			(gen0IsRuntime)
#define			genSetRuntime()			(gen0IsRuntime = true)

extern Bool		inl0AfterInline;

#define			inlAfterInline()		(inl0AfterInline)
#define			inlSetAfterInline()		(inl0AfterInline=true)

/*****************************************************************************
 *
 * :: Flags for -W runtime-hashcheck
 *
 ****************************************************************************/

extern Bool		gen0Hashcheck;

#define			genHashcheck()			(gen0Hashcheck)
#define			genSetHashcheck()		(gen0Hashcheck = true)

/*****************************************************************************
 *
 * :: Foam Patching
 *
 ****************************************************************************/

void	fpPatchUnit		(Foam unit);

/*****************************************************************************
 *
 * :: Make Flat Sequences
 *
 ****************************************************************************/

Foam		utilMakeFlatSeq		(Foam);
void            utilMakeFlatFlog	(FlowGraph);

/*****************************************************************************
 *
 * :: General Utility
 *
 ****************************************************************************/


#endif /* !_OF_UTIL_H_ */
