#pragma once

#include "smsdk_ext.h"

extern CGlobalVars* gpGlobals;

//--------------------------------------------------------------------------------------------------------------
class CIntervalTimerHandler : public IHandleTypeDispatch
{
public:
	void OnHandleDestroy(HandleType_t type, void* object)
	{
		CIntervalTimerHandler* pIntervalTimerHandler = (CIntervalTimerHandler*)object;
		delete pIntervalTimerHandler;
	}
};

//--------------------------------------------------------------------------------------------------------------
class CCountdownTimerHandler : public IHandleTypeDispatch
{
public:
	void OnHandleDestroy(HandleType_t type, void* object)
	{
		CCountdownTimerHandler* pCountdownTimerHandler = (CCountdownTimerHandler*)object;
		delete pCountdownTimerHandler;
	}
};

//--------------------------------------------------------------------------------------------------------------
/**
 * Simple class for tracking intervals of game time.
 * Upon creation, the timer is invalidated.  To measure time intervals, start the timer via Start().
 */
class IntervalTimer
{
public:
	IntervalTimer(void)
	{
		m_timestamp = -1.0f;
	}

	void Reset(void)
	{
		m_timestamp = gpGlobals->curtime;
	}

	void Start(void)
	{
		m_timestamp = gpGlobals->curtime;
	}

	void Invalidate(void)
	{
		m_timestamp = -1.0f;
	}

	bool HasStarted(void) const
	{
		return (m_timestamp > 0.0f);
	}

	/// if not started, elapsed time is very large
	float GetElapsedTime(void) const
	{
		return (HasStarted()) ? (gpGlobals->curtime - m_timestamp) : 99999.9f;
	}

	bool IsLessThan(float duration) const
	{
		return (gpGlobals->curtime - m_timestamp < duration) ? true : false;
	}

	bool IsGreaterThan(float duration) const
	{
		return (gpGlobals->curtime - m_timestamp > duration) ? true : false;
	}

private:
	float m_timestamp;
};

//--------------------------------------------------------------------------------------------------------------
/**
 * Simple class for counting down a short interval of time.
 * Upon creation, the timer is invalidated.  Invalidated countdown timers are considered to have elapsed.
 */
class CountdownTimer
{
public:
	CountdownTimer(void)
	{
		m_timestamp = -1.0f;
		m_duration = 0.0f;
	}

	void Reset(void)
	{
		m_timestamp = gpGlobals->curtime + m_duration;
	}

	void Start(float duration)
	{
		m_timestamp = gpGlobals->curtime + duration;
		m_duration = duration;
	}

	void Invalidate(void)
	{
		m_timestamp = -1.0f;
	}

	bool HasStarted(void) const
	{
		return (m_timestamp > 0.0f);
	}

	bool IsElapsed(void) const
	{
		return (gpGlobals->curtime > m_timestamp);
	}

	float GetElapsedTime(void) const
	{
		return gpGlobals->curtime - m_timestamp + m_duration;
	}

	float GetRemainingTime(void) const
	{
		return (m_timestamp - gpGlobals->curtime);
	}

	/// return original countdown time
	float GetCountdownDuration(void) const
	{
		return (m_timestamp > 0.0f) ? m_duration : 0.0f;
	}

private:
	float m_duration;
	float m_timestamp;
};

//--------------------------------------------------------------------------------------------------------------
class MoreTimers : public SDKExtension
{
public:
	/**
	 * @brief This is called after the initial loading sequence has been processed.
	 *
	 * @param error		Error message buffer.
	 * @param maxlen	Size of error message buffer.
	 * @param late		Whether or not the module was loaded after map load.
	 * @return			True to succeed loading, false to fail.
	 */
	 //virtual bool SDK_OnLoad(char* error, size_t maxlen, bool late);

	 /**
	  * @brief This is called right before the extension is unloaded.
	  */
	  //virtual void SDK_OnUnload();

	  /**
	   * @brief This is called once all known extensions have been loaded.
	   * Note: It is is a good idea to add natives here, if any are provided.
	   */
	virtual void SDK_OnAllLoaded();

	/**
	 * @brief Called when the pause state is changed.
	 */
	 //virtual void SDK_OnPauseChange(bool paused);

