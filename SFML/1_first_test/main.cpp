#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <chrono>
#include <iostream>
#include <thread>
using namespace std::chrono_literals;

float x = 0;
float y = 0;
float step = 10;

int main() {

  


  // 创建渲染窗口
  sf::RenderWindow window(sf::VideoMode({800, 600}), "Hello SFML!");

  // 创建角色
  sf::RectangleShape player(sf::Vector2f({100.f, 100.f}));
  // 设置角色原点
  player.setOrigin({player.getSize().x / 2, player.getSize().y / 2});
  // 设置位置
  player.setPosition({player.getSize().x / 2, player.getSize().y / 2});
  // 设置填充颜色
  // player.setFillColor(sf::Color::Black);
  // 纹理
  sf::Texture player_texture("./tux_from_linux.png");
  // 设置纹理
  player.setTexture(&player_texture);

  while (window.isOpen()) {
    // 事件处理
    while (const std::optional event = window.pollEvent()) {
      // 窗口关闭
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
      // 改变窗口大小
      else if (const auto* e = event->getIf<sf::Event::Resized>()) {
        printf("%d, %d\n", window.getSize().x, window.getSize().y);
        printf("%d, %d\n", e->size.x, e->size.y);
      }
      // 按键按下
      else if (const auto* e = event->getIf<sf::Event::KeyPressed>()) {
        // printf("Scan: %d, Code: %d\n", e->scancode, e->code);
        if (e->scancode == sf::Keyboard::Scan::A) {
          player.move({-step, 0});
        } else if (e->scancode == sf::Keyboard::Scan::D) {
          player.move({step, 0});
        } else if (e->scancode == sf::Keyboard::Scan::W) {
          player.move({0, -step});
        } else if (e->scancode == sf::Keyboard::Scan::S) {
          player.move({0, step});
        }
      }
      // 文本输入
      else if (const auto* e = event->getIf<sf::Event::TextEntered>()) {
        sf::String s(e->unicode);
        std::cout << "TextEntered: " << s.toAnsiString() << std::endl;
      }
      // 鼠标输入
      // 单次点击
      else if (const auto* e = event->getIf<sf::Event::MouseButtonPressed>()) {
        if (e->button == sf::Mouse::Button::Left) {
          player.setPosition({e->position.x, e->position.y});
        }
      }
      // 鼠标按住
      else if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
        // 一定要捕获相对于窗口的位置
        auto [new_x, new_y] = sf::Mouse::getPosition(window);
        printf("x: %d, y:%d\n", new_x, new_y);
        player.setPosition({new_x, new_y});
      }
    }

    // 清理窗口内容(可以在这里填充颜色)
    window.clear();

    // 渲染窗口内容
    window.draw(player);
    // std::this_thread::sleep_for(3s);

    // 显示窗口内容
    window.display();
  }
}