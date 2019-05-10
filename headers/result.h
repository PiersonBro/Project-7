#ifndef _RESULT_H_
#define _RESULT_H_

struct Result {
    int comparisons = 0;
    int movements = 0;

    Result& operator+=(const Result& other){
        comparisons += other.comparisons;
        movements += other.movements;
        return *this;
    }

};

#endif