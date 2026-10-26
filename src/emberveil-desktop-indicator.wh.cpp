// ==WindhawkMod==
// @id              emberveil-desktop-indicator
// @name            Virtual Desktop Manager
// @description     Windows 11 virtual desktop display, navigation, and native transitions
// @version         1.5.0
// @author          Hendrik Heitlager (based on work by Simon Benedict)
// @github          https://github.com/simon-ami
// @include         explorer.exe
// @architecture    x86-64
// @compilerOptions -lole32 -loleaut32 -lruntimeobject -lversion
// @license         MIT
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Virtual Desktop Manager

Displays virtual desktop numbers, names, or clickable markers using native Windows 11 taskbar XAML.

## Features

* Number mode or workspace markers mode
* Current virtual desktop name mode
* Workspace markers mode with `⬤` markers by default
* Roman or Arabic numbering in number mode
* Custom marker symbol and inactive-marker dimming in workspace markers mode \
  Example symbols: `⬤`, `●`, `•`, `○`, `◉`
* Optional custom colors for the active indicator and inactive markers
* Optional hiding of the indicator when only one desktop exists
* Configurable indicator weight and size
* Configurable spacing and padding
* Notification-based desktop change detection
* Optional polling fallback

## Screenshot

![Workspace markers mode](https://raw.githubusercontent.com/simon-ami/images/main/windhawk/taskbar-desktop-indicator/marker-indicator.png) \
_Workspace markers mode (example)_

![Number mode](https://raw.githubusercontent.com/simon-ami/images/main/windhawk/taskbar-desktop-indicator/roman-number.png) \
_Number mode (example)_

## Notes

* Windows 11 only
* Uses native taskbar XAML placement rather than modifying clock text
* The default appearance is workspace markers with dimmed inactive markers
* The mod uses virtual desktop notifications as the primary update path
* Polling fallback is disabled by default
* If the indicator doesn't update when switching desktops on your system, set the poll interval to `50` or `100` ms
* Lower poll intervals increase registry reads in Explorer

## Smooth desktop transitions (experimental)

Optional native desktop animation tuning, adapted from enesky's MIT-licensed
Smooth Virtual Desktop Switching mod. Controls touchpad and keyboard transition
durations and easing. Marker clicks use keyboard shortcuts. Requires private
Windows shell symbols; failures do not disable the desktop indicator. Avoid
running both mods at once, and do not combine with a transition-disabling mod.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- Placement:
  - position: beforeTray
    $name: Taskbar position
    $options:
      - beforeTray: Before system tray
      - afterClock: After system tray (far edge)
      - afterStartBeforeIcons: Before taskbar icons
      - afterStartAfterIcons: After taskbar icons
      - dynamicCenter: Dynamic center (experimental)
  - horizontalOffset: 0
    $name: Dynamic center horizontal offset (DIP)
    $description: Moves Dynamic center left (negative) or right (positive) without changing marker spacing. The offset is limited to the available taskbar region.
  - nativeMargins: "0, 0, 0, 0"
    $name: Native margins (left, top, right, bottom)
    $description: Four signed DIP offsets, e.g. "-5, 0, 0, 0". Applies to independent positions only.
  $name: Placement
- Content:
  - indicatorMode: markers
    $name: Virtual desktop display
    $description: Choose how virtual desktops appear in the taskbar.
    $options:
      - number: Current number (Roman / Arabic)
      - markers: Symbol indicators
      - desktopName: Current name
  - numberingFormat: roman
    $name: Number format
    $description: Used when Virtual desktop display is Current number.
    $options:
      - roman: Roman numerals · I II III IV V
      - arabic: Arabic numerals · 1 2 3 4 5
  - markerSymbol: ⬤
    $name: Virtual desktop indicator symbol
    $description: Symbol or short text used for each virtual desktop marker in indicator mode. E.g. ┃, ⬤, ●, •, ○, ◉, ⎕, ∎, ◆, ♦, ★ [Default ⬤]
  - hideWhenSingleDesktop: false
    $name: Hide when using a single desktop
    $description: Hide the indicator while only one virtual desktop exists. [Default false]
  $name: Content
- Appearance:
  - themePreset: windows
    $name: Theme preset
    $description: Choose a palette. Empty individual colors inherit this theme; Custom falls back to Windows accent colors.
    $options:
      - windows: Windows Default (accent)
      - monochrome: Monochrome (light/dark aware)
      - emberveil: Emberveil
      - catppuccinMocha: Catppuccin Mocha
      - catppuccinLatte: Catppuccin Latte
      - catppuccinMacchiato: Catppuccin Macchiato
      - catppuccinFrappe: Catppuccin Frappé
      - dracula: Dracula
      - gruvbox: Gruvbox
      - nord: Nord
      - solarized: Solarized
      - tokyoNight: Tokyo Night
      - custom: Custom (Windows defaults for empty colors)
  - activeIndicatorColor: ""
    $name: Active indicator color
    $description: >-
      Optional custom color for number mode and the active workspace marker. Use
      #RRGGBB or #AARRGGBB. Leave empty to inherit the selected theme. [Default
      empty]
  - inactiveMarkerColor: ""
    $name: Inactive marker color
    $description: >-
      Optional custom color for inactive workspace markers. Use #RRGGBB or
      #AARRGGBB. Leave empty to inherit the selected theme. [Default empty]
  - hoverMarkerColor: ""
    $name: Hover marker color
    $description: Optional #RRGGBB or #AARRGGBB override for inactive markers on hover. Empty uses the selected theme. Active markers do not change on hover.
  - inactiveMarkerOpacity: 20
    $name: Inactive indicator opacity
    $description: Enter a value from 0 to 100. Opacity percentage for non-active markers in workspace markers mode. 100 matches the active marker, lower values make inactive markers dimmer. [Default 20]
  - indicatorWeight: normal
    $name: Indicator weight
    $description: Font weight for the desktop indicator in both modes. [Default normal]
    $options:
      - normal: Normal
      - bold: Bold
  - indicatorSize: normal
    $name: Indicator size
    $description: Relative font size for the desktop indicator in both modes. [Default normal]
    $options:
      - smaller: Smaller
      - normal: Normal
      - larger: Larger
  - markerTooltips: true
    $name: Show indicator tooltips
    $description: Show a list of virtual desktop numbers and names when hovering over the indicators. [Default true]
  $name: Appearance
- Spacing:
  - indicatorCharacterSpacing: 1
    $name: Character spacing
    $description: Number of spaces inserted between indicator characters in both modes. [Default 1]
  - leftPadding: 6
    $name: Left padding
    $description: Number of spaces between the clock text and the desktop indicator. [Default 6]
  - rightPadding: 0
    $name: Right padding
    $description: Number of spaces after the desktop indicator. [Default 0]
  $name: Spacing
- Transitions:
  - smoothDesktopTransitions: true
    $name: Virtual desktop transitions
    $description: Enable native desktop transition animation tuning. Requires private Windows symbols; if unavailable, the indicator continues working.
  - durationMs: 750
    $name: Touchpad transition duration (ms)
    $description: Duration from 150 to 5000 ms.
  - keyboardDurationMs: 750
    $name: Keyboard and marker transition duration (ms)
    $description: Duration from 150 to 5000 ms for Win+Ctrl+Arrow, including marker clicks.
  - transitionCurve: native
    $name: Desktop transition curve
    $options:
      - native: Native Windows
      - linear: Linear
      - easeOut: Ease-out
  - forceAnimations: true
    $name: Allow desktop animations when Windows animations are disabled
    $description: Scoped to desktop transitions; does not change the Windows setting.
  $name: Transitions
- Advanced:
  - pollIntervalMs: 0
    $name: Poll interval (ms)
    $description: Optional polling fallback for desktop changes. 0 disables polling. If indicator doesn't update on your system, try 50 or 100. [Default 0]
  $name: Advanced
*/
// ==/WindhawkModSettings==

#include <commctrl.h>
#include <windhawk_utils.h>
#include <uxtheme.h>

// windows.h defines GetCurrentTime() as a macro; C++/WinRT declares a method
// with the same name. Undefine it before the first WinRT header.
#undef GetCurrentTime

#include <algorithm>
#include <cmath>
#include <atomic>
#include <cwctype>
#include <limits>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

#undef GetCurrentTime

#include <servprov.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.UI.h>
#include <winrt/Windows.UI.Core.h>
#include <winrt/Windows.UI.Text.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Input.h>
#include <winrt/Windows.UI.Xaml.Documents.h>
#include <winrt/Windows.UI.Xaml.Media.h>
#include <winrt/base.h>

using namespace winrt::Windows::UI::Xaml;
using WindhawkUtils::StringSetting;
using namespace winrt::Windows::UI::Text;
namespace Documents = winrt::Windows::UI::Xaml::Documents;

enum class IndicatorPosition {
    Clock,
    AfterStartBeforeIcons,
    AfterStartAfterIcons,
    BeforeTray,
    AfterClock,
    DynamicCenter,
};

enum class IndicatorMode {
    Number,
    Markers,
    DesktopName,
};

enum class IndicatorSegmentStyle {
    Normal,
    Dimmed,
    Transparent,
};

struct IndicatorSegment {
    std::wstring text;
    IndicatorSegmentStyle style = IndicatorSegmentStyle::Normal;
};

struct IndicatorLayout {
    std::wstring renderedSuffix;
    double widestSuffixWidth = 0;
    std::vector<IndicatorSegment> suffixSegments;
};

enum class WinVersion {
    Unsupported,
    Win10,
    Win11,
    Win11_22H2,
    Win11_24H2,
};

enum class NumberingFormat {
    Roman,
    Arabic,
};

enum class IndicatorWeight {
    Normal,
    Bold,
};

enum class IndicatorSize {
    Smaller,
    Normal,
    Larger,
};

struct ModSettings {
    IndicatorPosition position = IndicatorPosition::BeforeTray;
    int nativeGap = 0;
    int horizontalOffset = 0;
    int nativeMarginLeft = 0;
    int nativeMarginTop = 0;
    int nativeMarginRight = 0;
    int nativeMarginBottom = 0;
    IndicatorMode indicatorMode = IndicatorMode::Markers;
    std::wstring markerSymbol = L"\u2b24";
    std::wstring themePreset = L"windows";
    std::wstring hoverMarkerColor;
    std::wstring activeIndicatorColor;
    std::wstring inactiveMarkerColor;
    bool hideWhenSingleDesktop = false;
    bool markerTooltips = true;
    NumberingFormat numberingFormat = NumberingFormat::Roman;
    int leftPadding = 6;
    int rightPadding = 0;
    int indicatorCharacterSpacing = 1;
    int inactiveMarkerOpacity = 20;
    int pollIntervalMs = 0;
    IndicatorWeight indicatorWeight = IndicatorWeight::Normal;
    IndicatorSize indicatorSize = IndicatorSize::Normal;
};

struct ClockEntry {
    winrt::weak_ref<Controls::TextBlock> dateTextBlock;
    winrt::weak_ref<Controls::TextBlock> timeTextBlock;
    winrt::weak_ref<Controls::Grid> containerGrid;
    winrt::weak_ref<Controls::StackPanel> stackPanel;
    winrt::weak_ref<Controls::TextBlock> indicatorTextBlock;
    std::wstring baseDateText;
    std::wstring baseTimeText;
    std::wstring lastAppliedSuffix;
    std::vector<GridLength> originalContainerGridColumnWidths;
    double originalDateMinWidth = 0;
    double originalTimeMinWidth = 0;
    TextAlignment originalDateTextAlignment = TextAlignment::End;
    TextAlignment originalTimeTextAlignment = TextAlignment::End;
    int originalStackPanelColumn = 0;
    bool originalDateMinWidthCaptured = false;
    bool originalTimeMinWidthCaptured = false;
    bool originalDateTextAlignmentCaptured = false;
    bool originalTimeTextAlignmentCaptured = false;
    bool originalContainerGridColumnsCaptured = false;
    bool originalStackPanelColumnCaptured = false;
    bool usingSeparateIndicator = false;
    std::mutex mutex;
};

using ClockEntryPtr = std::shared_ptr<ClockEntry>;

struct NotificationInterfaceConfig {
    int64_t iidPart1 = 0;
    int64_t iidPart2 = 0;
    int methodCount = 0;
    int currentChangedIndex = -1;
    bool currentChangedHasMonitors = false;
};

struct VirtualDesktopNotificationObject {
    void** vtable = nullptr;
    LONG refCount = 1;
};

WinVersion g_winVersion = WinVersion::Unsupported;
WORD g_explorerBuildNumber = 0;
WORD g_explorerRevisionNumber = 0;
std::atomic<bool> g_systemTrayModuleHooked = false;
std::atomic<bool> g_unloading = false;
std::atomic<int> g_currentDesktopNumber = 1;
std::atomic<int> g_pollIntervalMs = 0;
std::atomic<bool> g_virtualDesktopNotificationsRegistered = false;

std::mutex g_clockEntriesMutex;
std::vector<ClockEntryPtr> g_clockEntries;

HANDLE g_stopEvent = nullptr;
HANDLE g_pollThread = nullptr;
HANDLE g_notificationStopEvent = nullptr;
HANDLE g_notificationThread = nullptr;
HANDLE g_notificationReadyEvent = nullptr;
ModSettings g_settings;
DWORD g_virtualDesktopNotificationCookie = 0;
VirtualDesktopNotificationObject* g_virtualDesktopNotificationObject = nullptr;

using ClockSystemTrayIconDataModel_RefreshIcon_t = void(WINAPI*)(LPVOID, LPVOID);
ClockSystemTrayIconDataModel_RefreshIcon_t
    ClockSystemTrayIconDataModel_RefreshIcon_Original;
ClockSystemTrayIconDataModel_RefreshIcon_t
    ClockSystemTrayIconDataModel2_RefreshIcon_Original;

using DateTimeIconContent_OnApplyTemplate_t = void(WINAPI*)(LPVOID);
DateTimeIconContent_OnApplyTemplate_t
    DateTimeIconContent_OnApplyTemplate_Original;

using BadgeIconContent_get_ViewModel_t = HRESULT(WINAPI*)(LPVOID, LPVOID);
BadgeIconContent_get_ViewModel_t BadgeIconContent_get_ViewModel_Original;

using ClockButton_v_OnDisplayStateChange_t = void(WINAPI*)(LPVOID, bool);
ClockButton_v_OnDisplayStateChange_t ClockButton_v_OnDisplayStateChange_Original;

int ReadCurrentDesktopNumberFromRegistry();
void UpdateAllClockEntries(bool captureBaseText);
void RestoreClockText(const ClockEntryPtr& entry);

const CLSID CLSID_ImmersiveShell = {
    0xc2f03a33,
    0x21f5,
    0x47fa,
    {0xb4, 0xbb, 0x15, 0x63, 0x62, 0xa2, 0xf2, 0x39},
};

const GUID SID_VirtualDesktopNotificationService = {
    0xa501fdec,
    0x4a09,
    0x464c,
    {0xae, 0x4e, 0x1b, 0x9c, 0x21, 0xb8, 0x49, 0x18},
};

const GUID IID_IUnknown_Local = {
    0x00000000,
    0x0000,
    0x0000,
    {0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46},
};

const GUID IID_IVirtualDesktopNotificationService = {
    0x0cd45e71,
    0xd927,
    0x4f15,
    {0x8b, 0x0a, 0x8f, 0xef, 0x52, 0x53, 0x37, 0xbf},
};

MIDL_INTERFACE("0CD45E71-D927-4F15-8B0A-8FEF525337BF")
IVirtualDesktopNotificationService : public IUnknown {
   public:
    virtual HRESULT STDMETHODCALLTYPE Register(IUnknown* pNotification,
                                               DWORD* pdwCookie) = 0;
    virtual HRESULT STDMETHODCALLTYPE Unregister(DWORD dwCookie) = 0;
};

bool EndsWith(const std::wstring& value, const std::wstring& suffix) {
    return value.size() >= suffix.size() &&
           value.compare(value.size() - suffix.size(), suffix.size(), suffix) == 0;
}

std::wstring TrimAppliedSuffix(const std::wstring& text,
                               const std::wstring& suffix) {
    if (suffix.empty()) {
        return text;
    }

    if (text == suffix) {
        return L"";
    }

    if (EndsWith(text, suffix)) {
        return text.substr(0, text.size() - suffix.size());
    }

    return text;
}

std::wstring ToRomanNumeral(int value) {
    if (value <= 0) {
        return L"?";
    }

    struct RomanPart {
        int value;
        PCWSTR numeral;
    };

    static constexpr RomanPart kRomanParts[] = {
        {1000, L"M"}, {900, L"CM"}, {500, L"D"}, {400, L"CD"}, {100, L"C"},
        {90, L"XC"},  {50, L"L"},   {40, L"XL"}, {10, L"X"},   {9, L"IX"},
        {5, L"V"},    {4, L"IV"},   {1, L"I"},
    };

    std::wstring result;
    for (const auto& part : kRomanParts) {
        while (value >= part.value) {
            result += part.numeral;
            value -= part.value;
        }
    }

    return result;
}

std::wstring ToArabicNumeral(int value) {
    return std::to_wstring(std::max(value, 0));
}

std::wstring BuildPadding(int count) {
    return std::wstring(std::max(count, 0), L' ');
}

std::wstring BuildTrailingPadding(int count) {
    return std::wstring(std::max(count, 0), L'\u00A0');
}

std::wstring BuildIndicatorGap() {
    return BuildPadding(std::max(g_settings.indicatorCharacterSpacing, 0));
}

std::wstring GetConfiguredMarkerSymbol() {
    return g_settings.markerSymbol.empty() ? std::wstring(L"\u2b24")
                                           : g_settings.markerSymbol;
}

bool TryParseColorString(const std::wstring& value,
                         winrt::Windows::UI::Color* color) {
    if (!color) {
        return false;
    }

    const wchar_t* start = value.c_str();
    while (*start && iswspace(*start)) {
        ++start;
    }

    const wchar_t* end = start + wcslen(start);
    while (end > start && iswspace(*(end - 1))) {
        --end;
    }

    if (start == end) {
        return false;
    }

    std::wstring trimmed(start, end);
    if (trimmed.rfind(L"#", 0) == 0) {
        trimmed.erase(0, 1);
    } else if (trimmed.rfind(L"0x", 0) == 0 || trimmed.rfind(L"0X", 0) == 0) {
        trimmed.erase(0, 2);
    }

    if (trimmed.size() != 6 && trimmed.size() != 8) {
        return false;
    }

    if (!std::all_of(trimmed.begin(), trimmed.end(),
                     [](wchar_t ch) { return iswxdigit(ch) != 0; })) {
        return false;
    }

    unsigned long parsed = wcstoul(trimmed.c_str(), nullptr, 16);
    if (trimmed.size() == 6) {
        color->A = 0xFF;
        color->R = static_cast<BYTE>((parsed >> 16) & 0xFF);
        color->G = static_cast<BYTE>((parsed >> 8) & 0xFF);
        color->B = static_cast<BYTE>(parsed & 0xFF);
    } else {
        color->A = static_cast<BYTE>((parsed >> 24) & 0xFF);
        color->R = static_cast<BYTE>((parsed >> 16) & 0xFF);
        color->G = static_cast<BYTE>((parsed >> 8) & 0xFF);
        color->B = static_cast<BYTE>(parsed & 0xFF);
    }

    return true;
}

std::wstring ApplyIndicatorCharacterSpacing(const std::wstring& text) {
    int spacing = std::max(g_settings.indicatorCharacterSpacing, 0);
    if (spacing == 0 || text.size() < 2) {
        return text;
    }

    std::wstring gap = BuildPadding(spacing);
    std::wstring result;
    result.reserve(text.size() + (text.size() - 1) * gap.size());

    for (size_t i = 0; i < text.size(); ++i) {
        if (i > 0) {
            result += gap;
        }
        result += text[i];
    }

    return result;
}

std::wstring FormatDesktopNumber(int value) {
    std::wstring desktopNumber;
    switch (g_settings.numberingFormat) {
        case NumberingFormat::Arabic:
            desktopNumber = ToArabicNumeral(value);
            break;
        case NumberingFormat::Roman:
        default:
            desktopNumber = ToRomanNumeral(value);
            break;
    }

    return ApplyIndicatorCharacterSpacing(desktopNumber);
}

std::wstring BuildIndicatorSuffix(bool hasBaseText,
                                  const std::wstring& desktopNumber) {
    std::wstring leftPadding =
        hasBaseText ? BuildPadding(g_settings.leftPadding) : L"";
    std::wstring rightPadding = BuildTrailingPadding(g_settings.rightPadding);
    return leftPadding + desktopNumber + rightPadding;
}

std::wstring BuildMarkerSequenceText(int desktopCount) {
    desktopCount = std::max(desktopCount, 1);

    std::wstring gap = BuildIndicatorGap();
    std::wstring markerSymbol = GetConfiguredMarkerSymbol();
    std::wstring result;

    for (int i = 0; i < desktopCount; ++i) {
        if (i > 0) {
            result += gap;
        }
        result += markerSymbol;
    }

    return result;
}

std::wstring FormatDesktopNameOrNumber(
    int value,
    const std::vector<std::wstring>& desktopNames) {
    if (value > 0 && static_cast<size_t>(value) <= desktopNames.size() &&
        !desktopNames[value - 1].empty()) {
        return desktopNames[value - 1];
    }

    return FormatDesktopNumber(value);
}

std::wstring BuildIndicatorCoreText(
    int currentDesktopNumber,
    int desktopCount,
    const std::vector<std::wstring>& desktopNames) {
    if (g_settings.indicatorMode == IndicatorMode::Markers) {
        return BuildMarkerSequenceText(desktopCount);
    }

    if (g_settings.indicatorMode == IndicatorMode::DesktopName) {
        return FormatDesktopNameOrNumber(currentDesktopNumber, desktopNames);
    }

    return FormatDesktopNumber(currentDesktopNumber);
}

FontWeight GetConfiguredIndicatorFontWeight() {
    switch (g_settings.indicatorWeight) {
        case IndicatorWeight::Bold:
            return FontWeights::Bold();
        case IndicatorWeight::Normal:
        default:
            return FontWeights::Normal();
    }
}

double GetConfiguredIndicatorFontSize(double baseFontSize) {
    switch (g_settings.indicatorSize) {
        case IndicatorSize::Smaller:
            return baseFontSize * 0.9;
        case IndicatorSize::Larger:
            return baseFontSize * 1.15;
        case IndicatorSize::Normal:
        default:
            return baseFontSize;
    }
}

bool UseTabularNumeralsForIndicator() {
    return g_settings.indicatorMode == IndicatorMode::Number &&
           g_settings.numberingFormat == NumberingFormat::Arabic;
}

NotificationInterfaceConfig GetNotificationInterfaceConfig() {
    if (g_explorerBuildNumber < 22000) {
        return {};
    }

    if (g_explorerBuildNumber < 22483 ||
        (g_explorerBuildNumber == 22621 && g_explorerRevisionNumber < 2215)) {
        return {
            5481970284372180562ll,
            -1679294552252794956ll,
            13,
            11,
            true,
        };
    }

    if (g_explorerBuildNumber < 22631 ||
        (g_explorerBuildNumber == 22631 && g_explorerRevisionNumber < 3085)) {
        return {
            5123538856297626140ll,
            8491238173783613346ll,
            14,
            10,
            false,
        };
    }

    return {
        5308375338100058445ll,
        -2401892766147978065ll,
        14,
        10,
        false,
    };
}

bool IsCurrentNotificationInterface(REFIID riid) {
    auto config = GetNotificationInterfaceConfig();
    if (config.methodCount == 0) {
        return false;
    }

    auto riidParts = reinterpret_cast<const int64_t*>(&riid);
    return riidParts[0] == config.iidPart1 && riidParts[1] == config.iidPart2;
}

void HandleVirtualDesktopChangedNotification() {
    if (g_unloading) {
        return;
    }

    int currentDesktopNumber = ReadCurrentDesktopNumberFromRegistry();
    int previousDesktopNumber = g_currentDesktopNumber.exchange(currentDesktopNumber);
    if (currentDesktopNumber != previousDesktopNumber) {
        UpdateAllClockEntries(false);
    }
}

HRESULT STDMETHODCALLTYPE VirtualDesktopNotification_QueryInterface(
    VirtualDesktopNotificationObject* pThis,
    REFIID riid,
    void** ppvObject) {
    if (!ppvObject) {
        return E_POINTER;
    }

    *ppvObject = nullptr;

    if (InlineIsEqualGUID(riid, IID_IUnknown_Local) ||
        IsCurrentNotificationInterface(riid)) {
        *ppvObject = pThis;
        InterlockedIncrement(&pThis->refCount);
        return S_OK;
    }

    return E_NOINTERFACE;
}

ULONG STDMETHODCALLTYPE
VirtualDesktopNotification_AddRef(VirtualDesktopNotificationObject* pThis) {
    return static_cast<ULONG>(InterlockedIncrement(&pThis->refCount));
}

ULONG STDMETHODCALLTYPE
VirtualDesktopNotification_Release(VirtualDesktopNotificationObject* pThis) {
    LONG refCount = InterlockedDecrement(&pThis->refCount);
    if (refCount == 0) {
        delete[] pThis->vtable;
        delete pThis;
    }

    return static_cast<ULONG>(std::max<LONG>(refCount, 0));
}

HRESULT STDMETHODCALLTYPE VirtualDesktopNotification_NoOp() {
    return S_OK;
}

HRESULT STDMETHODCALLTYPE VirtualDesktopNotification_CurrentChanged(
    VirtualDesktopNotificationObject*) {
    HandleVirtualDesktopChangedNotification();
    return S_OK;
}

HRESULT STDMETHODCALLTYPE VirtualDesktopNotification_CurrentChangedWithMonitors(
    VirtualDesktopNotificationObject*,
    void*,
    void*,
    void*) {
    HandleVirtualDesktopChangedNotification();
    return S_OK;
}

VirtualDesktopNotificationObject* CreateVirtualDesktopNotificationObject() {
    auto config = GetNotificationInterfaceConfig();
    if (config.methodCount == 0 || config.currentChangedIndex < 0 ||
        config.currentChangedIndex >= config.methodCount) {
        return nullptr;
    }

    auto object = new (std::nothrow) VirtualDesktopNotificationObject();
    if (!object) {
        return nullptr;
    }

    object->vtable = new (std::nothrow) void*[config.methodCount];
    if (!object->vtable) {
        delete object;
        return nullptr;
    }

    for (int i = 0; i < config.methodCount; ++i) {
        object->vtable[i] = reinterpret_cast<void*>(
            &VirtualDesktopNotification_NoOp);
    }

    object->vtable[0] = reinterpret_cast<void*>(
        &VirtualDesktopNotification_QueryInterface);
    object->vtable[1] = reinterpret_cast<void*>(
        &VirtualDesktopNotification_AddRef);
    object->vtable[2] = reinterpret_cast<void*>(
        &VirtualDesktopNotification_Release);
    if (config.currentChangedHasMonitors) {
        object->vtable[config.currentChangedIndex] = reinterpret_cast<void*>(
            &VirtualDesktopNotification_CurrentChangedWithMonitors);
    } else {
        object->vtable[config.currentChangedIndex] = reinterpret_cast<void*>(
            &VirtualDesktopNotification_CurrentChanged);
    }

    return object;
}

std::vector<BYTE> ReadRegistryValue(HKEY root,
                                    const std::wstring& subKey,
                                    const std::wstring& valueName,
                                    DWORD* valueType) {
    DWORD type = 0;
    DWORD size = 0;

    LONG ret = RegGetValueW(root, subKey.c_str(), valueName.c_str(),
                            RRF_RT_ANY, &type, nullptr, &size);
    if (ret != ERROR_SUCCESS || size == 0) {
        return {};
    }

    std::vector<BYTE> buffer(size);
    ret = RegGetValueW(root, subKey.c_str(), valueName.c_str(), RRF_RT_ANY, &type,
                       buffer.data(), &size);
    if (ret != ERROR_SUCCESS) {
        return {};
    }

    buffer.resize(size);
    if (valueType) {
        *valueType = type;
    }

    return buffer;
}

bool ParseGuidValue(const std::vector<BYTE>& buffer, DWORD type, GUID* guid) {
    if (!guid || buffer.empty()) {
        return false;
    }

    if (type == REG_BINARY && buffer.size() >= sizeof(GUID)) {
        memcpy(guid, buffer.data(), sizeof(GUID));
        return true;
    }

    if (type == REG_SZ || type == REG_EXPAND_SZ) {
        const wchar_t* text = reinterpret_cast<const wchar_t*>(buffer.data());
        if (!text || !*text) {
            return false;
        }

        return SUCCEEDED(CLSIDFromString(text, guid));
    }

    return false;
}

std::vector<GUID> ReadVirtualDesktopIds() {
    std::vector<GUID> ids;
    DWORD sessionId = 0;
    ProcessIdToSessionId(GetCurrentProcessId(), &sessionId);

    std::wstring sessionPath =
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\SessionInfo\\" +
        std::to_wstring(sessionId) + L"\\VirtualDesktops";

    for (const auto& path : {
             std::wstring(
                 L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\VirtualDesktops"),
             sessionPath,
         }) {
        DWORD type = 0;
        auto buffer =
            ReadRegistryValue(HKEY_CURRENT_USER, path, L"VirtualDesktopIDs", &type);
        if (type != REG_BINARY || buffer.size() < sizeof(GUID)) {
            continue;
        }

        size_t count = buffer.size() / sizeof(GUID);
        ids.resize(count);
        memcpy(ids.data(), buffer.data(), count * sizeof(GUID));
        return ids;
    }

    return ids;
}

bool ReadCurrentDesktopGuid(GUID* guid) {
    if (!guid) {
        return false;
    }

    DWORD sessionId = 0;
    ProcessIdToSessionId(GetCurrentProcessId(), &sessionId);

    std::wstring sessionPath =
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\SessionInfo\\" +
        std::to_wstring(sessionId) + L"\\VirtualDesktops";

    for (const auto& path : {
             sessionPath,
             std::wstring(
                 L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\VirtualDesktops"),
         }) {
        DWORD type = 0;
        auto buffer = ReadRegistryValue(HKEY_CURRENT_USER, path,
                                        L"CurrentVirtualDesktop", &type);
        if (ParseGuidValue(buffer, type, guid)) {
            return true;
        }
    }

    return false;
}

int ReadCurrentDesktopNumberFromRegistry() {
    auto desktopIds = ReadVirtualDesktopIds();
    if (desktopIds.empty()) {
        return 1;
    }

    GUID currentGuid{};
    if (!ReadCurrentDesktopGuid(&currentGuid)) {
        return 1;
    }

    for (size_t i = 0; i < desktopIds.size(); ++i) {
        if (InlineIsEqualGUID(desktopIds[i], currentGuid)) {
            return static_cast<int>(i + 1);
        }
    }

    return 1;
}

int ReadDesktopCountFromRegistry() {
    auto desktopIds = ReadVirtualDesktopIds();
    return desktopIds.empty() ? 1 : static_cast<int>(desktopIds.size());
}

std::wstring ReadRegistryStringValue(HKEY root,
                                     const std::wstring& subKey,
                                     const std::wstring& valueName) {
    DWORD type = 0;
    auto buffer = ReadRegistryValue(root, subKey, valueName, &type);
    if ((type != REG_SZ && type != REG_EXPAND_SZ) ||
        buffer.size() < sizeof(wchar_t)) {
        return {};
    }

    std::wstring value(reinterpret_cast<const wchar_t*>(buffer.data()),
                       buffer.size() / sizeof(wchar_t));
    while (!value.empty() && value.back() == L'\0') {
        value.pop_back();
    }

    return value;
}

std::wstring GuidToRegistryString(const GUID& guid) {
    wchar_t guidText[39] = {};
    if (StringFromGUID2(guid, guidText, ARRAYSIZE(guidText)) == 0) {
        return {};
    }

    return guidText;
}

std::wstring ReadVirtualDesktopName(const GUID& desktopId) {
    DWORD sessionId = 0;
    ProcessIdToSessionId(GetCurrentProcessId(), &sessionId);

    std::wstring desktopIdText = GuidToRegistryString(desktopId);
    if (desktopIdText.empty()) {
        return {};
    }

    std::wstring sessionPath =
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\SessionInfo\\" +
        std::to_wstring(sessionId) + L"\\VirtualDesktops\\Desktops\\" +
        desktopIdText;

    for (const auto& path : {
             std::wstring(
                 L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\VirtualDesktops\\Desktops\\") +
                 desktopIdText,
             sessionPath,
         }) {
        std::wstring name = ReadRegistryStringValue(HKEY_CURRENT_USER, path, L"Name");
        if (!name.empty()) {
            return name;
        }
    }

    return {};
}

std::vector<std::wstring> ReadVirtualDesktopNames() {
    std::vector<std::wstring> names;
    auto desktopIds = ReadVirtualDesktopIds();
    names.reserve(desktopIds.size());

    for (const auto& desktopId : desktopIds) {
        names.push_back(ReadVirtualDesktopName(desktopId));
    }

    return names;
}

void LoadSettings() {
    StringSetting position = StringSetting::make(L"Placement.position");
    const wchar_t* positionValue = position.get();
    if (wcscmp(positionValue, L"afterStartBeforeIcons") == 0) {
        g_settings.position = IndicatorPosition::AfterStartBeforeIcons;
    } else if (wcscmp(positionValue, L"afterStartAfterIcons") == 0) {
        g_settings.position = IndicatorPosition::AfterStartAfterIcons;
    } else if (wcscmp(positionValue, L"beforeTray") == 0) {
        g_settings.position = IndicatorPosition::BeforeTray;
    } else if (wcscmp(positionValue, L"afterClock") == 0) {
        g_settings.position = IndicatorPosition::AfterClock;
    } else if (wcscmp(positionValue, L"dynamicCenter") == 0) {
        g_settings.position = IndicatorPosition::DynamicCenter;
    } else {
        g_settings.position = IndicatorPosition::BeforeTray;
    }


    g_settings.horizontalOffset = std::clamp(Wh_GetIntSetting(L"Placement.horizontalOffset"), -1000, 1000);

    // Four signed values, matching Mawaqit's compact margin setting.
    g_settings.nativeGap = 0;
    g_settings.nativeMarginLeft = g_settings.nativeMarginTop = 0;
    g_settings.nativeMarginRight = g_settings.nativeMarginBottom = 0;
    {
        StringSetting margins = StringSetting::make(L"Placement.nativeMargins");
        const wchar_t* cursor = margins.get();
        int* values[] = {&g_settings.nativeMarginLeft, &g_settings.nativeMarginTop,
                         &g_settings.nativeMarginRight, &g_settings.nativeMarginBottom};
        bool valid = cursor != nullptr;
        for (int i = 0; i < 4 && valid; ++i) {
            while (*cursor == L' ' || *cursor == L'\t') ++cursor;
            wchar_t* end = nullptr;
            long value = wcstol(cursor, &end, 10);
            if (end == cursor) { valid = false; break; }
            *values[i] = static_cast<int>(std::clamp(value, -100L, 100L));
            cursor = end;
            while (*cursor == L' ' || *cursor == L'\t') ++cursor;
            if (i < 3) {
                if (*cursor != L',') { valid = false; break; }
                ++cursor;
            } else if (*cursor != L'\0') {
                valid = false;
            }
        }
        if (!valid) {
            g_settings.nativeMarginLeft = g_settings.nativeMarginTop = 0;
            g_settings.nativeMarginRight = g_settings.nativeMarginBottom = 0;
            Wh_Log(L"[Emberveil] Invalid nativeMargins; expected left, top, right, bottom");
        }
    }

    StringSetting indicatorMode = StringSetting::make(L"Content.indicatorMode");
    if (wcscmp(indicatorMode.get(), L"number") == 0) {
        g_settings.indicatorMode = IndicatorMode::Number;
    } else if (wcscmp(indicatorMode.get(), L"desktopName") == 0) {
        g_settings.indicatorMode = IndicatorMode::DesktopName;
    } else {
        g_settings.indicatorMode = IndicatorMode::Markers;
    }

    StringSetting markerSymbol = StringSetting::make(L"Content.markerSymbol");
    g_settings.markerSymbol = markerSymbol.get();
    if (g_settings.markerSymbol.empty()) {
        g_settings.markerSymbol = L"\u2b24";
    }

    StringSetting themePreset = StringSetting::make(L"Appearance.themePreset");
    g_settings.themePreset = themePreset.get();
    if (g_settings.themePreset.empty()) g_settings.themePreset = L"windows";
    StringSetting hoverMarkerColor = StringSetting::make(L"Appearance.hoverMarkerColor");
    g_settings.hoverMarkerColor = hoverMarkerColor.get();

    StringSetting activeIndicatorColor = StringSetting::make(L"Appearance.activeIndicatorColor");
    g_settings.activeIndicatorColor = activeIndicatorColor.get();

    StringSetting inactiveMarkerColor = StringSetting::make(L"Appearance.inactiveMarkerColor");
    g_settings.inactiveMarkerColor = inactiveMarkerColor.get();

    g_settings.hideWhenSingleDesktop = Wh_GetIntSetting(L"Content.hideWhenSingleDesktop");
    g_settings.markerTooltips = Wh_GetIntSetting(L"Appearance.markerTooltips") != 0;

    StringSetting numberingFormat = StringSetting::make(L"Content.numberingFormat");
    if (wcscmp(numberingFormat.get(), L"arabic") == 0) {
        g_settings.numberingFormat = NumberingFormat::Arabic;
    } else {
        g_settings.numberingFormat = NumberingFormat::Roman;
    }

    StringSetting indicatorWeight = StringSetting::make(L"Appearance.indicatorWeight");
    if (wcscmp(indicatorWeight.get(), L"bold") == 0) {
        g_settings.indicatorWeight = IndicatorWeight::Bold;
    } else {
        g_settings.indicatorWeight = IndicatorWeight::Normal;
    }

    StringSetting indicatorSize = StringSetting::make(L"Appearance.indicatorSize");
    if (wcscmp(indicatorSize.get(), L"smaller") == 0) {
        g_settings.indicatorSize = IndicatorSize::Smaller;
    } else if (wcscmp(indicatorSize.get(), L"larger") == 0) {
        g_settings.indicatorSize = IndicatorSize::Larger;
    } else {
        g_settings.indicatorSize = IndicatorSize::Normal;
    }

    g_settings.leftPadding = std::max(0, Wh_GetIntSetting(L"Spacing.leftPadding"));
    g_settings.rightPadding = std::max(0, Wh_GetIntSetting(L"Spacing.rightPadding"));
    g_settings.indicatorCharacterSpacing =
        std::max(0, Wh_GetIntSetting(L"Spacing.indicatorCharacterSpacing"));
    g_settings.inactiveMarkerOpacity =
        std::clamp(Wh_GetIntSetting(L"Appearance.inactiveMarkerOpacity"), 0, 100);
    g_settings.pollIntervalMs = std::clamp(Wh_GetIntSetting(L"Advanced.pollIntervalMs"), 0, 2000);
    g_pollIntervalMs.store(g_settings.pollIntervalMs);
}

VS_FIXEDFILEINFO* GetModuleVersionInfo(HMODULE module, UINT* length) {
    void* fixedFileInfo = nullptr;
    UINT fixedFileInfoLength = 0;

    HRSRC versionResource =
        FindResourceW(module, MAKEINTRESOURCEW(VS_VERSION_INFO), RT_VERSION);
    if (versionResource) {
        HGLOBAL loadedResource = LoadResource(module, versionResource);
        if (loadedResource) {
            void* lockedResource = LockResource(loadedResource);
            if (lockedResource &&
                (!VerQueryValueW(lockedResource, L"\\", &fixedFileInfo,
                                 &fixedFileInfoLength) ||
                 fixedFileInfoLength == 0)) {
                fixedFileInfo = nullptr;
                fixedFileInfoLength = 0;
            }
        }
    }

    if (length) {
        *length = fixedFileInfoLength;
    }

    return static_cast<VS_FIXEDFILEINFO*>(fixedFileInfo);
}

WinVersion GetExplorerVersion() {
    VS_FIXEDFILEINFO* fixedFileInfo = GetModuleVersionInfo(nullptr, nullptr);
    if (!fixedFileInfo) {
        return WinVersion::Unsupported;
    }

    WORD major = HIWORD(fixedFileInfo->dwFileVersionMS);
    WORD build = HIWORD(fixedFileInfo->dwFileVersionLS);
    WORD revision = LOWORD(fixedFileInfo->dwFileVersionLS);

    g_explorerBuildNumber = build;
    g_explorerRevisionNumber = revision;

    if (major != 10) {
        return WinVersion::Unsupported;
    }

    if (build < 22000) {
        return WinVersion::Win10;
    }

    if (build == 22000) {
        return WinVersion::Win11;
    }

    if (build < 26100) {
        return WinVersion::Win11_22H2;
    }

    return WinVersion::Win11_24H2;
}

bool RegisterVirtualDesktopNotificationsOnCurrentThread() {
    if (g_virtualDesktopNotificationsRegistered) {
        return true;
    }

    auto config = GetNotificationInterfaceConfig();
    if (config.methodCount == 0) {
        Wh_Log(L"Virtual desktop notifications unavailable for Explorer build %u.%u",
               g_explorerBuildNumber, g_explorerRevisionNumber);
        return false;
    }

    IServiceProvider* serviceProvider = nullptr;
    HRESULT hr = CoCreateInstance(CLSID_ImmersiveShell, nullptr,
                                  CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER,
                                  IID_PPV_ARGS(&serviceProvider));
    if (FAILED(hr)) {
        Wh_Log(L"Virtual desktop notification registration failed at CoCreateInstance: hr=0x%08X",
               hr);
        return false;
    }

    IVirtualDesktopNotificationService* notificationService = nullptr;
    hr = serviceProvider->QueryService(SID_VirtualDesktopNotificationService,
                                       IID_IVirtualDesktopNotificationService,
                                       reinterpret_cast<void**>(&notificationService));
    serviceProvider->Release();
    if (FAILED(hr)) {
        Wh_Log(L"Virtual desktop notification registration failed at QueryService: hr=0x%08X",
               hr);
        return false;
    }

    auto notificationObject = CreateVirtualDesktopNotificationObject();
    if (!notificationObject) {
        Wh_Log(L"Virtual desktop notification registration failed: couldn't create notification object");
        notificationService->Release();
        return false;
    }

    DWORD cookie = 0;
    hr = notificationService->Register(reinterpret_cast<IUnknown*>(notificationObject),
                                       &cookie);
    notificationService->Release();

    if (FAILED(hr) || cookie == 0) {
        Wh_Log(L"Virtual desktop notification registration failed at Register: hr=0x%08X, cookie=%lu",
               hr, cookie);
        VirtualDesktopNotification_Release(notificationObject);
        return false;
    }

    g_virtualDesktopNotificationObject = notificationObject;
    g_virtualDesktopNotificationCookie = cookie;
    g_virtualDesktopNotificationsRegistered = true;
    return true;
}

void UnregisterVirtualDesktopNotificationsOnCurrentThread() {
    if (!g_virtualDesktopNotificationsRegistered) {
        return;
    }

    IServiceProvider* serviceProvider = nullptr;
    HRESULT hr = CoCreateInstance(CLSID_ImmersiveShell, nullptr,
                                  CLSCTX_INPROC_SERVER | CLSCTX_LOCAL_SERVER,
                                  IID_PPV_ARGS(&serviceProvider));
    if (SUCCEEDED(hr)) {
        IVirtualDesktopNotificationService* notificationService = nullptr;
        hr = serviceProvider->QueryService(
            SID_VirtualDesktopNotificationService,
            IID_IVirtualDesktopNotificationService,
            reinterpret_cast<void**>(&notificationService));
        serviceProvider->Release();

        if (SUCCEEDED(hr)) {
            notificationService->Unregister(g_virtualDesktopNotificationCookie);
            notificationService->Release();
        }
    }

    if (g_virtualDesktopNotificationObject) {
        VirtualDesktopNotification_Release(g_virtualDesktopNotificationObject);
        g_virtualDesktopNotificationObject = nullptr;
    }

    g_virtualDesktopNotificationCookie = 0;
    g_virtualDesktopNotificationsRegistered = false;
}

DWORD WINAPI VirtualDesktopNotificationThreadProc(LPVOID) {
    HRESULT initHr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(initHr)) {
        Wh_Log(L"Virtual desktop notification thread failed to initialize COM: hr=0x%08X",
               initHr);
        if (g_notificationReadyEvent) {
            SetEvent(g_notificationReadyEvent);
        }
        return 0;
    }

    RegisterVirtualDesktopNotificationsOnCurrentThread();
    if (g_notificationReadyEvent) {
        SetEvent(g_notificationReadyEvent);
    }

    if (g_notificationStopEvent) {
        bool stopping = false;
        while (!stopping) {
            if (!g_virtualDesktopNotificationsRegistered) {
                RegisterVirtualDesktopNotificationsOnCurrentThread();
            }

            DWORD waitTimeout = g_virtualDesktopNotificationsRegistered ? INFINITE : 1000;
            DWORD waitResult = MsgWaitForMultipleObjects(
                1, &g_notificationStopEvent, FALSE, waitTimeout, QS_ALLINPUT);
            switch (waitResult) {
                case WAIT_OBJECT_0:
                    stopping = true;
                    break;
                case WAIT_OBJECT_0 + 1: {
                    MSG msg;
                    while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
                        TranslateMessage(&msg);
                        DispatchMessageW(&msg);
                    }
                    break;
                }
                case WAIT_TIMEOUT:
                    break;
                default:
                    Wh_Log(L"Virtual desktop notification thread wait returned unexpectedly: %lu",
                           waitResult);
                    stopping = true;
                    break;
            }
        }
    }

    if (g_virtualDesktopNotificationsRegistered) {
        UnregisterVirtualDesktopNotificationsOnCurrentThread();
    }

    CoUninitialize();
    return 0;
}

bool EnsureVirtualDesktopNotificationThread() {
    if (g_notificationThread &&
        WaitForSingleObject(g_notificationThread, 0) == WAIT_OBJECT_0) {
        CloseHandle(g_notificationThread);
        g_notificationThread = nullptr;

        if (g_notificationReadyEvent) {
            CloseHandle(g_notificationReadyEvent);
            g_notificationReadyEvent = nullptr;
        }

        if (g_notificationStopEvent) {
            CloseHandle(g_notificationStopEvent);
            g_notificationStopEvent = nullptr;
        }
    }

    if (g_notificationThread) {
        return g_virtualDesktopNotificationsRegistered.load();
    }

    g_notificationStopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!g_notificationStopEvent) {
        Wh_Log(L"Failed to create virtual desktop notification stop event");
        return false;
    }

    g_notificationReadyEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!g_notificationReadyEvent) {
        Wh_Log(L"Failed to create virtual desktop notification ready event");
        CloseHandle(g_notificationStopEvent);
        g_notificationStopEvent = nullptr;
        return false;
    }

    g_notificationThread = CreateThread(nullptr, 0,
                                        VirtualDesktopNotificationThreadProc,
                                        nullptr, 0, nullptr);
    if (!g_notificationThread) {
        Wh_Log(L"Failed to create virtual desktop notification thread");
        CloseHandle(g_notificationReadyEvent);
        g_notificationReadyEvent = nullptr;
        CloseHandle(g_notificationStopEvent);
        g_notificationStopEvent = nullptr;
        return false;
    }

    DWORD waitResult = WaitForSingleObject(g_notificationReadyEvent, 3000);
    if (waitResult != WAIT_OBJECT_0) {
        Wh_Log(L"Timed out waiting for virtual desktop notification thread readiness: %lu",
               waitResult);
    }

    return g_virtualDesktopNotificationsRegistered.load();
}

