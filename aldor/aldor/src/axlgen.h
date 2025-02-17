/*****************************************************************************
 *
 * axlgen.h: General library, not specific to Aldor.
 *
 * Copyright (c) 1990-2007 Aldor Software Organization Ltd (Aldor.org).
 *
 ****************************************************************************/

#ifndef _AXLGEN_H_
#define _AXLGEN_H_

/*
 * Declarations for basic types and functions.
 * Defining FOAM_RTS gives only those needed for store.c and bigint.c.
 */

#include "axlgen0.h"
#include "list.h"
#include "table.h"
#include "ttable.h"

#define OB_Other		0
#define OB_Bogus		1

#define OB_BInt			2
#define OB_BTree		3

#define OB_Bitv			4
#define OB_Buffer		5
#define OB_List			6
#define OB_String		7
#define OB_Symbol		8
#define OB_Table		9
#define OB_DNF			10

#define OB_CCode		11
#define OB_JCode		12
#define OB_SExpr		13
#define OB_AXLGEN_LIMIT		14

/* Forward declarations for general library types. */
typedef struct fileName *          FileName;
typedef ULong			   SrcPos;
typedef struct sposCell	*	   SrcPosCell;
typedef union  sposStack           SrcPosStack;
typedef union  SExprUnion *        SExpr;
typedef struct bint *              BInt;
typedef union  ccode *             CCode;

/* Lists of general library types. */
DECLARE_LIST(FileName);
DECLARE_LIST(AInt);

#endif /* !_AXLGEN_H_ */
