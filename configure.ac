AC_INIT([libqt4json], [1.1.0-beta1], [corentin.lebail@gmail.com],,[https://sourceforge.net/projects/libqt4json/]) 

LT_INIT
LT_LANG([C++])

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE()

AC_PROG_CC
AC_PROG_CXX
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

AC_CONFIG_MACRO_DIR([m4])

AC_CONFIG_FILES([Makefile src/Makefile src/libqt4json.pc src/example/Makefile])

AC_CHECK_PROG(LRELEASE, lrelease-qt4, lrelease-qt4)
if test x$LRELEASE = x; then
	AC_CHECK_PROG(LRELEASE, lrelease, lrelease)
	if test x$LRELEASE = x ; then
		AC_MSG_ERROR([lrelease not found! Make sure you have Qt-devel-tools installed!])
	fi
fi

AC_CHECK_PROG(MOC, moc-qt4, moc-qt4)
if test MOC = x; then
	AC_CHECK_PROG(MOC, moc, moc)
	if test MOC = x ; then
		AC_MSG_ERROR([moc not found! Make sure you have Qt-devel-tools installed!])
	fi
fi

PKG_CHECK_MODULES([QT4], [QtCore QtGui])
PKG_CHECK_MODULES([LIBJSON], [json-c])

AC_OUTPUT
