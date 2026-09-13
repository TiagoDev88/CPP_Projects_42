
template<typename T>
Array<T>::Array() : _arr(NULL), _size(0) {}


template<typename T>
Array<T>::Array(unsigned int n) : _arr(new T[n]()), _size(n) {}

template<typename T>
Array<T>::Array(const Array<T>& other) : _arr(new T[other._size]), _size(other._size)
{
    for(size_t i = 0; i < other._size; i++)
        _arr[i] = other._arr[i];

}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
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
Array<T>::~Array() { delete[] _arr; }

template<typename T>
T& Array<T>::operator[](unsigned int num)
{
    if (num >= _size)
        throw std::out_of_range("index out of bounds");

    return this->_arr[num];    
}

template<typename T>
const T& Array<T>::operator[](unsigned int num) const
{
    if (num >= _size)
        throw std::out_of_range("index out of bounds");

    return this->_arr[num];    
}

template<typename T>
unsigned int Array<T>::size() const { return _size; }