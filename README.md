# Taskbar Tray & Clock Tweaks

A unified [Windhawk](https://windhawk.net/) mod combining granular control over Windows system tray icons with comprehensive taskbar clock customization, live hardware metrics, media information, web feeds, and additional taskbar indicators.

![Taskbar Tray & Clock Tweaks Screenshot](./screenshot.png)

## Supported Windows Versions

* **Windows 10 (64-bit)**
* **Windows 11**

> System tray icon customization features are intended for Windows 11.

---

## Features

### 🖥️ System Tray Icon Control — Windows 11

Customize the visibility and appearance of native Windows system-tray components.

* Hide **Volume** icon
* Hide **Network / Wi-Fi** icon
* Hide **Battery** icon
* Grayscale battery icon
* Hide **Microphone** icon
* Hide **Location / GPS** icon
* Hide **Studio Effects** icon
* Hide **Windows Recall** icon
* Hide **Language Bar**
* Hide supplementary **IME / input indicators**
* Customize **Notification Center / Bell** visibility:

  * Never
  * When there are no new notifications
  * When there are no new notifications and Do Not Disturb is off
  * Always
* Hide the **Show Desktop** button
* Customize the **Show Desktop** button width

---

## 🕐 Taskbar Clock Customization

Customize the information displayed in the Windows taskbar clock.

You can configure:

* Top Line
* Bottom Line
* Middle Line — Windows 10
* Additional tooltip line
* Time format
* Date format
* Weekday format
* Time zones
* Clock width and height
* Text spacing
* Font and text styling

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

---

## 📊 Hardware & Performance Metrics

Display live system performance information directly in the taskbar clock.

### Network

* `%upload_speed%`
* `%download_speed%`
* `%total_speed%`

### Disk

* `%disk_read%`
* `%disk_write%`
* `%disk_total%`

### CPU

* `%cpu%`
* `%cpu_temp%`
* `%cpu_temp_f%`

### RAM

* `%ram%`
* `%ram_used%`
* `%ram_total%`
* `%ram_committed%`
* `%ram_committed_used%`
* `%ram_committed_total%`

### GPU & VRAM

* `%gpu%`
* `%vram%`
* `%vram_used%`
* `%vram_total%`
* `%vram_shared%`
* `%vram_shared_used%`
* `%vram_shared_total%`

### Power & Battery

* `%battery%`
* `%battery_time%`
* `%power%`

The battery indicator can additionally display:

* `⚡` while charging
* `❗` when the battery level is at or below 20%

---

## 🔊 Volume Indicator

The `%volume%` variable provides a compact master-volume indicator.

* `🔊` when audio is active
* `🔇` when muted
* Displays the current volume percentage when the volume changes
* Automatically returns to the icon after approximately 3 seconds

Example:

```text
🔊 75%
```

---

## 🎙️ Microphone Activity Indicator

The `%mic%` variable displays an indicator when the microphone is currently being used.

```text
🎙️
```

This can be combined with other clock variables to create a compact system-status display.

---

## 🎵 Media Player Integration

The mod uses Windows' **Global System Media Transport Controls (GSMTC)** to retrieve information from supported media applications.

Available variables include:

| Variable         | Description                |
| ---------------- | -------------------------- |
| `%media_title%`  | Current media title        |
| `%media_artist%` | Artist                     |
| `%media_album%`  | Album                      |
| `%media_status%` | Playback status            |
| `%media_info%`   | Combined media information |

Media information can be formatted and truncated according to the configured settings.

---

## 🌤️ Web Feeds & Weather

Display information retrieved from web pages, RSS feeds, XML, HTML sources, and weather services.

### Weather

```text
%weather%
```

Weather information is retrieved through [wttr.in](https://wttr.in/) and can be configured using a custom location, unit system, and format.

### Web Content

```text
%web<n>%
%web<n>_full%
```

Web content can be extracted from supported RSS, XML, HTML, and plain-text sources.

---

## 🎨 Font & Text Styling

On supported Windows 11 versions, the clock's Date and Time elements can be styled independently.

Available customization includes:

* Text color
* `#RRGGBB` / `#AARRGGBB` colors
* Font family
* Font size
* Font weight
* Font stretch
* Font style
* Text alignment
* Character spacing
* Line height
* Line spacing

The clock can also use a dynamic warning color when the battery level reaches the configured low-battery threshold.

---

## ⚙️ Example

A customized taskbar clock can combine multiple variables:

```text
%time% | %cpu% | %ram% | %cpu_temp% | %volume%
```

Or a more compact setup:

```text
%time%
%cpu% CPU | %ram% RAM | %gpu% GPU
```

The exact layout depends on the user's configured clock settings.

---

## 📦 Installation

1. Install [Windhawk](https://windhawk.net/).
2. Open Windhawk.
3. Create or install the **Taskbar Tray & Clock Tweaks** mod.
4. Open the mod's settings.
5. Configure the tray, clock, metrics, media, web, and styling options.
6. Apply the settings.

---

## 🔀 Project Background

This project is a **combined derivative work** integrating functionality from two existing Windhawk projects:

### Taskbar Clock Customization

Original project by **m417z**:

https://github.com/ramensoftware/windhawk-mods/blob/main/mods/taskbar-clock-customization.wh.cpp

The clock, formatting, hardware metrics, media, web-content, weather, and related taskbar-clock functionality are derived from this project.

### Taskbar Tray System Icon Tweaks

Original project by **m417z**:

https://github.com/ramensoftware/windhawk-mods/blob/main/mods/taskbar-tray-system-icon-tweaks.wh.cpp

The system-tray icon customization functionality is derived from this project.

---

## 🛠️ Additional Modifications & Integration

Additional modifications and integration by **mzihadul** include:

* Combining the taskbar clock and system-tray functionality into a single Windhawk mod
* Unified settings and configuration
* Unified symbol hooking and module handling
* `%volume%` taskbar variable
* Master volume and mute detection
* Temporary volume-percentage display
* `%mic%` microphone activity variable
* Microphone activity detection
* Charging-state indicator for `%battery%`
* Low-battery indicator for `%battery%`
* Low-battery clock styling
* Integration and maintenance of the combined codebase

The project should therefore be considered a **derivative and integrated work**, rather than an entirely original implementation.

---

## 📄 License

This project is released under the **GNU General Public License v3.0 (GPL-3.0)**.

The project incorporates derivative code from the upstream projects identified above. Their respective copyright and licensing terms remain applicable to the portions derived from those projects.

See the [`LICENSE`](./LICENSE) file for the complete license text.

---

## 🙏 Credits

Special thanks to **m417z** for the original Windhawk projects that provide the foundation for this combined mod.

* Taskbar Clock Customization — m417z
* Taskbar Tray System Icon Tweaks — m417z

Additional integration, modifications, and maintenance:

**mzihadul**

---

## ⚠️ Disclaimer

This project is provided as-is. Windows internal implementations can change between Windows versions and updates, which may affect compatibility or functionality.

Always keep a backup of your Windhawk configuration before making significant changes.
