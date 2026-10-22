# Changelog

All notable changes to **Taskbar Tray & Clock Tweaks** are documented in this file.

# Changelog

## [1.7.1] - 2026-10-22
 
### Added
- "Isha time ends at" setting under Clock: prayer times: Islamic midnight (default) or the next Fajr.
- `%prayer_midnight%` tag: Islamic midnight of tonight.

### Fixed
- `%prayer_current_*%` kept showing Isha with hours left until the next Fajr (e.g. "Isha (5h 4m left)" at 11:38 PM), long after the Isha time ended. Isha now ends at Islamic midnight, halfway between Maghrib and the next Fajr, and from then until Fajr no prayer is current (`--`).
- `%prayer_current%` showed "Sunrise" from sunrise until Dhuhr, for hours after the sun had risen. Between Sunrise and Dhuhr no prayer is current now, so `%prayer_current%`, `%prayer_current_left%`, `%prayer_current_end%` and `%prayer_current_info%` show `--` during that time. `%prayer_next_info%` still counts down to Dhuhr.

## [1.7.0] - 2026-10-18

### Added
- Prayer times for the clock, calculated on your computer from latitude, longitude and the system clock (no network access). New "Clock: prayer times" settings section with calculation method (Karachi default, Muslim World League, ISNA, Egyptian, Umm al-Qura, custom angles), Asr rule (Hanafi default or standard), time format, prayer names and per-prayer minute adjustments. Defaults to Dhaka.
- New clock tags: `%prayer_next%`, `%prayer_next_time%`, `%prayer_next_in%`, `%prayer_next_info%`, `%prayer_current%`, `%prayer_current_left%`, `%prayer_current_end%`, `%prayer_current_info%`, `%prayer_all%`, `%prayer_fajr%`, `%prayer_sunrise%`, `%prayer_dhuhr%`, `%prayer_asr%`, `%prayer_maghrib%`, `%prayer_isha%`.
- When style rules for a target fail to load, the mod log now says which target and why, instead of ignoring them silently.

### Fixed
- Bangla text on the clock looked larger than the English text. A new "Bangla text size (%)" setting under Alternate calendars (default 90, 100 turns it off) scales only the Bangla characters on the top and bottom lines (Windows 11 22H2+).
- Explorer lag and a missing taskbar at startup on Windows 11 24H2 (build 26100.9711, KB5127648), untested on that build:
  - Explorer startup no longer blocks on the taskbar size and icon size apply. The first apply now runs on a background thread and waits for the taskbar window to exist.
  - Taskbar size changes wait at most about 1 second for the layout pass, down from up to 10 seconds. If the layout hook never fires, the apply continues instead of hanging.
  - The settings-change messages sent to the taskbar now time out after 2 seconds and skip a hung taskbar.

### Changed
- The transparency watchdog waits about 10 seconds after startup before its first pass, then re-applies every 3 seconds (was 1.5). Dynamic transparency still reacts within 250 ms of a window being maximized or restored. Stopping it on unload waits at most 5 seconds.
- On unload, the taskbar height restore no longer waits for the layout pass, so it may take a moment longer to settle visually.

## [1.6.0] - 2026-10-15

### Added
- **Taskbar shape** (Windows 11 new taskbar): rounded bar and pill presets with corner radius, background color and border. The transparency modes Fully Transparent, Blurry Glass and Liquid Glass are drawn inside the shape (Mica is not applied with a shape).
- **`%if(condition,then,else)%`** conditional tag. Metrics: `cpu`, `ram`, `gpu`, `cpu_temp`, `cpu_freq`, `battery`, `charging`, `hour`, `minute`, `weekday`.
- **`%stopwatch%`, `%timer%`, `%pomodoro%`** with a shared run state, configurable lengths and sound, and new middle-click actions "Start / pause the timer" and "Reset the timer". New "Pomodoro timer" clock layout preset.
- **`%cpu_freq%`** average CPU clock.
- **Weather fallback**: Open-Meteo is used when wttr.in does not answer (placeholders `%c %t %w %h %l %S %s`).

### Removed
- *Tabler icons*: the `%ti:name%` tag and its settings were taken out because they did not fit the mod.

### Notes
- The shape feature is a visual effect; the taskbar window keeps its full size.
- Per-monitor clock layouts, settings export / import and extra GPU / fan sensors are not part of this release.

## [1.5.0] - 2026-10-10

### ⚠️ Upgrade note: some settings reset to defaults
Settings moved into categories get new key paths, and Windhawk stores values by key path. After updating, re-enter the settings below. A previously exported `settings.txt` no longer matches the new layout.

| Category | Old key | New key |
| :--- | :--- | :--- |
| System tray icons | `hide*Icon`, `hideLanguage*`, `hideBellIcon`, `grayscaleBatteryIcon`, `showDesktopButtonWidth` | `SystemTray.*` |
| Clock: date, time & time zones | `ShowSeconds`, `TimeFormat`, `DateFormat`, `DateLocale`, `WeekdayFormat`, `WeekdayFormatCustom`, `TimeZones` | `ClockFormat.*` |
| Clock: text lines & tooltip | `TopLine`, `BottomLine`, `MiddleLine`, `TooltipLine`, `TooltipLineMode` | `ClockLines.*` |
| Clock: size & spacing | `Width`, `Height`, `MaxWidth`, `TextSpacing` | `ClockLayout.*` |
| Weather & web content | `WebContentWeather*`, `WebContentsItems`, `WebContentsUpdateInterval` | `WebContent.*` |
| Taskbar transparency & app visibility | `TransparencyMode`, `TransparencyAlpha`, `HideTaskbarApps`, `AppExceptions` | `TaskbarAppearance.*` |
| Taskbar size & icons | `TaskbarHeight`, `IconSize`, `TaskbarButtonWidth`, `IconSizeSmall`, `TaskbarButtonWidthSmall` | `TaskbarSize.*` |
| Advanced styling (XAML) | `styleConstants`, `controlStyles`, `themeResourceVariables`, `xamlDiagnosticsHandling` | `Styling.*` |