void StopVirtualDesktopNotificationThread() {
    if (g_notificationStopEvent) {
        SetEvent(g_notificationStopEvent);
    }

    if (g_notificationThread) {
        WaitForSingleObject(g_notificationThread, 3000);
        CloseHandle(g_notificationThread);
        g_notificationThread = nullptr;
    }

    if (g_notificationReadyEvent) {
        CloseHandle(g_notificationReadyEvent);
        g_notificationReadyEvent = nullptr;
    }

    if (g_notificationStopEvent) {
        CloseHandle(g_notificationStopEvent);
        g_notificationStopEvent = nullptr;
    }
}

FrameworkElement FindDescendantByName(const DependencyObject& parent,
                                      const winrt::hstring& name) {
    auto frameworkElement = parent.try_as<FrameworkElement>();
    if (frameworkElement && frameworkElement.Name() == name) {
        return frameworkElement;
    }

    int childrenCount = Media::VisualTreeHelper::GetChildrenCount(parent);
    for (int i = 0; i < childrenCount; ++i) {
        auto child = Media::VisualTreeHelper::GetChild(parent, i);
        auto result = FindDescendantByName(child, name);
        if (result) {
            return result;
        }
    }

    return nullptr;
}

bool TryGetClockTextBlocks(FrameworkElement root,
                           Controls::TextBlock* dateTextBlock,
                           Controls::TextBlock* timeTextBlock) {
    if (!dateTextBlock || !timeTextBlock) {
        return false;
    }

    *dateTextBlock = FindDescendantByName(root, L"DateInnerTextBlock")
                         .try_as<Controls::TextBlock>();
    *timeTextBlock = FindDescendantByName(root, L"TimeInnerTextBlock")
                         .try_as<Controls::TextBlock>();

    return static_cast<bool>(*dateTextBlock || *timeTextBlock);
}

