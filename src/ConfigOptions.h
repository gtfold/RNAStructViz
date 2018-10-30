/* ConfigOptions.h : Header for the user-configurable program options; 
 * Author: Maxie D. Schmidt (maxieds@gmail.com) 
 * Created: 2018.10.20
 */

#ifndef _CONFIG_OPTIONS_H_
#define _CONFIG_OPTIONS_H_

#include <FL/Fl.H>
#include <FL/Enumerations.H>

#ifdef TARGETOS_LINUX
     #define __TARGETOS_LINUX__
     #define TARGETOS "GNU/Linux"
#endif
#ifdef TARGETOS_MACOSX
     #define __TARGETOS_APPLE__
     #define TARGETOS "Mac/OSX"
#endif
#ifdef TARGETOS_GENERIC_UNIX
     #define __TARGETOS_UNIX__
     #define TARGETOS "Unix"
#endif

#define RNASTRUCTVIZ_VERSION_STRING    ("RNAStructViz v1.0")

#define FLTK_USE_CAIRO 1
#define FLTK_HAVE_CAIRO 1

#define MAX_BUFFER_SIZE                 (256)

#define DEFAULT_CTFILE_SEARCH_DIRECTORY ("./")
#define DEFAULT_PNG_OUTPUT_DIRECTORY    ("./")
#define DEFAULT_PNG_OUTPUT_PATH         ("RNAStructViz-GUIView-%F-%H%M%S.png") 
                                        /* As a strftime format string */
#define DEFAULT_FLTK_THEME              ("local")
#define FLTK_THEME_COUNT                (6)
#define USER_CONFIG_PATH                ("~/.RNAStructViz/config.cfg")

extern char CTFILE_SEARCH_DIRECTORY[MAX_BUFFER_SIZE];
extern char PNG_OUTPUT_DIRECTORY[MAX_BUFFER_SIZE];
extern char PNG_OUTPUT_PATH[MAX_BUFFER_SIZE];
extern char FLTK_THEME[MAX_BUFFER_SIZE];
extern const char *ALL_FLTK_THEMES[FLTK_THEME_COUNT];
extern const char *FLTK_THEME_HELP[FLTK_THEME_COUNT];
extern char LIBFLTK_VERSION_STRING[MAX_BUFFER_SIZE];

/* Some basic color operations for getting shades of color: */
#define RGBColor(r, g, b)               (((r & 0xff) << 24) | ((g & 0xff) << 16) | ((b & 0xff) << 8))
#define Lighter(color, alpha)           (fl_color_average(color, FL_WHITE, alpha))
#define Darker(color, alpha)            (fl_color_average(color, FL_BLACK, alpha))
#define Inactive(color)                 (fl_inactive(color))
#define Contrast(color)                 (fl_contrast(color, FL_WHITE))
#define GetRed(flc)                     ((flc >> 24) & 0x000000ff)
#define GetGreen(flc)                   ((flc >> 16) & 0x000000ff)
#define GetBlue(flc)                    ((flc >> 8) & 0x000000ff)

/* Local "theme" defines for RNAStructViz: */
#define LOCAL_WINDOW_BGCOLOR            (FL_WHITE)
#define LOCAL_FGCOLOR                   (FL_DARK1)
#define LOCAL_BG2COLOR                  (FL_LIGHT2)
#define LOCAL_HIGHLIGHT_COLOR           (FL_LIGHT3)
#define LOCAL_BGCOLOR                   (RGBColor(123, 77, 211))
#define LOCAL_BUTTON_COLOR              (Lighter(RGBColor(210, 194, 240), 0.5f))
#define LOCAL_TEXT_COLOR                (RGBColor(52, 25, 102))
//#define LOCAL_BGCOLOR                   (RGBColor(0x1F, 0x78, 0x0D))
//#define LOCAL_BUTTON_COLOR              (RGBColor(0xB9, 0xDA, 0xB5))
//#define LOCAL_TEXT_COLOR                (Lighter(RGBColor(0x13, 0x48, 0x09), 0.95f))
#define LOCAL_TEXT_SIZE                 (12)
#define LOCAL_RMFONT                    (FL_SCREEN)
#define LOCAL_BFFONT                    (FL_SCREEN_BOLD)

extern Fl_Color GUI_WINDOW_BGCOLOR;
extern Fl_Color GUI_BGCOLOR;
extern Fl_Color GUI_BTEXT_COLOR;
extern Fl_Color GUI_TEXT_COLOR;

#endif
