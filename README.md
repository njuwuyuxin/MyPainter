## MyPainter 系统使用说明书

##### 作者姓名：吴雨昕 161290019

### 开发环境

- 编译器: QtCreator 4.10.0 (Community)
- Develop Kit: Qt_5_12_5_MinGW_64_bit
- Qt版本: 5.12.5

### 代码编译说明
代码编译时使用了MinGW 64bit 编译器，Qt版本5.12.5，可在Debug或Release模式下编译。

### 使用方法
- 工具栏：工具栏包括各种图元图标，点击可选择模式，还包括选择画笔颜色，清空画布等功能按钮
  - 选择画笔颜色：点击按钮后，弹出颜色选择框，选择好颜色后，即可继续绘制![SelectColor](/Pictures/SelectColor.png)
  - 清空画布：点击工具栏中的清空图标，即可清空画布

- 绘图模式：
  - 线段：鼠标点击画布开始绘制，松开画布绘制完成，线段以点击处为起点，以释放处为终点![DrawLine](/Pictures/DrawLine.png)
  - 多边形：鼠标点击或拖动绘制顶点和边，当鼠标按下右键，自动补全最后一条边，多边形完成绘制![DrawPolygon](/Pictures/DrawPolygon.png)
  - 圆形：鼠标点击画布开始绘制，松开画布绘制完成，圆形以点击处为圆心，以释放处和点击处的距离为半径![DrawCircle](/Pictures/DrawCircle.png)
  - 椭圆：鼠标点击点作为椭圆所在外接矩形某一顶点，拖动绘制椭圆，鼠标时放点作为所在外接矩形与起始点对应的对角顶点。![DrawEllipse](/Pictures/DrawEllipse.png)
  - 曲线：鼠标点击点作为各控制点位置，可以点击任意数量的控制点，按下鼠标右键时，曲线根据之前点击的控制点，进行绘制。![DrawCurve](/Pictures/DrawCurve.png)
  
- 命令行模式：
  - 命令行模式可以通过接受两个参数：指令序列文件和保存图片目录，来进行图元绘制![Cmd](/Pictures/Cmd.png)
  - 命令行模式目前已实现各图元的绘制以及各图元的平移功能。GUI目前尚未对应图元平移功能。