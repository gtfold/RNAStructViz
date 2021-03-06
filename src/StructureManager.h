/*
    A class that manages the RNA structures that have been loaded.
*/

#ifndef STRUCTUREMANAGER_H
#define STRUCTUREMANAGER_H

#include <vector>

#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Pack.H>
#include <FL/Fl_Scroll.H>

#include "RNAStructure.h"
#include "FolderStructure.h"

class StructureManager
{
    public:
        StructureManager();
        ~StructureManager();

        /*
	    Add a new structure, given as a file name to load.
        */
        void AddFile(const char* filename, bool removeDuplicateStructs = true, bool guiQuiet = false);

        /*
	    Remove a structure.
        */
        void RemoveStructure(const int index);
    
        /*
         Remove a folder.
        */
        void RemoveFolder(const int index);

        /*
	    Get the number of structures. Some may be NULL.
        */
        inline int GetStructureCount() const
        {
	        return m_structureCount;
        }

        /*
	     Get a structure.
        */
        inline RNAStructure* GetStructure(const int index)
        {
	        return m_structures[index];
        }

	inline RNAStructure* LookupStructureByCTPath(const char *ctPath) {
	     if(ctPath == NULL) {
	          return NULL;
	     }
	     for(int sidx = 0; sidx < m_structureCount; sidx++) {
	          RNAStructure *rnaStruct = GetStructure(sidx);
		  if((rnaStruct != NULL) && !strcmp(rnaStruct->GetFilename(), ctPath)) {
	               return rnaStruct;
		  }
	     }
	     return NULL;
	}

	inline int LookupStructureIndexByCTPath(const char *ctPath) {
	     if(ctPath == NULL) {
	          return -1;
	     }
	     for(int sidx = 0; sidx < m_structureCount; sidx++) {
	          RNAStructure *rnaStruct = GetStructure(sidx);
		  if((rnaStruct != NULL) && !strcmp(rnaStruct->GetFilename(), ctPath)) {
	               return sidx;
		  }
	     }
	     return -1;
	}

	/* 
	 * Check if a folder with the same name already exists:
	 */
	inline bool FolderNameExists(const char *newFolderName) {
             if(newFolderName == NULL || !strcmp(newFolderName, "")) {
	          return true;
	     }
	     for(unsigned int fi = 0; fi < folders.size(); fi++) {
                  if(folders[fi] != NULL && !strcmp(folders[fi]->folderName, newFolderName)) {
		       return true;
		  }
	     }
             return false;
	}

	/* 
	 * Check if a duplicate structure already exists in the folder: 
	 */
	inline bool DuplicateStructureExistsInFolder(RNAStructure *structToLoad) {
	     if(structToLoad == NULL) {
	          return false;
	     }
	     for(unsigned int fi = 0; fi < folders.size(); fi++) {
	          for(int j = 0; j < folders[fi]->structCount; j++) {
	               RNAStructure *compStruct = m_structures[folders[fi]->folderStructs[j]];
		       if(compStruct != NULL && SequenceCompare(compStruct, structToLoad)) {
	                    return true;
		       }
		  }
	     }
	     return false;
	}

        /*
	    Popup (or bring to front) a window displaying the file contents.
        */
        void DisplayFileContents(const int index, 
			         const char *displaySuffix = NULL);
    
        /*
         Update Diagram Window, Stats Window, and Folder Window for a folder.
         */
        void AddNewStructure(const int folderIndex, const int index);
    
        inline Folder* GetFolderAt(int index)
        {
             if(index >= 0 && index < folders.size()) {
	          return folders[index];
	     }
	     return NULL;
        }
    
        /*
         Returns a pointer to all the folders.
         */
        inline const std::vector<Folder*>& GetFolders() const
        {
            return folders;
        }
    
        /*
         Decrease the structCount of a folder by 1;
         */
        void DecreaseStructCount(const int index);
    
        /*
         Function for testing purposes.
         */
        void PrintFolders();

    private:
        /*
         Add structures to program
         Initializes folders and m_structures on the first occurance
         */
        int AddFirstEmpty(RNAStructure* structure, bool excludeDuplicateStructs = false);
    
        // Creates a new folder for that structure
        void AddFolder(RNAStructure* structure, const int index);
    
        // The allocated size of m_structures
        int m_structureCount;

        // A non-packed array of pointers to structures. Can have 0 entries.
        RNAStructure** m_structures;
    
        // Vector of folders
        std::vector<Folder*> folders;
    
	// Keep track of the InputWindow used to fetch input folder name input from the user:
	InputWindow *m_inputWindow;

        /*
         Compares two RNAStructures, if the sequences of the structures are the same
         returns true, and false otherwise.
         */
        bool SequenceCompare(RNAStructure* struct1, RNAStructure* struct2) const;

};

#endif //STRUCTUREMANAGER_H
