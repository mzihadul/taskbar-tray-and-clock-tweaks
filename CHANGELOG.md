# Changelog

All notable changes to **Taskbar Tray & Clock Tweaks** are documented in this file.

## [1.3.0] - 2026-09-23

### Added
- **Taskbar Control & Icon Styling Engine:**
  - Integrated full styling engine from *Windows 11 Taskbar Styler*.
  - Added support for targeting XAML controls by type, class, name, or automation ID (e.g. `Taskbar.TaskListButton[AutomationProperties.AutomationId=Appid: ...]`).
  - Added property overrides for taskbar elements (`Source` for custom app icons, `Width`, `Height`, `CornerRadius`, `Background`, `Margin`, etc.).
  - Added support for local image files and remote image URLs with offline disk caching and automatic retry upon network reconnection.
  - Added embedded `<WindhawkBlur ... />` brush support and XAML markup syntax (`:=`).
  - Added visual state styling support (`Style@VisualState=Value`).
  - Added dynamic style variable extraction and propagation (`Property=>VarName`, `{{VarName}}`).
  - Added theme resource variable overrides with dark/light mode detection (`Key@Dark=Value`, `Key@Light=Value`).
  - Added `xamlDiagnosticsHandling` setting (`alert`, `block`, `allow`) to handle external XAML diagnostics consumers cleanly.

### Changed
- Refactored initialization routine to coordinate XAML visual tree hooks alongside system tray and clock hooks.
- Updated compiler options to include `-ldxgi`, `-lpdh`, `-lpowrprof`, and related Windows Runtime libraries.

## [v1.2.1] - 2026-09-22

### Bug Fix
- Fixed: "Hide Running/Pinned Apps" had no effect.

## [v1.2.0] - 2026-09-22

### Added

- Added configurable Taskbar Transparency Mode for Windows 11.
- Added the following transparency modes:
  - Default
  - Fully Transparent
  - Blurry Glass
  - Liquid Glass (Acrylic)
  - Mica
- Added Transparency Level control from 0% to 100%.
- Added support for applying transparency to the primary taskbar.
- Added handling for secondary taskbar windows.
- Added XAML taskbar background handling for the Windows 11 taskbar.
- Added DWM-based composition handling for supported transparency modes.
- Added Mica material support through Windows DWM.
- Added restoration of the original taskbar composition when the mod is unloaded.
- Added reapplication of transparency when the taskbar/XAML interface is recreated.
- Added Hide Running/Pinned Apps option.
- Added the ability to hide taskbar application buttons while retaining the taskbar, Start/Search, and system-tray areas.
- Added App Exceptions.
- Added support for identifying exceptions using:
  - AUMID
  - Visible application name
- Added case-insensitive application matching.
- Added partial-name matching for application exceptions.
- Added handling for application identity information exposed through taskbar button elements.

### Changed

- Expanded the mod description to include taskbar transparency and application visibility controls.
- Expanded the Windhawk README documentation with the new v1.2.0 functionality.
- Integrated transparency and application-visibility handling into the existing taskbar/XAML lifecycle.
- Transparency is now reapplied when the Windows 11 taskbar visual tree is recreated.
- Taskbar application visibility is reapplied as taskbar buttons are created.
- Transparency and application-visibility settings are restored automatically when the mod is unloaded.
- Updated taskbar processing so the transparency and application-visibility features operate alongside the existing tray, clock, and taskbar-size functionality.

## [v1.1.0] — 2026-09-20

### Added

- Added **Taskbar Height & Icon Size** support for the Windows 11 new/XAML taskbar.
- Added configurable taskbar height.
- Added configurable main taskbar icon size.
- Added configurable taskbar button width.
- Added separate small-icon size support for newer Windows 11 builds.
- Added separate small taskbar button width support.
- Added handling for Windows 11 taskbar size settings so the mod can apply its custom icon sizing.
- Added taskbar frame-size handling for both the primary and secondary taskbar/system-tray controllers.
- Added icon-loading hooks to support the configured icon size, including small-icon handling.
- Added taskbar icon-height hooks for task-list and task-group views.
- Added handling for taskbar setting changes and dynamic module loading.
- Added restoration of the original taskbar height when the mod is unloaded.
- Added settings-change handling so taskbar sizing is reapplied when the mod configuration changes.
- Added the required `shcore` compiler library for the new taskbar sizing implementation.

### Changed

- Updated the mod version from **1.0.0** to **1.1.0**.
- Expanded the mod description to include taskbar height and icon-size control.
- Expanded the Windhawk README section with documentation for the new taskbar sizing feature.
- Updated the project attribution references to the specific upstream Windhawk source files.
- Updated the project background from a two-project integration to a three-project integration.
- Refined the description of the battery-related clock styling.
- The new taskbar-size functionality is only initialized for the Windows 11 new/XAML taskbar.
- The taskbar-size functionality is skipped when **Customize the old taskbar on Windows 11** is enabled.
- Added compatibility handling for newer Windows 11 builds that expose small taskbar icons.
- Unified the new taskbar-size module lifecycle with the existing mod lifecycle, including initialization, settings changes, and unloading.

### Default Settings Added

| Setting | Default |
|---|---:|
| Taskbar height | `52` px |
| Icon size | `32` px |
| Taskbar button width | `44` px |
| Small icon size | `16` px |
| Small taskbar button width | `32` px |

### Technical Notes

- The v1.1.0 implementation adds hooks around Windows taskbar, task-list, system-tray, and icon-loading components used by the new taskbar.
- The implementation detects the relevant Windows taskbar/runtime classes before overriding taskbar-size behavior.
- The mod preserves the stock taskbar sizing behavior when the new taskbar-size feature is not applicable.
- The implementation includes additional handling for taskbar auto-hide/secondary-taskbar sizing and icon retrieval.
- The feature is integrated into the existing Windhawk module lifecycle rather than operating as a separate mod.

## [v1.0.0] — 2026-09-17

### Added

Initial public version combining functionality from the following Windhawk projects:

- **Taskbar Clock Customization** — m417z
- **Taskbar Tray System Icon Tweaks** — m417z

### Features

- Windows system-tray icon visibility controls.
- Volume, network/Wi-Fi, and battery icon controls.
- Grayscale battery icon option.
- Microphone, location, Studio Effects, and Recall icon controls.
- Language bar and supplementary input/IME icon controls.
- Configurable Notification Center/Bell visibility.
- Show Desktop button visibility and width control.
- Custom taskbar clock lines.
- Custom time, date, weekday, and time-zone formatting.
- Live network, disk, CPU, RAM, GPU/VRAM, and power/battery metrics.
- `%volume%` volume indicator.
- `%mic%` microphone activity indicator.
- Media-player integration through Windows GSMTC.
- Web-content and RSS/XML/HTML extraction.
- Weather integration through wttr.in.
- Independent Windows 11 22H2+ Date and Time text styling.
- Battery charging and low-battery indicators.
- Low-battery clock styling.

[1.1.0]: https://github.com/mzihadul/taskbar-tray-and-clock-tweaks/releases/tag/v1.1.0
[1.0.0]: https://github.com/mzihadul/taskbar-tray-and-clock-tweaks/releases/tag/v1.0.0
