#ifndef _SEND_H_
#define _SEND_H_
//=============================================================================
//
//   File : send.h
//   Creation date : Tue Sep 24 09 2000 15:06:12 by Szymon Stefanek
//
//   This file is part of the KVirc irc client distribution
//   Copyright (C) 2000-2008 Szymon Stefanek (pragma at kvirc dot net)
//
//   This program is FREE software. You can redistribute it and/or
//   modify it under the terms of the GNU General Public License
//   as published by the Free Software Foundation; either version 2
//   of the License, or (at your opinion) any later version.
//
//   This program is distributed in the HOPE that it will be USEFUL,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//   See the GNU General Public License for more details.
//
//   You should have received a copy of the GNU General Public License
//   along with this program. If not, write to the Free Software Foundation,
//   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
//
//=============================================================================

#include "descriptor.h"
#include "window.h"
#include "thread.h"

#include "kvi_window.h"
#include "kvi_string.h"
#include "kvi_sockettype.h"
#include "kvi_pointerlist.h"
#include "kvi_filetransfer.h"
#include "kvi_time.h"
#include "kvi_tal_popupmenu.h"
#include "kvi_tal_hbox.h"
#include "kvi_tal_vbox.h"

#include <QLabel>
#include <QProgressBar>
#include <QFile>
#include <QDialog>
#include <QCheckBox>

class QSpinBox;
class QTimer;
class QPainter;
class KviDccFileTransfer;
class KviDccMarshal;
class KviTalPopupMenu;

typedef struct _KviDccSendThreadOptions
{
	KviStr       szFileName;
	quint64      uStartPosition;
	int          iPacketSize;
	int          iIdleStepLengthInMSec;
	bool         bFastSend;
	bool         bNoAcks;
	bool         bIsTdcc;
	unsigned int uMaxBandwidth;
} KviDccSendThreadOptions;


class KviDccSendThread : public KviDccThread
{
public:
	KviDccSendThread(QObject * par,kvi_socket_t fd,KviDccSendThreadOptions * opt);
	~KviDccSendThread();
private:
	// stats: SHARED!!!
	uint           m_uAverageSpeed;
	uint           m_uInstantSpeed;
	quint64        m_uFilePosition;
	quint64        m_uAckedBytes;
	quint64        m_uTotalSentBytes;
	// internal
	unsigned long  m_uStartTime;
	unsigned long  m_uInstantSpeedInterval;
	quint64        m_uInstantSentBytes;
	KviDccSendThreadOptions * m_pOpt;
	KviMSecTimeInterval * m_pTimeInterval;             // used for computing the instant bandwidth but not only
public:
	void initGetInfo();
	uint averageSpeed(){ return m_uAverageSpeed; };
	uint instantSpeed(){ return m_uInstantSpeed; };
	quint64 filePosition(){ return m_uFilePosition; };
	// sent ONLY in this session
	quint64 sentBytes(){ return m_uTotalSentBytes; };
	quint64 ackedBytes(){ return m_uAckedBytes; };
	unsigned int bandwidthLimit(){ return m_pOpt->uMaxBandwidth; };
	void setBandwidthLimit(unsigned int uMaxBandwidth){ m_pOpt->uMaxBandwidth = uMaxBandwidth; };
	void doneGetInfo();
protected:
	void updateStats();
	virtual void run();
};

typedef struct _KviDccRecvThreadOptions
{
	bool         bResume;
	KviStr       szFileName;
	quint64      uTotalFileSize;
	int          iIdleStepLengthInMSec;
	bool         bSendZeroAck;
	bool         bNoAcks;
	bool         bIsTdcc;
	unsigned int uMaxBandwidth;
} KviDccRecvThreadOptions;

class KviDccRecvThread : public KviDccThread
{
public:
	KviDccRecvThread(QObject * par,kvi_socket_t fd,KviDccRecvThreadOptions * opt);
	~KviDccRecvThread();
protected:
	KviDccRecvThreadOptions * m_pOpt;

	// stats: SHARED!
	uint                  m_uAverageSpeed;
	uint                  m_uInstantSpeed;
	quint64               m_uFilePosition;
	quint64               m_uTotalReceivedBytes;

