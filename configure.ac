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

if test "x${gsl_path}" != x; then
	if test -e ${gsl_path}/lib; then LDFLAGS+=" -L${gsl_path}/lib"; fi
	if test -e ${gsl_path}/include; then CPPFLAGS+=" -I${gsl_path}/include"; fi
fi

echo "checking for gsl in ${gsl_path}"

have_gsl=no

AC_SEARCH_LIBS([gsl_cdf_binomial_Q], [gsl], [have_gsl=yes], [have_gsl=no])

if test "x${have_gsl}" = xyes; then
	AC_CHECK_HEADERS([gsl/gsl_cdf.h], [], [have_gsl=no])
fi

if test "x${have_gsl}" = xno; then
	AC_MSG_ERROR([Unable to locate gsl])
fi
## END: CHECKINF FOR GSL ##

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
				 src/Makefile
				 doc/Makefile
				 test/Makefile])

AC_OUTPUT
