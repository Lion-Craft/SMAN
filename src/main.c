/*
BSD 3-Clause License

Copyright (c) 2025, Leon Frommholz

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

//  Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "connect.h"

//	This section should be revised eventually
#define MAX_ENTRIES 100 // Maximum number of entries to handle
#define MAX_LINE_LENGTH 256
#define MAX_NAME_LENGTH 32
#define MAX_USERNAME_LENGTH 32
#define MAX_ADDRESS_LENGTH 64


typedef struct {
    char name[MAX_NAME_LENGTH];
    char username[MAX_USERNAME_LENGTH];
    char address[MAX_ADDRESS_LENGTH];
    int port;
    int useSSHKey;
} ConfigEntry;

int main() {
    //  Variables
    int iSelection;
    FILE *pConfig;
    char strConfigContent[MAX_LINE_LENGTH];
    ConfigEntry configEntries[MAX_ENTRIES];
    int entryCount = 0;
    int i;

	//	Define Platform-Specific paths
	#ifdef __WIN32__	//	Windows
    //  Open config file
	char* strPath = getenv("LOCALAPPDATA");
	strcat(strPath, "\\SMAN\\sman.conf");
    pConfig = fopen(strPath, "r");
	if (pConfig == NULL) {
        perror("Error opening config file (Platform: Windows)");
        return 1;
    }
	#else	// Unix/Unix-like
	//  Open config file
	char* strPath = getenv("HOME");
	strcat(strPath, "/.config/sman.conf");
    pConfig = fopen(strPath, "r");
	if (pConfig == NULL) {
        perror("Error opening config file (Platform: UNIX)");
        return 1;
    }
	#endif

    //  Read config contents
    while (fgets(strConfigContent, MAX_LINE_LENGTH, pConfig) != NULL && entryCount < MAX_ENTRIES) {
        // Parse the line
        char *token;
        char *name = strtok(strConfigContent, ";");
        char *username = strtok(NULL, ";");
        char *address = strtok(NULL, ";");
        char *portStr = strtok(NULL, ";");
        char *useSSHKeyStr = strtok(NULL, ";");

        if (name != NULL && username != NULL && address != NULL && portStr != NULL && useSSHKeyStr != NULL) {
            // Store the values in the ConfigEntry struct
            strncpy(configEntries[entryCount].name, name, MAX_NAME_LENGTH - 1);
            configEntries[entryCount].name[MAX_NAME_LENGTH - 1] = '\0'; // Ensure null termination

            strncpy(configEntries[entryCount].username, username, MAX_USERNAME_LENGTH - 1);
            configEntries[entryCount].username[MAX_USERNAME_LENGTH - 1] = '\0';

            strncpy(configEntries[entryCount].address, address, MAX_ADDRESS_LENGTH - 1);
            configEntries[entryCount].address[MAX_ADDRESS_LENGTH - 1] = '\0';

            configEntries[entryCount].port = atoi(portStr);
            configEntries[entryCount].useSSHKey = atoi(useSSHKeyStr);

            entryCount++;
        } else {
            fprintf(stderr, "Warning: Invalid line in config file: %s", strConfigContent);
        }
    }

    //  Close config file
    fclose(pConfig);

    //  Temporarily set iSelection to 1
    iSelection = 1;

    //  Main Loop. Enter a number below 0 to exit
    while (iSelection >= 1)
    {
        //  Welcome Message
        printf("SSH Session Manager\n");

        //  Help Message
        printf("\nEnter 0 or Ctrl+C to Exit.\n\n");

        //  Present the list to the user
        printf("Available Connections:\n");
        for (i = 0; i < entryCount; i++) 
        {
            printf("%d: %s (%s@%s:%d)\n", i + 1, configEntries[i].name, configEntries[i].username, configEntries[i].address, configEntries[i].port);
        }

        //  Read User selection
        printf("Enter the number of the connection to use: ");
        if (scanf("%d", &iSelection) != 1) 
        {
            fprintf(stderr, "Invalid input.\n");
            return 1;
        }

        // Validate the selection
        if (iSelection > entryCount) 
        {
            fprintf(stderr, "Invalid selection.\n");
            return 1;
        }

        if (iSelection < 1) 
        {
            printf("Exiting.\n");
            return 0;
        }

        //  Call sshConnect with the selected entry
        sshConnect(configEntries[iSelection - 1].address, configEntries[iSelection - 1].username, configEntries[iSelection - 1].port);
    }

    //  Exit Code
    return 0;
}
