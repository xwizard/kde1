SUBDIRS = doc
bin_PROGRAMS= ksnapshot

INCLUDES = -DKSNAPVERSION="\"0.2.7\"" $(all_includes) 

ksnapshot_LDFLAGS = $(all_libraries) $(KDE_RPATH)
ksnapshot_LDADD = $(LIB_KIMGIO) $(LIB_KDEUI)

ksnapshot_SOURCES = eps.cpp gif.cpp main.cpp formats.cpp ksnapshot.cpp preview.cpp

ksnapshot_METASOURCES = USE_AUTOMOC

lnkdir = $(kde_appsdir)/Graphics
lnk_DATA = ksnapshot.kdelnk

icondir = $(kde_icondir)
icon_DATA = ksnapshot.xpm

EXTRA_DIST = $(lnk_DATA) $(icon_DATA) mini-ksnapshot.xpm large-ksnapshot.xpm

install-data-local: mini-ksnapshot.xpm large-ksnapshot.xpm
	$(mkinstalldirs) $(kde_minidir)
	$(INSTALL_DATA) $(srcdir)/mini-ksnapshot.xpm $(kde_minidir)/ksnapshot.xpm
	$(mkinstalldirs) $(kde_icondir)/large
	$(INSTALL_DATA) $(srcdir)/large-ksnapshot.xpm $(kde_icondir)/large/ksnapshot.xpm

uninstall-local:
	-rm -f $(kde_minidir)/ksnapshot.xpm
	-rm -f $(kde_icondir)/large/ksnapshot.xpm

messages:
	$(XGETTEXT) -C -ki18n -ktranslate -x $(includedir)/kde.pot $(ksnapshot_SOURCES) && mv messages.po ../po/ksnapshot.pot







