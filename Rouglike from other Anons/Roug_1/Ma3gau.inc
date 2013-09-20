;;
;; ported from masm32 to fasm
;;
;; this must be included after all standart files or fasm will generate compile error
;; "equ" is reason but i'm too lazy to replace "equ" with "="

null		=	0
NULL		=	0
TRUE		=	1
true		=	1
FALSE		=	0
false		=	0
almost_overlapped   equ  WS_BORDER or WS_CAPTION or WS_MINIMIZEBOX or WS_SYSMENU

;-------------------------------------------------------------
; Class styles

CS_VREDRAW		=	0001h
CS_HREDRAW		=	0002h
CS_DBLCLKS		=	0008h
CS_OWNDC		=	0020h
CS_CLASSDC		=	0040h
CS_PARENTDC		=	0080h
CS_NOCLOSE		=	0200h
CS_SAVEBITS		=	0800h
CS_BYTEALIGNCLIENT	=	1000h
CS_BYTEALIGNWINDOW	=	2000h
CS_GLOBALCLASS		=	4000h


;----------------------------------------------------------------
; Window Styles

WS_OVERLAPPED		=	 00000000h
WS_POPUP		=	 80000000h
WS_CHILD		=	 40000000h
WS_MINIMIZE		=	 20000000h
WS_VISIBLE		=	 10000000h
WS_DISABLED		=	 08000000h
WS_CLIPSIBLINGS 	=	 04000000h
WS_CLIPCHILDREN 	=	 02000000h
WS_MAXIMIZE		=	 01000000h
WS_CAPTION		=	 00C00000h     ;/* WS_BORDER or WS_DLGFRAME  */
WS_BORDER		=	 00800000h
WS_DLGFRAME		=	 00400000h
WS_VSCROLL		=	 00200000h
WS_HSCROLL		=	 00100000h
WS_SYSMENU		=	 00080000h
WS_THICKFRAME		=	 00040000h
WS_GROUP		=	 00020000h
WS_TABSTOP		=	 00010000h

WS_MINIMIZEBOX		=	 00020000h
WS_MAXIMIZEBOX		=	 00010000h
WS_TILED		=	 WS_OVERLAPPED
WS_ICONIC		=	 WS_MINIMIZE
WS_SIZEBOX		=	 WS_THICKFRAME
WS_TILEDWINDOW		=	 WS_OVERLAPPEDWINDOW

WS_OVERLAPPEDWINDOW	= WS_OVERLAPPED or WS_CAPTION or WS_SYSMENU or WS_THICKFRAME or WS_MINIMIZEBOX or WS_MAXIMIZEBOX

WS_POPUPWINDOW		= WS_POPUP or WS_BORDER or WS_SYSMENU

WS_CHILDWINDOW		= WS_CHILD

;------------------------------------------------------------------------
; Extended Window Styles


WS_EX_DLGMODALFRAME	=	 00000001h
WS_EX_NOPARENTNOTIFY	=	 00000004h
WS_EX_TOPMOST		=	 00000008h
WS_EX_ACCEPTFILES	=	 00000010h
WS_EX_TRANSPARENT	=	 00000020h
WS_EX_MDICHILD		=	 00000040h
WS_EX_TOOLWINDOW	=	 00000080h
WS_EX_WINDOWEDGE	=	 00000100h
WS_EX_CLIENTEDGE	=	 00000200h
WS_EX_CONTEXTHELP	=	 00000400h
WS_EX_RIGHT		=	 00001000h
WS_EX_LEFT		=	 00000000h
WS_EX_RTLREADING	=	 00002000h
WS_EX_LTRREADING	=	 00000000h
WS_EX_LEFTSCROLLBAR	=	 00004000h
WS_EX_RIGHTSCROLLBAR	=	 00000000h
WS_EX_CONTROLPARENT	=	 00010000h
WS_EX_STATICEDGE	=	 00020000h
WS_EX_APPWINDOW 	=	 00040000h
WS_EX_LAYERED		=	 00080000h

WS_EX_OVERLAPPEDWINDOW	=  WS_EX_WINDOWEDGE or WS_EX_CLIENTEDGE
WS_EX_PALETTEWINDOW	=  WS_EX_WINDOWEDGE or WS_EX_TOOLWINDOW or WS_EX_TOPMOST

		   
;--------------------------------------------------------
; Color Types

CTLCOLOR_MSGBOX 	=	0
CTLCOLOR_EDIT		=	1
CTLCOLOR_LISTBOX	=	2
CTLCOLOR_BTN		=	3
CTLCOLOR_DLG		=	4
CTLCOLOR_SCROLLBAR	=	5
CTLCOLOR_STATIC 	=	6
CTLCOLOR_MAX		=	7
COLOR_SCROLLBAR 	=	0
COLOR_BACKGROUND	=	1
COLOR_ACTIVECAPTION	=	2
COLOR_INACTIVECAPTION	=	3
COLOR_MENU		=	4
COLOR_WINDOW		=	5
COLOR_WINDOWFRAME	=	6
COLOR_MENUTEXT		=	7
COLOR_WINDOWTEXT	=	8
COLOR_CAPTIONTEXT	=	9
COLOR_ACTIVEBORDER	=	10
COLOR_INACTIVEBORDER	=	11
COLOR_APPWORKSPACE	=	12
COLOR_HIGHLIGHT 	=	13
COLOR_HIGHLIGHTTEXT	=	14
COLOR_BTNFACE		=	15
COLOR_BTNSHADOW 	=	16
COLOR_GRAYTEXT		=	17
COLOR_BTNTEXT		=	18
COLOR_INACTIVECAPTIONTEXT = 19
COLOR_BTNHIGHLIGHT	=	20

COLOR_3DDKSHADOW	=	21
COLOR_3DLIGHT		=	22
COLOR_INFOTEXT		=	23
COLOR_INFOBK		=	24

COLOR_HOTLIGHT			=	26
COLOR_GRADIENTACTIVECAPTION	=	27
COLOR_GRADIENTINACTIVECAPTION	=	28

