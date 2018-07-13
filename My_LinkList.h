#pragma once
template<typename T>
struct Node {
	T Value;
	Node<T> *p_next=nullptr;
};
template<typename T>
class my_LinkList {
private:
	Node<T> *_head = nullptr;
	Node<T> *_end = nullptr;
	size_t _size = 0;
public:
	~my_LinkList() {
		Node<T> *tmp = _head;
		Node<T> *tmp_1 = _head;
		for (size_t i = 0; i < _size; i++) {
			tmp_1 = tmp;
			tmp = tmp->p_next;
			delete tmp_1;
		}
	}
	T &operator[](const size_t &index) {
		if (index < _size) {
			Node<T> *tmp = _head;
			for (size_t i = 0; i < _size; i++) {
				if (i == index)
					return tmp->Value;
				tmp = tmp->p_next;
			}
		}
	}
	void operator+(const T &_val) {
		Add(_val);
	}
	void Add(const T &_Value) {
		if (_head == nullptr) {
			_head = new Node<T>();
			_head->Value = _Value;
			_end = _head;
		}
		else {
			_end->p_next = new Node<T>();
			_end->p_next->Value = _Value;
			_end = _end->p_next;
		}
		_size++;
	}
	void Set(const size_t &index,const T &_val) {
		if (index < _size) {
			Node<T> *tmp = _head;
			for (size_t i = 0; i < _size; i++) {
				if (i == index) {
					tmp->Value = _val;
					break;
				}
				tmp = tmp->p_next;
			}
		}
	}
	T* ToArray() {
		T* arr = new T[_size];
		Node<T> *tmp = _head;
		for (size_t i = 0; i < _size; i++) {
			arr[i] = tmp->Value;
			tmp = tmp->p_next;
		}
		return arr;
	}
	void RemoveAt(const size_t &index) {
		if (index < _size) {
			bool _find = false;
			Node<T> *tmp = _head;
			if (index == _size - 1) {
				while (tmp!=nullptr)
				{
					if (tmp->p_next->p_next == nullptr) {
						delete tmp->p_next;
						_end = tmp;
						tmp->p_next = nullptr;
						_size--;
						break;
					}
					tmp = tmp->p_next;
				}
			}
			else {
				for (size_t i = 0; i < _size; i++) {
					if (i == index) {
						_find = true;
					}
					if (_find) {
						if (tmp->p_next != nullptr) {
							tmp->Value = tmp->p_next->Value;
							if (tmp->p_next->p_next == nullptr) {
								delete tmp->p_next;
								tmp->p_next = nullptr;
								_end = tmp;
								_size--;
								break;
							}
						}
					}
					tmp = tmp->p_next;
				}
			}
		}
	}
	inline const size_t &Size() {
		return _size;
	}
	void Clear() {
		Node<T> *tmp = _head;
		Node<T> *tmp_1 = _head;
		for (size_t i = 0; i < _size; i++) {
			tmp_1 = tmp;
			tmp = tmp->p_next;
			delete tmp_1;
		}
		_head = nullptr;
		_end = nullptr;
		_size = 0;
	}
	T At(const size_t &index) {
		Node<T> *tmp = _head;
		for (size_t i = 0; i < _size; i++) {
			if (i == index)
				return tmp->Value;
			tmp = tmp->p_next;
		}
	}
	size_t IndexOf(const T &item) {
		Node<T> *tmp = _head;
		for (size_t i = 0; i < _size; i++) {
			if (tmp->Value == item)
				return i;
			tmp = tmp->p_next;
		}
		return -1;
	}
};