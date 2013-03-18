AC_INIT([libqt4json], [1.0.0-prealpha1], [corentin.lebail@gmail.com],,[https://sourceforge.net/projects/libqt4json/]) 

LT_INIT
LT_LANG([C++])

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE()

AC_PROG_CC
AC_PROG_CXX
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_FILES([Makefile src/Makefile src/example/Makefile])

AC_CHECK_PROG(LRELEASE, lrelease-qt4, lrelease-qt4)
if test x$LRELEASE = x; then
	AC_CHECK_PROG(LRELEASE, lrelease, lrelease)
	if test x$LRELEASE = x ; then
		AC_MSG_ERROR([lrelease not found! Make sure you have Qt-devel-tools installed!])
	fi
fi

AC_CHECK_PROG(FLEX, flex, flex)
if test x$FLEX = x ; then
	AC_MSG_ERROR([flex not found! Make sure you have flex installed!])
fi

AC_CHECK_PROG(BISON, bison, bison)
if test x$BISON = x ; then
	AC_MSG_ERROR([bison not found! Make sure you have bison installed!])
fi

PKG_CHECK_MODULES([QT4], [QtCore])

AC_OUTPUT