COLOR_DESKTOP		=	COLOR_BACKGROUND
COLOR_3DFACE		=	COLOR_BTNFACE
COLOR_3DSHADOW		=	COLOR_BTNSHADOW
COLOR_3DHIGHLIGHT	=	COLOR_BTNHIGHLIGHT
COLOR_3DHILIGHT 	=	COLOR_BTNHIGHLIGHT
COLOR_BTNHILIGHT	=	COLOR_BTNHIGHLIGHT

;-------------------------------------------------------------
; icon


IDI_APPLICATION 	=	32512
IDI_HAND		=	32513
IDI_QUESTION		=	32514
IDI_EXCLAMATION 	=	32515
IDI_ASTERISK		=	32516
IDI_WINLOGO		=	32517
IDI_WARNING		=	IDI_EXCLAMATION
IDI_ERROR		=	IDI_HAND
IDI_INFORMATION 	=	IDI_ASTERISK

;--------------------------------------------------------------
; Dialog Box Command IDs


IDOK			=	1
IDCANCEL		=	2
IDABORT 		=	3
IDRETRY 		=	4
IDIGNORE		=	5
IDYES			=	6
IDNO			=	7
IDCLOSE 		=	8
IDHELP			=	9



;---------------------------------------------------------------
; Standard Cursor IDs


IDC_ARROW	    =     32512
IDC_IBEAM	    =     32513
IDC_WAIT	    =     32514
IDC_CROSS	    =     32515
IDC_UPARROW	    =     32516
IDC_SIZE	    =     32640	; /* OBSOLETE: use IDC_SIZEALL */
IDC_ICON	    =     32641	; /* OBSOLETE: use IDC_ARROW */
IDC_SIZENWSE	    =     32642
IDC_SIZENESW	    =     32643
IDC_SIZEWE	    =     32644
IDC_SIZENS	    =     32645
IDC_SIZEALL	    =     32646
IDC_NO		    =     32648	; /* not in win3.1 */

IDC_HAND	    =     32649

IDC_APPSTARTING     =     32650	; /* not in win3.1 */

IDC_HELP	    =     32651


;-----------------------------------------------------------------------
; GetSystemMetrics() codes


SM_CXSCREEN		=	0
SM_CYSCREEN		=	1
SM_CXVSCROLL		=	2
SM_CYHSCROLL		=	3
SM_CYCAPTION		=	4
SM_CXBORDER		=	5
SM_CYBORDER		=	6
SM_CXDLGFRAME		=	7
SM_CYDLGFRAME		=	8
SM_CYVTHUMB		=	9
SM_CXHTHUMB		=	10
SM_CXICON		=	11
SM_CYICON		=	12
SM_CXCURSOR		=	13
SM_CYCURSOR		=	14
SM_CYMENU		=	15
SM_CXFULLSCREEN 	=	16
SM_CYFULLSCREEN 	=	17
SM_CYKANJIWINDOW	=	18
SM_MOUSEPRESENT 	=	19
SM_CYVSCROLL		=	20
SM_CXHSCROLL		=	21
SM_DEBUG		=	22
SM_SWAPBUTTON		=	23
SM_RESERVED1		=	24
SM_RESERVED2		=	25
SM_RESERVED3		=	26
SM_RESERVED4		=	27
SM_CXMIN		=	28
SM_CYMIN		=	29
SM_CXSIZE		=	30
SM_CYSIZE		=	31
SM_CXFRAME		=	32
SM_CYFRAME		=	33
SM_CXMINTRACK		=	34
SM_CYMINTRACK		=	35
SM_CXDOUBLECLK		=	36
SM_CYDOUBLECLK		=	37
SM_CXICONSPACING	=	38
SM_CYICONSPACING	=	39
SM_MENUDROPALIGNMENT	=	40
SM_PENWINDOWS		=	41
SM_DBCSENABLED		=	42
SM_CMOUSEBUTTONS	=	43

SM_CXFIXEDFRAME 	=	SM_CXDLGFRAME	;win40 name change */
SM_CYFIXEDFRAME 	=	SM_CYDLGFRAME	;win40 name change */
SM_CXSIZEFRAME		=	SM_CXFRAME	;win40 name change */
SM_CYSIZEFRAME		=	SM_CYFRAME	;win40 name change */

SM_SECURE		=	44
SM_CXEDGE		=	45
SM_CYEDGE		=	46
SM_CXMINSPACING 	=	47
SM_CYMINSPACING 	=	48
SM_CXSMICON		=	49
SM_CYSMICON		=	50
SM_CYSMCAPTION		=	51
SM_CXSMSIZE		=	52
SM_CYSMSIZE		=	53
SM_CXMENUSIZE		=	54
SM_CYMENUSIZE		=	55
SM_ARRANGE		=	56
SM_CXMINIMIZED		=	57
SM_CYMINIMIZED		=	58
SM_CXMAXTRACK		=	59
SM_CYMAXTRACK		=	60
SM_CXMAXIMIZED		=	61
SM_CYMAXIMIZED		=	62
SM_NETWORK		=	63
SM_CLEANBOOT		=	67
SM_CXDRAG		=	68
SM_CYDRAG		=	69

SM_SHOWSOUNDS		=	70

SM_CXMENUCHECK		=	71   ;/* Use instead of GetMenuCheckMarkDimensions()! */
SM_CYMENUCHECK		=	72
SM_SLOWMACHINE		=	73
SM_MIDEASTENABLED	=	74
SM_MOUSEWHEELPRESENT	=	75
SM_XVIRTUALSCREEN	=	76
SM_YVIRTUALSCREEN	=	77
SM_CXVIRTUALSCREEN	=	78
SM_CYVIRTUALSCREEN	=	79
SM_CMONITORS		=	80
SM_SAMEDISPLAYFORMAT	=	81

SM_CMETRICS		=	76

;; SM_CMETRICS             =  83


;--------------------------------------------------------
; Edit Control Styles

