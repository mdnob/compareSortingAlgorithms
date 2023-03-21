#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	// recursion
	
	// condition
	if(l < r){
		// middle
		int m = (l + r) / 2;

		// left half
		mergeSort(pData, l, m);

		// right half
		mergeSort(pData, m + 1, r);

		
		int i = 0;
		int j = 0;
		
		int * sort = (int *) malloc((r - l + 1) * sizeof(int));

		extraMemoryAllocated += (r - l + 1) * sizeof(int);
		
		// merge
		while(l + i <= m || m + j + 1 <= r){
			if(m + j + 1 > r){
				sort[i + j] = pData[l + i];
				i++;
			}
			else if(l + i > m){
				sort[i + j] = pData[m + j + 1];
				j++;
			}
			else if(pData[l + i] <= pData[m + j + 1]){
				sort[i + j] = pData[l + i];
				i++;
			}
			else if(pData[l + i] >= pData[m + j + 1]){
				sort[i + j] = pData[m + j + 1];
				j++;
			}
		}

		
		i = 0;

		// copy
		for(int k = l; k <= r; k++){
			pData[k] = sort[i];
			i++;
		}

		free(sort);
	}

}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int i, j;
	int number;
	extraMemoryAllocated = sizeof(number);

	for (i = 1; i < n; i++) {
		number = pData[i];

		for(j = i - 1; j >= 0; j--) {
			// index before number
			if(pData[j] > number) {
				// shifts to the right
				pData[j + 1] = pData[j];
			}
			else {
				break;
			}
		}
		// index before break
		pData[j + 1] = number;
	}
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	for (int i = 0; i < n; i++) {
		for(int j = 0; j < (n - 1) - i; j++) {
			if(pData[j] > pData[j + 1]){
				// swap
				int temp = pData[j];
				pData[j] = pData[j + 1];
				pData[j + 1] = temp;
			}
		}
	}
	extraMemoryAllocated = sizeof(int);
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	int index;

	for(int i = 0; i < n; i++){
		index = i;
		extraMemoryAllocated += sizeof(index);
		
		for(int j = i; j < n; j++){
			// finds index with minimum
			if(pData[j] < pData[index]){
				index = j;
			}
		}
		// swap with minimum
		int temp = pData[i];
		pData[i] = pData[index];
		pData[index] = temp;
	}	
	extraMemoryAllocated = sizeof(int) * 2;
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);

		// Implement parse data block
		int * pData = (int*) malloc(dataSz * sizeof(int));
		int value;
		for(int i = 0; i < dataSz; i++){
			fscanf(inFile,"%d", &value);
			pData[i] = value;
		}
		memcpy(*ppData, pData, dataSz * sizeof(int));
		free(pData);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}