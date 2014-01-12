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
	main.c\
	net/addr/addr.c\
	net/eth/eth.c\
	net/ip/ip.c\
	net/mac/mac.c\
	net/tcp/tcp.c\
	net/udp/udp.c\
	nfqueue.c\
	precog.c

precog_LDFLAGS = -lnetfilter_queue -lnfnetlink
precog_LDADD = $(PRECOG_LIBS)