ES_LEFT 	    =     0000h
ES_CENTER	    =     0001h
ES_RIGHT	    =     0002h
ES_MULTILINE	    =     0004h
ES_UPPERCASE	    =     0008h
ES_LOWERCASE	    =     0010h
ES_PASSWORD	    =     0020h
ES_AUTOVSCROLL	    =     0040h
ES_AUTOHSCROLL	    =     0080h
ES_NOHIDESEL	    =     0100h
ES_OEMCONVERT	    =     0400h
ES_READONLY	    =     0800h
ES_WANTRETURN	    =     1000h

ES_NUMBER	    =     2000h


;-----------------------------------------------------------
; ShowWindow() Commands


SW_HIDE 	    =     0
SW_SHOWNORMAL	    =     1
SW_NORMAL	    =     1
SW_SHOWMINIMIZED    =     2
SW_SHOWMAXIMIZED    =     3
SW_MAXIMIZE	    =     3
SW_SHOWNOACTIVATE   =     4
SW_SHOW 	    =     5
SW_MINIMIZE	    =     6
SW_SHOWMINNOACTIVE  =     7
SW_SHOWNA	    =     8
SW_RESTORE	    =     9
SW_SHOWDEFAULT	    =     10
SW_FORCEMINIMIZE    =     11
SW_MAX		    =     11

;----------------------------------
; Old ShowWindow() Commands

HIDE_WINDOW	    =     0
SHOW_OPENWINDOW     =     1
SHOW_ICONWINDOW     =     2
SHOW_FULLSCREEN     =     3
SHOW_OPENNOACTIVATE =     4

;----------------------------------
; Identifiers for the WM_SHOWWINDOW message

SW_PARENTCLOSING    =     1
SW_OTHERZOOM	    =     2
SW_PARENTOPENING    =     3
SW_OTHERUNZOOM	    =     4


;---------------------------------------------------------------
; SetWindowPos Flags



SWP_NOSIZE	    =     0001h
SWP_NOMOVE	    =     0002h
SWP_NOZORDER	    =     0004h
SWP_NOREDRAW	    =     0008h
SWP_NOACTIVATE	    =     0010h
SWP_FRAMECHANGED    =     0020h ;/* The frame changed: send WM_NCCALCSIZE */
SWP_SHOWWINDOW	    =     0040h
SWP_HIDEWINDOW	    =     0080h
SWP_NOCOPYBITS	    =     0100h
SWP_NOOWNERZORDER   =     0200h  ;/* Don't do owner Z ordering */
SWP_NOSENDCHANGING  =     0400h  ;/* Don't send WM_WINDOWPOSCHANGING */

SWP_DRAWFRAME	    =     SWP_FRAMECHANGED
SWP_NOREPOSITION    =     SWP_NOOWNERZORDER


SWP_DEFERERASE	    =     2000h
SWP_ASYNCWINDOWPOS  =     4000h


HWND_TOP	    =     0
HWND_BOTTOM	    =     1
HWND_TOPMOST	    =     -1
HWND_NOTOPMOST	    =     -2


;-------------------------------------------------------------------
; Window field offsets for GetWindowLong()


GWL_WNDPROC	    = 	-4
GWL_HINSTANCE	    = 	-6
GWL_HWNDPARENT	    = 	-8
GWL_STYLE	    = 	-16
GWL_EXSTYLE	    = 	-20
GWL_USERDATA	    = 	-21
GWL_ID		    = 	-12



;--------------------------------------------------------------
; Window Messages


WM_NULL 			=	0000h
WM_CREATE			=	0001h
WM_DESTROY			=	0002h
WM_MOVE 			=	0003h
WM_SIZE 			=	0005h

WM_ACTIVATE			=	0006h
    WA_INACTIVE 		=	0
    WA_ACTIVE			=	1
    WA_CLICKACTIVE		=	2

WM_SETFOCUS			=	0007h
WM_KILLFOCUS			=	0008h
WM_ENABLE			=	000Ah
WM_SETREDRAW			=	000Bh
WM_SETTEXT			=	000Ch
WM_GETTEXT			=	000Dh
WM_GETTEXTLENGTH		=	000Eh
WM_PAINT			=	000Fh
WM_CLOSE			=	0010h
WM_QUERYENDSESSION		=	0011h
WM_QUIT 			=	0012h
WM_QUERYOPEN			=	0013h
WM_ERASEBKGND			=	0014h
WM_SYSCOLORCHANGE		=	0015h
WM_ENDSESSION			=	0016h
WM_SHOWWINDOW			=	0018h
WM_WININICHANGE 		=	001Ah

WM_SETTINGCHANGE		=	WM_WININICHANGE
WM_DEVMODECHANGE		=	001Bh
WM_ACTIVATEAPP			=	001Ch
WM_FONTCHANGE			=	001Dh
WM_TIMECHANGE			=	001Eh
WM_CANCELMODE			=	001Fh
WM_SETCURSOR			=	0020h
WM_MOUSEACTIVATE		=	0021h
WM_CHILDACTIVATE		=	0022h
WM_QUEUESYNC			=	0023h

WM_GETMINMAXINFO		=	0024h

WM_DEVICECHANGE 		=	0219h

WM_MDICREATE			=	0220h
WM_MDIDESTROY			=	0221h
WM_MDIACTIVATE			=	0222h
WM_MDIRESTORE			=	0223h
WM_MDINEXT			=	0224h
WM_MDIMAXIMIZE			=	0225h
WM_MDITILE			=	0226h
WM_MDICASCADE			=	0227h
WM_MDIICONARRANGE		=	0228h
WM_MDIGETACTIVE 		=	0229h

WM_MDISETMENU			=	0230h
WM_ENTERSIZEMOVE		=	0231h
WM_EXITSIZEMOVE 		=	0232h
WM_DROPFILES			=	0233h
WM_MDIREFRESHMENU		=	0234h

WM_IME_SETCONTEXT		=	0281h
WM_IME_NOTIFY			=	0282h
WM_IME_CONTROL			=	0283h
WM_IME_COMPOSITIONFULL		=	0284h
WM_IME_SELECT			=	0285h
WM_IME_CHAR			=	0286h
WM_IME_REQUEST			=	0288h
WM_IME_KEYDOWN			=	0290h
WM_IME_KEYUP			=	0291h

