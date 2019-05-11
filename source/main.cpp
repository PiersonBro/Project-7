#include <iostream>
#include <vector>
#include <ctime> // rand()
#include <time.h>
#include <cstdlib> // rand()
#include <sstream>
#include "result.h"
using std::vector;

// QuickSort Algorithm
// Received assistance from Advanced Sorting lecture slides pages 118 and 146-160 as well as page 610 of the book for how/why it works (such as the usage of a do-while loop instead of a while loop)
// The pivot value is the front of the vector (at the moment there is no process in choosing a pivot, it just uses what is there)

// Partion a sequential data structure 
// It front -- the generic iterator that represents the beginning of the data structure
// IT back -- the genric iterator that represents the end of the data structure
// Result -- Debugging class used to keep track of movements and comparisons.
// Returns an iterator that represents the pivot 
template <typename It>
It QuickPartition(It front, It back, Result& result) {
  // Index values for comparing the data inside the partition with the pivot (but don't want to change the front and back values so that they can be used later)
  It left = front + 1;
  It right = back - 1;
  // A do while loop so that it runs atleast once to make sure that all left and right are in right order
  do {
    // Increment left comparison index value until it comes across a value greater than the pivot OR reaches the end of the partitioned portion of the vector
    while ( (left < back-1) && !(*front < *left) ) {
      ++left;
      result.comparisons++;
    }
    result.comparisons++;

    while (*front < *right) {
      --right;
      result.comparisons++;
    }
    result.comparisons++;

    if (left < right) {
      std::iter_swap(left, right);
      result.movements++;
    }
    // Result comparison increased for if statement, kept seperate from while loop comparison addition
    result.comparisons++;
    
    result.comparisons++;
  } while (left < right);
  // Swap the pivot with the right value so that it is in the middle of the partitioned sides before returning the position of pivot 
  std::iter_swap(front, right);
  result.movements++;
  return right;
}


// The "main sorting function" that takes the iterators and calls partition before recursively quicksort on the left and right sides of the pivot
// It front -- the generic iterator that represents the beginning of the data structure
// IT back -- the genric iterator that represents the end of the data structure
// Returns Result which keeps track of the number of comparisions and movements.
template <typename It>
Result QuickSort(It front, It back) {
  Result result;
  if (back - front != 0){
    It pivot = QuickPartition(front, back, result);

    result +=QuickSort(front, pivot);
    result +=QuickSort(pivot+1,back);
  }
  result.comparisons++;

  return result;
}

// Helper function that calls QuickSort with the first case for the entire vector range
// data -- the vector to sort.
// Returns Result which keeps track of the number of comparisions and movements.
template <typename T>
Result QuickSort(std::vector<T>& data) {
  return QuickSort(data.begin(), data.end() );
}
// End of QuickSort



// MergeSort Algorithm
// Merge two sequences of the sequential data structure back together.
// left_start -- the beginning of the left sequence
// left_end -- the end of the left sequence
// right_stat -- the beginning of the right sequence
// right_end -- the end of the right sequence
// output -- the start of the two merged sequences.
// Returns Result which keeps track of the number of comparisions and movements.
template <typename It>
Result Merge(It left_start, It left_end, It right_start, It right_end, It output) {
  Result result;
  // While there are elements within the left and right halves to be compared and to put into the output vector
  while (left_start < left_end && right_start < right_end){
    result.comparisons++;
    // If the left top value to be added is less than the right top value, then put the left top onto the ouput vector and move the position of left top iterator and output for the next comparison
    if (*left_start < *right_start){
      *output = *left_start;
      ++output;
      ++left_start;
      result.movements++;
    }
    // If the left top is not less than right, than that means right is either less or equal to and will be put onto the output vector in the same process as for left
    else {
      *output = *right_start;
      ++output;
      ++right_start;
      result.movements++;
    }
    result.comparisons++;
    
  }
  result.comparisons++;

  // These two while loops are for when either the left or right half has been completely pushed onto the output vector and the other still has elements left, and since it was already sorted the remaining elements only have to be pushed onto the output until there are no more left 
  while (left_start < left_end){
    result.comparisons++;
    *output = *left_start;
    ++output;
    ++left_start;
    result.movements++;
  }
  result.comparisons++;

  while (right_start < right_end){
    result.comparisons++;
    *output = *right_start;
    ++output;
    ++right_start;
    result.movements++;
  }
  result.comparisons++;
  return result;
}
// Sort a sequenced data structure using the merge sort technique.
// It front -- the generic iterator that represents the beginning of the data structure
// IT back -- the genric iterator that represents the end of the data structure
// Returns Result which keeps track of the number of comparisions and movements.
// Received assistance from the book on page 598 for using the iterators
template<typename It>
Result MergeSort(It start, It end) {
  Result result;
  // If there is more than one element in the vector portion, create two vectors for the left portion and right halves to be sorted
  if (end - start > 1){
    It middle = start + (end-start)/2;

    // Create the two halves by creating vectors using iterator locations for the constructor
    typedef typename std::iterator_traits<It>::value_type T;
    std::vector<T> left_v(start, middle);
    std::vector<T> right_v(middle, end);

    // Call MergeSort on the left and right halves of the vector
    result += MergeSort(left_v.begin(), left_v.end());
    result += MergeSort(right_v.begin(), right_v.end());

    // Merge the sorted vectors, using their iterators with the start iterator of the main vector as the starting point for output of the merge
    result += Merge(left_v.begin(), left_v.end(), right_v.begin(), right_v.end(), start);
  }

  result.comparisons++;
  return result;
}


