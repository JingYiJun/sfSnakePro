<!-- 
this change log is to log the difference from origin sfSnake on https://github.com/jhpy1024/sfSnake.git
-->

# change log

<!-- ## 20220508 -->

1. modify `void GameScreen::generateFruit()` in `GameScreen.cpp`
```c++
// GameScreen.cpp
- static std::default_random_engine engine;
- engine.seed(time(NULL));
+ static std::default_random_engine engine(time(NULL));
```
修复了水果生成为同一行的bug

2. modify `Snake::Snake()` in `Snake.cpp`
```c++
// Snake.cpp
- pickupBuffer_.loadFromFile("Sounds/pickup.aiff");
+ pickupBuffer_.loadFromFile("Sounds/pickup.wav");
```
修复了拾取水果后无音效的bug
需要将"Sounds/pickup.aiff"转码为"Sounds/pickup.wav"

> `// InputSoundFile.hpp`
> The supported audio formats are: WAV (PCM only), OGG/Vorbis, FLAC.
> The supported sample sizes for FLAC and WAV are 8, 16, 24 and 32 bit.

3. modify `Snake::Snake()` in `Snake.cpp`
```c++
// Snake.cpp
- Snake::Snake() : direction_(Direction::Up), hitSelf_(false)
+ Snake::Snake() : hitSelf_(false), direction_(Direction::Up)
```
修改了构造函数初始化表的顺序为`Snake`类中声明的顺序

4. modify `GameOverScreen::GameOverScreen(std::size_t score)` in `GameOverScreen.cpp`

```c++ 
// GameOverScreen.cpp
- text_.setColor(sf::Color::Red);
+ text_.setFillColor(sf::Color::Red);
```

5. modify `MenuScreen::MenuScreen()` in `MenuScreen.cpp`
```c++ 
// MenuScreen.cpp
- snakeText_.setColor(sf::Color::Green);
+ snakeText_.setFillColor(sf::Color::Green);
```
将已弃用(deprecated)的`setColor`方法更改为建议使用的`setFillColor`方法

**自此源代码中的所有bug被修复，所有编译错误和建议被修复**