WM_MOUSEHOVER			=	02A1h
WM_MOUSELEAVE			=	02A3h

WM_CUT				=	0300h
WM_COPY 			=	0301h
WM_PASTE			=	0302h
WM_CLEAR			=	0303h
WM_UNDO 			=	0304h
WM_RENDERFORMAT 		=	0305h
WM_RENDERALLFORMATS		=	0306h
WM_DESTROYCLIPBOARD		=	0307h
WM_DRAWCLIPBOARD		=	0308h
WM_PAINTCLIPBOARD		=	0309h
WM_VSCROLLCLIPBOARD		=	030Ah
WM_SIZECLIPBOARD		=	030Bh
WM_ASKCBFORMATNAME		=	030Ch
WM_CHANGECBCHAIN		=	030Dh
WM_HSCROLLCLIPBOARD		=	030Eh
WM_QUERYNEWPALETTE		=	030Fh
WM_PALETTEISCHANGING		=	0310h
WM_PALETTECHANGED		=	0311h
WM_HOTKEY			=	0312h

WM_PRINT			=	0317h
WM_PRINTCLIENT			=	0318h

WM_HANDHELDFIRST		=	0358h
WM_HANDHELDLAST 		=	035Fh

WM_AFXFIRST			=	0360h
WM_AFXLAST			=	037Fh

WM_PENWINFIRST			=	0380h
WM_PENWINLAST			=	038Fh

WM_APP				=	8000h

;; /*
;; * NOTE: All Message Numbers below =    0400 are RESERVED.
;; *
;; * Private Window Messages Start Here:
;; */

WM_USER 			=	0400h



;; /*  wParam for WM_SIZING message  */

WMSZ_LEFT	    =    1
WMSZ_RIGHT	    =    2
WMSZ_TOP	    =    3
WMSZ_TOPLEFT	    =    4
WMSZ_TOPRIGHT	    =    5
WMSZ_BOTTOM	    =    6
WMSZ_BOTTOMLEFT     =    7
WMSZ_BOTTOMRIGHT    =    8

;; /*
;; * WM_NCHITTEST and MOUSEHOOKSTRUCT Mouse Position Codes
;; */

HTERROR 	    =    -2
HTTRANSPARENT	    =    -1
HTNOWHERE	    =    0
HTCLIENT	    =    1
HTCAPTION	    =    2
HTSYSMENU	    =    3
HTGROWBOX	    =    4
HTSIZE		    =    HTGROWBOX
HTMENU		    =    5
HTHSCROLL	    =    6
HTVSCROLL	    =    7
HTMINBUTTON	    =    8
HTMAXBUTTON	    =    9
HTLEFT		    =    10
HTRIGHT 	    =    11
HTTOP		    =    12
HTTOPLEFT	    =    13
HTTOPRIGHT	    =    14
HTBOTTOM	    =    15
HTBOTTOMLEFT	    =    16
HTBOTTOMRIGHT	    =    17
HTBORDER	    =    18
HTREDUCE	    =    HTMINBUTTON
HTZOOM		    =    HTMAXBUTTON
HTSIZEFIRST	    =    HTLEFT
HTSIZELAST	    =    HTBOTTOMRIGHT
HTOBJECT	    =    19
HTCLOSE 	    =    20
HTHELP		    =    21

;; /*
;; * SendMessageTimeout values
;; */

SMTO_NORMAL	    =    0000h
SMTO_BLOCK	    =    0001h
SMTO_ABORTIFHUNG    =    0002h

SMTO_NOTIMEOUTIFNOTHUNG =    0008h

;; /*
;; * WM_MOUSEACTIVATE Return Codes
;; */

MA_ACTIVATE	    =    1
MA_ACTIVATEANDEAT   =    2
MA_NOACTIVATE	    =    3
MA_NOACTIVATEANDEAT =    4

;; /*
;; * WM_SETICON , WM_GETICON Type Codes
;; */

ICON_SMALL	    =    0
ICON_BIG	    =    1

WM_NOTIFY			=    004Eh
WM_INPUTLANGCHANGEREQUEST	=    0050h
WM_INPUTLANGCHANGE		=    0051h
WM_TCARD			=    0052h
WM_HELP 			=    0053h
WM_USERCHANGED			=    0054h
WM_NOTIFYFORMAT 		=    0055h

NFR_ANSI			=    1
NFR_UNICODE			=    2
NF_QUERY			=    3
NF_REQUERY			=    4

WM_CONTEXTMENU			=    007Bh
WM_STYLECHANGING		=    007Ch
WM_STYLECHANGED 		=    007Dh
WM_DISPLAYCHANGE		=    007Eh
WM_GETICON			=    007Fh
WM_SETICON			=    0080h

WM_NCCREATE			=    0081h
WM_NCDESTROY			=    0082h
WM_NCCALCSIZE			=    0083h
WM_NCHITTEST			=    0084h
WM_NCPAINT			=    0085h
WM_NCACTIVATE			=    0086h
WM_GETDLGCODE			=    0087h
WM_SYNCPAINT			=    0088h
WM_NCMOUSEMOVE			=    00A0h
WM_NCLBUTTONDOWN		=    00A1h
WM_NCLBUTTONUP			=    00A2h
WM_NCLBUTTONDBLCLK		=    00A3h
WM_NCRBUTTONDOWN		=    00A4h
WM_NCRBUTTONUP			=    00A5h
WM_NCRBUTTONDBLCLK		=    00A6h
WM_NCMBUTTONDOWN		=    00A7h
WM_NCMBUTTONUP			=    00A8h
WM_NCMBUTTONDBLCLK		=    00A9h

WM_KEYFIRST			=    0100h
WM_KEYDOWN			=    0100h
WM_KEYUP			=    0101h
WM_CHAR 			=    0102h
WM_DEADCHAR			=    0103h
WM_SYSKEYDOWN			=    0104h
WM_SYSKEYUP			=    0105h
WM_SYSCHAR			=    0106h
WM_SYSDEADCHAR			=    0107h
WM_KEYLAST			=    0108h

