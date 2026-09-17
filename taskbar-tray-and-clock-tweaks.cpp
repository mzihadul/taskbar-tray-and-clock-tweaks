// ==WindhawkMod==
// @id              taskbar-tray-and-clock-tweaks
// @name            Taskbar Tray & Clock Tweaks
// @description     Customizable taskbar clock, system metrics, media info, and granular system tray icon visibility controls.
// @version         1.0.0
// @author          mzihadul
// @github          https://github.com/mzihadul/taskbar-tray-and-clock-tweaks
// @include         explorer.exe
// @architecture    x86-64
// @compilerOptions -lole32 -loleaut32 -lruntimeobject -lversion -lwininet -lshlwapi -ldxgi -lpdh -lpowrprof
// ==/WindhawkMod==

// This project is a combined derivative work based on:
//
// 1. Taskbar Clock Customization
//    Original author: m417z
//    https://github.com/m417z/my-windhawk-mods
//
// 2. Taskbar Tray System Icon Tweaks
//    Original author: m417z
//    https://github.com/ramensoftware/windhawk-mods
//
// The two projects have been integrated into a single Windhawk mod.
// Additional modifications and integration by mzihadul include:
//
// - Unified taskbar clock and system tray functionality
// - Volume indicator (%volume%)
// - Microphone activity indicator (%mic%)
// - Battery charging indicator
// - Low-battery indicator
// - Battery-related clock styling
// - Unified settings, hooks, and module lifecycle
//
// This project is licensed under the GNU General Public License v3.0.

// ==WindhawkModReadme==
/*
# Taskbar Tray & Clock Tweaks

A unified Windhawk mod combining granular control over Windows system tray icon visibility with comprehensive taskbar clock customization, live hardware metrics, media controls, and web feed integration.

Only **Windows 10 (64-bit)** and **Windows 11** are supported. System tray icon hiding features require Windows 11.

---

## Preview

![Screenshot](https://raw.githubusercontent.com/mzihadul/taskbar-tray-and-clock-tweaks/main/screenshot.png) 

---

## Features

### 1. System Tray Icon Control (Windows 11)
Selectively hide or style native system tray components:
* **Control Center Icons:** Volume, Network/Wi-Fi, and Battery.
* **Battery Tweaks:** Grayscale battery mode (uses standard text foreground instead of accent green/yellow).
* **System Privacy & Device Icons:** Microphone, Location (GPS), Studio Effects, and Windows Recall.
* **Input Indicators:** Language bar and supplementary input method (IME) status icons.
* **Notification Center (Bell):** Hide always, or auto-hide dynamically when there are no unread notifications (with optional Do Not Disturb override).
* **Show Desktop Button:** Hide or adjust custom pixel width.

---

### 2. Taskbar Clock Customization & Live Metrics
Configure custom text lines for **Top Line**, **Bottom Line**, **Middle Line** (Windows 10 only), and **Tooltip Extra Line** using dynamic tags.

#### Date & Time Patterns
* `%time%` — Configured time format.
  * `%time<n>%` — Additional time format (separated by `;` in format settings, starting at `<n>=2`).
  * `%time_tz<n>%` — Time mapped to configured time zone index `<n>`.
* `%date%` — Configured date format.
  * `%date<n>%` — Additional date format (starting at `<n>=2`).
  * `%date_tz<n>%` — Date mapped to configured time zone index `<n>`.
* `%weekday%` — Full, abbreviated, or custom comma-separated week day name.
  * `%weekday_tz<n>%` — Weekday mapped to custom time zone index `<n>`.
* `%weekday_num%` — Week day number based on locale's first day of week (1 to 7).
* `%weeknum%` — Week number according to regional settings.
* `%weeknum_iso%` — ISO 8601 week number.
* `%dayofyear%` — Day number of the year (1–366).
* `%timezone%` — UTC bias offset (e.g. `+06:00`).
* `%newline%` or `%n%` — Inserts a line break.

#### System Hardware & Performance Metrics
* **Network Speeds:** `%upload_speed%`, `%download_speed%`, `%total_speed%` (Dynamic KB/s or MB/s formatting).
* **Disk Activity:** `%disk_read%`, `%disk_write%`, `%disk_total%`.
* **Processor (CPU):** `%cpu%` (usage percentage), `%cpu_temp%` (°C), `%cpu_temp_f%` (°F).
* **Memory (RAM):** `%ram%` (usage percentage), `%ram_used%` (GB), `%ram_total%` (GB), `%ram_committed%` (%), `%ram_committed_used%` (GB), `%ram_committed_total%` (GB).
* **Graphics (GPU & VRAM):** `%gpu%` (3D engine usage %), `%vram%` (dedicated VRAM %), `%vram_used%` (GB), `%vram_total%` (GB), `%vram_shared%` (shared pool %), `%vram_shared_used%` (GB), `%vram_shared_total%` (GB).
* **Power & Battery:** 
  * `%battery%` — Battery percentage (appends `⚡` when charging on AC, adds `❗` when critical battery ≤ 20%).
  * `%battery_time%` — Remaining runtime / charging time in `h:mm` format.
  * `%power%` — Discharge / charge rate in watts (`+W` or `-W`).
* **Volume Indicator:** `%volume%` — Master volume icon (`🔊` / `🔇`) that expands to show level `%` during volume adjustments and auto-hides back to icon after 3 seconds.
* **Microphone State:** `%mic%` — Active in-use indicator (`🎙️`) when any application uses the recording device.

#### Media Player Integration (GSMTC)
Reads metadata from media apps (Spotify, Chrome, Edge, VLC, etc.):
* `%media_title%` — Media title.
* `%media_artist%` — Media artist.
* `%media_album%` — Album title.
* `%media_status%` — Playback state emoji (`⏯`, `⏸`, `⏹`).
* `%media_info%` — Combined formatted text with truncation support (e.g., `Artist - Title`).

#### Web Feeds & Weather
* `%weather%` — Live weather status powered by [wttr.in](https://wttr.in) using custom location, units, and formatting strings.
* `%web<n>%` / `%web<n>_full%` — Live text extracted from RSS feeds, XML, HTML, or raw web pages.

---

### 3. Font & Text Styling (Windows 11 22H2+)
Independent visual styling for both Date and Time lines:
* Hex color overrides (`#RRGGBB` / `#AARRGGBB`) or standard named colors.
* Dynamic red warning color trigger when battery drops below 20%.
* Font Family, Font Size, Font Weight, Font Stretch, and Font Style.
* Text alignment (Left, Center, Right, Justified), character spacing, line height, and line spacing.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- hideVolumeIcon: false
  $name: Hide volume icon
- hideNetworkIcon: false
  $name: Hide network icon
- hideBatteryIcon: false
  $name: Hide battery icon
- grayscaleBatteryIcon: false
  $name: Grayscale battery icon
  $description: >-
    Show the battery icon using the standard text color instead of its colored variant.
- hideMicrophoneIcon: false
  $name: Hide microphone icon
- hideGeolocationIcon: false
  $name: Hide location (e.g. GPS) icon
- hideStudioEffectsIcon: false
  $name: Hide Studio Effects icon
- hideRecallIcon: false
  $name: Hide Recall icon
- hideLanguageBar: false
  $name: Hide language bar
- hideLanguageSupplementaryIcons: false
  $name: Hide language supplementary icons
- hideBellIcon: never
  $name: Hide bell icon
  $options:
  - never: Never
  - whenInactive: When there are no new notifications
  - whenInactiveAndNoDnd: When there are no new notifications and "Do not disturb" is off
  - always: Always
- showDesktopButtonWidth: 12
  $name: '"Show desktop" button width'
- ShowSeconds: true
  $name: Show seconds
- TimeFormat: >-
    hh':'mm':'ss tt
  $name: Time format
- DateFormat: >-
    ddd',' MMM dd yyyy
  $name: Date format
- DateLocale: ""
  $name: Date locale
- WeekdayFormat: dddd
  $name: Week day format
  $options:
  - dddd: Full day of the week
  - ddd: Abbreviated day of the week
  - custom: Custom, specified below
- WeekdayFormatCustom: Sun, Mon, Tue, Wed, Thu, Fri, Sat
  $name: Custom week day format
- TopLine: '%date% | %time%'
  $name: Top line
- BottomLine: '%web1%'
  $name: Bottom line
- MiddleLine: '%weekday%'
  $name: Middle line (Windows 10 only)
- TooltipLine: '%web1_full%'
  $name: Tooltip extra line
- TooltipLineMode: append
  $name: Tooltip line mode
  $options:
  - append: Append to default tooltip
  - replace: Replace default tooltip
- Width: 180
  $name: Clock width (Windows 10 only)
- Height: 60
  $name: Clock height (Windows 10 only)
- MaxWidth: 0
  $name: Clock max width (Windows 11 only)
- TextSpacing: 0
  $name: Line spacing
- DataCollection:
  - NetworkMetricsFormat: mbs
    $name: Network metrics format
    $options:
    - mbs: MB/s
    - mbsNumberOnly: MB/s, number only
    - mbsDynamic: MB/s or KB/s (dynamic)
    - mbits: MBit/s
    - mbitsNumberOnly: MBit/s, number only
    - mbitsDynamic: MBit/s or KBit/s (dynamic)
  - NetworkMetricsFixedDecimals: -1
    $name: Network metrics fixed decimal places
  - DiskMetricsFormat: sameAsNetwork
    $name: Disk metrics format
    $options:
    - sameAsNetwork: Same as network metrics format
    - mbs: MB/s
    - mbsNumberOnly: MB/s, number only
    - mbsDynamic: MB/s or KB/s (dynamic)
    - mbits: MBit/s
    - mbitsNumberOnly: MBit/s, number only
    - mbitsDynamic: MBit/s or KBit/s (dynamic)
  - DiskMetricsFixedDecimals: -1
    $name: Disk metrics fixed decimal places
  - PercentageFormat: spacePaddingAndSymbol
    $name: Percentage format
    $options:
    - spacePaddingAndSymbol: Pad with spaces, add percentage symbol
    - spacePadding: Pad with spaces, number only
    - singleSpacePadding: Pad with a single space, number only (for monospaced fonts)
    - zeroPadding: Pad with zeros, number only
    - noPadding: No padding, number only
  - UpdateInterval: 1
    $name: Update interval
  - NetworkAdapterName: ""
    $name: Network adapter name
  - GpuAdapterName: ""
    $name: GPU adapter name
  $name: System performance metrics
- MediaPlayer:
  - IgnoredPlayers: [""]
    $name: Ignored media players
  - MaxLength: 28
    $name: Maximum info length
  - MediaInfoFormat: "%media_artist% - %media_title%"
    $name: Format when media is playing
  - NoMediaText: No media
    $name: Format when media is not playing
  - RemoveBrackets: false
    $name: Remove brackets from info
  $name: Media player info
- WebContentWeatherLocation: ""
  $name: Weather location
- WebContentWeatherFormat: "%c \U0001F321\uFE0F%t \U0001F32C\uFE0F%w"
  $name: Weather format
- WebContentWeatherUnits: autoDetect
  $name: Weather units
  $options:
  - autoDetect: Auto (default)
  - uscs: USCS (used by default in US)
  - metric: Metric (SI) (used by default everywhere except US)
  - metricMsWind: Metric (SI), but show wind speed in m/s
- WebContentsItems:
  - - Url: https://rss.nytimes.com/services/xml/rss/nyt/World.xml
      $name: Web content URL
    - BlockStart: '<item>'
      $name: Web content block start
    - Start: '<title>'
      $name: Web content start
    - End: '</title>'
      $name: Web content end
    - ContentMode: xmlHtml
      $name: Content mode
      $options:
      - "": Plain text
      - html: HTML
      - xml: XML
      - xmlHtml: XML+HTML
    - SearchReplace:
      - - Search: ""
        - Replace: ""
      $name: Content search/replace
    - MaxLength: 28
      $name: Web content maximum length
  $name: Web content items
- WebContentsUpdateInterval: 10
  $name: Web content update interval
- TimeZones: ["Eastern Standard Time"]
  $name: Time zones
- TimeStyle:
  - Hidden: false
  - TextColor: ""
    $name: Text color
  - TextAlignment: ""
    $name: Text alignment
    $options:
    - "": Default
    - Right: Right
    - Center: Center
    - Left: Left
    - Justify: Justified
  - FontSize: 0
    $name: Font size
  - FontFamily: ""
    $name: Font family
  - FontWeight: ""
    $name: Font weight
    $options:
    - "": Default
    - Thin: Thin
    - ExtraLight: Extra light
    - Light: Light
    - SemiLight: Semi light
    - Normal: Normal
    - Medium: Medium
    - SemiBold: Semi bold
    - Bold: Bold
    - ExtraBold: Extra bold
    - Black: Black
    - ExtraBlack: Extra black
  - FontStyle: ""
    $name: Font style
    $options:
    - "": Default
    - Normal: Normal
    - Oblique: Oblique
    - Italic: Italic
  - FontStretch: ""
    $name: Font stretch
    $options:
    - "": Default
    - Undefined: Undefined
    - UltraCondensed: Ultra condensed
    - ExtraCondensed: Extra condensed
    - Condensed: Condensed
    - SemiCondensed: Semi condensed
    - Normal: Normal
    - SemiExpanded: Semi expanded
    - Expanded: Expanded
    - ExtraExpanded: Extra expanded
    - UltraExpanded: Ultra expanded
  - CharacterSpacing: 0
    $name: Character spacing
  - LineHeight: 0
    $name: Line height
  $name: Top line style (Windows 11 version 22H2 and newer)
- DateStyle:
  - Hidden: false
  - TextColor: ""
    $name: Text color
  - TextAlignment: ""
    $name: Text alignment
    $options:
    - "": Default
    - Right: Right
    - Center: Center
    - Left: Left
    - Justify: Justified
  - FontSize: 0
    $name: Font size
  - FontFamily: ""
    $name: Font family
  - FontWeight: ""
    $name: Font weight
    $options:
    - "": Default
    - Thin: Thin
    - ExtraLight: Extra light
    - Light: Light
    - SemiLight: Semi light
    - Normal: Normal
    - Medium: Medium
    - SemiBold: Semi bold
    - Bold: Bold
    - ExtraBold: Extra bold
    - Black: Black
    - ExtraBlack: Extra black
  - FontStyle: ""
    $name: Font style
    $options:
    - "": Default
    - Normal: Normal
    - Oblique: Oblique
    - Italic: Italic
  - FontStretch: ""
    $name: Font stretch
    $options:
    - "": Default
    - Undefined: Undefined
    - UltraCondensed: Ultra condensed
    - ExtraCondensed: Extra condensed
    - Condensed: Condensed
    - SemiCondensed: Semi condensed
    - Normal: Normal
    - SemiExpanded: Semi expanded
    - Expanded: Expanded
    - ExtraExpanded: Extra expanded
    - UltraExpanded: Ultra expanded
  - CharacterSpacing: 0
    $name: Character spacing
  - LineHeight: 0
    $name: Line height
  $name: Bottom line style (Windows 11 version 22H2 and newer)
- oldTaskbarOnWin11: false
  $name: Customize the old taskbar on Windows 11
*/
// ==/WindhawkModSettings==

// Source code is published under The GNU General Public License v3.0.

// ==WindhawkModSettings==
/*
- hideVolumeIcon: false
  $name: Hide volume icon
- hideNetworkIcon: false
  $name: Hide network icon
- hideBatteryIcon: false
  $name: Hide battery icon
- grayscaleBatteryIcon: false
  $name: Grayscale battery icon
  $description: >-
    Show the battery icon using the standard text color instead of its colored variant.
- hideMicrophoneIcon: false
  $name: Hide microphone icon
- hideGeolocationIcon: false
  $name: Hide location (e.g. GPS) icon
- hideStudioEffectsIcon: false
  $name: Hide Studio Effects icon
- hideRecallIcon: false
  $name: Hide Recall icon
- hideLanguageBar: false
  $name: Hide language bar
- hideLanguageSupplementaryIcons: false
  $name: Hide language supplementary icons
- hideBellIcon: never
  $name: Hide bell icon
  $options:
  - never: Never
  - whenInactive: When there are no new notifications
  - whenInactiveAndNoDnd: When there are no new notifications and "Do not disturb" is off
  - always: Always
- showDesktopButtonWidth: 12
  $name: '"Show desktop" button width'
- ShowSeconds: true
  $name: Show seconds
- TimeFormat: >-
    hh':'mm':'ss tt
  $name: Time format
- DateFormat: >-
    ddd',' MMM dd yyyy
  $name: Date format
- DateLocale: ""
  $name: Date locale
- WeekdayFormat: dddd
  $name: Week day format
  $options:
  - dddd: Full day of the week
  - ddd: Abbreviated day of the week
  - custom: Custom, specified below
- WeekdayFormatCustom: Sun, Mon, Tue, Wed, Thu, Fri, Sat
  $name: Custom week day format
- TopLine: '%date% | %time%'
  $name: Top line
- BottomLine: '%web1%'
  $name: Bottom line
- MiddleLine: '%weekday%'
  $name: Middle line (Windows 10 only)
- TooltipLine: '%web1_full%'
  $name: Tooltip extra line
- TooltipLineMode: append
  $name: Tooltip line mode
  $options:
  - append: Append to default tooltip
  - replace: Replace default tooltip
- Width: 180
  $name: Clock width (Windows 10 only)
- Height: 60
  $name: Clock height (Windows 10 only)
- MaxWidth: 0
  $name: Clock max width (Windows 11 only)
- TextSpacing: 0
  $name: Line spacing
- DataCollection:
  - NetworkMetricsFormat: mbs
    $name: Network metrics format
    $options:
    - mbs: MB/s
    - mbsNumberOnly: MB/s, number only
    - mbsDynamic: MB/s or KB/s (dynamic)
    - mbits: MBit/s
    - mbitsNumberOnly: MBit/s, number only
    - mbitsDynamic: MBit/s or KBit/s (dynamic)
  - NetworkMetricsFixedDecimals: -1
    $name: Network metrics fixed decimal places
  - DiskMetricsFormat: sameAsNetwork
    $name: Disk metrics format
    $options:
    - sameAsNetwork: Same as network metrics format
    - mbs: MB/s
    - mbsNumberOnly: MB/s, number only
    - mbsDynamic: MB/s or KB/s (dynamic)
    - mbits: MBit/s
    - mbitsNumberOnly: MBit/s, number only
    - mbitsDynamic: MBit/s or KBit/s (dynamic)
  - DiskMetricsFixedDecimals: -1
    $name: Disk metrics fixed decimal places
  - PercentageFormat: spacePaddingAndSymbol
    $name: Percentage format
    $options:
    - spacePaddingAndSymbol: Pad with spaces, add percentage symbol
    - spacePadding: Pad with spaces, number only
    - singleSpacePadding: Pad with a single space, number only (for monospaced fonts)
    - zeroPadding: Pad with zeros, number only
    - noPadding: No padding, number only
  - UpdateInterval: 1
    $name: Update interval
  - NetworkAdapterName: ""
    $name: Network adapter name
  - GpuAdapterName: ""
    $name: GPU adapter name
  $name: System performance metrics
- MediaPlayer:
  - IgnoredPlayers: [""]
    $name: Ignored media players
  - MaxLength: 28
    $name: Maximum info length
  - MediaInfoFormat: "%media_artist% - %media_title%"
    $name: Format when media is playing
  - NoMediaText: No media
    $name: Format when media is not playing
  - RemoveBrackets: false
    $name: Remove brackets from info
  $name: Media player info
- WebContentWeatherLocation: ""
  $name: Weather location
- WebContentWeatherFormat: "%c \U0001F321\uFE0F%t \U0001F32C\uFE0F%w"
  $name: Weather format
- WebContentWeatherUnits: autoDetect
  $name: Weather units
  $options:
  - autoDetect: Auto (default)
  - uscs: USCS (used by default in US)
  - metric: Metric (SI) (used by default everywhere except US)
  - metricMsWind: Metric (SI), but show wind speed in m/s
- WebContentsItems:
  - - Url: https://rss.nytimes.com/services/xml/rss/nyt/World.xml
      $name: Web content URL
    - BlockStart: '<item>'
      $name: Web content block start
    - Start: '<title>'
      $name: Web content start
    - End: '</title>'
      $name: Web content end
    - ContentMode: xmlHtml
      $name: Content mode
      $options:
      - "": Plain text
      - html: HTML
      - xml: XML
      - xmlHtml: XML+HTML
    - SearchReplace:
      - - Search: ""
        - Replace: ""
      $name: Content search/replace
    - MaxLength: 28
      $name: Web content maximum length
  $name: Web content items
- WebContentsUpdateInterval: 10
  $name: Web content update interval
- TimeZones: ["Eastern Standard Time"]
  $name: Time zones
- TimeStyle:
  - Hidden: false
  - TextColor: ""
    $name: Text color
  - TextAlignment: ""
    $name: Text alignment
    $options:
    - "": Default
    - Right: Right
    - Center: Center
    - Left: Left
    - Justify: Justified
  - FontSize: 0
    $name: Font size
  - FontFamily: ""
    $name: Font family
  - FontWeight: ""
    $name: Font weight
    $options:
    - "": Default
    - Thin: Thin
    - ExtraLight: Extra light
    - Light: Light
    - SemiLight: Semi light
    - Normal: Normal
    - Medium: Medium
    - SemiBold: Semi bold
    - Bold: Bold
    - ExtraBold: Extra bold
    - Black: Black
    - ExtraBlack: Extra black
  - FontStyle: ""
    $name: Font style
    $options:
    - "": Default
    - Normal: Normal
    - Oblique: Oblique
    - Italic: Italic
  - FontStretch: ""
    $name: Font stretch
    $options:
    - "": Default
    - Undefined: Undefined
    - UltraCondensed: Ultra condensed
    - ExtraCondensed: Extra condensed
    - Condensed: Condensed
    - SemiCondensed: Semi condensed
    - Normal: Normal
    - SemiExpanded: Semi expanded
    - Expanded: Expanded
    - ExtraExpanded: Extra expanded
    - UltraExpanded: Ultra expanded
  - CharacterSpacing: 0
    $name: Character spacing
  - LineHeight: 0
    $name: Line height
  $name: Top line style (Windows 11 version 22H2 and newer)
- DateStyle:
  - Hidden: false
  - TextColor: ""
    $name: Text color
  - TextAlignment: ""
    $name: Text alignment
    $options:
    - "": Default
    - Right: Right
    - Center: Center
    - Left: Left
    - Justify: Justified
  - FontSize: 0
    $name: Font size
  - FontFamily: ""
    $name: Font family
  - FontWeight: ""
    $name: Font weight
    $options:
    - "": Default
    - Thin: Thin
    - ExtraLight: Extra light
    - Light: Light
    - SemiLight: Semi light
    - Normal: Normal
    - Medium: Medium
    - SemiBold: Semi bold
    - Bold: Bold
    - ExtraBold: Extra bold
    - Black: Black
    - ExtraBlack: Extra black
  - FontStyle: ""
    $name: Font style
    $options:
    - "": Default
    - Normal: Normal
    - Oblique: Oblique
    - Italic: Italic
  - FontStretch: ""
    $name: Font stretch
    $options:
    - "": Default
    - Undefined: Undefined
    - UltraCondensed: Ultra condensed
    - ExtraCondensed: Extra condensed
    - Condensed: Condensed
    - SemiCondensed: Semi condensed
    - Normal: Normal
    - SemiExpanded: Semi expanded
    - Expanded: Expanded
    - ExtraExpanded: Extra expanded
    - UltraExpanded: Ultra expanded
  - CharacterSpacing: 0
    $name: Character spacing
  - LineHeight: 0
    $name: Line height
  $name: Bottom line style (Windows 11 version 22H2 and newer)
- oldTaskbarOnWin11: false
  $name: Customize the old taskbar on Windows 11
*/
// ==/WindhawkModSettings==

#include <windhawk_utils.h>

using WindhawkUtils::StringSetting;

#include <algorithm>
#include <atomic>
#include <functional>
#include <list>
#include <mutex>
#include <optional>
#include <regex>
#include <string>
#include <string_view>
#include <unordered_set>
#include <vector>

using namespace std::string_view_literals;

#include <initguid.h>
#include <comutil.h>
#include <dxgi.h>
#include <endpointvolume.h>
#include <mmdeviceapi.h>
#include <mshtml.h>
#include <pdh.h>
#include <pdhmsg.h>
#include <powrprof.h>
#include <psapi.h>
#include <shlwapi.h>
#include <wininet.h>

#undef GetCurrentTime

#include <winrt/Windows.Data.Xml.Dom.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Media.Control.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Xaml.Automation.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Windows.UI.Xaml.Markup.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/base.h>

using namespace winrt::Windows::UI::Xaml;

#ifndef URL_ESCAPE_ASCII_URI_COMPONENT
#define URL_ESCAPE_ASCII_URI_COMPONENT 0x00080000
#endif

// ==========================================
// COMMON ENUMS & SETTINGS STRUCTS
// ==========================================

enum class HideBellIcon {
    never,
    whenInactive,
    whenInactiveAndNoDnd,
    always,
};

enum class TooltipLineMode {
    append,
    replace,
};

enum class NetworkMetricsFormat {
    mbs,
    mbsNumberOnly,
    mbsDynamic,
    mbits,
    mbitsNumberOnly,
    mbitsDynamic,
};

enum class PercentageFormat {
    spacePaddingAndSymbol,
    spacePadding,
    singleSpacePadding,
    zeroPadding,
    noPadding,
};

struct DataCollectionSettings {
    NetworkMetricsFormat networkMetricsFormat;
    int networkMetricsFixedDecimals;
    NetworkMetricsFormat diskMetricsFormat;
    int diskMetricsFixedDecimals;
    PercentageFormat percentageFormat;
    int updateInterval;
    StringSetting networkAdapterName;
    StringSetting gpuAdapterName;
};

struct MediaPlayerSettings {
    std::vector<StringSetting> ignoredPlayers;
    int maxLength;
    StringSetting mediaInfoFormat;
    StringSetting noMediaText;
    bool removeBrackets;
};

enum class WebContentWeatherUnits {
    autoDetect,
    uscs,
    metric,
    metricMsWind,
};

enum class ContentMode {
    plainText,
    html,
    xml,
    xmlHtml,
};

struct WebContentsSettings {
    StringSetting url;
    StringSetting blockStart;
    StringSetting start;
    StringSetting end;
    ContentMode contentMode;
    std::vector<std::pair<std::wregex, std::wstring>> searchReplace;
    int maxLength;
};

struct TextStyleSettings {
    bool hidden;
    StringSetting textColor;
    StringSetting textAlignment;
    int fontSize;
    StringSetting fontFamily;
    StringSetting fontWeight;
    StringSetting fontStyle;
    StringSetting fontStretch;
    int characterSpacing;
    int lineHeight;
};

struct Settings {
    // Tray Settings
    bool hideVolumeIcon;
    bool hideNetworkIcon;
    bool hideBatteryIcon;
    bool grayscaleBatteryIcon;
    bool hideMicrophoneIcon;
    bool hideGeolocationIcon;
    bool hideStudioEffectsIcon;
    bool hideRecallIcon;
    bool hideLanguageBar;
    bool hideLanguageSupplementaryIcons;
    HideBellIcon hideBellIcon;
    int showDesktopButtonWidth;

