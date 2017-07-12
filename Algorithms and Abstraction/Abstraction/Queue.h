#ifndef QUEUE
#define QUEUE

template<typename T>

class Queue 
{
    public:
        virtual ~Queue() {}
        virtual void enqueue(const T &t) = 0;
        virtual T dequeue() = 0;
        virtual T peek() const = 0;
        virtual bool isEmpty() const = 0;
};
// Virtual : It allows derived class to override it with the same name

#endif