GMOCK_DIR = @GMOCK_DIR@
GTEST_DIR = @GTEST_DIR@

GSL_CPPFLAGS = @GSL_CPPFLAGS@
GSL_LDADDS = @GSL_LDADDS@
GMOCK_CPPFLAGS = @GMOCK_CPPFLAGS@
GMOCK_CXXFLAGS = @GMOCK_CXXFLAGS@
GMOCK_LDFLAGS = @GMOCK_LDFLAGS@
GMOCK_LDADDS = @GMOCK_LDADDS@

AM_LDFLAGS = -all-static

AM_CPPFLAGS = -I$(srcdir)/../src ${GSL_CPPFLAGS} ${GMOCK_CPPFLAGS} ${GMOCK_CXXFLAGS}
LDADD = ../src/libyi_bayesgenotype.la ${GSL_LDADDS} ${GMOCK_LDFLAGS} ${GMOCK_LDADDS} -lgmock_main

#if CUSTOM_GMOCK_PATH
#AM_CPPFLAGS += -isystem ${GMOCK_DIR}/include \
#			   -I${GMOCK_DIR} \
#			   -isystem ${GTEST_DIR}/include \
#			   -I${GTEST_DIR}
#
#LDADD += ${GMOCK_DIR}/lib/libgmock.la \
#		 ${GTEST_DIR}/lib/libgtest.la \
#		 ${GMOCK_DIR}/lib/libgmock_main.la
#else
#LDADD += -lgmock -lgtest -lgmock_main
#endif

## -- below to be changed -- ##

TESTS = testSingleNtAlleleAlphabet \
		testSingleSample

check_PROGRAMS = ${TESTS}
testSingleNtAlleleAlphabet_SOURCES=testSingleNtAlleleAlphabet.cc
testSingleSample_SOURCES=testSingleSample.cc
