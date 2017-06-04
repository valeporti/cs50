/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include <math.h>

#include "helpers.h"


/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // TODO: implement a searching algorithm
    if (n < 1)
    {
        return false;
    }
    else
    {
        int m = n;
        int first = 0;
        int last = n;
        while (m > 0)
        {
            m = last - first;
            float flo = first + m/2;
            int middle = roundf(flo);
            if (values[middle] == value)
            {
                return true;
            }
            else if (values[middle] > value)
            {
                last = middle - 1;
            }
            else if (values[middle] < value)
            {
                first = middle + 1;
            }
            else 
            {
            }
        }
        return false;
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
     //TODO: implement an O(n^2) sorting algorithm
     // n + 1 dado que seimpre sale un valor de más sin asignar
     //es necesario tomarlo en cuena para que salgan todos los valores
    for (int j = 0; j < n + 1 ; j ++)
    {
        int VN = values[j];
        for (int i = j; i < n ; i++)
        {
            if(VN > values[i+1])
            {
                values[j] = values[i+1];
                values[i+1] = VN;
                VN = values[j];
            }
            else
            {
            }
        }
        printf("haystack[%i] = %i \n",j , values[j]);
    }
    //check_sorted(values,n);
}

bool check_sorted(int values[], int n)
{
    // list contains 0 or 1 element(s), which cannot be 'unsorted'
    if (n < 2)
    {
        return true;
    }

    // note that loop to n - 1
    for (int i = 0, m = n - 1; i < m; i++)
    {
        // return false if next value is greater than current value  
        if (values[i] > values[i + 1])
        {
            printf("not sorted!!");
            return false;
        }
    }

    // all values are in expected order
    printf("Sorted!!");
    return true;
}