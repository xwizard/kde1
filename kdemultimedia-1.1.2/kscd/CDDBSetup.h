/*
 * This file was initialy generated by QTArchitect, but was heavily modified
 * afterwards.
 */

#ifndef CDDBSetup_included
#define CDDBSetup_included

#include "CDDBSetupData.h"
#include <qstrlist.h>

class CDDBSetup : public CDDBSetupData
{
    Q_OBJECT

public:

    CDDBSetup
    (
        QWidget* parent = NULL,
        const char* name = NULL
    );

    virtual ~CDDBSetup();

public slots:
    void serverlist_update();

    void getData(QStrList& _serverlist,
                 QStrList& _submitlist,
                 QString& _basedir,
                 QString& _submitaddress,
                 QString& _current_server,
                 bool& _remote_enabled,
                 bool&    http_proxy_enabled,
                 QString  &http_proxy_host,
                 int      &http_proxy_port
                );

    void insertData(const QStrList& _serverlist,
                    const QStrList& _submitlist,
                    const QString& _basedir,
                    const QString& _submitaddress,
                    const QString& _current_server,
                    const bool&    _remote_enabled,
                    const bool&    http_proxy_enabled,
                    const QString  &http_proxy_host,
                    const int      &http_proxy_port
                   );

protected slots:
   void help();
   void enable_remote_cddb(bool en);
   void basedir_changed(const char* str);
   void set_current_server(int i);
   void set_current_submission_address(int i);
   void set_defaults();
   virtual void http_access_toggled(bool);
   void insertSL();
   void removeSL();
   void insertSUL();
   void removeSUL();

signals:
   void updateCDDBServers();
   void updateCurrentServer();

public:
   void insertServerList(const QStrList& list);
   void getCurrentServer(QString& ser);

private:

   QString basedirstring;
   QString submitaddressstring;
   QString current_server_string;
   QStrList submitlist;
};
#endif // CDDBSetup_included