Controls::Grid TryGetClockContainerGrid(FrameworkElement root) {
    return FindDescendantByName(root, L"ContainerGrid").try_as<Controls::Grid>();
}

Controls::StackPanel TryGetClockStackPanel(Controls::Grid containerGrid) {
    if (!containerGrid) {
        return nullptr;
    }

    for (const auto& child : containerGrid.Children()) {
        auto stackPanel = child.try_as<Controls::StackPanel>();
        if (stackPanel) {
            return stackPanel;
        }
    }

    return nullptr;
}

ClockEntryPtr AddOrGetClockEntry(Controls::TextBlock dateTextBlock,
                                 Controls::TextBlock timeTextBlock) {
    auto sameBlock = [&](const ClockEntryPtr& entry) {
        auto existingDate = entry->dateTextBlock.get();
        auto existingTime = entry->timeTextBlock.get();
        return (existingDate && dateTextBlock && existingDate == dateTextBlock) ||
               (existingTime && timeTextBlock && existingTime == timeTextBlock);
    };

    std::lock_guard<std::mutex> lock(g_clockEntriesMutex);

    g_clockEntries.erase(
        std::remove_if(g_clockEntries.begin(), g_clockEntries.end(),
                       [](const ClockEntryPtr& entry) {
                           return !entry->dateTextBlock.get() &&
                                  !entry->timeTextBlock.get();
                       }),
        g_clockEntries.end());

    auto it = std::find_if(g_clockEntries.begin(), g_clockEntries.end(), sameBlock);
    if (it != g_clockEntries.end()) {
        (*it)->dateTextBlock = dateTextBlock;
        (*it)->timeTextBlock = timeTextBlock;
        return *it;
    }

    auto entry = std::make_shared<ClockEntry>();
    entry->dateTextBlock = dateTextBlock;
    entry->timeTextBlock = timeTextBlock;
    g_clockEntries.push_back(entry);
    return entry;
}

std::vector<ClockEntryPtr> GetClockEntriesSnapshot() {
    std::lock_guard<std::mutex> lock(g_clockEntriesMutex);
    return g_clockEntries;
}

double MeasureSingleRunTextWidth(const Controls::TextBlock& source,
                                 const std::wstring& text,
                                 FontWeight fontWeight) {
    Controls::TextBlock measureBlock;
    measureBlock.FontFamily(source.FontFamily());
    measureBlock.FontSize(source.FontSize());
    measureBlock.FontStretch(source.FontStretch());
    measureBlock.FontStyle(source.FontStyle());
    measureBlock.FontWeight(source.FontWeight());
    measureBlock.CharacterSpacing(source.CharacterSpacing());
    measureBlock.TextWrapping(TextWrapping::NoWrap);

    auto inlines = measureBlock.Inlines();
    inlines.Clear();

    Documents::Run run;
    run.Text(winrt::hstring(text));
    run.FontWeight(fontWeight);
    run.FontSize(GetConfiguredIndicatorFontSize(source.FontSize()));
    if (UseTabularNumeralsForIndicator()) {
        Documents::Typography::SetNumeralAlignment(
            run, FontNumeralAlignment::Tabular);
    }
    inlines.Append(run);

    measureBlock.Measure(winrt::Windows::Foundation::Size{
        std::numeric_limits<float>::infinity(),
        std::numeric_limits<float>::infinity(),
    });
    return measureBlock.DesiredSize().Width;
}

double MeasureIndicatorTextWidth(const Controls::TextBlock& source,
                                 const std::wstring& baseText,
                                 const std::wstring& suffix) {
    Controls::TextBlock measureBlock;
    measureBlock.FontFamily(source.FontFamily());
    measureBlock.FontSize(source.FontSize());
    measureBlock.FontStretch(source.FontStretch());
    measureBlock.FontStyle(source.FontStyle());
    measureBlock.FontWeight(source.FontWeight());
    measureBlock.CharacterSpacing(source.CharacterSpacing());
    measureBlock.TextWrapping(TextWrapping::NoWrap);

    auto inlines = measureBlock.Inlines();
    inlines.Clear();

    if (!baseText.empty()) {
        Documents::Run baseRun;
        baseRun.Text(winrt::hstring(baseText));
        inlines.Append(baseRun);
    }

    if (!suffix.empty()) {
        Documents::Run suffixRun;
        suffixRun.Text(winrt::hstring(suffix));
        suffixRun.FontWeight(GetConfiguredIndicatorFontWeight());
        suffixRun.FontSize(GetConfiguredIndicatorFontSize(source.FontSize()));
        if (UseTabularNumeralsForIndicator()) {
            Documents::Typography::SetNumeralAlignment(
                suffixRun, FontNumeralAlignment::Tabular);
        }
        inlines.Append(suffixRun);
    }

    measureBlock.Measure(winrt::Windows::Foundation::Size{
        std::numeric_limits<float>::infinity(),
        std::numeric_limits<float>::infinity(),
    });
    return measureBlock.DesiredSize().Width;
}

std::vector<IndicatorSegment> BuildMarkerSuffixSegments(bool hasBaseText,
                                                        int currentDesktopNumber,
                                                        int desktopCount) {
    std::vector<IndicatorSegment> segments;

    if (hasBaseText && g_settings.leftPadding > 0) {
        segments.push_back({BuildPadding(g_settings.leftPadding),
                            IndicatorSegmentStyle::Normal});
    }

    std::wstring gap = BuildIndicatorGap();
    std::wstring markerSymbol = GetConfiguredMarkerSymbol();
    desktopCount = std::max(desktopCount, 1);
    currentDesktopNumber = std::clamp(currentDesktopNumber, 1, desktopCount);

    for (int i = 1; i <= desktopCount; ++i) {
        if (i > 1 && !gap.empty()) {
            segments.push_back({gap, IndicatorSegmentStyle::Normal});
        }

        segments.push_back(
            {markerSymbol,
             i == currentDesktopNumber ? IndicatorSegmentStyle::Normal
                                       : IndicatorSegmentStyle::Dimmed});
    }

    if (g_settings.rightPadding > 0) {
        segments.push_back(
            {BuildTrailingPadding(g_settings.rightPadding),
             IndicatorSegmentStyle::Normal});
    }

    return segments;
}

IndicatorLayout BuildIndicatorLayout(const Controls::TextBlock& source,
                                     bool hasBaseText,
                                     int currentDesktopNumber,
                                     int desktopCount,
                                     const std::vector<std::wstring>& desktopNames) {
    IndicatorLayout layout;

    if (g_settings.indicatorMode == IndicatorMode::Markers) {
        layout.renderedSuffix = BuildIndicatorSuffix(
            hasBaseText,
            BuildIndicatorCoreText(currentDesktopNumber, desktopCount,
                                   desktopNames));
        layout.widestSuffixWidth = MeasureSingleRunTextWidth(
            source, layout.renderedSuffix, GetConfiguredIndicatorFontWeight());
        layout.suffixSegments = BuildMarkerSuffixSegments(
            hasBaseText, currentDesktopNumber, desktopCount);
        return layout;
    }

    std::wstring visibleSuffix = BuildIndicatorSuffix(
        hasBaseText,
        BuildIndicatorCoreText(currentDesktopNumber, desktopCount, desktopNames));

    double currentWidth = MeasureSingleRunTextWidth(
        source, visibleSuffix, GetConfiguredIndicatorFontWeight());
    layout.widestSuffixWidth = currentWidth;

    for (int i = 1; i <= desktopCount; ++i) {
        std::wstring candidateText =
            g_settings.indicatorMode == IndicatorMode::DesktopName
                ? FormatDesktopNameOrNumber(i, desktopNames)
                : FormatDesktopNumber(i);
        std::wstring candidateSuffix = BuildIndicatorSuffix(hasBaseText,
                                                            candidateText);
        double candidateWidth = MeasureSingleRunTextWidth(
            source, candidateSuffix, GetConfiguredIndicatorFontWeight());
        if (candidateWidth > layout.widestSuffixWidth) {
            layout.widestSuffixWidth = candidateWidth;
        }
    }

    struct SpacerCandidate {
        wchar_t ch;
        double width;
    };

    const wchar_t spacerChars[] = {
        L'\u00A0',  // no-break space
        L'\u2007',  // figure space
        L'\u2005',  // four-per-em space
        L'\u2009',  // thin space
        L'\u200A',  // hair space
    };

    auto buildInvisibleFillerText = [&](double targetWidth) {
        if (targetWidth <= 0.1) {
            return std::wstring{};
        }

        std::vector<SpacerCandidate> candidates;
        for (wchar_t ch : spacerChars) {
            std::wstring text(1, ch);
            double width = MeasureSingleRunTextWidth(
                source, text, GetConfiguredIndicatorFontWeight());
            if (width > 0.01) {
                candidates.push_back({ch, width});
            }
        }

        std::sort(candidates.begin(), candidates.end(),
                  [](const SpacerCandidate& a, const SpacerCandidate& b) {
                      return a.width > b.width;
                  });

        std::wstring result;
        double usedWidth = 0;
        for (const auto& candidate : candidates) {
            while (usedWidth + candidate.width <= targetWidth + 0.01) {
                result += candidate.ch;
                usedWidth += candidate.width;
            }
        }

        return result;
    };

    double fillerWidth = std::max(0.0, layout.widestSuffixWidth - currentWidth);
    std::wstring leftFiller = buildInvisibleFillerText(fillerWidth / 2.0);
    double leftFillerWidth = MeasureSingleRunTextWidth(
        source, leftFiller, GetConfiguredIndicatorFontWeight());
    std::wstring rightFiller =
        buildInvisibleFillerText(std::max(0.0, fillerWidth - leftFillerWidth));

    layout.renderedSuffix = leftFiller + visibleSuffix + rightFiller;
    layout.suffixSegments.push_back(
        {leftFiller, IndicatorSegmentStyle::Transparent});
    layout.suffixSegments.push_back(
        {visibleSuffix, IndicatorSegmentStyle::Normal});
    layout.suffixSegments.push_back(
        {rightFiller, IndicatorSegmentStyle::Transparent});
    return layout;
}

template <typename TInlines>
void AppendRun(const TInlines& inlines,
               const std::wstring& text,
               FontWeight fontWeight,
               Media::Brush foreground = nullptr,
               bool useIndicatorTypography = true,
               double fontSize = 0) {
    if (text.empty()) {
        return;
    }

    Documents::Run run;
    run.Text(winrt::hstring(text));
    run.FontWeight(fontWeight);
    if (fontSize > 0) {
        run.FontSize(fontSize);
    }
    if (useIndicatorTypography && UseTabularNumeralsForIndicator()) {
        Documents::Typography::SetNumeralAlignment(
            run, FontNumeralAlignment::Tabular);
    }
    if (foreground) {
        run.Foreground(foreground);
    }
    inlines.Append(run);
}

Media::Brush CreateTransparentBrush() {
    return Media::SolidColorBrush(winrt::Windows::UI::Color{0, 255, 255, 255});
}

Media::Brush CreateConfiguredIndicatorBrush(const std::wstring& colorValue) {
    winrt::Windows::UI::Color color{};
    if (!TryParseColorString(colorValue, &color)) {
        return nullptr;
    }

    return Media::SolidColorBrush(color);
}

Media::Brush CreateDimmedIndicatorBrush(Controls::TextBlock targetTextBlock) {
    winrt::Windows::UI::Color color{255, 255, 255, 255};

    if (!TryParseColorString(g_settings.inactiveMarkerColor, &color)) {
        auto solidBrush =
            targetTextBlock.Foreground().try_as<Media::SolidColorBrush>();
        if (solidBrush) {
            color = solidBrush.Color();
        }
    }

    color.A = static_cast<BYTE>((color.A * std::clamp(
        g_settings.inactiveMarkerOpacity, 0, 100)) / 100);

    return Media::SolidColorBrush(color);
}

