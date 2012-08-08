////////////////////////////////////////////////////////////////////////////
// silo_network.h
//
// Copyright 2005-2007 Intrinsyc Software International, Inc.  All rights reserved.
// Patents pending in the United States of America and other jurisdictions.
//
//
// Description:
//    Defines the CSilo_Network class, which provides response handlers and
//    parsing functions for the network-related RIL components.
//
/////////////////////////////////////////////////////////////////////////////
//
//  Network silo class.  This class handles all network functionality including:
//  -Register on network
//  -Unregister from network
//  -Get operator list
//  -Get current operator
//  -Get own number (Get Subscriber Number)
//  -Get preferred operator list
//  -Add/Remove preferred operator
//

#ifndef RRIL_SILO_NETWORK_H
#define RRIL_SILO_NETWORK_H

#include "silo.h"

class CSilo_Network : public CSilo
{
public:
    CSilo_Network(CChannel *pChannel);
    virtual ~CSilo_Network();

protected:
    enum SILO_NETWORK_REGISTRATION_TYPES
        {
        SILO_NETWORK_CREG,
        SILO_NETWORK_CGREG,
        SILO_NETWORK_XREG
        };

protected:
    //  Parse notification functions here.
    virtual BOOL    ParseRegistrationStatus(CResponse* const pResponse, const char*& rszPointer,
                                            SILO_NETWORK_REGISTRATION_TYPES regType);
    virtual BOOL    ParseXNITZINFO(CResponse* const pResponse, const char*& rszPointer);
    virtual BOOL    ParseCREG(CResponse* const pResponse, const char*& rszPointer);
    virtual BOOL    ParseCGREG(CResponse* const pResponse, const char*& rszPointer);
    virtual BOOL    ParseXREG(CResponse* const pResponse, const char*& rszPointer);
    virtual BOOL    ParseCGEV(CResponse* const pResponse, const char*& rszPointer);
    virtual BOOL    ParseXCSQ(CResponse* const pResponse, const char*& rszPointer);
    virtual BOOL    ParseXDATASTAT(CResponse* const pResponse, const char* &rszPointer);

private:
    BOOL GetContextIdFromDeact(const char* pData, UINT32& uiCID);
#if defined(M2_DUALSIM_FEATURE_ENABLED)
    BOOL ParseXREGFastOoS(CResponse *const pResponse, const char* &rszPointer);
#endif // M2_DUALSIM_FEATURE_ENABLED
};

#endif // RRIL_SILO_NETWORK_H
