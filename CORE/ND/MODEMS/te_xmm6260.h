////////////////////////////////////////////////////////////////////////////
// te_xmm6260.h
//
// Copyright 2009 Intrinsyc Software International, Inc.  All rights reserved.
// Patents pending in the United States of America and other jurisdictions.
//
//
// Description:
//    Overlay for the IMC 6260 modem
//
/////////////////////////////////////////////////////////////////////////////

#ifndef RRIL_TE_XMM6260_H
#define RRIL_TE_XMM6260_H

#include "te_base.h"
#include "rril.h"
#include "channel_data.h"

class CEvent;

class CTE_XMM6260 : public CTEBase
{
public:

    CTE_XMM6260(CTE& cte);
    virtual ~CTE_XMM6260();

private:

    CTE_XMM6260();

    //  Prevent assignment: Declared but not implemented.
    CTE_XMM6260(const CTE_XMM6260& rhs);  // Copy Constructor
    CTE_XMM6260& operator=(const CTE_XMM6260& rhs);  //  Assignment operator

protected:
    int m_currentNetworkType;
    char m_szUICCID[MAX_PROP_VALUE];

public:
    // modem overrides

    // RIL_REQUEST_GET_SIM_STATUS 1
    virtual RIL_RESULT_CODE CoreGetSimStatus(REQUEST_DATA & rReqData, void * pData, UINT32 uiDataSize);
    virtual RIL_RESULT_CODE ParseGetSimStatus(RESPONSE_DATA & rRspData);

    virtual RIL_RESULT_CODE ParseEnterSimPin(RESPONSE_DATA & rRspData);

    // RIL_REQUEST_SETUP_DATA_CALL 27
    virtual RIL_RESULT_CODE CoreSetupDataCall(REQUEST_DATA & rReqData, void * pData, UINT32 uiDataSize, UINT32 uiCID);
    virtual RIL_RESULT_CODE ParseSetupDataCall(RESPONSE_DATA & rRspData);

    // RIL_REQUEST_SIM_IO 28
    virtual RIL_RESULT_CODE CoreSimIo(REQUEST_DATA & rReqData, void * pData, UINT32 uiDataSize);
    virtual RIL_RESULT_CODE ParseSimIo(RESPONSE_DATA & rRspData);

    // RIL_REQUEST_DEACTIVATE_DATA_CALL 41
    virtual RIL_RESULT_CODE CoreDeactivateDataCall(REQUEST_DATA & rReqData, void * pData, UINT32 uiDataSize);
    virtual RIL_RESULT_CODE ParseDeactivateDataCall(RESPONSE_DATA & rRspData);

    // RIL_REQUEST_OEM_HOOK_RAW 59
    virtual RIL_RESULT_CODE CoreHookRaw(REQUEST_DATA & rReqData, void * pData, UINT32 uiDataSize, UINT32 & uiRilChannel);
    virtual RIL_RESULT_CODE ParseHookRaw(RESPONSE_DATA & rRspData);

    // RIL_REQUEST_OEM_HOOK_STRINGS 60
    virtual RIL_RESULT_CODE CoreHookStrings(REQUEST_DATA& rReqData, void* pData, UINT32 uiDataSize, UINT32 & uiRilChannel);
    virtual RIL_RESULT_CODE ParseHookStrings(RESPONSE_DATA& rRspData);

    // RIL_REQUEST_SET_BAND_MODE 65
    virtual RIL_RESULT_CODE CoreSetBandMode(REQUEST_DATA & rReqData, void * pData, UINT32 uiDataSize);
    virtual RIL_RESULT_CODE ParseSetBandMode(RESPONSE_DATA & rRspData);

    // RIL_REQUEST_QUERY_AVAILABLE_BAND_MODE 66
    virtual RIL_RESULT_CODE CoreQueryAvailableBandMode(REQUEST_DATA & rReqData, void * pData, UINT32 uiDataSize);
    virtual RIL_RESULT_CODE ParseQueryAvailableBandMode(RESPONSE_DATA & rRspData);

    // RIL_REQUEST_STK_GET_PROFILE 67
    virtual RIL_RESULT_CODE CoreStkGetProfile(REQUEST_DATA & rReqData, void * pData, UINT32 uiDataSize);
    virtual RIL_RESULT_CODE ParseStkGetProfile(RESPONSE_DATA & rRspData);

    // RIL_REQUEST_STK_SET_PROFILE 68
    virtual RIL_RESULT_CODE CoreStkSetProfile(REQUEST_DATA & rReqData, void * pData, UINT32 uiDataSize);
    virtual RIL_RESULT_CODE ParseStkSetProfile(RESPONSE_DATA & rRspData);

