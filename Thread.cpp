#include "thread.h"
#include <stdio.h>

/**
	Creates a new Thread object (creates a new thread in Windows).
	The thread starts out suspended, a function pointer must be set before calling Run().
*/
Thread::Thread() {
	 this->threadHandle = CreateThread(NULL, 0, &Thread::ThreadEntry, 
		 this, CREATE_SUSPENDED, &(this->threadId));
	if (this->threadHandle == INVALID_HANDLE_VALUE) {
		throw new std::exception("Failed to create new thread!");
	}
	this->threadState = 1;
}

/**
	Destroys this Thread object and kills the corresponding thread in Windows.
*/
Thread::~Thread() {
	if (this->State()) {
		this->Kill();
		this->threadState = 0;
	}
}

/**
	Resume this thread.
*/
void Thread::Run() {
	if (this->State() == 1) {
		ResumeThread(this->threadHandle);
		this->threadState = 2;
	}
}

void Thread::Suspend() {
	if (this->State() == 2) {
		SuspendThread(this->threadHandle);
		this->threadState = 1;
	}
}

/**
	Kills the current thread in Windows. Does not destroy this Thread object.
*/
void Thread::Kill() {
	if (this->State()) {
		TerminateThread(this->threadHandle, -1);
		this->threadState = 0;
	}
}

/**
	New thread entry point routine. Calls the user-supplied function.
	The thread will terminate once the user-supplied function returns.
*/
DWORD __stdcall Thread::ThreadEntry(PVOID us) {
	Thread* me = ((Thread*) (us));

	(me->function)(me->params);
	me->threadState = 0;
	return 0;
}

/**
	Get the current thread state.
*/
int Thread::State() {
	return this->threadState;
}