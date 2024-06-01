#pragma once
#include <string>
#include <thread>
#include <iostream>
#include <Ship.hpp>
#include <Bullet.hpp>
#include <chrono>

namespace mt
{

	const float pi = acos(-1);

	class Game
	{
		int m_width;
		int m_height;
		std::string m_capture;
		mt::Circle* m_c;
		int m_n;
		sf::RenderWindow m_window;
		sf::Texture m_textureBackground;
		sf::Sprite m_spriteBackground;
		sf::Font m_font;
		sf::Text m_fpsText;
		sf::Text text;
		sf::Text text2;
		sf::Text text3;
		Ship m_ship;
		bool isVisible = true;
		bool isTouchBorder = true;
		bool circleavailible[1] = { true };
		bool timetocreate = true;
		
		
	public:
		
		
		Game(int width, int height, const std::string& capture)
		{
			m_width = width;
			m_height = height;
			m_capture = capture;
		}

		//создание сущностей и подгрузка assets
		bool Setup(int n)
		{
			m_n = n;
			// Создание окна
			m_window.create(sf::VideoMode(m_width, m_height), m_capture);

			// Загрузка текстуры фона
			if (!m_textureBackground.loadFromFile("assets\\background.jpg"))
			{
				std::cout << "Error while loading background.jpg" << std::endl;
				return false;
			}
			m_spriteBackground.setTexture(m_textureBackground);

			// Загрузка шрифта
			if (!m_font.loadFromFile("assets\\arial.ttf"))
			{
				std::cout << "Error while loading arial.ttf" << std::endl;
				return false;
			}
			m_fpsText.setFont(m_font);
			//надпись
			text.setFont(m_font);
			text.setCharacterSize(30);
			text.setColor(sf::Color::Yellow);
			text.setString("Press (space) for regular and (T) for Touhou");
			text.setPosition(10, 50);

			text2.setFont(m_font);
			text2.setCharacterSize(20);
			text2.setColor(sf::Color::Yellow);
			text2.setString("ya krayne izvinyayus chto tak tyanu s labami, prosto delalla ih parallel'no *shrug kaomoji*");
			text2.setPosition(10, 100);

			text3.setFont(m_font);
			text3.setCharacterSize(20);
			text3.setColor(sf::Color::Yellow);
			text3.setString("nu i chastichno mne prihodyat idei i ya zaciklivayus' na ih realizacii (chto konechno ne vsegda vyhodit), naprimer granicy ekrana dlya korablya");
			text3.setPosition(10, 150);

			// Создание корабля игрока
			if (!m_ship.Setup(100, 100))
				return false;

			srand(time(0));

			m_c = new mt::Circle[m_n];
			for (int i = 0; i < m_n; i++)
			{
				int r = rand() % 100 + 10;
				int x = rand() % (1000 - 2*r) + r;
				int y = rand() % (600 - 2*r) + r;
				int v = rand() % 50 + 100;
				float alfa = rand() % 7;
				m_c[i].Setup(x, y, r, v, alfa);
			}
		}
		//бордер
		void TouchBorder(Circle& obj)
		{
			float x = obj.X();
			float y = obj.Y();
			float r = obj.R();

			//std::cout << x << " " << y << std::endl;

			if (isTouchBorder)
			{
				isTouchBorder = false;

				if (x + r >= m_width || x - r <= 0)
				{
					obj.Alfa(pi - obj.Alfa());
				}

				if (y + r >= m_height || y - r <= 0)
				{
					obj.Alfa(2 * pi - obj.Alfa());
				}

			}
			else
			{
				if (x + r + 20 <= m_width || x - r - 20 >= 0)
				{
					isTouchBorder = true;
				}

				if (y + r + 20 <= m_height || y - r - 20 >= 0)
				{
					isTouchBorder = true;
				}
			}

		}

