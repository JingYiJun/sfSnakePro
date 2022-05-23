<!-- 
this change log is to log the difference from origin sfSnake on https://github.com/jhpy1024/sfSnake.git
-->

# change log

## 20220508

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

## 20220520

1. 大幅修改 `Snake` 类的实现。(70%)
    1. 节点
    现在 `Snake` 类不依赖于 `SnakeNode` 类，不使用 `vector` 而使用 `deque` 作为蛇路径的容器，
    头结点（0号节点）作为蛇头节点，之后第$10k (k = 1, 2, ... , n)$个节点是蛇身体节点，
    使用黄色，半径为 $r$ 的圆作为节点的形状
    第$5(2k+1) (k = 1, 2, ... , n)$个节点是蛇的关节节点，使用$r \times \sqrt{3}r$的矩形作为形状
    矩形法线方向为 后一节点->前一节点 的方向

    2. 更新
    每次更新时，`push_front` 一个头结点+方向向量的节点
    同时判断尾结点的重叠次数(overlap)，若重叠次数为零，则 `pop_back` 尾结点
    每次只加入一个path节点，而将固定帧率提高到100fps，操作和视觉效果更加流畅、丝滑。

    3. 性能方面
    相比于 `vector` 每次更新时要全部移动一位，`deque` 只需要改变头尾节点，处理更高效。
    尤其在 `size()` 很大的时候，有非常显著的性能提升。

2. `Game.cpp` 的更改
    1. render()放在while中，将原先render帧数 3000+fps 降至固定的 100fps, 减少不必要的性能浪费
    GPU占用率从73%降到35%
    原版：
    ![占用率](image/原版的占用率.png "原版的占用率")
    改版：
    ![占用率2](image/改版的占用率.png "改版的占用率")

    1. 使用 `sf::VideoMode::getDesktopMode()` 函数获取当前桌面分辨率，将窗口大小设定为当前窗口分辨率的一半
    以适配不同适配分辨率的机器，后续可能会增加全屏模式。

    1. 类的静态中成员增加了作为游戏全局设置的变量，包括
    ```c++
    static bool GridVisibility_;       //全局网格可见性
    static sf::Color BackgroundColor_; //背景颜色
    static sf::Color GridColor_;       //网格颜色
    ```

3. 字体改动
   修改全局字体为 SourceHanSansSC-Bold.otf 思源黑体，支持中文显示

4. 文件树优化
   所有源文件归类到src文件夹，其他资源归类到assets文件夹，分好类。便于查看

5. makefile的优化
   使用static编译，让最终的程序可以分发。

## 20220520

1. `Fruit` 的更改
    1. 将 `Fruit` 类修改为struct，没有什么值得私有的成员变量
    2. `fruit` 的存储也由 `vector` 改为 `deque`，删除一个水果的效率提高了。
    3. 新增5种水果的表示，用score存储每种水果的得分。
    4. 修改了随机生成水果的函数，现在可以按照要求生成五种水果了。