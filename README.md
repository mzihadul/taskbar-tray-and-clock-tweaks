# Taskbar Tray & Clock Tweaks

A unified [Windhawk](https://windhawk.net/) mod for customizing the Windows taskbar clock, system tray icons, live hardware metrics, media information, web content, taskbar transparency, application visibility, and taskbar/icon sizing.

The project combines functionality from several Windhawk mods and extends them with additional features and unified settings.

![Taskbar Tray & Clock Tweaks Screenshot](./screenshot.png)

## Supported Windows Versions

* **Windows 10 (64-bit)**
* **Windows 11**

> System tray icon customization features are intended for Windows 11.

**Taskbar transparency,** application visibility, and taskbar height/icon-size customization apply to the Windows 11 taskbar.

The **Taskbar Height & Icon Size** feature applies only to the Windows 11 new/XAML taskbar. It is disabled when **Customize the old taskbar on Windows 11** is enabled and is not used on Windows 10.

## Features

### 1. System Tray Icon Control (Windows 11)

Customize the visibility and appearance of native Windows system-tray components.

- Control Center Icons
  - Hide Volume icon
  - Hide Network / Wi-Fi icon
  - Hide Battery icon
  - Grayscale battery icon
- Privacy & Device Indicators
  - Hide Microphone icon
  - Hide Location / GPS icon
  - Hide Studio Effects icon
  - Hide Windows Recall icon
- Input Indicators
  - Hide Language Bar
  - Hide supplementary IME / input indicators
- Configure Notification Center / Bell visibility:
  - Never
  - When there are no new notifications
  - When there are no new notifications and Do Not Disturb is off
  - Always
- Show Desktop
  - Customize the Show Desktop button width
  - Effectively hide the button by setting its width to '0'

## 2. Taskbar Clock Customization

Customize the information displayed in the Windows taskbar clock.

- Top line
- Bottom line
- Middle line (Windows 10 Only Feature)
- Additional tooltip line
- Time format
- Date format
- Weekday format
- Multiple time zones
- Clock width and height where supported
- Maximum clock width on Windows 11
- Line/text spacing

### Date & Time Variables

| Variable            | Description                        |
| ------------------- | ---------------------------------- |
| `%time%`            | Configured time format             |
| `%time<n>%`         | Additional time format             |
| `%time_tz<n>%`      | Time for a configured time zone    |
| `%date%`            | Configured date format             |
| `%date<n>%`         | Additional date format             |
| `%date_tz<n>%`      | Date for a configured time zone    |
| `%weekday%`         | Weekday name                       |
| `%weekday_tz<n>%`   | Weekday for a configured time zone |
| `%weekday_num%`     | Weekday number                     |
| `%weeknum%`         | Regional week number               |
| `%weeknum_iso%`     | ISO 8601 week number               |
| `%dayofyear%`       | Day of the year                    |
| `%timezone%`        | UTC offset                         |
| `%newline%` / `%n%` | Insert a line break                |

## 3. Hardware & Performance Metrics

Display live system performance information directly in the taskbar clock.

### Network
Supports MB/s, KB/s, MBit/s, and KBit/s formats, including dynamic formats.
- `%upload_speed%`
- `%download_speed%`
- `%total_speed%`

### Disk

- `%disk_read%`
- `%disk_write%`
- `%disk_total%`

### CPU

- `%cpu%` — CPU usage
- `%cpu_temp%` — CPU temperature in °C
- `%cpu_temp_f%` — CPU temperature in °F

### RAM

- `%ram%`
- `%ram_used%`
- `%ram_total%`
- `%ram_committed%`
- `%ram_committed_used%`
- `%ram_committed_total%`

### GPU & VRAM

- `%gpu%`
- `%vram%`
- `%vram_used%`
- `%vram_total%`
- `%vram_shared%`
- `%vram_shared_used%`
- `%vram_shared_total%`

### Power & Battery

- `%battery%`
- `%battery_time%`
- `%power%`

The battery indicator can additionally display:

- `⚡` while charging
- `❗` when the battery level is at or below 20%

## 4. Volume Indicator

The `%volume%` variable provides a compact master-volume indicator.

- `🔊` when audio is active
- `🔇` when muted
- Shows the current volume percentage during volume changes
- Returns to the icon automatically after approximately 3 seconds

## 5. Microphone Activity Indicator

The `%mic%` variable displays an indicator when the microphone is currently being used.

```text
🎙️
```

This can be combined with other clock variables to create a compact system-status display.

---

## 6. Media Player Integration

The mod uses Windows' **Global System Media Transport Controls (GSMTC)** to retrieve information from supported media applications.

Available variables include:

| Variable         | Description                |
| ---------------- | -------------------------- |
| `%media_title%`  | Current media title        |
| `%media_artist%` | Artist                     |
| `%media_album%`  | Album                      |
| `%media_status%` | Playback status            |
| `%media_info%`   | Combined media information |

Media information supports:
- Custom formatting
- Maximum-length limits
- Bracket removal
- Ignored media players.

## 7. Web Feeds & Weather

Display information retrieved from web pages, RSS feeds, XML, HTML sources, and weather services.

### Weather

```text
%weather%
```

Weather information is retrieved through [wttr.in](https://wttr.in/) and can be configured using a custom location, unit system, and format. It supports:

- Custom location
- Automatic unit detection
- USCS
- Metric
- Metric with wind speed in m/s
- Custom output formatting

### Web Content

```text
%web<n>%
%web<n>_full%
```

Web-content items can extract text from configured RSS, XML, HTML, or plain-text sources, with optional search/replace rules and maximum-length limits.

## 8. Font & Text Styling (Windows 11 22H2+ Only)

Date and Time elements can be styled independently.

Available customization includes:

- Text color
- `#RRGGBB` colors
- `#AARRGGBB` colors
- Font family
- Font size
- Font weight
- Font stretch
- Font style
- Text alignment
- Character spacing
- Line height
- Line spacing

The clock can also use a dynamic warning color when the battery level reaches the configured low-battery threshold.

## 9. Taskbar Transparency (Windows 11)

**Added in v1.2.0.**

The taskbar can be configured using several visual modes:

| Mode                     | Description                                |
| Default                  | Uses the normal Windows taskbar appearance |
| Fully Transparent        | Removes the taskbar's opaque background    |
| Blurry Glass             | Applies a blurred taskbar appearance       |
| Liquid Glass (Acrylic)   | Uses an acrylic-style taskbar effect       |
| Mica                     | Uses the Windows Mica material             |

**Transparency Level**

- For the alpha-based modes, transparency can be adjusted from:
  - 0% → Opaque
  - 100% → Fully Transparent
- The setting applies to:
  - Fully Transparent
  - Blurry Glass
  - Liquid Glass (Acrylic)

**Mica** uses the Windows material system and therefore does not use the transparency-level value.

The implementation handles both the primary and secondary taskbar windows where applicable.

When the mod is unloaded, the taskbar composition is restored to its original state.

## 10. Hide Running / Pinned Taskbar Apps

**Added in v1.2.0**

Windows 11 taskbar application buttons can be hidden while retaining the rest of the taskbar.

When enabled:

- Running/pinned application buttons are hidden
- Start/Search and system-tray areas remain available
- The taskbar itself remains active

This allows the taskbar to be used primarily for system information, clock, tray controls, and other taskbar elements without displaying application buttons.

**App Exceptions**

- Specific applications can be excluded from the hiding behavior.
  - Exceptions can be entered using:
    - AUMID
    - Visible application name
  - Matching is:
    - Case-insensitive
    - Partial-match capable

For example, an exception can match an application by part of its visible name rather than requiring an exact full-name match.

## 11. Taskbar Height & Icon Size (Windows 11 New Taskbar Only)

**Added in v1.1.0.**

The Windows 11 new taskbar normally uses 24×24 taskbar icons. This feature allows the taskbar and its icons to be resized instead of relying on the default sizing.

Available settings:

| Variable                     | Description                      |
| ---------------------------- | --------------------------       |
| `Taskbar height`             | Taskbar height in pixels         |
| `Icon size`                  | Main taskbar icon size in pixels |
| `Taskbar button width`       | Taskbar button width in pixels   |
| `Small icon size`            | Icon size used by newer Windows 11 builds with small-icon support|
| `Small taskbar button width` | Combined media information |

The default values added by v1.1.0 are:

```text
Taskbar height:             52
Icon size:                  32
Taskbar button width:       44
Small icon size:            16
Small taskbar button width: 32
```
Windows 11's newer small-taskbar-icon support is handled separately from the regular icon-size setting.

> **Compatibility:** This feature is for the Windows 11 new/XAML taskbar. It is automatically skipped when **Customize the old taskbar on Windows 11** is enabled.

## ⚙️ Example Configurations

A customized taskbar clock can combine multiple variables:

```text
🔼 %upload_speed% 🔽 %download_speed% ⚙ %cpu% 🗃️ %ram% %weather% 📅 %date% 🌿 %time% %mic% %volume% ♻️ %battery%
```

The exact appearance depends on the configured clock lines, fonts, spacing, and Windows version.

## 📦 Installation

1. Install [Windhawk](https://windhawk.net/).
2. Open Windhawk.
3. Install or create the **Taskbar Tray & Clock Tweaks** mod.
4. Open the mod settings.
5. Configure the tray, clock, metrics, media, web, styling, and taskbar-size options.
6. Apply the settings.

A restart of Explorer may be required after major Windows updates or when Windows changes internal taskbar components.

## 🧩 Compatibility Notes

This mod hooks internal Windows taskbar and Explorer components. Windows updates can change internal class names, symbols, layouts, and implementation details.

As a result:
- Some features may behave differently between Windows builds.
- Features may require updates after major Windows releases.
- The Windows 11 new/XAML taskbar is required for the taskbar sizing functionality.
- The transparency implementation targets the current Windows 11 taskbar structure.
- Unsupported Windows versions are not modified by the corresponding feature modules.

## 🔄 Version History

See [`CHANGELOG.md`](CHANGELOG.md) for the release history.

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

## 📄 License

This project is released under the **GNU General Public License v3.0 (GPL-3.0)**.

The project incorporates derivative code from the upstream projects identified above. Their respective copyright and licensing terms remain applicable to the portions derived from those projects.

See the [`LICENSE`](./LICENSE) file for the complete license text.

## 🙏 Credits

Special thanks to **m417z** for the original Windhawk projects that provide the foundation for this combined mod.

- Taskbar Clock Customization — m417z
- Taskbar Tray System Icon Tweaks — m417z
- Taskbar Icon Size — m417z

## ⚠️ Disclaimer

This project is provided as-is. 

Windows internal implementations can change between Windows versions and updates, which may affect compatibility or functionality. Features that hook internal Windows components may require updates after major Windows releases.

Always keep a backup of your Windhawk configuration before making significant changes.
