/*
 * Kscd - A simple cd player for the KDE Project
 *
 * $Id: smtp.h,v 1.3.2.2 1999/04/14 20:47:34 porten Exp $
 *
 * Copyright (c) 1997 Bernd Johannes wuebben@math.cornell.edu
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 */

#ifndef SMTP_H
#define SMTP_H

#include <qobject.h>
#include <qtimer.h>
#include <ksock.h>

/*int SMTPServerStatus[] = {
    220,  // greeting from server
    221,  // server acknolages goodbye
    250,  // command successful
    354,  // ready to recieve data
    501,  // error
    550,  // user unkown
    0     // null
};

int SMTPClientStatus[] = {
    50,   // not logged in yet.
    100,  // logged in, got 220
    150,  // sent helo, got 250
    200,  // sent mail from, got 250
    250,  // sent rctp to, got 250
    300,  // data sent, got 354
    350,  // sent data/., got 250
    400,  // send quit, got 221
    450,  // finished, logged out
    0     // null
};
*/

#define DEFAULT_SMTP_PORT 25
#define DEFAULT_SMTP_SERVER localhost
#define DEFAULT_SMTP_TIMEOUT 60

#define SMTP_READ_BUFFER_SIZE 256

class SMTP:public QObject
{
    Q_OBJECT
public:
    SMTP(char *serverhost = 0, int port = 0, int timeout = DEFAULT_SMTP_TIMEOUT);
    ~SMTP();
    
    void setServerHost(char *serverhost);
    void setPort(int port);
    void setTimeOut(int timeout);
    
    bool isConnected(){return connected;};
    bool isFinished(){return finished;};
    char *getLastLine(){return lastLine.data();};
    
    void setSenderAddress(char *sender);
    void setRecipientAddress(char *recipient);
    void setMessageSubject(char *subject);
    void setMessageBody(char *message);

    typedef enum {
      NONE = 0,             /* null */
      GREET = 220,          /* greeting from server */
      GOODBYE = 221,        /* server acknolages quit */
      SUCCESSFUL = 250,     /* command successful */
      READYDATA = 354,      /* server ready to recieve data */
      ERROR = 501,          /* error */
      UNKNOWN = 550         /* user unknown */
    }SMTPServerStatus;

    typedef enum {
      INIT = 50,            /* not logged in yet */
      IN = 100,             /* logged in, got 220 */
      READY = 150,          /* sent HELO, got 250 */
      SENTFROM = 200,       /* sent MAIL FROM:, got 250 */
      SENTTO = 250,         /* sent RCTP TO:, got 250 */
      DATA = 300,           /* DATA sent, got 354 */
      FINISHED = 350,       /* finished sending data, got 250 */
      QUIT = 400,           /* sent QUIT, got 221 */
      OUT = 450,            /* finished, logged out */
      CERROR = 500          /* didn't finish, had error or connection drop */
    }SMTPClientStatus;

    typedef enum {
        NOERROR = 0,
        CONNECTERROR = 10,
        NOTCONNECTED = 11,
        CONNECTTIMEOUT = 15,
        INTERACTTIMEOUT = 16,
        UNKNOWNRESPONSE = 20,
        UNKNOWNUSER = 30,
        COMMAND = 40
    }SMTPError;

protected:
    void processLine(QString *line);

public slots:
    void openConnection();
    void sendMessage();
    void closeConnection();

    void connectTimerTick();
    void connectTimedOut();
    void interactTimedOut();

    void socketRead(KSocket *);
    void socketClose(KSocket *);

signals:
    void connectionClosed();
    void messageSent();
    void error(int);

private:
    QString serverHost;
    int hostPort;
    int timeOut;

    bool connected;
    bool finished;
    
    QString senderAddress;
    QString recipientAddress;
    QString messageSubject;
    QString messageBody;

    SMTPClientStatus state;
    SMTPClientStatus lastState;
    SMTPServerStatus serverState;

    QString domainName;

    KSocket *sock;
    QTimer connectTimer;
    QTimer timeOutTimer;
    QTimer interactTimer;

    char readBuffer[SMTP_READ_BUFFER_SIZE];
    QString lineBuffer;
    QString lastLine;
    QString writeString;
};
#endif
