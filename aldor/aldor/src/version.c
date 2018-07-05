/*****************************************************************************
 *
 * version.c: Compiler version number.
 *
 * Copyright (c) 1990-2007 Aldor Software Organization Ltd (Aldor.org).
 *
 ****************************************************************************/

#include "axlobs.h"
#include "opsys.h"
#include "version.h"
#include "comsg.h"
#include "strops.h"

/*
 * The version of this program.
 */

#ifndef VCSVERSION
#define VCSVERSION ""
#endif

CString	verName		= "Aldor";

int	verMajorVersion	=  1;
int	verMinorVersion	=  3;
int	verMinorFreeze	=  0;
CString	verPatchLevel	= VCSVERSION;
