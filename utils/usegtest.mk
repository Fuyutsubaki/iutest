#
# usegtest.mk
#
# Copyright (C) 2017, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

ifdef GTEST_ROOT

GTEST_ROOT_=$(subst \,/,$(GTEST_ROOT))
ifeq ($(shell test -e $(GTEST_ROOT_)/googletest/include && echo -n yes), yes)
GTEST_ROOT_=$(GTEST_ROOT_)/googletest
endif

endif

ifdef GMOCK_ROOT

GMOCK_ROOT_=$(subst \,/,$(GMOCK_ROOT))
ifeq ($(shell test -e $(GMOCK_ROOT_)/googlemock/include && echo -n yes), yes)
GMOCK_ROOT_=$(GMOCK_ROOT_)/googlemock
endif

ifndef GTEST_ROOT_

ifeq ($(shell test -e $(GMOCK_ROOT_)/gtest/include && echo -n yes), yes)
GTEST_ROOT_=$(GMOCK_ROOT_)/gtest
endif

ifeq ($(shell test -e $(GMOCK_ROOT_)/googletest/include && echo -n yes), yes)
GTEST_ROOT_=$(GMOCK_ROOT_)/googletest
endif

endif

endif

#
# Use Google Test
#
ifdef USE_GTEST

ifdef GTEST_ROOT_

GTEST_INC_=-I$(GTEST_ROOT_)/include
#GTEST_LIB_=$(GTEST_ROOT_)/make/gtest.a
GTEST_LIB_=$(GTEST_ROOT_)/make/gtest-all.o

else

GTEST_INC_=
GTEST_LIB_=-lgtest -lpthread

endif

LDFLAGS += $(GTEST_LIB_)
CXXFLAGS += -DIUTEST_USE_GTEST -DIUTEST_HAS_SOCKET=0 $(NO_UNUSED_LOCAL_TYPEDEFS) -Wno-sign-compare $(GTEST_INC_)

endif

#
# Use Google Mock
#

ifdef USE_GMOCK

ifdef GTEST_ROOT_

ifndef GMOCK_ROOT_

ifeq ($(shell test -e $(GTEST_ROOT_)/../googlemock/include && echo -n yes), yes)
GMOCK_ROOT_=$(GTEST_ROOT_)/../googlemock
endif

endif

endif


ifdef GMOCK_ROOT_

GMOCK_INC_=-I$(GMOCK_ROOT_)/include -I$(GTEST_ROOT_)/include
GMOCK_LIB_=$(GMOCK_ROOT_)/make/gmock-all.o $(GMOCK_ROOT_)/make/gtest-all.o

else

GMOCK_INC_=
GMOCK_LIB_=-lgmock -lgtest -lpthread

endif

LDFLAGS += $(GMOCK_LIB_)
CXXFLAGS += -DIUTEST_USE_GTEST -DIUTEST_USE_GMOCK -DIUTEST_HAS_SOCKET=0 $(NO_UNUSED_LOCAL_TYPEDEFS) $(GMOCK_INC_)

endif

