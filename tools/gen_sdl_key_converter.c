/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *   Mupen64plus - gen_sdl_key_converter.c                                 *
 *   Mupen64Plus homepage: http://code.google.com/p/mupen64plus/           *
 *   Copyright (C) 2013 Mupen64plus development team                       *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* gcc -E `sdl2-config --cflags --libs` `sdl-config --cflags --libs` gen_sdl_key_converter.c -o gen_sdl_key_converter */

#include <SDL_keysym.h>
#include <SDL_scancode.h>
#include <inttypes.h>
#include <stdint.h>

struct keycode2scancode {
    const char *keysym_name;
    uint32_t keysym;
    const char *scancode_name;
    uint32_t scancode;
};

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))
#define _XSTR(x) #x
#define KEYSYM2SCANCODE(k, s) { \
        .keysym_name = _XSTR(SDLK_##k), \
        .keysym = SDLK_##k, \
        .scancode_name = _XSTR(SDL_SCANCODE_##s), \
        .scancode = SDL_SCANCODE_##s, \
    }

/* Table from SDL 1.2.5 to SDL2 2.0-rc1 */
static const struct keycode2scancode keycode2scancode[] = {
    KEYSYM2SCANCODE(BACKSPACE, BACKSPACE),
    KEYSYM2SCANCODE(TAB, TAB),
    KEYSYM2SCANCODE(CLEAR, CLEAR),
    KEYSYM2SCANCODE(RETURN, RETURN),
    KEYSYM2SCANCODE(PAUSE, PAUSE),
    KEYSYM2SCANCODE(ESCAPE, ESCAPE),
    KEYSYM2SCANCODE(SPACE, SPACE),
    KEYSYM2SCANCODE(EXCLAIM, UNKNOWN),
    KEYSYM2SCANCODE(QUOTEDBL, UNKNOWN),
    KEYSYM2SCANCODE(HASH, UNKNOWN),
    KEYSYM2SCANCODE(DOLLAR, UNKNOWN),
    KEYSYM2SCANCODE(AMPERSAND, UNKNOWN),
    KEYSYM2SCANCODE(QUOTE, UNKNOWN),
    KEYSYM2SCANCODE(LEFTPAREN, UNKNOWN),
    KEYSYM2SCANCODE(RIGHTPAREN, UNKNOWN),
    KEYSYM2SCANCODE(ASTERISK, UNKNOWN),
    KEYSYM2SCANCODE(PLUS, UNKNOWN),
    KEYSYM2SCANCODE(COMMA, COMMA),
    KEYSYM2SCANCODE(MINUS, MINUS),
    KEYSYM2SCANCODE(PERIOD, PERIOD),
    KEYSYM2SCANCODE(SLASH, SLASH),
    KEYSYM2SCANCODE(0, 0),
    KEYSYM2SCANCODE(1, 1),
    KEYSYM2SCANCODE(2, 2),
    KEYSYM2SCANCODE(3, 3),
    KEYSYM2SCANCODE(4, 4),
    KEYSYM2SCANCODE(5, 5),
    KEYSYM2SCANCODE(6, 6),
    KEYSYM2SCANCODE(7, 7),
    KEYSYM2SCANCODE(8, 8),
    KEYSYM2SCANCODE(9, 9),
    KEYSYM2SCANCODE(COLON, UNKNOWN),
    KEYSYM2SCANCODE(SEMICOLON, SEMICOLON),
    KEYSYM2SCANCODE(LESS, UNKNOWN),
    KEYSYM2SCANCODE(EQUALS, EQUALS),
    KEYSYM2SCANCODE(GREATER, UNKNOWN),
    KEYSYM2SCANCODE(QUESTION, UNKNOWN),
    KEYSYM2SCANCODE(AT, UNKNOWN),
    KEYSYM2SCANCODE(LEFTBRACKET, LEFTBRACKET),
    KEYSYM2SCANCODE(BACKSLASH, BACKSLASH),
    KEYSYM2SCANCODE(RIGHTBRACKET, RIGHTBRACKET),
    KEYSYM2SCANCODE(CARET, UNKNOWN),
    KEYSYM2SCANCODE(UNDERSCORE, UNKNOWN),
    KEYSYM2SCANCODE(BACKQUOTE, UNKNOWN),
    KEYSYM2SCANCODE(a, A),
    KEYSYM2SCANCODE(b, B),
    KEYSYM2SCANCODE(c, C),
    KEYSYM2SCANCODE(d, D),
    KEYSYM2SCANCODE(e, E),
    KEYSYM2SCANCODE(f, F),
    KEYSYM2SCANCODE(g, G),
    KEYSYM2SCANCODE(h, H),
    KEYSYM2SCANCODE(i, I),
    KEYSYM2SCANCODE(j, J),
    KEYSYM2SCANCODE(k, K),
    KEYSYM2SCANCODE(l, L),
    KEYSYM2SCANCODE(m, M),
    KEYSYM2SCANCODE(n, N),
    KEYSYM2SCANCODE(o, O),
    KEYSYM2SCANCODE(p, P),
    KEYSYM2SCANCODE(q, Q),
    KEYSYM2SCANCODE(r, R),
    KEYSYM2SCANCODE(s, S),
    KEYSYM2SCANCODE(t, T),
    KEYSYM2SCANCODE(u, U),
    KEYSYM2SCANCODE(v, V),
    KEYSYM2SCANCODE(w, W),
    KEYSYM2SCANCODE(x, X),
    KEYSYM2SCANCODE(y, Y),
    KEYSYM2SCANCODE(z, Z),
    KEYSYM2SCANCODE(DELETE, DELETE),
    KEYSYM2SCANCODE(WORLD_0, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_1, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_2, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_3, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_4, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_5, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_6, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_7, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_8, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_9, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_10, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_11, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_12, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_13, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_14, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_15, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_16, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_17, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_18, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_19, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_20, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_21, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_22, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_23, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_24, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_25, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_26, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_27, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_28, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_29, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_30, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_31, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_32, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_33, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_34, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_35, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_36, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_37, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_38, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_39, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_40, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_41, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_42, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_43, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_44, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_45, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_46, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_47, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_48, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_49, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_50, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_51, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_52, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_53, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_54, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_55, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_56, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_57, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_58, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_59, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_60, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_61, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_62, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_63, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_64, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_65, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_66, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_67, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_68, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_69, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_70, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_71, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_72, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_73, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_74, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_75, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_76, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_77, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_78, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_79, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_80, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_81, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_82, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_83, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_84, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_85, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_86, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_87, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_88, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_89, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_90, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_91, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_92, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_93, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_94, UNKNOWN),
    KEYSYM2SCANCODE(WORLD_95, UNKNOWN),
    KEYSYM2SCANCODE(KP0, KP_0),
    KEYSYM2SCANCODE(KP1, KP_1),
    KEYSYM2SCANCODE(KP2, KP_2),
    KEYSYM2SCANCODE(KP3, KP_3),
    KEYSYM2SCANCODE(KP4, KP_4),
    KEYSYM2SCANCODE(KP5, KP_5),
    KEYSYM2SCANCODE(KP6, KP_6),
    KEYSYM2SCANCODE(KP7, KP_7),
    KEYSYM2SCANCODE(KP8, KP_8),
    KEYSYM2SCANCODE(KP9, KP_9),
    KEYSYM2SCANCODE(KP_PERIOD, KP_PERIOD),
    KEYSYM2SCANCODE(KP_DIVIDE, KP_DIVIDE),
    KEYSYM2SCANCODE(KP_MULTIPLY, KP_MULTIPLY),
    KEYSYM2SCANCODE(KP_MINUS, KP_MINUS),
    KEYSYM2SCANCODE(KP_PLUS, KP_PLUS),
    KEYSYM2SCANCODE(KP_ENTER, KP_ENTER),
    KEYSYM2SCANCODE(KP_EQUALS, KP_EQUALS),
    KEYSYM2SCANCODE(UP, UP),
    KEYSYM2SCANCODE(DOWN, DOWN),
    KEYSYM2SCANCODE(RIGHT, RIGHT),
    KEYSYM2SCANCODE(LEFT, LEFT),
    KEYSYM2SCANCODE(INSERT, INSERT),
    KEYSYM2SCANCODE(HOME, HOME),
    KEYSYM2SCANCODE(END, END),
    KEYSYM2SCANCODE(PAGEUP, PAGEUP),
    KEYSYM2SCANCODE(PAGEDOWN, PAGEDOWN),
    KEYSYM2SCANCODE(F1, F1),
    KEYSYM2SCANCODE(F2, F2),
    KEYSYM2SCANCODE(F3, F3),
    KEYSYM2SCANCODE(F4, F4),
    KEYSYM2SCANCODE(F5, F5),
    KEYSYM2SCANCODE(F6, F6),
    KEYSYM2SCANCODE(F7, F7),
    KEYSYM2SCANCODE(F8, F8),
    KEYSYM2SCANCODE(F9, F9),
    KEYSYM2SCANCODE(F10, F10),
    KEYSYM2SCANCODE(F11, F11),
    KEYSYM2SCANCODE(F12, F12),
    KEYSYM2SCANCODE(F13, F13),
    KEYSYM2SCANCODE(F14, F14),
    KEYSYM2SCANCODE(F15, F15),
    KEYSYM2SCANCODE(NUMLOCK, NUMLOCKCLEAR),
    KEYSYM2SCANCODE(CAPSLOCK, CAPSLOCK),
    KEYSYM2SCANCODE(SCROLLOCK, UNKNOWN),
    KEYSYM2SCANCODE(RSHIFT, RSHIFT),
    KEYSYM2SCANCODE(LSHIFT, LSHIFT),
    KEYSYM2SCANCODE(RCTRL, RCTRL),
    KEYSYM2SCANCODE(LCTRL, LCTRL),
    KEYSYM2SCANCODE(RALT, RALT),
    KEYSYM2SCANCODE(LALT, LALT),
    KEYSYM2SCANCODE(RMETA, UNKNOWN),
    KEYSYM2SCANCODE(LMETA, UNKNOWN),
    KEYSYM2SCANCODE(LSUPER, LGUI),
    KEYSYM2SCANCODE(RSUPER, RGUI),
    KEYSYM2SCANCODE(MODE, MODE),
    KEYSYM2SCANCODE(COMPOSE, UNKNOWN),
    KEYSYM2SCANCODE(HELP, HELP),
    KEYSYM2SCANCODE(PRINT, UNKNOWN),
    KEYSYM2SCANCODE(SYSREQ, SYSREQ),
    KEYSYM2SCANCODE(BREAK, UNKNOWN),
    KEYSYM2SCANCODE(MENU, MENU),
    KEYSYM2SCANCODE(POWER, POWER),
    KEYSYM2SCANCODE(EURO, UNKNOWN),
    KEYSYM2SCANCODE(UNDO, UNDO),
    KEYSYM2SCANCODE(UNKNOWN, NONUSHASH),
    KEYSYM2SCANCODE(UNKNOWN, APOSTROPHE),
    KEYSYM2SCANCODE(UNKNOWN, GRAVE),
    KEYSYM2SCANCODE(UNKNOWN, PRINTSCREEN),
    KEYSYM2SCANCODE(UNKNOWN, SCROLLLOCK),
    KEYSYM2SCANCODE(UNKNOWN, NONUSBACKSLASH),
    KEYSYM2SCANCODE(UNKNOWN, APPLICATION),
    KEYSYM2SCANCODE(UNKNOWN, F16),
    KEYSYM2SCANCODE(UNKNOWN, F17),
    KEYSYM2SCANCODE(UNKNOWN, F18),
    KEYSYM2SCANCODE(UNKNOWN, F19),
    KEYSYM2SCANCODE(UNKNOWN, F20),
    KEYSYM2SCANCODE(UNKNOWN, F21),
    KEYSYM2SCANCODE(UNKNOWN, F22),
    KEYSYM2SCANCODE(UNKNOWN, F23),
    KEYSYM2SCANCODE(UNKNOWN, F24),
    KEYSYM2SCANCODE(UNKNOWN, EXECUTE),
    KEYSYM2SCANCODE(UNKNOWN, SELECT),
    KEYSYM2SCANCODE(UNKNOWN, STOP),
    KEYSYM2SCANCODE(UNKNOWN, AGAIN),
    KEYSYM2SCANCODE(UNKNOWN, CUT),
    KEYSYM2SCANCODE(UNKNOWN, COPY),
    KEYSYM2SCANCODE(UNKNOWN, PASTE),
    KEYSYM2SCANCODE(UNKNOWN, FIND),
    KEYSYM2SCANCODE(UNKNOWN, MUTE),
    KEYSYM2SCANCODE(UNKNOWN, VOLUMEUP),
    KEYSYM2SCANCODE(UNKNOWN, VOLUMEDOWN),
    KEYSYM2SCANCODE(UNKNOWN, KP_COMMA),
    KEYSYM2SCANCODE(UNKNOWN, KP_EQUALSAS400),
    KEYSYM2SCANCODE(UNKNOWN, INTERNATIONAL1),
    KEYSYM2SCANCODE(UNKNOWN, INTERNATIONAL2),
    KEYSYM2SCANCODE(UNKNOWN, INTERNATIONAL3),
    KEYSYM2SCANCODE(UNKNOWN, INTERNATIONAL4),
    KEYSYM2SCANCODE(UNKNOWN, INTERNATIONAL5),
    KEYSYM2SCANCODE(UNKNOWN, INTERNATIONAL6),
    KEYSYM2SCANCODE(UNKNOWN, INTERNATIONAL7),
    KEYSYM2SCANCODE(UNKNOWN, INTERNATIONAL8),
    KEYSYM2SCANCODE(UNKNOWN, INTERNATIONAL9),
    KEYSYM2SCANCODE(UNKNOWN, LANG1),
    KEYSYM2SCANCODE(UNKNOWN, LANG2),
    KEYSYM2SCANCODE(UNKNOWN, LANG3),
    KEYSYM2SCANCODE(UNKNOWN, LANG4),
    KEYSYM2SCANCODE(UNKNOWN, LANG5),
    KEYSYM2SCANCODE(UNKNOWN, LANG6),
    KEYSYM2SCANCODE(UNKNOWN, LANG7),
    KEYSYM2SCANCODE(UNKNOWN, LANG8),
    KEYSYM2SCANCODE(UNKNOWN, LANG9),
    KEYSYM2SCANCODE(UNKNOWN, ALTERASE),
    KEYSYM2SCANCODE(UNKNOWN, CANCEL),
    KEYSYM2SCANCODE(UNKNOWN, PRIOR),
    KEYSYM2SCANCODE(UNKNOWN, RETURN2),
    KEYSYM2SCANCODE(UNKNOWN, SEPARATOR),
    KEYSYM2SCANCODE(UNKNOWN, OUT),
    KEYSYM2SCANCODE(UNKNOWN, OPER),
    KEYSYM2SCANCODE(UNKNOWN, CLEARAGAIN),
    KEYSYM2SCANCODE(UNKNOWN, CRSEL),
    KEYSYM2SCANCODE(UNKNOWN, EXSEL),
    KEYSYM2SCANCODE(UNKNOWN, KP_00),
    KEYSYM2SCANCODE(UNKNOWN, KP_000),
    KEYSYM2SCANCODE(UNKNOWN, THOUSANDSSEPARATOR),
    KEYSYM2SCANCODE(UNKNOWN, DECIMALSEPARATOR),
    KEYSYM2SCANCODE(UNKNOWN, CURRENCYUNIT),
    KEYSYM2SCANCODE(UNKNOWN, CURRENCYSUBUNIT),
    KEYSYM2SCANCODE(UNKNOWN, KP_LEFTPAREN),
    KEYSYM2SCANCODE(UNKNOWN, KP_RIGHTPAREN),
    KEYSYM2SCANCODE(UNKNOWN, KP_LEFTBRACE),
    KEYSYM2SCANCODE(UNKNOWN, KP_RIGHTBRACE),
    KEYSYM2SCANCODE(UNKNOWN, KP_TAB),
    KEYSYM2SCANCODE(UNKNOWN, KP_BACKSPACE),
    KEYSYM2SCANCODE(UNKNOWN, KP_A),
    KEYSYM2SCANCODE(UNKNOWN, KP_B),
    KEYSYM2SCANCODE(UNKNOWN, KP_C),
    KEYSYM2SCANCODE(UNKNOWN, KP_D),
    KEYSYM2SCANCODE(UNKNOWN, KP_E),
    KEYSYM2SCANCODE(UNKNOWN, KP_F),
    KEYSYM2SCANCODE(UNKNOWN, KP_XOR),
    KEYSYM2SCANCODE(UNKNOWN, KP_POWER),
    KEYSYM2SCANCODE(UNKNOWN, KP_PERCENT),
    KEYSYM2SCANCODE(UNKNOWN, KP_LESS),
    KEYSYM2SCANCODE(UNKNOWN, KP_GREATER),
    KEYSYM2SCANCODE(UNKNOWN, KP_AMPERSAND),
    KEYSYM2SCANCODE(UNKNOWN, KP_DBLAMPERSAND),
    KEYSYM2SCANCODE(UNKNOWN, KP_VERTICALBAR),
    KEYSYM2SCANCODE(UNKNOWN, KP_DBLVERTICALBAR),
    KEYSYM2SCANCODE(UNKNOWN, KP_COLON),
    KEYSYM2SCANCODE(UNKNOWN, KP_HASH),
    KEYSYM2SCANCODE(UNKNOWN, KP_SPACE),
    KEYSYM2SCANCODE(UNKNOWN, KP_AT),
    KEYSYM2SCANCODE(UNKNOWN, KP_EXCLAM),
    KEYSYM2SCANCODE(UNKNOWN, KP_MEMSTORE),
    KEYSYM2SCANCODE(UNKNOWN, KP_MEMRECALL),
    KEYSYM2SCANCODE(UNKNOWN, KP_MEMCLEAR),
    KEYSYM2SCANCODE(UNKNOWN, KP_MEMADD),
    KEYSYM2SCANCODE(UNKNOWN, KP_MEMSUBTRACT),
    KEYSYM2SCANCODE(UNKNOWN, KP_MEMMULTIPLY),
    KEYSYM2SCANCODE(UNKNOWN, KP_MEMDIVIDE),
    KEYSYM2SCANCODE(UNKNOWN, KP_PLUSMINUS),
    KEYSYM2SCANCODE(UNKNOWN, KP_CLEAR),
    KEYSYM2SCANCODE(UNKNOWN, KP_CLEARENTRY),
    KEYSYM2SCANCODE(UNKNOWN, KP_BINARY),
    KEYSYM2SCANCODE(UNKNOWN, KP_OCTAL),
    KEYSYM2SCANCODE(UNKNOWN, KP_DECIMAL),
    KEYSYM2SCANCODE(UNKNOWN, KP_HEXADECIMAL),
    KEYSYM2SCANCODE(UNKNOWN, AUDIONEXT),
    KEYSYM2SCANCODE(UNKNOWN, AUDIOPREV),
    KEYSYM2SCANCODE(UNKNOWN, AUDIOSTOP),
    KEYSYM2SCANCODE(UNKNOWN, AUDIOPLAY),
    KEYSYM2SCANCODE(UNKNOWN, AUDIOMUTE),
    KEYSYM2SCANCODE(UNKNOWN, MEDIASELECT),
    KEYSYM2SCANCODE(UNKNOWN, WWW),
    KEYSYM2SCANCODE(UNKNOWN, MAIL),
    KEYSYM2SCANCODE(UNKNOWN, CALCULATOR),
    KEYSYM2SCANCODE(UNKNOWN, COMPUTER),
    KEYSYM2SCANCODE(UNKNOWN, AC_SEARCH),
    KEYSYM2SCANCODE(UNKNOWN, AC_HOME),
    KEYSYM2SCANCODE(UNKNOWN, AC_BACK),
    KEYSYM2SCANCODE(UNKNOWN, AC_FORWARD),
    KEYSYM2SCANCODE(UNKNOWN, AC_STOP),
    KEYSYM2SCANCODE(UNKNOWN, AC_REFRESH),
    KEYSYM2SCANCODE(UNKNOWN, AC_BOOKMARKS),
    KEYSYM2SCANCODE(UNKNOWN, BRIGHTNESSDOWN),
    KEYSYM2SCANCODE(UNKNOWN, BRIGHTNESSUP),
    KEYSYM2SCANCODE(UNKNOWN, DISPLAYSWITCH),
    KEYSYM2SCANCODE(UNKNOWN, KBDILLUMTOGGLE),
    KEYSYM2SCANCODE(UNKNOWN, KBDILLUMDOWN),
    KEYSYM2SCANCODE(UNKNOWN, KBDILLUMUP),
    KEYSYM2SCANCODE(UNKNOWN, EJECT),
    KEYSYM2SCANCODE(UNKNOWN, SLEEP),
    KEYSYM2SCANCODE(UNKNOWN, APP1),
    KEYSYM2SCANCODE(UNKNOWN, APP2),
};

int main(void)
{
    size_t i, j;
    int found;
    uint16_t max_keysym = 0, max_scancode = 0;

    for (i = 0; i < ARRAY_SIZE(keycode2scancode); i++) {
        if (max_keysym < keycode2scancode[i].keysym)
            max_keysym = keycode2scancode[i].keysym;

        if (max_scancode < keycode2scancode[i].scancode)
            max_scancode = keycode2scancode[i].scancode;
    }

    puts("#include <stdint.h>");
    puts("#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))\n");

    puts("uint16_t sdl_keysym2scancode(uint16_t keysym)\n{");

    printf("    static const uint16_t keysym2scancode[%"PRIu16"] = {\n",
           max_keysym + 1);
    for (i = 0; i < (max_keysym + 1); i++) {
        found = 0;
        for (j = 0; j < ARRAY_SIZE(keycode2scancode); j++) {
            if (i != 0 && keycode2scancode[j].keysym == i) {
                printf("        0x%04xu, /* %s -> %s */\n",
                       keycode2scancode[j].scancode,
                       keycode2scancode[j].keysym_name,
                       keycode2scancode[j].scancode_name);

                if (found)
                    fprintf(stderr,
                            "Multiple entry with keysym %zu, %s -> %s\n",
                            i, keycode2scancode[j].keysym_name,
                            keycode2scancode[j].scancode_name);
                found = 1;
            }
        }

        if (!found)
            printf("        0x%04xu, /* %s -> %s */\n",
                   0,
                   "unassigned",
                   "SDL_SCANCODE_UNKNOWN");
    }
    puts("    };\n");
    puts("    if (keysym >= ARRAY_SIZE(keysym2scancode))");
    puts("        return 0;");
    puts("    return keysym2scancode[keysym];\n}\n");

    

    puts("uint16_t sdl_scancode2keysym(uint16_t scancode)\n{");

    printf("    static const uint16_t scancode2keysym[%"PRIu16"] = {\n",
           max_scancode + 1);
    for (i = 0; i < (max_scancode + 1); i++) {
        found = 0;
        for (j = 0; j < ARRAY_SIZE(keycode2scancode); j++) {
            if (i != 0 && keycode2scancode[j].scancode == i) {
                printf("        0x%04xu, /* %s -> %s */\n",
                       keycode2scancode[j].keysym,
                       keycode2scancode[j].scancode_name,
                       keycode2scancode[j].keysym_name);

                if (found)
                    fprintf(stderr,
                            "Multiple entry with scancode %zu, %s -> %s\n",
                            i, keycode2scancode[j].scancode_name,
                            keycode2scancode[j].keysym_name);
                found = 1;
            }
        }

        if (!found)
            printf("        0x%04xu, /* %s -> %s */\n",
                   0,
                   "unassigned",
                   "SDLK_UNKNOWN");
    }
    puts("    };\n");
    puts("    if (scancode >= ARRAY_SIZE(scancode2keysym))");
    puts("        return 0;");
    puts("    return scancode2keysym[scancode];\n}");

    return 0;
}
