class sort {
public:
	static void print(int* arr, int start, int end);
	static void print(int* arr, int start, int end, int piv);

	static int* bubbleSort(int* arr, int len);
	static int* insersionSort(int* arr, int len);
	static int* selectionSort(int* arr, int len);
	static int* quickSort(int* arr, int len);
	static int* heapSort(int* arr, int len);
	static int* mergeSort(int* arr, int len);

	static int* invert(int* arr, int len);
private:
	static int* QSPartition(int* arr, int start, int end);

	static int* maxHeapify(int* arr, int len, int end);
	
	static int* merge(int* arr1, int len1, int* arr2, int len2);
	static int* partArray(int* fullArray, int from, int to);
};