**Keep their values:** *Customize the old taskbar on Windows 11*, Live metrics, Media player info, and the top and bottom line styles.

All new options default to off or to the previous behavior.

### Added

**Settings**
- Settings are grouped by category, with Windows version notes shown once per group.

**Clock tags**
- Text graphs: `%cpu_graph%`, `%ram_graph%`, `%gpu_graph%`, `%download_graph%`, `%upload_graph%`, `%disk_graph%` (length configurable).
- Drive space: `%drive_free_C%`, `%drive_used_C%`, `%drive_total_C%`, `%drive_free_pct_C%`, `%drive_used_pct_C%`.
- System info: `%uptime%`, `%process_count%`, `%top_process%`, `%top_process_cpu%`.
- Keyboard state: `%lang%`, `%lang_full%`, `%capslock%`, `%numlock%`.
- Countdowns: `%countdown<n>%`, `%countdown<n>_days%`.
- Network: `%ping%`, `%wifi_ssid%`, `%wifi_signal%`, `%vpn%`, `%local_ip%`.
- Alternate calendars: `%date_hijri%` (Umm al-Qura or civil, ±2 day adjustment), `%date_persian%`, `%date_japanese%`, `%date_bengali%` and `%date_bengali_en%` (Bangladesh revised calendar).
- Calendar events from an ICS feed: `%next_event%`, `%next_event_time%`, `%next_event_in%`.
- Media progress: `%media_position%`, `%media_duration%`, `%media_remaining%`, `%media_progress%`, `%media_bar%`.
- Tabler Icons: `%ti:name%` and `%ti:U+XXXX%` (needs the Tabler icon font installed; 146 common icons built in, all icons with the optional `tabler-icons.css`).
- Unknown tags are shown as `[?name]` (can be turned off).

**Clock behavior**
- Clock layout presets: Minimal, System monitor, Battery, Media player, Weather.
- Automatic profiles that switch the layout on battery, when plugged in, below a battery level, with one or several monitors, or at certain hours.
- Threshold color rules for CPU, RAM, GPU, CPU temperature and battery level.
- Mouse wheel over the clock (volume or track) and middle click (play/pause, mute, next/previous, Task Manager, or a custom command).
- Marquee scrolling for long `%media_info%` text.
- Weather presets, including sunrise and sunset.
- Slower metrics update interval while on battery.

**Taskbar**
- Dynamic transparency: the default taskbar on a monitor while a window is maximized there.
- Quick switches to hide the Start, Search, Task View and Widgets buttons.
- Running-app indicator styling: hide it, or set color, width, height and corner radius (with a separate color and width for the focused app).
- Hide individual notification-area icons by exact name.

**Diagnostics**
- Optional logging of clock threads and taskbar windows to the Windhawk log, to help investigate per-monitor clock settings.

### Changed
- Shorter setting labels and descriptions, a condensed mod header and readme, and single-line section banners in the source.

### Fixed
- **Hide running / pinned apps** no longer hides the Start, Search, Task View and Widgets buttons. It now matches app buttons only.
- A configured **text color** is now parsed (hex or named color). Previously any value turned the text white.

### Removed
- Unused legacy single-URL web content code (`WebContentsUrl`, `WebContentsBlockStart`, `WebContentsStart`, `WebContentsEnd`, `WebContentsMaxLength`). These keys were not in the settings schema and never had a value. Use the web content list (`%web1%`, `%web2%`, ...) instead.

### Known limitations
- Wi-Fi signal is reported by Windows in 0-5 bars (shown in 20% steps), and VPN detection is best effort.
- `%ping%` takes an IPv4 address only.
- ICS: events with a named time zone are read as local time, and "second Tuesday"-style monthly rules show only the first occurrence.
- Media position stays empty for players that report no timeline, which is common with browsers.
- Tabler icons work in the top and bottom lines (Windows 11), not in the tooltip, and only one Tabler font style can be installed at a time.
- Profiles switch the clock layout only, not other settings.
- Hiding tray icons needs the exact icon name, and tooltips that change will not match.

## [1.4.0] - 2026-10-07

### Changed
- Settings are now grouped by category. Each category collapses in the Windhawk settings window, so it's clear which part of the taskbar you're changing.
- Version and platform notes (Windows 11 only, new taskbar only, 22H2+) are now shown once per category instead of on individual settings.
- Shorter setting labels and descriptions, for example "Web content URL" is now "URL" inside the web content group.
- Condensed the mod header and readme. The readme now includes a table of the settings categories, and all clock tags are still documented.
- Section banners in the source are now single-line comments.

### Removed
- Unused legacy single-URL web content code (WebContentsUrl, WebContentsBlockStart, WebContentsStart, WebContentsEnd, WebContentsMaxLength). These keys were no longer in the settings schema, so they never had a value. Use the web content list (%web1%, %web2%, …) instead.

### Upgrade note:
- Some settings reset to defaults.
- Settings moved into categories get new key paths, and Windhawk stores values by key path.
- After updating, re-enter the settings below.

## [1.3.1] - 2026-09-27

### Fixed
- Taskbar transparency (Transparent / Blurry Glass / Liquid Glass / Mica) would intermittently stop applying.

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
