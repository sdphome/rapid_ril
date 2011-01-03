////////////////////////////////////////////////////////////////////////////
// silo.cpp
//
// Copyright 2005-2007 Intrinsyc Software International, Inc.  All rights reserved.
// Patents pending in the United States of America and other jurisdictions.
//
//
// Description:
//    Implements the base class from which the various RIL Silos are derived.
//
// Author:  Dennis Peter
// Created: 2007-07-30
//
/////////////////////////////////////////////////////////////////////////////
//  Modification Log:
//
//  Date        Who      Ver   Description
//  ----------  -------  ----  -----------------------------------------------
//  June 03/08  DP       1.00  Established v1.00 based on current code base.
//  May  04/09  CW       1.01  Moved common code to base class, identified
//                             platform-specific implementations, implemented
//                             general code clean-up.
//
/////////////////////////////////////////////////////////////////////////////

#include "types.h"
#include "util.h"
#include "rillog.h"
#include "extract.h"
#include "channel_nd.h"
#include "response.h"
#include "silo.h"

//
//
CSilo::CSilo(CChannel *pChannel)
: m_pChannel(pChannel),
  m_pATRspTable(NULL),
  m_pATRspTableExt(NULL)

{
}

//
//
CSilo::~CSilo()
{
}

//  Called by CChannel::ParseUnsolicitedResponse() for each silo in the channel.
//  CChannel::ParseUnsolicitedResponse() is in turn called at the beginning of
//  CResponse::ParseUnsolicitedResponse().
//
//  Parameters:
//    [in]      pResponse  = Pointer to CResponse class
//    [in/out]  rszPointer = Pointer to string response buffer.
//    [in/out]  fGotoError = Set to TRUE if we wish to stop response chain and goto Error in CResponse::ParseUnsolicitedResponse().
//
//  Return values:
//    TRUE  if response is handled by this hook, then handling still stop.
//    FALSE if response is not handled by this hook, and handling will continue to other silos, then framework.
//
BOOL CSilo::ParseUnsolicitedResponse(CResponse* const pResponse, const BYTE*& szPointer, BOOL& fGotoError)
{
    //RIL_LOG_VERBOSE("CSilo::ParseUnsolicitedResponse() - Enter\r\n");

    BOOL            fRet = FALSE;
    UINT32          nRow = 0;
    PFN_ATRSP_PARSE fctParser = NULL;

    if (NULL == pResponse)
    {
        RIL_LOG_CRITICAL("CSilo::ParseUnsolicitedResponse() chnl=[%d] - ERROR: pResponse is NULL\r\n", m_pChannel->GetRilChannel());
        fGotoError = TRUE;
    }
    else
    {
        fctParser = FindParser(m_pATRspTable, szPointer);
        if (NULL == fctParser)
        {
            fctParser = FindParser(m_pATRspTableExt, szPointer);
        }
    }

    if (NULL != fctParser)
    {
        // Call the function pointer
        if (!(this->*fctParser)(pResponse, szPointer))
        {
            // There was a problem parsing the response, goto error
            fGotoError = TRUE;
        }
        else
        {
            // We found the response and parsed it correctly
            fRet = TRUE;
        }
    }

    //RIL_LOG_VERBOSE("CSilo::ParseUnsolicitedResponse() - Exit\r\n");
    return fRet;
}

PFN_ATRSP_PARSE CSilo::FindParser(ATRSPTABLE* pRspTable, const BYTE*& pszStr)
{
    PFN_ATRSP_PARSE fctParser = NULL;

    if (NULL != pRspTable && NULL != pszStr)
    {
        for (int nRow = 0; ; ++nRow)
        {
            const BYTE* szATRsp = pRspTable[nRow].szATResponse;
            
            // Check for a valid pointer
            if (NULL == szATRsp)
            {
                RIL_LOG_INFO("CSilo::FindParser() chnl=[%d] - Prefix String pointer is NULL\r\n", m_pChannel->GetRilChannel());
                break;
            }
            
            // Check for the end of the AT response table
            if (0 == strlen(szATRsp))
            {
                break;
            }
            
            if (SkipString(pszStr, szATRsp, pszStr))
            {
                fctParser = m_pATRspTable[nRow].pfnATParseRsp;
                //RIL_LOG_INFO("CSilo::FindParser() chnl=[%d] - Found parse function for response [%s]\r\n",
                //                m_pChannel->GetRilChannel(),
                //                CRLFExpandedString(m_pATRspTable[nRow].szATResponse, strlen(m_pATRspTable[nRow].szATResponse)).GetString());
            
                break;
            }
        }
    }

    return fctParser;
}


//
//
BOOL CSilo::ParseNULL(CResponse *const pResponse, const BYTE* &rszPointer)
{
    return TRUE;
}

//
//
BOOL CSilo::ParseUnrecognized(CResponse *const pResponse, const BYTE* &rszPointer)
{
    RIL_LOG_VERBOSE("CSilo::ParseUnrecognized() - Enter\r\n");
    BOOL fRet = FALSE;

    // Look for a "<postfix>"
    if (!FindAndSkipRspEnd(rszPointer, g_szNewLine, rszPointer))
    {
        // This isn't a complete registration notification -- no need to parse it
        RIL_LOG_CRITICAL("CSilo::ParseUnrecognized() chnl=[%d] - ERROR: Failed to find postfix in the response.\r\n", m_pChannel->GetRilChannel());
        goto Error;
    }

    //  Back up over the "\r\n".
    rszPointer -= 2;

    //  Flag as unrecognized.
    pResponse->SetUnrecognizedFlag(TRUE);

    fRet = TRUE;

Error:
    RIL_LOG_VERBOSE("CSilo::ParseUnrecognized() - Exit\r\n");
    return fRet;
}
