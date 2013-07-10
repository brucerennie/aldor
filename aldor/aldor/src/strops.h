/*****************************************************************************
 *
 * strops.h: String manipulations which can allocate.
 *
 * Copyright (c) 1990-2007 Aldor Software Organization Ltd (Aldor.org).
 *
 ****************************************************************************/

/*
 * This file is called "strops.h" since on some systems it is not possible
 * to have both "string.h" and <string.h>.
 */

#ifndef _STROPS_H_
#define _STROPS_H_

# include "axlport.h"

extern String           strOfChars      (char *);
#define                 strChars(s)     (s)

extern Length           strLength       (String);
extern Length		strUntabLength	(String, Length tabstop);
	
extern String           strCopy         (String);
extern String           strnCopy        (String s, Length n);
extern String		strCopyIf	(String);
 			/*
			 * strCopy   allocates store and copies its argument.
			 * strnCopy  same but copies at most n characters.
			 * strCopyIf same but returns 0 if its argument was 0.
			 */

extern String           strConcat       (String, String);
extern String           strlConcat      (String, ...);
			/*
			 * These functions allocate a new string
			 * and concatenate the arguments into it.
			 * strlConcat's argument list is terminated by a 0.
			 *
			 * E.g., r = strlConcat(s1, s2, ..., sn, NULL)
			 */

extern String           strPrintf  (const char *, ...);
extern String           strVPrintf (const char *, va_list);
			/*
			 * Allocate a new string and print into it.
			 */
extern String           strAlloc        (Length);
extern void             strFree         (String);
extern String           strResize       (String, Length);

extern Bool             strEqual        (String, String); /* case-sensitive  */
extern Bool		strAEqual	(String, String); /* case-insensitive*/

extern Hash             strHash         (String);	  /* case-sensitive  */
extern Hash             strSmallHash    (String);	  /* less filling  */
extern Hash             strAHash        (String);	  /* case-insensitive*/

extern Length           strMatch        (String, String);
extern Length           strAMatch       (String, String);

extern String           strIsPrefix     (String pre, String);
extern String		strAIsPrefix	(String pre, String);

extern String           strIsSuffix     (String suf, String);
extern String           strAIsSuffix    (String suf, String);

extern String		strUpper	(String);
extern String		strLower	(String);

extern String		strnToAsciiStatic(String, Length);
extern String		strnFrAsciiStatic(String, Length);

extern int		strPrint	(FILE *, String,
					 int oq, int cq,
					 int e, const char *fmt);
			/*
			 * Print string with quotes (oq, cq) and escape
			 * character e.  fmt is used to print the unprintables.
			 * The character count is returned.
			 */

#endif /* !_STROPS_H_ */