void SetIndicatorTextBlockContent(Controls::TextBlock targetTextBlock,
                                  const std::wstring& baseText,
                                  const IndicatorLayout& layout) {
    auto inlines = targetTextBlock.Inlines();
    inlines.Clear();

    if (!baseText.empty()) {
        AppendRun(inlines, baseText, targetTextBlock.FontWeight(), nullptr, false,
                  targetTextBlock.FontSize());
    }

    Media::Brush transparentBrush = CreateTransparentBrush();
    Media::Brush indicatorBrush =
        CreateConfiguredIndicatorBrush(g_settings.activeIndicatorColor);
    Media::Brush dimmedBrush = CreateDimmedIndicatorBrush(targetTextBlock);
    double indicatorFontSize =
        GetConfiguredIndicatorFontSize(targetTextBlock.FontSize());

    for (const auto& segment : layout.suffixSegments) {
        Media::Brush foreground = nullptr;
        if (segment.style == IndicatorSegmentStyle::Transparent) {
            foreground = transparentBrush;
        } else if (segment.style == IndicatorSegmentStyle::Dimmed) {
            foreground = dimmedBrush;
        } else if (indicatorBrush) {
            foreground = indicatorBrush;
        }

        AppendRun(inlines, segment.text, GetConfiguredIndicatorFontWeight(),
                  foreground, true, indicatorFontSize);
    }
}

bool ShouldUseSeparateIndicator(const ClockEntryPtr& entry) {
    auto dateTextBlock = entry->dateTextBlock.get();
    auto timeTextBlock = entry->timeTextBlock.get();

    return dateTextBlock && timeTextBlock &&
           dateTextBlock.Visibility() == Visibility::Visible &&
           timeTextBlock.Visibility() == Visibility::Visible;
}

void RestoreInlineClockTextOnly(const ClockEntryPtr& entry) {
    auto dateTextBlock = entry->dateTextBlock.get();
    auto timeTextBlock = entry->timeTextBlock.get();

    if (dateTextBlock &&
        (!entry->baseDateText.empty() || !entry->lastAppliedSuffix.empty())) {
        dateTextBlock.Inlines().Clear();
        dateTextBlock.Text(winrt::hstring(entry->baseDateText));
        if (entry->originalDateMinWidthCaptured) {
            dateTextBlock.MinWidth(entry->originalDateMinWidth);
        }
        if (entry->originalDateTextAlignmentCaptured) {
            dateTextBlock.TextAlignment(entry->originalDateTextAlignment);
        }
    }

    if (timeTextBlock &&
        (!entry->baseTimeText.empty() || !entry->lastAppliedSuffix.empty())) {
        timeTextBlock.Inlines().Clear();
        timeTextBlock.Text(winrt::hstring(entry->baseTimeText));
        if (entry->originalTimeMinWidthCaptured) {
            timeTextBlock.MinWidth(entry->originalTimeMinWidth);
        }
        if (entry->originalTimeTextAlignmentCaptured) {
            timeTextBlock.TextAlignment(entry->originalTimeTextAlignment);
        }
    }

    entry->lastAppliedSuffix.clear();
}

void RestoreSeparateIndicatorOnly(const ClockEntryPtr& entry) {
    auto containerGrid = entry->containerGrid.get();
    auto indicatorTextBlock = entry->indicatorTextBlock.get();

    if (containerGrid && indicatorTextBlock) {
        auto children = containerGrid.Children();
        for (uint32_t i = 0; i < children.Size(); ++i) {
            if (children.GetAt(i) == indicatorTextBlock) {
                children.RemoveAt(i);
                break;
            }
        }
    }

    if (containerGrid) {
        auto children = containerGrid.Children();
        for (uint32_t i = 0; i < children.Size();) {
            auto childTextBlock = children.GetAt(i).try_as<Controls::TextBlock>();
            if (childTextBlock &&
                childTextBlock.Name() == L"DesktopIndicatorTextBlock") {
                children.RemoveAt(i);
                continue;
            }

            ++i;
        }
    }

    auto stackPanel = entry->stackPanel.get();
    if (stackPanel && entry->originalStackPanelColumnCaptured) {
        Controls::Grid::SetColumn(stackPanel, entry->originalStackPanelColumn);
    }

    if (containerGrid && entry->originalContainerGridColumnsCaptured) {
        auto columnDefinitions = containerGrid.ColumnDefinitions();
        columnDefinitions.Clear();
        for (const auto& width : entry->originalContainerGridColumnWidths) {
            Controls::ColumnDefinition columnDefinition;
            columnDefinition.Width(width);
            columnDefinitions.Append(columnDefinition);
        }
    }

    entry->indicatorTextBlock = nullptr;
    entry->usingSeparateIndicator = false;
}

Controls::TextBlock EnsureSeparateIndicatorTextBlock(
    const ClockEntryPtr& entry,
    Controls::TextBlock sourceTextBlock) {
    auto containerGrid = entry->containerGrid.get();
    if (!containerGrid || !sourceTextBlock) {
        return nullptr;
    }

    auto stackPanel = entry->stackPanel.get();
    if (!stackPanel) {
        stackPanel = TryGetClockStackPanel(containerGrid);
        entry->stackPanel = stackPanel;
    }

    if (!stackPanel) {
        return nullptr;
    }

    if (!entry->originalContainerGridColumnsCaptured) {
        auto columnDefinitions = containerGrid.ColumnDefinitions();
        entry->originalContainerGridColumnWidths.clear();
        for (const auto& columnDefinition : columnDefinitions) {
            entry->originalContainerGridColumnWidths.push_back(
                columnDefinition.Width());
        }
        entry->originalContainerGridColumnsCaptured = true;
    }

    if (!entry->originalStackPanelColumnCaptured) {
        entry->originalStackPanelColumn = Controls::Grid::GetColumn(stackPanel);
        entry->originalStackPanelColumnCaptured = true;
    }

    auto columnDefinitions = containerGrid.ColumnDefinitions();
    if (columnDefinitions.Size() < 2) {
        columnDefinitions.Clear();

        Controls::ColumnDefinition mainColumn;
        mainColumn.Width(GridLengthHelper::Auto());
        columnDefinitions.Append(mainColumn);

        Controls::ColumnDefinition indicatorColumn;
        indicatorColumn.Width(GridLengthHelper::Auto());
        columnDefinitions.Append(indicatorColumn);
    }

    Controls::Grid::SetColumn(stackPanel, 0);

    auto indicatorTextBlock = entry->indicatorTextBlock.get();
    if (!indicatorTextBlock) {
        for (const auto& child : containerGrid.Children()) {
            auto childTextBlock = child.try_as<Controls::TextBlock>();
            if (childTextBlock &&
                childTextBlock.Name() == L"DesktopIndicatorTextBlock") {
                indicatorTextBlock = childTextBlock;
                break;
            }
        }
    }

    if (!indicatorTextBlock) {
        indicatorTextBlock = Controls::TextBlock();
        indicatorTextBlock.Name(L"DesktopIndicatorTextBlock");
        containerGrid.Children().Append(indicatorTextBlock);
    }

    indicatorTextBlock.FontFamily(sourceTextBlock.FontFamily());
    indicatorTextBlock.FontSize(sourceTextBlock.FontSize());
    indicatorTextBlock.FontStretch(sourceTextBlock.FontStretch());
    indicatorTextBlock.FontStyle(sourceTextBlock.FontStyle());
    indicatorTextBlock.FontWeight(sourceTextBlock.FontWeight());
    indicatorTextBlock.CharacterSpacing(sourceTextBlock.CharacterSpacing());
    indicatorTextBlock.Foreground(sourceTextBlock.Foreground());
    indicatorTextBlock.TextWrapping(TextWrapping::NoWrap);
    indicatorTextBlock.TextAlignment(TextAlignment::Start);
    indicatorTextBlock.VerticalAlignment(VerticalAlignment::Center);
    indicatorTextBlock.HorizontalAlignment(HorizontalAlignment::Left);

    Controls::Grid::SetColumn(indicatorTextBlock, 1);
    entry->indicatorTextBlock = indicatorTextBlock;
    entry->usingSeparateIndicator = true;
    return indicatorTextBlock;
}

void ApplySeparateIndicator(const ClockEntryPtr& entry,
                            Controls::TextBlock sourceTextBlock,
                            int currentDesktopNumber,
                            int desktopCount,
                            const std::vector<std::wstring>& desktopNames) {
    auto indicatorTextBlock =
        EnsureSeparateIndicatorTextBlock(entry, sourceTextBlock);
    if (!indicatorTextBlock) {
        return;
    }

    IndicatorLayout layout =
        BuildIndicatorLayout(sourceTextBlock, true, currentDesktopNumber,
                             desktopCount, desktopNames);
    indicatorTextBlock.MinWidth(layout.widestSuffixWidth);
    SetIndicatorTextBlockContent(indicatorTextBlock, L"", layout);
}

void EnsureReservedWidth(const ClockEntryPtr& entry,
                         Controls::TextBlock targetTextBlock,
                         const std::wstring& baseText,
                         const std::vector<std::wstring>& desktopNames) {
    if (!targetTextBlock) {
        return;
    }

    int desktopCount = ReadDesktopCountFromRegistry();
    double widestWidth = 0;

    if (g_settings.indicatorMode == IndicatorMode::Markers) {
        widestWidth = MeasureIndicatorTextWidth(
            targetTextBlock, baseText,
            BuildIndicatorSuffix(!baseText.empty(), BuildMarkerSequenceText(desktopCount)));
    } else {
        auto getCandidateText = [&](int desktopNumber) {
            if (g_settings.indicatorMode == IndicatorMode::DesktopName) {
                return FormatDesktopNameOrNumber(desktopNumber, desktopNames);
            }

            return FormatDesktopNumber(desktopNumber);
        };

        widestWidth = MeasureIndicatorTextWidth(
            targetTextBlock, baseText,
            BuildIndicatorSuffix(!baseText.empty(), getCandidateText(1)));

        for (int i = 2; i <= desktopCount; ++i) {
            double candidateWidth = MeasureIndicatorTextWidth(
                targetTextBlock, baseText,
                BuildIndicatorSuffix(!baseText.empty(), getCandidateText(i)));
            if (candidateWidth > widestWidth) {
                widestWidth = candidateWidth;
            }
        }
    }

    if (targetTextBlock == entry->dateTextBlock.get()) {
        if (!entry->originalDateMinWidthCaptured) {
            entry->originalDateMinWidth = targetTextBlock.MinWidth();
            entry->originalDateMinWidthCaptured = true;
        }

        targetTextBlock.MinWidth(std::max(entry->originalDateMinWidth, widestWidth));
    } else if (targetTextBlock == entry->timeTextBlock.get()) {
        if (!entry->originalTimeMinWidthCaptured) {
            entry->originalTimeMinWidth = targetTextBlock.MinWidth();
            entry->originalTimeMinWidthCaptured = true;
        }

        targetTextBlock.MinWidth(std::max(entry->originalTimeMinWidth, widestWidth));
    }
}

void EnsureStableTextAlignment(const ClockEntryPtr& entry,
                               Controls::TextBlock targetTextBlock) {
    if (!targetTextBlock) {
        return;
    }

    if (targetTextBlock == entry->dateTextBlock.get()) {
        if (!entry->originalDateTextAlignmentCaptured) {
            entry->originalDateTextAlignment = targetTextBlock.TextAlignment();
            entry->originalDateTextAlignmentCaptured = true;
        }

        targetTextBlock.TextAlignment(TextAlignment::Start);
    } else if (targetTextBlock == entry->timeTextBlock.get()) {
        if (!entry->originalTimeTextAlignmentCaptured) {
            entry->originalTimeTextAlignment = targetTextBlock.TextAlignment();
            entry->originalTimeTextAlignmentCaptured = true;
        }

        targetTextBlock.TextAlignment(TextAlignment::Start);
    }
}

void ApplyIndicator(const ClockEntryPtr& entry) {
    if (g_settings.position != IndicatorPosition::Clock) {RestoreClockText(entry);return;}
    if (!entry || g_unloading) {
        return;
    }

    auto dateTextBlock = entry->dateTextBlock.get();
    auto timeTextBlock = entry->timeTextBlock.get();
    if (!dateTextBlock && !timeTextBlock) {
        return;
    }

    int currentDesktopNumber = g_currentDesktopNumber.load();
    int desktopCount = ReadDesktopCountFromRegistry();
    std::vector<std::wstring> desktopNames =
        g_settings.indicatorMode == IndicatorMode::DesktopName
            ? ReadVirtualDesktopNames()
            : std::vector<std::wstring>{};

    std::lock_guard<std::mutex> lock(entry->mutex);

    if (g_settings.hideWhenSingleDesktop && desktopCount <= 1) {
        if (!entry->lastAppliedSuffix.empty()) {
            RestoreInlineClockTextOnly(entry);
        }
        if (entry->usingSeparateIndicator) {
            RestoreSeparateIndicatorOnly(entry);
        }
        return;
    }

    if (ShouldUseSeparateIndicator(entry)) {
        if (!entry->lastAppliedSuffix.empty()) {
            RestoreInlineClockTextOnly(entry);
        }

        auto sourceTextBlock = dateTextBlock ? dateTextBlock : timeTextBlock;
        ApplySeparateIndicator(entry, sourceTextBlock, currentDesktopNumber,
                               desktopCount, desktopNames);
        return;
    }

    if (entry->usingSeparateIndicator) {
        RestoreSeparateIndicatorOnly(entry);
    }

    bool useDateLine = dateTextBlock && !entry->baseDateText.empty();
    if (!useDateLine && dateTextBlock && !timeTextBlock) {
        useDateLine = true;
    }

    if (useDateLine) {
        IndicatorLayout layout =
            BuildIndicatorLayout(dateTextBlock, !entry->baseDateText.empty(),
                                 currentDesktopNumber, desktopCount,
                                 desktopNames);
        EnsureReservedWidth(entry, dateTextBlock, entry->baseDateText,
                            desktopNames);
        EnsureStableTextAlignment(entry, dateTextBlock);
        SetIndicatorTextBlockContent(dateTextBlock, entry->baseDateText, layout);
        entry->lastAppliedSuffix = layout.renderedSuffix;
    } else if (timeTextBlock) {
        IndicatorLayout layout =
            BuildIndicatorLayout(timeTextBlock, !entry->baseTimeText.empty(),
                                 currentDesktopNumber, desktopCount,
                                 desktopNames);
        EnsureReservedWidth(entry, timeTextBlock, entry->baseTimeText,
                            desktopNames);
        EnsureStableTextAlignment(entry, timeTextBlock);
        SetIndicatorTextBlockContent(timeTextBlock, entry->baseTimeText, layout);
        entry->lastAppliedSuffix = layout.renderedSuffix;
    }
}

void CaptureClockBaseText(const ClockEntryPtr& entry) {
    if (!entry) {
        return;
    }

    auto dateTextBlock = entry->dateTextBlock.get();
    auto timeTextBlock = entry->timeTextBlock.get();
    if (!dateTextBlock && !timeTextBlock) {
        return;
    }

    std::lock_guard<std::mutex> lock(entry->mutex);

    if (dateTextBlock) {
        entry->baseDateText =
            TrimAppliedSuffix(dateTextBlock.Text().c_str(),
                              entry->lastAppliedSuffix);
    }

    if (timeTextBlock) {
        entry->baseTimeText =
            TrimAppliedSuffix(timeTextBlock.Text().c_str(),
                              entry->lastAppliedSuffix);
    }
}

void RestoreClockText(const ClockEntryPtr& entry) {
    if (!entry) {
        return;
    }

    auto dateTextBlock = entry->dateTextBlock.get();
    auto timeTextBlock = entry->timeTextBlock.get();
    if (!dateTextBlock && !timeTextBlock) {
        return;
    }

    std::lock_guard<std::mutex> lock(entry->mutex);
    RestoreInlineClockTextOnly(entry);
    RestoreSeparateIndicatorOnly(entry);
}

void DispatchToEntry(const ClockEntryPtr& entry, bool captureBaseText) {
    auto dateTextBlock = entry->dateTextBlock.get();
    auto timeTextBlock = entry->timeTextBlock.get();
    auto dispatchSource = dateTextBlock ? dateTextBlock : timeTextBlock;
    if (!dispatchSource) {
        return;
    }

    auto dispatcher = dispatchSource.Dispatcher();
    if (!dispatcher) {
        return;
    }

    dispatcher.RunAsync(
        winrt::Windows::UI::Core::CoreDispatcherPriority::Low,
        [entry, captureBaseText] {
            if (g_unloading) {
                return;
            }

            if (captureBaseText) {
                CaptureClockBaseText(entry);
            }

            ApplyIndicator(entry);
        });
}

void DispatchRestoreToEntry(const ClockEntryPtr& entry) {
    auto dateTextBlock = entry->dateTextBlock.get();
    auto timeTextBlock = entry->timeTextBlock.get();
    auto dispatchSource = dateTextBlock ? dateTextBlock : timeTextBlock;
    if (!dispatchSource) {
        return;
    }

    auto dispatcher = dispatchSource.Dispatcher();
    if (!dispatcher) {
        return;
    }

    dispatcher.RunAsync(
        winrt::Windows::UI::Core::CoreDispatcherPriority::Normal,
        [entry] { RestoreClockText(entry); });
}

void UpdateAllClockEntriesCurrentThread(bool captureBaseText) {
    for (const auto& entry : GetClockEntriesSnapshot()) {
        if (captureBaseText) {
            CaptureClockBaseText(entry);
        }

        ApplyIndicator(entry);
    }
}

void UpdateAllClockEntries(bool captureBaseText) {
    for (const auto& entry : GetClockEntriesSnapshot()) {
        DispatchToEntry(entry, captureBaseText);
    }
}

void RestoreAllClockEntries() {
    for (const auto& entry : GetClockEntriesSnapshot()) {
        DispatchRestoreToEntry(entry);
    }
}

void ProcessDateTimeIconContentElement(FrameworkElement root) {
    Controls::TextBlock dateTextBlock = nullptr;
    Controls::TextBlock timeTextBlock = nullptr;
    if (!TryGetClockTextBlocks(root, &dateTextBlock, &timeTextBlock)) {
        return;
    }

    auto entry = AddOrGetClockEntry(dateTextBlock, timeTextBlock);
    entry->containerGrid = TryGetClockContainerGrid(root);
    if (auto containerGrid = entry->containerGrid.get()) {
        entry->stackPanel = TryGetClockStackPanel(containerGrid);
    }
    CaptureClockBaseText(entry);
    ApplyIndicator(entry);
}

void ClockSystemTrayIconDataModel_RefreshIcon_Hook_Impl(
    LPVOID pThis,
    LPVOID param1,
    ClockSystemTrayIconDataModel_RefreshIcon_t original) {
    original(pThis, param1);
    UpdateAllClockEntriesCurrentThread(true);
}

void WINAPI ClockSystemTrayIconDataModel_RefreshIcon_Hook(LPVOID pThis,
                                                          LPVOID param1) {
    ClockSystemTrayIconDataModel_RefreshIcon_Hook_Impl(
        pThis, param1, ClockSystemTrayIconDataModel_RefreshIcon_Original);
}

void WINAPI ClockSystemTrayIconDataModel2_RefreshIcon_Hook(LPVOID pThis,
                                                           LPVOID param1) {
    ClockSystemTrayIconDataModel_RefreshIcon_Hook_Impl(
        pThis, param1, ClockSystemTrayIconDataModel2_RefreshIcon_Original);
}

void WINAPI DateTimeIconContent_OnApplyTemplate_Hook(LPVOID pThis) {
    DateTimeIconContent_OnApplyTemplate_Original(pThis);

    IUnknown* elementUnknown = *((IUnknown**)pThis + 1);
    if (!elementUnknown) {
        return;
    }

    FrameworkElement root = nullptr;
    elementUnknown->QueryInterface(winrt::guid_of<FrameworkElement>(),
                                   winrt::put_abi(root));
    if (!root) {
        return;
    }

    try {
        ProcessDateTimeIconContentElement(root);
    } catch (...) {
        Wh_Log(L"Failed to process DateTimeIconContent template");
    }
}

HRESULT WINAPI BadgeIconContent_get_ViewModel_Hook(LPVOID pThis, LPVOID pArgs) {
    HRESULT hr = BadgeIconContent_get_ViewModel_Original(pThis, pArgs);

    try {
        winrt::Windows::Foundation::IInspectable inspectable = nullptr;
        winrt::check_hresult(
            ((IUnknown*)pThis)
                ->QueryInterface(
                    winrt::guid_of<winrt::Windows::Foundation::IInspectable>(),
                    winrt::put_abi(inspectable)));

        if (winrt::get_class_name(inspectable) == L"SystemTray.DateTimeIconContent") {
            auto root = inspectable.try_as<FrameworkElement>();
            if (root && root.IsLoaded()) {
                ProcessDateTimeIconContentElement(root);
            }
        }
    } catch (...) {
    }

    return hr;
}

