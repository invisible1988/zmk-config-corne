#include <behaviors.dtsi>
#include <dt-bindings/zmk/keys.h>
#include <dt-bindings/zmk/bt.h>

#define HOST_OS 2
#include "../zmk-nodefree-config/helper.h"
#include "../zmk-nodefree-config/keypos_def/keypos_42keys.h"
#include "../zmk-nodefree-config/international_chars/german.dtsi"

/* layer and key shortcuts */
#define XXX &none
#define ___ &trans

#define MEH   LC(LS(LALT))

#define DEF 0
#define NAV 1
#define UTL 2
#define NUM 3
#define FUN 4
#define SYS 6


#define QUICK_TAP_MS 175

/* Homerow mods */
#define KEYS_L LT0 LT1 LT2 LT3 LT4 LM0 LM1 LM2 LM3 LM4 LB0 LB1 LB2 LB3 LB4  // left hand
#define KEYS_R RT0 RT1 RT2 RT3 RT4 RM0 RM1 RM2 RM3 RM4 RB0 RB1 RB2 RB3 RB4  // right hand
#define THUMBS LH2 LH1 LH0 RH0 RH1 RH2                                      // thumbs

#define MAKE_HRM(NAME, HOLD, TAP, TRIGGER_POS) \
    ZMK_BEHAVIOR(NAME, hold_tap, \
        flavor = "tap-preferred"; \
        tapping-term-ms = <200>; \
        quick-tap-ms = <QUICK_TAP_MS>; \
        bindings = <&kp>, <&kp>; \
        global-quick-tap-ms = <150>; \
        global-quick-tap; \
        hold-trigger-key-positions = <TRIGGER_POS>; \
    )

MAKE_HRM(hml, &kp, &kp, KEYS_R THUMBS)  // left-hand HRMs
MAKE_HRM(hmr, &kp, &kp, KEYS_L THUMBS)  // right-hand HRMs

ZMK_UNICODE_PAIR(N9_EUR,   N0, N0, N3, N9,    N2, N0, A, C)

&caps_word {  // mods deactivate caps-word, requires PR #1451
    /delete-property/ ignore-modifiers;
};

ZMK_BEHAVIOR(tp, hold_tap,
    flavor = "tap-preferred";
    tapping-term-ms = <200>;
    quick-tap-ms = <QUICK_TAP_MS>;
    bindings = <&mo>, <&kp>;
)

// tap: space | shift + tap: dot -> space -> sticky shift | hold: activate layer
ZMK_BEHAVIOR(lt_spc, hold_tap,
    flavor = "balanced";
    tapping-term-ms = <200>;
    quick-tap-ms = <QUICK_TAP_MS>;
    bindings = <&mo>, <&spc_morph>;
)
ZMK_BEHAVIOR(spc_morph, mod_morph,
    bindings = <&kp SPACE>, <&dot_spc>;
    mods = <(MOD_LSFT|MOD_RSFT)>;
)
ZMK_BEHAVIOR(dot_spc, macro,
    wait-ms = <0>;
    tap-ms = <5>;
    bindings = <&kp DOT &kp SPACE &sk LSHFT>;
)

// tap: comma | shift + tap: semicolon
ZMK_BEHAVIOR(comma_morph, mod_morph,
    mods = <(MOD_LSFT|MOD_RSFT)>;
    bindings = <&kp COMMA>, <&kp SEMICOLON>;
)
// tap: dot | shift + tap: colon
ZMK_BEHAVIOR(dot_morph, mod_morph,
    bindings = <&kp DOT>, <&kp COLON>;
    mods = <(MOD_LSFT|MOD_RSFT)>;
)

// tap: qmark | shift + tap: excl
ZMK_BEHAVIOR(qexcl, mod_morph,
    bindings = <&kp QMARK>, <&kp EXCL>;
    mods = <(MOD_LSFT|MOD_RSFT)>;
)

// tap: DOT | shift + tap: LPAR
ZMK_BEHAVIOR(DOT_LPAR, mod_morph,
    bindings = <&kp DOT>, <&kp LPAR>;
    mods = <(MOD_LSFT|MOD_RSFT)>;
)

// tap: N1 | shift + tap: forward slash
ZMK_BEHAVIOR(N1_FSLH, mod_morph,
    bindings = <&kp N1>, <&kp FSLH>;
    mods = <(MOD_LSFT|MOD_RSFT)>;
)


// GUI+Tab swapper, requires PR #1366
ZMK_BEHAVIOR(swapper, tri_state,
    bindings = <&kt LCMD>, <&kp TAB>, <&kt LGUI>;
    ignored-key-positions = <LT2 LT3 LT4>;
)


ZMK_CONDITIONAL_LAYER(NUM FUN, SYS)

/* keymap */
ZMK_LAYER(default_layer,
      // ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮
          ___            &kp Q          &kp W          &kp E          &kp R          &kp T            &kp Y          &kp U          &kp I          &kp O          &kp P          ___ 
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          &mt LSHFT ESC  &hml MEH A     &hml LCTRL S   &hml LCMD D    &kp F          &hml LALT G      &hmr RALT H    &kp J          &hmr RCMD K    &hmr RCTRL L   &hmr MEH SQT   &kp RSHFT
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            &kp Z          &kp X          &kp C          &kp V          &kp B            &kp N          &kp M          &kp COMMA      &kp DOT        &qexcl         ___
      // ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯
                                                       &mo NAV        &spc_morph     &mo NUM          &tp FUN RET    &kp BKSP       &mo UTL
      //                                              ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────┴──────────────╯
        )

ZMK_LAYER(nav_layer,
      // ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮
          XXX            ___            ___            XXX            XXX            XXX              XXX            &de_ue         XXX            &de_oe         XXX            XXX
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            &kp MEH        &kp LCTRL      &kp LCMD       &kp LSHFT      &kp LALT         &kp LEFT       &kp DOWN       &kp UP         &kp RIGHT      &caps_word     XXX
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          XXX            XXX            XXX            XXX            XXX            XXX              &kp HOME       &kp PG_DN      &kp PG_UP      &kp END        XXX            XXX
      // ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯
                                                       ___            ___            ___              ___            &kp BKSP       &kp DEL
      //                                              ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────┴──────────────╯
          )

ZMK_LAYER(utils_layer,
      // ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮
          XXX            XXX            XXX            &kp LG(LBRC)   &kp LG(RBRC)   XXX              XXX            XXX            XXX            XXX            XXX            XXX
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          XXX            &de_ae         &de_eszett     XXX            XXX            XXX              &kp  RALT      &kp  RSHFT     &kp  RCMD      &kp  RCTRL     &kp  MEH       ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          XXX            XXX            XXX            XXX            XXX            XXX              XXX            XXX            XXX            XXX            XXX            XXX
      // ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯
                                                       ___            &kp TAB        ___              ___            ___            ___
      //                                              ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────┴──────────────╯
          )

ZMK_LAYER(num_layer,
      // ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮
          XXX            XXX            XXX            &kp LS(TAB)    &swapper       XXX              &kp LBKT       &kp N7         &kp N8         &kp N9         &kp RBKT       XXX
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          XXX            &kp MEH        &kp LCTRL      &kp LCMD       &kp LSHFT      &kp LALT         &kp SEMI       &kp N4         &kp N5         &kp N6         &kp EQUAL      XXX
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          XXX            XXX            XXX            XXX            XXX            XXX              &kp GRAVE      &N1_FSLH       &kp N2         &kp N3         &kp BSLH       XXX
      // ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯
                                                       ___            ___            ___              &DOT_LPAR      &kp N0         &kp MINUS
      //                                              ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────┴──────────────╯
          )

ZMK_LAYER(fn_layer,
      // ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮
          XXX            &kp F12        &kp F7         &kp F8         &kp F9         XXX              XXX            &kp C_VOL_DN   &kp C_MUTE     &kp C_VOL_UP   &kp C_AL_LOCK  XXX
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          XXX            &kp F11        &kp F4         &kp F5         &kp F6         XXX              XXX            &kp C_PREV     &kp C_PP       &kp C_NEXT     XXX            XXX
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          XXX            &kp F10        &kp F1         &kp F2         &kp F3         XXX              XXX            XXX            XXX            XXX            XXX            XXX
      // ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯
                                                       ___            ___            ___              ___            ___            ___ 
      //                                              ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────┴──────────────╯
          )

ZMK_LAYER(system_layer,
      // ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮
          ___            &bt BT_SEL 0   &bt BT_SEL 1   &bt BT_SEL 2   &bt BT_SEL 3   &bt BT_SEL 4     ___            ___            ___            ___            ___            ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            ___            ___            ___            ___            &bootloader      &bootloader    ___            ___            ___            ___            ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            &bt BT_CLR     ___            ___            ___            &sys_reset       &sys_reset     ___            ___            ___            ___            ___
      // ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯
                                                       ___            ___            ___              ___            ___            ___
      //                                              ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────┴──────────────╯
          )
