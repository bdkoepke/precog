SUBDIRS = src 

precogdocdir = ${prefix}/doc/precog
precogdoc_DATA = \
	README\
	COPYING\
	AUTHORS\
	ChangeLog\
	INSTALL\
	NEWS

EXTRA_DIST = $(precog_DATA)

ACLOCAL_AMFLAGS = -I m4

# Remove doc directory on uninstall
uninstall-local:
	-rm -r $(precogdocdir)
