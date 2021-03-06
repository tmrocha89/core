/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/*
 * This file is part of the LibreOffice project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * This file incorporates work covered by the following license notice:
 *
 *   Licensed to the Apache Software Foundation (ASF) under one or more
 *   contributor license agreements. See the NOTICE file distributed
 *   with this work for additional information regarding copyright
 *   ownership. The ASF licenses this file to you under the Apache
 *   License, Version 2.0 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.apache.org/licenses/LICENSE-2.0 .
 */

#ifndef INCLUDED_VCL_SCHEDULER_HXX
#define INCLUDED_VCL_SCHEDULER_HXX

#include <vcl/dllapi.h>
#include <list>


class Scheduler;
struct ImplSchedulerData
{
    bool        mbDelete;           // Destroy this scheduler?
    Scheduler*  mpScheduler;        // Pointer to VCL Scheduler instance
};

#define MAX_TIMER_PERIOD    SAL_MAX_UINT64

enum class SchedulerPriority {
    HIGHEST   = 0,
    HIGH      = 1,
    RESIZE    = 2,
    REPAINT   = 3,
    MEDIUM    = 3,
    LOW       = 4,
    LOWER     = 5,
    LOWEST    = 6
};

class VCL_DLLPUBLIC Scheduler
{
protected:
    ImplSchedulerData*  mpSchedulerData;    /// Pointer to element in scheduler list
    const sal_Char     *mpDebugName;        /// Useful for debugging
    SchedulerPriority   mePriority;         /// Scheduler priority
    bool                mbActive;           /// Currently in the scheduler
    sal_uInt64          mnUpdateTime;       /// Last Update Time

    friend struct ImplSchedulerData;
    virtual void SetDeletionFlags();
    virtual bool ReadyForSchedule( bool bTimer ) = 0;
    virtual sal_uInt64 UpdateMinPeriod( sal_uInt64 nMinPeriod, sal_uInt64 nTime ) = 0;

public:
    Scheduler( const sal_Char *pDebugName = NULL );
    Scheduler( const Scheduler& rScheduler );
    virtual ~Scheduler();

    void SetPriority( SchedulerPriority ePriority );
    SchedulerPriority GetPriority() const { return mePriority; }

    void            SetDebugName( const sal_Char *pDebugName ) { mpDebugName = pDebugName; }
    const sal_Char *GetDebugName() { return mpDebugName; }

    // Call handler
    virtual void    Invoke() = 0;

    virtual void    Start();
    void            Stop();

    bool            IsActive() const { return mbActive; }
    void            SetInActive() { mbActive = false; }

    Scheduler&      operator=( const Scheduler& rScheduler );
    static void ImplDeInitScheduler(bool bAll=true);
    static void ImplInitScheduler();

    // Process one pending Timer with highest priority
    static void CallbackTaskScheduling( bool ignore );
    /// Process one pending task ahead of time with highest priority.
    static void ProcessTaskScheduling( bool bTimer );

private:
    bool                mbInScheduler;   // Scheduler currently processed?
    sal_uInt32          mnUpdateStack;   // Update Stack

    bool  ImplHandleTaskScheduling(sal_uInt64& nMinPeriod, sal_uInt64 nTime);
    void  ImplInvoke(sal_uInt64 nTime);
    static Scheduler* ImplGetHighestPrioTask( bool bTimer );
    bool ImplIsScheduleReady(sal_uInt32 nUpdateStack);
    void ImplDispose();
};

typedef ::std::list< ImplSchedulerData* > ImplScheduler_t;

#endif // INCLUDED_VCL_SCHEDULER_HXX

/* vim:set shiftwidth=4 softtabstop=4 expandtab: */