    // Clock Settings
    bool showSeconds;
    StringSetting timeFormat;
    StringSetting dateFormat;
    StringSetting dateLocale;
    StringSetting weekdayFormat;
    std::vector<std::wstring> weekdayFormatCustom;
    StringSetting topLine;
    StringSetting bottomLine;
    StringSetting middleLine;
    StringSetting tooltipLine;
    TooltipLineMode tooltipLineMode;
    int width;
    int height;
    int maxWidth;
    int textSpacing;
    DataCollectionSettings dataCollection;
    MediaPlayerSettings mediaPlayer;
    StringSetting webContentWeatherLocation;
    StringSetting webContentWeatherFormat;
    WebContentWeatherUnits webContentWeatherUnits;
    std::vector<WebContentsSettings> webContentsItems;
    int webContentsUpdateInterval;
    std::vector<StringSetting> timeZones;
    TextStyleSettings timeStyle;
    TextStyleSettings dateStyle;
    bool oldTaskbarOnWin11;

    // Compatibility
    StringSetting webContentsUrl;
    StringSetting webContentsBlockStart;
    StringSetting webContentsStart;
    StringSetting webContentsEnd;
    int webContentsMaxLength;
} g_settings;

#define FORMATTED_BUFFER_SIZE 256
#define INTEGER_BUFFER_SIZE sizeof("-2147483648")

enum class WinVersion {
    Unsupported,
    Win10,
    Win11,
    Win11_22H2,
    Win11_24H2,
};

WinVersion g_winVersion;
std::atomic<bool> g_systemTrayModuleHooked{false};
std::atomic<bool> g_unloading{false};
std::atomic<bool> g_initialized{false};
std::atomic<bool> g_explorerPatcherInitialized{false};

// ==========================================
// GENERAL SHARED HELPERS
// ==========================================

HWND FindCurrentProcessTaskbarWnd() {
    HWND hTaskbarWnd = nullptr;
    EnumWindows(
        [](HWND hWnd, LPARAM lParam) -> BOOL {
            DWORD dwProcessId;
            WCHAR className[32];
            if (GetWindowThreadProcessId(hWnd, &dwProcessId) &&
                dwProcessId == GetCurrentProcessId() &&
                GetClassName(hWnd, className, ARRAYSIZE(className)) &&
                _wcsicmp(className, L"Shell_TrayWnd") == 0) {
                *reinterpret_cast<HWND*>(lParam) = hWnd;
                return FALSE;
            }
            return TRUE;
        },
        reinterpret_cast<LPARAM>(&hTaskbarWnd));
    return hTaskbarWnd;
}

VS_FIXEDFILEINFO* GetModuleVersionInfo(HMODULE hModule, UINT* puPtrLen) {
    void* pFixedFileInfo = nullptr;
    UINT uPtrLen = 0;
    HRSRC hResource = FindResource(hModule, MAKEINTRESOURCE(VS_VERSION_INFO), RT_VERSION);
    if (hResource) {
        HGLOBAL hGlobal = LoadResource(hModule, hResource);
        if (hGlobal) {
            void* pData = LockResource(hGlobal);
            if (pData) {
                if (!VerQueryValue(pData, L"\\", &pFixedFileInfo, &uPtrLen) || uPtrLen == 0) {
                    pFixedFileInfo = nullptr;
                    uPtrLen = 0;
                }
            }
        }
    }
    if (puPtrLen) *puPtrLen = uPtrLen;
    return (VS_FIXEDFILEINFO*)pFixedFileInfo;
}

FrameworkElement EnumChildElements(FrameworkElement element, std::function<bool(FrameworkElement)> enumCallback) {
    int childrenCount = Media::VisualTreeHelper::GetChildrenCount(element);
    for (int i = 0; i < childrenCount; i++) {
        auto child = Media::VisualTreeHelper::GetChild(element, i).try_as<FrameworkElement>();
        if (!child) continue;
        if (enumCallback(child)) return child;
    }
    return nullptr;
}

FrameworkElement FindChildByName(FrameworkElement element, std::wstring_view name) {
    return EnumChildElements(element, [name](FrameworkElement child) {
        return child.Name() == name;
    });
}

FrameworkElement FindChildByClassName(FrameworkElement element, PCWSTR className) {
    return EnumChildElements(element, [className](FrameworkElement child) {
        return winrt::get_class_name(child) == className;
    });
}

FrameworkElement EnumParentElements(FrameworkElement element, std::function<bool(FrameworkElement)> enumCallback) {
    auto parent = element;
    while (true) {
        parent = Media::VisualTreeHelper::GetParent(parent).try_as<FrameworkElement>();
        if (!parent) return nullptr;
        if (enumCallback(parent)) return parent;
    }
}

FrameworkElement GetParentElementByName(FrameworkElement element, PCWSTR name) {
    return EnumParentElements(element, [name](FrameworkElement parent) {
        return parent.Name() == name;
    });
}

bool IsChildOfElementByName(FrameworkElement element, PCWSTR name) {
    return !!GetParentElementByName(element, name);
}

std::wstring StringToHex(std::wstring_view input) {
    static const WCHAR kHexDigits[] = L"0123456789ABCDEF";
    std::wstring output;
    output.reserve(input.length() * 5);
    for (WCHAR c : input) {
        output.push_back(kHexDigits[(c >> 12) & 15]);
        output.push_back(kHexDigits[(c >> 8) & 15]);
        output.push_back(kHexDigits[(c >> 4) & 15]);
        output.push_back(kHexDigits[c & 15]);
        output.push_back(L' ');
    }
    if (!output.empty() && output.back() == L' ') output.resize(output.length() - 1);
    return output;
}

// ==========================================
// TRAY TWEAKS LOGIC
// ==========================================

using FrameworkElementLoadedEventRevoker = winrt::impl::event_revoker<
    IFrameworkElement,
    &winrt::impl::abi<IFrameworkElement>::type::remove_Loaded>;

std::list<FrameworkElementLoadedEventRevoker> g_autoRevokerList;
winrt::weak_ref<Controls::TextBlock> g_mainStackInnerTextBlock;
int64_t g_mainStackTextChangedToken = 0;
winrt::weak_ref<FrameworkElement> g_bellSystemTrayIconElement;
int64_t g_bellAutomationNameChangedToken = 0;

struct BatteryTextBlockState {
    winrt::weak_ref<Controls::TextBlock> textBlock;
    Media::Brush savedForeground{nullptr};
    int64_t foregroundChangedToken{0};
};
std::vector<BatteryTextBlockState> g_batteryTextBlockStates;

enum class SystemTrayIconIdent {
    kUnknown, kNone, kVolume, kNetwork, kBattery, kMicrophone, kGeolocation,
    kMicrophoneAndGeolocation, kBellEmpty, kBellEmptyDnd, kBellFull, kBellFullDnd,
    kLanguage, kStudioEffects, kRecall,
};

SystemTrayIconIdent IdentifySystemTrayIconFromText(std::wstring_view text) {
    if (text.length() == 0) return SystemTrayIconIdent::kNone;
    if (text.length() != 1) return SystemTrayIconIdent::kUnknown;

    switch (text[0]) {
        case L'\uE74F': case L'\uE992': case L'\uE993': case L'\uE994':
        case L'\uE995': case L'\uEA85': case L'\uEBC5':
            return SystemTrayIconIdent::kVolume;

        case L'\uE709': case L'\uE7F4': case L'\uE839': case L'\uE86C':
        case L'\uE86D': case L'\uE86E': case L'\uE86F': case L'\uE870':
        case L'\uEAA1': case L'\uEAA2': case L'\uEAA3': case L'\uEAA4':
        case L'\uEAA5': case L'\uEAA8': case L'\uEC1E': case L'\uEC3C':
        case L'\uEC3D': case L'\uEC3E': case L'\uEC3F': case L'\uF384':
        case L'\uF8C0': case L'\uF8C1': case L'\uF8C2': case L'\uF8C3':
        case L'\uF8C4': case L'\uF8C5': case L'\uF8C6': case L'\uF8C7':
        case L'\uF8C8': case L'\uF8C9': case L'\uF8CA': case L'\uF8CB':
        case L'\uF8CC':
            return SystemTrayIconIdent::kNetwork;

        case L'\uE3C1': case L'\uE3C2': case L'\uE3C3': case L'\uE3C4':
        case L'\uE3C5': case L'\uE3C6': case L'\uE3C7': case L'\uE3C8':
        case L'\uE3C9': case L'\uE3CA': case L'\uE3CB': case L'\uE408':
        case L'\uE409': case L'\uE40A': case L'\uE40B': case L'\uE40C':
        case L'\uE40D': case L'\uE40E': case L'\uE40F': case L'\uE410':
        case L'\uE411': case L'\uE412': case L'\uE413': case L'\uE414':
        case L'\uE415': case L'\uE416': case L'\uE417': case L'\uE418':
        case L'\uE419': case L'\uE41A': case L'\uE41B': case L'\uE41C':
        case L'\uE41D': case L'\uEBA0': case L'\uEBA1': case L'\uEBA2':
        case L'\uEBA3': case L'\uEBA4': case L'\uEBA5': case L'\uEBA6':
        case L'\uEBA7': case L'\uEBA8': case L'\uEBA9': case L'\uEBAA':
        case L'\uEBAB': case L'\uEBAC': case L'\uEBAD': case L'\uEBAE':
        case L'\uEBAF': case L'\uEBB0': case L'\uEBB1': case L'\uEBB2':
        case L'\uEBB3': case L'\uEBB4': case L'\uEBB5': case L'\uEBB6':
        case L'\uEBB7': case L'\uEBB8': case L'\uEBB9': case L'\uEBBA':
        case L'\uEBBB': case L'\uEBBC': case L'\uEBBD': case L'\uEBBE':
        case L'\uEBBF': case L'\uEBC0': case L'\uEB17': case L'\uEC02':
        case L'\uF1E8':
            return SystemTrayIconIdent::kBattery;

        case L'\uE361': case L'\uE720': case L'\uEC71':
            return SystemTrayIconIdent::kMicrophone;

        case L'\uE37A':
            return SystemTrayIconIdent::kGeolocation;

        case L'\uF47F':
            return SystemTrayIconIdent::kMicrophoneAndGeolocation;

        case L'\uF2A3': return SystemTrayIconIdent::kBellEmpty;
        case L'\uF285': return SystemTrayIconIdent::kBellEmptyDnd;
        case L'\uF2A5': return SystemTrayIconIdent::kBellFull;
        case L'\uF2A8': return SystemTrayIconIdent::kBellFullDnd;

        case L'\uE4D7': case L'\uE4D8': case L'\uE5BF': case L'\uE97E':
        case L'\uE97F': case L'\uE980': case L'\uE982': case L'\uE983':
        case L'\uE986': case L'\uE987': case L'\uE988': case L'\uEB90':
        case L'\uEE41': case L'\uEE42': case L'\uEE43': case L'\uEE44':
        case L'\uEE45': case L'\uEE75': case L'\uEE76':
            return SystemTrayIconIdent::kLanguage;

        case L'\uEABC':
            return SystemTrayIconIdent::kStudioEffects;

        case L'\uEC83': case L'\uEADD': case L'\uEB16': case L'\uEF97': case L'\uF1C6':
            return SystemTrayIconIdent::kRecall;
    }
    return SystemTrayIconIdent::kUnknown;
}

void ApplyMainStackIconViewStyle(FrameworkElement notifyIconViewElement) {
    FrameworkElement child = notifyIconViewElement;
    if (!((child = FindChildByName(child, L"ContainerGrid")) &&
          (child = FindChildByName(child, L"ContentPresenter")) &&
          (child = FindChildByName(child, L"ContentGrid")) &&
          (child = FindChildByClassName(child, L"SystemTray.TextIconContent")))) {
        return;
    }

    FrameworkElement systemTrayTextIconContent = child;
    Controls::TextBlock innerTextBlock = nullptr;
    child = systemTrayTextIconContent;
    if ((child = FindChildByName(child, L"ContainerGrid")) &&
        (child = FindChildByName(child, L"Base")) &&
        (child = FindChildByName(child, L"InnerTextBlock"))) {
        innerTextBlock = child.as<Controls::TextBlock>();
    } else {
        return;
    }

    auto shouldHide = [](Controls::TextBlock tb) {
        auto text = tb.Text();
        auto ident = IdentifySystemTrayIconFromText(text);
        bool hide = false;
        if (!g_unloading) {
            switch (ident) {
                case SystemTrayIconIdent::kMicrophone: hide = g_settings.hideMicrophoneIcon; break;
                case SystemTrayIconIdent::kGeolocation: hide = g_settings.hideGeolocationIcon; break;
                case SystemTrayIconIdent::kMicrophoneAndGeolocation:
                    hide = g_settings.hideMicrophoneIcon && g_settings.hideGeolocationIcon; break;
                case SystemTrayIconIdent::kStudioEffects: hide = g_settings.hideStudioEffectsIcon; break;
                case SystemTrayIconIdent::kRecall: hide = g_settings.hideRecallIcon; break;
                default: break;
            }
        }
        return hide;
    };

    bool hide = shouldHide(innerTextBlock);
    notifyIconViewElement.Visibility(hide ? Visibility::Collapsed : Visibility::Visible);

    if (!g_unloading && !g_mainStackInnerTextBlock.get()) {
        auto notifyWeak = winrt::make_weak(notifyIconViewElement);
        g_mainStackInnerTextBlock = innerTextBlock;
        g_mainStackTextChangedToken = innerTextBlock.RegisterPropertyChangedCallback(
            Controls::TextBlock::TextProperty(),
            [notifyWeak, shouldHide](DependencyObject sender, DependencyProperty) {
                auto tb = sender.try_as<Controls::TextBlock>();
                auto elem = notifyWeak.get();
                if (tb && elem) {
                    elem.Visibility(shouldHide(tb) ? Visibility::Collapsed : Visibility::Visible);
                }
            });
    }
}

void ApplyNonActivatableStackIconViewStyle(FrameworkElement notifyIconViewElement) {
    FrameworkElement child = notifyIconViewElement;
    bool hide = false;
    if ((child = FindChildByName(child, L"ContainerGrid")) &&
        (child = FindChildByName(child, L"ContentPresenter")) &&
        (child = FindChildByName(child, L"ContentGrid"))) {
        child = EnumChildElements(child, [&hide](FrameworkElement c) {
            auto className = winrt::get_class_name(c);
            if (className == L"SystemTray.TextIconContent") {
                FrameworkElement inner = c;
                if ((inner = FindChildByName(inner, L"ContainerGrid")) &&
                    (inner = FindChildByName(inner, L"Base")) &&
                    (inner = FindChildByName(inner, L"InnerTextBlock"))) {
                    auto tb = inner.as<Controls::TextBlock>();
                    auto ident = IdentifySystemTrayIconFromText(tb.Text());
                    if (ident == SystemTrayIconIdent::kLanguage) {
                        hide = g_settings.hideLanguageSupplementaryIcons;
                        return true;
                    }
                }
                return false;
            } else if (className == L"SystemTray.ImageIconContent") {
                hide = g_settings.hideLanguageSupplementaryIcons;
                return true;
            } else if (className == L"SystemTray.LanguageTextIconContent" ||
                       className == L"SystemTray.LanguageImageIconContent") {
                hide = g_settings.hideLanguageBar;
                return true;
            }
            return false;
        });
    }

    if (!child) {
        if (Media::VisualTreeHelper::GetChildrenCount(notifyIconViewElement) == 0) {
            notifyIconViewElement.Visibility(Visibility::Visible);
        }
        return;
    }

    hide = !g_unloading && hide;
    notifyIconViewElement.Visibility(hide ? Visibility::Collapsed : Visibility::Visible);
}

void ApplyBatteryIconGrayscaleStyle(FrameworkElement batteryIconContent) {
    bool grayscale = !g_unloading && g_settings.grayscaleBatteryIcon;
    std::erase_if(g_batteryTextBlockStates, [](const BatteryTextBlockState& s) {
        return !s.textBlock.get();
    });

    if (!grayscale && g_batteryTextBlockStates.empty()) return;

    FrameworkElement grid = batteryIconContent;
    if (!((grid = FindChildByName(grid, L"ContainerGrid")) &&
          (grid = FindChildByClassName(grid, L"Windows.UI.Xaml.Controls.StackPanel")) &&
          (grid = FindChildByClassName(grid, L"Windows.UI.Xaml.Controls.Grid")))) {
        return;
    }

    EnumChildElements(grid, [grayscale](FrameworkElement textChild) {
        auto textBlock = textChild.try_as<Controls::TextBlock>();
        if (!textBlock) return false;

        auto it = std::find_if(g_batteryTextBlockStates.begin(), g_batteryTextBlockStates.end(),
                               [&](const BatteryTextBlockState& s) { return s.textBlock.get() == textBlock; });
        bool managed = (it != g_batteryTextBlockStates.end());

        if (grayscale && !managed) {
            auto localForeground = textBlock.ReadLocalValue(Controls::TextBlock::ForegroundProperty()).try_as<Media::Brush>();
            if (!localForeground) return false;

            BatteryTextBlockState state;
            state.textBlock = textBlock;
            state.savedForeground = localForeground;
            state.foregroundChangedToken = textBlock.RegisterPropertyChangedCallback(
                Controls::TextBlock::ForegroundProperty(),
                [](DependencyObject sender, DependencyProperty) {
                    auto tb = sender.try_as<Controls::TextBlock>();
                    if (!tb) return;
                    auto fg = tb.ReadLocalValue(Controls::TextBlock::ForegroundProperty()).try_as<Media::Brush>();
                    if (!fg) return;
                    for (auto& s : g_batteryTextBlockStates) {
                        if (s.textBlock.get() == tb) {
                            s.savedForeground = fg;
                            break;
                        }
                    }
                    tb.as<DependencyObject>().ClearValue(Controls::TextBlock::ForegroundProperty());
                });
            g_batteryTextBlockStates.push_back(std::move(state));
            textBlock.as<DependencyObject>().ClearValue(Controls::TextBlock::ForegroundProperty());
        } else if (!grayscale && managed) {
            textBlock.UnregisterPropertyChangedCallback(Controls::TextBlock::ForegroundProperty(), it->foregroundChangedToken);
            textBlock.Foreground(it->savedForeground);
            g_batteryTextBlockStates.erase(it);
        }
        return false;
    });
}

void ApplyControlCenterButtonIconStyle(FrameworkElement systemTrayIconElement) {
    FrameworkElement contentGrid = nullptr;
    FrameworkElement child = systemTrayIconElement;
    if ((child = FindChildByName(child, L"ContainerGrid")) &&
        (child = FindChildByName(child, L"ContentGrid"))) {
        contentGrid = child;
    } else {
        return;
    }

    bool hide = false;
    FrameworkElement batteryContent = FindChildByClassName(contentGrid, L"SystemTray.BatteryIconContent");
    if (batteryContent) {
        if (!g_unloading) hide = g_settings.hideBatteryIcon;
        ApplyBatteryIconGrayscaleStyle(batteryContent);
    } else {
        FrameworkElement textContent = FindChildByClassName(contentGrid, L"SystemTray.TextIconContent");
        if (!textContent) return;

        Controls::TextBlock innerTextBlock = nullptr;
        child = textContent;
        if ((child = FindChildByName(child, L"ContainerGrid")) &&
            (child = FindChildByName(child, L"Base")) &&
            (child = FindChildByName(child, L"InnerTextBlock"))) {
            innerTextBlock = child.as<Controls::TextBlock>();
        } else {
            return;
        }

        auto ident = IdentifySystemTrayIconFromText(innerTextBlock.Text());
        if (!g_unloading) {
            switch (ident) {
                case SystemTrayIconIdent::kVolume: hide = g_settings.hideVolumeIcon; break;
                case SystemTrayIconIdent::kNetwork: hide = g_settings.hideNetworkIcon; break;
                case SystemTrayIconIdent::kBattery: hide = g_settings.hideBatteryIcon; break;
                default: break;
            }
        }
        batteryContent = textContent;
    }

    bool hidden = batteryContent.Visibility() == Visibility::Collapsed;
    if (hide == hidden) return;

    batteryContent.Visibility(hide ? Visibility::Collapsed : Visibility::Visible);
    if (auto control = systemTrayIconElement.try_as<Controls::Control>()) {
        control.IsEnabled(!hide);
    }

    FrameworkElement parent = systemTrayIconElement;
    if ((parent = Media::VisualTreeHelper::GetParent(parent).try_as<FrameworkElement>()) &&
        winrt::get_class_name(parent) == L"Windows.UI.Xaml.Controls.ContentPresenter" &&
        (parent = Media::VisualTreeHelper::GetParent(parent).try_as<FrameworkElement>()) &&
        winrt::get_class_name(parent) == L"Windows.UI.Xaml.Controls.StackPanel") {
        bool anyEnabled = false;
        EnumChildElements(parent, [&anyEnabled](FrameworkElement ch) {
            auto ctrl = FindChildByName(ch, L"SystemTrayIcon").try_as<Controls::Control>();
            if (ctrl && ctrl.IsEnabled()) {
                anyEnabled = true;
                return true;
            }
            return false;
        });
        parent.Visibility(anyEnabled ? Visibility::Visible : Visibility::Collapsed);
    }
}

void ApplyBellIconStyle(FrameworkElement systemTrayIconElement);

void ApplyBellIconStyleWithRetry(FrameworkElement systemTrayIconElement, int attempt) {
    if (attempt == 10) return;
    FrameworkElement containerGrid = FindChildByName(systemTrayIconElement, L"ContainerGrid");
    if (!containerGrid) {
        systemTrayIconElement.Dispatcher().TryRunAsync(
            winrt::Windows::UI::Core::CoreDispatcherPriority::Low,
            [systemTrayIconElement, attempt]() {
                ApplyBellIconStyleWithRetry(systemTrayIconElement, attempt + 1);
            });
        return;
    }
    ApplyBellIconStyle(systemTrayIconElement);
}

void ApplyBellIconStyle(FrameworkElement systemTrayIconElement) {
    FrameworkElement containerGrid = FindChildByName(systemTrayIconElement, L"ContainerGrid");
    if (!containerGrid) return;

    bool hasContentPresenterForMissingClock = true;
    FrameworkElement child = FindChildByName(containerGrid, L"ContentPresenter");
    if (!child) {
        hasContentPresenterForMissingClock = false;
        child = containerGrid;
    }

    FrameworkElement systemTrayTextIconContent = nullptr;
    if ((child = FindChildByName(child, L"ContentGrid")) &&
        (child = FindChildByClassName(child, L"SystemTray.TextIconContent"))) {
        systemTrayTextIconContent = child;
    } else {
        return;
    }

    auto contentPresenter = Media::VisualTreeHelper::GetParent(systemTrayIconElement).try_as<FrameworkElement>();
    bool hide = false;

    if (!g_unloading) {
        if (g_settings.hideBellIcon == HideBellIcon::always) {
            hide = true;
        } else if (g_settings.hideBellIcon == HideBellIcon::whenInactive ||
                   g_settings.hideBellIcon == HideBellIcon::whenInactiveAndNoDnd) {
            Controls::TextBlock innerTextBlock = nullptr;
            child = systemTrayTextIconContent;
            if ((child = FindChildByName(child, L"ContainerGrid")) &&
                (child = FindChildByName(child, L"Base")) &&
                (child = FindChildByName(child, L"InnerTextBlock"))) {
                innerTextBlock = child.as<Controls::TextBlock>();
            } else {
                return;
            }

            auto ident = IdentifySystemTrayIconFromText(innerTextBlock.Text());
            if (ident == SystemTrayIconIdent::kBellEmpty) {
                hide = true;
            } else if (ident == SystemTrayIconIdent::kBellEmptyDnd) {
                hide = (g_settings.hideBellIcon != HideBellIcon::whenInactiveAndNoDnd);
            }

            if (!g_bellSystemTrayIconElement.get()) {
                g_bellSystemTrayIconElement = systemTrayIconElement;
                g_bellAutomationNameChangedToken = systemTrayIconElement.RegisterPropertyChangedCallback(
                    Automation::AutomationProperties::NameProperty(),
                    [](DependencyObject sender, DependencyProperty) {
                        auto elem = sender.try_as<FrameworkElement>();
                        if (elem) ApplyBellIconStyleWithRetry(elem, 0);
                    });
            }
        }
    }

    systemTrayTextIconContent.Visibility(hide ? Visibility::Collapsed : Visibility::Visible);
    if (contentPresenter) {
        if (hide && hasContentPresenterForMissingClock) {
            contentPresenter.MaxWidth(0);
        } else {
            contentPresenter.ClearValue(FrameworkElement::MaxWidthProperty());
        }
    }
}

void ApplyShowDesktopStyle(FrameworkElement systemTrayIconElement) {
    auto showDesktopStack = GetParentElementByName(systemTrayIconElement, L"ShowDesktopStack");
    if (!showDesktopStack) return;

    if (g_unloading) {
        systemTrayIconElement.as<DependencyObject>().ClearValue(FrameworkElement::MinWidthProperty());
        systemTrayIconElement.as<DependencyObject>().ClearValue(FrameworkElement::MaxWidthProperty());
        showDesktopStack.as<DependencyObject>().ClearValue(FrameworkElement::MinWidthProperty());
        showDesktopStack.as<DependencyObject>().ClearValue(FrameworkElement::MaxWidthProperty());
    } else {
        int width = g_settings.showDesktopButtonWidth;
        systemTrayIconElement.MinWidth(width);
        systemTrayIconElement.MaxWidth(width);
        showDesktopStack.MinWidth(width);
        showDesktopStack.MaxWidth(width);
    }
}

template <typename F>
bool IterateItemsPresenterStack(FrameworkElement container, F callback) {
    FrameworkElement stackPanel = container;
    if ((stackPanel = FindChildByName(stackPanel, L"Content")) &&
        (stackPanel = FindChildByName(stackPanel, L"IconStack")) &&
        (stackPanel = FindChildByClassName(stackPanel, L"Windows.UI.Xaml.Controls.ItemsPresenter")) &&
        (stackPanel = FindChildByClassName(stackPanel, L"Windows.UI.Xaml.Controls.StackPanel"))) {
        EnumChildElements(stackPanel, [&callback](FrameworkElement child) {
            auto iconElem = FindChildByName(child, L"SystemTrayIcon");
            if (iconElem) callback(iconElem);
            return false;
        });
        return true;
    }
    return false;
}

