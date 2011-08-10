////////////////////////////////////////////////////////////////////////////
// callbacks.cpp
//
// Copyright 2005-2008 Intrinsyc Software International, Inc.  All rights reserved.
// Patents pending in the United States of America and other jurisdictions.
//
//
// Description:
//    Implementations for all functions provided to RIL_requestTimedCallback
//
// Author:  Mike Worth
// Created: 2009-10-20
//
/////////////////////////////////////////////////////////////////////////////
//  Modification Log:
//
//  Date       Who      Ver   Description
//  ---------  -------  ----  -----------------------------------------------
//  Oct 20/09  MW       1.00  Established v1.00 based on current code base.
//
/////////////////////////////////////////////////////////////////////////////

#include "types.h"
#include "command.h"
#include "rildmain.h"
#include "rillog.h"
#include "te.h"
#include "../util.h"

void notifyChangedCallState(void *param)
{
    RIL_onUnsolicitedResponse (RIL_UNSOL_RESPONSE_CALL_STATE_CHANGED, NULL, 0);
}

void triggerSignalStrength(void *param)
{
    CCommand * pCmd = new CCommand(g_arChannelMapping[ND_REQ_ID_SIGNALSTRENGTH], NULL, REQ_ID_NONE, "AT+CSQ\r", &CTE::ParseUnsolicitedSignalStrength);

    if (pCmd)
    {
        if (!CCommand::AddCmdToQueue(pCmd))
        {
            RIL_LOG_CRITICAL("triggerSignalStrength() - ERROR: Unable to queue command!\r\n");
            delete pCmd;
            pCmd = NULL;
        }
    }
    else
    {
        RIL_LOG_CRITICAL("triggerSignalStrength() - ERROR: Unable to allocate memory for new command!\r\n");
    }
}

void triggerSMSAck(void *param)
{
    CCommand * pCmd = new CCommand(g_arChannelMapping[ND_REQ_ID_SMSACKNOWLEDGE], NULL, REQ_ID_NONE, "AT+CNMA=1\r");

    if (pCmd)
    {
        if (!CCommand::AddCmdToQueue(pCmd))
        {
            RIL_LOG_CRITICAL("triggerSMSAck() - ERROR: Unable to queue command!\r\n");
            delete pCmd;
            pCmd = NULL;
        }
    }
    else
    {
        RIL_LOG_CRITICAL("triggerSMSAck() - ERROR: Unable to allocate memory for new command!\r\n");
    }
}

void triggerUSSDNotification(void *param)
{
    P_ND_USSD_STATUS pUssdStatus = (P_ND_USSD_STATUS)param;

    RIL_onUnsolicitedResponse (RIL_UNSOL_ON_USSD, pUssdStatus, sizeof(S_ND_USSD_POINTERS));

    free(pUssdStatus);
}

void triggerDataCallListChanged(void *param)
{
    CCommand * pCmd = new CCommand(g_arChannelMapping[ND_REQ_ID_PDPCONTEXTLIST_UNSOL], NULL, ND_REQ_ID_PDPCONTEXTLIST_UNSOL, "AT+CGACT?;+CGDCONT?\r", &CTE::ParseDataCallListChanged);

    if (pCmd)
    {
        if (!CCommand::AddCmdToQueue(pCmd))
        {
            RIL_LOG_CRITICAL("triggerDataCallListChanged() - ERROR: Unable to queue command!\r\n");
            delete pCmd;
            pCmd = NULL;
        }
    }
    else
    {
        RIL_LOG_CRITICAL("triggerDataCallListChanged() - ERROR: Unable to allocate memory for new command!\r\n");
    }
}


//  [in] param = context id.
void triggerDeactivateDataCall(void *param)
{
    UINT32 nCID;
    REQUEST_DATA rReqData;

    if (param == NULL)
       return;

    nCID = (UINT32)param;

    memset(&rReqData, 0, sizeof(REQUEST_DATA));
    if (!PrintStringNullTerminate(rReqData.szCmd1, sizeof(rReqData.szCmd1), "AT+CGACT=0,%d\r", nCID))
    {
        RIL_LOG_CRITICAL("triggerDeactivateDataCall() - ERROR: Unable to create CGACT command!\r\n");
        return;
    }
    rReqData.pContextData = param;
    CCommand * pCmd = new CCommand(g_arChannelMapping[ND_REQ_ID_DEACTIVATEDATACALL], NULL, ND_REQ_ID_DEACTIVATEDATACALL, rReqData, &CTE::ParseDeactivateDataCall);

    if (pCmd)
    {
        if (!CCommand::AddCmdToQueue(pCmd))
        {
            RIL_LOG_CRITICAL("triggerDeactivateDataCall() - ERROR: Unable to queue command!\r\n");
            delete pCmd;
            pCmd = NULL;
        }
    }
    else
    {
        RIL_LOG_CRITICAL("triggerDeactivateDataCall() - ERROR: Unable to allocate memory for new command!\r\n");
    }

}
