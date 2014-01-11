AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\" \
	$(PRECOG_CFLAGS)

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = precog

precog_SOURCES = \
	nfqueue.c\
	precog.c

precog_LDFLAGS = -lnetfilter_queue -lnfnetlink
precog_LDADD = $(PRECOG_LIBS)
