#include <cstdio>
#include <cstdint>
#include <exception>

class InputGenerator {
public:
    InputGenerator() = default;
    ~InputGenerator() = default;
    
    int64_t GetInput() {
        const static int64_t kDivisor = (1LL << 32);
        if (input_ < 0) {
            input_ = 1983;
            return input_;
        }
        input_ = (input_ * 214013 + 2531011) % kDivisor;
        return input_ % 10000 + 1;
    }
    
private:
    int64_t input_ = -1;
};

template <typename T>
class MyQueue {
public:
    MyQueue() {
        array_ = new T[capacity_];
    }
    ~MyQueue() {
        delete array_;
    }

    void Reserve(size_t n) {
        if (n < size_) {
            throw std::exception();
        }
        ResizeAndMove(n);
    }

    void Push(T data) {
        if (size_ == capacity_) {
            ResizeAndMove(capacity_ * 2);
        }
        array_[(head_ + size_++) % capacity_] = data;
    }

    T Front() {
        if (size_ == 0) {
            throw std::exception();
        }
        return array_[head_];
    }

    void Pop() {
        if (size_ == 0) {
            throw std::exception();
        }
        size_--;
        head_ = (head_ + 1) % capacity_;
    }

    bool Empty() {
        return size_ == 0;
    }

private:
    void ResizeAndMove(size_t new_capacity) {
        if (new_capacity < size_) {
            size_ = new_capacity;
        }

        T *new_array = new T[new_capacity];
        for(int i=0; i<size_; i++) {
            new_array[i] = array_[(head_ + i) % capacity_];
        }
        head_ = 0;
        capacity_ = new_capacity;
        delete array_;
        array_ = new_array;
    }

    int capacity_ = 1;
    int size_ = 0;
    int head_ = 0;

    T *array_;
};

int main() {
    int c;
    scanf("%d", &c);

    while(c--) {
        int k, n;
        scanf("%d %d", &k, &n);

        InputGenerator gen;
        MyQueue<int64_t> queue;

        int64_t sum = 0;
        int result = 0;
        for (int i=0; i<n; i++) {
            int64_t input = gen.GetInput();
            sum += input;
            queue.Push(input);
            while (sum >= k && !queue.Empty()) {
                if (sum == k) {
                    result++;
                }
                sum -= queue.Front();
                queue.Pop();
            }
        }
        printf("%d\n", result);
    }
    return 0;
}