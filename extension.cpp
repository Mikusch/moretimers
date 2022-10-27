#include "extension.h"
#include "ISDKTools.h"

CGlobalVars* gpGlobals = nullptr;

HandleType_t g_IntervalTimerHandleType;
HandleType_t g_CountdownTimerHandleType;
CIntervalTimerHandler g_IntervalTimerHandler;
CCountdownTimerHandler g_CountdownTimerHandler;

MoreTimers g_MoreTimers;
SMEXT_LINK(&g_MoreTimers);

template<typename T>
inline T* GetObjFromHandle(HandleType_t type, cell_t cellhandle, IPluginContext* pContext)
{
	Handle_t handle = (Handle_t)cellhandle;
	HandleError hndlError;
	HandleSecurity hndlSecurity;

	hndlSecurity.pOwner = pContext->GetIdentity();
	hndlSecurity.pIdentity = myself->GetIdentity();

	T* obj = nullptr;
	if ((hndlError = g_pHandleSys->ReadHandle(handle, type, &hndlSecurity, (void**)&obj)) != HandleError_None)
	{
		if (!pContext)
		{
			smutils->LogError(myself, "Invalid timer handle %x (error %d)", handle, hndlError);
		}
		else
		{
			pContext->ThrowNativeError("Invalid timer handle %x (error %d)", handle, hndlError);
		}

		return nullptr;
	}

	return obj;
}

void MoreTimers::SDK_OnAllLoaded()
{
	if (!handlesys->FindHandleType("IntervalTimer", &g_IntervalTimerHandleType))
	{
		g_IntervalTimerHandleType = handlesys->CreateType("IntervalTimer", &g_IntervalTimerHandler, 0, nullptr, nullptr, myself->GetIdentity(), nullptr);
	}

	if (!handlesys->FindHandleType("CountdownTimer", &g_CountdownTimerHandleType))
	{
		g_CountdownTimerHandleType = handlesys->CreateType("CountdownTimer", &g_CountdownTimerHandler, 0, nullptr, nullptr, myself->GetIdentity(), nullptr);
	}

	sharesys->AddNatives(myself, MoreTimersNative::g_ExtensionNatives);
	sharesys->RegisterLibrary(myself, "moretimers");
}

bool MoreTimers::SDK_OnMetamodLoad(ISmmAPI* ismm, char* error, size_t maxlen, bool late)
{
	gpGlobals = ismm->GetCGlobals();

	return true;
}

namespace MoreTimersNative
{
	static cell_t IntervalTimer_Create(IPluginContext* pContext, const cell_t* params)
	{
		auto* pIntervalTimer = new IntervalTimer();

		if (!pIntervalTimer)
		{
			return 0;
		}

		return handlesys->CreateHandle(g_IntervalTimerHandleType, pIntervalTimer, pContext->GetIdentity(), myself->GetIdentity(), NULL);
	}

	static cell_t IntervalTimer_Reset(IPluginContext* pContext, const cell_t* params)
	{
		auto* pIntervalTimer = GetObjFromHandle<IntervalTimer>(g_IntervalTimerHandleType, params[1], pContext);
		if (pIntervalTimer)
		{
			pIntervalTimer->Reset();
		}

		return 0;
	}

	static cell_t IntervalTimer_Start(IPluginContext* pContext, const cell_t* params)
	{
		auto* pIntervalTimer = GetObjFromHandle<IntervalTimer>(g_IntervalTimerHandleType, params[1], pContext);
		if (pIntervalTimer)
		{
			pIntervalTimer->Start();
		}

		return 0;
	}

	static cell_t IntervalTimer_Invalidate(IPluginContext* pContext, const cell_t* params)
	{
		auto* pIntervalTimer = GetObjFromHandle<IntervalTimer>(g_IntervalTimerHandleType, params[1], pContext);
		if (pIntervalTimer)
		{
			pIntervalTimer->Invalidate();
		}

		return 0;
	}

	static cell_t IntervalTimer_HasStarted(IPluginContext* pContext, const cell_t* params)
	{
		auto* pIntervalTimer = GetObjFromHandle<IntervalTimer>(g_IntervalTimerHandleType, params[1], pContext);
		if (pIntervalTimer)
		{
			return pIntervalTimer->HasStarted();
		}

		return 0;
	}

