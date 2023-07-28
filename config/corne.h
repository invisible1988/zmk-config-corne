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
#define FUN 3
#define SYM 4
#define SYS 5


#include "mouse.dtsi"

#define QUICK_TAP_MS 175

&sk {  // sticky-key config
    release-after-ms = <900>;  // release after 0.9s
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

ZMK_BEHAVIOR(hrm, hold_tap, 
    label = "hrm";
    flavor = "tap-preferred"; 
    tapping-term-ms = <200>; 
    quick-tap-ms = <QUICK_TAP_MS>; 
    bindings = <&kp>, <&kp>; 
    global-quick-tap-ms = <150>; \
    global-quick-tap;
)

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

// hyper_tap
ZMK_BEHAVIOR(ht, hold_tap,
    flavor = "hold-preferred";
    tapping-term-ms = <200>;
    quick-tap-ms = <QUICK_TAP_MS>;
    bindings = <&kp>, <&mo>;
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

// GUI+Tab swapper, requires PR #1366
ZMK_BEHAVIOR(swapper, tri_state,
    bindings = <&kt LGUI>, <&kp TAB>, <&kt LGUI>;
    ignored-key-positions = <LT2 LT4>;
)

// euro sign
ZMK_UNICODE_SINGLE(euro_sign, N2, N0, A, C)  // €

// combos
// ZMK_COMBO(combo_copy,   &kp LG(C),  LB2 LB3, ALL)  // Ctrl + C, active on all layers
// ZMK_COMBO(combo_paste,  &kp LG(V),  LB1 LB2, ALL)  // Ctrl + V, active on all layers
ZMK_COMBO(combo_enter,  &kp RET, RM1 RM2, DEF)
ZMK_COMBO(combo_esc,    &kp ESC, LM1 LM2, DEF)
// ZMK_COMBO(combo_esc,    &kp ESC, LT4 LT3, ALL)


// ZMK_CONDITIONAL_LAYER(NAV NUM, SYS

/* keymap */
ZMK_LAYER(default_layer,
      // ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮
          ___            &kp Q          &kp W          &kp E          &kp R          &kp T            &kp Y          &kp U          &kp I          &kp O          &kp P          &mo SYS
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            &kp A          &hrm LALT S    &hrm LCTRL D   &hrm LGUI F    &kp G            &kp H          &hrm RGUI J    &hrm RCTRL K   &hrm RALT L    &kp SQT        ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            &kp Z          &kp X          &kp C          &kp V          &kp B            &kp N          &kp M          &comma_morph   &dot_morph     &qexcl         ___
      // ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯
                                                       &ht HYPER FUN  &lt_spc NAV 0  &lt SYM TAB      &smart_shft    &kp BKSP       SMART_NUM
      //                                              ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────┴──────────────╯
        )

ZMK_LAYER(nav_layer,
      // ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮
          XXX            ___            XXX            &kp LS(TAB)    &swapper       XXX              XXX            &de_ue         XXX            &de_oe         XXX            XXX
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          XXX            &de_ae         &de_eszett     XXX            XXX            XXX              &kp LEFT       &kp DOWN       &kp UP         &kp RIGHT      XXX            XXX
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          XXX            XXX            XXX            XXX            XXX            XXX              &kp HOME       &kp PG_DN      &kp PG_UP      &kp END        XXX            XXX
      // ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯
                                                       ___            ___            ___              ___            &kp DEL        ___
      //                                              ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────┴──────────────╯
          )

ZMK_LAYER(num_layer,
      // ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮
          ___            &kp N1         &kp N2         &kp N3         &kp N4         &kp N5           &kp N6         &kp N7         &kp N8         &kp N9         &kp N0         ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            ___            ___            ___            &kp LGUI       &kp PLUS         &kp FSLH       &kp RGUI       &kp PRCNT      &kp EQUAL      ___            ___
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          ___            ___            ___            ___            ___            &kp MINUS        &kp STAR       ___            ___            ___            ___            ___
      // ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯
                                                       ___            ___            ___              ___            ___            ___
      //                                              ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────┴──────────────╯
          )

ZMK_LAYER(fn_layer,
      // ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮
          XXX            &kp F1         &kp F2         &kp F3         &kp F4         XXX              XXX            &kp C_VOL_DN   &kp C_MUTE     &kp C_VOL_UP   &kp C_AL_LOCK  XXX
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          XXX            &kp F5         &kp F6         &kp F7         &kp F8         XXX              XXX            &kp C_PREV     &kp C_PP       &kp C_NEXT     XXX            XXX
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          XXX            &kp F9         &kp F10        &kp F11        &kp F12        XXX              XXX            XXX            XXX            XXX            XXX            XXX
      // ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯
                                                       ___            ___            ___              ___            ___            ___
      //                                              ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────┴──────────────╯
          )

ZMK_LAYER(symbols_layer,
      // ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮
          XXX            XXX            &kp CARET      &kp AT         &kp HASH       &kp TILDE        &kp AMPS       &kp PLUS       &kp STAR       &kp EQUAL      &kp GRAVE      XXX
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          XXX            &kp LT         &kp LBKT       &kp LBRC       &kp LPAR       &kp DLLR         &kp FSLH       &kp MINUS      &kp PRCNT      &kp PIPE       &kp SQT        XXX
      // ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤
          XXX            &kp GT         &kp RBKT       &kp RBRC       &kp RPAR       &euro_sign       &kp BSLH       &kp UNDER      &kp SEMI       &kp COLON      &kp DQT        XXX
      // ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼─────────────┼───────────────┼──────────────╯
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