bool ApplyTrayStylesVisualTree(XamlRoot xamlRoot) {
    FrameworkElement systemTrayFrameGrid = xamlRoot.Content().try_as<FrameworkElement>();
    if (systemTrayFrameGrid &&
        (systemTrayFrameGrid = FindChildByClassName(systemTrayFrameGrid, L"SystemTray.SystemTrayFrame")) &&
        (systemTrayFrameGrid = FindChildByName(systemTrayFrameGrid, L"SystemTrayFrameGrid"))) {
    } else {
        return false;
    }

    bool success = false;
    if (auto mainStack = FindChildByName(systemTrayFrameGrid, L"MainStack")) {
        success |= IterateItemsPresenterStack(mainStack, ApplyMainStackIconViewStyle);
    }
    if (auto nonAct = FindChildByName(systemTrayFrameGrid, L"NonActivatableStack")) {
        success |= IterateItemsPresenterStack(nonAct, ApplyNonActivatableStackIconViewStyle);
    }
    if (auto ctrlCenter = FindChildByName(systemTrayFrameGrid, L"ControlCenterButton")) {
        FrameworkElement sp = ctrlCenter;
        if ((sp = FindChildByClassName(sp, L"Windows.UI.Xaml.Controls.Grid")) &&
            (sp = FindChildByName(sp, L"ContentPresenter")) &&
            (sp = FindChildByClassName(sp, L"Windows.UI.Xaml.Controls.ItemsPresenter")) &&
            (sp = FindChildByClassName(sp, L"Windows.UI.Xaml.Controls.StackPanel"))) {
            EnumChildElements(sp, [](FrameworkElement child) {
                if (auto iconElem = FindChildByName(child, L"SystemTrayIcon")) {
                    ApplyControlCenterButtonIconStyle(iconElem);
                }
                return false;
            });
            success = true;
        }
    }
    if (auto notifCenter = FindChildByName(systemTrayFrameGrid, L"NotificationCenterButton")) {
        FrameworkElement sp = notifCenter;
        if ((sp = FindChildByClassName(sp, L"Windows.UI.Xaml.Controls.Grid")) &&
            (sp = FindChildByName(sp, L"ContentPresenter")) &&
            (sp = FindChildByClassName(sp, L"Windows.UI.Xaml.Controls.ItemsPresenter")) &&
            (sp = FindChildByClassName(sp, L"Windows.UI.Xaml.Controls.StackPanel"))) {
            EnumChildElements(sp, [](FrameworkElement child) {
                if (auto iconElem = FindChildByName(child, L"SystemTrayIcon")) {
                    ApplyBellIconStyle(iconElem);
                }
                return false;
            });
            success = true;
        }
    }
    if (auto showDesktop = FindChildByName(systemTrayFrameGrid, L"ShowDesktopStack")) {
        success |= IterateItemsPresenterStack(showDesktop, ApplyShowDesktopStyle);
    }
    return success;
}

using IconView_IconView_t = void*(WINAPI*)(void* pThis);
IconView_IconView_t IconView_IconView_Original;
void* WINAPI IconView_IconView_Hook(void* pThis) {
    void* ret = IconView_IconView_Original(pThis);
    FrameworkElement iconView = nullptr;
    ((IUnknown**)pThis)[1]->QueryInterface(winrt::guid_of<FrameworkElement>(), winrt::put_abi(iconView));
    if (!iconView) return ret;

    g_autoRevokerList.emplace_back();
    auto autoRevokerIt = g_autoRevokerList.end();
    --autoRevokerIt;

    *autoRevokerIt = iconView.Loaded(
        winrt::auto_revoke_t{},
        [autoRevokerIt](winrt::Windows::Foundation::IInspectable const& sender, RoutedEventArgs const&) {
            g_autoRevokerList.erase(autoRevokerIt);
            auto icon = sender.try_as<FrameworkElement>();
            if (!icon || winrt::get_class_name(icon) != L"SystemTray.IconView" || icon.Name() != L"SystemTrayIcon") {
                return;
            }

            if (IsChildOfElementByName(icon, L"MainStack")) {
                ApplyMainStackIconViewStyle(icon);
            } else if (IsChildOfElementByName(icon, L"NonActivatableStack")) {
                ApplyNonActivatableStackIconViewStyle(icon);
            } else if (IsChildOfElementByName(icon, L"ControlCenterButton")) {
                ApplyControlCenterButtonIconStyle(icon);
            } else if (IsChildOfElementByName(icon, L"NotificationCenterButton")) {
                ApplyBellIconStyle(icon);
            } else if (IsChildOfElementByName(icon, L"ShowDesktopStack")) {
                ApplyShowDesktopStyle(icon);
            }
        });
    return ret;
}

void* CTaskBand_ITaskListWndSite_vftable;
using CTaskBand_GetTaskbarHost_t = void*(WINAPI*)(void* pThis, void** result);
CTaskBand_GetTaskbarHost_t CTaskBand_GetTaskbarHost_Original;
void* TaskbarHost_FrameHeight_Original;
using std__Ref_count_base__Decref_t = void(WINAPI*)(void* pThis);
std__Ref_count_base__Decref_t std__Ref_count_base__Decref_Original;

XamlRoot GetTaskbarXamlRoot(HWND hTaskbarWnd) {
    HWND hTaskSwWnd = (HWND)GetProp(hTaskbarWnd, L"TaskbandHWND");
    if (!hTaskSwWnd) return nullptr;

    void* taskBand = (void*)GetWindowLongPtr(hTaskSwWnd, 0);
    void* taskBandSite = taskBand;
    for (int i = 0; *(void**)taskBandSite != CTaskBand_ITaskListWndSite_vftable; i++) {
        if (i == 20) return nullptr;
        taskBandSite = (void**)taskBandSite + 1;
    }

    void* hostSharedPtr[2]{};
    CTaskBand_GetTaskbarHost_Original(taskBandSite, hostSharedPtr);
    if (!hostSharedPtr[0] && !hostSharedPtr[1]) return nullptr;

    size_t offset = 0x48;
#if defined(_M_X64)
    const BYTE* b = (const BYTE*)TaskbarHost_FrameHeight_Original;
    if (b && b[0] == 0x48 && b[1] == 0x83 && b[2] == 0xEC && b[4] == 0x48 &&
        b[5] == 0x83 && b[6] == 0xC1 && b[7] <= 0x7F) {
        offset = b[7];
    }
#endif

    auto* unk = *(IUnknown**)((BYTE*)hostSharedPtr[0] + offset);
    FrameworkElement taskbarElem = nullptr;
    if (unk) unk->QueryInterface(winrt::guid_of<FrameworkElement>(), winrt::put_abi(taskbarElem));
    auto result = taskbarElem ? taskbarElem.XamlRoot() : nullptr;
    std__Ref_count_base__Decref_Original(hostSharedPtr[1]);
    return result;
}

using RunFromWindowThreadProc_t = void(WINAPI*)(void* parameter);
bool RunFromWindowThread(HWND hWnd, RunFromWindowThreadProc_t proc, void* procParam) {
    static const UINT msg = RegisterWindowMessage(L"Windhawk_RunFromWindowThread_" WH_MOD_ID);
    struct PARAM { RunFromWindowThreadProc_t proc; void* procParam; };

    DWORD tid = GetWindowThreadProcessId(hWnd, nullptr);
    if (tid == 0) return false;
    if (tid == GetCurrentThreadId()) {
        proc(procParam);
        return true;
    }

    HHOOK hook = SetWindowsHookEx(
        WH_CALLWNDPROC,
        [](int nCode, WPARAM wParam, LPARAM lParam) -> LRESULT {
            if (nCode == HC_ACTION) {
                const CWPSTRUCT* cwp = (const CWPSTRUCT*)lParam;
                if (cwp->message == msg) {
                    PARAM* p = (PARAM*)cwp->lParam;
                    p->proc(p->procParam);
                }
            }
            return CallNextHookEx(nullptr, nCode, wParam, lParam);
        },
        nullptr, tid);
    if (!hook) return false;

    PARAM p{proc, procParam};
    SendMessage(hWnd, msg, 0, (LPARAM)&p);
    UnhookWindowsHookEx(hook);
    return true;
}

bool HookTaskbarDllSymbols() {
    HMODULE module = LoadLibraryEx(L"taskbar.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!module) return false;

    WindhawkUtils::SYMBOL_HOOK hooks[] = {
        {{LR"(const CTaskBand::`vftable'{for `ITaskListWndSite'})"}, &CTaskBand_ITaskListWndSite_vftable},
        {{LR"(public: virtual class std::shared_ptr<class TaskbarHost> __cdecl CTaskBand::GetTaskbarHost(void)const )"}, &CTaskBand_GetTaskbarHost_Original},
        {{LR"(public: int __cdecl TaskbarHost::FrameHeight(void)const )"}, &TaskbarHost_FrameHeight_Original},
        {{LR"(public: void __cdecl std::_Ref_count_base::_Decref(void))"}, &std__Ref_count_base__Decref_Original},
    };
    return HookSymbols(module, hooks, ARRAYSIZE(hooks));
}

// ==========================================
// CLOCK & MONITORING LOGIC
// ==========================================

bool g_formattingInitialized;
DWORD g_formatIndex;
SYSTEMTIME g_formatTime;
std::mutex g_formatLineMutex;

template <size_t N>
struct FormattedString {
    DWORD formatIndex;
    WCHAR buffer[N];
};

FormattedString<FORMATTED_BUFFER_SIZE> g_timeFormatted;
std::vector<std::wstring> g_timeFormattedExtra;
std::vector<FormattedString<FORMATTED_BUFFER_SIZE>> g_timeFormattedTz;
FormattedString<FORMATTED_BUFFER_SIZE> g_dateFormatted;
std::vector<std::wstring> g_dateFormattedExtra;
std::vector<FormattedString<FORMATTED_BUFFER_SIZE>> g_dateFormattedTz;
FormattedString<FORMATTED_BUFFER_SIZE> g_weekdayFormatted;
std::vector<FormattedString<FORMATTED_BUFFER_SIZE>> g_weekdayFormattedTz;
FormattedString<INTEGER_BUFFER_SIZE> g_weekdayNumFormatted;
FormattedString<INTEGER_BUFFER_SIZE> g_weeknumFormatted;
FormattedString<INTEGER_BUFFER_SIZE> g_weeknumIsoFormatted;
FormattedString<INTEGER_BUFFER_SIZE> g_dayOfYearFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_timezoneFormatted;

FormattedString<FORMATTED_BUFFER_SIZE> g_uploadSpeedFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_downloadSpeedFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_totalSpeedFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_diskReadSpeedFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_diskWriteSpeedFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_diskTotalSpeedFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_cpuFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_ramFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_ramUsedFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_ramTotalFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_ramCommittedFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_ramCommittedUsedFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_ramCommittedTotalFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_gpuFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_vramFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_vramUsedFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_vramTotalFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_vramSharedFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_vramSharedUsedFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_vramSharedTotalFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_cpuTempFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_cpuTempFFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_batteryFormatted;
std::atomic<bool> g_isBatteryLow{false};
FormattedString<FORMATTED_BUFFER_SIZE> g_batteryTimeFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_powerFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_volumeFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_micFormatted;

FormattedString<FORMATTED_BUFFER_SIZE> g_mediaTitleFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_mediaArtistFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_mediaAlbumFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_mediaStatusFormatted;
FormattedString<FORMATTED_BUFFER_SIZE> g_mediaInfoFormatted;

winrt::Windows::Media::Control::GlobalSystemMediaTransportControlsSessionManager g_mediaSessionManager{nullptr};
winrt::Windows::Media::Control::GlobalSystemMediaTransportControlsSession g_mediaCurrentSession{nullptr};
std::mutex g_mediaMutex;
std::atomic<bool> g_mediaDataDirty{true};
winrt::event_token g_mediaSessionsChangedToken;
winrt::event_token g_mediaPropertiesChangedToken;
winrt::event_token g_mediaPlaybackChangedToken;
bool g_mediaActive = false;
bool g_inMediaInfoFormat = false;

std::vector<std::optional<DYNAMIC_TIME_ZONE_INFORMATION>> g_timeZoneInformation;
std::atomic<HANDLE> g_webContentUpdateThread{nullptr};
HANDLE g_webContentUpdateRefreshEvent = nullptr;
HANDLE g_webContentUpdateStopEvent = nullptr;
std::mutex g_webContentMutex;
std::atomic<bool> g_webContentLoaded{false};
std::vector<std::optional<std::wstring>> g_webContentStrings;
std::vector<std::optional<std::wstring>> g_webContentStringsFull;
std::optional<std::wstring> g_webContentWeather;
WCHAR g_webContent[FORMATTED_BUFFER_SIZE];
WCHAR g_webContentFull[FORMATTED_BUFFER_SIZE];

struct ClockElementStyleData {
    winrt::weak_ref<FrameworkElement> dateTimeIconContentElement;
    DWORD styleIndex;
    std::optional<int64_t> dateVisibilityPropertyChangedToken;
    std::optional<int64_t> timeVisibilityPropertyChangedToken;
};

std::atomic<bool> g_clockElementStyleEnabled{false};
std::atomic<DWORD> g_clockElementStyleIndex{0};
std::vector<ClockElementStyleData> g_clockElementStyleData;

using GetDpiForWindow_t = UINT(WINAPI*)(HWND hwnd);
GetDpiForWindow_t pGetDpiForWindow;
using SystemTimeToTzSpecificLocalTimeEx_t = BOOL(WINAPI*)(const DYNAMIC_TIME_ZONE_INFORMATION*, const SYSTEMTIME*, LPSYSTEMTIME);
SystemTimeToTzSpecificLocalTimeEx_t pSystemTimeToTzSpecificLocalTimeEx;
using EnumDynamicTimeZoneInformation_t = DWORD(WINAPI*)(const DWORD, PDYNAMIC_TIME_ZONE_INFORMATION);
EnumDynamicTimeZoneInformation_t pEnumDynamicTimeZoneInformation;

using GetLocalTime_t = decltype(&GetLocalTime);
GetLocalTime_t GetLocalTime_Original;
using GetTimeFormatEx_t = decltype(&GetTimeFormatEx);
GetTimeFormatEx_t GetTimeFormatEx_Original;
using GetDateFormatEx_t = decltype(&GetDateFormatEx);
GetDateFormatEx_t GetDateFormatEx_Original;
using GetDateFormatW_t = decltype(&GetDateFormatW);
GetDateFormatW_t GetDateFormatW_Original;
using SendMessageW_t = decltype(&SendMessageW);
SendMessageW_t SendMessageW_Original;

std::optional<std::wstring> GetUrlContent(PCWSTR lpUrl, bool failIfNot200 = true) {
    HINTERNET hOpenHandle = InternetOpen(L"WindhawkMod", INTERNET_OPEN_TYPE_PRECONFIG, nullptr, nullptr, 0);
    if (!hOpenHandle) return std::nullopt;

    HINTERNET hUrlHandle = InternetOpenUrl(hOpenHandle, lpUrl, nullptr, 0,
        INTERNET_FLAG_NO_AUTH | INTERNET_FLAG_NO_CACHE_WRITE | INTERNET_FLAG_NO_COOKIES |
        INTERNET_FLAG_NO_UI | INTERNET_FLAG_PRAGMA_NOCACHE | INTERNET_FLAG_RELOAD, 0);
    if (!hUrlHandle) {
        InternetCloseHandle(hOpenHandle);
        return std::nullopt;
    }

    if (failIfNot200) {
        DWORD dwStatusCode = 0, dwStatusCodeSize = sizeof(dwStatusCode);
        if (!HttpQueryInfo(hUrlHandle, HTTP_QUERY_STATUS_CODE | HTTP_QUERY_FLAG_NUMBER,
                           &dwStatusCode, &dwStatusCodeSize, nullptr) || dwStatusCode != 200) {
            InternetCloseHandle(hUrlHandle);
            InternetCloseHandle(hOpenHandle);
            return std::nullopt;
        }
    }

    LPBYTE pUrlContent = (LPBYTE)HeapAlloc(GetProcessHeap(), 0, 0x400);
    if (!pUrlContent) {
        InternetCloseHandle(hUrlHandle);
        InternetCloseHandle(hOpenHandle);
        return std::nullopt;
    }

    DWORD dwRead, dwLength = 0;
    while (InternetReadFile(hUrlHandle, pUrlContent + dwLength, 0x400, &dwRead) && dwRead != 0) {
        dwLength += dwRead;
        LPBYTE pNew = (LPBYTE)HeapReAlloc(GetProcessHeap(), 0, pUrlContent, dwLength + 0x400);
        if (!pNew) {
            HeapFree(GetProcessHeap(), 0, pUrlContent);
            InternetCloseHandle(hUrlHandle);
            InternetCloseHandle(hOpenHandle);
            return std::nullopt;
        }
        pUrlContent = pNew;
    }

    InternetCloseHandle(hUrlHandle);
    InternetCloseHandle(hOpenHandle);

    int charsNeeded = MultiByteToWideChar(CP_UTF8, 0, (PCSTR)pUrlContent, dwLength, nullptr, 0);
    std::wstring unicodeContent(charsNeeded, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, (PCSTR)pUrlContent, dwLength, unicodeContent.data(), unicodeContent.size());
    HeapFree(GetProcessHeap(), 0, pUrlContent);
    return unicodeContent;
}

std::wstring ReplaceAll(std::wstring_view source, std::wstring_view from, std::wstring_view to) {
    std::wstring newString;
    size_t lastPos = 0, findPos;
    while ((findPos = source.find(from, lastPos)) != source.npos) {
        newString.append(source, lastPos, findPos - lastPos);
        newString += to;
        lastPos = findPos + from.length();
    }
    newString += source.substr(lastPos);
    return newString;
}

std::wstring_view TrimStringView(std::wstring_view s) {
    s.remove_prefix(std::min(s.find_first_not_of(L" \t\r\v\n"), s.size()));
    s.remove_suffix(std::min(s.size() - s.find_last_not_of(L" \t\r\v\n") - 1, s.size()));
    return s;
}

std::vector<std::wstring_view> SplitStringView(std::wstring_view s, std::wstring_view delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::wstring_view token;
    std::vector<std::wstring_view> res;
    while ((pos_end = s.find(delimiter, pos_start)) != std::wstring_view::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }
    res.push_back(s.substr(pos_start));
    return res;
}

int StringCopyTruncated(PWSTR dest, size_t destSize, PCWSTR src, bool* truncated) {
    if (destSize == 0) {
        *truncated = *src;
        return 0;
    }
    size_t i;
    for (i = 0; i < destSize - 1 && *src; i++) *dest++ = *src++;
    *dest = L'\0';
    *truncated = *src;
    return i;
}

int StringCopyTruncatedWithEllipsis(PWSTR dest, size_t destSize, PCWSTR src) {
    if (destSize == 0) return 0;
    bool truncated = false;
    size_t i = StringCopyTruncated(dest, destSize, src, &truncated);
    if (truncated && destSize >= 4) {
        dest[destSize - 4] = L'.';
        dest[destSize - 3] = L'.';
        dest[destSize - 2] = L'.';
        dest[destSize - 1] = L'\0';
    }
    return i;
}

std::wstring ExtractWebContent(std::wstring_view webContent, PCWSTR blockStart, PCWSTR startStr, PCWSTR endStr) {
    auto block = webContent.find(blockStart);
    if (block == webContent.npos) return {};
    auto start = webContent.find(startStr, block);
    if (start == webContent.npos) return {};
    start += wcslen(startStr);
    auto end = *endStr ? webContent.find(endStr, start) : webContent.length();
    if (end == webContent.npos) return {};
    return std::wstring(webContent.substr(start, end - start));
}

std::wstring ExtractTextFromHtml(std::wstring html) {
    winrt::com_ptr<IHTMLDocument2> doc;
    winrt::check_hresult(CoCreateInstance(CLSID_HTMLDocument, nullptr, CLSCTX_INPROC_SERVER, IID_IHTMLDocument2, doc.put_void()));
    _bstr_t htmlBstr(SysAllocStringLen(html.data(), static_cast<UINT>(html.length())), false);
    SAFEARRAY* psa = SafeArrayCreateVector(VT_VARIANT, 0, 1);
    VARIANT* pva;
    if (SUCCEEDED(SafeArrayAccessData(psa, reinterpret_cast<void**>(&pva)))) {
        pva->vt = VT_BSTR;
        pva->bstrVal = htmlBstr.Detach();
        SafeArrayUnaccessData(psa);
    }
    doc->write(psa);
    SafeArrayDestroy(psa);
    winrt::com_ptr<IHTMLElement> body;
    doc->get_body(body.put());
    if (!body) return {};
    _bstr_t text;
    body->get_innerText(text.GetAddress());
    return std::wstring(text, text.length());
}

std::wstring ExtractTextFromXml(std::wstring xml) {
    xml = L"<root>" + xml + L"</root>";
    winrt::Windows::Data::Xml::Dom::XmlDocument xmlDoc;
    xmlDoc.LoadXml(winrt::hstring(xml));
    return std::wstring(xmlDoc.InnerText());
}

bool IsStrInDateTimePatternSettings(PCWSTR str) {
    if (wcsstr(g_settings.topLine, str) || wcsstr(g_settings.bottomLine, str) ||
        wcsstr(g_settings.middleLine, str) || wcsstr(g_settings.tooltipLine, str)) {
        return true;
    }
    if (wcsstr(g_settings.topLine, L"%media_info%") || wcsstr(g_settings.bottomLine, L"%media_info%") ||
        wcsstr(g_settings.middleLine, L"%media_info%") || wcsstr(g_settings.tooltipLine, L"%media_info%")) {
        if (wcsstr(g_settings.mediaPlayer.mediaInfoFormat.get(), str) ||
            wcsstr(g_settings.mediaPlayer.noMediaText.get(), str)) {
            return true;
        }
    }
    return false;
}

std::wstring EscapeUrlComponent(PCWSTR input, DWORD flags = URL_ESCAPE_ASCII_URI_COMPONENT | URL_ESCAPE_AS_UTF8) {
    WCHAR outStack[256];
    DWORD needed = ARRAYSIZE(outStack);
    if (SUCCEEDED(UrlEscape(input, outStack, &needed, flags))) return outStack;
    if (needed < 1) return {};
    std::wstring out(needed - 1, L'\0');
    if (FAILED(UrlEscape(input, &out[0], &needed, flags))) return {};
    return out;
}

bool UpdateWeatherWebContent() {
    std::wstring format = g_settings.webContentWeatherFormat.get();
    if (format.empty()) format = L"%c \U0001F321\uFE0F%t \U0001F32C\uFE0F%w";
    format = ReplaceAll(format, L"%c", L"%c\uE000");

    std::wstring weatherUrl = L"https://wttr.in/" + EscapeUrlComponent(g_settings.webContentWeatherLocation) + L'?';
    switch (g_settings.webContentWeatherUnits) {
        case WebContentWeatherUnits::uscs: weatherUrl += L"u&"; break;
        case WebContentWeatherUnits::metric: weatherUrl += L"m&"; break;
        case WebContentWeatherUnits::metricMsWind: weatherUrl += L"M&"; break;
        default: break;
    }
    weatherUrl += L"format=" + EscapeUrlComponent(format.c_str());

    auto urlContent = GetUrlContent(weatherUrl.c_str());
    if (!urlContent || urlContent->empty() || *urlContent == L"This query is already being processed") return false;

    std::wstring weatherContent;
    size_t lastPos = 0, findPos;
    while ((findPos = urlContent->find(L'\uE000', lastPos)) != urlContent->npos) {
        size_t lastPosCount = findPos - lastPos;
        while (lastPosCount > 0 && urlContent->at(lastPos + lastPosCount - 1) == L' ') lastPosCount--;
        weatherContent.append(*urlContent, lastPos, lastPosCount);
        lastPos = findPos + 1;
    }
    weatherContent += urlContent->substr(lastPos);

    std::lock_guard<std::mutex> guard(g_webContentMutex);
    g_webContentWeather = weatherContent;
    return true;
}

void UpdateWebContent() {
    int failed = 0;
    std::wstring lastUrl;
    std::optional<std::wstring> urlContent;

    if (g_settings.webContentsUrl && g_settings.webContentsBlockStart &&
        g_settings.webContentsStart && g_settings.webContentsEnd) {
        lastUrl = g_settings.webContentsUrl;
        urlContent = GetUrlContent(g_settings.webContentsUrl, false);
        if (urlContent) {
            std::wstring extracted = ExtractWebContent(*urlContent, g_settings.webContentsBlockStart,
                                                       g_settings.webContentsStart, g_settings.webContentsEnd);
            std::lock_guard<std::mutex> guard(g_webContentMutex);
            int maxLen = ARRAYSIZE(g_webContent) - 1;
            if (g_settings.webContentsMaxLength > 0 && g_settings.webContentsMaxLength < maxLen) {
                maxLen = g_settings.webContentsMaxLength;
            }
            StringCopyTruncatedWithEllipsis(g_webContent, maxLen + 1, extracted.c_str());
            StringCopyTruncatedWithEllipsis(g_webContentFull, ARRAYSIZE(g_webContentFull), extracted.c_str());
        } else {
            failed++;
        }
    }

    for (size_t i = 0; i < g_settings.webContentsItems.size(); i++) {
        WCHAR p1[32], p2[32];
        swprintf_s(p1, L"%%web%zu%%", i + 1);
        swprintf_s(p2, L"%%web%zu_full%%", i + 1);
        if (!IsStrInDateTimePatternSettings(p1) && !IsStrInDateTimePatternSettings(p2)) continue;

        const auto& item = g_settings.webContentsItems[i];
        if (item.url.get() != lastUrl) {
            lastUrl = item.url;
            urlContent = GetUrlContent(item.url, false);
        }
        if (!urlContent) {
            failed++;
            continue;
        }

        std::wstring extracted = ExtractWebContent(*urlContent, item.blockStart, item.start, item.end);
        try {
            switch (item.contentMode) {
                case ContentMode::html: extracted = ExtractTextFromHtml(extracted); break;
                case ContentMode::xml: extracted = ExtractTextFromXml(extracted); break;
                case ContentMode::xmlHtml: extracted = ExtractTextFromHtml(ExtractTextFromXml(extracted)); break;
                default: break;
            }
        } catch (...) {}

        for (const auto& [s, r] : item.searchReplace) {
            try { extracted = std::regex_replace(extracted, s, r); } catch (...) {}
        }

        std::lock_guard<std::mutex> guard(g_webContentMutex);
        if (item.maxLength <= 0 || extracted.length() <= (size_t)item.maxLength) {
            g_webContentStrings[i] = extracted;
        } else {
            std::wstring truncated(extracted.begin(), extracted.begin() + item.maxLength);
            if (truncated.length() >= 3) {
                truncated[truncated.length() - 1] = L'.';
                truncated[truncated.length() - 2] = L'.';
                truncated[truncated.length() - 3] = L'.';
            }
            g_webContentStrings[i] = std::move(truncated);
        }
        g_webContentStringsFull[i] = std::move(extracted);
    }

    if (IsStrInDateTimePatternSettings(L"%weather%") && !UpdateWeatherWebContent()) failed++;
    if (failed == 0) g_webContentLoaded = true;
}

DWORD WINAPI WebContentUpdateThread(LPVOID) {
    constexpr DWORD kQuickRetry = 30;
    HANDLE handles[] = {g_webContentUpdateStopEvent, g_webContentUpdateRefreshEvent};

    while (true) {
        UpdateWebContent();
        DWORD seconds = std::max(g_settings.webContentsUpdateInterval, 1) * 60;
        if (!g_webContentLoaded && seconds > kQuickRetry) seconds = kQuickRetry;

        DWORD dwWaitResult = WaitForMultipleObjects(ARRAYSIZE(handles), handles, FALSE, seconds * 1000);
        if (dwWaitResult == WAIT_FAILED || dwWaitResult == WAIT_OBJECT_0) break;
    }
    return 0;
}

void WebContentUpdateThreadInit() {
    std::lock_guard<std::mutex> guard(g_webContentMutex);
    g_webContentStrings.resize(g_settings.webContentsItems.size());
    g_webContentStringsFull.resize(g_settings.webContentsItems.size());
    if (IsStrInDateTimePatternSettings(L"%web") || IsStrInDateTimePatternSettings(L"%weather%")) {
        g_webContentUpdateRefreshEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        g_webContentUpdateStopEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
        g_webContentUpdateThread = CreateThread(nullptr, 0, WebContentUpdateThread, nullptr, 0, nullptr);
    }
}

void WebContentUpdateThreadUninit() {
    HANDLE thread, stopEvt, refEvt;
    {
        std::lock_guard<std::mutex> guard(g_webContentMutex);
        thread = g_webContentUpdateThread;
        stopEvt = g_webContentUpdateStopEvent;
        refEvt = g_webContentUpdateRefreshEvent;
        g_webContentUpdateThread = nullptr;
        g_webContentUpdateStopEvent = nullptr;
        g_webContentUpdateRefreshEvent = nullptr;
    }
    if (thread) {
        SetEvent(stopEvt);
        WaitForSingleObject(thread, INFINITE);
        CloseHandle(thread);
        CloseHandle(refEvt);
        CloseHandle(stopEvt);
    }
    std::lock_guard<std::mutex> guard(g_webContentMutex);
    g_webContentLoaded = false;
    *g_webContent = L'\0';
    *g_webContentFull = L'\0';
    g_webContentStrings.clear();
    g_webContentStringsFull.clear();
    g_webContentWeather.reset();
}

std::optional<DYNAMIC_TIME_ZONE_INFORMATION> GetTimeZoneInformation(PCWSTR timeZone) {
    if (!pEnumDynamicTimeZoneInformation) return std::nullopt;
    DWORD i = 0, res;
    do {
        DYNAMIC_TIME_ZONE_INFORMATION tz;
        res = pEnumDynamicTimeZoneInformation(i++, &tz);
        if (res == ERROR_SUCCESS && _wcsicmp(tz.TimeZoneKeyName, timeZone) == 0) return tz;
    } while (res != ERROR_NO_MORE_ITEMS);
    return std::nullopt;
}

DWORD GetStartDayOfWeek(const SYSTEMTIME* time) {
    DWORD startDayOfWeek;
    GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT, LOCALE_IFIRSTDAYOFWEEK | LOCALE_RETURN_NUMBER,
                    (PWSTR)&startDayOfWeek, sizeof(startDayOfWeek) / sizeof(WCHAR));
    return (startDayOfWeek + 1) % 7;
}

