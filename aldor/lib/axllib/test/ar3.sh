#!/bin/sh
#
# This script tests importing from archives of compiler libraries. 

# If ${TMPDIR} is not defined, just use /tmp.
TMPDIR=${TMPDIR-/tmp}

rm -rf $TMPDIR/lib
mkdir $TMPDIR/lib

if [ "`platform | sed -e "s/.*msvc.*/y/g"`" = "y" ]; then
	ALDOR=aldor.sh
	LM=
else
	ALDOR=aldor
	LM=-lm
fi

echo '== Compiling triv*.as into triv*.ao and triv*.o'
$ALDOR -Mno-ALDOR_W_CantUseArchive $LM -l axllib -R $TMPDIR -F ao -F o triv*.as 2>&1 | grep -v "GC:" | grep -v "warning: conflicting types for built-in function"

echo '== Building an archive containing triv*.ao'
${AR} cr $TMPDIR/lib/libtriv.al $TMPDIR/triv*.ao
rm -f $TMPDIR/triv*.ao

echo '== Building an archive containing triv*.o'
PL=`platform|tr "\r" " "`
if [ "$PL" = "win32msvc - Win32 [+] " ]; then
	lib /nologo /out:`cygpath -m $TMPDIR`/lib/libtriv.lib `cygpath -m $TMPDIR`/triv*.obj
else
	${AR} cr $TMPDIR/lib/libtriv.a $TMPDIR/triv*.o
	ranlib $TMPDIR/lib/libtriv.a
fi

rm -f $TMPDIR/triv*.obj

echo '== Creating a client for the archive'
cat << END_libarch.as > $TMPDIR/libarch.as

-- A minimal program depending on archives of compiler libraries

#library Triv "triv4.ao"

import from Triv;

printTriv();

END_libarch.as

echo '== Testing that the client imports from the archive'
cd $TMPDIR
$ALDOR -Mno-ALDOR_W_CantUseArchive $LM -l axllib -Grun -Y $TMPDIR/lib -ltriv $TMPDIR/libarch.as

echo '== Done'
