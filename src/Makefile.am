ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libqt4json.la

AM_CPPFLAGS = $(QT4_CFLAGS)

TRANSLATE = 

lrelease_FILES = 

libqt4json_la_SOURCES = 	libqt4json.cpp \
							libqt4json.h \
							libqt4json.y.c \
							libqt4json.y.h \
							libqt4json.l.c
						
libqt4json_la_LIBADD = $(QT4_LIBS) 

%.qm: %.ts
	$(LRELEASE) $< -qm $@

libqt4json.l.c: libqt4json.l
	$(FLEX) -o $@ $<

libqt4json.y.c: libqt4json.y
	$(BISON) -o $@ -d $<

$(libqt4json_la_OBJECTS): $(lrelease_FILES)

clean-qt-extra:
	rm -f *.o
	rm -f *.lo
	
clean-am: clean-qt-extra

install-data-hook:
	
dist-hook:
