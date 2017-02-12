#include "sort.h"
#include <iostream>

void sort::print(int* arr, int start, int end) {
	for (int i = start; i <= end; i++)
		std::cout << arr[i] << " ";

	std::cout << std::endl;
}

void sort::print(int* arr, int start, int end, int piv) {
	for (int i = start; i <= end; i++) {
		if (i == piv)
			std::cout << "[" << arr[i] << "] ";
		else
			std::cout << arr[i] << " ";
	}
	std::cout << std::endl;
}

int* sort::bubbleSort(int* arr, int len) {
	bool sorted = false;

	//goes through the array until no swaps are made 
	do {
		sorted = true;

		//goes through the array and swaps any values that are the wrong way round
		for (int i = 0; i < len - 1; i++) {
			if (arr[i] > arr[i + 1]) {
				int temp = arr[i];
				arr[i] = arr[i + 1];
				arr[i + 1] = temp;
				sorted = false;
			}
		}
		len -= 1;
	} while (!sorted);

	return arr;
}

int* sort::insersionSort(int* arr, int len) {

	//goes through the array 
	for (int i = 0; i < len; i++) {

		//takes the value at the current location and 
		//moves it down untill the value on the left is larger than it
		for (int j = i; j > 0; j--) {

			if (arr[j] > arr[j - 1])
				break;
			else {
				int temp = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = temp;
			}

		}

	}

	return arr;

}

int* sort::selectionSort(int* arr, int len) {

	for (int i = 0; i < len - 1; i++) {

		//finds the larges value
		int largestIndex = 0, largestValue = 0;

		for (int j = i; j < len; j++) {
			if (arr[j] > largestValue) {

				largestValue = arr[j];
				largestIndex = j;
			}
		}

		//swaps the larges values with the current possition
		int temp = arr[i];
		arr[i] = arr[largestIndex];
		arr[largestIndex] = temp;
	}

	sort::invert(arr, len);

	return arr;
}

int* sort::quickSort(int* arr, int len) {

	QSPartition(arr, 0, len - 1);

	return arr;
}

int* QSPartition1(int* arr, int start, int end) {

	std::cout << " (len " << end - start + 1 << ")";
	if (end - start + 1 <= 1) {
		std::cout << "rtn" << std::endl;
		return arr;
	}
	//select pivot
	int pivotVal = arr[end];
	int endPtr = end, startPtr = 0;

	int* sortArr = new int[end - start + 1];

	std::cout << "sorting " << start << " to " << end << " -- " << std::endl;
	//sort::print(arr, start, end);
	//std::cout << std::endl;

	for (int i = start; i <= end; i++) {
		//puts the smaller values at the front of the new arrar and the larger at the end
		if (arr[i] <= pivotVal) {
			sortArr[startPtr] = arr[i];
			//std::cout << "[" << arr[i] << " to " << startPtr << "]" << std::endl;
			startPtr++;
		}
		else {
			sortArr[endPtr] = arr[i];
			//std::cout << "[" << arr[i] << " to " << endPtr << "]" << std::endl;
			endPtr--;
		}

	}
	//print(sortArr, 0, end - start);
	//std::cout << std::endl;

	//pivot should be at startPtr - 1 or endPtr
	//sort left side
	if (endPtr - 1 - start >= 1) {
		//QSPartition(sortArr, start, endPtr - 1);
	}
	//sort right side
	if (end - endPtr + 1 >= 1) {
		//QSPartition(sortArr, endPtr + 1, end);
	}
	//puts the sorted array chunk into the original array
	for (int i = 0; i <= end; i++)
		arr[start + i] = sortArr[i];

	delete sortArr;

	return arr;
}

