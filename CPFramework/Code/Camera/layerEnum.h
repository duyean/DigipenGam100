#pragma once

typedef enum {
    PARALLAX_BACKGROUND,
    PARALLAX_CENTER,
    PARALLAX_FOREGROUND,
    PARALLAX_UI
} ParallaxDepth;

/*
Day here, to tell you!

Background  >   Walls/Doors
Center      >   Player/Monster
Foreground  >   Decorative pieces that will obstruct the player and camera (ie. vines, pipes, etc)
UI          >   HUD/Menu (If. applicable, I'm not sure how you all want to use this!)
*/