bin_PROGRAMS = hello
hello_SOURCES = main.c
hello_CPPFLAGS = -I lib1/
hello_LDFLAGS = -lmygoodbye

lib_LTLIBRARIES = libmyhello.la
libmyhello_la_SOURCES = lib/mylib.c
include_HEADERS = lib/mylib.h

lib_LTLIBRARIES += libmygoodbye.la
libmygoodbye_la_SOURCES = lib1/mylib1.c
include_HEADERS = lib1/mylib1.h
libmygoodbye_la_LDFLAGS = -lmyhello


libmygoodbye_la_CPPFLAGS = -I lib/

