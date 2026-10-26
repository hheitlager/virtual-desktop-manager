# Emberveil Desktop Indicator — Mawaqit positioning-engine port

Status: engineering handoff, **not a compiled or working positioning implementation**.

Sources reviewed:
- `emberveil-desktop-indicator.wh.cpp` (v1.4.0-dev.1)
- `windhawk-mawaqit-v0.6.9-final-test.wh.cpp` (Mawaqit final regression baseline)

## Reuse from Mawaqit

1. `folder_menus_taskbar_window`, `folder_menus_dispatch`, `folder_menus_taskbar_xaml` for taskbar HWND discovery, UI-thread dispatch, and XAML-root discovery. These helpers depend on Windhawk symbol hooks and should be ported together, not pasted in isolation.
2. `FindApplicationRepeater`: identify `TaskbarFrameRepeater` and its supported parent.
3. `ResolvePositionParent`: adapt five modes to desktop indicator's enum. For `AfterStartBeforeIcons`, use before-icons anchor; `AfterStartAfterIcons`, use after-icons overlay; `BeforeTray`, use before-tray slot; `AfterClock`, use after-show-desktop anchor and verify it truly follows clock; `DynamicCenter`, use full taskbar Grid.
4. `UpdateDynamicCenterOnUiThread` and `UpdateAfterIconsOnUiThread`: adapt pill references to indicator XAML element. Recompute from realized button bounds and tray origin.
5. `EnsureTaskbarSlotOnUiThread`, startup worker, settings application, and teardown: preserve UI-thread ownership and recover from XAML recreation.

## Adapt from desktop indicator

Keep `ReadVirtualDesktopIds`, `ReadCurrentDesktopNumberFromRegistry`, `ReadVirtualDesktopNames`, notification registration, and polling fallback. Replace `UpdateAllClockEntries` with a dispatcher that refreshes the independent indicator `TextBlock` on the taskbar XAML thread. Existing `BuildIndicatorCoreText`, marker segments, number formatting and color parsing can be adapted to independent XAML rendering.

## Safety/compatibility requirements

- Disable the old clock suffix rendering when independent positioning is selected. Never show both.
- Never mutate XAML objects from desktop notification thread. Dispatch to taskbar UI thread.
- Keep `Clock` fallback as an explicit mode, but do not silently fall back when another position fails: log and retry or hide.
- For `AfterClock`, verify visual-tree ordering on target Windows build; Show Desktop may be a separate trailing target.
- Support secondary taskbars explicitly or document primary-only behavior.
- On unload, detach events, restore leased grid columns and remove injected controls before Explorer teardown.
- Avoid unbounded retries, duplicate inserts and stale weak references.
- Validate compatibility with taskbar customization mods, top taskbar, scaling, and Explorer restart.

## Current state

The v1.4.0-dev.1 fork contains position enum/settings but still logs that new positions fall back to clock. No tested native insertion engine has been integrated yet. This document intentionally does not represent that as implemented.
