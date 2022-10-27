/**
 * Copyright (C) 2022  Mikusch
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma semicolon 1
#pragma newdecls required

/**
 * Simple timer for tracking intervals of game time.
 * Upon creation, the timer is invalidated.  To measure time intervals, start the timer via Start().
 */
methodmap IntervalTimer < Handle
{
	/**
	 * Creates a new interval timer.
	 */
	public native IntervalTimer();
	
	/**
	 * Resets this timer.
	 * This is functionally identical to Start().
	 */
	public native void Reset();
	
	/**
	 * Starts this timer.
	 * This is functionally identical to Reset().
	 */
	public native void Start();
	
	/**
	 * Invalidates this timer.
	 */
	public native void Invalidate();
	
	/**
	 * Returns whether this timer has started.
	 *
	 * @return	True if this timer has started, false otherwise.
	 */
	public native bool HasStarted();
	
	/**
	 * Returns the elapsed time of this timer.
	 * If the timer has not started, the returned value is very large.
	 *
	 * @return	The elapsed time.
	 */
	public native float GetElapsedTime();
	
	/**
	 * Returns whether the elapsed time is less than a given value.
	 *
	 * @param duration	Duration to check against.
	 * @return			True if the elapsed time is less than the given value, false otherwise.
	 */
	public native bool IsLessThan(float duration);
	
	/**
	 * Returns whether the elapsed time is greater than a given value.
	 *
	 * @param duration	Duration to check against.
	 * @return			True if the elapsed time is greater than the given value, false otherwise.
	 */
	public native bool IsGreaterThan(float duration);
}

/**
 * Simple timer for counting down a short interval of time.
 * Upon creation, the timer is invalidated.  Invalidated countdown timers are considered to have elapsed.
 */
methodmap CountdownTimer < Handle
{
	/**
	 * Creates a new countdown timer.
	 */
	public native CountdownTimer();
	
	/**
	 * Resets this timer.
	 */
	public native void Reset();
	
	/*
	 * Starts this timer with a given duration.
	 *
	 * @param duration	Duration of the timer.
	 */
	public native void Start(float duration);
	
	/**
	 * Invalidates this timer.
	 */
	public native void Invalidate();
	
	/**
	 * Returns whether this timer has started.
	 *
	 * @return	True if this timer has started, false otherwise.
	 */
	public native bool HasStarted();
	
	/**
	 * Returns whether this timer is considered to have elapsed.
	 *
	 * @return	True if the timer is considered to have elapsed, false otherwise.
	 */
	public native bool IsElapsed();
	
	/**
	 * Returns the elapsed time of this timer.
	 *
	 * @return	The elapsed time.
	 */
	public native float GetElapsedTime();
	
	/**
	 * Returns the remaining time of this timer.
	 *
	 * @return	The remaining time.
	 */
	public native float GetRemainingTime();
	
	/**
	 * Returns the original countdown duration of this timer.
	 *
	 * @return	The countdown duration.
	 */
	public native float GetCountdownDuration();
}
