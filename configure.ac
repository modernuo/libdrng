AC_INIT([libdrng], [1.0], [Intel Software Network])

AC_PROG_CC([icc gcc])

if test "x$CC" = "xgcc"
then
	AC_MSG_CHECKING([if gcc knows the rdrand instruction])
	AC_TRY_COMPILE([], [
		asm("rdrand %eax;");
	], AC_DEFINE([HAVE_RDRAND_IN_GCC],[],[Check for rdrand instruction]) AC_MSG_RESULT([yes]), AC_MSG_RESULT([no]))
fi

if test "x$CC" = "xgcc"
then
	AC_MSG_CHECKING([if gcc knows the rdseed instruction])
	AC_TRY_COMPILE([], [
		asm("rdseed %eax;");
	], AC_DEFINE([HAVE_RDSEED_IN_GCC],[],[Check for rdseed instructions]) AC_MSG_RESULT([yes]), AC_MSG_RESULT([no]))
fi

AC_CHECK_HEADERS([inttypes.h])

AC_CONFIG_FILES([Makefile])

AC_CONFIG_HEADERS([config.h])

AC_OUTPUT


