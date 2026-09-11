
template<typename T>
Array<T>::Array() : arr()
{
    std::cout << "Constructor Default\n";
    
}

template<typename T>
Array<T>::Array(T value) : arr(value) 
{
    std::cout << "Constructor with value\n";

}

template<typename T>
Array<T>::Array(const Array<T>& other) : arr(other.arr) 
{
    std::cout << "Copy Operator\n";

}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& other)
{
    std::cout << "Assignment Operator\n";
    if (this != &other)
        arr = other.arr;

    return *this;

}

template<typename T>
Array<T>::~Array()
{
    std::cout << "DESTRUCTOR\n";
}

template<typename T>
T Array<T>::getArr() const
{
    return arr;
}
