bin_PROGRAMS = example

AM_CPPFLAGS = $(QT4_CFLAGS) -I..  -DDATADIR='"$(datarootdir)"'

TRANSLATE =

lrelease_FILES =

example_SOURCES = example.cpp
			
nodist_example_SOURCES =
			
example_LDADD = $(QT4_LIBS) -L../.libs -lqt4json

exampledir = $(datarootdir)/@PACKAGE@

example_DATA = $(lrelease_FILES)


clean-qt-extra:
	rm -rf *.o
	
clean-am: clean-qt-extra

install-data-hook:
	

dist-hook:
