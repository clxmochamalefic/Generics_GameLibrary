#ifndef Ggl_Keys_H
#define Ggl_Keys_H

/*
 * Virtual Keys, Standard Set
 */
#define GIK_LBUTTON        0x01
#define GIK_RBUTTON        0x02
#define GIK_CANCEL         0x03
#define GIK_MBUTTON        0x04    /* NOT contiguous with L & RBUTTON */

#if(_WIN32_WINNT >= 0x0500)
#define GIK_XBUTTON1       0x05    /* NOT contiguous with L & RBUTTON */
#define GIK_XBUTTON2       0x06    /* NOT contiguous with L & RBUTTON */
#endif /* _WIN32_WINNT >= 0x0500 */

/*
 * 0x07 : unassigned
 */

#define GIK_BACK           0x08
#define GIK_TAB            0x09

/*
 * 0x0A - 0x0B : reserved
 */

#define GIK_CLEAR          0x0C
#define GIK_RETURN         0x0D

#define GIK_SHIFT          0x10
#define GIK_CONTROL        0x11
#define GIK_MENU           0x12
#define GIK_PAUSE          0x13
#define GIK_CAPITAL        0x14

#define GIK_KANA           0x15
#define GIK_HANGEUL        0x15  /* old name - should be here for compatibility */
#define GIK_HANGUL         0x15
#define GIK_JUNJA          0x17
#define GIK_FINAL          0x18
#define GIK_HANJA          0x19
#define GIK_KANJI          0x19

#define GIK_ESCAPE         0x1B

#define GIK_CONVERT        0x1C
#define GIK_NONCONVERT     0x1D
#define GIK_ACCEPT         0x1E
#define GIK_MODECHANGE     0x1F

#define GIK_SPACE          0x20
#define GIK_PRIOR          0x21
#define GIK_NEXT           0x22
#define GIK_END            0x23
#define GIK_HOME           0x24
#define GIK_LEFT           0x25
#define GIK_UP             0x26
#define GIK_RIGHT          0x27
#define GIK_DOWN           0x28
#define GIK_SELECT         0x29
#define GIK_PRINT          0x2A
#define GIK_EXECUTE        0x2B
#define GIK_SNAPSHOT       0x2C
#define GIK_INSERT         0x2D
#define GIK_DELETE         0x2E
#define GIK_HELP           0x2F

/*
 * GIK_0 - GIK_9 are the same as ASCII '0' - '9' (0x30 - 0x39)
 * 0x40 : unassigned
 * GIK_A - GIK_Z are the same as ASCII 'A' - 'Z' (0x41 - 0x5A)
 */

#define GIK_LWIN           0x5B
#define GIK_RWIN           0x5C
#define GIK_APPS           0x5D

/*
 * 0x5E : reserved
 */

#define GIK_SLEEP          0x5F

#define GIK_NUMPAD0        0x60
#define GIK_NUMPAD1        0x61
#define GIK_NUMPAD2        0x62
#define GIK_NUMPAD3        0x63
#define GIK_NUMPAD4        0x64
#define GIK_NUMPAD5        0x65
#define GIK_NUMPAD6        0x66
#define GIK_NUMPAD7        0x67
#define GIK_NUMPAD8        0x68
#define GIK_NUMPAD9        0x69
#define GIK_MULTIPLY       0x6A
#define GIK_ADD            0x6B
#define GIK_SEPARATOR      0x6C
#define GIK_SUBTRACT       0x6D
#define GIK_DECIMAL        0x6E
#define GIK_DIVIDE         0x6F
#define GIK_F1             0x70
#define GIK_F2             0x71
#define GIK_F3             0x72
#define GIK_F4             0x73
#define GIK_F5             0x74
#define GIK_F6             0x75
#define GIK_F7             0x76
#define GIK_F8             0x77
#define GIK_F9             0x78
#define GIK_F10            0x79
#define GIK_F11            0x7A
#define GIK_F12            0x7B
#define GIK_F13            0x7C
#define GIK_F14            0x7D
#define GIK_F15            0x7E
#define GIK_F16            0x7F
#define GIK_F17            0x80
#define GIK_F18            0x81
#define GIK_F19            0x82
#define GIK_F20            0x83
#define GIK_F21            0x84
#define GIK_F22            0x85
#define GIK_F23            0x86
#define GIK_F24            0x87

/*
 * 0x88 - 0x8F : unassigned
 */

#define GIK_NUMLOCK        0x90
#define GIK_SCROLL         0x91

/*
 * NEC PC-9800 kbd definitions
 */
#define GIK_OEM_NEC_EQUAL  0x92   // '=' key on numpad

/*
 * Fujitsu/OASYS kbd definitions
 */
#define GIK_OEM_FJ_JISHO   0x92   // 'Dictionary' key
#define GIK_OEM_FJ_MASSHOU 0x93   // 'Unregister word' key
#define GIK_OEM_FJ_TOUROKU 0x94   // 'Register word' key
#define GIK_OEM_FJ_LOYA    0x95   // 'Left OYAYUBI' key
#define GIK_OEM_FJ_ROYA    0x96   // 'Right OYAYUBI' key

/*
 * 0x97 - 0x9F : unassigned
 */

/*
 * GIK_L* & GIK_R* - left and right Alt, Ctrl and Shift virtual keys.
 * Used only as parameters to GetAsyncKeyState() and GetKeyState().
 * No other API or message will distinguish left and right keys in this way.
 */
