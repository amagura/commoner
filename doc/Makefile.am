info_TEXINFOS = libcommoner.texi
libcommoner_TEXINFOS = LICENSE
dist_doc_data = LICENSE README AUTHORS
#TEXTS =
#man3_MANS = libcommoner.man
dist_man_MANS = libcommoner.3

dist-hook:
	$(MKDIR_P) $(distdir)
	cp -L $(srcdir)/LICENSE $(distdir)
	cp -L $(srcdir)/README.md $(distdir)/README

clean-local:
	$(RM) libcommoner.info
