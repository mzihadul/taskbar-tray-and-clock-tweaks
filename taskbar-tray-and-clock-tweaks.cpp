// ==WindhawkMod==
// @id              taskbar-tray-and-clock-tweaks
// @name            Taskbar Tray & Clock Tweaks
// @description     Taskbar clock with live metrics, media info, weather and prayer times; system tray icon control; taskbar size and transparency; and XAML control styling.
// @version         1.7.1
// @author          mzihadul
// @github          https://github.com/mzihadul/taskbar-tray-and-clock-tweaks
// @include         explorer.exe
// @architecture    x86-64
// @compilerOptions -lcomctl32 -lgdi32 -lole32 -loleaut32 -lruntimeobject -lshcore -lversion -lwininet -lshlwapi -ldxgi -lpdh -lpowrprof
// ==/WindhawkMod==

// Combined derivative work based on these Windhawk mods by m417z
// (https://github.com/ramensoftware/windhawk-mods/blob/main/mods/):
//   - taskbar-clock-customization.wh.cpp
//   - taskbar-tray-system-icon-tweaks.wh.cpp
//   - taskbar-icon-size.wh.cpp
//   - windows-11-taskbar-styler.wh.cpp (styling engine only; themes omitted)
//
// Additions and integration by mzihadul: unified clock/tray hooks, settings and
// lifecycle; %volume% and %mic% indicators; battery charging / low-battery
// indicators and styling.
//
// Licensed under the GNU General Public License v3.0.

// ==WindhawkModReadme==
/*
# Taskbar Tray & Clock Tweaks

Taskbar clock customization with live hardware metrics, media info and weather, granular system tray icon control, taskbar size / transparency, and XAML control styling.

Supports **Windows 10 (64-bit)** and **Windows 11**. Everything except the clock requires Windows 11, and the taskbar size and styling features also require the new (XAML) taskbar. They are inactive when "Customize the old taskbar on Windows 11" is enabled.

![Screenshot](https://raw.githubusercontent.com/mzihadul/taskbar-tray-and-clock-tweaks/main/screenshot.png)

## Settings categories

| Category | What it controls |
| --- | --- |
| System tray icons | Hide or restyle volume, network, battery, microphone, location, Studio Effects, Recall, language, bell and "Show desktop" |
| Clock: date, time & time zones | Time / date / weekday formats, locale, seconds, time zones |
| Clock: text lines & tooltip | What the top, middle (Windows 10) and bottom lines and the tooltip show, ready-made layout presets, unknown-tag hints |
| Clock: size & spacing | Clock width / height (Windows 10), max width and line spacing (Windows 11) |
| Clock: top / bottom line style | Color, font, alignment and spacing per line (Windows 11 22H2+) |
| Clock: click & scroll actions | Mouse wheel and middle click on the clock: volume, media keys, Task Manager or a command (Windows 11) |
| Clock: timer, stopwatch & Pomodoro | Lengths and sound for `%stopwatch%`, `%timer%`, `%pomodoro%`; start / pause / reset with a middle click |
| Clock: automatic profiles | Switch the clock to a ready-made layout on battery, with several monitors, or at certain hours |
| Clock: color rules | Change the clock text color when CPU, RAM, GPU, temperature or battery cross a threshold (Windows 11 22H2+) |
| Clock: prayer times | Location, calculation method, Asr rule, names and minute adjustments for the `%prayer_*%` tags |
| Network info | Ping, Wi-Fi name and signal, VPN status, local IP |
| Alternate calendars | Hijri, Persian, Japanese and Bengali (Bangladesh) dates |
| Calendar events (ICS) | Next event from a calendar feed |
| Live metrics | Update interval (and a slower one on battery), number formats, network / GPU adapter, graph length |
| Media player info | Format, length limit, scrolling marquee and ignored players for `%media_*%` |
| Weather & web content | Weather (wttr.in, with an Open-Meteo fallback) with presets, and web / RSS extraction for `%weather%`, `%web<n>%` |
| Taskbar transparency & app visibility | Transparency mode and level, dynamic transparency, hide running / pinned apps |
| Taskbar size & icons | Taskbar height, icon size, button width |
| Tray icons | Hide individual notification-area icons by name |
| Taskbar shape | Rounded bar or pill: corner radius, background and border |
| Taskbar buttons | Hide the Start, Search, Task View and Widgets buttons |
| Running-app indicator | Hide it, or set its color, size and corner radius (with a separate look for the focused app) |
| Advanced styling (XAML) | Style constants, control styles, theme resources |

## Clock tags

Use these in the top, middle, bottom and tooltip lines.

### Date & time
* `%time%`, `%date%` - configured formats. `%time<n>%` / `%date<n>%` use additional formats (separated by `;`, starting at `<n>=2`).
* `%time_tz<n>%`, `%date_tz<n>%`, `%weekday_tz<n>%` - value for the time zone at index `<n>`.
* `%weekday%` - full, abbreviated or custom week day name.
* `%weekday_num%` - week day number from the locale's first day of week (1-7).
* `%weeknum%` / `%weeknum_iso%` - week number (regional settings / ISO 8601).
* `%dayofyear%` - day of the year (1-366).
* `%timezone%` - UTC offset, e.g. `+06:00`.
* `%newline%` or `%n%` - line break.
* `%date_hijri%`, `%date_persian%`, `%date_japanese%` - the date in the Hijri (Umm al-Qura or civil, adjustable by days), Persian or Japanese-era calendar.
* `%date_bengali%` / `%date_bengali_en%` - the Bengali date of the Bangladesh revised calendar, in Bangla script and digits or in Latin letters (e.g. `25 Ashwin 1433`). Bangla letters are drawn in a fallback font that looks larger than the Latin font, so the "Bangla text size" setting (default 90%) scales just those characters on the clock lines.
* `%stopwatch%` / `%timer%` / `%pomodoro%` - count up, count down from the configured length, or alternate work and break phases. They share one run state: set a middle-click action to start / pause or reset them.
* `%if(condition,then,else)%` - show text only when a condition holds, e.g. `%if(battery<20,"low",)%` or `%if(cpu>=90,%cpu%,)%`. Conditions are `<metric><op><number>` with metric `cpu`, `ram`, `gpu`, `cpu_temp`, `cpu_freq`, `battery`, `charging` (1/0), `hour`, `minute` or `weekday` (Mon=1) and op `>`, `>=`, `<`, `<=`, `==`, `!=`. The text parts may contain other tags; wrap them in double quotes to keep commas or spaces. Do not put a space right after `%if(`.
* `%countdown<n>%` - time left until target `<n>` (e.g. `12d 4h 3m`, or `Done`); `%countdown<n>_days%` - whole days left. Targets are set in the date and time settings.

### Hardware & performance
* **Graphs:** `%cpu_graph%`, `%ram_graph%`, `%gpu_graph%`, `%download_graph%`, `%upload_graph%`, `%disk_graph%` - recent history drawn with block characters (▁▂▃▅▇). Percent graphs use a fixed 0-100% scale; speed graphs scale to the recent peak.
* **Network:** `%upload_speed%`, `%download_speed%`, `%total_speed%`
* **Disk:** `%disk_read%`, `%disk_write%`, `%disk_total%`
* **CPU:** `%cpu%` (%), `%cpu_temp%` (°C), `%cpu_temp_f%` (°F), `%cpu_freq%` (average clock, e.g. `3.4 GHz`)
* **RAM:** `%ram%` (%), `%ram_used%`, `%ram_total%` (GB), `%ram_committed%` (%), `%ram_committed_used%`, `%ram_committed_total%` (GB)
* **GPU / VRAM:** `%gpu%` (3D engine %), `%vram%` (%), `%vram_used%`, `%vram_total%` (GB), `%vram_shared%` (%), `%vram_shared_used%`, `%vram_shared_total%` (GB)
* **Battery:**
  * `%battery%` - percentage; appends `⚡` while charging and `❗` at 20% or below.
  * `%battery_time%` - remaining / charging time as `h:mm`.
  * `%power%` - charge / discharge rate in watts (`+W` / `-W`).
* **Volume:** `%volume%` - `🔊` / `🔇` icon that expands to the level % while adjusting, then collapses after 3 seconds.
* **Microphone:** `%mic%` - `🎙️` while any app is recording.

### System info & input
* `%uptime%` - time since boot (e.g. `2d 5h 12m`).
* `%process_count%` - number of running processes.
* `%top_process%` / `%top_process_cpu%` - busiest process by CPU and its usage. Sampled every few seconds.
* `%drive_free_C%`, `%drive_used_C%`, `%drive_total_C%` - space on a local drive (use any drive letter); `%drive_free_pct_C%` / `%drive_used_pct_C%` give percentages.
* `%lang%` / `%lang_full%` - current input language (e.g. `EN` / `English`).
* `%capslock%` / `%numlock%` - `CAPS` / `NUM` while the key is on, otherwise empty.

A tag that does not exist is shown as `[?name]` so typos are easy to spot (can be turned off).

### Network & calendar events
* `%ping%` - round-trip time to the configured IPv4 host (e.g. `23 ms`, `--` when unreachable).
* `%wifi_ssid%`, `%wifi_signal%` - connected Wi-Fi name and signal (Windows reports 0-5 bars, shown in 20% steps).
* `%vpn%` - `VPN` while a VPN-like connection is up (best effort), otherwise empty.
* `%local_ip%` - IPv4 address of the adapter used for internet.
* `%next_event%`, `%next_event_time%`, `%next_event_in%` - the next event of an ICS calendar feed, its start (`14:30`, `Fri 09:00`, `Oct 20 09:00`) and the time left (`in 25m`).

### Media (Spotify, Chrome, Edge, VLC, ...)
`%media_title%`, `%media_artist%`, `%media_album%`, `%media_status%` (`⏯` / `⏸` / `⏹`), `%media_info%` (formatted and truncated, or scrolling).

Playback progress: `%media_position%`, `%media_duration%`, `%media_remaining%`, `%media_progress%` (percent) and `%media_bar%` (▰▰▰▱▱▱▱▱). They stay empty when the player does not report a timeline.

### Prayer times
Calculated on your computer from the latitude, longitude and method in the "Clock: prayer times" settings (defaults to Dhaka, Karachi method, Hanafi Asr), so no internet is needed. Times follow the system clock and time zone, including daylight saving time.
* `%prayer_next%`, `%prayer_next_time%`, `%prayer_next_in%` - name, start time and time left (`1h 12m`) of the next prayer. After Isha it points to tomorrow's Fajr.
* `%prayer_next_info%` - all three together, e.g. `Asr 3:45 PM (1h 12m)`.
* `%prayer_current%` - the prayer whose time it is now, or `--` when no prayer is current (between Sunrise and Dhuhr, and after Isha ends).
* `%prayer_current_left%`, `%prayer_current_end%`, `%prayer_current_info%` - time left in the current prayer's period, when it ends, or both (e.g. `Asr (1h 12m left)`). A period ends at the next event: Fajr at Sunrise, Dhuhr at Asr, Asr at Maghrib, Maghrib at Isha, and Isha at Islamic midnight (halfway between Maghrib and the next Fajr; the setting can make it the next Fajr instead). Between Sunrise and Dhuhr, and from the end of Isha until Fajr, no prayer is current, so these show `--`.
* `%prayer_fajr%`, `%prayer_sunrise%`, `%prayer_dhuhr%`, `%prayer_asr%`, `%prayer_maghrib%`, `%prayer_isha%` - today's times.
* `%prayer_all%` - the five prayers on one line.
* `%prayer_midnight%` - Islamic midnight of tonight, halfway between Maghrib and the next Fajr.
Use the adjustments setting to match your local mosque's timetable. Times are shown as `--` where the sun never reaches the Fajr / Isha angle (far-north winters and summers).

### Weather & web
* `%weather%` - from [wttr.in](https://wttr.in), using your location, units and format. When wttr.in does not answer, [Open-Meteo](https://open-meteo.com) is used instead (`%c %t %w %h %l %S %s` only).
* `%web<n>%` / `%web<n>_full%` - text extracted from RSS, XML, HTML or plain web pages (item `<n>` in the web content list).

## Taskbar features (Windows 11)

### Transparency & app visibility
* Modes: Default, Fully Transparent, Blurry Glass, Liquid Glass (Acrylic), Mica.
* Level: 0% (opaque) to 100% (fully transparent) for the transparent, blur and acrylic modes; Mica ignores it.
* Hide running / pinned apps while keeping Start, Search, Task View, Widgets and the tray (those have their own switches under Taskbar buttons). Exceptions accept an AUMID or app name (case-insensitive, partial match). The Copilot button counts as an app button; add `Copilot` to the exceptions to keep it.
* Applied to the primary and secondary taskbars and reset when the mod unloads.

### Shape (rounded, pill)
Gives the taskbar background rounded corners. With a shape selected, the Fully Transparent, Blurry Glass and Liquid Glass modes are drawn inside the shape and Mica is not applied.

### Size & icons
Icons are normally 24x24, a downscaled 32x32 that looks blurry. Set the icon size to 32 (or any other size) for crisp icons, and adjust the taskbar height and button width to match. Small icon settings apply to newer builds with small taskbar icons.

### Dynamic transparency
With a transparency mode set, the taskbar can switch to the default opaque look on a monitor while a window is maximized there, and go back to your mode when it is restored.

### Tray icons by name
Add the exact name of a classic notification-area icon (its tooltip text, readable with the UWPSpy tool) to hide just that icon.

### Buttons & running indicator
Simple switches that generate the matching control styles for you, so common tweaks need no XAML. They are applied before your own control styles, which can still override them.

### Advanced styling
* Target elements by class name, element ID or app ID (`Taskbar.TaskListButton[AutomationProperties.AutomationId=Appid: ...]`).
* Override properties such as `Source` (custom app icons), `Width`, `Height`, `CornerRadius`, `Background` and `Margin`.
* Local files and remote image URLs, with offline caching and retry on reconnect.
* `:=` XAML markup syntax and the built-in `WindhawkBlur` brush.
* Visual states (`Style@VisualState=Value`) and variables (`Property=>VarName`, `{{VarName}}`).
* Theme resource overrides with dark / light awareness.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- oldTaskbarOnWin11: false
  $name: Customize the old taskbar on Windows 11
- SystemTray:
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
  $name: System tray icons
  $description: >-
    Windows 11 only.
- ClockFormat:
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
  - TimeZones: ["Eastern Standard Time"]
    $name: Time zones
  - Countdowns: [""]
    $name: Countdown targets (used as %countdown1%, %countdown2%, ...)
    $description: >-
      Local date and optional time, for example 2027-01-01 or 2027-01-01 18:30.
      %countdown<n>% shows the time left, %countdown<n>_days% the whole days left.
  $name: 'Clock: date, time & time zones'
- ClockLines:
  - Preset: custom
    $name: Preset
    $description: >-
      Pick a ready-made layout, or Custom to use the lines below. A preset
      replaces the top line, bottom line and tooltip line (the Windows 10
      middle line is not affected).
    $options:
    - custom: Custom (use the lines below)
    - minimal: Minimal (time and date)
    - monitor: System monitor
    - battery: Battery
    - media: Media player
    - weather: Weather
    - pomodoro: Pomodoro timer
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
  - ShowTagHints: true
    $name: Show hints for unknown tags
    $description: >-
      Display [?name] where a line contains a tag that does not exist, for
      example a misspelled %cpuu%.
  $name: 'Clock: text lines & tooltip'
  $description: >-
    Tags such as %date%, %time%, %cpu% are listed in the mod description.
- ClockLayout:
  - Width: 180
    $name: Clock width (Windows 10 only)
  - Height: 60
    $name: Clock height (Windows 10 only)
  - MaxWidth: 0
    $name: Clock max width (Windows 11 only)
  - TextSpacing: 0
    $name: Line spacing
  $name: 'Clock: size & spacing'
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
  $name: 'Clock: top line style'
  $description: >-
    Windows 11 version 22H2 and newer.
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
  $name: 'Clock: bottom line style'
  $description: >-
    Windows 11 version 22H2 and newer.
- ClockColors:
  - Rules:
    - - Metric: ""
        $name: Metric
        $options:
        - "": None
        - cpu: CPU usage (%)
        - ram: RAM usage (%)
        - gpu: GPU usage (%)
        - cpu_temp: CPU temperature (°C)
        - battery: Battery level (%)
      - Condition: above
        $name: Condition
        $options:
        - above: Value is above the threshold
        - below: Value is below the threshold
      - Threshold: 90
        $name: Threshold
      - Color: "#FF5555"
        $name: Color
        $description: >-
          Hex (#RRGGBB or #AARRGGBB) or a named color such as Red.
      - Line: both
        $name: Apply to
        $options:
        - both: Top and bottom line
        - top: Top line only
        - bottom: Bottom line only
    $name: Rules
    $description: >-
      Rules are checked in order and the first match for each line wins.
      Metrics are read live, so the color changes as the value crosses the
      threshold.
  $name: 'Clock: color rules'
  $description: >-
    Windows 11 version 22H2 and newer.
- ClockActions:
  - Scroll: none
    $name: Mouse wheel over the clock
    $options:
    - none: Do nothing
    - volume: Change the volume
    - track: Previous / next track
  - MiddleClick: none
    $name: Middle click on the clock
    $options:
    - none: Do nothing
    - playpause: Play / pause
    - mute: Mute / unmute
    - next: Next track
    - previous: Previous track
    - taskmgr: Open Task Manager
    - command: Run the command below
    - timer_toggle: Start / pause the timer
    - timer_reset: Reset the timer
  - Command: ""
    $name: Command to run
    $description: >-
      Full command line, for example C:\Windows\System32\notepad.exe. Used by
      the "Run the command below" middle-click action.
  $name: 'Clock: click & scroll actions'
  $description: >-
    Windows 11 only. Nothing is attached to the clock unless an action is set.
- ClockTimer:
  - TimerMinutes: 25
    $name: Timer length (minutes)
    $description: >-
      Length counted down by %timer%.
  - WorkMinutes: 25
    $name: Pomodoro work length (minutes)
  - BreakMinutes: 5
    $name: Pomodoro break length (minutes)
  - PlaySound: true
    $name: Play a sound when the timer ends or the Pomodoro phase changes
  $name: 'Clock: timer, stopwatch & Pomodoro'
  $description: >-
    %stopwatch%, %timer% and %pomodoro% share one run state. Start / pause and
    reset them with a middle-click action under "Clock: click & scroll
    actions". Windows 11 only for the click actions.
- Prayer:
  - Latitude: "23.8103"
    $name: Latitude
    $description: >-
      Decimal degrees, north is positive. The default is Dhaka.
  - Longitude: "90.4125"
    $name: Longitude
    $description: >-
      Decimal degrees, east is positive. The default is Dhaka.
  - Method: karachi
    $name: Calculation method
    $options:
    - karachi: University of Islamic Sciences, Karachi (Fajr 18, Isha 18)
    - mwl: Muslim World League (Fajr 18, Isha 17)
    - isna: ISNA (Fajr 15, Isha 15)
    - egypt: Egyptian General Authority (Fajr 19.5, Isha 17.5)
    - makkah: Umm al-Qura, Makkah (Fajr 18.5, Isha 90 min after Maghrib)
    - custom: Custom angles, set below
  - CustomFajrAngle: "18"
    $name: Custom Fajr angle (degrees)
  - CustomIshaAngle: "18"
    $name: Custom Isha angle (degrees)
  - Asr: hanafi
    $name: Asr calculation
    $options:
    - hanafi: Hanafi (shadow length 2x)
    - standard: Shafi, Maliki, Hanbali (shadow length 1x)
  - IshaEnd: midnight
    $name: Isha time ends at
    $description: >-
      Islamic midnight is halfway between Maghrib and the next Fajr. After the
      Isha time ends, no prayer is current (%prayer_current_*% show --) until
      Fajr.
    $options:
    - midnight: Islamic midnight
    - fajr: Next Fajr
  - TimeFormat: 12hAmPm
    $name: Time format
    $options:
    - 12hAmPm: 12-hour with AM / PM
    - 12h: 12-hour without AM / PM
    - 24h: 24-hour
  - Names: "Fajr,Sunrise,Dhuhr,Asr,Maghrib,Isha"
    $name: Prayer names
    $description: >-
      Six names separated by commas, in the order Fajr, Sunrise, Dhuhr, Asr,
      Maghrib, Isha. Change them to show the names in another language.
  - Adjustments: "0,0,0,0,0,0"
    $name: Adjustments (minutes)
    $description: >-
      Six whole numbers separated by commas, in the same order, added to the
      calculated times. Use them to match your local mosque or timetable, for
      example 0,0,0,0,2,0 for a later Maghrib.
  $name: 'Clock: prayer times'
  $description: >-
    Used by the %prayer_*% tags. Times are calculated on this computer from
    your coordinates and the system clock, so no internet access is needed.
- Profiles:
  - Rules:
    - - Condition: ""
        $name: When
        $options:
        - "": None
        - onBattery: The PC is running on battery
        - pluggedIn: The PC is plugged in
        - batteryBelow: Battery is below the threshold
        - multiMonitor: More than one monitor is connected
        - singleMonitor: Only one monitor is connected
        - hours: The time is within the hours below
      - Threshold: 20
        $name: Battery threshold (%)
      - StartHour: 9
        $name: Start hour (0-23)
      - EndHour: 18
        $name: End hour (0-23)
      - Preset: minimal
        $name: Use this clock layout
        $options:
        - minimal: Minimal (time and date)
        - monitor: System monitor
        - battery: Battery
        - media: Media player
        - weather: Weather
        - pomodoro: Pomodoro timer
    $name: Rules
    $description: >-
      Rules are checked in order and the first match wins. The threshold applies
      to the battery condition, the start and end hours to the hours condition
      (a range such as 22 to 6 wraps past midnight).
  $name: 'Clock: automatic profiles'
  $description: >-
    Switches the clock to a ready-made layout when a condition is met. When no
    rule matches, your normal clock lines or preset apply.
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
  - GraphLength: 8
    $name: Graph length (characters)
    $description: >-
      Number of samples drawn by %cpu_graph%, %ram_graph%, %gpu_graph%,
      %download_graph%, %upload_graph% and %disk_graph% (4 to 32).
  - BatteryUpdateInterval: 0
    $name: Update interval on battery (seconds)
    $description: >-
      Samples metrics less often while unplugged to save power. 0, or a value
      not larger than the normal interval, keeps the normal interval.
  $name: Live metrics (CPU, RAM, GPU, network, disk)
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
  - Marquee: false
    $name: Scroll long text (marquee)
    $description: >-
      Scrolls %media_info% instead of cutting it off when it is longer than
      the maximum length. Needs a maximum length above 0, and scrolls only
      while playing.
  - MarqueeSpeed: 2
    $name: Marquee speed (characters per second)
  $name: Media player info
- WebContent:
  - WeatherPreset: custom
    $name: Weather preset
    $description: >-
      Ready-made weather formats. Custom uses the weather format below.
    $options:
    - custom: Custom (use the format below)
    - conditions: Conditions and temperature
    - sun: Sunrise and sunset
    - full: Conditions, humidity, wind, sunrise and sunset
  - WeatherLocation: ""
    $name: Weather location
  - WeatherFallback: true
    $name: Use Open-Meteo when wttr.in does not answer
    $description: >-
      Falls back to Open-Meteo (no account needed). It supports the placeholders
      %c, %t, %w, %h, %l, %S and %s in the weather format; others are dropped.
      Without a location, the place is estimated from your IP address.
  - WeatherFormat: "%c 🌡️%t 🌬️%w"
    $name: Weather format
  - WeatherUnits: autoDetect
    $name: Weather units
    $options:
    - autoDetect: Auto (default)
    - uscs: USCS (used by default in US)
    - metric: Metric (SI) (used by default everywhere except US)
    - metricMsWind: Metric (SI), but show wind speed in m/s
  - Items:
    - - Url: https://rss.nytimes.com/services/xml/rss/nyt/World.xml
        $name: URL
      - BlockStart: '<item>'
        $name: Block start
      - Start: '<title>'
        $name: Start
      - End: '</title>'
        $name: End
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
        $name: Maximum length
    $name: Web content items (used as %web1%, %web2%, ...)
  - UpdateInterval: 10
    $name: Update interval (minutes)
  $name: Weather & web content
- NetworkInfo:
  - PingHost: "1.1.1.1"
    $name: Ping host
    $description: >-
      IPv4 address measured by %ping%. Host names are not supported.
  - PingInterval: 5
    $name: Ping interval (seconds)
    $description: >-
      How often %ping% measures (2 to 300).
  $name: Network info
  $description: >-
    Tags: %ping%, %wifi_ssid%, %wifi_signal%, %vpn%, %local_ip%.
- AlternateCalendars:
  - HijriType: umalqura
    $name: Hijri calendar type
    $options:
    - umalqura: Umm al-Qura (Saudi Arabia)
    - civil: Civil (tabular)
  - HijriOffset: 0
    $name: Hijri date adjustment (days)
    $description: >-
      Shifts %date_hijri% by -2 to +2 days, for example to match local moon
      sighting.
  - BengaliTextScale: 90
    $name: Bangla text size (%)
    $description: >-
      Windows draws Bangla letters in a fallback font that looks larger than
      the Latin font at the same size. This scales only the Bangla characters
      on the clock lines (Windows 11 22H2 and newer). Use 100 to turn it off.
  $name: Alternate calendars
  $description: >-
    Tags: %date_hijri%, %date_persian%, %date_japanese%, %date_bengali%
    (Bangla script) and %date_bengali_en% (Latin letters, Bangladesh revised
    calendar).
- CalendarEvents:
  - IcsUrl: ""
    $name: Calendar feed URL (ICS)
    $description: >-
      A secret iCalendar link, for example from Google Calendar (webcal://
      links work too). Refreshed with the web content update interval.
  - MaxLength: 30
    $name: Event title maximum length
    $description: >-
      0 for no limit.
  - IncludeAllDay: false
    $name: Include all-day events
  - NoEventText: No upcoming events
    $name: Text when there is no upcoming event
  $name: Calendar events (ICS)
  $description: >-
    Tags: %next_event%, %next_event_time%, %next_event_in%. Daily, weekly
    (with weekdays), monthly and yearly repeats are supported. Times given in
    another time zone are read as local time.
- TaskbarAppearance:
  - TransparencyMode: default
    $name: Transparency mode
    $options:
    - default: Default
    - transparent: Fully Transparent
    - blur: Blurry Glass
    - acrylic: Liquid Glass (Acrylic)
    - mica: Mica
  - TransparencyAlpha: 100
    $name: Transparency level (0-100%)
    $description: >-
      0% = opaque, 100% = fully transparent. Applies to transparent, blur and
      acrylic modes. Mica uses the Windows material and ignores this value.
  - DynamicTransparency: off
    $name: Dynamic transparency
    $options:
    - off: Off
    - opaque: Default taskbar while a window is maximized
    $description: >-
      Uses the default (opaque) taskbar on a monitor while a window is
      maximized there, and your transparency mode otherwise. Needs a mode
      other than Default.
  - HideTaskbarApps: false
    $name: Hide running / pinned apps
    $description: >-
      Hides app buttons only. Start, Search, Task View, Widgets and the system
      tray are not affected; use the Taskbar buttons settings to hide those.
  - AppExceptions: [""]
    $name: App exceptions (AUMID or app name)
  $name: Taskbar transparency & app visibility
  $description: >-
    Windows 11 only.
- TaskbarSize:
  - TaskbarHeight: 52
    $name: Taskbar height
    $description: >-
      Height in pixels (Windows 11 default: 48)
  - IconSize: 32
    $name: Icon size
    $description: >-
      Icon size in pixels (Windows 11 default: 24)
  - TaskbarButtonWidth: 44
    $name: Taskbar button width
    $description: >-
      Button width in pixels (Windows 11 default: 44)
  - IconSizeSmall: 16
    $name: Small icon size
    $description: >-
      Small icon size in pixels (Windows 11 default: 16). Only used by newer Windows 11 builds with small taskbar icons (around July 2025).
  - TaskbarButtonWidthSmall: 32
    $name: Small taskbar button width
    $description: >-
      Small button width in pixels (Windows 11 default: 32). Same builds as above.
  $name: Taskbar size & icons
  $description: >-
    Windows 11 new taskbar only. Ignored when customizing the old taskbar, and on Windows 10.
- TaskbarShape:
  - Style: default
    $name: Shape
    $description: >-
      Gives the taskbar background rounded corners.
    $options:
    - default: Default
    - rounded: Rounded bar
    - pill: Pill
  - CornerRadius: 0
    $name: Corner radius
    $description: >-
      In pixels. 0 uses the preset's radius (rounded 12, pill 24).
  - FillColor: ""
    $name: Background color
    $description: >-
      Hex (#RRGGBB or #AARRGGBB) or a named color. Empty keeps the transparency
      mode below, or the default taskbar color.
  - BorderColor: ""
    $name: Border color
  - BorderThickness: 0
    $name: Border thickness
    $description: >-
      In pixels. 0 for no border.
  $name: Taskbar shape
  $description: >-
    Windows 11 new taskbar only. With a shape selected, the transparency modes
    Fully Transparent, Blurry Glass and Liquid Glass are drawn inside the shape
    instead of on the whole taskbar window, and Mica is not applied.
- TaskbarButtons:
  - HideStart: false
    $name: Hide Start button
  - HideSearch: false
    $name: Hide Search button
  - HideTaskView: false
    $name: Hide Task View button
  - HideWidgets: false
    $name: Hide Widgets button
  $name: Taskbar buttons
  $description: >-
    Windows 11 new taskbar only. Independent of hiding running / pinned apps.
- RunningIndicator:
  - Mode: default
    $name: Style
    $options:
    - default: Default
    - hidden: Hidden
    - custom: Custom (use the options below)
  - Color: ""
    $name: Color
    $description: >-
      Hex (#RRGGBB) or a named color such as Red. Empty keeps the default.
  - ActiveColor: ""
    $name: Color for the focused app
  - Width: 0
    $name: Width
    $description: >-
      In pixels. 0 keeps the default.
  - ActiveWidth: 0
    $name: Width for the focused app
  - Height: 0
    $name: Height
  - CornerRadius: 0
    $name: Corner radius
  $name: Running-app indicator
  $description: >-
    Windows 11 new taskbar only. The options below apply when the style is Custom.
- TrayIcons:
  - HiddenNames: [""]
    $name: Icon names to hide
    $description: >-
      The exact name of a classic notification-area icon, as shown in its
      tooltip. Use the UWPSpy tool to read it from the AutomationProperties.Name
      property. Names containing ] are not supported.
  $name: Tray icons
  $description: >-
    Windows 11 new taskbar only. Hides individual notification-area icons by
    name. Windows system icons such as volume and network have their own
    switches under System tray icons.
- Styling:
  - styleConstants: [""]
    $name: Style constants
    $description: >-
      Style constants allow defining a value once and referencing it in multiple
      styles with $name. For technical details, refer to the mod description.
  - controlStyles:
    - - target: ""
        $name: Target
      - styles: [""]
        $name: Styles
    $name: Control styles
    $description: >-
      Customize taskbar controls and icons. Specify target control elements
      and styles to apply.
  - themeResourceVariables: [""]
    $name: Resource variables
    $description: >-
      Use "Key=Value" to override an existing resource with a new value.

      Use "Key@Dark=Value" or "Key@Light=Value" to define theme-aware resources
      that can be referenced with {ThemeResource Key} in styles.

      The ":=" syntax can be used to set a XAML value.
  - xamlDiagnosticsHandling: alert
    $name: XAML diagnostics consumer handling
    $description: >-
      How to handle other programs that try to use XAML diagnostics. There can
      only be one consumer at a time. Block will prevent other programs from using
      it, which might break them. Allow will let them use it, which might break
      this mod.
    $options:
    - alert: Alert (prompt before blocking)
    - block: Block other consumers
    - allow: Allow other consumers
  $name: Advanced styling (XAML)
  $description: >-
    Windows 11 new taskbar only. See the mod description for syntax.
- Diagnostics:
  - LogClockThreads: false
    $name: Log clock threads and taskbar windows
    $description: >-
      Writes which thread each clock runs on, and which monitor each taskbar
      belongs to, into the Windhawk log. Only needed to investigate
      per-monitor clock settings.
  $name: Diagnostics
*/
// ==/WindhawkModSettings==

// Source code is published under The GNU General Public License v3.0.

#include <windhawk_utils.h>

using WindhawkUtils::StringSetting;

#include <algorithm>
#include <atomic>
#include <charconv>
#include <chrono>
#include <cmath>
#include <cwctype>
#include <condition_variable>
#include <filesystem>
#include <functional>
#include <limits>
#include <list>
#include <memory>
#include <mutex>
#include <optional>
#include <random>
#include <regex>
#include <string>
#include <string_view>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>

using namespace std::string_view_literals;

#include <initguid.h>
#include <combaseapi.h>
#include <commctrl.h>
#include <comutil.h>
#include <d2d1_1.h>
#include <dxgi.h>
#include <endpointvolume.h>
#include <mmdeviceapi.h>
#include <mshtml.h>
#include <ocidl.h>
#include <pdh.h>
#include <pdhmsg.h>
#include <powrprof.h>
#include <psapi.h>
#include <roapi.h>
#include <shlwapi.h>
#include <tlhelp32.h>
#include <Unknwn.h>
#include <weakreference.h>
#include <windows.graphics.effects.h>
#include <wininet.h>
#include <winstring.h>
#include <xamlom.h>

#undef GetCurrentTime

#include <winrt/Windows.Data.Xml.Dom.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Globalization.h>
#include <winrt/Windows.Graphics.Effects.h>
#include <winrt/Windows.Media.Control.h>
#include <winrt/Windows.Networking.Connectivity.h>
#include <winrt/Windows.Networking.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.System.Power.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Input.h>
#include <winrt/Windows.UI.Text.h>
#include <winrt/Windows.UI.ViewManagement.h>
#include <winrt/Windows.UI.Xaml.Automation.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Documents.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.UI.Xaml.Input.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Windows.UI.Xaml.Markup.h>
#include <winrt/Windows.UI.Xaml.Media.Imaging.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/Windows.UI.Xaml.Shapes.h>
#include <winrt/Windows.UI.Xaml.h>
#include <winrt/base.h>

#define WH_WINRT_WINUI2
#include <winrt/Microsoft.UI.Xaml.Controls.h>

using namespace winrt::Windows::UI::Xaml;
namespace muxc = winrt::Microsoft::UI::Xaml::Controls;
namespace wge = winrt::Windows::Graphics::Effects;
namespace wuc = winrt::Windows::UI::Composition;
namespace wuxh = winrt::Windows::UI::Xaml::Hosting;
namespace awge = ABI::Windows::Graphics::Effects;
namespace wf = winrt::Windows::Foundation;
namespace wux = winrt::Windows::UI::Xaml;

#ifndef URL_ESCAPE_ASCII_URI_COMPONENT
#define URL_ESCAPE_ASCII_URI_COMPONENT 0x00080000
#endif

// ----- COMMON ENUMS & SETTINGS STRUCTS -----

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
    int graphLength;
    int batteryUpdateInterval;
};

struct MediaPlayerSettings {
    std::vector<StringSetting> ignoredPlayers;
    int maxLength;
    StringSetting mediaInfoFormat;
    StringSetting noMediaText;
    bool removeBrackets;
    bool marquee;
    int marqueeSpeed;
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

struct ColorRule {
    int metric;
    bool above;
    double threshold;
    StringSetting color;
    int lines;  // bit 0: top line, bit 1: bottom line
};

struct LinePreset;

struct ProfileRule {
    int condition;
    int threshold;  // battery percent
    int startHour;
    int endHour;
    const LinePreset* preset;
};

struct PrayerSettings {
    double latitude = 23.8103;
    double longitude = 90.4125;
    double fajrAngle = 18.0;
    double ishaAngle = 18.0;
    int ishaMinutesAfterMaghrib = 0;  // > 0: Isha is fixed minutes after Maghrib
    int asrFactor = 2;                // 1 Shafi/Maliki/Hanbali, 2 Hanafi
    int offsets[6] = {0, 0, 0, 0, 0, 0};  // Fajr, Sunrise, Dhuhr, Asr, Maghrib, Isha (minutes)
    int timeFormat = 0;               // 0 12h with AM/PM, 1 12h, 2 24h
    bool ishaEndsAtFajr = false;      // false: Isha ends at Islamic midnight
    std::wstring names[6] = {L"Fajr", L"Sunrise", L"Dhuhr", L"Asr", L"Maghrib", L"Isha"};
};

struct Settings {
    PrayerSettings prayer;
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

    // Clock extras
    bool showTagHints;
    int weatherPreset;
    std::vector<ULONGLONG> countdownTargets;
    std::vector<ColorRule> colorRules;

    // Network, calendars and events
    std::wstring pingHost;
    int pingInterval;
    bool hijriCivil;
    int hijriOffset;
    int bengaliTextScale;  // percent, 100 = off
    std::wstring icsUrl;
    int icsMaxLength;
    bool icsIncludeAllDay;
    std::wstring icsNoEventText;

    // Click / scroll actions, dynamic transparency, profiles, diagnostics
    int clockScrollAction;  // 0 none, 1 volume, 2 track
    int clockMiddleAction;  // 0 none, 1 play/pause, 2 mute, 3 next, 4 previous, 5 Task Manager, 6 command, 7 timer start/pause, 8 timer reset
    std::wstring clockCommand;
    int dynamicTransparency;  // 0 off, 1 default taskbar while a window is maximized
    std::vector<ProfileRule> profileRules;
    bool logClockThreads;

    // Taskbar shape preset: 0 default, 1 rounded, 2 pill
    int shapeStyle;

    // Timer / stopwatch / Pomodoro
    int timerMinutes;
    int pomodoroWorkMinutes;
    int pomodoroBreakMinutes;
    bool timerSound;

    bool weatherFallback;

    // Transparency and App Hiding
    StringSetting transparencyMode;
    int transparencyAlpha;
    bool hideTaskbarApps;
    std::vector<std::wstring> appExceptions;
} g_settings;

struct LinePreset {
    PCWSTR id;
    PCWSTR top;
    PCWSTR bottom;
    PCWSTR tooltip;
};

const LinePreset kLinePresets[] = {
    {L"minimal", L"%time%", L"%date%", L""},
    {L"monitor", L"CPU %cpu% | RAM %ram%", L"\u2193 %download_speed%  \u2191 %upload_speed%",
     L"%date% %time%%n%GPU %gpu% | Disk %disk_total%"},
    {L"battery", L"%time%", L"%battery% %power%", L"%battery_time%"},
    {L"media", L"%time%", L"%media_info%", L"%media_title%%n%%media_artist%%n%%media_album%"},
    {L"weather", L"%time%", L"%weather%", L"%date%"},
    {L"pomodoro", L"%time%", L"%pomodoro%", L"%date%%n%%stopwatch% elapsed | %timer% left"},
};

// When a clock line preset is selected, these point at the preset's strings
// and take priority over the custom top / bottom / tooltip lines.
PCWSTR g_presetTopLine;
PCWSTR g_presetBottomLine;
PCWSTR g_presetTooltipLine;

// Chosen at runtime by the automatic profile rules; takes priority over everything else.
const LinePreset* g_profilePreset = nullptr;

PCWSTR EffTopLine() {
    if (g_profilePreset) return g_profilePreset->top;
    return g_presetTopLine ? g_presetTopLine : g_settings.topLine.get();
}
PCWSTR EffBottomLine() {
    if (g_profilePreset) return g_profilePreset->bottom;
    return g_presetBottomLine ? g_presetBottomLine : g_settings.bottomLine.get();
}
PCWSTR EffTooltipLine() {
    if (g_profilePreset) return g_profilePreset->tooltip;
    return g_presetTooltipLine ? g_presetTooltipLine : g_settings.tooltipLine.get();
}

const LinePreset* FindLinePreset(PCWSTR id) {
    for (const auto& p : kLinePresets) {
        if (wcscmp(id, p.id) == 0) return &p;
    }
    return nullptr;
}

enum class XamlDiagnosticsHandling {
    kAlert,
    kBlock,
    kAllow,
};

struct StylerSettings {
    XamlDiagnosticsHandling xamlDiagnosticsHandling;
} g_stylerSettings;

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

// ----- GENERAL SHARED HELPERS -----

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

std::optional<bool> IsOsFeatureEnabled(UINT32 featureId) {
    enum FEATURE_ENABLED_STATE {
        FEATURE_ENABLED_STATE_DEFAULT = 0,
        FEATURE_ENABLED_STATE_DISABLED = 1,
        FEATURE_ENABLED_STATE_ENABLED = 2,
    };

#pragma pack(push, 1)
    struct RTL_FEATURE_CONFIGURATION {
        unsigned int featureId;
        unsigned __int32 group : 4;
        FEATURE_ENABLED_STATE enabledState : 2;
        unsigned __int32 enabledStateOptions : 1;
        unsigned __int32 unused1 : 1;
        unsigned __int32 variant : 6;
        unsigned __int32 variantPayloadKind : 2;
        unsigned __int32 unused2 : 16;
        unsigned int payload;
    };
#pragma pack(pop)

    using RtlQueryFeatureConfiguration_t =
        int(NTAPI*)(UINT32, int, INT64*, RTL_FEATURE_CONFIGURATION*);
    static RtlQueryFeatureConfiguration_t pRtlQueryFeatureConfiguration = []() {
        HMODULE hNtDll = GetModuleHandle(L"ntdll.dll");
        return hNtDll ? (RtlQueryFeatureConfiguration_t)GetProcAddress(
                            hNtDll, "RtlQueryFeatureConfiguration")
                      : nullptr;
    }();

    if (!pRtlQueryFeatureConfiguration) {
        Wh_Log(L"RtlQueryFeatureConfiguration not found");
        return std::nullopt;
    }

    RTL_FEATURE_CONFIGURATION feature = {0};
    INT64 changeStamp = 0;
    HRESULT hr =
        pRtlQueryFeatureConfiguration(featureId, 1, &changeStamp, &feature);
    if (SUCCEEDED(hr)) {
        Wh_Log(L"RtlQueryFeatureConfiguration result for %u: %d", featureId,
               feature.enabledState);

        switch (feature.enabledState) {
            case FEATURE_ENABLED_STATE_DISABLED:
                return false;
            case FEATURE_ENABLED_STATE_ENABLED:
                return true;
            case FEATURE_ENABLED_STATE_DEFAULT:
                return std::nullopt;
        }
    } else {
        Wh_Log(L"RtlQueryFeatureConfiguration error for %u: %08X", featureId,
               hr);
    }

    return std::nullopt;
}

// ----- TRAY TWEAKS LOGIC -----

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

// ----- CLOCK & MONITORING LOGIC -----

bool g_formattingInitialized;
bool g_liveTagsUsed;
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
FormattedString<FORMATTED_BUFFER_SIZE> g_cpuFreqFormatted;
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
bool g_mediaPlaying = false;
struct MediaTimeline {
    double position = 0;  // seconds, at queryTick
    double duration = 0;  // seconds, 0 if unknown
    double rate = 1;
    ULONGLONG queryTick = 0;
    bool valid = false;
} g_mediaTimeline;
ULONGLONG g_mediaTimelineLastQuery = 0;
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
    std::optional<int64_t> dateTextChangedToken;
    std::optional<int64_t> timeTextChangedToken;
    winrt::weak_ref<UIElement> actionTarget;
    std::optional<winrt::Windows::UI::Xaml::Input::PointerEventHandler> wheelHandler;
    std::optional<winrt::Windows::UI::Xaml::Input::PointerEventHandler> pressedHandler;
};

std::atomic<bool> g_clockElementStyleEnabled{false};
std::atomic<DWORD> g_clockElementStyleIndex{0};
std::vector<ClockElementStyleData> g_clockElementStyleData;

// Threshold color rules: the color currently chosen for [top, bottom] line.
std::mutex g_clockRuleMutex;
std::wstring g_clockRuleColor[2];
std::atomic<int> g_colorRuleCount{0};

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
    // Profiles can switch to any of their presets at runtime, so every one of
    // them has to count as used (metrics, threads and sessions start for them).
    for (const auto& r : g_settings.profileRules) {
        if (!r.preset) continue;
        if (wcsstr(r.preset->top, str) || wcsstr(r.preset->bottom, str) || wcsstr(r.preset->tooltip, str)) {
            return true;
        }
        if (wcsstr(r.preset->top, L"%media_info%") || wcsstr(r.preset->bottom, L"%media_info%") ||
            wcsstr(r.preset->tooltip, L"%media_info%")) {
            if (wcsstr(g_settings.mediaPlayer.mediaInfoFormat.get(), str) ||
                wcsstr(g_settings.mediaPlayer.noMediaText.get(), str)) {
                return true;
            }
        }
    }
    if (wcsstr(EffTopLine(), str) || wcsstr(EffBottomLine(), str) ||
        wcsstr(g_settings.middleLine, str) || wcsstr(EffTooltipLine(), str)) {
        return true;
    }
    if (wcsstr(EffTopLine(), L"%media_info%") || wcsstr(EffBottomLine(), L"%media_info%") ||
        wcsstr(g_settings.middleLine, L"%media_info%") || wcsstr(EffTooltipLine(), L"%media_info%")) {
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

// ----- WEATHER FALLBACK (Open-Meteo) -----
//
// wttr.in is a single volunteer-run service that is often rate limited. When it
// does not answer, the weather is fetched from Open-Meteo instead (no API key).
// Supported format placeholders: %c condition icon, %t temperature, %w wind,
// %h humidity, %l location, %S sunrise, %s sunset.

bool JsonFindNumber(const std::wstring& json, size_t from, PCWSTR key, double* out) {
    std::wstring needle = L"\"" + std::wstring(key) + L"\":";
    size_t p = json.find(needle, from);
    if (p == std::wstring::npos) return false;
    p += needle.size();
    PWSTR end = nullptr;
    double v = wcstod(json.c_str() + p, &end);
    if (end == json.c_str() + p) return false;
    *out = v;
    return true;
}

std::wstring JsonFindString(const std::wstring& json, size_t from, PCWSTR key) {
    std::wstring needle = L"\"" + std::wstring(key) + L"\":\"";
    size_t p = json.find(needle, from);
    if (p == std::wstring::npos) return {};
    p += needle.size();
    size_t e = json.find(L'"', p);
    if (e == std::wstring::npos) return {};
    return json.substr(p, e - p);
}

PCWSTR WeatherCodeIcon(int code) {
    if (code == 0) return L"☀️";
    if (code <= 2) return L"\U0001F324️";
    if (code == 3) return L"☁️";
    if (code == 45 || code == 48) return L"\U0001F32B️";
    if (code >= 51 && code <= 57) return L"\U0001F326️";
    if (code >= 61 && code <= 67) return L"\U0001F327️";
    if (code >= 71 && code <= 77) return L"\U0001F328️";
    if (code >= 80 && code <= 82) return L"\U0001F327️";
    if (code == 85 || code == 86) return L"\U0001F328️";
    if (code >= 95) return L"⛈️";
    return L"❓";
}

bool WeatherUnitsAreImperial() {
    switch (g_settings.webContentWeatherUnits) {
        case WebContentWeatherUnits::uscs: return true;
        case WebContentWeatherUnits::metric:
        case WebContentWeatherUnits::metricMsWind: return false;
        default: break;
    }
    DWORD measure = 0;
    if (GetLocaleInfoEx(LOCALE_NAME_USER_DEFAULT, LOCALE_IMEASURE | LOCALE_RETURN_NUMBER,
                        reinterpret_cast<LPWSTR>(&measure), sizeof(measure) / sizeof(WCHAR)) == 0) {
        return false;
    }
    return measure == 1;  // 1 = US measurement system
}

bool UpdateWeatherFallback(const std::wstring& format) {
    double lat = 0, lon = 0;
    std::wstring place;
    const std::wstring location = g_settings.webContentWeatherLocation.get();

    if (location.empty()) {
        auto ip = GetUrlContent(L"http://ip-api.com/json/?fields=status,city,lat,lon");
        if (!ip || !JsonFindNumber(*ip, 0, L"lat", &lat) || !JsonFindNumber(*ip, 0, L"lon", &lon)) return false;
        place = JsonFindString(*ip, 0, L"city");
    } else {
        auto geo = GetUrlContent((L"https://geocoding-api.open-meteo.com/v1/search?count=1&name=" +
                                  EscapeUrlComponent(location.c_str())).c_str());
        if (!geo || !JsonFindNumber(*geo, 0, L"latitude", &lat) || !JsonFindNumber(*geo, 0, L"longitude", &lon)) {
            return false;
        }
        place = JsonFindString(*geo, 0, L"name");
    }

    const bool imperial = WeatherUnitsAreImperial();
    const bool windMs = g_settings.webContentWeatherUnits == WebContentWeatherUnits::metricMsWind;
    WCHAR url[512];
    swprintf_s(url,
               L"https://api.open-meteo.com/v1/forecast?latitude=%.4f&longitude=%.4f"
               L"&current=temperature_2m,relative_humidity_2m,weather_code,wind_speed_10m"
               L"&daily=sunrise,sunset&forecast_days=1&timezone=auto%s",
               lat, lon,
               imperial ? L"&temperature_unit=fahrenheit&wind_speed_unit=mph"
                        : (windMs ? L"&wind_speed_unit=ms" : L""));
    auto forecast = GetUrlContent(url);
    if (!forecast) return false;

    size_t cur = forecast->find(L"\"current\":{");
    if (cur == std::wstring::npos) return false;
    double temp = 0, hum = 0, code = 0, wind = 0;
    if (!JsonFindNumber(*forecast, cur, L"temperature_2m", &temp)) return false;
    JsonFindNumber(*forecast, cur, L"relative_humidity_2m", &hum);
    JsonFindNumber(*forecast, cur, L"weather_code", &code);
    JsonFindNumber(*forecast, cur, L"wind_speed_10m", &wind);

    auto timeOf = [&](PCWSTR key) -> std::wstring {
        std::wstring needle = L"\"" + std::wstring(key) + L"\":[\"";
        size_t p = forecast->find(needle);
        if (p == std::wstring::npos) return L"-";
        p += needle.size();
        size_t t = forecast->find(L'T', p);
        if (t == std::wstring::npos || t + 6 > forecast->size()) return L"-";
        return forecast->substr(t + 1, 5);
    };

    WCHAR num[48];
    std::wstring out;
    for (size_t i = 0; i < format.size(); i++) {
        if (format[i] != L'%' || i + 1 >= format.size()) {
            out += format[i];
            continue;
        }
        wchar_t c = format[++i];
        switch (c) {
            case L'c': out += WeatherCodeIcon(static_cast<int>(code)); break;
            case L't':
                swprintf_s(num, L"%d°%c", static_cast<int>(std::lround(temp)), imperial ? L'F' : L'C');
                out += num;
                break;
            case L'w':
                swprintf_s(num, L"%d%s", static_cast<int>(std::lround(wind)), imperial ? L"mph" : (windMs ? L"m/s" : L"km/h"));
                out += num;
                break;
            case L'h':
                swprintf_s(num, L"%d%%", static_cast<int>(std::lround(hum)));
                out += num;
                break;
            case L'l': out += place; break;
            case L'S': out += timeOf(L"sunrise"); break;
            case L's': out += timeOf(L"sunset"); break;
            case L'%': out += L'%'; break;
            default: break;  // unsupported placeholder
        }
    }

    std::lock_guard<std::mutex> guard(g_webContentMutex);
    g_webContentWeather = out;
    return true;
}

bool UpdateWeatherWebContent() {
    std::wstring format;
    switch (g_settings.weatherPreset) {
        case 1: format = L"%c %t"; break;
        case 2: format = L"\U0001F305 %S  \U0001F307 %s"; break;
        case 3: format = L"%c %t  \U0001F4A7%h  \U0001F32C\uFE0F%w  \U0001F305%S \U0001F307%s"; break;
        default: format = g_settings.webContentWeatherFormat.get(); break;
    }
    if (format.empty()) format = L"%c \U0001F321\uFE0F%t \U0001F32C\uFE0F%w";
    const std::wstring plainFormat = format;
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
    if (!urlContent || urlContent->empty() || *urlContent == L"This query is already being processed") {
        // wttr.in is down or rate limiting: try the fallback provider.
        return g_settings.weatherFallback && UpdateWeatherFallback(plainFormat);
    }

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

// ----- CALENDAR EVENTS (ICS) -----

struct IcsRule {
    int freq = 0;  // 0 none, 1 daily, 2 weekly, 3 monthly, 4 yearly
    int interval = 1;
    int count = 0;  // 0 = unlimited
    int64_t until = INT64_MAX;
    unsigned byDayMask = 0;  // bit 0 = Monday ... bit 6 = Sunday (weekly only)
    int byMonthDay = 0;      // monthly only
    bool unsupported = false;
};

struct IcsEvent {
    std::wstring uid;
    std::wstring summary;
    int64_t start = 0;  // local wall-clock seconds since 1970-01-01
    bool allDay = false;
    IcsRule rule;
    std::vector<int64_t> exdates;
};

// Converts a UTC timestamp (seconds) to local wall-clock seconds.
int64_t (*g_icsUtcToLocal)(int64_t) = [](int64_t utc) { return utc; };

int64_t IcsDaysFromCivil(int y, unsigned m, unsigned d) {
    y -= m <= 2;
    const int64_t era = (y >= 0 ? y : y - 399) / 400;
    const unsigned yoe = static_cast<unsigned>(y - era * 400);
    const unsigned doy = (153 * (m + (m > 2 ? -3 : 9)) + 2) / 5 + d - 1;
    const unsigned doe = yoe * 365 + yoe / 4 - yoe / 100 + doy;
    return era * 146097 + static_cast<int64_t>(doe) - 719468;
}

void IcsCivilFromDays(int64_t z, int* y, unsigned* m, unsigned* d) {
    z += 719468;
    const int64_t era = (z >= 0 ? z : z - 146096) / 146097;
    const unsigned doe = static_cast<unsigned>(z - era * 146097);
    const unsigned yoe = (doe - doe / 1460 + doe / 36524 - doe / 146096) / 365;
    const int64_t yy = static_cast<int64_t>(yoe) + era * 400;
    const unsigned doy = doe - (365 * yoe + yoe / 4 - yoe / 100);
    const unsigned mp = (5 * doy + 2) / 153;
    *d = doy - (153 * mp + 2) / 5 + 1;
    *m = mp < 10 ? mp + 3 : mp - 9;
    *y = static_cast<int>(yy + (*m <= 2));
}

int64_t IcsFloorDiv(int64_t a, int64_t b) {
    int64_t q = a / b;
    return (a % b != 0 && ((a < 0) != (b < 0))) ? q - 1 : q;
}

int IcsDaysInMonth(int y, int m) {
    static const int kDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (m == 2 && ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0)) return 29;
    return kDays[m - 1];
}

// 0 = Monday ... 6 = Sunday
int IcsWeekday(int64_t days) {
    return static_cast<int>(((days + 3) % 7 + 7) % 7);
}

bool IcsParseDateTime(std::wstring_view v, bool* isDate, int64_t* outLocal) {
    auto num = [&](size_t pos, size_t len, int* out) {
        int r = 0;
        for (size_t i = 0; i < len; i++) {
            if (pos + i >= v.size() || v[pos + i] < L'0' || v[pos + i] > L'9') return false;
            r = r * 10 + (v[pos + i] - L'0');
        }
        *out = r;
        return true;
    };
    int y, mo, d, h = 0, mi = 0, s = 0;
    if (!num(0, 4, &y) || !num(4, 2, &mo) || !num(6, 2, &d)) return false;
    if (mo < 1 || mo > 12 || d < 1 || d > IcsDaysInMonth(y, mo)) return false;
    *isDate = true;
    bool utc = false;
    if (v.size() >= 15 && v[8] == L'T') {
        if (!num(9, 2, &h) || !num(11, 2, &mi) || !num(13, 2, &s)) return false;
        *isDate = false;
        utc = v.size() >= 16 && v[15] == L'Z';
    }
    int64_t secs = IcsDaysFromCivil(y, mo, d) * 86400 + h * 3600 + mi * 60 + s;
    *outLocal = utc ? g_icsUtcToLocal(secs) : secs;
    return true;
}

std::wstring IcsUnescape(std::wstring_view v) {
    std::wstring r;
    for (size_t i = 0; i < v.size(); i++) {
        if (v[i] == L'\\' && i + 1 < v.size()) {
            wchar_t c = v[++i];
            r += (c == L'n' || c == L'N') ? L' ' : c;
        } else {
            r += v[i];
        }
    }
    return r;
}

void IcsParseRule(std::wstring_view v, const IcsEvent& e, IcsRule* r) {
    size_t pos = 0;
    bool hasByDay = false, hasOther = false;
    while (pos <= v.size()) {
        size_t end = v.find(L';', pos);
        if (end == std::wstring_view::npos) end = v.size();
        std::wstring_view part = v.substr(pos, end - pos);
        pos = end + 1;
        size_t eq = part.find(L'=');
        if (eq == std::wstring_view::npos) continue;
        std::wstring key(part.substr(0, eq));
        std::wstring val(part.substr(eq + 1));
        for (auto& c : key) c = static_cast<wchar_t>(towupper(c));
        for (auto& c : val) c = static_cast<wchar_t>(towupper(c));

        if (key == L"FREQ") {
            r->freq = val == L"DAILY" ? 1 : val == L"WEEKLY" ? 2 : val == L"MONTHLY" ? 3 : val == L"YEARLY" ? 4 : -1;
        } else if (key == L"INTERVAL") {
            r->interval = std::max(1, _wtoi(val.c_str()));
        } else if (key == L"COUNT") {
            r->count = std::max(0, _wtoi(val.c_str()));
        } else if (key == L"UNTIL") {
            bool isDate;
            int64_t t;
            if (IcsParseDateTime(val, &isDate, &t)) r->until = isDate ? t + 86399 : t;
        } else if (key == L"BYDAY") {
            hasByDay = true;
            static const wchar_t* kDays[] = {L"MO", L"TU", L"WE", L"TH", L"FR", L"SA", L"SU"};
            size_t p = 0;
            while (p < val.size()) {
                size_t c = val.find(L',', p);
                if (c == std::wstring::npos) c = val.size();
                std::wstring d = val.substr(p, c - p);
                p = c + 1;
                bool matched = false;
                for (int i = 0; i < 7; i++) {
                    if (d == kDays[i]) {
                        r->byDayMask |= 1u << i;
                        matched = true;
                    }
                }
                if (!matched) r->unsupported = true;  // e.g. 2TU (ordinal)
            }
        } else if (key == L"BYMONTHDAY") {
            int d = _wtoi(val.c_str());
            if (val.find(L',') != std::wstring::npos || d < 1 || d > 31) r->unsupported = true;
            else r->byMonthDay = d;
        } else if (key == L"WKST") {
            // week start is assumed Monday
        } else if (key == L"BYMONTH" || key == L"BYSETPOS" || key == L"BYYEARDAY" || key == L"BYWEEKNO" ||
                   key == L"BYHOUR" || key == L"BYMINUTE" || key == L"BYSECOND") {
            hasOther = true;
        }
    }
    if (r->freq < 0 || hasOther) r->unsupported = true;
    if (hasByDay && r->freq != 2) r->unsupported = true;
    if (r->byMonthDay && r->freq != 3) r->unsupported = true;
    (void)e;
}

std::vector<IcsEvent> IcsParse(const std::wstring& text, bool includeAllDay) {
    // Unfold lines
    std::vector<std::wstring> lines;
    size_t pos = 0;
    while (pos < text.size()) {
        size_t nl = text.find(L'\n', pos);
        if (nl == std::wstring::npos) nl = text.size();
        std::wstring line = text.substr(pos, nl - pos);
        pos = nl + 1;
        if (!line.empty() && line.back() == L'\r') line.pop_back();
        if (!line.empty() && (line[0] == L' ' || line[0] == L'\t') && !lines.empty()) {
            lines.back() += line.substr(1);
        } else {
            lines.push_back(std::move(line));
        }
    }

    std::vector<IcsEvent> events;
    std::vector<std::pair<std::wstring, int64_t>> overrides;  // uid, original start
    bool inEvent = false;
    IcsEvent cur;
    bool cancelled = false, haveStart = false, hasRecurrenceId = false;
    int64_t recurrenceId = 0;
    std::wstring rruleValue;

    for (const auto& line : lines) {
        if (line == L"BEGIN:VEVENT") {
            inEvent = true;
            cur = IcsEvent();
            cancelled = haveStart = hasRecurrenceId = false;
            rruleValue.clear();
            continue;
        }
        if (line == L"END:VEVENT") {
            if (inEvent && haveStart && !cancelled && (includeAllDay || !cur.allDay)) {
                if (!rruleValue.empty()) IcsParseRule(rruleValue, cur, &cur.rule);
                if (hasRecurrenceId) overrides.emplace_back(cur.uid, recurrenceId);
                events.push_back(cur);
            }
            inEvent = false;
            continue;
        }
        if (!inEvent) continue;

        size_t colon = std::wstring::npos;
        bool quoted = false;
        for (size_t i = 0; i < line.size(); i++) {
            if (line[i] == L'"') quoted = !quoted;
            else if (line[i] == L':' && !quoted) {
                colon = i;
                break;
            }
        }
        if (colon == std::wstring::npos) continue;
        std::wstring nameAndParams = line.substr(0, colon);
        std::wstring value = line.substr(colon + 1);
        size_t semi = nameAndParams.find(L';');
        std::wstring name = nameAndParams.substr(0, semi);
        for (auto& c : name) c = static_cast<wchar_t>(towupper(c));

        if (name == L"DTSTART") {
            bool isDate;
            if (IcsParseDateTime(value, &isDate, &cur.start)) {
                haveStart = true;
                cur.allDay = isDate;
            }
        } else if (name == L"SUMMARY") {
            cur.summary = IcsUnescape(value);
        } else if (name == L"UID") {
            cur.uid = value;
        } else if (name == L"STATUS") {
            std::wstring v = value;
            for (auto& c : v) c = static_cast<wchar_t>(towupper(c));
            if (v == L"CANCELLED") cancelled = true;
        } else if (name == L"RRULE") {
            rruleValue = value;
        } else if (name == L"RECURRENCE-ID") {
            bool isDate;
            if (IcsParseDateTime(value, &isDate, &recurrenceId)) hasRecurrenceId = true;
        } else if (name == L"EXDATE") {
            size_t p = 0;
            while (p <= value.size()) {
                size_t c = value.find(L',', p);
                if (c == std::wstring::npos) c = value.size();
                bool isDate;
                int64_t t;
                if (IcsParseDateTime(std::wstring_view(value).substr(p, c - p), &isDate, &t)) cur.exdates.push_back(t);
                p = c + 1;
            }
        }
    }

    // A modified instance replaces the matching occurrence of its series.
    for (const auto& [uid, orig] : overrides) {
        for (auto& e : events) {
            if (e.uid == uid && e.rule.freq != 0) e.exdates.push_back(orig);
        }
    }
    return events;
}

bool IcsNextOccurrence(const IcsEvent& e, int64_t now, int64_t* out) {
    auto excluded = [&](int64_t t) {
        return std::find(e.exdates.begin(), e.exdates.end(), t) != e.exdates.end();
    };
    const IcsRule& r = e.rule;
    if (r.freq == 0 || r.unsupported) {
        if (e.start >= now && !excluded(e.start)) {
            *out = e.start;
            return true;
        }
        return false;
    }

    const int64_t startDay = IcsFloorDiv(e.start, 86400);
    const int64_t tod = e.start - startDay * 86400;
    const int64_t nowDay = IcsFloorDiv(now, 86400);
    int emitted = 0;

    // 1 = found, -1 = series ended, 0 = keep going
    auto consider = [&](int64_t t) {
        if (t < e.start) return 0;
        if (t > r.until) return -1;
        emitted++;
        if (r.count && emitted > r.count) return -1;
        if (t >= now && !excluded(t)) {
            *out = t;
            return 1;
        }
        return 0;
    };
    const bool canSkip = r.count == 0;
    constexpr int kMaxIterations = 20000;

    if (r.freq == 1) {
        int64_t k0 = canSkip ? std::max<int64_t>(0, (nowDay - startDay) / r.interval - 1) : 0;
        for (int64_t k = k0, n = 0; n < kMaxIterations; k++, n++) {
            int res = consider((startDay + k * r.interval) * 86400 + tod);
            if (res) return res > 0;
        }
    } else if (r.freq == 2) {
        const int64_t weekStart = startDay - IcsWeekday(startDay);
        unsigned mask = r.byDayMask ? r.byDayMask : (1u << IcsWeekday(startDay));
        int64_t w0 = canSkip ? std::max<int64_t>(0, (nowDay - weekStart) / (7 * r.interval) - 1) : 0;
        for (int64_t w = w0, n = 0; n < kMaxIterations; w++, n++) {
            int64_t base = weekStart + w * 7 * r.interval;
            for (int wd = 0; wd < 7; wd++) {
                if (!(mask & (1u << wd))) continue;
                int res = consider((base + wd) * 86400 + tod);
                if (res) return res > 0;
            }
        }
    } else if (r.freq == 3 || r.freq == 4) {
        int sy;
        unsigned sm, sd;
        IcsCivilFromDays(startDay, &sy, &sm, &sd);
        int ny;
        unsigned nm, nd;
        IcsCivilFromDays(nowDay, &ny, &nm, &nd);
        const int day = (r.freq == 3 && r.byMonthDay) ? r.byMonthDay : static_cast<int>(sd);
        const int64_t startIdx = static_cast<int64_t>(sy) * 12 + (sm - 1);
        const int64_t nowIdx = static_cast<int64_t>(ny) * 12 + (nm - 1);
        const int64_t unit = r.freq == 3 ? 1 : 12;  // months per period unit
        int64_t p0 = canSkip ? std::max<int64_t>(0, (nowIdx - startIdx) / (unit * r.interval) - 1) : 0;
        for (int64_t p = p0, n = 0; n < kMaxIterations; p++, n++) {
            int64_t idx = startIdx + p * unit * r.interval;
            int yy = static_cast<int>(IcsFloorDiv(idx, 12));
            int mm = static_cast<int>(idx - static_cast<int64_t>(yy) * 12) + 1;
            if (day > IcsDaysInMonth(yy, mm)) continue;
            int res = consider(IcsDaysFromCivil(yy, mm, day) * 86400 + tod);
            if (res) return res > 0;
        }
    }
    return false;
}

struct IcsNext {
    bool found = false;
    std::wstring summary;
    int64_t start = 0;
};

IcsNext IcsFindNext(const std::vector<IcsEvent>& events, int64_t nowLocal) {
    IcsNext best;
    for (const auto& e : events) {
        int64_t t;
        if (IcsNextOccurrence(e, nowLocal, &t) && (!best.found || t < best.start)) {
            best.found = true;
            best.start = t;
            best.summary = e.summary;
        }
    }
    return best;
}

std::wstring IcsFormatIn(int64_t diffSeconds) {
    if (diffSeconds < 60) return L"now";
    unsigned total = static_cast<unsigned>(std::min<int64_t>(diffSeconds, 4000000000LL));
    unsigned d = total / 86400, h = (total % 86400) / 3600, m = (total % 3600) / 60;
    WCHAR buf[48];
    if (d) swprintf_s(buf, L"in %ud %uh", d, h);
    else if (h) { if (m) swprintf_s(buf, L"in %uh %um", h, m); else swprintf_s(buf, L"in %uh", h); }
    else swprintf_s(buf, L"in %um", m);
    return buf;
}

// ----- PURE HELPERS (calendar conversion, parsing, text effects) -----

struct BengaliDate {
    int year;
    int month;  // 1 = Boishakh ... 12 = Choitro
    int day;
};

// Bangladesh revised Bengali calendar (Bangla Academy, 1987): the new year is
// April 14; months 1-6 have 31 days, 7-11 have 30, Falgun (11) has 29 (30 in a
// leap year) and Choitro (12) has 30. The Gregorian date on which each month
// starts is the same every year.
BengaliDate GregorianToBengali(int y, int m, int d) {
    struct Start { int gm, gd, bengaliMonth; };
    static const Start kStarts[12] = {
        {1, 15, 10}, {2, 14, 11}, {3, 15, 12}, {4, 14, 1},  {5, 15, 2},  {6, 15, 3},
        {7, 16, 4},  {8, 16, 5},  {9, 16, 6},  {10, 17, 7}, {11, 16, 8}, {12, 16, 9},
    };
    int idx = -1;
    for (int i = 0; i < 12; i++) {
        if (m > kStarts[i].gm || (m == kStarts[i].gm && d >= kStarts[i].gd)) idx = i;
    }
    int startYear = y, gm, gd, bm;
    if (idx < 0) {  // before January 15: still Poush, which began on December 16
        startYear = y - 1;
        gm = 12;
        gd = 16;
        bm = 9;
    } else {
        gm = kStarts[idx].gm;
        gd = kStarts[idx].gd;
        bm = kStarts[idx].bengaliMonth;
    }
    BengaliDate r;
    r.month = bm;
    r.day = static_cast<int>(IcsDaysFromCivil(y, m, d) - IcsDaysFromCivil(startYear, gm, gd)) + 1;
    r.year = (m > 4 || (m == 4 && d >= 14)) ? y - 593 : y - 594;
    return r;
}

std::wstring ToBanglaDigits(const std::wstring& s) {
    std::wstring r = s;
    for (auto& c : r) {
        if (c >= L'0' && c <= L'9') c = static_cast<wchar_t>(0x09E6 + (c - L'0'));
    }
    return r;
}

// Dotted-quad IPv4 address in network byte order (as used by IcmpSendEcho).
bool ParseIPv4(const std::wstring& s, unsigned long* out) {
    unsigned long parts[4];
    const wchar_t* p = s.c_str();
    for (int i = 0; i < 4; i++) {
        if (*p < L'0' || *p > L'9') return false;
        wchar_t* end;
        unsigned long v = wcstoul(p, &end, 10);
        if (v > 255 || end == p) return false;
        parts[i] = v;
        p = end;
        if (i < 3) {
            if (*p != L'.') return false;
            p++;
        }
    }
    if (*p != L'\0') return false;
    *out = parts[0] | (parts[1] << 8) | (parts[2] << 16) | (parts[3] << 24);
    return true;
}

// "m:ss", or "h:mm:ss" from one hour up.
std::wstring FormatMediaClock(double seconds) {
    if (seconds < 0) seconds = 0;
    unsigned total = static_cast<unsigned>(std::min(seconds, 359999.0));
    unsigned h = total / 3600, m = (total % 3600) / 60, s = total % 60;
    WCHAR buf[24];
    if (h) swprintf_s(buf, L"%u:%02u:%02u", h, m, s);
    else swprintf_s(buf, L"%u:%02u", m, s);
    return buf;
}

std::wstring MediaProgressBar(double position, double duration, int cells) {
    if (duration <= 0 || cells <= 0) return L"";
    double frac = std::min(std::max(position / duration, 0.0), 1.0);
    int filled = static_cast<int>(frac * cells + 0.5);
    std::wstring bar;
    for (int i = 0; i < cells; i++) bar += i < filled ? L'\u25B0' : L'\u25B1';
    return bar;
}

// A scrolling window over text + gap, `window` characters wide, starting at
// `offset`. Never starts or ends in the middle of a surrogate pair.
std::wstring MarqueeWindow(const std::wstring& text, size_t window, size_t offset) {
    if (text.size() <= window || window == 0) return text;
    const std::wstring cycle = text + L"   ";
    offset %= cycle.size();
    auto isLow = [](wchar_t c) { return c >= 0xDC00 && c <= 0xDFFF; };
    auto isHigh = [](wchar_t c) { return c >= 0xD800 && c <= 0xDBFF; };
    if (isLow(cycle[offset])) offset = (offset + 1) % cycle.size();
    std::wstring out;
    for (size_t i = 0; i < window; i++) out += cycle[(offset + i) % cycle.size()];
    if (!out.empty() && isHigh(out.back())) out.back() = L' ';
    return out;
}

int64_t IcsUtcToLocalWindows(int64_t utc) {
    ULARGE_INTEGER u;
    u.QuadPart = static_cast<ULONGLONG>(utc + 11644473600LL) * 10000000ULL;
    FILETIME ft{u.LowPart, u.HighPart};
    SYSTEMTIME stUtc, stLocal;
    if (!FileTimeToSystemTime(&ft, &stUtc) || !SystemTimeToTzSpecificLocalTime(nullptr, &stUtc, &stLocal)) return utc;
    return IcsDaysFromCivil(stLocal.wYear, stLocal.wMonth, stLocal.wDay) * 86400 + stLocal.wHour * 3600 +
           stLocal.wMinute * 60 + stLocal.wSecond;
}

std::vector<IcsEvent> g_icsEvents;  // guarded by g_webContentMutex
unsigned g_icsVersion = 0;          // guarded by g_webContentMutex

bool UpdateCalendarEvents() {
    if (g_settings.icsUrl.empty()) return true;
    std::wstring url = g_settings.icsUrl;
    if (url.rfind(L"webcal://", 0) == 0) url = L"https://" + url.substr(9);

    auto content = GetUrlContent(url.c_str());
    if (!content) return false;

    g_icsUtcToLocal = IcsUtcToLocalWindows;
    std::vector<IcsEvent> events;
    try {
        events = IcsParse(*content, g_settings.icsIncludeAllDay);
    } catch (...) {
        return false;
    }

    std::lock_guard<std::mutex> guard(g_webContentMutex);
    g_icsEvents = std::move(events);
    g_icsVersion++;
    return true;
}

void UpdateWebContent() {
    int failed = 0;
    std::wstring lastUrl;
    std::optional<std::wstring> urlContent;

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
    if (IsStrInDateTimePatternSettings(L"%next_event") && !UpdateCalendarEvents()) failed++;
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
    if (IsStrInDateTimePatternSettings(L"%web") || IsStrInDateTimePatternSettings(L"%weather%") ||
        IsStrInDateTimePatternSettings(L"%next_event")) {
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

// ----- PERFORMANCE DATA COLLECTION -----

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

enum GraphKind { kGraphCpu, kGraphRam, kGraphGpu, kGraphDownload, kGraphUpload, kGraphDisk, kGraphCount };
constexpr int kGraphMaxLength = 32;

struct GraphHistory {
    double v[kGraphMaxLength];
    int count;
    void Push(double x) {
        if (count < kGraphMaxLength) {
            v[count++] = x;
        } else {
            memmove(v, v + 1, sizeof(double) * (kGraphMaxLength - 1));
            v[kGraphMaxLength - 1] = x;
        }
    }
};

GraphHistory g_graphHistory[kGraphCount];
bool g_graphUsed[kGraphCount];
FormattedString<FORMATTED_BUFFER_SIZE> g_graphFormatted[kGraphCount];

enum RuleMetric {
    kRuleNone, kRuleCpu, kRuleRam, kRuleGpu, kRuleCpuTemp, kRuleBattery,
    // Extra values that only the %if(...)% tag can test
    kRuleCharging, kRuleHour, kRuleMinute, kRuleWeekday, kRuleCpuFreq,
};

bool ColorRulesUseMetric(int metric) {
    for (const auto& r : g_settings.colorRules) {
        if (r.metric == metric) return true;
    }
    return false;
}

// ----- MEDIA PLAYER INTEGRATION -----

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
    g_mediaPlaying = false;
    g_mediaTimeline.valid = false;
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
        g_mediaPlaying = status == Status::Playing;
        g_mediaTimelineLastQuery = 0;  // track or state changed: re-read the timeline
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

// Reads the playback position and duration of the active session (at most
// every 3 seconds). Between reads the position is extrapolated while playing.
void QueryMediaTimelineIfNeeded() {
    ULONGLONG now = GetTickCount64() | 1;
    if (g_mediaTimelineLastQuery && now - g_mediaTimelineLastQuery < 3000) return;
    g_mediaTimelineLastQuery = now;

    std::lock_guard<std::mutex> guard(g_mediaMutex);
    g_mediaTimeline.valid = false;
    try {
        if (!g_mediaSessionManager) return;
        auto session = FindActiveMediaSession();
        if (!session) return;

        auto toSeconds = [](auto ts) { return std::chrono::duration_cast<std::chrono::duration<double>>(ts).count(); };
        auto timeline = session.GetTimelineProperties();
        double start = toSeconds(timeline.StartTime());
        double end = toSeconds(timeline.EndTime());
        double position = toSeconds(timeline.Position()) - start;

        auto info = session.GetPlaybackInfo();
        bool playing = info.PlaybackStatus() ==
                       winrt::Windows::Media::Control::GlobalSystemMediaTransportControlsSessionPlaybackStatus::Playing;
        double rate = 1;
        if (auto r = info.PlaybackRate()) rate = r.Value();
        if (playing) {
            double elapsed = toSeconds(winrt::clock::now() - timeline.LastUpdatedTime());
            if (elapsed > 0 && elapsed < 86400) position += elapsed * rate;
        }

        g_mediaTimeline.position = std::max(position, 0.0);
        g_mediaTimeline.duration = std::max(end - start, 0.0);
        g_mediaTimeline.rate = rate;
        g_mediaTimeline.queryTick = now;
        g_mediaTimeline.valid = true;
        g_mediaPlaying = playing;
    } catch (...) {}
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

    static const PCWSTR kGraphTags[kGraphCount] = {
        L"%cpu_graph%", L"%ram_graph%", L"%gpu_graph%", L"%download_graph%", L"%upload_graph%", L"%disk_graph%",
    };
    for (int i = 0; i < kGraphCount; i++) {
        g_graphUsed[i] = IsStrInDateTimePatternSettings(kGraphTags[i]);
        g_graphHistory[i].count = 0;
    }
    auto enable = [&](MetricType m, bool on) {
        if (on) metrics[static_cast<int>(m)] = true;
    };
    enable(MetricType::kCpu, g_graphUsed[kGraphCpu] || ColorRulesUseMetric(kRuleCpu));
    enable(MetricType::kGpuUsage, g_graphUsed[kGraphGpu] || ColorRulesUseMetric(kRuleGpu));
    enable(MetricType::kCpuTemp, ColorRulesUseMetric(kRuleCpuTemp));
    enable(MetricType::kCpu, IsStrInDateTimePatternSettings(L"%if(cpu"));
    enable(MetricType::kGpuUsage, IsStrInDateTimePatternSettings(L"%if(gpu"));
    enable(MetricType::kCpuTemp, IsStrInDateTimePatternSettings(L"%if(cpu_temp"));
    enable(MetricType::kDownloadSpeed, g_graphUsed[kGraphDownload]);
    enable(MetricType::kUploadSpeed, g_graphUsed[kGraphUpload]);
    enable(MetricType::kDiskReadSpeed, g_graphUsed[kGraphDisk]);
    enable(MetricType::kDiskWriteSpeed, g_graphUsed[kGraphDisk]);

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
    return IsStrInDateTimePatternSettings(L"%media_");
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

// Update interval in seconds, using the slower "on battery" interval when
// the PC is unplugged. The power state is checked at most every 5 seconds.
int GetEffectiveUpdateInterval() {
    int normal = std::max(g_settings.dataCollection.updateInterval, 1);
    int onBattery = g_settings.dataCollection.batteryUpdateInterval;
    if (onBattery <= normal) return normal;

    static ULONGLONG s_lastCheck = 0;
    static bool s_onBattery = false;
    ULONGLONG now = GetTickCount64() | 1;
    if (!s_lastCheck || now - s_lastCheck >= 5000) {
        SYSTEM_POWER_STATUS ps;
        s_onBattery = GetSystemPowerStatus(&ps) && ps.ACLineStatus == 0;
        s_lastCheck = now;
    }
    return s_onBattery ? onBattery : normal;
}

DWORD GetDataCollectionFormatIndex() {
    FILETIME ft{};
    SystemTimeToFileTime(&g_formatTime, &ft);
    ULARGE_INTEGER i{.LowPart = ft.dwLowDateTime, .HighPart = ft.dwHighDateTime};
    ULONGLONG interval = 10000000ULL * GetEffectiveUpdateInterval();
    return static_cast<DWORD>(i.QuadPart / interval);
}

void RecordGraphHistory();

void DataCollectionSampleIfNeeded() {
    DWORD idx = GetDataCollectionFormatIndex();
    if (g_dataCollectionLastFormatIndex != idx) {
        if (g_dataCollectionSession) {
            g_dataCollectionSession->UpdateAllMetrics();
            g_dataCollectionSession->SampleData();
        }
        RecordGraphHistory();
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

// ----- NETWORK INFO, ALTERNATE CALENDARS, NEXT EVENT -----

// Network snapshot, refreshed at most every 5 seconds.

struct NetworkSnapshot {
    std::wstring ssid;
    int signalPercent = -1;
    bool vpn = false;
    std::wstring localIp;
    ULONGLONG tick = 0;
} g_net;

void RefreshNetworkSnapshotIfNeeded() {
    ULONGLONG now = GetTickCount64() | 1;
    if (g_net.tick && now - g_net.tick < 5000) return;
    g_net = NetworkSnapshot();
    g_net.tick = now;
    try {
        namespace Conn = winrt::Windows::Networking::Connectivity;
        auto profile = Conn::NetworkInformation::GetInternetConnectionProfile();
        if (profile) {
            if (profile.IsWlanConnectionProfile()) {
                g_net.ssid = std::wstring(profile.WlanConnectionProfileDetails().GetConnectedSsid());
            }
            // The API reports 0-5 signal bars, not a percentage.
            if (auto bars = profile.GetSignalBars()) g_net.signalPercent = bars.Value() * 20;
            if (auto adapter = profile.NetworkAdapter()) {
                for (auto const& hostName : Conn::NetworkInformation::GetHostNames()) {
                    if (hostName.Type() != winrt::Windows::Networking::HostNameType::Ipv4) continue;
                    auto ipInfo = hostName.IPInformation();
                    if (ipInfo && ipInfo.NetworkAdapter() &&
                        ipInfo.NetworkAdapter().NetworkAdapterId() == adapter.NetworkAdapterId()) {
                        g_net.localIp = std::wstring(hostName.CanonicalName());
                        break;
                    }
                }
            }
        }

        // Best effort: a connected profile on a PPP / tunnel / virtual adapter, or named "VPN".
        for (auto const& p : Conn::NetworkInformation::GetConnectionProfiles()) {
            if (p.GetNetworkConnectivityLevel() == Conn::NetworkConnectivityLevel::None) continue;
            auto adapter = p.NetworkAdapter();
            if (!adapter) continue;
            uint32_t type = adapter.IanaInterfaceType();
            bool vpnLike = type == 23 || type == 131 || type == 53;
            if (!vpnLike) {
                std::wstring name(p.ProfileName());
                for (auto& c : name) c = static_cast<wchar_t>(towlower(c));
                vpnLike = name.find(L"vpn") != std::wstring::npos;
            }
            if (vpnLike) {
                g_net.vpn = true;
                break;
            }
        }
    } catch (...) {}
}

PCWSTR GetWifiSsidFormatted() {
    RefreshNetworkSnapshotIfNeeded();
    return g_net.ssid.c_str();
}

PCWSTR GetWifiSignalFormatted() {
    RefreshNetworkSnapshotIfNeeded();
    static WCHAR buf[8];
    if (g_net.signalPercent < 0) return L"";
    swprintf_s(buf, L"%d%%", g_net.signalPercent);
    return buf;
}

PCWSTR GetVpnFormatted() {
    RefreshNetworkSnapshotIfNeeded();
    return g_net.vpn ? L"VPN" : L"";
}

PCWSTR GetLocalIpFormatted() {
    RefreshNetworkSnapshotIfNeeded();
    return g_net.localIp.c_str();
}

// Ping, measured on a background thread (iphlpapi is loaded on demand).

struct PingReplyHeader {  // first fields of ICMP_ECHO_REPLY
    ULONG Address;
    ULONG Status;
    ULONG RoundTripTime;
};
using IcmpCreateFile_t = HANDLE(WINAPI*)();
using IcmpCloseHandle_t = BOOL(WINAPI*)(HANDLE);
using IcmpSendEcho_t = DWORD(WINAPI*)(HANDLE, ULONG, LPVOID, WORD, LPVOID, LPVOID, DWORD, DWORD);

std::atomic<int> g_pingMs{-2};  // -2 not measured yet, -1 failed or timed out
HANDLE g_pingThread = nullptr;
HANDLE g_pingStopEvent = nullptr;
unsigned long g_pingAddress = 0;
int g_pingIntervalSec = 5;

DWORD WINAPI PingThread(LPVOID) {
    HMODULE hIp = LoadLibraryW(L"iphlpapi.dll");
    if (!hIp) return 0;
    auto pCreate = reinterpret_cast<IcmpCreateFile_t>(GetProcAddress(hIp, "IcmpCreateFile"));
    auto pClose = reinterpret_cast<IcmpCloseHandle_t>(GetProcAddress(hIp, "IcmpCloseHandle"));
    auto pSend = reinterpret_cast<IcmpSendEcho_t>(GetProcAddress(hIp, "IcmpSendEcho"));
    HANDLE hIcmp = (pCreate && pClose && pSend) ? pCreate() : INVALID_HANDLE_VALUE;
    if (hIcmp != INVALID_HANDLE_VALUE) {
        char payload[32] = "WindhawkTaskbarPing";
        alignas(8) BYTE reply[256];
        while (true) {
            DWORD n = pSend(hIcmp, g_pingAddress, payload, sizeof(payload), nullptr, reply, sizeof(reply), 1500);
            const auto* header = reinterpret_cast<const PingReplyHeader*>(reply);
            g_pingMs = (n > 0 && header->Status == 0) ? static_cast<int>(header->RoundTripTime) : -1;
            if (WaitForSingleObject(g_pingStopEvent, g_pingIntervalSec * 1000) != WAIT_TIMEOUT) break;
        }
        pClose(hIcmp);
    }
    FreeLibrary(hIp);
    return 0;
}

void PingThreadInit() {
    g_pingMs = -2;
    if (!IsStrInDateTimePatternSettings(L"%ping%")) return;
    if (!ParseIPv4(g_settings.pingHost, &g_pingAddress)) return;  // %ping% shows "--"
    g_pingIntervalSec = std::clamp(g_settings.pingInterval, 2, 300);
    g_pingStopEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    g_pingThread = CreateThread(nullptr, 0, PingThread, nullptr, 0, nullptr);
}

void PingThreadUninit() {
    if (!g_pingThread) return;
    SetEvent(g_pingStopEvent);
    WaitForSingleObject(g_pingThread, INFINITE);
    CloseHandle(g_pingThread);
    CloseHandle(g_pingStopEvent);
    g_pingThread = nullptr;
    g_pingStopEvent = nullptr;
}

PCWSTR GetPingFormatted() {
    static WCHAR buf[24];
    int ms = g_pingMs;
    if (ms < 0) return L"--";
    swprintf_s(buf, L"%d ms", ms);
    return buf;
}

// Alternate calendars

std::wstring ComputeAltCalendarDate(int kind) {  // 0 Hijri, 1 Persian, 2 Japanese
    try {
        namespace Glob = winrt::Windows::Globalization;
        winrt::hstring id;
        PCWSTR language = L"en-US";
        if (kind == 0) id = g_settings.hijriCivil ? Glob::CalendarIdentifiers::Hijri() : Glob::CalendarIdentifiers::UmAlQura();
        else if (kind == 1) id = Glob::CalendarIdentifiers::Persian();
        else {
            id = Glob::CalendarIdentifiers::Japanese();
            language = L"ja-JP";
        }

        // The calendar runs in UTC so the local wall-clock time in g_formatTime is read back unchanged.
        Glob::Calendar cal(std::vector<winrt::hstring>{winrt::hstring(language)}, id,
                           Glob::ClockIdentifiers::TwentyFourHour(), L"UTC");
        FILETIME ft{};
        SystemTimeToFileTime(&g_formatTime, &ft);
        cal.SetDateTime(winrt::clock::from_file_time(ft));
        if (kind == 0 && g_settings.hijriOffset) cal.AddDays(g_settings.hijriOffset);

        if (kind == 2) {
            int year = cal.Year();
            return std::wstring(cal.EraAsString()) + (year == 1 ? std::wstring(L"\u5143") : std::to_wstring(year)) +
                   L"\u5E74" + std::to_wstring(cal.Month()) + L"\u6708" + std::to_wstring(cal.Day()) + L"\u65E5";
        }
        return std::to_wstring(cal.Day()) + L" " + std::wstring(cal.MonthAsString()) + L" " + std::to_wstring(cal.Year());
    } catch (...) {
        return L"?";
    }
}

PCWSTR GetAltCalendarDate(int kind) {
    static std::wstring cache[3];
    static int64_t cacheKey[3] = {-1, -1, -1};
    int64_t key = (static_cast<int64_t>(g_formatTime.wYear) * 10000 + g_formatTime.wMonth * 100 + g_formatTime.wDay) * 100 +
                  (g_settings.hijriOffset + 10) * 2 + (g_settings.hijriCivil ? 1 : 0);
    if (cacheKey[kind] != key) {
        cache[kind] = ComputeAltCalendarDate(kind);
        cacheKey[kind] = key;
    }
    return cache[kind].c_str();
}

PCWSTR GetBengaliDate(bool bangla) {
    static std::wstring cache[2];
    static int cacheKey[2] = {-1, -1};
    int key = g_formatTime.wYear * 10000 + g_formatTime.wMonth * 100 + g_formatTime.wDay;
    int idx = bangla ? 1 : 0;
    if (cacheKey[idx] != key) {
        static const wchar_t* kLatin[12] = {L"Boishakh", L"Joishtho", L"Asharh",    L"Shrabon", L"Bhadro",  L"Ashwin",
                                            L"Kartik",   L"Agrahayan", L"Poush",     L"Magh",    L"Falgun",  L"Choitro"};
        static const wchar_t* kBangla[12] = {L"\u09AC\u09C8\u09B6\u09BE\u0996", L"\u099C\u09CD\u09AF\u09C8\u09B7\u09CD\u09A0",
                                             L"\u0986\u09B7\u09BE\u09A2\u09BC",   L"\u09B6\u09CD\u09B0\u09BE\u09AC\u09A3",
                                             L"\u09AD\u09BE\u09A6\u09CD\u09B0",   L"\u0986\u09B6\u09CD\u09AC\u09BF\u09A8",
                                             L"\u0995\u09BE\u09B0\u09CD\u09A4\u09BF\u0995", L"\u0985\u0997\u09CD\u09B0\u09B9\u09BE\u09AF\u09BC\u09A3",
                                             L"\u09AA\u09CC\u09B7",               L"\u09AE\u09BE\u0998",
                                             L"\u09AB\u09BE\u09B2\u09CD\u0997\u09C1\u09A8", L"\u099A\u09C8\u09A4\u09CD\u09B0"};
        BengaliDate b = GregorianToBengali(g_formatTime.wYear, g_formatTime.wMonth, g_formatTime.wDay);
        std::wstring text = std::to_wstring(b.day) + L" " + (bangla ? kBangla : kLatin)[b.month - 1] + L" " +
                            std::to_wstring(b.year);
        cache[idx] = bangla ? ToBanglaDigits(text) : text;
        cacheKey[idx] = key;
    }
    return cache[idx].c_str();
}

// Next calendar event (from the ICS feed)

int64_t LocalSecondsFromSystemTime(const SYSTEMTIME& st) {
    return IcsDaysFromCivil(st.wYear, st.wMonth, st.wDay) * 86400 + st.wHour * 3600 + st.wMinute * 60 + st.wSecond;
}

struct NextEventCache {
    int64_t minuteKey = -1;
    unsigned version = ~0u;
    IcsNext next;
} g_nextEventCache;

IcsNext GetNextEventCached(int64_t* nowLocalOut) {
    int64_t nowLocal = LocalSecondsFromSystemTime(g_formatTime);
    int64_t key = nowLocal / 60;
    *nowLocalOut = nowLocal;
    std::lock_guard<std::mutex> guard(g_webContentMutex);
    if (key != g_nextEventCache.minuteKey || g_icsVersion != g_nextEventCache.version) {
        g_nextEventCache.next = IcsFindNext(g_icsEvents, nowLocal);
        g_nextEventCache.minuteKey = key;
        g_nextEventCache.version = g_icsVersion;
    }
    return g_nextEventCache.next;
}

PCWSTR GetNextEventFormatted() {
    static std::wstring buf;
    int64_t nowLocal;
    IcsNext next = GetNextEventCached(&nowLocal);
    if (!next.found) {
        buf = g_settings.icsNoEventText;
    } else {
        buf = next.summary;
        size_t maxLen = g_settings.icsMaxLength > 0 ? static_cast<size_t>(g_settings.icsMaxLength) : 0;
        if (maxLen >= 4 && buf.size() > maxLen) buf = buf.substr(0, maxLen - 3) + L"...";
    }
    return buf.c_str();
}

PCWSTR GetNextEventTimeFormatted() {
    static std::wstring buf;
    int64_t nowLocal;
    IcsNext next = GetNextEventCached(&nowLocal);
    if (!next.found) return L"";

    int64_t startDay = IcsFloorDiv(next.start, 86400);
    int64_t tod = next.start - startDay * 86400;
    int64_t dayDiff = startDay - IcsFloorDiv(nowLocal, 86400);
    WCHAR hm[8];
    swprintf_s(hm, L"%02d:%02d", static_cast<int>(tod / 3600), static_cast<int>((tod % 3600) / 60));
    if (dayDiff <= 0) {
        buf = hm;
    } else if (dayDiff < 7) {
        static const wchar_t* kWeekday[] = {L"Mon", L"Tue", L"Wed", L"Thu", L"Fri", L"Sat", L"Sun"};
        buf = std::wstring(kWeekday[IcsWeekday(startDay)]) + L" " + hm;
    } else {
        static const wchar_t* kMonth[] = {L"Jan", L"Feb", L"Mar", L"Apr", L"May", L"Jun",
                                          L"Jul", L"Aug", L"Sep", L"Oct", L"Nov", L"Dec"};
        int y;
        unsigned m, d;
        IcsCivilFromDays(startDay, &y, &m, &d);
        buf = std::wstring(kMonth[m - 1]) + L" " + std::to_wstring(d) + L" " + hm;
    }
    return buf.c_str();
}

PCWSTR GetNextEventInFormatted() {
    static std::wstring buf;
    int64_t nowLocal;
    IcsNext next = GetNextEventCached(&nowLocal);
    if (!next.found) return L"";
    buf = IcsFormatIn(next.start - nowLocal);
    return buf.c_str();
}

// ----- GRAPHS, SYSTEM INFO, KEYBOARD, DRIVES, COUNTDOWNS -----

void RecordGraphHistory() {
    for (int k = 0; k < kGraphCount; k++) {
        if (!g_graphUsed[k]) continue;
        double val = 0;
        auto query = [](MetricType m) -> double {
            if (!g_dataCollectionSession) return 0;
            auto v = g_dataCollectionSession->QueryData(m);
            return v ? std::max(*v, 0.0) : 0.0;
        };
        switch (k) {
            case kGraphCpu: val = std::min(query(MetricType::kCpu), 100.0); break;
            case kGraphGpu: val = std::min(query(MetricType::kGpuUsage), 100.0); break;
            case kGraphRam: {
                auto r = GetRamStatus();
                if (r) val = r->dwMemoryLoad;
                break;
            }
            case kGraphDownload: val = query(MetricType::kDownloadSpeed); break;
            case kGraphUpload: val = query(MetricType::kUploadSpeed); break;
            case kGraphDisk: val = query(MetricType::kDiskReadSpeed) + query(MetricType::kDiskWriteSpeed); break;
        }
        g_graphHistory[k].Push(val);
    }
}

PCWSTR GetGraphFormatted(int kind) {
    DataCollectionSampleIfNeeded();
    auto& s = g_graphFormatted[kind];
    DWORD idx = GetDataCollectionFormatIndex();
    if (s.formatIndex != idx) {
        static const WCHAR kBlocks[] = L"\u2581\u2582\u2583\u2584\u2585\u2586\u2587\u2588";
        int len = std::clamp(g_settings.dataCollection.graphLength, 4, kGraphMaxLength);
        const auto& h = g_graphHistory[kind];

        double maxV = 100.0;  // percentages
        if (kind == kGraphDownload || kind == kGraphUpload || kind == kGraphDisk) {
            maxV = 100.0 * 1024;  // bytes/s floor so an idle link doesn't fill the graph
            for (int i = 0; i < h.count; i++) maxV = std::max(maxV, h.v[i]);
        }

        for (int i = 0; i < len; i++) {
            int src = h.count - len + i;
            int level = 0;
            if (src >= 0) level = std::clamp(static_cast<int>(h.v[src] / maxV * 7.0 + 0.5), 0, 7);
            s.buffer[i] = kBlocks[level];
        }
        s.buffer[len] = L'\0';
        s.formatIndex = idx;
    }
    return s.buffer;
}

ULONGLONG FtToU64(const FILETIME& f) {
    return (static_cast<ULONGLONG>(f.dwHighDateTime) << 32) | f.dwLowDateTime;
}

// Uptime

FormattedString<FORMATTED_BUFFER_SIZE> g_uptimeFormatted;

PCWSTR GetUptimeFormatted() {
    return GetMetricFormatted(g_uptimeFormatted, [](PWSTR b, size_t s) {
        ULONGLONG sec = GetTickCount64() / 1000;
        unsigned d = static_cast<unsigned>(sec / 86400);
        unsigned h = static_cast<unsigned>((sec % 86400) / 3600);
        unsigned m = static_cast<unsigned>((sec % 3600) / 60);
        if (d) swprintf_s(b, s, L"%ud %uh %um", d, h, m);
        else if (h) swprintf_s(b, s, L"%uh %um", h, m);
        else swprintf_s(b, s, L"%um", m);
        return true;
    });
}

// Process count and busiest process (sampled at most every few seconds)

struct ProcessSampleState {
    ULONGLONG lastTick = 0;
    std::unordered_map<DWORD, ULONGLONG> prevCpuTime;
    int count = 0;
    std::wstring topName;
    int topCpu = -1;
} g_proc;

void SampleProcessesIfNeeded() {
    ULONGLONG now = GetTickCount64();
    ULONGLONG minGap = std::max<ULONGLONG>(3000, static_cast<ULONGLONG>(GetEffectiveUpdateInterval()) * 1000);
    if (g_proc.lastTick && now - g_proc.lastTick < minGap) return;

    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return;

    SYSTEM_INFO si;
    GetSystemInfo(&si);
    double cpuCount = std::max<DWORD>(si.dwNumberOfProcessors, 1);
    ULONGLONG wallMs = g_proc.lastTick ? now - g_proc.lastTick : 0;

    std::unordered_map<DWORD, ULONGLONG> cur;
    int count = 0;
    double bestPct = -1;
    std::wstring bestName;

    PROCESSENTRY32W pe{};
    pe.dwSize = sizeof(pe);
    if (Process32FirstW(snap, &pe)) {
        do {
            count++;
            if (pe.th32ProcessID == 0) continue;
            HANDLE h = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pe.th32ProcessID);
            if (!h) continue;
            FILETIME c, e, k, u;
            if (GetProcessTimes(h, &c, &e, &k, &u)) {
                ULONGLONG total = FtToU64(k) + FtToU64(u);
                cur[pe.th32ProcessID] = total;
                auto it = g_proc.prevCpuTime.find(pe.th32ProcessID);
                if (wallMs > 0 && it != g_proc.prevCpuTime.end() && total >= it->second) {
                    double pct = static_cast<double>(total - it->second) / (wallMs * 10000.0 * cpuCount) * 100.0;
                    if (pct > bestPct) {
                        bestPct = pct;
                        bestName = pe.szExeFile;
                    }
                }
            }
            CloseHandle(h);
        } while (Process32NextW(snap, &pe));
    }
    CloseHandle(snap);

    if (bestPct >= 0) {
        if (bestName.size() > 4 && _wcsicmp(bestName.c_str() + bestName.size() - 4, L".exe") == 0) {
            bestName.resize(bestName.size() - 4);
        }
        g_proc.topName = bestName;
        g_proc.topCpu = std::min(static_cast<int>(bestPct + 0.5), 100);
    }
    g_proc.prevCpuTime = std::move(cur);
    g_proc.count = count;
    g_proc.lastTick = now;
}

PCWSTR GetProcessCountFormatted() {
    SampleProcessesIfNeeded();
    static WCHAR buf[16];
    swprintf_s(buf, L"%d", g_proc.count);
    return buf;
}

PCWSTR GetTopProcessFormatted() {
    SampleProcessesIfNeeded();
    return g_proc.topName.empty() ? L"-" : g_proc.topName.c_str();
}

PCWSTR GetTopProcessCpuFormatted() {
    SampleProcessesIfNeeded();
    static WCHAR buf[16];
    if (g_proc.topCpu < 0) return L"-";
    swprintf_s(buf, L"%d%%", g_proc.topCpu);
    return buf;
}

// Keyboard state

PCWSTR GetInputLanguage(bool full) {
    static WCHAR buf[2][64];
    WCHAR* b = buf[full ? 1 : 0];
    HWND fg = GetForegroundWindow();
    DWORD tid = fg ? GetWindowThreadProcessId(fg, nullptr) : 0;
    HKL hkl = GetKeyboardLayout(tid);
    LANGID lid = LOWORD(reinterpret_cast<DWORD_PTR>(hkl));
    int n = GetLocaleInfoW(MAKELCID(lid, SORT_DEFAULT), full ? LOCALE_SENGLISHLANGUAGENAME : LOCALE_SISO639LANGNAME, b, 64);
    if (n <= 0) {
        wcscpy_s(b, 64, L"-");
        return b;
    }
    if (!full) CharUpperW(b);
    return b;
}

PCWSTR GetLangFormatted() { return GetInputLanguage(false); }
PCWSTR GetLangFullFormatted() { return GetInputLanguage(true); }
PCWSTR GetCapsLockFormatted() { return (GetKeyState(VK_CAPITAL) & 1) ? L"CAPS" : L""; }
PCWSTR GetNumLockFormatted() { return (GetKeyState(VK_NUMLOCK) & 1) ? L"NUM" : L""; }

// Drive space (local fixed / removable drives only)

struct DriveSpaceCache {
    ULONGLONG tick;
    ULONGLONG total;
    ULONGLONG free;
    bool valid;
};
DriveSpaceCache g_driveCache[26];

bool GetDriveSpace(int idx, ULONGLONG* total, ULONGLONG* freeBytes) {
    ULONGLONG now = GetTickCount64() | 1;
    auto& c = g_driveCache[idx];
    if (!c.tick || now - c.tick >= 10000) {
        c.tick = now;
        c.valid = false;
        WCHAR root[4] = {static_cast<WCHAR>(L'A' + idx), L':', L'\\', 0};
        UINT type = GetDriveTypeW(root);
        if (type == DRIVE_FIXED || type == DRIVE_REMOVABLE) {
            DWORD oldMode = 0;
            BOOL modeSet = SetThreadErrorMode(SEM_FAILCRITICALERRORS, &oldMode);
            ULARGE_INTEGER avail{}, tot{}, fr{};
            if (GetDiskFreeSpaceExW(root, &avail, &tot, &fr)) {
                c.total = tot.QuadPart;
                c.free = fr.QuadPart;
                c.valid = true;
            }
            if (modeSet) SetThreadErrorMode(oldMode, nullptr);
        }
    }
    if (!c.valid) return false;
    *total = c.total;
    *freeBytes = c.free;
    return true;
}

void FormatByteSize(double bytes, PWSTR b, size_t s) {
    double gb = bytes / kGBInBytes;
    if (gb >= 1000.0) swprintf_s(b, s, L"%s TB", FormatLocaleNum(gb / 1024.0, 2).c_str());
    else if (gb >= 100.0) swprintf_s(b, s, L"%s GB", FormatLocaleNum(gb, 0).c_str());
    else swprintf_s(b, s, L"%s GB", FormatLocaleNum(gb, 1).c_str());
}

size_t ResolveDriveToken(std::wstring_view format, const std::function<void(PCWSTR)>& callback) {
    struct { std::wstring_view pre; int kind; } kinds[] = {
        {L"%drive_free_pct_"sv, 3}, {L"%drive_used_pct_"sv, 4},
        {L"%drive_free_"sv, 0}, {L"%drive_used_"sv, 1}, {L"%drive_total_"sv, 2},
    };
    for (const auto& k : kinds) {
        if (!format.starts_with(k.pre)) continue;
        if (format.size() < k.pre.size() + 2 || format[k.pre.size() + 1] != L'%') return 0;
        WCHAR letter = format[k.pre.size()];
        if (letter >= L'a' && letter <= L'z') letter -= 32;
        if (letter < L'A' || letter > L'Z') return 0;

        size_t len = k.pre.size() + 2;
        ULONGLONG total = 0, freeBytes = 0;
        if (!GetDriveSpace(letter - L'A', &total, &freeBytes) || total == 0) {
            callback(L"-");
            return len;
        }
        ULONGLONG used = total - std::min(freeBytes, total);
        WCHAR buf[64];
        switch (k.kind) {
            case 0: FormatByteSize(static_cast<double>(freeBytes), buf, ARRAYSIZE(buf)); break;
            case 1: FormatByteSize(static_cast<double>(used), buf, ARRAYSIZE(buf)); break;
            case 2: FormatByteSize(static_cast<double>(total), buf, ARRAYSIZE(buf)); break;
            case 3: FormatPercentValue(static_cast<int>(freeBytes * 100.0 / total + 0.5), buf, ARRAYSIZE(buf), 100); break;
            default: FormatPercentValue(static_cast<int>(used * 100.0 / total + 0.5), buf, ARRAYSIZE(buf), 100); break;
        }
        callback(buf);
        return len;
    }
    return 0;
}

// Countdowns

PCWSTR GetCountdownFormatted(int n, bool daysOnly) {
    static WCHAR buf[64];
    size_t i = static_cast<size_t>(n - 1);
    if (i >= g_settings.countdownTargets.size() || g_settings.countdownTargets[i] == 0) return L"-";

    FILETIME ft{};
    SystemTimeToFileTime(&g_formatTime, &ft);
    ULONGLONG now = FtToU64(ft);
    ULONGLONG target = g_settings.countdownTargets[i];
    if (target <= now) return daysOnly ? L"0" : L"Done";

    ULONGLONG sec = (target - now) / 10000000ULL;
    unsigned d = static_cast<unsigned>(sec / 86400);
    unsigned h = static_cast<unsigned>((sec % 86400) / 3600);
    unsigned m = static_cast<unsigned>((sec % 3600) / 60);
    if (daysOnly) swprintf_s(buf, L"%u", d);
    else if (d) swprintf_s(buf, L"%ud %uh %um", d, h, m);
    else if (h) swprintf_s(buf, L"%uh %um", h, m);
    else swprintf_s(buf, L"%um", m);
    return buf;
}

// ----- PRAYER TIMES -----
// Offline calculation (the usual astronomical method used by PrayTimes.org):
// sun declination and equation of time for the date, then the hour angles for
// the Fajr / Isha twilight angles, sunrise / sunset and the Asr shadow length.

namespace prayer {

constexpr double kPi = 3.14159265358979323846;
inline double Rad(double d) { return d * kPi / 180.0; }
inline double Deg(double r) { return r * 180.0 / kPi; }
inline double FixAngle(double a) { a = std::fmod(a, 360.0); return a < 0 ? a + 360.0 : a; }
inline double FixHour(double h) { h = std::fmod(h, 24.0); return h < 0 ? h + 24.0 : h; }

double JulianDate(int y, int m, int d) {
    if (m <= 2) { y -= 1; m += 12; }
    int a = y / 100;
    int b = 2 - a + a / 4;
    return std::floor(365.25 * (y + 4716)) + std::floor(30.6001 * (m + 1)) + d + b - 1524.5;
}

void SunPosition(double jd, double* declination, double* equation) {
    double D = jd - 2451545.0;
    double g = FixAngle(357.529 + 0.98560028 * D);
    double q = FixAngle(280.459 + 0.98564736 * D);
    double L = FixAngle(q + 1.915 * std::sin(Rad(g)) + 0.020 * std::sin(Rad(2 * g)));
    double e = 23.439 - 0.00000036 * D;
    double RA = Deg(std::atan2(std::cos(Rad(e)) * std::sin(Rad(L)), std::cos(Rad(L)))) / 15.0;
    *equation = q / 15.0 - FixHour(RA);
    *declination = Deg(std::asin(std::sin(Rad(e)) * std::sin(Rad(L))));
}

double MidDay(double jd, double t) {
    double decl, eqt;
    SunPosition(jd + t, &decl, &eqt);
    return FixHour(12 - eqt);
}

// Time (hours) when the sun is `angle` degrees below the horizon; NaN if it never gets there.
double SunAngleTime(double jd, double lat, double angle, double t, bool ccw) {
    double decl, eqt;
    SunPosition(jd + t, &decl, &eqt);
    double noon = MidDay(jd, t);
    double x = (-std::sin(Rad(angle)) - std::sin(Rad(decl)) * std::sin(Rad(lat))) /
               (std::cos(Rad(decl)) * std::cos(Rad(lat)));
    if (x < -1.0 || x > 1.0) return NAN;
    double dt = Deg(std::acos(x)) / 15.0;
    return noon + (ccw ? -dt : dt);
}

double AsrTime(double jd, double lat, int factor, double t) {
    double decl, eqt;
    SunPosition(jd + t, &decl, &eqt);
    double angle = -Deg(std::atan(1.0 / (factor + std::tan(Rad(std::fabs(lat - decl))))));
    return SunAngleTime(jd, lat, angle, t, false);
}

// Local times in minutes after midnight (NaN when not defined) for one date:
// Fajr, Sunrise, Dhuhr, Asr, Maghrib, Isha.
void Compute(const PrayerSettings& s, int y, int m, int d, double utcOffsetHours, double out[6]) {
    double jd = JulianDate(y, m, d) - s.longitude / (15.0 * 24.0);
    double t[6] = {5.0 / 24, 6.0 / 24, 12.0 / 24, 13.0 / 24, 18.0 / 24, 18.0 / 24};
    double h[6] = {};
    for (int pass = 0; pass < 2; pass++) {
        h[0] = SunAngleTime(jd, s.latitude, s.fajrAngle, t[0], true);
        h[1] = SunAngleTime(jd, s.latitude, 0.833, t[1], true);
        h[2] = MidDay(jd, t[2]);
        h[3] = AsrTime(jd, s.latitude, s.asrFactor, t[3]);
        h[4] = SunAngleTime(jd, s.latitude, 0.833, t[4], false);
        h[5] = s.ishaMinutesAfterMaghrib > 0 ? h[4] + s.ishaMinutesAfterMaghrib / 60.0
                                             : SunAngleTime(jd, s.latitude, s.ishaAngle, t[5], false);
        for (int i = 0; i < 6; i++) {
            if (!std::isnan(h[i])) t[i] = h[i] / 24.0;
        }
    }
    double shift = utcOffsetHours - s.longitude / 15.0;
    for (int i = 0; i < 6; i++) {
        out[i] = std::isnan(h[i]) ? NAN : (h[i] + shift) * 60.0 + s.offsets[i];
    }
}

struct Day {
    int key = -1;
    double minutes[6] = {};
};

}  // namespace prayer

struct PrayerState {
    int dayKey = -1;
    double utcOffset = 0;
    prayer::Day today, tomorrow, yesterday;
    unsigned settingsVersion = 0;
} g_prayerState;
unsigned g_prayerSettingsVersion = 1;

static void PrayerAddDay(int y, int m, int d, int days, int* oy, int* om, int* od) {
    // Civil date arithmetic through the Julian day number.
    double jd = prayer::JulianDate(y, m, d) + days + 0.5;
    int Z = static_cast<int>(jd);
    int A = Z;
    if (Z >= 2299161) {
        int alpha = static_cast<int>((Z - 1867216.25) / 36524.25);
        A = Z + 1 + alpha - alpha / 4;
    }
    int B = A + 1524;
    int C = static_cast<int>((B - 122.1) / 365.25);
    int D = static_cast<int>(365.25 * C);
    int E = static_cast<int>((B - D) / 30.6001);
    *od = B - D - static_cast<int>(30.6001 * E);
    *om = E < 14 ? E - 1 : E - 13;
    *oy = *om > 2 ? C - 4716 : C - 4715;
}

static void PrayerEnsureDays() {
    const SYSTEMTIME& now = g_formatTime;
    int key = now.wYear * 10000 + now.wMonth * 100 + now.wDay;
    if (g_prayerState.dayKey == key && g_prayerState.settingsVersion == g_prayerSettingsVersion) return;

    // UTC offset in hours for the current moment (includes daylight saving time).
    SYSTEMTIME utc{};
    double offset = 0;
    if (TzSpecificLocalTimeToSystemTime(nullptr, &now, &utc)) {
        offset = (LocalSecondsFromSystemTime(now) - LocalSecondsFromSystemTime(utc)) / 3600.0;
    }
    g_prayerState.utcOffset = offset;

    auto fill = [&](prayer::Day& day, int delta) {
        int y, m, d;
        PrayerAddDay(now.wYear, now.wMonth, now.wDay, delta, &y, &m, &d);
        day.key = y * 10000 + m * 100 + d;
        prayer::Compute(g_settings.prayer, y, m, d, offset, day.minutes);
    };
    fill(g_prayerState.yesterday, -1);
    fill(g_prayerState.today, 0);
    fill(g_prayerState.tomorrow, 1);
    g_prayerState.dayKey = key;
    g_prayerState.settingsVersion = g_prayerSettingsVersion;
}

// Formats minutes after midnight (may be outside 0..1440 for neighbouring days).
static PCWSTR PrayerFormatClock(double minutes) {
    static WCHAR bufs[8][32];
    static int next = 0;
    PWSTR buf = bufs[next++ & 7];
    if (std::isnan(minutes)) { wcscpy_s(buf, 32, L"--"); return buf; }
    int total = static_cast<int>(std::floor(minutes + 0.5));
    total = ((total % 1440) + 1440) % 1440;
    int h = total / 60, m = total % 60;
    const auto fmt = g_settings.prayer.timeFormat;
    if (fmt == 2) {
        swprintf_s(buf, 32, L"%02d:%02d", h, m);
    } else {
        int h12 = h % 12 == 0 ? 12 : h % 12;
        if (fmt == 0) swprintf_s(buf, 32, L"%d:%02d %s", h12, m, h < 12 ? L"AM" : L"PM");
        else swprintf_s(buf, 32, L"%d:%02d", h12, m);
    }
    return buf;
}

static PCWSTR PrayerFormatSpan(double minutes) {
    static WCHAR bufs[4][32];
    static int next = 0;
    PWSTR buf = bufs[next++ & 3];
    int total = std::max(0, static_cast<int>(std::floor(minutes)));
    int h = total / 60, m = total % 60;
    if (h) swprintf_s(buf, 32, L"%dh %dm", h, m);
    else swprintf_s(buf, 32, L"%dm", m);
    return buf;
}

// Index 0..5 into Fajr, Sunrise, Dhuhr, Asr, Maghrib, Isha.
static PCWSTR GetPrayerTimeFormatted(int index) {
    PrayerEnsureDays();
    return PrayerFormatClock(g_prayerState.today.minutes[index]);
}

struct PrayerNext {
    int index = -1;       // 0 Fajr, 2 Dhuhr, 3 Asr, 4 Maghrib, 5 Isha (Sunrise is not a prayer)
    double minutes = 0;   // start time on the 'today' time line (can exceed 1440)
};

static PrayerNext PrayerFindNext() {
    PrayerEnsureDays();
    const SYSTEMTIME& now = g_formatTime;
    double nowMin = now.wHour * 60.0 + now.wMinute + now.wSecond / 60.0;
    static const int order[5] = {0, 2, 3, 4, 5};
    for (int i : order) {
        double t = g_prayerState.today.minutes[i];
        if (!std::isnan(t) && t > nowMin) return {i, t};
    }
    double t = g_prayerState.tomorrow.minutes[0];
    if (!std::isnan(t)) return {0, t + 1440.0};
    return {};
}

// End of the Isha period on the 'today' time line. For the night that starts
// this evening it is tomorrow's Fajr or Islamic midnight (halfway between
// Maghrib and the next Fajr); for the night that started yesterday evening
// (before today's Fajr) the same with yesterday's Maghrib and today's Fajr.
// NaN if it cannot be calculated.
static double PrayerIshaEnd(bool previousNight) {
    double maghrib, fajr;
    if (previousNight) {
        maghrib = g_prayerState.yesterday.minutes[4] - 1440.0;
        fajr = g_prayerState.today.minutes[0];
    } else {
        maghrib = g_prayerState.today.minutes[4];
        fajr = g_prayerState.tomorrow.minutes[0] + 1440.0;
    }
    if (std::isnan(fajr)) return NAN;
    if (g_settings.prayer.ishaEndsAtFajr) return fajr;
    if (std::isnan(maghrib)) return NAN;
    return (maghrib + fajr) / 2.0;
}

// The prayer whose period is running now: the most recent of the six events,
// except that from Sunrise until Dhuhr, and from Islamic midnight until Fajr
// (unless the setting makes Isha last until Fajr), no prayer is current (-1).
// Before Fajr the candidate is yesterday's Isha.
static int PrayerFindCurrent() {
    PrayerEnsureDays();
    const SYSTEMTIME& now = g_formatTime;
    double nowMin = now.wHour * 60.0 + now.wMinute + now.wSecond / 60.0;
    int best = -1;
    double bestT = -1e9;
    for (int i = 0; i < 6; i++) {
        double t = g_prayerState.today.minutes[i];
        if (!std::isnan(t) && t <= nowMin && t > bestT) { best = i; bestT = t; }
    }
    bool previousNight = false;
    if (best < 0 && !std::isnan(g_prayerState.yesterday.minutes[5])) {
        best = 5;
        previousNight = true;
    }
    if (best == 1) return -1;  // between Sunrise and Dhuhr
    if (best == 5) {
        double end = PrayerIshaEnd(previousNight);
        if (!std::isnan(end) && nowMin >= end) return -1;  // after Isha ended
    }
    return best;
}

// End of the current period: the next of the six events, on the 'today' time
// line (tomorrow's Fajr after Isha, so it can exceed 1440). NaN if unknown.
static double PrayerCurrentEndMinutes(int current) {
    if (current < 0) return NAN;
    if (current == 5) {
        const SYSTEMTIME& now = g_formatTime;
        double nowMin = now.wHour * 60.0 + now.wMinute + now.wSecond / 60.0;
        double isha = g_prayerState.today.minutes[5];
        // After today's Isha the period belongs to tonight; before Fajr it is
        // still yesterday's Isha.
        return PrayerIshaEnd(std::isnan(isha) || isha > nowMin);
    }
    return g_prayerState.today.minutes[current + 1];
}

// Islamic midnight of tonight: halfway between today's Maghrib and tomorrow's Fajr.
static PCWSTR GetPrayerMidnightFormatted() {
    PrayerEnsureDays();
    double maghrib = g_prayerState.today.minutes[4];
    double fajr = g_prayerState.tomorrow.minutes[0] + 1440.0;
    if (std::isnan(maghrib) || std::isnan(fajr)) return L"--";
    return PrayerFormatClock((maghrib + fajr) / 2.0);
}

static PCWSTR GetPrayerCurrentEndFormatted() {
    int c = PrayerFindCurrent();
    double end = PrayerCurrentEndMinutes(c);
    return std::isnan(end) ? L"--" : PrayerFormatClock(end);
}

static PCWSTR GetPrayerCurrentLeftFormatted() {
    int c = PrayerFindCurrent();
    double end = PrayerCurrentEndMinutes(c);
    if (std::isnan(end)) return L"--";
    const SYSTEMTIME& now = g_formatTime;
    double nowMin = now.wHour * 60.0 + now.wMinute + now.wSecond / 60.0;
    return PrayerFormatSpan(end - nowMin);
}

static PCWSTR GetPrayerCurrentInfoFormatted() {
    static WCHAR bufs[2][96];
    static int next = 0;
    PWSTR buf = bufs[next++ & 1];
    int c = PrayerFindCurrent();
    if (c < 0) { wcscpy_s(buf, 96, L"--"); return buf; }
    std::wstring name = g_settings.prayer.names[c];
    std::wstring left = GetPrayerCurrentLeftFormatted();
    swprintf_s(buf, 96, L"%s (%s left)", name.c_str(), left.c_str());
    return buf;
}

static PCWSTR GetPrayerNextNameFormatted() {
    PrayerNext n = PrayerFindNext();
    return n.index < 0 ? L"--" : g_settings.prayer.names[n.index].c_str();
}

static PCWSTR GetPrayerNextTimeFormatted() {
    PrayerNext n = PrayerFindNext();
    return n.index < 0 ? L"--" : PrayerFormatClock(n.minutes);
}

static PCWSTR GetPrayerNextInFormatted() {
    PrayerNext n = PrayerFindNext();
    if (n.index < 0) return L"--";
    const SYSTEMTIME& now = g_formatTime;
    double nowMin = now.wHour * 60.0 + now.wMinute + now.wSecond / 60.0;
    return PrayerFormatSpan(n.minutes - nowMin);
}

static PCWSTR GetPrayerNextInfoFormatted() {
    static WCHAR bufs[2][96];
    static int next = 0;
    PWSTR buf = bufs[next++ & 1];
    PrayerNext n = PrayerFindNext();
    if (n.index < 0) { wcscpy_s(buf, 96, L"--"); return buf; }
    std::wstring name = g_settings.prayer.names[n.index];
    std::wstring at = PrayerFormatClock(n.minutes);
    std::wstring in = GetPrayerNextInFormatted();
    swprintf_s(buf, 96, L"%s %s (%s)", name.c_str(), at.c_str(), in.c_str());
    return buf;
}

static PCWSTR GetPrayerCurrentFormatted() {
    int i = PrayerFindCurrent();
    return i < 0 ? L"--" : g_settings.prayer.names[i].c_str();
}

static PCWSTR GetPrayerAllFormatted() {
    static std::wstring buf;
    PrayerEnsureDays();
    static const int order[5] = {0, 2, 3, 4, 5};
    buf.clear();
    for (int i : order) {
        if (!buf.empty()) buf += L"  ";
        buf += g_settings.prayer.names[i];
        buf += L' ';
        buf += PrayerFormatClock(g_prayerState.today.minutes[i]);
    }
    return buf.c_str();
}

// Output of CallNtPowerInformation(ProcessorInformation). Declared here because
// the MinGW headers used by Windhawk do not provide it.
struct ClockProcessorPowerInfo {
    ULONG Number;
    ULONG MaxMhz;
    ULONG CurrentMhz;
    ULONG MhzLimit;
    ULONG MaxIdleState;
    ULONG CurrentIdleState;
};

// Average current CPU clock over all logical processors, in MHz.
bool GetCpuFreqMhz(double* out) {
    static double cached = 0;
    static DWORD lastIdx = 0xFFFFFFFF;
    DWORD idx = GetDataCollectionFormatIndex();
    if (idx != lastIdx) {
        lastIdx = idx;
        cached = 0;
        SYSTEM_INFO si;
        GetSystemInfo(&si);
        DWORD n = std::max<DWORD>(si.dwNumberOfProcessors, 1);
        std::vector<ClockProcessorPowerInfo> info(n);
        if (CallNtPowerInformation(ProcessorInformation, nullptr, 0, info.data(),
                                   static_cast<ULONG>(n * sizeof(ClockProcessorPowerInfo))) == 0) {
            double sum = 0;
            for (const auto& p : info) sum += p.CurrentMhz;
            cached = sum / n;
        }
    }
    if (cached <= 0) return false;
    *out = cached;
    return true;
}

PCWSTR GetCpuFreqFormatted() {
    return GetMetricFormatted(g_cpuFreqFormatted, [](PWSTR b, size_t s) {
        double mhz;
        if (!GetCpuFreqMhz(&mhz)) return false;
        if (mhz >= 1000) swprintf_s(b, s, L"%.1f GHz", mhz / 1000.0);
        else swprintf_s(b, s, L"%d MHz", static_cast<int>(mhz));
        return true;
    });
}

// Numeric values for threshold color rules and %if(...)% conditions

bool GetRuleMetricValue(int metric, double* out) {
    switch (metric) {
        case kRuleCpu:
        case kRuleGpu:
        case kRuleCpuTemp: {
            DataCollectionSampleIfNeeded();
            if (!g_dataCollectionSession) return false;
            MetricType type = metric == kRuleCpu ? MetricType::kCpu
                            : metric == kRuleGpu ? MetricType::kGpuUsage
                                                 : MetricType::kCpuTemp;
            auto v = g_dataCollectionSession->QueryData(type);
            if (!v) return false;
            *out = *v;
            return true;
        }
        case kRuleRam: {
            auto r = GetRamStatus();
            if (!r) return false;
            *out = r->dwMemoryLoad;
            return true;
        }
        case kRuleBattery: {
            SYSTEM_POWER_STATUS ps;
            if (!GetSystemPowerStatus(&ps) || ps.BatteryLifePercent == 255) return false;
            *out = ps.BatteryLifePercent;
            return true;
        }
        case kRuleCharging: {
            SYSTEM_POWER_STATUS ps;
            if (!GetSystemPowerStatus(&ps) || ps.ACLineStatus == 255) return false;
            *out = ps.ACLineStatus == 1 ? 1 : 0;
            return true;
        }
        case kRuleHour: *out = g_formatTime.wHour; return true;
        case kRuleMinute: *out = g_formatTime.wMinute; return true;
        case kRuleWeekday: *out = g_formatTime.wDayOfWeek == 0 ? 7 : g_formatTime.wDayOfWeek; return true;  // Mon=1 ... Sun=7
        case kRuleCpuFreq: return GetCpuFreqMhz(out);
    }
    return false;
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

// Playback position (extrapolated while playing) and duration in seconds.
bool GetMediaTimelineNow(double* position, double* duration) {
    RefreshMediaDataIfDirty();
    QueryMediaTimelineIfNeeded();
    std::lock_guard<std::mutex> guard(g_mediaMutex);
    if (!g_mediaActive || !g_mediaTimeline.valid) return false;
    double p = g_mediaTimeline.position;
    if (g_mediaPlaying) p += (GetTickCount64() - g_mediaTimeline.queryTick) / 1000.0 * g_mediaTimeline.rate;
    if (g_mediaTimeline.duration > 0) p = std::min(p, g_mediaTimeline.duration);
    *position = std::max(p, 0.0);
    *duration = g_mediaTimeline.duration;
    return true;
}

PCWSTR GetMediaPositionFormatted() {
    static std::wstring s;
    double p, d;
    if (!GetMediaTimelineNow(&p, &d)) return L"";
    s = FormatMediaClock(p);
    return s.c_str();
}

PCWSTR GetMediaDurationFormatted() {
    static std::wstring s;
    double p, d;
    if (!GetMediaTimelineNow(&p, &d)) return L"";
    if (d <= 0) return L"--:--";
    s = FormatMediaClock(d);
    return s.c_str();
}

PCWSTR GetMediaRemainingFormatted() {
    static std::wstring s;
    double p, d;
    if (!GetMediaTimelineNow(&p, &d)) return L"";
    if (d <= 0) return L"--:--";
    s = L"-" + FormatMediaClock(d - p);
    return s.c_str();
}

PCWSTR GetMediaProgressFormatted() {
    static WCHAR buf[8];
    double p, d;
    if (!GetMediaTimelineNow(&p, &d) || d <= 0) return L"";
    swprintf_s(buf, L"%d%%", std::clamp(static_cast<int>(p / d * 100.0), 0, 100));
    return buf;
}

PCWSTR GetMediaBarFormatted() {
    static std::wstring s;
    double p, d;
    if (!GetMediaTimelineNow(&p, &d)) return L"";
    s = MediaProgressBar(p, d, 8);
    return s.c_str();
}

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
        if (g_settings.mediaPlayer.marquee && g_settings.mediaPlayer.maxLength > 0) {
            // Scroll instead of cutting the text off (only while playing).
            WCHAR full[FORMATTED_BUFFER_SIZE];
            FormatLineNoLock(full, ARRAYSIZE(full), fmt);
            size_t speed = static_cast<size_t>(std::clamp(g_settings.mediaPlayer.marqueeSpeed, 1, 20));
            size_t offset = g_mediaPlaying ? static_cast<size_t>(GetTickCount64() / 1000) * speed : 0;
            std::wstring window = MarqueeWindow(full, static_cast<size_t>(maxLen), offset);
            wcsncpy_s(g_mediaInfoFormatted.buffer, ARRAYSIZE(g_mediaInfoFormatted.buffer), window.c_str(), _TRUNCATE);
        } else {
            FormatLineNoLock(g_mediaInfoFormatted.buffer, maxLen + 1, fmt);
        }
        g_inMediaInfoFormat = false;
        g_mediaInfoFormatted.formatIndex = g_formatIndex;
    }
    return g_mediaInfoFormatted.buffer;
}

// ----- TIMER, STOPWATCH & POMODORO -----
//
// One shared run state drives three tags: %stopwatch% counts up, %timer% counts
// down from the configured duration and %pomodoro% alternates work and break
// phases. Start / pause and reset are bound to middle-click actions.

struct ClockTimerState {
    bool running = false;
    ULONGLONG startTick = 0;       // GetTickCount64() when it was last started
    ULONGLONG accumulatedMs = 0;   // time counted before the last start
    bool timerDoneNotified = false;
    long long lastPomodoroPhase = -1;
};
ClockTimerState g_clockTimer;
std::mutex g_clockTimerMutex;

ULONGLONG ClockTimerElapsedMs() {
    std::lock_guard<std::mutex> guard(g_clockTimerMutex);
    return g_clockTimer.accumulatedMs + (g_clockTimer.running ? GetTickCount64() - g_clockTimer.startTick : 0);
}

void ClockTimerToggle() {
    std::lock_guard<std::mutex> guard(g_clockTimerMutex);
    if (g_clockTimer.running) {
        g_clockTimer.accumulatedMs += GetTickCount64() - g_clockTimer.startTick;
        g_clockTimer.running = false;
    } else {
        g_clockTimer.startTick = GetTickCount64();
        g_clockTimer.running = true;
    }
}

void ClockTimerReset() {
    std::lock_guard<std::mutex> guard(g_clockTimerMutex);
    g_clockTimer = ClockTimerState{};
}

std::wstring FormatTimerSeconds(ULONGLONG totalSec) {
    unsigned h = static_cast<unsigned>(totalSec / 3600);
    unsigned m = static_cast<unsigned>((totalSec % 3600) / 60);
    unsigned s = static_cast<unsigned>(totalSec % 60);
    WCHAR buf[32];
    if (h) swprintf_s(buf, L"%u:%02u:%02u", h, m, s);
    else swprintf_s(buf, L"%02u:%02u", m, s);
    return buf;
}

PCWSTR GetStopwatchFormatted() {
    static std::wstring s;
    s = FormatTimerSeconds(ClockTimerElapsedMs() / 1000);
    return s.c_str();
}

PCWSTR GetTimerFormatted() {
    static std::wstring s;
    ULONGLONG totalMs = static_cast<ULONGLONG>(std::max(1, g_settings.timerMinutes)) * 60000ULL;
    ULONGLONG elapsed = ClockTimerElapsedMs();
    bool running;
    {
        std::lock_guard<std::mutex> guard(g_clockTimerMutex);
        running = g_clockTimer.running;
    }
    if (elapsed >= totalMs) {
        bool notify = false;
        {
            std::lock_guard<std::mutex> guard(g_clockTimerMutex);
            if (!g_clockTimer.timerDoneNotified) {
                g_clockTimer.timerDoneNotified = true;
                notify = true;
            }
        }
        if (notify && g_settings.timerSound) MessageBeep(MB_ICONEXCLAMATION);
        s = L"Done";
    } else {
        // Round up so the display reaches 00:00 together with the sound.
        s = FormatTimerSeconds((totalMs - elapsed + 999) / 1000);
        if (!running && elapsed > 0) s = L"⏸ " + s;
    }
    return s.c_str();
}

PCWSTR GetPomodoroFormatted() {
    static std::wstring s;
    ULONGLONG workMs = static_cast<ULONGLONG>(std::max(1, g_settings.pomodoroWorkMinutes)) * 60000ULL;
    ULONGLONG breakMs = static_cast<ULONGLONG>(std::max(1, g_settings.pomodoroBreakMinutes)) * 60000ULL;
    ULONGLONG cycle = workMs + breakMs;
    ULONGLONG elapsed = ClockTimerElapsedMs();
    ULONGLONG pos = elapsed % cycle;
    bool working = pos < workMs;
    ULONGLONG remainingMs = working ? workMs - pos : cycle - pos;

    long long phase = static_cast<long long>(elapsed / cycle) * 2 + (working ? 0 : 1);
    bool beep = false;
    bool running;
    {
        std::lock_guard<std::mutex> guard(g_clockTimerMutex);
        running = g_clockTimer.running;
        if (running && g_clockTimer.lastPomodoroPhase >= 0 && g_clockTimer.lastPomodoroPhase != phase) beep = true;
        if (running || elapsed == 0) g_clockTimer.lastPomodoroPhase = elapsed == 0 ? -1 : phase;
    }
    if (beep && g_settings.timerSound) MessageBeep(MB_ICONASTERISK);

    s = working ? L"\U0001F345 " : L"☕ ";
    if (!running && elapsed > 0) s = L"⏸ " + s;
    s += FormatTimerSeconds((remainingMs + 999) / 1000);
    return s.c_str();
}

// ----- CONDITIONAL TAG: %if(condition,then,else)% -----
//
// Example: %if(battery<20,"low",)% or %if(cpu>=90,%cpu%,)%. The condition is
// <metric><operator><number> with metric one of cpu, ram, gpu, cpu_temp,
// cpu_freq, battery, charging, hour, minute or weekday, and operator one of
// > >= < <= == !=. The text parts may contain other tags and may be wrapped
// in double quotes to keep commas or spaces. A metric without a value (for
// example battery on a desktop PC) makes the condition false.

int ParseIfMetric(std::wstring_view name) {
    struct { std::wstring_view n; int id; } metrics[] = {
        {L"cpu"sv, kRuleCpu}, {L"ram"sv, kRuleRam}, {L"gpu"sv, kRuleGpu},
        {L"cpu_temp"sv, kRuleCpuTemp}, {L"cpu_freq"sv, kRuleCpuFreq}, {L"battery"sv, kRuleBattery},
        {L"charging"sv, kRuleCharging}, {L"hour"sv, kRuleHour}, {L"minute"sv, kRuleMinute},
        {L"weekday"sv, kRuleWeekday},
    };
    for (const auto& m : metrics) {
        if (name == m.n) return m.id;
    }
    return kRuleNone;
}

// Splits at top-level commas (not inside parentheses or double quotes),
// returning at most `maxParts` parts; the last part keeps any further commas.
std::vector<std::wstring_view> SplitIfArguments(std::wstring_view args, size_t maxParts) {
    std::vector<std::wstring_view> parts;
    size_t depth = 0, begin = 0;
    bool quoted = false;
    for (size_t i = 0; i < args.size() && parts.size() + 1 < maxParts; i++) {
        wchar_t c = args[i];
        if (c == L'"') quoted = !quoted;
        else if (quoted) continue;
        else if (c == L'(') depth++;
        else if (c == L')' && depth > 0) depth--;
        else if (c == L',' && depth == 0) {
            parts.push_back(args.substr(begin, i - begin));
            begin = i + 1;
        }
    }
    parts.push_back(args.substr(begin));
    return parts;
}

std::wstring_view StripIfQuotes(std::wstring_view s) {
    s = TrimStringView(s);
    if (s.size() >= 2 && s.front() == L'"' && s.back() == L'"') return s.substr(1, s.size() - 2);
    return s;
}

int FormatLineNoLock(PWSTR buffer, size_t bufferSize, std::wstring_view format);

// Returns the number of characters consumed, or 0 if `format` is not a valid
// %if(...)% tag.
size_t ResolveIfToken(std::wstring_view format, const std::function<void(PCWSTR)>& callback) {
    if (!format.starts_with(L"%if("sv)) return 0;

    size_t depth = 0, close = std::wstring_view::npos;
    bool quoted = false;
    for (size_t i = 4; i < format.size(); i++) {
        wchar_t c = format[i];
        if (c == L'"') quoted = !quoted;
        else if (quoted) continue;
        else if (c == L'(') depth++;
        else if (c == L')') {
            if (depth == 0) {
                if (i + 1 < format.size() && format[i + 1] == L'%') close = i;
                break;
            }
            depth--;
        }
    }
    if (close == std::wstring_view::npos) return 0;

    auto parts = SplitIfArguments(format.substr(4, close - 4), 3);
    if (parts.size() < 2) return 0;

    // Condition: <metric><op><number>
    std::wstring_view cond = TrimStringView(parts[0]);
    size_t opPos = cond.find_first_of(L"<>=!"sv);
    if (opPos == std::wstring_view::npos || opPos == 0) return 0;
    std::wstring_view metricName = TrimStringView(cond.substr(0, opPos));
    size_t opLen = (opPos + 1 < cond.size() && cond[opPos + 1] == L'=') ? 2 : 1;
    std::wstring_view op = cond.substr(opPos, opLen);
    std::wstring valueText(TrimStringView(cond.substr(opPos + opLen)));
    if (valueText.empty()) return 0;
    PWSTR numEnd = nullptr;
    double threshold = wcstod(valueText.c_str(), &numEnd);
    if (numEnd == valueText.c_str() || *numEnd) return 0;

    int metric = ParseIfMetric(metricName);
    size_t consumed = close + 2;
    if (metric == kRuleNone) {
        if (g_settings.showTagHints) {
            std::wstring hint = L"[?if:" + std::wstring(metricName) + L"]";
            callback(hint.c_str());
            return consumed;
        }
        return 0;
    }

    double value = 0;
    bool have = GetRuleMetricValue(metric, &value);
    bool result = false;
    if (have) {
        if (op == L">"sv) result = value > threshold;
        else if (op == L">="sv) result = value >= threshold;
        else if (op == L"<"sv) result = value < threshold;
        else if (op == L"<="sv) result = value <= threshold;
        else if (op == L"=="sv || op == L"="sv) result = value == threshold;
        else if (op == L"!="sv) result = value != threshold;
        else return 0;
    }

    std::wstring_view chosen = result ? StripIfQuotes(parts[1]) : (parts.size() > 2 ? StripIfQuotes(parts[2]) : L""sv);
    if (chosen.empty()) {
        callback(L"");
        return consumed;
    }
    WCHAR buf[FORMATTED_BUFFER_SIZE];
    FormatLineNoLock(buf, ARRAYSIZE(buf), chosen);
    callback(buf);
    return consumed;
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
        {L"%uptime%"sv, GetUptimeFormatted}, {L"%process_count%"sv, GetProcessCountFormatted},
        {L"%top_process%"sv, GetTopProcessFormatted}, {L"%top_process_cpu%"sv, GetTopProcessCpuFormatted},
        {L"%lang%"sv, GetLangFormatted}, {L"%lang_full%"sv, GetLangFullFormatted},
        {L"%capslock%"sv, GetCapsLockFormatted}, {L"%numlock%"sv, GetNumLockFormatted},
        {L"%cpu_graph%"sv, []() { return GetGraphFormatted(kGraphCpu); }},
        {L"%ram_graph%"sv, []() { return GetGraphFormatted(kGraphRam); }},
        {L"%gpu_graph%"sv, []() { return GetGraphFormatted(kGraphGpu); }},
        {L"%download_graph%"sv, []() { return GetGraphFormatted(kGraphDownload); }},
        {L"%upload_graph%"sv, []() { return GetGraphFormatted(kGraphUpload); }},
        {L"%disk_graph%"sv, []() { return GetGraphFormatted(kGraphDisk); }},
        {L"%ping%"sv, GetPingFormatted}, {L"%wifi_ssid%"sv, GetWifiSsidFormatted},
        {L"%wifi_signal%"sv, GetWifiSignalFormatted}, {L"%vpn%"sv, GetVpnFormatted},
        {L"%local_ip%"sv, GetLocalIpFormatted},
        {L"%date_hijri%"sv, []() { return GetAltCalendarDate(0); }},
        {L"%date_persian%"sv, []() { return GetAltCalendarDate(1); }},
        {L"%date_japanese%"sv, []() { return GetAltCalendarDate(2); }},
        {L"%date_bengali%"sv, []() { return GetBengaliDate(true); }},
        {L"%date_bengali_en%"sv, []() { return GetBengaliDate(false); }},
        {L"%next_event%"sv, GetNextEventFormatted}, {L"%next_event_time%"sv, GetNextEventTimeFormatted},
        {L"%next_event_in%"sv, GetNextEventInFormatted},
        {L"%media_position%"sv, GetMediaPositionFormatted}, {L"%media_duration%"sv, GetMediaDurationFormatted},
        {L"%media_remaining%"sv, GetMediaRemainingFormatted}, {L"%media_progress%"sv, GetMediaProgressFormatted},
        {L"%media_bar%"sv, GetMediaBarFormatted},
        {L"%cpu_freq%"sv, GetCpuFreqFormatted}, {L"%stopwatch%"sv, GetStopwatchFormatted},
        {L"%timer%"sv, GetTimerFormatted}, {L"%pomodoro%"sv, GetPomodoroFormatted},
        {L"%prayer_next%"sv, GetPrayerNextNameFormatted}, {L"%prayer_next_time%"sv, GetPrayerNextTimeFormatted},
        {L"%prayer_next_in%"sv, GetPrayerNextInFormatted}, {L"%prayer_next_info%"sv, GetPrayerNextInfoFormatted},
        {L"%prayer_current%"sv, GetPrayerCurrentFormatted},
        {L"%prayer_current_end%"sv, GetPrayerCurrentEndFormatted}, {L"%prayer_current_left%"sv, GetPrayerCurrentLeftFormatted},
        {L"%prayer_current_info%"sv, GetPrayerCurrentInfoFormatted},
        {L"%prayer_midnight%"sv, GetPrayerMidnightFormatted}, {L"%prayer_all%"sv, GetPrayerAllFormatted},
        {L"%prayer_fajr%"sv, []() { return GetPrayerTimeFormatted(0); }},
        {L"%prayer_sunrise%"sv, []() { return GetPrayerTimeFormatted(1); }},
        {L"%prayer_dhuhr%"sv, []() { return GetPrayerTimeFormatted(2); }},
        {L"%prayer_asr%"sv, []() { return GetPrayerTimeFormatted(3); }},
        {L"%prayer_maghrib%"sv, []() { return GetPrayerTimeFormatted(4); }},
        {L"%prayer_isha%"sv, []() { return GetPrayerTimeFormatted(5); }},
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

    if (format.starts_with(L"%if("sv)) {
        if (size_t len = ResolveIfToken(format, callback)) return len;
    }
    if (format.starts_with(L"%drive_"sv)) {
        if (size_t len = ResolveDriveToken(format, callback)) return len;
    }
    if (int d = ResolveFormatTokenWithDigit(format, L"%countdown"sv, L"_days%"sv)) {
        callback(GetCountdownFormatted(d, true));
        return 17;
    }
    if (int d = ResolveFormatTokenWithDigit(format, L"%countdown"sv, L"%"sv)) {
        callback(GetCountdownFormatted(d, false));
        return 12;
    }
    return 0;
}

void EnsureFormattingInitialized() {
    if (g_formattingInitialized) return;
    g_formattingInitialized = true;
    WebContentUpdateThreadInit();
    DataCollectionSessionInit();
    MediaSessionInit();
    PingThreadInit();
    g_liveTagsUsed = IsStrInDateTimePatternSettings(L"%lang") || IsStrInDateTimePatternSettings(L"%capslock%") ||
                     IsStrInDateTimePatternSettings(L"%numlock%") || IsStrInDateTimePatternSettings(L"%top_process") ||
                     IsStrInDateTimePatternSettings(L"%process_count%") || IsStrInDateTimePatternSettings(L"_graph%") ||
                     IsStrInDateTimePatternSettings(L"%ping%") || IsStrInDateTimePatternSettings(L"%wifi_signal%") ||
                     IsStrInDateTimePatternSettings(L"%media_position%") || IsStrInDateTimePatternSettings(L"%media_remaining%") ||
                     IsStrInDateTimePatternSettings(L"%media_progress%") || IsStrInDateTimePatternSettings(L"%media_bar%") ||
                     IsStrInDateTimePatternSettings(L"%if(") || IsStrInDateTimePatternSettings(L"%stopwatch%") ||
                     IsStrInDateTimePatternSettings(L"%timer%") || IsStrInDateTimePatternSettings(L"%pomodoro%") ||
                     IsStrInDateTimePatternSettings(L"%cpu_freq%") ||
                     (g_settings.mediaPlayer.marquee && IsStrInDateTimePatternSettings(L"%media_info%")) ||
                     !g_settings.colorRules.empty();
}

// Length of a "%name%" token made of lowercase letters, digits and underscores
// (at least two characters), or 0 if the text does not start with one.
size_t MatchTagLikeToken(std::wstring_view s) {
    if (s.empty() || s[0] != L'%') return 0;
    size_t j = 1;
    while (j < s.size() && ((s[j] >= L'a' && s[j] <= L'z') || (s[j] >= L'0' && s[j] <= L'9') || s[j] == L'_')) j++;
    if (j < 3 || j >= s.size() || s[j] != L'%' || j > 60) return 0;
    return j + 1;
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
            if (g_settings.showTagHints) {
                if (size_t hintLen = MatchTagLikeToken(suffix)) {
                    std::wstring hint = L"[?";
                    hint.append(suffix.substr(1, hintLen - 2));
                    hint += L"]";
                    bool hintTrunc = false;
                    buffer += StringCopyTruncated(buffer, end - buffer, hint.c_str(), &hintTrunc);
                    if (hintTrunc) break;
                    suffix = suffix.substr(hintLen);
                    continue;
                }
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

enum ProfileCondition { kProfNone, kProfOnBattery, kProfPluggedIn, kProfBatteryBelow, kProfMultiMonitor, kProfSingleMonitor, kProfHours };

int ParseProfileCondition(PCWSTR s) {
    if (wcscmp(s, L"onBattery") == 0) return kProfOnBattery;
    if (wcscmp(s, L"pluggedIn") == 0) return kProfPluggedIn;
    if (wcscmp(s, L"batteryBelow") == 0) return kProfBatteryBelow;
    if (wcscmp(s, L"multiMonitor") == 0) return kProfMultiMonitor;
    if (wcscmp(s, L"singleMonitor") == 0) return kProfSingleMonitor;
    if (wcscmp(s, L"hours") == 0) return kProfHours;
    return kProfNone;
}

// True if `hour` is in [start, end). A range that wraps midnight (for example
// 22 to 6) is supported, and start == end means the whole day.
bool HourInRange(int hour, int start, int end) {
    if (start == end) return true;
    if (start < end) return hour >= start && hour < end;
    return hour >= start || hour < end;
}

// Chooses the automatic profile (a clock layout preset) at most every 2 seconds.
void UpdateActiveProfile() {
    if (g_settings.profileRules.empty()) {
        g_profilePreset = nullptr;
        return;
    }
    static ULONGLONG s_last = 0;
    ULONGLONG now = GetTickCount64() | 1;
    if (s_last && now - s_last < 2000) return;
    s_last = now;

    SYSTEM_POWER_STATUS ps{};
    const bool havePower = GetSystemPowerStatus(&ps) != 0;
    const LinePreset* chosen = nullptr;
    for (const auto& r : g_settings.profileRules) {
        bool match = false;
        switch (r.condition) {
            case kProfOnBattery: match = havePower && ps.ACLineStatus == 0; break;
            case kProfPluggedIn: match = havePower && ps.ACLineStatus == 1; break;
            case kProfBatteryBelow:
                match = havePower && ps.BatteryLifePercent != 255 && ps.BatteryLifePercent < r.threshold;
                break;
            case kProfMultiMonitor: match = GetSystemMetrics(SM_CMONITORS) > 1; break;
            case kProfSingleMonitor: match = GetSystemMetrics(SM_CMONITORS) <= 1; break;
            case kProfHours: match = HourInRange(g_formatTime.wHour, r.startHour, r.endHour); break;
        }
        if (match) {
            chosen = r.preset;
            break;
        }
    }
    g_profilePreset = chosen;
}

int FormatLine(PWSTR buffer, size_t bufferSize, std::wstring_view format) {
    if (bufferSize == 0) return 0;
    std::lock_guard<std::mutex> guard(g_formatLineMutex);
    EnsureFormattingInitialized();
    UpdateActiveProfile();
    return FormatLineNoLock(buffer, bufferSize, format);
}

// ----- TASKBAR XAML & CLOCK HOOKS -----

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

// ----- DIAGNOSTICS -----

// Logs which thread each clock model runs on and which thread / monitor each
// taskbar window belongs to. Used to investigate per-monitor clock settings.
void LogClockModelThread(LPVOID model) {
    static std::vector<std::pair<LPVOID, DWORD>> s_seen;
    DWORD tid = GetCurrentThreadId();
    for (const auto& s : s_seen) {
        if (s.first == model && s.second == tid) return;
    }
    if (s_seen.size() >= 40) return;
    s_seen.emplace_back(model, tid);

    Wh_Log(L"[clock] model=%p thread=%u", model, tid);
    EnumWindows(
        [](HWND hWnd, LPARAM) -> BOOL {
            DWORD pid = 0;
            DWORD wndTid = GetWindowThreadProcessId(hWnd, &pid);
            WCHAR cls[64]{};
            if (pid != GetCurrentProcessId() || !GetClassNameW(hWnd, cls, ARRAYSIZE(cls))) return TRUE;
            if (_wcsicmp(cls, L"Shell_TrayWnd") != 0 && _wcsicmp(cls, L"Shell_SecondaryTrayWnd") != 0) return TRUE;

            MONITORINFO mi{sizeof(mi)};
            HMONITOR mon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
            GetMonitorInfoW(mon, &mi);
            Wh_Log(L"[clock] taskbar %s hwnd=%p thread=%u monitor=(%ld,%ld)-(%ld,%ld)%s", cls, hWnd, wndTid,
                   mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right, mi.rcMonitor.bottom,
                   (mi.dwFlags & MONITORINFOF_PRIMARY) ? L" primary" : L"");
            return TRUE;
        },
        0);
}

void UpdateClockColorRules();

void ClockSystemTrayIconDataModel_RefreshIcon_Hook_Impl(LPVOID pThis, LPVOID param1, ClockSystemTrayIconDataModel_RefreshIcon_t orig) {
    {
        std::lock_guard<std::mutex> guard(g_formatLineMutex);
        EnsureFormattingInitialized();
    }
    if (g_settings.logClockThreads) LogClockModelThread(pThis);
    g_refreshIconThreadId = GetCurrentThreadId();
    g_refreshIconNeedToAdjustTimer = g_settings.showSeconds || g_dataCollectionSession || g_liveTagsUsed || (g_webContentUpdateThread && !g_webContentLoaded);
    orig(pThis, param1);
    g_refreshIconThreadId = 0;
    g_refreshIconNeedToAdjustTimer = false;
    try { UpdateClockColorRules(); } catch (...) {}
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
    size_t len = FormatLine(extra, ARRAYSIZE(extra), EffTooltipLine());
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

Media::Brush ParseBrush(PCWSTR value) {
    try {
        return Markup::XamlBindingHelper::ConvertValue(
                   winrt::xaml_typename<Media::Brush>(),
                   winrt::box_value(winrt::hstring(value)))
            .as<Media::Brush>();
    } catch (...) {
        return nullptr;
    }
}

// Bangla letters come from a fallback font that looks larger than the Latin
// font at the same size. Put the Bangla characters in their own runs with a
// scaled font size. The clock replaces the text on every refresh, so this is
// called again from a Text property callback.
thread_local bool g_inBengaliScale = false;

static bool IsBengaliScriptChar(wchar_t c) { return c >= 0x0980 && c <= 0x09FF; }

void ApplyBengaliScaleToTextBlock(Controls::TextBlock tb) {
    if (g_inBengaliScale) return;
    const int scale = g_settings.bengaliTextScale;
    if (scale == 100 || g_unloading) return;

    winrt::hstring text = tb.Text();
    std::wstring_view sv = text;
    bool hasBengali = false;
    for (wchar_t c : sv) {
        if (IsBengaliScriptChar(c)) { hasBengali = true; break; }
    }
    if (!hasBengali) return;

    g_inBengaliScale = true;
    try {
        const double bengaliSize = tb.FontSize() * scale / 100.0;
        auto inlines = tb.Inlines();
        inlines.Clear();

        std::wstring seg;
        int segKind = -2;  // -2 unset, 0 other, 1 Bangla
        auto flush = [&]() {
            if (seg.empty()) return;
            Documents::Run run;
            run.Text(seg);
            if (segKind == 1) run.FontSize(bengaliSize);
            inlines.Append(run);
            seg.clear();
            segKind = -2;
        };
        for (wchar_t c : sv) {
            if (c == L'\r') continue;
            if (c == L'\n') {
                flush();
                inlines.Append(Documents::LineBreak());
                continue;
            }
            // Spaces, punctuation and joiners stay with the surrounding run.
            const bool neutral = (c < 0x80 && !iswalnum(c)) || c == 0x200C || c == 0x200D;
            if (!neutral) {
                int kind = IsBengaliScriptChar(c) ? 1 : 0;
                if (segKind != -2 && segKind != kind) flush();
                segKind = kind;
            }
            seg += c;
        }
        flush();
    } catch (...) {}
    g_inBengaliScale = false;
}

// line: 0 = top line, 1 = bottom line, -1 = no color rules.
void ApplyTextBlockStyles(Controls::TextBlock textBlock, const TextStyleSettings* s, bool noWrap, std::optional<int64_t>* token, int line,
                          std::optional<int64_t>* textToken) {
    if (textToken->has_value()) {
        try { textBlock.UnregisterPropertyChangedCallback(Controls::TextBlock::TextProperty(), textToken->value()); } catch (...) {}
        textToken->reset();
    }
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

    std::wstring ruleColor;
    if (s && line >= 0) {
        std::lock_guard<std::mutex> guard(g_clockRuleMutex);
        ruleColor = g_clockRuleColor[line];
    }

    Media::Brush brush = nullptr;
    if (g_isBatteryLow) {
        brush = Media::SolidColorBrush(winrt::Windows::UI::Colors::Red());
    } else if (!ruleColor.empty()) {
        brush = ParseBrush(ruleColor.c_str());
    }
    if (!brush && s && *s->textColor) {
        brush = ParseBrush(s->textColor.get());
    }
    if (brush) {
        textBlock.Foreground(brush);
    } else {
        textBlock.as<DependencyObject>().ClearValue(Controls::TextBlock::ForegroundProperty());
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

    if (s && g_settings.bengaliTextScale != 100 && !g_unloading) {
        try {
            *textToken = textBlock.RegisterPropertyChangedCallback(
                Controls::TextBlock::TextProperty(),
                [](DependencyObject sender, DependencyProperty) {
                    if (auto tb = sender.try_as<Controls::TextBlock>()) ApplyBengaliScaleToTextBlock(tb);
                });
            ApplyBengaliScaleToTextBlock(textBlock);
        } catch (...) {}
    }
}

// ----- CLOCK CLICK & SCROLL ACTIONS -----

void StartProcessDetached(const std::wstring& commandLine) {
    if (commandLine.empty()) return;
    std::wstring cmd = commandLine;  // CreateProcess may modify the buffer
    STARTUPINFOW si{};
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi{};
    if (CreateProcessW(nullptr, cmd.data(), nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
    }
}

void SendKeyTap(WORD vk) {
    INPUT in[2] = {};
    in[0].type = INPUT_KEYBOARD;
    in[0].ki.wVk = vk;
    in[1] = in[0];
    in[1].ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(2, in, sizeof(INPUT));
}

// Returns true when the wheel event was used.
bool PerformClockScrollAction(bool up) {
    switch (g_settings.clockScrollAction) {
        case 1: SendKeyTap(up ? VK_VOLUME_UP : VK_VOLUME_DOWN); return true;
        case 2: SendKeyTap(up ? VK_MEDIA_NEXT_TRACK : VK_MEDIA_PREV_TRACK); return true;
    }
    return false;
}

bool PerformClockMiddleAction() {
    switch (g_settings.clockMiddleAction) {
        case 1: SendKeyTap(VK_MEDIA_PLAY_PAUSE); return true;
        case 2: SendKeyTap(VK_VOLUME_MUTE); return true;
        case 3: SendKeyTap(VK_MEDIA_NEXT_TRACK); return true;
        case 4: SendKeyTap(VK_MEDIA_PREV_TRACK); return true;
        case 5: StartProcessDetached(L"taskmgr.exe"); return true;
        case 6: StartProcessDetached(g_settings.clockCommand); return true;
        case 7: ClockTimerToggle(); return true;
        case 8: ClockTimerReset(); return true;
    }
    return false;
}

// Attaches (or removes) the wheel / middle-click handlers on the clock button.
// Nothing is attached unless a click or scroll action is configured.
void ApplyClockActionHandlers(FrameworkElement content, ClockElementStyleData* d, bool enabled) {
    namespace Input = winrt::Windows::UI::Xaml::Input;
    const bool want = enabled && (g_settings.clockScrollAction || g_settings.clockMiddleAction);
    UIElement target = d->actionTarget.get();

    if (!want) {
        if (target) {
            try {
                if (d->wheelHandler) target.RemoveHandler(UIElement::PointerWheelChangedEvent(), winrt::box_value(*d->wheelHandler));
                if (d->pressedHandler) target.RemoveHandler(UIElement::PointerPressedEvent(), winrt::box_value(*d->pressedHandler));
            } catch (...) {}
        }
        d->wheelHandler.reset();
        d->pressedHandler.reset();
        d->actionTarget = nullptr;
        return;
    }
    if (target && d->wheelHandler && d->pressedHandler) return;  // already attached

    // The clickable element is the SystemTray.IconView that hosts the clock content.
    UIElement found = nullptr;
    DependencyObject cur = content;
    while (cur) {
        if (winrt::get_class_name(cur) == L"SystemTray.IconView") {
            found = cur.try_as<UIElement>();
            break;
        }
        cur = Media::VisualTreeHelper::GetParent(cur);
    }
    if (!found) found = content;

    d->wheelHandler = Input::PointerEventHandler(
        [](winrt::Windows::Foundation::IInspectable const& sender, Input::PointerRoutedEventArgs const& e) {
            try {
                auto relativeTo = sender.try_as<UIElement>();
                if (!relativeTo) return;
                int delta = e.GetCurrentPoint(relativeTo).Properties().MouseWheelDelta();
                if (delta != 0 && PerformClockScrollAction(delta > 0)) e.Handled(true);
            } catch (...) {}
        });
    d->pressedHandler = Input::PointerEventHandler(
        [](winrt::Windows::Foundation::IInspectable const& sender, Input::PointerRoutedEventArgs const& e) {
            try {
                auto relativeTo = sender.try_as<UIElement>();
                if (!relativeTo) return;
                if (e.GetCurrentPoint(relativeTo).Properties().IsMiddleButtonPressed() && PerformClockMiddleAction()) {
                    e.Handled(true);
                }
            } catch (...) {}
        });

    // handledEventsToo: the button marks pointer events as handled before they reach us.
    found.AddHandler(UIElement::PointerWheelChangedEvent(), winrt::box_value(*d->wheelHandler), true);
    found.AddHandler(UIElement::PointerPressedEvent(), winrt::box_value(*d->pressedHandler), true);
    d->actionTarget = winrt::make_weak(found);
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

    ApplyTextBlockStyles(dTb, enabled ? &g_settings.dateStyle : nullptr, maxW, &dataPtr->dateVisibilityPropertyChangedToken, 1, &dataPtr->dateTextChangedToken);
    ApplyTextBlockStyles(tTb, enabled ? &g_settings.timeStyle : nullptr, maxW, &dataPtr->timeVisibilityPropertyChangedToken, 0, &dataPtr->timeTextChangedToken);
    try { ApplyClockActionHandlers(dateTimeIconContentElement, dataPtr, enabled); } catch (...) {}
    dataPtr->styleIndex = curIdx;
}

std::vector<HWND> GetXamlHostWnds();
HWND GetTaskbarUiWnd();

void RefreshClockElementStylesOnCurrentThread() {
    std::vector<FrameworkElement> elements;
    for (const auto& d : g_clockElementStyleData) {
        if (auto e = d.dateTimeIconContentElement.get()) elements.push_back(e);
    }
    ++g_clockElementStyleIndex;
    for (auto& e : elements) {
        // Elements that live on another XAML thread throw here and are
        // handled when that thread runs this function.
        try { ApplyDateTimeIconContentStyles(e); } catch (...) {}
    }
}

void RefreshClockElementStyles() {
    if (g_winVersion < WinVersion::Win11_22H2 || g_unloading) return;
    if (HWND hUi = GetTaskbarUiWnd()) {
        RunFromWindowThread(hUi, [](PVOID) { RefreshClockElementStylesOnCurrentThread(); }, nullptr);
    }
    for (HWND hHost : GetXamlHostWnds()) {
        RunFromWindowThread(hHost, [](PVOID) { RefreshClockElementStylesOnCurrentThread(); }, nullptr);
    }
}

// Picks the first matching color rule for the top and bottom line and
// re-applies the clock styles when the chosen colors change.
void UpdateClockColorRules() {
    if (g_colorRuleCount == 0 || g_unloading) return;

    std::wstring newColors[2];
    {
        std::lock_guard<std::mutex> guard(g_formatLineMutex);
        for (int line = 0; line < 2; line++) {
            for (const auto& r : g_settings.colorRules) {
                if (!(r.lines & (1 << line))) continue;
                double v = 0;
                if (!GetRuleMetricValue(r.metric, &v)) continue;
                if (r.above ? v > r.threshold : v < r.threshold) {
                    newColors[line] = r.color.get();
                    break;
                }
            }
        }
    }

    bool changed = false;
    {
        std::lock_guard<std::mutex> guard(g_clockRuleMutex);
        for (int line = 0; line < 2; line++) {
            if (g_clockRuleColor[line] != newColors[line]) {
                g_clockRuleColor[line] = newColors[line];
                changed = true;
            }
        }
    }
    if (changed) RefreshClockElementStyles();
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
        if (wcscmp(EffTopLine(), L"-") != 0) {
            if (!cch) return FORMATTED_BUFFER_SIZE;
            return FormatLine(str, cch, EffTopLine()) + 1;
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
            if (wcscmp(EffBottomLine(), L"-") != 0) {
                if (!cch) return FORMATTED_BUFFER_SIZE;
                return FormatLine(str, cch, EffBottomLine()) + 1;
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

// ----- WIN10 & EXPLORER PATCHER HOOKS -----

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
            FormatLine(g_getTooltipTextBuffer, g_getTooltipTextBufferSize, EffTooltipLine());
        } else {
            size_t slen = wcslen(g_getTooltipTextBuffer);
            WCHAR* p = g_getTooltipTextBuffer + slen;
            size_t rem = g_getTooltipTextBufferSize - slen;
            if (rem > 4) {
                wcscpy(p, L"\r\n\r\n");
                FormatLine(p + 4, rem - 4, EffTooltipLine());
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
        if (wcscmp(EffTopLine(), L"-") != 0) {
            return FormatLine(str, cch, EffTopLine()) + 1;
        }
    }
    return GetTimeFormatEx_Original(loc, fl, t, fmt, str, cch);
}

int WINAPI GetDateFormatEx_Hook_Win10(LPCWSTR loc, DWORD fl, CONST SYSTEMTIME* dt, LPCWSTR fmt, LPWSTR str, int cch, LPCWSTR cal) {
    if (g_updateTextStringThreadId == GetCurrentThreadId()) {
        g_getDateFormatExCounter++;
        PCWSTR f = (g_getDateFormatExCounter > 1) ? g_settings.middleLine.get() : EffBottomLine();
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

// ----- UNIFIED SYMBOL HOOKING -----

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

// ----- SETTINGS APPLICATION -----

NetworkMetricsFormat ParseNetworkMetricsFormat(PCWSTR value) {
    if (wcscmp(value, L"mbsNumberOnly") == 0) return NetworkMetricsFormat::mbsNumberOnly;
    if (wcscmp(value, L"mbsDynamic") == 0) return NetworkMetricsFormat::mbsDynamic;
    if (wcscmp(value, L"mbits") == 0) return NetworkMetricsFormat::mbits;
    if (wcscmp(value, L"mbitsNumberOnly") == 0) return NetworkMetricsFormat::mbitsNumberOnly;
    if (wcscmp(value, L"mbitsDynamic") == 0) return NetworkMetricsFormat::mbitsDynamic;
    return NetworkMetricsFormat::mbs;
}

// Parses "YYYY-MM-DD" or "YYYY-MM-DD HH:MM" (local time) into FILETIME ticks.
bool ParseCountdownTarget(PCWSTR s, ULONGLONG* out) {
    PWSTR p = const_cast<PWSTR>(s);
    long v[5] = {0, 0, 0, 0, 0};
    v[0] = wcstol(p, &p, 10);
    if (*p != L'-') return false;
    v[1] = wcstol(p + 1, &p, 10);
    if (*p != L'-') return false;
    v[2] = wcstol(p + 1, &p, 10);
    while (*p == L' ' || *p == L'T') p++;
    if (*p) {
        v[3] = wcstol(p, &p, 10);
        if (*p == L':') v[4] = wcstol(p + 1, &p, 10);
    }
    SYSTEMTIME st{};
    st.wYear = static_cast<WORD>(v[0]);
    st.wMonth = static_cast<WORD>(v[1]);
    st.wDay = static_cast<WORD>(v[2]);
    st.wHour = static_cast<WORD>(v[3]);
    st.wMinute = static_cast<WORD>(v[4]);
    FILETIME ft;
    if (!SystemTimeToFileTime(&st, &ft)) return false;
    *out = FtToU64(ft);
    return true;
}

static double ParsePrayerDouble(PCWSTR text, double fallback, double lo, double hi) {
    PWSTR end = nullptr;
    double v = wcstod(text, &end);
    if (end == text || !std::isfinite(v)) return fallback;
    return std::clamp(v, lo, hi);
}

static std::vector<std::wstring> SplitPrayerList(PCWSTR text) {
    std::vector<std::wstring> parts;
    std::wstring cur;
    for (PCWSTR c = text; ; c++) {
        if (*c == L',' || *c == L'\0') {
            size_t a = cur.find_first_not_of(L" \t");
            size_t b = cur.find_last_not_of(L" \t");
            parts.push_back(a == std::wstring::npos ? L"" : cur.substr(a, b - a + 1));
            cur.clear();
            if (*c == L'\0') break;
        } else {
            cur += *c;
        }
    }
    return parts;
}

void LoadPrayerSettings() {
    PrayerSettings p;
    p.latitude = ParsePrayerDouble(StringSetting::make(L"Prayer.Latitude"), p.latitude, -90.0, 90.0);
    p.longitude = ParsePrayerDouble(StringSetting::make(L"Prayer.Longitude"), p.longitude, -180.0, 180.0);

    StringSetting method = StringSetting::make(L"Prayer.Method");
    if (wcscmp(method, L"mwl") == 0) { p.fajrAngle = 18; p.ishaAngle = 17; }
    else if (wcscmp(method, L"isna") == 0) { p.fajrAngle = 15; p.ishaAngle = 15; }
    else if (wcscmp(method, L"egypt") == 0) { p.fajrAngle = 19.5; p.ishaAngle = 17.5; }
    else if (wcscmp(method, L"makkah") == 0) { p.fajrAngle = 18.5; p.ishaMinutesAfterMaghrib = 90; }
    else if (wcscmp(method, L"custom") == 0) {
        p.fajrAngle = ParsePrayerDouble(StringSetting::make(L"Prayer.CustomFajrAngle"), 18, 0, 30);
        p.ishaAngle = ParsePrayerDouble(StringSetting::make(L"Prayer.CustomIshaAngle"), 18, 0, 30);
    }  // else karachi: 18 / 18

    p.asrFactor = wcscmp(StringSetting::make(L"Prayer.Asr"), L"standard") == 0 ? 1 : 2;
    p.ishaEndsAtFajr = wcscmp(StringSetting::make(L"Prayer.IshaEnd"), L"fajr") == 0;

    StringSetting fmt = StringSetting::make(L"Prayer.TimeFormat");
    p.timeFormat = wcscmp(fmt, L"24h") == 0 ? 2 : (wcscmp(fmt, L"12h") == 0 ? 1 : 0);

    auto names = SplitPrayerList(StringSetting::make(L"Prayer.Names"));
    for (size_t i = 0; i < 6 && i < names.size(); i++) {
        if (!names[i].empty()) p.names[i] = names[i];
    }
    auto adj = SplitPrayerList(StringSetting::make(L"Prayer.Adjustments"));
    for (size_t i = 0; i < 6 && i < adj.size(); i++) {
        p.offsets[i] = std::clamp(static_cast<int>(wcstol(adj[i].c_str(), nullptr, 10)), -180, 180);
    }

    g_settings.prayer = std::move(p);
    g_prayerSettingsVersion++;
}

int ParseRuleMetric(PCWSTR s) {
    if (wcscmp(s, L"cpu") == 0) return kRuleCpu;
    if (wcscmp(s, L"ram") == 0) return kRuleRam;
    if (wcscmp(s, L"gpu") == 0) return kRuleGpu;
    if (wcscmp(s, L"cpu_temp") == 0) return kRuleCpuTemp;
    if (wcscmp(s, L"battery") == 0) return kRuleBattery;
    return kRuleNone;
}

void LoadSettings() {
    // Tray settings
    g_settings.hideVolumeIcon = Wh_GetIntSetting(L"SystemTray.hideVolumeIcon");
    g_settings.hideNetworkIcon = Wh_GetIntSetting(L"SystemTray.hideNetworkIcon");
    g_settings.hideBatteryIcon = Wh_GetIntSetting(L"SystemTray.hideBatteryIcon");
    g_settings.grayscaleBatteryIcon = Wh_GetIntSetting(L"SystemTray.grayscaleBatteryIcon");
    g_settings.hideMicrophoneIcon = Wh_GetIntSetting(L"SystemTray.hideMicrophoneIcon");
    g_settings.hideGeolocationIcon = Wh_GetIntSetting(L"SystemTray.hideGeolocationIcon");
    g_settings.hideStudioEffectsIcon = Wh_GetIntSetting(L"SystemTray.hideStudioEffectsIcon");
    g_settings.hideRecallIcon = Wh_GetIntSetting(L"SystemTray.hideRecallIcon");
    g_settings.hideLanguageBar = Wh_GetIntSetting(L"SystemTray.hideLanguageBar");
    g_settings.hideLanguageSupplementaryIcons = Wh_GetIntSetting(L"SystemTray.hideLanguageSupplementaryIcons");

    PCWSTR hideBell = Wh_GetStringSetting(L"SystemTray.hideBellIcon");
    g_settings.hideBellIcon = HideBellIcon::never;
    if (wcscmp(hideBell, L"whenInactive") == 0) g_settings.hideBellIcon = HideBellIcon::whenInactive;
    else if (wcscmp(hideBell, L"whenInactiveAndNoDnd") == 0) g_settings.hideBellIcon = HideBellIcon::whenInactiveAndNoDnd;
    else if (wcscmp(hideBell, L"always") == 0) g_settings.hideBellIcon = HideBellIcon::always;
    Wh_FreeStringSetting(hideBell);

    g_settings.showDesktopButtonWidth = Wh_GetIntSetting(L"SystemTray.showDesktopButtonWidth");

    // Clock settings
    g_settings.showSeconds = Wh_GetIntSetting(L"ClockFormat.ShowSeconds");
    g_settings.timeFormat = StringSetting::make(L"ClockFormat.TimeFormat");
    g_settings.dateFormat = StringSetting::make(L"ClockFormat.DateFormat");
    g_settings.dateLocale = StringSetting::make(L"ClockFormat.DateLocale");
    g_settings.weekdayFormat = StringSetting::make(L"ClockFormat.WeekdayFormat");

    g_settings.weekdayFormatCustom.clear();
    if (wcscmp(g_settings.weekdayFormat, L"custom") == 0) {
        StringSetting custom = StringSetting::make(L"ClockFormat.WeekdayFormatCustom");
        for (const auto name : SplitStringView(custom.get(), L",")) {
            g_settings.weekdayFormatCustom.emplace_back(TrimStringView(name));
        }
        g_settings.weekdayFormatCustom.resize(7);
    }

    g_settings.topLine = StringSetting::make(L"ClockLines.TopLine");
    g_settings.bottomLine = StringSetting::make(L"ClockLines.BottomLine");
    g_settings.middleLine = StringSetting::make(L"ClockLines.MiddleLine");
    g_settings.tooltipLine = StringSetting::make(L"ClockLines.TooltipLine");

    g_settings.tooltipLineMode = TooltipLineMode::append;
    StringSetting tlm = StringSetting::make(L"ClockLines.TooltipLineMode");
    if (wcscmp(tlm, L"replace") == 0) g_settings.tooltipLineMode = TooltipLineMode::replace;

    g_presetTopLine = g_presetBottomLine = g_presetTooltipLine = nullptr;
    {
        StringSetting preset = StringSetting::make(L"ClockLines.Preset");
        for (const auto& p : kLinePresets) {
            if (wcscmp(preset, p.id) == 0) {
                g_presetTopLine = p.top;
                g_presetBottomLine = p.bottom;
                g_presetTooltipLine = p.tooltip;
                break;
            }
        }
    }
    g_settings.showTagHints = Wh_GetIntSetting(L"ClockLines.ShowTagHints");

    g_settings.pingHost = StringSetting::make(L"NetworkInfo.PingHost").get();
    g_settings.pingInterval = Wh_GetIntSetting(L"NetworkInfo.PingInterval");
    {
        StringSetting hijri = StringSetting::make(L"AlternateCalendars.HijriType");
        g_settings.hijriCivil = wcscmp(hijri, L"civil") == 0;
    }
    g_settings.hijriOffset = std::clamp<int>(Wh_GetIntSetting(L"AlternateCalendars.HijriOffset"), -2, 2);
    g_settings.bengaliTextScale = std::clamp<int>(Wh_GetIntSetting(L"AlternateCalendars.BengaliTextScale"), 50, 150);
    g_settings.icsUrl = StringSetting::make(L"CalendarEvents.IcsUrl").get();
    g_settings.icsMaxLength = Wh_GetIntSetting(L"CalendarEvents.MaxLength");
    g_settings.icsIncludeAllDay = Wh_GetIntSetting(L"CalendarEvents.IncludeAllDay");
    g_settings.icsNoEventText = StringSetting::make(L"CalendarEvents.NoEventText").get();

    {
        StringSetting scroll = StringSetting::make(L"ClockActions.Scroll");
        g_settings.clockScrollAction = wcscmp(scroll, L"volume") == 0 ? 1 : wcscmp(scroll, L"track") == 0 ? 2 : 0;
        StringSetting mid = StringSetting::make(L"ClockActions.MiddleClick");
        g_settings.clockMiddleAction = wcscmp(mid, L"playpause") == 0  ? 1
                                       : wcscmp(mid, L"mute") == 0     ? 2
                                       : wcscmp(mid, L"next") == 0     ? 3
                                       : wcscmp(mid, L"previous") == 0 ? 4
                                       : wcscmp(mid, L"taskmgr") == 0  ? 5
                                       : wcscmp(mid, L"command") == 0  ? 6
                                       : wcscmp(mid, L"timer_toggle") == 0 ? 7
                                       : wcscmp(mid, L"timer_reset") == 0  ? 8
                                                                       : 0;
    }
    g_settings.clockCommand = StringSetting::make(L"ClockActions.Command").get();
    {
        StringSetting dyn = StringSetting::make(L"TaskbarAppearance.DynamicTransparency");
        g_settings.dynamicTransparency = wcscmp(dyn, L"opaque") == 0 ? 1 : 0;
    }
    g_settings.logClockThreads = Wh_GetIntSetting(L"Diagnostics.LogClockThreads");
    {
        StringSetting shape = StringSetting::make(L"TaskbarShape.Style");
        g_settings.shapeStyle = wcscmp(shape, L"rounded") == 0 ? 1
                                : wcscmp(shape, L"pill") == 0  ? 2
                                                               : 0;
    }

    g_settings.timerMinutes = std::clamp<int>(Wh_GetIntSetting(L"ClockTimer.TimerMinutes"), 1, 1440);
    g_settings.pomodoroWorkMinutes = std::clamp<int>(Wh_GetIntSetting(L"ClockTimer.WorkMinutes"), 1, 240);
    g_settings.pomodoroBreakMinutes = std::clamp<int>(Wh_GetIntSetting(L"ClockTimer.BreakMinutes"), 1, 120);
    g_settings.timerSound = Wh_GetIntSetting(L"ClockTimer.PlaySound");

    g_settings.profileRules.clear();
    g_profilePreset = nullptr;
    for (int i = 0;; i++) {
        StringSetting cond = StringSetting::make(L"Profiles.Rules[%d].Condition", i);
        if (*cond == L'\0') break;
        ProfileRule r{};
        r.condition = ParseProfileCondition(cond);
        StringSetting presetId = StringSetting::make(L"Profiles.Rules[%d].Preset", i);
        r.preset = FindLinePreset(presetId);
        if (!r.condition || !r.preset) continue;
        r.threshold = Wh_GetIntSetting(L"Profiles.Rules[%d].Threshold", i);
        r.startHour = Wh_GetIntSetting(L"Profiles.Rules[%d].StartHour", i);
        r.endHour = Wh_GetIntSetting(L"Profiles.Rules[%d].EndHour", i);
        g_settings.profileRules.push_back(r);
    }
    {
        // The feed is fetched again by the web content thread after a settings change.
        std::lock_guard<std::mutex> icsGuard(g_webContentMutex);
        g_icsEvents.clear();
        g_icsVersion++;
    }

    g_settings.countdownTargets.clear();
    for (int i = 0;; i++) {
        StringSetting c = StringSetting::make(L"ClockFormat.Countdowns[%d]", i);
        if (*c == L'\0') break;
        ULONGLONG target = 0;
        if (!ParseCountdownTarget(c.get(), &target)) target = 0;
        g_settings.countdownTargets.push_back(target);
    }

    LoadPrayerSettings();

    g_settings.width = Wh_GetIntSetting(L"ClockLayout.Width");
    g_settings.height = Wh_GetIntSetting(L"ClockLayout.Height");
    g_settings.maxWidth = Wh_GetIntSetting(L"ClockLayout.MaxWidth");
    g_settings.textSpacing = Wh_GetIntSetting(L"ClockLayout.TextSpacing");

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
    g_settings.dataCollection.graphLength = Wh_GetIntSetting(L"DataCollection.GraphLength");
    g_settings.dataCollection.batteryUpdateInterval = Wh_GetIntSetting(L"DataCollection.BatteryUpdateInterval");
    g_settings.dataCollection.networkAdapterName = StringSetting::make(L"DataCollection.NetworkAdapterName");
    g_settings.dataCollection.gpuAdapterName = StringSetting::make(L"DataCollection.GpuAdapterName");

    g_settings.mediaPlayer.maxLength = Wh_GetIntSetting(L"MediaPlayer.MaxLength");
    g_settings.mediaPlayer.mediaInfoFormat = StringSetting::make(L"MediaPlayer.MediaInfoFormat");
    g_settings.mediaPlayer.noMediaText = StringSetting::make(L"MediaPlayer.NoMediaText");
    g_settings.mediaPlayer.removeBrackets = Wh_GetIntSetting(L"MediaPlayer.RemoveBrackets");
    g_settings.mediaPlayer.marquee = Wh_GetIntSetting(L"MediaPlayer.Marquee");
    g_settings.mediaPlayer.marqueeSpeed = Wh_GetIntSetting(L"MediaPlayer.MarqueeSpeed");
    g_settings.mediaPlayer.ignoredPlayers.clear();
    for (int i = 0;; i++) {
        StringSetting player = StringSetting::make(L"MediaPlayer.IgnoredPlayers[%d]", i);
        if (*player == '\0') break;
        g_settings.mediaPlayer.ignoredPlayers.push_back(std::move(player));
    }

    g_settings.webContentWeatherLocation = StringSetting::make(L"WebContent.WeatherLocation");
    g_settings.webContentWeatherFormat = StringSetting::make(L"WebContent.WeatherFormat");
    g_settings.webContentWeatherUnits = WebContentWeatherUnits::autoDetect;
    StringSetting wu = StringSetting::make(L"WebContent.WeatherUnits");
    if (wcscmp(wu, L"uscs") == 0) g_settings.webContentWeatherUnits = WebContentWeatherUnits::uscs;
    else if (wcscmp(wu, L"metric") == 0) g_settings.webContentWeatherUnits = WebContentWeatherUnits::metric;
    else if (wcscmp(wu, L"metricMsWind") == 0) g_settings.webContentWeatherUnits = WebContentWeatherUnits::metricMsWind;

    g_settings.weatherFallback = Wh_GetIntSetting(L"WebContent.WeatherFallback");
    g_settings.weatherPreset = 0;
    {
        StringSetting wp = StringSetting::make(L"WebContent.WeatherPreset");
        if (wcscmp(wp, L"conditions") == 0) g_settings.weatherPreset = 1;
        else if (wcscmp(wp, L"sun") == 0) g_settings.weatherPreset = 2;
        else if (wcscmp(wp, L"full") == 0) g_settings.weatherPreset = 3;
    }

    g_settings.webContentsItems.clear();
    for (int i = 0;; i++) {
        WebContentsSettings itm;
        itm.url = StringSetting::make(L"WebContent.Items[%d].Url", i);
        if (*itm.url == '\0') break;
        itm.blockStart = StringSetting::make(L"WebContent.Items[%d].BlockStart", i);
        itm.start = StringSetting::make(L"WebContent.Items[%d].Start", i);
        itm.end = StringSetting::make(L"WebContent.Items[%d].End", i);
        itm.contentMode = ContentMode::plainText;
        StringSetting cm = StringSetting::make(L"WebContent.Items[%d].ContentMode", i);
        if (wcscmp(cm, L"xml") == 0) itm.contentMode = ContentMode::xml;
        else if (wcscmp(cm, L"html") == 0) itm.contentMode = ContentMode::html;
        else if (wcscmp(cm, L"xmlHtml") == 0) itm.contentMode = ContentMode::xmlHtml;

        for (int j = 0;; j++) {
            StringSetting s = StringSetting::make(L"WebContent.Items[%d].SearchReplace[%d].Search", i, j);
            if (*s == '\0') break;
            StringSetting r = StringSetting::make(L"WebContent.Items[%d].SearchReplace[%d].Replace", i, j);
            try { itm.searchReplace.push_back({std::wregex(s), std::wstring(r)}); } catch (...) {}
        }
        itm.maxLength = Wh_GetIntSetting(L"WebContent.Items[%d].MaxLength", i);
        g_settings.webContentsItems.push_back(std::move(itm));
    }
    g_settings.webContentsUpdateInterval = Wh_GetIntSetting(L"WebContent.UpdateInterval");

    g_timeZoneInformation.clear();
    g_timeFormattedTz.clear();
    g_dateFormattedTz.clear();
    g_weekdayFormattedTz.clear();
    g_settings.timeZones.clear();
    for (int i = 0;; i++) {
        StringSetting tz = StringSetting::make(L"ClockFormat.TimeZones[%d]", i);
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

    g_settings.colorRules.clear();
    for (int i = 0;; i++) {
        StringSetting metric = StringSetting::make(L"ClockColors.Rules[%d].Metric", i);
        if (*metric == L'\0') break;
        int m = ParseRuleMetric(metric);
        if (!m) continue;

        ColorRule r;
        r.metric = m;
        StringSetting cond = StringSetting::make(L"ClockColors.Rules[%d].Condition", i);
        r.above = wcscmp(cond, L"below") != 0;
        r.threshold = Wh_GetIntSetting(L"ClockColors.Rules[%d].Threshold", i);
        r.color = StringSetting::make(L"ClockColors.Rules[%d].Color", i);
        StringSetting line = StringSetting::make(L"ClockColors.Rules[%d].Line", i);
        r.lines = wcscmp(line, L"top") == 0 ? 1 : wcscmp(line, L"bottom") == 0 ? 2 : 3;
        g_settings.colorRules.push_back(std::move(r));
    }
    g_colorRuleCount = static_cast<int>(g_settings.colorRules.size());
    {
        std::lock_guard<std::mutex> ruleGuard(g_clockRuleMutex);
        g_clockRuleColor[0].clear();
        g_clockRuleColor[1].clear();
    }

    g_clockElementStyleEnabled =
        (g_settings.maxWidth || g_settings.textSpacing || !g_settings.colorRules.empty() ||
         g_settings.clockScrollAction || g_settings.clockMiddleAction ||
         g_settings.timeStyle.hidden || *g_settings.timeStyle.textColor ||
         *g_settings.timeStyle.textAlignment || g_settings.timeStyle.fontSize ||
         *g_settings.timeStyle.fontFamily || *g_settings.timeStyle.fontWeight ||
         *g_settings.timeStyle.fontStyle || *g_settings.timeStyle.fontStretch ||
         g_settings.timeStyle.characterSpacing || g_settings.timeStyle.lineHeight ||
         g_settings.dateStyle.hidden || *g_settings.dateStyle.textColor ||
         *g_settings.dateStyle.textAlignment || g_settings.dateStyle.fontSize ||
         *g_settings.dateStyle.fontFamily || *g_settings.dateStyle.fontWeight ||
         *g_settings.dateStyle.fontStyle || *g_settings.dateStyle.fontStretch ||
         g_settings.dateStyle.characterSpacing || g_settings.dateStyle.lineHeight ||
         g_settings.bengaliTextScale != 100);
    g_clockElementStyleIndex++;
    g_settings.oldTaskbarOnWin11 = Wh_GetIntSetting(L"oldTaskbarOnWin11");

    // Transparency and App Hiding Settings
    g_settings.transparencyMode = StringSetting::make(L"TaskbarAppearance.TransparencyMode");
    g_settings.transparencyAlpha = Wh_GetIntSetting(L"TaskbarAppearance.TransparencyAlpha");
    g_settings.hideTaskbarApps = Wh_GetIntSetting(L"TaskbarAppearance.HideTaskbarApps");
    
    g_settings.appExceptions.clear();
    for (int i = 0;; i++) {
        StringSetting exception = StringSetting::make(L"TaskbarAppearance.AppExceptions[%d]", i);
        if (*exception == L'\0') break;
        g_settings.appExceptions.push_back(std::wstring(exception.get()));
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

// Forward declarations for transparency & app visibility
void ApplyTaskbarTransparency();
void ApplyTaskbarWindowComposition(HWND hTaskbar);
void ApplyTaskbarXamlBackgroundTransparency(XamlRoot xamlRoot, HWND hTaskbar);
void ApplyTaskbarAppVisibility(XamlRoot xamlRoot);
void ApplyTaskbarAppVisibilityToButton(FrameworkElement button);

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
        if (xamlRoot) {
            ApplyTaskbarXamlBackgroundTransparency(xamlRoot, hWnd);
            ApplyTrayStylesVisualTree(xamlRoot);
            ApplyTaskbarAppVisibility(xamlRoot);
        }

        ApplyTaskbarWindowComposition(hWnd);
    }, &hTaskbarWnd);
}

void ApplySettings() {
    HWND hTaskbarWnd = FindCurrentProcessTaskbarWnd();
    ApplySettingsTray(hTaskbarWnd);

    if (g_winVersion >= WinVersion::Win11) {
        ApplyTaskbarTransparency();
        ApplySettingsWin11Clock();
    } else {
        ApplySettingsWin10Clock();
    }
}

// ----- TASKBAR TRANSPARENCY & APP VISIBILITY -----

enum ACCENT_STATE {
    ACCENT_DISABLED = 0,
    ACCENT_ENABLE_GRADIENT = 1,
    ACCENT_ENABLE_TRANSPARENTGRADIENT = 2,
    ACCENT_ENABLE_BLURBEHIND = 3,
    ACCENT_ENABLE_ACRYLICBLURBEHIND = 4,
};

struct ACCENT_POLICY {
    ACCENT_STATE AccentState;
    DWORD AccentFlags;
    DWORD GradientColor;
    DWORD AnimationId;
};

struct WINDOWCOMPOSITIONATTRIBDATA {
    DWORD Attrib;
    PVOID pvData;
    SIZE_T cbData;
};

using SetWindowCompositionAttribute_t =
    BOOL(WINAPI*)(HWND, WINDOWCOMPOSITIONATTRIBDATA*);

using DwmSetWindowAttribute_t =
    HRESULT(WINAPI*)(HWND, DWORD, LPCVOID, DWORD);

constexpr DWORD kWcaAccentPolicy = 19;
constexpr DWORD kDwmwaSystemBackdropType = 38;
constexpr DWORD kDwmwaMicaEffect = 1029;

enum class TaskbarBackdropType : DWORD {
    Auto = 0,
    None = 1,
    Mica = 2,
    Acrylic = 3,
    Tabbed = 4,
};

// ----- DYNAMIC TRANSPARENCY -----

using DwmGetWindowAttribute_t = HRESULT(WINAPI*)(HWND, DWORD, PVOID, DWORD);

bool IsWindowCloaked(HWND hWnd) {
    static DwmGetWindowAttribute_t s_get = []() -> DwmGetWindowAttribute_t {
        HMODULE hDwm = LoadLibraryExW(L"dwmapi.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        return hDwm ? reinterpret_cast<DwmGetWindowAttribute_t>(GetProcAddress(hDwm, "DwmGetWindowAttribute")) : nullptr;
    }();
    DWORD cloaked = 0;
    constexpr DWORD kDwmaCloaked = 14;
    return s_get && SUCCEEDED(s_get(hWnd, kDwmaCloaked, &cloaked, sizeof(cloaked))) && cloaked;
}

std::mutex g_maximizedMutex;
std::vector<HMONITOR> g_maximizedMonitors;
ULONGLONG g_maximizedTick = 0;

// Monitors that currently show a visible, maximized, top-level app window.
void RefreshMaximizedMonitors() {
    std::vector<HMONITOR> found;
    EnumWindows(
        [](HWND hWnd, LPARAM lParam) -> BOOL {
            auto* out = reinterpret_cast<std::vector<HMONITOR>*>(lParam);
            if (!IsWindowVisible(hWnd) || IsIconic(hWnd) || !IsZoomed(hWnd)) return TRUE;
            if (GetWindow(hWnd, GW_OWNER)) return TRUE;
            if (GetWindowLongPtrW(hWnd, GWL_EXSTYLE) & WS_EX_TOOLWINDOW) return TRUE;
            if (IsWindowCloaked(hWnd)) return TRUE;

            WCHAR cls[64]{};
            if (GetClassNameW(hWnd, cls, ARRAYSIZE(cls))) {
                if (_wcsicmp(cls, L"Progman") == 0 || _wcsicmp(cls, L"WorkerW") == 0 ||
                    _wcsicmp(cls, L"Shell_TrayWnd") == 0 || _wcsicmp(cls, L"Shell_SecondaryTrayWnd") == 0) {
                    return TRUE;
                }
            }
            HMONITOR mon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONULL);
            if (mon && std::find(out->begin(), out->end(), mon) == out->end()) out->push_back(mon);
            return TRUE;
        },
        reinterpret_cast<LPARAM>(&found));

    std::lock_guard<std::mutex> guard(g_maximizedMutex);
    g_maximizedMonitors = std::move(found);
    g_maximizedTick = GetTickCount64() | 1;
}

void RefreshMaximizedMonitorsIfStale() {
    {
        std::lock_guard<std::mutex> guard(g_maximizedMutex);
        if (g_maximizedTick && GetTickCount64() - g_maximizedTick < 300) return;
    }
    RefreshMaximizedMonitors();
}

bool MonitorHasMaximizedWindow(HMONITOR mon) {
    RefreshMaximizedMonitorsIfStale();
    std::lock_guard<std::mutex> guard(g_maximizedMutex);
    return std::find(g_maximizedMonitors.begin(), g_maximizedMonitors.end(), mon) != g_maximizedMonitors.end();
}

// Changes whenever the set of monitors with a maximized window changes.
uintptr_t MaximizedMonitorsSignature() {
    RefreshMaximizedMonitors();
    std::lock_guard<std::mutex> guard(g_maximizedMutex);
    uintptr_t sig = 0;
    for (HMONITOR m : g_maximizedMonitors) sig ^= reinterpret_cast<uintptr_t>(m) * 2654435761u;
    return sig ^ g_maximizedMonitors.size();
}

// True when a taskbar shape is selected together with a transparency mode. The
// window-level backdrop would fill the whole (square) window, so the shape
// styles draw the transparency inside the rounded background instead.
bool ShapeOwnsBackdrop() {
    if (g_settings.shapeStyle == 0 || g_settings.oldTaskbarOnWin11 || !g_settings.transparencyMode) return false;
    PCWSTR mode = g_settings.transparencyMode.get();
    return *mode && _wcsicmp(mode, L"default") != 0;
}

// The transparency mode to use for a taskbar window: the configured mode, or
// the default (opaque) taskbar while dynamic transparency detects a maximized
// window on that taskbar's monitor.
std::wstring GetEffectiveTransparencyMode(HWND hTaskbar) {
    if (ShapeOwnsBackdrop()) return L"default";
    std::wstring mode = g_settings.transparencyMode ? std::wstring(g_settings.transparencyMode.get()) : L"default";
    if (!mode.empty() && g_settings.dynamicTransparency && hTaskbar) {
        HMONITOR mon = MonitorFromWindow(hTaskbar, MONITOR_DEFAULTTOPRIMARY);
        if (MonitorHasMaximizedWindow(mon)) return L"default";
    }
    return mode;
}

bool IsTransparencyMode(std::wstring_view mode, std::wstring_view expected) {
    return _wcsicmp(std::wstring(mode).c_str(), std::wstring(expected).c_str()) == 0;
}

void ResetTaskbarWindowComposition(HWND hTaskbar) {
    if (!hTaskbar) return;

    if (HMODULE hUser = GetModuleHandle(L"user32.dll")) {
        auto setWindowCompositionAttribute =
            reinterpret_cast<SetWindowCompositionAttribute_t>(
                GetProcAddress(hUser, "SetWindowCompositionAttribute"));

        if (setWindowCompositionAttribute) {
            ACCENT_POLICY policy{};
            policy.AccentState = ACCENT_DISABLED;
            WINDOWCOMPOSITIONATTRIBDATA data{
                kWcaAccentPolicy, &policy, sizeof(policy)};
            setWindowCompositionAttribute(hTaskbar, &data);
        }
    }

    if (HMODULE hDwm = LoadLibraryEx(
            L"dwmapi.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32)) {
        auto dwmSetWindowAttribute =
            reinterpret_cast<DwmSetWindowAttribute_t>(
                GetProcAddress(hDwm, "DwmSetWindowAttribute"));

        if (dwmSetWindowAttribute) {
            TaskbarBackdropType backdrop = TaskbarBackdropType::Auto;
            dwmSetWindowAttribute(hTaskbar, kDwmwaSystemBackdropType,
                                  &backdrop, sizeof(backdrop));

            BOOL mica = FALSE;
            dwmSetWindowAttribute(hTaskbar, kDwmwaMicaEffect,
                                  &mica, sizeof(mica));
        }

        FreeLibrary(hDwm);
    }
}

void ApplyTaskbarXamlBackgroundTransparency(XamlRoot xamlRoot, HWND hTaskbar) {
    if (!xamlRoot || !xamlRoot.Content()) return;

    // The shape styles own the background fill; clearing it here would undo them.
    if (!g_unloading && ShapeOwnsBackdrop()) return;

    std::wstring mode = GetEffectiveTransparencyMode(hTaskbar);

    int transparency = std::clamp(g_settings.transparencyAlpha, 0, 100);
    bool isMica = IsTransparencyMode(mode, L"mica");
    bool enable = !g_unloading && !mode.empty() &&
                  !IsTransparencyMode(mode, L"default") &&
                  (isMica || transparency > 0);

    auto root = xamlRoot.Content().try_as<FrameworkElement>();
    if (!root) return;

    auto taskbarFrame = FindChildByClassName(root, L"Taskbar.TaskbarFrame");
    if (!taskbarFrame) {
        if (winrt::get_class_name(root) == L"Taskbar.TaskbarFrame") {
            taskbarFrame = root;
        }
    }
    if (!taskbarFrame) return;

    auto rootGrid = FindChildByName(taskbarFrame, L"RootGrid");
    if (!rootGrid) return;

    auto rootGridPanel = rootGrid.try_as<Controls::Panel>();
    auto backgroundControl = FindChildByClassName(rootGrid, L"Taskbar.TaskbarBackground");
    auto backgroundPanel = backgroundControl.try_as<Controls::Panel>();

    FrameworkElement backgroundFill = nullptr;
    FrameworkElement backgroundStroke = nullptr;
    if (backgroundControl) {
        auto backgroundGrid = FindChildByClassName(
            backgroundControl, L"Windows.UI.Xaml.Controls.Grid");
        if (backgroundGrid) {
            backgroundFill = FindChildByName(backgroundGrid, L"BackgroundFill");
            backgroundStroke = FindChildByName(backgroundGrid, L"BackgroundStroke");
        }
    }

    if (!enable) {
        if (rootGridPanel) {
            rootGridPanel.ClearValue(Controls::Panel::BackgroundProperty());
        }
        if (backgroundPanel) {
            backgroundPanel.ClearValue(Controls::Panel::BackgroundProperty());
        }
        if (auto rect = backgroundFill.try_as<Shapes::Shape>()) {
            rect.ClearValue(Shapes::Shape::FillProperty());
        }
        if (auto rect = backgroundStroke.try_as<Shapes::Shape>()) {
            rect.ClearValue(Shapes::Shape::FillProperty());
        }
        return;
    }

    auto transparentBrush =
        Media::SolidColorBrush(winrt::Windows::UI::Colors::Transparent());

    if (rootGridPanel) {
        rootGridPanel.Background(transparentBrush);
    }
    if (backgroundPanel) {
        backgroundPanel.Background(transparentBrush);
    }
    if (auto rect = backgroundFill.try_as<Shapes::Shape>()) {
        rect.Fill(transparentBrush);
    }
    if (auto rect = backgroundStroke.try_as<Shapes::Shape>()) {
        rect.Fill(transparentBrush);
    }
}

void ApplyTaskbarWindowComposition(HWND hTaskbar) {
    if (!hTaskbar) return;

    std::wstring mode = GetEffectiveTransparencyMode(hTaskbar);

    if (g_unloading || mode.empty() || IsTransparencyMode(mode, L"default")) {
        ResetTaskbarWindowComposition(hTaskbar);
        return;
    }

    int transparency = std::clamp(g_settings.transparencyAlpha, 0, 100);

    if (transparency == 0 && !IsTransparencyMode(mode, L"mica")) {
        ResetTaskbarWindowComposition(hTaskbar);
        return;
    }

    DWORD alpha = static_cast<DWORD>((100 - transparency) * 255 / 100);

    if (IsTransparencyMode(mode, L"mica")) {
        HMODULE hDwm =
            LoadLibraryEx(L"dwmapi.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (hDwm) {
            auto dwmSetWindowAttribute =
                reinterpret_cast<DwmSetWindowAttribute_t>(
                    GetProcAddress(hDwm, "DwmSetWindowAttribute"));

            if (dwmSetWindowAttribute) {
                TaskbarBackdropType backdrop = TaskbarBackdropType::Mica;
                HRESULT hr = dwmSetWindowAttribute(
                    hTaskbar, kDwmwaSystemBackdropType, &backdrop,
                    sizeof(backdrop));

                if (FAILED(hr)) {
                    BOOL mica = TRUE;
                    dwmSetWindowAttribute(hTaskbar, kDwmwaMicaEffect,
                                          &mica, sizeof(mica));
                }
            }

            FreeLibrary(hDwm);
        }
        return;
    }

    HMODULE hUser = GetModuleHandle(L"user32.dll");
    if (!hUser) return;

    auto setWindowCompositionAttribute =
        reinterpret_cast<SetWindowCompositionAttribute_t>(
            GetProcAddress(hUser, "SetWindowCompositionAttribute"));
    if (!setWindowCompositionAttribute) {
        Wh_Log(L"SetWindowCompositionAttribute is unavailable");
        return;
    }

    ACCENT_POLICY policy{};
    policy.GradientColor = (alpha << 24) | 0x00000000;
    policy.AccentFlags = 2;

    if (IsTransparencyMode(mode, L"transparent")) {
        policy.AccentState = ACCENT_ENABLE_TRANSPARENTGRADIENT;
    } else if (IsTransparencyMode(mode, L"blur")) {
        policy.AccentState = ACCENT_ENABLE_BLURBEHIND;
    } else if (IsTransparencyMode(mode, L"acrylic")) {
        policy.AccentState = ACCENT_ENABLE_ACRYLICBLURBEHIND;
    } else {
        ResetTaskbarWindowComposition(hTaskbar);
        return;
    }

    WINDOWCOMPOSITIONATTRIBDATA data{
        kWcaAccentPolicy, &policy, sizeof(policy)};

    if (!setWindowCompositionAttribute(hTaskbar, &data)) {
        Wh_Log(L"SetWindowCompositionAttribute failed for taskbar");
    }
}

void ApplyTaskbarTransparency() {
    EnumWindows(
        [](HWND hWnd, LPARAM) -> BOOL {
            DWORD processId = 0;
            WCHAR className[64]{};

            if (!GetWindowThreadProcessId(hWnd, &processId) ||
                processId != GetCurrentProcessId() ||
                !GetClassName(hWnd, className, ARRAYSIZE(className))) {
                return TRUE;
            }

            if (_wcsicmp(className, L"Shell_TrayWnd") == 0 ||
                _wcsicmp(className, L"Shell_SecondaryTrayWnd") == 0) {
                ApplyTaskbarWindowComposition(hWnd);
            }

            return TRUE;
        },
        0);
}

// ------------------------------------------
// TRANSPARENCY WATCHDOG
//
// ApplyTaskbarWindowComposition()/ApplyTaskbarXamlBackgroundTransparency()
// are otherwise only invoked from ApplySettings() at mod init/uninit/settings
// change. Windows 11 can silently rebuild the taskbar's XAML tree or reset
// its window composition attribute (monitor hotplug, sleep/resume, DPI
// change, Explorer hiccups) without notifying the mod, which is why the
// transparency effect can "randomly" stop applying. This watchdog keeps
// re-asserting it periodically. The calls below are cheap/idempotent when
// nothing actually changed, so this should not cause visible flicker.
// ------------------------------------------

std::atomic<bool> g_transparencyWatchdogRunning;
HANDLE g_transparencyWatchdogThread;

DWORD WINAPI TransparencyWatchdogThreadProc(LPVOID) {
    // Polls every 250 ms. With dynamic transparency the taskbar is updated as
    // soon as a window is maximized or restored; otherwise it is re-asserted
    // every 1.5 seconds as before.
    int sinceApplyMs = 0;
    uintptr_t lastSignature = 0;
    // Let Explorer finish starting before doing any periodic work.
    for (int i = 0; i < 100 && g_transparencyWatchdogRunning; i++) {
        Sleep(100);
    }
    while (g_transparencyWatchdogRunning) {
        for (int i = 0; i < 5 && g_transparencyWatchdogRunning; i++) {
            Sleep(50);
        }
        if (!g_transparencyWatchdogRunning) break;
        sinceApplyMs += 250;

        uintptr_t signature = g_settings.dynamicTransparency ? MaximizedMonitorsSignature() : 0;
        if (signature == lastSignature && sinceApplyMs < 3000) continue;
        lastSignature = signature;
        sinceApplyMs = 0;

        std::wstring mode = g_settings.transparencyMode
                                ? std::wstring(g_settings.transparencyMode.get())
                                : L"default";
        if (mode.empty() || IsTransparencyMode(mode, L"default")) {
            continue;
        }

        HWND hTaskbarWnd = FindCurrentProcessTaskbarWnd();
        if (hTaskbarWnd) {
            ApplySettingsTray(hTaskbarWnd);
        }
        ApplyTaskbarTransparency();
    }
    return 0;
}

void StartTransparencyWatchdog() {
    if (g_transparencyWatchdogRunning.exchange(true)) return;
    g_transparencyWatchdogThread =
        CreateThread(nullptr, 0, TransparencyWatchdogThreadProc, nullptr, 0, nullptr);
}

void StopTransparencyWatchdog() {
    if (!g_transparencyWatchdogRunning.exchange(false)) return;
    if (g_transparencyWatchdogThread) {
        WaitForSingleObject(g_transparencyWatchdogThread, 5000);
        CloseHandle(g_transparencyWatchdogThread);
        g_transparencyWatchdogThread = nullptr;
    }
}

bool TextMatchesException(std::wstring_view value,
                          const std::vector<std::wstring>& exceptions) {
    if (value.empty()) return false;

    for (const auto& exception : exceptions) {
        if (exception.empty()) continue;

        size_t first = exception.find_first_not_of(L" \t\r\n");
        size_t last = exception.find_last_not_of(L" \t\r\n");
        if (first == std::wstring::npos) continue;

        std::wstring needle = exception.substr(first, last - first + 1);
        if (needle.empty()) continue;

        std::wstring lowerValue(value);
        std::wstring lowerNeedle(needle);
        std::transform(lowerValue.begin(), lowerValue.end(), lowerValue.begin(),
                       towlower);
        std::transform(lowerNeedle.begin(), lowerNeedle.end(), lowerNeedle.begin(),
                       towlower);

        if (lowerValue.find(lowerNeedle) != std::wstring::npos) {
            return true;
        }
    }

    return false;
}

bool TaskbarButtonIsException(FrameworkElement button) {
    if (!button) return false;

    std::wstring automationId =
        Automation::AutomationProperties::GetAutomationId(button).c_str();
    std::wstring automationName =
        Automation::AutomationProperties::GetName(button).c_str();

    if (TextMatchesException(automationId, g_settings.appExceptions) ||
        TextMatchesException(automationName, g_settings.appExceptions)) {
        return true;
    }

    bool found = false;
    EnumChildElements(button, [&](FrameworkElement child) {
        std::wstring id =
            Automation::AutomationProperties::GetAutomationId(child).c_str();
        std::wstring name =
            Automation::AutomationProperties::GetName(child).c_str();

        if (TextMatchesException(id, g_settings.appExceptions) ||
            TextMatchesException(name, g_settings.appExceptions)) {
            found = true;
            return true;
        }
        return false;
    });

    return found;
}

void ApplyTaskbarAppVisibilityToButton(FrameworkElement button) {
    if (!button) return;

    bool hide = g_settings.hideTaskbarApps && !g_unloading;
    if (!hide) {
        button.ClearValue(UIElement::VisibilityProperty());
        button.ClearValue(FrameworkElement::MaxWidthProperty());
        return;
    }

    bool exception = TaskbarButtonIsException(button);

    if (exception) {
        button.ClearValue(UIElement::VisibilityProperty());
        button.ClearValue(FrameworkElement::MaxWidthProperty());
    } else {
        button.Visibility(Visibility::Collapsed);
        button.MaxWidth(0);
    }
}

template <typename F>
void WalkVisualTree(FrameworkElement root, F callback) {
    if (!root) return;

    int childrenCount = Media::VisualTreeHelper::GetChildrenCount(root);
    for (int i = 0; i < childrenCount; ++i) {
        auto child =
            Media::VisualTreeHelper::GetChild(root, i).try_as<FrameworkElement>();
        if (!child) continue;

        callback(child);
        WalkVisualTree(child, callback);
    }
}

void ApplyTaskbarAppVisibility(XamlRoot xamlRoot) {
    if (!xamlRoot) return;

    FrameworkElement root = xamlRoot.Content().try_as<FrameworkElement>();
    if (!root) return;

    WalkVisualTree(root, [](FrameworkElement element) {
        std::wstring className = winrt::get_class_name(element).c_str();

        // Exact match: app buttons only. Start, Search, Task View and Widgets
        // contain a Taskbar.TaskListButtonPanel child, so a substring match
        // would hide their content too.
        if (className == L"Taskbar.TaskListButton") {
            ApplyTaskbarAppVisibilityToButton(element);
        }
    });
}

// ----- TASKBAR ICON SIZE HELPERS -----

struct {
    int taskbarHeight;
    int iconSize;
    int taskbarButtonWidth;
    int iconSizeSmall;
    int taskbarButtonWidthSmall;
} g_iconSizeSettings;

std::atomic<bool> g_iconSizeSystemTrayModuleHooked;
std::atomic<bool> g_taskbarViewDllLoaded;
std::atomic<bool> g_searchUxUiDllLoaded;
std::atomic<bool> g_applyingSettings;
std::atomic<bool> g_pendingMeasureOverride;
std::atomic<int> g_hookCallCounter;

bool g_hasDynamicIconScaling;
std::atomic<bool> g_smallIconSize;
int g_originalTaskbarHeight;
int g_taskbarHeight;
std::atomic<DWORD> g_shellIconLoaderV2_LoadAsyncIcon__ResumeCoro_ThreadId;
bool g_inSystemTrayController_UpdateFrameSize;
bool g_taskbarButtonWidthCustomized;

double* double_48_value_Original;

typedef enum MONITOR_DPI_TYPE {
    MDT_EFFECTIVE_DPI = 0,
    MDT_ANGULAR_DPI = 1,
    MDT_RAW_DPI = 2,
    MDT_DEFAULT = MDT_EFFECTIVE_DPI
} MONITOR_DPI_TYPE;
STDAPI GetDpiForMonitor(HMONITOR hmonitor,
                        MONITOR_DPI_TYPE dpiType,
                        UINT* dpiX,
                        UINT* dpiY);

size_t OffsetFromAssemblyRegex(void* func,
                               size_t defValue,
                               std::regex regex,
                               int limit = 30) {
    BYTE* p = (BYTE*)func;
    for (int i = 0; i < limit; i++) {
        WH_DISASM_RESULT result;
        if (!Wh_Disasm(p, &result)) {
            break;
        }

        p += result.length;

        std::string_view s = result.text;
        if (s == "ret") {
            break;
        }

        std::match_results<std::string_view::const_iterator> match;
        if (std::regex_match(s.begin(), s.end(), match, regex)) {
            return std::stoull(match[1], nullptr, 16);
        }
    }

    Wh_Log(L"Failed for %p", func);
    return defValue;
}

bool IsVerticalTaskbar() {
    APPBARDATA appBarData = {
        .cbSize = sizeof(APPBARDATA),
    };
    if (!SHAppBarMessage(ABM_GETTASKBARPOS, &appBarData)) {
        Wh_Log(L"SHAppBarMessage(ABM_GETTASKBARPOS) failed");
        return false;
    }

    return appBarData.uEdge == ABE_LEFT || appBarData.uEdge == ABE_RIGHT;
}

void OverrideResourceDirectoryLookup(
    PCSTR sourceFunctionName,
    const winrt::Windows::Foundation::IInspectable* key,
    winrt::Windows::Foundation::IInspectable* value) {
    if (g_unloading) {
        return;
    }

    const auto keyString = key->try_as<winrt::hstring>();
    if (!keyString) {
        return;
    }

    double newValueDouble;
    if (*keyString == L"MediumTaskbarButtonExtent") {
        newValueDouble = g_iconSizeSettings.taskbarButtonWidth;
    } else if (*keyString == L"SmallTaskbarButtonExtent") {
        newValueDouble = g_iconSizeSettings.taskbarButtonWidthSmall;
    } else {
        return;
    }

    const auto valueDouble = value->try_as<double>();
    if (!valueDouble) {
        return;
    }

    if (newValueDouble != *valueDouble) {
        Wh_Log(L"[%S] Overriding value %s: %f->%f", sourceFunctionName,
               keyString->c_str(), *valueDouble, newValueDouble);
        *value = winrt::box_value(newValueDouble);
    }
}

using ResourceDictionary_Lookup_TaskbarView_t =
    winrt::Windows::Foundation::IInspectable*(
        WINAPI*)(void* pThis,
                 void** result,
                 winrt::Windows::Foundation::IInspectable* key);
ResourceDictionary_Lookup_TaskbarView_t
    ResourceDictionary_Lookup_TaskbarView_Original;
winrt::Windows::Foundation::IInspectable* WINAPI
ResourceDictionary_Lookup_TaskbarView_Hook(
    void* pThis,
    void** result,
    winrt::Windows::Foundation::IInspectable* key) {

    auto ret =
        ResourceDictionary_Lookup_TaskbarView_Original(pThis, result, key);
    if (!*ret) {
        return ret;
    }

    OverrideResourceDirectoryLookup(__FUNCTION__, key, ret);

    return ret;
}

using ResourceDictionary_Lookup_SearchUxUi_t =
    winrt::Windows::Foundation::IInspectable*(
        WINAPI*)(void* pThis,
                 void** result,
                 winrt::Windows::Foundation::IInspectable* key);
ResourceDictionary_Lookup_SearchUxUi_t
    ResourceDictionary_Lookup_SearchUxUi_Original;
winrt::Windows::Foundation::IInspectable* WINAPI
ResourceDictionary_Lookup_SearchUxUi_Hook(
    void* pThis,
    void** result,
    winrt::Windows::Foundation::IInspectable* key) {

    auto ret =
        ResourceDictionary_Lookup_SearchUxUi_Original(pThis, result, key);
    if (!*ret) {
        return ret;
    }

    OverrideResourceDirectoryLookup(__FUNCTION__, key, ret);

    return ret;
}

using IconUtils_GetIconSize_t = void(WINAPI*)(bool isSmall,
                                              int type,
                                              SIZE* size);
IconUtils_GetIconSize_t IconUtils_GetIconSize_Original;
void WINAPI IconUtils_GetIconSize_Hook(bool isSmall, int type, SIZE* size) {
    if (g_hasDynamicIconScaling) {
        IconUtils_GetIconSize_Original(isSmall, type, size);
        return;
    }

    IconUtils_GetIconSize_Original(isSmall, type, size);

    if (!g_unloading && !isSmall) {
        size->cx = MulDiv(size->cx, g_iconSizeSettings.iconSize, 24);
        size->cy = MulDiv(size->cy, g_iconSizeSettings.iconSize, 24);
    }
}

using IconContainer_IsStorageRecreationRequired_t = bool(WINAPI*)(void* pThis,
                                                                  void* param1,
                                                                  int flags);
IconContainer_IsStorageRecreationRequired_t
    IconContainer_IsStorageRecreationRequired_Original;
bool WINAPI IconContainer_IsStorageRecreationRequired_Hook(void* pThis,
                                                           void* param1,
                                                           int flags) {
    if (g_hasDynamicIconScaling) {
        return IconContainer_IsStorageRecreationRequired_Original(pThis, param1,
                                                                  flags);
    }

    if (g_applyingSettings) {
        return true;
    }

    return IconContainer_IsStorageRecreationRequired_Original(pThis, param1,
                                                              flags);
}

using TrayUI_GetMinSize_t = void(WINAPI*)(void* pThis,
                                          HMONITOR monitor,
                                          SIZE* size);
TrayUI_GetMinSize_t TrayUI_GetMinSize_Original;
void WINAPI TrayUI_GetMinSize_Hook(void* pThis, HMONITOR monitor, SIZE* size) {
    TrayUI_GetMinSize_Original(pThis, monitor, size);

    if (!IsVerticalTaskbar() && g_taskbarHeight) {
        UINT dpiX = 0;
        UINT dpiY = 0;
        GetDpiForMonitor(monitor, MDT_DEFAULT, &dpiX, &dpiY);

        size->cy = MulDiv(g_taskbarHeight, dpiY, 96);
    }
}

using CIconLoadingFunctions_GetClassLongPtrW_t = ULONG_PTR(WINAPI*)(void* pThis,
                                                                    HWND hWnd,
                                                                    int nIndex);
CIconLoadingFunctions_GetClassLongPtrW_t
    CIconLoadingFunctions_GetClassLongPtrW_Original;
ULONG_PTR WINAPI CIconLoadingFunctions_GetClassLongPtrW_Hook(void* pThis,
                                                             HWND hWnd,
                                                             int nIndex) {
    if (g_hasDynamicIconScaling) {
        return CIconLoadingFunctions_GetClassLongPtrW_Original(pThis, hWnd,
                                                               nIndex);
    }

    if (!g_unloading && nIndex == GCLP_HICON && g_iconSizeSettings.iconSize <= 16) {
        nIndex = GCLP_HICONSM;
    }

    ULONG_PTR ret =
        CIconLoadingFunctions_GetClassLongPtrW_Original(pThis, hWnd, nIndex);

    return ret;
}

using CIconLoadingFunctions_SendMessageCallbackW_t =
    BOOL(WINAPI*)(void* pThis,
                  HWND hWnd,
                  UINT Msg,
                  WPARAM wParam,
                  LPARAM lParam,
                  SENDASYNCPROC lpResultCallBack,
                  ULONG_PTR dwData);
CIconLoadingFunctions_SendMessageCallbackW_t
    CIconLoadingFunctions_SendMessageCallbackW_Original;
BOOL WINAPI
CIconLoadingFunctions_SendMessageCallbackW_Hook(void* pThis,
                                                HWND hWnd,
                                                UINT Msg,
                                                WPARAM wParam,
                                                LPARAM lParam,
                                                SENDASYNCPROC lpResultCallBack,
                                                ULONG_PTR dwData) {
    if (g_hasDynamicIconScaling) {
        return CIconLoadingFunctions_SendMessageCallbackW_Original(
            pThis, hWnd, Msg, wParam, lParam, lpResultCallBack, dwData);
    }

    if (!g_unloading && Msg == WM_GETICON && wParam == ICON_BIG &&
        g_iconSizeSettings.iconSize <= 16) {
        wParam = ICON_SMALL2;
    }

    BOOL ret = CIconLoadingFunctions_SendMessageCallbackW_Original(
        pThis, hWnd, Msg, wParam, lParam, lpResultCallBack, dwData);

    return ret;
}

using ShellIconLoaderV2_LoadAsyncIcon__ResumeCoro_t =
    void(WINAPI*)(void* pThis);
ShellIconLoaderV2_LoadAsyncIcon__ResumeCoro_t
    ShellIconLoaderV2_LoadAsyncIcon__ResumeCoro_Original;
void WINAPI ShellIconLoaderV2_LoadAsyncIcon__ResumeCoro_Hook(void* pThis) {
    if (g_hasDynamicIconScaling) {
        ShellIconLoaderV2_LoadAsyncIcon__ResumeCoro_Original(pThis);
        return;
    }

    g_shellIconLoaderV2_LoadAsyncIcon__ResumeCoro_ThreadId =
        GetCurrentThreadId();

    ShellIconLoaderV2_LoadAsyncIcon__ResumeCoro_Original(pThis);

    g_shellIconLoaderV2_LoadAsyncIcon__ResumeCoro_ThreadId = 0;
}

using TrayUI__StuckTrayChange_t = void(WINAPI*)(void* pThis);
TrayUI__StuckTrayChange_t TrayUI__StuckTrayChange_Original;

using TrayUI__HandleSettingChange_t = void(WINAPI*)(void* pThis,
                                                    void* param1,
                                                    void* param2,
                                                    void* param3,
                                                    void* param4);
TrayUI__HandleSettingChange_t TrayUI__HandleSettingChange_Original;
void WINAPI TrayUI__HandleSettingChange_Hook(void* pThis,
                                             void* param1,
                                             void* param2,
                                             void* param3,
                                             void* param4) {
    TrayUI__HandleSettingChange_Original(pThis, param1, param2, param3, param4);

    if (g_applyingSettings) {
        TrayUI__StuckTrayChange_Original(pThis);
    }
}

using TaskListItemViewModel_GetIconHeight_t = int(WINAPI*)(void* pThis,
                                                           void* param1,
                                                           double* iconHeight);
TaskListItemViewModel_GetIconHeight_t
    TaskListItemViewModel_GetIconHeight_Original;
int WINAPI TaskListItemViewModel_GetIconHeight_Hook(void* pThis,
                                                    void* param1,
                                                    double* iconHeight) {
    if (g_hasDynamicIconScaling) {
        return TaskListItemViewModel_GetIconHeight_Original(pThis, param1,
                                                            iconHeight);
    }

    int ret =
        TaskListItemViewModel_GetIconHeight_Original(pThis, param1, iconHeight);

    if (!g_unloading) {
        *iconHeight = g_iconSizeSettings.iconSize;
    }

    return ret;
}

using TaskListGroupViewModel_GetIconHeight_t = int(WINAPI*)(void* pThis,
                                                            void* param1,
                                                            double* iconHeight);
TaskListGroupViewModel_GetIconHeight_t
    TaskListGroupViewModel_GetIconHeight_Original;
int WINAPI TaskListGroupViewModel_GetIconHeight_Hook(void* pThis,
                                                     void* param1,
                                                     double* iconHeight) {
    if (g_hasDynamicIconScaling) {
        return TaskListGroupViewModel_GetIconHeight_Original(pThis, param1,
                                                             iconHeight);
    }

    int ret = TaskListGroupViewModel_GetIconHeight_Original(pThis, param1,
                                                            iconHeight);

    if (!g_unloading) {
        *iconHeight = g_iconSizeSettings.iconSize;
    }

    return ret;
}

using TaskbarConfiguration_GetIconHeightInViewPixels_taskbarSizeEnum_t =
    double(WINAPI*)(int enumTaskbarSize);
TaskbarConfiguration_GetIconHeightInViewPixels_taskbarSizeEnum_t
    TaskbarConfiguration_GetIconHeightInViewPixels_taskbarSizeEnum_Original;
double WINAPI
TaskbarConfiguration_GetIconHeightInViewPixels_taskbarSizeEnum_Hook(
    int enumTaskbarSize) {
    if (g_hasDynamicIconScaling) {
        g_hasDynamicIconScaling = false;
    }

    if (!g_unloading && (enumTaskbarSize == 1 || enumTaskbarSize == 2)) {
        return g_iconSizeSettings.iconSize;
    }

    return TaskbarConfiguration_GetIconHeightInViewPixels_taskbarSizeEnum_Original(
        enumTaskbarSize);
}

using TaskbarConfiguration_GetIconHeightInViewPixels_double_t =
    double(WINAPI*)(double baseHeight);
TaskbarConfiguration_GetIconHeightInViewPixels_double_t
    TaskbarConfiguration_GetIconHeightInViewPixels_double_Original;
double WINAPI
TaskbarConfiguration_GetIconHeightInViewPixels_double_Hook(double baseHeight) {
    if (g_hasDynamicIconScaling) {
        g_hasDynamicIconScaling = false;
    }

    if (!g_unloading) {
        return g_iconSizeSettings.iconSize;
    }

    return TaskbarConfiguration_GetIconHeightInViewPixels_double_Original(
        baseHeight);
}

thread_local bool g_inTaskbarFrame_GetMetrics;
thread_local std::optional<double> g_TaskbarFrame_GetMetrics_iconHeight;

using TaskbarConfiguration_GetIconHeightInViewPixels_method_t =
    double(WINAPI*)(void* pThis);
TaskbarConfiguration_GetIconHeightInViewPixels_method_t
    TaskbarConfiguration_GetIconHeightInViewPixels_method_Original;
double WINAPI
TaskbarConfiguration_GetIconHeightInViewPixels_method_Hook(void* pThis) {
    double iconSize =
        TaskbarConfiguration_GetIconHeightInViewPixels_method_Original(pThis);

    g_smallIconSize = iconSize <= 16;

    if (g_inTaskbarFrame_GetMetrics) {
        g_TaskbarFrame_GetMetrics_iconHeight = iconSize;
        return iconSize;
    }

    if (!g_unloading) {
        return iconSize <= 16 ? g_iconSizeSettings.iconSizeSmall : g_iconSizeSettings.iconSize;
    }

    return iconSize;
}

using TaskListButton_IconHeight_t = void(WINAPI*)(void* pThis, double height);
TaskListButton_IconHeight_t TaskListButton_IconHeight_Original;

size_t GetIconHeightOffset() {
    static size_t iconHeightOffset = []() -> size_t {
        if (!TaskListButton_IconHeight_Original) {
            Wh_Log(L"Error: TaskListButton_IconHeight_Original is null");
            return 0;
        }

        size_t offset =
#if defined(_M_X64)
            OffsetFromAssemblyRegex(
                (void*)TaskListButton_IconHeight_Original, 0,
                std::regex(R"(movsd xmm\d+, qword ptr \[rcx\+0x([0-9a-f]+)\])",
                           std::regex_constants::icase),
                30);
#elif defined(_M_ARM64)
            OffsetFromAssemblyRegex(
                (void*)TaskListButton_IconHeight_Original, 0,
                std::regex(R"(ldr\s+d\d+, \[x\d+, #0x([0-9a-f]+)\])",
                           std::regex_constants::icase),
                30);
#else
#error "Unsupported architecture"
#endif
        Wh_Log(L"iconHeightOffset=0x%X", offset);
        return offset > 0xFFFF ? 0 : offset;
    }();

    return iconHeightOffset;
}

void TaskListButton_IconHeight_InitOffsets() {
    GetIconHeightOffset();
}

bool IsRuntimeClass(void* pThis, std::wstring_view className) {
    void* abi = pThis ? *(void**)pThis : nullptr;
    if (!abi) {
        return false;
    }

    static std::mutex mutex;
    static std::unordered_map<void*, winrt::hstring> cache;

    std::lock_guard<std::mutex> guard(mutex);

    auto [it, inserted] = cache.try_emplace(*(void**)abi);
    if (inserted) {
        try {
            it->second = winrt::get_class_name(
                *reinterpret_cast<winrt::Windows::Foundation::IInspectable*>(
                    pThis));
        } catch (const winrt::hresult_error& ex) {
            Wh_Log(L"Error %08X: %s", ex.code().value, ex.message().c_str());
        }
    }

    return it->second == className;
}

int OverrideTaskbarSettingsSize(PCSTR sourceFunctionName,
                                void* pThis,
                                int enumTaskbarSize) {
    if (g_unloading || enumTaskbarSize != 0 ||
        !IsRuntimeClass(pThis, L"WindowsUdk.UI.Shell.TaskbarSettings")) {
        return enumTaskbarSize;
    }

    Wh_Log(L"[%S] Overriding the small taskbar size", sourceFunctionName);
    return 1;
}

using TaskbarSettings_Size_t = int(WINAPI*)(void* pThis);

TaskbarSettings_Size_t TaskbarSettings_Size_TaskbarDll_Original;
int WINAPI TaskbarSettings_Size_TaskbarDll_Hook(void* pThis) {
    return OverrideTaskbarSettingsSize(
        __FUNCTION__, pThis, TaskbarSettings_Size_TaskbarDll_Original(pThis));
}

TaskbarSettings_Size_t TaskbarSettings_Size_SystemTray_Original;
int WINAPI TaskbarSettings_Size_SystemTray_Hook(void* pThis) {
    return OverrideTaskbarSettingsSize(
        __FUNCTION__, pThis, TaskbarSettings_Size_SystemTray_Original(pThis));
}

TaskbarSettings_Size_t TaskbarSettings_Size_TaskbarView_Original;
int WINAPI TaskbarSettings_Size_TaskbarView_Hook(void* pThis) {
    return OverrideTaskbarSettingsSize(
        __FUNCTION__, pThis, TaskbarSettings_Size_TaskbarView_Original(pThis));
}

using SystemTrayController_GetFrameSize_t =
    double(WINAPI*)(void* pThis, int enumTaskbarSize);
SystemTrayController_GetFrameSize_t SystemTrayController_GetFrameSize_Original;
double WINAPI SystemTrayController_GetFrameSize_Hook(void* pThis,
                                                     int enumTaskbarSize) {
    if (!IsVerticalTaskbar() && g_taskbarHeight &&
        (enumTaskbarSize == 1 || enumTaskbarSize == 2)) {
        return g_taskbarHeight;
    }

    return SystemTrayController_GetFrameSize_Original(pThis, enumTaskbarSize);
}

using SystemTraySecondaryController_GetFrameSize_t =
    double(WINAPI*)(void* pThis, int enumTaskbarSize);
SystemTraySecondaryController_GetFrameSize_t
    SystemTraySecondaryController_GetFrameSize_Original;
double WINAPI
SystemTraySecondaryController_GetFrameSize_Hook(void* pThis,
                                                int enumTaskbarSize) {
    if (!IsVerticalTaskbar() && g_taskbarHeight &&
        (enumTaskbarSize == 1 || enumTaskbarSize == 2)) {
        return g_taskbarHeight;
    }

    return SystemTraySecondaryController_GetFrameSize_Original(pThis,
                                                               enumTaskbarSize);
}

using TaskbarConfiguration_GetFrameSize_t =
    double(WINAPI*)(int enumTaskbarSize);
TaskbarConfiguration_GetFrameSize_t TaskbarConfiguration_GetFrameSize_Original;
double WINAPI TaskbarConfiguration_GetFrameSize_Hook(int enumTaskbarSize) {
    if (!g_originalTaskbarHeight &&
        (enumTaskbarSize == 1 || enumTaskbarSize == 2)) {
        g_originalTaskbarHeight =
            TaskbarConfiguration_GetFrameSize_Original(enumTaskbarSize);
    }

    if (!IsVerticalTaskbar() && g_taskbarHeight &&
        (enumTaskbarSize == 1 || enumTaskbarSize == 2)) {
        return g_taskbarHeight;
    }

    return TaskbarConfiguration_GetFrameSize_Original(enumTaskbarSize);
}

#ifdef _M_ARM64
thread_local double* g_TaskbarConfiguration_UpdateFrameSize_frameSize;

using TaskbarConfiguration_UpdateFrameSize_t = void(WINAPI*)(void* pThis);
TaskbarConfiguration_UpdateFrameSize_t
    TaskbarConfiguration_UpdateFrameSize_SymbolAddress;

LONG GetFrameSizeOffset() {
    static LONG frameSizeOffset = []() -> LONG {
        if (!TaskbarConfiguration_UpdateFrameSize_SymbolAddress) {
            return 0;
        }

        const DWORD* start =
            (const DWORD*)TaskbarConfiguration_UpdateFrameSize_SymbolAddress;
        const DWORD* end = start + 0x80;
        std::regex regex1(R"(str\s+d\d+, \[x\d+, #0x([0-9a-f]+)\])");
        for (const DWORD* p = start; p != end; p++) {
            WH_DISASM_RESULT result1;
            if (!Wh_Disasm((void*)p, &result1)) {
                break;
            }

            std::string_view s1 = result1.text;
            if (s1 == "ret") {
                break;
            }

            std::match_results<std::string_view::const_iterator> match1;
            if (!std::regex_match(s1.begin(), s1.end(), match1, regex1)) {
                continue;
            }

            LONG offset = std::stoull(match1[1], nullptr, 16);
            return (offset < 0 || offset > 0xFFFF) ? 0 : offset;
        }

        return 0;
    }();

    return frameSizeOffset;
}

void TaskbarConfiguration_UpdateFrameSize_InitOffsets() {
    GetFrameSizeOffset();
}

TaskbarConfiguration_UpdateFrameSize_t
    TaskbarConfiguration_UpdateFrameSize_Original;
void WINAPI TaskbarConfiguration_UpdateFrameSize_Hook(void* pThis) {
    LONG frameSizeOffset = GetFrameSizeOffset();
    if (!frameSizeOffset) {
        TaskbarConfiguration_UpdateFrameSize_Original(pThis);
        return;
    }

    g_TaskbarConfiguration_UpdateFrameSize_frameSize =
        (double*)((BYTE*)pThis + frameSizeOffset);

    TaskbarConfiguration_UpdateFrameSize_Original(pThis);

    g_TaskbarConfiguration_UpdateFrameSize_frameSize = nullptr;
}

using Event_operator_call_t = void(WINAPI*)(void* pThis);
Event_operator_call_t Event_operator_call_Original;
void WINAPI Event_operator_call_Hook(void* pThis) {
    if (g_TaskbarConfiguration_UpdateFrameSize_frameSize) {
        if (!g_originalTaskbarHeight) {
            g_originalTaskbarHeight =
                *g_TaskbarConfiguration_UpdateFrameSize_frameSize;
        }

        if (!IsVerticalTaskbar() && g_taskbarHeight) {
            *g_TaskbarConfiguration_UpdateFrameSize_frameSize = g_taskbarHeight;
        }
    }

    Event_operator_call_Original(pThis);
}
#endif  // _M_ARM64

using SystemTrayController_UpdateFrameSize_t = void(WINAPI*)(void* pThis);
SystemTrayController_UpdateFrameSize_t
    SystemTrayController_UpdateFrameSize_SymbolAddress;

LONG GetLastHeightOffset() {
    static LONG lastHeightOffset = []() -> LONG {
        if (!SystemTrayController_UpdateFrameSize_SymbolAddress) {
            return 0;
        }

#if defined(_M_X64)
        const BYTE* start =
            (const BYTE*)SystemTrayController_UpdateFrameSize_SymbolAddress;
        const BYTE* end = start + 0x400;
        for (const BYTE* p = start; p != end; p++) {
            if (p[0] == 0x66 && p[1] == 0x0F && p[2] == 0x2E &&
                (p[3] & 0xC0) == 0x80 && p[8] == 0x7A &&
                (p[10] == 0x74 || p[10] == 0x75 ||
                 (p[10] == 0x0F && (p[11] == 0x84 || p[11] == 0x85)))) {
                LONG offset = *(LONG*)(p + 4);
                return (offset < 0 || offset > 0xFFFF) ? 0 : offset;
            }
        }
#elif defined(_M_ARM64)
        const DWORD* start =
            (const DWORD*)SystemTrayController_UpdateFrameSize_SymbolAddress;
        const DWORD* end = start + 0x100;
        std::regex regex1(R"(ldr\s+d\d+, \[x\d+, #0x([0-9a-f]+)\])");
        std::regex regex2(R"(fcmp\s+d\d+, d\d+)");
        std::regex regex3(R"(b\.eq\s+0x[0-9a-f]+)");
        for (const DWORD* p = start; p != end; p++) {
            WH_DISASM_RESULT result1;
            if (!Wh_Disasm((void*)p, &result1)) break;
            std::string_view s1 = result1.text;
            if (s1 == "ret") break;
            std::match_results<std::string_view::const_iterator> match1;
            if (!std::regex_match(s1.begin(), s1.end(), match1, regex1)) continue;

            WH_DISASM_RESULT result2;
            if (!Wh_Disasm((void*)(p + 1), &result2)) break;
            std::string_view s2 = result2.text;
            if (!std::regex_match(s2.begin(), s2.end(), regex2)) continue;

            WH_DISASM_RESULT result3;
            if (!Wh_Disasm((void*)(p + 2), &result3)) break;
            std::string_view s3 = result3.text;
            if (!std::regex_match(s3.begin(), s3.end(), regex3)) continue;

            LONG offset = std::stoull(match1[1], nullptr, 16);
            return (offset < 0 || offset > 0xFFFF) ? 0 : offset;
        }
#else
#error "Unsupported architecture"
#endif
        return 0;
    }();

    return lastHeightOffset;
}

void SystemTrayController_UpdateFrameSize_InitOffsets() {
    GetLastHeightOffset();
}

SystemTrayController_UpdateFrameSize_t
    SystemTrayController_UpdateFrameSize_Original;
void WINAPI SystemTrayController_UpdateFrameSize_Hook(void* pThis) {
    if (IsVerticalTaskbar()) {
        SystemTrayController_UpdateFrameSize_Original(pThis);
        return;
    }

    LONG lastHeightOffset = GetLastHeightOffset();
    if (lastHeightOffset) {
        *(double*)((BYTE*)pThis + lastHeightOffset) = 0;
    }

    g_inSystemTrayController_UpdateFrameSize = true;
    SystemTrayController_UpdateFrameSize_Original(pThis);
    g_inSystemTrayController_UpdateFrameSize = false;
}

using TaskbarFrame_MaxHeight_double_t = void(WINAPI*)(void* pThis,
                                                      double value);
TaskbarFrame_MaxHeight_double_t TaskbarFrame_MaxHeight_double_Original;

using TaskbarFrame_Height_double_t = void(WINAPI*)(void* pThis, double value);
TaskbarFrame_Height_double_t TaskbarFrame_Height_double_Original;
void WINAPI TaskbarFrame_Height_double_Hook(void* pThis, double value) {
    if (IsVerticalTaskbar()) {
        TaskbarFrame_Height_double_Original(pThis, value);
        return;
    }

    if (TaskbarFrame_MaxHeight_double_Original) {
        TaskbarFrame_MaxHeight_double_Original(
            pThis, std::numeric_limits<double>::infinity());
    }

    return TaskbarFrame_Height_double_Original(pThis, value);
}

void* TaskbarController_OnGroupingModeChanged_Original;

LONG GetTaskbarFrameOffset() {
    static LONG taskbarFrameOffset = []() -> LONG {
        if (!TaskbarController_OnGroupingModeChanged_Original) {
            return 0;
        }

#if defined(_M_X64)
        const BYTE* p =
            (const BYTE*)TaskbarController_OnGroupingModeChanged_Original;
        if (p && p[0] == 0x48 && p[1] == 0x83 && p[2] == 0xEC &&
            (p[4] == 0x48 || p[4] == 0x4C) && p[5] == 0x8B &&
            (p[6] & 0xC0) == 0x80) {
            LONG offset = *(LONG*)(p + 7);
            return (offset < 0 || offset > 0xFFFF) ? 0 : offset;
        }
#elif defined(_M_ARM64)
        const DWORD* start =
            (const DWORD*)TaskbarController_OnGroupingModeChanged_Original;
        const DWORD* end = start + 10;
        std::regex regex1(R"(ldr\s+x\d+, \[x\d+, #0x([0-9a-f]+)\])");
        for (const DWORD* p = start; p != end; p++) {
            WH_DISASM_RESULT result1;
            if (!Wh_Disasm((void*)p, &result1)) break;
            std::string_view s1 = result1.text;
            if (s1 == "ret") break;
            std::match_results<std::string_view::const_iterator> match1;
            if (!std::regex_match(s1.begin(), s1.end(), match1, regex1)) continue;
            LONG offset = std::stoull(match1[1], nullptr, 16);
            return (offset < 0 || offset > 0xFFFF) ? 0 : offset;
        }
#else
#error "Unsupported architecture"
#endif
        return 0;
    }();

    return taskbarFrameOffset;
}

void TaskbarController_OnGroupingModeChanged_InitOffsets() {
    GetTaskbarFrameOffset();
}

using TaskbarController_UpdateFrameHeight_t = void(WINAPI*)(void* pThis);
TaskbarController_UpdateFrameHeight_t
    TaskbarController_UpdateFrameHeight_Original;
void WINAPI TaskbarController_UpdateFrameHeight_Hook(void* pThis) {
    if (IsVerticalTaskbar()) {
        TaskbarController_UpdateFrameHeight_Original(pThis);
        return;
    }

    LONG taskbarFrameOffset = GetTaskbarFrameOffset();
    if (!taskbarFrameOffset) {
        TaskbarController_UpdateFrameHeight_Original(pThis);
        return;
    }

    void* taskbarFrame = *(void**)((BYTE*)pThis + taskbarFrameOffset);
    if (!taskbarFrame) {
        TaskbarController_UpdateFrameHeight_Original(pThis);
        return;
    }

    FrameworkElement taskbarFrameElement = nullptr;
    ((IUnknown**)taskbarFrame)[1]->QueryInterface(
        winrt::guid_of<FrameworkElement>(),
        winrt::put_abi(taskbarFrameElement));
    if (!taskbarFrameElement) {
        TaskbarController_UpdateFrameHeight_Original(pThis);
        return;
    }

    taskbarFrameElement.MaxHeight(std::numeric_limits<double>::infinity());
    TaskbarController_UpdateFrameHeight_Original(pThis);

    auto contentGrid = Media::VisualTreeHelper::GetParent(taskbarFrameElement)
                           .try_as<FrameworkElement>();
    if (contentGrid) {
        double height = taskbarFrameElement.Height();
        double contentGridHeight = contentGrid.Height();
        if (contentGridHeight > 0 && contentGridHeight != height) {
            contentGrid.Height(height);
        }
    }
}

using SystemTraySecondaryController_UpdateFrameSize_t =
    void(WINAPI*)(void* pThis);
SystemTraySecondaryController_UpdateFrameSize_t
    SystemTraySecondaryController_UpdateFrameSize_Original;
void WINAPI SystemTraySecondaryController_UpdateFrameSize_Hook(void* pThis) {
    g_inSystemTrayController_UpdateFrameSize = true;
    SystemTraySecondaryController_UpdateFrameSize_Original(pThis);
    g_inSystemTrayController_UpdateFrameSize = false;
}

using SystemTrayFrame_Height_t = void(WINAPI*)(void* pThis, double value);
SystemTrayFrame_Height_t SystemTrayFrame_Height_Original;
void WINAPI SystemTrayFrame_Height_Hook(void* pThis, double value) {
    if (!IsVerticalTaskbar() && g_inSystemTrayController_UpdateFrameSize &&
        g_taskbarHeight) {
        value = g_taskbarHeight;
    }

    SystemTrayFrame_Height_Original(pThis, value);
}

thread_local winrt::Windows::Foundation::Size*
    g_systemTrayFrameMeasureOverrideSize;

using FrameworkElementOverrides_MeasureOverride_t =
    winrt::Windows::Foundation::Size*(
        WINAPI*)(void* pThis,
                 winrt::Windows::Foundation::Size* result,
                 winrt::Windows::Foundation::Size* availableSize);
FrameworkElementOverrides_MeasureOverride_t
    FrameworkElementOverrides_MeasureOverride_Original;
winrt::Windows::Foundation::Size* WINAPI
FrameworkElementOverrides_MeasureOverride_Hook(
    void* pThis,
    winrt::Windows::Foundation::Size* result,
    winrt::Windows::Foundation::Size* availableSize) {
    if (g_systemTrayFrameMeasureOverrideSize) {
        availableSize = g_systemTrayFrameMeasureOverrideSize;
        g_systemTrayFrameMeasureOverrideSize = nullptr;
    }

    return FrameworkElementOverrides_MeasureOverride_Original(pThis, result,
                                                              availableSize);
}

using SystemTrayFrame_MeasureOverride_t =
    int(WINAPI*)(void* pThis,
                 winrt::Windows::Foundation::Size size,
                 winrt::Windows::Foundation::Size* resultSize);
SystemTrayFrame_MeasureOverride_t SystemTrayFrame_MeasureOverride_Original;
int WINAPI SystemTrayFrame_MeasureOverride_Hook(
    void* pThis,
    winrt::Windows::Foundation::Size size,
    winrt::Windows::Foundation::Size* resultSize) {
    if (!g_originalTaskbarHeight ||
        !FrameworkElementOverrides_MeasureOverride_Original ||
        IsVerticalTaskbar()) {
        return SystemTrayFrame_MeasureOverride_Original(pThis, size,
                                                        resultSize);
    }

    winrt::Windows::Foundation::Size availableSize = size;
    size.Height = static_cast<float>(g_originalTaskbarHeight);
    g_systemTrayFrameMeasureOverrideSize = &availableSize;

    int ret = SystemTrayFrame_MeasureOverride_Original(pThis, size, resultSize);
    g_systemTrayFrameMeasureOverrideSize = nullptr;
    return ret;
}

using TaskbarFrame_MeasureOverride_t =
    int(WINAPI*)(void* pThis,
                 winrt::Windows::Foundation::Size size,
                 winrt::Windows::Foundation::Size* resultSize);
TaskbarFrame_MeasureOverride_t TaskbarFrame_MeasureOverride_Original;
int WINAPI TaskbarFrame_MeasureOverride_Hook(
    void* pThis,
    winrt::Windows::Foundation::Size size,
    winrt::Windows::Foundation::Size* resultSize) {
    g_hookCallCounter++;
    int ret = TaskbarFrame_MeasureOverride_Original(pThis, size, resultSize);
    g_pendingMeasureOverride = false;
    g_hookCallCounter--;
    return ret;
}

using TaskbarFrame_GetMetrics_t = void*(WINAPI*)(void* pThis, void* metrics);
TaskbarFrame_GetMetrics_t TaskbarFrame_GetMetrics_Original;
void* WINAPI TaskbarFrame_GetMetrics_Hook(void* pThis, void* metrics) {
    g_inTaskbarFrame_GetMetrics = true;
    g_TaskbarFrame_GetMetrics_iconHeight.reset();

    void* ret = TaskbarFrame_GetMetrics_Original(pThis, metrics);

    g_inTaskbarFrame_GetMetrics = false;
    std::optional<double> iconHeight = g_TaskbarFrame_GetMetrics_iconHeight;

    if (!iconHeight || *iconHeight == 32) {
        return ret;
    }

    double newValue;
    if (*iconHeight == 16) {
        newValue = g_unloading ? 32 : g_iconSizeSettings.taskbarButtonWidthSmall;
    } else {
        newValue = g_unloading ? 44 : g_iconSizeSettings.taskbarButtonWidth;
    }

    double* buttonExtent = (double*)((BYTE*)metrics + sizeof(double));
    if (*buttonExtent >= 1 && *buttonExtent < 10000 &&
        *buttonExtent != newValue) {
        *buttonExtent = newValue;
    }

    return ret;
}

using TaskListButton_UpdateButtonPadding_t = void(WINAPI*)(void* pThis);
TaskListButton_UpdateButtonPadding_t
    TaskListButton_UpdateButtonPadding_Original;
void WINAPI TaskListButton_UpdateButtonPadding_Hook(void* pThis) {
    if (!g_hasDynamicIconScaling || g_unloading) {
        TaskListButton_UpdateButtonPadding_Original(pThis);
        return;
    }

    double* iconHeight = nullptr;
    double prevIconHeight;
    if (size_t iconHeightOffset = GetIconHeightOffset()) {
        iconHeight = (double*)((BYTE*)pThis + iconHeightOffset);
        prevIconHeight = *iconHeight;
        double newIconHeight = g_smallIconSize ? 16 : 24;
        *iconHeight = newIconHeight;
    }

    TaskListButton_UpdateButtonPadding_Original(pThis);

    if (iconHeight) {
        *iconHeight = prevIconHeight;
    }
}

using TaskListButton_OverlayIcon_t = void(WINAPI*)(void* pThis, void* param1);
TaskListButton_OverlayIcon_t TaskListButton_OverlayIcon_Original;
void WINAPI TaskListButton_OverlayIcon_Hook(void* pThis, void* param1) {
    if (!g_hasDynamicIconScaling || g_unloading) {
        TaskListButton_OverlayIcon_Original(pThis, param1);
        return;
    }

    double* iconHeight = nullptr;
    double prevIconHeight;
    if (size_t iconHeightOffset = GetIconHeightOffset()) {
        iconHeight = (double*)((BYTE*)pThis + iconHeightOffset);
        prevIconHeight = *iconHeight;
        double newIconHeight = 24;
        *iconHeight = newIconHeight;
    }

    TaskListButton_OverlayIcon_Original(pThis, param1);

    if (iconHeight) {
        *iconHeight = prevIconHeight;
    }
}

using TaskListButton_UpdateBadge_t = void(WINAPI*)(void* pThis);
TaskListButton_UpdateBadge_t TaskListButton_UpdateBadge_Original;
void WINAPI TaskListButton_UpdateBadge_Hook(void* pThis) {
    if (!g_hasDynamicIconScaling || g_unloading) {
        TaskListButton_UpdateBadge_Original(pThis);
        return;
    }

    double* iconHeight = nullptr;
    double prevIconHeight;
    if (size_t iconHeightOffset = GetIconHeightOffset()) {
        iconHeight = (double*)((BYTE*)pThis + iconHeightOffset);
        prevIconHeight = *iconHeight;
        double newIconHeight = 24;
        *iconHeight = newIconHeight;
    }

    TaskListButton_UpdateBadge_Original(pThis);

    if (iconHeight) {
        *iconHeight = prevIconHeight;
    }
}

using TaskListButton_UpdateMultiWindowClip_t = void(WINAPI*)(void* pThis);
TaskListButton_UpdateMultiWindowClip_t
    TaskListButton_UpdateMultiWindowClip_Original;
void WINAPI TaskListButton_UpdateMultiWindowClip_Hook(void* pThis) {
    if (!g_hasDynamicIconScaling || g_unloading) {
        TaskListButton_UpdateMultiWindowClip_Original(pThis);
        return;
    }

    double* iconHeight = nullptr;
    double prevIconHeight;
    if (size_t iconHeightOffset = GetIconHeightOffset()) {
        iconHeight = (double*)((BYTE*)pThis + iconHeightOffset);
        prevIconHeight = *iconHeight;
        double newIconHeight = g_smallIconSize ? 16 : 24;
        *iconHeight = newIconHeight;
    }

    TaskListButton_UpdateMultiWindowClip_Original(pThis);

    if (iconHeight) {
        *iconHeight = prevIconHeight;
    }
}

using TaskListButton_CreateMultiWindowClip_t = void(WINAPI*)(void* pThis);
TaskListButton_CreateMultiWindowClip_t
    TaskListButton_CreateMultiWindowClip_Original;
void WINAPI TaskListButton_CreateMultiWindowClip_Hook(void* pThis) {
    if (!g_hasDynamicIconScaling || g_unloading) {
        TaskListButton_CreateMultiWindowClip_Original(pThis);
        return;
    }

    double* iconHeight = nullptr;
    double prevIconHeight;
    if (size_t iconHeightOffset = GetIconHeightOffset()) {
        iconHeight = (double*)((BYTE*)pThis + iconHeightOffset);
        prevIconHeight = *iconHeight;
        double newIconHeight = g_smallIconSize ? 16 : 24;
        *iconHeight = newIconHeight;
    }

    TaskListButton_CreateMultiWindowClip_Original(pThis);

    if (iconHeight) {
        *iconHeight = prevIconHeight;
    }
}

void* TaskListButton_UpdateIconColumnDefinition_Original;

LONG GetMediumTaskbarButtonExtentOffset() {
    static LONG mediumTaskbarButtonExtentOffset = []() -> LONG {
#if defined(_M_X64)
        const BYTE* start =
            (const BYTE*)TaskListButton_UpdateIconColumnDefinition_Original;
        const BYTE* end = start + 0x200;
        LONG offsetCandidate = 0;
        LONG offset = 0;
        for (const BYTE* p = start; p != end; p++) {
            if (p[0] == 0xF2 && p[1] == 0x0F && p[2] == 0x10 &&
                (p[3] & 0xC0) == 0x80) {
                offsetCandidate = *(LONG*)(p + 4);
            }

            if (p[0] == 0xF2 && p[1] == 0x44 && p[2] == 0x0F && p[3] == 0x10 &&
                (p[4] & 0xC0) == 0x80) {
                offsetCandidate = *(LONG*)(p + 5);
            }

            if (p[0] == 0xF2 && p[1] == 0x0F && p[2] == 0x5C &&
                (p[3] & 0xC0) == 0x80) {
                offset = offsetCandidate;
                break;
            }

            if (p[0] == 0xF2 && p[1] == 0x44 && p[2] == 0x0F && p[3] == 0x5C &&
                (p[4] & 0xC0) == 0x80) {
                offset = offsetCandidate;
                break;
            }
        }
        return (offset < 0 || offset > 0xFFFF) ? 0 : offset;
#elif defined(_M_ARM64)
        const DWORD* start =
            (const DWORD*)TaskListButton_UpdateIconColumnDefinition_Original;
        const DWORD* end = start + 0x80;
        std::regex regexLdr(R"(ldr\s+(d\d+), \[(x\d+), #0x([0-9a-f]+)\])");
        std::regex regexLdrOther(R"(ldr\s+(d\d+),.*)");
        std::regex regexFsub(R"(fsub\s+d\d+, (d\d+), (d\d+))");
        struct {
            std::string reg;
            std::string regSrc;
            LONG offset;
        } ldrs[32];
        size_t ldrCount = 0;
        for (const DWORD* p = start; p != end; p++) {
            WH_DISASM_RESULT result;
            if (!Wh_Disasm((void*)p, &result)) break;
            std::string_view s = result.text;
            if (s == "ret") break;

            if (ldrCount == ARRAYSIZE(ldrs)) break;

            std::match_results<std::string_view::const_iterator> matchLdr;
            if (std::regex_match(s.begin(), s.end(), matchLdr, regexLdr)) {
                std::string reg = matchLdr[1];
                std::string regSrc = matchLdr[2];
                LONG offset = std::stoull(matchLdr[3], nullptr, 16);
                ldrs[ldrCount++] = {std::move(reg), std::move(regSrc), offset};
                continue;
            }

            std::match_results<std::string_view::const_iterator> matchLdrOther;
            if (std::regex_match(s.begin(), s.end(), matchLdrOther, regexLdrOther)) {
                std::string reg = matchLdrOther[1];
                ldrs[ldrCount++] = {std::move(reg), std::string(), 0};
                continue;
            }

            std::match_results<std::string_view::const_iterator> matchFsub;
            if (std::regex_match(s.begin(), s.end(), matchFsub, regexFsub)) {
                std::string regA = matchFsub[1];
                std::string regB = matchFsub[2];

                std::remove_reference_t<decltype(ldrs[0])>* ldrA = nullptr;
                std::remove_reference_t<decltype(ldrs[0])>* ldrB = nullptr;

                for (size_t i = 0; i < ldrCount; i++) {
                    const auto& [ldrReg, ldrRegSrc, ldrOffset] = ldrs[ldrCount - 1 - i];
                    if (!ldrA && ldrReg == regA) ldrA = &ldrs[ldrCount - 1 - i];
                    if (!ldrB && ldrReg == regB) ldrB = &ldrs[ldrCount - 1 - i];
                }

                if (ldrA && ldrB && ldrA->regSrc == ldrB->regSrc) {
                    LONG offset = ldrA->offset;
                    return (offset < 0 || offset > 0xFFFF) ? 0 : offset;
                }
            }
        }
#else
#error "Unsupported architecture"
#endif
        return 0;
    }();

    return mediumTaskbarButtonExtentOffset;
}

void TaskListButton_UpdateIconColumnDefinition_InitOffsets() {
    GetMediumTaskbarButtonExtentOffset();
}

thread_local double g_taskListButtonPostureIconHeight;
thread_local double g_taskListButtonCustomIconHeight;

using TaskListButton_UpdateVisualStates_t = void(WINAPI*)(void* pThis);
TaskListButton_UpdateVisualStates_t TaskListButton_UpdateVisualStates_Original;
void WINAPI TaskListButton_UpdateVisualStates_Hook(void* pThis) {
    if (TaskListButton_UpdateIconColumnDefinition_Original &&
        (g_applyingSettings || g_taskbarButtonWidthCustomized)) {
        LONG mediumTaskbarButtonExtentOffset =
            GetMediumTaskbarButtonExtentOffset();
        if (mediumTaskbarButtonExtentOffset) {
            bool updateButtonPadding = false;

            double* mediumTaskbarButtonExtent =
                (double*)((BYTE*)pThis + mediumTaskbarButtonExtentOffset);
            if (*mediumTaskbarButtonExtent >= 1 &&
                *mediumTaskbarButtonExtent < 10000) {
                double newValue =
                    g_unloading ? 44 : g_iconSizeSettings.taskbarButtonWidth;
                if (newValue != *mediumTaskbarButtonExtent) {
                    *mediumTaskbarButtonExtent = newValue;
                    updateButtonPadding = true;
                }
            }

            double* smallTaskbarButtonExtent =
                g_hasDynamicIconScaling ? mediumTaskbarButtonExtent - 1
                                        : nullptr;
            if (smallTaskbarButtonExtent && *smallTaskbarButtonExtent >= 1 &&
                *smallTaskbarButtonExtent < 10000) {
                double newValue =
                    g_unloading ? 32 : g_iconSizeSettings.taskbarButtonWidthSmall;
                if (newValue != *smallTaskbarButtonExtent) {
                    *smallTaskbarButtonExtent = newValue;
                    updateButtonPadding = true;
                }
            }

            if (updateButtonPadding) {
                g_taskbarButtonWidthCustomized = true;
                TaskListButton_UpdateButtonPadding_Hook(pThis);
            }
        }
    }

    double* iconHeight = nullptr;
    double prevIconHeight;
    if (g_hasDynamicIconScaling && !g_unloading) {
        if (size_t iconHeightOffset = GetIconHeightOffset()) {
            iconHeight = (double*)((BYTE*)pThis + iconHeightOffset);
            prevIconHeight = *iconHeight;
            double newIconHeight = g_smallIconSize ? 16 : 24;
            *iconHeight = newIconHeight;
            g_taskListButtonPostureIconHeight = newIconHeight;
            g_taskListButtonCustomIconHeight = prevIconHeight;
        }
    }

    TaskListButton_UpdateVisualStates_Original(pThis);

    // APP HIDING LOGIC
    FrameworkElement taskListButtonElement = nullptr;
    ((IUnknown*)pThis + 3)->QueryInterface(
        winrt::guid_of<FrameworkElement>(),
        winrt::put_abi(taskListButtonElement));

    if (taskListButtonElement) {
        ApplyTaskbarAppVisibilityToButton(taskListButtonElement);
    }

    if (iconHeight) {
        g_taskListButtonPostureIconHeight = 0;
        *iconHeight = prevIconHeight;
    }

    if (g_applyingSettings && !g_hasDynamicIconScaling) {
        FrameworkElement taskListButtonElem = nullptr;
        ((IUnknown*)pThis + 3)
            ->QueryInterface(winrt::guid_of<FrameworkElement>(),
                             winrt::put_abi(taskListButtonElem));
        if (taskListButtonElem) {
            if (auto iconPanelElement =
                    FindChildByName(taskListButtonElem, L"IconPanel")) {
                if (auto iconElement =
                        FindChildByName(iconPanelElement, L"Icon")) {
                    double iconSize = g_unloading ? 24 : g_iconSizeSettings.iconSize;
                    iconElement.Width(iconSize);
                    iconElement.Height(iconSize);
                }
            }
        }
    }
}

using TaskbarComponentHost_IconHeight_t = void(WINAPI*)(void* pThis,
                                                        double height);
TaskbarComponentHost_IconHeight_t TaskbarComponentHost_IconHeight_Original;

size_t GetTaskbarComponentHostIconHeightOffset() {
    static size_t iconHeightOffset = []() -> size_t {
        if (!TaskbarComponentHost_IconHeight_Original) {
            return 0;
        }

        size_t offset =
#if defined(_M_X64)
            OffsetFromAssemblyRegex(
                (void*)TaskbarComponentHost_IconHeight_Original, 0,
                std::regex(R"(movsd xmm\d+, qword ptr \[rcx\+0x([0-9a-f]+)\])",
                           std::regex_constants::icase),
                30);
#elif defined(_M_ARM64)
            OffsetFromAssemblyRegex(
                (void*)TaskbarComponentHost_IconHeight_Original, 0,
                std::regex(R"(ldr\s+d\d+, \[x\d+, #0x([0-9a-f]+)\])",
                           std::regex_constants::icase),
                30);
#else
#error "Unsupported architecture"
#endif
        return offset > 0xFFFF ? 0 : offset;
    }();

    return iconHeightOffset;
}

void TaskbarComponentHost_IconHeight_InitOffsets() {
    GetTaskbarComponentHostIconHeightOffset();
}

using TaskbarComponentHost_UpdateDefaultWidth_t = void(WINAPI*)(void* pThis);
TaskbarComponentHost_UpdateDefaultWidth_t
    TaskbarComponentHost_UpdateDefaultWidth_Original;
void WINAPI TaskbarComponentHost_UpdateDefaultWidth_Hook(void* pThis) {
    double* iconHeight = nullptr;
    double prevIconHeight;
    if (g_hasDynamicIconScaling && !g_unloading) {
        if (size_t iconHeightOffset =
                GetTaskbarComponentHostIconHeightOffset()) {
            iconHeight = (double*)((BYTE*)pThis + iconHeightOffset);
            prevIconHeight = *iconHeight;
            double newIconHeight = g_smallIconSize ? 16 : 24;
            *iconHeight = newIconHeight;
        }
    }

    TaskbarComponentHost_UpdateDefaultWidth_Original(pThis);

    if (iconHeight) {
        *iconHeight = prevIconHeight;
    }
}

using ExperienceToggleButton_IconHeight_get_t = double(WINAPI*)(void* pThis);
ExperienceToggleButton_IconHeight_get_t
    ExperienceToggleButton_IconHeight_get_Original;

using ExperienceToggleButton_IconHeight_set_t = void(WINAPI*)(void* pThis,
                                                              double height);
ExperienceToggleButton_IconHeight_set_t
    ExperienceToggleButton_IconHeight_set_Original;

thread_local bool g_inExperienceToggleButton_IconHeight;

void SetExperienceToggleButtonIconHeight(void* pThis, double height) {
    g_inExperienceToggleButton_IconHeight = true;
    ExperienceToggleButton_IconHeight_set_Original(pThis, height);
    g_inExperienceToggleButton_IconHeight = false;
}

void UpdateAugmentedEntryPointContent(FrameworkElement panelElement) {
    FrameworkElement augmentedEntryPointContentGrid =
        FindChildByName(panelElement, L"AugmentedEntryPointContentGrid");
    if (!augmentedEntryPointContentGrid) {
        return;
    }

    double marginValue = static_cast<double>(40 - g_iconSizeSettings.iconSize) / 2;
    if (marginValue < 0) {
        marginValue = 0;
    }

    EnumChildElements(augmentedEntryPointContentGrid, [marginValue](
                                                          FrameworkElement
                                                              child) {
        if (winrt::get_class_name(child) != L"Windows.UI.Xaml.Controls.Grid") {
            return false;
        }

        FrameworkElement panelGrid =
            FindChildByClassName(child, L"Windows.UI.Xaml.Controls.Grid");
        if (!panelGrid) {
            return false;
        }

        FrameworkElement panel = FindChildByClassName(
            panelGrid, L"AdaptiveCards.Rendering.Uwp.WholeItemsPanel");
        if (!panel) {
            return false;
        }

        double labelsTopBorderExtraMargin = 0;

        bool widePanel = panelGrid.Width() > panelGrid.Height();
        if (widePanel) {
            auto margin = Thickness{3, 3, 3, 3};

            if (!g_unloading && marginValue <= 3) {
                labelsTopBorderExtraMargin = 3 - marginValue;
                margin.Left = marginValue;
                margin.Top = marginValue;
                margin.Right = 0;
                margin.Bottom = 0;
            }

            panel.Margin(margin);
            panelGrid.VerticalAlignment(g_unloading
                                            ? VerticalAlignment::Stretch
                                            : VerticalAlignment::Center);
        } else {
            auto margin = Thickness{8, 8, 8, 8};

            if (!g_unloading) {
                margin.Left = marginValue;
                margin.Top = marginValue;
                margin.Right = 0;
                margin.Bottom = 0;

                if (g_taskbarHeight < 48) {
                    margin.Top -= static_cast<double>(48 - g_taskbarHeight) / 2;
                    if (margin.Top < 0) {
                        margin.Top = 0;
                    }
                }
            }

            panel.Margin(margin);
        }

        FrameworkElement tickerGrid = panel;
        if ((tickerGrid = FindChildByClassName(
                 tickerGrid, L"Windows.UI.Xaml.Controls.Border")) &&
            (tickerGrid = FindChildByClassName(
                 tickerGrid, L"AdaptiveCards.Rendering.Uwp.WholeItemsPanel")) &&
            (tickerGrid = FindChildByClassName(
                 tickerGrid, L"Windows.UI.Xaml.Controls.Grid"))) {
        } else {
            return false;
        }

        double badgeMaxValue = g_unloading ? 24 : 40 - marginValue * 2;

        FrameworkElement badgeSmall = tickerGrid;
        if ((badgeSmall = FindChildByName(badgeSmall, L"SmallTicker1")) &&
            (badgeSmall = FindChildByClassName(
                 badgeSmall, L"AdaptiveCards.Rendering.Uwp.WholeItemsPanel")) &&
            (badgeSmall =
                 FindChildByName(badgeSmall, L"BadgeAnchorSmallTicker"))) {
            badgeSmall.MaxWidth(badgeMaxValue);
            badgeSmall.MaxHeight(badgeMaxValue);
        }

        FrameworkElement badgeLarge = tickerGrid;
        if ((badgeLarge = FindChildByName(badgeLarge, L"LargeTicker1")) &&
            (badgeLarge = FindChildByClassName(
                 badgeLarge, L"AdaptiveCards.Rendering.Uwp.WholeItemsPanel")) &&
            (badgeLarge =
                 FindChildByName(badgeLarge, L"BadgeAnchorLargeTicker"))) {
            badgeLarge.MaxWidth(badgeMaxValue);
            badgeLarge.MaxHeight(badgeMaxValue);
        }

        FrameworkElement labelsBorder = tickerGrid;
        if ((labelsBorder = FindChildByName(labelsBorder, L"LargeTicker2"))) {
            auto margin = Thickness{0, labelsTopBorderExtraMargin, 0, 0};
            labelsBorder.Margin(margin);
        }

        return false;
    });
}

using ExperienceToggleButton_UpdateButtonPadding_t = void(WINAPI*)(void* pThis);
ExperienceToggleButton_UpdateButtonPadding_t
    ExperienceToggleButton_UpdateButtonPadding_Original;
void WINAPI ExperienceToggleButton_UpdateButtonPadding_Hook(void* pThis) {
    if (g_inExperienceToggleButton_IconHeight) {
        return;
    }

    std::optional<double> prevIconHeight;
    if (g_hasDynamicIconScaling && !g_unloading &&
        ExperienceToggleButton_IconHeight_get_Original &&
        ExperienceToggleButton_IconHeight_set_Original) {
        double postureIconHeight = g_smallIconSize ? 16 : 24;
        double iconHeight =
            ExperienceToggleButton_IconHeight_get_Original(pThis);
        if (iconHeight != postureIconHeight) {
            prevIconHeight = iconHeight;
            SetExperienceToggleButtonIconHeight(pThis, postureIconHeight);
        }
    }

    ExperienceToggleButton_UpdateButtonPadding_Original(pThis);

    if (prevIconHeight) {
        SetExperienceToggleButtonIconHeight(pThis, *prevIconHeight);
    }

    FrameworkElement toggleButtonElement = nullptr;
    ((IUnknown**)pThis)[1]->QueryInterface(winrt::guid_of<FrameworkElement>(),
                                           winrt::put_abi(toggleButtonElement));
    if (!toggleButtonElement) {
        return;
    }

    auto panelElement =
        FindChildByName(toggleButtonElement, L"ExperienceToggleButtonRootPanel")
            .try_as<Controls::Grid>();
    if (!panelElement) {
        return;
    }

    auto className = winrt::get_class_name(toggleButtonElement);

    if (className == L"Taskbar.AugmentedEntryPointButton") {
        UpdateAugmentedEntryPointContent(panelElement);
        return;
    }

    if (g_hasDynamicIconScaling && g_unloading) {
        return;
    }

    double defaultWidthExtra = -4;

    if (className == L"Taskbar.ExperienceToggleButton") {
        auto automationId = Automation::AutomationProperties::GetAutomationId(
            toggleButtonElement);
        if (automationId == L"StartButton") {
            defaultWidthExtra = -3;
        }
    } else if (className == L"Taskbar.SearchBoxButton") {
        if (panelElement.Margin() != Thickness{}) {
            return;
        }
    } else {
        return;
    }

    double buttonWidth = panelElement.Width();
    if (!(buttonWidth > 0)) {
        return;
    }

    auto buttonPadding = panelElement.Padding();

    double defaultWidth = g_smallIconSize ? 32 : 44;
    double overrideWidth =
        g_unloading ? defaultWidth
                    : (g_smallIconSize ? g_iconSizeSettings.taskbarButtonWidthSmall
                                       : g_iconSizeSettings.taskbarButtonWidth);

    double newWidth = overrideWidth + buttonPadding.Left + buttonPadding.Right +
                      defaultWidthExtra;
    if (newWidth != buttonWidth) {
        panelElement.Width(newWidth);
    }
}

bool IsSearchIconButton(void* pThis) {
    FrameworkElement buttonElement = nullptr;
    ((IUnknown**)pThis)[1]->QueryInterface(winrt::guid_of<FrameworkElement>(),
                                           winrt::put_abi(buttonElement));
    if (!buttonElement) {
        return false;
    }

    return winrt::get_class_name(buttonElement) !=
           L"SearchUx.SearchUI.SearchBoxButton";
}

using SearchButtonBase_IconHeight_t = void(WINAPI*)(void* pThis, double height);
SearchButtonBase_IconHeight_t SearchButtonBase_IconHeight_Original;

thread_local bool g_inSearchButtonBase_IconHeight;

void SetSearchButtonIconHeight(void* pThis, double height) {
    g_inSearchButtonBase_IconHeight = true;
    SearchButtonBase_IconHeight_Original(pThis, height);
    g_inSearchButtonBase_IconHeight = false;
}

void WINAPI SearchButtonBase_IconHeight_Hook(void* pThis, double height) {
    if (!g_unloading && IsSearchIconButton(pThis)) {
        double iconSize =
            g_smallIconSize ? g_iconSizeSettings.iconSizeSmall : g_iconSizeSettings.iconSize;
        if (height != iconSize) {
            height = iconSize;
        }
    }

    SearchButtonBase_IconHeight_Original(pThis, height);
}

Controls::Grid GetSearchButtonRootPanel(FrameworkElement buttonElement) {
    auto panelElement =
        FindChildByName(buttonElement, L"SearchBoxButtonRootPanel")
            .try_as<Controls::Grid>();
    if (!panelElement) {
        return nullptr;
    }

    if (FindChildByName(panelElement, L"SearchBoxTextBlock")) {
        return nullptr;
    }

    return panelElement;
}

void SetSearchButtonRootPanelWidth(Controls::Grid panelElement) {
    double buttonWidth = panelElement.Width();
    if (!(buttonWidth > 0)) {
        return;
    }

    auto buttonPadding = panelElement.Padding();

    double defaultWidth = g_smallIconSize ? 32 : 44;
    double overrideWidth =
        g_unloading ? defaultWidth
                    : (g_smallIconSize ? g_iconSizeSettings.taskbarButtonWidthSmall
                                       : g_iconSizeSettings.taskbarButtonWidth);

    double newWidth =
        overrideWidth + buttonPadding.Left + buttonPadding.Right - 4;
    if (newWidth != buttonWidth) {
        panelElement.Width(newWidth);
    }
}

using SearchButtonBase_MeasureOverride_t =
    int(WINAPI*)(void* pThis,
                 winrt::Windows::Foundation::Size size,
                 winrt::Windows::Foundation::Size* resultSize);
SearchButtonBase_MeasureOverride_t SearchButtonBase_MeasureOverride_Original;
int WINAPI SearchButtonBase_MeasureOverride_Hook(
    void* pThis,
    winrt::Windows::Foundation::Size size,
    winrt::Windows::Foundation::Size* resultSize) {

    FrameworkElement buttonElement = nullptr;
    ((IUnknown*)pThis)
        ->QueryInterface(winrt::guid_of<FrameworkElement>(),
                         winrt::put_abi(buttonElement));
    if (buttonElement) {
        if (auto panelElement = GetSearchButtonRootPanel(buttonElement)) {
            SetSearchButtonRootPanelWidth(panelElement);
        }
    }

    return SearchButtonBase_MeasureOverride_Original(pThis, size, resultSize);
}

using SearchButtonBase_UpdateButtonPadding_t = void(WINAPI*)(void* pThis);
SearchButtonBase_UpdateButtonPadding_t
    SearchButtonBase_UpdateButtonPadding_Original;
void WINAPI SearchButtonBase_UpdateButtonPadding_Hook(void* pThis) {
    if (g_inSearchButtonBase_IconHeight) {
        return;
    }

    std::optional<double> prevIconHeight;
    if (!g_unloading && SearchButtonBase_IconHeight_Original &&
        IsSearchIconButton(pThis)) {
        double postureIconHeight = g_smallIconSize ? 16 : 24;
        double iconHeight =
            g_smallIconSize ? g_iconSizeSettings.iconSizeSmall : g_iconSizeSettings.iconSize;
        if (iconHeight != postureIconHeight) {
            prevIconHeight = iconHeight;
            SetSearchButtonIconHeight(pThis, postureIconHeight);
        }
    }

    SearchButtonBase_UpdateButtonPadding_Original(pThis);

    if (prevIconHeight) {
        SetSearchButtonIconHeight(pThis, *prevIconHeight);
    }

    if (g_hasDynamicIconScaling && g_unloading) {
        return;
    }

    FrameworkElement toggleButtonElement = nullptr;
    ((IUnknown**)pThis)[1]->QueryInterface(winrt::guid_of<FrameworkElement>(),
                                           winrt::put_abi(toggleButtonElement));
    if (!toggleButtonElement) {
        return;
    }

    auto panelElement = GetSearchButtonRootPanel(toggleButtonElement);
    if (!panelElement) {
        return;
    }

    SetSearchButtonRootPanelWidth(panelElement);
}

using ProgressBar_Width_t = void(WINAPI*)(void* pThis, double width);
ProgressBar_Width_t ProgressBar_Width_Original;
void WINAPI ProgressBar_Width_Hook(void* pThis, double width) {
    if (g_taskListButtonPostureIconHeight &&
        width == g_taskListButtonPostureIconHeight &&
        IsRuntimeClass(pThis, L"Microsoft.UI.Xaml.Controls.ProgressBar")) {
        width = g_taskListButtonCustomIconHeight;
    }

    ProgressBar_Width_Original(pThis, width);
}

using SHAppBarMessage_t = decltype(&SHAppBarMessage);
SHAppBarMessage_t SHAppBarMessage_Original;
auto WINAPI SHAppBarMessage_Hook(DWORD dwMessage, PAPPBARDATA pData) {
    auto ret = SHAppBarMessage_Original(dwMessage, pData);

    if (dwMessage == ABM_QUERYPOS && ret && !IsVerticalTaskbar() &&
        g_taskbarHeight) {
        HMONITOR monitor = (HMONITOR)GetProp(pData->hWnd, L"TaskbarMonitor");
        UINT dpiX = 0;
        UINT dpiY = 0;

        if (monitor) {
            GetDpiForMonitor(monitor, MDT_DEFAULT, &dpiX, &dpiY);
        }

        if (dpiY) {
            pData->rc.top =
                pData->rc.bottom - MulDiv(g_taskbarHeight, dpiY, 96);
        }
    }

    return ret;
}

using SendMessageTimeoutW_t = decltype(&SendMessageTimeoutW);
SendMessageTimeoutW_t SendMessageTimeoutW_Original;
LRESULT WINAPI SendMessageTimeoutW_Hook(HWND hWnd,
                                        UINT Msg,
                                        WPARAM wParam,
                                        LPARAM lParam,
                                        UINT fuFlags,
                                        UINT uTimeout,
                                        PDWORD_PTR lpdwResult) {
    if (g_shellIconLoaderV2_LoadAsyncIcon__ResumeCoro_ThreadId ==
            GetCurrentThreadId() &&
        !g_unloading && Msg == WM_GETICON && wParam == ICON_BIG &&
        (g_smallIconSize ? g_iconSizeSettings.iconSizeSmall : g_iconSizeSettings.iconSize) <=
            16) {
        wParam = ICON_SMALL2;
    }

    LRESULT ret = SendMessageTimeoutW_Original(hWnd, Msg, wParam, lParam,
                                               fuFlags, uTimeout, lpdwResult);

    return ret;
}

void LoadIconSizeSettings() {
    g_iconSizeSettings.taskbarHeight = Wh_GetIntSetting(L"TaskbarSize.TaskbarHeight");
    g_iconSizeSettings.iconSize = Wh_GetIntSetting(L"TaskbarSize.IconSize");
    g_iconSizeSettings.taskbarButtonWidth = Wh_GetIntSetting(L"TaskbarSize.TaskbarButtonWidth");
    g_iconSizeSettings.iconSizeSmall = Wh_GetIntSetting(L"TaskbarSize.IconSizeSmall");
    g_iconSizeSettings.taskbarButtonWidthSmall =
        Wh_GetIntSetting(L"TaskbarSize.TaskbarButtonWidthSmall");
}

bool ProtectAndMemcpy(DWORD protect, void* dst, const void* src, size_t size) {
    DWORD oldProtect;
    if (!VirtualProtect(dst, size, protect, &oldProtect)) {
        return false;
    }

    memcpy(dst, src, size);
    VirtualProtect(dst, size, oldProtect, &oldProtect);
    return true;
}

void ApplySettingsIconSize(int taskbarHeight) {
    if (taskbarHeight < 2) {
        taskbarHeight = 2;
    }

    HWND hTaskbarWnd = FindCurrentProcessTaskbarWnd();
    if (!hTaskbarWnd) {
        g_taskbarHeight = taskbarHeight;
        return;
    }

    if (!g_taskbarHeight) {
        g_taskbarHeight = g_originalTaskbarHeight;
    }

    if (!g_taskbarHeight) {
        RECT taskbarRect{};
        GetWindowRect(hTaskbarWnd, &taskbarRect);

        HMONITOR monitor = (HMONITOR)GetProp(hTaskbarWnd, L"TaskbarMonitor");
        UINT dpiX = 0;
        UINT dpiY = 0;

        if (monitor) {
            GetDpiForMonitor(monitor, MDT_DEFAULT, &dpiX, &dpiY);
        }

        if (!dpiY) {
            dpiY = 96;
        }

        g_taskbarHeight =
            MulDiv(taskbarRect.bottom - taskbarRect.top, 96, dpiY);
    }

    g_applyingSettings = true;

    if (!IsVerticalTaskbar() && taskbarHeight == g_taskbarHeight) {
        g_pendingMeasureOverride = true;

        g_taskbarHeight = taskbarHeight - 1;
        if (!TaskbarConfiguration_GetFrameSize_Original &&
            double_48_value_Original) {
            double tempTaskbarHeight = g_taskbarHeight;
            ProtectAndMemcpy(PAGE_READWRITE, double_48_value_Original,
                             &tempTaskbarHeight, sizeof(double));
        }

        DWORD_PTR sendResult1;
        SendMessageTimeout(hTaskbarWnd, WM_SETTINGCHANGE,
                           SPI_SETLOGICALDPIOVERRIDE, 0,
                           SMTO_ABORTIFHUNG | SMTO_NORMAL, 2000, &sendResult1);

        for (int i = 0; i < 20 && !g_unloading; i++) {
            if (!g_pendingMeasureOverride) break;
            Sleep(50);
        }
        g_pendingMeasureOverride = false;
    }

    g_pendingMeasureOverride = true;

    g_taskbarHeight = taskbarHeight;
    if (!TaskbarConfiguration_GetFrameSize_Original &&
        double_48_value_Original) {
        double tempTaskbarHeight = g_taskbarHeight;
        ProtectAndMemcpy(PAGE_READWRITE, double_48_value_Original,
                         &tempTaskbarHeight, sizeof(double));
    }

    DWORD_PTR sendResult2;
    SendMessageTimeout(hTaskbarWnd, WM_SETTINGCHANGE,
                       SPI_SETLOGICALDPIOVERRIDE, 0,
                       SMTO_ABORTIFHUNG | SMTO_NORMAL, 2000, &sendResult2);

    if (!IsVerticalTaskbar()) {
        for (int i = 0; i < 20 && !g_unloading; i++) {
            if (!g_pendingMeasureOverride) break;
            Sleep(50);
        }
        g_pendingMeasureOverride = false;
    } else {
        g_pendingMeasureOverride = false;
    }

    HWND hReBarWindow32 =
        FindWindowEx(hTaskbarWnd, nullptr, L"ReBarWindow32", nullptr);
    if (hReBarWindow32) {
        HWND hMSTaskSwWClass =
            FindWindowEx(hReBarWindow32, nullptr, L"MSTaskSwWClass", nullptr);
        if (hMSTaskSwWClass) {
            SendMessage(hMSTaskSwWClass, 0x452, 3, 0);
        }
    }

    g_applyingSettings = false;
}

bool HookSystemTraySymbols(HMODULE module) {
    WindhawkUtils::SYMBOL_HOOK symbolHooks[] = {
        {
            {LR"(public: __cdecl winrt::impl::consume_WindowsUdk_UI_Shell_ITaskbarSettings<struct winrt::WindowsUdk::UI::Shell::ITaskbarSettings>::Size(void)const )"},
            &TaskbarSettings_Size_SystemTray_Original,
            TaskbarSettings_Size_SystemTray_Hook,
            true,
        },
        {
            {LR"(private: double __cdecl winrt::SystemTray::implementation::SystemTrayController::GetFrameSize(enum winrt::WindowsUdk::UI::Shell::TaskbarSize))"},
            &SystemTrayController_GetFrameSize_Original,
            SystemTrayController_GetFrameSize_Hook,
            true,
        },
        {
            {LR"(private: double __cdecl winrt::SystemTray::implementation::SystemTraySecondaryController::GetFrameSize(enum winrt::WindowsUdk::UI::Shell::TaskbarSize))"},
            &SystemTraySecondaryController_GetFrameSize_Original,
            SystemTraySecondaryController_GetFrameSize_Hook,
            true,
        },
        {
            {LR"(private: void __cdecl winrt::SystemTray::implementation::SystemTrayController::UpdateFrameSize(void))"},
            &SystemTrayController_UpdateFrameSize_SymbolAddress,
            nullptr,
            true,
        },
        {
            {LR"(private: void __cdecl winrt::SystemTray::implementation::SystemTraySecondaryController::UpdateFrameSize(void))"},
            &SystemTraySecondaryController_UpdateFrameSize_Original,
            SystemTraySecondaryController_UpdateFrameSize_Hook,
            true,
        },
        {
            {LR"(public: __cdecl winrt::impl::consume_Windows_UI_Xaml_IFrameworkElement<struct winrt::SystemTray::SystemTrayFrame>::Height(double)const )"},
            &SystemTrayFrame_Height_Original,
            SystemTrayFrame_Height_Hook,
            true,
        },
        {
            {LR"(public: virtual int __cdecl winrt::impl::produce<struct winrt::SystemTray::implementation::SystemTrayFrame,struct winrt::Windows::UI::Xaml::IFrameworkElementOverrides>::MeasureOverride(struct winrt::Windows::Foundation::Size,struct winrt::Windows::Foundation::Size *))"},
            &SystemTrayFrame_MeasureOverride_Original,
            SystemTrayFrame_MeasureOverride_Hook,
            true,
        },
        {
            {LR"(public: __cdecl winrt::impl::consume_Windows_UI_Xaml_IFrameworkElementOverrides<struct winrt::Windows::UI::Xaml::IFrameworkElementOverrides>::MeasureOverride(struct winrt::Windows::Foundation::Size const &)const )"},
            &FrameworkElementOverrides_MeasureOverride_Original,
            FrameworkElementOverrides_MeasureOverride_Hook,
            true,
        },
    };

    if (!HookSymbols(module, symbolHooks, ARRAYSIZE(symbolHooks))) {
        Wh_Log(L"HookSymbols failed");
        return false;
    }

    if (SystemTrayController_UpdateFrameSize_SymbolAddress) {
        SystemTrayController_UpdateFrameSize_InitOffsets();
        WindhawkUtils::SetFunctionHook(
            SystemTrayController_UpdateFrameSize_SymbolAddress,
            SystemTrayController_UpdateFrameSize_Hook,
            &SystemTrayController_UpdateFrameSize_Original);
    }

    return true;
}

bool HookTaskbarViewDllSymbols(HMODULE module,
                               bool hookSystemTraySymbolsInline) {
    WindhawkUtils::SYMBOL_HOOK symbolHooks[] = {
        {
            {LR"(__real@4048000000000000)"},
            &double_48_value_Original,
            nullptr,
            true,
        },
        {
            {
                LR"(public: __cdecl winrt::impl::consume_Windows_Foundation_Collections_IMap<struct winrt::Windows::UI::Xaml::ResourceDictionary,struct winrt::Windows::Foundation::IInspectable,struct winrt::Windows::Foundation::IInspectable>::Lookup(struct winrt::Windows::Foundation::IInspectable const &)const )",
                LR"(public: struct winrt::Windows::Foundation::IInspectable __cdecl winrt::impl::consume_Windows_Foundation_Collections_IMap<struct winrt::Windows::UI::Xaml::ResourceDictionary,struct winrt::Windows::Foundation::IInspectable,struct winrt::Windows::Foundation::IInspectable>::Lookup(struct winrt::Windows::Foundation::IInspectable const &)const )",
            },
            &ResourceDictionary_Lookup_TaskbarView_Original,
            ResourceDictionary_Lookup_TaskbarView_Hook,
        },
        {
            {LR"(public: virtual int __cdecl winrt::impl::produce<struct winrt::Taskbar::implementation::TaskListItemViewModel,struct winrt::Taskbar::ITaskListItemViewModel>::GetIconHeight(void *,double *))"},
            &TaskListItemViewModel_GetIconHeight_Original,
            TaskListItemViewModel_GetIconHeight_Hook,
            true,
        },
        {
            {LR"(public: virtual int __cdecl winrt::impl::produce<struct winrt::Taskbar::implementation::TaskListGroupViewModel,struct winrt::Taskbar::ITaskbarAppItemViewModel>::GetIconHeight(void *,double *))"},
            &TaskListGroupViewModel_GetIconHeight_Original,
            TaskListGroupViewModel_GetIconHeight_Hook,
            true,
        },
        {
            {LR"(public: static double __cdecl winrt::Taskbar::implementation::TaskbarConfiguration::GetIconHeightInViewPixels(enum winrt::WindowsUdk::UI::Shell::TaskbarSize))"},
            &TaskbarConfiguration_GetIconHeightInViewPixels_taskbarSizeEnum_Original,
            TaskbarConfiguration_GetIconHeightInViewPixels_taskbarSizeEnum_Hook,
        },
        {
            {LR"(public: static double __cdecl winrt::Taskbar::implementation::TaskbarConfiguration::GetIconHeightInViewPixels(double))"},
            &TaskbarConfiguration_GetIconHeightInViewPixels_double_Original,
            TaskbarConfiguration_GetIconHeightInViewPixels_double_Hook,
            true,
        },
        {
            {LR"(public: double __cdecl winrt::Taskbar::implementation::TaskbarConfiguration::GetIconHeightInViewPixels(void))"},
            &TaskbarConfiguration_GetIconHeightInViewPixels_method_Original,
            TaskbarConfiguration_GetIconHeightInViewPixels_method_Hook,
            true,
        },
        {
            {LR"(public: void __cdecl winrt::Taskbar::implementation::TaskListButton::IconHeight(double))"},
            &TaskListButton_IconHeight_Original,
            nullptr,
            true,
        },
        {
            {LR"(public: __cdecl winrt::impl::consume_WindowsUdk_UI_Shell_ITaskbarSettings<struct winrt::WindowsUdk::UI::Shell::ITaskbarSettings>::Size(void)const )"},
            &TaskbarSettings_Size_TaskbarView_Original,
            TaskbarSettings_Size_TaskbarView_Hook,
            true,
        },
        {
            {LR"(public: static double __cdecl winrt::Taskbar::implementation::TaskbarConfiguration::GetFrameSize(enum winrt::WindowsUdk::UI::Shell::TaskbarSize))"},
            &TaskbarConfiguration_GetFrameSize_Original,
            TaskbarConfiguration_GetFrameSize_Hook,
            true,
        },
#ifdef _M_ARM64
        {
            {LR"(private: void __cdecl winrt::Taskbar::implementation::TaskbarConfiguration::UpdateFrameSize(void))"},
            &TaskbarConfiguration_UpdateFrameSize_SymbolAddress,
            nullptr,
        },
        {
            {LR"(public: void __cdecl winrt::event<struct winrt::delegate<> >::operator()<>(void))"},
            &Event_operator_call_Original,
            Event_operator_call_Hook,
        },
#endif
        {
            {LR"(public: __cdecl winrt::impl::consume_Windows_UI_Xaml_IFrameworkElement<struct winrt::Taskbar::implementation::TaskbarFrame>::MaxHeight(double)const )"},
            &TaskbarFrame_MaxHeight_double_Original,
            nullptr,
            true,
        },
        {
            {
                LR"(public: __cdecl winrt::impl::consume_Windows_UI_Xaml_IFrameworkElement<struct winrt::Taskbar::implementation::TaskbarFrame>::Height(double)const )",
                LR"(public: void __cdecl winrt::impl::consume_Windows_UI_Xaml_IFrameworkElement<struct winrt::Taskbar::implementation::TaskbarFrame>::Height(double)const )",
            },
            &TaskbarFrame_Height_double_Original,
            TaskbarFrame_Height_double_Hook,
            true,
        },
        {
            {LR"(private: void __cdecl winrt::Taskbar::implementation::TaskbarController::OnGroupingModeChanged(void))"},
            &TaskbarController_OnGroupingModeChanged_Original,
            nullptr,
            true,
        },
        {
            {LR"(private: void __cdecl winrt::Taskbar::implementation::TaskbarController::UpdateFrameHeight(void))"},
            &TaskbarController_UpdateFrameHeight_Original,
            TaskbarController_UpdateFrameHeight_Hook,
            true,
        },
        {
            {LR"(public: virtual int __cdecl winrt::impl::produce<struct winrt::Taskbar::implementation::TaskbarFrame,struct winrt::Windows::UI::Xaml::IFrameworkElementOverrides>::MeasureOverride(struct winrt::Windows::Foundation::Size,struct winrt::Windows::Foundation::Size *))"},
            &TaskbarFrame_MeasureOverride_Original,
            TaskbarFrame_MeasureOverride_Hook,
        },
        {
            {LR"(public: struct winrt::Taskbar::implementation::TaskbarFrameMetrics __cdecl winrt::Taskbar::implementation::TaskbarFrame::GetMetrics(void)const )"},
            &TaskbarFrame_GetMetrics_Original,
            TaskbarFrame_GetMetrics_Hook,
            true,
        },
        {
            {LR"(private: void __cdecl winrt::Taskbar::implementation::TaskListButton::UpdateButtonPadding(void))"},
            &TaskListButton_UpdateButtonPadding_Original,
            TaskListButton_UpdateButtonPadding_Hook,
        },
        {
            {LR"(public: void __cdecl winrt::Taskbar::implementation::TaskListButton::OverlayIcon(struct winrt::Windows::Storage::Streams::IRandomAccessStream const &))"},
            &TaskListButton_OverlayIcon_Original,
            TaskListButton_OverlayIcon_Hook,
        },
        {
            {LR"(private: void __cdecl winrt::Taskbar::implementation::TaskListButton::UpdateBadge(void))"},
            &TaskListButton_UpdateBadge_Original,
            TaskListButton_UpdateBadge_Hook,
        },
        {
            {LR"(private: void __cdecl winrt::Taskbar::implementation::TaskListButton::UpdateMultiWindowClip(void))"},
            &TaskListButton_UpdateMultiWindowClip_Original,
            TaskListButton_UpdateMultiWindowClip_Hook,
            true,
        },
        {
            {LR"(private: void __cdecl winrt::Taskbar::implementation::TaskListButton::CreateMultiWindowClip(void))"},
            &TaskListButton_CreateMultiWindowClip_Original,
            TaskListButton_CreateMultiWindowClip_Hook,
            true,
        },
        {
            {LR"(private: void __cdecl winrt::Taskbar::implementation::TaskListButton::UpdateIconColumnDefinition(void))"},
            &TaskListButton_UpdateIconColumnDefinition_Original,
            nullptr,
            true,
        },
        {
            {LR"(private: void __cdecl winrt::Taskbar::implementation::TaskListButton::UpdateVisualStates(void))"},
            &TaskListButton_UpdateVisualStates_Original,
            TaskListButton_UpdateVisualStates_Hook,
        },
        {
            {LR"(public: void __cdecl winrt::Microsoft::Windows::Taskbar::implementation::TaskbarComponentHost::IconHeight(double))"},
            &TaskbarComponentHost_IconHeight_Original,
            nullptr,
            true,
        },
        {
            {LR"(private: void __cdecl winrt::Microsoft::Windows::Taskbar::implementation::TaskbarComponentHost::UpdateDefaultWidth(void))"},
            &TaskbarComponentHost_UpdateDefaultWidth_Original,
            TaskbarComponentHost_UpdateDefaultWidth_Hook,
            true,
        },
        {
            {LR"(public: double __cdecl winrt::Taskbar::implementation::ExperienceToggleButton::IconHeight(void)const )"},
            &ExperienceToggleButton_IconHeight_get_Original,
            nullptr,
            true,
        },
        {
            {LR"(public: void __cdecl winrt::Taskbar::implementation::ExperienceToggleButton::IconHeight(double))"},
            &ExperienceToggleButton_IconHeight_set_Original,
            nullptr,
            true,
        },
        {
            {LR"(protected: virtual void __cdecl winrt::Taskbar::implementation::ExperienceToggleButton::UpdateButtonPadding(void))"},
            &ExperienceToggleButton_UpdateButtonPadding_Original,
            ExperienceToggleButton_UpdateButtonPadding_Hook,
        },
        {
            {LR"(public: __cdecl winrt::impl::consume_Windows_UI_Xaml_IFrameworkElement<struct winrt::Microsoft::UI::Xaml::Controls::ProgressBar>::Width(double)const )"},
            &ProgressBar_Width_Original,
            ProgressBar_Width_Hook,
            true,
        },
    };

    WindhawkUtils::SYMBOL_HOOK symbolHooksSystemTray[] = {
        {
            {LR"(private: double __cdecl winrt::SystemTray::implementation::SystemTrayController::GetFrameSize(enum winrt::WindowsUdk::UI::Shell::TaskbarSize))"},
            &SystemTrayController_GetFrameSize_Original,
            SystemTrayController_GetFrameSize_Hook,
            true,
        },
        {
            {LR"(private: double __cdecl winrt::SystemTray::implementation::SystemTraySecondaryController::GetFrameSize(enum winrt::WindowsUdk::UI::Shell::TaskbarSize))"},
            &SystemTraySecondaryController_GetFrameSize_Original,
            SystemTraySecondaryController_GetFrameSize_Hook,
            true,
        },
        {
            {LR"(private: void __cdecl winrt::SystemTray::implementation::SystemTrayController::UpdateFrameSize(void))"},
            &SystemTrayController_UpdateFrameSize_SymbolAddress,
            nullptr,
            true,
        },
        {
            {LR"(private: void __cdecl winrt::SystemTray::implementation::SystemTraySecondaryController::UpdateFrameSize(void))"},
            &SystemTraySecondaryController_UpdateFrameSize_Original,
            SystemTraySecondaryController_UpdateFrameSize_Hook,
            true,
        },
        {
            {LR"(public: __cdecl winrt::impl::consume_Windows_UI_Xaml_IFrameworkElement<struct winrt::SystemTray::SystemTrayFrame>::Height(double)const )"},
            &SystemTrayFrame_Height_Original,
            SystemTrayFrame_Height_Hook,
            true,
        },
        {
            {LR"(public: virtual int __cdecl winrt::impl::produce<struct winrt::SystemTray::implementation::SystemTrayFrame,struct winrt::Windows::UI::Xaml::IFrameworkElementOverrides>::MeasureOverride(struct winrt::Windows::Foundation::Size,struct winrt::Windows::Foundation::Size *))"},
            &SystemTrayFrame_MeasureOverride_Original,
            SystemTrayFrame_MeasureOverride_Hook,
            true,
        },
        {
            {LR"(public: __cdecl winrt::impl::consume_Windows_UI_Xaml_IFrameworkElementOverrides<struct winrt::Windows::UI::Xaml::IFrameworkElementOverrides>::MeasureOverride(struct winrt::Windows::Foundation::Size const &)const )"},
            &FrameworkElementOverrides_MeasureOverride_Original,
            FrameworkElementOverrides_MeasureOverride_Hook,
            true,
        },
    };

    using COMBINED_SH = WindhawkUtils::SYMBOL_HOOK;
    COMBINED_SH allHooks[ARRAYSIZE(symbolHooks) + ARRAYSIZE(symbolHooksSystemTray)];
    int index = 0;

    for (auto& hook : symbolHooks) {
        allHooks[index++] = std::move(hook);
    }

    if (hookSystemTraySymbolsInline) {
        for (auto& hook : symbolHooksSystemTray) {
            allHooks[index++] = std::move(hook);
        }
    }

    if (!HookSymbols(module, allHooks, index)) {
        Wh_Log(L"HookSymbols failed");
        return false;
    }

    if (TaskListButton_IconHeight_Original) {
        TaskListButton_IconHeight_InitOffsets();
    }
    if (TaskbarComponentHost_IconHeight_Original) {
        TaskbarComponentHost_IconHeight_InitOffsets();
    }

#ifdef _M_ARM64
    if (TaskbarConfiguration_UpdateFrameSize_SymbolAddress) {
        TaskbarConfiguration_UpdateFrameSize_InitOffsets();
        WindhawkUtils::SetFunctionHook(
            TaskbarConfiguration_UpdateFrameSize_SymbolAddress,
            TaskbarConfiguration_UpdateFrameSize_Hook,
            &TaskbarConfiguration_UpdateFrameSize_Original);
    }
#endif

    if (hookSystemTraySymbolsInline &&
        SystemTrayController_UpdateFrameSize_SymbolAddress) {
        SystemTrayController_UpdateFrameSize_InitOffsets();
        WindhawkUtils::SetFunctionHook(
            SystemTrayController_UpdateFrameSize_SymbolAddress,
            SystemTrayController_UpdateFrameSize_Hook,
            &SystemTrayController_UpdateFrameSize_Original);
    }

    if (TaskbarController_OnGroupingModeChanged_Original) {
        TaskbarController_OnGroupingModeChanged_InitOffsets();
    }

    if (TaskListButton_UpdateIconColumnDefinition_Original) {
        TaskListButton_UpdateIconColumnDefinition_InitOffsets();
    }

    constexpr UINT kDynamicIconScaling = 29785184;
    if (TaskbarConfiguration_GetIconHeightInViewPixels_method_Original &&
        IsOsFeatureEnabled(kDynamicIconScaling).value_or(true)) {
        g_hasDynamicIconScaling = true;
    }

    return true;
}

bool HookSearchUxUiDllSymbols(HMODULE module) {
    WindhawkUtils::SYMBOL_HOOK symbolHooks[] = {
        {
            {LR"(public: __cdecl winrt::impl::consume_Windows_Foundation_Collections_IMap<struct winrt::Windows::UI::Xaml::ResourceDictionary,struct winrt::Windows::Foundation::IInspectable,struct winrt::Windows::Foundation::IInspectable>::Lookup(struct winrt::Windows::Foundation::IInspectable const &)const )"},
            &ResourceDictionary_Lookup_SearchUxUi_Original,
            ResourceDictionary_Lookup_SearchUxUi_Hook,
        },
        {
            {LR"(public: void __cdecl winrt::SearchUx::SearchUI::implementation::SearchButtonBase::IconHeight(double))"},
            &SearchButtonBase_IconHeight_Original,
            SearchButtonBase_IconHeight_Hook,
            true,
        },
        {
            {LR"(protected: virtual void __cdecl winrt::SearchUx::SearchUI::implementation::SearchButtonBase::UpdateButtonPadding(void))"},
            &SearchButtonBase_UpdateButtonPadding_Original,
            SearchButtonBase_UpdateButtonPadding_Hook,
        },
        {
            {LR"(public: virtual int __cdecl winrt::impl::produce<struct winrt::SearchUx::SearchUI::implementation::SearchButtonBase,struct winrt::Windows::UI::Xaml::IFrameworkElementOverrides>::MeasureOverride(struct winrt::Windows::Foundation::Size,struct winrt::Windows::Foundation::Size *))"},
            &SearchButtonBase_MeasureOverride_Original,
            SearchButtonBase_MeasureOverride_Hook,
            true,
        },
    };

    if (!HookSymbols(module, symbolHooks, ARRAYSIZE(symbolHooks))) {
        Wh_Log(L"HookSymbols failed");
        return false;
    }

    return true;
}

bool HookIconSizeTaskbarDllSymbols() {
    HMODULE module =
        LoadLibraryEx(L"taskbar.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!module) {
        Wh_Log(L"Failed to load taskbar.dll");
        return false;
    }

    WindhawkUtils::SYMBOL_HOOK taskbarDllHooks[] = {
        {
            {LR"(void __cdecl IconUtils::GetIconSize(bool,enum IconUtils::IconType,struct tagSIZE *))"},
            &IconUtils_GetIconSize_Original,
            IconUtils_GetIconSize_Hook,
        },
        {
            {LR"(public: virtual bool __cdecl IconContainer::IsStorageRecreationRequired(class CCoSimpleArray<unsigned int,4294967294,class CSimpleArrayStandardCompareHelper<unsigned int> > const &,enum IconContainerFlags))"},
            &IconContainer_IsStorageRecreationRequired_Original,
            IconContainer_IsStorageRecreationRequired_Hook,
        },
        {
            {LR"(public: virtual void __cdecl TrayUI::GetMinSize(struct HMONITOR__ *,struct tagSIZE *))"},
            &TrayUI_GetMinSize_Original,
            TrayUI_GetMinSize_Hook,
            true,
        },
        {
            {LR"(public: __cdecl winrt::impl::consume_WindowsUdk_UI_Shell_ITaskbarSettings<struct winrt::WindowsUdk::UI::Shell::ITaskbarSettings>::Size(void)const )"},
            &TaskbarSettings_Size_TaskbarDll_Original,
            TaskbarSettings_Size_TaskbarDll_Hook,
            true,
        },
        {
            {LR"(public: virtual unsigned __int64 __cdecl CIconLoadingFunctions::GetClassLongPtrW(struct HWND__ *,int))"},
            &CIconLoadingFunctions_GetClassLongPtrW_Original,
            CIconLoadingFunctions_GetClassLongPtrW_Hook,
        },
        {
            {LR"(public: virtual int __cdecl CIconLoadingFunctions::SendMessageCallbackW(struct HWND__ *,unsigned int,unsigned __int64,__int64,void (__cdecl*)(struct HWND__ *,unsigned int,unsigned __int64,__int64),unsigned __int64))"},
            &CIconLoadingFunctions_SendMessageCallbackW_Original,
            CIconLoadingFunctions_SendMessageCallbackW_Hook,
        },
        {
            {LR"(static  ShellIconLoaderV2::LoadAsyncIcon$_ResumeCoro$1())"},
            &ShellIconLoaderV2_LoadAsyncIcon__ResumeCoro_Original,
            ShellIconLoaderV2_LoadAsyncIcon__ResumeCoro_Hook,
            true,
        },
        {
            {LR"(public: void __cdecl TrayUI::_StuckTrayChange(void))"},
            &TrayUI__StuckTrayChange_Original,
        },
        {
            {LR"(public: void __cdecl TrayUI::_HandleSettingChange(struct HWND__ *,unsigned int,unsigned __int64,__int64))"},
            &TrayUI__HandleSettingChange_Original,
            TrayUI__HandleSettingChange_Hook,
        },
    };

    if (!HookSymbols(module, taskbarDllHooks, ARRAYSIZE(taskbarDllHooks))) {
        Wh_Log(L"HookSymbols failed");
        return false;
    }

    return true;
}

HMODULE GetTaskbarViewModuleHandle() {
    HMODULE module = GetModuleHandle(L"Taskbar.View.dll");
    if (!module) {
        module = GetModuleHandle(L"ExplorerExtensions.dll");
    }

    return module;
}

HMODULE GetSearchUxUiModuleHandle() {
    return GetModuleHandle(L"SearchUx.UI.dll");
}

void HandleLoadedModuleIconSize(HMODULE module, LPCWSTR lpLibFileName) {
    if (!g_iconSizeSystemTrayModuleHooked &&
        GetSystemTrayModuleHandle() == module &&
        module != GetTaskbarViewModuleHandle() &&
        !g_iconSizeSystemTrayModuleHooked.exchange(true)) {
        if (HookSystemTraySymbols(module)) {
            Wh_ApplyHookOperations();
        }
    }

    if (!g_taskbarViewDllLoaded && GetTaskbarViewModuleHandle() == module &&
        !g_taskbarViewDllLoaded.exchange(true)) {
        bool hookSystemTraySymbolsInline =
            !g_iconSizeSystemTrayModuleHooked &&
            GetSystemTrayModuleHandle() == module &&
            !g_iconSizeSystemTrayModuleHooked.exchange(true);

        if (HookTaskbarViewDllSymbols(module, hookSystemTraySymbolsInline)) {
            Wh_ApplyHookOperations();
        }
    }

    if (!g_searchUxUiDllLoaded && GetSearchUxUiModuleHandle() == module &&
        !g_searchUxUiDllLoaded.exchange(true)) {
        if (HookSearchUxUiDllSymbols(module)) {
            Wh_ApplyHookOperations();
        }
    }
}

BOOL IconSize_ModInit() {
    LoadIconSizeSettings();

    if (!HookIconSizeTaskbarDllSymbols()) {
        return FALSE;
    }

    if (HMODULE systemTrayModule = GetSystemTrayModuleHandle()) {
        if (systemTrayModule != GetTaskbarViewModuleHandle()) {
            g_iconSizeSystemTrayModuleHooked = true;
            if (!HookSystemTraySymbols(systemTrayModule)) {
                return FALSE;
            }
        }
    }

    if (HMODULE taskbarViewModule = GetTaskbarViewModuleHandle()) {
        g_taskbarViewDllLoaded = true;
        bool hookSystemTraySymbolsInline =
            !g_iconSizeSystemTrayModuleHooked &&
            GetSystemTrayModuleHandle() == taskbarViewModule;
        if (hookSystemTraySymbolsInline) {
            g_iconSizeSystemTrayModuleHooked = true;
        }
        if (!HookTaskbarViewDllSymbols(taskbarViewModule,
                                       hookSystemTraySymbolsInline)) {
            return FALSE;
        }
    }

    if (HMODULE searchUxUiModule = GetSearchUxUiModuleHandle()) {
        g_searchUxUiDllLoaded = true;
        if (!HookSearchUxUiDllSymbols(searchUxUiModule)) {
            return FALSE;
        }
    }

    WindhawkUtils::SetFunctionHook(SHAppBarMessage, SHAppBarMessage_Hook,
                                   &SHAppBarMessage_Original);

    WindhawkUtils::SetFunctionHook(SendMessageTimeoutW,
                                   SendMessageTimeoutW_Hook,
                                   &SendMessageTimeoutW_Original);

    return TRUE;
}

HANDLE g_iconSizeInitialApplyThread;

void IconSize_ModAfterInit() {
    if (!g_iconSizeSystemTrayModuleHooked) {
        if (HMODULE systemTrayModule = GetSystemTrayModuleHandle()) {
            if (systemTrayModule != GetTaskbarViewModuleHandle() &&
                !g_iconSizeSystemTrayModuleHooked.exchange(true)) {
                if (HookSystemTraySymbols(systemTrayModule)) {
                    Wh_ApplyHookOperations();
                }
            }
        }
    }

    if (!g_taskbarViewDllLoaded) {
        if (HMODULE taskbarViewModule = GetTaskbarViewModuleHandle()) {
            if (!g_taskbarViewDllLoaded.exchange(true)) {
                bool hookSystemTraySymbolsInline =
                    !g_iconSizeSystemTrayModuleHooked &&
                    GetSystemTrayModuleHandle() == taskbarViewModule &&
                    !g_iconSizeSystemTrayModuleHooked.exchange(true);

                if (HookTaskbarViewDllSymbols(taskbarViewModule,
                                              hookSystemTraySymbolsInline)) {
                    Wh_ApplyHookOperations();
                }
            }
        }
    }

    if (!g_searchUxUiDllLoaded) {
        if (HMODULE searchUxUiModule = GetSearchUxUiModuleHandle()) {
            if (!g_searchUxUiDllLoaded.exchange(true)) {
                if (HookSearchUxUiDllSymbols(searchUxUiModule)) {
                    Wh_ApplyHookOperations();
                }
            }
        }
    }

    // Apply on a background thread so Explorer startup is never blocked.
    g_iconSizeInitialApplyThread = CreateThread(
        nullptr, 0,
        [](LPVOID) -> DWORD {
            for (int i = 0; i < 40 && !g_unloading; i++) {
                if (FindCurrentProcessTaskbarWnd()) break;
                Sleep(250);
            }
            if (!g_unloading) {
                ApplySettingsIconSize(g_iconSizeSettings.taskbarHeight);
            }
            return 0;
        },
        nullptr, 0, nullptr);
}

void IconSize_ModBeforeUninit() {
    if (g_iconSizeInitialApplyThread) {
        WaitForSingleObject(g_iconSizeInitialApplyThread, 10000);
        CloseHandle(g_iconSizeInitialApplyThread);
        g_iconSizeInitialApplyThread = nullptr;
    }
    ApplySettingsIconSize(g_originalTaskbarHeight ? g_originalTaskbarHeight
                                                   : 48);
}

void IconSize_ModUninit() {
    while (g_hookCallCounter > 0) {
        Sleep(100);
    }
}

void IconSize_ModSettingsChanged() {
    LoadIconSizeSettings();
    ApplySettingsIconSize(g_iconSizeSettings.taskbarHeight);
}

// ----- TASKBAR CONTROL & ICON STYLING ENGINE -----

void LoadStylerSettings() {
    PCWSTR xamlDiagnosticsHandling =
        Wh_GetStringSetting(L"Styling.xamlDiagnosticsHandling");
    g_stylerSettings.xamlDiagnosticsHandling = XamlDiagnosticsHandling::kAlert;
    if (wcscmp(xamlDiagnosticsHandling, L"block") == 0) {
        g_stylerSettings.xamlDiagnosticsHandling = XamlDiagnosticsHandling::kBlock;
    } else if (wcscmp(xamlDiagnosticsHandling, L"allow") == 0) {
        g_stylerSettings.xamlDiagnosticsHandling = XamlDiagnosticsHandling::kAllow;
    }
    Wh_FreeStringSetting(xamlDiagnosticsHandling);
}

HANDLE g_restartExplorerPromptThread;
std::atomic<HWND> g_restartExplorerPromptWindow;

constexpr WCHAR kRestartExplorerPromptTitle[] =
    L"Taskbar Tray & Clock Tweaks - Windhawk";
constexpr WCHAR kRestartExplorerPromptTextFormat[] =
    L"Restarting Explorer is required for the mod to activate.\n\nDo you want "
    L"to restart Explorer now?\n\nStatus code: 0x%08X";
constexpr WCHAR kRestartExplorerCommand[] =
    LR"(cmd /c "echo Terminating Explorer...)"
    LR"( & taskkill /f /im explorer.exe)"
    LR"( & timeout /t 1 /nobreak >nul)"
    LR"( & start explorer.exe)"
    LR"( & echo Starting Explorer...)"
    LR"( & timeout /t 3 /nobreak >nul")";

void PromptToRestartExplorer(HRESULT statusCode) {
    if (g_restartExplorerPromptThread) {
        if (WaitForSingleObject(g_restartExplorerPromptThread, 0) !=
            WAIT_OBJECT_0) {
            return;
        }

        CloseHandle(g_restartExplorerPromptThread);
    }

    g_restartExplorerPromptThread = CreateThread(
        nullptr, 0,
        [](LPVOID lpParameter) -> DWORD {
            HRESULT statusCode =
                static_cast<HRESULT>(reinterpret_cast<ULONG_PTR>(lpParameter));

            WCHAR promptText[256];
            _snwprintf_s(promptText, _TRUNCATE,
                         kRestartExplorerPromptTextFormat, statusCode);

            TASKDIALOGCONFIG taskDialogConfig{
                .cbSize = sizeof(taskDialogConfig),
                .dwFlags = TDF_ALLOW_DIALOG_CANCELLATION,
                .dwCommonButtons = TDCBF_YES_BUTTON | TDCBF_NO_BUTTON,
                .pszWindowTitle = kRestartExplorerPromptTitle,
                .pszMainIcon = TD_INFORMATION_ICON,
                .pszContent = promptText,
                .pfCallback = [](HWND hwnd, UINT msg, WPARAM wParam,
                                 LPARAM lParam, LONG_PTR lpRefData) -> HRESULT {
                    switch (msg) {
                        case TDN_CREATED:
                            g_restartExplorerPromptWindow = hwnd;
                            SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0,
                                         SWP_NOMOVE | SWP_NOSIZE);
                            break;

                        case TDN_DESTROYED:
                            g_restartExplorerPromptWindow = nullptr;
                            break;
                    }

                    return S_OK;
                },
            };

            int button;
            if (SUCCEEDED(TaskDialogIndirect(&taskDialogConfig, &button,
                                             nullptr, nullptr)) &&
                button == IDYES) {
                WCHAR commandLine[ARRAYSIZE(kRestartExplorerCommand)];
                memcpy(commandLine, kRestartExplorerCommand,
                       sizeof(kRestartExplorerCommand));
                STARTUPINFO si = {
                    .cb = sizeof(si),
                };
                PROCESS_INFORMATION pi{};
                if (CreateProcess(nullptr, commandLine, nullptr, nullptr, FALSE,
                                  0, nullptr, nullptr, &si, &pi)) {
                    CloseHandle(pi.hThread);
                    CloseHandle(pi.hProcess);
                }
            }

            return 0;
        },
        reinterpret_cast<LPVOID>(static_cast<ULONG_PTR>(statusCode)), 0,
        nullptr);
}

enum class ElementId : uint64_t { None = 0 };

ElementId GetOrCreateElementId(
    InstanceHandle handle,
    winrt::Windows::Foundation::IInspectable const& element);
ElementId FindElementId(InstanceHandle handle);
void ForgetElementId(InstanceHandle handle);

void ApplyCustomizations(ElementId elementId,
                         winrt::Windows::UI::Xaml::FrameworkElement element,
                         PCWSTR fallbackClassName);
void CleanupCustomizations(ElementId elementId);
void QueueDiagnosticsRelease(InstanceHandle handle);
void FlushDiagnosticsReleasesIfQuiet();

HMODULE GetCurrentModuleHandle() {
    HMODULE module;
    if (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                               GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                           L"", &module)) {
        return nullptr;
    }

    return module;
}

thread_local bool g_reportCompositionDiagAsDisabled;

winrt::weak_ref<wf::IInspectable> TryMakeWeak(wf::IInspectable const& object) {
    if (!object.try_as<::IWeakReferenceSource>()) {
        return nullptr;
    }

    return winrt::make_weak(object);
}

static constexpr GUID IID_IXamlDiagnosticsTestHooks =
    {0x735941a2, 0x3ee3, 0x495a, {0x8d, 0xa9, 0x97, 0x26, 0x27, 0x00, 0x30, 0x75}};

struct IXamlDiagnosticsTestHooks : IUnknown {
    virtual HRESULT STDMETHODCALLTYPE UnregisterInstance(InstanceHandle handle) = 0;
    virtual HRESULT STDMETHODCALLTYPE TryGetDispatcherQueueForObject(InstanceHandle handle, void** dispatcherQueue) = 0;
};

InstanceHandle HandleFromInspectable(wf::IInspectable const& instance) {
    winrt::com_ptr<::IInspectable> inspectable;
    winrt::check_hresult(reinterpret_cast<::IUnknown*>(winrt::get_abi(instance))->QueryInterface(winrt::guid_of<wf::IInspectable>(), inspectable.put_void()));
    return reinterpret_cast<InstanceHandle>(inspectable.get());
}

thread_local bool g_stylerInitializedForThread = false;

std::atomic<bool> g_stylerInitialized{false};
thread_local bool g_elementPropertyModifying = false;


class VisualTreeWatcher : public winrt::implements<VisualTreeWatcher, IVisualTreeServiceCallback2, winrt::non_agile> {
public:
    VisualTreeWatcher(winrt::com_ptr<IUnknown> site);

    VisualTreeWatcher(const VisualTreeWatcher&) = delete;
    VisualTreeWatcher& operator=(const VisualTreeWatcher&) = delete;

    VisualTreeWatcher(VisualTreeWatcher&&) = delete;
    VisualTreeWatcher& operator=(VisualTreeWatcher&&) = delete;

    ~VisualTreeWatcher();

    void UnadviseVisualTreeChange();
    bool ReleaseDiagnosticsReference(InstanceHandle handle);

private:
    HRESULT STDMETHODCALLTYPE OnVisualTreeChange(ParentChildRelation relation, VisualElement element, VisualMutationType mutationType) override;
    HRESULT STDMETHODCALLTYPE OnElementStateChanged(InstanceHandle element, VisualElementState elementState, LPCWSTR context) noexcept override;

    wf::IInspectable FromHandle(InstanceHandle handle) {
        wf::IInspectable obj;
        winrt::check_hresult(m_XamlDiagnostics->GetIInspectableFromHandle(handle, reinterpret_cast<::IInspectable**>(winrt::put_abi(obj))));
        return obj;
    }

    winrt::com_ptr<IXamlDiagnostics> m_XamlDiagnostics = nullptr;
    winrt::com_ptr<IXamlDiagnosticsTestHooks> m_XamlDiagnosticsTestHooks = nullptr;
};

VisualTreeWatcher::VisualTreeWatcher(winrt::com_ptr<IUnknown> site) :
    m_XamlDiagnostics(site.as<IXamlDiagnostics>()) {
    HRESULT hr = m_XamlDiagnostics->QueryInterface(IID_IXamlDiagnosticsTestHooks, m_XamlDiagnosticsTestHooks.put_void());
    if (FAILED(hr)) {
        Wh_Log(L"IXamlDiagnosticsTestHooks is unavailable: %08X", hr);
    }

    HANDLE thread = CreateThread(
        nullptr, 0,
        [](LPVOID lpParam) -> DWORD {
            auto watcher = reinterpret_cast<VisualTreeWatcher*>(lpParam);
            auto service = watcher->m_XamlDiagnostics.as<IVisualTreeService3>();
            g_reportCompositionDiagAsDisabled = true;
            HRESULT hr = service->AdviseVisualTreeChange(watcher);
            g_reportCompositionDiagAsDisabled = false;
            watcher->Release();
            if (FAILED(hr)) {
                Wh_Log(L"AdviseVisualTreeChange failed with error %08X", hr);
                PromptToRestartExplorer(hr);
            }
            return 0;
        },
        this, 0, nullptr);
    if (thread) {
        AddRef();
        CloseHandle(thread);
    }
}

VisualTreeWatcher::~VisualTreeWatcher() {}

void VisualTreeWatcher::UnadviseVisualTreeChange() {
    HRESULT hr = m_XamlDiagnostics.as<IVisualTreeService3>()->UnadviseVisualTreeChange(this);
    if (FAILED(hr)) {
        Wh_Log(L"UnadviseVisualTreeChange failed: %08X", hr);
    }
}

bool VisualTreeWatcher::ReleaseDiagnosticsReference(InstanceHandle handle) {
    if (!m_XamlDiagnosticsTestHooks) {
        return false;
    }

    winrt::weak_ref<wf::IInspectable> weakElement;
    {
        wf::IInspectable element;
        HRESULT hr = m_XamlDiagnostics->GetIInspectableFromHandle(handle, reinterpret_cast<::IInspectable**>(winrt::put_abi(element)));
        if (SUCCEEDED(hr) && element) {
            try {
                weakElement = TryMakeWeak(element);
            } catch (...) {
                Wh_Log(L"Error %08X", winrt::to_hresult());
            }
        }
    }

    HRESULT hr = m_XamlDiagnosticsTestHooks->UnregisterInstance(handle);
    if (FAILED(hr)) {
        return false;
    }

    return weakElement && !weakElement.get();
}

HRESULT VisualTreeWatcher::OnVisualTreeChange(ParentChildRelation relation, VisualElement element, VisualMutationType mutationType) try {
    if (!g_stylerInitializedForThread) {
        return S_OK;
    }

    try {
        if (mutationType == Add) {
            const auto inspectable = FromHandle(element.Handle);
            auto elementId = GetOrCreateElementId(element.Handle, inspectable);
            auto frameworkElement = inspectable.try_as<wux::FrameworkElement>();
            if (frameworkElement) {
                if (elementId != ElementId::None) {
                    ApplyCustomizations(elementId, frameworkElement, element.Type);
                }
            }
        } else if (mutationType == Remove) {
            CleanupCustomizations(FindElementId(element.Handle));
        }
    } catch (...) {
        Wh_Log(L"Error %08X", winrt::to_hresult());
    }

    FlushDiagnosticsReleasesIfQuiet();

    if (mutationType == Add) {
        QueueDiagnosticsRelease(element.Handle);
        QueueDiagnosticsRelease(relation.Parent);
    } else if (mutationType == Remove) {
        QueueDiagnosticsRelease(element.Handle);
        ForgetElementId(element.Handle);
    }

    return S_OK;
} catch (...) {
    return S_OK;
}

HRESULT VisualTreeWatcher::OnElementStateChanged(InstanceHandle, VisualElementState, LPCWSTR) noexcept {
    return S_OK;
}

winrt::com_ptr<VisualTreeWatcher> g_visualTreeWatcher;

static constexpr CLSID CLSID_WindhawkTAP = { 0xc85d8cc7, 0x5463, 0x40e8, { 0xa4, 0x32, 0xf5, 0x91, 0x6b, 0x64, 0x27, 0xe5 } };

class WindhawkTAP : public winrt::implements<WindhawkTAP, IObjectWithSite, winrt::non_agile> {
public:
    HRESULT STDMETHODCALLTYPE SetSite(IUnknown *pUnkSite) override;
    HRESULT STDMETHODCALLTYPE GetSite(REFIID riid, void **ppvSite) noexcept override;

private:
    winrt::com_ptr<IUnknown> site;
};

HRESULT WindhawkTAP::SetSite(IUnknown *pUnkSite) try {
    if (g_visualTreeWatcher) {
        g_visualTreeWatcher->UnadviseVisualTreeChange();
        g_visualTreeWatcher = nullptr;
    }

    site.copy_from(pUnkSite);

    if (site) {
        FreeLibrary(GetCurrentModuleHandle());
        g_visualTreeWatcher = winrt::make_self<VisualTreeWatcher>(site);
    }

    return S_OK;
} catch (...) {
    HRESULT hr = winrt::to_hresult();
    Wh_Log(L"Error %08X", hr);
    return hr;
}

HRESULT WindhawkTAP::GetSite(REFIID riid, void **ppvSite) noexcept {
    return site.as(riid, ppvSite);
}

template<class T>
struct SimpleFactory : winrt::implements<SimpleFactory<T>, IClassFactory, winrt::non_agile> {
    HRESULT STDMETHODCALLTYPE CreateInstance(IUnknown* pUnkOuter, REFIID riid, void** ppvObject) override try {
        if (!pUnkOuter) {
            *ppvObject = nullptr;
            return winrt::make<T>().as(riid, ppvObject);
        } else {
            return CLASS_E_NOAGGREGATION;
        }
    } catch (...) {
        HRESULT hr = winrt::to_hresult();
        Wh_Log(L"Error %08X", hr);
        return hr;
    }

    HRESULT STDMETHODCALLTYPE LockServer(BOOL) noexcept override {
        return S_OK;
    }
};

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdll-attribute-on-redeclaration"

__declspec(dllexport)
_Use_decl_annotations_ STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv) try {
    if (rclsid == CLSID_WindhawkTAP) {
        *ppv = nullptr;
        return winrt::make<SimpleFactory<WindhawkTAP>>().as(riid, ppv);
    } else {
        return CLASS_E_CLASSNOTAVAILABLE;
    }
} catch (...) {
    HRESULT hr = winrt::to_hresult();
    Wh_Log(L"Error %08X", hr);
    return hr;
}

__declspec(dllexport)
_Use_decl_annotations_ STDAPI DllCanUnloadNow() {
    if (winrt::get_module_lock()) {
        return S_FALSE;
    } else {
        return S_OK;
    }
}

#pragma clang diagnostic pop

bool g_inInjectWindhawkTAP = false;

using PFN_INITIALIZE_XAML_DIAGNOSTICS_EX = decltype(&InitializeXamlDiagnosticsEx);

HRESULT InjectWindhawkTAP() noexcept {
    HMODULE module = GetCurrentModuleHandle();
    if (!module) {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    WCHAR location[MAX_PATH];
    switch (GetModuleFileName(module, location, ARRAYSIZE(location))) {
    case 0:
    case ARRAYSIZE(location):
        return HRESULT_FROM_WIN32(GetLastError());
    }

    const HMODULE wux(LoadLibraryEx(L"Windows.UI.Xaml.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32));
    if (!wux) [[unlikely]] {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    const auto ixde = reinterpret_cast<PFN_INITIALIZE_XAML_DIAGNOSTICS_EX>(GetProcAddress(wux, "InitializeXamlDiagnosticsEx"));
    if (!ixde) [[unlikely]] {
        return HRESULT_FROM_WIN32(GetLastError());
    }

    g_inInjectWindhawkTAP = true;

    HRESULT hr;
    for (int i = 0; i < 10000; i++) {
        WCHAR connectionName[256];
        wsprintf(connectionName, L"VisualDiagConnection%d", i + 1);

        hr = ixde(connectionName, GetCurrentProcessId(), L"", location, CLSID_WindhawkTAP, nullptr);
        if (hr != HRESULT_FROM_WIN32(ERROR_NOT_FOUND)) {
            break;
        }
    }

    g_inInjectWindhawkTAP = false;
    return hr;
}

template <> inline constexpr winrt::guid winrt::impl::guid_v<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>{
    winrt::impl::guid_v<winrt::Windows::Foundation::IPropertyValue>
};

typedef enum MY_D2D1_GAUSSIANBLUR_OPTIMIZATION {
    MY_D2D1_GAUSSIANBLUR_OPTIMIZATION_SPEED = 0,
    MY_D2D1_GAUSSIANBLUR_OPTIMIZATION_BALANCED = 1,
    MY_D2D1_GAUSSIANBLUR_OPTIMIZATION_QUALITY = 2,
    MY_D2D1_GAUSSIANBLUR_OPTIMIZATION_FORCE_DWORD = 0xffffffff
} MY_D2D1_GAUSSIANBLUR_OPTIMIZATION;

class XamlBlurBrush : public Media::XamlCompositionBrushBaseT<XamlBlurBrush> {
public:
    XamlBlurBrush(UIElement element,
                  float blurAmount,
                  winrt::Windows::UI::Color tint,
                  std::optional<uint8_t> tintOpacity,
                  winrt::hstring tintThemeResourceKey,
                  std::optional<float> tintLuminosityOpacity,
                  std::optional<float> tintSaturation,
                  std::optional<float> noiseOpacity,
                  std::optional<float> noiseDensity,
                  std::optional<winrt::Windows::UI::Color> fallbackColor,
                  winrt::hstring fallbackThemeResourceKey);
    ~XamlBlurBrush();

    void OnConnected();
    void OnDisconnected();

private:
    void RefreshThemeTint();
    void RefreshFallbackColor();
    bool ShouldUseFallback() const;
    void RefreshBrush();
    wuc::CompositionBrush CreateEffectBrush();
    wuc::CompositionBrush CreateFallbackBrush();

    wuc::Compositor m_compositor;
    float m_blurAmount;
    winrt::Windows::UI::Color m_tint;
    std::optional<uint8_t> m_tintOpacity;
    winrt::hstring m_tintThemeResourceKey;
    std::optional<float> m_tintLuminosityOpacity;
    std::optional<float> m_tintSaturation;
    std::optional<float> m_noiseOpacity;
    std::optional<float> m_noiseDensity;
    std::optional<winrt::Windows::UI::Color> m_fallbackColor;
    winrt::hstring m_fallbackThemeResourceKey;
    Media::SolidColorBrush m_proxyBrush{nullptr};
    Media::SolidColorBrush m_fallbackProxyBrush{nullptr};
    winrt::weak_ref<FrameworkElement> m_weakProxyElement;
    winrt::hstring m_proxyKey;
    winrt::hstring m_fallbackProxyKey;
    winrt::Windows::UI::ViewManagement::UISettings m_uiSettings{nullptr};
    winrt::event_token m_advancedEffectsEnabledChangedToken{};
    winrt::event_token m_energySaverStatusChangedToken{};
    winrt::Windows::System::DispatcherQueue m_dispatcher{nullptr};
    HKEY m_powerKey{nullptr};
    HANDLE m_regNotifyEvent{nullptr};
    HANDLE m_regWaitHandle{nullptr};

    static void CALLBACK OnEnergySaverRegistryChanged(PVOID context, BOOLEAN timerOrWaitFired);
};

#ifndef BUILD_WINDOWS
namespace ABI {
#endif
namespace Windows {
namespace Graphics {
namespace Effects {

typedef interface IGraphicsEffectSource IGraphicsEffectSource;
typedef interface IGraphicsEffectD2D1Interop IGraphicsEffectD2D1Interop;

typedef enum GRAPHICS_EFFECT_PROPERTY_MAPPING {
    GRAPHICS_EFFECT_PROPERTY_MAPPING_UNKNOWN,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_VECTORX,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_VECTORY,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_VECTORZ,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_VECTORW,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_RECT_TO_VECTOR4,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_RADIANS_TO_DEGREES,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_COLORMATRIX_ALPHA_MODE,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_COLOR_TO_VECTOR3,
    GRAPHICS_EFFECT_PROPERTY_MAPPING_COLOR_TO_VECTOR4
} GRAPHICS_EFFECT_PROPERTY_MAPPING;

#undef INTERFACE
#define INTERFACE IGraphicsEffectD2D1Interop
DECLARE_INTERFACE_IID_(IGraphicsEffectD2D1Interop, IUnknown, "2FC57384-A068-44D7-A331-30982FCF7177")
{
    STDMETHOD(GetEffectId)(_Out_ GUID * id) PURE;
    STDMETHOD(GetNamedPropertyMapping)(LPCWSTR name, _Out_ UINT * index, _Out_ GRAPHICS_EFFECT_PROPERTY_MAPPING * mapping) PURE;
    STDMETHOD(GetPropertyCount)(_Out_ UINT * count) PURE;
    STDMETHOD(GetProperty)(UINT index, _Outptr_ winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue> ** value) PURE;
    STDMETHOD(GetSource)(UINT index, _Outptr_ IGraphicsEffectSource ** source) PURE;
    STDMETHOD(GetSourceCount)(_Out_ UINT * count) PURE;
};

} // namespace Effects
} // namespace Graphics
} // namespace Windows
#ifndef BUILD_WINDOWS
} // namespace ABI
#endif

template <> inline constexpr winrt::guid winrt::impl::guid_v<ABI::Windows::Graphics::Effects::IGraphicsEffectD2D1Interop>{
    0x2FC57384, 0xA068, 0x44D7, { 0xA3, 0x31, 0x30, 0x98, 0x2F, 0xCF, 0x71, 0x77 }
};

struct CompositeEffect : winrt::implements<CompositeEffect, wge::IGraphicsEffect, wge::IGraphicsEffectSource, awge::IGraphicsEffectD2D1Interop> {
    HRESULT STDMETHODCALLTYPE GetEffectId(GUID* id) noexcept override {
        if (!id) return E_INVALIDARG;
        *id = CLSID_D2D1Composite;
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE GetNamedPropertyMapping(LPCWSTR name, UINT* index, awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept override {
        if (!index || !mapping) return E_INVALIDARG;
        if (std::wstring_view(name) == L"Mode") {
            *index = D2D1_COMPOSITE_PROP_MODE;
            *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;
            return S_OK;
        }
        return E_INVALIDARG;
    }
    HRESULT STDMETHODCALLTYPE GetPropertyCount(UINT* count) noexcept override {
        if (!count) return E_INVALIDARG;
        *count = 1;
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE GetProperty(UINT index, winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>** value) noexcept override try {
        if (!value) return E_INVALIDARG;
        if (index == D2D1_COMPOSITE_PROP_MODE) {
            *value = wf::PropertyValue::CreateUInt32((UINT32)Mode).as<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>().detach();
            return S_OK;
        }
        return E_BOUNDS;
    } catch (...) { return winrt::to_hresult(); }
    HRESULT STDMETHODCALLTYPE GetSource(UINT index, awge::IGraphicsEffectSource** source) noexcept override try {
        if (!source) return E_INVALIDARG;
        winrt::copy_to_abi(Sources.at(index), *reinterpret_cast<void**>(source));
        return S_OK;
    } catch (...) { return winrt::to_hresult(); }
    HRESULT STDMETHODCALLTYPE GetSourceCount(UINT* count) noexcept override {
        if (!count) return E_INVALIDARG;
        *count = static_cast<UINT>(Sources.size());
        return S_OK;
    }
    winrt::hstring Name() { return m_name; }
    void Name(winrt::hstring name) { m_name = name; }

    std::vector<wge::IGraphicsEffectSource> Sources;
    D2D1_COMPOSITE_MODE Mode = D2D1_COMPOSITE_MODE_SOURCE_OVER;
private:
    winrt::hstring m_name = L"CompositeEffect";
};

struct FloodEffect : winrt::implements<FloodEffect, wge::IGraphicsEffect, wge::IGraphicsEffectSource, awge::IGraphicsEffectD2D1Interop> {
    HRESULT STDMETHODCALLTYPE GetEffectId(GUID* id) noexcept override {
        if (!id) return E_INVALIDARG;
        *id = CLSID_D2D1Flood;
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE GetNamedPropertyMapping(LPCWSTR name, UINT* index, awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept override {
        if (!index || !mapping) return E_INVALIDARG;
        if (std::wstring_view(name) == L"Color") {
            *index = D2D1_FLOOD_PROP_COLOR;
            *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;
            return S_OK;
        }
        return E_INVALIDARG;
    }
    HRESULT STDMETHODCALLTYPE GetPropertyCount(UINT* count) noexcept override {
        if (!count) return E_INVALIDARG;
        *count = 1;
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE GetProperty(UINT index, winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>** value) noexcept override try {
        if (!value) return E_INVALIDARG;
        if (index == D2D1_FLOOD_PROP_COLOR) {
            *value = wf::PropertyValue::CreateSingleArray({
                Color.R / 255.0f, Color.G / 255.0f, Color.B / 255.0f, Color.A / 255.0f,
            }).as<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>().detach();
            return S_OK;
        }
        return E_BOUNDS;
    } catch (...) { return winrt::to_hresult(); }
    HRESULT STDMETHODCALLTYPE GetSource(UINT, awge::IGraphicsEffectSource** source) noexcept override {
        if (!source) return E_INVALIDARG;
        return E_BOUNDS;
    }
    HRESULT STDMETHODCALLTYPE GetSourceCount(UINT* count) noexcept override {
        if (!count) return E_INVALIDARG;
        *count = 0;
        return S_OK;
    }
    winrt::hstring Name() { return m_name; }
    void Name(winrt::hstring name) { m_name = name; }

    winrt::Windows::UI::Color Color{};
private:
    winrt::hstring m_name = L"FloodEffect";
};

struct BorderEffect : winrt::implements<BorderEffect, wge::IGraphicsEffect, wge::IGraphicsEffectSource, awge::IGraphicsEffectD2D1Interop> {
    HRESULT STDMETHODCALLTYPE GetEffectId(GUID* id) noexcept override {
        if (!id) return E_INVALIDARG;
        *id = CLSID_D2D1Border;
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE GetNamedPropertyMapping(LPCWSTR name, UINT* index, awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept override {
        if (!index || !mapping) return E_INVALIDARG;
        std::wstring_view nameView(name);
        if (nameView == L"ExtendX") {
            *index = D2D1_BORDER_PROP_EDGE_MODE_X;
            *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;
            return S_OK;
        }
        if (nameView == L"ExtendY") {
            *index = D2D1_BORDER_PROP_EDGE_MODE_Y;
            *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;
            return S_OK;
        }
        return E_INVALIDARG;
    }
    HRESULT STDMETHODCALLTYPE GetPropertyCount(UINT* count) noexcept override {
        if (!count) return E_INVALIDARG;
        *count = 2;
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE GetProperty(UINT index, winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>** value) noexcept override try {
        if (!value) return E_INVALIDARG;
        switch (index) {
            case D2D1_BORDER_PROP_EDGE_MODE_X:
                *value = wf::PropertyValue::CreateUInt32((UINT32)ExtendX).as<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>().detach();
                break;
            case D2D1_BORDER_PROP_EDGE_MODE_Y:
                *value = wf::PropertyValue::CreateUInt32((UINT32)ExtendY).as<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>().detach();
                break;
            default: return E_BOUNDS;
        }
        return S_OK;
    } catch (...) { return winrt::to_hresult(); }
    HRESULT STDMETHODCALLTYPE GetSource(UINT index, awge::IGraphicsEffectSource** source) noexcept override {
        if (!source) return E_INVALIDARG;
        if (index == 0 && Source) {
            winrt::copy_to_abi(Source, *reinterpret_cast<void**>(source));
            return S_OK;
        }
        return E_BOUNDS;
    }
    HRESULT STDMETHODCALLTYPE GetSourceCount(UINT* count) noexcept override {
        if (!count) return E_INVALIDARG;
        *count = 1;
        return S_OK;
    }
    winrt::hstring Name() { return m_name; }
    void Name(winrt::hstring name) { m_name = name; }

    wge::IGraphicsEffectSource Source{nullptr};
    D2D1_BORDER_EDGE_MODE ExtendX = D2D1_BORDER_EDGE_MODE_WRAP;
    D2D1_BORDER_EDGE_MODE ExtendY = D2D1_BORDER_EDGE_MODE_WRAP;
private:
    winrt::hstring m_name = L"BorderEffect";
};

struct GaussianBlurEffect : winrt::implements<GaussianBlurEffect, wge::IGraphicsEffect, wge::IGraphicsEffectSource, awge::IGraphicsEffectD2D1Interop> {
    HRESULT STDMETHODCALLTYPE GetEffectId(GUID* id) noexcept override {
        if (!id) return E_INVALIDARG;
        *id = CLSID_D2D1GaussianBlur;
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE GetNamedPropertyMapping(LPCWSTR name, UINT* index, awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept override {
        if (!index || !mapping) return E_INVALIDARG;
        std::wstring_view nameView(name);
        if (nameView == L"BlurAmount") {
            *index = D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION;
            *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;
            return S_OK;
        } else if (nameView == L"Optimization") {
            *index = D2D1_GAUSSIANBLUR_PROP_OPTIMIZATION;
            *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;
            return S_OK;
        } else if (nameView == L"BorderMode") {
            *index = D2D1_GAUSSIANBLUR_PROP_BORDER_MODE;
            *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;
            return S_OK;
        }
        return E_INVALIDARG;
    }
    HRESULT STDMETHODCALLTYPE GetPropertyCount(UINT* count) noexcept override {
        if (!count) return E_INVALIDARG;
        *count = 3;
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE GetProperty(UINT index, winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>** value) noexcept override try {
        if (!value) return E_INVALIDARG;
        switch (index) {
            case D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION:
                *value = wf::PropertyValue::CreateSingle(BlurAmount).as<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>().detach();
                break;
            case D2D1_GAUSSIANBLUR_PROP_OPTIMIZATION:
                *value = wf::PropertyValue::CreateUInt32((UINT32)Optimization).as<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>().detach();
                break;
            case D2D1_GAUSSIANBLUR_PROP_BORDER_MODE:
                *value = wf::PropertyValue::CreateUInt32((UINT32)BorderMode).as<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>().detach();
                break;
            default: return E_BOUNDS;
        }
        return S_OK;
    } catch (...) { return winrt::to_hresult(); }
    HRESULT STDMETHODCALLTYPE GetSource(UINT index, awge::IGraphicsEffectSource** source) noexcept override {
        if (!source) return E_INVALIDARG;
        if (index == 0) {
            winrt::copy_to_abi(Source, *reinterpret_cast<void**>(source));
            return S_OK;
        }
        return E_BOUNDS;
    }
    HRESULT STDMETHODCALLTYPE GetSourceCount(UINT* count) noexcept override {
        if (!count) return E_INVALIDARG;
        *count = 1;
        return S_OK;
    }
    winrt::hstring Name() { return m_name; }
    void Name(winrt::hstring name) { m_name = name; }

    wge::IGraphicsEffectSource Source;
    float BlurAmount = 3.0f;
    MY_D2D1_GAUSSIANBLUR_OPTIMIZATION Optimization = MY_D2D1_GAUSSIANBLUR_OPTIMIZATION_BALANCED;
    D2D1_BORDER_MODE BorderMode = D2D1_BORDER_MODE_SOFT;
private:
    winrt::hstring m_name = L"GaussianBlurEffect";
};

struct ColorMatrixEffect : winrt::implements<ColorMatrixEffect, wge::IGraphicsEffect, wge::IGraphicsEffectSource, awge::IGraphicsEffectD2D1Interop> {
    HRESULT STDMETHODCALLTYPE GetEffectId(GUID* id) noexcept override {
        if (!id) return E_INVALIDARG;
        *id = CLSID_D2D1ColorMatrix;
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE GetNamedPropertyMapping(LPCWSTR name, UINT* index, awge::GRAPHICS_EFFECT_PROPERTY_MAPPING* mapping) noexcept override {
        if (!index || !mapping) return E_INVALIDARG;
        std::wstring_view nameView(name);
        if (nameView == L"ColorMatrix") {
            *index = D2D1_COLORMATRIX_PROP_COLOR_MATRIX;
            *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;
            return S_OK;
        }
        if (nameView == L"AlphaMode") {
            *index = D2D1_COLORMATRIX_PROP_ALPHA_MODE;
            *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;
            return S_OK;
        }
        if (nameView == L"ClampOutput") {
            *index = D2D1_COLORMATRIX_PROP_CLAMP_OUTPUT;
            *mapping = awge::GRAPHICS_EFFECT_PROPERTY_MAPPING_DIRECT;
            return S_OK;
        }
        return E_INVALIDARG;
    }
    HRESULT STDMETHODCALLTYPE GetPropertyCount(UINT* count) noexcept override {
        if (!count) return E_INVALIDARG;
        *count = 3;
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE GetProperty(UINT index, winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>** value) noexcept override try {
        if (!value) return E_INVALIDARG;
        switch (index) {
            case D2D1_COLORMATRIX_PROP_COLOR_MATRIX:
                *value = wf::PropertyValue::CreateSingleArray(
                    winrt::array_view<const float>(Matrix, Matrix + 20)
                ).as<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>().detach();
                break;
            case D2D1_COLORMATRIX_PROP_ALPHA_MODE:
                *value = wf::PropertyValue::CreateUInt32(AlphaMode).as<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>().detach();
                break;
            case D2D1_COLORMATRIX_PROP_CLAMP_OUTPUT:
                *value = wf::PropertyValue::CreateBoolean(ClampOutput).as<winrt::impl::abi_t<winrt::Windows::Foundation::IPropertyValue>>().detach();
                break;
            default: return E_BOUNDS;
        }
        return S_OK;
    } catch (...) { return winrt::to_hresult(); }
    HRESULT STDMETHODCALLTYPE GetSource(UINT index, awge::IGraphicsEffectSource** source) noexcept override {
        if (!source) return E_INVALIDARG;
        if (index == 0 && Source) {
            winrt::copy_to_abi(Source, *reinterpret_cast<void**>(source));
            return S_OK;
        }
        return E_BOUNDS;
    }
    HRESULT STDMETHODCALLTYPE GetSourceCount(UINT* count) noexcept override {
        if (!count) return E_INVALIDARG;
        *count = 1;
        return S_OK;
    }
    winrt::hstring Name() { return m_name; }
    void Name(winrt::hstring name) { m_name = name; }

    wge::IGraphicsEffectSource Source{nullptr};
    float Matrix[20] = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1,
        0, 0, 0, 0,
    };
    uint32_t AlphaMode = D2D1_COLORMATRIX_ALPHA_MODE_PREMULTIPLIED;
    bool ClampOutput = false;
private:
    winrt::hstring m_name = L"ColorMatrixEffect";
};

XamlBlurBrush::XamlBlurBrush(UIElement element,
                             float blurAmount,
                             winrt::Windows::UI::Color tint,
                             std::optional<uint8_t> tintOpacity,
                             winrt::hstring tintThemeResourceKey,
                             std::optional<float> tintLuminosityOpacity,
                             std::optional<float> tintSaturation,
                             std::optional<float> noiseOpacity,
                             std::optional<float> noiseDensity,
                             std::optional<winrt::Windows::UI::Color> fallbackColor,
                             winrt::hstring fallbackThemeResourceKey) :
    m_compositor(wuxh::ElementCompositionPreview::GetElementVisual(element).Compositor()),
    m_blurAmount(blurAmount),
    m_tint(tint),
    m_tintOpacity(tintOpacity),
    m_tintThemeResourceKey(std::move(tintThemeResourceKey)),
    m_tintLuminosityOpacity(tintLuminosityOpacity),
    m_tintSaturation(tintSaturation),
    m_noiseOpacity(noiseOpacity),
    m_noiseDensity(noiseDensity),
    m_fallbackColor(fallbackColor),
    m_fallbackThemeResourceKey(std::move(fallbackThemeResourceKey)) {
    auto fe = element.try_as<FrameworkElement>();

    auto createProxy = [&](winrt::hstring const& themeResourceKey) -> Media::SolidColorBrush {
        if (!fe) return nullptr;
        std::wstring xaml =
            L"<SolidColorBrush xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\" Color=\"{ThemeResource " +
            std::wstring(themeResourceKey) + L"}\"/>";
        try {
            return Markup::XamlReader::Load(winrt::hstring(xaml)).try_as<Media::SolidColorBrush>();
        } catch (winrt::hresult_error const& ex) {
            Wh_Log(L"Failed to create proxy brush: %08X", ex.code());
            return nullptr;
        }
    };

    static std::atomic<uint64_t> s_proxyCounter{0};

    if (!m_tintThemeResourceKey.empty()) {
        if (auto proxyBrush = createProxy(m_tintThemeResourceKey)) {
            auto proxyKey = winrt::hstring(L"__WhBlurProxy_" + std::to_wstring(++s_proxyCounter));
            fe.Resources().Insert(winrt::box_value(proxyKey), proxyBrush);
            m_proxyBrush = proxyBrush;
            m_weakProxyElement = winrt::make_weak(fe);
            m_proxyKey = proxyKey;
        }

        if (m_proxyBrush) {
            m_proxyBrush.RegisterPropertyChangedCallback(
                Media::SolidColorBrush::ColorProperty(),
                [weakThis = get_weak()](auto&&, auto&&) {
                    if (auto self = weakThis.get()) {
                        self->RefreshBrush();
                    }
                });
        }
    }

    if (!m_fallbackThemeResourceKey.empty()) {
        if (auto proxyBrush = createProxy(m_fallbackThemeResourceKey)) {
            auto proxyKey = winrt::hstring(L"__WhBlurFallbackProxy_" + std::to_wstring(++s_proxyCounter));
            fe.Resources().Insert(winrt::box_value(proxyKey), proxyBrush);
            m_fallbackProxyBrush = proxyBrush;
            if (!m_weakProxyElement.get()) {
                m_weakProxyElement = winrt::make_weak(fe);
            }
            m_fallbackProxyKey = proxyKey;
        }

        if (m_fallbackProxyBrush) {
            m_fallbackProxyBrush.RegisterPropertyChangedCallback(
                Media::SolidColorBrush::ColorProperty(),
                [weakThis = get_weak()](auto&&, auto&&) {
                    if (auto self = weakThis.get()) {
                        self->RefreshBrush();
                    }
                });
        }
    }

    if (m_fallbackColor || !m_fallbackThemeResourceKey.empty()) {
        m_dispatcher = winrt::Windows::System::DispatcherQueue::GetForCurrentThread();

        try {
            m_uiSettings = winrt::Windows::UI::ViewManagement::UISettings();
            auto dispatcher = m_dispatcher;
            m_advancedEffectsEnabledChangedToken =
                m_uiSettings.AdvancedEffectsEnabledChanged(
                    [weakThis = get_weak(), dispatcher](auto&&, auto&&) {
                        dispatcher.TryEnqueue([weakThis] {
                            if (auto self = weakThis.get()) {
                                self->RefreshBrush();
                            }
                        });
                    });
            m_energySaverStatusChangedToken =
                winrt::Windows::System::Power::PowerManager::EnergySaverStatusChanged(
                    [weakThis = get_weak(), dispatcher](auto&&, auto&&) {
                        dispatcher.TryEnqueue([weakThis] {
                            if (auto self = weakThis.get()) {
                                self->RefreshBrush();
                            }
                        });
                    });
        } catch (winrt::hresult_error const& ex) {
            Wh_Log(L"Failed to register fallback state listeners: %08X", ex.code());
        }

        LONG regStatus = RegOpenKeyExW(
            HKEY_LOCAL_MACHINE,
            L"SYSTEM\\CurrentControlSet\\Control\\Power", 0, KEY_NOTIFY,
            &m_powerKey);
        if (regStatus == ERROR_SUCCESS) {
            m_regNotifyEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
            if (m_regNotifyEvent) {
                regStatus = RegNotifyChangeKeyValue(m_powerKey, FALSE,
                                                   REG_NOTIFY_CHANGE_LAST_SET,
                                                   m_regNotifyEvent, TRUE);
                if (regStatus == ERROR_SUCCESS) {
                    if (!RegisterWaitForSingleObject(
                            &m_regWaitHandle, m_regNotifyEvent,
                            OnEnergySaverRegistryChanged, this, INFINITE,
                            WT_EXECUTEINWAITTHREAD)) {
                        m_regWaitHandle = nullptr;
                    }
                } else {
                    CloseHandle(m_regNotifyEvent);
                    m_regNotifyEvent = nullptr;
                    RegCloseKey(m_powerKey);
                    m_powerKey = nullptr;
                }
            } else {
                RegCloseKey(m_powerKey);
                m_powerKey = nullptr;
            }
        }
    }
}

void CALLBACK XamlBlurBrush::OnEnergySaverRegistryChanged(PVOID context, BOOLEAN) {
    auto* self = static_cast<XamlBlurBrush*>(context);
    if (self->m_powerKey && self->m_regNotifyEvent) {
        RegNotifyChangeKeyValue(self->m_powerKey, FALSE,
                                REG_NOTIFY_CHANGE_LAST_SET,
                                self->m_regNotifyEvent, TRUE);
    }
    if (self->m_dispatcher) {
        auto weakThis = self->get_weak();
        self->m_dispatcher.TryEnqueue([weakThis] {
            if (auto strongThis = weakThis.get()) {
                strongThis->RefreshBrush();
            }
        });
    }
}

XamlBlurBrush::~XamlBlurBrush() {
    if (m_regWaitHandle) {
        UnregisterWaitEx(m_regWaitHandle, INVALID_HANDLE_VALUE);
        m_regWaitHandle = nullptr;
    }
    if (m_regNotifyEvent) {
        CloseHandle(m_regNotifyEvent);
        m_regNotifyEvent = nullptr;
    }
    if (m_powerKey) {
        RegCloseKey(m_powerKey);
        m_powerKey = nullptr;
    }

    if (m_uiSettings && m_advancedEffectsEnabledChangedToken.value) {
        try {
            m_uiSettings.AdvancedEffectsEnabledChanged(m_advancedEffectsEnabledChangedToken);
        } catch (...) {}
    }

    if (m_energySaverStatusChangedToken.value) {
        try {
            winrt::Windows::System::Power::PowerManager::EnergySaverStatusChanged(m_energySaverStatusChangedToken);
        } catch (...) {}
    }

    if (auto element = m_weakProxyElement.get()) {
        try {
            if (!m_proxyKey.empty()) {
                element.Resources().Remove(winrt::box_value(m_proxyKey));
            }
            if (!m_fallbackProxyKey.empty()) {
                element.Resources().Remove(winrt::box_value(m_fallbackProxyKey));
            }
        } catch (...) {}
    }
}

void XamlBlurBrush::OnConnected() {
    if (!CompositionBrush()) {
        RefreshThemeTint();
        RefreshFallbackColor();
        CompositionBrush(ShouldUseFallback() ? CreateFallbackBrush() : CreateEffectBrush());
    }
}

wuc::CompositionBrush XamlBlurBrush::CreateFallbackBrush() {
    return m_compositor.CreateColorBrush(m_fallbackColor.value_or(m_tint));
}

winrt::Windows::Storage::Streams::IRandomAccessStream CreateNoiseStream(float density) {
    thread_local float cachedDensity = std::numeric_limits<float>::quiet_NaN();
    thread_local winrt::Windows::Storage::Streams::InMemoryRandomAccessStream cachedStream{nullptr};

    if (density == cachedDensity && cachedStream) {
        return cachedStream.CloneStream();
    }

    constexpr int kSize = 256;
    constexpr DWORD kBpp = 32;
    constexpr DWORD rowSize = kSize * (kBpp / 8);
    constexpr DWORD dataSize = rowSize * kSize;

    BITMAPFILEHEADER fileHeader{
        .bfType = 0x4D42,
        .bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + dataSize,
        .bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER),
    };

    BITMAPINFOHEADER infoHeader{
        .biSize = sizeof(BITMAPINFOHEADER),
        .biWidth = kSize,
        .biHeight = kSize,
        .biPlanes = 1,
        .biBitCount = kBpp,
        .biSizeImage = dataSize,
    };

    std::vector<uint8_t> pixels(dataSize);

    float safeDensity = std::clamp(density, 0.001f, 1.0f);
    float exponent = 1.0f / safeDensity;

    uint8_t lut[256];
    for (int i = 0; i < 256; i++) {
        lut[i] = static_cast<uint8_t>(std::pow(i / 255.0f, exponent) * 255.0f);
    }

    std::mt19937 rng(0);
    std::uniform_int_distribution<int> dist(0, 255);

    for (size_t i = 0; i < pixels.size(); i += 4) {
        uint8_t gray = lut[dist(rng)];
        pixels[i] = gray;
        pixels[i + 1] = gray;
        pixels[i + 2] = gray;
        pixels[i + 3] = 255;
    }

    winrt::Windows::Storage::Streams::InMemoryRandomAccessStream stream;
    winrt::Windows::Storage::Streams::DataWriter writer(stream);
    writer.WriteBytes(winrt::array_view<const uint8_t>(reinterpret_cast<const uint8_t*>(&fileHeader), sizeof(fileHeader)));
    writer.WriteBytes(winrt::array_view<const uint8_t>(reinterpret_cast<const uint8_t*>(&infoHeader), sizeof(infoHeader)));
    writer.WriteBytes(pixels);
    writer.StoreAsync().get();
    writer.DetachStream();

    cachedStream = std::move(stream);
    cachedDensity = density;

    return cachedStream.CloneStream();
}

wuc::CompositionBrush XamlBlurBrush::CreateEffectBrush() {
    auto backdropBrush = m_compositor.CreateBackdropBrush();

    constexpr float kLumaR = 0.2126f;
    constexpr float kLumaG = 0.7152f;
    constexpr float kLumaB = 0.0722f;

    auto blurEffect = winrt::make_self<GaussianBlurEffect>();
    blurEffect->Source = wuc::CompositionEffectSourceParameter(L"backdrop");
    blurEffect->BlurAmount = m_blurAmount;
    blurEffect->Name(L"BlurEffect");

    wge::IGraphicsEffectSource topOfStack = *blurEffect;

    if (m_tintSaturation && *m_tintSaturation != 1.0f) {
        float s = std::max(*m_tintSaturation, 0.0f);
        float invS = 1.0f - s;

        auto satMatrix = winrt::make_self<ColorMatrixEffect>();
        satMatrix->Source = topOfStack;

        auto& m = satMatrix->Matrix;
        m[0]  = invS * kLumaR + s; m[1]  = invS * kLumaR;     m[2]  = invS * kLumaR;     m[3]  = 0.0f;
        m[4]  = invS * kLumaG;     m[5]  = invS * kLumaG + s; m[6]  = invS * kLumaG;     m[7]  = 0.0f;
        m[8]  = invS * kLumaB;     m[9]  = invS * kLumaB;     m[10] = invS * kLumaB + s; m[11] = 0.0f;
        m[12] = 0.0f;              m[13] = 0.0f;              m[14] = 0.0f;              m[15] = 1.0f;

        satMatrix->Name(L"SaturationEffect");
        topOfStack = *satMatrix;
    }

    if (m_tintLuminosityOpacity && *m_tintLuminosityOpacity > 0.0f) {
        float op = std::clamp(*m_tintLuminosityOpacity, 0.0f, 1.0f);
        float tintLum = (m_tint.R / 255.0f) * kLumaR + (m_tint.G / 255.0f) * kLumaG + (m_tint.B / 255.0f) * kLumaB;

        auto lumMatrix = winrt::make_self<ColorMatrixEffect>();
        lumMatrix->Source = topOfStack;

        auto& m = lumMatrix->Matrix;
        m[0]  = 1.0f - (kLumaR * op); m[1]  = -(kLumaR * op);       m[2]  = -(kLumaR * op);       m[3]  = 0.0f;
        m[4]  = -(kLumaG * op);       m[5]  = 1.0f - (kLumaG * op); m[6]  = -(kLumaG * op);       m[7]  = 0.0f;
        m[8]  = -(kLumaB * op);       m[9]  = -(kLumaB * op);       m[10] = 1.0f - (kLumaB * op); m[11] = 0.0f;
        m[12] = 0.0f;                 m[13] = 0.0f;                 m[14] = 0.0f;                 m[15] = 1.0f;
        m[16] = tintLum * op;         m[17] = tintLum * op;         m[18] = tintLum * op;         m[19] = 0.0f;

        lumMatrix->Name(L"LuminosityBlend");
        topOfStack = *lumMatrix;
    }

    wuc::CompositionSurfaceBrush noiseBrush{nullptr};
    if (m_noiseOpacity && *m_noiseOpacity > 0.0f) {
        float density = m_noiseDensity.value_or(1.0f);
        auto stream = CreateNoiseStream(density);
        auto surface = Media::LoadedImageSurface::StartLoadFromStream(stream);
        noiseBrush = m_compositor.CreateSurfaceBrush(surface);
        noiseBrush.Stretch(wuc::CompositionStretch::None);

        auto borderEffect = winrt::make_self<BorderEffect>();
        borderEffect->Source = wuc::CompositionEffectSourceParameter(L"NoiseSource");

        float nOp = std::clamp(*m_noiseOpacity, 0.0f, 1.0f);

        auto opacityEffect = winrt::make_self<ColorMatrixEffect>();
        opacityEffect->Source = *borderEffect;
        opacityEffect->Matrix[0] = nOp;
        opacityEffect->Matrix[5] = nOp;
        opacityEffect->Matrix[10] = nOp;
        opacityEffect->Matrix[15] = nOp;
        opacityEffect->Name(L"NoiseOpacityEffect");

        auto noiseComposite = winrt::make_self<CompositeEffect>();
        noiseComposite->Mode = D2D1_COMPOSITE_MODE_SOURCE_OVER;
        noiseComposite->Sources.push_back(topOfStack);
        noiseComposite->Sources.push_back(*opacityEffect);
        noiseComposite->Name(L"NoiseComposite");
        topOfStack = *noiseComposite;
    }

    auto floodEffect = winrt::make_self<FloodEffect>();
    floodEffect->Color = m_tint;
    floodEffect->Name(L"FloodEffect");

    auto compositeEffect = winrt::make_self<CompositeEffect>();
    compositeEffect->Mode = D2D1_COMPOSITE_MODE_SOURCE_OVER;
    compositeEffect->Sources.push_back(topOfStack);
    compositeEffect->Sources.push_back(*floodEffect);

    auto factory = m_compositor.CreateEffectFactory(*compositeEffect);
    auto brush = factory.CreateBrush();

    brush.SetSourceParameter(L"backdrop", backdropBrush);

    if (noiseBrush) {
        brush.SetSourceParameter(L"NoiseSource", noiseBrush);
    }

    return brush;
}

void XamlBlurBrush::OnDisconnected() {
    if (const auto brush = CompositionBrush()) {
        brush.Close();
        CompositionBrush(nullptr);
    }
}

void XamlBlurBrush::RefreshThemeTint() {
    if (!m_proxyBrush) return;
    m_tint = m_proxyBrush.Color();
    if (m_tintOpacity) m_tint.A = *m_tintOpacity;
}

void XamlBlurBrush::RefreshFallbackColor() {
    if (!m_fallbackProxyBrush) return;
    m_fallbackColor = m_fallbackProxyBrush.Color();
}

bool XamlBlurBrush::ShouldUseFallback() const {
    if (!m_fallbackColor && m_fallbackThemeResourceKey.empty()) return false;

    bool energySaverActive = false;
    HKEY key{};
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SYSTEM\\CurrentControlSet\\Control\\Power", 0, KEY_QUERY_VALUE, &key) == ERROR_SUCCESS) {
        DWORD value = 0, type = 0, size = sizeof(value);
        if (RegQueryValueExW(key, L"EnergySaverState", nullptr, &type, reinterpret_cast<LPBYTE>(&value), &size) == ERROR_SUCCESS && type == REG_DWORD) {
            energySaverActive = (value == 1);
        }
        RegCloseKey(key);
    }

    if (!energySaverActive) {
        SYSTEM_POWER_STATUS powerStatus{};
        if (GetSystemPowerStatus(&powerStatus) && powerStatus.SystemStatusFlag != 0) {
            energySaverActive = true;
        }
    }

    bool advancedEffectsOff = false;
    if (m_uiSettings) {
        try {
            advancedEffectsOff = !m_uiSettings.AdvancedEffectsEnabled();
        } catch (...) {}
    }

    return energySaverActive || advancedEffectsOff;
}

void XamlBlurBrush::RefreshBrush() {
    if (const auto brush = CompositionBrush()) {
        brush.Close();
        CompositionBrush(nullptr);
        OnConnected();
    }
}

// ----- REMOTE IMAGE CACHING & DOWNLOAD ENGINE -----

struct TrackedImage {
    winrt::weak_ref<DependencyObject> target;
    DependencyProperty sourceProperty{nullptr};
    winrt::Windows::Foundation::Uri uri{nullptr};
    std::wstring url;
    std::filesystem::path cachePath;

    int32_t decodePixelWidth = 0;
    int32_t decodePixelHeight = 0;
    Media::Imaging::DecodePixelType decodePixelType =
        Media::Imaging::DecodePixelType::Physical;
    Media::Imaging::BitmapCreateOptions createOptions =
        Media::Imaging::BitmapCreateOptions::None;
    bool autoPlay = true;

    Media::ImageBrush::ImageFailed_revoker brushImageFailedRevoker;
    Media::ImageBrush::ImageOpened_revoker brushImageOpenedRevoker;
    Controls::Image::ImageFailed_revoker elementImageFailedRevoker;
    Controls::Image::ImageOpened_revoker elementImageOpenedRevoker;

    bool loaded = false;
    bool usingCache = false;

    ULONGLONG lastRetryTick = 0;
    int retryCount = 0;
};

struct TrackedImagesForThread {
    std::list<std::shared_ptr<TrackedImage>> images;
    winrt::Windows::System::DispatcherQueue dispatcher{nullptr};
    winrt::Windows::System::DispatcherQueueTimer retryTimer{nullptr};
    winrt::Windows::System::DispatcherQueueTimer::Tick_revoker retryTimerTickRevoker;
    ULONGLONG retryDueTick = 0;
};

thread_local TrackedImagesForThread g_trackedImagesForThread;
thread_local std::unordered_map<std::wstring, winrt::Windows::Foundation::Uri> g_imageCacheUriRemotes;

constexpr DWORD kNetworkChangeDebounceMs = 2000;
constexpr ULONGLONG kImageRetryBaseDelayMs = 5000;
constexpr int kImageRetryMaxBackoffShift = 6;
constexpr ULONGLONG kImageRetryMaxDelayMs = kImageRetryBaseDelayMs << kImageRetryMaxBackoffShift;
constexpr int kImageRetryMaxCount = 20;

std::mutex g_imageRetryMutex;
bool g_imageRetryActive;
std::vector<winrt::weak_ref<winrt::Windows::System::DispatcherQueue>> g_imageRetryDispatchers;
winrt::event_token g_networkStatusChangedToken;
bool g_networkStatusChangedRegistering;
size_t g_imageRetryPendingCallbacks;
std::condition_variable g_imageRetryPendingCallbacksCv;

constexpr ULONGLONG kImageCacheRefreshIntervalMs = 7ULL * 24 * 60 * 60 * 1000;
constexpr ULONGLONG kImageCacheMaxUnusedMs = 30ULL * 24 * 60 * 60 * 1000;

std::mutex g_imageDownloadMutex;
std::list<std::wstring> g_imageDownloadQueue;
std::unordered_set<std::wstring> g_imageDownloadUrls;
std::unordered_set<std::wstring> g_imageCacheRejectedUrls;
PTP_WORK g_imageDownloadWork;
bool g_imageDownloadRunning;
bool g_imageDownloadStopping;

bool HasInternetAccess() {
    try {
        auto profile = winrt::Windows::Networking::Connectivity::
            NetworkInformation::GetInternetConnectionProfile();
        return profile && profile.GetNetworkConnectivityLevel() ==
                              winrt::Windows::Networking::Connectivity::
                                  NetworkConnectivityLevel::InternetAccess;
    } catch (winrt::hresult_error const& ex) {
        Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
        return true;
    }
}

const std::filesystem::path& GetImageCacheDir() {
    static const std::filesystem::path dir = []() -> std::filesystem::path {
        WCHAR storagePathBuffer[MAX_PATH];
        if (!Wh_GetModStoragePath(storagePathBuffer,
                                  ARRAYSIZE(storagePathBuffer))) {
            Wh_Log(L"Wh_GetModStoragePath failed");
            return std::filesystem::path();
        }

        auto path = std::filesystem::path{storagePathBuffer} / L"images";

        std::error_code ec;
        std::filesystem::create_directories(path, ec);
        if (!std::filesystem::is_directory(path, ec)) {
            Wh_Log(L"Failed to create %s", path.c_str());
            return std::filesystem::path();
        }

        return path;
    }();

    return dir;
}

std::filesystem::path ImageCachePath(std::wstring_view url) {
    const auto& cacheDir = GetImageCacheDir();
    if (cacheDir.empty()) {
        return std::filesystem::path();
    }

    uint64_t hash = 14695981039346656037ULL;
    for (wchar_t c : url) {
        hash ^= (uint16_t)c;
        hash *= 1099511628211ULL;
    }

    WCHAR hashString[17];
    swprintf_s(hashString, L"%016llx", hash);

    std::wstring name = hashString;

    auto urlPath = url.substr(0, url.find_first_of(L"?#"));
    auto extension = std::filesystem::path(urlPath).extension().native();
    if (extension.length() >= 2 && extension.length() <= 5 &&
        std::all_of(extension.begin() + 1, extension.end(), [](wchar_t c) {
            return (c >= L'a' && c <= L'z') || (c >= L'A' && c <= L'Z') ||
                   (c >= L'0' && c <= L'9');
        })) {
        name += extension;
    }

    return cacheDir / name;
}

winrt::Windows::Foundation::Uri ImageCacheFileUri(const std::filesystem::path& path) {
    std::wstring uri(path.native().size() * 3 + 16, L'\0');

    DWORD uriLength = (DWORD)uri.size();
    HRESULT hr = UrlCreateFromPath(path.c_str(), uri.data(), &uriLength, 0);
    if (FAILED(hr)) {
        Wh_Log(L"UrlCreateFromPath returned 0x%08X", hr);
        return nullptr;
    }

    uri.resize(uriLength);

    try {
        return winrt::Windows::Foundation::Uri(uri);
    } catch (winrt::hresult_error const& ex) {
        Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
        return nullptr;
    }
}

ULONGLONG FileAgeMs(std::filesystem::file_time_type writeTime) {
    auto age = std::filesystem::file_time_type::clock::now() - writeTime;
    if (age.count() <= 0) return 0;
    return std::chrono::duration_cast<std::chrono::milliseconds>(age).count();
}

std::optional<ULONGLONG> FileAgeMs(const std::filesystem::path& path) {
    std::error_code ec;
    auto writeTime = std::filesystem::last_write_time(path, ec);
    if (ec) return std::nullopt;
    return FileAgeMs(writeTime);
}

void TouchFile(const std::filesystem::path& path) {
    std::error_code ec;
    std::filesystem::last_write_time(path, std::filesystem::file_time_type::clock::now(), ec);
}

void SweepImageCache() {
    const auto& cacheDir = GetImageCacheDir();
    if (cacheDir.empty()) return;

    Wh_Log(L"Sweeping the image cache");

    try {
        std::error_code ec;
        for (const auto& entry : std::filesystem::directory_iterator(cacheDir, ec)) {
            if (!entry.is_regular_file(ec)) continue;

            auto writeTime = entry.last_write_time(ec);
            if (ec || FileAgeMs(writeTime) < kImageCacheMaxUnusedMs) continue;

            Wh_Log(L"Removing unused cached image: %s", entry.path().filename().c_str());
            std::filesystem::remove(entry.path(), ec);
        }
    } catch (const std::exception& ex) {
        Wh_Log(L"Error sweeping image cache: %S", ex.what());
    }
}

void DownloadImage(const std::wstring& url) {
    auto cachePath = ImageCachePath(url);
    if (cachePath.empty()) return;

    auto tempPath = cachePath;
    tempPath += L".tmp" + std::to_wstring(GetCurrentProcessId());

    bool succeeded = false;

    WH_GET_URL_CONTENT_OPTIONS options{
        .optionsSize = sizeof(options),
        .targetFilePath = tempPath.c_str(),
    };

    if (const WH_URL_CONTENT* urlContent = Wh_GetUrlContent(url.c_str(), &options)) {
        if (urlContent->statusCode == 200) {
            succeeded = true;
        } else {
            Wh_Log(L"Wh_GetUrlContent returned %d", urlContent->statusCode);
        }
        Wh_FreeUrlContent(urlContent);
    } else {
        Wh_Log(L"Wh_GetUrlContent failed");
    }

    std::error_code ec;

    if (succeeded) {
        auto size = std::filesystem::file_size(tempPath, ec);
        if (ec || size == 0) {
            succeeded = false;
        }
    }

    if (succeeded) {
        std::filesystem::rename(tempPath, cachePath, ec);
    }

    std::filesystem::remove(tempPath, ec);
}

void ProcessImageDownloads() {
    for (;;) {
        std::wstring url;

        {
            std::lock_guard<std::mutex> lock(g_imageDownloadMutex);

            if (g_imageDownloadStopping || g_imageDownloadQueue.empty()) {
                g_imageDownloadRunning = false;
                return;
            }

            url = std::move(g_imageDownloadQueue.front());
            g_imageDownloadQueue.pop_front();
        }

        if (url.empty()) {
            SweepImageCache();
            continue;
        }

        Wh_Log(L"Downloading image: %s", url.c_str());
        DownloadImage(url);

        std::lock_guard<std::mutex> lock(g_imageDownloadMutex);
        g_imageDownloadUrls.erase(url);
    }
}

void SubmitImageDownloadWork() {
    if (g_imageDownloadRunning) return;

    if (!g_imageDownloadWork) {
        g_imageDownloadWork =
            CreateThreadpoolWork([](PTP_CALLBACK_INSTANCE, PVOID, PTP_WORK) { ProcessImageDownloads(); },
                                 nullptr, nullptr);
        if (!g_imageDownloadWork) {
            g_imageDownloadQueue.clear();
            g_imageDownloadUrls.clear();
            return;
        }
    }

    g_imageDownloadRunning = true;
    SubmitThreadpoolWork(g_imageDownloadWork);
}

void QueueImageDownload(const std::wstring& url) {
    std::lock_guard<std::mutex> lock(g_imageDownloadMutex);
    if (g_imageDownloadStopping) return;
    if (!g_imageDownloadUrls.insert(url).second) return;

    g_imageDownloadQueue.push_back(url);
    SubmitImageDownloadWork();
}

void QueueImageCacheSweep() {
    static std::once_flag once;
    std::call_once(once, []() {
        std::lock_guard<std::mutex> lock(g_imageDownloadMutex);
        if (g_imageDownloadStopping) return;
        g_imageDownloadQueue.emplace_back();
        SubmitImageDownloadWork();
    });
}

bool IsImageCacheRejected(const std::wstring& url) {
    std::lock_guard<std::mutex> lock(g_imageDownloadMutex);
    return g_imageCacheRejectedUrls.contains(url);
}

void RejectImageCache(const std::wstring& url) {
    std::lock_guard<std::mutex> lock(g_imageDownloadMutex);
    g_imageCacheRejectedUrls.insert(url);
}

void StopImageDownloads() {
    PTP_WORK work;
    {
        std::lock_guard<std::mutex> lock(g_imageDownloadMutex);
        g_imageDownloadStopping = true;
        g_imageDownloadQueue.clear();
        g_imageDownloadUrls.clear();
        g_imageCacheRejectedUrls.clear();

        work = g_imageDownloadWork;
        g_imageDownloadWork = nullptr;
    }

    if (work) {
        WaitForThreadpoolWorkCallbacks(work, TRUE);
        CloseThreadpoolWork(work);
    }
}

winrt::Windows::Foundation::Uri ImageSourceUri(const std::shared_ptr<TrackedImage>& tracked) {
    if (!tracked->cachePath.empty() && !IsImageCacheRejected(tracked->url)) {
        if (auto age = FileAgeMs(tracked->cachePath)) {
            if (*age >= kImageCacheRefreshIntervalMs) {
                TouchFile(tracked->cachePath);
                QueueImageDownload(tracked->url);
            }

            if (auto uri = ImageCacheFileUri(tracked->cachePath)) {
                return uri;
            }
        } else {
            QueueImageDownload(tracked->url);
        }
    }

    return tracked->uri;
}

void RestoreRejectedImageSource(const std::shared_ptr<TrackedImage>& tracked,
                                Media::Imaging::BitmapImage const& bitmapImage) {
    try {
        if (bitmapImage.UriSource().Equals(tracked->uri) || !IsImageCacheRejected(tracked->url)) {
            return;
        }

        bitmapImage.UriSource(tracked->uri);
    } catch (winrt::hresult_error const& ex) {
        Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
    }
}

void StartImageRetry(const std::shared_ptr<TrackedImage>& tracked) {
    auto target = tracked->target.get();
    if (!target) return;

    tracked->lastRetryTick = GetTickCount64();
    tracked->retryCount++;

    bool wasModifying = g_elementPropertyModifying;
    g_elementPropertyModifying = true;

    try {
        auto uri = ImageSourceUri(tracked);
        tracked->usingCache = !uri.Equals(tracked->uri);

        Media::Imaging::BitmapImage retryImage;
        retryImage.CreateOptions(
            tracked->createOptions | Media::Imaging::BitmapCreateOptions::IgnoreImageCache);
        retryImage.DecodePixelType(tracked->decodePixelType);
        retryImage.DecodePixelWidth(tracked->decodePixelWidth);
        retryImage.DecodePixelHeight(tracked->decodePixelHeight);
        retryImage.AutoPlay(tracked->autoPlay);

        target.SetValue(tracked->sourceProperty, retryImage);
        retryImage.UriSource(uri);
    } catch (winrt::hresult_error const& ex) {
        Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
    }

    g_elementPropertyModifying = wasModifying;
}

ULONGLONG ImageRetryDelayMs(int retryCount) {
    return kImageRetryBaseDelayMs << std::clamp(retryCount - 1, 0, kImageRetryMaxBackoffShift);
}

void ScheduleImageLoadRetryOnCurrentThread(ULONGLONG delayMs, bool reschedule);

void RetryFailedImageLoadsOnCurrentThread() {
    if (!g_stylerInitializedForThread) return;

    auto& images = g_trackedImagesForThread.images;
    std::erase_if(images, [](const auto& tracked) { return !tracked->target.get(); });

    std::vector<std::shared_ptr<TrackedImage>> snapshot(images.begin(), images.end());
    ULONGLONG tick = GetTickCount64();
    ULONGLONG nextRoundDelay = 0;
    auto armNextRoundIn = [&nextRoundDelay](ULONGLONG delay) {
        if (!nextRoundDelay || delay < nextRoundDelay) nextRoundDelay = delay;
    };

    for (const auto& tracked : snapshot) {
        if (tracked->loaded) continue;

        ULONGLONG remaining = 0;
        if (tracked->lastRetryTick) {
            ULONGLONG sinceLastRetry = tick - tracked->lastRetryTick;
            if (sinceLastRetry >= kImageRetryMaxDelayMs) {
                tracked->retryCount = 0;
            } else {
                ULONGLONG delay = ImageRetryDelayMs(tracked->retryCount);
                if (sinceLastRetry < delay) remaining = delay - sinceLastRetry;
            }
        }

        if (tracked->retryCount >= kImageRetryMaxCount) continue;

        if (remaining) {
            armNextRoundIn(remaining);
            continue;
        }

        StartImageRetry(tracked);

        if (tracked->retryCount < kImageRetryMaxCount) {
            armNextRoundIn(ImageRetryDelayMs(tracked->retryCount));
        }
    }

    if (nextRoundDelay) {
        ScheduleImageLoadRetryOnCurrentThread(nextRoundDelay, false);
    }
}

void ScheduleImageLoadRetryOnCurrentThread(ULONGLONG delayMs, bool reschedule) {
    if (!g_stylerInitializedForThread) return;

    auto& state = g_trackedImagesForThread;
    ULONGLONG dueTick = GetTickCount64() + delayMs;

    if (!reschedule && state.retryDueTick && state.retryDueTick <= dueTick) return;

    try {
        if (!state.retryTimer) {
            if (!state.dispatcher) return;

            state.retryTimer = state.dispatcher.CreateTimer();
            state.retryTimer.IsRepeating(false);
            state.retryTimerTickRevoker = state.retryTimer.Tick(
                winrt::auto_revoke,
                [](winrt::Windows::System::DispatcherQueueTimer const&,
                   winrt::Windows::Foundation::IInspectable const&) {
                    g_trackedImagesForThread.retryDueTick = 0;
                    RetryFailedImageLoadsOnCurrentThread();
                });
        }

        state.retryTimer.Stop();
        state.retryTimer.Interval(std::chrono::milliseconds{delayMs});
        state.retryTimer.Start();
        state.retryDueTick = dueTick;
    } catch (winrt::hresult_error const& ex) {
        Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
    }
}

std::shared_ptr<void> TrackImageRetryCallback() {
    {
        std::lock_guard<std::mutex> lock(g_imageRetryMutex);
        if (!g_imageRetryActive) return nullptr;
        g_imageRetryPendingCallbacks++;
    }

    return std::shared_ptr<void>(&g_imageRetryPendingCallbacks, [](void*) {
        {
            std::lock_guard<std::mutex> lock(g_imageRetryMutex);
            g_imageRetryPendingCallbacks--;
        }
        g_imageRetryPendingCallbacksCv.notify_all();
    });
}

void ScheduleImageLoadRetryOnAllUiThreads() {
    if (!HasInternetAccess()) return;

    std::vector<winrt::Windows::System::DispatcherQueue> dispatchers;
    {
        std::lock_guard<std::mutex> lock(g_imageRetryMutex);
        if (!g_imageRetryActive) return;

        for (auto& weakDispatcher : g_imageRetryDispatchers) {
            if (auto dispatcher = weakDispatcher.get()) {
                dispatchers.push_back(dispatcher);
            }
        }

        std::erase_if(g_imageRetryDispatchers, [](const auto& weakDispatcher) {
            return !weakDispatcher.get();
        });
    }

    for (auto& dispatcher : dispatchers) {
        auto callbackRef = TrackImageRetryCallback();
        if (!callbackRef) return;

        try {
            dispatcher.TryEnqueue([callbackRef]() {
                ScheduleImageLoadRetryOnCurrentThread(kNetworkChangeDebounceMs, true);
            });
        } catch (winrt::hresult_error const& ex) {
            Wh_Log(L"Error dispatching retry %08X: %s", ex.code(), ex.message().c_str());
        }
    }
}

void OnNetworkStatusChanged(winrt::Windows::Foundation::IInspectable const&) {
    auto callbackRef = TrackImageRetryCallback();
    if (!callbackRef) return;

    ScheduleImageLoadRetryOnAllUiThreads();
}

winrt::event_token RegisterNetworkStatusChangedHandler() {
    try {
        return winrt::Windows::Networking::Connectivity::NetworkInformation::NetworkStatusChanged(OnNetworkStatusChanged);
    } catch (winrt::hresult_error const& ex) {
        Wh_Log(L"Error registering network status handler %08X: %s", ex.code(), ex.message().c_str());
        return {};
    }
}

void UnregisterNetworkStatusChangedHandler(winrt::event_token token) {
    try {
        winrt::Windows::Networking::Connectivity::NetworkInformation::NetworkStatusChanged(token);
    } catch (winrt::hresult_error const& ex) {
        Wh_Log(L"Error unregistering network status handler %08X: %s", ex.code(), ex.message().c_str());
    }
}

void StopImageLoadRetries() {
    winrt::event_token token;
    {
        std::lock_guard<std::mutex> lock(g_imageRetryMutex);
        g_imageRetryActive = false;
        token = g_networkStatusChangedToken;
        g_networkStatusChangedToken = {};
        g_imageRetryDispatchers.clear();
    }

    if (token) UnregisterNetworkStatusChangedHandler(token);

    std::unique_lock<std::mutex> lock(g_imageRetryMutex);
    g_imageRetryPendingCallbacksCv.wait(lock, [] { return g_imageRetryPendingCallbacks == 0; });
}

void StopImageLoadRetriesForCurrentThread() {
    auto dispatcher = g_trackedImagesForThread.dispatcher;
    if (!dispatcher) return;

    g_trackedImagesForThread.dispatcher = nullptr;
    winrt::event_token token;

    {
        std::lock_guard<std::mutex> lock(g_imageRetryMutex);
        std::erase_if(g_imageRetryDispatchers, [&dispatcher](const auto& weakDispatcher) {
            auto registeredDispatcher = weakDispatcher.get();
            return !registeredDispatcher || registeredDispatcher == dispatcher;
        });

        if (!g_imageRetryDispatchers.empty()) return;

        g_imageRetryActive = false;
        token = g_networkStatusChangedToken;
        g_networkStatusChangedToken = {};
    }

    if (token) UnregisterNetworkStatusChangedHandler(token);
}

void SetupImageTracking(DependencyObject const& target,
                        DependencyProperty const& sourceProperty,
                        Media::Imaging::BitmapImage const& bitmapImage,
                        winrt::Windows::Foundation::Uri const& uri) {
    auto& images = g_trackedImagesForThread.images;

    std::erase_if(images, [](const auto& tracked) { return !tracked->target.get(); });

    auto it = std::find_if(images.begin(), images.end(),
                           [&target](const auto& tracked) {
                               if (auto trackedTarget = tracked->target.get()) {
                                   return trackedTarget == target;
                               }
                               return false;
                           });

    if (it != images.end()) {
        if ((*it)->uri.Equals(uri)) {
            RestoreRejectedImageSource(*it, bitmapImage);
            (*it)->usingCache = !bitmapImage.UriSource().Equals(uri);
            return;
        }
        images.erase(it);
    }

    auto tracked = std::make_shared<TrackedImage>();
    tracked->target = winrt::make_weak(target);
    tracked->sourceProperty = sourceProperty;
    tracked->uri = uri;
    tracked->url = std::wstring(uri.RawUri());
    tracked->cachePath = ImageCachePath(tracked->url);

    if (!tracked->cachePath.empty()) {
        QueueImageCacheSweep();
    }

    try {
        tracked->decodePixelWidth = bitmapImage.DecodePixelWidth();
        tracked->decodePixelHeight = bitmapImage.DecodePixelHeight();
        tracked->decodePixelType = bitmapImage.DecodePixelType();
        tracked->createOptions = bitmapImage.CreateOptions();
        tracked->autoPlay = bitmapImage.AutoPlay();
        tracked->loaded = bitmapImage.PixelWidth() != 0;

        auto sourceUri = ImageSourceUri(tracked);

        if (!tracked->loaded && !sourceUri.Equals(bitmapImage.UriSource())) {
            bool fromCache = !sourceUri.Equals(uri);
            if (fromCache) {
                g_imageCacheUriRemotes.insert_or_assign(std::wstring(sourceUri.RawUri()), uri);
            }
            bitmapImage.UriSource(sourceUri);
        }

        tracked->usingCache = !bitmapImage.UriSource().Equals(uri);
    } catch (winrt::hresult_error const& ex) {
        Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
    }

    std::weak_ptr<TrackedImage> trackedWeak = tracked;

    auto onImageFailed = [trackedWeak](winrt::Windows::Foundation::IInspectable const&, ExceptionRoutedEventArgs const&) {
        auto tracked = trackedWeak.lock();
        if (!tracked) return;

        tracked->loaded = false;
        if (tracked->usingCache) {
            tracked->usingCache = false;
            RejectImageCache(tracked->url);
            std::error_code ec;
            std::filesystem::remove(tracked->cachePath, ec);
            QueueImageDownload(tracked->url);
        }

        ScheduleImageLoadRetryOnCurrentThread(kImageRetryBaseDelayMs, false);
    };

    auto onImageOpened = [trackedWeak](winrt::Windows::Foundation::IInspectable const&, RoutedEventArgs const&) {
        auto tracked = trackedWeak.lock();
        if (!tracked) return;

        tracked->loaded = true;
        tracked->retryCount = 0;
        tracked->lastRetryTick = 0;
    };

    if (auto brush = target.try_as<Media::ImageBrush>()) {
        tracked->brushImageFailedRevoker = brush.ImageFailed(winrt::auto_revoke, onImageFailed);
        tracked->brushImageOpenedRevoker = brush.ImageOpened(winrt::auto_revoke, onImageOpened);
    } else if (auto image = target.try_as<Controls::Image>()) {
        tracked->elementImageFailedRevoker = image.ImageFailed(winrt::auto_revoke, onImageFailed);
        tracked->elementImageOpenedRevoker = image.ImageOpened(winrt::auto_revoke, onImageOpened);
    }

    images.push_back(std::move(tracked));

    bool registerHandler = false;
    {
        std::lock_guard<std::mutex> lock(g_imageRetryMutex);
        g_imageRetryActive = true;

        if (!g_trackedImagesForThread.dispatcher) {
            try {
                auto dispatcher = winrt::Windows::System::DispatcherQueue::GetForCurrentThread();
                if (dispatcher) {
                    g_trackedImagesForThread.dispatcher = dispatcher;
                    g_imageRetryDispatchers.push_back(winrt::make_weak(dispatcher));
                }
            } catch (winrt::hresult_error const& ex) {
                Wh_Log(L"Error %08X: %s", ex.code(), ex.message().c_str());
            }
        }

        if (!g_networkStatusChangedToken && !g_networkStatusChangedRegistering) {
            g_networkStatusChangedRegistering = true;
            registerHandler = true;
        }
    }

    if (!registerHandler) return;

    winrt::event_token token = RegisterNetworkStatusChangedHandler();
    bool stopped;
    {
        std::lock_guard<std::mutex> lock(g_imageRetryMutex);
        g_networkStatusChangedRegistering = false;
        stopped = !g_imageRetryActive;
        if (!stopped) g_networkStatusChangedToken = token;
    }

    if (stopped && token) UnregisterNetworkStatusChangedHandler(token);
}

void TrackIfRemoteImageSource(DependencyObject const& target,
                              DependencyProperty const& sourceProperty,
                              winrt::Windows::Foundation::IInspectable const& imageSource) {
    auto bitmapImage = imageSource.try_as<Media::Imaging::BitmapImage>();
    if (!bitmapImage) return;

    auto uri = bitmapImage.UriSource();
    if (!uri) return;

    auto scheme = uri.SchemeName();
    if (scheme == L"file") {
        auto it = g_imageCacheUriRemotes.find(std::wstring(uri.RawUri()));
        if (it == g_imageCacheUriRemotes.end()) return;
        uri = it->second;
    } else if (scheme != L"http" && scheme != L"https") {
        return;
    }

    SetupImageTracking(target, sourceProperty, bitmapImage, uri);
}

// ----- ELEMENT MATCHING, STYLE PARSING & RULES -----

struct ElementIdEntry {
    ElementId id = ElementId::None;
    winrt::weak_ref<wf::IInspectable> element;
};

thread_local std::unordered_map<InstanceHandle, ElementIdEntry> g_elementIds;
thread_local uint64_t g_lastElementId;

ElementId GetOrCreateElementId(InstanceHandle handle, wf::IInspectable const& element) {
    if (!handle || !element) return ElementId::None;

    auto& entry = g_elementIds[handle];
    if (entry.id != ElementId::None && entry.element.get() == element) {
        return entry.id;
    }

    entry.id = static_cast<ElementId>(++g_lastElementId);

    winrt::weak_ref<wf::IInspectable> weakElement;
    try {
        weakElement = TryMakeWeak(element);
    } catch (...) {}

    if (!weakElement) {
        g_elementIds.erase(handle);
        return ElementId::None;
    }

    entry.element = std::move(weakElement);
    return entry.id;
}

ElementId FindElementId(InstanceHandle handle) {
    auto it = g_elementIds.find(handle);
    return it != g_elementIds.end() ? it->second.id : ElementId::None;
}

void ForgetElementId(InstanceHandle handle) {
    g_elementIds.erase(handle);
}

thread_local size_t g_elementIdsReapThreshold = 64;

void ReapDeadElementIdsIfNeeded() {
    if (g_elementIds.size() < g_elementIdsReapThreshold) return;

    std::vector<std::pair<InstanceHandle, ElementId>> dead;
    for (const auto& [handle, entry] : g_elementIds) {
        if (!entry.element.get()) dead.push_back({handle, entry.id});
    }

    for (const auto& [handle, elementId] : dead) {
        CleanupCustomizations(elementId);
        g_elementIds.erase(handle);
    }

    g_elementIdsReapThreshold = std::max<size_t>(64, g_elementIds.size() * 2);
}

using PropertyKeyValue = std::pair<DependencyProperty, winrt::Windows::Foundation::IInspectable>;
using PropertyValuesUnresolved = std::vector<std::pair<std::wstring, std::wstring>>;
using PropertyValues = std::vector<PropertyKeyValue>;
using PropertyValuesMaybeUnresolved = std::variant<PropertyValuesUnresolved, PropertyValues>;

struct ElementMatcher {
    enum class Kind { Element, Wildcard, Root };
    Kind kind = Kind::Element;
    std::wstring type;
    std::wstring name;
    std::optional<std::wstring> visualStateGroupName;
    int oneBasedIndex = 0;
    PropertyValuesMaybeUnresolved propertyValues;
};

struct ValueRule {
    std::wstring propertyName;
    std::wstring visualState;
    std::wstring value;
    bool isXamlValue = false;
    bool isDynamic() const { return value.find(L"{{") != std::wstring::npos; }
};

struct CaptureRule {
    std::wstring propertyName;
    std::wstring varName;
};

struct UnresolvedRules {
    std::vector<ValueRule> valueRules;
    std::vector<CaptureRule> captureRules;
};

struct XamlBlurBrushParams {
    float blurAmount;
    winrt::Windows::UI::Color tint;
    std::optional<uint8_t> tintOpacity;
    std::wstring tintThemeResourceKey;
    std::optional<float> tintLuminosityOpacity;
    std::optional<float> tintSaturation;
    std::optional<float> noiseOpacity;
    std::optional<float> noiseDensity;
    std::optional<winrt::Windows::UI::Color> fallbackColor;
    std::wstring fallbackThemeResourceKey;
};

struct DynamicStyleTemplate {
    std::wstring propertyName;
    std::wstring rawValue;
    bool isXamlValue = false;
};

using PropertyOverrideValue = std::variant<winrt::Windows::Foundation::IInspectable, XamlBlurBrushParams, DynamicStyleTemplate>;
using PropertyOverrides = std::unordered_map<DependencyProperty, std::unordered_map<std::wstring, PropertyOverrideValue>>;

struct CaptureSpec {
    DependencyProperty property{nullptr};
    std::wstring varName;
};

struct ResolvedRules {
    PropertyOverrides propertyOverrides;
    std::vector<CaptureSpec> captures;
    bool hasDynamicValues = false;
};

using PropertyOverridesMaybeUnresolved = std::variant<UnresolvedRules, ResolvedRules>;

struct StyleVariableDependency {
    std::wstring name;
    ElementId owner = ElementId::None;
};

struct ElementTreeNode {
    winrt::weak_ref<DependencyObject> ref;
    std::shared_ptr<ElementTreeNode> parent;
    uint32_t depth = 0;
    ElementTreeNode* root = nullptr;
};

thread_local std::unordered_map<void*, std::weak_ptr<ElementTreeNode>> g_elementTreeNodes;
thread_local size_t g_elementTreeNodesReapThreshold = 64;

void* ElementIdentityKey(DependencyObject const& object) {
    return winrt::get_abi(object.as<winrt::Windows::Foundation::IUnknown>());
}

bool IsStaleSpine(ElementTreeNode const& node) {
    auto object = node.root->ref.get();
    return object && Media::VisualTreeHelper::GetParent(object);
}

std::shared_ptr<ElementTreeNode> GetOrCreateElementTreeNode(DependencyObject object) {
    if (!object) return nullptr;

    std::shared_ptr<ElementTreeNode> node;
    std::vector<DependencyObject> missing;

    try {
        for (auto iter = object; iter; iter = Media::VisualTreeHelper::GetParent(iter)) {
            auto key = ElementIdentityKey(iter);
            if (auto it = g_elementTreeNodes.find(key); it != g_elementTreeNodes.end()) {
                auto existing = it->second.lock();
                if (!existing || !existing->ref.get()) {
                    g_elementTreeNodes.erase(it);
                } else if (!IsStaleSpine(*existing)) {
                    node = std::move(existing);
                    break;
                } else {
                    g_elementTreeNodes.erase(it);
                }
            }
            missing.push_back(iter);
        }

        for (auto it = missing.rbegin(); it != missing.rend(); ++it) {
            auto fresh = std::make_shared<ElementTreeNode>();
            fresh->ref = *it;
            fresh->depth = node ? node->depth + 1 : 0;
            fresh->root = node ? node->root : fresh.get();
            fresh->parent = std::move(node);
            g_elementTreeNodes[ElementIdentityKey(*it)] = fresh;
            node = std::move(fresh);
        }
    } catch (...) {
        return nullptr;
    }

    return node;
}

void ReapElementTreeNodesIfNeeded() {
    if (g_elementTreeNodes.size() < g_elementTreeNodesReapThreshold) return;
    std::erase_if(g_elementTreeNodes, [](const auto& item) { return item.second.expired(); });
    g_elementTreeNodesReapThreshold = std::max<size_t>(64, g_elementTreeNodes.size() * 2);
}

int ElementTreeLcaDepth(ElementTreeNode const* a, ElementTreeNode const* b) {
    if (!a || !b) return -1;
    while (a->depth > b->depth) a = a->parent.get();
    while (b->depth > a->depth) b = b->parent.get();
    while (a != b) {
        a = a->parent.get();
        b = b->parent.get();
        if (!a || !b) return -1;
    }
    return static_cast<int>(a->depth);
}

struct ElementCustomizationRules {
    ElementMatcher elementMatcher;
    std::vector<ElementMatcher> parentElementMatchers;
    PropertyOverridesMaybeUnresolved propertyOverrides;
};

thread_local std::vector<ElementCustomizationRules> g_elementsCustomizationRules;

struct ElementPropertyCustomizationState {
    std::optional<winrt::Windows::Foundation::IInspectable> originalValue;
    std::optional<PropertyOverrideValue> customValue;
    winrt::Windows::Foundation::IInspectable lastAppliedValue{nullptr};
    int64_t propertyChangedToken = 0;
    std::optional<DynamicStyleTemplate> dynamicTemplate;
    std::vector<StyleVariableDependency> variableDependencies;
    bool lastResolveFailed = false;
};

struct CapturePropertyCustomizationState {
    std::wstring varName;
    int64_t propertyChangedToken = 0;
};

struct ElementCustomizationStateForVisualStateGroup {
    std::unordered_map<DependencyProperty, ElementPropertyCustomizationState> propertyCustomizationStates;
    winrt::event_token visualStateGroupCurrentStateChangedToken;
};

struct ElementCustomizationState {
    winrt::weak_ref<FrameworkElement> element;
    winrt::weak_ref<XamlRoot> xamlRoot;
    std::shared_ptr<ElementTreeNode> treeNode;
    std::unordered_map<DependencyProperty, CapturePropertyCustomizationState> captureCustomizationStates;
    winrt::event_token captureSizeChangedToken;
    std::list<std::pair<std::optional<winrt::weak_ref<VisualStateGroup>>, ElementCustomizationStateForVisualStateGroup>> perVisualStateGroup;
};

thread_local std::unordered_map<ElementId, ElementCustomizationState> g_elementsCustomizationState;

ElementTreeNode* EnsureElementTreeNode(ElementCustomizationState& elementCustomizationState) {
    if (!elementCustomizationState.treeNode || IsStaleSpine(*elementCustomizationState.treeNode)) {
        if (auto element = elementCustomizationState.element.get()) {
            elementCustomizationState.treeNode = GetOrCreateElementTreeNode(element);
        }
    }
    return elementCustomizationState.treeNode.get();
}

struct StyleVariableValue {
    std::wstring stringForm;
    std::optional<double> numeric;
    bool substitutable = false;
};

struct StyleVariableCapture {
    ElementId elementId;
    StyleVariableValue value;
};

struct StyleVariableConsumer {
    ElementId elementId;
    DependencyProperty property{nullptr};
    std::wstring fallbackClassName;
};

struct StyleVariableState {
    winrt::weak_ref<XamlRoot> xamlRoot;
    std::unordered_map<std::wstring, std::vector<StyleVariableCapture>> variables;
    std::unordered_map<std::wstring, std::vector<StyleVariableConsumer>> consumers;
    std::unordered_map<ElementId, size_t> elementRefs;
};

void AddStyleVariableElementRef(StyleVariableState* state, ElementId elementId) {
    state->elementRefs[elementId]++;
}

void ReleaseStyleVariableElementRefs(StyleVariableState* state, ElementId elementId, size_t count) {
    if (!count) return;
    auto it = state->elementRefs.find(elementId);
    if (it == state->elementRefs.end()) return;
    if (it->second > count) it->second -= count;
    else state->elementRefs.erase(it);
}

thread_local std::list<StyleVariableState> g_styleVariableState;
thread_local int g_styleVariableStatePinDepth = 0;

struct StyleVariableStatePin {
    StyleVariableStatePin() { g_styleVariableStatePinDepth++; }
    ~StyleVariableStatePin() { g_styleVariableStatePinDepth--; }
    StyleVariableStatePin(const StyleVariableStatePin&) = delete;
    StyleVariableStatePin& operator=(const StyleVariableStatePin&) = delete;
};

thread_local int g_styleVariablePropagationDepth = 0;

struct PendingStyleVariablePropagation {
    StyleVariableState* state;
    std::wstring varName;
    std::optional<ElementId> changedOwner;
    bool operator==(const PendingStyleVariablePropagation&) const = default;
};

thread_local std::vector<PendingStyleVariablePropagation> g_pendingStyleVariablePropagations;

StyleVariableState* GetStyleVariableState(XamlRoot const& xamlRoot) {
    if (!xamlRoot) return nullptr;
    if (g_styleVariableStatePinDepth == 0) {
        g_styleVariableState.remove_if([](StyleVariableState const& entry) {
            return !entry.xamlRoot.get();
        });
    }
    for (auto& entry : g_styleVariableState) {
        if (entry.xamlRoot.get() == xamlRoot) return &entry;
    }
    auto& fresh = g_styleVariableState.emplace_back();
    fresh.xamlRoot = xamlRoot;
    return &fresh;
}

StyleVariableState* GetStyleVariableState(winrt::weak_ref<XamlRoot> const& xamlRootWeak) {
    auto strong = xamlRootWeak.get();
    if (!strong) return nullptr;
    return GetStyleVariableState(strong);
}

StyleVariableState* GetStyleVariableState(FrameworkElement const& element) {
    if (!element) return nullptr;
    XamlRoot xamlRoot{nullptr};
    try {
        xamlRoot = element.XamlRoot();
    } catch (...) {}
    return GetStyleVariableState(xamlRoot);
}

thread_local std::list<std::pair<winrt::weak_ref<DependencyObject>, winrt::Windows::Foundation::IAsyncOperation<bool>>> g_delayedBackgroundFillSet;

winrt::Windows::Foundation::IInspectable ReadLocalValueWithWorkaround(DependencyObject elementDo, DependencyProperty property) {
    auto value = elementDo.ReadLocalValue(property);
    if (value) {
        auto className = winrt::get_class_name(value);
        if (className == L"Windows.UI.Xaml.Data.BindingExpressionBase" ||
            className == L"Windows.UI.Xaml.Data.BindingExpression") {
            value = elementDo.GetAnimationBaseValue(property);
        }
    }
    return value;
}

std::wstring EscapeXmlAttribute(std::wstring_view data) {
    std::wstring buffer;
    buffer.reserve(data.size());
    for (const auto c : data) {
        switch (c) {
            case '&': buffer.append(L"&amp;"); break;
            case '\"': buffer.append(L"&quot;"); break;
            case '<': buffer.append(L"&lt;"); break;
            case '>': buffer.append(L"&gt;"); break;
            default: buffer.push_back(c); break;
        }
    }
    return buffer;
}

std::optional<PropertyOverrideValue> ParseNonXamlPropertyOverrideValue(std::wstring_view stringValue) {
    auto substr = TrimStringView(stringValue);

    constexpr auto kWindhawkBlurPrefix = L"<WindhawkBlur "sv;
    if (!substr.starts_with(kWindhawkBlurPrefix)) return std::nullopt;
    substr = substr.substr(std::size(kWindhawkBlurPrefix));

    constexpr auto kWindhawkBlurSuffix = L"/>"sv;
    if (!substr.ends_with(kWindhawkBlurSuffix)) throw std::runtime_error("WindhawkBlur: Bad suffix");
    substr = substr.substr(0, substr.size() - std::size(kWindhawkBlurSuffix));

    bool pendingTintColorThemeResource = false;
    bool pendingFallbackColorThemeResource = false;
    std::wstring tintThemeResourceKey;
    std::wstring fallbackThemeResourceKey;
    winrt::Windows::UI::Color tint{};
    std::optional<winrt::Windows::UI::Color> fallbackColor;
    float tintOpacity = std::numeric_limits<float>::quiet_NaN();
    float tintLuminosityOpacity = std::numeric_limits<float>::quiet_NaN();
    float tintSaturation = std::numeric_limits<float>::quiet_NaN();
    float noiseOpacity = std::numeric_limits<float>::quiet_NaN();
    float noiseDensity = std::numeric_limits<float>::quiet_NaN();
    float blurAmount = 0;

    constexpr auto kTintColorThemeResourcePrefix = L"TintColor=\"{ThemeResource"sv;
    constexpr auto kTintColorThemeResourceSuffix = L"}\""sv;
    constexpr auto kTintColorPrefix = L"TintColor=\"#"sv;
    constexpr auto kTintOpacityPrefix = L"TintOpacity=\""sv;
    constexpr auto kTintLuminosityOpacityPrefix = L"TintLuminosityOpacity=\""sv;
    constexpr auto kTintSaturationPrefix = L"TintSaturation=\""sv;
    constexpr auto kNoiseOpacityPrefix = L"NoiseOpacity=\""sv;
    constexpr auto kNoiseDensityPrefix = L"NoiseDensity=\""sv;
    constexpr auto kBlurAmountPrefix = L"BlurAmount=\""sv;
    constexpr auto kFallbackColorThemeResourcePrefix = L"FallbackColor=\"{ThemeResource"sv;
    constexpr auto kFallbackColorThemeResourceSuffix = L"}\""sv;
    constexpr auto kFallbackColorPrefix = L"FallbackColor=\"#"sv;

    for (const auto prop : SplitStringView(substr, L" ")) {
        const auto propSubstr = TrimStringView(prop);
        if (propSubstr.empty()) continue;

        if (pendingTintColorThemeResource) {
            if (!propSubstr.ends_with(kTintColorThemeResourceSuffix)) {
                throw std::runtime_error("WindhawkBlur: Invalid TintColor theme resource syntax");
            }
            pendingTintColorThemeResource = false;
            tintThemeResourceKey = propSubstr.substr(0, propSubstr.size() - std::size(kTintColorThemeResourceSuffix));
            continue;
        }

        if (pendingFallbackColorThemeResource) {
            if (!propSubstr.ends_with(kFallbackColorThemeResourceSuffix)) {
                throw std::runtime_error("WindhawkBlur: Invalid FallbackColor theme resource syntax");
            }
            pendingFallbackColorThemeResource = false;
            fallbackThemeResourceKey = propSubstr.substr(0, propSubstr.size() - std::size(kFallbackColorThemeResourceSuffix));
            continue;
        }

        if (propSubstr == kTintColorThemeResourcePrefix) { pendingTintColorThemeResource = true; continue; }
        if (propSubstr == kFallbackColorThemeResourcePrefix) { pendingFallbackColorThemeResource = true; continue; }

        if (propSubstr.starts_with(kTintColorPrefix) && propSubstr.back() == L'\"') {
            auto valStr = propSubstr.substr(std::size(kTintColorPrefix), propSubstr.size() - std::size(kTintColorPrefix) - 1);
            bool hasAlpha = (valStr.size() == 8);
            auto valNum = std::stoul(std::wstring(valStr), nullptr, 16);
            uint8_t a = hasAlpha ? HIBYTE(HIWORD(valNum)) : 255;
            uint8_t r = LOBYTE(HIWORD(valNum));
            uint8_t g = HIBYTE(LOWORD(valNum));
            uint8_t b = LOBYTE(LOWORD(valNum));
            tint = {a, r, g, b};
            continue;
        }

        if (propSubstr.starts_with(kFallbackColorPrefix) && propSubstr.back() == L'\"') {
            auto valStr = propSubstr.substr(std::size(kFallbackColorPrefix), propSubstr.size() - std::size(kFallbackColorPrefix) - 1);
            bool hasAlpha = (valStr.size() == 8);
            auto valNum = std::stoul(std::wstring(valStr), nullptr, 16);
            uint8_t a = hasAlpha ? HIBYTE(HIWORD(valNum)) : 255;
            uint8_t r = LOBYTE(HIWORD(valNum));
            uint8_t g = HIBYTE(LOWORD(valNum));
            uint8_t b = LOBYTE(LOWORD(valNum));
            fallbackColor = winrt::Windows::UI::Color{a, r, g, b};
            continue;
        }

        if (propSubstr.starts_with(kTintOpacityPrefix) && propSubstr.back() == L'\"') {
            auto valStr = propSubstr.substr(std::size(kTintOpacityPrefix), propSubstr.size() - std::size(kTintOpacityPrefix) - 1);
            tintOpacity = std::stof(std::wstring(valStr));
            continue;
        }

        if (propSubstr.starts_with(kTintLuminosityOpacityPrefix) && propSubstr.back() == L'\"') {
            auto valStr = propSubstr.substr(std::size(kTintLuminosityOpacityPrefix), propSubstr.size() - std::size(kTintLuminosityOpacityPrefix) - 1);
            tintLuminosityOpacity = std::stof(std::wstring(valStr));
            continue;
        }

        if (propSubstr.starts_with(kTintSaturationPrefix) && propSubstr.back() == L'\"') {
            auto valStr = propSubstr.substr(std::size(kTintSaturationPrefix), propSubstr.size() - std::size(kTintSaturationPrefix) - 1);
            tintSaturation = std::stof(std::wstring(valStr));
            continue;
        }

        if (propSubstr.starts_with(kNoiseOpacityPrefix) && propSubstr.back() == L'\"') {
            auto valStr = propSubstr.substr(std::size(kNoiseOpacityPrefix), propSubstr.size() - std::size(kNoiseOpacityPrefix) - 1);
            noiseOpacity = std::stof(std::wstring(valStr));
            continue;
        }

        if (propSubstr.starts_with(kNoiseDensityPrefix) && propSubstr.back() == L'\"') {
            auto valStr = propSubstr.substr(std::size(kNoiseDensityPrefix), propSubstr.size() - std::size(kNoiseDensityPrefix) - 1);
            noiseDensity = std::stof(std::wstring(valStr));
            continue;
        }

        if (propSubstr.starts_with(kBlurAmountPrefix) && propSubstr.back() == L'\"') {
            auto valStr = propSubstr.substr(std::size(kBlurAmountPrefix), propSubstr.size() - std::size(kBlurAmountPrefix) - 1);
            blurAmount = std::stof(std::wstring(valStr));
            continue;
        }

        throw std::runtime_error("WindhawkBlur: Bad property");
    }

    if (!std::isnan(tintOpacity)) {
        tintOpacity = std::clamp(tintOpacity, 0.0f, 1.0f);
        tint.A = static_cast<uint8_t>(tintOpacity * 255.0f);
    }

    return XamlBlurBrushParams{
        .blurAmount = blurAmount,
        .tint = tint,
        .tintOpacity = !std::isnan(tintOpacity) ? std::optional(tint.A) : std::nullopt,
        .tintThemeResourceKey = std::move(tintThemeResourceKey),
        .tintLuminosityOpacity = !std::isnan(tintLuminosityOpacity) ? std::optional(tintLuminosityOpacity) : std::nullopt,
        .tintSaturation = !std::isnan(tintSaturation) ? std::optional(tintSaturation) : std::nullopt,
        .noiseOpacity = !std::isnan(noiseOpacity) ? std::optional(noiseOpacity) : std::nullopt,
        .noiseDensity = !std::isnan(noiseDensity) ? std::optional(noiseDensity) : std::nullopt,
        .fallbackColor = fallbackColor,
        .fallbackThemeResourceKey = std::move(fallbackThemeResourceKey),
    };
}

Style GetStyleFromXamlSetters(const std::wstring_view type, const std::wstring_view xamlStyleSetters) {
    std::wstring xaml =
        LR"(<ResourceDictionary
    xmlns="http://schemas.microsoft.com/winfx/2006/xaml/presentation"
    xmlns:x="http://schemas.microsoft.com/winfx/2006/xaml"
    xmlns:d="http://schemas.microsoft.com/expression/blend/2008"
    xmlns:mc="http://schemas.openxmlformats.org/markup-compatibility/2006"
    xmlns:muxc="using:Microsoft.UI.Xaml.Controls")";

    if (auto pos = type.rfind('.'); pos != type.npos) {
        auto typeNamespace = std::wstring_view(type).substr(0, pos);
        auto typeName = std::wstring_view(type).substr(pos + 1);

        xaml += L"\n    xmlns:windhawkstyler=\"using:";
        xaml += EscapeXmlAttribute(typeNamespace);
        xaml += L"\">\n    <Style TargetType=\"windhawkstyler:";
        xaml += EscapeXmlAttribute(typeName);
        xaml += L"\">\n";
    } else {
        xaml += L">\n    <Style TargetType=\"";
        xaml += EscapeXmlAttribute(type);
        xaml += L"\">\n";
    }

    xaml += xamlStyleSetters;
    xaml += L"    </Style>\n</ResourceDictionary>";

    auto resourceDictionary = Markup::XamlReader::Load(xaml).as<ResourceDictionary>();
    auto [styleKey, styleInspectable] = resourceDictionary.First().Current();
    return styleInspectable.as<Style>();
}

Style GetStyleFromXamlSettersWithFallbackType(const std::wstring_view type, const std::wstring_view fallbackType, const std::wstring_view xamlStyleSetters) {
    try {
        return GetStyleFromXamlSetters(type, xamlStyleSetters);
    } catch (winrt::hresult_error const& ex) {
        constexpr HRESULT kStowedException = 0x802B000A;
        if (ex.code() != kStowedException || fallbackType.empty() || fallbackType == type) throw;
        return GetStyleFromXamlSetters(fallbackType, xamlStyleSetters);
    }
}

const ResolvedRules& GetResolvedPropertyOverrides(const std::wstring_view type, const std::wstring_view fallbackType, PropertyOverridesMaybeUnresolved* propertyOverridesMaybeUnresolved) {
    if (const auto* resolved = std::get_if<ResolvedRules>(propertyOverridesMaybeUnresolved)) {
        return *resolved;
    }

    ResolvedRules resolved;
    try {
        const auto& unresolved = std::get<UnresolvedRules>(*propertyOverridesMaybeUnresolved);
        const auto& valueRules = unresolved.valueRules;
        const auto& captureRules = unresolved.captureRules;

        if (!valueRules.empty() || !captureRules.empty()) {
            std::wstring xaml;
            std::vector<std::optional<PropertyOverrideValue>> propertyOverrideValues;
            propertyOverrideValues.reserve(valueRules.size());

            for (const auto& rule : valueRules) {
                const bool isDynamic = rule.isDynamic();

                propertyOverrideValues.push_back(
                    !isDynamic && rule.isXamlValue
                        ? ParseNonXamlPropertyOverrideValue(rule.value)
                        : std::nullopt);

                xaml += L"        <Setter Property=\"";
                xaml += EscapeXmlAttribute(rule.propertyName);
                xaml += L"\"";
                if (isDynamic || propertyOverrideValues.back() || (rule.isXamlValue && rule.value.empty())) {
                    xaml += L" Value=\"{x:Null}\" />\n";
                } else if (!rule.isXamlValue) {
                    xaml += L" Value=\"";
                    xaml += EscapeXmlAttribute(rule.value);
                    xaml += L"\" />\n";
                } else {
                    xaml += L">\n            <Setter.Value>\n";
                    xaml += rule.value;
                    xaml += L"\n            </Setter.Value>\n        </Setter>\n";
                }
            }

            for (const auto& rule : captureRules) {
                xaml += L"        <Setter Property=\"";
                xaml += EscapeXmlAttribute(rule.propertyName);
                xaml += L"\" Value=\"{x:Null}\" />\n";
            }

            auto style = GetStyleFromXamlSettersWithFallbackType(type, fallbackType, xaml);

            uint32_t setterIndex = 0;
            for (size_t i = 0; i < valueRules.size(); i++, setterIndex++) {
                const auto& rule = valueRules[i];
                const auto setter = style.Setters().GetAt(setterIndex).as<Setter>();
                auto property = setter.Property();
                if (rule.isDynamic()) {
                    resolved.propertyOverrides[property][rule.visualState] =
                        DynamicStyleTemplate{rule.propertyName, rule.value, rule.isXamlValue};
                    resolved.hasDynamicValues = true;
                } else {
                    resolved.propertyOverrides[property][rule.visualState] =
                        propertyOverrideValues[i].value_or(
                            rule.isXamlValue && rule.value.empty()
                                ? DependencyProperty::UnsetValue()
                                : setter.Value());
                }
            }

            for (const auto& rule : captureRules) {
                const auto setter = style.Setters().GetAt(setterIndex++).as<Setter>();
                resolved.captures.push_back({setter.Property(), rule.varName});
            }
        }
    } catch (winrt::hresult_error const& ex) {
        // A single bad setter invalidates every style rule for this target.
        Wh_Log(L"Style rules for %s ignored: 0x%08X %s",
               std::wstring(type).c_str(), (unsigned)ex.code().value,
               ex.message().c_str());
    } catch (...) {
        Wh_Log(L"Style rules for %s ignored: unknown error",
               std::wstring(type).c_str());
    }

    *propertyOverridesMaybeUnresolved = std::move(resolved);
    return std::get<ResolvedRules>(*propertyOverridesMaybeUnresolved);
}

std::optional<PropertyOverrideValue> ResolveExpandedSinglePropertyValue(
    std::wstring_view type,
    std::wstring_view fallbackType,
    std::wstring_view propertyName,
    std::wstring_view expandedValue,
    bool isXamlValue) {
    if (isXamlValue) {
        if (auto blur = ParseNonXamlPropertyOverrideValue(expandedValue)) {
            return *blur;
        }

        if (TrimStringView(expandedValue).empty()) {
            return PropertyOverrideValue{DependencyProperty::UnsetValue()};
        }
    }

    std::wstring xaml = L"        <Setter Property=\"";
    xaml += EscapeXmlAttribute(propertyName);
    xaml += L"\"";
    if (!isXamlValue) {
        xaml += L" Value=\"";
        xaml += EscapeXmlAttribute(expandedValue);
        xaml += L"\" />\n";
    } else {
        xaml += L">\n            <Setter.Value>\n";
        xaml += expandedValue;
        xaml += L"\n            </Setter.Value>\n        </Setter>\n";
    }

    try {
        auto style = GetStyleFromXamlSettersWithFallbackType(type, fallbackType, xaml);
        const auto setter = style.Setters().GetAt(0).as<Setter>();
        return PropertyOverrideValue{setter.Value()};
    } catch (...) {
        return std::nullopt;
    }
}

const PropertyValues& GetResolvedPropertyValues(
    const std::wstring_view type,
    const std::wstring_view fallbackType,
    PropertyValuesMaybeUnresolved* propertyValuesMaybeUnresolved) {
    if (const auto* resolved = std::get_if<PropertyValues>(propertyValuesMaybeUnresolved)) {
        return *resolved;
    }

    PropertyValues propertyValues;
    try {
        const auto& propertyValuesStr = std::get<PropertyValuesUnresolved>(*propertyValuesMaybeUnresolved);
        if (!propertyValuesStr.empty()) {
            std::wstring xaml;
            for (const auto& [property, value] : propertyValuesStr) {
                xaml += L"        <Setter Property=\"";
                xaml += EscapeXmlAttribute(property);
                xaml += L"\" Value=\"";
                xaml += EscapeXmlAttribute(value);
                xaml += L"\" />\n";
            }

            auto style = GetStyleFromXamlSettersWithFallbackType(type, fallbackType, xaml);
            for (size_t i = 0; i < propertyValuesStr.size(); i++) {
                const auto setter = style.Setters().GetAt(i).as<Setter>();
                propertyValues.push_back({setter.Property(), setter.Value()});
            }
        }
    } catch (...) {}

    *propertyValuesMaybeUnresolved = std::move(propertyValues);
    return std::get<PropertyValues>(*propertyValuesMaybeUnresolved);
}

VisualStateGroup GetVisualStateGroup(FrameworkElement element, std::wstring_view visualStateGroupName) {
    if (winrt::get_class_name(element) == L"Taskbar.TaskListButtonPanel") {
        auto parent = Media::VisualTreeHelper::GetParent(element).try_as<FrameworkElement>();
        if (parent && winrt::get_class_name(parent) == L"Taskbar.SearchBoxLaunchListButton") {
            return nullptr;
        }
    }

    if (winrt::get_class_name(element) == L"SearchUx.SearchUI.SearchButtonRootGrid") {
        auto parent = Media::VisualTreeHelper::GetParent(element).try_as<FrameworkElement>();
        if (parent && winrt::get_class_name(parent) == L"SearchUx.SearchUI.SearchPillButton") {
            return nullptr;
        }
    }

    auto list = VisualStateManager::GetVisualStateGroups(element);
    for (const auto& v : list) {
        if (v.Name() == visualStateGroupName) {
            return v;
        }
    }
    return nullptr;
}

std::wstring FormatDoubleInvariant(double d) {
    if (std::isnan(d)) return L"NaN";
    if (std::isinf(d)) return d < 0 ? L"-Infinity" : L"Infinity";
    char buf[64];
    auto [end, ec] = std::to_chars(buf, buf + std::size(buf), d);
    if (ec != std::errc{}) return L"0";
    return std::wstring(buf, end);
}

std::optional<double> ParseDoubleInvariant(std::wstring_view sv) {
    std::string narrow;
    narrow.reserve(sv.size());
    for (auto c : sv) {
        if (c > 127) return std::nullopt;
        narrow.push_back(static_cast<char>(c));
    }
    double result = 0;
    auto [ptr, ec] = std::from_chars(narrow.data(), narrow.data() + narrow.size(), result);
    if (ec != std::errc{} || ptr != narrow.data() + narrow.size()) return std::nullopt;
    return result;
}

using UnboxedPropertyValue = std::variant<std::wstring, bool, char16_t, uint8_t, int16_t, uint16_t, int32_t, uint32_t, int64_t, uint64_t, float, double>;

std::optional<UnboxedPropertyValue> TryUnboxPropertyValue(winrt::Windows::Foundation::IInspectable const& value) {
    using winrt::Windows::Foundation::IPropertyValue;
    using winrt::Windows::Foundation::PropertyType;

    auto pv = value.try_as<IPropertyValue>();
    if (!pv) return std::nullopt;

    switch (pv.Type()) {
        case PropertyType::String: return UnboxedPropertyValue{std::wstring(pv.GetString())};
        case PropertyType::Boolean: return UnboxedPropertyValue{pv.GetBoolean()};
        case PropertyType::Char16: return UnboxedPropertyValue{pv.GetChar16()};
        case PropertyType::Double: return UnboxedPropertyValue{pv.GetDouble()};
        case PropertyType::Single: return UnboxedPropertyValue{pv.GetSingle()};
        case PropertyType::UInt8: return UnboxedPropertyValue{pv.GetUInt8()};
        case PropertyType::Int16: return UnboxedPropertyValue{pv.GetInt16()};
        case PropertyType::UInt16: return UnboxedPropertyValue{pv.GetUInt16()};
        case PropertyType::Int32: return UnboxedPropertyValue{pv.GetInt32()};
        case PropertyType::UInt32: return UnboxedPropertyValue{pv.GetUInt32()};
        case PropertyType::Int64: return UnboxedPropertyValue{pv.GetInt64()};
        case PropertyType::UInt64: return UnboxedPropertyValue{pv.GetUInt64()};
        case PropertyType::OtherType: {
            if (auto intVal = value.try_as<int32_t>()) {
                return UnboxedPropertyValue{*intVal};
            }
            return std::nullopt;
        }
        default: return std::nullopt;
    }
}

std::wstring FormatUnboxedPropertyValue(UnboxedPropertyValue const& v) {
    return std::visit(
        [](auto const& x) -> std::wstring {
            using T = std::decay_t<decltype(x)>;
            if constexpr (std::is_same_v<T, std::wstring>) return x;
            else if constexpr (std::is_same_v<T, bool>) return x ? L"True" : L"False";
            else if constexpr (std::is_same_v<T, char16_t>) return std::wstring(1, static_cast<wchar_t>(x));
            else if constexpr (std::is_floating_point_v<T>) return FormatDoubleInvariant(static_cast<double>(x));
            else return std::to_wstring(x);
        },
        v);
}

std::optional<double> UnboxedPropertyValueAsNumeric(UnboxedPropertyValue const& v) {
    return std::visit(
        [](auto const& x) -> std::optional<double> {
            using T = std::decay_t<decltype(x)>;
            if constexpr (std::is_same_v<T, std::wstring>) return std::nullopt;
            else return static_cast<double>(x);
        },
        v);
}

bool TestElementMatcher(FrameworkElement element, ElementMatcher& matcher, VisualStateGroup* visualStateGroup, PCWSTR fallbackClassName) {
    if (!matcher.type.empty() &&
        matcher.type != winrt::get_class_name(element) &&
        (!fallbackClassName || matcher.type != fallbackClassName)) {
        return false;
    }

    if (!matcher.name.empty() && matcher.name != element.Name()) {
        return false;
    }

    if (matcher.oneBasedIndex) {
        auto parent = Media::VisualTreeHelper::GetParent(element);
        if (!parent) return false;

        int index = matcher.oneBasedIndex - 1;
        if (index < 0 ||
            index >= Media::VisualTreeHelper::GetChildrenCount(parent) ||
            Media::VisualTreeHelper::GetChild(parent, index) != element) {
            return false;
        }
    }

    auto elementDo = element.as<DependencyObject>();

    for (const auto& propertyValue : GetResolvedPropertyValues(
             matcher.type,
             fallbackClassName ? fallbackClassName : winrt::name_of<FrameworkElement>(),
             &matcher.propertyValues)) {
        const auto value = ReadLocalValueWithWorkaround(elementDo, propertyValue.first);
        if (!value || value == DependencyProperty::UnsetValue()) return false;

        auto expectedUnboxed = TryUnboxPropertyValue(propertyValue.second);
        auto valueUnboxed = TryUnboxPropertyValue(value);
        if (!expectedUnboxed || !valueUnboxed) return false;
        if (*expectedUnboxed != *valueUnboxed) return false;
    }

    if (matcher.visualStateGroupName && visualStateGroup) {
        *visualStateGroup = GetVisualStateGroup(element, *matcher.visualStateGroupName);
    }

    return true;
}

struct ElementResolvedRules {
    std::unordered_map<VisualStateGroup, PropertyOverrides> overridesPerVSG;
    std::vector<CaptureSpec> captures;
    bool hasDynamicValues = false;
};

ElementResolvedRules FindElementPropertyOverrides(FrameworkElement element, PCWSTR fallbackClassName) {
    ElementResolvedRules result;
    std::unordered_set<DependencyProperty> propertiesAdded;
    std::unordered_set<std::wstring> capturesAdded;

    for (auto it = g_elementsCustomizationRules.rbegin(); it != g_elementsCustomizationRules.rend(); ++it) {
        auto& override = *it;
        VisualStateGroup visualStateGroup = nullptr;

        if (!TestElementMatcher(element, override.elementMatcher, &visualStateGroup, fallbackClassName)) {
            continue;
        }

        auto& parentMatchers = override.parentElementMatchers;
        auto matchParents = [&](auto& self, FrameworkElement iter, size_t mi) -> bool {
            if (mi >= parentMatchers.size()) return true;
            auto& matcher = parentMatchers[mi];

            if (matcher.kind == ElementMatcher::Kind::Root) {
                if (Media::VisualTreeHelper::GetParent(iter)) return false;
                return self(self, iter, mi + 1);
            }

            if (matcher.kind == ElementMatcher::Kind::Wildcard) {
                auto& nextMatcher = parentMatchers[mi + 1];
                auto cur = iter;
                while (true) {
                    auto parent = Media::VisualTreeHelper::GetParent(cur).try_as<FrameworkElement>();
                    if (!parent) return false;
                    cur = parent;
                    if (TestElementMatcher(cur, nextMatcher, &visualStateGroup, nullptr) &&
                        self(self, cur, mi + 2)) {
                        return true;
                    }
                }
            }

            auto parent = Media::VisualTreeHelper::GetParent(iter).try_as<FrameworkElement>();
            if (!parent) return false;
            if (!TestElementMatcher(parent, matcher, &visualStateGroup, nullptr)) return false;

            return self(self, parent, mi + 1);
        };

        if (!matchParents(matchParents, element, 0)) continue;

        const auto& resolvedRules = GetResolvedPropertyOverrides(
            override.elementMatcher.type,
            fallbackClassName ? fallbackClassName : winrt::name_of<FrameworkElement>(),
            &override.propertyOverrides);

        result.hasDynamicValues |= resolvedRules.hasDynamicValues;

        auto& propertyOverridesForVSG = result.overridesPerVSG[visualStateGroup];
        for (const auto& [property, valuesPerVisualState] : resolvedRules.propertyOverrides) {
            if (!propertiesAdded.insert(property).second) continue;

            auto& propertyOverrides = propertyOverridesForVSG[property];
            for (const auto& [visualState, value] : valuesPerVisualState) {
                propertyOverrides.insert({visualState, value});
            }
        }

        for (const auto& capture : resolvedRules.captures) {
            if (!capturesAdded.insert(capture.varName).second) continue;
            result.captures.push_back(capture);
        }
    }

    std::erase_if(result.overridesPerVSG, [](const auto& item) { return item.second.empty(); });
    return result;
}

struct StyleVariableResolution {
    const StyleVariableValue* value = nullptr;
    ElementId owner = ElementId::None;
};

std::pair<int, int> StyleVariableCaptureRank(ElementTreeNode const* consumerNode, ElementTreeNode const* captureNode) {
    int lcaDepth = ElementTreeLcaDepth(consumerNode, captureNode);
    int captureDepth = captureNode ? static_cast<int>(captureNode->depth) : std::numeric_limits<int>::max();
    return {-lcaDepth, captureDepth};
}

StyleVariableResolution FindWinningCapture(StyleVariableState* state, const std::wstring& varName, ElementTreeNode const* consumerNode) {
    StyleVariableResolution result;
    auto it = state->variables.find(varName);
    if (it == state->variables.end() || it->second.empty()) return result;

    const auto& captures = it->second;
    if (captures.size() == 1) {
        return {&captures.front().value, captures.front().elementId};
    }

    std::pair<int, int> bestRank;
    for (const auto& capture : captures) {
        ElementTreeNode const* captureNode = nullptr;
        if (auto elementIt = g_elementsCustomizationState.find(capture.elementId);
            elementIt != g_elementsCustomizationState.end()) {
            captureNode = EnsureElementTreeNode(elementIt->second);
        }

        auto rank = StyleVariableCaptureRank(consumerNode, captureNode);
        if (!result.value || rank <= bestRank) {
            bestRank = rank;
            result = {&capture.value, capture.elementId};
        }
    }
    return result;
}

struct StyleVariableCandidate {
    ElementId owner = ElementId::None;
    std::shared_ptr<ElementTreeNode> node;
};

std::vector<StyleVariableCandidate> SnapshotStyleVariableCaptures(const std::vector<StyleVariableCapture>& captures) {
    std::vector<StyleVariableCandidate> candidates;
    candidates.reserve(captures.size());

    for (const auto& capture : captures) {
        StyleVariableCandidate candidate;
        candidate.owner = capture.elementId;
        if (auto elementIt = g_elementsCustomizationState.find(capture.elementId);
            elementIt != g_elementsCustomizationState.end()) {
            auto& elementCustomizationState = elementIt->second;
            EnsureElementTreeNode(elementCustomizationState);
            candidate.node = elementCustomizationState.treeNode;
        }
        candidates.push_back(std::move(candidate));
    }
    return candidates;
}

ElementId PickWinningCaptureOwner(const std::vector<StyleVariableCandidate>& candidates, ElementTreeNode const* consumerNode) {
    ElementId owner = ElementId::None;
    bool haveBest = false;
    std::pair<int, int> bestRank;

    for (const auto& candidate : candidates) {
        auto rank = StyleVariableCaptureRank(consumerNode, candidate.node.get());
        if (!haveBest || rank <= bestRank) {
            haveBest = true;
            bestRank = rank;
            owner = candidate.owner;
        }
    }
    return owner;
}

struct StyleVariableLookupContext {
    StyleVariableState* state;
    ElementTreeNode const* consumerNode;
    std::vector<StyleVariableDependency>* outDeps;
};

bool IsValidStyleVariableIdentifier(std::wstring_view sv) {
    if (sv.empty()) return false;
    auto isStart = [](wchar_t c) {
        return (c >= L'A' && c <= L'Z') || (c >= L'a' && c <= L'z') || c == L'_';
    };
    auto isCont = [&](wchar_t c) {
        return isStart(c) || (c >= L'0' && c <= L'9');
    };
    if (!isStart(sv[0])) return false;
    for (size_t i = 1; i < sv.size(); i++) {
        if (!isCont(sv[i])) return false;
    }
    return true;
}

struct StyleExpressionValue {
    std::optional<double> number;
    std::wstring text;

    static StyleExpressionValue Number(double d) { return {d, std::wstring()}; }
    static StyleExpressionValue String(std::wstring s) { return {std::nullopt, std::move(s)}; }
    bool IsNumber() const { return number.has_value(); }
};

struct StyleVariableSkipRequested {};

class StyleVariableExpressionEvaluator {
public:
    StyleVariableExpressionEvaluator(std::wstring_view text, const StyleVariableLookupContext* context)
        : m_text(text), m_context(context) {}

    std::wstring Evaluate() {
        m_pos = 0;
        SkipWhitespace();
        StyleExpressionValue v = ParseExpression();
        SkipWhitespace();
        if (m_pos != m_text.size()) {
            throw std::runtime_error("Unexpected trailing characters in style variable expression");
        }
        if (v.IsNumber()) return FormatDoubleInvariant(*v.number);
        return v.text;
    }

private:
    void SkipWhitespace() {
        while (m_pos < m_text.size() && (m_text[m_pos] == L' ' || m_text[m_pos] == L'\t' || m_text[m_pos] == L'\r' || m_text[m_pos] == L'\n')) {
            m_pos++;
        }
    }

    bool ConsumeChar(wchar_t c) {
        SkipWhitespace();
        if (m_pos < m_text.size() && m_text[m_pos] == c) {
            m_pos++;
            return true;
        }
        return false;
    }

    bool ConsumeOperator(std::wstring_view op) {
        SkipWhitespace();
        if (m_text.size() - m_pos >= op.size() && m_text.compare(m_pos, op.size(), op) == 0) {
            m_pos += op.size();
            return true;
        }
        return false;
    }

    double RequireNumber(const StyleExpressionValue& v) {
        if (v.IsNumber()) return *v.number;
        if (m_live) throw std::runtime_error("Non-numeric value where number is required");
        return 0.0;
    }

    bool ValuesEqual(const StyleExpressionValue& a, const StyleExpressionValue& b) {
        if (a.IsNumber() && b.IsNumber()) return *a.number == *b.number;
        if (!a.IsNumber() && !b.IsNumber()) return a.text == b.text;
        return false;
    }

    StyleExpressionValue ParseExpression() { return ParseTernary(); }

    StyleExpressionValue ParseTernary() {
        StyleExpressionValue cond = ParseEquality();
        if (!ConsumeChar(L'?')) return cond;

        bool condTrue = RequireNumber(cond) != 0.0;
        bool prevLive = m_live;

        m_live = prevLive && condTrue;
        StyleExpressionValue thenVal = ParseExpression();
        m_live = prevLive;

        if (!ConsumeChar(L':')) throw std::runtime_error("Missing ':' in ternary");

        m_live = prevLive && !condTrue;
        StyleExpressionValue elseVal = ParseTernary();
        m_live = prevLive;

        return condTrue ? thenVal : elseVal;
    }

    StyleExpressionValue ParseEquality() {
        StyleExpressionValue v = ParseRelational();
        while (true) {
            if (ConsumeOperator(L"==")) v = StyleExpressionValue::Number(ValuesEqual(v, ParseRelational()) ? 1.0 : 0.0);
            else if (ConsumeOperator(L"!=")) v = StyleExpressionValue::Number(ValuesEqual(v, ParseRelational()) ? 0.0 : 1.0);
            else break;
        }
        return v;
    }

    StyleExpressionValue ParseRelational() {
        StyleExpressionValue v = ParseAdditive();
        while (true) {
            if (ConsumeOperator(L"<=")) {
                double lhs = RequireNumber(v);
                v = StyleExpressionValue::Number(lhs <= RequireNumber(ParseAdditive()) ? 1.0 : 0.0);
            } else if (ConsumeOperator(L">=")) {
                double lhs = RequireNumber(v);
                v = StyleExpressionValue::Number(lhs >= RequireNumber(ParseAdditive()) ? 1.0 : 0.0);
            } else if (ConsumeOperator(L"<")) {
                double lhs = RequireNumber(v);
                v = StyleExpressionValue::Number(lhs < RequireNumber(ParseAdditive()) ? 1.0 : 0.0);
            } else if (ConsumeOperator(L">")) {
                double lhs = RequireNumber(v);
                v = StyleExpressionValue::Number(lhs > RequireNumber(ParseAdditive()) ? 1.0 : 0.0);
            } else break;
        }
        return v;
    }

    StyleExpressionValue ParseAdditive() {
        StyleExpressionValue v = ParseTerm();
        while (true) {
            SkipWhitespace();
            if (ConsumeChar(L'+')) {
                double lhs = RequireNumber(v);
                v = StyleExpressionValue::Number(lhs + RequireNumber(ParseTerm()));
            } else if (ConsumeChar(L'-')) {
                double lhs = RequireNumber(v);
                v = StyleExpressionValue::Number(lhs - RequireNumber(ParseTerm()));
            } else break;
        }
        return v;
    }

    StyleExpressionValue ParseTerm() {
        StyleExpressionValue v = ParseFactor();
        while (true) {
            SkipWhitespace();
            if (ConsumeChar(L'*')) {
                double lhs = RequireNumber(v);
                v = StyleExpressionValue::Number(lhs * RequireNumber(ParseFactor()));
            } else if (ConsumeChar(L'/')) {
                double lhs = RequireNumber(v);
                double rhs = RequireNumber(ParseFactor());
                if (rhs == 0.0) {
                    if (m_live) throw std::runtime_error("Division by zero in style expression");
                    v = StyleExpressionValue::Number(lhs);
                } else {
                    v = StyleExpressionValue::Number(lhs / rhs);
                }
            } else break;
        }
        return v;
    }

    StyleExpressionValue ParseFactor() {
        SkipWhitespace();
        if (ConsumeChar(L'+')) return StyleExpressionValue::Number(RequireNumber(ParseFactor()));
        if (ConsumeChar(L'-')) return StyleExpressionValue::Number(-RequireNumber(ParseFactor()));
        return ParsePrimary();
    }

    StyleExpressionValue ParsePrimary() {
        SkipWhitespace();
        if (m_pos >= m_text.size()) throw std::runtime_error("Unexpected end of style expression");

        wchar_t c = m_text[m_pos];
        if (c == L'(') {
            m_pos++;
            StyleExpressionValue v = ParseExpression();
            SkipWhitespace();
            if (!ConsumeChar(L')')) throw std::runtime_error("Missing ')' in style expression");
            return v;
        }

        if (c == L'`') return ParseStringLiteral();
        if ((c >= L'0' && c <= L'9') || c == L'.') return StyleExpressionValue::Number(ParseNumberLiteral());
        if ((c >= L'A' && c <= L'Z') || (c >= L'a' && c <= L'z') || c == L'_') return ParseIdentifierOrCall();

        throw std::runtime_error("Unexpected character in style expression");
    }

    StyleExpressionValue ParseStringLiteral() {
        m_pos++;
        std::wstring out;
        while (m_pos < m_text.size()) {
            wchar_t c = m_text[m_pos];
            if (c == L'`') {
                if (m_pos + 1 < m_text.size() && m_text[m_pos + 1] == L'`') {
                    out.push_back(L'`');
                    m_pos += 2;
                    continue;
                }
                m_pos++;
                return StyleExpressionValue::String(std::move(out));
            }
            out.push_back(c);
            m_pos++;
        }
        throw std::runtime_error("Unterminated string literal in style expression");
    }

    double ParseNumberLiteral() {
        size_t start = m_pos;
        bool sawDigit = false, sawDot = false;
        while (m_pos < m_text.size()) {
            wchar_t c = m_text[m_pos];
            if (c >= L'0' && c <= L'9') { sawDigit = true; m_pos++; }
            else if (c == L'.' && !sawDot) { sawDot = true; m_pos++; }
            else break;
        }
        if (m_pos < m_text.size() && (m_text[m_pos] == L'e' || m_text[m_pos] == L'E')) {
            m_pos++;
            if (m_pos < m_text.size() && (m_text[m_pos] == L'+' || m_text[m_pos] == L'-')) m_pos++;
            while (m_pos < m_text.size() && m_text[m_pos] >= L'0' && m_text[m_pos] <= L'9') m_pos++;
        }
        if (!sawDigit) throw std::runtime_error("Bad number literal in style expression");
        auto parsed = ParseDoubleInvariant(m_text.substr(start, m_pos - start));
        if (!parsed) throw std::runtime_error("Bad number literal in style expression");
        return *parsed;
    }

    StyleExpressionValue ParseIdentifierOrCall() {
        size_t start = m_pos;
        while (m_pos < m_text.size()) {
            wchar_t c = m_text[m_pos];
            if ((c >= L'A' && c <= L'Z') || (c >= L'a' && c <= L'z') || (c >= L'0' && c <= L'9') || c == L'_') m_pos++;
            else break;
        }
        std::wstring_view ident = m_text.substr(start, m_pos - start);
        SkipWhitespace();
        if (m_pos < m_text.size() && m_text[m_pos] == L'(') {
            m_pos++;
            if (ident == L"skip") {
                if (!ConsumeChar(L')')) throw std::runtime_error("skip() takes no arguments");
                if (m_live) throw StyleVariableSkipRequested{};
                return StyleExpressionValue::Number(0.0);
            }
            double a = RequireNumber(ParseExpression());
            if (!ConsumeChar(L',')) throw std::runtime_error("Expected ',' in min/max call");
            double b = RequireNumber(ParseExpression());
            if (!ConsumeChar(L')')) throw std::runtime_error("Missing ')' in min/max call");
            if (ident == L"min") return StyleExpressionValue::Number((a < b) ? a : b);
            if (ident == L"max") return StyleExpressionValue::Number((a > b) ? a : b);
            if (m_live) throw std::runtime_error("Unknown function in style expression");
            return StyleExpressionValue::Number(0.0);
        }
        return LookupVariable(std::wstring(ident));
    }

    StyleExpressionValue LookupVariable(const std::wstring& name) {
        if (!m_live) return StyleExpressionValue::String(L"");

        auto resolution = FindWinningCapture(m_context->state, name, m_context->consumerNode);
        if (m_context->outDeps) {
            m_context->outDeps->push_back({name, resolution.owner});
        }
        if (!resolution.value) return StyleExpressionValue::String(L"");
        if (resolution.value->numeric) return StyleExpressionValue::Number(*resolution.value->numeric);
        if (resolution.value->substitutable) return StyleExpressionValue::String(resolution.value->stringForm);
        throw std::runtime_error("Style variable used in expression is not a primitive value");
    }

    std::wstring_view m_text;
    const StyleVariableLookupContext* m_context;
    size_t m_pos = 0;
    bool m_live = true;
};

std::optional<std::wstring> EvaluateStyleVariableExpression(std::wstring_view exprText, const StyleVariableLookupContext* context) {
    auto trimmed = TrimStringView(exprText);
    if (trimmed.empty()) return std::nullopt;

    if (IsValidStyleVariableIdentifier(trimmed)) {
        std::wstring name(trimmed);
        auto resolution = FindWinningCapture(context->state, name, context->consumerNode);
        if (context->outDeps) {
            context->outDeps->push_back({name, resolution.owner});
        }
        if (!resolution.value || !resolution.value->substitutable) return std::nullopt;
        return resolution.value->stringForm;
    }

    try {
        StyleVariableExpressionEvaluator eval(trimmed, context);
        return eval.Evaluate();
    } catch (StyleVariableSkipRequested const&) {
        throw;
    } catch (...) {
        return std::nullopt;
    }
}

std::optional<std::wstring> ExpandStyleVariables(std::wstring_view input, const StyleVariableLookupContext* context) {
    std::wstring result(input);
    size_t scanFrom = 0;

    while (true) {
        size_t closePos = std::wstring::npos;
        for (size_t i = scanFrom; i + 1 < result.size(); i++) {
            if (result[i] == L'}' && result[i + 1] == L'}') {
                closePos = i;
                break;
            }
        }
        if (closePos == std::wstring::npos) break;

        size_t openPos = std::wstring::npos;
        if (closePos >= 2) {
            for (size_t j = closePos - 1; j >= 1; j--) {
                if (result[j - 1] == L'{' && result[j] == L'{') {
                    openPos = j - 1;
                    break;
                }
                if (j == 1) break;
            }
        }

        if (openPos == std::wstring::npos) return std::nullopt;

        std::wstring_view exprText(result.data() + openPos + 2, closePos - openPos - 2);
        auto expanded = EvaluateStyleVariableExpression(exprText, context);
        if (!expanded) return std::nullopt;

        size_t spanLen = closePos + 2 - openPos;
        result.replace(openPos, spanLen, *expanded);
        scanFrom = openPos + expanded->size();
    }

    return result;
}

StyleVariableValue ReadCapturedStyleVariableValue(FrameworkElement element, DependencyProperty property) {
    StyleVariableValue out;
    auto elementDo = element.as<DependencyObject>();
    winrt::Windows::Foundation::IInspectable value{nullptr};
    try {
        value = elementDo.GetValue(property);
    } catch (...) {}

    if (!value || value == DependencyProperty::UnsetValue()) {
        out.stringForm = L"";
        return out;
    }

    try {
        if (auto unboxed = TryUnboxPropertyValue(value)) {
            out.stringForm = FormatUnboxedPropertyValue(*unboxed);
            out.numeric = UnboxedPropertyValueAsNumeric(*unboxed);
            out.substitutable = true;
            return out;
        }
        out.stringForm = std::wstring(winrt::get_class_name(value));
    } catch (...) {
        out.stringForm = L"";
    }
    return out;
}

void UpdateStyleVariableConsumers(
    StyleVariableState* state,
    ElementId elementId,
    DependencyProperty property,
    PCWSTR fallbackClassName,
    const std::vector<StyleVariableDependency>& oldDeps,
    const std::vector<StyleVariableDependency>& newDeps) {
    if (!state) return;

    for (const auto& dep : oldDeps) {
        auto it = state->consumers.find(dep.name);
        if (it == state->consumers.end()) continue;
        auto& consumers = it->second;
        ReleaseStyleVariableElementRefs(
            state, elementId,
            std::erase_if(consumers, [&](const StyleVariableConsumer& c) {
                return c.elementId == elementId && c.property == property;
            }));
        if (consumers.empty()) state->consumers.erase(it);
    }

    std::wstring fallbackClassNameStr = fallbackClassName ? fallbackClassName : L"";
    for (const auto& dep : newDeps) {
        auto& consumers = state->consumers[dep.name];
        bool already = std::any_of(consumers.begin(), consumers.end(),
                                   [&](const StyleVariableConsumer& c) {
                                       return c.elementId == elementId && c.property == property;
                                   });
        if (!already) {
            consumers.push_back({elementId, property, fallbackClassNameStr});
            AddStyleVariableElementRef(state, elementId);
        }
    }
}

template <typename T, typename... Ts>
std::optional<bool> SameBoxedStruct(winrt::Windows::Foundation::IInspectable const& a, winrt::Windows::Foundation::IInspectable const& b) {
    if (auto ra = a.try_as<winrt::Windows::Foundation::IReference<T>>()) {
        auto rb = b.try_as<winrt::Windows::Foundation::IReference<T>>();
        return rb && ra.Value() == rb.Value();
    }
    if constexpr (sizeof...(Ts) > 0) return SameBoxedStruct<Ts...>(a, b);
    else return std::nullopt;
}

bool SameLocalValue(winrt::Windows::Foundation::IInspectable const& a, winrt::Windows::Foundation::IInspectable const& b) {
    if (a == b) return true;
    if (!a || !b) return false;

    auto ua = TryUnboxPropertyValue(a);
    auto ub = TryUnboxPropertyValue(b);
    if (ua || ub) {
        return ua && ub &&
               std::visit(
                   [](auto const& x, auto const& y) -> bool {
                       using X = std::decay_t<decltype(x)>;
                       if constexpr (!std::is_same_v<X, std::decay_t<decltype(y)>>) return false;
                       else if constexpr (std::is_floating_point_v<X>) return x == y || (std::isnan(x) && std::isnan(y));
                       else return x == y;
                   },
                   *ua, *ub);
    }

    if (auto same = SameBoxedStruct<Thickness, CornerRadius, GridLength, winrt::Windows::Foundation::Point, winrt::Windows::Foundation::Size, winrt::Windows::Foundation::Rect, winrt::Windows::UI::Color, winrt::Windows::UI::Text::FontWeight>(a, b)) {
        return *same;
    }

    auto isBoxedValue = [](winrt::Windows::Foundation::IInspectable const& v) {
        return v.try_as<winrt::Windows::Foundation::IPropertyValue>() != nullptr ||
               std::wstring_view(winrt::get_class_name(v)).starts_with(L"Windows.Foundation.IReference`1<");
    };
    return isBoxedValue(a) && isBoxedValue(b);
}

void AdoptExternalValueAsOriginal(FrameworkElement element, DependencyProperty property, ElementPropertyCustomizationState* propertyCustomizationState) {
    if (!propertyCustomizationState->customValue) return;
    auto localValue = ReadLocalValueWithWorkaround(element, property);
    if (!SameLocalValue(localValue, propertyCustomizationState->lastAppliedValue)) {
        propertyCustomizationState->originalValue = localValue;
    }
}

winrt::Windows::Foundation::IInspectable SetOrClearValue(
    DependencyObject elementDo,
    DependencyProperty property,
    const PropertyOverrideValue& overrideValue,
    bool initialApply = false) {
    winrt::Windows::Foundation::IInspectable value;
    if (auto* inspectable = std::get_if<winrt::Windows::Foundation::IInspectable>(&overrideValue)) {
        value = *inspectable;
    } else if (auto* blurBrushParams = std::get_if<XamlBlurBrushParams>(&overrideValue)) {
        if (auto uiElement = elementDo.try_as<UIElement>()) {
            value = winrt::make<XamlBlurBrush>(
                uiElement, blurBrushParams->blurAmount, blurBrushParams->tint,
                blurBrushParams->tintOpacity,
                winrt::hstring(blurBrushParams->tintThemeResourceKey),
                blurBrushParams->tintLuminosityOpacity,
                blurBrushParams->tintSaturation, blurBrushParams->noiseOpacity,
                blurBrushParams->noiseDensity, blurBrushParams->fallbackColor,
                winrt::hstring(blurBrushParams->fallbackThemeResourceKey));
        } else {
            return nullptr;
        }
    } else {
        return nullptr;
    }

    if (winrt::get_class_name(elementDo) == L"Windows.UI.Xaml.Shapes.Rectangle" &&
        elementDo.as<FrameworkElement>().Name() == L"BackgroundFill" &&
        property == Shapes::Shape::FillProperty()) {
        auto it = std::find_if(g_delayedBackgroundFillSet.begin(), g_delayedBackgroundFillSet.end(),
                               [&elementDo](const auto& it) {
                                   if (auto elementDoIter = it.first.get()) return elementDoIter == elementDo;
                                   return false;
                               });

        if (value != DependencyProperty::UnsetValue() && initialApply && it == g_delayedBackgroundFillSet.end()) {
            auto asyncOp = elementDo.Dispatcher().TryRunAsync(
                winrt::Windows::UI::Core::CoreDispatcherPriority::High,
                [elementDo, property, value]() {
                    g_elementPropertyModifying = true;
                    try {
                        elementDo.SetValue(property, value);
                    } catch (...) {}
                    g_elementPropertyModifying = false;
                    std::erase_if(g_delayedBackgroundFillSet, [&elementDo](const auto& it) {
                        if (auto elementDoIter = it.first.get()) return elementDoIter == elementDo;
                        return false;
                    });
                });
            g_delayedBackgroundFillSet.emplace_back(elementDo, std::move(asyncOp));
            return value;
        } else if (it != g_delayedBackgroundFillSet.end()) {
            it->second.Cancel();
            g_delayedBackgroundFillSet.erase(it);
        }
    }

    if (value == DependencyProperty::UnsetValue()) {
        try { elementDo.ClearValue(property); } catch (...) {}
        return value;
    }

    if (auto imageBrush = value.try_as<Media::ImageBrush>()) {
        TrackIfRemoteImageSource(imageBrush, Media::ImageBrush::ImageSourceProperty(), imageBrush.ImageSource());
    } else if (auto imageBrush = elementDo.try_as<Media::ImageBrush>()) {
        if (property == Media::ImageBrush::ImageSourceProperty()) {
            TrackIfRemoteImageSource(imageBrush, property, value);
        }
    } else if (auto image = elementDo.try_as<Controls::Image>()) {
        if (property == Controls::Image::SourceProperty()) {
            TrackIfRemoteImageSource(image, property, value);
        }
    }

    try {
        if (property == Controls::TextBlock::FontWeightProperty() ||
            property == Controls::Control::FontWeightProperty() ||
            property == Controls::RichTextBlock::FontWeightProperty() ||
            property == Controls::FontIcon::FontWeightProperty() ||
            property == Controls::FontIconSource::FontWeightProperty() ||
            property == Controls::ContentPresenter::FontWeightProperty()) {
            auto valueInt = value.try_as<int>();
            if (valueInt && *valueInt >= std::numeric_limits<uint16_t>::min() && *valueInt <= std::numeric_limits<uint16_t>::max()) {
                value = winrt::box_value(winrt::Windows::UI::Text::FontWeight{static_cast<uint16_t>(*valueInt)});
            }
        }

        Controls::Grid definitionsCloneOwner{nullptr};
        if (auto sourceColumns = value.try_as<Controls::ColumnDefinitionCollection>()) {
            definitionsCloneOwner = Controls::Grid{};
            auto clonedColumns = definitionsCloneOwner.ColumnDefinitions();
            for (auto const& column : sourceColumns) {
                Controls::ColumnDefinition clonedColumn;
                clonedColumn.Width(column.Width());
                clonedColumn.MinWidth(column.MinWidth());
                clonedColumn.MaxWidth(column.MaxWidth());
                clonedColumns.Append(clonedColumn);
            }
            value = clonedColumns;
        } else if (auto sourceRows = value.try_as<Controls::RowDefinitionCollection>()) {
            definitionsCloneOwner = Controls::Grid{};
            auto clonedRows = definitionsCloneOwner.RowDefinitions();
            for (auto const& row : sourceRows) {
                Controls::RowDefinition clonedRow;
                clonedRow.Height(row.Height());
                clonedRow.MinHeight(row.MinHeight());
                clonedRow.MaxHeight(row.MaxHeight());
                clonedRows.Append(clonedRow);
            }
            value = clonedRows;
        }

        elementDo.SetValue(property, value);
    } catch (...) {}

    return value;
}

void UnapplyStyleValue(FrameworkElement element, DependencyProperty property, ElementPropertyCustomizationState* propertyCustomizationState) {
    AdoptExternalValueAsOriginal(element, property, propertyCustomizationState);
    if (propertyCustomizationState->originalValue) {
        bool wasModifying = g_elementPropertyModifying;
        g_elementPropertyModifying = true;
        SetOrClearValue(element, property, *propertyCustomizationState->originalValue);
        g_elementPropertyModifying = wasModifying;
        propertyCustomizationState->originalValue.reset();
    }
    propertyCustomizationState->lastAppliedValue = nullptr;
    propertyCustomizationState->customValue.reset();
}

std::optional<PropertyOverrideValue> ResolveDynamicStyleValue(
    StyleVariableState* state,
    ElementId elementId,
    FrameworkElement element,
    DependencyProperty property,
    PCWSTR fallbackClassName,
    ElementPropertyCustomizationState* propertyCustomizationState,
    ElementCustomizationState* elementCustomizationState) {
    if (!propertyCustomizationState->dynamicTemplate) return std::nullopt;

    const auto& tmpl = *propertyCustomizationState->dynamicTemplate;
    if (!elementCustomizationState) {
        if (auto it = g_elementsCustomizationState.find(elementId); it != g_elementsCustomizationState.end()) {
            elementCustomizationState = &it->second;
        }
    }

    ElementTreeNode const* consumerNode = elementCustomizationState ? EnsureElementTreeNode(*elementCustomizationState) : nullptr;
    std::vector<StyleVariableDependency> newDeps;
    StyleVariableLookupContext context{state, consumerNode, &newDeps};
    std::optional<std::wstring> expanded;
    bool skipped = false;
    try {
        expanded = ExpandStyleVariables(tmpl.rawValue, &context);
    } catch (StyleVariableSkipRequested const&) {
        skipped = true;
    }

    UpdateStyleVariableConsumers(state, elementId, property, fallbackClassName, propertyCustomizationState->variableDependencies, newDeps);
    propertyCustomizationState->variableDependencies = std::move(newDeps);

    if (skipped) {
        propertyCustomizationState->lastResolveFailed = false;
        UnapplyStyleValue(element, property, propertyCustomizationState);
        return std::nullopt;
    }

    if (!expanded) {
        propertyCustomizationState->lastResolveFailed = true;
        return std::nullopt;
    }

    auto typeName = winrt::get_class_name(element);
    auto resolved = ResolveExpandedSinglePropertyValue(
        std::wstring_view(typeName),
        fallbackClassName ? std::wstring_view(fallbackClassName) : winrt::name_of<FrameworkElement>(),
        tmpl.propertyName, *expanded, tmpl.isXamlValue);

    propertyCustomizationState->lastResolveFailed = !resolved;
    return resolved;
}

bool StyleVariableChangeAffectsConsumer(
    const ElementPropertyCustomizationState& propertyCustomizationState,
    const std::wstring& varName,
    std::optional<ElementId> changedOwner,
    ElementId winningOwner) {
    if (propertyCustomizationState.lastResolveFailed) return true;

    for (const auto& dep : propertyCustomizationState.variableDependencies) {
        if (dep.name != varName) continue;
        return changedOwner ? dep.owner == *changedOwner : dep.owner != winningOwner;
    }
    return false;
}

void PropagateStyleVariableChangeCore(StyleVariableState* state, const std::wstring& varName, std::optional<ElementId> changedOwner) {
    auto consumersIt = state->consumers.find(varName);
    if (consumersIt == state->consumers.end()) return;

    std::vector<StyleVariableCandidate> candidates;
    if (!changedOwner) {
        if (auto varIt = state->variables.find(varName); varIt != state->variables.end()) {
            candidates = SnapshotStyleVariableCaptures(varIt->second);
        }
    }

    auto consumersCopy = consumersIt->second;
    for (const auto& consumer : consumersCopy) {
        auto stateIt = g_elementsCustomizationState.find(consumer.elementId);
        if (stateIt == g_elementsCustomizationState.end()) continue;
        auto& elementState = stateIt->second;

        auto element = elementState.element.get();
        if (!element) continue;

        ElementId winningOwner = changedOwner ? ElementId::None : PickWinningCaptureOwner(candidates, EnsureElementTreeNode(elementState));
        PCWSTR consumerFallbackClassName = consumer.fallbackClassName.empty() ? nullptr : consumer.fallbackClassName.c_str();

        for (auto& [vsgWeak, vsgState] : elementState.perVisualStateGroup) {
            auto propIt = vsgState.propertyCustomizationStates.find(consumer.property);
            if (propIt == vsgState.propertyCustomizationStates.end()) continue;
            auto& propState = propIt->second;
            if (!propState.dynamicTemplate) continue;

            if (!StyleVariableChangeAffectsConsumer(propState, varName, changedOwner, winningOwner)) continue;

            auto resolved = ResolveDynamicStyleValue(state, consumer.elementId, element, consumer.property, consumerFallbackClassName, &propState, &elementState);
            if (!resolved) continue;

            AdoptExternalValueAsOriginal(element, consumer.property, &propState);
            if (!propState.originalValue) {
                propState.originalValue = ReadLocalValueWithWorkaround(element, consumer.property);
            }
            propState.customValue = *resolved;

            bool wasModifying = g_elementPropertyModifying;
            g_elementPropertyModifying = true;
            propState.lastAppliedValue = SetOrClearValue(element, consumer.property, *resolved);
            g_elementPropertyModifying = wasModifying;
        }
    }
}

void PropagateStyleVariableChange(StyleVariableState* state, const std::wstring& varName, std::optional<ElementId> changedOwner) {
    PendingStyleVariablePropagation propagation{state, varName, changedOwner};

    if (g_styleVariablePropagationDepth > 0) {
        auto& pending = g_pendingStyleVariablePropagations;
        if (std::find(pending.begin(), pending.end(), propagation) == pending.end()) {
            pending.push_back(std::move(propagation));
        }
        return;
    }

    StyleVariableStatePin statePin;
    struct DepthScope {
        DepthScope() { g_styleVariablePropagationDepth++; }
        ~DepthScope() { g_styleVariablePropagationDepth--; }
    } depthScope;

    PropagateStyleVariableChangeCore(state, varName, changedOwner);

    constexpr int kMaxDrainRounds = 32;
    for (int round = 0; !g_pendingStyleVariablePropagations.empty(); round++) {
        if (round >= kMaxDrainRounds) {
            g_pendingStyleVariablePropagations.clear();
            break;
        }

        auto pending = std::move(g_pendingStyleVariablePropagations);
        g_pendingStyleVariablePropagations.clear();
        for (const auto& pendingPropagation : pending) {
            PropagateStyleVariableChangeCore(pendingPropagation.state, pendingPropagation.varName, pendingPropagation.changedOwner);
        }
    }
}

bool SameNumericValue(const std::optional<double>& a, const std::optional<double>& b) {
    if (a.has_value() != b.has_value()) return false;
    return !a || *a == *b || (std::isnan(*a) && std::isnan(*b));
}

void SetStyleVariableIfChangedAndPropagate(StyleVariableState* state, const std::wstring& varName, ElementId owner, StyleVariableValue value) {
    auto varIt = state->variables.find(varName);
    if (varIt == state->variables.end()) return;

    auto& captures = varIt->second;
    auto it = std::find_if(captures.begin(), captures.end(), [owner](const StyleVariableCapture& capture) {
        return capture.elementId == owner;
    });
    if (it == captures.end()) return;

    if (it->value.stringForm == value.stringForm &&
        SameNumericValue(it->value.numeric, value.numeric) &&
        it->value.substitutable == value.substitutable) {
        return;
    }

    it->value = std::move(value);
    PropagateStyleVariableChange(state, varName, owner);
}

bool IsLayoutDrivenSizeProperty(DependencyProperty property) {
    return property == FrameworkElement::ActualWidthProperty() ||
           property == FrameworkElement::ActualHeightProperty();
}

void SetUpCapturesForElement(StyleVariableState* state, ElementId elementId, FrameworkElement element, const std::vector<CaptureSpec>& captures, ElementCustomizationState* elementState) {
    if (captures.empty()) return;

    auto elementDo = element.as<DependencyObject>();
    winrt::weak_ref<FrameworkElement> elementWeakRef = element;

    std::vector<std::wstring> seededVarNames;
    seededVarNames.reserve(captures.size());

    std::vector<std::pair<DependencyProperty, std::wstring>> sizeChangedCaptures;

    for (const auto& capture : captures) {
        const auto [it, inserted] = elementState->captureCustomizationStates.insert({capture.property, {}});
        if (!inserted) continue;

        auto& captureState = it->second;
        captureState.varName = capture.varName;

        auto value = ReadCapturedStyleVariableValue(element, capture.property);

        auto& capturesForVar = state->variables[capture.varName];
        capturesForVar.push_back({elementId, std::move(value)});
        AddStyleVariableElementRef(state, elementId);

        seededVarNames.push_back(capture.varName);

        if (IsLayoutDrivenSizeProperty(capture.property)) {
            sizeChangedCaptures.push_back({capture.property, capture.varName});
            continue;
        }

        std::wstring varName = capture.varName;
        captureState.propertyChangedToken = elementDo.RegisterPropertyChangedCallback(
            capture.property,
            [state, varName, elementId, elementWeakRef](DependencyObject sender, DependencyProperty property) {
                auto element = elementWeakRef.get();
                if (!element) return;
                auto value = ReadCapturedStyleVariableValue(element, property);
                SetStyleVariableIfChangedAndPropagate(state, varName, elementId, std::move(value));
            });
    }

    if (!sizeChangedCaptures.empty()) {
        elementState->captureSizeChangedToken = element.SizeChanged(
            [state, elementId, elementWeakRef, sizeChangedCaptures = std::move(sizeChangedCaptures)](
                winrt::Windows::Foundation::IInspectable const&, SizeChangedEventArgs const&) {
                auto element = elementWeakRef.get();
                if (!element) return;
                for (const auto& [property, varName] : sizeChangedCaptures) {
                    auto value = ReadCapturedStyleVariableValue(element, property);
                    SetStyleVariableIfChangedAndPropagate(state, varName, elementId, std::move(value));
                }
            });
    }

    for (const auto& varName : seededVarNames) {
        PropagateStyleVariableChange(state, varName, std::nullopt);
    }
}

void RestoreCapturesForElement(FrameworkElement element, const ElementCustomizationState& elementState) {
    if (!element) return;

    for (const auto& [property, captureState] : elementState.captureCustomizationStates) {
        if (!captureState.propertyChangedToken) continue;
        try {
            element.UnregisterPropertyChangedCallback(property, captureState.propertyChangedToken);
        } catch (...) {}
    }

    if (elementState.captureSizeChangedToken) {
        try {
            element.SizeChanged(elementState.captureSizeChangedToken);
        } catch (...) {}
    }
}

void ApplyCustomizationsForVisualStateGroup(
    StyleVariableState* state,
    ElementId elementId,
    FrameworkElement element,
    VisualStateGroup visualStateGroup,
    PCWSTR fallbackClassName,
    PropertyOverrides propertyOverrides,
    ElementCustomizationStateForVisualStateGroup* elementCustomizationStateForVisualStateGroup) {
    auto elementDo = element.as<DependencyObject>();

    VisualState currentVisualState(visualStateGroup ? visualStateGroup.CurrentState() : nullptr);
    std::wstring currentVisualStateName(currentVisualState ? currentVisualState.Name() : L"");

    for (const auto& [property, valuesPerVisualState] : propertyOverrides) {
        const auto [propertyCustomizationStatesIt, inserted] =
            elementCustomizationStateForVisualStateGroup->propertyCustomizationStates.insert({property, {}});
        if (!inserted) continue;

        auto& propertyCustomizationState = propertyCustomizationStatesIt->second;

        auto it = valuesPerVisualState.find(currentVisualStateName);
        if (it == valuesPerVisualState.end() && !currentVisualStateName.empty()) {
            it = valuesPerVisualState.find(L"");
        }

        if (it != valuesPerVisualState.end()) {
            std::optional<PropertyOverrideValue> resolved;
            if (auto* tmpl = std::get_if<DynamicStyleTemplate>(&it->second)) {
                propertyCustomizationState.dynamicTemplate = *tmpl;
                resolved = ResolveDynamicStyleValue(state, elementId, element, property, fallbackClassName, &propertyCustomizationState, nullptr);
            } else {
                resolved = it->second;
            }

            if (resolved) {
                propertyCustomizationState.originalValue = ReadLocalValueWithWorkaround(element, property);
                propertyCustomizationState.customValue = *resolved;
                propertyCustomizationState.lastAppliedValue = SetOrClearValue(element, property, *resolved, true);
            }
        }

        propertyCustomizationState.propertyChangedToken =
            elementDo.RegisterPropertyChangedCallback(
                property,
                [&propertyCustomizationState](DependencyObject sender, DependencyProperty property) {
                    if (g_elementPropertyModifying) return;
                    auto element = sender.try_as<FrameworkElement>();
                    if (!element || !propertyCustomizationState.customValue) return;

                    AdoptExternalValueAsOriginal(element, property, &propertyCustomizationState);

                    g_elementPropertyModifying = true;
                    propertyCustomizationState.lastAppliedValue = SetOrClearValue(element, property, *propertyCustomizationState.customValue);
                    g_elementPropertyModifying = false;
                });
    }

    if (visualStateGroup) {
        winrt::weak_ref<FrameworkElement> elementWeakRef = element;
        std::wstring fallbackClassNameStr = fallbackClassName ? fallbackClassName : L"";
        elementCustomizationStateForVisualStateGroup->visualStateGroupCurrentStateChangedToken =
            visualStateGroup.CurrentStateChanged(
                [state, elementWeakRef, propertyOverrides, elementId, fallbackClassNameStr, elementCustomizationStateForVisualStateGroup](
                    winrt::Windows::Foundation::IInspectable const&, VisualStateChangedEventArgs const& e) {
                    auto element = elementWeakRef.get();
                    if (!element) return;

                    g_elementPropertyModifying = true;
                    auto& propertyCustomizationStates = elementCustomizationStateForVisualStateGroup->propertyCustomizationStates;
                    PCWSTR fallbackClassNamePtr = fallbackClassNameStr.empty() ? nullptr : fallbackClassNameStr.c_str();

                    for (const auto& [property, valuesPerVisualState] : propertyOverrides) {
                        auto& propertyCustomizationState = propertyCustomizationStates.at(property);

                        auto newState = e.NewState();
                        auto newStateName = std::wstring{newState ? newState.Name() : L""};
                        auto it = valuesPerVisualState.find(newStateName);
                        if (it == valuesPerVisualState.end()) {
                            it = valuesPerVisualState.find(L"");
                            if (it != valuesPerVisualState.end()) {
                                auto oldState = e.OldState();
                                auto oldStateName = std::wstring{oldState ? oldState.Name() : L""};
                                if (!valuesPerVisualState.contains(oldStateName)) continue;
                            }
                        }

                        if (it != valuesPerVisualState.end()) {
                            std::optional<PropertyOverrideValue> resolved;
                            if (auto* tmpl = std::get_if<DynamicStyleTemplate>(&it->second)) {
                                propertyCustomizationState.dynamicTemplate = *tmpl;
                                resolved = ResolveDynamicStyleValue(state, elementId, element, property, fallbackClassNamePtr, &propertyCustomizationState, nullptr);
                            } else {
                                if (propertyCustomizationState.dynamicTemplate) {
                                    UpdateStyleVariableConsumers(state, elementId, property, nullptr, propertyCustomizationState.variableDependencies, {});
                                    propertyCustomizationState.variableDependencies.clear();
                                    propertyCustomizationState.dynamicTemplate.reset();
                                }
                                resolved = it->second;
                            }

                            if (resolved) {
                                AdoptExternalValueAsOriginal(element, property, &propertyCustomizationState);
                                if (!propertyCustomizationState.originalValue) {
                                    propertyCustomizationState.originalValue = ReadLocalValueWithWorkaround(element, property);
                                }
                                propertyCustomizationState.customValue = *resolved;
                                propertyCustomizationState.lastAppliedValue = SetOrClearValue(element, property, *resolved);
                            }
                        } else {
                            if (propertyCustomizationState.dynamicTemplate) {
                                UpdateStyleVariableConsumers(state, elementId, property, nullptr, propertyCustomizationState.variableDependencies, {});
                                propertyCustomizationState.variableDependencies.clear();
                                propertyCustomizationState.dynamicTemplate.reset();
                            }
                            UnapplyStyleValue(element, property, &propertyCustomizationState);
                        }
                    }

                    g_elementPropertyModifying = false;
                });
    }
}

void RestoreCustomizationsForVisualStateGroup(
    StyleVariableState* state,
    ElementId elementId,
    FrameworkElement element,
    std::optional<winrt::weak_ref<VisualStateGroup>> visualStateGroupOptionalWeakPtr,
    const ElementCustomizationStateForVisualStateGroup& elementCustomizationStateForVisualStateGroup) {
    if (element) {
        for (const auto& [property, propState] : elementCustomizationStateForVisualStateGroup.propertyCustomizationStates) {
            try {
                element.UnregisterPropertyChangedCallback(property, propState.propertyChangedToken);
            } catch (...) {}

            if (!propState.variableDependencies.empty()) {
                UpdateStyleVariableConsumers(state, elementId, property, nullptr, propState.variableDependencies, {});
            }

            if (propState.originalValue) {
                SetOrClearValue(element, property, *propState.originalValue);
            }
        }
    } else {
        for (const auto& [property, propState] : elementCustomizationStateForVisualStateGroup.propertyCustomizationStates) {
            if (!propState.variableDependencies.empty()) {
                UpdateStyleVariableConsumers(state, elementId, property, nullptr, propState.variableDependencies, {});
            }
        }
    }

    auto visualStateGroupIter = visualStateGroupOptionalWeakPtr ? visualStateGroupOptionalWeakPtr->get() : nullptr;
    if (visualStateGroupIter && elementCustomizationStateForVisualStateGroup.visualStateGroupCurrentStateChangedToken) {
        try {
            visualStateGroupIter.CurrentStateChanged(elementCustomizationStateForVisualStateGroup.visualStateGroupCurrentStateChangedToken);
        } catch (...) {}
    }
}

thread_local std::unordered_set<ElementId> g_recycledElements;
thread_local std::unordered_map<ElementId, winrt::weak_ref<wf::IInspectable>> g_elementMatchedItems;

struct VirtualizingRepeaterState {
    muxc::ItemsRepeater::ElementClearing_revoker elementClearingRevoker;
    muxc::ItemsRepeater::ElementPrepared_revoker elementPreparedRevoker;
};

thread_local std::unordered_map<ElementId, VirtualizingRepeaterState> g_virtualizingRepeaters;

ElementId ElementIdFromElement(FrameworkElement const& element) {
    if (!element) return ElementId::None;
    try {
        auto it = g_elementIds.find(HandleFromInspectable(element));
        if (it == g_elementIds.end() || it->second.element.get() != element) return ElementId::None;
        return it->second.id;
    } catch (...) {
        return ElementId::None;
    }
}

void ReapplyCustomizationsForSubtree(FrameworkElement element) {
    try {
        if (auto elementId = ElementIdFromElement(element); elementId != ElementId::None) {
            CleanupCustomizations(elementId);
            auto className = winrt::get_class_name(element);
            ApplyCustomizations(elementId, element, className.c_str());
        }
    } catch (...) {}

    std::vector<FrameworkElement> children;
    try {
        int count = Media::VisualTreeHelper::GetChildrenCount(element);
        for (int i = 0; i < count; i++) {
            if (auto child = Media::VisualTreeHelper::GetChild(element, i).try_as<FrameworkElement>()) {
                children.push_back(std::move(child));
            }
        }
    } catch (...) {
        return;
    }

    for (const auto& child : children) {
        ReapplyCustomizationsForSubtree(child);
    }
}

winrt::weak_ref<wf::IInspectable> RepeaterItemAt(muxc::ItemsRepeater const& repeater, int index) {
    try {
        auto itemsSourceView = repeater.ItemsSourceView();
        if (!itemsSourceView || index < 0 || index >= itemsSourceView.Count()) return nullptr;
        return TryMakeWeak(itemsSourceView.GetAt(index));
    } catch (...) {
        return nullptr;
    }
}

void HandleVirtualizingRepeater(ElementId elementId, FrameworkElement element) {
    auto repeater = element.try_as<muxc::ItemsRepeater>();
    if (!repeater || g_virtualizingRepeaters.contains(elementId)) return;

    auto& state = g_virtualizingRepeaters[elementId];

    state.elementClearingRevoker = repeater.ElementClearing(
        winrt::auto_revoke,
        [](muxc::ItemsRepeater const&, muxc::ItemsRepeaterElementClearingEventArgs const& args) {
            auto element = args.Element().try_as<FrameworkElement>();
            if (!element) return;
            auto elementId = ElementIdFromElement(element);
            if (elementId == ElementId::None) return;
            g_recycledElements.insert(elementId);
        });

    state.elementPreparedRevoker = repeater.ElementPrepared(
        winrt::auto_revoke,
        [](muxc::ItemsRepeater const& sender, muxc::ItemsRepeaterElementPreparedEventArgs const& args) {
            auto element = args.Element().try_as<FrameworkElement>();
            if (!element) return;
            auto elementId = ElementIdFromElement(element);
            if (elementId == ElementId::None) return;

            auto item = RepeaterItemAt(sender, args.Index());
            auto strongItem = item.get();

            if (!g_recycledElements.erase(elementId)) {
                if (strongItem) g_elementMatchedItems[elementId] = std::move(item);
                return;
            }

            if (strongItem) {
                auto it = g_elementMatchedItems.find(elementId);
                if (it != g_elementMatchedItems.end() && it->second.get() == strongItem) return;
            }

            ReapplyCustomizationsForSubtree(element);
            if (strongItem) g_elementMatchedItems[elementId] = std::move(item);
        });
}

void MergeResourceVariables();


using StyleConstant = std::pair<std::wstring, std::wstring>;
using StyleConstants = std::vector<StyleConstant>;

std::wstring ApplyStyleConstants(std::wstring_view style, const StyleConstants& styleConstants) {
    std::wstring result;
    size_t lastPos = 0, findPos;

    while ((findPos = style.find('$', lastPos)) != style.npos) {
        result.append(style, lastPos, findPos - lastPos);

        const StyleConstant* constant = nullptr;
        for (const auto& s : styleConstants) {
            if (s.first == style.substr(findPos + 1, s.first.size())) {
                constant = &s;
                break;
            }
        }

        if (constant) {
            result += constant->second;
            lastPos = findPos + 1 + constant->first.size();
        } else {
            result += '$';
            lastPos = findPos + 1;
        }
    }

    result += style.substr(lastPos);
    return result;
}

std::optional<StyleConstant> ParseStyleConstant(std::wstring_view constant, const StyleConstants& styleConstants) {
    if (constant.starts_with(L"//")) return std::nullopt;

    auto eqPos = constant.find(L'=');
    if (eqPos == constant.npos) return std::nullopt;

    auto key = TrimStringView(constant.substr(0, eqPos));
    auto valueRaw = TrimStringView(constant.substr(eqPos + 1));
    auto value = ApplyStyleConstants(valueRaw, styleConstants);

    return StyleConstant{std::wstring(key), std::move(value)};
}

StyleConstants LoadStyleConstants() {
    StyleConstants result;
    auto addToResult = [&result](StyleConstant sc) {
        auto insertIndex = std::lower_bound(
            result.begin(), result.end(), sc,
            [](const StyleConstant& a, const StyleConstant& b) {
                return a.first.size() > b.first.size();
            });
        result.insert(insertIndex, std::move(sc));
    };

    for (int i = 0;; i++) {
        PCWSTR constantSetting = Wh_GetStringSetting(L"Styling.styleConstants[%d]", i);
        if (!*constantSetting) {
            Wh_FreeStringSetting(constantSetting);
            break;
        }

        if (auto parsed = ParseStyleConstant(constantSetting, result)) {
            addToResult(std::move(*parsed));
        }
        Wh_FreeStringSetting(constantSetting);
    }
    return result;
}


enum class ResourceVariableTheme { None, Dark, Light };
enum class ResourceVariableType { String, Xaml, ThemeResourceReference };

struct ResourceVariableEntry {
    std::wstring key;
    std::wstring value;
    ResourceVariableTheme theme;
    ResourceVariableType type;
};

thread_local std::vector<ResourceVariableEntry> g_resourceVariables;
thread_local std::unordered_map<std::wstring, winrt::Windows::Foundation::IInspectable> g_originalResourceValues;
thread_local ResourceDictionary g_resourceVariablesThemeDict{nullptr};
thread_local winrt::Windows::UI::ViewManagement::UISettings g_uiSettings{nullptr};
thread_local winrt::event_token g_colorValuesChangedToken;

std::optional<ResourceVariableEntry> ParseResourceVariable(std::wstring_view entry, const StyleConstants& styleConstants) {
    if (entry.starts_with(L"//")) return std::nullopt;

    auto eqPos = entry.find(L'=');
    if (eqPos == entry.npos) return std::nullopt;

    auto keyPart = TrimStringView(entry.substr(0, eqPos));
    auto valueRaw = TrimStringView(entry.substr(eqPos + 1));
    auto value = ApplyStyleConstants(valueRaw, styleConstants);

    constexpr std::wstring_view kThemeResourcePrefix = L"{ThemeResource ";
    ResourceVariableType type = ResourceVariableType::String;

    if (keyPart.size() > 0 && keyPart.back() == L':') {
        type = ResourceVariableType::Xaml;
        keyPart = TrimStringView(keyPart.substr(0, keyPart.size() - 1));
    } else if (value.starts_with(kThemeResourcePrefix) && value.ends_with(L"}")) {
        type = ResourceVariableType::ThemeResourceReference;
        value = TrimStringView(value.substr(kThemeResourcePrefix.size(), value.size() - kThemeResourcePrefix.size() - 1));
    }

    ResourceVariableTheme theme = ResourceVariableTheme::None;
    std::wstring key;

    auto atPos = keyPart.find(L'@');
    if (atPos != keyPart.npos) {
        key = TrimStringView(keyPart.substr(0, atPos));
        auto themePart = TrimStringView(keyPart.substr(atPos + 1));
        if (themePart == L"Dark") theme = ResourceVariableTheme::Dark;
        else if (themePart == L"Light") theme = ResourceVariableTheme::Light;
        else return std::nullopt;
    } else {
        key = std::wstring(keyPart);
    }

    return ResourceVariableEntry{std::move(key), std::move(value), theme, type};
}

winrt::Windows::Foundation::IInspectable ParseXamlValue(std::wstring_view xamlValue) {
    std::wstring xaml;
    xaml += L"        <Setter Property=\"Tag\">\n            <Setter.Value>\n";
    xaml += xamlValue;
    xaml += L"\n            </Setter.Value>\n        </Setter>\n";

    auto style = GetStyleFromXamlSetters(L"FrameworkElement", xaml);
    return style.Setters().GetAt(0).as<Setter>().Value();
}

bool ProcessResourceVariable(ResourceDictionary resources, ResourceDictionary darkDict, ResourceDictionary lightDict, const ResourceVariableEntry& entry) {
    auto boxedKey = winrt::box_value(entry.key);

    if (entry.theme != ResourceVariableTheme::None) {
        ResourceDictionary& targetDict = (entry.theme == ResourceVariableTheme::Dark) ? darkDict : lightDict;
        if (targetDict.HasKey(boxedKey)) return false;

        winrt::Windows::Foundation::IInspectable value;
        switch (entry.type) {
            case ResourceVariableType::String:
                value = winrt::box_value(entry.value);
                break;
            case ResourceVariableType::Xaml:
                value = entry.value.empty() ? nullptr : ParseXamlValue(entry.value);
                break;
            case ResourceVariableType::ThemeResourceReference:
                value = resources.Lookup(winrt::box_value(entry.value));
                break;
        }

        targetDict.Insert(boxedKey, value);
        return true;
    }

    auto existingResource = resources.TryLookup(boxedKey);
    if (!existingResource) return false;

    auto [it, inserted] = g_originalResourceValues.try_emplace(entry.key, existingResource);
    if (!inserted) return false;

    winrt::Windows::Foundation::IInspectable value;
    switch (entry.type) {
        case ResourceVariableType::String: {
            auto resourceClassName = winrt::get_class_name(existingResource);
            if (resourceClassName.starts_with(L"Windows.Foundation.IReference`1<") && resourceClassName.ends_with(L'>')) {
                size_t prefixSize = sizeof("Windows.Foundation.IReference`1<") - 1;
                resourceClassName = winrt::hstring(resourceClassName.data() + prefixSize, resourceClassName.size() - prefixSize - 1);
            }
            value = Markup::XamlBindingHelper::ConvertValue(Interop::TypeName{resourceClassName}, winrt::box_value(entry.value));
            break;
        }
        case ResourceVariableType::Xaml:
            value = entry.value.empty() ? nullptr : ParseXamlValue(entry.value);
            break;
        case ResourceVariableType::ThemeResourceReference:
            value = resources.Lookup(winrt::box_value(entry.value));
            break;
    }

    resources.Insert(boxedKey, value);
    return true;
}

void RefreshThemeResourceEntries() {
    if (g_resourceVariables.empty()) return;

    auto resources = Application::Current().Resources();
    auto darkDict = g_resourceVariablesThemeDict.ThemeDictionaries().TryLookup(winrt::box_value(L"Dark")).try_as<ResourceDictionary>();
    auto lightDict = g_resourceVariablesThemeDict.ThemeDictionaries().TryLookup(winrt::box_value(L"Light")).try_as<ResourceDictionary>();

    for (const auto& entry : g_resourceVariables) {
        if (entry.type != ResourceVariableType::ThemeResourceReference) continue;

        try {
            auto boxedKey = winrt::box_value(entry.key);
            auto value = resources.Lookup(winrt::box_value(entry.value));

            if (entry.theme == ResourceVariableTheme::Dark && darkDict) {
                darkDict.Insert(boxedKey, value);
            } else if (entry.theme == ResourceVariableTheme::Light && lightDict) {
                lightDict.Insert(boxedKey, value);
            } else {
                resources.Insert(boxedKey, value);
            }
        } catch (...) {}
    }
}

std::vector<ResourceVariableEntry> ProcessResourceVariablesFromSettings(const StyleConstants& styleConstants) {
    std::vector<ResourceVariableEntry> resourceVariables;

    for (int i = 0;; i++) {
        PCWSTR setting = Wh_GetStringSetting(L"Styling.themeResourceVariables[%d]", i);
        if (!*setting) {
            Wh_FreeStringSetting(setting);
            break;
        }

        auto parsed = ParseResourceVariable(setting, styleConstants);
        if (parsed) {
            resourceVariables.push_back(std::move(*parsed));
        }
        Wh_FreeStringSetting(setting);
    }

    return resourceVariables;
}

void MergeResourceVariables() {
    auto resources = Application::Current().Resources();

    g_resourceVariablesThemeDict = ResourceDictionary();
    ResourceDictionary darkDict;
    ResourceDictionary lightDict;
    bool hasThemeResources = false;
    bool hasThemeResourceReferences = false;

    for (auto it = g_resourceVariables.rbegin(); it != g_resourceVariables.rend(); ++it) {
        try {
            if (ProcessResourceVariable(resources, darkDict, lightDict, *it)) {
                if (it->theme != ResourceVariableTheme::None) hasThemeResources = true;
                if (it->type == ResourceVariableType::ThemeResourceReference) hasThemeResourceReferences = true;
            }
        } catch (...) {}
    }

    if (hasThemeResources) {
        g_resourceVariablesThemeDict.ThemeDictionaries().Insert(winrt::box_value(L"Dark"), darkDict);
        g_resourceVariablesThemeDict.ThemeDictionaries().Insert(winrt::box_value(L"Light"), lightDict);
        resources.MergedDictionaries().Append(g_resourceVariablesThemeDict);
    }

    if (hasThemeResourceReferences) {
        g_uiSettings = winrt::Windows::UI::ViewManagement::UISettings();
        auto dispatcherQueue = winrt::Windows::System::DispatcherQueue::GetForCurrentThread();
        g_colorValuesChangedToken = g_uiSettings.ColorValuesChanged([dispatcherQueue](auto&&, auto&&) {
            dispatcherQueue.TryEnqueue(RefreshThemeResourceEntries);
        });
    }
}

void UninitializeResourceVariables() {
    if (g_colorValuesChangedToken) {
        g_uiSettings.ColorValuesChanged(g_colorValuesChangedToken);
        g_colorValuesChangedToken = {};
    }
    g_uiSettings = nullptr;
    g_resourceVariables.clear();

    auto resources = Application::Current().Resources();
    for (const auto& [key, originalValue] : g_originalResourceValues) {
        try {
            resources.Insert(winrt::box_value(key), originalValue);
        } catch (...) {}
    }
    g_originalResourceValues.clear();

    if (g_resourceVariablesThemeDict) {
        auto merged = resources.MergedDictionaries();
        uint32_t index;
        if (merged.IndexOf(g_resourceVariablesThemeDict, index)) {
            merged.RemoveAt(index);
        }
        g_resourceVariablesThemeDict = nullptr;
    }
}


void ApplyCustomizations(ElementId elementId, FrameworkElement element, PCWSTR fallbackClassName) {
    if (!g_resourceVariablesThemeDict) {
        MergeResourceVariables();
    }

    HandleVirtualizingRepeater(elementId, element);

    StyleVariableStatePin statePin;
    auto* state = GetStyleVariableState(element);
    if (!state) return;

    auto resolved = FindElementPropertyOverrides(element, fallbackClassName);
    if (resolved.overridesPerVSG.empty() && resolved.captures.empty()) return;

    auto& elementCustomizationState = g_elementsCustomizationState[elementId];

    for (const auto& [visualStateGroupOptionalWeakPtrIter, stateIter] : elementCustomizationState.perVisualStateGroup) {
        RestoreCustomizationsForVisualStateGroup(state, elementId, element, visualStateGroupOptionalWeakPtrIter, stateIter);
    }

    elementCustomizationState.element = element;
    elementCustomizationState.xamlRoot = state->xamlRoot;
    elementCustomizationState.perVisualStateGroup.clear();

    elementCustomizationState.treeNode = nullptr;
    if (!resolved.captures.empty() || resolved.hasDynamicValues) {
        elementCustomizationState.treeNode = GetOrCreateElementTreeNode(element);
    }

    SetUpCapturesForElement(state, elementId, element, resolved.captures, &elementCustomizationState);

    for (auto& [visualStateGroup, overridesForVisualStateGroup] : resolved.overridesPerVSG) {
        std::optional<winrt::weak_ref<VisualStateGroup>> visualStateGroupOptionalWeakPtr;
        if (visualStateGroup) visualStateGroupOptionalWeakPtr = visualStateGroup;

        elementCustomizationState.perVisualStateGroup.push_back({visualStateGroupOptionalWeakPtr, {}});
        auto* elementCustomizationStateForVisualStateGroup = &elementCustomizationState.perVisualStateGroup.back().second;

        ApplyCustomizationsForVisualStateGroup(state, elementId, element, visualStateGroup, fallbackClassName,
                                                std::move(overridesForVisualStateGroup),
                                                elementCustomizationStateForVisualStateGroup);
    }
}

thread_local std::vector<InstanceHandle> g_pendingDiagnosticsRelease;
thread_local ULONGLONG g_lastDiagnosticsReleaseQueueTick;
thread_local bool g_diagnosticsReleaseDrainQueued;
thread_local winrt::Windows::System::DispatcherQueueTimer g_diagnosticsReleaseDrainTimer{nullptr};
thread_local winrt::Windows::System::DispatcherQueueTimer::Tick_revoker g_diagnosticsReleaseDrainTimerTickRevoker;

constexpr ULONGLONG kDiagnosticsReleaseDelay = 200;
constexpr ULONGLONG kDiagnosticsReleaseDrainDelay = 1;

bool ElementHasState(ElementId elementId) {
    if (elementId == ElementId::None) return false;

    if (g_elementsCustomizationState.contains(elementId) ||
        g_virtualizingRepeaters.contains(elementId) ||
        g_recycledElements.contains(elementId) ||
        g_elementMatchedItems.contains(elementId)) {
        return true;
    }

    for (const auto& state : g_styleVariableState) {
        if (state.elementRefs.contains(elementId)) return true;
    }

    for (const auto& propagation : g_pendingStyleVariablePropagations) {
        if (propagation.changedOwner == elementId) return true;
    }

    return false;
}

void FlushDiagnosticsReleases() {
    auto pending = std::move(g_pendingDiagnosticsRelease);
    g_pendingDiagnosticsRelease.clear();

    if (!g_visualTreeWatcher) return;

    std::sort(pending.begin(), pending.end());
    pending.erase(std::unique(pending.begin(), pending.end()), pending.end());

    for (InstanceHandle handle : pending) {
        if (ElementHasState(FindElementId(handle))) continue;
        if (g_visualTreeWatcher->ReleaseDiagnosticsReference(handle)) {
            ForgetElementId(handle);
        }
    }

    ReapDeadElementIdsIfNeeded();
}

void QueueDiagnosticsRelease(InstanceHandle handle) {
    if (!handle) return;
    g_pendingDiagnosticsRelease.push_back(handle);
    g_lastDiagnosticsReleaseQueueTick = GetTickCount64();
}

void DrainDiagnosticsReleases() {
    g_diagnosticsReleaseDrainQueued = false;
    FlushDiagnosticsReleases();
}

void FlushDiagnosticsReleasesIfQuiet() {
    if (g_pendingDiagnosticsRelease.empty() || g_diagnosticsReleaseDrainQueued ||
        GetTickCount64() - g_lastDiagnosticsReleaseQueueTick < kDiagnosticsReleaseDelay) {
        return;
    }

    try {
        if (!g_diagnosticsReleaseDrainTimer) {
            auto dispatcherQueue = winrt::Windows::System::DispatcherQueue::GetForCurrentThread();
            if (!dispatcherQueue) return;

            g_diagnosticsReleaseDrainTimer = dispatcherQueue.CreateTimer();
            g_diagnosticsReleaseDrainTimer.IsRepeating(false);
            g_diagnosticsReleaseDrainTimer.Interval(std::chrono::milliseconds{kDiagnosticsReleaseDrainDelay});
            g_diagnosticsReleaseDrainTimerTickRevoker = g_diagnosticsReleaseDrainTimer.Tick(
                winrt::auto_revoke,
                [](winrt::Windows::System::DispatcherQueueTimer const&, winrt::Windows::Foundation::IInspectable const&) {
                    DrainDiagnosticsReleases();
                });
        }

        g_diagnosticsReleaseDrainTimer.Start();
        g_diagnosticsReleaseDrainQueued = true;
    } catch (...) {}
}

void StopDiagnosticsReleases() {
    g_pendingDiagnosticsRelease.clear();
    if (g_diagnosticsReleaseDrainTimer) {
        try { g_diagnosticsReleaseDrainTimer.Stop(); } catch (...) {}
    }
    g_diagnosticsReleaseDrainTimerTickRevoker.revoke();
    g_diagnosticsReleaseDrainTimer = nullptr;
    g_diagnosticsReleaseDrainQueued = false;
}

void CleanupCustomizations(ElementId elementId) {
    g_virtualizingRepeaters.erase(elementId);
    g_recycledElements.erase(elementId);
    g_elementMatchedItems.erase(elementId);

    auto it = g_elementsCustomizationState.find(elementId);
    if (it == g_elementsCustomizationState.end()) return;

    auto& elementCustomizationState = it->second;
    StyleVariableStatePin statePin;

    auto element = elementCustomizationState.element.get();
    auto* state = GetStyleVariableState(elementCustomizationState.xamlRoot);

    RestoreCapturesForElement(element, elementCustomizationState);

    std::vector<std::wstring> removedVarNames;
    if (state) {
        for (const auto& [property, captureState] : elementCustomizationState.captureCustomizationStates) {
            if (captureState.varName.empty()) continue;
            auto varIt = state->variables.find(captureState.varName);
            if (varIt == state->variables.end()) continue;

            size_t removed = std::erase_if(varIt->second, [elementId](const StyleVariableCapture& capture) {
                return capture.elementId == elementId;
            });
            if (!removed) continue;

            ReleaseStyleVariableElementRefs(state, elementId, removed);
            removedVarNames.push_back(captureState.varName);
            if (varIt->second.empty()) state->variables.erase(varIt);
        }
    }

    for (const auto& [visualStateGroupOptionalWeakPtrIter, stateIter] : elementCustomizationState.perVisualStateGroup) {
        RestoreCustomizationsForVisualStateGroup(state, elementId, element, visualStateGroupOptionalWeakPtrIter, stateIter);
    }

    g_elementsCustomizationState.erase(elementId);
    ReapElementTreeNodesIfNeeded();

    for (const auto& varName : removedVarNames) {
        PropagateStyleVariableChange(state, varName, std::nullopt);
    }
}

ElementMatcher ElementMatcherFromString(std::wstring_view str) {
    ElementMatcher result;
    PropertyValuesUnresolved propertyValuesUnresolved;

    auto trimmed = TrimStringView(str);
    if (trimmed == L"*") {
        result.kind = ElementMatcher::Kind::Wildcard;
        return result;
    }
    if (trimmed == L":root") {
        result.kind = ElementMatcher::Kind::Root;
        return result;
    }

    auto i = str.find_first_of(L"#@[");
    result.type = TrimStringView(str.substr(0, i));
    if (result.type.empty()) {
        throw std::runtime_error("Bad target syntax, empty type");
    }

    while (i != str.npos) {
        auto iNext = str.find_first_of(L"#@[", i + 1);
        auto nextPart = str.substr(i + 1, iNext == str.npos ? str.npos : iNext - (i + 1));

        switch (str[i]) {
            case L'#':
                if (!result.name.empty()) throw std::runtime_error("Bad target syntax, more than one name");
                result.name = TrimStringView(nextPart);
                if (result.name.empty()) throw std::runtime_error("Bad target syntax, empty name");
                break;
            case L'@':
                if (result.visualStateGroupName) throw std::runtime_error("Bad target syntax, more than one visual state group");
                result.visualStateGroupName = TrimStringView(nextPart);
                break;
            case L'[': {
                auto rule = TrimStringView(nextPart);
                if (rule.length() == 0 || rule.back() != L']') throw std::runtime_error("Bad target syntax, missing ']'");
                rule = TrimStringView(rule.substr(0, rule.length() - 1));
                if (rule.length() == 0) throw std::runtime_error("Bad target syntax, empty property");

                if (rule.find_first_not_of(L"0123456789") == rule.npos) {
                    result.oneBasedIndex = std::stoi(std::wstring(rule));
                    break;
                }

                auto ruleEqPos = rule.find(L'=');
                if (ruleEqPos == rule.npos) throw std::runtime_error("Bad target syntax, missing '=' in property");

                auto ruleKey = TrimStringView(rule.substr(0, ruleEqPos));
                auto ruleVal = TrimStringView(rule.substr(ruleEqPos + 1));
                if (ruleKey.length() == 0) throw std::runtime_error("Bad target syntax, empty property name");

                propertyValuesUnresolved.push_back({std::wstring(ruleKey), std::wstring(ruleVal)});
                break;
            }
            default:
                throw std::runtime_error("Bad target syntax");
        }
        i = iNext;
    }

    result.propertyValues = std::move(propertyValuesUnresolved);
    return result;
}

std::variant<ValueRule, CaptureRule> ParseRule(std::wstring_view str) {
    auto eqPos = str.find(L'=');
    if (eqPos == str.npos) throw std::runtime_error("Bad style syntax, '=' is missing");

    auto name = str.substr(0, eqPos);
    auto value = str.substr(eqPos + 1);

    if (!value.empty() && value.front() == L'>') {
        value = value.substr(1);

        if (!name.empty() && name.back() == L':') {
            throw std::runtime_error("Bad style syntax, ':=>' is not valid");
        }
        if (name.find(L'@') != name.npos) {
            throw std::runtime_error("Bad style syntax, '@VisualState' not allowed on capture rule");
        }

        auto trimmedPropertyName = TrimStringView(name);
        if (trimmedPropertyName.empty()) throw std::runtime_error("Bad style syntax, empty name");
        auto trimmedVarName = TrimStringView(value);
        if (trimmedVarName.empty() || !IsValidStyleVariableIdentifier(trimmedVarName)) {
            throw std::runtime_error("Bad style syntax, invalid capture variable name");
        }

        return CaptureRule{std::wstring(trimmedPropertyName), std::wstring(trimmedVarName)};
    }

    ValueRule result;
    result.value = TrimStringView(value);

    if (!name.empty() && name.back() == L':') {
        result.isXamlValue = true;
        name = name.substr(0, name.size() - 1);
    }

    auto atPos = name.find(L'@');
    if (atPos != name.npos) {
        result.visualState = TrimStringView(name.substr(atPos + 1));
        name = name.substr(0, atPos);
    }

    result.propertyName = TrimStringView(name);
    if (result.propertyName.empty()) throw std::runtime_error("Bad style syntax, empty name");
    return result;
}

std::wstring AdjustTypeName(std::wstring_view type) {
    if (type.find_first_of(L".:") == type.npos) {
        if (type == L"Rectangle") return L"Windows.UI.Xaml.Shapes.Rectangle";
        return L"Windows.UI.Xaml.Controls." + std::wstring{type};
    }

    static const std::vector<std::pair<std::wstring_view, std::wstring_view>> adjustments = {
        {L"taskbar:", L"Taskbar."},
        {L"systemtray:", L"SystemTray."},
        {L"udk:", L"WindowsUdk.UI.Shell."},
        {L"muxc:", L"Microsoft.UI.Xaml.Controls."},
    };

    for (const auto& adjustment : adjustments) {
        if (type.starts_with(adjustment.first)) {
            auto result = std::wstring{adjustment.second};
            result += type.substr(adjustment.first.size());
            return result;
        }
    }

    return std::wstring{type};
}

std::vector<std::wstring_view> SplitTargetString(std::wstring_view target) {
    std::vector<std::wstring_view> result;
    size_t partBegin = 0;
    bool inProperty = false;

    for (size_t i = 0; i < target.size(); i++) {
        switch (target[i]) {
            case L'[': inProperty = true; break;
            case L']': inProperty = false; break;
            case L',':
                if (!inProperty) {
                    result.push_back(target.substr(partBegin, i - partBegin));
                    partBegin = i + 1;
                }
                break;
        }
    }
    result.push_back(target.substr(partBegin));
    return result;
}

void AddElementCustomizationRulesForSingleTarget(std::wstring_view target, const std::vector<std::wstring>& styles) {
    ElementCustomizationRules elementCustomizationRules;
    auto targetParts = SplitStringView(target, L" > ");

    bool first = true;
    bool hasVisualStateGroup = false;

    for (auto i = targetParts.rbegin(); i != targetParts.rend(); ++i) {
        const auto& targetPart = *i;
        const bool isLeftmost = (i + 1 == targetParts.rend());

        auto matcher = ElementMatcherFromString(targetPart);
        const auto& prevParents = elementCustomizationRules.parentElementMatchers;
        const bool prevIsWildcard = !prevParents.empty() && prevParents.back().kind == ElementMatcher::Kind::Wildcard;

        switch (matcher.kind) {
            case ElementMatcher::Kind::Element:
                matcher.type = AdjustTypeName(matcher.type);
                break;
            case ElementMatcher::Kind::Wildcard:
                if (first || isLeftmost || prevIsWildcard) {
                    throw std::runtime_error("Bad target syntax around '*'");
                }
                break;
            case ElementMatcher::Kind::Root:
                if (first || !isLeftmost || prevIsWildcard) {
                    throw std::runtime_error("Bad target syntax around ':root'");
                }
                break;
        }

        if (matcher.visualStateGroupName) {
            if (hasVisualStateGroup) throw std::runtime_error("More than one visual state group");
            hasVisualStateGroup = true;
        }

        if (first) {
            UnresolvedRules unresolvedRules;
            for (const auto& style : styles) {
                auto parsed = ParseRule(style);
                if (auto* valueRule = std::get_if<ValueRule>(&parsed)) {
                    unresolvedRules.valueRules.push_back(std::move(*valueRule));
                } else {
                    unresolvedRules.captureRules.push_back(std::move(std::get<CaptureRule>(parsed)));
                }
            }

            elementCustomizationRules.elementMatcher = std::move(matcher);
            elementCustomizationRules.propertyOverrides = std::move(unresolvedRules);
        } else {
            elementCustomizationRules.parentElementMatchers.push_back(std::move(matcher));
        }

        first = false;
    }

    g_elementsCustomizationRules.push_back(std::move(elementCustomizationRules));
}

void AddElementCustomizationRules(std::wstring_view target, const std::vector<std::wstring>& styles) {
    auto targets = SplitTargetString(target);
    for (const auto& singleTarget : targets) {
        try {
            AddElementCustomizationRulesForSingleTarget(singleTarget, styles);
        } catch (...) {}
    }
}

bool ProcessSingleTargetStylesFromSettings(int index, const StyleConstants& styleConstants) {
    PCWSTR targetStringSetting = Wh_GetStringSetting(L"Styling.controlStyles[%d].target", index);
    if (!*targetStringSetting) {
        Wh_FreeStringSetting(targetStringSetting);
        return false;
    }

    if (targetStringSetting[0] == L'/' && targetStringSetting[1] == L'/') {
        Wh_FreeStringSetting(targetStringSetting);
        return true;
    }

    std::vector<std::wstring> styles;
    for (int styleIndex = 0;; styleIndex++) {
        PCWSTR styleSetting = Wh_GetStringSetting(L"Styling.controlStyles[%d].styles[%d]", index, styleIndex);
        if (!*styleSetting) {
            Wh_FreeStringSetting(styleSetting);
            break;
        }

        if (!(styleSetting[0] == L'/' && styleSetting[1] == L'/')) {
            styles.push_back(ApplyStyleConstants(styleSetting, styleConstants));
        }
        Wh_FreeStringSetting(styleSetting);
    }

    if (!styles.empty()) {
        AddElementCustomizationRules(targetStringSetting, styles);
    }

    Wh_FreeStringSetting(targetStringSetting);
    return true;
}

// Control styles generated from the quick-toggle settings (taskbar buttons,
// running indicator, tray icons). They are added before the user's own
// control styles, so those can still override them. Selectors follow the
// Windows 11 Taskbar Styler themes.
void AddBuiltInStyles() {
    try {
        // Taskbar shape (rounded bar, pill)
        if (g_settings.shapeStyle != 0) {
            int radius = Wh_GetIntSetting(L"TaskbarShape.CornerRadius");
            if (radius <= 0) radius = g_settings.shapeStyle == 2 ? 24 : 12;

            std::vector<std::wstring> fillStyles = {
                L"RadiusX=" + std::to_wstring(radius),
                L"RadiusY=" + std::to_wstring(radius),
            };

            StringSetting fillColor = StringSetting::make(L"TaskbarShape.FillColor");
            if (*fillColor) {
                fillStyles.push_back(std::wstring(L"Fill=") + fillColor.get());
            } else if (ShapeOwnsBackdrop()) {
                // Draw the configured transparency mode inside the rounded shape.
                PCWSTR mode = g_settings.transparencyMode.get();
                int level = std::clamp(g_settings.transparencyAlpha, 0, 100);
                double opacity = (100 - level) / 100.0;
                if (level >= 100) {
                    fillStyles.push_back(L"Fill=Transparent");
                } else if (level > 0 && _wcsicmp(mode, L"transparent") == 0) {
                    WCHAR argb[16];
                    swprintf_s(argb, L"#%02X000000", static_cast<unsigned>(opacity * 255.0 + 0.5));
                    fillStyles.push_back(std::wstring(L"Fill=") + argb);
                } else if (level > 0 && (_wcsicmp(mode, L"blur") == 0 || _wcsicmp(mode, L"acrylic") == 0)) {
                    WCHAR brush[160];
                    swprintf_s(brush,
                               L"Fill=<WindhawkBlur BlurAmount=\"%d\" TintColor=\"#000000\" TintOpacity=\"%.2f\"/>",
                               _wcsicmp(mode, L"acrylic") == 0 ? 30 : 12, opacity);
                    fillStyles.push_back(brush);
                }
            }

            StringSetting borderColor = StringSetting::make(L"TaskbarShape.BorderColor");
            int borderThickness = Wh_GetIntSetting(L"TaskbarShape.BorderThickness");
            if (*borderColor && borderThickness > 0) {
                fillStyles.push_back(std::wstring(L"Stroke=") + borderColor.get());
                fillStyles.push_back(L"StrokeThickness=" + std::to_wstring(borderThickness));
            }

            AddElementCustomizationRules(
                L"Taskbar.TaskbarFrame > Grid#RootGrid > Taskbar.TaskbarBackground > Grid > Rectangle#BackgroundFill",
                fillStyles);
            // The flat top stroke would cut across the rounded corners.
            AddElementCustomizationRules(
                L"Taskbar.TaskbarFrame > Grid#RootGrid > Taskbar.TaskbarBackground > Grid > Rectangle#BackgroundStroke",
                {L"Visibility=Collapsed"});
        }

        // Taskbar buttons
        if (Wh_GetIntSetting(L"TaskbarButtons.HideStart")) {
            AddElementCustomizationRules(
                L"Taskbar.ExperienceToggleButton#LaunchListButton[AutomationProperties.AutomationId=StartButton]",
                {L"Visibility=Collapsed"});
        }
        if (Wh_GetIntSetting(L"TaskbarButtons.HideSearch")) {
            AddElementCustomizationRules(
                L"Taskbar.SearchBoxButton#SearchBoxButton[AutomationProperties.AutomationId=SearchButton]",
                {L"Visibility=Collapsed"});
        }
        if (Wh_GetIntSetting(L"TaskbarButtons.HideTaskView")) {
            AddElementCustomizationRules(
                L"Taskbar.ExperienceToggleButton#LaunchListButton[AutomationProperties.AutomationId=TaskViewButton]",
                {L"Visibility=Collapsed"});
        }
        if (Wh_GetIntSetting(L"TaskbarButtons.HideWidgets")) {
            AddElementCustomizationRules(
                L"Taskbar.AugmentedEntryPointButton[AutomationProperties.AutomationId=WidgetsButton]",
                {L"Visibility=Collapsed"});
        }

        // Running-app indicator
        StringSetting indicatorMode = StringSetting::make(L"RunningIndicator.Mode");
        if (wcscmp(indicatorMode, L"hidden") == 0) {
            AddElementCustomizationRules(L"Rectangle#RunningIndicator", {L"Visibility=Collapsed"});
        } else if (wcscmp(indicatorMode, L"custom") == 0) {
            std::vector<std::wstring> styles;
            StringSetting color = StringSetting::make(L"RunningIndicator.Color");
            if (*color) styles.push_back(std::wstring(L"Fill=") + color.get());
            StringSetting activeColor = StringSetting::make(L"RunningIndicator.ActiveColor");
            if (*activeColor) styles.push_back(std::wstring(L"Fill@ActiveRunningIndicator=") + activeColor.get());
            if (int v = Wh_GetIntSetting(L"RunningIndicator.Width"); v > 0) {
                styles.push_back(L"Width=" + std::to_wstring(v));
            }
            if (int v = Wh_GetIntSetting(L"RunningIndicator.ActiveWidth"); v > 0) {
                styles.push_back(L"Width@ActiveRunningIndicator=" + std::to_wstring(v));
            }
            if (int v = Wh_GetIntSetting(L"RunningIndicator.Height"); v > 0) {
                styles.push_back(L"Height=" + std::to_wstring(v));
            }
            if (int v = Wh_GetIntSetting(L"RunningIndicator.CornerRadius"); v > 0) {
                styles.push_back(L"RadiusX=" + std::to_wstring(v));
                styles.push_back(L"RadiusY=" + std::to_wstring(v));
            }
            if (!styles.empty()) {
                AddElementCustomizationRules(
                    L"Grid#IconPanel@RunningIndicatorStates > Rectangle#RunningIndicator, "
                    L"Taskbar.TaskListLabeledButtonPanel@RunningIndicatorStates > Rectangle#RunningIndicator",
                    styles);
            }
        }

        // Classic notification-area icons, matched by their exact name (tooltip text)
        for (int i = 0;; i++) {
            StringSetting name = StringSetting::make(L"TrayIcons.HiddenNames[%d]", i);
            if (*name == L'\0') break;
            if (wcschr(name.get(), L']')) continue;  // would end the selector early
            AddElementCustomizationRules(
                std::wstring(L"SystemTray.NotifyIconView#NotifyItemIcon[AutomationProperties.Name=") + name.get() + L"]",
                {L"Visibility=Collapsed"});
        }
    } catch (...) {}
}

void ProcessAllStylesFromSettings() {
    StyleConstants styleConstants = LoadStyleConstants();
    AddBuiltInStyles();

    for (int i = 0;; i++) {
        try {
            if (!ProcessSingleTargetStylesFromSettings(i, styleConstants)) break;
        } catch (...) {}
    }

    g_resourceVariables = ProcessResourceVariablesFromSettings(styleConstants);
}

void UninitializeStylerForCurrentThread() {
    StopImageLoadRetriesForCurrentThread();

    for (const auto& [elementDo, asyncOp] : g_delayedBackgroundFillSet) {
        asyncOp.Cancel();
    }
    g_delayedBackgroundFillSet.clear();

    StopDiagnosticsReleases();
    g_virtualizingRepeaters.clear();
    g_recycledElements.clear();
    g_elementMatchedItems.clear();

    auto elementsCustomizationState = std::move(g_elementsCustomizationState);
    g_elementsCustomizationState.clear();

    for (const auto& [elementId, elementCustomizationState] : elementsCustomizationState) {
        auto element = elementCustomizationState.element.get();
        auto* state = GetStyleVariableState(elementCustomizationState.xamlRoot);

        RestoreCapturesForElement(element, elementCustomizationState);

        for (const auto& [visualStateGroupOptionalWeakPtrIter, stateIter] : elementCustomizationState.perVisualStateGroup) {
            RestoreCustomizationsForVisualStateGroup(state, elementId, element, visualStateGroupOptionalWeakPtrIter, stateIter);
        }
    }

    elementsCustomizationState.clear();
    g_elementTreeNodes.clear();
    g_elementTreeNodesReapThreshold = 64;
    g_pendingStyleVariablePropagations.clear();
    g_styleVariableState.clear();

    g_elementIds.clear();
    g_elementIdsReapThreshold = 64;
    g_elementsCustomizationRules.clear();

    UninitializeResourceVariables();

    g_stylerInitializedForThread = false;
}

void UninitializeStylerSettingsAndTap() {
    if (g_visualTreeWatcher) {
        g_visualTreeWatcher->UnadviseVisualTreeChange();
        g_visualTreeWatcher = nullptr;
    }
    g_stylerInitialized = false;
}

void InitializeStylerForCurrentThread() {
    if (g_stylerInitializedForThread) return;
    ProcessAllStylesFromSettings();
    g_stylerInitializedForThread = true;
}

void InitializeStylerSettingsAndTap() {
    if (g_stylerInitialized.exchange(true)) return;
    HRESULT hr = InjectWindhawkTAP();
    if (FAILED(hr)) {
        Wh_Log(L"InjectWindhawkTAP failed: 0x%08X", hr);
    }
}

void OnWindowCreated(HWND hWnd, HWND hWndParent, LPCWSTR lpClassName, PCSTR funcName) {
    BOOL bTextualClassName = ((ULONG_PTR)lpClassName & ~(ULONG_PTR)0xffff) != 0;

    WCHAR className[64];
    if (hWndParent && GetClassName(hWnd, className, ARRAYSIZE(className)) &&
        _wcsicmp(className, L"Windows.UI.Composition.DesktopWindowContentBridge") == 0 &&
        GetClassName(hWndParent, className, ARRAYSIZE(className)) &&
        _wcsicmp(className, L"Shell_TrayWnd") == 0) {
        InitializeStylerForCurrentThread();
        InitializeStylerSettingsAndTap();
        return;
    }

    if (bTextualClassName &&
        (_wcsicmp(lpClassName, L"XamlExplorerHostIslandWindow") == 0 ||
         _wcsicmp(lpClassName, L"Shell_InputSwitchTopLevelWindow") == 0)) {
        InitializeStylerForCurrentThread();
        InitializeStylerSettingsAndTap();
        return;
    }
}

using CreateWindowExW_t = decltype(&CreateWindowExW);
CreateWindowExW_t CreateWindowExW_Original;
HWND WINAPI CreateWindowExW_Hook(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle,
                                 int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu,
                                 HINSTANCE hInstance, PVOID lpParam) {
    HWND hWnd = CreateWindowExW_Original(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight,
                                         hWndParent, hMenu, hInstance, lpParam);
    if (!hWnd) return hWnd;
    OnWindowCreated(hWnd, hWndParent, lpClassName, __FUNCTION__);
    return hWnd;
}

using CreateWindowInBand_t = HWND(WINAPI*)(DWORD, LPCWSTR, LPCWSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, PVOID, DWORD);
CreateWindowInBand_t CreateWindowInBand_Original;
HWND WINAPI CreateWindowInBand_Hook(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle,
                                    int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu,
                                    HINSTANCE hInstance, PVOID lpParam, DWORD dwBand) {
    HWND hWnd = CreateWindowInBand_Original(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight,
                                            hWndParent, hMenu, hInstance, lpParam, dwBand);
    if (!hWnd) return hWnd;
    OnWindowCreated(hWnd, hWndParent, lpClassName, __FUNCTION__);
    return hWnd;
}

using CreateWindowInBandEx_t = HWND(WINAPI*)(DWORD, LPCWSTR, LPCWSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, PVOID, DWORD, DWORD);
CreateWindowInBandEx_t CreateWindowInBandEx_Original;
HWND WINAPI CreateWindowInBandEx_Hook(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle,
                                      int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu,
                                      HINSTANCE hInstance, PVOID lpParam, DWORD dwBand, DWORD dwTypeFlags) {
    HWND hWnd = CreateWindowInBandEx_Original(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight,
                                              hWndParent, hMenu, hInstance, lpParam, dwBand, dwTypeFlags);
    if (!hWnd) return hWnd;
    OnWindowCreated(hWnd, hWndParent, lpClassName, __FUNCTION__);
    return hWnd;
}

PFN_INITIALIZE_XAML_DIAGNOSTICS_EX InitializeXamlDiagnosticsEx_Original;
HRESULT WINAPI InitializeXamlDiagnosticsEx_Hook(_In_ PCWSTR endPointName, _In_ DWORD pid, _In_ PCWSTR wszDllXamlDiagnostics,
                                                _In_ PCWSTR wszTAPDllName, _In_ CLSID tapClsid, _In_opt_ PCWSTR wszInitializationData) {
    if (g_inInjectWindhawkTAP) {
        return InitializeXamlDiagnosticsEx_Original(endPointName, pid, wszDllXamlDiagnostics, wszTAPDllName, tapClsid, wszInitializationData);
    }

    bool blockCall = false;
    switch (g_stylerSettings.xamlDiagnosticsHandling) {
        case XamlDiagnosticsHandling::kAlert: {
            void* retAddress = __builtin_return_address(0);
            WCHAR modulePath[MAX_PATH];
            PCWSTR modulePathStr = L"<unknown>";
            HMODULE module;
            if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                  reinterpret_cast<LPCWSTR>(retAddress), &module)) {
                if (GetModuleFileName(module, modulePath, ARRAYSIZE(modulePath))) {
                    modulePathStr = modulePath;
                }
            }

            WCHAR message[1024];
            _snwprintf_s(message, _TRUNCATE,
                         L"The following module is trying to use XAML diagnostics:\n\n%s\n\n"
                         L"There can only be one consumer at a time. Blocking it might break that module, but allowing it might break custom taskbar styles.\n\n"
                         L"Do you want to block it?", modulePathStr);
            int result = MessageBox(nullptr, message, L"Taskbar Tray & Clock Tweaks - Windhawk", MB_YESNO | MB_ICONQUESTION | MB_TOPMOST);
            blockCall = (result == IDYES);
            break;
        }
        case XamlDiagnosticsHandling::kBlock:
            blockCall = true;
            break;
        case XamlDiagnosticsHandling::kAllow:
            blockCall = false;
            break;
    }

    if (blockCall) {
        return S_OK;
    }

    return InitializeXamlDiagnosticsEx_Original(endPointName, pid, wszDllXamlDiagnostics, wszTAPDllName, tapClsid, wszInitializationData);
}

bool HookInitializeXamlDiagnosticsExIfNeeded() {
    if (InitializeXamlDiagnosticsEx_Original) return false;
    const HMODULE wux = GetModuleHandle(L"Windows.UI.Xaml.dll");
    if (!wux) return false;

    const auto ixde = reinterpret_cast<PFN_INITIALIZE_XAML_DIAGNOSTICS_EX>(GetProcAddress(wux, "InitializeXamlDiagnosticsEx"));
    if (!ixde) return false;

    return WindhawkUtils::SetFunctionHook(ixde, InitializeXamlDiagnosticsEx_Hook, &InitializeXamlDiagnosticsEx_Original);
}

using RegOpenKeyExW_t = decltype(&RegOpenKeyExW);
RegOpenKeyExW_t RegOpenKeyExW_Original;
LSTATUS WINAPI RegOpenKeyExW_Hook(HKEY hKey, LPCWSTR lpSubKey, DWORD ulOptions, REGSAM samDesired, PHKEY phkResult) {
    LSTATUS result = RegOpenKeyExW_Original(hKey, lpSubKey, ulOptions, samDesired, phkResult);
    if (result == ERROR_SUCCESS || !g_reportCompositionDiagAsDisabled ||
        hKey != HKEY_LOCAL_MACHINE || !lpSubKey ||
        _wcsicmp(lpSubKey, L"Software\\Microsoft\\XAML\\Debug") != 0) {
        return result;
    }
    return RegOpenKeyExW_Original(HKEY_LOCAL_MACHINE, L"Software\\Microsoft", ulOptions, samDesired, phkResult);
}

using RegQueryValueExW_t = decltype(&RegQueryValueExW);
RegQueryValueExW_t RegQueryValueExW_Original;
LSTATUS WINAPI RegQueryValueExW_Hook(HKEY hKey, LPCWSTR lpValueName, LPDWORD lpReserved, LPDWORD lpType, LPBYTE lpData, LPDWORD lpcbData) {
    if (!g_reportCompositionDiagAsDisabled || !lpValueName ||
        _wcsicmp(lpValueName, L"DisableCompositionDiag") != 0) {
        return RegQueryValueExW_Original(hKey, lpValueName, lpReserved, lpType, lpData, lpcbData);
    }

    if (lpType) *lpType = REG_DWORD;
    if (lpData && (!lpcbData || *lpcbData < sizeof(DWORD))) {
        if (lpcbData) *lpcbData = sizeof(DWORD);
        return ERROR_MORE_DATA;
    }
    if (lpData) *reinterpret_cast<DWORD*>(lpData) = 1;
    if (lpcbData) *lpcbData = sizeof(DWORD);
    return ERROR_SUCCESS;
}

std::vector<HWND> GetXamlHostWnds() {
    struct ENUM_WINDOWS_PARAM { std::vector<HWND>* hWnds; };
    std::vector<HWND> hWnds;
    ENUM_WINDOWS_PARAM param = {&hWnds};
    EnumWindows(
        [](HWND hWnd, LPARAM lParam) -> BOOL {
            auto& p = *(ENUM_WINDOWS_PARAM*)lParam;
            DWORD pid = 0;
            if (!GetWindowThreadProcessId(hWnd, &pid) || pid != GetCurrentProcessId()) return TRUE;
            WCHAR szClassName[32];
            if (!GetClassName(hWnd, szClassName, ARRAYSIZE(szClassName))) return TRUE;
            if (_wcsicmp(szClassName, L"XamlExplorerHostIslandWindow") == 0 ||
                _wcsicmp(szClassName, L"Shell_InputSwitchTopLevelWindow") == 0) {
                p.hWnds->push_back(hWnd);
            }
            return TRUE;
        },
        (LPARAM)&param);
    return hWnds;
}

HWND GetTaskbarUiWnd() {
    HWND hTaskbarWnd = FindCurrentProcessTaskbarWnd();
    if (!hTaskbarWnd) return nullptr;
    return FindWindowEx(hTaskbarWnd, nullptr, L"Windows.UI.Composition.DesktopWindowContentBridge", nullptr);
}

// ----- MODULE LIFECYCLE -----

using LoadLibraryExW_t = decltype(&LoadLibraryExW);
LoadLibraryExW_t LoadLibraryExW_Original;

HMODULE WINAPI LoadLibraryExW_Hook(LPCWSTR lpLibFileName, HANDLE hFile, DWORD dwFlags) {
    HMODULE module = LoadLibraryExW_Original(lpLibFileName, hFile, dwFlags);
    if (module) {
        if (!((ULONG_PTR)module & 3) && !g_explorerPatcherInitialized) {
            if (IsExplorerPatcherModule(module)) HookExplorerPatcherSymbols(module);
        }
        HandleLoadedModuleIfSystemTray(module, lpLibFileName);
        if (g_winVersion >= WinVersion::Win11 && !g_settings.oldTaskbarOnWin11) {
            HandleLoadedModuleIconSize(module, lpLibFileName);
            if (!InitializeXamlDiagnosticsEx_Original && lpLibFileName) {
                PCWSTR fileName = wcsrchr(lpLibFileName, L'\\');
                fileName = fileName ? fileName + 1 : lpLibFileName;
                if (_wcsicmp(fileName, L"Windows.UI.Xaml.dll") == 0 &&
                    HookInitializeXamlDiagnosticsExIfNeeded()) {
                    Wh_ApplyHookOperations();
                }
            }
        }
    }
    return module;
}

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
    LoadIconSizeSettings();
    LoadStylerSettings();

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

        // Taskbar height / icon size feature.
        if (!IconSize_ModInit()) return FALSE;

        // Taskbar styler window hooks:
        WindhawkUtils::SetFunctionHook(CreateWindowExW, CreateWindowExW_Hook,
                                       &CreateWindowExW_Original);

        HMODULE user32Module =
            LoadLibraryEx(L"user32.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (user32Module) {
            auto pCreateWindowInBand = (CreateWindowInBand_t)GetProcAddress(
                user32Module, "CreateWindowInBand");
            if (pCreateWindowInBand) {
                WindhawkUtils::SetFunctionHook(pCreateWindowInBand,
                                               CreateWindowInBand_Hook,
                                               &CreateWindowInBand_Original);
            }

            auto pCreateWindowInBandEx = (CreateWindowInBandEx_t)GetProcAddress(
                user32Module, "CreateWindowInBandEx");
            if (pCreateWindowInBandEx) {
                WindhawkUtils::SetFunctionHook(pCreateWindowInBandEx,
                                               CreateWindowInBandEx_Hook,
                                               &CreateWindowInBandEx_Original);
            }
        }
    } else {
        if (!HookWin10TaskbarSymbols()) return FALSE;
    }

    if (!HandleLoadedExplorerPatcher()) return FALSE;

    HMODULE kernelBaseModule = GetModuleHandle(L"kernelbase.dll");
    auto pKernelBaseLoadLibraryExW = (decltype(&LoadLibraryExW))GetProcAddress(kernelBaseModule, "LoadLibraryExW");
    WindhawkUtils::SetFunctionHook(pKernelBaseLoadLibraryExW, LoadLibraryExW_Hook, &LoadLibraryExW_Original);

    if (g_winVersion >= WinVersion::Win11 && !g_settings.oldTaskbarOnWin11) {
        auto pKernelBaseRegOpenKeyExW =
            (RegOpenKeyExW_t)GetProcAddress(kernelBaseModule, "RegOpenKeyExW");
        WindhawkUtils::SetFunctionHook(pKernelBaseRegOpenKeyExW, RegOpenKeyExW_Hook,
                                       &RegOpenKeyExW_Original);

        auto pKernelBaseRegQueryValueExW = (RegQueryValueExW_t)GetProcAddress(
            kernelBaseModule, "RegQueryValueExW");
        WindhawkUtils::SetFunctionHook(pKernelBaseRegQueryValueExW,
                                       RegQueryValueExW_Hook,
                                       &RegQueryValueExW_Original);

        HookInitializeXamlDiagnosticsExIfNeeded();
    }

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

    if (g_winVersion >= WinVersion::Win11 && !g_settings.oldTaskbarOnWin11) {
        IconSize_ModAfterInit();

        bool initializeStyler = false;
        HWND hTaskbarUiWnd = GetTaskbarUiWnd();
        if (hTaskbarUiWnd) {
            RunFromWindowThread(
                hTaskbarUiWnd, [](PVOID) { InitializeStylerForCurrentThread(); },
                nullptr);
            initializeStyler = true;
        }

        for (auto hXamlHostWnd : GetXamlHostWnds()) {
            RunFromWindowThread(
                hXamlHostWnd, [](PVOID) { InitializeStylerForCurrentThread(); }, nullptr);
            initializeStyler = true;
        }

        if (initializeStyler) {
            InitializeStylerSettingsAndTap();
        }
    }

    ApplySettings();

    if (g_winVersion >= WinVersion::Win11) {
        StartTransparencyWatchdog();
    }
}

void Wh_ModBeforeUninit() {
    g_unloading = true;

    StopTransparencyWatchdog();

    if (g_winVersion >= WinVersion::Win11 && !g_settings.oldTaskbarOnWin11) {
        HWND restartExplorerPromptWindow = g_restartExplorerPromptWindow;
        if (restartExplorerPromptWindow) {
            PostMessage(restartExplorerPromptWindow, WM_CLOSE, 0, 0);
        }

        if (g_restartExplorerPromptThread) {
            WaitForSingleObject(g_restartExplorerPromptThread, INFINITE);
            CloseHandle(g_restartExplorerPromptThread);
            g_restartExplorerPromptThread = nullptr;
        }

        StopImageDownloads();
        StopImageLoadRetries();
        UninitializeStylerSettingsAndTap();

        IconSize_ModBeforeUninit();
    }

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
        PingThreadUninit();
        MediaSessionUninit();
    }

    if (g_winVersion >= WinVersion::Win11 && !g_settings.oldTaskbarOnWin11) {
        IconSize_ModUninit();

        HWND hTaskbarUiWnd = GetTaskbarUiWnd();
        if (hTaskbarUiWnd) {
            RunFromWindowThread(
                hTaskbarUiWnd, [](PVOID) { UninitializeStylerForCurrentThread(); },
                nullptr);
        }

        for (auto hXamlHostWnd : GetXamlHostWnds()) {
            RunFromWindowThread(
                hXamlHostWnd, [](PVOID) { UninitializeStylerForCurrentThread(); },
                nullptr);
        }
    }

    ApplySettings();
    if (g_winVersion >= WinVersion::Win11) {
        ApplyTaskbarTransparency();
    }
}

BOOL Wh_ModSettingsChanged(BOOL* bReload) {
    StopTransparencyWatchdog();

    {
        std::lock_guard<std::mutex> guard(g_formatLineMutex);
        WebContentUpdateThreadUninit();
        DataCollectionSessionUninit();
        PingThreadUninit();
        MediaSessionUninit();
        g_formattingInitialized = false;

        bool prevOldTaskbar = g_settings.oldTaskbarOnWin11;
        LoadSettings();
        LoadStylerSettings();
        *bReload = (g_settings.oldTaskbarOnWin11 != prevOldTaskbar);
        if (*bReload) return TRUE;
    }

    if (g_winVersion >= WinVersion::Win11 && !g_settings.oldTaskbarOnWin11) {
        IconSize_ModSettingsChanged();

        UninitializeStylerSettingsAndTap();

        bool initializeStyler = false;
        HWND hTaskbarUiWnd = GetTaskbarUiWnd();
        if (hTaskbarUiWnd) {
            RunFromWindowThread(
                hTaskbarUiWnd,
                [](PVOID) {
                    UninitializeStylerForCurrentThread();
                    InitializeStylerForCurrentThread();
                },
                nullptr);
            initializeStyler = true;
        }

        for (auto hXamlHostWnd : GetXamlHostWnds()) {
            RunFromWindowThread(
                hXamlHostWnd,
                [](PVOID) {
                    UninitializeStylerForCurrentThread();
                    InitializeStylerForCurrentThread();
                },
                nullptr);
            initializeStyler = true;
        }

        if (initializeStyler) {
            InitializeStylerSettingsAndTap();
        }
    }

    ApplySettings();

    if (g_winVersion >= WinVersion::Win11) {
        StartTransparencyWatchdog();
    }
    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE, DWORD fdwReason, LPVOID lpReserved) {
    if (fdwReason == DLL_PROCESS_DETACH && lpReserved) {
        winrt::detach_abi(g_mediaSessionManager);
        winrt::detach_abi(g_mediaCurrentSession);
    }
    return TRUE;
}
