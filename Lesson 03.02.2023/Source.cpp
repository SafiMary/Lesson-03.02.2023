#include <iostream>
#include <windows.h>
#include <map>
#include <vector>
#include <algorithm>

int foo() {

	return 2;
}

int globalvalue = 10;
int& bar() {
	return globalvalue;
}
class A {
public:
	void foo() const {
		std::cout << "A::foo() const\n";
	}
	void foo()  {
		std::cout << "A::foo() \n";
	}
};
A aFunc() { return A(); }
const A c_aFunc() { return A(); }


class Intvec {
public:
	explicit Intvec(size_t num = 0): m_size(num), m_data(new int[m_size]) {
		log("constructor");
	}
	~Intvec() {
		log("destructor");
		if (m_data) {
			delete[] m_data;
			m_data = nullptr;
		}
	}
	Intvec(const Intvec& other) : m_size(other.m_size),
		m_data(new int[m_size]) {
		log("copy constructor");
		for (size_t i = 0; i < m_size; i++) {
			m_data[i] = other.m_data[i];
		}
	}

	Intvec& operator=(Intvec&& other) noexcept{//ссылка на rvalue&&
		//оператор присваивания перемещения
		log("move assigment operator");
		std::swap(m_size,other.m_size);
		std::swap(m_data,other.m_data);
		return *this;
	}
	Intvec& operator=(const Intvec& other) {
		//оператор присваивания и копирования
		log("copy assigment operator");
		Intvec tmp(other);
		std::swap(m_size, tmp.m_size);//copy swap idioma
		std::swap(m_data, tmp.m_data);
		return *this;
	}

private:
	void log(const char* msg) {
		std::cout << "[" << this << "]" << msg << '\n';
	}
	size_t m_size;
	int* m_data;

};

int main() {
	aFunc().foo();
	c_aFunc().foo();//cv квалифицированное rvalue


	Intvec v1(20);
	Intvec v2;
	Intvec v3;
	std::cout << "assigning Lvalue...\n";
	v2 = v1;
	std::cout << "ended assigning Lvalue...\n";
	std::cout << "++++++++++++++++++++++++\n";
	std::cout << "assigning rvalue...\n";
	v3 = Intvec(33);
	std::cout << "ended assigning Lvalue...\n";


}




//int main() {
//	SetConsoleCP(1251);
//	SetConsoleOutputCP(1251);
//
//	int x = 5;
//	//foo() = 2;
//	bar() = 10;//результат выполнения бара это ссылка на globalvalue
//	//Lvalue - объект, занимающий идентифицируемое место в памяти, например имеет адрес
//
//	std::map<int, float> mymap;
//	mymap[10] = 5.6f;//вызван оператор кв скобок, который вернул ссылку на объект, который можно изменять
//
//	const int a = 5;//является Lvalue
//	// a = 10;//  не можем присвоить новое значение
//
//	//конструкторы языка принимают rvalue  в качестве аргумента
//	int t = 1;
//	int tt = 2;
//	int res = t + tt;// operator+ ожидает rvalue поэтому
//	//Lvalue  неявно преобразуется в rvalue
//	//неявного преобразования rvalue в Lvalue
//
//	int arr[] = { 1, 2 };
//	int* p = &arr[0];
//	*(p + 1) = 10; //явное преобразование rvalue (p+1) в Lvalue
//	//c помщью*
//	//*(p + 1) -Lvalue
//	// 
//	//превращение из Lvalue в  rvalue
//	int var = 10;
//	int* bad_addr = &(var + 1); //error для унарного оператора&
//	//требуется Lvalue
//
//	int* addr = &var;//ok
//	//&var = 0;//error, с левой стооны требуется Lvalue
//
//	//Lvalue  на тип Т не являюющимся функциональным
//	// или массивом, может быть преобразован в rvalue.
//	//Если Т не класс, типом  rvalue является
//	//сv- неспефицированная версия типа Т. Иначе, типом
//	//rvalue является Т
//
//	//T Lvalue -> T rvalue
//	// const volatile T Lvalue -> T rvalue 
//	// Если Т это класс, то rvalue может сохранить cv специфицированность
//	// сv: с -const , v - volatile
//
//	//сv специфицированный тип- тип,у которого 
//	//есть свойство быть либо const либо volatile
//
//	std::vector<int> vec;
//	for(size_t i = 0; i < vec.size();i++){  /*......*/  }
//
//
//
//
//
//
//
//
//}