#define GIK_LSHIFT         0xA0
#define GIK_RSHIFT         0xA1
#define GIK_LCONTROL       0xA2
#define GIK_RCONTROL       0xA3
#define GIK_LMENU          0xA4
#define GIK_RMENU          0xA5

#if(_WIN32_WINNT >= 0x0500)
#define GIK_BROWSER_BACK        0xA6
#define GIK_BROWSER_FORWARD     0xA7
#define GIK_BROWSER_REFRESH     0xA8
#define GIK_BROWSER_STOP        0xA9
#define GIK_BROWSER_SEARCH      0xAA
#define GIK_BROWSER_FAVORITES   0xAB
#define GIK_BROWSER_HOME        0xAC

#define GIK_VOLUME_MUTE         0xAD
#define GIK_VOLUME_DOWN         0xAE
#define GIK_VOLUME_UP           0xAF
#define GIK_MEDIA_NEXT_TRACK    0xB0
#define GIK_MEDIA_PREV_TRACK    0xB1
#define GIK_MEDIA_STOP          0xB2
#define GIK_MEDIA_PLAY_PAUSE    0xB3
#define GIK_LAUNCH_MAIL         0xB4
#define GIK_LAUNCH_MEDIA_SELECT 0xB5
#define GIK_LAUNCH_APP1         0xB6
#define GIK_LAUNCH_APP2         0xB7

#endif /* _WIN32_WINNT >= 0x0500 */

/*
 * 0xB8 - 0xB9 : reserved
 */

#define GIK_OEM_1          0xBA   // ';:' for US
#define GIK_OEM_PLUS       0xBB   // '+' any country
#define GIK_OEM_COMMA      0xBC   // ',' any country
#define GIK_OEM_MINUS      0xBD   // '-' any country
#define GIK_OEM_PERIOD     0xBE   // '.' any country
#define GIK_OEM_2          0xBF   // '/?' for US
#define GIK_OEM_3          0xC0   // '`~' for US

/*
 * 0xC1 - 0xD7 : reserved
 */

/*
 * 0xD8 - 0xDA : unassigned
 */

#define GIK_OEM_4          0xDB  //  '[{' for US
#define GIK_OEM_5          0xDC  //  '\|' for US
#define GIK_OEM_6          0xDD  //  ']}' for US
#define GIK_OEM_7          0xDE  //  ''"' for US
#define GIK_OEM_8          0xDF

/*
 * 0xE0 : reserved
 */

/*
 * Various extended or enhanced keyboards
 */
#define GIK_OEM_AX         0xE1  //  'AX' key on Japanese AX kbd
#define GIK_OEM_102        0xE2  //  "<>" or "\|" on RT 102-key kbd.
#define GIK_ICO_HELP       0xE3  //  Help key on ICO
#define GIK_ICO_00         0xE4  //  00 key on ICO

#if(WINVER >= 0x0400)
#define GIK_PROCESSKEY     0xE5
#endif /* WINVER >= 0x0400 */

#define GIK_ICO_CLEAR      0xE6


#if(_WIN32_WINNT >= 0x0500)
#define GIK_PACKET         0xE7
#endif /* _WIN32_WINNT >= 0x0500 */

/*
 * 0xE8 : unassigned
 */

/*
 * Nokia/Ericsson definitions
 */
#define GIK_OEM_RESET      0xE9
#define GIK_OEM_JUMP       0xEA
#define GIK_OEM_PA1        0xEB
#define GIK_OEM_PA2        0xEC
#define GIK_OEM_PA3        0xED
#define GIK_OEM_WSCTRL     0xEE
#define GIK_OEM_CUSEL      0xEF
#define GIK_OEM_ATTN       0xF0
#define GIK_OEM_FINISH     0xF1
#define GIK_OEM_COPY       0xF2
#define GIK_OEM_AUTO       0xF3
#define GIK_OEM_ENLW       0xF4
#define GIK_OEM_BACKTAB    0xF5

#define GIK_ATTN           0xF6
#define GIK_CRSEL          0xF7
#define GIK_EXSEL          0xF8
#define GIK_EREOF          0xF9
#define GIK_PLAY           0xFA
#define GIK_ZOOM           0xFB
#define GIK_NONAME         0xFC
#define GIK_PA1            0xFD
#define GIK_OEM_CLEAR      0xFE


/*
 * 普通のアルファベットや数字も定数化
 */
#define GIK_0			'0'
#define GIK_1			'1'
#define GIK_2			'2'
#define GIK_3			'3'
#define GIK_4			'4'
#define GIK_5			'5'
#define GIK_6			'6'
#define GIK_7			'7'
#define GIK_8			'8'
#define GIK_9			'9'

#define GIK_A			'A'
#define GIK_B			'B'
#define GIK_C			'C'
#define GIK_D			'D'
#define GIK_E			'E'
#define GIK_F			'F'
#define GIK_G			'G'
#define GIK_H			'H'
#define GIK_I			'I'
#define GIK_J			'J'
#define	GIK_K			'K'
#define	GIK_L			'L'
#define GIK_M			'M'
#define GIK_N			'N'
#define GIK_O			'O'
#define GIK_P			'P'
#define GIK_Q			'Q'
#define GIK_R			'R'
#define GIK_S			'S'
#define GIK_T			'T'
#define GIK_U			'U'
#define GIK_V			'V'
#define GIK_W			'W'
#define GIK_X			'X'
#define GIK_Y			'Y'
#define GIK_Z			'Z'


#endif