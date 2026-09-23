# Taskbar Tray & Clock Tweaks

[![Windhawk Mod](https://img.shields.io/badge/Windhawk-Mod-blue.svg)](https://windhawk.net/)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![Platform](https://img.shields.io/badge/Platform-Windows%2010%20%7C%20Windows%2011-0078D6.svg)](#compatibility)
[![Architecture](https://img.shields.io/badge/Arch-x86--64-brightgreen.svg)](#)

A comprehensive, all-in-one **[Windhawk](https://windhawk.net/)** mod that unifies granular system tray icon controls, extensive taskbar clock formatting, live hardware performance monitors, media playback display, taskbar transparency, app button visibility, taskbar height/icon sizing, and a complete XAML control/icon styling engine.

![Taskbar Tray & Clock Tweaks Preview](./screenshot.png)

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

---

## 2. Taskbar Clock Customization
Configure custom text lines for **Top Line**, **Bottom Line**, **Middle Line** (Windows 10 only), and **Tooltip Extra Line** using dynamic tags.

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

#### ⚡ Hardware Performance & System Status
* **Network Speeds:** `%upload_speed%`, `%download_speed%`, `%total_speed%` (Auto-formatted in KB/s, MB/s, or MBit/s).
* **Disk I/O:** `%disk_read%`, `%disk_write%`, `%disk_total%`.
* **Processor (CPU):** `%cpu%` (usage percentage), `%cpu_temp%` (°C), `%cpu_temp_f%` (°F).
* **System Memory (RAM):** `%ram%` (%), `%ram_used%` (GB), `%ram_total%` (GB), `%ram_committed%` (%), `%ram_committed_used%` (GB), `%ram_committed_total%` (GB).
* **Graphics (GPU & VRAM):** `%gpu%` (3D engine usage %), `%vram%` (dedicated %), `%vram_used%` (GB), `%vram_total%` (GB), `%vram_shared%` (%), `%vram_shared_used%` (GB), `%vram_shared_total%` (GB).
* **Power & Battery:**
  * `%battery%` — Battery percentage (appends `⚡` on AC power, appends `❗` when battery ≤ 20%).
  * `%battery_time%` — Estimated remaining battery discharge or charge time (`h:mm`).
  * `%power%` — Real-time discharge/charge rate in watts (`+W` or `-W`).
* **Volume Level:** `%volume%` — Shows `🔊` or `🔇`, automatically expanding to `🔊 45%` for 3 seconds during volume adjustments.
* **Microphone Activity:** `%mic%` — Active `🎙️` indicator when any application accesses a recording device.

#### 🎵 Media Player Integration (GSMTC)
Extracts track details from Spotify, Chrome, Edge, VLC, Apple Music, and other media players:
* `%media_title%` — Current track title (brackets optionally stripped).
* `%media_artist%` — Current artist.
* `%media_album%` — Album title.
* `%media_status%` — Playback state emoji (`⏯`, `⏸`, `⏹`).
* `%media_info%` — Combined formatted text with truncation support (e.g. `Artist - Title`).

#### ⛅ Weather & Web Feeds
* `%weather%` — Live weather status powered by [wttr.in](https://wttr.in) with custom location, metrics, and symbols.
* `%web<n>%` / `%web<n>_full%` — Live text extracted from RSS feeds, XML, HTML, or plain web endpoints.

---

### 3. Font & Text Styling (Windows 11 22H2+)
* Independent visual styles for Date and Time lines.
* Hex color overrides (`#RRGGBB` / `#AARRGGBB`) or named colors.
* Dynamic automatic red color switch on low battery (≤ 20%).
* Custom Font Family, Size, Weight, Stretch, and Style.
* Alignment (Left, Center, Right, Justified), character spacing, line height, and line spacing.

---

### 4. Taskbar Transparency & App Visibility (Windows 11) **[Added in v1.2.0]**
* **Backdrop Modes:** Default, Fully Transparent, Blurry Glass, Liquid Glass (Acrylic), and Mica.
* **Custom Opacity:** 0% (solid) to 100% (fully clear).
* **Hide Running / Pinned Apps:** Hides taskbar application buttons while retaining Start, Search, and System Tray elements.
* **App Exceptions Whitelist:** Preserve specific application icons using partial or full AUMID or window title matches.

---

### 5. Taskbar Height & Icon Size (Windows 11 New Taskbar) **[Added in v1.1.0]**
* Fixes blurry 24×24 downscaled Windows 11 icons by allowing crisp, native 32×32 or 16×16 rendering.
* Configurable taskbar height (default 48px, adjustable to 32px, 52px, 60px, etc.).
* Configurable icon size and button width for regular and compact taskbar modes.

---

### 6. Taskbar Control & Icon Styling Engine (Windows 11 New Taskbar) **[Added in v1.3.0]**
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

The exact appearance depends on the configured clock lines, fonts, spacing, and Windows version. You can also copy and paste the [Settings](./settings.txt) for exact view.

## 💻 Compatibility

| Operating System | Tray Icons | Clock Customization | Performance Metrics | Transparency | Height & Icon Size | Control Styler |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: |
| **Windows 11 (22H2 / 23H2 / 24H2)** | ✅ | ✅ | ✅ | ✅ | ✅ | ✅ |
| **Windows 11 (21H2)** | ✅ | ✅ | ✅ | ✅ | ✅ | ⚠️ Partial |
| **Windows 10 (64-bit)** | ❌ | ✅ | ✅ | ❌ | ❌ | ❌ |
| **ExplorerPatcher (Win10 Taskbar on Win11)** | ❌ | ✅ | ✅ | ❌ | ❌ | ❌ |

> **Note:** Taskbar Height/Icon Size and Control Styling features only apply to the Windows 11 XAML-based taskbar. When *"Customize the old taskbar on Windows 11"* is enabled or when running on Windows 10, those subsystems remain inactive.

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

---

## 🛠️ Additional Modifications & Integration

Additional modifications and integration includes:

- Unified taskbar clock and system-tray functionality
- Unified settings and module lifecycle
- Unified symbol hooking and module handling
- `%volume%` taskbar variable
- Master volume and mute detection
- Temporary volume-percentage display
- `%mic%` microphone activity variable
- Microphone activity detection
- Charging-state indicator for `%battery%`
- Low-battery indicator for `%battery%`
- Low-battery clock styling
- Integration of taskbar height and icon-size functionality
- Support for newer Windows 11 small taskbar icon sizing
- Taskbar transparency modes
- Adjustable transparency level
- Primary and secondary taskbar transparency handling
- Running/pinned application visibility control
- Application exceptions using AUMID or application name
- Ongoing maintenance of the combined codebase

The project should therefore be considered a **derivative and integrated work**, rather than an entirely original implementation.

---

## 🙏 Credits

Special thanks to **[m417z](https://github.com/m417z)** for the original Windhawk projects that provide the foundation for this combined mod.

* [Taskbar Clock Customization](https://github.com/ramensoftware/windhawk-mods/blob/main/mods/taskbar-clock-customization.wh.cpp)
* [Taskbar Tray System Icon Tweaks](https://github.com/ramensoftware/windhawk-mods/blob/main/mods/taskbar-tray-system-icon-tweaks.wh.cpp)
* [Taskbar height and icon size](https://github.com/ramensoftware/windhawk-mods/blob/main/mods/taskbar-icon-size.wh.cpp)
* [Windows 11 Taskbar Styler](https://github.com/ramensoftware/windhawk-mods/blob/main/mods/windows-11-taskbar-styler.wh.cpp)

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