int CalculateWeeknum(const SYSTEMTIME* time, DWORD startDayOfWeek) {
    SYSTEMTIME secondWeek{.wYear = time->wYear, .wMonth = 1, .wDay = 1};
    FILETIME fileTime;
    SystemTimeToFileTime(&secondWeek, &fileTime);
    FileTimeToSystemTime(&fileTime, &secondWeek);
    do {
        secondWeek.wDay++;
        secondWeek.wDayOfWeek = (secondWeek.wDayOfWeek + 1) % 7;
    } while (secondWeek.wDayOfWeek != startDayOfWeek);

    FILETIME ftTarget, ftSecond;
    SystemTimeToFileTime(time, &ftTarget);
    SystemTimeToFileTime(&secondWeek, &ftSecond);
    ULARGE_INTEGER uTarget{.LowPart = ftTarget.dwLowDateTime, .HighPart = ftTarget.dwHighDateTime};
    ULARGE_INTEGER uSecond{.LowPart = ftSecond.dwLowDateTime, .HighPart = ftSecond.dwHighDateTime};

    int weeknum = 1;
    if (uTarget.QuadPart >= uSecond.QuadPart) {
        weeknum += 1 + (uTarget.QuadPart - uSecond.QuadPart) / (10000000ULL * 60 * 60 * 24 * 7);
    }
    return weeknum;
}

int CalculateWeeknumIso(const SYSTEMTIME* time) {
    const int year = time->wYear, month = time->wMonth, day = time->wDay;
    const bool leapYear = ((year % 4) == 0 && (year % 100) != 0) || (year % 400) == 0;
    const bool leapYear_1 = (((year - 1) % 4) == 0 && ((year - 1) % 100) != 0) || ((year - 1) % 400) == 0;

    static const int MAP[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    int d = day + MAP[month - 1];
    if (leapYear && month > 2) d++;

    int YY = (year - 1) % 100, C = (year - 1) - YY, G = YY + YY / 4;
    int jan1 = 1 + (((((C / 100) % 4) * 5) + G) % 7);
    int H = d + (jan1 - 1), wd = 1 + ((H - 1) % 7);
    int y = year, w = 0;

    if (d <= (8 - jan1) && jan1 > 4) {
        y = year - 1;
        w = (jan1 == 5 || (jan1 == 6 && leapYear_1)) ? 53 : 52;
    } else {
        y = year;
    }

    if (y == year) {
        int i = (leapYear ? 366 : 365);
        if ((i - d) < (4 - wd)) w = 1;
    }
    if (y == year && w == 0) {
        int j = d + (7 - wd) + (jan1 - 1);
        w = j / 7;
        if (jan1 > 4) w--;
    }
    return w;
}

int CalculateDayOfYearNumber(const SYSTEMTIME* time) {
    const int year = time->wYear, month = time->wMonth, day = time->wDay;
    const bool leapYear = ((year % 4) == 0 && (year % 100) != 0) || (year % 400) == 0;
    static const int MAP[12] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334};
    int d = day + MAP[month - 1];
    if (leapYear && month > 2) d++;
    return d;
}

void GetTimeZone(WCHAR* buffer, size_t bufferSize) {
    TIME_ZONE_INFORMATION tz = {};
    long bias = (GetTimeZoneInformation(&tz) == TIME_ZONE_ID_DAYLIGHT)
                    ? tz.Bias + tz.DaylightBias
                    : tz.Bias + tz.StandardBias;
    _snwprintf_s(buffer, bufferSize, _TRUNCATE, L"%c%02d:%02d",
                 bias <= 0 ? L'+' : L'-', static_cast<int>(abs(bias) / 60), static_cast<int>(abs(bias) % 60));
}

std::vector<std::wstring> SplitTimeFormatString(std::wstring_view s) {
    size_t posStart = 0;
    std::vector<std::wstring> result;
    while (true) {
        size_t posEnd = s.size();
        bool inQuote = false;
        for (size_t i = posStart; i < s.size(); i++) {
            if (s[i] == L'\'') inQuote = !inQuote;
            if (!inQuote && s[i] == L';') { posEnd = i; break; }
        }
        if (posEnd == s.size()) break;
        result.push_back(std::wstring(s.substr(posStart, posEnd - posStart)));
        posStart = posEnd + 1;
    }
    result.push_back(std::wstring(s.substr(posStart)));
    return result;
}

int GetTimeFormatExWithShowSeconds(LPCWSTR lpLocaleName, const SYSTEMTIME* lpTime, LPCWSTR lpFormat, LPWSTR lpTimeStr, int cchTime) {
    DWORD dwFlags = g_settings.showSeconds ? 0 : TIME_NOSECONDS;
    if (!g_settings.showSeconds && lpFormat) {
        std::wstring formatNoSeconds = ReplaceAll(lpFormat, L"':'ss", L"");
        return GetTimeFormatEx_Original(lpLocaleName, dwFlags, lpTime, formatNoSeconds.c_str(), lpTimeStr, cchTime);
    }
    return GetTimeFormatEx_Original(lpLocaleName, dwFlags, lpTime, lpFormat, lpTimeStr, cchTime);
}

PCWSTR GetTimeFormattedWithExtra(std::vector<std::wstring>** extra) {
    if (g_timeFormatted.formatIndex != g_formatIndex) {
        auto parts = SplitTimeFormatString(g_settings.timeFormat.get());
        GetTimeFormatExWithShowSeconds(nullptr, &g_formatTime, !parts[0].empty() ? parts[0].c_str() : nullptr,
                                       g_timeFormatted.buffer, ARRAYSIZE(g_timeFormatted.buffer));
        g_timeFormattedExtra.resize(parts.size() - 1);
        for (size_t i = 1; i < parts.size(); i++) {
            WCHAR buf[FORMATTED_BUFFER_SIZE];
            GetTimeFormatExWithShowSeconds(nullptr, &g_formatTime, !parts[i].empty() ? parts[i].c_str() : nullptr, buf, ARRAYSIZE(buf));
            g_timeFormattedExtra[i - 1] = buf;
        }
        g_timeFormatted.formatIndex = g_formatIndex;
    }
    if (extra) *extra = &g_timeFormattedExtra;
    return g_timeFormatted.buffer;
}

PCWSTR GetTimeFormatted() { return GetTimeFormattedWithExtra(nullptr); }
std::vector<std::wstring>* GetTimeFormattedExtra() { std::vector<std::wstring>* e; GetTimeFormattedWithExtra(&e); return e; }

PCWSTR GetTimeFormattedTz(size_t index) {
    if (index >= g_settings.timeZones.size()) return nullptr;
    auto& tzStr = g_timeFormattedTz[index];
    if (tzStr.formatIndex != g_formatIndex) {
        const auto& tzInfo = g_timeZoneInformation[index];
        if (tzInfo && pSystemTimeToTzSpecificLocalTimeEx) {
            SYSTEMTIME sys, loc;
            TzSpecificLocalTimeToSystemTime(nullptr, &g_formatTime, &sys);
            pSystemTimeToTzSpecificLocalTimeEx(&*tzInfo, &sys, &loc);
            auto parts = SplitTimeFormatString(g_settings.timeFormat.get());
            GetTimeFormatExWithShowSeconds(nullptr, &loc, !parts[0].empty() ? parts[0].c_str() : nullptr, tzStr.buffer, ARRAYSIZE(tzStr.buffer));
        } else {
            wcscpy_s(tzStr.buffer, L"-");
        }
        tzStr.formatIndex = g_formatIndex;
    }
    return tzStr.buffer;
}

PCWSTR GetDateLocaleName() { return *g_settings.dateLocale ? g_settings.dateLocale.get() : nullptr; }

PCWSTR GetDateFormattedWithExtra(std::vector<std::wstring>** extra) {
    if (g_dateFormatted.formatIndex != g_formatIndex) {
        auto parts = SplitTimeFormatString(g_settings.dateFormat.get());
        GetDateFormatEx_Original(GetDateLocaleName(), DATE_AUTOLAYOUT, &g_formatTime,
                                 !parts[0].empty() ? parts[0].c_str() : nullptr,
                                 g_dateFormatted.buffer, ARRAYSIZE(g_dateFormatted.buffer), nullptr);
        g_dateFormattedExtra.resize(parts.size() - 1);
        for (size_t i = 1; i < parts.size(); i++) {
            WCHAR buf[FORMATTED_BUFFER_SIZE];
            GetDateFormatEx_Original(GetDateLocaleName(), DATE_AUTOLAYOUT, &g_formatTime,
                                     !parts[i].empty() ? parts[i].c_str() : nullptr, buf, ARRAYSIZE(buf), nullptr);
            g_dateFormattedExtra[i - 1] = buf;
        }
        g_dateFormatted.formatIndex = g_formatIndex;
    }
    if (extra) *extra = &g_dateFormattedExtra;
    return g_dateFormatted.buffer;
}

PCWSTR GetDateFormatted() { return GetDateFormattedWithExtra(nullptr); }
std::vector<std::wstring>* GetDateFormattedExtra() { std::vector<std::wstring>* e; GetDateFormattedWithExtra(&e); return e; }

PCWSTR GetDateFormattedTz(size_t index) {
    if (index >= g_settings.timeZones.size()) return nullptr;
    auto& tzStr = g_dateFormattedTz[index];
    if (tzStr.formatIndex != g_formatIndex) {
        const auto& tzInfo = g_timeZoneInformation[index];
        if (tzInfo && pSystemTimeToTzSpecificLocalTimeEx) {
            SYSTEMTIME sys, loc;
            TzSpecificLocalTimeToSystemTime(nullptr, &g_formatTime, &sys);
            pSystemTimeToTzSpecificLocalTimeEx(&*tzInfo, &sys, &loc);
            auto parts = SplitTimeFormatString(g_settings.dateFormat.get());
            GetDateFormatEx_Original(GetDateLocaleName(), DATE_AUTOLAYOUT, &loc,
                                     !parts[0].empty() ? parts[0].c_str() : nullptr, tzStr.buffer, ARRAYSIZE(tzStr.buffer), nullptr);
        } else {
            wcscpy_s(tzStr.buffer, L"-");
        }
        tzStr.formatIndex = g_formatIndex;
    }
    return tzStr.buffer;
}

void FormatWeekday(const SYSTEMTIME* time, PWSTR buffer, size_t bufferSize) {
    if (g_settings.weekdayFormatCustom.empty()) {
        GetDateFormatEx_Original(GetDateLocaleName(), DATE_AUTOLAYOUT, time,
                                 *g_settings.weekdayFormat ? g_settings.weekdayFormat.get() : L"dddd",
                                 buffer, bufferSize, nullptr);
    } else if (g_settings.weekdayFormatCustom.size() > time->wDayOfWeek) {
        wcsncpy_s(buffer, bufferSize, g_settings.weekdayFormatCustom[time->wDayOfWeek].c_str(), bufferSize - 1);
    } else {
        wcscpy_s(buffer, bufferSize, L"-");
    }
}

PCWSTR GetWeekdayFormatted() {
    if (g_weekdayFormatted.formatIndex != g_formatIndex) {
        FormatWeekday(&g_formatTime, g_weekdayFormatted.buffer, ARRAYSIZE(g_weekdayFormatted.buffer));
        g_weekdayFormatted.formatIndex = g_formatIndex;
    }
    return g_weekdayFormatted.buffer;
}

PCWSTR GetWeekdayFormattedTz(size_t index) {
    if (index >= g_settings.timeZones.size()) return nullptr;
    auto& tzStr = g_weekdayFormattedTz[index];
    if (tzStr.formatIndex != g_formatIndex) {
        const auto& tzInfo = g_timeZoneInformation[index];
        if (tzInfo && pSystemTimeToTzSpecificLocalTimeEx) {
            SYSTEMTIME sys, loc;
            TzSpecificLocalTimeToSystemTime(nullptr, &g_formatTime, &sys);
            pSystemTimeToTzSpecificLocalTimeEx(&*tzInfo, &sys, &loc);
            FormatWeekday(&loc, tzStr.buffer, ARRAYSIZE(tzStr.buffer));
        } else {
            wcscpy_s(tzStr.buffer, L"-");
        }
        tzStr.formatIndex = g_formatIndex;
    }
    return tzStr.buffer;
}

PCWSTR GetWeekdayNumFormatted() {
    if (g_weekdayNumFormatted.formatIndex != g_formatIndex) {
        DWORD start = GetStartDayOfWeek(&g_formatTime);
        swprintf_s(g_weekdayNumFormatted.buffer, L"%d", 1 + (7 + g_formatTime.wDayOfWeek - start) % 7);
        g_weekdayNumFormatted.formatIndex = g_formatIndex;
    }
    return g_weekdayNumFormatted.buffer;
}

PCWSTR GetWeeknumFormatted() {
    if (g_weeknumFormatted.formatIndex != g_formatIndex) {
        DWORD start = GetStartDayOfWeek(&g_formatTime);
        swprintf_s(g_weeknumFormatted.buffer, L"%02d", CalculateWeeknum(&g_formatTime, start));
        g_weeknumFormatted.formatIndex = g_formatIndex;
    }
    return g_weeknumFormatted.buffer;
}

PCWSTR GetWeeknumIsoFormatted() {
    if (g_weeknumIsoFormatted.formatIndex != g_formatIndex) {
        swprintf_s(g_weeknumIsoFormatted.buffer, L"%02d", CalculateWeeknumIso(&g_formatTime));
        g_weeknumIsoFormatted.formatIndex = g_formatIndex;
    }
    return g_weeknumIsoFormatted.buffer;
}

PCWSTR GetDayOfYearFormatted() {
    if (g_dayOfYearFormatted.formatIndex != g_formatIndex) {
        swprintf_s(g_dayOfYearFormatted.buffer, L"%d", CalculateDayOfYearNumber(&g_formatTime));
        g_dayOfYearFormatted.formatIndex = g_formatIndex;
    }
    return g_dayOfYearFormatted.buffer;
}

PCWSTR GetTimezoneFormatted() {
    if (g_timezoneFormatted.formatIndex != g_formatIndex) {
        GetTimeZone(g_timezoneFormatted.buffer, ARRAYSIZE(g_timezoneFormatted.buffer));
        g_timezoneFormatted.formatIndex = g_formatIndex;
    }
    return g_timezoneFormatted.buffer;
}

// ------------------------------------------
// PERFORMANCE DATA COLLECTION
// ------------------------------------------

constexpr double kGBInBytes = 1024.0 * 1024.0 * 1024.0;
enum class MetricType {
    kUploadSpeed, kDownloadSpeed, kDiskReadSpeed, kDiskWriteSpeed,
    kCpu, kGpuUsage, kVramUsed, kVramSharedUsed, kCpuTemp, kCount,
};

struct DxgiAdapterInfo {
    std::wstring description;
    std::wstring luid;
    SIZE_T dedicated_video_memory;
    SIZE_T shared_system_memory;
};

std::optional<DxgiAdapterInfo> GetDxgiAdapterInfo(PCWSTR gpu_name, bool quiet) {
    static std::optional<std::wstring> s_gpuName;
    static std::optional<DxgiAdapterInfo> s_info;
    std::wstring key = gpu_name ? gpu_name : L"";
    if (s_gpuName == key) return s_info;
    s_gpuName = key;
    s_info.reset();

    winrt::com_ptr<IDXGIFactory> factory;
    if (FAILED(CreateDXGIFactory(IID_PPV_ARGS(factory.put())))) return std::nullopt;

    DXGI_ADAPTER_DESC best{};
    bool found = false;
    for (UINT i = 0;; i++) {
        winrt::com_ptr<IDXGIAdapter> adapter;
        if (factory->EnumAdapters(i, adapter.put()) == DXGI_ERROR_NOT_FOUND) break;
        DXGI_ADAPTER_DESC desc{};
        if (FAILED(adapter->GetDesc(&desc))) continue;
        if (gpu_name && *gpu_name) {
            if (wcsstr(desc.Description, gpu_name)) { best = desc; found = true; break; }
        } else {
            if (!found || desc.DedicatedVideoMemory > best.DedicatedVideoMemory) { best = desc; found = true; }
        }
    }
    if (!found) return std::nullopt;
    WCHAR luid_str[32];
    swprintf_s(luid_str, L"0x%08X_0x%08X", best.AdapterLuid.HighPart, best.AdapterLuid.LowPart);
    s_info = DxgiAdapterInfo{best.Description, luid_str, best.DedicatedVideoMemory, best.SharedSystemMemory};
    return s_info;
}

std::optional<double> GetDedicatedVramTotalGb() {
    auto info = GetDxgiAdapterInfo(g_settings.dataCollection.gpuAdapterName, true);
    if (info && info->dedicated_video_memory > 0) return (double)info->dedicated_video_memory / kGBInBytes;
    return std::nullopt;
}

std::optional<double> GetSharedVramTotalGb() {
    auto info = GetDxgiAdapterInfo(g_settings.dataCollection.gpuAdapterName, true);
    if (info && info->shared_system_memory > 0) return (double)info->shared_system_memory / kGBInBytes;
    return std::nullopt;
}

class QueryDataCollectionSession {
public:
    QueryDataCollectionSession() { winrt::check_hresult(PdhOpenQuery(nullptr, 0, &query_)); }
    ~QueryDataCollectionSession() { PdhCloseQuery(query_); }

    bool AddMetric(MetricType type);
    void UpdateAllMetrics();
    bool SampleData();
    std::optional<double> QueryData(MetricType type);
    std::optional<double> QueryDataAvg(MetricType type);

private:
    struct QueryDataResult { double sum; size_t count; };
    std::optional<QueryDataResult> QueryDataWithCount(MetricType type);
    void UpdateMetric(MetricType type);
    std::vector<std::wstring> ExpandEnglishWildcard(PCWSTR wildcard_path, bool quiet);
    static std::wstring_view ExtractInstanceName(std::wstring_view path);
    static std::wstring_view ExtractGpuLuid(std::wstring_view instance);
    static std::vector<std::wstring> FilterNetworkPathsByAdapterName(const std::vector<std::wstring>& paths, PCWSTR adapter_name, bool quiet);
    static std::vector<std::wstring> FilterGpuPathsByAdapterName(const std::vector<std::wstring>& paths, PCWSTR gpu_name, bool quiet);

    std::vector<std::wstring> ExpandAndFilterWildcardPaths(MetricType type, PCWSTR counter_path, PCWSTR adapter_name, bool quiet) {
        auto paths = ExpandEnglishWildcard(counter_path, quiet);
        if (!paths.empty()) {
            if (type == MetricType::kGpuUsage || type == MetricType::kVramUsed || type == MetricType::kVramSharedUsed) {
                paths = FilterGpuPathsByAdapterName(paths, adapter_name, quiet);
            } else if (adapter_name && *adapter_name) {
                paths = FilterNetworkPathsByAdapterName(paths, adapter_name, quiet);
            }
        }
        return paths;
    }

    struct CounterEntry { std::wstring path; PDH_HCOUNTER counter; };
    struct MetricData { std::vector<CounterEntry> counters; PCWSTR wildcard_path = nullptr; PCWSTR adapter_name = nullptr; };

    PDH_HQUERY query_;
    MetricData metrics_[static_cast<int>(MetricType::kCount)];
};

bool QueryDataCollectionSession::AddMetric(MetricType type) {
    PCWSTR counter_path;
    bool is_wildcard = false;
    PCWSTR adapter_name = nullptr;

    switch (type) {
        case MetricType::kDownloadSpeed:
            counter_path = L"\\Network Interface(*)\\Bytes Received/sec";
            is_wildcard = true;
            adapter_name = g_settings.dataCollection.networkAdapterName;
            break;
        case MetricType::kUploadSpeed:
            counter_path = L"\\Network Interface(*)\\Bytes Sent/sec";
            is_wildcard = true;
            adapter_name = g_settings.dataCollection.networkAdapterName;
            break;
        case MetricType::kDiskReadSpeed:
            counter_path = L"\\PhysicalDisk(_Total)\\Disk Read Bytes/sec";
            break;
        case MetricType::kDiskWriteSpeed:
            counter_path = L"\\PhysicalDisk(_Total)\\Disk Write Bytes/sec";
            break;
        case MetricType::kCpu:
            counter_path = L"\\Processor Information(_Total)\\% Processor Utility";
            break;
        case MetricType::kGpuUsage:
            counter_path = L"\\GPU Engine(*)\\Utilization Percentage";
            is_wildcard = true;
            adapter_name = g_settings.dataCollection.gpuAdapterName;
            break;
        case MetricType::kVramUsed:
            counter_path = L"\\GPU Adapter Memory(*)\\Dedicated Usage";
            is_wildcard = true;
            adapter_name = g_settings.dataCollection.gpuAdapterName;
            break;
        case MetricType::kVramSharedUsed:
            counter_path = L"\\GPU Adapter Memory(*)\\Shared Usage";
            is_wildcard = true;
            adapter_name = g_settings.dataCollection.gpuAdapterName;
            break;
        case MetricType::kCpuTemp:
            counter_path = L"\\Thermal Zone Information(*)\\Temperature";
            is_wildcard = true;
            break;
        default: return false;
    }

    auto& metric = metrics_[static_cast<int>(type)];
    if (!metric.counters.empty()) return false;

    metric.wildcard_path = is_wildcard ? counter_path : nullptr;
    metric.adapter_name = adapter_name;

    if (is_wildcard) {
        auto paths = ExpandAndFilterWildcardPaths(type, counter_path, adapter_name, false);
        for (const auto& path : paths) {
            PDH_HCOUNTER counter;
            if (SUCCEEDED(PdhAddCounter(query_, path.c_str(), 0, &counter))) {
                metric.counters.push_back({path, counter});
            }
        }
    } else {
        PDH_HCOUNTER counter;
        if (SUCCEEDED(PdhAddEnglishCounter(query_, counter_path, 0, &counter))) {
            metric.counters.push_back({counter_path, counter});
        }
    }
    return !metric.counters.empty();
}

void QueryDataCollectionSession::UpdateMetric(MetricType type) {
    auto& metric = metrics_[static_cast<int>(type)];
    if (!metric.wildcard_path) return;

    auto current_paths = ExpandAndFilterWildcardPaths(type, metric.wildcard_path, metric.adapter_name, true);
    std::unordered_set<std::wstring> cur_set(current_paths.begin(), current_paths.end());

    for (auto it = metric.counters.begin(); it != metric.counters.end();) {
        if (!cur_set.contains(it->path)) {
            PdhRemoveCounter(it->counter);
            it = metric.counters.erase(it);
        } else {
            ++it;
        }
    }

    std::unordered_set<std::wstring> exist_set;
    for (const auto& entry : metric.counters) exist_set.insert(entry.path);

    for (const auto& path : current_paths) {
        if (!exist_set.contains(path)) {
            PDH_HCOUNTER counter;
            if (SUCCEEDED(PdhAddCounter(query_, path.c_str(), 0, &counter))) {
                metric.counters.push_back({path, counter});
            }
        }
    }
}

void QueryDataCollectionSession::UpdateAllMetrics() {
    for (int i = 0; i < static_cast<int>(MetricType::kCount); i++) {
        if (metrics_[i].wildcard_path) UpdateMetric(static_cast<MetricType>(i));
    }
}

bool QueryDataCollectionSession::SampleData() {
    return SUCCEEDED(PdhCollectQueryData(query_));
}

std::optional<QueryDataCollectionSession::QueryDataResult> QueryDataCollectionSession::QueryDataWithCount(MetricType type) {
    const auto& metric = metrics_[static_cast<int>(type)];
    if (metric.counters.empty()) return std::nullopt;

    double sum = 0.0;
    size_t count = 0;
    for (const auto& entry : metric.counters) {
        PDH_FMT_COUNTERVALUE val;
        if (SUCCEEDED(PdhGetFormattedCounterValue(entry.counter, PDH_FMT_DOUBLE, nullptr, &val))) {
            if (type == MetricType::kCpuTemp && val.doubleValue < 200) continue;
            sum += val.doubleValue;
            count++;
        }
    }
    if (count == 0) return std::nullopt;
    return QueryDataResult{sum, count};
}

std::optional<double> QueryDataCollectionSession::QueryData(MetricType type) {
    auto r = QueryDataWithCount(type);
    return r ? std::optional<double>(r->sum) : std::nullopt;
}

std::optional<double> QueryDataCollectionSession::QueryDataAvg(MetricType type) {
    auto r = QueryDataWithCount(type);
    return r ? std::optional<double>(r->sum / r->count) : std::nullopt;
}

std::vector<std::wstring> QueryDataCollectionSession::ExpandEnglishWildcard(PCWSTR wildcard_path, bool quiet) {
    PDH_HCOUNTER temp;
    if (FAILED(PdhAddEnglishCounter(query_, wildcard_path, 0, &temp))) return {};
    DWORD req = 0;
    PdhGetCounterInfo(temp, FALSE, &req, nullptr);
    if (!req) { PdhRemoveCounter(temp); return {}; }

    std::vector<BYTE> buf(req);
    PDH_COUNTER_INFO* info = reinterpret_cast<PDH_COUNTER_INFO*>(buf.data());
    if (FAILED(PdhGetCounterInfo(temp, FALSE, &req, info))) { PdhRemoveCounter(temp); return {}; }
    PdhRemoveCounter(temp);

    req = 0;
    PdhExpandWildCardPath(nullptr, info->szFullPath, nullptr, &req, 0);
    if (!req) return {};
    std::vector<WCHAR> path_buf(req);
    if (FAILED(PdhExpandWildCardPath(nullptr, info->szFullPath, path_buf.data(), &req, 0))) return {};

    std::vector<std::wstring> out;
    WCHAR* p = path_buf.data();
    while (*p) {
        out.emplace_back(p);
        p += wcslen(p) + 1;
    }
    return out;
}

