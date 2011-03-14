//=============================================================================
//
//   File : optw_channel.cpp
//   Creation date : Sat Sep 27 19:30:02 2008 GMT by Elvio Basello
//
//   This file is part of the KVirc irc client distribution
//   Copyright (C) 2008 Elvio Basello (hellvis69 at netsons dot org)
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
//
// This file was originally part of optw_irc.cpp
//
//=============================================================================


#include "optw_channel.h"

#include "kvi_options.h"
#include "kvi_locale.h"
#include "kvi_settings.h"
#include "kvi_ircmask.h"

#include <QComboBox>

KviChannelOptionsWidget::KviChannelOptionsWidget(QWidget * pParent)
: KviOptionsWidget(pParent)
{
}

KviChannelOptionsWidget::~KviChannelOptionsWidget()
{
}

KviChannelGeneralOptionsWidget::KviChannelGeneralOptionsWidget(QWidget * pParent)
: KviOptionsWidget(pParent)
{
	createLayout();

	KviTalGroupBox * g = addGroupBox(0,0,0,0,Qt::Horizontal,__tr2qs_ctx("On Channel Kick","options"));

 	KviBoolSelector *b = addBoolSelector(g,__tr2qs_ctx("Rejoin channel","options"),KviOption_boolRejoinChannelOnKick);
	mergeTip(b,
		__tr2qs_ctx("<center>This option will cause KVIrc to attempt " \
		"to rejoin a channel after being kicked.</center>","options"));
	b = addBoolSelector(g,__tr2qs_ctx("Keep channel open","options"),KviOption_boolKeepChannelOpenOnKick);
	mergeTip(b,
		__tr2qs_ctx("<center>This option will cause KVIrc to keep " \
			"the channel window open after being kicked.<br>" \
			"It might be a good idea to also enable the " \
			"\"Rejoin channel\" option.</center>","options"));

	g = addGroupBox(0,1,0,1,Qt::Horizontal,__tr2qs_ctx("On Channel Part","options"));

	b = addBoolSelector(g,__tr2qs_ctx("Keep channel open","options"),KviOption_boolKeepChannelOpenOnPart);
	mergeTip(b,
		__tr2qs_ctx("<center>This option will cause KVIrc to keep " \
			"the channel window open after leaving it.</center>","options"));

	b = addBoolSelector(0,2,0,2,__tr2qs_ctx("Automatically join channel on invite","options"),KviOption_boolAutoJoinOnInvite);
	mergeTip(b,
		__tr2qs_ctx("<center>This option will cause KVIrc to automatically " \
			"join a channel when an INVITE message for that channel is received.<br>" \
			"<b>Warning:</b> This may help spammers harass you. :)</center>","options"));

	b = addBoolSelector(0,3,0,3, __tr2qs_ctx("Always open channels as minimized","options"),KviOption_boolCreateMinimizedChannels);
	mergeTip(b,
		__tr2qs_ctx("<center>This option causes newly created " \
			"channel windows to be immediately minimized.<br>" \
			"Enable this if you don't like channels " \
			"popping up while you're typing something in a channel. :D</center>","options"));

	addRowSpacer(0,4,0,4);
}

KviChannelGeneralOptionsWidget::~KviChannelGeneralOptionsWidget()
{
}


