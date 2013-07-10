#!/bin/sh
if [ "$GmpDir" = "" ] 
then echo "no GmpDir defined -- the linker will fail unless the GMP library is in a well-known place"
dir="" 
else dir="-Y $GmpDir"
fi
$ALDORROOT/bin/axiomxl $dir -Cruntime=foam-gmp,gmp $*