std::wstring_view QueryDataCollectionSession::ExtractInstanceName(std::wstring_view path) {
    auto start = path.find(L'(');
    auto end = path.rfind(L')');
    if (start == std::wstring_view::npos || end == std::wstring_view::npos || end <= start) return {};
    return path.substr(start + 1, end - start - 1);
}

std::wstring_view QueryDataCollectionSession::ExtractGpuLuid(std::wstring_view instance) {
    auto pos = instance.find(L"luid_");
    if (pos == std::wstring_view::npos) return {};
    auto start = pos + 5;
    auto end = instance.find(L"_phys_", start);
    if (end == std::wstring_view::npos) return {};
    return instance.substr(start, end - start);
}

std::vector<std::wstring> QueryDataCollectionSession::FilterNetworkPathsByAdapterName(const std::vector<std::wstring>& paths, PCWSTR name, bool quiet) {
    std::vector<std::wstring> res;
    for (const auto& path : paths) {
        auto inst = ExtractInstanceName(path);
        if (!inst.empty() && inst.find(name) != std::wstring_view::npos) res.push_back(path);
    }
    return res;
}

std::vector<std::wstring> QueryDataCollectionSession::FilterGpuPathsByAdapterName(const std::vector<std::wstring>& paths, PCWSTR name, bool quiet) {
    auto info = GetDxgiAdapterInfo(name, quiet);
    if (!info) return {};
    std::vector<std::wstring> res;
    for (const auto& path : paths) {
        auto inst = ExtractInstanceName(path);
        auto luid = ExtractGpuLuid(inst);
        if (!luid.empty() && _wcsicmp(std::wstring(luid).c_str(), info->luid.c_str()) == 0) res.push_back(path);
    }
    return res;
}

std::optional<QueryDataCollectionSession> g_dataCollectionSession;
DWORD g_dataCollectionLastFormatIndex;

// ------------------------------------------
// MEDIA PLAYER INTEGRATION
// ------------------------------------------

bool IsMediaPlayerIgnored(const winrt::hstring& appId) {
    std::wstring lower(appId);
    std::transform(lower.begin(), lower.end(), lower.begin(), ::towlower);
    for (const auto& ign : g_settings.mediaPlayer.ignoredPlayers) {
        std::wstring iLower(ign.get());
        if (iLower.empty()) continue;
        std::transform(iLower.begin(), iLower.end(), iLower.begin(), ::towlower);
        if (lower.find(iLower) != std::wstring::npos) return true;
    }
    return false;
}

void RemoveBracketedContent(std::wstring& str, wchar_t open, wchar_t close) {
    size_t start = 0;
    while ((start = str.find(open, start)) != std::wstring::npos) {
        size_t end = std::wstring::npos;
        int depth = 0;
        for (size_t i = start; i < str.size(); i++) {
            if (str[i] == open) depth++;
            else if (str[i] == close && --depth == 0) { end = i; break; }
        }
        if (end == std::wstring::npos) break;

        bool hasContent = false;
        for (size_t i = start + 1; i < end; i++) {
            if (str[i] != L' ' && str[i] != L'\t' && str[i] != L'\n' && str[i] != L'\r') {
                hasContent = true; break;
            }
        }
        if (hasContent) {
            size_t rs = start, re = end;
            if (start > 0 && str[start - 1] == L' ') rs--;
            else if (end + 1 < str.size() && str[end + 1] == L' ') re++;
            str.erase(rs, re - rs + 1);
            start = rs;
        } else {
            start = end + 1;
        }
    }
}

std::wstring RemoveBracketsFromString(std::wstring_view input) {
    if (!g_settings.mediaPlayer.removeBrackets) return std::wstring(input);
    std::wstring res(input);
    RemoveBracketedContent(res, L'(', L')');
    RemoveBracketedContent(res, L'[', L']');
    size_t s = res.find_first_not_of(L' ');
    if (s == std::wstring::npos) return {};
    size_t e = res.find_last_not_of(L' ');
    return res.substr(s, e - s + 1);
}

void ClearMediaFormattedStrings() {
    g_mediaActive = false;
    wcscpy_s(g_mediaTitleFormatted.buffer, L"");
    wcscpy_s(g_mediaArtistFormatted.buffer, L"");
    wcscpy_s(g_mediaAlbumFormatted.buffer, L"");
    wcscpy_s(g_mediaStatusFormatted.buffer, L"");
}

winrt::Windows::Media::Control::GlobalSystemMediaTransportControlsSession FindActiveMediaSession() {
    if (!g_mediaSessionManager) return nullptr;
    auto cur = g_mediaSessionManager.GetCurrentSession();
    if (cur) {
        try { if (!IsMediaPlayerIgnored(cur.SourceAppUserModelId())) return cur; } catch (...) {}
    }
    try {
        auto sessions = g_mediaSessionManager.GetSessions();
        using Status = winrt::Windows::Media::Control::GlobalSystemMediaTransportControlsSessionPlaybackStatus;
        for (uint32_t i = 0; i < sessions.Size(); i++) {
            auto s = sessions.GetAt(i);
            try {
                if (IsMediaPlayerIgnored(s.SourceAppUserModelId())) continue;
                auto st = s.GetPlaybackInfo().PlaybackStatus();
                if (st == Status::Playing || st == Status::Paused) return s;
            } catch (...) {}
        }
        for (uint32_t i = 0; i < sessions.Size(); i++) {
            auto s = sessions.GetAt(i);
            try { if (!IsMediaPlayerIgnored(s.SourceAppUserModelId())) return s; } catch (...) {}
        }
    } catch (...) {}
    return nullptr;
}

void RefreshMediaData() {
    std::lock_guard<std::mutex> guard(g_mediaMutex);
    try {
        if (!g_mediaSessionManager) { ClearMediaFormattedStrings(); return; }
        auto session = FindActiveMediaSession();
        if (!session) { ClearMediaFormattedStrings(); return; }
        auto props = session.TryGetMediaPropertiesAsync().get();
        if (!props) { ClearMediaFormattedStrings(); return; }

        g_mediaActive = true;
        using Status = winrt::Windows::Media::Control::GlobalSystemMediaTransportControlsSessionPlaybackStatus;
        auto status = session.GetPlaybackInfo().PlaybackStatus();
        switch (status) {
            case Status::Playing: wcscpy_s(g_mediaStatusFormatted.buffer, L"\u23EF"); break;
            case Status::Paused: wcscpy_s(g_mediaStatusFormatted.buffer, L"\u23F8"); break;
            case Status::Stopped: wcscpy_s(g_mediaStatusFormatted.buffer, L"\u23F9"); break;
            default: wcscpy_s(g_mediaStatusFormatted.buffer, L""); break;
        }

        std::wstring title = RemoveBracketsFromString(props.Title());
        std::wstring artist = RemoveBracketsFromString(props.Artist());
        auto album = props.AlbumTitle();

        StringCopyTruncatedWithEllipsis(g_mediaTitleFormatted.buffer, ARRAYSIZE(g_mediaTitleFormatted.buffer), title.c_str());
        StringCopyTruncatedWithEllipsis(g_mediaArtistFormatted.buffer, ARRAYSIZE(g_mediaArtistFormatted.buffer), artist.c_str());
        StringCopyTruncatedWithEllipsis(g_mediaAlbumFormatted.buffer, ARRAYSIZE(g_mediaAlbumFormatted.buffer), album.c_str());
    } catch (...) {
        ClearMediaFormattedStrings();
    }
    g_mediaDataDirty = false;
}

void DataCollectionSessionInit() {
    bool metrics[static_cast<int>(MetricType::kCount)]{};
    metrics[static_cast<int>(MetricType::kUploadSpeed)] = IsStrInDateTimePatternSettings(L"%upload_speed%");
    metrics[static_cast<int>(MetricType::kDownloadSpeed)] = IsStrInDateTimePatternSettings(L"%download_speed%");
    if (IsStrInDateTimePatternSettings(L"%total_speed%")) {
        metrics[static_cast<int>(MetricType::kUploadSpeed)] = true;
        metrics[static_cast<int>(MetricType::kDownloadSpeed)] = true;
    }
    metrics[static_cast<int>(MetricType::kDiskReadSpeed)] = IsStrInDateTimePatternSettings(L"%disk_read%");
    metrics[static_cast<int>(MetricType::kDiskWriteSpeed)] = IsStrInDateTimePatternSettings(L"%disk_write%");
    if (IsStrInDateTimePatternSettings(L"%disk_total%")) {
        metrics[static_cast<int>(MetricType::kDiskReadSpeed)] = true;
        metrics[static_cast<int>(MetricType::kDiskWriteSpeed)] = true;
    }
    metrics[static_cast<int>(MetricType::kCpu)] = IsStrInDateTimePatternSettings(L"%cpu%");
    metrics[static_cast<int>(MetricType::kGpuUsage)] = IsStrInDateTimePatternSettings(L"%gpu%");
    metrics[static_cast<int>(MetricType::kVramUsed)] = IsStrInDateTimePatternSettings(L"%vram%") || IsStrInDateTimePatternSettings(L"%vram_used%");
    metrics[static_cast<int>(MetricType::kVramSharedUsed)] = IsStrInDateTimePatternSettings(L"%vram_shared%") || IsStrInDateTimePatternSettings(L"%vram_shared_used%");
    metrics[static_cast<int>(MetricType::kCpuTemp)] = IsStrInDateTimePatternSettings(L"%cpu_temp%") || IsStrInDateTimePatternSettings(L"%cpu_temp_f%");

    if (!std::any_of(std::begin(metrics), std::end(metrics), [](bool x) { return x; })) return;

    try {
        g_dataCollectionSession.emplace();
    } catch (...) { return; }

    for (size_t i = 0; i < ARRAYSIZE(metrics); i++) {
        if (metrics[i]) g_dataCollectionSession->AddMetric(static_cast<MetricType>(i));
    }
    g_dataCollectionSession->SampleData();
}

void DataCollectionSessionUninit() {
    g_dataCollectionSession.reset();
    g_dataCollectionLastFormatIndex = 0;
}

bool IsMediaPatternUsed() {
    return IsStrInDateTimePatternSettings(L"%media_title%") ||
           IsStrInDateTimePatternSettings(L"%media_artist%") ||
           IsStrInDateTimePatternSettings(L"%media_album%") ||
           IsStrInDateTimePatternSettings(L"%media_status%") ||
           IsStrInDateTimePatternSettings(L"%media_info%");
}

void UnsubscribeFromMediaSession() {
    if (g_mediaCurrentSession) {
        try {
            g_mediaCurrentSession.MediaPropertiesChanged(g_mediaPropertiesChangedToken);
            g_mediaCurrentSession.PlaybackInfoChanged(g_mediaPlaybackChangedToken);
        } catch (...) {}
        g_mediaCurrentSession = nullptr;
    }
}

void SubscribeToMediaSession() {
    UnsubscribeFromMediaSession();
    if (!g_mediaSessionManager) return;
    try {
        auto session = FindActiveMediaSession();
        if (!session) return;
        g_mediaCurrentSession = session;
        g_mediaPropertiesChangedToken = session.MediaPropertiesChanged([](auto&&, auto&&) { g_mediaDataDirty = true; });
        g_mediaPlaybackChangedToken = session.PlaybackInfoChanged([](auto&&, auto&&) { g_mediaDataDirty = true; });
    } catch (...) {}
}

void MediaSessionUninit() {
    UnsubscribeFromMediaSession();
    if (g_mediaSessionManager) {
        try { g_mediaSessionManager.SessionsChanged(g_mediaSessionsChangedToken); } catch (...) {}
        g_mediaSessionManager = nullptr;
    }
    g_mediaDataDirty = true;
}

void MediaSessionInit() {
    if (!IsMediaPatternUsed()) return;
    try {
        g_mediaSessionManager = winrt::Windows::Media::Control::GlobalSystemMediaTransportControlsSessionManager::RequestAsync().get();
        g_mediaSessionsChangedToken = g_mediaSessionManager.SessionsChanged([](auto&&, auto&&) {
            g_mediaDataDirty = true;
            SubscribeToMediaSession();
        });
        SubscribeToMediaSession();
        RefreshMediaData();
    } catch (...) {
        MediaSessionUninit();
    }
}

DWORD GetDataCollectionFormatIndex() {
    FILETIME ft{};
    SystemTimeToFileTime(&g_formatTime, &ft);
    ULARGE_INTEGER i{.LowPart = ft.dwLowDateTime, .HighPart = ft.dwHighDateTime};
    ULONGLONG interval = 10000000ULL * std::max(g_settings.dataCollection.updateInterval, 1);
    return static_cast<DWORD>(i.QuadPart / interval);
}

void DataCollectionSampleIfNeeded() {
    DWORD idx = GetDataCollectionFormatIndex();
    if (g_dataCollectionLastFormatIndex != idx) {
        if (g_dataCollectionSession) {
            g_dataCollectionSession->UpdateAllMetrics();
            g_dataCollectionSession->SampleData();
        }
        g_dataCollectionLastFormatIndex = idx;
    }
}

std::optional<MEMORYSTATUSEX> GetRamStatus() {
    static MEMORYSTATUSEX status{};
    static bool valid = false;
    static DWORD lastIdx = 0xFFFFFFFF;
    DWORD idx = GetDataCollectionFormatIndex();
    if (lastIdx != idx) {
        status.dwLength = sizeof(status);
        valid = GlobalMemoryStatusEx(&status);
        lastIdx = idx;
    }
    return valid ? std::optional<MEMORYSTATUSEX>(status) : std::nullopt;
}

std::wstring FormatLocaleNum(double val, unsigned int digits) {
    int len = _scwprintf(L"%.17f", val);
    if (len < 0) return {};
    std::wstring valStr(len + 1, L'\0');
    swprintf_s(valStr.data(), valStr.size(), L"%.17f", val);

    WCHAR decSep[4];
    if (!GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT, LOCALE_SDECIMAL, decSep, ARRAYSIZE(decSep))) {
        decSep[0] = L'.'; 
        decSep[1] = L'\0';
    }

    NUMBERFMTW fmt{
        .NumDigits = digits,
        .LeadingZero = 1,
        .Grouping = 0,
        .lpDecimalSep = const_cast<LPWSTR>(decSep),
        .lpThousandSep = const_cast<LPWSTR>(L""),
        .NegativeOrder = 1
    };

    int needed = GetNumberFormatEx(LOCALE_NAME_USER_DEFAULT, 0, valStr.c_str(), &fmt, nullptr, 0);
    if (!needed) return {};
    std::wstring out(needed - 1, L'\0');
    GetNumberFormatEx(LOCALE_NAME_USER_DEFAULT, 0, valStr.c_str(), &fmt, out.data(), needed);
    return out;
}

void FormatTransferSpeed(double val, NetworkMetricsFormat format, int fixedDecimals, PWSTR buffer, size_t bufferSize) {
    constexpr int kKB = 1024, kMB = 1024 * kKB, kKbit = 1000 / 8, kMbit = 1000 * kKbit;
    double valUnit = 0;
    PCWSTR unit = L"";

    switch (format) {
        case NetworkMetricsFormat::mbs: valUnit = val / kMB; unit = L" MB/s"; break;
        case NetworkMetricsFormat::mbsNumberOnly: valUnit = val / kMB; break;
        case NetworkMetricsFormat::mbsDynamic:
            if (val / kKB < 1000) { valUnit = val / kKB; unit = L" KB/s"; }
            else { valUnit = val / kMB; unit = L" MB/s"; }
            break;
        case NetworkMetricsFormat::mbits: valUnit = val / kMbit; unit = L" MBit/s"; break;
        case NetworkMetricsFormat::mbitsNumberOnly: valUnit = val / kMbit; break;
        case NetworkMetricsFormat::mbitsDynamic:
            if (val / kKbit < 1000) { valUnit = val / kKbit; unit = L" KBit/s"; }
            else { valUnit = val / kMbit; unit = L" MBit/s"; }
            break;
    }

    int digits = 0;
    PCWSTR prefix = L"";
    if (fixedDecimals == -1) {
        if (valUnit < 10) digits = 2;
        else if (valUnit < 100) digits = 1;
        else if (valUnit < 1000) prefix = L"\u2008";
    } else {
        digits = fixedDecimals;
    }
    swprintf_s(buffer, bufferSize, L"%s%s%s", prefix, FormatLocaleNum(valUnit, digits).c_str(), unit);
}

void FormatPercentValue(int val, PWSTR buffer, size_t bufferSize, int maxVal) {
    if (val > maxVal) val = maxVal;
    PCWSTR pad = L"", suf = L"";
    switch (g_settings.dataCollection.percentageFormat) {
        case PercentageFormat::spacePaddingAndSymbol: pad = L"  "; suf = L"%"; break;
        case PercentageFormat::spacePadding: pad = L"  "; break;
        case PercentageFormat::singleSpacePadding: pad = L" "; break;
        case PercentageFormat::zeroPadding: pad = L"0"; break;
        default: break;
    }
    swprintf_s(buffer, bufferSize, L"%s%d%s", val < 10 ? pad : L"", val, suf);
}

template <size_t N, typename Formatter>
PCWSTR GetMetricFormatted(FormattedString<N>& s, Formatter f) {
    DWORD idx = GetDataCollectionFormatIndex();
    if (s.formatIndex != idx) {
        if (!f(s.buffer, ARRAYSIZE(s.buffer))) wcscpy_s(s.buffer, L"-");
        s.formatIndex = idx;
    }
    return s.buffer;
}

PCWSTR GetUploadSpeedFormatted() {
    DataCollectionSampleIfNeeded();
    return GetMetricFormatted(g_uploadSpeedFormatted, [](PWSTR b, size_t s) {
        if (!g_dataCollectionSession) return false;
        auto v = g_dataCollectionSession->QueryData(MetricType::kUploadSpeed);
        if (!v) return false;
        FormatTransferSpeed(*v, g_settings.dataCollection.networkMetricsFormat, g_settings.dataCollection.networkMetricsFixedDecimals, b, s);
        return true;
    });
}

PCWSTR GetDownloadSpeedFormatted() {
    DataCollectionSampleIfNeeded();
    return GetMetricFormatted(g_downloadSpeedFormatted, [](PWSTR b, size_t s) {
        if (!g_dataCollectionSession) return false;
        auto v = g_dataCollectionSession->QueryData(MetricType::kDownloadSpeed);
        if (!v) return false;
        FormatTransferSpeed(*v, g_settings.dataCollection.networkMetricsFormat, g_settings.dataCollection.networkMetricsFixedDecimals, b, s);
        return true;
    });
}

PCWSTR GetTotalSpeedFormatted() {
    DataCollectionSampleIfNeeded();
    return GetMetricFormatted(g_totalSpeedFormatted, [](PWSTR b, size_t s) {
        if (!g_dataCollectionSession) return false;
        auto u = g_dataCollectionSession->QueryData(MetricType::kUploadSpeed);
        auto d = g_dataCollectionSession->QueryData(MetricType::kDownloadSpeed);
        if (!u || !d) return false;
        FormatTransferSpeed(*u + *d, g_settings.dataCollection.networkMetricsFormat, g_settings.dataCollection.networkMetricsFixedDecimals, b, s);
        return true;
    });
}

PCWSTR GetDiskReadSpeedFormatted() {
    DataCollectionSampleIfNeeded();
    return GetMetricFormatted(g_diskReadSpeedFormatted, [](PWSTR b, size_t s) {
        if (!g_dataCollectionSession) return false;
        auto v = g_dataCollectionSession->QueryData(MetricType::kDiskReadSpeed);
        if (!v) return false;
        FormatTransferSpeed(*v, g_settings.dataCollection.diskMetricsFormat, g_settings.dataCollection.diskMetricsFixedDecimals, b, s);
        return true;
    });
}

PCWSTR GetDiskWriteSpeedFormatted() {
    DataCollectionSampleIfNeeded();
    return GetMetricFormatted(g_diskWriteSpeedFormatted, [](PWSTR b, size_t s) {
        if (!g_dataCollectionSession) return false;
        auto v = g_dataCollectionSession->QueryData(MetricType::kDiskWriteSpeed);
        if (!v) return false;
        FormatTransferSpeed(*v, g_settings.dataCollection.diskMetricsFormat, g_settings.dataCollection.diskMetricsFixedDecimals, b, s);
        return true;
    });
}

PCWSTR GetDiskTotalSpeedFormatted() {
    DataCollectionSampleIfNeeded();
    return GetMetricFormatted(g_diskTotalSpeedFormatted, [](PWSTR b, size_t s) {
        if (!g_dataCollectionSession) return false;
        auto r = g_dataCollectionSession->QueryData(MetricType::kDiskReadSpeed);
        auto w = g_dataCollectionSession->QueryData(MetricType::kDiskWriteSpeed);
        if (!r || !w) return false;
        FormatTransferSpeed(*r + *w, g_settings.dataCollection.diskMetricsFormat, g_settings.dataCollection.diskMetricsFixedDecimals, b, s);
        return true;
    });
}

PCWSTR GetCpuFormatted() {
    DataCollectionSampleIfNeeded();
    return GetMetricFormatted(g_cpuFormatted, [](PWSTR b, size_t s) {
        if (!g_dataCollectionSession) return false;
        auto v = g_dataCollectionSession->QueryData(MetricType::kCpu);
        if (!v) return false;
        FormatPercentValue(static_cast<int>(*v), b, s, 99);
        return true;
    });
}

PCWSTR GetRamFormatted() {
    return GetMetricFormatted(g_ramFormatted, [](PWSTR b, size_t s) {
        auto r = GetRamStatus();
        if (!r) return false;
        FormatPercentValue(r->dwMemoryLoad, b, s, 99);
        return true;
    });
}

PCWSTR GetRamUsedFormatted() {
    return GetMetricFormatted(g_ramUsedFormatted, [](PWSTR b, size_t s) {
        auto r = GetRamStatus();
        if (!r) return false;
        swprintf_s(b, s, L"%.1f", (double)(r->ullTotalPhys - r->ullAvailPhys) / kGBInBytes);
        return true;
    });
}

PCWSTR GetRamTotalFormatted() {
    return GetMetricFormatted(g_ramTotalFormatted, [](PWSTR b, size_t s) {
        auto r = GetRamStatus();
        if (!r) return false;
        swprintf_s(b, s, L"%.1f", (double)r->ullTotalPhys / kGBInBytes);
        return true;
    });
}

PCWSTR GetRamCommittedFormatted() {
    return GetMetricFormatted(g_ramCommittedFormatted, [](PWSTR b, size_t s) {
        auto r = GetRamStatus();
        if (!r || !r->ullTotalPageFile) return false;
        FormatPercentValue(static_cast<int>(((r->ullTotalPageFile - r->ullAvailPageFile) * 100) / r->ullTotalPageFile), b, s, 99);
        return true;
    });
}

PCWSTR GetRamCommittedUsedFormatted() {
    return GetMetricFormatted(g_ramCommittedUsedFormatted, [](PWSTR b, size_t s) {
        auto r = GetRamStatus();
        if (!r) return false;
        swprintf_s(b, s, L"%.1f", (double)(r->ullTotalPageFile - r->ullAvailPageFile) / kGBInBytes);
        return true;
    });
}

PCWSTR GetRamCommittedTotalFormatted() {
    return GetMetricFormatted(g_ramCommittedTotalFormatted, [](PWSTR b, size_t s) {
        auto r = GetRamStatus();
        if (!r) return false;
        swprintf_s(b, s, L"%.1f", (double)r->ullTotalPageFile / kGBInBytes);
        return true;
    });
}

PCWSTR GetGpuFormatted() {
    DataCollectionSampleIfNeeded();
    return GetMetricFormatted(g_gpuFormatted, [](PWSTR b, size_t s) {
        if (!g_dataCollectionSession) return false;
        auto v = g_dataCollectionSession->QueryData(MetricType::kGpuUsage);
        if (!v) return false;
        FormatPercentValue(static_cast<int>(*v), b, s, 99);
        return true;
    });
}

PCWSTR GetVramFormatted() {
    DataCollectionSampleIfNeeded();
    return GetMetricFormatted(g_vramFormatted, [](PWSTR b, size_t s) {
        if (!g_dataCollectionSession) return false;
        auto u = g_dataCollectionSession->QueryData(MetricType::kVramUsed);
        auto t = GetDedicatedVramTotalGb();
        if (!u || !t || *t <= 0) return false;
        FormatPercentValue(static_cast<int>((*u / kGBInBytes) / *t * 100.0), b, s, 99);
        return true;
    });
}

PCWSTR GetVramUsedFormatted() {
    DataCollectionSampleIfNeeded();
    return GetMetricFormatted(g_vramUsedFormatted, [](PWSTR b, size_t s) {
        if (!g_dataCollectionSession) return false;
        auto v = g_dataCollectionSession->QueryData(MetricType::kVramUsed);
        if (!v) return false;
        swprintf_s(b, s, L"%.1f", *v / kGBInBytes);
        return true;
    });
}

PCWSTR GetVramTotalFormatted() {
    return GetMetricFormatted(g_vramTotalFormatted, [](PWSTR b, size_t s) {
        auto v = GetDedicatedVramTotalGb();
        if (!v) return false;
        swprintf_s(b, s, L"%.1f", *v);
        return true;
    });
}

PCWSTR GetVramSharedFormatted() {
    DataCollectionSampleIfNeeded();
    return GetMetricFormatted(g_vramSharedFormatted, [](PWSTR b, size_t s) {
        if (!g_dataCollectionSession) return false;
        auto u = g_dataCollectionSession->QueryData(MetricType::kVramSharedUsed);
        auto t = GetSharedVramTotalGb();
        if (!u || !t || *t <= 0) return false;
        FormatPercentValue(static_cast<int>((*u / kGBInBytes) / *t * 100.0), b, s, 99);
        return true;
    });
}

PCWSTR GetVramSharedUsedFormatted() {
    DataCollectionSampleIfNeeded();
    return GetMetricFormatted(g_vramSharedUsedFormatted, [](PWSTR b, size_t s) {
        if (!g_dataCollectionSession) return false;
        auto v = g_dataCollectionSession->QueryData(MetricType::kVramSharedUsed);
        if (!v) return false;
        swprintf_s(b, s, L"%.1f", *v / kGBInBytes);
        return true;
    });
}

PCWSTR GetVramSharedTotalFormatted() {
    return GetMetricFormatted(g_vramSharedTotalFormatted, [](PWSTR b, size_t s) {
        auto v = GetSharedVramTotalGb();
        if (!v) return false;
        swprintf_s(b, s, L"%.1f", *v);
        return true;
    });
}

PCWSTR GetCpuTempFormatted() {
    DataCollectionSampleIfNeeded();
    return GetMetricFormatted(g_cpuTempFormatted, [](PWSTR b, size_t s) {
        if (!g_dataCollectionSession) return false;
        auto k = g_dataCollectionSession->QueryDataAvg(MetricType::kCpuTemp);
        if (!k) return false;
        swprintf_s(b, s, L"%d\u00B0C", static_cast<int>(*k - 273.15));
        return true;
    });
}

