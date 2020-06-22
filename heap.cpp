#include <iostream>
#include <utility>
#include <vector>

using namespace std;

class PriorityQueue{
public:
    explicit PriorityQueue(vector<int> v2);
    ~PriorityQueue();

    void build_heap();
    int pop();
    int top();
    void push(int value);

    unsigned int size()
    {
        return A.size();
    }

private:
    vector<int> A;
    void heapify_up(int i);
    void heapify_down(int i);

    static int PARENT(int i)
    {
        return (i - 1) / 2;
    }

    static int LEFT(int i)
    {
        return (2 * i + 1);
    }

    static int RIGHT(int i)
    {
        return (2 * i + 2);
    }

};

PriorityQueue::PriorityQueue(vector<int> v2) {
    A = std::move(v2);
    }


PriorityQueue::~PriorityQueue() {
    A.clear();
}



void PriorityQueue::heapify_up(int i) {
    if (i>0) {
        int temp;
        if (A[PARENT(i)] < A[i]) {

            temp = A[PARENT(i)];
            A[PARENT(i)] = A[i];
            A[i] = temp;

            heapify_up(PARENT(i));
        }
    }
}

void PriorityQueue::heapify_down(int i)
{        int temp;

    int left = LEFT(i);
    int right = RIGHT(i);

    int largest = i;

    if (left < size() && A[left] > A[i])
        largest = left;

    if (right < size() && A[right] > A[largest])
        largest = right;


    if (largest != i) {
        temp = A[i];
        A[i] = A[largest];
        A[largest] = temp;
        heapify_down(largest);
    }


}

void PriorityQueue::build_heap(){
        for (int i =int(size())/2 - 1; i>=0; i--) {
            heapify_down(i);
        }
}


void PriorityQueue::push(int value)
{
    A.push_back(value);

    int index = int(size()) - 1;
    heapify_up(index);
}

int PriorityQueue::pop()
{
    int val;
    if (int(size()) == 0){
        val = 0;
    }

    else {
        val = A[0];
        A[0] = A.back();
        A.pop_back();

        heapify_down(0);}

    return val;


}

int PriorityQueue::top()
{

    return A.at(0);
}


int main()
{

    int n, i, j, k;
    int sum, val_add, len, step;
    vector<int> v2(0);
    cin >> n;
    vector<int> v1(0);  //вектор яблок
    for (i =1 ; i<=n; i++){
        cin >> j;
        v2.push_back(j);
    }

    PriorityQueue pq(v2);
    pq.build_heap();

    cin >> k;

    step =0;
    while (pq.size() > 0){


        sum = 0;
        i = 1;
        v1.clear();

        len = int(pq.size());
        while ((sum < k) && i<= len){  //пока не будет перевес или не закончится куча

            val_add = pq.top();

            if (sum + val_add > k) {
                break;
            }  //выходим из цикла, если следующее яблокок с перевесом
            else {
                val_add = pq.pop();
                sum += val_add;   //добавялем яблоко в сумму для фильтра
                v1.push_back(val_add);   //добавялем яблоко для съедания
            }

            i++;

        }

        len = int(v1.size()-1);   //съедаем половинки
        for (int i = len; i >= 0; i--) {
            if (v1[i] == 1) {
                v1[i] = 0;
            } else {
                v1[i] = (v1[i] / 2);

            }

            if (v1[i] != 0) {   //если не ноль, то возвращаем в кучу
                pq.push(v1[i]);
            }
            v1.pop_back();
        }


        step++;


    }

    cout << step << endl;


    return 0;
}