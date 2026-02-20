// implement modes here

/* a mode is a set of displays/inputs specific to a context? */

// TODO: implement display modes
// - menu mode
//   > pause menu mode
//   > main menu mode
// - game mode
//   > game scene + hud overlay
//   > inventory menu mode
//   > dialogue menu mode

// TODO: implement a way to switch between those modes
// - maybe have a display function for each individual mode,
//   then have a variable pointing to the current loop mode,
//   and that variable changes inside those modes
//   and have it called here maybe maybe
//   emscripten_set_main_loop( currentMode, 0, 1);
