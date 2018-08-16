#pragma once
template<typename TKey,typename TValue>
struct Entry {
public:
	int _hashCode;
	Entry *_next;
	TKey *_key;
	TValue *_value;
	Entry() :_hashCode(-1), _next(nullptr),_key(nullptr),_value(nullptr) { }
	~Entry() {
		delete _key;
		delete _value;
	}
};
template<typename TKey>
class Comparer {
public:
	typedef bool(*Equals_)(const TKey &k1, const TKey &k2);
	typedef int(*HashCode_)(const TKey &key);
	Equals_ Equals;
	HashCode_ HashCode;
	Comparer(Equals_ e, HashCode_ h) :Equals(e), HashCode(h) { }
};
template<typename TKey,typename TValue>
class Dictionary {
private:
	int *_buckets;
	Entry<TKey,TValue> **_entries;
	int _size;
	int _count;
	Comparer<TKey> *_comparer;
	const int _primes[72];
	int GetPrime(const int &min) {
		if (min > 3) for (int i = 0; i < 72; i++) if (_primes[i] >= min) return _primes[i];
		return 3;
	}
	void Initialize(const int &capcity) {
		int cap = GetPrime(capcity);
		_buckets = new int[cap];
		_entries = new Entry<TKey,TValue>*[cap];
		for (int i = 0; i < cap; i++) {
			_buckets[i] = -1;
			_entries[i] = nullptr;
		}
		_size = cap;
	}
public:
	~Dictionary() {
		for (int i = 0; i < _size; i++) {
			if (_buckets[i] != -1) {
				Entry<TKey, TValue> *tmp = _entries[i];
				Entry<TKey, TValue> *tmp_1 = tmp;
				while (tmp != nullptr) {
					tmp = tmp->_next;
					delete tmp_1;
					tmp_1 = tmp;
				}
			}
		}
		delete[] _buckets, _entries;
		delete _comparer;
	}
	void Clear() {
		for (int i = 0; i < _size; i++) {
			if (_buckets[i] != -1) {
				Entry<TKey, TValue> *tmp = _entries[i];
				Entry<TKey, TValue> *tmp_1 = tmp;
				while (tmp != nullptr) {
					tmp = tmp->_next;
					delete tmp_1;
					tmp_1 = tmp;
				}
				_buckets[i] = -1;
				_entries[i] = nullptr;
			}
		}
		_count = 0;
	}
	TValue &operator[](const TKey &indexKey) const {
		int hashcode = _comparer->HashCode(indexKey);
		if (_buckets[hashcode%_size] == -1)
			throw std::string("Key not exists!");
		Entry<TKey, TValue> *tmp = _entries[hashcode%_size];
		while (tmp != nullptr) {
			if (_comparer->Equals(*(tmp->_key), indexKey)) {
				return *(tmp->_value);
			}
			tmp = tmp->_next;
		}
		throw std::string("Key not exists!");
	}
	void Remove(const TKey &key) {
		int hashcode = _comparer->HashCode(key);
		if (_buckets[hashcode%_size] == -1)
			throw std::string("Key not exists!");
		Entry<TKey, TValue> *tmp = _entries[hashcode%_size];
		while (tmp != nullptr) {
			if (_comparer->Equals(*(tmp->_key), key)) {
				
			}
		}
	}
	inline const int &Count()const {
		return _count;
	}
	void Add(const TKey &key,const TValue &value) {
		int hashcode = _comparer->HashCode(key);
		if (_buckets[hashcode%_size]==-1) {
			Entry<TKey,TValue> *tmp = new Entry<TKey,TValue>();
			tmp->_hashCode = hashcode;
			TKey *k = new TKey(key);
			TValue *v = new TValue(value);
			tmp->_key = k;
			tmp->_value = v;
			_count++;
			_entries[hashcode%_size] = tmp;
			_buckets[hashcode%_size] = 0;
		}
		else {
			Entry<TKey, TValue> *tmp = _entries[hashcode % _size];
			while (tmp != nullptr) {
				if (_comparer->Equals(*(tmp->_key),key))
					throw std::string("Key must be unique!");
				if (tmp->_next == nullptr) {
					Entry<TKey,TValue> *newEntry = new Entry<TKey,TValue>();
					TKey *k = new TKey(key);
					TValue *v =new TValue(value);
					newEntry->_hashCode = hashcode;
					newEntry->_key = k;
					newEntry->_value = v;
					tmp->_next = newEntry;
					_count++;
					return;
				}
				tmp = tmp->_next;
			}
		}
	}
	Dictionary(const int &capcity,Comparer<TKey> *comparer) :_comparer(comparer),_count(0),_primes{
		3, 7, 11, 17, 23, 29, 37, 47, 59, 71, 89, 107, 131, 163, 197, 239, 293, 353, 431, 521, 631, 761, 919,
		1103, 1327, 1597, 1931, 2333, 2801, 3371, 4049, 4861, 5839, 7013, 8419, 10103, 12143, 14591,
		17519, 21023, 25229, 30293, 36353, 43627, 52361, 62851, 75431, 90523, 108631, 130363, 156437,
		187751, 225307, 270371, 324449, 389357, 467237, 560689, 672827, 807403, 968897, 1162687, 1395263,
		1674319, 2009191, 2411033, 2893249, 3471899, 4166287, 4999559, 5999471, 7199369 } {
		if (comparer == nullptr) throw std::string("Comparer can not be null!");
		Initialize(capcity);
	}
};