#include <stdio.h>

#include <cstring>
#include <iostream>
#include <utility>

class SumVector {
   private:
    size_t capacity;
    size_t size;
    int64_t sum;
    int* data;

   public:
    SumVector() : capacity(10), size(0), sum(0) {
        data = (int*)malloc(10 * sizeof(int));
    }

    ~SumVector() {
        if (data != nullptr) {
            free(data);
        }
    }

    SumVector(const SumVector& other)
        : capacity(other.capacity), size(other.size), sum(other.sum) {
        data = (int*)malloc(capacity * sizeof(int));
        std::memcpy(data, other.data, size * sizeof(int));
    }

    SumVector(SumVector&& other)
        : capacity(other.capacity), size(other.size), sum(other.sum) {
        data = std::exchange(other.data, nullptr);
    }

    SumVector& push_back(int v) {
        if (size == capacity) {
            capacity *= 2;
            data = (int*)realloc(data, capacity * sizeof(int));
        }
        data[size++] = v;
        sum += v;
        return *this;
    }

    SumVector& pop() {
        sum -= data[--size];
        return *this;
    }

    void print() {
        std::cout << "Size = " << size << "\n"
                  << "Sum = " << sum << "\n";
        for (size_t i = 0; i < size; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    SumVector first;
    first.push_back(1).push_back(2).push_back(3);
    SumVector second = first;
    second.pop().push_back(66).push_back(102);
    first.print();
    second.print();
}
