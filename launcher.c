/*
	Course: CS 30200
  	Name: Luis Norman
  	Assignment: 2
 */

#include <windows.h>
#include <stdio.h>

// function prototype
void printError(char* functionName);


int main(void)
{
   int selection;
   
   #define NUMBER_OF_PROCESSES 5
   LPTSTR lpCommandLine[NUMBER_OF_PROCESSES];
   PROCESS_INFORMATION processInfo[NUMBER_OF_PROCESSES];

   STARTUPINFO startInfo;

   ZeroMemory(&startInfo, sizeof(startInfo));
   startInfo.cb = sizeof(startInfo);
   

   /* 
   set up the command lines 
   My applications and its path are a bit strange due to me using parallels on mac		
   */
   lpCommandLine[0] = "C:\\Windows\\notepad.exe";
   lpCommandLine[1] = "C:\\Program Files\\WIndows NT\\Accessories\\wordpad.exe";
   lpCommandLine[2] = "C:\\Windows\\system32\\cmd.exe";
   lpCommandLine[3] = "C:\\Windows\\system32\\calc.exe";
   lpCommandLine[4] = "C:\\Windows\\explorer.exe";
   
   					  
   // Loop over laucher program until user wants out
   do {
   	printf("Please make a choice from the following list.\n");
   	printf("  0: Quit\n");
   	printf("  1: Run Notepad\n");
   	printf("  2: Run Wordpad\n");
   	printf(" *3: Run cmd shell\n");
   	printf("  4: Run Calculator\n");
   	printf("  5: Run Explorer\n");
   	printf("Enter you choice now: ");
   	scanf("%d", &selection);
   	
	   
	switch(selection) {
		// User selects quit
   		case 0 : 
   			break;
   			
   		// User selects notepad
		case 1 :
			if( !CreateProcess(NULL, lpCommandLine[selection-1], NULL, NULL, FALSE,
                         HIGH_PRIORITY_CLASS | CREATE_NEW_CONSOLE,
                         NULL, NULL, &startInfo, &processInfo[selection-1]) )
      		{
          		printError("CreateProcess");
      		}
      		else
      		{
         		printf("Started program %d with pid = %d\n\n", selection, (int)processInfo[selection-1].dwProcessId);
         		CloseHandle(processInfo[selection-1].hThread);
     		 	  CloseHandle(processInfo[selection-1].hProcess);
      		}
			break;
		// User selects wordpad	
		case 2 :
			if( !CreateProcess(NULL, lpCommandLine[selection-1], NULL, NULL, FALSE,
                         HIGH_PRIORITY_CLASS | CREATE_NEW_CONSOLE,
                         NULL, NULL, &startInfo, &processInfo[selection-1]) )
      		{
          		printError("CreateProcess");
      		}
      		else
      		{
  	     		printf("Started program %d with pid = %d\n\n", selection, (int)processInfo[selection-1].dwProcessId);
  	     		CloseHandle(processInfo[selection-1].hThread);
     		 	CloseHandle(processInfo[selection-1].hProcess);
      		}
			break;
		// User selects command prompt	
		case 3 :
			startInfo.lpTitle = "What is your command?";
			putenv("prompt=Speak to me$G");
			if( !CreateProcess(NULL, lpCommandLine[selection-1], NULL, NULL, FALSE,
                         HIGH_PRIORITY_CLASS | CREATE_NEW_CONSOLE,
                         NULL, NULL, &startInfo, &processInfo[selection-1] ))
      		{
          		printError("CreateProcess");
      		}
      		else {
      			printf("Started program %d with pid = %d\n", selection, (int)processInfo[selection-1].dwProcessId);
       			printf("   waiting for program %d to terminate...\n", selection);
				WaitForSingleObject(processInfo[selection-1].hProcess, INFINITE);
				DWORD exitCode;
      			int result = GetExitCodeProcess(processInfo[selection-1].hProcess, &exitCode);
       			printf("   program %d exited with return value %d \n\n", selection, exitCode);
       			CloseHandle(processInfo[selection-1].hThread);
     		 	CloseHandle(processInfo[selection-1].hProcess);
      		}
      		
 
			break;
		// User selects calculator	
		case 4 :
			if( !CreateProcess(NULL, lpCommandLine[selection-1], NULL, NULL, FALSE,
                         HIGH_PRIORITY_CLASS | CREATE_NEW_CONSOLE,
                         NULL, NULL, &startInfo, &processInfo[selection-1]) )
      		{
          		printError("CreateProcess");
      		}
      		else
      		{
         		printf("Started program %d with pid = %d\n\n", selection, (int)processInfo[selection-1].dwProcessId);
         		CloseHandle(processInfo[selection-1].hThread);
     		 	CloseHandle(processInfo[selection-1].hProcess);
      		}
			break;
			
		// User selects explorer
		case 5 :
			if( !CreateProcess(NULL, lpCommandLine[selection-1], NULL, NULL, FALSE,
                         HIGH_PRIORITY_CLASS | CREATE_NEW_CONSOLE,
                         NULL, NULL, &startInfo, &processInfo[selection-1]) )
      		{
          		printError("CreateProcess");
      		}
      		else
      		{
         		printf("Started program %d with pid = %d\n\n", selection, (int)processInfo[selection-1].dwProcessId);
         		CloseHandle(processInfo[selection-1].hThread);
     		 	CloseHandle(processInfo[selection-1].hProcess);
      		}
			break;	
   	}
	      
   } while (selection != 0);

   return 0;
}



/****************************************************************
   The following function can be used to print out "meaningfull"
   error messages. If you call a Win32 function and it returns
   with an error condition, then call this function right away and
   pass it a string containing the name of the Win32 function that
   failed. This function will print out a reasonable text message
   explaining the error and then (if chosen) terminate the program.
*/
void printError(char* functionName)
{
   LPVOID lpMsgBuf;
   int error_no;
   error_no = GetLastError();
   FormatMessage(
         FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
         NULL,
         error_no,
         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
         (LPTSTR) &lpMsgBuf,
         0,
         NULL
   );
   // Display the string.
   fprintf(stderr, "\n%s failed on error %d: ", functionName, error_no);
   fprintf(stderr, (char*)lpMsgBuf);
   // Free the buffer.
   LocalFree( lpMsgBuf );
   //ExitProcess(1);  // terminate the program
}//printError

