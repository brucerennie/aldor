/*****************************************************************************
 *
 * format.h: Code for prettyprinting.
 *
 * Copyright (c) 1990-2007 Aldor Software Organization Ltd (Aldor.org).
 *
 ****************************************************************************/

#ifndef _FORMAT_H_
#define _FORMAT_H_

# include "axlport.h"

extern int  findent;
extern int  fnewline    (FILE *f);

/*
 * xprintf takes a function to put the characters.
 *
 * The XPutFun consumes at most n characters of s and returns the count.
 * If n == -1 no limit is imposed.
 * A null function pointer computes the count without doing output.
 */
typedef int (*XPutFun)  (const char *s, int n);

extern  int  xprintf	(XPutFun f, const char *fmt, ...);
extern  int  vxprintf	(XPutFun f, const char *fmt, va_list argp);
#endif