HMODULE GetSystemTrayModuleHandle() {
    HMODULE module = GetModuleHandleW(L"SystemTray.dll");

    if (!module) {
        module = GetModuleHandleW(L"Taskbar.View.dll");
        // First known Taskbar.View.dll version without SystemTray symbols:
        // 2604.8002.200.6000.
        if (module) {
            VS_FIXEDFILEINFO* fixedFileInfo = GetModuleVersionInfo(module, nullptr);
            WORD moduleMajor =
                fixedFileInfo ? HIWORD(fixedFileInfo->dwFileVersionMS) : 0;

            if (!moduleMajor || moduleMajor >= 2604) {
                Wh_Log(L"Skipping Taskbar.View.dll version %d", moduleMajor);
                module = nullptr;
            }
        }
    }
    if (!module) {
        module = GetModuleHandleW(L"ExplorerExtensions.dll");
    }

    return module;
}

bool HookSystemTraySymbols(HMODULE module) {
    // SystemTray.dll, Taskbar.View.dll, ExplorerExtensions.dll
    WindhawkUtils::SYMBOL_HOOK systemTrayHooks[] = {
        {
            {LR"(private: void __cdecl winrt::SystemTray::implementation::ClockSystemTrayIconDataModel::RefreshIcon(class SystemTrayTelemetry::ClockUpdate &))"},
            &ClockSystemTrayIconDataModel_RefreshIcon_Original,
            ClockSystemTrayIconDataModel_RefreshIcon_Hook,
        },
        {
            {LR"(private: void __cdecl winrt::SystemTray::implementation::ClockSystemTrayIconDataModel2::RefreshIcon(class SystemTrayTelemetry::ClockUpdate &))"},
            &ClockSystemTrayIconDataModel2_RefreshIcon_Original,
            ClockSystemTrayIconDataModel2_RefreshIcon_Hook,
            true,
        },
        {
            {LR"(public: void __cdecl winrt::SystemTray::implementation::DateTimeIconContent::OnApplyTemplate(void))"},
            &DateTimeIconContent_OnApplyTemplate_Original,
            DateTimeIconContent_OnApplyTemplate_Hook,
            true,
        },
        {
            {LR"(public: virtual int __cdecl winrt::impl::produce<struct winrt::SystemTray::implementation::BadgeIconContent,struct winrt::SystemTray::IBadgeIconContent>::get_ViewModel(void * *))"},
            &BadgeIconContent_get_ViewModel_Original,
            BadgeIconContent_get_ViewModel_Hook,
            true,
        },
    };

    if (!HookSymbols(module, systemTrayHooks, ARRAYSIZE(systemTrayHooks))) {
        Wh_Log(L"HookSymbols failed");
        return false;
    }

    return true;
}

bool TryHookSystemTrayModule(HMODULE module) {
    if (!module || g_systemTrayModuleHooked.exchange(true)) {
        return false;
    }

    if (!HookSystemTraySymbols(module)) {
        g_systemTrayModuleHooked = false;
        return false;
    }

    return true;
}

bool HookExplorerExeSymbols() {
    WindhawkUtils::SYMBOL_HOOK explorerExeHooks[] = {
        {
            {LR"(protected: virtual void __cdecl ClockButton::v_OnDisplayStateChange(bool))"},
            &ClockButton_v_OnDisplayStateChange_Original,
            nullptr,
            true,
        },
    };

    if (!HookSymbols(GetModuleHandle(nullptr), explorerExeHooks,
                     ARRAYSIZE(explorerExeHooks))) {
        Wh_Log(L"HookSymbols for explorer.exe failed");
        return false;
    }

    return true;
}

HWND FindCurrentProcessTaskbarWnd() {
    HWND taskbarWnd = nullptr;

    EnumWindows(
        [](HWND hWnd, LPARAM lParam) -> BOOL {
            DWORD processId = 0;
            WCHAR className[32];
            if (GetWindowThreadProcessId(hWnd, &processId) &&
                processId == GetCurrentProcessId() &&
                GetClassNameW(hWnd, className, ARRAYSIZE(className)) &&
                _wcsicmp(className, L"Shell_TrayWnd") == 0) {
                *reinterpret_cast<HWND*>(lParam) = hWnd;
                return FALSE;
            }

            return TRUE;
        },
        reinterpret_cast<LPARAM>(&taskbarWnd));

    return taskbarWnd;
}

void RefreshClockButtonWindow(HWND hWnd) {
    if (!hWnd || !ClockButton_v_OnDisplayStateChange_Original) {
        return;
    }

    HWND clockButtonWnd = FindWindowExW(hWnd, nullptr, L"ClockButton", nullptr);
    if (!clockButtonWnd) {
        return;
    }

    LONG_PTR clockButtonLongPtr = GetWindowLongPtrW(clockButtonWnd, 0);
    if (clockButtonLongPtr) {
        ClockButton_v_OnDisplayStateChange_Original((LPVOID)clockButtonLongPtr,
                                                    true);
    }
}

void TriggerWin11ClockUpdateWatcher() {
    constexpr WCHAR kTempValueName[] =
        L"_temp_windhawk_taskbar-desktop-indicator";

    HKEY hSubKey;
    LONG result = RegOpenKeyExW(HKEY_CURRENT_USER,
                                L"Control Panel\\TimeDate\\AdditionalClocks", 0,
                                KEY_WRITE, &hSubKey);
    if (result != ERROR_SUCCESS) {
        Wh_Log(L"Failed to open clock update watcher key: %ld", result);
        return;
    }

    if (RegSetValueExW(hSubKey, kTempValueName, 0, REG_SZ, (const BYTE*)L"",
                       sizeof(WCHAR)) != ERROR_SUCCESS) {
        Wh_Log(L"Failed to create temp clock update watcher value");
    } else if (RegDeleteValueW(hSubKey, kTempValueName) != ERROR_SUCCESS) {
        Wh_Log(L"Failed to remove temp clock update watcher value");
    }

    RegCloseKey(hSubKey);
}

void RefreshLiveTaskbarClock() {
    if (g_winVersion < WinVersion::Win11) {
        return;
    }

    HWND taskbarWnd = FindCurrentProcessTaskbarWnd();
    if (!taskbarWnd) {
        return;
    }

    TriggerWin11ClockUpdateWatcher();

    if (!ClockButton_v_OnDisplayStateChange_Original) {
        return;
    }

    RefreshClockButtonWindow(taskbarWnd);

    DWORD taskbarThreadId = GetWindowThreadProcessId(taskbarWnd, nullptr);
    if (!taskbarThreadId) {
        return;
    }

    auto enumWindowsProc = [](HWND hWnd) {
        WCHAR className[32];
        if (!GetClassNameW(hWnd, className, ARRAYSIZE(className)) ||
            _wcsicmp(className, L"Shell_SecondaryTrayWnd") != 0) {
            return;
        }

        RefreshClockButtonWindow(hWnd);
    };

    EnumThreadWindows(
        taskbarThreadId,
        [](HWND hWnd, LPARAM lParam) -> BOOL {
            auto& proc = *reinterpret_cast<decltype(enumWindowsProc)*>(lParam);
            proc(hWnd);
            return TRUE;
        },
        reinterpret_cast<LPARAM>(&enumWindowsProc));
}

void HandleLoadedModuleIfSystemTray(HMODULE module, LPCWSTR moduleName) {
    if (g_winVersion < WinVersion::Win11 || g_systemTrayModuleHooked) {
        return;
    }

    if (GetSystemTrayModuleHandle() != module) {
        return;
    }

    Wh_Log(L"Loaded %s", moduleName);

    if (TryHookSystemTrayModule(module)) {
        Wh_ApplyHookOperations();
    }
}

using LoadLibraryExW_t = decltype(&LoadLibraryExW);
LoadLibraryExW_t LoadLibraryExW_Original;

HMODULE WINAPI LoadLibraryExW_Hook(LPCWSTR libFileName,
                                   HANDLE file,
                                   DWORD flags) {
    HMODULE module = LoadLibraryExW_Original(libFileName, file, flags);
    if (module) {
        HandleLoadedModuleIfSystemTray(module, libFileName);
    }

    return module;
}

DWORD WINAPI DesktopPollThreadProc(LPVOID) {
    int lastDesktopNumber = ReadCurrentDesktopNumberFromRegistry();
    g_currentDesktopNumber.store(lastDesktopNumber);

    while (WaitForSingleObject(g_stopEvent, g_pollIntervalMs.load()) == WAIT_TIMEOUT) {
        int desktopNumber = ReadCurrentDesktopNumberFromRegistry();
        if (desktopNumber != lastDesktopNumber) {
            lastDesktopNumber = desktopNumber;
            g_currentDesktopNumber.store(desktopNumber);
            UpdateAllClockEntries(false);
        }
    }

    return 0;
}

bool StartDesktopPollThread() {
    g_stopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!g_stopEvent) {
        Wh_Log(L"Failed to create desktop poll stop event");
        return false;
    }

    g_pollThread = CreateThread(nullptr, 0, DesktopPollThreadProc, nullptr, 0, nullptr);
    if (!g_pollThread) {
        CloseHandle(g_stopEvent);
        g_stopEvent = nullptr;
        return false;
    }
    return true;
}

void StopDesktopPollThread() {
    if (g_stopEvent) {
        SetEvent(g_stopEvent);
    }

    if (g_pollThread) {
        WaitForSingleObject(g_pollThread, 3000);
        CloseHandle(g_pollThread);
        g_pollThread = nullptr;
    }

    if (g_stopEvent) {
        CloseHandle(g_stopEvent);
        g_stopEvent = nullptr;
    }
}

void EnsureDesktopChangeTracking() {
    bool notificationsRegistered = EnsureVirtualDesktopNotificationThread();

    if (g_settings.pollIntervalMs <= 0) {
        if (g_pollThread || g_stopEvent) {
            StopDesktopPollThread();
        }
    } else if (!g_pollThread && !g_stopEvent) {
        if (!StartDesktopPollThread()) {
            Wh_Log(L"Failed to start desktop poll thread");
        }
    }

    if (!notificationsRegistered && g_settings.pollIntervalMs <= 0) {
        Wh_Log(L"Desktop change tracking has no active update mechanism");
    }
}


// ---- Native taskbar position engine, adapted from Mawaqit v0.6.9 ----
namespace folder_menus_slot_lease {

using winrt::Windows::UI::Xaml::FrameworkElement;
using winrt::Windows::UI::Xaml::GridUnitType;
using winrt::Windows::UI::Xaml::Controls::ColumnDefinition;
using winrt::Windows::UI::Xaml::Controls::Grid;
using winrt::Windows::UI::Xaml::Controls::Panel;
using winrt::Windows::UI::Xaml::Controls::StackPanel;

enum class Anchor {
    BeforeIcons,
    AfterShowDesktop,
};

// Which layout contract the live tray panel follows.
enum class Kind {
    Unsupported,  // some other Panel: do not guess its layout semantics.
    Columns,      // Grid. A slot is a column index.
    Order,        // StackPanel. A slot is a child index.
};

struct Lease {
    std::wstring markerName;
    int slot = -1;
    Kind kind = Kind::Unsupported;
    bool createdBaseColumn = false;
};

inline Kind Classify(FrameworkElement const& parent) {
    if (!parent)
        return Kind::Unsupported;
    if (parent.try_as<Grid>())
        return Kind::Columns;
    if (parent.try_as<StackPanel>())
        return Kind::Order;
    return Kind::Unsupported;
}

// Class name of an unexpected panel, so a mod can log what it actually got
// instead of reporting a bare "not found" for an element that is right there.
inline std::wstring ClassName(FrameworkElement const& element) {
    if (!element)
        return L"(null)";
    try {
        return std::wstring(winrt::get_class_name(element));
    } catch (...) {
        return L"(unknown)";
    }
}

// Named direct children, for logging when an anchor cannot be resolved. A tray
// restructure shows up here as missing or renamed names, which is the one thing
// a user's debug log otherwise cannot tell us.
inline std::wstring DescribeChildren(Panel const& parent) {
    if (!parent)
        return L"(none)";
    std::wstring names;
    try {
        for (auto const& child : parent.Children()) {
            auto element = child.try_as<FrameworkElement>();
            if (!element || element.Name().empty())
                continue;
            if (!names.empty())
                names += L", ";
            names += element.Name();
        }
    } catch (...) {
        return L"(unreadable)";
    }
    return names.empty() ? L"(no named children)" : names;
}

inline FrameworkElement FindDirectChild(Panel const& parent,
                                        wchar_t const* name) {
    if (!parent || !name)
        return nullptr;
    for (auto const& child : parent.Children()) {
        auto element = child.try_as<FrameworkElement>();
        if (element && element.Name() == name)
            return element;
    }
    return nullptr;
}

inline int IndexOfChild(Panel const& parent, FrameworkElement const& child) {
    if (!parent || !child)
        return -1;
    for (uint32_t i = 0; i < parent.Children().Size(); ++i) {
        if (parent.Children().GetAt(i).try_as<FrameworkElement>() == child)
            return static_cast<int>(i);
    }
    return -1;
}

inline bool ResolveSlot(Panel const& parent, Anchor anchor, int& slot) {
    Kind kind = Classify(parent);
    if (kind == Kind::Unsupported)
        return false;

    if (anchor == Anchor::BeforeIcons) {
        slot = 0;
        return true;
    }

    wchar_t const* referenceName = nullptr;
    bool after = false;
    switch (anchor) {
        case Anchor::AfterShowDesktop:
            referenceName = L"ShowDesktopStack";
            after = true;
            break;
        case Anchor::BeforeIcons:
            break;
    }

    auto reference = FindDirectChild(parent, referenceName);
    if (!reference)
        return false; // Never silently turn an unavailable anchor into slot 0.

    if (kind == Kind::Columns) {
        slot = Grid::GetColumn(reference) +
               (after ? std::max(1, Grid::GetColumnSpan(reference)) : 0);
        return true;
    }

    // Order: the reference's own child index is the slot. There is no span to
    // step over -- a StackPanel child occupies exactly one position.
    int index = IndexOfChild(parent, reference);
    if (index < 0)
        return false;
    slot = index + (after ? 1 : 0);
    return true;
}

inline bool Release(Panel const& parent, Lease& lease);

inline bool AcquireAt(Panel const& parent, int slot,
                      std::wstring const& markerName, Lease& lease) {
    Kind kind = Classify(parent);
    if (kind == Kind::Unsupported || slot < 0 || markerName.empty())
        return false;

    // A marker with this name already in the tray is either this caller's own
    // live lease — refuse, acquiring twice would strand the first slot — or a
    // leftover from an instance whose teardown never reached the UI thread.
    // Refusing the leftover would block every later apply until Explorer
    // restarts, so release it and take the slot fresh, correcting the
    // requested slot if the released one sat before it.
    if (auto stale = FindDirectChild(parent, markerName.c_str())) {
        if (lease.markerName == markerName)
            return false;
        int staleSlot = kind == Kind::Columns
                            ? Grid::GetColumn(stale)
                            : IndexOfChild(parent, stale);
        Lease leftover{markerName, staleSlot, kind};
        if (!Release(parent, leftover))
            return false;
        if (staleSlot >= 0 && staleSlot < slot)
            --slot;
    }

    Grid marker;
    marker.Name(markerName);
    marker.Width(0.0);
    marker.Height(0.0);
    marker.IsHitTestVisible(false);

    if (kind == Kind::Columns) {
        auto grid = parent.try_as<Grid>();
        if (!grid)
            return false;
        // A Grid without ColumnDefinitions uses one implicit full-width column.
        // Materialize that implicit column before inserting a lease column;
        // otherwise the repeater is shifted to column 1 in a ONE-column grid.
        bool createdBaseColumn = grid.ColumnDefinitions().Size() == 0;
        if (createdBaseColumn) {
            ColumnDefinition base;
            base.Width({1.0, GridUnitType::Star});
            grid.ColumnDefinitions().Append(base);
        }
        ColumnDefinition definition;
        definition.Width({1.0, GridUnitType::Auto});
        slot = std::min(slot, static_cast<int>(grid.ColumnDefinitions().Size()));
        if (static_cast<uint32_t>(slot) < grid.ColumnDefinitions().Size())
            grid.ColumnDefinitions().InsertAt(slot, definition);
        else
            grid.ColumnDefinitions().Append(definition);

        for (auto const& child : grid.Children()) {
            auto element = child.try_as<FrameworkElement>();
            if (!element) continue;
            int start = Grid::GetColumn(element);
            int span = Grid::GetColumnSpan(element);
            if (start >= slot)
                Grid::SetColumn(element, start + 1);
            else if (start + span > slot)
                Grid::SetColumnSpan(element, span + 1);
        }

        Grid::SetColumn(marker, slot);
        grid.Children().Append(marker);
        lease.createdBaseColumn = createdBaseColumn;
    } else {
        // Order: no column is created or owned. The marker simply holds the
        // position, and PlaceChild drops the content next to it.
        uint32_t index = std::min(static_cast<uint32_t>(slot),
                                  parent.Children().Size());
        parent.Children().InsertAt(index, marker);
        slot = static_cast<int>(index);
    }

    lease = {markerName, slot, kind, lease.createdBaseColumn};
    return true;
}

// Live index of the lease marker. Other mods inject and remove siblings around
// us, so the acquire-time index is a hint, never the truth at removal time.
inline bool FindMarker(Panel const& parent, Lease const& lease,
                       uint32_t& index) {
    if (!parent || lease.markerName.empty())
        return false;
    for (uint32_t i = 0; i < parent.Children().Size(); ++i) {
        auto element = parent.Children().GetAt(i).try_as<FrameworkElement>();
        if (element && element.Name() == lease.markerName) {
            index = i;
            return true;
        }
    }
    return false;
}

// Put mod content into the leased slot. On a Grid the content joins the leased
// column; on a StackPanel it is inserted directly after the marker, so the
// marker's position is the content's position.
inline bool PlaceChild(Panel const& parent, Lease const& lease,
                       FrameworkElement const& content) {
    if (!parent || !content || lease.kind == Kind::Unsupported)
        return false;

    uint32_t markerIndex = 0;
    if (!FindMarker(parent, lease, markerIndex))
        return false;

    if (lease.kind == Kind::Columns) {
        auto marker = parent.Children().GetAt(markerIndex)
                          .try_as<FrameworkElement>();
        Grid::SetColumn(content, marker ? Grid::GetColumn(marker) : lease.slot);
        parent.Children().Append(content);
        return true;
    }

    parent.Children().InsertAt(markerIndex + 1, content);
    return true;
}

inline bool Release(Panel const& parent, Lease& lease) {
    if (!parent || lease.markerName.empty())
        return false;

    uint32_t markerIndex = 0;
    if (!FindMarker(parent, lease, markerIndex))
        return false;

    if (lease.kind == Kind::Order) {
        parent.Children().RemoveAt(markerIndex);
        lease = {};
        return true;
    }

    auto grid = parent.try_as<Grid>();
    auto marker =
        parent.Children().GetAt(markerIndex).try_as<FrameworkElement>();
    int liveColumn = marker ? Grid::GetColumn(marker) : lease.slot;
    if (!grid || liveColumn < 0)
        return false;

    grid.Children().RemoveAt(markerIndex);
    if (static_cast<uint32_t>(liveColumn) < grid.ColumnDefinitions().Size())
        grid.ColumnDefinitions().RemoveAt(liveColumn);

    for (auto const& child : grid.Children()) {
        auto element = child.try_as<FrameworkElement>();
        if (!element) continue;
        int start = Grid::GetColumn(element);
        int span = Grid::GetColumnSpan(element);
        if (start > liveColumn)
            Grid::SetColumn(element, start - 1);
        else if (start < liveColumn && start + span > liveColumn)
            Grid::SetColumnSpan(element, std::max(1, span - 1));
    }

    // Restore the original implicit-column layout only for columns we created.
    if (lease.createdBaseColumn && grid.ColumnDefinitions().Size() == 1)
        grid.ColumnDefinitions().Clear();
    lease = {};
    return true;
}

}  // namespace folder_menus_slot_lease
namespace folder_menus_taskbar_window {

// ---- Window discovery -------------------------------------------------------

inline HWND FindCurrentProcessTaskbarWnd() {
    HWND result = nullptr;
    EnumWindows(
        [](HWND window, LPARAM parameter) -> BOOL {
            DWORD processId = 0;
            WCHAR className[32];
            if (GetWindowThreadProcessId(window, &processId) &&
                processId == GetCurrentProcessId() &&
                GetClassName(window, className, ARRAYSIZE(className)) &&
                _wcsicmp(className, L"Shell_TrayWnd") == 0) {
                *reinterpret_cast<HWND*>(parameter) = window;
                return FALSE;
            }
            return TRUE;
        },
        reinterpret_cast<LPARAM>(&result));
    return result;
}

// Shell_TrayWnd can be recreated inside Explorer. A cache is useful only while
// it names a live window; otherwise rediscover before dispatch or teardown.
inline HWND ResolveTaskbarWnd(HWND cached) {
    if (cached && IsWindow(cached))
        return cached;
    return FindCurrentProcessTaskbarWnd();
}

}  // namespace folder_menus_taskbar_window
namespace folder_menus_dispatch {

// ---- UI-thread marshalling --------------------------------------------------
//
// XAML may only be touched from the thread that owns it. This posts work onto
// the taskbar's thread with a CALLWNDPROC hook and a private registered
// message, and reports whether the callback actually ran — a caller that
// assumes it did will corrupt its own state when the dispatch failed.

using ThreadProc = void (*)(void*);
using ExceptionLogFn = void (*)(PCWSTR context);

inline ExceptionLogFn g_logException = nullptr;

// Point this at the mod's logger once in Wh_ModInit so failures inside a UI
// callback are reported in the mod's own voice.
inline void SetExceptionLogger(ExceptionLogFn logger) {
    g_logException = logger;
}

inline bool Invoke(ThreadProc proc, void* parameter) {
    try {
        proc(parameter);
        return true;
    } catch (...) {
        if (g_logException) g_logException(L"UI callback");
    }
    return false;
}

struct Dispatch {
    ThreadProc proc;
    void* parameter;
    bool succeeded = false;
    // Every concurrent caller installs its own hook with this same proc, and
    // each hook instance sees every message equal to g_dispatchMessage. With
    // two dispatches in flight, both hooks are in the chain when either
    // message arrives, so without this each callback would run twice. The
    // hooks run one after another on the UI thread, so a plain flag suffices.
    bool ran = false;
};

// The private message this mod dispatches on. Set before the hook is
// installed, and read by the hook proc to recognise its own message.
//
// A CALLWNDPROC HOOK SEES EVERY MESSAGE SENT TO EVERY WINDOW ON THE TASKBAR'S
// UI THREAD. `lParam` for all of those is arbitrary — an integer, a flag, a
// pointer to something else entirely. So the message MUST be checked first,
// against a value that does not come from lParam, and only then may lParam be
// treated as a Dispatch*. Reading anything out of lParam before that check
// dereferences whatever happened to be in the message and takes Explorer down
// with it.
//
// Atomic because the caller may be the retry thread while the hook
// proc runs on the taskbar's UI thread. RegisterWindowMessageW returns the
// same value for the same string for the lifetime of the session, so this
// settles on one value immediately and never changes again.
inline std::atomic<UINT> g_dispatchMessage{0};

// messageName must embed WH_MOD_ID, so two mods cannot collide on the message.
inline bool RunFromWindowThread(HWND window, ThreadProc proc, void* parameter,
                                PCWSTR messageName) {
    UINT message = RegisterWindowMessageW(messageName);
    if (!message) return false;

    DWORD threadId = GetWindowThreadProcessId(window, nullptr);
    if (!threadId) return false;
    if (threadId == GetCurrentThreadId()) return Invoke(proc, parameter);

    g_dispatchMessage.store(message, std::memory_order_release);

    HHOOK hook = SetWindowsHookExW(
        WH_CALLWNDPROC,
        [](int code, WPARAM wParam, LPARAM lParam) -> LRESULT {
            if (code == HC_ACTION) {
                auto const* call = reinterpret_cast<CWPSTRUCT const*>(lParam);
                // Message first. Only our own private message carries a
                // Dispatch* in lParam; everything else carries something we
                // must not touch.
                UINT expected =
                    g_dispatchMessage.load(std::memory_order_acquire);
                if (expected && call->message == expected) {
                    if (auto* dispatch =
                            reinterpret_cast<Dispatch*>(call->lParam);
                        dispatch && !dispatch->ran) {
                        dispatch->ran = true;
                        dispatch->succeeded =
                            Invoke(dispatch->proc, dispatch->parameter);
                    }
                }
            }
            return CallNextHookEx(nullptr, code, wParam, lParam);
        },
        nullptr, threadId);
    if (!hook) return false;

    Dispatch dispatch{proc, parameter};
    SendMessageW(window, message, 0, reinterpret_cast<LPARAM>(&dispatch));
    UnhookWindowsHookEx(hook);
    return dispatch.succeeded;
}

}  // namespace folder_menus_dispatch
namespace folder_menus_taskbar_xaml {

using winrt::Windows::UI::Xaml::FrameworkElement;
using winrt::Windows::UI::Xaml::XamlRoot;

// ---- XamlRoot ---------------------------------------------------------------

using CTaskBand_GetTaskbarHost_t = void*(WINAPI*)(void*, void*);
using TaskbarHost_FrameHeight_t = int(WINAPI*)(void*);
using Ref_count_base_Decref_t = void(WINAPI*)(void*);
using TrayUI_StartTaskbar_t = void(WINAPI*)(void*);

inline CTaskBand_GetTaskbarHost_t CTaskBand_GetTaskbarHost_Original = nullptr;
inline TaskbarHost_FrameHeight_t TaskbarHost_FrameHeight_Original = nullptr;
inline Ref_count_base_Decref_t Ref_count_base_Decref_Original = nullptr;
inline TrayUI_StartTaskbar_t TrayUI_StartTaskbar_Original = nullptr;
inline void* CTaskBand_ITaskListWndSite_vftable = nullptr;

// The mod's rebuild callback, invoked after Explorer rebuilds the taskbar.
inline void (*g_onTaskbarRebuilt)() = nullptr;

inline void WINAPI TrayUI_StartTaskbar_Hook(void* self) {
    TrayUI_StartTaskbar_Original(self);
    try {
        if (g_onTaskbarRebuilt) g_onTaskbarRebuilt();
    } catch (...) {
        if (folder_menus_dispatch::g_logException)
            folder_menus_dispatch::g_logException(L"TrayUI::StartTaskbar hook");
    }
}

inline bool HookTaskbarSymbols(void (*onTaskbarRebuilt)()) {
    g_onTaskbarRebuilt = onTaskbarRebuilt;
    HMODULE taskbar = LoadLibraryExW(L"taskbar.dll", nullptr,
                                     LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!taskbar) return false;
    WindhawkUtils::SYMBOL_HOOK taskbarDllHooks[] = {
        {{LR"(const CTaskBand::`vftable'{for `ITaskListWndSite'})"},
         &CTaskBand_ITaskListWndSite_vftable},
        {{LR"(public: virtual class std::shared_ptr<class TaskbarHost> __cdecl CTaskBand::GetTaskbarHost(void)const )"},
         &CTaskBand_GetTaskbarHost_Original},
        {{LR"(public: int __cdecl TaskbarHost::FrameHeight(void)const )"},
         &TaskbarHost_FrameHeight_Original},
        {{LR"(public: void __cdecl std::_Ref_count_base::_Decref(void))"},
         &Ref_count_base_Decref_Original},
        {{LR"(public: virtual void __cdecl TrayUI::StartTaskbar(void))"},
         &TrayUI_StartTaskbar_Original, TrayUI_StartTaskbar_Hook},
    };
    return WindhawkUtils::HookSymbols(taskbar, taskbarDllHooks,
                                      ARRAYSIZE(taskbarDllHooks));
}

// The FrameworkElement lives at an offset inside TaskbarHost that MOVES
// between Windows builds, so it is read out of TaskbarHost::FrameHeight's
// prologue at runtime rather than hardcoded.
inline size_t FrameworkElementOffset() {
    size_t offset = 0x10;
#if defined(_M_X64)
    BYTE const* code =
        reinterpret_cast<BYTE const*>(TaskbarHost_FrameHeight_Original);
    if (code[0] == 0x48 && code[1] == 0x83 && code[2] == 0xEC &&
        code[4] == 0x48 && code[5] == 0x83 && code[6] == 0xC1 &&
        code[7] <= 0x7F) {
        offset = code[7];
    }
#elif defined(_M_ARM64)
    DWORD const* code =
        reinterpret_cast<DWORD const*>(TaskbarHost_FrameHeight_Original);
    if (code[0] == 0xD503237F && (code[1] & 0xFFC07FFF) == 0xA9807BFD &&
        code[2] == 0x910003FD && (code[3] & 0xFFF00FE0) == 0xF8400C00) {
        offset = (code[3] >> 12) & 0xFF;
    }
#else
#error "Unsupported architecture"
#endif
    return offset;
}

inline XamlRoot GetTaskbarXamlRoot(HWND taskbarWnd) {
    if (!CTaskBand_GetTaskbarHost_Original ||
        !TaskbarHost_FrameHeight_Original || !Ref_count_base_Decref_Original ||
        !CTaskBand_ITaskListWndSite_vftable)
        return nullptr;

    HWND taskSwWnd = (HWND)GetProp(taskbarWnd, L"TaskbandHWND");
    if (!taskSwWnd) return nullptr;
    void* taskBand = (void*)GetWindowLongPtr(taskSwWnd, 0);
    if (!taskBand) return nullptr;

    void* site = taskBand;
    for (int i = 0; *(void**)site != CTaskBand_ITaskListWndSite_vftable; ++i) {
        if (i == 20) return nullptr;
        site = (void**)site + 1;
    }

    void* host[2]{};
    CTaskBand_GetTaskbarHost_Original(site, host);
    if (!host[0] || !host[1]) {
        if (host[1]) Ref_count_base_Decref_Original(host[1]);
        return nullptr;
    }

    auto* unknown =
        *(IUnknown**)((BYTE*)host[0] + FrameworkElementOffset());
    if (!unknown) {
        Ref_count_base_Decref_Original(host[1]);
        return nullptr;
    }
    FrameworkElement element = nullptr;
    unknown->QueryInterface(winrt::guid_of<FrameworkElement>(),
                            winrt::put_abi(element));
    auto result = element ? element.XamlRoot() : nullptr;
    Ref_count_base_Decref_Original(host[1]);
    return result;
}

}  // namespace folder_menus_taskbar_xaml



