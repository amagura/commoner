## Process this file with automake to produce Makefile.in ##

lib_LTLIBRARIES = libcommoner.la
libcommoner_la_SOURCES = common.c
libcommoner_la_LDFLAGS = -version-info '0:0:0'
include_HEADERS = commoner.h


commoner.h:
	cp common.h commoner.h

clean-local:
	$(RM) commoner.h
