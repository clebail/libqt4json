ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libqt4json.la

AM_CPPFLAGS = $(QT4_CFLAGS)

TRANSLATE = 

lrelease_FILES = 

flexBison_SOURCES =	libqt4json.y.cpp \
			libqt4json.y.hpp \
			libqt4json.l.cpp 

libqt4json_la_SOURCES = 	$(flexBison_SOURCES) \
				libqt4json.cpp \
				libqt4json.h \
				CScanner.h
				
nodist_libqt4json_la_SOURCES = 	
					
libqt4json_la_LIBADD = $(QT4_LIBS) 

%.qm: %.ts
	$(LRELEASE) $< -qm $@

libqt4json.l.cpp: libqt4json.l
	$(FLEX) -o $@ --c++ $<

libqt4json.y.cpp: libqt4json.y
	$(BISON) -o $@ -d $<

$(libqt4json_la_OBJECTS): $(lrelease_FILES)

clean-qt-extra:
	rm -f *.o
	rm -f *.lo
	rm -f libqt4json.l.cpp
	rm -f libqt4json.y.cpp
	rm -f libqt4json.y.hpp
	
clean-am: clean-qt-extra

install-data-hook:
	
dist-hook:
	cp $(srcdir)/libqt4json.l $(distdir); \
	cp $(srcdir)/libqt4json.y $(distdir); \
	cd $(distdir) && rm $(flexBison_SOURCES);
