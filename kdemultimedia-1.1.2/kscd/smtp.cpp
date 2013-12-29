/*
 * Kscd - A simple cd player for the KDE Project
 *
 * $Id: smtp.cpp,v 1.3.2.2 1999/06/29 10:20:56 porten Exp $
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

#include <smtp.h>

#include <sys/utsname.h>
#include <unistd.h>
#include <stdio.h>

extern bool debugflag;

SMTP::SMTP(char *serverhost, int port, int timeout)
{
    struct utsname uts;

    serverHost = serverhost;
    hostPort = port;
    timeOut = timeout * 1000;

    senderAddress = "user@host.ext";
    recipientAddress = "user@host.ext";
    messageSubject = "cddb unknown unknown";
    messageBody = "empty";
    
    connected = false;
    finished = false;

    sock = 0L;
    state = INIT;
    serverState = NONE;

    uname(&uts);
    domainName = uts.nodename;
    domainName.detach();
    
    if(domainName.isEmpty())
        domainName = "somemachine.nowhere.org";

    if(debugflag)
        printf("SMTP object created\n");
    
    connect(&connectTimer, SIGNAL(timeout()), this, SLOT(connectTimerTick()));
    connect(&timeOutTimer, SIGNAL(timeout()), this, SLOT(connectTimedOut()));
    connect(&interactTimer, SIGNAL(timeout()), this, SLOT(interactTimedOut()));

    // some sendmail will give 'duplicate helo' error, quick fix for now
    connect(this, SIGNAL(messageSent()), SLOT(closeConnection()));
}

SMTP::~SMTP()
{
    if(sock){
        delete sock;
        sock = 0L;
    }
    connectTimer.stop();
    timeOutTimer.stop();
}

void SMTP::setServerHost(char *serverhost)
{
    serverHost = serverhost;
}

void SMTP::setPort(int port)
{
    hostPort = port;
}

void SMTP::setTimeOut(int timeout)
{
    timeOut = timeout;
}

void SMTP::setSenderAddress(char *sender)
{
    senderAddress = sender;
}

void SMTP::setRecipientAddress(char *recipient)
{
    recipientAddress = recipient;
}

void SMTP::setMessageSubject(char *subject)
{
    messageSubject = subject;
}

void SMTP::setMessageBody(char *message)
{
    messageBody = message;
}

void SMTP::openConnection(void)
{
    if(debugflag)
        printf("started connect timer\n");
    connectTimer.start(100, TRUE);
}

void SMTP::closeConnection(void)
{
    socketClose(sock);
}

void SMTP::sendMessage(void)
{
    if(!connected)
        connectTimerTick();
    if(state == FINISHED && connected){
        if(debugflag)
            printf("state was == FINISHED\n");
        finished = false;
        state = IN;
        writeString.sprintf("helo %s\r\n", domainName.data());
        write(sock->socket(), writeString.data(), writeString.length());
    }
    if(connected){
        if(debugflag)
            printf("enabling read on sock...\n");
        interactTimer.start(timeOut, TRUE);
        sock->enableRead(true);
    }
}
#include <stdio.h>

void SMTP::connectTimerTick(void)
{
    connectTimer.stop();
//    timeOutTimer.start(timeOut, TRUE);

    if(debugflag)
        printf("connectTimerTick called...\n");
    
    if(sock){
        delete sock;
        sock = 0L;
    }

    if(debugflag)
        printf("connecting to %s:%d ..... \n", serverHost.data(), hostPort);
    sock = new KSocket(serverHost, hostPort);

    if(sock == 0L || sock->socket() < 0){
        timeOutTimer.stop();
        if(debugflag)
            printf("connection failed!\n");
        emit error(CONNECTERROR);
        connected = false;
        return;
    }
    connected = true;
    finished = false;
    state = INIT;
    serverState = NONE;

    connect(sock, SIGNAL(readEvent(KSocket *)), this, SLOT(socketRead(KSocket *)));
    connect(sock, SIGNAL(closeEvent(KSocket *)), this, SLOT(socketClose(KSocket *)));
    //    sock->enableRead(true);
    timeOutTimer.stop();
    if(debugflag)
        printf("connected\n");
}

void SMTP::connectTimedOut(void)
{
    timeOutTimer.stop();

    if(sock) 
	sock->enableRead(false);
    if (debugflag)
        printf("socket connection timed out\n");
    socketClose(sock);
    emit error(CONNECTTIMEOUT);
}

void SMTP::interactTimedOut(void)
{
    interactTimer.stop();

    if(sock)
        sock->enableRead(false);
    if(debugflag)
        printf("time out waiting for server interaction");
    socketClose(sock);
    emit error(INTERACTTIMEOUT);
}

void SMTP::socketRead(KSocket *socket)
{
    int n, nl;

    if(debugflag)
        printf("socketRead() called...\n");
    interactTimer.stop();

    if(socket == 0L || socket->socket() < 0)
        return;
    n = read(socket->socket(), readBuffer, SMTP_READ_BUFFER_SIZE-1 );
    readBuffer[n] = '\0';
    lineBuffer += readBuffer;
    nl = lineBuffer.find('\n');
    if(nl == -1)
        return;
    lastLine = lineBuffer.left(nl);
    lineBuffer = lineBuffer.right(lineBuffer.length() - nl - 1);
    processLine(&lastLine);
    if(connected)
        interactTimer.start(timeOut, TRUE);
}

void SMTP::socketClose(KSocket *socket)
{
    timeOutTimer.stop();
    disconnect(sock, SIGNAL(readEvent(KSocket *)), this, SLOT(socketRead(KSocket *)));
    disconnect(sock, SIGNAL(closeEvent(KSocket *)), this, SLOT(socketClose(KSocket *)));
    socket->enableRead(false);
    if(debugflag)
        printf("connection terminated\n");
    connected = false;
    if(socket){
        delete socket;
        socket = 0L;
        sock = 0L;
    }
    emit connectionClosed();
}

void SMTP::processLine(QString *line)
{
    int i, stat;
    QString tmpstr;
    
    i = line->find(' ');
    tmpstr = line->left(i);
    if(debugflag)
        if(i > 3){
            
            printf("warning: SMTP status code longer then 3 digits: %s\n", tmpstr.data());
        }
    stat = tmpstr.toInt();
    serverState = (SMTPServerStatus)stat;
    lastState = state;

    if(debugflag)
        printf("smtp state: [%d][%s]\n", stat, line->data());

    switch(stat){
    case GREET:     //220
        state = IN;
        writeString.sprintf("helo %s\r\n", domainName.data());
	write(sock->socket(), writeString.data(), writeString.length());
        break;
    case GOODBYE:   //221
        state = QUIT;
        break;
    case SUCCESSFUL://250
        switch(state){
        case IN:
            state = READY;
            writeString.sprintf("mail from: %s\r\n", senderAddress.data());
            write(sock->socket(), writeString.data(), writeString.length());
            break;
        case READY:
            state = SENTFROM;
            writeString.sprintf("rcpt to: %s\r\n", recipientAddress.data());
            write(sock->socket(), writeString.data(), writeString.length());
            break;
        case SENTFROM:
            state = SENTTO;
            writeString.sprintf("data\r\n");
            write(sock->socket(), writeString.data(), writeString.length());
            break;
        case DATA:
            state = FINISHED;
            finished = true;
            sock->enableRead(false);
            emit messageSent();
            break;
        default:
            state = CERROR;
            if(debugflag)
                printf("smtp error (state error): [%d]:[%d][%s]\n", lastState, stat, line->data());
            socketClose(sock);
            emit error(COMMAND);
            break;
        }
        break;
    case READYDATA: //354
        state = DATA;
        //        writeString.sprintf("Subject: %s\n%s\n.\n", messageSubject.data(), messageBody.data());
        writeString.sprintf("Subject: %s\r\n", messageSubject.data());
        writeString += messageBody.data();
        writeString += ".\r\n";
        write(sock->socket(), writeString.data(), writeString.length());
        break;
    case ERROR:     //501
        state = CERROR;
        if(debugflag)
            printf("smtp error (command error): [%d]:[%d][%s]\n", lastState, stat, line->data());
        socketClose(sock);
        emit error(COMMAND);
        break;
    case UNKNOWN:   //550
        state = CERROR;
        if(debugflag)
            printf("smtp error (unknown user): [%d]:[%d][%s]\n", lastState, stat, line->data());
        socketClose(sock);
        emit error(UNKNOWNUSER);
        break;
    default:
        state = CERROR;
        if(debugflag)
            printf("unknown response: [%d]:[%d][%s]\n", lastState, stat, line->data());
        socketClose(sock);
        emit error(UNKNOWNRESPONSE);
    }
}
#include "smtp.moc"
