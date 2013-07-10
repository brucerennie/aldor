#!/bin/sh
#
# doaldor $(FILE) $(AXLFLAGS)
#
# example:  doaldor lang.as

# AXIOMXLROOT is taken from the environment.

FILE="$1"
shift
AXLFLAGS="$*"

# Environment
PWD=`pwd`
LIBDIR=$PWD/lib
LAXL=$LIBDIR/libaxllib.al
AEFLAGS="-Q3 -Qinline-all -Fao ${AXLFLAGS}"
AXLFLAGS="-R${LIBDIR} ${AEFLAGS} -M no-ALDOR_W_OverRideLibraryFile"

ARFLAGS="rv"
TMPDIR=/tmp/`basename $0`.$$
mkdir $TMPDIR
export TMPDIR

if [ "$MACHINE" = "win32msvc" ]; then
	ALDOR="$ALDORROOT/bin/aldor.sh"
	UNICL="$ALDORROOT/bin/unicl.sh"
	LIBEXT="lib"
	OBJ="obj"
	LOB=$LIBDIR/libaxllib.$LIBEXT
	#AR="lib"
	#ARFLAGS="/nologo `cygpath -m $LIBA`"
	#ARFLAGSFIRST="/nologo /OUT:`cygpath -m $LIBA`"
	AR="ar"
elif [ "$MACHINE" = "win32gcc" ]; then
	ALDOR="$ALDORROOT/bin/aldor.sh"
	UNICL="$ALDORROOT/bin/unicl.sh"
	LIBEXT="a"
	OBJ="o"
	LOB=$LIBDIR/libaxllib.$LIBEXT
	AR="ar"
else
	ALDOR="$ALDORROOT/bin/aldor"
	UNICL="$ALDORROOT/bin/unicl"
	LIBEXT="a"
	OBJ="o"
	LOB=$LIBDIR/libaxllib.$LIBEXT
	AR="ar"
fi

ARR="${AR} ${ARFLAGS}"
RM="rm -f"

# Remove the ao file from the library, compile the file, update the libraries.

echo "${ALDOR} ${AEFLAGS} ${FILE}"

if ${ALDOR} ${AXLFLAGS} ${FILE}
then
	cd $LIBDIR
	FILEPREF=$LIBDIR/`basename $FILE .as`

	${ARR} ${LAXL} ${FILEPREF}.ao
#	${ARR} ${LOB} ${FILEPREF}.$OBJ
	${RM} ${FILEPREF}.ao
# ${FILEPREF}.$OBJ
	rm -rf $TMPDIR
else
	status=$?
	rm -rf $TMPDIR
	exit $status # $? (martin@nag)
fi

