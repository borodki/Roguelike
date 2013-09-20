KEY_EVENT                 = 0x0001
MOUSE_EVENT               = 0x0002
WINDOW_BUFFER_SIZE_EVENT  = 0x0004
MENU_EVENT                = 0x0008
FOCUS_EVENT               = 0x0010

struct CHAR_INFO
  union
    UnicodeChar dw ?
    AsciiChar db ?
  ends
  Attributes dw ?
ends

struct KEY_EVENT_RECORD
  bKeyDown dd ?
  wRepeatCount dw ?
  wVirtualKeyCode dw ?
  wVirtualScanCode dw ?
  union
    UnicodeChar dw ?
    AsciiChar db ?
  ends 
  dwControlKeyState dd ?
ends

struct MOUSE_EVENT_RECORD
  dwMousePosition COORD
  dwButtonState dd ?
  dwControlKeyState dd ?
  dwEventFlags dd ?
ends

struct WINDOW_BUFFER_SIZE_RECORD
  dwSize COORD
ends 
 
struct MENU_EVENT_RECORD
  dwComandId  dd ?
ends

struct FOCUS_EVENT_RECORD
  bSetFocus dd ?
ends

struct INPUT_RECORD
  EventType dw ?
  __pad dw ?
  union
    KeyEvent KEY_EVENT_RECORD
    MouseEvent MOUSE_EVENT_RECORD
    WindowBufferSizeEvent WINDOW_BUFFER_SIZE_RECORD
    MenuEvent MENU_EVENT_RECORD
    FocusEvent FOCUS_EVENT_RECORD
  ends
ends

RIGHT_ALT_PRESSED     = 0x0001      ; the right alt key is pressed.
LEFT_ALT_PRESSED      = 0x0002      ; the left alt key is pressed.
RIGHT_CTRL_PRESSED    = 0x0004      ; the right ctrl key is pressed.
LEFT_CTRL_PRESSED     = 0x0008      ; the left ctrl key is pressed.
SHIFT_PRESSED         = 0x0010      ; the shift key is pressed.
NUMLOCK_ON            = 0x0020      ; the numlock light is on.
SCROLLLOCK_ON         = 0x0040      ; the scrolllock light is on.
CAPSLOCK_ON           = 0x0080      ; the capslock light is on.
ENHANCED_KEY          = 0x0100      ; the key is enhanced.
NLS_DBCSCHAR          = 0x00010000  ; DBCS for JPN: SBCS/DBCS mode.
NLS_ALPHANUMERIC      = 0x00000000  ; DBCS for JPN: Alphanumeric mode.
NLS_KATAKANA          = 0x00020000  ; DBCS for JPN: Katakana mode.
NLS_HIRAGANA          = 0x00040000  ; DBCS for JPN: Hiragana mode.
NLS_ROMAN             = 0x00400000  ; DBCS for JPN: Roman/Noroman mode.
NLS_IME_CONVERSION    = 0x00800000  ; DBCS for JPN: IME conversion.
NLS_IME_DISABLE       = 0x20000000  ; DBCS for JPN: IME enable/disable.

ENABLE_PROCESSED_INPUT      = 0x0001
ENABLE_LINE_INPUT           = 0x0002
ENABLE_ECHO_INPUT           = 0x0004
ENABLE_WINDOW_INPUT         = 0x0008
ENABLE_MOUSE_INPUT          = 0x0010

ENABLE_PROCESSED_OUTPUT     = 0x0001
ENABLE_WRAP_AT_EOL_OUTPUT   = 0x0002

CONSOLE_TEXTMODE_BUFFER     = 1  