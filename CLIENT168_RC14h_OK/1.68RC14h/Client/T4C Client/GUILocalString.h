#ifndef GUILOCALSTRING_H
#define GUILOCALSTRING_H

// Include File
#include <stdio.h>
#include <vector>

class GUILocalString {
// Class that load and provide localized string.

	private:
        std::vector< char * > LanguageString; // String Array
        std::vector< char >	  bHotKey;        // String Array
        DWORD                 dwStringNb;     // Number of String
		CRITICAL_SECTION      csLanguageLock; // Lock
		bool bCreated;

		void LoadAllStrings( int dwLanguage); // Load all string in file.
		
	public:

		GUILocalString(void);  // Constructor
		~GUILocalString(void); // Destructor

		void Create( int dwLanguage);  // Open Local String file and put all string into memory.
		void Release(void); // Close the Local String file.

		char *operator[](unsigned int l); // Get A string.

		char GetHotKey(int l);
      void CannotParse(void);
};

// Global Var;
extern GUILocalString g_GUILocalString;

#endif