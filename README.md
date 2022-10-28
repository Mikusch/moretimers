# More Timers

**More Timers** is a SourceMod extension that adds the `IntervalTimer` and `CountdownTimer` classes from the Source SDK as Handle methodmaps.

This is useful if you want Valve-style timers without having to keep track of timestamps and durations by yourself.

**Example:**

```sourcepawn
#include <moretimers>

CountdownTimer g_PrintCountdownTimer;
IntervalTimer g_PrintIntervalTimer;

public void OnPluginStart()
{
	// Initialize our timer variables.
	// Remember to close Handles using the 'delete' operator to avoid memory leaks.
	g_PrintCountdownTimer = new CountdownTimer();
	g_PrintIntervalTimer = new IntervalTimer();
}

public void OnClientPutInServer(int client)
{
	// Start the countdown timer. If restarted while already running, the elapsed time resets.
	g_PrintCountdownTimer.Start(3.0);
}

public void OnGameFrame()
{
	// Use the countdown timer.
	if (g_PrintCountdownTimer.HasStarted() && g_PrintCountdownTimer.IsElapsed())
	{
		g_PrintCountdownTimer.Invalidate();
		LogMessage("New player(s) have joined the server.");
	}
	
	// Start and use the interval timer.
	if (!g_PrintIntervalTimer.HasStarted())
	{
		g_PrintIntervalTimer.Start();
	}
	else if (g_PrintIntervalTimer.IsGreaterThan(10.0))
	{
		g_PrintIntervalTimer.Invalidate();
		LogMessage("This log message sends every 10 seconds.");
	}
}
```
