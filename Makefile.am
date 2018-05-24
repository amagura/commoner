dist_doc_data = LICENSE README.md AUTHORS

SUBDIRS = src

DIST_SUBDIRS = $(SUBDIRS)

ACLOCAL_AMFLAGS = -I m4

all-local:

anew: clean all


clean-local:
	$(RM) *stamp*
	$(RM) *~

dist-local:
	./update-version.sh

uninstall:
	cd $(libdir); \
	  $(RM) $(wildcard *libcommoner*)
	cd $(includedir); \
	  $(RM) commoner.h