namespace slot = folder_menus_slot_lease;
namespace taskwin = folder_menus_taskbar_window;
namespace taskxaml = folder_menus_taskbar_xaml;
using namespace winrt::Windows::UI::Xaml::Controls;
using namespace winrt::Windows::UI::Xaml::Media;
static std::atomic<bool> g_nativeStop{false};
static std::atomic<bool> g_nativeRebuild{false};
static HANDLE g_nativeWorker=nullptr;
static HANDLE g_nativeStopEvent=nullptr;
static slot::Lease g_lease{};
static winrt::weak_ref<Panel> g_parent;
static winrt::weak_ref<FrameworkElement> g_placeholder;
static FrameworkElement g_pill{nullptr};
// The task buttons are generated by ItemsRepeater, not a mutable Panel.
// Reserve a layout slot using the first realized task button's margin.
static winrt::weak_ref<FrameworkElement> g_beforeIconsFirstButton;
static winrt::Windows::UI::Xaml::Thickness g_beforeIconsOriginalMargin{};
static bool g_beforeIconsMarginApplied=false;
static void RestoreBeforeIconsReservation() {
    if (!g_beforeIconsMarginApplied) return;
    try {
        if (auto button=g_beforeIconsFirstButton.get())
            button.Margin(g_beforeIconsOriginalMargin);
    } catch (...) { Wh_Log(L"[Emberveil] Could not restore first task button margin"); }
    g_beforeIconsFirstButton={};
    g_beforeIconsMarginApplied=false;
}

static std::wstring g_position=L"before-tray";
static std::wstring NativePosition() {
 switch(g_settings.position) {
 case IndicatorPosition::AfterStartBeforeIcons: return L"before-icons";
 case IndicatorPosition::AfterStartAfterIcons: return L"after-icons";
 case IndicatorPosition::BeforeTray: return L"before-tray";
 case IndicatorPosition::AfterClock: return L"after-tray";
 case IndicatorPosition::DynamicCenter: return L"center";
 default: return L"clock";
 }
}
static void NativeLogException(PCWSTR where) {
 try {throw;} catch(winrt::hresult_error const& e) {
  Wh_Log(L"[Emberveil] %s: 0x%08X %s",where,(unsigned)e.code().value,e.message().c_str());
 } catch(...) {Wh_Log(L"[Emberveil] %s: exception",where);}
}
static bool NativeDispatch(folder_menus_dispatch::ThreadProc proc) {
 HWND hwnd=taskwin::FindCurrentProcessTaskbarWnd();
 return hwnd && folder_menus_dispatch::RunFromWindowThread(hwnd,proc,nullptr,
  L"Windhawk_EmberveilDesktopIndicator_Dispatch");
}

static constexpr wchar_t kSlotName[]=L"EmberveilDesktopIndicatorSlot";
static constexpr wchar_t kLeaseName[]=L"EmberveilDesktopIndicatorLease";

static FrameworkElement FindNamed(FrameworkElement const& root, wchar_t const* name, int depth=0) {
    if(!root || depth>24) return nullptr;
    if(root.Name()==name) return root;
    int count=VisualTreeHelper::GetChildrenCount(root);
    for(int i=0;i<count;i++) {
        auto child=VisualTreeHelper::GetChild(root,i).try_as<FrameworkElement>();
        if(auto found=FindNamed(child,name,depth+1)) return found;
    }
    return nullptr;
}

static FrameworkElement LiveTaskbarRoot() {
    HWND wnd=taskwin::FindCurrentProcessTaskbarWnd();
    if(!wnd) return nullptr;
    auto xamlRoot=taskxaml::GetTaskbarXamlRoot(wnd);
    return xamlRoot ? xamlRoot.Content().try_as<FrameworkElement>() : nullptr;
}

static Panel LiveTray() {
    auto root=LiveTaskbarRoot();
    return root ? FindNamed(root,L"SystemTrayFrameGrid").try_as<Panel>() : nullptr;
}

// Locate the application repeater's actual parent for icon-area insertion.
// Do not substitute a tray slot when the XAML hierarchy differs.
static bool FindApplicationRepeater(FrameworkElement const& root,
                                    Panel& parent, FrameworkElement& repeater,
                                    int depth=0) {
    if(!root || depth>24) return false;
    // Windows 11 taskbar applications are hosted by TaskbarFrameRepeater.
    // Only lease beside a direct child of a supported panel.
    if(auto panel=root.try_as<Panel>()) {
        for(auto const& child:panel.Children()) {
            auto element=child.try_as<FrameworkElement>();
            if(element && element.Name()==L"TaskbarFrameRepeater" &&
               slot::Classify(panel)!=slot::Kind::Unsupported) {
                parent=panel;
                repeater=element;
                return true;
            }
        }
    }
    int count=VisualTreeHelper::GetChildrenCount(root);
    for(int i=0;i<count;i++) {
        auto child=VisualTreeHelper::GetChild(root,i).try_as<FrameworkElement>();
        if(child && FindApplicationRepeater(child,parent,repeater,depth+1))
            return true;
    }
    return false;
}

// Center uses a full-width taskbar root Grid overlay rather than a leased
// application/tray slot. Only accept a root that actually spans the taskbar;
// otherwise skip rather than accidentally center inside a small subpanel.
static Panel ResolveCenterParent() {
    auto root=LiveTaskbarRoot();
    auto grid=root.try_as<Grid>();
    HWND wnd=taskwin::FindCurrentProcessTaskbarWnd();
    RECT rect{};
    if(!grid || !wnd || !GetWindowRect(wnd,&rect)) return nullptr;
    double dpi=(double)GetDpiForWindow(wnd);
    double taskbarWidth=(rect.right-rect.left)*96.0/dpi;
    if(taskbarWidth<=0 || grid.ActualWidth()<taskbarWidth*0.75) {
        Wh_Log(L"[Emberveil] Center skipped: root Grid width %.1f vs taskbar %.1f DIP",
               grid.ActualWidth(),taskbarWidth);
        return nullptr;
    }
    Panel iconsParent{nullptr};
    FrameworkElement repeater{nullptr};
    auto tray=FindNamed(root,L"SystemTrayFrameGrid");
    if(!tray || tray.ActualWidth()<=0 ||
       !FindApplicationRepeater(root,iconsParent,repeater) ||
       !repeater || repeater.ActualWidth()<=0) {
        Wh_Log(L"[Emberveil] Center waiting for application/tray layout");
        return nullptr;
    }
    return grid;
}

static Panel ResolvePositionParent(int& slotIndex) {
    slotIndex=-1;
    if(g_position==L"after-icons" || g_position==L"before-icons") {
        // Unlike before-icons, the repeater's column spans nearly the whole
        // taskbar. Use a non-layout-affecting overlay anchored to realized icons.
        auto root=LiveTaskbarRoot();
        auto grid=root.try_as<Grid>();
        Panel iconsParent{nullptr}; FrameworkElement repeater{nullptr};
        if(grid && grid.ActualWidth()>0 &&
           FindApplicationRepeater(root,iconsParent,repeater) &&
           repeater && repeater.ActualWidth()>0) {
            slotIndex=0;
            return grid;
        }
        return nullptr;
    }
    if(g_position==L"center") {
        auto center=ResolveCenterParent();
        if(center) slotIndex=0;
        return center;
    }
    if(g_position==L"before-tray") {
        auto tray=LiveTray();
        if(tray && slot::ResolveSlot(tray,slot::Anchor::BeforeIcons,slotIndex)) return tray;
        return nullptr;
    }
    if(g_position==L"after-tray") {
        auto tray=LiveTray();
        if(!tray) return nullptr;
        if(slot::ResolveSlot(tray,slot::Anchor::AfterShowDesktop,slotIndex)) return tray;
        Wh_Log(L"[Emberveil] After-tray anchor unavailable; named children: %s",
               slot::DescribeChildren(tray).c_str());
        return nullptr;
    }
    auto root=LiveTaskbarRoot();
    Panel parent{nullptr};
    FrameworkElement repeater{nullptr};
    if(root && FindApplicationRepeater(root,parent,repeater)) {
        // During Explorer startup the repeater can exist before its first
        // layout pass. Inserting at that point can lease column zero and
        // overlay the Start area. Let the startup worker retry instead.
        if(root.ActualWidth()<=0 || parent.ActualWidth()<=0 ||
           repeater.ActualWidth()<=0 || repeater.ActualHeight()<=0) {
            Wh_Log(L"[Emberveil] Icon anchor waiting for layout: root=%.1f parent=%.1f repeater=%.1fx%.1f",
                   root.ActualWidth(),parent.ActualWidth(),
                   repeater.ActualWidth(),repeater.ActualHeight());
            return nullptr;
        }
        try {
            auto point=repeater.TransformToVisual(parent).TransformPoint({0,0});
            if(!std::isfinite(point.X) || !std::isfinite(point.Y) ||
               point.X < -1.0 || point.X > parent.ActualWidth()+1.0) {
                Wh_Log(L"[Emberveil] Icon anchor waiting for stable coordinates: x=%.1f",point.X);
                return nullptr;
            }
        } catch(...) {
            Wh_Log(L"[Emberveil] Icon anchor transform unavailable; retrying");
            return nullptr;
        }
        auto kind=slot::Classify(parent);
        if(kind==slot::Kind::Columns) {
            int column=Grid::GetColumn(repeater);
            int span=std::max(1,Grid::GetColumnSpan(repeater));
            slotIndex=column+(g_position==L"after-icons"?span:0);
        } else if(kind==slot::Kind::Order) {
            int index=slot::IndexOfChild(parent,repeater);
            if(index>=0) slotIndex=index+(g_position==L"after-icons"?1:0);
        }
        Wh_Log(L"[Emberveil] Icon anchor: parent=%s repeater=%s slot=%d children=%s",
               slot::ClassName(parent).c_str(),slot::ClassName(repeater).c_str(),
               slotIndex,slot::DescribeChildren(parent).c_str());
        if(slotIndex>=0) return parent;
    }
    Wh_Log(L"[Emberveil] Icon position '%s' unavailable: no supported TaskbarFrameRepeater parent; insertion skipped",
           g_position.c_str());
    return nullptr;
}

