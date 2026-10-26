# Emberveil Desktop Indicator — development plan

Based on Simon Benedict's Taskbar Desktop Indicator (MIT). Preserve attribution and upstream license when publishing.

## v1.4.0-dev.1 (prepared)
- Independent fork identity and settings schema for six placement modes.
- Existing clock rendering retained as a safe fallback.
- Five new placements are **not implemented** yet. Selecting them logs a warning and continues to render at the clock.
- Not compiled or runtime-tested.

## v1.4.0-dev.2 (implementation)
- Separate the indicator rendering from clock text mutation.
- Identify XAML taskbar root and per-monitor taskbar containers on supported Windows 11 builds.
- Implement before/after app group, before tray, after clock at far edge, and physical-center anchoring.
- Account for top/bottom taskbar, multiple monitors, DPI, taskbar bounds, clipping and Show Desktop hit target.
- Restore original layout and detach owned elements on unload; rebind on Explorer restart.

## v1.4.0-dev.3 (appearance)
- Port exact theme names, palette and semantics from Mawaqit v0.6.9 after obtaining its final source.
- Keep an Emberveil palette as an additional preset; allow custom overrides.

## Regression checks
- All six positions, centered/left-aligned taskbar icons, top/bottom placement, single/multiple monitors.
- Virtual desktop create/delete/reorder/name/switch; clock remains unchanged in non-clock modes.
- Taskbar auto-hide, scaling, Explorer restart, disable/re-enable, unload cleanup.
- Windhawk compile and logs without warnings/errors.
