
# This has to be set. The rest should be reusable
GMOFILES = kfind.gmo kdehelp.gmo kcmdisplay.gmo kvt.gmo \
	kfm.gmo kwm.gmo kfontmanager.gmo kcontrol.gmo \
	kpanel.gmo krootwm.gmo kmenuedit.gmo kcmbell.gmo \
	kcminfo.gmo kcminput.gmo kcmkpanel.gmo kcmkwm.gmo \
	kcmlocale.gmo kcmsamba.gmo kcmsample.gmo kdm.gmo \
	kdmconfig.gmo klock.gmo kcmsyssound.gmo kstart.gmo \
	kcmkfm.gmo kcmkeys.gmo kpanel.gmo kikbd.gmo konsole.gmo \
	kbgndwm.gmo kpager.gmo

POFILES = $(GMOFILES:.gmo=.po)

LANG = sv

localedir = $(kde_locale)

EXTRA_DIST = $(POFILES) 

all: all-$(USE_NLS)
install-data-local: install-$(USE_NLS)

SUFFIXES = .po .gmo

.po.gmo:
	@file=`echo $* | sed 's,.*/,,'`.gmo; \
	echo $(GMSGFMT) -o $$file $< ;\
	rm -f $$file && $(GMSGFMT) -o $$file $< 

all-yes: $(GMOFILES)
all-no:

install-yes: all
	@catalogs='$(GMOFILES)'; \
	for cat in $$catalogs; do \
	destdir=$(localedir); \
	name=`echo $$cat | sed -e 's/\.gmo/\.mo/'` \
	dir=$$destdir/$(LANG)/LC_MESSAGES; \
	$(mkinstalldirs) $$dir; \
	$(INSTALL_DATA) $$cat $$dir/$$name; \
	  echo "installing $$cat as $$dir/$$name"; \
	done

install-no:

uninstall-local:
	@catalogs='$(GMOFILES)'; \
	for cat in $$catalogs; do \
	destdir=$(localedir); \
	name=`echo $$cat | sed -e 's/\.gmo/\.mo/'` \
	dir=$$destdir/$(LANG)/LC_MESSAGES; \
	rm -f $$cat $$dir/$$name; \
	echo "removing $$dir/$$name" ; \
	done

dist-hook: $(GMOFILES)
	cp $(GMOFILES) $(distdir)