	// internal
	unsigned long         m_uStartTime;
	KviMSecTimeInterval * m_pTimeInterval;             // used for computing the instant bandwidth
	quint64              m_uInstantReceivedBytes;
	quint64               m_uInstantSpeedInterval;
	QFile               * m_pFile;
public:
	void initGetInfo();
	uint averageSpeed(){ return m_uAverageSpeed; };
	uint instantSpeed(){ return m_uInstantSpeed; };
	quint64 filePosition(){ return m_uFilePosition; };
	// received ONLY in this session
	quint64 receivedBytes(){ return m_uTotalReceivedBytes; };
	unsigned int bandwidthLimit(){ return m_pOpt->uMaxBandwidth; };
	void setBandwidthLimit(unsigned int uMaxBandwidth){ m_pOpt->uMaxBandwidth = uMaxBandwidth; };
	void doneGetInfo();
protected:
	void postMessageEvent(const char * msg);
	void updateStats();
	bool sendAck(int filePos);
	virtual void run();
};


class KviDccFileTransferBandwidthDialog : public QDialog
{
	Q_OBJECT
public:
	KviDccFileTransferBandwidthDialog(QWidget * pParent,KviDccFileTransfer * t);
	~KviDccFileTransferBandwidthDialog();
protected:
	KviDccFileTransfer * m_pTransfer;
	QCheckBox * m_pEnableLimitCheck;
	QSpinBox * m_pLimitBox;
protected:
	virtual void closeEvent(QCloseEvent *e);
protected slots:
	void okClicked();
	void cancelClicked();
};


class KviDccFileTransfer : public KviFileTransfer, public KviDccMarshalOutputContext
{
	enum GeneralStatus { Connecting , Transferring , Success , Failure };
	Q_OBJECT
public:
	KviDccFileTransfer(KviDccDescriptor * dcc);
	~KviDccFileTransfer();
private:
	KviDccSendThread       * m_pSlaveSendThread;
	KviDccRecvThread       * m_pSlaveRecvThread;
	KviDccDescriptor       * m_pDescriptor;
	KviDccMarshal          * m_pMarshal;

	KviStr                   m_szTarget;
	KviStr                   m_szDccType;
	QString                  m_szTransferIdString;

	QString                  m_szStatusString;
	GeneralStatus            m_eGeneralStatus;

	QString                  m_szTransferLog; // html

	kvi_time_t               m_tTransferStartTime;
	kvi_time_t               m_tTransferEndTime;
	// cached stats
	quint64                  m_uTotalFileSize; // total file size to transfer

	unsigned int             m_uMaxBandwidth;
	KviDccFileTransferBandwidthDialog * m_pBandwidthDialog;

	QTimer                 * m_pResumeTimer; // used to signal resume timeout
public:
	bool resumeAccepted(const char * filename,const char * port,const char *szZeroPortTag);
	bool doResume(const char * filename,const char * port,quint64 filePos);

	static void init();
	static void done();
	static unsigned int runningTransfersCount();
	static KviDccFileTransfer * nonFailedTransferWithLocalFileName(const QString &szLocalFileName);
	static unsigned int transferCount();
	static bool handleResumeAccepted(const char * filename,const char * port,const char * szZeroPortTag);
	static bool handleResumeRequest(const char * filename,const char * port,quint64 filePos);

	virtual bool event(QEvent *e);

	virtual KviWindow * dccMarshalOutputWindow();
	virtual const char * dccMarshalOutputContextString();

	virtual void displayPaint(QPainter * p,int column, QRect rect);
	virtual int displayHeight(int iLineSpacing);
	virtual void fillContextPopup(KviTalPopupMenu * m);
	virtual void fillStatusString(QString &szBuffer);
	virtual bool active();
	virtual QString tipText();
	virtual QString localFileName();

	bool isFileUpload(){ return m_pDescriptor->isFileUpload(); };

	unsigned int averageSpeed();
	unsigned int transferredBytes();

	int bandwidthLimit();
	void setBandwidthLimit(int iVal);
protected:
	void startConnection();
	void listenOrConnect();
	void addToTransferLog(const QString &s);
	void outputAndLog(const QString &s);
	void outputAndLog(int msgtype,const QString &s);
	KviWindow * eventWindow();
protected slots:
	void connectionInProgress();
	void sslError(const char * msg);
	void startingSSLHandshake();
	void handleMarshalError(int err);
	void connected();
	void bandwidthDialogDestroyed();
	void configureBandwidth();
	void resumeTimedOut();
public slots:
	void abort();
	void retryDCC();
	void retryTDCC();
	void retryRevDCC();
};

#endif //_SEND_H_