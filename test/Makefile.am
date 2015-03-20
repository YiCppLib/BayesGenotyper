GMOCK_DIR = @GMOCK_DIR@
GTEST_DIR = @GTEST_DIR@

AM_LDFLAGS = -all-static

AM_CPPFLAGS = -I$(srcdir)/../src
LDADD = ../src/libyi_bayesgenotype.la

if CUSTOM_GMOCK_PATH
AM_CPPFLAGS += -isystem ${GMOCK_DIR}/include \
			   -I${GMOCK_DIR} \
			   -isystem ${GTEST_DIR}/include \
			   -I${GTEST_DIR}

LDADD += ${GMOCK_DIR}/lib/libgmock.la \
		 ${GTEST_DIR}/lib/libgtest.la \
		 ${GMOCK_DIR}/lib/libgmock_main.la 

endif

## -- below to be changed -- ##

TESTS = testSingleNtAlleleAlphabet \
		testSingleSample

check_PROGRAMS = ${TESTS}
testSingleNtAlleleAlphabet_SOURCES=testSingleNtAlleleAlphabet.cc
testSingleSample_SOURCES=testSingleSample.cc