// Keep the overlay centered until the live application repeater reaches it,
// then translate right, stopping before the tray. Windows icon layout and
// overflow behavior remain unchanged.
static int g_centerDiagnosticCount=0;
static void UpdateDynamicCenterOnUiThread() {
    if(g_position!=L"center" || !g_pill) return;
    auto root=LiveTaskbarRoot();
    auto grid=root.try_as<Grid>();
    auto tray=LiveTray();
    if(!grid || !tray || grid.ActualWidth()<=0) return;
    Panel iconsParent{nullptr};
    FrameworkElement repeater{nullptr};
    if(!FindApplicationRepeater(root,iconsParent,repeater) || !repeater) return;
    try {
        auto point=winrt::Windows::Foundation::Point{0,0};
        auto appOrigin=repeater.TransformToVisual(grid).TransformPoint(point);
        auto trayOrigin=tray.TransformToVisual(grid).TransformPoint(point);
        // Auto-sized XAML Width is NaN. Measure the content instead of
        // propagating NaN into the positioning and visibility calculations.
        double pillWidth=g_pill.ActualWidth();
        if(!std::isfinite(pillWidth) || pillWidth<=0) {
            g_pill.Measure({10000.0, 100.0});
            pillWidth=g_pill.DesiredSize().Width;
        }
        if(!std::isfinite(pillWidth) || pillWidth<=0) {
            Wh_Log(L"[Emberveil] Dynamic center awaiting valid measured width");
            return;
        }
        double centeredLeft=(grid.ActualWidth()-pillWidth)/2.0;
        // ItemsRepeater can occupy the entire taskbar even when its realized
        // buttons use only a small portion. Measure the realized children.
        double appRight=appOrigin.X;
        unsigned measuredButtons=0;
        int count=VisualTreeHelper::GetChildrenCount(repeater);
        for(int i=0;i<count;++i) {
            auto child=VisualTreeHelper::GetChild(repeater,i).try_as<FrameworkElement>();
            if(!child || child.Visibility()!=Visibility::Visible ||
               child.ActualWidth()<=0 || child.ActualWidth()>400.0) continue;
            auto pos=child.TransformToVisual(grid).TransformPoint({0,0});
            if(std::isfinite(pos.X) && pos.X>=0 &&
               pos.X+child.ActualWidth()<=grid.ActualWidth()+1.0) {
                appRight=std::max(appRight,pos.X+child.ActualWidth());
                ++measuredButtons;
            }
        }
        // If buttons are not realized yet, do not mistake the full-width
        // repeater for occupied space; defer visibility until the next tick.
        if(measuredButtons==0) {
            Wh_Log(L"[Emberveil] Center awaiting realized buttons: repeaterW=%.1f children=%d",repeater.ActualWidth(),count);
            g_pill.Visibility(Visibility::Collapsed);
            return;
        }
        double gap=(double)g_settings.nativeGap;
        double maximumLeft=trayOrigin.X-pillWidth-gap;
        // Offset the visual position, not its layout width. Keep the marker
        // group inside the available app-to-tray region.
        double requestedLeft=std::max(centeredLeft,appRight+gap) +
                             (double)g_settings.horizontalOffset;
        double minimumLeft=std::max(0.0,appRight+gap);
        double wantedLeft=std::clamp(requestedLeft,minimumLeft,std::max(minimumLeft,maximumLeft));
        // If the available region is exhausted, hide rather than overlap the
        // system tray or the application buttons. This does not force overflow.
        bool room=maximumLeft>=minimumLeft;
        if(g_centerDiagnosticCount<12) {
            Wh_Log(L"[Emberveil] Center layout: root=%.1f repeaterX=%.1f repeaterW=%.1f appRight=%.1f trayX=%.1f pillW=%.1f centered=%.1f wanted=%.1f max=%.1f room=%d",
                   grid.ActualWidth(),appOrigin.X,repeater.ActualWidth(),appRight,
                   trayOrigin.X,pillWidth,centeredLeft,wantedLeft,maximumLeft,room?1:0);
            ++g_centerDiagnosticCount;
        }
        g_pill.Visibility(room?Visibility::Visible:Visibility::Collapsed);
        double left=wantedLeft;
        if(room) {
            auto translation=g_pill.RenderTransform().try_as<TranslateTransform>();
            if(!translation) {
                translation=TranslateTransform();
                g_pill.RenderTransform(translation);
            }
            translation.X(left-centeredLeft);
        }
    } catch(...) {
        // Do not disturb the stable anchored positions on unsupported trees.
        Wh_Log(L"[Emberveil] Dynamic center bounds unavailable; retaining last placement");
    }
}

// Diagnostic discovery of the Start/app coordinate spaces. Keep this bounded:
// the Windows taskbar visual tree may be large and changes across builds.
static void DiagnoseBeforeIconsTree(FrameworkElement const& root,
                                    FrameworkElement const& repeater,
                                    Grid const& grid) {
    static int runs=0;
    if (++runs>5 || !root || !grid) return;
    Wh_Log(L"[Emberveil] Anchor diagnostics: rootW=%.1f gridW=%.1f repeaterW=%.1f",
           root.ActualWidth(),grid.ActualWidth(),repeater?repeater.ActualWidth():-1.0);
    struct Item { FrameworkElement element; int depth; };
    std::vector<Item> pending{{root,0}};
    int inspected=0, printed=0;
    while(!pending.empty() && inspected<1500 && printed<32) {
        Item item=pending.back(); pending.pop_back(); ++inspected;
        try {
            auto name=std::wstring(item.element.Name());
            bool interesting=name.find(L"Start")!=std::wstring::npos ||
                name.find(L"TaskbarFrame")!=std::wstring::npos ||
                name.find(L"Search")!=std::wstring::npos ||
                name.find(L"Widget")!=std::wstring::npos;
            if(interesting && item.element.ActualWidth()>0) {
                auto pt=item.element.TransformToVisual(grid).TransformPoint({0,0});
                Wh_Log(L"[Emberveil] Anchor node: %s x=%.1f right=%.1f w=%.1f depth=%d",
                       name.c_str(),pt.X,pt.X+item.element.ActualWidth(),
                       item.element.ActualWidth(),item.depth);
                ++printed;
            }
            if(item.depth>=20) continue;
            int count=VisualTreeHelper::GetChildrenCount(item.element);
            for(int i=count-1;i>=0;--i) {
                auto child=VisualTreeHelper::GetChild(item.element,i).try_as<FrameworkElement>();
                if(child) pending.push_back({child,item.depth+1});
            }
        } catch(...) {}
    }
    Wh_Log(L"[Emberveil] Anchor scan: inspected=%d matched=%d",inspected,printed);
}

// Before-icons is anchored to the first realized app button, not the
// taskbar root's column zero (which can be ahead of Start).
static void UpdateBeforeIconsOnUiThread() {
    if(g_position!=L"before-icons" || !g_pill) return;
    auto root=LiveTaskbarRoot(); auto grid=root.try_as<Grid>();
    Panel iconsParent{nullptr}; FrameworkElement repeater{nullptr};
    if(!grid || !FindApplicationRepeater(root,iconsParent,repeater)) return;
    try {
        FrameworkElement startButton{nullptr};
        FrameworkElement firstApp{nullptr};
        double startRight=-1, firstX=grid.ActualWidth();
        int count=VisualTreeHelper::GetChildrenCount(repeater);
        for(int i=0;i<count;++i) {
            auto child=VisualTreeHelper::GetChild(repeater,i).try_as<FrameworkElement>();
            if(!child || child.Visibility()!=Visibility::Visible || child.ActualWidth()<=0) continue;
            auto point=child.TransformToVisual(grid).TransformPoint({0,0});
            if(!std::isfinite(point.X) || point.X<0 || point.X>=grid.ActualWidth()) continue;
            if(child.Name()==L"LaunchListButton") {
                if(point.X+child.ActualWidth()>startRight) {
                    startRight=point.X+child.ActualWidth(); startButton=child;
                }
            } else if(child.Name()==L"TaskListButton" && point.X<firstX) {
                firstX=point.X; firstApp=child;
            }
        }
        if(!startButton || startRight<0) {
            // A virtual desktop switch can temporarily unrealize the taskbar.
            // Retain the last good placement rather than hiding the indicator.
            static int missingStart=0;
            if(missingStart++<5) Wh_Log(L"[Emberveil] Before-icons dev12: Start unavailable; retaining placement");
            return;
        }
        // Some desktops have no running application buttons at all. The
        // Start button is still a valid anchor for the indicator. Reserve
        // space on the first app only when one actually exists.
        auto current=g_beforeIconsFirstButton.get();
        if(g_beforeIconsMarginApplied && current!=firstApp)
            RestoreBeforeIconsReservation();
        // ItemsRepeater owns its children; inserting an arbitrary child into
        // its visual tree is unsupported. Request space through a child margin.
        // Preserve the exact original value for clean uninstall/rebuild.
        // Measure the complete marker run rather than clipping it to 64 DIP.
        // TextBlock has 8 DIP horizontal margins on both sides.
        double width=64.0;
        if (auto panel=g_pill.try_as<Panel>()) {
            for (auto element:panel.Children()) {
                if (auto label=element.try_as<FrameworkElement>()) {
                    if(label.Visibility()!=Visibility::Visible) continue;
                    label.Measure({10000.0, 100.0});
                    width=std::max(width, std::ceil(label.DesiredSize().Width)+4.0);
                }
            }
        }
        if(!std::isfinite(width) || width<=0) width=64.0;
        if(std::abs(g_pill.Width()-width)>0.5) g_pill.Width(width);
        if(firstApp) {
            if(!g_beforeIconsMarginApplied) {
                g_beforeIconsOriginalMargin=firstApp.Margin();
                g_beforeIconsFirstButton=winrt::make_weak(firstApp);
                g_beforeIconsMarginApplied=true;
            }
            auto margin=g_beforeIconsOriginalMargin;
            margin.Left+=width+(double)g_settings.nativeMarginLeft+(double)g_settings.nativeMarginRight;
            firstApp.Margin(margin);
        }
        // Overlay is centered in the root grid, and its visual translation
        // targets the newly reserved area immediately following Start.
        double target=startRight+(double)g_settings.nativeMarginLeft+(width/2.0);
        double centered=grid.ActualWidth()/2.0;
        auto transform=g_pill.RenderTransform().try_as<TranslateTransform>();
        if(!transform){transform=TranslateTransform();g_pill.RenderTransform(transform);}
        transform.X(target-centered);
        g_pill.Visibility(Visibility::Visible);
        static int logged=0;
        if(logged++<12) Wh_Log(L"[Emberveil] Before-icons dev12: startRight=%.1f firstApp=%.1f reserve=%.1f left=%d right=%d actualFirst=%.1f",
                             startRight,firstX,width,g_settings.nativeMarginLeft,g_settings.nativeMarginRight,firstApp?firstApp.ActualWidth():0.0);
    } catch(...) { Wh_Log(L"[Emberveil] Before-icons dev10 measurement/reservation failed"); }
}

// After-icons is visually anchored to the last realized taskbar button.
// Never resize or re-column the taskbar's full-width ItemsRepeater.
static int g_afterIconsDiagnosticCount=0;
static void UpdateAfterIconsOnUiThread() {
    if(g_position!=L"after-icons" || !g_pill) return;
    auto root=LiveTaskbarRoot();
    auto grid=root.try_as<Grid>();
    if(!grid || grid.ActualWidth()<=0) return;
    Panel iconsParent{nullptr}; FrameworkElement repeater{nullptr};
    if(!FindApplicationRepeater(root,iconsParent,repeater) || !repeater) return;
    try {
        auto origin=repeater.TransformToVisual(grid).TransformPoint({0,0});
        double appRight=origin.X;
        unsigned measured=0;
        int count=VisualTreeHelper::GetChildrenCount(repeater);
        for(int i=0;i<count;++i) {
            auto child=VisualTreeHelper::GetChild(repeater,i).try_as<FrameworkElement>();
            if(!child || child.Visibility()!=Visibility::Visible ||
               child.ActualWidth()<=0 || child.ActualWidth()>400.0) continue;
            auto pos=child.TransformToVisual(grid).TransformPoint({0,0});
            if(std::isfinite(pos.X) && pos.X>=0 &&
               pos.X+child.ActualWidth()<=grid.ActualWidth()+1.0) {
                appRight=std::max(appRight,pos.X+child.ActualWidth());
                ++measured;
            }
        }
        double pillWidth=g_pill.ActualWidth();
        if(pillWidth<=0) pillWidth=g_pill.Width();
        double centeredLeft=(grid.ActualWidth()-pillWidth)/2.0;
        double desiredLeft=appRight+(double)g_settings.nativeGap;
        double rightLimit=grid.ActualWidth();
        if(auto tray=LiveTray()) {
            auto trayPos=tray.TransformToVisual(grid).TransformPoint({0,0});
            rightLimit=trayPos.X;
        }
        bool room=measured>0 && desiredLeft+pillWidth<=rightLimit;
        g_pill.Visibility(room?Visibility::Visible:Visibility::Collapsed);
        if(room) {
            auto transform=g_pill.RenderTransform().try_as<TranslateTransform>();
            if(!transform) {transform=TranslateTransform();g_pill.RenderTransform(transform);}
            transform.X(desiredLeft-centeredLeft);
        }
        if(g_afterIconsDiagnosticCount<15) {
            Wh_Log(L"[Emberveil] After-icons: repeaterW=%.1f measured=%u appRight=%.1f desired=%.1f trayLeft=%.1f pillW=%.1f room=%d",
                   repeater.ActualWidth(),measured,appRight,desiredLeft,rightLimit,pillWidth,room?1:0);
            ++g_afterIconsDiagnosticCount;
        }
    } catch(...) {
        Wh_Log(L"[Emberveil] After-icons measurement unavailable; retrying");
    }
}



// Direct desktop selection for marker mode. Windows doesn't expose a public
// virtual-desktop switch-by-index API. Use the supported Win+Ctrl+Arrow
// shortcut, advancing from the currently observed desktop number.
// SendInput is intentionally restricted to a user-initiated marker click.
static void SwitchToDesktopFromMarker(int target) {
 int current=g_currentDesktopNumber.load();
 int count=ReadDesktopCountFromRegistry();
 if(target<1 || target>count || current<1 || current>count || target==current) return;
 const WORD arrow=target>current?VK_RIGHT:VK_LEFT;
 const int steps=std::abs(target-current);
 Wh_Log(L"[Emberveil] Marker click: current=%d target=%d steps=%d",current,target,steps);
 for(int i=0;i<steps && !g_unloading.load();++i) {
  INPUT keys[6]{};
  WORD codes[6]={VK_LWIN,VK_CONTROL,arrow,arrow,VK_CONTROL,VK_LWIN};
  for(int k=0;k<6;++k) {
   keys[k].type=INPUT_KEYBOARD;
   keys[k].ki.wVk=codes[k];
   if(k>=3) keys[k].ki.dwFlags=KEYEVENTF_KEYUP;
  }
  if(SendInput(6,keys,sizeof(INPUT))!=6) {
   Wh_Log(L"[Emberveil] Marker navigation: SendInput failed (%lu)",GetLastError());
   break;
  }
  // Allow the shell to process each transition before the next shortcut.
  if(i+1<steps) Sleep(100);
 }
}

