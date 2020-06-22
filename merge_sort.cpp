#include<iostream>
#include<bits/stdc++.h>
using namespace std;


template<class T>
class IsLessDefaultFunctor {
public:
    bool operator()(const T& l, const T& r)
    {
        return l < r;
    }
};


template<class T, class IsLess = IsLessDefaultFunctor<T> >
void merge(T *arr, int low, int high, int mid, IsLess isLess = IsLess())
{
    int i, j, k, c[high+1];
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high) {
        if (isLess(arr[i], arr[j])) {
            c[k] = arr[i];
            k++;
            i++;
        }
        else  {
            c[k] = arr[j];
            k++;
            j++;
        }
    }
    while (i <= mid) {
        c[k] = arr[i];
        k++;
        i++;
    }
    while (j <= high) {
        c[k] = arr[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++)  {
        arr[i] = c[i];
    }

}


template<class T>
void merge_sort(T *arr, int low, int high)
{
    int mid;
    if (low < high){
        mid=(low+high)/2;
        merge_sort(arr,low,mid);
        merge_sort(arr,mid+1,high);
        merge(arr,low,high,mid);
    }
}






int main()
{   int n, k, count, count_g, max;
    max = INT_MAX ;
    count  = 1;
    count_g = 0;
    cin >> n >> k;
    int * array1, * array2, * array1_2;
    array1 = new int [k];
    array2 = new int [k];
    array1_2 = new int [2*k];



    for (int i = 0; i < k; i++) {
        cin>>array1[i];
    } //считываем первые к элементов

    for (int i = 0; i < (n-k); i++) {
        if (count<=k){
            cin>>array2[count-1];
            count++;
            count_g++;
        }  //считываем вторые к элементов

        if ((count > k) || (count_g == n-k)) {   //если считали к или это последнее из n чисел
            for (int j = 0; j < k; j++) {
                array1_2[j] = array1[j];
            }

            for (int j = 0; j < k; j++) {
                array1_2[j+k] = array2[j];
            }  //объединяем два массива в один



            merge_sort(array1_2, 0, 2*k-1);  //сортируем его
            count = 1;

            for (int j = 0; j < k; j++) {
                array1[j] = array1_2[j];  //перезаписываем первый массив первыми отсортированными чилами
            }

            for (int j = 0; j < k; j++) {
                array2[j] = max;  //заполняем второй максимальными числами
            }


        }

    }


    for (int i = 0; i < k; i++)
    {
        cout << array1[i] << ' ';
    }

    delete [] array1;
    delete [] array2;
    delete [] array1_2;


}
