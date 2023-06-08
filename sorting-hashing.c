/*
 * sorting-hashing.c
 *
 *  Sorting & Hashing
 *  School of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

/* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));

	do{
		printf("----------------------------------------------------------------\n");
		printf("   Sorting & Hashing [----- [chae seohee] [2022041084] -----]   \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;

	return 0;
}

int freeArray(int *a)
{
	if(a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)
{
	int min; // 최소값을 담아둘 변수
	int minindex; // 최소값의 위치를 담아둘 변수
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++) // 외부 for루프: 어디까지 정렬이 진행되었는지 알려줌
	{
		minindex = i; // minindex에는 정렬되지 않은 배열의 가장 앞 원소인덱스
		min = a[i]; // min에는 정렬되지 않은 배열의 가장 앞 원소값
		for(j = i+1; j < MAX_ARRAY_SIZE; j++) // 내부 for루프: 정렬되지 않은 배열 안에서 가장 작은 값을 선택
		{
			if (min > a[j]) // min에 들어있는 값이 j번째 원소보다 작으면
			{
				min = a[j]; // min에 j번째 원소값을 넣고
				minindex = j; // minindex에 j저장  
			}
		}
		// 내부 for루프를 돌고나서 선택된 정렬되지 않은 배열 안에서 가장 작은 값과 i번째원소를 교환 
		a[minindex] = a[i]; 
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++) // 외부 for루프: 정렬된 배열과 정렬되지 않은 배열을 구분함(0 ~ i-1은 정렬된 배열, i~ maxsize-1은 정렬되지 않은 배열)
	{
		t = a[i]; // t는 정렬되지 않은 첫번째
		j = i; // j에는 t값의 인덱스값 저장
		while (a[j-1] > t && j > 0) // 내부 for루프: 정렬되지 않은 배열의 첫번째 원소를 선택해 정렬된 배열 안에서 삽입할 위치까지 이동
		{ 
			a[j] = a[j-1]; 
			j--;
		}
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 0; i < MAX_ARRAY_SIZE; i++) // 외부 for루프: 총 max_size번만큼 실행(1번 실행할 때마다 가장 큰 원소가 맨 뒤에 정렬됨)
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++) // 내부 for루프: max_size-1번만큼 앞뒤원소 비교하고 swap
		{
			if (a[j-1] > a[j]) // 서로 접해있는 두 개의 원소를 비교했을 때 앞쪽에 위치한 수가 더 큰 경우에 두 원소를 swap
			{
				t = a[j-1]; 
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

// 삽입정렬을 보완한 정렬
int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)
	{
		for (i = 0; i < h; i++)
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j];
				k = j;
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n-1]; //pivot값은 주어진 배열의 마지막 원소
		i = -1;
		j = n - 1;

		while(1)
		{
			while(a[++i] < v);
			while(a[--j] > v);

			if (i >= j) break;
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i);
		quickSort(a+i+1, n-i-1);
	}


	return 0;
}

int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE; // 해시코드는 키값에 대한 모듈러연산으로 도출
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	// 해시테이블의 모든 값을 -1로 초기화
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);

		if (hashtable[hashcode] == -1) // hashcode값의 해시테이블이 비어있는 경우
		{
			hashtable[hashcode] = key; // key값을 그 해시테이블에 삽입하고
		} 
		else 	// hashcode값의 해시테이블에 이미 다른 값이 존재하는 경우
		{
			index = hashcode; 

			while(hashtable[index] != -1) // 빈 해시테이블을 찾을 때까지 해시코드를 변경
			{
				index = (++index) % MAX_HASH_TABLE_SIZE; 
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key); // key에 대한 index값을 찾고

	if(ht[index] == key) // 해시 테이블의 index번째 원소로 가서 key값과 일치하면 
		return index; // 그 인덱스를 리턴

	// 그 외의 경우
	while(ht[++index] != key) // while루프를 통해 key값이 같은 index를 찾을 때까지
	{
		index = index % MAX_HASH_TABLE_SIZE; // index를 다시 모듈러연산
	}
	return index;
}



