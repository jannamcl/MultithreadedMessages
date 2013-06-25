#ifndef THREAD_H
#define THREAD_H

#define WIN32_MEAN_AND_LEAN
#include <windows.h>
#include <exception>

class Thread {
public:
	Thread();
	~Thread();
	void Suspend();
	void Run();
	void Kill();
	int State();
	void (*function)(void*);
	void* params;

private:
	// The Windows thread ID
	DWORD threadId;
	// Handle of the Windows thread
	HANDLE threadHandle;
	// The thread state. 2 = Running, 1 = Suspended, 0 = Terminated
	int threadState;
	static DWORD __stdcall ThreadEntry(PVOID Params);

};

#endif