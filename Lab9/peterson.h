#define TRUE 1
#define FALSE 0
struct Memory {
	int  turn;
	int flag[2];
};
void initializePeterson();
void removePeterson();
void enterCriticalSection(int i);
int exitCriticalSection(int i);

