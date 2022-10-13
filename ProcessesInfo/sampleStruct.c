#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <windows.h>
#include <psapi.h>
#include "dllStruct.h"
#include "proccesStruct.h"
#include "sampleStruct.h"
#include "log.h"
#pragma warning(disable:4996)

sampleList* sampleHead = NULL;
sampleList* sampleTail = NULL;

//add sample item to the list
sampleList* addSampleItem(proccessList* pList, unsigned short proccessCnt, char sampleTime[100], unsigned short sampleCnt)
{
	sampleList* curr;
	curr = (sampleList*)malloc(sizeof(sampleList)); //memory allocation
	if (!curr) //allocation check
	{
		Log_Error(strerror(GetLastError()));
		return;
	}
	Log_Event("adding sample item.\n");
	curr->next = NULL;
	curr->prev = NULL;

	//put values to item
	curr->pList = pList;
	curr->proccessCnt = proccessCnt;
	strcpy(curr->sampleTime, sampleTime);
	curr->sampleCnt = sampleCnt;

	if (sampleHead == NULL) //if list is empty
	{
		sampleHead = curr;
		sampleTail = curr;
	}
	else //if not empty
	{
		sampleTail->next = curr;
		curr->prev = sampleTail;
		sampleTail = curr;
	}

	return sampleHead;
}

void resetSampleList() //reset sampleHead/Tail to NULL
{
	sampleHead = NULL;
	sampleTail = NULL;
	Log_Event("Reset Sample List.\n");
}


void resetCollections() //free sample list memory
{
	dllList* currentDll;
	dllList* releaseDll;
	proccessList* currentProccess;
	proccessList* releaseProccess;
	sampleList* currentSample = sampleHead;
	sampleList* releaseSample = sampleHead;

	Log_Event("Free Sample memory.\n");

	while (currentSample != NULL)
	{
		currentProccess = currentSample->pList;
		releaseProccess = currentSample->pList;

		while (currentProccess != NULL)
		{
			currentDll = currentProccess->dList;
			releaseDll = currentProccess->dList;

			while (currentDll != NULL)
			{
				releaseDll = currentDll;
				currentDll = currentDll->next;
				free(releaseDll); //free dll item
			}
			releaseProccess = currentProccess;
			currentProccess = currentProccess->next;
			free(releaseProccess); //free proccess item
		}
		releaseSample = currentSample;
		currentSample = currentSample->next;
		free(releaseSample); //free sample item
	}
}

proccessList* getFullProccessListBySampleList(sampleList* sList) //create full connected proccess list of all samples
{
	proccessList* curr;
	proccessList* copy = NULL;
	proccessList* pList;

	while (sList != NULL)
	{
		pList = sList->pList; //head of proccess list in sample item

		while (pList != NULL)
		{
			curr = (proccessList*)malloc(sizeof(proccessList)); //memory allocation
			if (!curr) //allocation check
			{
				Log_Error(strerror(GetLastError()));
				printf("Error of memory\n");
				return;
			}

			curr->next = NULL;
			curr->prev = NULL;

			//copy values to item
			strcpy(curr->processName, pList->processName);
			curr->proccessId = pList->proccessId;
			//curr->PageFaultCount = pList->PageFaultCount;
			//curr->WorkingSetSize = pList->WorkingSetSize;
			//curr->QuotaPagedPoolUsage = pList->QuotaPagedPoolUsage;
			//curr->QuotaPeakPagedPoolUsage = pList->QuotaPeakPagedPoolUsage;
			//curr->PagefileUsage = pList->PagefileUsage;
			//curr->dList = pList->dList;
			//curr->dllCnt = pList->dllCnt;

			if (copy == NULL) //if list is empty
			{
				copy = curr;
			}
			else { //if list is not empty
				while (copy->next != NULL) //get the pointer to tail of list
				{
					copy = copy->next;
				}

				copy->next = curr;
				curr->prev = copy;
				copy = curr;
			}

			pList = pList->next; //next item in proccess list
		}
		sList = sList->next; //next sample in sample list
	}

	if (copy != NULL)
	{
		while (copy->prev != NULL) //get the pointer to head of list
		{
			copy = copy->prev;
		}
	}

	return copy;
}