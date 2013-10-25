ACLOCAL_AMFLAGS = -I m4

lib_LTLIBRARIES = libqt4json.la

AM_CPPFLAGS = $(QT4_CFLAGS) $(LIBJSON_CFLAGS)

TRANSLATE = 

lrelease_FILES = 

libqt4json_la_SOURCES =	libqt4json.cpp \
						CCommon.cpp \
						libqt4json.h \
						CCommon.h
				

nodist_libqt4json_la_SOURCES = 
					
libqt4json_la_LIBADD = $(QT4_LIBS) $(LIBJSON_LIBS)

%.qm: %.ts
	$(LRELEASE) $< -qm $@

$(libqt4json_la_OBJECTS): $(lrelease_FILES)

clean-qt-extra:
	rm -f *.o
	rm -f *.lo
	rm -rf
	
	
clean-am: clean-qt-extra

install-data-hook:
	mkdir -p $(includedir); \
	mkdir -p $(libdir)/pkgconfig; \
	cp $(srcdir)/libqt4json.h $(includedir); \
	cp $(srcdir)/libqt4json.pc $(libdir)/pkgconfig
	
dist-hook:
	cp $(srcdir)/libqt4json.doxy $(distdir); \
	cp $(srcdir)/libqt4json.png $(distdir)