PCWSTR GetCpuTempFFormatted() {
    DataCollectionSampleIfNeeded();
    return GetMetricFormatted(g_cpuTempFFormatted, [](PWSTR b, size_t s) {
        if (!g_dataCollectionSession) return false;
        auto k = g_dataCollectionSession->QueryDataAvg(MetricType::kCpuTemp);
        if (!k) return false;
        swprintf_s(b, s, L"%d\u00B0F", static_cast<int>((*k - 273.15) * 9.0 / 5.0 + 32.0));
        return true;
    });
}

PCWSTR GetBatteryFormatted() {
    return GetMetricFormatted(g_batteryFormatted, [](PWSTR b, size_t s) {
        SYSTEM_POWER_STATUS ps;
        if (!GetSystemPowerStatus(&ps)) return false;
        if (ps.ACLineStatus == 1) {
            if (ps.BatteryLifePercent != 255) swprintf_s(b, s, L"%d%%⚡", ps.BatteryLifePercent);
            else swprintf_s(b, s, L"⚡");
            return true;
        }
        if (ps.BatteryLifePercent != 255) {
            if (ps.BatteryLifePercent <= 20) swprintf_s(b, s, L"%d%%❗", ps.BatteryLifePercent);
            else swprintf_s(b, s, L"%d%%", ps.BatteryLifePercent);
            return true;
        }
        return false;
    });
}

PCWSTR GetBatteryTimeFormatted() {
    return GetMetricFormatted(g_batteryTimeFormatted, [](PWSTR b, size_t s) {
        DWORD sec = 0;
        SYSTEM_POWER_STATUS ps;
        if (GetSystemPowerStatus(&ps)) {
            if (ps.BatteryLifeTime != (DWORD)-1) {
                sec = ps.BatteryLifeTime;
            } else if (ps.ACLineStatus == 1 && ps.BatteryLifePercent < 100) {
                SYSTEM_BATTERY_STATE bs{};
                if (CallNtPowerInformation(SystemBatteryState, nullptr, 0, &bs, sizeof(bs)) == 0 && bs.Rate > 0) {
                    sec = ((bs.MaxCapacity - bs.RemainingCapacity) * 3600) / bs.Rate;
                }
            }
        }
        swprintf_s(b, s, L"%u:%02u", sec / 3600, (sec % 3600) / 60);
        return true;
    });
}

PCWSTR GetPowerFormatted() {
    return GetMetricFormatted(g_powerFormatted, [](PWSTR b, size_t s) {
        SYSTEM_BATTERY_STATE bs{};
        if (CallNtPowerInformation(SystemBatteryState, nullptr, 0, &bs, sizeof(bs)) == 0 && bs.MaxCapacity > 0) {
            DWORD rate = (bs.Rate == 0x80000000) ? 0 : bs.Rate;
            long mw = static_cast<long>(rate);
            swprintf_s(b, s, L"%+ldW", (mw + (mw >= 0 ? 500 : -500)) / 1000);
            return true;
        }
        return false;
    });
}

PCWSTR GetVolumeFormatted() {
    static int s_lastVol = -1;
    static BOOL s_lastMuted = FALSE;
    static ULONGLONG s_showUntil = 0;

    if (g_volumeFormatted.formatIndex != g_formatIndex) {
        wcscpy_s(g_volumeFormatted.buffer, L"🔊");
        IMMDeviceEnumerator* en = nullptr;
        if (SUCCEEDED(CoCreateInstance(__uuidof(MMDeviceEnumerator), nullptr, CLSCTX_INPROC_SERVER, __uuidof(IMMDeviceEnumerator), (void**)&en))) {
            IMMDevice* dev = nullptr;
            if (SUCCEEDED(en->GetDefaultAudioEndpoint(eRender, eConsole, &dev))) {
                IAudioEndpointVolume* ep = nullptr;
                if (SUCCEEDED(dev->Activate(__uuidof(IAudioEndpointVolume), CLSCTX_INPROC_SERVER, nullptr, (void**)&ep))) {
                    BOOL muted = FALSE;
                    float vol = 0.0f;
                    ep->GetMute(&muted);
                    ep->GetMasterVolumeLevelScalar(&vol);
                    int pct = (int)((vol * 100.0f) + 0.5f);
                    ULONGLONG now = GetTickCount64();

                    if (s_lastVol == -1) {
                        s_lastVol = pct;
                        s_lastMuted = muted;
                    } else if (s_lastVol != pct || s_lastMuted != muted) {
                        s_lastVol = pct;
                        s_lastMuted = muted;
                        s_showUntil = now + 3000;
                    }

                    PCWSTR icon = muted ? L"🔇" : L"🔊";
                    if (now < s_showUntil) swprintf_s(g_volumeFormatted.buffer, L"%s %d%%", icon, pct);
                    else swprintf_s(g_volumeFormatted.buffer, L"%s", icon);

                    ep->Release();
                }
                dev->Release();
            }
            en->Release();
        }
        g_volumeFormatted.formatIndex = g_formatIndex;
    }
    return g_volumeFormatted.buffer;
}

bool IsMicrophoneInUse() {
    static const PCWSTR paths[] = {
        L"Software\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\microphone",
        L"Software\\Microsoft\\Windows\\CurrentVersion\\CapabilityAccessManager\\ConsentStore\\microphone\\NonPackaged"
    };
    for (PCWSTR p : paths) {
        HKEY hBase;
        if (RegOpenKeyExW(HKEY_CURRENT_USER, p, 0, KEY_READ, &hBase) == ERROR_SUCCESS) {
            DWORD idx = 0;
            WCHAR sub[256];
            DWORD subLen = ARRAYSIZE(sub);
            while (RegEnumKeyExW(hBase, idx++, sub, &subLen, nullptr, nullptr, nullptr, nullptr) == ERROR_SUCCESS) {
                HKEY hSub;
                if (RegOpenKeyExW(hBase, sub, 0, KEY_READ, &hSub) == ERROR_SUCCESS) {
                    ULONGLONG st = 0;
                    DWORD sz = sizeof(st), tp = 0;
                    LONG r = RegQueryValueExW(hSub, L"LastUsedTimeStop", nullptr, &tp, (LPBYTE)&st, &sz);
                    RegCloseKey(hSub);
                    if (r == ERROR_SUCCESS && st == 0) { RegCloseKey(hBase); return true; }
                }
                subLen = ARRAYSIZE(sub);
            }
            RegCloseKey(hBase);
        }
    }
    return false;
}

PCWSTR GetMicFormatted() {
    if (g_micFormatted.formatIndex != g_formatIndex) {
        wcscpy_s(g_micFormatted.buffer, IsMicrophoneInUse() ? L"🎙️" : L"");
        g_micFormatted.formatIndex = g_formatIndex;
    }
    return g_micFormatted.buffer;
}

void RefreshMediaDataIfDirty() { if (g_mediaDataDirty) RefreshMediaData(); }
PCWSTR GetMediaTitleFormatted() { RefreshMediaDataIfDirty(); return g_mediaTitleFormatted.buffer; }
PCWSTR GetMediaArtistFormatted() { RefreshMediaDataIfDirty(); return g_mediaArtistFormatted.buffer; }
PCWSTR GetMediaAlbumFormatted() { RefreshMediaDataIfDirty(); return g_mediaAlbumFormatted.buffer; }
PCWSTR GetMediaStatusFormatted() { RefreshMediaDataIfDirty(); return g_mediaStatusFormatted.buffer; }

int FormatLineNoLock(PWSTR buffer, size_t bufferSize, std::wstring_view format);

PCWSTR GetMediaInfoFormatted() {
    RefreshMediaDataIfDirty();
    if (g_inMediaInfoFormat) return L"";
    if (g_mediaInfoFormatted.formatIndex != g_formatIndex) {
        PCWSTR fmt = g_mediaActive ? g_settings.mediaPlayer.mediaInfoFormat.get() : g_settings.mediaPlayer.noMediaText.get();
        int maxLen = ARRAYSIZE(g_mediaInfoFormatted.buffer) - 1;
        if (g_settings.mediaPlayer.maxLength > 0 && g_settings.mediaPlayer.maxLength < maxLen) {
            maxLen = g_settings.mediaPlayer.maxLength;
        }
        g_inMediaInfoFormat = true;
        FormatLineNoLock(g_mediaInfoFormatted.buffer, maxLen + 1, fmt);
        g_inMediaInfoFormat = false;
        g_mediaInfoFormatted.formatIndex = g_formatIndex;
    }
    return g_mediaInfoFormatted.buffer;
}

int ResolveFormatTokenWithDigit(std::wstring_view format, std::wstring_view prefix, std::wstring_view suffix) {
    if (format.size() < prefix.size() + 1 + suffix.size() || !format.starts_with(prefix)) return 0;
    WCHAR d = format[prefix.size()];
    if (d < L'1' || d > L'9' || !format.substr(prefix.size() + 1).starts_with(suffix)) return 0;
    return d - L'0';
}

size_t ResolveFormatToken(std::wstring_view format, std::function<void(PCWSTR)> callback) {
    struct { std::wstring_view tok; PCWSTR (*get)(); } tokens[] = {
        {L"%time%"sv, GetTimeFormatted}, {L"%date%"sv, GetDateFormatted},
        {L"%weekday%"sv, GetWeekdayFormatted}, {L"%weekday_num%"sv, GetWeekdayNumFormatted},
        {L"%weeknum%"sv, GetWeeknumFormatted}, {L"%weeknum_iso%"sv, GetWeeknumIsoFormatted},
        {L"%dayofyear%"sv, GetDayOfYearFormatted}, {L"%timezone%"sv, GetTimezoneFormatted},
        {L"%upload_speed%"sv, GetUploadSpeedFormatted}, {L"%download_speed%"sv, GetDownloadSpeedFormatted},
        {L"%total_speed%"sv, GetTotalSpeedFormatted}, {L"%disk_read%"sv, GetDiskReadSpeedFormatted},
        {L"%disk_write%"sv, GetDiskWriteSpeedFormatted}, {L"%disk_total%"sv, GetDiskTotalSpeedFormatted},
        {L"%cpu%"sv, GetCpuFormatted}, {L"%ram%"sv, GetRamFormatted},
        {L"%ram_used%"sv, GetRamUsedFormatted}, {L"%ram_total%"sv, GetRamTotalFormatted},
        {L"%ram_committed%"sv, GetRamCommittedFormatted}, {L"%ram_committed_used%"sv, GetRamCommittedUsedFormatted},
        {L"%ram_committed_total%"sv, GetRamCommittedTotalFormatted}, {L"%gpu%"sv, GetGpuFormatted},
        {L"%vram%"sv, GetVramFormatted}, {L"%vram_used%"sv, GetVramUsedFormatted},
        {L"%vram_total%"sv, GetVramTotalFormatted}, {L"%vram_shared%"sv, GetVramSharedFormatted},
        {L"%vram_shared_used%"sv, GetVramSharedUsedFormatted}, {L"%vram_shared_total%"sv, GetVramSharedTotalFormatted},
        {L"%cpu_temp%"sv, GetCpuTempFormatted}, {L"%cpu_temp_f%"sv, GetCpuTempFFormatted},
        {L"%battery%"sv, GetBatteryFormatted}, {L"%battery_time%"sv, GetBatteryTimeFormatted},
        {L"%power%"sv, GetPowerFormatted}, {L"%volume%"sv, GetVolumeFormatted},
        {L"%mic%"sv, GetMicFormatted}, {L"%media_title%"sv, GetMediaTitleFormatted},
        {L"%media_artist%"sv, GetMediaArtistFormatted}, {L"%media_album%"sv, GetMediaAlbumFormatted},
        {L"%media_status%"sv, GetMediaStatusFormatted}, {L"%media_info%"sv, GetMediaInfoFormatted},
        {L"%newline%"sv, []() { return L"\n"; }}, {L"%n%"sv, []() { return L"\n"; }},
    };

    for (const auto& t : tokens) {
        if (format.starts_with(t.tok)) {
            callback(t.get());
            return t.tok.size();
        }
    }

    struct { std::wstring_view pre; PCWSTR (*get)(size_t); } tzTokens[] = {
        {L"%time_tz"sv, GetTimeFormattedTz}, {L"%date_tz"sv, GetDateFormattedTz}, {L"%weekday_tz"sv, GetWeekdayFormattedTz},
    };
    for (auto& t : tzTokens) {
        if (int d = ResolveFormatTokenWithDigit(format, t.pre, L"%"sv)) {
            PCWSTR val = t.get(d - 1);
            callback(val ? val : L"-");
            return t.pre.size() + 2;
        }
    }

    if (format.starts_with(L"%web%"sv)) {
        std::lock_guard<std::mutex> g(g_webContentMutex);
        callback(*g_webContent ? g_webContent : L"Loading...");
        return 5;
    }
    if (format.starts_with(L"%web_full%"sv)) {
        std::lock_guard<std::mutex> g(g_webContentMutex);
        callback(*g_webContentFull ? g_webContentFull : L"Loading...");
        return 10;
    }

    struct { std::wstring_view pre; std::vector<std::wstring>* (*get)(); } extraTokens[] = {
        {L"%time"sv, GetTimeFormattedExtra}, {L"%date"sv, GetDateFormattedExtra},
    };
    for (auto& t : extraTokens) {
        if (int d = ResolveFormatTokenWithDigit(format, t.pre, L"%"sv)) {
            const auto& vec = *t.get();
            callback((d < 2 || static_cast<size_t>(d - 2) >= vec.size()) ? L"-" : vec[d - 2].c_str());
            return t.pre.size() + 2;
        }
    }

    if (int d = ResolveFormatTokenWithDigit(format, L"%web"sv, L"%"sv)) {
        std::lock_guard<std::mutex> g(g_webContentMutex);
        size_t idx = d - 1;
        callback((idx >= g_webContentStrings.size()) ? L"-" : (!g_webContentStrings[idx] ? L"Loading..." : g_webContentStrings[idx]->c_str()));
        return 6;
    }
    if (int d = ResolveFormatTokenWithDigit(format, L"%web"sv, L"_full%"sv)) {
        std::lock_guard<std::mutex> g(g_webContentMutex);
        size_t idx = d - 1;
        callback((idx >= g_webContentStringsFull.size()) ? L"-" : (!g_webContentStringsFull[idx] ? L"Loading..." : g_webContentStringsFull[idx]->c_str()));
        return 11;
    }
    if (format.starts_with(L"%weather%"sv)) {
        std::lock_guard<std::mutex> g(g_webContentMutex);
        callback(g_webContentWeather ? g_webContentWeather->c_str() : L"Loading...");
        return 9;
    }
    return 0;
}

void EnsureFormattingInitialized() {
    if (g_formattingInitialized) return;
    g_formattingInitialized = true;
    WebContentUpdateThreadInit();
    DataCollectionSessionInit();
    MediaSessionInit();
}

int FormatLineNoLock(PWSTR buffer, size_t bufferSize, std::wstring_view format) {
    if (bufferSize == 0) return 0;
    std::wstring_view suffix = format;
    PWSTR start = buffer;
    PWSTR end = start + bufferSize;

    while (!suffix.empty() && end - buffer > 1) {
        if (suffix[0] == L'%') {
            bool trunc = false;
            size_t len = ResolveFormatToken(suffix, [&buffer, end, &trunc](PCWSTR str) {
                buffer += StringCopyTruncated(buffer, end - buffer, str, &trunc);
            });
            if (len > 0) {
                if (trunc) break;
                suffix = suffix.substr(len);
                continue;
            }
        }
        *buffer++ = suffix[0];
        suffix = suffix.substr(1);
    }
    if (!suffix.empty() && bufferSize >= 4) {
        buffer[-1] = L'.'; buffer[-2] = L'.'; buffer[-3] = L'.';
    }
    *buffer = L'\0';
    return buffer - start;
}

int FormatLine(PWSTR buffer, size_t bufferSize, std::wstring_view format) {
    if (bufferSize == 0) return 0;
    std::lock_guard<std::mutex> guard(g_formatLineMutex);
    EnsureFormattingInitialized();
    return FormatLineNoLock(buffer, bufferSize, format);
}

// ------------------------------------------
// TASKBAR XAML & CLOCK HOOKS
// ------------------------------------------

DWORD g_refreshIconThreadId;
bool g_refreshIconNeedToAdjustTimer;
bool g_inGetTimeToolTipString;

using ClockSystemTrayIconDataModel_RefreshIcon_t = void(WINAPI*)(LPVOID, LPVOID);
ClockSystemTrayIconDataModel_RefreshIcon_t ClockSystemTrayIconDataModel_RefreshIcon_Original;
ClockSystemTrayIconDataModel_RefreshIcon_t ClockSystemTrayIconDataModel2_RefreshIcon_Original;
using ClockSystemTrayIconDataModel_GetTimeToolTipString_t = LPVOID(WINAPI*)(LPVOID, LPVOID, LPVOID, LPVOID, LPVOID);
ClockSystemTrayIconDataModel_GetTimeToolTipString_t ClockSystemTrayIconDataModel_GetTimeToolTipString_Original;
ClockSystemTrayIconDataModel_GetTimeToolTipString_t ClockSystemTrayIconDataModel2_GetTimeToolTipString_Original;
using ClockSystemTrayIconDataModel_GetTimeToolTipString2_t = LPVOID(WINAPI*)(LPVOID, LPVOID, LPVOID, LPVOID, LPVOID);
ClockSystemTrayIconDataModel_GetTimeToolTipString2_t ClockSystemTrayIconDataModel_GetTimeToolTipString2_Original;
ClockSystemTrayIconDataModel_GetTimeToolTipString2_t ClockSystemTrayIconDataModel2_GetTimeToolTipString2_Original;
using DateTimeIconContent_OnApplyTemplate_t = HRESULT(WINAPI*)(LPVOID);
DateTimeIconContent_OnApplyTemplate_t DateTimeIconContent_OnApplyTemplate_Original;
using BadgeIconContent_get_ViewModel_t = HRESULT(WINAPI*)(LPVOID, LPVOID);
BadgeIconContent_get_ViewModel_t BadgeIconContent_get_ViewModel_Original;
using ClockSystemTrayIconDataModel_GetTimeToolTipString_2_t = LPVOID(WINAPI*)(LPVOID, LPVOID, LPVOID, LPVOID);
ClockSystemTrayIconDataModel_GetTimeToolTipString_2_t ClockSystemTrayIconDataModel_GetTimeToolTipString_2_Original;
using ICalendar_Second_t = int(WINAPI*)(LPVOID);
ICalendar_Second_t ICalendar_Second_Original;
using ThreadPoolTimer_CreateTimer_t = LPVOID(WINAPI*)(LPVOID, LPVOID, LPVOID, LPVOID);
ThreadPoolTimer_CreateTimer_t ThreadPoolTimer_CreateTimer_Original;
using ThreadPoolTimer_CreateTimer_lambda_t = LPVOID(WINAPI*)(DWORD_PTR**, LPVOID, LPVOID);
ThreadPoolTimer_CreateTimer_lambda_t ThreadPoolTimer_CreateTimer_lambda_Original;

void ClockSystemTrayIconDataModel_RefreshIcon_Hook_Impl(LPVOID pThis, LPVOID param1, ClockSystemTrayIconDataModel_RefreshIcon_t orig) {
    {
        std::lock_guard<std::mutex> guard(g_formatLineMutex);
        EnsureFormattingInitialized();
    }
    g_refreshIconThreadId = GetCurrentThreadId();
    g_refreshIconNeedToAdjustTimer = g_settings.showSeconds || g_dataCollectionSession || (g_webContentUpdateThread && !g_webContentLoaded);
    orig(pThis, param1);
    g_refreshIconThreadId = 0;
    g_refreshIconNeedToAdjustTimer = false;
}

void WINAPI ClockSystemTrayIconDataModel_RefreshIcon_Hook(LPVOID pThis, LPVOID p1) {
    ClockSystemTrayIconDataModel_RefreshIcon_Hook_Impl(pThis, p1, ClockSystemTrayIconDataModel_RefreshIcon_Original);
}
void WINAPI ClockSystemTrayIconDataModel2_RefreshIcon_Hook(LPVOID pThis, LPVOID p1) {
    ClockSystemTrayIconDataModel_RefreshIcon_Hook_Impl(pThis, p1, ClockSystemTrayIconDataModel2_RefreshIcon_Original);
}

void UpdateToolTipString(LPVOID tooltipPtrPtr) {
    auto sep = L"\r\n\r\n"sv;
    WCHAR extra[4096];
    size_t len = FormatLine(extra, ARRAYSIZE(extra), g_settings.tooltipLine.get());
    if (len == 0) return;

    struct shared_hstring_header {
        uint32_t flags, length, padding1, padding2;
        wchar_t const* ptr;
        int32_t count;
        wchar_t buffer[1];
    };
    shared_hstring_header* oldH = *(shared_hstring_header**)tooltipPtrPtr;
    uint64_t bytes = sizeof(shared_hstring_header) + sizeof(wchar_t) *
        (g_settings.tooltipLineMode == TooltipLineMode::replace ? len : (oldH->length + sep.length() + len));

    shared_hstring_header* newH = (shared_hstring_header*)HeapReAlloc(GetProcessHeap(), 0, oldH, bytes);
    if (!newH) return;
    newH->ptr = newH->buffer;

    if (g_settings.tooltipLineMode == TooltipLineMode::replace) {
        memcpy(newH->buffer, extra, sizeof(wchar_t) * len);
        newH->length = len;
    } else {
        memcpy(newH->buffer + newH->length, sep.data(), sizeof(wchar_t) * sep.length());
        newH->length += sep.length();
        memcpy(newH->buffer + newH->length, extra, sizeof(wchar_t) * len);
        newH->length += len;
    }
    newH->buffer[newH->length] = L'\0';
    *(shared_hstring_header**)tooltipPtrPtr = newH;
}

LPVOID ClockSystemTrayIconDataModel_GetTimeToolTipString_Hook_Impl(LPVOID pThis, LPVOID p1, LPVOID p2, LPVOID p3, LPVOID p4, ClockSystemTrayIconDataModel_GetTimeToolTipString_t orig) {
    g_inGetTimeToolTipString = true;
    LPVOID ret = orig(pThis, p1, p2, p3, p4);
    UpdateToolTipString(ret);
    g_inGetTimeToolTipString = false;
    return ret;
}

LPVOID WINAPI ClockSystemTrayIconDataModel_GetTimeToolTipString_Hook(LPVOID pThis, LPVOID p1, LPVOID p2, LPVOID p3, LPVOID p4) {
    return ClockSystemTrayIconDataModel_GetTimeToolTipString_Hook_Impl(pThis, p1, p2, p3, p4, ClockSystemTrayIconDataModel_GetTimeToolTipString_Original);
}
LPVOID WINAPI ClockSystemTrayIconDataModel2_GetTimeToolTipString_Hook(LPVOID pThis, LPVOID p1, LPVOID p2, LPVOID p3, LPVOID p4) {
    return ClockSystemTrayIconDataModel_GetTimeToolTipString_Hook_Impl(pThis, p1, p2, p3, p4, ClockSystemTrayIconDataModel2_GetTimeToolTipString_Original);
}

LPVOID ClockSystemTrayIconDataModel_GetTimeToolTipString2_Hook_Impl(LPVOID pThis, LPVOID p1, LPVOID p2, LPVOID p3, LPVOID p4, ClockSystemTrayIconDataModel_GetTimeToolTipString2_t orig) {
    g_inGetTimeToolTipString = true;
    LPVOID ret = orig(pThis, p1, p2, p3, p4);
    UpdateToolTipString(ret);
    g_inGetTimeToolTipString = false;
    return ret;
}

LPVOID WINAPI ClockSystemTrayIconDataModel_GetTimeToolTipString2_Hook(LPVOID pThis, LPVOID p1, LPVOID p2, LPVOID p3, LPVOID p4) {
    return ClockSystemTrayIconDataModel_GetTimeToolTipString2_Hook_Impl(pThis, p1, p2, p3, p4, ClockSystemTrayIconDataModel_GetTimeToolTipString2_Original);
}
LPVOID WINAPI ClockSystemTrayIconDataModel2_GetTimeToolTipString2_Hook(LPVOID pThis, LPVOID p1, LPVOID p2, LPVOID p3, LPVOID p4) {
    return ClockSystemTrayIconDataModel_GetTimeToolTipString2_Hook_Impl(pThis, p1, p2, p3, p4, ClockSystemTrayIconDataModel2_GetTimeToolTipString2_Original);
}

void ApplyTextBlockStyles(Controls::TextBlock textBlock, const TextStyleSettings* s, bool noWrap, std::optional<int64_t>* token) {
    if (token->has_value()) {
        textBlock.UnregisterPropertyChangedCallback(UIElement::VisibilityProperty(), token->value());
    }
    if (s && s->hidden) {
        textBlock.Visibility(Visibility::Collapsed);
        *token = textBlock.RegisterPropertyChangedCallback(
            UIElement::VisibilityProperty(),
            [](DependencyObject sender, DependencyProperty) {
                if (auto tb = sender.try_as<Controls::TextBlock>()) tb.Visibility(Visibility::Collapsed);
            });
        return;
    }
    token->reset();
    textBlock.Visibility(Visibility::Visible);

    if (noWrap) textBlock.TextWrapping(TextWrapping::NoWrap);
    else textBlock.as<DependencyObject>().ClearValue(Controls::TextBlock::TextWrappingProperty());

    if (g_isBatteryLow) {
        textBlock.Foreground(Media::SolidColorBrush(winrt::Windows::UI::Colors::Red()));
    } else if (s && *s->textColor) {
        textBlock.Foreground(Media::SolidColorBrush(winrt::Windows::UI::Colors::White()));
    } else {
        textBlock.ClearValue(Controls::TextBlock::ForegroundProperty());
    }

    if (s && *s->textAlignment) {
        auto a = Markup::XamlBindingHelper::ConvertValue(winrt::xaml_typename<TextAlignment>(), winrt::box_value(s->textAlignment.get())).as<TextAlignment>();
        textBlock.TextAlignment(a);
    } else {
        textBlock.TextAlignment(TextAlignment::End);
    }

    if (s && s->fontSize) textBlock.FontSize(s->fontSize);
    else textBlock.as<DependencyObject>().ClearValue(Controls::TextBlock::FontSizeProperty());

    if (s && *s->fontFamily) {
        auto f = Markup::XamlBindingHelper::ConvertValue(winrt::xaml_typename<Media::FontFamily>(), winrt::box_value(s->fontFamily.get())).as<Media::FontFamily>();
        textBlock.FontFamily(f);
    } else {
        textBlock.as<DependencyObject>().ClearValue(Controls::TextBlock::FontFamilyProperty());
    }

    if (s && *s->fontWeight) {
        auto w = Markup::XamlBindingHelper::ConvertValue(winrt::xaml_typename<winrt::Windows::UI::Text::FontWeight>(), winrt::box_value(s->fontWeight.get())).as<winrt::Windows::UI::Text::FontWeight>();
        textBlock.FontWeight(w);
    } else {
        textBlock.as<DependencyObject>().ClearValue(Controls::TextBlock::FontWeightProperty());
    }

    if (s && *s->fontStyle) {
        auto st = Markup::XamlBindingHelper::ConvertValue(winrt::xaml_typename<winrt::Windows::UI::Text::FontStyle>(), winrt::box_value(s->fontStyle.get())).as<winrt::Windows::UI::Text::FontStyle>();
        textBlock.FontStyle(st);
    } else {
        textBlock.as<DependencyObject>().ClearValue(Controls::TextBlock::FontStyleProperty());
    }

    if (s && *s->fontStretch) {
        auto str = Markup::XamlBindingHelper::ConvertValue(winrt::xaml_typename<winrt::Windows::UI::Text::FontStretch>(), winrt::box_value(s->fontStretch.get())).as<winrt::Windows::UI::Text::FontStretch>();
        textBlock.FontStretch(str);
    } else {
        textBlock.as<DependencyObject>().ClearValue(Controls::TextBlock::FontStretchProperty());
    }

    if (s && s->characterSpacing) textBlock.CharacterSpacing(s->characterSpacing);
    else textBlock.as<DependencyObject>().ClearValue(Controls::TextBlock::CharacterSpacingProperty());

    if (s && s->lineHeight) {
        textBlock.LineHeight(s->lineHeight);
        textBlock.LineStackingStrategy(LineStackingStrategy::BlockLineHeight);
    } else {
        textBlock.as<DependencyObject>().ClearValue(Controls::TextBlock::LineHeightProperty());
        textBlock.as<DependencyObject>().ClearValue(Controls::TextBlock::LineStackingStrategyProperty());
    }
}

