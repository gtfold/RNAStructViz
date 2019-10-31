#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <locale.h>

#include <FL/Fl.H>
#include <FL/Enumerations.H>

#ifdef WITHGPERFTOOLS
#include <gperftools/heap-profiler.h>
#endif

#include "MainWindow.h"
#include "RNAStructViz.h"
#include "ConfigOptions.h"
#include "ConfigParser.h"
#include "DisplayConfigWindow.h"
#include "TerminalPrinting.h"

char rnaStructVizExecPath[MAX_BUFFER_SIZE];
char runtimeCWDPath[MAX_BUFFER_SIZE];
char activeSystemUserFromEnv[MAX_BUFFER_SIZE];

int main(int argc, char **argv) {

    #ifdef WITHGPERFTOOLS
    HeapProfilerStart("RNAStructViz.log");
    #endif
   
    DisplayConfigWindow::SetupInitialConfig();
    strncpy(rnaStructVizExecPath, argv[0], MAX_BUFFER_SIZE);
    rnaStructVizExecPath[MAX_BUFFER_SIZE - 1] = '\0';
    getcwd(runtimeCWDPath, MAX_BUFFER_SIZE);
    runtimeCWDPath[MAX_BUFFER_SIZE - 1] = '\0';
    getUserNameFromEnv(activeSystemUserFromEnv, MAX_BUFFER_SIZE);
    
    // TODO: --quiet, --help, --about, --new-config, --no-ansi-color, --no-unicode, ... 
    if(argc > 1 && 
       (!strcmp(argv[1], "--about") || !strcmp(argv[0], "--help") || 
	!strcmp(argv[1], "-h"))) {
        ApplicationBuildInfo::PrintAboutListing(stdout);
        return 0;
    }
    else if(argc > 1 && !strcmp(argv[1], "--debug")) {
        DEBUGGING_ON = true;
	CFG_DEBUG_MODE = CFG_VERBOSE_MODE = true;
	TerminalText::PrintDebug("THEME WINDOW BGCOLOR: 0x%08x\n", GUI_WINDOW_BGCOLOR);
	TerminalText::PrintDebug("THEME WIDGET COLOR:   0x%08x\n", GUI_BGCOLOR);
	TerminalText::PrintDebug("THEME BTEXT COLOR:    0x%08x\n", GUI_BTEXT_COLOR);
	TerminalText::PrintDebug("THEME TEXT COLOR:     0x%08x\n", GUI_TEXT_COLOR);
	argv[1] = argv[0]; // remove our custom option before parsing 
	++argv; --argc;
    }	
    RNAStructViz::Initialize(argc, argv);
    
    Fl::option(Fl::OPTION_VISIBLE_FOCUS, false);
    Fl::option(Fl::OPTION_SHOW_TOOLTIPS, true);
    Fl::option(Fl::OPTION_FNFC_USES_GTK, false);
    
    Fl_File_Icon::load_system_icons();
    Fl::scheme((char *) FLTK_THEME);
    MainWindow::ResetThemeColormaps();
    fl_font(LOCAL_BFFONT, LOCAL_TEXT_SIZE);
    //Fl::add_handler(RNAStructViz::HandleGlobalKeypressEvent);

    if(DISPLAY_FIRSTRUN_MESSAGE) {
         MainWindow::GetInstance()->DisplayFirstTimeUserInstructions();
    }
    while(MainWindow::IsRunning()) {
        Fl::wait();
    }
    //Fl::remove_handler(RNAStructViz::HandleGlobalKeypressEvent);
    RNAStructViz::Shutdown();
    
    #ifdef WITHGPERFTOOLS
    HeapProfilerStop();
    #endif
    
    return EXIT_SUCCESS;

}

