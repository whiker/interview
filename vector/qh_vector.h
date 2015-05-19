#ifndef QIHOO_VECTOR_H_
#define QIHOO_VECTOR_H_

namespace qh
{
    template<class T>
    class vector {
    public:
        //ctor
        vector()
            : data_(NULL), size_(0), capacity_(0)
        {
        }

        explicit vector( size_t n, const T& value = T())
            : data_(NULL), size_(0), capacity_(0)
        {
            if (n > 0)
            {
                data_ = new T[n];
                for (size_t i = 0; i < n; i++)
                    data_[i] = value;
                capacity_ = size_ = n;
            }
        }

        vector<T>& operator=(const vector<T>& rhs)
        {
            if (&rhs == this)
                return *this;
            size_t newsize = rhs.size_;

            if (newsize > capacity_)
            {
                if (data_)
                    delete[] data_;
                data_ = new T[newsize];
                capacity_ = newsize;
            }

            copyData(data_, rhs.data_, newsize);
            size_ = newsize;
            return *this;
        }

        //dtor
        ~vector()
        {
            if (data_)
            {
                delete[] data_;
            }
        }

        //get
        size_t size() const
        {
            return size_;
        }

        // set & get
        T& operator[](size_t index)
        {
            return *(data_+index);
        }

        // set
        void push_back(const T& element)
        {
            if (size_ == capacity_)
            {
                size_t increase = capacity_ / 2;
                if (increase < MinIncrease)
                    increase = MinIncrease;
                reserve(capacity_+increase);
            }
            data_[size_++] = element;
        }

        void pop_back(const T& element)
        {
            if (size_ > 0)
                element = data_[--size_];
        }

        void resize(size_t newsize)
        {
            reserve(newsize);
            size_ = newsize;
        }

        void reserve(size_t capacity)
        {
            if (capacity_ < capacity)
            {
                T* new_data = new T[capacity];
                if (data_)
                {
                    copyData(new_data, data_, size_);
                    delete[] data_;
                }
                data_ = new_data;
                capacity_ = capacity;
            }
        }

        void clear()
        {
            size_ = 0;
        }

        bool empty()
        {
            return size_ == 0;
        }

    private:
        void copyData(T* dst, T* src, size_t n)
        {
            for (size_t i = 0; i < n; i++)
                dst[i] = src[i];
        }

    private:
        T*      data_;
        size_t  size_;
        size_t  capacity_;

    private:
        const static size_t MinIncrease = 10;
    };
}

#endif