	static cell_t IntervalTimer_GetElapsedTimed(IPluginContext* pContext, const cell_t* params)
	{
		auto* pIntervalTimer = GetObjFromHandle<IntervalTimer>(g_IntervalTimerHandleType, params[1], pContext);
		if (pIntervalTimer)
		{
			return sp_ftoc(pIntervalTimer->GetElapsedTime());
		}

		return 0;
	}

	static cell_t IntervalTimer_IsLessThan(IPluginContext* pContext, const cell_t* params)
	{
		auto* pIntervalTimer = GetObjFromHandle<IntervalTimer>(g_IntervalTimerHandleType, params[1], pContext);
		if (pIntervalTimer)
		{
			return pIntervalTimer->IsLessThan(sp_ctof(params[2]));
		}

		return 0;
	}

	static cell_t IntervalTimer_IsGreaterThan(IPluginContext* pContext, const cell_t* params)
	{
		auto* pIntervalTimer = GetObjFromHandle<IntervalTimer>(g_IntervalTimerHandleType, params[1], pContext);
		if (pIntervalTimer)
		{
			return pIntervalTimer->IsGreaterThan(sp_ctof(params[2]));
		}

		return 0;
	}

	static cell_t CountdownTimer_Create(IPluginContext* pContext, const cell_t* params)
	{
		auto* pCountdownTimer = new CountdownTimer();

		if (!pCountdownTimer)
		{
			return 0;
		}

		return handlesys->CreateHandle(g_CountdownTimerHandleType, pCountdownTimer, pContext->GetIdentity(), myself->GetIdentity(), NULL);
	}

	static cell_t CountdownTimer_Reset(IPluginContext* pContext, const cell_t* params)
	{
		auto* pCountdownTimer = GetObjFromHandle<CountdownTimer>(g_CountdownTimerHandleType, params[1], pContext);
		if (pCountdownTimer)
		{
			pCountdownTimer->Reset();
		}

		return 0;
	}

	static cell_t CountdownTimer_Start(IPluginContext* pContext, const cell_t* params)
	{
		auto* pCountdownTimer = GetObjFromHandle<CountdownTimer>(g_CountdownTimerHandleType, params[1], pContext);
		if (pCountdownTimer)
		{
			pCountdownTimer->Start(sp_ctof(params[2]));
		}

		return 0;
	}

	static cell_t CountdownTimer_Invalidate(IPluginContext* pContext, const cell_t* params)
	{
		auto* pCountdownTimer = GetObjFromHandle<CountdownTimer>(g_CountdownTimerHandleType, params[1], pContext);
		if (pCountdownTimer)
		{
			pCountdownTimer->Invalidate();
		}

		return 0;
	}

	static cell_t CountdownTimer_HasStarted(IPluginContext* pContext, const cell_t* params)
	{
		auto* pCountdownTimer = GetObjFromHandle<CountdownTimer>(g_CountdownTimerHandleType, params[1], pContext);
		if (pCountdownTimer)
		{
			return pCountdownTimer->HasStarted();
		}

		return 0;
	}

	static cell_t CountdownTimer_IsElapsed(IPluginContext* pContext, const cell_t* params)
	{
		auto* pCountdownTimer = GetObjFromHandle<CountdownTimer>(g_CountdownTimerHandleType, params[1], pContext);
		if (pCountdownTimer)
		{
			return pCountdownTimer->IsElapsed();
		}

		return 0;
	}

	static cell_t CountdownTimer_GetElapsedTime(IPluginContext* pContext, const cell_t* params)
	{
		auto* pCountdownTimer = GetObjFromHandle<CountdownTimer>(g_CountdownTimerHandleType, params[1], pContext);
		if (pCountdownTimer)
		{
			return sp_ftoc(pCountdownTimer->GetElapsedTime());
		}

		return 0;
	}

	static cell_t CountdownTimer_GetRemainingTime(IPluginContext* pContext, const cell_t* params)
	{
		auto* pCountdownTimer = GetObjFromHandle<CountdownTimer>(g_CountdownTimerHandleType, params[1], pContext);
		if (pCountdownTimer)
		{
			return sp_ftoc(pCountdownTimer->GetRemainingTime());
		}

		return 0;
	}

	static cell_t CountdownTimer_GetCountdownDuration(IPluginContext* pContext, const cell_t* params)
	{
		auto* pCountdownTimer = GetObjFromHandle<CountdownTimer>(g_CountdownTimerHandleType, params[1], pContext);
		if (pCountdownTimer)
		{
			return sp_ftoc(pCountdownTimer->GetCountdownDuration());
		}

		return 0;
	}
}
