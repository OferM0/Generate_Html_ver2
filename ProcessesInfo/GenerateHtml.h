void generateHtml(sampleList* sList); //generate html site

SIZE_T getMemoryAvg(sampleList* sList); //average memory for each sample item

unsigned short getDllCnt(sampleList* sList); //get dll cnt sum of all proccesses in sample item

char* createLink(char arr[10], unsigned short cnt); //create link to page

//create sorted sample html link to page
char* createSortSampleHtmlLink(unsigned char cnt);

//create sample html page- show sample number, time and it's proccess list
void createSampleHtml(sampleList* sList, char sampleHtmlName[20]); 

dllList* removeMultiplies(sampleList* sList); //remove dll multiplies in whole sample list

SIZE_T highestMemory(proccessList* pList); //get highest memory by workingSetSize value

//create sorted sample html page- show sample number, time and it's proccess list sorted by dll cnt
void createSortSampleHtml(proccessList* pList, char sampleHtmlName[20], char sortSampleHtmlName[30]);

proccessList* removeProccessMultiplies(proccessList* pList); //remove proccess multiplies in proccess list 

proccessList* getProccessListByDllName(sampleList* sList, char dllName[500]); //get new proccess list which use dll with this name 

//create dll html page- show number of proccess used this dll, dll name and proccess list
void createDllHtml(sampleList* sList, char dllHtmlName[20], char dllName[500]);