WM_IME_STARTCOMPOSITION 	=    010Dh
WM_IME_ENDCOMPOSITION		=    010Eh
WM_IME_COMPOSITION		=    010Fh
WM_IME_KEYLAST			=    010Fh

WM_INITDIALOG			=    0110h
WM_COMMAND			=    0111h
WM_SYSCOMMAND			=    0112h
WM_TIMER			=    0113h
WM_HSCROLL			=    0114h
WM_VSCROLL			=    0115h
WM_INITMENU			=    0116h
WM_INITMENUPOPUP		=    0117h
WM_MENUSELECT			=    011Fh
WM_MENUCHAR			=    0120h
WM_ENTERIDLE			=    0121h

WM_MENURBUTTONUP		=    0122h
WM_MENUDRAG			=    0123h
WM_MENUGETOBJECT		=    0124h
WM_UNINITMENUPOPUP		=    0125h
WM_MENUCOMMAND			=    0126h

WM_CTLCOLORMSGBOX		=    0132h
WM_CTLCOLOREDIT 		=    0133h
WM_CTLCOLORLISTBOX		=    0134h
WM_CTLCOLORBTN			=    0135h
WM_CTLCOLORDLG			=    0136h
WM_CTLCOLORSCROLLBAR		=    0137h
WM_CTLCOLORSTATIC		=    0138h

WM_MOUSEFIRST			=    0200h
WM_MOUSEMOVE			=    0200h
WM_LBUTTONDOWN			=    0201h
WM_LBUTTONUP			=    0202h
WM_LBUTTONDBLCLK		=    0203h
WM_RBUTTONDOWN			=    0204h
WM_RBUTTONUP			=    0205h
WM_RBUTTONDBLCLK		=    0206h
WM_MBUTTONDOWN			=    0207h
WM_MBUTTONUP			=    0208h
WM_MBUTTONDBLCLK		=    0209h

WM_MOUSEWHEEL			=    020Ah
WM_MOUSELAST			=    020Ah

;; WM_MOUSELAST                  =    0209h 

;;comment @ ---------------------------------------------
;;
;; #if (_WIN32_WINNT >= 0400h) || (_WIN32_WINDOWS > 0400h)
;;  WM_MOUSEWHEEL                   020Ah
;;  WM_MOUSELAST                    020Ah
;; #else
;;  WM_MOUSELAST                    0209h
;; #endif /* if (_WIN32_WINNT < 0400h) */
;;
;; ------------------------------------------------------@


;; WHEEL_DELTA                     120      ;/* Value for rolling one detent */
;; WHEEL_PAGESCROLL                UINT_MAX ;/* Scroll one page */

WM_PARENTNOTIFY 		=    0210h
WM_ENTERMENULOOP		=    0211h
WM_EXITMENULOOP 		=    0212h

WM_NEXTMENU			=    0213h

WM_SIZING			=    0214h
WM_CAPTURECHANGED		=    0215h
WM_MOVING			=    0216h

;-----------------------------------------------------------------------------------
; MessageBox() Flags


MB_OK			    =    00000000h
MB_OKCANCEL		    =    00000001h
MB_ABORTRETRYIGNORE	    =    00000002h
MB_YESNOCANCEL		    =    00000003h
MB_YESNO		    =    00000004h
MB_RETRYCANCEL		    =    00000005h

MB_ICONHAND		    =    00000010h
MB_ICONQUESTION 	    =    00000020h
MB_ICONEXCLAMATION	    =    00000030h
MB_ICONASTERISK 	    =    00000040h

MB_USERICON		    =    00000080h
MB_ICONWARNING		    =    MB_ICONEXCLAMATION
MB_ICONERROR		    =    MB_ICONHAND

MB_ICONINFORMATION	    =    MB_ICONASTERISK
MB_ICONSTOP		    =    MB_ICONHAND

MB_DEFBUTTON1		    =    00000000h
MB_DEFBUTTON2		    =    00000100h
MB_DEFBUTTON3		    =    00000200h

MB_DEFBUTTON4		    =    00000300h

MB_APPLMODAL		    =    00000000h
MB_SYSTEMMODAL		    =    00001000h
MB_TASKMODAL		    =    00002000h

MB_HELP 		    =    00004000h ;; // Help Button

MB_NOFOCUS		    =    00008000h
MB_SETFOREGROUND	    =    00010000h
MB_DEFAULT_DESKTOP_ONLY     =    00020000h

MB_TOPMOST		    =    00040000h
MB_RIGHT		    =    00080000h
MB_RTLREADING		    =    00100000h

MB_SERVICE_NOTIFICATION     =    00200000h

;; MB_SERVICE_NOTIFICATION          =    00040000h

;;comment @-----------------------------------

;; #ifdef _WIN32_WINNT
;; #if (_WIN32_WINNT >= 0400h)
;;  MB_SERVICE_NOTIFICATION          00200000h
;; #else
;;  MB_SERVICE_NOTIFICATION          00040000h
;; #endif
;;  MB_SERVICE_NOTIFICATION_NT3X     00040000h
;; #endif

;; -----------------------------------@
MB_SERVICE_NOTIFICATION_NT3X	 = 00040000h

MB_TYPEMASK		    =    0000000Fh
MB_ICONMASK		    =    000000F0h
MB_DEFMASK		    =    00000F00h
MB_MODEMASK		    =    00003000h
MB_MISCMASK		    =    0000C000h


;------------------------------------------------------------------
; From windows.inc by Hutch

BN_CLICKED			     = 0
BN_PAINT			     = 1
BN_HILITE			     = 2
BN_UNHILITE			     = 3
BN_DISABLE			     = 4
BN_DOUBLECLICKED		     = 5
BN_SETFOCUS			     = 6
BN_KILLFOCUS			     = 7
BN_PUSHED				  = BN_HILITE
BN_UNPUSHED				  = BN_UNHILITE
BN_DBLCLK				  = BN_DOUBLECLICKED


;----------------------------------------------------------------------
; Virtual Keys, Standard Set


VK_LBUTTON	  =  01h
VK_RBUTTON	  =  02h
VK_CANCEL	  =  03h
VK_MBUTTON	  =  04h   ;/* NOT contiguous with L & RBUTTON */

