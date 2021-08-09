#include <iostream>
#include<SFML/Graphics.hpp>
#include "Header.h"

static int rec_count = 0;

template <class T>
void drawTree(Leaf<T>* leaf, sf::RenderWindow& window, sf::Vector2f pos = sf::Vector2f((1280 / 2) - 20, 5))
{
	if (leaf != nullptr)
	{
		//sf::Vector2f pos((1280 / 2) - 20, 5);
		++rec_count;
		sf::CircleShape cage(40, 4);
		cage.setPosition(pos);
		if(leaf->cl==BLACK)
			cage.setFillColor(sf::Color::Black);
		else
			cage.setFillColor(sf::Color::Red);
		window.draw(cage);
		sf::Font font;
		font.loadFromFile("consola.ttf");
		sf::Text num;
		num.setFont(font);
		num.setFillColor(sf::Color::Blue);
		num.setCharacterSize(36);
		num.setPosition(cage.getPosition() + sf::Vector2f(18, 16));
		num.setString(std::to_string(leaf->data));
		window.draw(num);
		sf::Vector2f l_offset(-80, 80);
		sf::Vector2f r_offset(80, 80);

		sf::VertexArray line(sf::LinesStrip, 2);
		line[0].color = sf::Color::Red;
		line[1].color = sf::Color::Red;

		window.draw(line);
		if (rec_count == 1)
		{
			l_offset = sf::Vector2f(-260, 160);
			r_offset = sf::Vector2f(260, 160);
		}
		if (leaf->left != nullptr)
		{
			line[0].position = pos + sf::Vector2f(20, 60);
			line[1].position = pos + l_offset + sf::Vector2f(60, 20);
			window.draw(line);
			drawTree(leaf->left, window, (pos + l_offset));
		}
		if (leaf->right != nullptr)
		{
			line[0].position = pos + sf::Vector2f(60, 60);
			line[1].position = pos + r_offset + sf::Vector2f(20, 20);
			window.draw(line);
			drawTree(leaf->right, window, (pos + r_offset));
		}
	}
}


int main()
{
	BinaryTree<int> tree;
	tree.push(17);
	tree.push(11);
	tree.push(13);
	//tree.push(22);
	//tree.push(21);
	//tree.push(30);
	//tree.push(14);

	tree.push(9);
	//tree.push(10);

	tree.print();
	

	sf::RenderWindow window(sf::VideoMode(1280, 720), "BinaryTree");
	while (window.isOpen())
	{
		rec_count = 0;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::KeyPressed)
				window.close();
		}

		window.clear(sf::Color::White);
		drawTree(tree.root, window);
		window.display();
	}

	return 0;
}