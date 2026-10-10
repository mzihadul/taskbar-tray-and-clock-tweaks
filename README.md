# Taskbar Tray & Clock Tweaks

[![Windhawk Mod](https://img.shields.io/badge/Windhawk-Mod-blue.svg)](https://windhawk.net/)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Platform](https://img.shields.io/badge/Platform-Windows%2010%20%7C%20Windows%2011-0078D6.svg)](#compatibility)
[![Architecture](https://img.shields.io/badge/Arch-x86--64-brightgreen.svg)](#)

A comprehensive, all-in-one **[Windhawk](https://windhawk.net/)** mod that unifies granular system tray icon controls, extensive taskbar clock formatting, live hardware performance monitors, network and calendar information, media playback display, Tabler icons, taskbar transparency, taskbar button visibility, taskbar height/icon sizing, and a complete XAML control/icon styling engine.

![Taskbar Tray & Clock Tweaks Preview](./screenshot.png)

## 🆕 What's New in v1.5.0

* **Settings are now grouped by category**, so you can see which part of the taskbar you are changing (see [Settings Categories](#-settings-categories)).
* **New clock tags:** history graphs, drive space, uptime and process info, keyboard state, countdowns, network details (ping, Wi-Fi, VPN, local IP), alternate calendars (Hijri, Persian, Japanese, Bengali), the next event from a calendar feed, and media playback progress.
* **Tabler Icons** in the clock lines with `%ti:name%`.
* **Clock layout presets and automatic profiles** that switch the clock layout on battery, with several monitors, or at certain hours.
* **Threshold color rules** and **click & scroll actions** for the clock.
* **Dynamic transparency**, **quick switches** for the Start, Search, Task View and Widgets buttons, **running-app indicator styling**, and **hiding individual tray icons by name**.
* **Marquee** for long media titles, a slower **update interval on battery**, and **hints for unknown tags** (`[?name]`).
* **Fixes:** *Hide running / pinned apps* no longer hides the Start, Search, Task View and Widgets buttons, and a configured text color is now applied instead of always turning the text white.

> **Upgrading from an earlier version:** settings that moved into categories are stored under new names, so they **fall back to their defaults** and must be entered again. This covers the tray icon options, clock formats, clock lines, clock size and spacing, weather and web content, transparency, taskbar size and the advanced styling rules. Settings that were already grouped (live metrics, media player, top/bottom line style) and *Customize the old taskbar on Windows 11* keep their values. A previously exported [`settings.txt`](./settings.txt) no longer matches the new layout.

---

## 🗂️ Settings Categories

| Category | What it controls |
| :--- | :--- |
| System tray icons | Hide or restyle volume, network, battery, microphone, location, Studio Effects, Recall, language, bell and "Show desktop" |
| Clock: date, time & time zones | Time / date / weekday formats, locale, seconds, time zones, countdown targets |
| Clock: text lines & tooltip | What the top, middle (Windows 10) and bottom lines and the tooltip show, ready-made layout presets, unknown-tag hints |
| Clock: size & spacing | Clock width / height (Windows 10), max width and line spacing (Windows 11) |
| Clock: top / bottom line style | Color, font, alignment and spacing per line (Windows 11 22H2+) |
| Clock: click & scroll actions | Mouse wheel and middle click on the clock: volume, media keys, Task Manager or a command (Windows 11) |
| Clock: automatic profiles | Switch the clock to a ready-made layout on battery, with several monitors, or at certain hours |
| Icons (Tabler Icons) | Show Tabler icons in the clock lines with `%ti:name%` |
| Clock: color rules | Change the clock text color when CPU, RAM, GPU, temperature or battery cross a threshold (Windows 11 22H2+) |
| Network info | Ping, Wi-Fi name and signal, VPN status, local IP |
| Alternate calendars | Hijri, Persian, Japanese and Bengali (Bangladesh) dates |
| Calendar events (ICS) | Next event from a calendar feed |
| Live metrics | Update interval (and a slower one on battery), number formats, network / GPU adapter, graph length |
| Media player info | Format, length limit, scrolling marquee and ignored players for `%media_*%` |
| Weather & web content | Weather (wttr.in) with presets, and web / RSS extraction for `%weather%`, `%web<n>%` |
| Taskbar transparency & app visibility | Transparency mode and level, dynamic transparency, hide running / pinned apps |
| Taskbar size & icons | Taskbar height, icon size, button width |
| Tray icons | Hide individual notification-area icons by name |
| Taskbar buttons | Hide the Start, Search, Task View and Widgets buttons |
| Running-app indicator | Hide it, or set its color, size and corner radius (with a separate look for the focused app) |
| Advanced styling (XAML) | Style constants, control styles, theme resources |
| Diagnostics | Optional logging of clock threads and taskbar windows |

---

## ✨ Features

### 1. System Tray Icon Control (Windows 11)
Selectively hide or style native system tray components:
* **Control Center Icons:** Selectively hide Volume, Network/Wi-Fi, and Battery icons.
* **Battery Grayscale Mode:** Display the battery icon using standard text foreground colors instead of accent green/yellow.
* **Privacy & Hardware Indicators:** Selectively hide Microphone, Location (GPS), Studio Effects, and Windows Recall.
* **Input Switchers:** Hide the language bar and supplementary input method (IME) status icons.
* **Notification Center (Bell):**
  * `Never hide`
  * `When inactive` (hides when there are no unread notifications)
  * `When inactive and Do Not Disturb is off`
  * `Always hide`
* **Show Desktop Button:** Hide completely or configure custom pixel width.
* **Hide Individual Tray Icons by Name:** **[Added in v1.5.0]** Hide classic notification-area icons by their exact name (the tooltip text, readable with the [UWPSpy](https://github.com/ramensoftware/UWPSpy) tool). Windows system icons such as volume and network have their own switches above.

---

### 2. Taskbar Clock Customization
Configure custom text lines for **Top Line**, **Bottom Line**, **Middle Line** (Windows 10 only), and **Tooltip Extra Line** using dynamic tags. A tag that does not exist is shown as `[?name]` so typos are easy to spot (can be turned off).

#### 🕒 Date, Time & Locale
* `%time%` — Configured primary time format.
* `%time<n>%` — Secondary time formats (separated by `;` in format settings, e.g. `%time2%`).
* `%time_tz<n>%` — Time mapped to a configured time zone index.
* `%date%` — Configured primary date format.
* `%date<n>%` — Secondary date formats (e.g. `%date2%`).
* `%date_tz<n>%` — Date mapped to a configured time zone index.
* `%weekday%` — Full, abbreviated, or custom comma-separated week day names.
* `%weekday_tz<n>%` — Weekday mapped to a custom time zone index.
* `%weekday_num%` — Day of week number (1–7) respecting user locale settings.
* `%weeknum%` / `%weeknum_iso%` — Standard regional or ISO 8601 week number.
* `%dayofyear%` — Day of the year (1–366).
* `%timezone%` — UTC bias offset (e.g. `+06:00`).
* `%newline%` or `%n%` — Insert a line break.
* `%countdown<n>%` / `%countdown<n>_days%` — **[Added in v1.5.0]** Time left until target `<n>` (e.g. `12d 4h 3m`, or `Done`) and the whole days left. Targets are local dates such as `2027-01-01` or `2027-01-01 18:30`, set in the date and time settings.

#### 📆 Alternate Calendars **[Added in v1.5.0]**
* `%date_hijri%` — Hijri date, Umm al-Qura or civil, adjustable by ±2 days to match local moon sighting.
* `%date_persian%` — Persian (Solar Hijri) date.
* `%date_japanese%` — Japanese-era date.
* `%date_bengali%` / `%date_bengali_en%` — Bengali date of the **Bangladesh revised calendar** (new year on 14 April), in Bangla script and digits or in Latin letters (e.g. `25 Ashwin 1433`).

#### ⚡ Hardware Performance & System Status
* **Network Speeds:** `%upload_speed%`, `%download_speed%`, `%total_speed%` (Auto-formatted in KB/s, MB/s, or MBit/s).
* **Disk I/O:** `%disk_read%`, `%disk_write%`, `%disk_total%`.
* **Processor (CPU):** `%cpu%` (usage percentage), `%cpu_temp%` (°C), `%cpu_temp_f%` (°F).
* **System Memory (RAM):** `%ram%` (%), `%ram_used%` (GB), `%ram_total%` (GB), `%ram_committed%` (%), `%ram_committed_used%` (GB), `%ram_committed_total%` (GB).
* **Graphics (GPU & VRAM):** `%gpu%` (3D engine usage %), `%vram%` (dedicated %), `%vram_used%` (GB), `%vram_total%` (GB), `%vram_shared%` (%), `%vram_shared_used%` (GB), `%vram_shared_total%` (GB).
* **Graphs:** **[Added in v1.5.0]** `%cpu_graph%`, `%ram_graph%`, `%gpu_graph%`, `%download_graph%`, `%upload_graph%`, `%disk_graph%` — recent history drawn with block characters (▁▂▃▅▇). Percent graphs use a fixed 0–100% scale; speed graphs scale to the recent peak. The length is configurable.
* **Drive Space:** **[Added in v1.5.0]** `%drive_free_C%`, `%drive_used_C%`, `%drive_total_C%` for any local drive letter, and `%drive_free_pct_C%` / `%drive_used_pct_C%` for percentages.
* **System Info:** **[Added in v1.5.0]** `%uptime%` (e.g. `2d 5h 12m`), `%process_count%`, `%top_process%` / `%top_process_cpu%` (busiest process by CPU, sampled every few seconds).
* **Keyboard State:** **[Added in v1.5.0]** `%lang%` / `%lang_full%` (current input language, e.g. `EN` / `English`), `%capslock%` / `%numlock%` (`CAPS` / `NUM` while on, otherwise empty).
* **Power & Battery:**
  * `%battery%` — Battery percentage (appends `⚡` on AC power, appends `❗` when battery ≤ 20%).
  * `%battery_time%` — Estimated remaining battery discharge or charge time (`h:mm`).
  * `%power%` — Real-time discharge/charge rate in watts (`+W` or `-W`).
* **Volume Level:** `%volume%` — Shows `🔊` or `🔇`, automatically expanding to `🔊 45%` for 3 seconds during volume adjustments.
* **Microphone Activity:** `%mic%` — Active `🎙️` indicator when any application accesses a recording device.

The metrics update at the configured interval, and a slower interval can be used while the PC is running on battery.

#### 🌐 Network Info **[Added in v1.5.0]**
* `%ping%` — Round-trip time to a configurable IPv4 address (e.g. `23 ms`, `--` when unreachable).
* `%wifi_ssid%` / `%wifi_signal%` — Connected Wi-Fi name and signal. Windows reports 0–5 bars, shown in 20% steps.
* `%vpn%` — `VPN` while a VPN-like connection is up (best effort), otherwise empty.
* `%local_ip%` — IPv4 address of the adapter used for internet.

#### 🎵 Media Player Integration (GSMTC)
Extracts track details from Spotify, Chrome, Edge, VLC, Apple Music, and other media players:
* `%media_title%` — Current track title (brackets optionally stripped).
* `%media_artist%` — Current artist.
* `%media_album%` — Album title.
* `%media_status%` — Playback state emoji (`⏯`, `⏸`, `⏹`).
* `%media_info%` — Combined formatted text with truncation support (e.g. `Artist - Title`), or **scrolling as a marquee** **[Added in v1.5.0]** while playing.
* **Playback progress:** **[Added in v1.5.0]** `%media_position%`, `%media_duration%`, `%media_remaining%`, `%media_progress%` (percent) and `%media_bar%` (▰▰▰▱▱▱▱▱). They stay empty for players that do not report a timeline, which is common with browsers.

#### ⛅ Weather & Web Feeds
* `%weather%` — Live weather status powered by [wttr.in](https://wttr.in) with custom location, metrics, and symbols. **[v1.5.0]** Ready-made presets are available, including one for sunrise and sunset.
* `%web<n>%` / `%web<n>_full%` — Live text extracted from RSS feeds, XML, HTML, or plain web endpoints.

#### 📅 Calendar Events (ICS) **[Added in v1.5.0]**
Shows the next event from an iCalendar feed URL (for example a secret Google Calendar link; `webcal://` links work too):
* `%next_event%` — Event title (length limit configurable).
* `%next_event_time%` — Start time (`14:30`, `Fri 09:00`, `Oct 20 09:00`).
* `%next_event_in%` — Time left (`in 25m`, `in 2h 5m`, `in 3d 4h`).

Daily, weekly (with weekdays), monthly and yearly repeats are supported, along with excluded dates and moved single occurrences. Events with a named time zone are read as local time, and "second Tuesday"-style monthly rules show only the first occurrence. All-day events are skipped unless enabled.

#### 🎨 Icons (Tabler Icons) **[Added in v1.5.0]**
Use `%ti:name%` to show an icon from [Tabler Icons](https://tabler.io/icons) in the top or bottom clock line, for example `%ti:battery-charging% %battery%` or `%ti:wifi% %wifi_ssid%`. `%ti:U+EA35%` uses a raw codepoint, and an unknown name is shown as `[?ti:name]`.

1. Get the Tabler webfont package (npm: `@tabler/icons-webfont`) and install `dist/fonts/tabler-icons.ttf`. Install only **one** Tabler font style (outline, filled, 200 or 300 weight): they all share the family name `tabler-icons`, so Windows cannot hold two at once.
2. Optionally set the path to the matching `tabler-icons.css` in the *Icons* settings so every icon name works. Without it, a built-in list of 146 common outline icons is used.
3. The mod puts the icon font first in the clock text's font list. It has no letters or digits, so normal text keeps its font.

Icons need Windows 11 and work in the top and bottom lines, not in the tooltip. The font and the icon artwork are **not** bundled with the mod.

#### 🧩 Layout Presets & Automatic Profiles **[Added in v1.5.0]**
* **Presets:** Minimal, System monitor, Battery, Media player and Weather layouts fill in the top line, bottom line and tooltip for you.
* **Profiles:** rules switch the clock to one of those presets automatically — when running on battery, plugged in, below a battery level, with one or several monitors connected, or within certain hours (ranges such as 22 to 6 wrap past midnight). The first matching rule wins; with no match your normal clock lines apply.

#### 🖱️ Click & Scroll Actions (Windows 11) **[Added in v1.5.0]**
* **Mouse wheel over the clock:** change the volume, or skip to the previous / next track.
* **Middle click on the clock:** play / pause, mute / unmute, next or previous track, open Task Manager, or run your own command.

Nothing is attached to the clock unless an action is configured.

---

### 3. Font & Text Styling (Windows 11 22H2+)
* Independent visual styles for Date and Time lines.
* Hex color overrides (`#RRGGBB` / `#AARRGGBB`) or named colors.
* **Threshold color rules:** **[Added in v1.5.0]** change a line's color while CPU usage, RAM usage, GPU usage, CPU temperature or battery level is above or below a value (for example red below 20% battery). Rules are checked in order and the first match wins per line.
* Custom Font Family, Size, Weight, Stretch, and Style.
* Alignment (Left, Center, Right, Justified), character spacing, line height, and line spacing.

---

### 4. Taskbar Transparency & App Visibility (Windows 11) **[Added in v1.2.0]**
* **Backdrop Modes:** Default, Fully Transparent, Blurry Glass, Liquid Glass (Acrylic), and Mica.
* **Custom Opacity:** 0% (solid) to 100% (fully clear).
* **Dynamic Transparency:** **[Added in v1.5.0]** Uses the default (opaque) taskbar on a monitor while a window is maximized there, and your transparency mode otherwise.
* **Hide Running / Pinned Apps:** Hides taskbar application buttons while retaining Start, Search, Task View, Widgets, and System Tray elements. **[Fixed in v1.5.0]** Earlier versions also hid the contents of those buttons.
* **App Exceptions Whitelist:** Preserve specific application icons using partial or full AUMID or window title matches. The Copilot button counts as an app button, so add `Copilot` here to keep it.

---

### 5. Taskbar Height & Icon Size (Windows 11 New Taskbar) **[Added in v1.1.0]**
* Fixes blurry 24×24 downscaled Windows 11 icons by allowing crisp, native 32×32 or 16×16 rendering.
* Configurable taskbar height (default 48px, adjustable to 32px, 52px, 60px, etc.).
* Configurable icon size and button width for regular and compact taskbar modes.

---

### 6. Taskbar Buttons & Running-App Indicator (Windows 11 New Taskbar) **[Added in v1.5.0]**
Simple switches that generate the matching control styles for you, so common tweaks need no XAML. They are applied before your own control styles, which can still override them.
* **Taskbar Buttons:** Hide the Start, Search, Task View and Widgets buttons independently.
* **Running-App Indicator:** Keep the default, hide it, or customize its color, width, height and corner radius, with a separate color and width for the focused app.

---

### 7. Taskbar Control & Icon Styling Engine (Windows 11 New Taskbar) **[Added in v1.3.0]**
* Target any XAML control by class name, element ID, or application ID (`Taskbar.TaskListButton[AutomationProperties.AutomationId=Appid: ...]`).
* Override element properties (e.g. custom icon `Source`, `Width`, `Height`, `CornerRadius`, `Background`, `Margin`).
* Support for local files and remote image URLs with local disk caching and automatic offline retry.
* Embedded `<WindhawkBlur ... />` brush and XAML markup syntax (`:=`).
* Visual state matching (`Style@VisualState=Value`) and dynamic style variable propagation (`Property=>VarName`, `{{VarName}}`).
* Theme-aware resource variable overrides (`Key@Dark=Value`, `Key@Light=Value`).

---

## ⚙️ Example Configurations

A customized taskbar clock can combine multiple variables:

```text
🔼 %upload_speed% 🔽 %download_speed% ⚙ %cpu% 🗃️ %ram% %weather% 📅 %date% 🌿 %time% %mic% %volume% ♻️ %battery%
```

A second example using the newer tags (with the Tabler icon font installed):

```text
%ti:cpu% %cpu_graph% %cpu% %ti:wifi% %wifi_ssid% %ping% %ti:calendar-event% %next_event% %next_event_in% %ti:battery-charging% %battery%
```

The exact appearance depends on the configured clock lines, fonts, spacing, and Windows version. You can also copy and paste the [Settings](./settings.txt) for exact view.

## 💻 Compatibility

| Operating System | Tray Icons | Clock Customization | Performance Metrics | Transparency | Height & Icon Size | Control Styler |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: |
| **Windows 11 (22H2 / 23H2 / 24H2)** | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| **Windows 11 (21H2)** | ✅ | ✅ | ✅ | ✅ | ✅ | ⚠️ Partial |
| **Windows 10 (64-bit)** | ❌ | ✅ | ✅ | ❌ | ❌ | ❌ |
| **ExplorerPatcher (Win10 Taskbar on Win11)** | ❌ | ✅ | ✅ | ❌ | ❌ | ❌ |

> **Note:** Taskbar Height/Icon Size and Control Styling features only apply to the Windows 11 XAML-based taskbar. When *"Customize the old taskbar on Windows 11"* is enabled or when running on Windows 10, those subsystems remain inactive.

> **Note:** The clock tags are produced by the shared formatting engine. The features that style or attach to the Windows 11 clock — Tabler icons, threshold color rules, click & scroll actions and the top/bottom line styles — require the Windows 11 XAML taskbar, as do the taskbar button, running-indicator, dynamic transparency and tray-icon features.

---

## 📦 Installation

1. Install [Windhawk](https://windhawk.net/).
2. In Windhawk, go to **Mods** → **Add Custom Mod**.
3. Paste the contents of [`taskbar-tray-and-clock-tweaks.wh.cpp`](https://github.com/mzihadul/taskbar-tray-and-clock-tweaks/blob/main/taskbar-tray-and-clock-tweaks.wh.cpp).
4. Click **Compile and Save**.

---

## ⚙️ Compilation Options

When compiling via Windhawk, the following libraries are required:
```text
-lcomctl32 -lgdi32 -lole32 -loleaut32 -lruntimeobject -lshcore -lversion -lwininet -lshlwapi -ldxgi -lpdh -lpowrprof
```

---

## 🔀 Project Background

This project is a **combined derivative work** integrating functionality from those existing Windhawk projects:

### Taskbar Clock Customization

Original author: **m417z**

Source:
https://github.com/ramensoftware/windhawk-mods/blob/main/mods/taskbar-clock-customization.wh.cpp

Provides the foundation for the taskbar clock, formatting, hardware metrics, media, web-content, weather, and related functionality.

### Taskbar Tray System Icon Tweaks

Original author: **m417z**

Source:
https://github.com/ramensoftware/windhawk-mods/blob/main/mods/taskbar-tray-system-icon-tweaks.wh.cpp

Provides the foundation for system-tray icon customization.

### Taskbar Icon Size

Original author: **m417z**

Source:
https://github.com/ramensoftware/windhawk-mods/blob/main/mods/taskbar-icon-size.wh.cpp

Integrated as part of v1.1.0 to provide taskbar height, icon-size, and taskbar-button-width control for the Windows 11 new taskbar.

### Windows 11 Taskbar Styler

Original author: **m417z**

Source:
https://github.com/ramensoftware/windhawk-mods/blob/main/mods/windows-11-taskbar-styler.wh.cpp

Provides the control and icon styling engine (themes omitted). The element selectors used by the taskbar button, running-indicator and tray-icon switches follow the conventions of its themes.

---

## 🛠️ Additional Modifications & Integration

Additional modifications and integration includes:

- Unified taskbar clock and system-tray functionality
- Unified settings and module lifecycle
- Unified symbol hooking and module handling
- Settings grouped into categories
- `%volume%` taskbar variable
- Master volume and mute detection
- Temporary volume-percentage display
- `%mic%` microphone activity variable
- Microphone activity detection
- Charging-state indicator for `%battery%`
- Low-battery indicator for `%battery%`
- Integration of taskbar height and icon-size functionality
- Support for newer Windows 11 small taskbar icon sizing
- Taskbar transparency modes
- Adjustable transparency level
- Dynamic transparency based on maximized windows
- Primary and secondary taskbar transparency handling
- Running/pinned application visibility control
- Application exceptions using AUMID or application name
- Quick switches for taskbar buttons and the running-app indicator
- Hiding of individual tray icons by name
- Text graphs, drive space, uptime, process and keyboard-state variables
- Countdown variables
- Network variables (ping, Wi-Fi, VPN, local IP)
- Hijri, Persian, Japanese and Bangladesh-revised Bengali calendar variables
- ICS calendar feed parsing for upcoming events
- Media playback progress variables and marquee scrolling
- Tabler Icons integration through `%ti:name%`
- Clock layout presets and automatic profiles
- Threshold color rules and clock click & scroll actions
- Slower metric updates on battery
- Hints for unknown clock tags
- Ongoing maintenance of the combined codebase

The project should therefore be considered a **derivative and integrated work**, rather than an entirely original implementation.

---

## 🙏 Credits

Special thanks to **[m417z](https://github.com/m417z)** for the original Windhawk projects that provide the foundation for this combined mod.

* [Taskbar Clock Customization](https://github.com/ramensoftware/windhawk-mods/blob/main/mods/taskbar-clock-customization.wh.cpp)
* [Taskbar Tray System Icon Tweaks](https://github.com/ramensoftware/windhawk-mods/blob/main/mods/taskbar-tray-system-icon-tweaks.wh.cpp)
* [Taskbar height and icon size](https://github.com/ramensoftware/windhawk-mods/blob/main/mods/taskbar-icon-size.wh.cpp)
* [Windows 11 Taskbar Styler](https://github.com/ramensoftware/windhawk-mods/blob/main/mods/windows-11-taskbar-styler.wh.cpp)

The optional icon feature uses the [Tabler Icons](https://github.com/tabler/tabler-icons) font by **Paweł Kuna**, released under the MIT license. It is installed separately and is not part of this project.

---

## 📄 License

This project is released under the **GNU General Public License v3.0 (GPL-3.0)**.

The project incorporates derivative code from the upstream projects identified above. Their respective copyright and licensing terms remain applicable to the portions derived from those projects.

See the [`LICENSE`](./LICENSE) file for the complete license text.

---

## ⚠️ Disclaimer

This project is provided as-is. 

Windows internal implementations can change between Windows versions and updates, which may affect compatibility or functionality. Features that hook internal Windows components may require updates after major Windows releases.

Always keep a backup of your Windhawk configuration before making significant changes.