VK_BACK 	  =  08h
VK_TAB		  =  09h

VK_CLEAR	  =  0Ch
VK_RETURN	  =  0Dh

VK_SHIFT	  =  10h
VK_CONTROL	  =  11h
VK_MENU 	  =  12h
VK_PAUSE	  =  13h
VK_CAPITAL	  =  14h

VK_KANA 	  =  15h
VK_HANGEUL	  =  15h   ;/* old name - should be here for compatibility */
VK_HANGUL	  =  15h
VK_JUNJA	  =  17h
VK_FINAL	  =  18h
VK_HANJA	  =  19h
VK_KANJI	  =  19h

VK_ESCAPE	  =  1Bh

VK_CONVERT	  =  1Ch
VK_NONCONVERT	  =  1Dh
VK_ACCEPT	  =  1Eh
VK_MODECHANGE	  =  1Fh

VK_SPACE	  =  20h
VK_PRIOR	  =  21h
VK_NEXT 	  =  22h
VK_END		  =  23h
VK_HOME 	  =  24h
VK_LEFT 	  =  25h
VK_UP		  =  26h
VK_RIGHT	  =  27h
VK_DOWN 	  =  28h
VK_SELECT	  =  29h
VK_PRINT	  =  2Ah
VK_EXECUTE	  =  2Bh
VK_SNAPSHOT	  =  2Ch
VK_INSERT	  =  2Dh
VK_DELETE	  =  2Eh
VK_HELP 	  =  2Fh

;; /* VK_0 thru VK_9 are the same as ASCII '0' thru '9' (equ    30 - =    39) */
;; /* VK_A thru VK_Z are the same as ASCII 'A' thru 'Z' (equ    41 - =    5A) */

VK_0		=	30h
VK_1		=	31h
VK_2		=	32h
VK_3		=	33h
VK_4		=	34h
VK_5		=	35h
VK_6		=	36h
VK_7		=	37h
VK_8		=	38h
VK_9		=	39h

VK_A		=	41h
VK_B		=	42h
VK_C		=	43h
VK_D		=	44h
VK_E		=	45h
VK_F		=	46h
VK_G		=	47h
VK_H		=	48h
VK_I		=	49h
VK_J		=	4Ah
VK_K		=	4Bh
VK_L		=	4Ch
VK_M		=	4Dh
VK_N		=	4Eh
VK_O		=	4Fh
VK_P		=	50h
VK_Q		=	51h
VK_R		=	52h
VK_S		=	53h
VK_T		=	54h
VK_U		=	55h
VK_V		=	56h
VK_W		=	57h
VK_X		=	58h
VK_Y		=	59h
VK_Z		=	5Ah

VK_LWIN 	  =  5Bh
VK_RWIN 	  =  5Ch
VK_APPS 	  =  5Dh

VK_NUMPAD0	  =  60h
VK_NUMPAD1	  =  61h
VK_NUMPAD2	  =  62h
VK_NUMPAD3	  =  63h
VK_NUMPAD4	  =  64h
VK_NUMPAD5	  =  65h
VK_NUMPAD6	  =  66h
VK_NUMPAD7	  =  67h
VK_NUMPAD8	  =  68h
VK_NUMPAD9	  =  69h
VK_MULTIPLY	  =  6Ah
VK_ADD		  =  6Bh
VK_SEPARATOR	  =  6Ch
VK_SUBTRACT	  =  6Dh
VK_DECIMAL	  =  6Eh
VK_DIVIDE	  =  6Fh
VK_F1		  =  70h
VK_F2		  =  71h
VK_F3		  =  72h
VK_F4		  =  73h
VK_F5		  =  74h
VK_F6		  =  75h
VK_F7		  =  76h
VK_F8		  =  77h
VK_F9		  =  78h
VK_F10		  =  79h
VK_F11		  =  7Ah
VK_F12		  =  7Bh
VK_F13		  =  7Ch
VK_F14		  =  7Dh
VK_F15		  =  7Eh
VK_F16		  =  7Fh
VK_F17		  =  80h
VK_F18		  =  81h
VK_F19		  =  82h
VK_F20		  =  83h
VK_F21		  =  84h
VK_F22		  =  85h
VK_F23		  =  86h
VK_F24		  =  87h

VK_NUMLOCK	  =  90h
VK_SCROLL	  =  91h

;;comment /*
;; * VK_L* & VK_R* - left and right Alt, Ctrl and Shift virtual keys.
;; * Used only as parameters to GetAsyncKeyState() and GetKeyState().
;; * No other API or message will distinguish left and right keys in this way.
;; */

VK_LSHIFT	  =  0A0h
VK_RSHIFT	  =  0A1h
VK_LCONTROL	  =  0A2h
VK_RCONTROL	  =  0A3h
VK_LMENU	  =  0A4h
VK_RMENU	  =  0A5h
VK_PROCESSKEY	  =  0E5h
VK_ATTN 	  =  0F6h
VK_CRSEL	  =  0F7h
VK_EXSEL	  =  0F8h
VK_EREOF	  =  0F9h
VK_PLAY 	  =  0FAh
VK_ZOOM 	  =  0FBh
VK_NONAME	  =  0FCh
VK_PA1		  =  0FDh
VK_OEM_CLEAR	  =  0FEh

;; comment /*
;;  * DrawText() Format Flags
;;  */
DT_TOP		    = 	 00000000h
DT_LEFT 	    = 	 00000000h
DT_CENTER	    = 	 00000001h
DT_RIGHT	    = 	 00000002h
DT_VCENTER	    = 	 00000004h
DT_BOTTOM	    = 	 00000008h
DT_WORDBREAK	    = 	 00000010h
DT_SINGLELINE	    = 	 00000020h
DT_EXPANDTABS	    = 	 00000040h
DT_TABSTOP	    = 	 00000080h
DT_NOCLIP	    = 	 00000100h
DT_EXTERNALLEADING  = 	 00000200h
DT_CALCRECT	    = 	 00000400h
DT_NOPREFIX	    = 	 00000800h
DT_INTERNAL	    = 	 00001000h

