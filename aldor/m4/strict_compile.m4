# Define warnings based on compiler (and version)

AC_DEFUN([ALDOR_CC_OPTION],
[AC_MSG_CHECKING($CC supports $1); echo "$3" > conftest$1.c;
 res=no
 if $CC -Werror $1 -c conftest$1.c > /dev/null 2>&1; then $2="$1"; res=yes; fi;
 AC_MSG_RESULT($res)])

AC_DEFUN([ALDOR_STRICT_COMPILE],
  [AC_MSG_CHECKING(Strict options for C compiler)
   ALDOR_CC_OPTION(-Wno-error=shift-negative-value,cfg_no_shift_negative_value,int main() { return -1 << 1; })
   ALDOR_CC_OPTION(-Wno-sign-compare, cfg_no_sign_compare)
   ALDOR_CC_OPTION(-Wno-deprecated-non-prototype, cfg_no_deprecated_non_prototype)
   ALDOR_CC_OPTION(-Wno-strict-prototypes, cfg_no_strict_prototypes)

   cfgSTRICTCFLAGS="-pedantic -std=c99 -Wall -Wextra -Werror -Wno-empty-body -Wno-enum-compare \
                    -Wno-missing-field-initializers -Wno-unused -Wno-unused-parameter \
		    -Wno-error=format -Wno-error=type-limits -Wno-error=strict-aliasing \
		    $cfg_no_sign_compare $cfg_no_shift_negative_value"
   case "${CC}" in
       gcc*)
             cfgSTRICTCFLAGS="${cfgSTRICTCFLAGS} -Wno-error=clobbered"
	     ;;
       clang*)
             cfgSTRICTCFLAGS="${cfgSTRICTCFLAGS} -fcolor-diagnostics -Wno-error=enum-conversion \
				-Wno-error=tautological-compare -Wno-parentheses-equality \
				$cfg_no_deprecated_non_prototype \
				$cfg_no_strict_prototypes"
	     ;;
       *)
             AC_MSG_WARN(Unknown C compiler ${CC})
             cfgSTRICTCFLAGS="";;
    esac
   AC_MSG_RESULT(${CC})])

AC_DEFUN([ALDOR_LIB_COMPILE],
	[AC_MSG_CHECKING([Options for build library ..])
	 ALDOR_CC_OPTION(-Wno-int-conversion,cfg_no_int_conversion, int main() { return 1; })
	 ALDOR_CC_OPTION(-Wno-builtin-declaration-mismatch,cfg_no_builtin_mismatch, int main() { return 1; })
	 ALDOR_CC_OPTION(-Wno-incompatible-pointer-types,cfg_no_incompatible_pointer_types, int main() { return 1; })
	 LIB_CC_FLAGS="${cfg_no_builtin_mismatch} ${cfg_no_incompatible_pointer_types} ${cfg_no_deprecated_non_prototype}"
	 AC_SUBST(LIB_CC_FLAGS)
	 ])
