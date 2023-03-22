#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r)
{
	if(l < r)
	{
		int mid, i, j, k;
		mid = (l+r)/2;
		mergeSort(pData, l, mid);
		mergeSort(pData, mid+1, r);

		int size1 = mid - l + 1;
		int size2 = r - mid;
			
		int* left = (int*)malloc(sizeof(int)*size1);
		int* right = (int*)malloc(sizeof(int)*size2);


		for(i = 0; i < size1; i++)
		{
			left[i] = pData[l+i];
		}
		for(j = 0; j < size2; j++)
		{
			right[j] = pData[mid + 1 +j];
		}

		i=0;
		j=0;
		k=l;

		while(i < size1 && j < size2)
		{
			if(left[i] <= right[j])
			{
				pData[k] = left[i];
				i++;
			}
			else
			{
				pData[k] = right[j];
				j++;
			}
			k++;
		}
		while(i < size1)
		{
			pData[k] = left[i];
			i++;
			k++;

		}
		while(j < size2)
		{
			pData[k] = right[j];
			j++;
			k++;
		}
		free(left);
		free(right);
	}
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int i, j, temp;
	for(i = 1; i < n; i++)
	{
		temp = pData[i];
		for(j = i - 1; j >= 0; j--)
		{
			if(pData[j] > temp)
				pData[j+1] = pData[j];
			else
				break;
		}
		pData[j+1] = temp;
	}
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n)
{
	int i, j, temp;
	for(i = 0; i < n-1; i++)
	{
		for(j = 0; j < n-i-1; j++)
		{
			if(pData[j] > pData[j+1])
			{
				temp = pData[j];
				pData[j] = pData[j+1];
				pData[j+1] = temp;
			}
		}
	}
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n)
{
	int i, j, min, temp;

	for(i = 0; i < n-1; i++)
	{
		min = i;
		for(j = i+1; j < n; j++)
		{
			if(pData[j] < pData[min])
				min = j;
		}

		temp = pData[i];
		pData[i] = pData[min];
		pData[min] = temp;
	}
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
		int temp;
		for(int i = 0; i < dataSz; i++)
		{
			temp = 0;
			fscanf(inFile,"%d", &temp);
			ppData[0][i] = temp;
		}
	}
	fclose(inFile);
	
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