;; #if(WINVER >= =          0400)
DT_EDITCONTROL	    = 	 00002000h
DT_PATH_ELLIPSIS    = 	 00004000h
DT_END_ELLIPSIS     = 	 00008000h
DT_MODIFYSTRING     = 	 00010000h
DT_RTLREADING	    = 	 00020000h
DT_WORD_ELLIPSIS    = 	 00040000h

;;-------------------------------------------------------
;; /* Pen Styles */

PS_SOLID	    = 	0
PS_DASH 	    = 	1      ;; /* -------  */
PS_DOT		    = 	2      ;; /* .......  */
PS_DASHDOT	    = 	3      ;; /* _._._._  */
PS_DASHDOTDOT	    = 	4      ;; /* _.._.._  */
PS_NULL 	    = 	5
PS_INSIDEFRAME	    = 	6
PS_USERSTYLE	    = 	7
PS_ALTERNATE	    = 	8
PS_STYLE_MASK	    =      0000000Fh

PS_ENDCAP_ROUND     =      00000000h
PS_ENDCAP_SQUARE    =      00000100h
PS_ENDCAP_FLAT	    =      00000200h
PS_ENDCAP_MASK	    =      00000F00h

PS_JOIN_ROUND	    =      00000000h
PS_JOIN_BEVEL	    =      00001000h
PS_JOIN_MITER	    =      00002000h
PS_JOIN_MASK	    =      0000F000h

PS_COSMETIC	    =      00000000h
PS_GEOMETRIC	    =      00010000h
PS_TYPE_MASK	    =      000F0000h

AD_COUNTERCLOCKWISE	=	1
AD_CLOCKWISE		=	2


;;--------------------------------------------------------------------------------------
;; /* Ternary raster operations */

 SRCCOPY	     =      00CC0020h ; /* dest = source                   */
 SRCPAINT	     =      00EE0086h ; /* dest = source OR dest           */
 SRCAND 	     =      008800C6h ; /* dest = source AND dest          */
 SRCINVERT	     =      00660046h ; /* dest = source XOR dest          */
 SRCERASE	     =      00440328h ; /* dest = source AND (NOT dest )   */
 NOTSRCCOPY	     =      00330008h ; /* dest = (NOT source)             */
 NOTSRCERASE	     =      001100A6h ; /* dest = (NOT src) AND (NOT dest) */
 MERGECOPY	     =      00C000CAh ; /* dest = (source AND pattern)     */
 MERGEPAINT	     =      00BB0226h ; /* dest = (NOT source) OR dest     */
 PATCOPY	     =      00F00021h ; /* dest = pattern                  */
 PATPAINT	     =      00FB0A09h ; /* dest = DPSnoo                   */
 PATINVERT	     =      005A0049h ; /* dest = pattern XOR dest         */
 DSTINVERT	     =      00550009h ; /* dest = (NOT dest)               */
 BLACKNESS	     =      00000042h ; /* dest = BLACK                    */
 WHITENESS	     =      00FF0062h ; /* dest = WHITE                    */

;;----------------------------------------------------------------------------------------
;; /* Quaternary raster codes */

;  MAKEROP4(fore,back) (DWORD)((((back) << 8) & 0xFF000000) | (fore)) ????????????


GDI_ERROR		=		0FFFFFFFFh
HGDI_ERROR		=		0FFFFFFFFh

;; /* Region Flags */

 ERROR		     = 	0
 NULLREGION	     = 	1
 SIMPLEREGION	     = 	2
 COMPLEXREGION	     = 	3
 RGN_ERROR	     = 	ERROR


;; /* CombineRgn() Styles */

 RGN_AND	     = 	1
 RGN_OR 	     = 	2
 RGN_XOR	     = 	3
 RGN_DIFF	     = 	4
 RGN_COPY	     = 	5
 RGN_MIN	     = 	RGN_AND
 RGN_MAX	     = 	RGN_COPY

;; /* StretchBlt() Modes */

BLACKONWHITE		     = 	1
WHITEONBLACK		     = 	2
COLORONCOLOR		     = 	3
HALFTONE		     = 	4
MAXSTRETCHBLTMODE	     = 	4

;; comment @***********************************************
;; #if(WINVER >= 0x0400)
;; /* New StretchBlt() Modes */
;;  STRETCH_ANDSCANS    BLACKONWHITE
;;  STRETCH_ORSCANS     WHITEONBLACK
;;  STRETCH_DELETESCANS COLORONCOLOR
;;  STRETCH_HALFTONE    HALFTONE
;; #endif /* WINVER >= 0x0400 */
;; ********************************************************@

;; /* PolyFill() Modes */

ALTERNATE		     = 	1
WINDING 		     = 	2
POLYFILL_LAST		     = 	2

;; /* Text Alignment Options */

TA_NOUPDATECP		     = 	0
TA_UPDATECP		     = 	1

TA_LEFT 		     = 	0
TA_RIGHT		     = 	2
TA_CENTER		     = 	6
TA_TOP			     = 	0
TA_BOTTOM		     = 	8
TA_BASELINE		     = 	24

;; comment @**********************************************************
;; #if (WINVER >= 0x0400)
;;  TA_RTLREADING                256
;;  TA_MASK       (TA_BASELINE+TA_CENTER+TA_UPDATECP+TA_RTLREADING)
;; #else
;;  TA_MASK       (TA_BASELINE+TA_CENTER+TA_UPDATECP)
;; #endif
;; *******************************************************************@

VTA_BASELINE	=		TA_BASELINE
VTA_LEFT	=		TA_BOTTOM
VTA_RIGHT	=		TA_TOP
VTA_CENTER	=		TA_CENTER
VTA_BOTTOM	=		TA_RIGHT
VTA_TOP 	=		TA_LEFT

ETO_OPAQUE		     = 	0002h
ETO_CLIPPED		     = 	0004h

