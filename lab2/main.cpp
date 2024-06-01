// (вариант 6) Создайте класс, описывающий указанный в вашем варианте реальный объект. Не забывайте про 
// принципы абстракции и инкапсуляции.Продемонстрируйте использование вашего класса.



//метод - функция в структуре(как работать с объектом)
//конструктор - нет возвращаемых значений, имя совпадает с классом(специальный метод который вызывается всегда, при создании объекта)
//специальный метод для удаления ~(название класса)
//Структура - хранение данных (поля открыты)
//Класс - объект для выполнение действий над ним (поля закрыты)


#include <iostream>
#include <math.h>

//Треугольник, расчет площади, периметра
class Triangle
{
	//m_ поля класса
	int m_a, m_b, m_c;

public:
	//конструктор по умолчанию
	Triangle() = default;
	Triangle(int a, int b, int c)
	{
		setA(a);
		setB(b);
		setC(c);
	}
	//сеттеры
	void setA(int a)
	{
		if (a < 0)
			std::cout << "Negative A" << std::endl;
		m_a = a;
	}

	void setB(int b)
	{
		if (b < 0)
			std::cout << "Negative B" << std::endl;
		m_b = b;
	}

	void setC(int c)
	{
		if (c<0)
			std::cout << "Negative C" << std::endl;
		m_c = c;
	}
	
	//площадь через формулу герона
	float square()
	{
		float p = ((m_a + m_b + m_c) / 2);
		return sqrt(p * (p - m_a)*(p - m_b)*(p - m_c));
	}
	//периметр
	int perimetr()
	{
		return (m_a + m_b + m_c);
	}

};

int main()
{
	int a, b, c;

	std::cout << "enter triangle sides a, b, c: ";
	std::cin >> a >> b >> c;

	Triangle r{};

	r.setA(a);
	r.setB(b);
	r.setC(c);

	std::cout.precision(3);
	std::cout << "ploshyad: " << r.square() << std::endl;
	std::cout << "perimetr: " << r.perimetr() << std::endl;

}