    // RIL_REQUEST_STK_SEND_ENVELOPE_COMMAND 69
    virtual RIL_RESULT_CODE CoreStkSendEnvelopeCommand(REQUEST_DATA & rReqData, void * pData, UINT32 uiDataSize);
    virtual RIL_RESULT_CODE ParseStkSendEnvelopeCommand(RESPONSE_DATA & rRspData);

    // RIL_REQUEST_STK_SEND_TERMINAL_RESPONSE 70
    virtual RIL_RESULT_CODE CoreStkSendTerminalResponse(REQUEST_DATA & rReqData, void * pData, UINT32 uiDataSize);
    virtual RIL_RESULT_CODE ParseStkSendTerminalResponse(RESPONSE_DATA & rRspData);

    // RIL_REQUEST_STK_HANDLE_CALL_SETUP_REQUESTED_FROM_SIM 71
    virtual RIL_RESULT_CODE CoreStkHandleCallSetupRequestedFromSim(REQUEST_DATA & rReqData, void * pData, UINT32 uiDataSize);
    virtual RIL_RESULT_CODE ParseStkHandleCallSetupRequestedFromSim(RESPONSE_DATA & rRspData);

    // RIL_REQUEST_SET_PREFERRED_NETWORK_TYPE 73
    virtual RIL_RESULT_CODE CoreSetPreferredNetworkType(REQUEST_DATA & rReqData, void * pData, UINT32 uiDataSize);
    virtual RIL_RESULT_CODE ParseSetPreferredNetworkType(RESPONSE_DATA & rRspData);

    // RIL_REQUEST_GET_PREFERRED_NETWORK_TYPE 74
    virtual RIL_RESULT_CODE CoreGetPreferredNetworkType(REQUEST_DATA & rReqData, void * pData, UINT32 uiDataSize);
    virtual RIL_RESULT_CODE ParseGetPreferredNetworkType(RESPONSE_DATA & rRspData);

    // RIL_REQUEST_GET_NEIGHBORING_CELL_IDS 75
    virtual RIL_RESULT_CODE CoreGetNeighboringCellIDs(REQUEST_DATA & rReqData, void * pData, UINT32 uiDataSize);
    virtual RIL_RESULT_CODE ParseGetNeighboringCellIDs(RESPONSE_DATA & rRspData);

    // RIL_REQUEST_SET_TTY_MODE 80
    virtual RIL_RESULT_CODE CoreSetTtyMode(REQUEST_DATA & rReqData, void * pData, UINT32 uiDataSize);
    virtual RIL_RESULT_CODE ParseSetTtyMode(RESPONSE_DATA & rRspData);

    // RIL_REQUEST_QUERY_TTY_MODE 81
    virtual RIL_RESULT_CODE CoreQueryTtyMode(REQUEST_DATA & rReqData, void * pData, UINT32 uiDataSize);
    virtual RIL_RESULT_CODE ParseQueryTtyMode(RESPONSE_DATA & rRspData);

    // RIL_REQUEST_SMS_MEMORY_STATUS 102
    virtual RIL_RESULT_CODE CoreReportSmsMemoryStatus(REQUEST_DATA & rReqData, void * pData, UINT32 uiDataSize);
    virtual RIL_RESULT_CODE ParseReportSmsMemoryStatus(RESPONSE_DATA & rRspData);

    // RIL_REQUEST_REPORT_STK_SERVICE_IS_RUNNING 103
    virtual RIL_RESULT_CODE CoreReportStkServiceRunning(REQUEST_DATA & rReqData, void * pData, UINT32 uiDataSize);
    virtual RIL_RESULT_CODE ParseReportStkServiceRunning(RESPONSE_DATA & rRspData);

    // RIL_REQUEST_STK_SEND_ENVELOPE_WITH_STATUS 107
    virtual RIL_RESULT_CODE ParseStkSendEnvelopeWithStatus(RESPONSE_DATA & rRspData);

    // internal response handlers
    virtual RIL_RESULT_CODE ParsePdpContextActivate(RESPONSE_DATA& rRspData);
    virtual RIL_RESULT_CODE ParseQueryIpAndDns(RESPONSE_DATA& rRspData);
    virtual RIL_RESULT_CODE ParseEnterDataState(RESPONSE_DATA& rRspData);

    // Silent Pin Entry request and response handler
    virtual BOOL HandleSilentPINEntry(void* pRilToken, void* pContextData, int dataSize);
    virtual RIL_RESULT_CODE ParseSilentPinEntry(RESPONSE_DATA& rRspData);

    // PIN retry count request and response handler
    virtual RIL_RESULT_CODE QueryPinRetryCount(REQUEST_DATA& rReqData,
                                                            void* pData, UINT32 uiDataSize);
    virtual RIL_RESULT_CODE ParseSimPinRetryCount(RESPONSE_DATA& rRspData);

