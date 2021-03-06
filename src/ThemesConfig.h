/* ThemesConfig.h : Definitions and static themes for use in the application;
 * Author: Maxie D. Schmidt (maxieds@gmail.com)
 * Created: 2018.11.15
 */

#ifndef __THEMES_CONFIG_H__
#define __THEMES_CONFIG_H__

#include <FL/Enumerations.H>
#include <FL/Fl_Text_Display.H>

#include "ConfigExterns.h"
#include "ConfigOptions.h"
#include "RNAStructVizTypes.h"

/*
 * See the following link for the built-in FLTK indexed colors:
 * http://www.fltk.org/doc-1.3/drawing.html#drawing_colors
 */
#define FL_LOCAL_DARK_GRAY                     (36)
#define FL_LOCAL_MEDIUM_GREEN                  (60)
#define FL_LOCAL_DARK_RED                      (80)
#define FL_LOCAL_BRIGHT_YELLOW                 (93)
#define FL_LOCAL_LIGHT_PURPLE                  (192)
#define FL_LOCAL_DEEP_BLUE                     (219)

static const Fl_Text_Display::Style_Table_Entry TEXT_BUFFER_STYLE_TABLE[] = {
     {FL_LOCAL_DARK_GRAY,        FL_SCREEN,             12},    // A -- default
     {FL_LOCAL_MEDIUM_GREEN,     FL_SCREEN,             12},    // B -- pair A
     {FL_LOCAL_DARK_RED,         FL_SCREEN,             12},    // C -- pair C
     {FL_LOCAL_LIGHT_PURPLE,     FL_SCREEN,             12},    // D -- pair G
     {FL_LOCAL_BRIGHT_YELLOW,    FL_SCREEN,             12},    // E -- pair U
     {FL_LOCAL_DEEP_BLUE,        FL_SCREEN_BOLD,        12},    // F -- first pairing
     {FL_LOCAL_DEEP_BLUE,        FL_SCREEN_BOLD,        12},    // G -- second pairing
     {NULL,                      NULL,                  NULL},  // NULL end of array
};

#define TBUFSTYLE_DEFAULT                     ('A')
#define TBUFSTYLE_DEFAULT_STRFMT              ("A")
#define TBUFSTYLE_SEQPAIR_A                   ('B')
#define TBUFSTYLE_SEQPAIR_C                   ('C')
#define TBUFSTYLE_SEQPAIR_G                   ('D')
#define TBUFSTYLE_SEQPAIR_U                   ('E')
#define TBUFSTYLE_BPAIR_START                 ('F')
#define TBUFSTYLE_BPAIR_END                   ('G')
#define TBUFSTYLE_BPAIR_START_STRFMT          ("F")
#define TBUFSTYLE_BPAIR_END_STRFMT            ("G")

extern volatile ColorTheme_t *LOCAL_COLOR_THEME;

static const ColorTheme_t PRESET_COLOR_THEMES[] = {
     {
          0x16161600, 
	  0x39393900, 
	  0x00da0000, 
	  0xd3d3b200,
          0x16161600, 
	  "Green On Black", // standard Linux / command line colors
	  true,
          &GUI_BGCOLOR,
     }, 
     {
          0xc3b68900, 
	  0x00305700, 
	  0xffffee00, 
	  0x0f0f0e00,
          Darker(0xc3b68900, 0.5f), 
	  "Blue on Gold", 
	  true,
	  &GUI_BTEXT_COLOR,
     }, 
     {
          0xeeb50000,
	  0xff6d0000,
	  0x3e3c4000,
	  0x604f0900,
	  Darker(0xeeb50000, 0.7f), 
	  "Sunshine", // very vibrant and bright
	  true,
	  &GUI_BGCOLOR,
     },
     {
          0x98a8a800,
	  0x3a6ea500,
	  0xdffff300,
	  0x24241f00,
	  Darker(0x98a8a800, 0.65f), 
	  "Redmond", // old school Windows 2000 era color scheme
	  true,
	  &GUI_BGCOLOR,
     },
     {
          0xf7efd400,
	  0xefda8d00,
	  0x0f0f0e00,
          0x0f0f0e00,
	  0xf7efd400, 
	  "Parchment",  // black and off white to gold 
	  true,
	  &GUI_BGCOLOR,
     },
     {
          0xf7f7f900,
	  0xcfd2d600,
	  0x00000000,
	  0x00000000,
	  0xf7f7f900, 
	  "Gray on white", 
	  true,
	  &GUI_BTEXT_COLOR,
     },
     {
          0xeff2f200,
	  0xd1d0d800,
	  0x0e014400,
          0x0e0144,
	  0xeff2f200, 
	  "Structviz default", 
	  true,
	  &GUI_BTEXT_COLOR,
    },
    {
          0, 
	  0, 
	  0, 
	  0, 
	  0, 
	  "-- Select Theme --", 
	  false,
	  NULL,
     }
};

static unsigned int NUM_LOCAL_THEMES = sizeof(PRESET_COLOR_THEMES) / sizeof(PRESET_COLOR_THEMES[0]);

static inline ColorTheme_t * GetColorThemeRefByName(const char *themeName) {
     for(int t = 0; t < NUM_LOCAL_THEMES; t++) {
          if(!strcmp(themeName, PRESET_COLOR_THEMES[t].themeName)) {
               return (ColorTheme_t *) &(PRESET_COLOR_THEMES[t]);
	  }
     }
     return NULL;
}

#endif