void ApplyDateTimeIconContentStyles(FrameworkElement dateTimeIconContentElement) {
    ClockElementStyleData* dataPtr = nullptr;
    for (auto it = g_clockElementStyleData.begin(); it != g_clockElementStyleData.end();) {
        auto elem = it->dateTimeIconContentElement.get();
        if (!elem) { it = g_clockElementStyleData.erase(it); continue; }
        if (elem == dateTimeIconContentElement) { dataPtr = &(*it); break; }
        ++it;
    }

    bool enabled = g_clockElementStyleEnabled;
    DWORD curIdx = g_clockElementStyleIndex;
    if (!dataPtr && !enabled) return;
    if (dataPtr && dataPtr->styleIndex == curIdx) return;

    auto grid = FindChildByName(dateTimeIconContentElement, L"ContainerGrid").as<Controls::Grid>();
    if (!grid) return;
    auto sp = grid.Children().GetAt(0).as<Controls::StackPanel>();
    Controls::TextBlock dTb = nullptr, tTb = nullptr;

    for (const auto& ch : sp.Children()) {
        auto tb = ch.try_as<Controls::TextBlock>();
        if (!tb) continue;
        if (tb.Name() == L"DateInnerTextBlock") dTb = tb;
        else if (tb.Name() == L"TimeInnerTextBlock") tTb = tb;
    }
    if (!dTb || !tTb) return;

    if (!dataPtr) {
        g_clockElementStyleData.push_back({winrt::make_weak(dateTimeIconContentElement)});
        dataPtr = &g_clockElementStyleData.back();
    }

    int maxW = enabled ? g_settings.maxWidth : 0;
    int spacing = enabled ? g_settings.textSpacing : 0;
    if (maxW) sp.MaxWidth(maxW); else sp.as<DependencyObject>().ClearValue(FrameworkElement::MaxWidthProperty());
    if (spacing) sp.Spacing(spacing); else sp.as<DependencyObject>().ClearValue(Controls::StackPanel::SpacingProperty());

    ApplyTextBlockStyles(dTb, enabled ? &g_settings.dateStyle : nullptr, maxW, &dataPtr->dateVisibilityPropertyChangedToken);
    ApplyTextBlockStyles(tTb, enabled ? &g_settings.timeStyle : nullptr, maxW, &dataPtr->timeVisibilityPropertyChangedToken);
    dataPtr->styleIndex = curIdx;
}

HRESULT WINAPI DateTimeIconContent_OnApplyTemplate_Hook(LPVOID pThis) {
    HRESULT ret = DateTimeIconContent_OnApplyTemplate_Original(pThis);
    FrameworkElement content = nullptr;
    ((IUnknown*)pThis)->QueryInterface(winrt::guid_of<FrameworkElement>(), winrt::put_abi(content));
    if (content) {
        try { ApplyDateTimeIconContentStyles(content); } catch (...) {}
    }
    return ret;
}

HRESULT WINAPI BadgeIconContent_get_ViewModel_Hook(LPVOID pThis, LPVOID pArgs) {
    HRESULT ret = BadgeIconContent_get_ViewModel_Original(pThis, pArgs);
    try {
        winrt::Windows::Foundation::IInspectable obj = nullptr;
        if (SUCCEEDED(((IUnknown*)pThis)->QueryInterface(winrt::guid_of<winrt::Windows::Foundation::IInspectable>(), winrt::put_abi(obj)))) {
            if (winrt::get_class_name(obj) == L"SystemTray.DateTimeIconContent") {
                auto elem = obj.as<FrameworkElement>();
                if (elem.IsLoaded()) ApplyDateTimeIconContentStyles(elem);
            }
        }
    } catch (...) {}
    return ret;
}

LPVOID WINAPI ClockSystemTrayIconDataModel_GetTimeToolTipString_2_Hook(LPVOID pThis, LPVOID p1, LPVOID p2, LPVOID p3) {
    g_inGetTimeToolTipString = true;
    LPVOID ret = ClockSystemTrayIconDataModel_GetTimeToolTipString_2_Original(pThis, p1, p2, p3);
    UpdateToolTipString(ret);
    g_inGetTimeToolTipString = false;
    return ret;
}

int WINAPI ICalendar_Second_Hook(LPVOID pThis) {
    if (g_refreshIconThreadId == GetCurrentThreadId() && !g_inGetTimeToolTipString && g_refreshIconNeedToAdjustTimer) {
        g_refreshIconNeedToAdjustTimer = false;
        return 59;
    }
    return ICalendar_Second_Original(pThis);
}

LPVOID WINAPI ThreadPoolTimer_CreateTimer_Hook(LPVOID p1, LPVOID p2, LPVOID p3, LPVOID p4) {
    ULONGLONG** elapse = (ULONGLONG**)(g_winVersion >= WinVersion::Win11_22H2 ? &p3 : &p4);
    ULONGLONG elapseNew;
    if (g_refreshIconThreadId == GetCurrentThreadId() && !g_inGetTimeToolTipString && **elapse == 10000000) {
        SYSTEMTIME t;
        if (GetLocalTime_Original) GetLocalTime_Original(&t); else GetLocalTime(&t);
        elapseNew = 10000ULL * (1000 - t.wMilliseconds);
        *elapse = &elapseNew;
    }
    return ThreadPoolTimer_CreateTimer_Original(p1, p2, p3, p4);
}

LPVOID WINAPI ThreadPoolTimer_CreateTimer_lambda_Hook(DWORD_PTR** p1, LPVOID p2, LPVOID p3) {
    DWORD_PTR* elapse = p1[1];
    if (g_refreshIconThreadId == GetCurrentThreadId() && !g_inGetTimeToolTipString && *elapse == 10000000) {
        SYSTEMTIME t;
        if (GetLocalTime_Original) GetLocalTime_Original(&t); else GetLocalTime(&t);
        *elapse = 10000ULL * (1000 - t.wMilliseconds);
    }
    return ThreadPoolTimer_CreateTimer_lambda_Original(p1, p2, p3);
}

VOID WINAPI GetLocalTime_Hook_Win11(LPSYSTEMTIME lpSystemTime) {
    if (g_refreshIconThreadId == GetCurrentThreadId() && !g_inGetTimeToolTipString && g_refreshIconNeedToAdjustTimer) {
        g_refreshIconNeedToAdjustTimer = false;
        memset(lpSystemTime, 0, sizeof(*lpSystemTime));
        lpSystemTime->wSecond = 59;
        return;
    }
    GetLocalTime_Original(lpSystemTime);
}

int WINAPI GetTimeFormatEx_Hook_Win11(LPCWSTR loc, DWORD fl, CONST SYSTEMTIME* t, LPCWSTR fmt, LPWSTR str, int cch) {
    if (g_refreshIconThreadId == GetCurrentThreadId() && !g_inGetTimeToolTipString) {
        if (wcscmp(g_settings.topLine, L"-") != 0) {
            if (!cch) return FORMATTED_BUFFER_SIZE;
            return FormatLine(str, cch, g_settings.topLine.get()) + 1;
        }
    }
    return GetTimeFormatEx_Original(loc, fl, t, fmt, str, cch);
}

int WINAPI GetDateFormatEx_Hook_Win11(LPCWSTR loc, DWORD fl, CONST SYSTEMTIME* dt, LPCWSTR fmt, LPWSTR str, int cch, LPCWSTR cal) {
    if (g_refreshIconThreadId == GetCurrentThreadId() && !g_inGetTimeToolTipString) {
        SYSTEMTIME sent;
        memset(&sent, 0, sizeof(sent));
        sent.wSecond = 59;
        if (memcmp(dt, &sent, sizeof(sent)) == 0) {
            if (GetLocalTime_Original) GetLocalTime_Original(const_cast<SYSTEMTIME*>(dt));
            else GetLocalTime(const_cast<SYSTEMTIME*>(dt));
        }
        if (!(fl & DATE_LONGDATE)) {
            if (!cch || g_winVersion >= WinVersion::Win11_22H2) {
                g_formatTime = *dt;
                g_formatIndex++;
            }
            if (wcscmp(g_settings.bottomLine, L"-") != 0) {
                if (!cch) return FORMATTED_BUFFER_SIZE;
                return FormatLine(str, cch, g_settings.bottomLine.get()) + 1;
            }
        }
    }
    return GetDateFormatEx_Original(loc, fl, dt, fmt, str, cch, cal);
}

LRESULT WINAPI SendMessageW_Hook(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
    LRESULT ret = SendMessageW_Original(hWnd, Msg, wParam, lParam);
    if (Msg == WM_POWERBROADCAST && wParam == PBT_APMQUERYSUSPEND) {
        switch (lParam) {
            case PBT_APMRESUMECRITICAL: case PBT_APMRESUMESUSPEND: case PBT_APMRESUMEAUTOMATIC: {
                WCHAR cls[64];
                if (GetClassName(hWnd, cls, ARRAYSIZE(cls)) && _wcsicmp(cls, L"MSTaskSwWClass") == 0) {
                    std::lock_guard<std::mutex> g(g_webContentMutex);
                    if (g_webContentUpdateRefreshEvent) {
                        g_webContentLoaded = false;
                        SetEvent(g_webContentUpdateRefreshEvent);
                    }
                }
                break;
            }
            default: break;
        }
    }
    return ret;
}

// ------------------------------------------
// WIN10 & EXPLORER PATCHER HOOKS
// ------------------------------------------

DWORD g_updateTextStringThreadId;
int g_getDateFormatExCounter;
DWORD g_getTooltipTextThreadId;
WCHAR* g_getTooltipTextBuffer;
int g_getTooltipTextBufferSize;

using ClockButton_UpdateTextStringsIfNecessary_t = unsigned int(WINAPI*)(LPVOID, bool*);
ClockButton_UpdateTextStringsIfNecessary_t ClockButton_UpdateTextStringsIfNecessary_Original;
using ClockButton_CalculateMinimumSize_t = LPSIZE(WINAPI*)(LPVOID, LPSIZE, SIZE);
ClockButton_CalculateMinimumSize_t ClockButton_CalculateMinimumSize_Original;
using ClockButton_GetTextSpacingForOrientation_t = int(WINAPI*)(LPVOID, bool, DWORD, DWORD, DWORD, DWORD);
ClockButton_GetTextSpacingForOrientation_t ClockButton_GetTextSpacingForOrientation_Original;
using ClockButton_v_GetTooltipText_t = HRESULT(WINAPI*)(LPVOID, LPVOID, LPVOID, LPVOID, LPVOID);
ClockButton_v_GetTooltipText_t ClockButton_v_GetTooltipText_Original;
using ClockButton_v_OnDisplayStateChange_t = void(WINAPI*)(LPVOID, bool);
ClockButton_v_OnDisplayStateChange_t ClockButton_v_OnDisplayStateChange_Original;

HRESULT WINAPI ClockButton_v_GetTooltipText_Hook(LPVOID pThis, LPVOID p1, LPVOID p2, LPVOID p3, LPVOID p4) {
    g_getTooltipTextThreadId = GetCurrentThreadId();
    HRESULT ret = ClockButton_v_GetTooltipText_Original(pThis, p1, p2, p3, p4);
    if (g_getTooltipTextBuffer) {
        if (g_settings.tooltipLineMode == TooltipLineMode::replace) {
            FormatLine(g_getTooltipTextBuffer, g_getTooltipTextBufferSize, g_settings.tooltipLine.get());
        } else {
            size_t slen = wcslen(g_getTooltipTextBuffer);
            WCHAR* p = g_getTooltipTextBuffer + slen;
            size_t rem = g_getTooltipTextBufferSize - slen;
            if (rem > 4) {
                wcscpy(p, L"\r\n\r\n");
                FormatLine(p + 4, rem - 4, g_settings.tooltipLine.get());
            }
        }
    }
    g_getTooltipTextBuffer = nullptr;
    g_getTooltipTextBufferSize = 0;
    g_getTooltipTextThreadId = 0;
    return ret;
}

unsigned int WINAPI ClockButton_UpdateTextStringsIfNecessary_Hook(LPVOID pThis, bool* p1) {
    g_updateTextStringThreadId = GetCurrentThreadId();
    g_getDateFormatExCounter = 0;
    unsigned int ret = ClockButton_UpdateTextStringsIfNecessary_Original(pThis, p1);
    g_updateTextStringThreadId = 0;

    if (g_settings.showSeconds || g_dataCollectionSession || (g_webContentUpdateThread && !g_webContentLoaded)) {
        SYSTEMTIME t;
        GetLocalTime(&t);
        return 1000 - t.wMilliseconds;
    }
    return ret;
}

LPSIZE WINAPI ClockButton_CalculateMinimumSize_Hook(LPVOID pThis, LPSIZE p1, SIZE p2) {
    LPSIZE ret = ClockButton_CalculateMinimumSize_Original(pThis, p1, p2);
    HWND hWnd = *((HWND*)pThis + 1);
    UINT dpi = pGetDpiForWindow ? pGetDpiForWindow(hWnd) : 0;
    if (g_settings.width > 0) {
        ret->cx = g_settings.width;
        if (dpi) ret->cx = MulDiv(ret->cx, dpi, 96);
    }
    if (g_settings.height > 0) {
        ret->cy = g_settings.height;
        if (dpi) ret->cy = MulDiv(ret->cy, dpi, 96);
    }
    return ret;
}

int WINAPI ClockButton_GetTextSpacingForOrientation_Hook(LPVOID pThis, bool h, DWORD sh, DWORD l1, DWORD l2, DWORD l3) {
    int sp = g_settings.textSpacing;
    if (sp == 0) return ClockButton_GetTextSpacingForOrientation_Original(pThis, h, sh, l1, l2, l3);
    if (l3 == 0 && l2 == 0) return 0;
    if (sp < 0) sp++;
    HWND hWnd = *((HWND*)pThis + 1);
    UINT dpi = pGetDpiForWindow ? pGetDpiForWindow(hWnd) : 0;
    return dpi ? MulDiv(sp, dpi, 96) : sp;
}

int WINAPI GetTimeFormatEx_Hook_Win10(LPCWSTR loc, DWORD fl, CONST SYSTEMTIME* t, LPCWSTR fmt, LPWSTR str, int cch) {
    if (g_updateTextStringThreadId == GetCurrentThreadId()) {
        g_formatTime = *t;
        g_formatIndex++;
        if (wcscmp(g_settings.topLine, L"-") != 0) {
            return FormatLine(str, cch, g_settings.topLine.get()) + 1;
        }
    }
    return GetTimeFormatEx_Original(loc, fl, t, fmt, str, cch);
}

int WINAPI GetDateFormatEx_Hook_Win10(LPCWSTR loc, DWORD fl, CONST SYSTEMTIME* dt, LPCWSTR fmt, LPWSTR str, int cch, LPCWSTR cal) {
    if (g_updateTextStringThreadId == GetCurrentThreadId()) {
        g_getDateFormatExCounter++;
        PCWSTR f = (g_getDateFormatExCounter > 1) ? g_settings.middleLine : g_settings.bottomLine;
        if (wcscmp(f, L"-") != 0) {
            return FormatLine(str, cch, f) + 1;
        }
    }
    return GetDateFormatEx_Original(loc, fl, dt, fmt, str, cch, cal);
}

int WINAPI GetDateFormatW_Hook_Win10(LCID loc, DWORD fl, CONST SYSTEMTIME* dt, LPCWSTR fmt, LPWSTR str, int cch) {
    if (g_getTooltipTextThreadId == GetCurrentThreadId() && !g_getTooltipTextBuffer) {
        g_getTooltipTextBuffer = str;
        g_getTooltipTextBufferSize = cch;
    }
    return GetDateFormatW_Original(loc, fl, dt, fmt, str, cch);
}

WinVersion GetExplorerVersion() {
    VS_FIXEDFILEINFO* info = GetModuleVersionInfo(nullptr, nullptr);
    if (!info) return WinVersion::Unsupported;
    WORD build = HIWORD(info->dwFileVersionLS);
    if (HIWORD(info->dwFileVersionMS) == 10) {
        if (build < 22000) return WinVersion::Win10;
        if (build <= 22000) return WinVersion::Win11;
        if (build < 26100) return WinVersion::Win11_22H2;
        return WinVersion::Win11_24H2;
    }
    return WinVersion::Unsupported;
}

struct EXPLORER_PATCHER_HOOK {
    PCSTR symbol;
    void** pOriginalFunction;
    void* hookFunction = nullptr;
    bool optional = false;

    template <typename Prototype>
    EXPLORER_PATCHER_HOOK(PCSTR sym, Prototype** orig, std::type_identity_t<Prototype*> hook = nullptr, bool opt = false)
        : symbol(sym), pOriginalFunction(reinterpret_cast<void**>(orig)), hookFunction(reinterpret_cast<void*>(hook)), optional(opt) {}
};

bool HookExplorerPatcherSymbols(HMODULE explorerPatcherModule) {
    if (g_explorerPatcherInitialized.exchange(true)) return true;
    if (g_winVersion >= WinVersion::Win11) g_winVersion = WinVersion::Win10;

    EXPLORER_PATCHER_HOOK hooks[] = {
        {R"(?UpdateTextStringsIfNecessary@ClockButton@@AEAAIPEA_N@Z)", &ClockButton_UpdateTextStringsIfNecessary_Original, ClockButton_UpdateTextStringsIfNecessary_Hook},
        {R"(?CalculateMinimumSize@ClockButton@@QEAA?AUtagSIZE@@U2@@Z)", &ClockButton_CalculateMinimumSize_Original, ClockButton_CalculateMinimumSize_Hook},
        {R"(?GetTextSpacingForOrientation@ClockButton@@AEAAH_NHHHH@Z)", &ClockButton_GetTextSpacingForOrientation_Original, ClockButton_GetTextSpacingForOrientation_Hook},
        {R"(?v_GetTooltipText@ClockButton@@MEAAJPEAPEAUHINSTANCE__@@PEAPEAGPEAG_K@Z)", &ClockButton_v_GetTooltipText_Original, ClockButton_v_GetTooltipText_Hook, true},
        {R"(?v_OnDisplayStateChange@ClockButton@@MEAAX_N@Z)", &ClockButton_v_OnDisplayStateChange_Original},
    };

    bool ok = true;
    for (const auto& h : hooks) {
        void* ptr = (void*)GetProcAddress(explorerPatcherModule, h.symbol);
        if (!ptr) {
            if (!h.optional) ok = false;
            continue;
        }
        if (h.hookFunction) Wh_SetFunctionHook(ptr, h.hookFunction, h.pOriginalFunction);
        else *h.pOriginalFunction = ptr;
    }
    if (ok && g_initialized) Wh_ApplyHookOperations();
    return ok;
}

bool IsExplorerPatcherModule(HMODULE module) {
    WCHAR path[MAX_PATH];
    if (GetModuleFileName(module, path, ARRAYSIZE(path)) == 0) return false;
    PCWSTR name = wcsrchr(path, L'\\');
    return name && _wcsnicmp(L"ep_taskbar.", name + 1, sizeof("ep_taskbar.") - 1) == 0;
}

bool HandleLoadedExplorerPatcher() {
    HMODULE hMods[1024];
    DWORD needed;
    if (EnumProcessModules(GetCurrentProcess(), hMods, sizeof(hMods), &needed)) {
        for (size_t i = 0; i < needed / sizeof(HMODULE); i++) {
            if (IsExplorerPatcherModule(hMods[i])) return HookExplorerPatcherSymbols(hMods[i]);
        }
    }
    return true;
}

bool HookWin10TaskbarSymbols() {
    WindhawkUtils::SYMBOL_HOOK hooks[] = {
        {{LR"(private: unsigned int __cdecl ClockButton::UpdateTextStringsIfNecessary(bool *))"}, &ClockButton_UpdateTextStringsIfNecessary_Original, ClockButton_UpdateTextStringsIfNecessary_Hook},
        {{LR"(public: struct tagSIZE __cdecl ClockButton::CalculateMinimumSize(struct tagSIZE))"}, &ClockButton_CalculateMinimumSize_Original, ClockButton_CalculateMinimumSize_Hook},
        {{LR"(private: int __cdecl ClockButton::GetTextSpacingForOrientation(bool,int,int,int,int))"}, &ClockButton_GetTextSpacingForOrientation_Original, ClockButton_GetTextSpacingForOrientation_Hook},
        {{LR"(protected: virtual long __cdecl ClockButton::v_GetTooltipText(struct HINSTANCE__ * *,unsigned short * *,unsigned short *,unsigned __int64))"}, &ClockButton_v_GetTooltipText_Original, ClockButton_v_GetTooltipText_Hook, true},
        {{LR"(protected: virtual void __cdecl ClockButton::v_OnDisplayStateChange(bool))"}, &ClockButton_v_OnDisplayStateChange_Original},
    };
    return HookSymbols(GetModuleHandle(nullptr), hooks, ARRAYSIZE(hooks));
}

// ------------------------------------------
// UNIFIED SYMBOL HOOKING
// ------------------------------------------

bool HookUnifiedSystemTraySymbols(HMODULE module) {
    WindhawkUtils::SYMBOL_HOOK hooks[] = {
        // Tray Tweaks Symbol
        {{LR"(public: __cdecl winrt::SystemTray::implementation::IconView::IconView(void))"}, &IconView_IconView_Original, IconView_IconView_Hook},

        // Clock Customization Symbols
        {{LR"(private: void __cdecl winrt::SystemTray::implementation::ClockSystemTrayIconDataModel::RefreshIcon(class SystemTrayTelemetry::ClockUpdate &))"}, &ClockSystemTrayIconDataModel_RefreshIcon_Original, ClockSystemTrayIconDataModel_RefreshIcon_Hook},
        {{LR"(private: void __cdecl winrt::SystemTray::implementation::ClockSystemTrayIconDataModel2::RefreshIcon(class SystemTrayTelemetry::ClockUpdate &))"}, &ClockSystemTrayIconDataModel2_RefreshIcon_Original, ClockSystemTrayIconDataModel2_RefreshIcon_Hook, true},
        {{LR"(private: struct winrt::hstring __cdecl winrt::SystemTray::implementation::ClockSystemTrayIconDataModel::GetTimeToolTipString(struct _SYSTEMTIME const &,struct _SYSTEMTIME const &,class SystemTrayTelemetry::ClockUpdate &))"}, &ClockSystemTrayIconDataModel_GetTimeToolTipString_Original, ClockSystemTrayIconDataModel_GetTimeToolTipString_Hook, true},
        {{LR"(private: struct winrt::hstring __cdecl winrt::SystemTray::implementation::ClockSystemTrayIconDataModel2::GetTimeToolTipString(struct _SYSTEMTIME const &,struct _SYSTEMTIME const &,class SystemTrayTelemetry::ClockUpdate &))"}, &ClockSystemTrayIconDataModel2_GetTimeToolTipString_Original, ClockSystemTrayIconDataModel2_GetTimeToolTipString_Hook, true},
        {{LR"(private: struct winrt::hstring __cdecl winrt::SystemTray::implementation::ClockSystemTrayIconDataModel::GetTimeToolTipString2(struct _SYSTEMTIME const &,struct _SYSTEMTIME const &,class SystemTrayTelemetry::ClockUpdate &))"}, &ClockSystemTrayIconDataModel_GetTimeToolTipString2_Original, ClockSystemTrayIconDataModel_GetTimeToolTipString2_Hook, true},
        {{LR"(private: struct winrt::hstring __cdecl winrt::SystemTray::implementation::ClockSystemTrayIconDataModel2::GetTimeToolTipString2(struct _SYSTEMTIME const &,struct _SYSTEMTIME const &,class SystemTrayTelemetry::ClockUpdate &))"}, &ClockSystemTrayIconDataModel2_GetTimeToolTipString2_Original, ClockSystemTrayIconDataModel2_GetTimeToolTipString2_Hook, true},
        {{LR"(public: virtual int __cdecl winrt::impl::produce<struct winrt::SystemTray::implementation::DateTimeIconContent,struct winrt::Windows::UI::Xaml::IFrameworkElementOverrides>::OnApplyTemplate(void))"}, &DateTimeIconContent_OnApplyTemplate_Original, DateTimeIconContent_OnApplyTemplate_Hook, true},
        {{LR"(public: virtual int __cdecl winrt::impl::produce<struct winrt::SystemTray::implementation::BadgeIconContent,struct winrt::SystemTray::IBadgeIconContent>::get_ViewModel(void * *))"}, &BadgeIconContent_get_ViewModel_Original, BadgeIconContent_get_ViewModel_Hook, true},
        {{LR"(private: struct winrt::hstring __cdecl winrt::SystemTray::implementation::ClockSystemTrayIconDataModel::GetTimeToolTipString(struct _SYSTEMTIME *,struct _TIME_DYNAMIC_ZONE_INFORMATION *,class SystemTrayTelemetry::ClockUpdate &))"}, &ClockSystemTrayIconDataModel_GetTimeToolTipString_2_Original, ClockSystemTrayIconDataModel_GetTimeToolTipString_2_Hook, true},
        {{LR"(public: int __cdecl winrt::impl::consume_Windows_Globalization_ICalendar<struct winrt::Windows::Globalization::ICalendar>::Second(void)const )"}, &ICalendar_Second_Original, ICalendar_Second_Hook, true},
        {{LR"(public: static __cdecl winrt::Windows::System::Threading::ThreadPoolTimer::CreateTimer(struct winrt::Windows::System::Threading::TimerElapsedHandler const &,class std::chrono::duration<__int64,struct std::ratio<1,10000000> > const &))",
          LR"(public: struct winrt::Windows::System::Threading::ThreadPoolTimer __cdecl winrt::impl::consume_Windows_System_Threading_IThreadPoolTimerStatics<struct winrt::Windows::System::Threading::IThreadPoolTimerStatics>::CreateTimer(struct winrt::Windows::System::Threading::TimerElapsedHandler const &,class std::chrono::duration<__int64,struct std::ratio<1,10000000> > const &)const )"}, &ThreadPoolTimer_CreateTimer_Original, ThreadPoolTimer_CreateTimer_Hook, true},
        {{LR"(public: __cdecl <lambda_b19cf72fe9674443383aa89d5c22450b>::operator()(struct winrt::Windows::System::Threading::IThreadPoolTimerStatics const &)const )",
          LR"(public: struct winrt::Windows::System::Threading::ThreadPoolTimer __cdecl <lambda_b19cf72fe9674443383aa89d5c22450b>::operator()(struct winrt::Windows::System::Threading::IThreadPoolTimerStatics const &)const )"}, &ThreadPoolTimer_CreateTimer_lambda_Original, ThreadPoolTimer_CreateTimer_lambda_Hook, true},
    };

    return HookSymbols(module, hooks, ARRAYSIZE(hooks));
}