// Helper function for starting case of user wanting to sort the entire vector
// data -- the vector to sort.
// Returns Result which keeps track of the number of comparisions and movements.
template <typename T>
Result MergeSort(std::vector<T>& data) {
  return MergeSort(data.begin(), data.end());
}
// End of MergeSort


// Sort a sequenced data structure using selection sort.
// vector -- the vector to sort
// Returns Result which keeps track of the number of comparisions and movements.
template <typename T>
Result SelectionSort(vector<T>& vector) {
    Result result;
    for (int i = 0; i < vector.size(); i++) {
        result.comparisons++;
        int smallestIndex = i;
        for (int j = i; j < vector.size(); j++) {
            result.comparisons++;
            if (vector[smallestIndex] > vector[j]) {
                smallestIndex = j;
            }
            result.comparisons++;
        }
        result.comparisons++;

        std::swap(vector[smallestIndex], vector[i]);
        result.movements++;
    }
    result.comparisons++;
    return result;
}

// Referred to the book for help on algorithm.
// Sort a sequenced data structure using selection sort.
// IT first -- the iterator that represents the beginning of the data structure
// IT last -- the iterator that represents the end of the data structure
// Returns Result which keeps track of the number of comparisions and movements.
template <typename IT>
Result InsertionSort(IT first, IT last) {
    Result result;
    for (IT next = first + 1; next < last; next++) {
        result.comparisons++;
        while (next != first && *next < *(next - 1)) {
            result.comparisons++;
            std::iter_swap(next, next - 1);
            --next;
            result.movements++;
        }
        result.comparisons++;
    }
    result.comparisons++;
    return result;
}

// Helper function for when the user wants to sort the entire vector
// Sort a sequenced data structure using selection sort.
// vector -- the vector to sort
// Returns Result which keeps track of the number of comparisions and movements.
template <typename T> 
Result InsertionSort(vector<T>& vector) {
    return InsertionSort(vector.begin(), vector.end());
}

