/*
 * All or portions of this file Copyright (c) Amazon.com, Inc. or its affiliates or
 * its licensors.
 *
 * For complete copyright and license terms please see the LICENSE at the root of this
 * distribution (the "License"). All use of this software is governed by the License,
 * or, if provided, by the license below or the license accompanying this file. Do not
 * remove or modify any license notices. This file is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *
 */

#pragma once

#include <AzCore/std/optional.h>

#include <chrono>

namespace AzFramework
{
    struct ScreenVector;

    //! Utility class to help detect different types of mouse click (mouse down and up with
    //! no movement), mouse move (down and initial move after some threshold) and mouse release
    //! (mouse down with movement and then mouse up).
    class ClickDetector
    {
        //! Alias for recording time of mouse down events
        using Time = std::chrono::time_point<std::chrono::steady_clock>;

    public:
        //! Internal representation of click event (map from external event for this when
        //! calling DetectClick).
        enum class ClickEvent
        {
            Nil,
            Down,
            Up
        };

        //! The type of mouse click.
        enum class ClickOutcome
        {
            Nil, //!< Not recognized.
            Move, //!< Initial move after mouse down.
            Click, //!< Mouse down and up with no intermediate movement.
            Release //!< Mouse down with movement and then mouse up.
        };

        //! Called from any type of 'handle event' function.
        ClickOutcome DetectClick(ClickEvent clickEvent, const ScreenVector& cursorDelta);

        void SetDoubleClickInterval(float doubleClickInterval);

    private:
        //! Internal state of ClickDetector based on incoming events.
        enum class DetectionState
        {
            Nil, //!< Initial state
            WaitingForMove, //! Mouse down has happened but mouse hasn't yet moved.
            Moved //! Mouse has moved, no longer will be counted as a click.
        };

        float m_moveAccumulator = 0.0f; //!< How far the mouse has moved after mouse down.
        float m_deadZone = 2.0f; //!< How far to move before a click is cancelled (when Move will fire).
        float m_doubleClickInterval = 0.4f; //!< Default double click interval, can be overridden.
        DetectionState m_detectionState; //!< Internal state of ClickDetector.
        AZStd::optional<Time> m_tryBeginTime; //!< Mouse down time (happens each mouse down, helps with double click handling).
    };

    inline void ClickDetector::SetDoubleClickInterval(const float doubleClickInterval)
    {
        m_doubleClickInterval = doubleClickInterval;
    }
} // namespace AzFramework