;; comment @*********************************************************
;; #if(WINVER >= 0x0400)
;;  ETO_GLYPH_INDEX              0x0010
;;  ETO_RTLREADING               0x0080
;;  ETO_NUMERICSLOCAL            0x0400
;;  ETO_NUMERICSLATIN            0x0800
;;  ETO_IGNORELANGUAGE           0x1000
;; #endif /* WINVER >= 0x0400 */
;; #if (_WIN32_WINNT >= 0x0500)
;;  ETO_PDY                      0x2000
;; #endif // (_WIN32_WINNT >= 0x0500)
;; ******************************************************************@
ASPECT_FILTERING	     = 	0001h


DLL_PROCESS_ATTACH	=	1
DLL_THREAD_ATTACH	=	2
DLL_THREAD_DETACH	=	3
DLL_PROCESS_DETACH	=	0


;; comment /*
;; * SetWindowsHook() codes
;; */
WH_MIN			=	-1
WH_MSGFILTER		=	-1
WH_JOURNALRECORD	=	0
WH_JOURNALPLAYBACK	=	1
WH_KEYBOARD		=	2
WH_GETMESSAGE		=	3
WH_CALLWNDPROC		=	4
WH_CBT			=	5
WH_SYSMSGFILTER 	=	6
WH_MOUSE		=	7
WH_HARDWARE		=	8
WH_DEBUG		=	9
WH_SHELL		=	10
WH_FOREGROUNDIDLE	=	11
WH_CALLWNDPROCRET	=	12

WH_KEYBOARD_LL		=	13
WH_MOUSE_LL		=	14

WH_MAX			=	14

;; comment %====================================
;; #if(WINVER >= 0x0400)
;; #if (_WIN32_WINNT >= 0x0400)
;; #define WH_MAX             14
;; #else
;; #define WH_MAX             12
;; #endif // (_WIN32_WINNT >= 0x0400)
;; #else
;; #define WH_MAX             11
;; #endif
;; ============================================%

WH_MINHOOK		=	WH_MIN
WH_MAXHOOK		=	WH_MAX

;; comment/*
;;  * Hook Codes
;;  */
HC_ACTION		=	0
HC_GETNEXT		=	1
HC_SKIP 		=	2
HC_NOREMOVE		=	3
HC_NOREM		=	HC_NOREMOVE
HC_SYSMODALON		=	4
HC_SYSMODALOFF		=	5

;; comment/*
;; * CBT Hook Codes
;; */
HCBT_MOVESIZE		=	0
HCBT_MINMAX		=	1
HCBT_QS 		=	2
HCBT_CREATEWND		=	3
HCBT_DESTROYWND 	=	4
HCBT_ACTIVATE		=	5
HCBT_CLICKSKIPPED	=	6
HCBT_KEYSKIPPED 	=	7
HCBT_SYSCOMMAND 	=	8
HCBT_SETFOCUS		=	9



;; /* ShellExecute() and ShellExecuteEx() error codes */

;; /* regular WinExec() codes */

SE_ERR_FNF			=	2	;// file not found
SE_ERR_PNF			=	3	;// path not found
SE_ERR_ACCESSDENIED		=	5	;// access denied
SE_ERR_OOM			=	8	;// out of memory
SE_ERR_DLLNOTFOUND		=	32

;; /* error values for ShellExecute() beyond the regular WinExec() codes */
SE_ERR_SHARE			=	26
SE_ERR_ASSOCINCOMPLETE		=	27
SE_ERR_DDETIMEOUT		=	28
SE_ERR_DDEFAIL			=	29
SE_ERR_DDEBUSY			=	30
SE_ERR_NOASSOC			=	31

;; // Note CLASSKEY overrides CLASSNAME
SEE_MASK_CLASSNAME		=	00000001h
SEE_MASK_CLASSKEY		=	00000003h

;; // Note INVOKEIDLIST overrides IDLIST
SEE_MASK_IDLIST 		=	00000004h
SEE_MASK_INVOKEIDLIST		=	0000000ch
SEE_MASK_ICON			=	00000010h
SEE_MASK_HOTKEY 		=	00000020h
SEE_MASK_NOCLOSEPROCESS 	=	00000040h
SEE_MASK_CONNECTNETDRV		=	00000080h
SEE_MASK_FLAG_DDEWAIT		=	00000100h
SEE_MASK_DOENVSUBST		=	00000200h
SEE_MASK_FLAG_NO_UI		=	00000400h
SEE_MASK_UNICODE		=	00004000h
SEE_MASK_NO_CONSOLE		=	00008000h
SEE_MASK_ASYNCOK		=	00100000h
SEE_MASK_HMONITOR		=	00200000h

PFD_DOUBLEBUFFER	    =     00000001h
PFD_STEREO		    = 	00000002h
PFD_DRAW_TO_WINDOW	    = 	00000004h
PFD_DRAW_TO_BITMAP	    = 	00000008h
PFD_SUPPORT_GDI 	    = 	    00000010h
PFD_SUPPORT_OPENGL	    = 	    00000020h
PFD_GENERIC_FORMAT	    = 	    00000040h
PFD_NEED_PALETTE	    = 	    00000080h
PFD_NEED_SYSTEM_PALETTE     = 	    00000100h
PFD_SWAP_EXCHANGE	    = 	00000200h
PFD_SWAP_COPY		    = 	    00000400h
PFD_SWAP_LAYER_BUFFERS	    = 	00000800h
PFD_GENERIC_ACCELERATED     = 	    00001000h
PFD_SUPPORT_DIRECTDRAW	    = 	    00002000h

;; /* PIXELFORMATDESCRIPTOR flags for use in ChoosePixelFormat only */
PFD_DEPTH_DONTCARE	    = 	20000000h
PFD_DOUBLEBUFFER_DONTCARE   = 	40000000h
PFD_STEREO_DONTCARE	    = 	80000000h

;; /* pixel types */
PFD_TYPE_RGBA	     =     0
PFD_TYPE_COLORINDEX  = 1

;;  /* layer types */
PFD_MAIN_PLANE	     =     0
PFD_OVERLAY_PLANE    =     1
PFD_UNDERLAY_PLANE   =      -1

struct COORD
    x dw ?
    y dw ?
ends