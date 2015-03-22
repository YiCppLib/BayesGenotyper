GSL_CPPFLAGS = @GSL_CPPFLAGS@
GSL_LDADDS = @GSL_LDADDS@
GMOCK_CPPFLAGS = @GMOCK_CPPFLAGS@
GMOCK_CXXFLAGS = @GMOCK_CXXFLAGS@
GMOCK_LDFLAGS = @GMOCK_LDFLAGS@
GMOCK_LDADDS = @GMOCK_LDADDS@

AM_CPPFLAGS = -I$(srcdir)/../src ${GSL_CPPFLAGS} ${GMOCK_CPPFLAGS} ${GMOCK_CXXFLAGS}
AM_LDFLAGS = -all-static ${GMOCK_LDFLAGS}
LDADD = ../src/libyi_bayesgenotype.la ${GSL_LDADDS} ${GMOCK_LDADDS} -lgmock_main

PLANNED_TESTS = testSingleNtAlleleAlphabet \
				testSingleSample

if FOUND_GMOCK
TESTS = ${PLANNED_TESTS}
endif

check_PROGRAMS = ${TESTS}
testSingleNtAlleleAlphabet_SOURCES=testSingleNtAlleleAlphabet.cc
testSingleSample_SOURCES=testSingleSample.cc