	 /**
	  * @brief this is called when Core wants to know if your extension is working.
	  *
	  * @param error		Error message buffer.
	  * @param maxlen	Size of error message buffer.
	  * @return			True if working, false otherwise.
	  */
	  //virtual bool QueryRunning(char *error, size_t maxlen);
public:
#if defined SMEXT_CONF_METAMOD
	/**
	 * @brief Called when Metamod is attached, before the extension version is called.
	 *
	 * @param error			Error buffer.
	 * @param maxlen		Maximum size of error buffer.
	 * @param late			Whether or not Metamod considers this a late load.
	 * @return				True to succeed, false to fail.
	 */
	virtual bool SDK_OnMetamodLoad(ISmmAPI* ismm, char* error, size_t maxlen, bool late);

	/**
	 * @brief Called when Metamod is detaching, after the extension version is called.
	 * NOTE: By default this is blocked unless sent from SourceMod.
	 *
	 * @param error			Error buffer.
	 * @param maxlen		Maximum size of error buffer.
	 * @return				True to succeed, false to fail.
	 */
	 //virtual bool SDK_OnMetamodUnload(char *error, size_t maxlen);

	 /**
	  * @brief Called when Metamod's pause state is changing.
	  * NOTE: By default this is blocked unless sent from SourceMod.
	  *
	  * @param paused		Pause state being set.
	  * @param error			Error buffer.
	  * @param maxlen		Maximum size of error buffer.
	  * @return				True to succeed, false to fail.
	  */
	  //virtual bool SDK_OnMetamodPauseChange(bool paused, char *error, size_t maxlen);
#endif
};

//--------------------------------------------------------------------------------------------------------------
namespace MoreTimersNative
{
	static cell_t IntervalTimer_Create(IPluginContext* pContext, const cell_t* params);
	static cell_t IntervalTimer_Reset(IPluginContext* pContext, const cell_t* params);
	static cell_t IntervalTimer_Start(IPluginContext* pContext, const cell_t* params);
	static cell_t IntervalTimer_Invalidate(IPluginContext* pContext, const cell_t* params);
	static cell_t IntervalTimer_HasStarted(IPluginContext* pContext, const cell_t* params);
	static cell_t IntervalTimer_GetElapsedTimed(IPluginContext* pContext, const cell_t* params);
	static cell_t IntervalTimer_IsLessThan(IPluginContext* pContext, const cell_t* params);
	static cell_t IntervalTimer_IsGreaterThan(IPluginContext* pContext, const cell_t* params);

	static cell_t CountdownTimer_Create(IPluginContext* pContext, const cell_t* params);
	static cell_t CountdownTimer_Reset(IPluginContext* pContext, const cell_t* params);
	static cell_t CountdownTimer_Start(IPluginContext* pContext, const cell_t* params);
	static cell_t CountdownTimer_Invalidate(IPluginContext* pContext, const cell_t* params);
	static cell_t CountdownTimer_HasStarted(IPluginContext* pContext, const cell_t* params);
	static cell_t CountdownTimer_IsElapsed(IPluginContext* pContext, const cell_t* params);
	static cell_t CountdownTimer_GetElapsedTime(IPluginContext* pContext, const cell_t* params);
	static cell_t CountdownTimer_GetRemainingTime(IPluginContext* pContext, const cell_t* params);
	static cell_t CountdownTimer_GetCountdownDuration(IPluginContext* pContext, const cell_t* params);

	const sp_nativeinfo_t g_ExtensionNatives[] =
	{
			{"IntervalTimer.IntervalTimer", IntervalTimer_Create},
			{"IntervalTimer.Reset", IntervalTimer_Reset},
			{"IntervalTimer.Start", IntervalTimer_Start},
			{"IntervalTimer.Invalidate", IntervalTimer_Invalidate},
			{"IntervalTimer.HasStarted", IntervalTimer_HasStarted},
			{"IntervalTimer.GetElapsedTime", IntervalTimer_GetElapsedTimed},
			{"IntervalTimer.IsLessThan", IntervalTimer_IsLessThan},
			{"IntervalTimer.IsGreaterThan", IntervalTimer_IsGreaterThan},

			{"CountdownTimer.CountdownTimer", CountdownTimer_Create},
			{"CountdownTimer.Reset", CountdownTimer_Reset},
			{"CountdownTimer.Start", CountdownTimer_Start},
			{"CountdownTimer.Invalidate", CountdownTimer_Invalidate},
			{"CountdownTimer.HasStarted", CountdownTimer_HasStarted},
			{"CountdownTimer.IsElapsed", CountdownTimer_IsElapsed},
			{"CountdownTimer.GetElapsedTime", CountdownTimer_GetElapsedTime},
			{"CountdownTimer.GetRemainingTime", CountdownTimer_GetRemainingTime},
			{"CountdownTimer.GetCountdownDuration", CountdownTimer_GetCountdownDuration},

			{nullptr, nullptr},
	};
}
