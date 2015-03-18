GMOCK_DIR = /opt/gmock-1.7.0
GTEST_DIR = ${GMOCK_DIR}/gtest

AM_LDFLAGS = -all-static

AM_CPPFLAGS = -isystem ${GMOCK_DIR}/include \
			  -I${GMOCK_DIR} \
			  -isystem ${GTEST_DIR}/include \
			  -I${GTEST_DIR} \
			  -I$(srcdir)/../src

LDADD = ../src/libyi_bayesgenotype.la \
		${GMOCK_DIR}/lib/libgmock.la \
		${GTEST_DIR}/lib/libgtest.la \
		${GMOCK_DIR}/lib/libgmock_main.la \
		-lz

## -- below to be changed -- ##

TESTS = testSingleSample

check_PROGRAMS = ${TESTS}
testSingleSample_SOURCES=testSingleSample.cc
