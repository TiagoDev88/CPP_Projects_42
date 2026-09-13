
template<typename T>
Array<T>::Array() : _arr(NULL), _size(0)
{
    std::cout << "Constructor Default\n";
}


template<typename T>
Array<T>::Array(unsigned int n) : _arr(new T[n]), _size(n)
{
    for(size_t i = 0; i < n; i++)
        _arr[i] = T();
    std::cout << "Constructor with unsigned int\n";
}

template<typename T>
Array<T>::Array(const Array<T>& other) : _arr(new T[other._size]), _size(other._size)
{
    std::cout << "Copy Operator\n";
    for(size_t i = 0; i < other._size; i++)
        _arr[i] = other._arr[i];

}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
    std::cout << "Assignment Operator\n";
    if (this != &other)
    {
        delete[] _arr;
        _arr = new T[other._size];
        _size = other._size;
        for(size_t i = 0; i < _size; i++)
            _arr[i] = other._arr[i];
    }
    return *this;
}

template<typename T>
Array<T>::~Array()
{
    std::cout << "DESTRUCTOR\n";
    delete[] _arr;
}
