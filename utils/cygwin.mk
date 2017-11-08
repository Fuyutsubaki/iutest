#
# cygwin.mk
#
# Copyright (C) 2017, Takazumi Shirayanagi
# This software is released under the new BSD License,
# see LICENSE
#

ifeq ($(findstring CYGWIN, $(shell uname)), CYGWIN)
IUTEST_MKFLAG_CYGWIN=1
else
IUTEST_MKFLAG_CYGWIN=0
endif

