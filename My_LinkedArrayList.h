#pragma once
#define _EXPAND_SIZE_ 10		//change _EXPAND_SIZE_ value to improve the efficiency ,
/**********************				for example,when length of data is about 1000000,the appropriate value is 1000
author:CharlosNels
don't delete this annotation
**********************/
template<typename T>
struct ArrayNode
{
	T *Data = nullptr;
	ArrayNode<T> *p_next = nullptr;
};
template<typename T>
class my_LinkArrayList {
private:
	ArrayNode<T> *_head;
	ArrayNode<T> *_end;
	size_t _max_size;
	size_t _size;
public:
	~my_LinkArrayList() {
		ArrayNode<T> *tmp = _head;
		ArrayNode<T> *tmp_1 = _head;
		while (tmp != nullptr) {
			tmp_1 = tmp;
			delete[]tmp_1->Data;
			tmp = tmp->p_next;
			delete tmp_1;
		}
	}
	my_LinkArrayList() :_head(nullptr), _end(nullptr), _max_size(0), _size(0) {}
	void operator+(const T &_val) {
		Add(_val);
	}
	T &operator[](const size_t &index) {
		if (index < _size) {
			size_t num = index / _EXPAND_SIZE_;
			ArrayNode<T> *tmp = _head;
			for (size_t i = 0; i < _max_size / _EXPAND_SIZE_; i++) {
				if (i == num) {
					return tmp->Data[index%_EXPAND_SIZE_];
				}
				tmp = tmp->p_next;
			}
		}
	}
	T *ToArray() const {
		T *arr = new T[_size];
		ArrayNode<T> *tmp = _head;
		for (size_t i = 0; i < _max_size / _EXPAND_SIZE_; i++) {
			for (size_t j = 0; j < _EXPAND_SIZE_; j++) {
				arr[i*_EXPAND_SIZE_ + j] = tmp->Data[j];
			}
			tmp = tmp->p_next;
		}
		return arr;
	}
	void Set(const size_t &index, const T &_val) {
		if (index < _size) {
			size_t num = index / _EXPAND_SIZE_;
			ArrayNode<T> *tmp = _head;
			for (size_t i = 0; i < _max_size / _EXPAND_SIZE_; i++) {
				if (i == num) {
					tmp->Data[index%_EXPAND_SIZE_] = _val;
					return;
				}
				tmp = tmp->p_next;
			}
		}
	}
	void Add(const T &_val) {
		if (_head == nullptr) {
			_head = new ArrayNode<T>();
			_head->Data = new T[_EXPAND_SIZE_];
			_head->Data[_size] = _val;
			_end = _head;
			_max_size = _EXPAND_SIZE_;
			_size++;
		}
		else {
			if (_size < _max_size) {
				_end->Data[_size + _EXPAND_SIZE_ - _max_size] = _val;
				_size++;
			}
			else {
				_end->p_next = new ArrayNode<T>();
				_end = _end->p_next;
				_end->Data = new T[_EXPAND_SIZE_];
				_end->Data[_size - _max_size] = _val;
				_size++;
				_max_size += _EXPAND_SIZE_;
			}
		}
	}
	void Clear() {
		if (_size != 0) {
			ArrayNode<T> *tmp = _head;
			ArrayNode<T> *tmp_1;
			while (tmp != nullptr) {
				tmp_1 = tmp;
				delete[] tmp_1->Data;
				tmp = tmp->p_next;
				delete tmp_1;
			}
			_size = 0;
			_max_size = 0;
			_head = nullptr;
			_end = _head;
		}
	}
	T At(const size_t &index) const {
		if (index < _size) {
			size_t num = index / _EXPAND_SIZE_;
			ArrayNode<T> *tmp = _head;
			for (size_t i = 0; i < _max_size / _EXPAND_SIZE_; i++) {
				if (i == num) {
					return tmp->Data[index%_EXPAND_SIZE_];
				}
				tmp = tmp->p_next;
			}
		}
	}
	inline const size_t &Size() const {
		return _size;
	}
};