		bool bulletTouch(Bullet &obj, Circle &obj2)
		{
			float x1 = obj.X();
			float y1 = obj.Y();
			float x2 = obj2.X();
			float y2 = obj2.Y();
			float r1 = obj.R();
			float r2 = obj2.R();
			float x = x1 - x2;
			float dy = y1 - y2;
			float d = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)) + 1; // расстояние между объектами
			if (d < r1 + r2) //если расстояние меньше суммы радиусов пути и круга то они "сталкиваются"
			{
				return true;
			}
			
		}

		void Collision(int i)
		{
			Circle& c = m_c[i];
			float dist = sqrt(pow(m_ship.X() - c.X(), 2) + pow(m_ship.Y() - c.Y(), 2));
			if (m_ship.R() + c.R() >= dist)
			{
				std::cout << "Collision " << m_ship.V() << std::endl;
				isVisible = false;
			}
		}

		void LifeCycle()
		{
			sf::Clock clock;
			sf::Clock lifespantimer;
			m_window.setFramerateLimit(60);
			
			while (m_window.isOpen())
			{
				// Обработка событий
				sf::Event event;
				while (m_window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed)
						m_window.close();
				}

		

				// Обработка клавиатуры TODO
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
				{
					m_ship.setVelocity(6);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
				{
					m_ship.setVelocity(-6);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
					m_ship.Rotate(-3);
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					m_ship.Rotate(3);
				}
				
			
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					if (lifespantimer.getElapsedTime().asSeconds() >= 0.3)
					{
						m_ship.creatbullet();
						lifespantimer.restart();
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
				{
					if (lifespantimer.getElapsedTime().asSeconds() >= 0.05)
					{
						m_ship.creatbullet();
						lifespantimer.restart();
					}
				}


				float dt = clock.getElapsedTime().asSeconds();
				clock.restart();

				for (int i = 0; i < m_n; i++)
				{
					float x = m_c[i].X();
					float y = m_c[i].Y();
					float r = m_c[i].R();
					float v = m_c[i].V();
					float alfa = m_c[i].Alfa();

					float x_s = x + v * cos(alfa) * dt;
					float y_s = y + v * sin(alfa) * dt;


					bool collision = false;
					if (x_s + r >= m_width)
					{
						m_c[i].Alfa(pi - m_c[i].Alfa());
						m_c[i].X(m_width - r);
						collision = true;
					}

					if (x_s - r <= 0)
					{
						m_c[i].Alfa(pi - m_c[i].Alfa());
						m_c[i].X(r);
						collision = true;
					}

					if (y_s + r >= m_height)
					{
						m_c[i].Alfa(2 * pi - m_c[i].Alfa());
						m_c[i].Y(m_height - r);
						collision = true;
					}

					if (y_s - r <= 0)
					{
						m_c[i].Alfa(2 * pi - m_c[i].Alfa());
						m_c[i].Y(r);
						collision = true;
					}

					if (!collision)
					{
						m_c[i].X(x_s);
						m_c[i].Y(y_s);
					}
				}

				
				for (int i = 0; i < m_ship.numberOfBullets(); i++)
				{
					for (int j = 0; j < m_n; j++)
						//*m_ship ссылка
						if (bulletTouch(*m_ship.GetBullet(i), m_c[j]) == true)
						{
							//аннигиляция пули i
							m_ship.delbul(i);
							//аннигиляция круга j
							m_c[j].R()=0;
							m_c[j].V() = 0;
							m_c[j].Alfa() = 0;
							m_c[j].X() = -1;
							m_c[j].Y() = -1;
							circleavailible[j] = false; //
						}
				}
				
				// Перемещение корабля
				m_ship.Move(dt);

				m_fpsText.setString(std::to_string(1 / dt));

				// Отображение
				m_window.clear();
				m_window.draw(m_spriteBackground);
				m_window.draw(m_fpsText);
				m_window.draw(text);
				m_window.draw(text2);
				m_window.draw(text3);
				for (int i = 0; i < m_n; i++)
					if (circleavailible[i] == true)
					{
						m_window.draw(m_c[i].Get());
					}

				for (int i=0; i < m_ship.numberOfBullets(); i++)
					m_window.draw(m_ship.GetBullet(i)-> Get());
				if (isVisible)
					m_window.draw(m_ship.Get());
				m_window.display();

			}
			
		}
	};

}