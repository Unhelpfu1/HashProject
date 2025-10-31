// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Generate a hash based on a string and another hash
extern "C" __declspec(dllexport) // Export the hash func
unsigned char* __stdcall hashNode(char* command, unsigned char* nextHash){
	unsigned char* hash = (unsigned char*)malloc(sizeof(unsigned char) * 5);

	for (int i = 0; i < 5; i++) {
		hash[i] = 0;
	}

	if (command != NULL) {
		for (int i = 0; i < strlen(command); i++) {
			hash[0] ^= command[i]; // apply a bunch of transformations
			hash[i % 2] &= command[i];
			hash[i % 3] |= command[i];
			hash[i % 4] ^= ~(command[i]) << 1;
			hash[i % 5] &= ~command[i] >> 1;
		}
	}


	if (nextHash != NULL) { // If next hash isn't null
		for (int i = 0; i < 5; i++) {
			hash[i] = hash[i] + nextHash[i] % 256;
		}
	}
	else {
		for (int i = 0; i < 5; i++) {
			hash[i] = hash[i] + 10 * i % 256; // Default seed values instead of previous hash
		}
	}

	//printf("Hashed Value: %x\n", hash); //DEBUG
	return hash;
}


BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	//printf("Hello from HashProject DLL\n"); // DEBUG
    
	switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