HMODULE GetSystemTrayModuleHandle() {
    HMODULE module = GetModuleHandle(L"SystemTray.dll");
    if (!module) {
        module = GetModuleHandle(L"Taskbar.View.dll");
        if (module) {
            VS_FIXEDFILEINFO* fixedFileInfo = GetModuleVersionInfo(module, nullptr);
            WORD moduleMajor = fixedFileInfo ? HIWORD(fixedFileInfo->dwFileVersionMS) : 0;
            if (!moduleMajor || moduleMajor >= 2604) module = nullptr;
        }
    }
    if (!module) module = GetModuleHandle(L"ExplorerExtensions.dll");
    return module;
}

void HandleLoadedModuleIfSystemTray(HMODULE module, LPCWSTR lpLibFileName) {
    if (!g_systemTrayModuleHooked && GetSystemTrayModuleHandle() == module && !g_systemTrayModuleHooked.exchange(true)) {
        if (HookUnifiedSystemTraySymbols(module)) {
            Wh_ApplyHookOperations();
        }
    }
}

using LoadLibraryExW_t = decltype(&LoadLibraryExW);
LoadLibraryExW_t LoadLibraryExW_Original;
HMODULE WINAPI LoadLibraryExW_Hook(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags) {
    HMODULE module = LoadLibraryExW_Original(lpLibFileName, hFile, dwFlags);
    if (module) {
        if (module && !((ULONG_PTR)module & 3) && !g_explorerPatcherInitialized) {
            if (IsExplorerPatcherModule(module)) HookExplorerPatcherSymbols(module);
        }
        HandleLoadedModuleIfSystemTray(module, lpLibFileName);
    }
    return module;
}

// ------------------------------------------
// SETTINGS APPLICATION
// ------------------------------------------

NetworkMetricsFormat ParseNetworkMetricsFormat(PCWSTR value) {
    if (wcscmp(value, L"mbsNumberOnly") == 0) return NetworkMetricsFormat::mbsNumberOnly;
    if (wcscmp(value, L"mbsDynamic") == 0) return NetworkMetricsFormat::mbsDynamic;
    if (wcscmp(value, L"mbits") == 0) return NetworkMetricsFormat::mbits;
    if (wcscmp(value, L"mbitsNumberOnly") == 0) return NetworkMetricsFormat::mbitsNumberOnly;
    if (wcscmp(value, L"mbitsDynamic") == 0) return NetworkMetricsFormat::mbitsDynamic;
    return NetworkMetricsFormat::mbs;
}

void LoadSettings() {
    // Tray settings
    g_settings.hideVolumeIcon = Wh_GetIntSetting(L"hideVolumeIcon");
    g_settings.hideNetworkIcon = Wh_GetIntSetting(L"hideNetworkIcon");
    g_settings.hideBatteryIcon = Wh_GetIntSetting(L"hideBatteryIcon");
    g_settings.grayscaleBatteryIcon = Wh_GetIntSetting(L"grayscaleBatteryIcon");
    g_settings.hideMicrophoneIcon = Wh_GetIntSetting(L"hideMicrophoneIcon");
    g_settings.hideGeolocationIcon = Wh_GetIntSetting(L"hideGeolocationIcon");
    g_settings.hideStudioEffectsIcon = Wh_GetIntSetting(L"hideStudioEffectsIcon");
    g_settings.hideRecallIcon = Wh_GetIntSetting(L"hideRecallIcon");
    g_settings.hideLanguageBar = Wh_GetIntSetting(L"hideLanguageBar");
    g_settings.hideLanguageSupplementaryIcons = Wh_GetIntSetting(L"hideLanguageSupplementaryIcons");

    PCWSTR hideBell = Wh_GetStringSetting(L"hideBellIcon");
    g_settings.hideBellIcon = HideBellIcon::never;
    if (wcscmp(hideBell, L"whenInactive") == 0) g_settings.hideBellIcon = HideBellIcon::whenInactive;
    else if (wcscmp(hideBell, L"whenInactiveAndNoDnd") == 0) g_settings.hideBellIcon = HideBellIcon::whenInactiveAndNoDnd;
    else if (wcscmp(hideBell, L"always") == 0) g_settings.hideBellIcon = HideBellIcon::always;
    Wh_FreeStringSetting(hideBell);

    g_settings.showDesktopButtonWidth = Wh_GetIntSetting(L"showDesktopButtonWidth");

    // Clock settings
    g_settings.showSeconds = Wh_GetIntSetting(L"ShowSeconds");
    g_settings.timeFormat = StringSetting::make(L"TimeFormat");
    g_settings.dateFormat = StringSetting::make(L"DateFormat");
    g_settings.dateLocale = StringSetting::make(L"DateLocale");
    g_settings.weekdayFormat = StringSetting::make(L"WeekdayFormat");

    g_settings.weekdayFormatCustom.clear();
    if (wcscmp(g_settings.weekdayFormat, L"custom") == 0) {
        StringSetting custom = StringSetting::make(L"WeekdayFormatCustom");
        for (const auto name : SplitStringView(custom.get(), L",")) {
            g_settings.weekdayFormatCustom.emplace_back(TrimStringView(name));
        }
        g_settings.weekdayFormatCustom.resize(7);
    }

    g_settings.topLine = StringSetting::make(L"TopLine");
    g_settings.bottomLine = StringSetting::make(L"BottomLine");
    g_settings.middleLine = StringSetting::make(L"MiddleLine");
    g_settings.tooltipLine = StringSetting::make(L"TooltipLine");

    g_settings.tooltipLineMode = TooltipLineMode::append;
    StringSetting tlm = StringSetting::make(L"TooltipLineMode");
    if (wcscmp(tlm, L"replace") == 0) g_settings.tooltipLineMode = TooltipLineMode::replace;

    g_settings.width = Wh_GetIntSetting(L"Width");
    g_settings.height = Wh_GetIntSetting(L"Height");
    g_settings.maxWidth = Wh_GetIntSetting(L"MaxWidth");
    g_settings.textSpacing = Wh_GetIntSetting(L"TextSpacing");

    g_settings.dataCollection.networkMetricsFormat = ParseNetworkMetricsFormat(StringSetting::make(L"DataCollection.NetworkMetricsFormat"));
    g_settings.dataCollection.networkMetricsFixedDecimals = Wh_GetIntSetting(L"DataCollection.NetworkMetricsFixedDecimals");

    StringSetting dmf = StringSetting::make(L"DataCollection.DiskMetricsFormat");
    if (wcscmp(dmf, L"sameAsNetwork") == 0) {
        g_settings.dataCollection.diskMetricsFormat = g_settings.dataCollection.networkMetricsFormat;
        g_settings.dataCollection.diskMetricsFixedDecimals = g_settings.dataCollection.networkMetricsFixedDecimals;
    } else {
        g_settings.dataCollection.diskMetricsFormat = ParseNetworkMetricsFormat(dmf);
        g_settings.dataCollection.diskMetricsFixedDecimals = Wh_GetIntSetting(L"DataCollection.DiskMetricsFixedDecimals");
    }

    g_settings.dataCollection.percentageFormat = PercentageFormat::spacePaddingAndSymbol;
    StringSetting pf = StringSetting::make(L"DataCollection.PercentageFormat");
    if (wcscmp(pf, L"spacePadding") == 0) g_settings.dataCollection.percentageFormat = PercentageFormat::spacePadding;
    else if (wcscmp(pf, L"singleSpacePadding") == 0) g_settings.dataCollection.percentageFormat = PercentageFormat::singleSpacePadding;
    else if (wcscmp(pf, L"zeroPadding") == 0) g_settings.dataCollection.percentageFormat = PercentageFormat::zeroPadding;
    else if (wcscmp(pf, L"noPadding") == 0) g_settings.dataCollection.percentageFormat = PercentageFormat::noPadding;

    g_settings.dataCollection.updateInterval = Wh_GetIntSetting(L"DataCollection.UpdateInterval");
    g_settings.dataCollection.networkAdapterName = StringSetting::make(L"DataCollection.NetworkAdapterName");
    g_settings.dataCollection.gpuAdapterName = StringSetting::make(L"DataCollection.GpuAdapterName");

    g_settings.mediaPlayer.maxLength = Wh_GetIntSetting(L"MediaPlayer.MaxLength");
    g_settings.mediaPlayer.mediaInfoFormat = StringSetting::make(L"MediaPlayer.MediaInfoFormat");
    g_settings.mediaPlayer.noMediaText = StringSetting::make(L"MediaPlayer.NoMediaText");
    g_settings.mediaPlayer.removeBrackets = Wh_GetIntSetting(L"MediaPlayer.RemoveBrackets");
    g_settings.mediaPlayer.ignoredPlayers.clear();
    for (int i = 0;; i++) {
        StringSetting player = StringSetting::make(L"MediaPlayer.IgnoredPlayers[%d]", i);
        if (*player == '\0') break;
        g_settings.mediaPlayer.ignoredPlayers.push_back(std::move(player));
    }

    g_settings.webContentWeatherLocation = StringSetting::make(L"WebContentWeatherLocation");
    g_settings.webContentWeatherFormat = StringSetting::make(L"WebContentWeatherFormat");
    g_settings.webContentWeatherUnits = WebContentWeatherUnits::autoDetect;
    StringSetting wu = StringSetting::make(L"WebContentWeatherUnits");
    if (wcscmp(wu, L"uscs") == 0) g_settings.webContentWeatherUnits = WebContentWeatherUnits::uscs;
    else if (wcscmp(wu, L"metric") == 0) g_settings.webContentWeatherUnits = WebContentWeatherUnits::metric;
    else if (wcscmp(wu, L"metricMsWind") == 0) g_settings.webContentWeatherUnits = WebContentWeatherUnits::metricMsWind;

    g_settings.webContentsItems.clear();
    for (int i = 0;; i++) {
        WebContentsSettings itm;
        itm.url = StringSetting::make(L"WebContentsItems[%d].Url", i);
        if (*itm.url == '\0') break;
        itm.blockStart = StringSetting::make(L"WebContentsItems[%d].BlockStart", i);
        itm.start = StringSetting::make(L"WebContentsItems[%d].Start", i);
        itm.end = StringSetting::make(L"WebContentsItems[%d].End", i);
        itm.contentMode = ContentMode::plainText;
        StringSetting cm = StringSetting::make(L"WebContentsItems[%d].ContentMode", i);
        if (wcscmp(cm, L"xml") == 0) itm.contentMode = ContentMode::xml;
        else if (wcscmp(cm, L"html") == 0) itm.contentMode = ContentMode::html;
        else if (wcscmp(cm, L"xmlHtml") == 0) itm.contentMode = ContentMode::xmlHtml;

        for (int j = 0;; j++) {
            StringSetting s = StringSetting::make(L"WebContentsItems[%d].SearchReplace[%d].Search", i, j);
            if (*s == '\0') break;
            StringSetting r = StringSetting::make(L"WebContentsItems[%d].SearchReplace[%d].Replace", i, j);
            try { itm.searchReplace.push_back({std::wregex(s), std::wstring(r)}); } catch (...) {}
        }
        itm.maxLength = Wh_GetIntSetting(L"WebContentsItems[%d].MaxLength", i);
        g_settings.webContentsItems.push_back(std::move(itm));
    }
    g_settings.webContentsUpdateInterval = Wh_GetIntSetting(L"WebContentsUpdateInterval");

    g_timeZoneInformation.clear();
    g_timeFormattedTz.clear();
    g_dateFormattedTz.clear();
    g_weekdayFormattedTz.clear();
    g_settings.timeZones.clear();
    for (int i = 0;; i++) {
        StringSetting tz = StringSetting::make(L"TimeZones[%d]", i);
        if (*tz == '\0') break;
        g_timeZoneInformation.emplace_back(GetTimeZoneInformation(tz));
        g_timeFormattedTz.emplace_back();
        g_dateFormattedTz.emplace_back();
        g_weekdayFormattedTz.emplace_back();
        g_settings.timeZones.push_back(std::move(tz));
    }

    g_settings.timeStyle.hidden = Wh_GetIntSetting(L"TimeStyle.Hidden");
    g_settings.timeStyle.textColor = StringSetting::make(L"TimeStyle.TextColor");
    g_settings.timeStyle.textAlignment = StringSetting::make(L"TimeStyle.TextAlignment");
    g_settings.timeStyle.fontSize = Wh_GetIntSetting(L"TimeStyle.FontSize");
    g_settings.timeStyle.fontFamily = StringSetting::make(L"TimeStyle.FontFamily");
    g_settings.timeStyle.fontWeight = StringSetting::make(L"TimeStyle.FontWeight");
    g_settings.timeStyle.fontStyle = StringSetting::make(L"TimeStyle.FontStyle");
    g_settings.timeStyle.fontStretch = StringSetting::make(L"TimeStyle.FontStretch");
    g_settings.timeStyle.characterSpacing = Wh_GetIntSetting(L"TimeStyle.CharacterSpacing");
    g_settings.timeStyle.lineHeight = Wh_GetIntSetting(L"TimeStyle.LineHeight");

    g_settings.dateStyle.hidden = Wh_GetIntSetting(L"DateStyle.Hidden");
    g_settings.dateStyle.textColor = StringSetting::make(L"DateStyle.TextColor");
    g_settings.dateStyle.textAlignment = StringSetting::make(L"DateStyle.TextAlignment");
    g_settings.dateStyle.fontSize = Wh_GetIntSetting(L"DateStyle.FontSize");
    g_settings.dateStyle.fontFamily = StringSetting::make(L"DateStyle.FontFamily");
    g_settings.dateStyle.fontWeight = StringSetting::make(L"DateStyle.FontWeight");
    g_settings.dateStyle.fontStyle = StringSetting::make(L"DateStyle.FontStyle");
    g_settings.dateStyle.fontStretch = StringSetting::make(L"DateStyle.FontStretch");
    g_settings.dateStyle.characterSpacing = Wh_GetIntSetting(L"DateStyle.CharacterSpacing");
    g_settings.dateStyle.lineHeight = Wh_GetIntSetting(L"DateStyle.LineHeight");

    g_clockElementStyleEnabled =
        (g_settings.maxWidth || g_settings.textSpacing ||
         g_settings.timeStyle.hidden || *g_settings.timeStyle.textColor ||
         *g_settings.timeStyle.textAlignment || g_settings.timeStyle.fontSize ||
         *g_settings.timeStyle.fontFamily || *g_settings.timeStyle.fontWeight ||
         *g_settings.timeStyle.fontStyle || *g_settings.timeStyle.fontStretch ||
         g_settings.timeStyle.characterSpacing || g_settings.timeStyle.lineHeight ||
         g_settings.dateStyle.hidden || *g_settings.dateStyle.textColor ||
         *g_settings.dateStyle.textAlignment || g_settings.dateStyle.fontSize ||
         *g_settings.dateStyle.fontFamily || *g_settings.dateStyle.fontWeight ||
         *g_settings.dateStyle.fontStyle || *g_settings.dateStyle.fontStretch ||
         g_settings.dateStyle.characterSpacing || g_settings.dateStyle.lineHeight);
    g_clockElementStyleIndex++;
    g_settings.oldTaskbarOnWin11 = Wh_GetIntSetting(L"oldTaskbarOnWin11");

    if (IsStrInDateTimePatternSettings(L"%web%") || IsStrInDateTimePatternSettings(L"%web_full%")) {
        g_settings.webContentsUrl = StringSetting::make(L"WebContentsUrl");
        g_settings.webContentsBlockStart = StringSetting::make(L"WebContentsBlockStart");
        g_settings.webContentsStart = StringSetting::make(L"WebContentsStart");
        g_settings.webContentsEnd = StringSetting::make(L"WebContentsEnd");
        g_settings.webContentsMaxLength = Wh_GetIntSetting(L"WebContentsMaxLength");
    }
}

void ApplySettingsWin11Clock() {
    HWND hTaskbarWnd = FindCurrentProcessTaskbarWnd();
    if (!hTaskbarWnd) return;

    constexpr WCHAR kTempValueName[] = L"_temp_windhawk_taskbar-taskbar-clock-customization";
    HKEY hSubKey;
    if (RegOpenKeyEx(HKEY_CURRENT_USER, L"Control Panel\\TimeDate\\AdditionalClocks", 0, KEY_WRITE, &hSubKey) == ERROR_SUCCESS) {
        if (RegSetValueEx(hSubKey, kTempValueName, 0, REG_SZ, (const BYTE*)L"", sizeof(WCHAR)) == ERROR_SUCCESS) {
            RegDeleteValue(hSubKey, kTempValueName);
        }
        RegCloseKey(hSubKey);
    }
}

void ApplySettingsWin10Clock() {
    HWND hTaskbarWnd = FindCurrentProcessTaskbarWnd();
    if (!hTaskbarWnd) return;

    RECT rc;
    if (GetClientRect(hTaskbarWnd, &rc)) {
        SendMessage(hTaskbarWnd, WM_SIZE, SIZE_RESTORED, MAKELPARAM(rc.right - rc.left, rc.bottom - rc.top));
    }
    HWND hNotify = FindWindowEx(hTaskbarWnd, nullptr, L"TrayNotifyWnd", nullptr);
    if (hNotify) {
        HWND hClock = FindWindowEx(hNotify, nullptr, L"TrayClockWClass", nullptr);
        if (hClock) {
            LONG_PTR lp = GetWindowLongPtr(hClock, 0);
            if (lp) ClockButton_v_OnDisplayStateChange_Original((LPVOID)lp, true);
        }
    }
    DWORD tid = GetWindowThreadProcessId(hTaskbarWnd, nullptr);
    if (!tid) return;

    auto enumWindowsProc = [](HWND hWnd) {
        WCHAR szClassName[32];
        if (!GetClassName(hWnd, szClassName, ARRAYSIZE(szClassName)) || _wcsicmp(szClassName, L"Shell_SecondaryTrayWnd") != 0) return;
        RECT rc;
        if (GetClientRect(hWnd, &rc)) {
            WINDOWPOS wp{.hwnd = hWnd, .hwndInsertAfter = nullptr, .x = 0, .y = 0, .cx = rc.right - rc.left, .cy = rc.bottom - rc.top, .flags = SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE};
            SendMessage(hWnd, WM_WINDOWPOSCHANGED, 0, (LPARAM)&wp);
        }
        HWND hBtn = FindWindowEx(hWnd, nullptr, L"ClockButton", nullptr);
        if (hBtn) {
            LONG_PTR lp = GetWindowLongPtr(hBtn, 0);
            if (lp) ClockButton_v_OnDisplayStateChange_Original((LPVOID)lp, true);
        }
    };
    EnumThreadWindows(tid, [](HWND hWnd, LPARAM lParam) -> BOOL {
        (*reinterpret_cast<decltype(enumWindowsProc)*>(lParam))(hWnd);
        return TRUE;
    }, reinterpret_cast<LPARAM>(&enumWindowsProc));
}

void ApplySettingsTray(HWND hTaskbarWnd) {
    if (!hTaskbarWnd || g_winVersion < WinVersion::Win11) return;

    RunFromWindowThread(hTaskbarWnd, [](void* pWnd) {
        HWND hWnd = *(HWND*)pWnd;
        g_autoRevokerList.clear();

        if (auto bell = g_bellSystemTrayIconElement.get()) {
            bell.UnregisterPropertyChangedCallback(Automation::AutomationProperties::NameProperty(), g_bellAutomationNameChangedToken);
            g_bellSystemTrayIconElement = nullptr;
            g_bellAutomationNameChangedToken = 0;
        }
        if (auto mainStack = g_mainStackInnerTextBlock.get()) {
            mainStack.UnregisterPropertyChangedCallback(Controls::TextBlock::TextProperty(), g_mainStackTextChangedToken);
            g_mainStackInnerTextBlock = nullptr;
            g_mainStackTextChangedToken = 0;
        }
        for (auto& s : g_batteryTextBlockStates) {
            if (auto tb = s.textBlock.get()) {
                tb.UnregisterPropertyChangedCallback(Controls::TextBlock::ForegroundProperty(), s.foregroundChangedToken);
                tb.Foreground(s.savedForeground);
            }
        }
        g_batteryTextBlockStates.clear();

        auto xamlRoot = GetTaskbarXamlRoot(hWnd);
        if (xamlRoot) ApplyTrayStylesVisualTree(xamlRoot);
    }, &hTaskbarWnd);
}

void ApplySettings() {
    HWND hTaskbarWnd = FindCurrentProcessTaskbarWnd();
    ApplySettingsTray(hTaskbarWnd);
    if (g_winVersion >= WinVersion::Win11) ApplySettingsWin11Clock();
    else ApplySettingsWin10Clock();
}

// ------------------------------------------
// MODULE LIFECYCLE
// ------------------------------------------

BOOL Wh_ModInit() {
    if (HMODULE hUser32 = LoadLibraryEx(L"user32.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32)) {
        pGetDpiForWindow = (GetDpiForWindow_t)GetProcAddress(hUser32, "GetDpiForWindow");
    }
    if (HMODULE hKernel32 = LoadLibraryEx(L"kernel32.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32)) {
        pSystemTimeToTzSpecificLocalTimeEx = (SystemTimeToTzSpecificLocalTimeEx_t)GetProcAddress(hKernel32, "SystemTimeToTzSpecificLocalTimeEx");
    }
    if (HMODULE hAdvapi32 = LoadLibraryEx(L"advapi32.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32)) {
        pEnumDynamicTimeZoneInformation = (EnumDynamicTimeZoneInformation_t)GetProcAddress(hAdvapi32, "EnumDynamicTimeZoneInformation");
    }

    LoadSettings();

    g_winVersion = GetExplorerVersion();
    if (g_winVersion == WinVersion::Unsupported) return FALSE;

    if (g_settings.oldTaskbarOnWin11) {
        bool hasWin10Taskbar = g_winVersion < WinVersion::Win11_24H2;
        if (g_winVersion >= WinVersion::Win11) g_winVersion = WinVersion::Win10;
        if (hasWin10Taskbar && !HookWin10TaskbarSymbols()) return FALSE;
    } else if (g_winVersion >= WinVersion::Win11) {
        if (HMODULE systemTrayModule = GetSystemTrayModuleHandle()) {
            g_systemTrayModuleHooked = true;
            if (!HookUnifiedSystemTraySymbols(systemTrayModule)) return FALSE;
        }
        if (!HookTaskbarDllSymbols()) return FALSE;
    } else {
        if (!HookWin10TaskbarSymbols()) return FALSE;
    }

    if (!HandleLoadedExplorerPatcher()) return FALSE;

    HMODULE kernelBaseModule = GetModuleHandle(L"kernelbase.dll");
    auto pKernelBaseLoadLibraryExW = (decltype(&LoadLibraryExW))GetProcAddress(kernelBaseModule, "LoadLibraryExW");
    WindhawkUtils::SetFunctionHook(pKernelBaseLoadLibraryExW, LoadLibraryExW_Hook, &LoadLibraryExW_Original);

    auto pGetTimeFormatEx = (decltype(&GetTimeFormatEx))GetProcAddress(kernelBaseModule, "GetTimeFormatEx");
    auto pGetDateFormatEx = (decltype(&GetDateFormatEx))GetProcAddress(kernelBaseModule, "GetDateFormatEx");
    if (!pGetTimeFormatEx || !pGetDateFormatEx) return FALSE;

    if (g_winVersion <= WinVersion::Win10) {
        WindhawkUtils::SetFunctionHook(pGetTimeFormatEx, GetTimeFormatEx_Hook_Win10, &GetTimeFormatEx_Original);
        WindhawkUtils::SetFunctionHook(pGetDateFormatEx, GetDateFormatEx_Hook_Win10, &GetDateFormatEx_Original);
        auto pGetDateFormatW = (decltype(&GetDateFormatW))GetProcAddress(kernelBaseModule, "GetDateFormatW");
        if (pGetDateFormatW) WindhawkUtils::SetFunctionHook(pGetDateFormatW, GetDateFormatW_Hook_Win10, &GetDateFormatW_Original);
    } else {
        if (g_winVersion >= WinVersion::Win11_22H2) {
            auto pGetLocalTime = (decltype(&GetLocalTime))GetProcAddress(kernelBaseModule, "GetLocalTime");
            if (!pGetLocalTime) return FALSE;
            WindhawkUtils::SetFunctionHook(pGetLocalTime, GetLocalTime_Hook_Win11, &GetLocalTime_Original);
        }
        WindhawkUtils::SetFunctionHook(pGetTimeFormatEx, GetTimeFormatEx_Hook_Win11, &GetTimeFormatEx_Original);
        WindhawkUtils::SetFunctionHook(pGetDateFormatEx, GetDateFormatEx_Hook_Win11, &GetDateFormatEx_Original);
        WindhawkUtils::SetFunctionHook(SendMessageW, SendMessageW_Hook, &SendMessageW_Original);
    }

    g_initialized = true;
    return TRUE;
}

void Wh_ModAfterInit() {
    if (g_winVersion >= WinVersion::Win11 && !g_systemTrayModuleHooked) {
        if (HMODULE systemTrayModule = GetSystemTrayModuleHandle()) {
            if (!g_systemTrayModuleHooked.exchange(true)) {
                if (HookUnifiedSystemTraySymbols(systemTrayModule)) Wh_ApplyHookOperations();
            }
        }
    }
    if (!g_explorerPatcherInitialized) HandleLoadedExplorerPatcher();
    ApplySettings();
}

void Wh_ModBeforeUninit() {
    g_unloading = true;
    if (g_winVersion >= WinVersion::Win11 && g_clockElementStyleEnabled.exchange(false)) {
        DWORD styleIndex = ++g_clockElementStyleIndex;
        ApplySettings();
        for (int i = 0; i < 20; i++) {
            bool allRestored = true;
            for (const auto& d : g_clockElementStyleData) {
                if (d.styleIndex < styleIndex) { allRestored = false; break; }
            }
            if (allRestored) break;
            Sleep(100);
        }
    } else {
        ApplySettings();
    }
}

void Wh_ModUninit() {
    {
        std::lock_guard<std::mutex> guard(g_formatLineMutex);
        WebContentUpdateThreadUninit();
        DataCollectionSessionUninit();
        MediaSessionUninit();
    }
    ApplySettings();
}

BOOL Wh_ModSettingsChanged(BOOL* bReload) {
    {
        std::lock_guard<std::mutex> guard(g_formatLineMutex);
        WebContentUpdateThreadUninit();
        DataCollectionSessionUninit();
        MediaSessionUninit();
        g_formattingInitialized = false;

        bool prevOldTaskbar = g_settings.oldTaskbarOnWin11;
        LoadSettings();
        *bReload = (g_settings.oldTaskbarOnWin11 != prevOldTaskbar);
        if (*bReload) return TRUE;
    }
    ApplySettings();
    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID lpReserved) {
    if (fdwReason == DLL_PROCESS_DETACH && lpReserved) {
        winrt::detach_abi(g_mediaSessionManager);
        winrt::detach_abi(g_mediaCurrentSession);
    }
    return TRUE;
}