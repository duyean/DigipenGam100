#pragma once

/*
==================================
		Choco Mochi Pie
		 Scene Package

		- CMP Scene Pak - 
Inherit in every Scene File.

This allows each scene to have 
access to the Transition System 
that is used to change scenes.
-Day
		- CMP Scene Pak - 
===================================

What is day listening to right now, 
   while refactoring your code?
   https://youtu.be/dWvVCHyn7tU
*/

//Main Transition Include
#include "Transitions/transition.h"

//Each Scene Includes Required to Function.
#include "Scenes/State - Main Menu/mainmenu.h"
#include "Scenes/State - Play/game.h"
#include "Scenes/State - Settings/settingsmenu.h"
#include "Scenes/State - Title Card/intro.h"
#include "Scenes/State - Credits/credits.h"
#include "Scenes/State - Cutscene/cutscene.h"
