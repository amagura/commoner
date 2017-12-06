## Process this file with automake to produce Makefile.in ##

lib_LTLIBRARIES = libcommoner.la
libcommoner_la_SOURCES = commoner.c
libcommoner_la_LDFLAGS = -version-info '0:0:0'
include_HEADERS = commoner.h

AM_CFLAGS =
AM_CPPFLAGS =
AM_LDFLAGS =

if DEBUG
AM_CFLAGS += -g -ggdb
endif

clean-local:
