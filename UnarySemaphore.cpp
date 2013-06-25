#if 0

// This class is just a joke!
// We made it while taking a break and included it since we thought you'd get a laugh out of it.
// We're obviously not serious (:

class UnarySemaphore {
public:
	UnarySemaphore();
	~UnarySemaphore();
	void P();
	void V();
	void QuantumPV();
}

UnarySemaphore::UnarySemaphore() {
#define VOODOOMAGIC int (*(*foo)(void ))(void , void *)
/* declare foo as pointer to function (void) returning pointer to function (void, pointer to void) returning int */

#define SCAREAWAYMYBOSS __fastcall (*LPOSVERSIONINFOEX)(void*, int*, long*, float*, double*, HANDLE, VOODOOMAGIC)
	void* waste = 1;
	while (waste) {
		waste = malloc(1); // Leave room to improve in the future if I need a raise
	}
	throw new std::runtime_error("Something went wrong. Better get Dave the Programmer on the job. Hope you didn't fire him! Consulting services start at $300 per hour, call (555) 555-5555.");
}

UnarySemaphore::~UnarySemaphore() {
	// No free() call
}

void UnarySemaphore::P() {
	SuspendThread(GetCurrentThread());
}

void UnarySemaphore::V() {
	throw new UnsupportedOperationException();
}

// It's either P or V, depending on when you observe it
void UnarySemaphore::QuantumPV() {
	seed(time());
	if (rand() % 2) {
		this->P();
	}
	else {
		this->V();
	}
}

#endif