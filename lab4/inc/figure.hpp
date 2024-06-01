#pragma once
#include <SFML/Graphics.hpp>

namespace sn
{
	class Circle
	{
		float m_r;
		float m_x, m_y;
		sf::CircleShape m_shape;

	public:
		Circle() = default;

		Circle(float x, float y, float r)
		{
			Setup(x, y, r);
		}

		void Setup(float x, float y, float r)
		{
			m_x = x;
			m_y = y;
			m_r = r;
			m_shape.setRadius(m_r);
			m_shape.setPosition(m_x, m_y);
			m_shape.setFillColor(sf::Color(251, 150, 165));
		}

		sf::CircleShape Get()
		{
			return m_shape;
		}
	};


	class Triangle
	{
		float m_r;
		float m_x, m_y;
		sf::CircleShape m_triangle; //т.к. круг тот же полигон, но с очень большим кол-вом сторон

	public:
		Triangle() = default;

		Triangle(float x, float y, float r)
		{
			Setup(x, y, r);
		}

		void Setup(float x, float y, float r)
		{
			m_x = x;
			m_y = y;
			m_r = r;
			m_triangle.setRadius(m_r);
			m_triangle.setPosition(m_x, m_y);
			m_triangle.setPointCount(3);
			m_triangle.setFillColor(sf::Color(255, 184, 90));
		}

		sf::CircleShape Get()
		{
			return m_triangle;
		}
	};


	class Vertex
	{
		float m_x1, m_y1;
		float m_x2, m_y2;
		sf::Vertex m_line;

	public:
		Vertex() = default;

		Vertex(float x1, float y1, float x2, float y2)
		{
			Setup(x1, y1, x2, y2);
		}

		void Setup(float x1, float y1, float x2, float y2)
		{
			m_x1 = x1;
			m_y1 = y1;
			m_x2 = x2;
			m_y2 = y2;

			sf::Vertex m_line[] = { sf::Vertex(sf::Vector2f(m_x1, m_y1)), sf::Vertex(sf::Vector2f(m_x2, m_y2)) };

			//Vertex m_line[] = { Vertex(Vector2f(m_x1, m_y1)), Vertex(Vector2f(m_x2, m_y2)) };
		}

		sf::Vertex Get()
		{
			return m_line;
		}

	};


	class Rectangle
	{
		float m_a, m_b; //стороны
		float m_x, m_y;
		sf::RectangleShape m_rectangle;

	public:
		Rectangle() = default;

		Rectangle(float x, float y, float a, float b)
		{
			Setup(x, y, a, b);
		}

		void Setup(float x, float y, float a, float b)
		{
			m_x = x;
			m_y = y;
			m_a = a;
			m_b = b;
			//sf::RectangleShape rectangle(sf::Vector2f(m_x, m_y)); ???
			m_rectangle.setSize(sf::Vector2f(m_a, m_b));
			m_rectangle.setPosition(m_x, m_y);
			m_rectangle.setFillColor(sf::Color(90, 255, 253));
		}

		sf::RectangleShape Get()
		{
			return m_rectangle;
		}
	};


	class RectLine
	{
		float m_a, m_angle; //длина, угол
		float m_x, m_y;
		sf::RectangleShape m_rectline;

	public:
		RectLine() = default;

		RectLine(float x, float y, float a, float ang)
		{
			Setup(x, y, a, ang);
		}

		void Setup(float x, float y, float a, float ang)
		{
			m_x = x;
			m_y = y;
			m_a = a;
			m_angle = ang;
			m_rectline.setSize(sf::Vector2f(m_a, 1));
			m_rectline.setPosition(m_x, m_y);
			m_rectline.rotate(m_angle);
			m_rectline.setFillColor(sf::Color(255, 253, 90));
		}

		sf::RectangleShape Get()
		{
			return m_rectline;
		}
	};
}