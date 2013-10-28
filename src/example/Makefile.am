bin_PROGRAMS = example bench leak

AM_CPPFLAGS = $(QT4_CFLAGS) -I..  -DDATADIR='"$(datarootdir)"'

TRANSLATE =

lrelease_FILES =

example_SOURCES =	example.cpp \
					CPerson.h \
					CJsonView.cpp \
					CJsonView.h

bench_SOURCES = benchParser.cpp

leak_SOURCES = leak.cpp

nodist_example_SOURCES =	moc_CPerson.cpp
			
example_LDADD = $(QT4_LIBS) $(LIBJSON_LIBS) -L../.libs -lqt4json

bench_LDADD = $(QT4_LIBS) -L../.libs -lqt4json

leak_LDADD = $(QT4_LIBS) -L../.libs -lqt4json

exampledir = $(datarootdir)/@PACKAGE@

example_DATA = $(lrelease_FILES)

moc_%.cpp: %.h
	$(MOC) -o $@ $<

clean-qt-extra:
	rm -rf *.o
	rm -f moc_*.cpp
	
clean-am: clean-qt-extra

install-data-hook:
	
dist-hook:
