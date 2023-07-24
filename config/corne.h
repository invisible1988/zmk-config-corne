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
#define HYPER LC(LS(LA(LGUI)))
#define MEH   LC(LS(LALT))

#define DEF 0  // layer shortcuts, must match order in which they are defined below
#define NAV 1
#define NUM 2
#define FN  3
#define SYM 4
#define SYS 5


#include "mouse.dtsi"

#define QUICK_TAP_MS 175

&sk {  // sticky-key config
    release-after-ms = <900>;  // release after 0.6s
    quick-release;             // no double capitalization when rolling keys
};

&sl {  // sticky-layer config
    ignore-modifiers;          // allow chording sticky mods & layers
};

&lt {  // layer-tap config
    flavor = "balanced";
    tapping-term-ms = <200>;
    quick-tap-ms = <QUICK_TAP_MS>;
};

#define KEYS_L LT0 LT1 LT2 LT3 LT4 LM0 LM1 LM2 LM3 LM4 LB0 LB1 LB2 LB3 LB4  // left hand
#define KEYS_R RT0 RT1 RT2 RT3 RT4 RM0 RM1 RM2 RM3 RM4 RB0 RB1 RB2 RB3 RB4  // right hand
#define THUMBS LH2 LH1 LH0 RH0 RH1 RH2                                      // thumbs

#define MAKE_HRM(NAME, HOLD, TAP, TRIGGER_POS) \
    ZMK_BEHAVIOR(NAME, hold_tap, \
        flavor = "balanced"; \
        tapping-term-ms = <280>; \
        quick-tap-ms = <QUICK_TAP_MS>; \
        global-quick-tap-ms = <150>; \
        bindings = <HOLD>, <TAP>; \
        hold-trigger-key-positions = <TRIGGER_POS>; \
        hold-trigger-on-release; \
    )
MAKE_HRM(hml, &kp, &kp, KEYS_R THUMBS)  // left-hand HRMs
MAKE_HRM(hmr, &kp, &kp, KEYS_L THUMBS)  // right-hand HRMs


/* Caps-word, num-word */

// tap: sticky-shift | shift + tap/ double-tap: caps-word | hold: shift
ZMK_BEHAVIOR(smart_shft, mod_morph,
    bindings = <&sk LSHFT>, <&caps_word>;
    mods = <(MOD_LSFT)>;
)
&caps_word {  // mods deactivate caps-word, requires PR #1451
    /delete-property/ ignore-modifiers;
};

// tap: num-word | double-tap: sticky num-layer | hold: num-layer
#define SMART_NUM &smart_num NUM 0
ZMK_BEHAVIOR(smart_num, hold_tap,
    flavor = "balanced";
    tapping-term-ms = <200>;
    quick-tap-ms = <QUICK_TAP_MS>;
    bindings = <&mo>, <&num_dance>;
)
ZMK_BEHAVIOR(num_dance, tap_dance,
    tapping-term-ms = <200>;
    bindings = <&num_word>, <&sl NUM>;  // reverse this for sticky-num on single tap
)
&num_word {  // num-word, requires PR #1451
    layers = <NUM>;
    continue-list = <BSPC DEL DOT COMMA PLUS MINUS STAR FSLH EQUAL>;
};

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

// tap: backspace | shift + tap: delete
ZMK_BEHAVIOR(bs_del, mod_morph,
    bindings = <&kp BSPC>, <&kp DEL>;
    mods = <(MOD_LSFT|MOD_RSFT)>;
)

// tap: comma | shift + tap: semicolon | ctrl + shift + tap: <
ZMK_BEHAVIOR(comma_morph, mod_morph,
    mods = <(MOD_LSFT|MOD_RSFT)>;
    bindings = <&kp COMMA>, <&comma_inner_morph>;
)
ZMK_BEHAVIOR(comma_inner_morph, mod_morph,
    bindings = <&kp SEMICOLON>, <&kp LESS_THAN>;
    mods = <(MOD_LCTL|MOD_RCTL)>;
)

// tap: dot | shift + tap: colon | ctrl + shift + tap: >
ZMK_BEHAVIOR(dot_morph, mod_morph,
    bindings = <&kp DOT>, <&dot_inner_morph>;
    mods = <(MOD_LSFT|MOD_RSFT)>;
)
ZMK_BEHAVIOR(dot_inner_morph, mod_morph,
    bindings = <&kp COLON>, <&kp GREATER_THAN>;
    mods = <(MOD_LCTL|MOD_RCTL)>;
)

// tap: qmark | shift + tap: excl
ZMK_BEHAVIOR(qexcl, mod_morph,
    bindings = <&kp QMARK>, <&kp EXCL>;
    mods = <(MOD_LSFT|MOD_RSFT)>;
)

// GUI+Tab swapper, requires PR #1366
ZMK_BEHAVIOR(swapper, tri_state,
    bindings = <&kt LGUI>, <&kp TAB>, <&kt LGUI>;
    ignored-key-positions = <LT2>;
)

// euro sign
ZMK_UNICODE_SINGLE(euro_sign, N2, N0, A, C)  // €

// combos
ZMK_COMBO(combo_sleep,  &kp LC(LG(Q)), RT3 RT4, NAV)  // custom sleep macro, only active on NAV layer
ZMK_COMBO(combo_copy,   &kp LG(C),  LB2 LB3, ALL)  // Ctrl + C, active on all layers
ZMK_COMBO(combo_paste,  &kp LG(V),  LB1 LB2, ALL)  // Ctrl + V, active on all layers
ZMK_COMBO(combo_enter,  &kp RET, RM1 RM2, ALL)
ZMK_COMBO(combo_esc,    &kp ESC, LT4 LT3, ALL)

//Umlaut combos
ZMK_COMBO(combo_ue, &de_ue, RT1 RT2, DEF)
ZMK_COMBO(combo_oe, &de_oe, RT2 RT3, DEF)
ZMK_COMBO(combo_ae, &de_ae, LM3 LM4, DEF)
ZMK_COMBO(combo_eszett, &de_eszett, LM3 LM2, DEF)


ZMK_CONDITIONAL_LAYER(FN NUM, SYS)

/* keymap */
ZMK_LAYER(default_layer,
      // ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮
          ___            &kp Q          &kp W          &hml MEH E     &hml HYPER R   &kp T            &hml MEH Y     &hmr HYPER U   &kp I          &kp O          &kp P          ___ 
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            &hml LALT A    &hml LCTRL S   &hml LGUI D    &hml LSHFT F   &kp G            &kp H          &hmr RSHFT J   &hmr RGUI K    &hmr RCTRL L   &hmr RALT SQT  ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            &kp Z          &kp X          &kp C          &kp V          &kp B            &kp N          &kp M          &comma_morph   &dot_morph     &qexcl         ___
      // ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯
                                                       &mo FN         &lt_spc NAV 0  &sl SYM          SMART_NUM      &bs_del        &smart_shft
      //                                              ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────┴──────────────╯
          )

ZMK_LAYER(nav_layer,
      // ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮
          ___            ___            ___            &kp LS(TAB)    &swapper       ___              &kp HOME       &kp PG_DN      &kp PG_UP      &kp END        ___            ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            &sk LALT       &sk LCTRL      &sk LGUI       &sk LSHFT      ___              &kp LEFT       &kp DOWN       &kp UP         &kp RIGHT      ___            ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            ___            ___            ___            ___            ___              ___            ___            ___            ___            ___            ___
      // ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯
                                                       ___            ___            ___              ___            ___            ___
      //                                              ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────┴──────────────╯
          )

ZMK_LAYER(num_layer,
      // ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮
          ___            &kp ESC        &kp N7         &kp N8         &kp N9         &kp FSLH         &kp PRCNT      ___            ___            ___            ___            ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            &kp TAB        &kp N4         &kp N5         &kp N6         &kp STAR         &kp EQUAL      &kp RSHFT      &kp RGUI       &kp RCTRL      &kp RALT       ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            &kp RET        &kp N1         &kp N2         &kp N3         &kp MINUS        ___            ___            ___            ___            ___            ___
      // ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯
                                                       &kp DOT        &kp N0         &kp PLUS         ___            ___            ___
      //                                              ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────┴──────────────╯
          )

ZMK_LAYER(fn_layer,
      // ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮
          ___            &kp F12        &kp F7         &kp F8         &kp F9         ___              ___            &kp C_VOL_DN   &kp C_MUTE     &kp C_VOL_UP   &kp C_AL_LOCK  ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            &kp F11        &kp F4         &kp F5         &kp F6         ___              ___            &kp C_PREV     &kp C_PP       &kp C_NEXT     ___            ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            &kp F10        &kp F1         &kp F2         &kp F3         ___              ___            ___            ___            ___            ___            ___
      // ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯
                                                       ___            ___            ___              ___            ___            ___
      //                                              ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────┴──────────────╯
          )

ZMK_LAYER(symbols_layer,
      // ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮
          ___            &kp AT         ___            ___            ___            ___              &kp CARET      &kp AMPS       &kp PIPE       &kp LBKT       &kp RBKT       ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            ___            ___            ___            ___            ___              &kp HASH       &kp TILDE      &kp UNDER      &kp LPAR       &kp RPAR       ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            ___            ___            ___            ___            ___              &euro_sign     &kp DLLR       &kp GRAVE      &kp LBRC       &kp RBRC       ___
      // ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯
                                                       ___            ___            ___              ___            &kp BSLH       &kp FSLH
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