// Vector creating functions that take in a size (and for with duplicates value for how much is duplicated)
// Create a vector that is ascending in order.
// int size -- the size of the vector to create.
// Returns a vector that is ascending in order.
vector<int> AscendingOrder(int size){
    vector<int> data;
    for (int i = 0; i < size; i++){
        data.push_back(i);
    }
    return data;
}
// Create a vector that is descending in order.
// int size -- the size of the vector to create.
// Returns a vector that is descending in order.
vector<int> DescendingOrder(int size){
    vector<int> data;
    for (int i = size-1; i >= 0; i--){
        data.push_back(i);
    }
    return data;
}
// Create a vector that is randomly ordered without any duplicates.
// int size -- the size of the vector to create.
// Returns a vector that is randomly ordered without any duplicates.
vector<int> RandomOrderNoDuplicates(int size){
    vector<int> data;
    for (int i = 0; i < size; i++){
        data.push_back(i);
    }
    // Shuffle the values inside data to create a random order    
    srand(time(NULL));
    for (int i = 0; i < data.size(); i++){
        std::swap(data[i], data[rand() % data.size()]);
    }
    return data;
}
// Create a vector that is randomly ordered with duplicates.
// int size -- the size of the vector to create.
// unqiuePercentage -- how much of the array must be non-duplicates
// Returns a vector that is randomly ordered with duplicates.
vector<int> RandomOrderWithDuplicates(int size, float uniquePercentage){
    vector<int> data;
    // First fill data with values up to the amount desired to be unique
    for (int i = 0; i < size*(uniquePercentage/100); i++){
        data.push_back(i);
    }
    srand(time(NULL));
    // Fill the rest of values as random values that would be in the vector (resulting in duplicates)
    while (data.size() < size){
        data.push_back(rand() % data.size()*((uniquePercentage)/100));
    }
    // Shuffle the values inside data to create a random order    
    for (int i = 0; i < data.size(); i++){
        std::swap(data[i], data[rand() % data.size()]);
    }
    return data;
}
// Generate a string based bar graph up to the given number.
// int graphNumber -- the number of points in the bar graph.
// char symbol -- the symbol to represent the "bar"
// string name -- the name of the graph
// returns the graph
std::string generateGraph(int graphNumber, char symbol, std::string name){
    std::stringstream stream;
    int counter = 0;
    stream << name << ": ";
    do {
        stream << symbol;
        counter++;
    } while (counter < graphNumber);

    stream << std::endl;

    return stream.str();
}

// Function pointer alias
typedef Result (*SORT_FUNC)(vector<int>&);
// Test a specific sorting method with a specific data set.
// vector -- the specific data set to sort.
// sortFunc -- a function pointer pointing to the sort function to use.
// sortFuncDescriptor -- describes the given sorting function
// Returns a string represention of the performance of the given sort function.
std::string testIndividualSort(vector<int> vector, SORT_FUNC sortFunc, std::string sortFuncDescriptor) {
    // We used a solution from stack overflow to time our function.
    // https://stackoverflow.com/questions/2962785/c-using-clock-to-measure-time-in-multi-threaded-programs/2962914#2962914
    Result result = sortFunc(vector);
    std::string stream;

    std::cout << sortFuncDescriptor << std::endl;
    std::cout << "Comparisons: " << result.comparisons << std::endl;
    std::cout << "Movements  : " << result.movements << std::endl << std::endl;

    
    stream += generateGraph(result.comparisons/(vector.size()*4), '-', sortFuncDescriptor);
    stream += generateGraph(result.movements/(vector.size()*4), '*', sortFuncDescriptor);


    return stream;
}
// Tests all four sorts with a given data set and displays the results.
// vector -- the data set to sort
// sortFuncOne -- the first sort function to use
// sortFuncTwo -- the second sort function to use
// sortFuncThree -- the third sort function to use
// sortFuncFour -- the fourth sort function to use
// sortDescriptorOne -- describes what kind of sort function sortFuncOne is.
// sortDescriptorTwo -- describes what kind of sort function sortFuncTwo is.
// sortDescriptorThree -- describes what kind of sort function sortFuncThree is.
// sortDescriptorFour -- describes what kind of sort function sortFuncFour is.
// returns void.
void testSorts(vector<int> vector, SORT_FUNC sortFuncOne, std::string sortDescriptorOne, SORT_FUNC sortFuncTwo, std::string sortDescriptorTwo, SORT_FUNC sortFuncThree, std::string sortDescriptorThree, SORT_FUNC sortFuncFour, std::string sortDescriptorFour) {
    std::string sortFirstLine = testIndividualSort(vector, sortFuncOne, sortDescriptorOne);
    std::string sortSecondLine = testIndividualSort(vector, sortFuncTwo, sortDescriptorTwo);
    std::string sortThirdLine = testIndividualSort(vector, sortFuncThree, sortDescriptorThree);
    std::string sortFourthLine = testIndividualSort(vector, sortFuncFour, sortDescriptorFour);
    std::string finalString = sortFirstLine + sortSecondLine + sortThirdLine + sortFourthLine;
    std::cout << "Number of Comparisons (-) and Number of Movements (*) scaled by the size of vector times 4 with a vector of size " << vector.size() << std::endl;
    std::cout << finalString << std::endl;
}

