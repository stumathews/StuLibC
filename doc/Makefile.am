docdir = $(datadir)/doc/@PACKAGE@
doc_DATA = README DONTS
if HAVE_DOXYGEN
directory = $(top_srcdir)/man/man3/

#dist_man_MANS = $(directory)/man_page_1.3 $(directory)/man_page_2.3
$(directory)/*.3: doxyfile.stamp
#$(directory)/man_page_2.3: doxyfile.stamp

doxyfile.stamp:
	$(DOXYGEN) Doxyfile
	echo Timestamp > doxyfile.stamp

CLEANFILES = doxyfile.stamp

all-local: doxyfile.stamp
clean-local:
	rm -rf $(top_srcdir)/man/man3
endif