KviChannelAdvancedOptionsWidget::KviChannelAdvancedOptionsWidget(QWidget * pParent)
: KviOptionsWidget(pParent)
{
	createLayout();

	KviBoolSelector * b = addBoolSelector(0,0,4,0,__tr2qs_ctx("Log joined channels history","options"),KviOption_boolLogChannelHistory);

	addLabel(0,1,0,1,__tr2qs_ctx("Default ban mask:","options"));

	m_pBanTypeCombo = new QComboBox(this);
	addWidgetToLayout(m_pBanTypeCombo,1,1,4,1);

	KviIrcMask hostmask("nick!user@machine.host.top");
	KviIrcMask ipmask("nick!user@192.168.1.2");
	QString tmp1;
	QString tmp2;
	for(int i=0;i<=26;i++)
	{

		hostmask.mask(tmp1,(KviIrcMask::MaskType)i);
		ipmask.mask(tmp2,(KviIrcMask::MaskType)i);
		m_pBanTypeCombo->insertItem(m_pBanTypeCombo->count(),QString("%1 (%2)").arg(tmp1, tmp2));
	}
	m_pBanTypeCombo->setCurrentIndex(KVI_OPTION_UINT(KviOption_uintDefaultBanType));

	KviTalGroupBox * g = addGroupBox(0,2,4,2,Qt::Horizontal,__tr2qs_ctx("On Channel Join","options"));
	KviUIntSelector *u = addUIntSelector(g,__tr2qs_ctx("Minimum delay between two requests:","options"),KviOption_uintOnJoinRequestsDelay,0,60,2);
	u->setSuffix(__tr2qs_ctx(" sec","options"));
	mergeTip(u,__tr2qs_ctx("<center>Minimum value: <b>0 secs</b><br>Maximum value: <b>60 secs</b></center>","options"));
	
	addBoolSelector(g,__tr2qs_ctx("Do not send /WHO request","options"),KviOption_boolDisableWhoRequestOnJoin);
	addBoolSelector(g,__tr2qs_ctx("Do not request ban list","options"),KviOption_boolDisableBanListRequestOnJoin);
	addBoolSelector(g,__tr2qs_ctx("Do not request ban exception list","options"),KviOption_boolDisableBanExceptionListRequestOnJoin);
	addBoolSelector(g,__tr2qs_ctx("Do not request invite list","options"),KviOption_boolDisableInviteListRequestOnJoin);
	addBoolSelector(g,__tr2qs_ctx("Do not request quiet ban list","options"),KviOption_boolDisableQuietBanListRequestOnJoin);
	addBoolSelector(g,__tr2qs_ctx("Echo channel topic","options"),KviOption_boolEchoNumericTopic);
	addBoolSelector(g,__tr2qs_ctx("Show channel sync time","options"),KviOption_boolShowChannelSyncTime);

	b = addBoolSelector(g,__tr2qs_ctx("Paste last channel log","options"),KviOption_boolPasteLastLogOnChannelJoin);

	KviTalHBox * box = new KviTalHBox(g);
	u = addUIntSelector(box,__tr2qs_ctx("Paste up to:","options"),KviOption_uintLinesToPasteOnChannelJoin,0,50,10,KVI_OPTION_BOOL(KviOption_boolPasteLastLogOnChannelJoin));
	u->setSuffix(__tr2qs_ctx(" lines","options"));
	mergeTip(u,__tr2qs_ctx("<center>Minimum value: <b>0 lines</b><br>Maximum value: <b>50 lines</b></center>","options"));
	connect(b,SIGNAL(toggled(bool)),u,SLOT(setEnabled(bool)));
	u = addUIntSelector(box,__tr2qs_ctx("Interval:","options"),KviOption_uintDaysIntervalToPasteOnChannelJoin,1,10,10,KVI_OPTION_BOOL(KviOption_boolPasteLastLogOnChannelJoin));
	u->setSuffix(__tr2qs_ctx(" days","options"));
	mergeTip(u,__tr2qs_ctx("<center>Minimum value: <b>0 days</b><br>Maximum value: <b>10 days</b></center>","options"));
	connect(b,SIGNAL(toggled(bool)),u,SLOT(setEnabled(bool)));

 	b = addBoolSelector(0,3,4,3,__tr2qs_ctx("Keep away list updated by sending WHO requests","options"),KviOption_boolEnableAwayListUpdates);
	mergeTip(b,
		__tr2qs_ctx("<center>KVIrc sends out a channel /WHO message every now and then to keep " \
			"the channel away list in sync. Use this option to disable this feature (and to save " \
			"your IRC bandwidth.</center>","options"));

	addRowSpacer(0,5,4,5);
}

KviChannelAdvancedOptionsWidget::~KviChannelAdvancedOptionsWidget()
{
}

void KviChannelAdvancedOptionsWidget::commit()
{
	KVI_OPTION_UINT(KviOption_uintDefaultBanType)=m_pBanTypeCombo->currentIndex();
	if((KVI_OPTION_UINT(KviOption_uintDefaultBanType)>26)) KVI_OPTION_UINT(KviOption_uintDefaultBanType)=7;
	KviOptionsWidget::commit();
}

#ifndef COMPILE_USE_STANDALONE_MOC_SOURCES
#include "m_optw_channel.moc"
#endif //COMPILE_USE_STANDALONE_MOC_SOURCES