    // Handles the PIN2 provided SIM IO requests
    RIL_RESULT_CODE HandlePin2RelatedSIMIO(RIL_SIM_IO_v6* pSimIOArgs,
                                           REQUEST_DATA& rReqData);

    virtual BOOL CreatePdpContextActivateReq(UINT32 uiChannel, RIL_Token rilToken,
                                    UINT32 uiReqId,void* pData,
                                    UINT32 uiDataSize, PFN_TE_PARSE pParseFcn,
                                    PFN_TE_POSTCMDHANDLER pPostCmdHandlerFcn);
    virtual BOOL CreateQueryIpAndDnsReq(UINT32 uiChannel, RIL_Token rilToken,
                                    UINT32 uiReqId, void* pData,
                                    UINT32 uiDataSize, PFN_TE_PARSE pParseFcn,
                                    PFN_TE_POSTCMDHANDLER pPostCmdHandlerFcn);
    virtual BOOL CreateEnterDataStateReq(UINT32 uiChannel, RIL_Token rilToken,
                                    UINT32 uiReqId, void* pData,
                                    UINT32 uiDataSize, PFN_TE_PARSE pParseFcn,
                                    PFN_TE_POSTCMDHANDLER pPostCmdHandlerFcn);
    virtual BOOL PdpContextActivate(REQUEST_DATA& rReqData, void* pData,
                                    UINT32 uiDataSize);
    virtual BOOL QueryIpAndDns(REQUEST_DATA& rReqData, UINT32 uiCID);
    virtual BOOL EnterDataState(REQUEST_DATA& rReqData, UINT32 uiCID);

    virtual void PostSetupDataCallCmdHandler(POST_CMD_HANDLER_DATA& rData);
    virtual void PostPdpContextActivateCmdHandler(POST_CMD_HANDLER_DATA& rData);
    virtual void PostQueryIpAndDnsCmdHandler(POST_CMD_HANDLER_DATA& rData);
    virtual void PostEnterDataStateCmdHandler(POST_CMD_HANDLER_DATA& rData);

    virtual void PostDeactivateDataCallCmdHandler(POST_CMD_HANDLER_DATA& rData);

    virtual BOOL SetupInterface(UINT32 uiCID);

    virtual void HandleSetupDataCallSuccess(UINT32 uiCID, void* pRilToken);
    virtual void HandleSetupDataCallFailure(UINT32 uiCID, void* pRilToken,
                                                    UINT32 uiResultCode);

    virtual BOOL DataConfigDown(UINT32 uiCID);

private:
    RIL_RESULT_CODE CreateGetThermalSensorValuesReq(REQUEST_DATA& rReqData,
                                                    const char** pszRequest,
                                                    const UINT32 uiDataSize);
    RIL_RESULT_CODE CreateActivateThermalSensorInd(REQUEST_DATA& rReqData,
                                                    const char** pszRequest,
                                                    const UINT32 uiDataSize);
    RIL_RESULT_CODE CreateAutonomousFDReq(REQUEST_DATA& rReqData,
                                          const char** pszRequest,
                                          const UINT32 uiDataSize);
    RIL_RESULT_CODE CreateSetSMSTransportModeReq(REQUEST_DATA& rReqData,
                                                 const char** pszRequest,
                                                 const UINT32 uiDataSize);
    RIL_RESULT_CODE CreateDebugScreenReq(REQUEST_DATA& rReqData,
                                          const char** pszRequest,
                                          const UINT32 uiDataSize);
    RIL_RESULT_CODE ParseXGATR(const char* pszRsp, RESPONSE_DATA& rRspData);
    RIL_RESULT_CODE ParseXDRV(const char* pszRsp, RESPONSE_DATA& rRspData);
    RIL_RESULT_CODE ParseCGED(const char* pszRsp, RESPONSE_DATA& rRspData);
    RIL_RESULT_CODE ParseXCGEDPAGE(const char* pszRsp, RESPONSE_DATA& rRspData);
    RIL_RESULT_CODE ParseCGSMS(const char* pszRsp, RESPONSE_DATA& rRspData);
    // internal response handlers
    RIL_RESULT_CODE ParseIpAddress(RESPONSE_DATA& rRspData);
    RIL_RESULT_CODE ParseDns(RESPONSE_DATA& rRspData);
#if defined(M2_DUALSIM_FEATURE_ENABLED)
    RIL_RESULT_CODE ParseSwapPS(const char* pszRsp, RESPONSE_DATA& rRspData);
#endif // M2_DUALSIM_FEATURE_ENABLED
};

#endif