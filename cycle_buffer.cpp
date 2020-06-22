#include <bits/stdc++.h>
using namespace std;
struct Node
{
    int data;
    struct Node* link; //решаем задачу односвязными списками
};
class Circular {

public:
    Circular();
    ~Circular();

    typedef struct QueueT
    {
        struct Node *front, *rear;
    } Queue;

    void pushback( int value);
    int popfront();
    int count; //число активных элементов
    int size; //размер буффера



private:
    Queue *q;

};


Circular::Circular(){
    count = 0;
    q = new Queue;
    q->front = q->rear = nullptr;
}


Circular::~Circular(){
    int k ;
    for (k = 1; k<=count; k++){   //через while != nullptr не получилось написать
        struct Node *temp = q->front->link;
        q->front = nullptr;
        q->front = temp;

    }
    q->rear = nullptr;

}
// Function to create Circular queue
void Circular::pushback( int value)
{
    if ((size == count) /*|| (q->front == q->rear)*/ ) {

        struct Node *temp = new Node;
        temp->data = value;
        if (q->front == nullptr)
            q->front = temp;
        else
            q->rear->link = temp;

        q->rear = temp;
        q->rear->link = q->front;   //цикличность

        size++;
        count++;

    }
    else {

        q->rear = q->rear->link;   //сдвигаемся по элементам, но не удаляем их
        q->rear->data = value;
        count++;

    }

}


int Circular::popfront()
{int value;
    if ((q->front == nullptr) || (q->front->data == -1))  //условие для пустого буффера
    {
        return -1;
    }else{



        value = q->front->data;     //зануляем дату и сдвигаемся к следующему элементу
        /*free(q->front);*/
        q->front->data = -1;
        q->front = q->front->link;
        count--;
    }

    return value ;
}





int main()
{
    int n, i, task;
    int j;
    char res = 'Y';
    Circular q;
    cin >> n;
    for (i =1 ; i<=n; i++){
        cin >> task >> j;
        if (task == 3){
            q.pushback(j);
        } else {
            if (q.popfront() != j) {
                res = 'N';
            }
        }
    }

    if (res == 'N'){
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
    }



    return 0;
}