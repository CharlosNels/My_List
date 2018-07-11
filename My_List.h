#pragma once
#define _DEFAULT_SIZE_ 4
/**********************
author:CharlosNels
don't delete this annotation
**********************/
template<typename T>		//define template T
class my_List{
private:
	size_t _size = 0;			//size(length)
	size_t old_size = _DEFAULT_SIZE_;		//actually size
	T *arr = new T[_DEFAULT_SIZE_];			//Data
	void Expand() {			//Expand Data if size is not enough
		old_size = old_size * 3 / 2 + 1;
		T *arr_cp = arr;
		arr = new T[old_size];
		for (size_t i = 0; i < _size; i++) {
			arr[i] = arr_cp[i];
		}
		delete[] arr_cp;
	}
public:
	~my_List() {		//Destructor
		delete[]arr;
	}
	T& operator[](const size_t &index) {
		if (index < _size) {
			return arr[index];
		}
	}
	void operator+(const T &value) {
		Add(value);
	}
	void Set(const size_t &index,const T &value) {
		if (index < _size) {
			arr[index] = value;
		}
	}
	bool Contains(const T &item) {
		for (size_t i = 0; i < _size; i++) {
			if (arr[i] == item)
				return true;
		}
		return false;
	}
	void RemoveRange(const size_t &index, const size_t &count) {
		if (index + count <= _size) {
			for (size_t i = index; i < _size-count;i++)
			{
				arr[i] = arr[i + count];
			}
			_size -= count;
		}
	}
	void Add(const T &value) {
		arr[_size] = value;
		_size++;
 		if (_size == old_size) {
			Expand();
		}
	}
	size_t Size() {
		return _size;
	}
	T* ToArray() {
		T* arr_cp = new T[_size];
		for (size_t i = 0; i < _size; i++) {
			arr_cp[i] = arr[i];
		}
		return arr_cp;
	}
	void Insert(const size_t &index, const T &value) {
		if (index < _size) {
			T tmp = arr[index];
			T tmp_1;
			arr[index] = value;
			for (size_t i = index + 1; i <= _size; i++) {
				tmp_1 = arr[i];
				arr[i] = tmp;
				tmp = tmp_1;
			}
			_size++;
			if (_size == old_size) {
				Expand();
			}
		}
	}
	void Clear() {
		_size = 0;
		old_size = _DEFAULT_SIZE_;
		delete[] arr;
		arr = new T[_DEFAULT_SIZE_];
	}
	void RemoveAt(const size_t &index) {
		if (index < _size) {
			for (size_t i = index; i < _size; i++) {
				arr[i] = arr[i + 1];
			}
			_size--;
		}
	}
	void Remove(const T &item) {
		for (size_t i = 0; i < _size; i++) {
			if (arr[i] == T)
				RemoveAt(i);
		}
	}
	T At(const size_t &index) {
		if (index < _size)
			return arr[index];
		return nullptr;
	}
	size_t IndexOf(const T &item) {
		for (size_t i = 0; i < _size; i++) {
			if (arr[i] == item)
				return i;
		}
		return -1;
	}
};