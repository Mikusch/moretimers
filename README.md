# More Timers

**More Timers** is a SourceMod extension that adds the `IntervalTimer` and `CountdownTimer` classes from the Source SDK to SourceMod as Handles.

This can be useful if you want Valve-style timers without having to keep track of timestamps and durations yourself, though for most people the standard SourceMod timers are sufficient.

**Example:**

```sourcepawn
#include <sourcemod>
#include <moretimers>

CountdownTimer g_PrintCountdownTimer;
IntervalTimer g_PrintIntervalTimer;

public void OnPluginStart()
{
	// Initialize timer handles.
	// Remember to 'delete' handles when they are not needed anymore!
	g_PrintCountdownTimer = new CountdownTimer();
	g_PrintIntervalTimer = new IntervalTimer();
}

public void OnClientPutInServer(int client)
{
	// Start the countdown timer.
	g_PrintCountdownTimer.Start(3.0);
}

public void OnGameFrame()
{
	// Handle the countdown timer.
	if (g_PrintCountdownTimer.HasStarted() && g_PrintCountdownTimer.IsElapsed())
	{
		g_PrintCountdownTimer.Invalidate();
		LogMessage("New player(s) have joined the server.");
	}
	
	// Start the interval timer.
	if (!g_PrintIntervalTimer.HasStarted())
	{
		g_PrintIntervalTimer.Start();
	}
	
	// Handle the interval timer.
	if (g_PrintIntervalTimer.IsGreaterThan(30.0))
	{
		g_PrintIntervalTimer.Invalidate();
		LogMessage("This log message sends every 30 seconds.");
	}
}
```
