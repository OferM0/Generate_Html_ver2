typedef struct sampleList {

	//REAL DATA
	proccessList* pList; //proccess list
	unsigned short proccessCnt;

	//sample data
	char sampleTime[100];
	unsigned short sampleCnt;

	//STRUCT MANAGMENT
	struct sampleList* next;
	struct sampleList* prev;
}sampleList;

//add sample item to the list
sampleList* addSampleItem(proccessList* pList, unsigned short proccessCnt, char sampleTime[100], unsigned short sampleCnt);

void resetSampleList(); //reset sampleHead/Tail to NULL

void resetCollections(); //free sample list memory

proccessList* getFullProccessListBySampleList(sampleList* sList); //create full connected proccess list of all samples
