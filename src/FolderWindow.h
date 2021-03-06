/*
    The window that shows the files in a folder.
 */

#ifndef FOLDERWINDOW_H
#define FOLDERWINDOW_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_RGB_Image.H>

#include <vector>
using std::vector;

#include "ConfigOptions.h"
#include "StructureType.h"
#include "RNAStructVizTypes.h"

#define STRUCT_PANE_LABEL_PREFIX         ("\n\n\n\n\n\n\n\n\n\n\n\n\n")

class FolderWindow : public Fl_Group
{

    public:
        void Construct(int w, int h, int folderIndex);
        FolderWindow(int x, int y, int wid, int hgt, const char *label, int folderIndex);
	virtual ~FolderWindow();

        /*
         Add a new sequence to the list of displayed sequences.
         */
        void AddStructure(const char* filename, const int index);

        /*
         Sets up all the structures in the folder.
         */
        void SetStructures(int folderIndex);

	inline void HideFolderWindowGUIDisplay(bool waitForNoVisible = true) {
	     if(folderPack != NULL) {
		 folderPack->hide();
	     }
	     if(folderScroll != NULL) {
	         folderScroll->hide();
	     }
	     this->hide();
	     if(waitForNoVisible) {
	          while(folderPack != NULL && folderPack->visible() || 
		        folderScroll != NULL && folderScroll->visible() || this->visible()) {
		       Fl::wait();
		  }
	     }
	}

    private:

        /*
         Callback to show/hide a file.
         */
        static void ShowFileCallback(Fl_Widget* widget, void* userData);

        /*
         Callback to remove a structure.
         */
        static void RemoveCallback(Fl_Widget* widget, void* userData);

        static void DiagramCallback(Fl_Widget* widget, void* userData);
        static void StatsCallback(Fl_Widget* widget, void* userData);
        
	friend class StructureData;
	friend class Folder;
	friend class StructureManager;
	friend class MainWindow;
	static vector<StructureData*> m_storedStructDisplayData;

	/*
         The scrolling group containing the folder info and files, and the packed group inside it.
         */
        Fl_Scroll *folderScroll;
        Fl_Pack *folderPack;
        
	/* The watermark structure icon at the top of the folder window. */
	Fl_RGB_Image *structureIcon;

        /*
         folderIndex of the folder being shown.
         */
        int m_folderIndex;

	Fl_Box *fileOpsLabel, *fileLabel;
        Fl_Box *structIconBox;
	Fl_Button *statsButton, *diagramButton;

    public:
        void RethemeFolderWindow(); 

};

#endif
