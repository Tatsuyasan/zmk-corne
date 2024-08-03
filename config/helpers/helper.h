#define HOST_OS 1
#define U_STRINGIFY(x) #x

/* BEHAVIOR */

#define SHIFT_FUNCTION(NAME, BINDING, SHIFT_BINDING) \
/ { \
  behaviors { \
    NAME: NAME { \
      compatible = "zmk,behavior-mod-morph"; \
      label = U_STRINGIFY(NAME); \
      #binding-cells = <0>; \
      bindings = <BINDING>, <SHIFT_BINDING>; \
      mods = <(MOD_LSFT|MOD_RSFT)>; \
    }; \
  }; \
};

/* CONDITIONAL_LAYER */

#define CONDITIONAL_LAYER(if_layers, then_layer) \
    / { \
        conditional_layers { \
            compatible = "zmk,conditional-layers"; \
            tri_layer { \
                if-layers = <if_layers>; \
                then-layer = <then_layer>; \
            }; \
        }; \
    };

/* MACRO */

#define U_MACRO(name,...) \
/ { \
  macros { \
    name: name { \
      label = U_STRINGIFY(ZM_ ## name); \
      compatible = "zmk,behavior-macro"; \
      #binding-cells = <0>; \
      __VA_ARGS__ \
    }; \
  }; \
};

#define UC_MACRO(name, unicode_bindings) \
/ { \
    macros { \
        name: name { \
            compatible = "zmk,behavior-macro"; \
            wait-ms = <0>; \
            tap-ms = <0>; \
            #binding-cells = <0>; \
            bindings = <OS_UNICODE_LEAD>, <&macro_tap unicode_bindings>, <OS_UNICODE_TRAIL>; \
        }; \
    }; \
};

#define SHIFT_MACRO(NAME, BINDING, SHIFT_BINDING) \
    U_MACRO(u_macro_ ## NAME, wait-ms = <0>; bindings = <SHIFT_BINDING>;) \
    SHIFT_FUNCTION(NAME, BINDING, &u_macro_ ## NAME)


/* UNICODE */

#if !defined OS_UNICODE_LEAD
    #if HOST_OS == 2
        #define OS_UNICODE_LEAD &macro_press &kp LALT      // macOS/Windows-Alt-Codes
    #elif HOST_OS == 1
        #define OS_UNICODE_LEAD &macro_tap &kp LS(LC(U))   // Linux
    #else
        #define OS_UNICODE_LEAD &macro_tap &kp RALT &kp U  // Windows + WinCompose (default)
    #endif
#endif
#if !defined OS_UNICODE_TRAIL
    #if HOST_OS == 2
        #define OS_UNICODE_TRAIL &macro_release &kp LALT  // macOS/Windows-Alt-Codes
    #elif HOST_OS == 1
        #define OS_UNICODE_TRAIL &macro_tap &kp SPACE     // Linux
    #else
        #define OS_UNICODE_TRAIL &macro_tap &kp RET       // Windows + WinCompose (default)
    #endif
#endif

#define ZMK_UNICODE_SINGLE(name, L0, L1, L2, L3) \
    UC_MACRO(name ## _lower, &kp L0 &kp L1 &kp L2 &kp L3) \
    SHIFT_FUNCTION(name, &name ## _lower, &none)

#define ZMK_UNICODE_PAIR(name, L0, L1, L2, L3, U0, U1, U2, U3) \
    UC_MACRO(name ## _lower, &kp L0 &kp L1 &kp L2 &kp L3) \
    UC_MACRO(name ## _upper, &kp U0 &kp U1 &kp U2 &kp U3) \
    SHIFT_FUNCTION(name, &name ## _lower, &name ## _upper)


/* OUTPUTS */

SHIFT_MACRO(bt_sel_0, &bt BT_SEL 0, &bt BT_SEL 0 &bt BT_CLR)
SHIFT_MACRO(bt_sel_1, &bt BT_SEL 1, &bt BT_SEL 1 &bt BT_CLR)
SHIFT_MACRO(bt_sel_2, &bt BT_SEL 2, &bt BT_SEL 2 &bt BT_CLR)
SHIFT_MACRO(bt_sel_3, &bt BT_SEL 3, &bt BT_SEL 3 &bt BT_CLR)

ZMK_UNICODE_PAIR(fr_ae,             N0, N0, E, N6,   N0, N0, C, N6)  // æ/Æ
ZMK_UNICODE_PAIR(fr_oe,             N0, N1, N5, N3,  N0, N1, N5, N2) // œ/Œ
ZMK_UNICODE_PAIR(fr_a_grave,        N0, N0, E, N0,   N0, N0, C, N0)  // à/À
ZMK_UNICODE_PAIR(fr_a_circumflex,   N0, N0, E, N2,   N0, N0, C, N2)  // â/Â
ZMK_UNICODE_PAIR(fr_c_cedilla,      N0, N0, E, N7,   N0, N0, C, N7)  // ç/Ç
ZMK_UNICODE_PAIR(fr_e_grave,        N0, N0, E, N8,   N0, N0, C, N8)  // è/È
ZMK_UNICODE_PAIR(fr_e_acute,        N0, N0, E, N9,   N0, N0, C, N9)  // é/É
ZMK_UNICODE_PAIR(fr_e_circumflex,   N0, N0, E, A,    N0, N0, C, A)   // ê/Ê
ZMK_UNICODE_PAIR(fr_e_diaeresis,    N0, N0, E, B,    N0, N0, C, B)   // ë/Ë
ZMK_UNICODE_PAIR(fr_i_circumflex,   N0, N0, E, E,    N0, N0, C, E)   // î/Î
ZMK_UNICODE_PAIR(fr_i_diaeresis,    N0, N0, E, F,    N0, N0, C, F)   // ï/Ï
ZMK_UNICODE_PAIR(fr_o_circumflex,   N0, N0, F, N4,   N0, N0, D, N4)  // ô/Ô
ZMK_UNICODE_PAIR(fr_u_grave,        N0, N0, F, N9,   N0, N0, D, N9)  // ù/Ù
ZMK_UNICODE_PAIR(fr_u_circumflex,   N0, N0, F, B,    N0, N0, D, B)   // û/Û
ZMK_UNICODE_PAIR(fr_u_diaeresis,    N0, N0, F, C,    N0, N0, D, C)   // ü/Ü
ZMK_UNICODE_PAIR(fr_y_diaeresis,    N0, N0, F, F,    N0, N1, N7, N8) // ÿ/Ÿ

