#include"标头.h"

template<typename T>
class MyVector {
private:
	T* data;
	size_t _size;
	size_t _capacity;
	void expand(size_t new_cap=0) {
		if (_capacity == 0) {
			reserve(1);
			return;
		}
		new_cap = _capacity * 2;
		T* new_data = new T[new_cap];
		for (size_t i = 0; i < _size; i++) {
			new_data[i] = move(data[i]);
		}
		data = new_data;
		_capacity = new_cap;
	}
public:
	//默认构造函数
	MyVector() :data(nullptr), _size(0), _capacity(0) { cout << "默认构造函数！" << endl; }
	//拷贝构造函数
	MyVector(const MyVector& vec) {
		data = new T[vec._capacity];
		for (size_t i = 0; i < vec._size; i++) {
			data[i] = vec.data[i];
		}
		_size = vec._size;
		_capacity = vec._capacity;
		cout << "拷贝构造函数！" << endl;
	}
	//移动构造函数
	MyVector(MyVector&& vec) :data(vec.data), _size(vec._size), _capacity(vec._capacity) { 
		cout << "移动构造函数！" << endl; 
		vec.data = nullptr;
		vec._size = 0;
		vec._capacity = 0;
	}
	//析构函数
	~MyVector() {
		delete[]data;
		cout << "析构函数!" << endl;
	}
	//重载=运算符
	MyVector& operator=(const MyVector& vec) {
		if (this == &vec)return *this;
		T* new_data = new T[vec._capacity];
		_size = vec._size;
		_capacity = vec._capacity;
		for (size_t i = 0; i < _size; i++) {
			new_data[i] = vec.data[i];
		}
		delete[]data;
		data = new_data;
		cout << "重载=运算符！" << endl;
		return *this;
	}
	//添加元素
	void push_back(const T& elem) {
		if (_size >= _capacity) {
			expand();
		}
		data[_size++] = elem;
	}
	//弹出元素
	void pop_back() {
		if (!empty()) {
			_size--;
		}
		else throw"data is empty!";
	}
	//预分配
	void reserve(size_t new_cap) {
		if (new_cap > _capacity) {
			T* new_data = new T[new_cap];
			for (size_t i = 0; i < _size; i++) {
				new_data[i] = move(data[i]);
			}
			delete[]data;
			data = new_data;
			_capacity = new_cap;
		}
	}
	//operator[]不检查越界
	T& operator[](const size_t val) {
		return data[val];
	}
	T& operator[](const size_t val) const{
		return data[val];
	}
	//at检查是否越界
	T& at(const size_t val) {
		if (val >= _size) {
			throw "wrong range!!!";
		}
		return data[val];
	}
	//容量查询
	size_t size() const{
		return _size;
	}
	size_t capacity() const{
		return _capacity;
	}
	bool empty() const{
		return _size == 0;
	}
	//迭代器
	T* begin() {
		return data;
	}
	T* begin() const{
		return data;
	}
	T* end() {
		return data + _size;
	}
	T* end() const{
		return data + _size;
	}
};

int main() {
	MyVector<char> vec;
	for (int i = 0; i < 100; i++) {
		vec.push_back('a');
	}
	cout<<vec.capacity()<<endl;
	cout<<vec.size()<<endl;
	//vec.push_back('a');
	//cout<<vec.size()<<endl;
	//cout<<vec.capacity()<<endl;
	////cout<<vec.begin()<<endl;
	////cout<<vec.end()<<endl;
	//cout<<vec[0]<<endl;
	//cout << vec.at(0) << endl;
	//vec.pop_back();
	//cout << vec.capacity() << endl;
	//cout << vec.size() << endl;
	//vec.push_back('a');
	//cout << vec[0] << endl;
	//cout << vec.at(0) << endl;
	//vec.pop_back();
	//vec.pop_back();
}