int main() {
    std::cout << "Random Order with No Duplicates with data of size 100\n";
    testSorts(RandomOrderNoDuplicates(100), InsertionSort, "Insertion Sort", SelectionSort, "Selection Sort", MergeSort, "Merge Sort    ", QuickSort, "Quick Sort    ");
    
    std::cout << "Random Order with Duplicates with data of size 100\n";
    testSorts(RandomOrderWithDuplicates(100, 90), InsertionSort, "Insertion Sort", SelectionSort, "Selection Sort", MergeSort, "Merge Sort    ", QuickSort, "Quick Sort    ");
    
    std::cout << "Ascending Order with data of size 100\n";
    testSorts(AscendingOrder(100), InsertionSort, "Insertion Sort", SelectionSort, "Selection Sort", MergeSort, "Merge Sort    ", QuickSort, "Quick Sort    ");
    
    std::cout << "Descending Order with data of size 100\n";
    testSorts(DescendingOrder(100), InsertionSort, "Insertion Sort", SelectionSort, "Selection Sort", MergeSort, "Merge Sort    ", QuickSort, "Quick Sort    ");

    std::cout << "\n\n\n\n";

    std::cout << "Random Order with No Duplicates with data of size 500\n";
    testSorts(RandomOrderNoDuplicates(500), InsertionSort, "Insertion Sort", SelectionSort, "Selection Sort", MergeSort, "Merge Sort    ", QuickSort, "Quick Sort    ");
    
    std::cout << "Random Order with Duplicates with data of size 500\n";
    testSorts(RandomOrderWithDuplicates(500, 90), InsertionSort, "Insertion Sort", SelectionSort, "Selection Sort", MergeSort, "Merge Sort    ", QuickSort, "Quick Sort    ");
    
    std::cout << "Ascending Order with data of size 500\n";
    testSorts(AscendingOrder(500), InsertionSort, "Insertion Sort", SelectionSort, "Selection Sort", MergeSort, "Merge Sort    ", QuickSort, "Quick Sort    ");
    
    std::cout << "Descending Order with data of size 500\n";
    testSorts(DescendingOrder(500), InsertionSort, "Insertion Sort", SelectionSort, "Selection Sort", MergeSort, "Merge Sort    ", QuickSort, "Quick Sort    ");

    std::cout << "\n\n\n\n";

    std::cout << "Random Order with No Duplicates with data of size 1000\n";
    testSorts(RandomOrderNoDuplicates(1000), InsertionSort, "Insertion Sort", SelectionSort, "Selection Sort", MergeSort, "Merge Sort    ", QuickSort, "Quick Sort    ");
    
    std::cout << "Random Order with Duplicates with data of size 1000\n";
    testSorts(RandomOrderWithDuplicates(1000, 90), InsertionSort, "Insertion Sort", SelectionSort, "Selection Sort", MergeSort, "Merge Sort    ", QuickSort, "Quick Sort    ");
    
    std::cout << "Ascending Order with data of size 1000\n";
    testSorts(AscendingOrder(1000), InsertionSort, "Insertion Sort", SelectionSort, "Selection Sort", MergeSort, "Merge Sort    ", QuickSort, "Quick Sort    ");
    
    std::cout << "Descending Order with data of size 1000\n";
    testSorts(DescendingOrder(1000), InsertionSort, "Insertion Sort", SelectionSort, "Selection Sort", MergeSort, "Merge Sort    ", QuickSort, "Quick Sort    ");

    std::cout << "\n\n\n\n";

    std::cout << "Random Order with No Duplicates with data of size 2000\n";
    testSorts(RandomOrderNoDuplicates(2000), InsertionSort, "Insertion Sort", SelectionSort, "Selection Sort", MergeSort, "Merge Sort    ", QuickSort, "Quick Sort    ");
    
    std::cout << "Random Order with Duplicates with data of size 2000\n";
    testSorts(RandomOrderWithDuplicates(2000, 90), InsertionSort, "Insertion Sort", SelectionSort, "Selection Sort", MergeSort, "Merge Sort    ", QuickSort, "Quick Sort    ");
    
    std::cout << "Ascending Order with data of size 2000\n";
    testSorts(AscendingOrder(2000), InsertionSort, "Insertion Sort", SelectionSort, "Selection Sort", MergeSort, "Merge Sort    ", QuickSort, "Quick Sort    ");
    
    std::cout << "Descending Order with data of size 2000\n";
    testSorts(DescendingOrder(2000), InsertionSort, "Insertion Sort", SelectionSort, "Selection Sort", MergeSort, "Merge Sort    ", QuickSort, "Quick Sort    ");
}
