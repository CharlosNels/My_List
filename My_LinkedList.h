#pragma once
template<typename T>
struct Node {
	T Value;
	Node<T> *p_next;
	Node(const T &val = T(), Node<T> *p = nullptr) :Value(val), p_next(p) {}
};
template<typename T>
class my_LinkList {
private:
	Node<T> *_head;
	Node<T> *_end;
	size_t _size;
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
	my_LinkList() :_head(nullptr), _end(nullptr), _size(0) {}
	explicit my_LinkList(const size_t &def_siz) : _head(new Node<T>()), _size(def_siz) {
		Node<T> *tmp = _head;
		for (size_t i = 0; i < def_siz; i++) {
			tmp->Value = T();
			if (i == def_siz - 1) {
				_end = tmp;
			}
			else {
				tmp->p_next = new Node<T>();
				tmp = tmp->p_next;
			}
		}
	}
	my_LinkList(std::initializer_list<T> il) : _head(new Node<T>()), _size(il.size()) {
		Node<T> *tmp = _head;
		for (auto beg = il.begin(); beg != il.end(); beg++) {
			tmp->Value = *beg;
			if (beg == il.end() - 1) {
				_end = tmp;
			}
			else {
				tmp->p_next = new Node<T>();
				tmp = tmp->p_next;
			}
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
	void Set(const size_t &index, const T &_val) {
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
	T* ToArray() const {
		T* arr = new T[_size];
		Node<T> *tmp = _head;
		for (size_t i = 0; i < _size; i++) {
			arr[i] = tmp->Value;
			tmp = tmp->p_next;
		}
		return arr;
	}
	void Insert(const size_t &index, const T &_val) {
		if (index <= _size) {
			Node<T> *tmp = new Node<T>();
			tmp->Value = _val;
			if (index == 0) {
				tmp->p_next = _head;
				_head = tmp;
			}
			else if (index == _size) {
				_end->p_next = tmp;
				_end = tmp;
			}
			else {
				Node<T> *tmp_1 = _head;
				for (size_t i = 0; i < index - 1; i++) {
					tmp_1 = tmp_1->p_next;
				}
				tmp->p_next = tmp_1->p_next;
				tmp_1->p_next = tmp;
			}
		}
	}
	void RemoveAt(const size_t &index) {
		if (index < _size) {
			Node<T> *tmp = _head;
			if (index == _size - 1) {
				while (tmp != nullptr)
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
			else if (index == 0) {
				_head = _head->p_next;
				delete tmp;
			}
			else {
				for (size_t i = 0; i < _size; i++) {
					if (i == index - 1) {
						Node<T> *tmp_1 = tmp->p_next;
						tmp->p_next = tmp->p_next->p_next;
						delete tmp_1;
						_size--;
						break;
					}
					tmp = tmp->p_next;
				}
			}
		}
	}
	inline const size_t &Size() const {
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
	T At(const size_t &index) const {
		Node<T> *tmp = _head;
		for (size_t i = 0; i < _size; i++) {
			if (i == index)
				return tmp->Value;
			tmp = tmp->p_next;
		}
	}
	void Reverse() {
		Node<T> *p = 0;
		Node<T> *tmp_head = _head;
		while (tmp_head) {
			Node<T> *q = tmp_head;
			tmp_head = q->p_next;
			q->p_next = p;
			p = q;
		}
		_end = _head;
		_head = p;
	}
	size_t IndexOf(const T &item) const {
		Node<T> *tmp = _head;
		for (size_t i = 0; i < _size; i++) {
			if (tmp->Value == item)
				return i;
			tmp = tmp->p_next;
		}
		return -1;
	}
};
