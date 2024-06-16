很多問題是沒有解析解的，例如橢圓積分，所以必須用數值解來得到數值，以前只能使用手算，現在都可以用電腦算，所以數值方法在現在是非常有用的。

## 1. 微分的定義
給定一個 f(x), f 在 [a, b] 中連續，且 x∈[a, b]。微分是從極限開始定義。
$$\frac{d}{dx} f(x) = f'(x) = \lim_{h \to 0} \frac{f(x+h) - f(x)}{h}$$

#### 1. 數值微分
因為在電腦中無法讓 h->0，所以只能轉為差分方程
$$\frac{d}{dx} f(x) = \lim_{h \to 0} \frac{f(x+h) - f(x)}{h} \rightarrow \frac{\Delta f(x)}{\Delta x} = \frac{f(x+\Delta x) - f(x)}{\Delta x}$$
舉例來說 $\Delta x = 2$，則差分方程轉為 code 為
$$\frac{\Delta f(x)}{\Delta x} = \frac{f(x+2) - f(x)}{2} \rightarrow \frac{\Delta f[0]}{\Delta x[0]} = \frac{f[2] - f[0]}{2}, \frac{\Delta f[1]}{\Delta x[1]} = \frac{f[3] - f[1]}{2}$$
數值微分相較於數值積分比較單純，因為只是求兩點斜率而已。
![image](https://github.com/JrPhy/numerical/blob/master/Integration/pic/diff_eq.jpg)
[圖一：數值微分]
## 2. 積分的定義
給定一個 f(x), f 在 [a, b] 中連續，且 x∈[a, b]。積分就是與座標軸圍成的面/體積。雖然 f(x) 不用連續也可以積分，只需要分段積分即可。
$$\int_{a}^{b} f(x) = \lim_{\Delta x \to 0} \sum_{i=0}^{n} f(x_i)\Delta x$$
在此可定義上和 
$$U = \lim_{\Delta x \to 0}  \sum_{i=1}^{n} f(x_i)\Delta x$$
與下和 
$$L = \lim_{\Delta x \to 0} \sum_{i=0}^{n-1} f(x_i)\Delta x$$
若此積分存在，則 L ≤ I ≤ U
![image](https://github.com/JrPhy/numerical/blob/master/Integration/pic/int_UL.jpg)\
[圖二：長方形法]
#### 1. 數值積分
從定義來講，直接求出長方形面積和即可。例如 $\Delta x = 2$，則數值積分值為\
f[0]*2 + f[2]*2 + ... + f[n-2]*2\
$\Delta x = 2$ 在數值積分中會取 (上限 - 下限)/切的分數\
$$\Delta x = \frac{b-a}{n}, I = \sum_{i=0}^{n} f(x+\Delta x)\Delta x$$
很明顯可看出，誤差會跟 n 有關，當 n -> 0 極為微分的定義。但是在電腦中除了數值誤差，還有捨入誤差，也就是浮點數本身的誤差，所以就有其他數值積分法來降低誤差。

## 3. 梯形法
從圖二可以知道，對於一曲線來說，用長方形的誤差會很大，所以用梯形的誤差會比較小
$$A = \sum_{i=0}^{n} \frac{f(x)+f(x+\Delta x)}{2}\Delta x $$
$$= 0.5f(x_0) + 0.5f(x_1) + 0.5f(x_1) + 0.5f(x_2) + ... + 0.5f(x_{n-1}) + 0.5f(x_n)$$
$$= 0.5f(x_0) + f(x_1) + f(x_2) + ... + f(x_{n-1}) + 0.5f(x_n)$$
$$= 0.5(f(x_0)+f(x_n) + \sum_{i=1}^{n-1}f(x_i)$$
不過對於任意曲線來說，梯形法在某些地方還是會有較高的誤差，所以就可以用多個點來 fit 出該部分的曲線，在對該部分做積分即可
![image](https://github.com/JrPhy/numerical/blob/master/Integration/pic/int_method.jpg)\
[圖三：梯形法與辛普森法]
## 4. 辛普森 1/3 法
對任一一個拋物線而言 y = ax<sup>2</sup> + bx + c, -h ≤ x ≤ x，積分得
$$A = \int_{-h}^{h} ydx = \int_{-h}^{h} (ax^2 + bx + c)dx$$
$$= (\frac{ax^3}{3} + \frac{bx^2}{2} + cx + d) |_{-h}^{h}$$
$$= (\frac{2ah^3}{3} + 2ch) = \frac{h}{3}(2ah^2 + 6c)$$
假設該拋物線通過以下三點 (-h, y<sub>0</sub>), (0, y<sub>1</sub>), (h, y<sub>2</sub>)
$$y_0 = ah^2 - bh + c, y_1 = c, y_2 = ah^2 + bh + c$$
可以得到 2ah<sup>2</sup> + 2c = y<sub>0</sub> + y<sub>2</sub>, c = y<sub>1</sub>

$$A = \frac{2ah^3}{3} + 2ch = \frac{h}{3}(2ah^2 + 6c) = \frac{h}{3}(y_0 + 4y_1 + y_2) $$
展開可得
$$\frac{h}{3}(y_0 + 4y_1 + y_2) + \frac{h}{3}(y_2 + 4y_3 + y_4) + ... + \frac{h}{3}(y_{n-2} + 4y_{n-1} + y_n)$$
$$= \frac{h}{3}(y_0 + 4 odd + 2even + y_n)$$
![image](https://github.com/JrPhy/numerical/blob/master/Integration/pic/13_method.jpg)\
[圖四：辛普森 1/3 法]\
在此直接在做一個計算 $I = \int_{-h}^{h} e^xdx = e-1 ~ 1.718281828...$\

| n | result | error |
| ---: | ---: | ---: |
| 3 | 1.718861 | 5.79e-04 |
| 4 | 1.466244 | -2.52e-01 |
| 5 | 1.718319 | 3.70e-05 |
| 6 | 1.555140 | -1.63e-04 |
| 7 | 1.718289 | 7.34e-06 |
| 8 | 1.623194 | -1.20e-04 |
| 9 | 1.718283 | 9.53e-07 |

可以看到當 n 為偶數時誤差會非常大，原因如圖四，因為會多算或少算一項。所以需要在混用 3/8 法
## 5. 辛普森 3/8 法
其推導方法如 1/3 法，最後結果可得
$$= \frac{3h}{8}(y_0 + 4(其他) + 2(3 的倍數) + y_n)$$
所以混用 1/3 法與 3/8 法，當資料點數為 2 時用梯形法，點數為  用 1/3 法， 4 用 3/8 法，其他則混用 1/3 與 3/8 法。\
以上都是討論 dx<sub>1</sub> = dx<sub>2</sub>  = ... = dx<sub>n</sub>，若 dx 不同的話可以參考以下論文。\
https://www.researchgate.net/publication/317339672_Numerical_Integration_Schemes_for_Unequal_Data_Spacing

There are many methods for integration, simpson's method is most widely used, 
so I just provide simpson's code. but introduce other mathods for integration.

#Note: If you integrate in polar or somespace with angle, remember to transform to degree to rad.

#Note: In scipy, it uses 1/3 rule for simpson, it just apply for odd number of point.
       For even, it uses trapezoid method, so the error is higher.
       
Try the script in testScipy
