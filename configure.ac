#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

# Perlude
AC_PREREQ([2.69])
AC_INIT([YiCppLib::BayesGenotype], [1.0.0], [atrusqiao@gmail.com])
AC_CONFIG_AUX_DIR([build-aux])
AC_CONFIG_MACRO_DIR([m4])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])

# Fixing file creation time
find ${srcdir} -name aclocal.m4 -exec touch {} \;
find ${srcdir} -name \*.in -exec touch {} \;
find ${srcdir} -name configure -exec touch {} \;

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AM_PROG_AR
LT_PREREQ([2.2])
LT_INIT([disable-shared])
AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11([noext], [mandatory])

AC_CHECK_PROG([dot], [dot], [yes], [no])
AM_CONDITIONAL([FOUND_DOT], [test "x$dot" = xyes])
AM_COND_IF([FOUND_DOT],,[AC_MSG_WARN([Graphviz dot utility not found. Document compiling disabled])])

AC_CONFIG_SRCDIR([src/Genotyper.cc])
AC_CONFIG_HEADERS([config.h])

# Checks for libraries.

## START: CHECKING FOR GSL ##
AC_ARG_WITH([gsl],
			[AS_HELP_STRING([--with-gsl=DIR], 
							[specify the path to search for gnu scientific library])],
							[gsl_path=${withval}])

if test "x${gsl_path}" != x -a -x "${gsl_path}/bin/gsl-config"; then
	GSL_LDADDS=`${gsl_path}/bin/gsl-config --libs` 
	GSL_CPPFLAGS=`${gsl_path}/bin/gsl-config --cflags`
elif test -x "$(which gsl-config)"; then
	GSL_LDADDS=`gsl-config --libs` 
	GSL_CPPFLAGS=`gsl-config --cflags`
else
	AC_MSG_ERROR([Unable to locate gsl-config. Make sure gsl is installed (if not in search path, use --with-gsl=<path>)])
fi

LDADDS+=" ${GSL_LDADDS}"
CPPFLAGS+=" ${GSL_CPPFLAGS}"

have_gsl=yes
AC_CHECK_LIB([gsl], [gsl_ran_multinomial_pdf], [], [have_gsl=no], [${GSL_LDADDS}])
AC_CHECK_LIB([gsl], [gsl_multiset_calloc], [], [have_gsl=no], [${GSL_LDADDS}])
AC_CHECK_LIB([gsl], [gsl_multiset_next], [], [have_gsl=no], [${GSL_LDADDS}])
AC_CHECK_LIB([gsl], [gsl_multiset_free], [], [have_gsl=no], [${GSL_LDADDS}])

AC_CHECK_HEADERS([gsl/gsl_multiset.h gsl/gsl_randist.h], [], [have_gsl=no])

AM_CONDITIONAL([FOUND_GSL], [test "x${have_gsl}" == xyes])
AM_COND_IF([FOUND_GSL], [
			AC_SUBST([GSL_LDADDS], [${GSL_LDADDS}])
			AC_SUBST([GSL_CPPFLAGS], [${GSL_CPPFLAGS}])], 
			[AC_MSG_ERROR([Unable to locate usable gsl library. If you have a custom built version, supply the path with --with-gsl=<path>])])
## END: CHECKINF FOR GSL ##

## START: CHECKING FOR GMOCK ##
AC_ARG_WITH([gmock],
			[AS_HELP_STRING([--with-gmock=DIR],
							[specify the path to search for gmock])],
							[gmock_path=${withval}])
if test "x${gmock_path}" != x -a -x "${gmock_path}/scripts/gmock-config"; then
	GMOCK_CONFIG="${gmock_path}/scripts/gmock-config"
	have_gmock_config=yes
elif test -x "$(which gmock-config)"; then
	GMOCK_CONFIG="gmock-config"
	have_gmock_config=yes
else
	AC_MSG_WARN([Unable to locate gmock-config. Testing is disabled. If your gmock-config is not in search path, use --with-gmock=<path> ])
	have_gmock_config=no
fi


if test "x${have_gmock_config}" == xyes; then
	GMOCK_CPPFLAGS=`${GMOCK_CONFIG} --cppflags`
	GMOCK_CXXFLAGS=`${GMOCK_CONFIG} --cxxflags`
	GMOCK_LDFLAGS=`${GMOCK_CONFIG} --ldflags`
	GMOCK_LDADDS=`${GMOCK_CONFIG} --libs`
fi

CPPFLAGS+=" ${GMOCK_CPPFLAGS}"
CXXFLAGS+=" ${GMOCK_CXXFLAGS}"

echo "checking for gmock in ${gmock_path}"

AC_CHECK_HEADERS([gmock/gmock.h, gtest/gtest.h], [have_gmock=yes], [have_gmock=no])

AM_CONDITIONAL([FOUND_GMOCK], [test "x${have_gmock}" == xyes])
AM_CONDITIONAL([FOUND_GTEST], [test "x${have_gtest}" == xyes])

AM_COND_IF([FOUND_GMOCK], [
			AC_SUBST([GMOCK_CPPFLAGS], [${GMOCK_CPPFLAGS}])
			AC_SUBST([GMOCK_CXXFLAGS], [${GMOCK_CXXFLAGS}])
			AC_SUBST([GMOCK_LDFLAGS], [${GMOCK_LDFLAGS}])
			AC_SUBST([GMOCK_LDADDS], [${GMOCK_LDADDS}])
			], [AC_MSG_WARN([Unable to locate gmock header, testing disabled])])
## END: CHECKINF FOR GMOCK ##


# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
				 src/Makefile
				 doc/Makefile
				 test/Makefile])

AC_OUTPUT
