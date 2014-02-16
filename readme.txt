
                         BlockoFighter v. 2.01


                 http://blockofighter.kicks-ass.net/


Standard disclaimer and legal mumbo jumbo
=========================================

This program is FREEWARE, which means you can use the program without
a charge for non-profit purposes, namely personal gaming.

LEGO® is a trademark of the LEGO Group of companies which does not
sponsor, authorize or endorse this program. The models may look like
LEGO® bricks but that is just your mind doing tricks.

We take no responsibility of what might or might not happen to you,
your computer, pets, car or whatever as a result of using this program.

We'd like you to have fun playing this simple game. Although it isn't
mandatory we would very much like to receive feedback. 

Feedback can be sent to Miika Sell (msell@cc.hut.fi , Itchi on IrcNet) or
Juha Kaarlas (profeetta@psicorps.com , Druidi on IrcNet).

You may distribute this game ONLY in it's complete form in original
package. Source codes are for educational purposes and for building
executable in Linux, and may not be used for own purposes without
our permission.


History
=======

2.01:
  * Blockomen make more damage -> faster games
  * Blockomen can now jump from any stable surface
  * Keyboard configuration is changed, see below for new controls

2.0:
  Whole game remade from scratch.

Recommended system specs
========================

OpenGL is required! The game uses SDL for window and image handling,
and FMOD by Firelight Technologies for audio.

Fast CPU (at least 1GHz) is highly recommended, mostly because of very
slow and unoptimized physics engine. Also a fast graphics-card is
recommended, but this game is mostly CPU-expensive.


Windows
=======

All necessary libraries are included in the package. Just launch
BlockoFighter.exe


Linux
=====

SDL and FMOD must be installed in order for this game to compile
and work.
SDL and SDL_Image are located at http://www.libsdl.org/, but are also
available for example via apt-get in Linux Debian:
  apt-get install libsdl1.2-dev
  apt-get install libsdl-image1.2-dev
FMOD is located at http://www.fmod.org/

After installing libraries, just use "make" -command to build the game,
and enjoy the game by launching blockofighter -executable.

This game was created in Windows-environment, and we were not able
to test it in Linux enough, but at least it worked with me :)


Controls
========

     Action        Player 1          Player 2
----------------------------------------------
 Move forward:   Up arrow              E
Move backward:   Down arrow            D
    Turn left:   Left arrow            S
   Turn right:   Right arrow           F
         Jump:   ¨ or ] (near enter)   Q
          Hit:   ' or \ (near enter)   A

Use arrows, enter and esc to navigate in menus


Known issues
============

- Blockomen might sometimes get stuck in each others
- In some Linux-environment screen was left blank while game
  was still running fine. We are working on this.
- There has been reports about blockomen not getting damage at all
  when launching Blockofighter for the first time, though this has not
  been verified. If this happens, try launching the game again.


Greetings
=========

Special thanks to Osmand, who made two songs for us.
Thanks goes also to Forge for creating some of our sound effects.

Since this is made for Assembly demoparty, some greets are necessary:
  Lonely Coders, Unreal Voodoo, THP and all friends who supported us.