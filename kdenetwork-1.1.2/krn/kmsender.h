/* KMail Mail Sender
 *
 * Author: Stefan Taferner <taferner@alpin.or.at>
 */
#ifndef kmsender_h
#define kmsender_h
#include <mimelib/smtp.h>
#include <mimelib/string.h>
#include <mimelib/utility.h>
#include <qstring.h>
#include <qobject.h>

class KMMessage;
class KMFolder;
class KMFolderMgr;
class KConfig;
class KProcess;
class DwSmtpClient;
class KMIOStatusDlg;
class KMSendProc;
class QStrList;

class KMSender: public QObject
{
  Q_OBJECT
  friend class KMSendProc;

public:
  enum Method { smUnknown=0, smSMTP=1, smMail=2 };

  KMSender();
  virtual ~KMSender();

  /** Send given message. The message is either queued or sent
    immediately. The default behaviour, as selected with 
    setSendImmediate(), can be overwritten with the parameter
    sendNow (by specifying TRUE or FALSE).
    The sender takes ownership of the given message on success,
    so DO NOT DELETE OR MODIFY the message further.
    Returns TRUE on success. */
  virtual bool send(KMMessage* msg, short sendNow=-1);

  /** Start sending all queued messages. Returns TRUE on success. */
  virtual bool sendQueued();

  virtual bool sendSingleMail(KMMessage *msg);
  /** Returns TRUE if sending is in progress. */
  bool sending(void) const { return mSendInProgress; }

  /** Method the sender shall use: either SMTP or local mail program */
  Method method(void) const { return mMethod; }
  virtual void setMethod(Method);

  /** Shall messages be sent immediately (TRUE), or shall they be
    queued and sent later upon call of sendQueued() ? */
  bool sendImmediate(void) const { return mSendImmediate; }
  virtual void setSendImmediate(bool);

  /** Shall messages be sent quoted-printable encoded. No encoding
    happens otherwise. */
  bool sendQuotedPrintable(void) const { return mSendQuotedPrintable; }
  virtual void setSendQuotedPrintable(bool);

  /** Name of the mail client (usually "/usr/bin/mail") that
    is used for mailing if the method is smMail */
  const QString mailer(void) const { return mMailer; }
  virtual void setMailer(const QString&);

  /** Name of the host that is contacted via SMTP if the mailing
    method is smSMTP. */
  const QString smtpHost(void) const { return mSmtpHost; }
  virtual void setSmtpHost(const QString&);

  /** Port of the SMTP host, usually 110. */
  int smtpPort(void) const { return mSmtpPort; }
  virtual void setSmtpPort(int);

  /** Read configuration from global config. */
  virtual void readConfig(void);

  /** Write configuration to global config with optional sync() */
  virtual void writeConfig(bool withSync=TRUE);

signals:
  /** Emitted regularly to inform the user of what is going on */
  void statusMsg(const char*);

protected slots:
  virtual void slotIdle();

protected:
  /** handle sending of messages */
  virtual void doSendMsg();

  /** cleanup after sending */
  virtual void cleanup(void);

  /** Test if all required settings are set.
      Reports problems to user via dialogs and returns FALSE.
      Returns TRUE if everything is Ok. */
  virtual bool settingsOk(void) const;

private:
  Method mMethod;
  bool mSendImmediate, mSendQuotedPrintable;
  QString mMailer;
  QString mSmtpHost;
  int mSmtpPort;

  bool mSentOk;
  QString mErrorMsg;
  KMIOStatusDlg* mSendDlg;
  KMSendProc* mSendProc;
  bool mSendProcStarted;
  bool mSendInProgress;
  KMMessage * mCurrentMsg;
};


//-----------------------------------------------------------------------------
#define KMSendProcInherited QObject
class KMSendProc: public QObject
{
  Q_OBJECT

public:
  KMSendProc(KMSender*);

  /** Initialize sending of one or more messages. */
  virtual bool start(void);

  /** Initializes variables directly before send() is called. */
  virtual void preSendInit(void);

  /** Send given message. May return before message is sent. */
  virtual bool send(KMMessage* msg) = 0;

  /** Cleanup after sending messages. */
  virtual bool finish(void);

  /** Returns TRUE if send was successful, and FALSE otherwise.
      Returns FALSE if sending is still in progress. */
  bool sendOk(void) const { return mSendOk; }

  /** Returns TRUE if sending is still in progress. */
  bool sending(void) const { return mSending; }

  /** Returns error message of last call of failed(). */
  const QString message(void) const { return mMsg; }

signals:
  /** Emitted when the current message is sent or an error occured. */
  void idle();

protected:
  /** Called to signal a transmission error. The sender then
    calls finish() and terminates sending of messages. 
    Sets mSending to FALSE. */
  virtual void failed(const QString msg);

  /** Prepare message for sending. */
  virtual const QString prepareStr(const QString str, bool toCRLF=FALSE);

  /** Informs the user about what is going on. */
  virtual void statusMsg(const char* msg);

  /** Called once for the contents of the header fields To, Cc, and Bcc.
    Returns TRUE on success and FALSE on failure. 
    Calls addOneRecipient() for each recipient in the list. Aborts and
    returns FALSE if addOneRecipient() returns FALSE. */
  virtual bool addRecipients(const QStrList& aRecpList);

  /** Called from within addRecipients() once for each recipient in
    the list after all surplus characters have been stripped. E.g.
    for: "Stefan Taferner" <taferner@kde.org>
    addRecpient(taferner@kde.org) is called. 
    Returns TRUE on success and FALSE on failure. */
  virtual bool addOneRecipient(const QString aRecipient) = 0;

protected:
  bool mSendOk, mSending;
  QString mMsg;
  KMSender* mSender;
};


//-----------------------------------------------------------------------------
#define KMSendSendmailInherited KMSendProc
class KMSendSendmail: public KMSendProc
{
  Q_OBJECT
public:
  KMSendSendmail(KMSender*);
  virtual ~KMSendSendmail();
  virtual bool start(void);
  virtual bool send(KMMessage* msg);
  virtual bool finish(void);

protected slots:
  void receivedStderr(KProcess*,char*,int);
  void wroteStdin(KProcess*);
  void sendmailExited(KProcess*);

protected:
  virtual bool addOneRecipient(const QString aRecipient);

  QString mMsgStr;
  char* mMsgPos;
  int mMsgRest;
  KProcess* mMailerProc;
};

//-----------------------------------------------------------------------------
#define KMSendSMTPInherited KMSendProc
class KMSendSMTP: public KMSendProc
{
public:
  KMSendSMTP(KMSender*);
  virtual ~KMSendSMTP();
  virtual bool start(void);
  virtual bool send(KMMessage* msg);
  virtual bool finish(void);

protected:
  virtual bool smtpSend(KMMessage* msg);
  virtual bool smtpFailed(const char* inCommand, int replyCode);
  virtual void smtpDebug(const char* inCommand);
  virtual void smtpInCmd(const char* inCommand);
  virtual bool addOneRecipient(const QString aRecipient);
  
  void (*mOldHandler)(int);
  DwSmtpClient* mClient;
};

#endif /*kmsender_h*/