int* sort::QSPartition(int* arr, int start, int end) {

	//if (end - start <= 0) return arr;
	sort::print(arr, start, end, end);

	int pivot = arr[end];
	int startPtr = start, endPtr = end;
	int* sortArr = new int[end - start + 1];

	//puts the current array into the copy
	for (int i = 0; i <= end; i++)
		sortArr[i] = arr[start + i];

	for (int i = 0; i <= end; i++) {

		if (sortArr[i] < pivot) {
			arr[startPtr] = sortArr[i];
			startPtr++;
		}
		else {
			arr[endPtr] = sortArr[i];
			endPtr--;
		}
	}
	endPtr++;
	std::cout << "here" << std::endl;
	//delete sortArr;
	//sort::print(arr, start, end, endPtr);
	

	system("pause");
	//sort left
	if (start < endPtr - 1) {
		std::cout << "\nSend Left " << std::endl;
		QSPartition(arr, start, endPtr - 1);
	}
	//sort right
	if (endPtr + 1 < end) {
		std::cout << "\nSend Right, " << endPtr + 1 << " -> " << end << std::endl;
		QSPartition(arr, endPtr + 1, end);
	}

	return arr;
}

int* sort::heapSort(int* arr, int len) {

	//forms the heap
	for (int i = (len - 1) / 2; i >= 0; i--) {
		sort::maxHeapify(arr, len, i);
	}
	
	int endCap = len;
	for (int i = len - 1; i > 0; i--) {
		//puts largest value at the end of the array
		int temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;

		//reforms heap excluding the sorted part at the end
		endCap--;
		//sort::print(arr, 0, endCap);
		sort::maxHeapify(arr, endCap, 0);

	}
	
	return arr;
}

int* sort::mergeSort(int* arr, int len) {

	if (len == 1) return arr;

	int mid = len*0.5;

	int *i = partArray(arr, 0, mid);//merge sorts the first half of the array
	mergeSort(i, mid + 1);

	int *j = partArray(arr, mid + 1, len - 1);//merge sorts the second half of the array
	mergeSort(j, len - mid + 1);

	return merge(i, mid+1, j, len - mid + 1);//puts the two halves together again, in order
}

int* sort::merge(int* arr1, int len1, int* arr2, int len2) {
	
	int*  out = new int[len1 + len2];
	int pt1 = 0, pt2 = 0, ptOut = 0;

	while (ptOut < len1 + len2) {
		if (pt1 == len1) {
			out[ptOut] = arr2[pt2];
			pt2++;
		} else if (pt2 == len2) {
			out[ptOut] = arr1[pt1];
			pt1++;
		}
		else {
			//puts the smaller of the 2 elements into the out array
			if (arr1[pt1] < arr2[pt2]) {
				out[ptOut] = arr1[pt1];
				pt1++;
			}
			else {
				out[ptOut] = arr2[pt2];
				pt2++;
			}
		}
		ptOut++;
	}

	return out;
}

int* sort::maxHeapify(int* heap, int len, int index) {
	
	//left child = (n*2) + 1
	//right child = (n*2) + 2
	int leftIndex = index * 2 + 1;
	int rightIndex = index * 2 + 2;
	int largest = index;

	//checks if the left child is larger than the parent
	if (leftIndex < len && heap[leftIndex] > heap[largest])
		largest = leftIndex;

	//checks if the right child is the largest of the 3 nodes
	if (rightIndex < len && heap[rightIndex] > heap[largest])
		largest = rightIndex;

	//if ether child was larger the largest is swapped with the parent
	if (largest != index) {

		int temp = heap[index];
		heap[index] = heap[largest];
		heap[largest] = temp;
		
		//maxheapify is called again on the larger childs old location
		sort::maxHeapify(heap, len, largest);
	}

	return heap;
}

int* sort::invert(int* arr, int len) {

	int i = 0, j = len - 1;
	int middle = len / 2;

	for (; i < middle;) {
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;

		i++;
		j--;
	}

	return arr;
}

int* sort::partArray(int* fullArray, int from, int to) {
	int* out = new int[to - from + 1];

	for (int i = from; i <= to; i++)
		out[i - from] = fullArray[i];

	return out;
}