// dev.20: independent hit-testable controls for marker navigation.
// Theme resolution is isolated from placement and desktop navigation.
struct MarkerPalette {
 winrt::Windows::UI::Color active, inactive, hover;
};
static winrt::Windows::UI::Color ThemeRgb(unsigned int rgb) {
 return winrt::Windows::UI::Color{255, static_cast<BYTE>((rgb>>16)&255),
  static_cast<BYTE>((rgb>>8)&255), static_cast<BYTE>(rgb&255)};
}
static bool ThemeLightMode() {
 DWORD value=0, size=sizeof(value);
 if(RegGetValueW(HKEY_CURRENT_USER,
   L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
   L"SystemUsesLightTheme",RRF_RT_REG_DWORD,nullptr,&value,&size)==ERROR_SUCCESS)
  return value!=0;
 return false;
}
static winrt::Windows::UI::Color ThemeWindowsAccent() {
 // DWM's colorization color follows the configured system accent on supported builds.
 using GetAccent=HRESULT (WINAPI*)(DWORD*,BOOL*);
 auto dll=GetModuleHandleW(L"dwmapi.dll");
 bool unload=false;
 if(!dll) {dll=LoadLibraryW(L"dwmapi.dll");unload=dll!=nullptr;}
 DWORD argb=0;BOOL opaque=FALSE;
 auto proc=dll?reinterpret_cast<GetAccent>(GetProcAddress(dll,"DwmGetColorizationColor")):nullptr;
 bool ok=proc && SUCCEEDED(proc(&argb,&opaque));
 if(unload) FreeLibrary(dll);
 if(ok) return ThemeRgb(argb&0xFFFFFF);
 DWORD fallback=GetSysColor(COLOR_HIGHLIGHT);
 return winrt::Windows::UI::Color{255,GetRValue(fallback),GetGValue(fallback),GetBValue(fallback)};
}
static MarkerPalette ResolveMarkerPalette() {
 auto accent=ThemeWindowsAccent();
 auto light=ThemeLightMode();
 MarkerPalette p{accent,ThemeRgb(light?0x666666:0xB0B0B0),accent};
 const auto& t=g_settings.themePreset;
 if(t==L"monochrome") p={ThemeRgb(light?0x404040:0xFFFFFF),ThemeRgb(light?0x606060:0xC0C0C0),ThemeRgb(light?0x202020:0xFFFFFF)};
 else if(t==L"emberveil") p={ThemeRgb(0xFFBC5E),ThemeRgb(0xB8A98A),ThemeRgb(0xD9A441)};
 else if(t==L"catppuccinMocha") p={ThemeRgb(0xCBA6F7),ThemeRgb(0x9399B2),ThemeRgb(0xF5C2E7)};
 else if(t==L"catppuccinLatte") p={ThemeRgb(0x8839EF),ThemeRgb(0x9CA0B0),ThemeRgb(0xEA76CB)};
 else if(t==L"catppuccinMacchiato") p={ThemeRgb(0xC6A0F6),ThemeRgb(0x939AB7),ThemeRgb(0xF5BDE6)};
 else if(t==L"catppuccinFrappe") p={ThemeRgb(0xCA9EE6),ThemeRgb(0x949CBB),ThemeRgb(0xF4B8E4)};
 else if(t==L"dracula") p={ThemeRgb(0xBD93F9),ThemeRgb(0x6272A4),ThemeRgb(0xFF79C6)};
 else if(t==L"gruvbox") p={ThemeRgb(0xFABD2F),ThemeRgb(0x928374),ThemeRgb(0xFE8019)};
 else if(t==L"nord") p={ThemeRgb(0x88C0D0),ThemeRgb(0x4C566A),ThemeRgb(0x81A1C1)};
 else if(t==L"solarized") p={ThemeRgb(0x268BD2),ThemeRgb(0x839496),ThemeRgb(0x2AA198)};
 else if(t==L"tokyoNight") p={ThemeRgb(0x7AA2F7),ThemeRgb(0x565F89),ThemeRgb(0xBB9AF7)};
 // 'custom' intentionally inherits Windows Default for empty overrides.
 winrt::Windows::UI::Color overrideColor{};
 if(TryParseColorString(g_settings.activeIndicatorColor,&overrideColor)) p.active=overrideColor;
 if(TryParseColorString(g_settings.inactiveMarkerColor,&overrideColor)) p.inactive=overrideColor;
 if(TryParseColorString(g_settings.hoverMarkerColor,&overrideColor)) p.hover=overrideColor;
 return p;
}
static std::wstring MarkerPaletteSignature(MarkerPalette const& p) {
 auto one=[](winrt::Windows::UI::Color c){return std::to_wstring(c.A)+L","+
  std::to_wstring(c.R)+L","+std::to_wstring(c.G)+L","+std::to_wstring(c.B);};
 return one(p.active)+L"|"+one(p.inactive)+L"|"+one(p.hover);
}
static void NativeUpdateTextOnUiThread() {
 if(!g_pill) return;
 auto text=FindNamed(g_pill,L"EmberveilDesktopText").try_as<TextBlock>();
 auto markers=FindNamed(g_pill,L"EmberveilMarkerPanel").try_as<StackPanel>();
 if(!text || !markers) return;
 auto ids=ReadVirtualDesktopIds();
 int count=std::max(1,(int)ids.size());
 int active=g_currentDesktopNumber.load();
 if(g_settings.hideWhenSingleDesktop && count==1) {
  g_pill.Visibility(Visibility::Collapsed);return;
 }
 g_pill.Visibility(Visibility::Visible);
 MarkerPalette palette=ResolveMarkerPalette();
 bool markerMode=g_settings.indicatorMode==IndicatorMode::Markers;
 text.Visibility(markerMode?Visibility::Collapsed:Visibility::Visible);
 markers.Visibility(markerMode?Visibility::Visible:Visibility::Collapsed);
 // Preserve XAML controls across polling ticks. Recreating them every second
 // dismisses any open tooltip and resets its hover delay.
 auto names=markerMode && g_settings.markerTooltips ? ReadVirtualDesktopNames() : std::vector<std::wstring>{};
 std::wstring signature=std::to_wstring(count)+L"|"+std::to_wstring(active)+L"|"+
  std::to_wstring(static_cast<int>(g_settings.indicatorMode))+L"|"+
  std::to_wstring(g_settings.markerTooltips)+L"|"+g_settings.markerSymbol+L"|"+
  MarkerPaletteSignature(palette)+L"|"+
  std::to_wstring(g_settings.inactiveMarkerOpacity)+L"|"+
  std::to_wstring(g_settings.indicatorCharacterSpacing)+L"|"+
  std::to_wstring(g_settings.leftPadding)+L"|"+
  std::to_wstring(g_settings.rightPadding)+L"|"+
  std::to_wstring(static_cast<int>(g_settings.indicatorSize))+L"|"+
  std::to_wstring(static_cast<int>(g_settings.indicatorWeight));
 for(auto const& name:names) signature+=L"|"+name;
 static void* previousPill=nullptr;
 static std::wstring previousSignature;
 if(previousPill==winrt::get_abi(g_pill) && previousSignature==signature) return;
 previousPill=winrt::get_abi(g_pill);
 previousSignature=std::move(signature);
 text.Inlines().Clear();
 markers.Children().Clear();
 if(markerMode) {
  // Explicit spacer widths: XAML collapses leading ordinary spaces.
  const double spaceWidth=GetConfiguredIndicatorFontSize(13)*0.33;
  if(g_settings.leftPadding>0) {
   Controls::Border spacer;
   spacer.Width(g_settings.leftPadding*spaceWidth);
   spacer.IsHitTestVisible(false);
   markers.Children().Append(spacer);
  }
  for(int i=1;i<=count;++i) {
   // Border has no Button visual states (hover bubble / focus rectangle).
   Controls::Border marker;
   marker.Name(L"EmberveilMarkerButton");
   marker.Padding({4,4,4,4});
   marker.Margin({0,0,0,0});
   marker.MinHeight(26);
   marker.Background(SolidColorBrush(winrt::Windows::UI::Colors::Transparent()));
   marker.HorizontalAlignment(HorizontalAlignment::Center);
   marker.VerticalAlignment(VerticalAlignment::Center);
   TextBlock symbol;
   symbol.Text(GetConfiguredMarkerSymbol());
   symbol.FontSize(GetConfiguredIndicatorFontSize(13));
   symbol.FontWeight(GetConfiguredIndicatorFontWeight());
   symbol.IsHitTestVisible(false);
   if(i!=active) {
    auto c=palette.inactive;
    c.A=static_cast<BYTE>(c.A*std::clamp(g_settings.inactiveMarkerOpacity,0,100)/100);
    symbol.Foreground(SolidColorBrush(c));
   } else symbol.Foreground(SolidColorBrush(palette.active));
   marker.Child(symbol);
   if(g_settings.markerTooltips) {
    std::wstring tip=L"Desktop "+std::to_wstring(i);
    if(static_cast<size_t>(i)<=names.size() && !names[i-1].empty()) tip+=L" — "+names[i-1];
    Controls::ToolTipService::SetToolTip(marker,winrt::box_value(tip));
   }
   if(i!=active) {
    auto hoverColor=palette.hover;
    marker.PointerEntered([symbol,hoverColor](auto const&,auto const&) {
     symbol.Foreground(SolidColorBrush(hoverColor));
    });
    auto normalColor=palette.inactive;
    normalColor.A=static_cast<BYTE>(normalColor.A*std::clamp(g_settings.inactiveMarkerOpacity,0,100)/100);
    marker.PointerExited([symbol,normalColor](auto const&,auto const&) {
     symbol.Foreground(SolidColorBrush(normalColor));
    });
   }
   marker.Tapped([desktop=i](auto const&,auto const&) {
    SwitchToDesktopFromMarker(desktop);
   });
   markers.Children().Append(marker);
   if(i<count) {
    // Use hit-testable spacing, rather than a dead TextBlock between buttons.
    // The existing setting counts space characters; approximate their width.
    marker.Margin({0,0,(double)std::max(0,g_settings.indicatorCharacterSpacing)*spaceWidth,0});
   }
  }
  if(g_settings.rightPadding>0) {
   Controls::Border spacer;
   spacer.Width(g_settings.rightPadding*spaceWidth);
   spacer.IsHitTestVisible(false);
   markers.Children().Append(spacer);
  }
  Wh_Log(L"[Emberveil] dev20 marker controls built: count=%d tooltip=%d",count,g_settings.markerTooltips?1:0);
 } else {
  std::wstring value;
  if(g_settings.indicatorMode==IndicatorMode::DesktopName)
   value=FormatDesktopNameOrNumber(active,ReadVirtualDesktopNames());
  else value=FormatDesktopNumber(active);
  Documents::Run run;run.Text(value);
  winrt::Windows::UI::Color c{};
  run.Foreground(SolidColorBrush(palette.active));
  text.Inlines().Append(run);
 }
}
static void NativeRemoveOnUiThread() {
 RestoreBeforeIconsReservation();
 auto parent=g_parent.get();
 if(parent) {
  for(int i=(int)parent.Children().Size()-1;i>=0;--i) {
   auto fe=parent.Children().GetAt(i).try_as<FrameworkElement>();
   if(fe && fe.Name()==kSlotName) parent.Children().RemoveAt(i);
  }
  if(!g_lease.markerName.empty() && !slot::Release(parent,g_lease))
   Wh_Log(L"[Emberveil] Old slot lease unavailable after taskbar recreation");
 }
 g_parent={};g_placeholder={};g_pill=nullptr;g_lease={};
}
static void NativeInsertOnUiThread() {
 if(g_nativeStop.load()) return;
 int index=-1;
 auto parent=ResolvePositionParent(index);
 if(!parent) return;
 for(auto child:parent.Children()) {
  auto fe=child.try_as<FrameworkElement>();
  if(fe && fe.Name()==kSlotName) return;
 }
 Grid box;box.Name(kSlotName);
 box.Height(30);box.VerticalAlignment(VerticalAlignment::Center);
 box.HorizontalAlignment(HorizontalAlignment::Center);
 // Enable hit testing for independent marker buttons.
 box.IsHitTestVisible(g_settings.indicatorMode==IndicatorMode::Markers);
 TextBlock label;label.Name(L"EmberveilDesktopText");
 label.FontSize(GetConfiguredIndicatorFontSize(13));
 label.FontWeight(GetConfiguredIndicatorFontWeight());
 label.VerticalAlignment(VerticalAlignment::Center);
 label.HorizontalAlignment(HorizontalAlignment::Center);
 label.Margin({8,0,8,0});
 label.IsTextSelectionEnabled(false);
 box.Margin({g_position==L"before-icons" || g_position==L"center" ? 0.0 : (double)g_settings.nativeMarginLeft,(double)g_settings.nativeMarginTop,g_position==L"before-icons" || g_position==L"center" ? 0.0 : (double)g_settings.nativeMarginRight,(double)g_settings.nativeMarginBottom});
 box.Children().Append(label);
 StackPanel markerPanel;
 markerPanel.Name(L"EmberveilMarkerPanel");
 markerPanel.Orientation(Controls::Orientation::Horizontal);
 markerPanel.VerticalAlignment(VerticalAlignment::Center);
 markerPanel.HorizontalAlignment(HorizontalAlignment::Center);
 markerPanel.Margin({8,0,8,0});
 box.Children().Append(markerPanel);
 // Width is based on content; centered overlays use a fixed conservative width
 // to avoid the full-width root Grid swallowing pointer input.
 if(g_position==L"center" || g_position==L"after-icons" || g_position==L"before-icons") {
  auto grid=parent.try_as<Grid>();if(!grid)return;
  // Dynamic center sizes to its actual marker content. The former fixed
  // 150-DIP box clipped markers when padding or spacing increased.
  if(g_position!=L"center") box.Width(g_position==L"before-icons" ? 64 : 150);
  Grid::SetColumn(box,0);
  Grid::SetColumnSpan(box,std::max(1,(int)grid.ColumnDefinitions().Size()));
  Grid::SetRowSpan(box,std::max(1,(int)grid.RowDefinitions().Size()));
  Canvas::SetZIndex(box,100);
  grid.Children().Append(box);
 } else {
  if(!slot::AcquireAt(parent,index,kLeaseName,g_lease))return;
  bool ok=false;
  try {ok=slot::PlaceChild(parent,g_lease,box);}catch(...) {slot::Release(parent,g_lease);throw;}
  if(!ok){slot::Release(parent,g_lease);return;}
 }
 g_parent=parent;g_placeholder=box;g_pill=box;
 NativeUpdateTextOnUiThread();
 UpdateDynamicCenterOnUiThread();UpdateAfterIconsOnUiThread();UpdateBeforeIconsOnUiThread();
 Wh_Log(L"[Emberveil] Native indicator inserted at %s",g_position.c_str());
}
static void NativeTickOnUiThread() {
 if(g_nativeStop.load())return;
 auto parent=g_parent.get();
 bool found=false;
 if(parent)for(auto child:parent.Children()) {
  auto fe=child.try_as<FrameworkElement>();
  if(fe && fe.Name()==kSlotName){found=true;break;}
 }
 if(g_nativeRebuild.exchange(false) || !found) {
  NativeRemoveOnUiThread();NativeInsertOnUiThread();
 }
 NativeUpdateTextOnUiThread();
 UpdateDynamicCenterOnUiThread();UpdateAfterIconsOnUiThread();UpdateBeforeIconsOnUiThread();
}
static DWORD WINAPI NativeWorker(void*) {
 while(!g_nativeStop.load()) {
  NativeDispatch([](void*){NativeTickOnUiThread();});
  if(WaitForSingleObject(g_nativeStopEvent,1000)!=WAIT_TIMEOUT)break;
 }
 return 0;
}


namespace desktop_animation {
using WindowCommit = HRESULT (*)(void*, void*, unsigned, float, bool);
using AddTransition = HRESULT (*)(void*, unsigned, unsigned, TA_TIMINGFUNCTION*, void*,
                                  void*, const double*, unsigned, bool);
WindowCommit g_originalCommit;
AddTransition g_originalTransition;
std::atomic<unsigned> g_duration{750};
std::atomic<unsigned> g_keyboardDuration{750};
enum class Curve { Native, Linear, EaseOut };
std::atomic<Curve> g_curve{Curve::Native};
std::atomic<bool> g_forceAnimations{true};
bool g_keyboardHooksAvailable = false;
std::atomic<bool> g_enabled{true};
thread_local unsigned g_hotkeyCommitDepth = 0;
thread_local unsigned g_commitDepth = 0;
thread_local unsigned g_keyboardDepth = 0;
using HotkeyCommit = HRESULT (*)(void*, void*, float);
using CycleInDirection = HRESULT (*)(void*, int);
HotkeyCommit g_originalHotkeyCommit;
CycleInDirection g_originalCycle;
decltype(&SystemParametersInfoW) g_originalSystemParametersInfo;


using AnimationsEnabledFunction = bool (*)(void*);
AnimationsEnabledFunction g_animationsEnabledOriginal;
bool AnimationsEnabledHook(void* self) {
    bool enabled = g_animationsEnabledOriginal(self);
    if (g_enabled.load() && g_forceAnimations.load() && (g_commitDepth || g_keyboardDepth) && !enabled) {
        Wh_Log(L"Allowing animation inside desktop transition");
        return true;
    }
    return enabled;
}

struct DepthScope {
    unsigned& depth;
    explicit DepthScope(unsigned& value) : depth(value) { ++depth; }
    ~DepthScope() { --depth; }
    DepthScope(const DepthScope&) = delete;
    DepthScope& operator=(const DepthScope&) = delete;
};

HRESULT CommitHook(void* self, void* handler, unsigned token,
                   float target, bool touch) {
    // FinishSwipe passes false; FinishTouchSwipe passes true.
    if (touch || !g_enabled.load()) return g_originalCommit(self, handler, token, target, touch);
        Wh_Log(L"gesture window commit: target=%f touch=%d token=%u", target, touch, token);
    DepthScope scope(g_commitDepth);
    return g_originalCommit(self, handler, token, target, touch);
}

HRESULT HotkeyCommitHook(void* self, void* animator, float target) {
    if (!g_enabled.load()) return g_originalHotkeyCommit(self, animator, target);
    Wh_Log(L"keyboard window commit: target=%f", target);
    DepthScope keyboardScope(g_hotkeyCommitDepth);
    DepthScope scope(g_commitDepth);
    return g_originalHotkeyCommit(self, animator, target);
}

HRESULT CycleInDirectionHook(void* self, int direction) {
    // Windows checks SPI_GETCLIENTAREAANIMATION before choosing its animated path.
    // Keep this permission scoped separately from duration changes in Commit.
    if (!g_enabled.load()) return g_originalCycle(self, direction);
    DepthScope scope(g_keyboardDepth);
    return g_originalCycle(self, direction);
}

BOOL WINAPI SystemParametersInfoHook(UINT action, UINT param, PVOID value, UINT flags) {
    if (g_enabled.load() && g_keyboardHooksAvailable && g_forceAnimations.load() && g_keyboardDepth && action == SPI_GETCLIENTAREAANIMATION && value) {
        *static_cast<BOOL*>(value) = TRUE;
        return TRUE;
    }
    return g_originalSystemParametersInfo(action, param, value, flags);
}

HRESULT TransitionHook(void* self, unsigned delayMs, unsigned durationMs,
                       TA_TIMINGFUNCTION* timing, void* storyboard, void* variable,
                       const double* values, unsigned count, bool force) {
    static TA_CUBIC_BEZIER ease{{TTFT_CUBIC_BEZIER}, .22f, 1.f, .36f, 1.f};
    static TA_CUBIC_BEZIER linear{{TTFT_CUBIC_BEZIER}, 1.f/3.f, 1.f/3.f, 2.f/3.f, 2.f/3.f};
    // Only animated cubic transitions within a gesture or hotkey commit are changed.
    // Instantaneous updates during dragging stay untouched.
    if (g_enabled.load() && g_commitDepth && durationMs && timing &&
        timing->eTimingFunctionType == TTFT_CUBIC_BEZIER) {
        unsigned chosen = g_hotkeyCommitDepth ? g_keyboardDuration.load() : g_duration.load();
                Wh_Log(L"settle transition: delay=%u native=%u requested=%u dimensions=%u",
                   delayMs, durationMs, chosen, count);
        durationMs = chosen;
        if (g_curve.load() == Curve::Linear) timing = &linear.header;
        else if (g_curve.load() == Curve::EaseOut) timing = &ease.header;
    }
    return g_originalTransition(self, delayMs, durationMs, timing, storyboard,
                                variable, values, count, force);
}

void LoadAnimationSettings() {
    g_duration = std::clamp(Wh_GetIntSetting(L"Transitions.durationMs"), 150, 5000);
    g_keyboardDuration = std::clamp(Wh_GetIntSetting(L"Transitions.keyboardDurationMs"), 150, 5000);
    PCWSTR curve = Wh_GetStringSetting(L"Transitions.transitionCurve");
    g_curve = wcscmp(curve, L"linear") == 0 ? Curve::Linear :
              wcscmp(curve, L"easeOut") == 0 ? Curve::EaseOut : Curve::Native;
    Wh_FreeStringSetting(curve);
    g_forceAnimations = Wh_GetIntSetting(L"Transitions.forceAnimations") != 0;
    g_enabled = Wh_GetIntSetting(L"Transitions.smoothDesktopTransitions") != 0;
}

bool InitAnimationHooks() {
    Wh_Log(L"[Emberveil] Optional native desktop animation hooks initializing");
    LoadAnimationSettings();
    HMODULE shell = LoadLibraryExW(L"twinui.pcshell.dll", nullptr,
                                   LOAD_LIBRARY_SEARCH_SYSTEM32);
    HMODULE thumbnails = LoadLibraryExW(L"twinui.dll", nullptr,
                                        LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!shell || !thumbnails) {
        Wh_Log(L"Failed to load required shell modules");
        return FALSE;
    }

    // twinui.pcshell.dll
    WindhawkUtils::SYMBOL_HOOK shellHooks[] = {
        {{
             L"public: long __cdecl VirtualDesktopGestureWindow::Commit(struct IVirtualDesktopGestureHandlerPrivate *,unsigned int,float,bool)",
         },
         &g_originalCommit,
         CommitHook},
        {{
             L"public: long __cdecl VirtualDesktopHotKeyWindow::Commit(struct IVirtualDesktopSwitchAnimator2 *,float)",
         },
         &g_originalHotkeyCommit,
         HotkeyCommitHook, true},
        {{
             L"private: long __cdecl CVirtualDesktopHotkeyHandler::_CycleInDirection(enum VirtualDesktopSwitchDirection)",
         },
         &g_originalCycle,
         CycleInDirectionHook, true},
    };
    WindhawkUtils::SYMBOL_HOOK twinuiDllHooks[] = {
        {{
             L"private: long __cdecl CDCompAbstractThumbnail::_AddTransition(unsigned int,unsigned int,struct TA_TIMINGFUNCTION *,struct IUIAnimationStoryboard2 *,struct IUIAnimationVariable2 *,double * const,unsigned int,bool)",
         },
         &g_originalTransition,
         TransitionHook},
        {{
             L"public: virtual bool __cdecl CSwitchThumbnailDeviceManager::AnimationsEnabled(void)",
         },
         &g_animationsEnabledOriginal,
         AnimationsEnabledHook},
    };
    if (!WindhawkUtils::HookSymbols(shell, shellHooks, ARRAYSIZE(shellHooks)) ||
        !WindhawkUtils::HookSymbols(thumbnails, twinuiDllHooks, ARRAYSIZE(twinuiDllHooks))) {
        Wh_Log(L"Failed to hook required symbols; initialization aborted.");
        return FALSE;
    }
    g_keyboardHooksAvailable = g_originalHotkeyCommit && g_originalCycle;
    if (!g_keyboardHooksAvailable) {
        Wh_Log(L"Keyboard symbols unavailable; touchpad support remains active");
    }
    if (g_keyboardHooksAvailable && !WindhawkUtils::SetFunctionHook(SystemParametersInfoW,
                                        SystemParametersInfoHook,
                                        &g_originalSystemParametersInfo)) {
        Wh_Log(L"Failed to hook the desktop hotkey animation preference query");
        g_keyboardHooksAvailable = false;
    }
    Wh_Log(L"[Emberveil] Native desktop animations ready; duration=%u ms", g_duration.load());
    return TRUE;
}


} // namespace desktop_animation

BOOL Wh_ModInit() {
    g_unloading = false;
    LoadSettings();
    g_position=NativePosition();
    g_winVersion = GetExplorerVersion();
    if (g_winVersion < WinVersion::Win11) {
        Wh_Log(L"Only Windows 11 is supported");
        return FALSE;
    }

    g_currentDesktopNumber.store(ReadCurrentDesktopNumberFromRegistry());

    // Animation is optional: unsupported private symbols must not break the indicator.
    if (!desktop_animation::InitAnimationHooks()) {
        Wh_Log(L"[Emberveil] Native animation hooks unavailable; indicator remains active");
    }

    // XAML-only: no clock, SystemTray.dll, or Explorer clock refresh hooks.

    EnsureDesktopChangeTracking();
    folder_menus_dispatch::SetExceptionLogger(NativeLogException);
    if(!taskxaml::HookTaskbarSymbols([](){g_nativeRebuild.store(true);}))
      Wh_Log(L"[Emberveil] Native taskbar hooks unavailable");
    return TRUE;
}

void Wh_ModSettingsChanged() {
    desktop_animation::LoadAnimationSettings();
    NativeDispatch([](void*){NativeRemoveOnUiThread();});
    LoadSettings();
    g_position=NativePosition();
    g_nativeRebuild.store(true);
    EnsureDesktopChangeTracking();
}

void Wh_ModAfterInit() {
    EnsureDesktopChangeTracking();
    if(!g_nativeWorker) {g_nativeStop=false;g_nativeStopEvent=CreateEventW(nullptr,TRUE,FALSE,nullptr);if(g_nativeStopEvent)g_nativeWorker=CreateThread(nullptr,0,NativeWorker,nullptr,0,nullptr);}
}

void Wh_ModBeforeUninit() {
    g_nativeStop=true;
    if(g_nativeStopEvent)SetEvent(g_nativeStopEvent);
    if(g_nativeWorker){WaitForSingleObject(g_nativeWorker,INFINITE);CloseHandle(g_nativeWorker);g_nativeWorker=nullptr;}
    if(g_nativeStopEvent){CloseHandle(g_nativeStopEvent);g_nativeStopEvent=nullptr;}
    NativeDispatch([](void*){NativeRemoveOnUiThread();});
    g_unloading = true;
    StopVirtualDesktopNotificationThread();
    StopDesktopPollThread();
}

void Wh_ModUninit() {
    // Native XAML cleanup is performed in Wh_ModBeforeUninit.
}
