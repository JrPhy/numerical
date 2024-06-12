內插是一種在資料範圍內建立新資料的方法，有內插跟外插，不過外插不一定能跟原始資料類似。有以下四種內插方法
1. 線性內插
2. Lagrange 內插
3. Spline 內插
4. 最小平方法內插

## 1. 線性內插
這是最簡單的內插方式，從最簡單的一維開始，假設有兩個點 a, b，距離為 d = |a - b|, | | 為絕對值，中間有一點 c，|b - c| = t, |a - b| = d - t
```
a-------------c---------------------b
|-------------|---------------------|
----- d - t ------------ t ----------
```
由距離比例可知
$\dfrac{t}{d-t} = \dfrac{b-c}{c-a}$ --> c = (d-t)b + ta。
若 d = 1, t = 0.5，則 c = 0.5a + 0.5b。而在程式中只存資料點，做內插之後資料點會變多，所以要另外新開一個陣列。假設原本有 m 的資料點，要在每兩個點中間插一個值，也就是用中點內插，新陣列長度為
```
(m-1)*(insert+1)+1
```
雖然線性內插很方便，但是誤差也是很大，所以有上面提到的另外三種方法\
![image](https://github.com/JrPhy/numerical/blob/master/interpolate/pic/interpolate.jpg)\
而二維內插就是直接去推廣，個別維度去做內插即可。

## 2. Lagrange 內插
如果有 m+1 個資料點，那麼最高可以得到 m 階的多項式
$$f(x) = \sum_{i=0}^{m} (a_i)^i$$
只需把 a<sub>i</sub> 全部解出來即可，可以寫成矩陣表示，此矩陣稱為 Vandermonde matrix
|   |  |  |  |  |  |  |  |  |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 1 | x<sub>0</sub> | x<sub>0</sub><sup>2</sup> | ... | x<sub>0</sub><sup>m</sup> | | a<sub>0</sub> | | y<sub>0</sub> |
| 1 | x<sub>1</sub> | x<sub>1</sub><sup>2</sup> | ... | x<sub>1</sub><sup>m</sup> | | a<sub>1</sub> | | y<sub>1</sub> |
| . | . | . | . | . | | . | | . | | . |
| 1 | x<sub>m</sub> | x<sub>m</sub><sup>2</sup> | ... | x<sub>2</sub><sup>m</sup> | | a<sub>m</sub> | | y<sub>m</sub> |

而 Vandermonde matrix 是一個[病態條件](https://github.com/JrPhy/numerical/tree/master/least-square#1-lu-%E5%88%86%E8%A7%A3)的矩陣，所以通常不會直接去解，而是去展開解。假設有三個點要去找出二次式，那麼\
$$P_2(x) = \sum_{i=0}^{2} (a_i)^i$$
P<sub>2</sub>(x<sup>0</sup>) = f(x<sub>0</sub>)\
P<sub>2</sub>(x<sup>1</sup>) = f(x<sub>1</sub>)\
P<sub>2</sub>(x<sup>2</sup>) = f(x<sub>2</sub>)\
![image](https://github.com/JrPhy/numerical/blob/master/interpolate/pic/Lagrange_inter.jpg)\
將每個三階行列式做完基本列運算在做降階可得\
![image](https://github.com/JrPhy/numerical/blob/master/interpolate/pic/Lagrange_inter_sol.jpg)\
即可得到之前熟悉的形式。用連加與連乘符號即可化簡為\
![image](https://github.com/JrPhy/numerical/blob/master/interpolate/pic/Lagrange_poly.jpg)

#### Runge 現象
假設有一函數為 $f(x) = \dfrac{1}{1+25x^2}$，在函數上得到 m+1 個點，且用 Lagrange 內插，則在兩端對有很大的震動，所以在選擇次數時通常不會選太高，Spline 內插就是只有使用三次函數進行 fit 與內插
![image](https://upload.wikimedia.org/wikipedia/commons/f/f9/Rungesphenomenon.png)

## 3. Spline 內插
在 Word 與 PPT 中有貝茲曲線，就是一種 Spline 曲線，用來連接兩個不同點的曲線。在此我們常取三次方的 Spline 曲線來使用，稱為 Cubic Spline，但是有四個未知數卻只有兩個方程式，是否可以得到唯一一條曲線呢?在此還需要加上其他條件，為了讓整條曲線看起來更平滑，還需要在邊界上有一階與二階微分連續的條件，所以\
S(x<sub>0</sub><sup>+</sup>) = S(x<sub>0</sub><sup>+</sup>)\
S'(x<sub>0</sub><sup>+</sup>) = S'(x<sub>0</sub><sup>+</sup>)\
S''(x<sub>0</sub><sup>+</sup>) = S''(x<sub>0</sub><sup>+</sup>)\
會發現還缺少了一個條件。因為在此還有微分，所以最後在給定初始條件即可唯一決定一條 Cubic Spline。實際上根據不同的初始條件，也會有不同的性質
1. Natural Spline: 起始點與終點的二階微分為 0，也就是 S''(x<sub>0</sub>) = 0 = S''(x<sub>n</sub>)
2. Clamped Spline: 起始點與終點的一階微分為 0，也就是 S'(x<sub>0</sub>) = 0 = S'(x<sub>n</sub>)
3. Not-A-Knot Spline: 再加入三階微分連續條件

有這些條件在連接點上會有比較平滑。假設有 n+1 個點 (x<sub>0</sub>, y<sub>0</sub>), (x<sub>1</sub>, y<sub>1</sub>), ..., (x<sub>n</sub>, y<sub>n</sub>)，就可以分段寫成
|   |  |
| --- | --- |
| S<sub>0</sub> | x<sub>0</sub> ≤ x ≤ x<sub>1</sub> |
| S<sub>1</sub> | x<sub>1</sub> ≤ x ≤ x<sub>2</sub> |
| . | . |
| S<sub>m</sub> | x<sub>n-1</sub> ≤ x ≤ x<sub>n</sub> |

S<sub>i</sub>(x) = a<sub>i</sub>(x - x<sub>i</sub>)<sup>3</sup> + b<sub>i</sub>(x - x<sub>i</sub>)<sup>2</sup> + c<sub>i</sub>(x - x<sub>i</sub>) + d<sub>i</sub>\
S'<sub>i</sub>(x) = 3a<sub>i</sub>(x - x<sub>i</sub>)<sup>2</sup> + 2b<sub>i</sub>(x - x<sub>i</sub>) + c<sub>i</sub>\
S''<sub>i</sub>(x) = 6a<sub>i</sub>(x - x<sub>i</sub>) + 2b<sub>i</sub>\
可解得
x<sub>i+1</sub> - x<sub>i</sub> = h<sub>i</sub>\
d<sub>i+1</sub> = a<sub>i</sub>h<sub>i</sub><sup>3</sup> + b<sub>i</sub>h<sub>i</sub><sup>2</sup> + c<sub>i</sub>h<sub>i</sub> + d<sub>i</sub>\
c<sub>i+1</sub> = 3a<sub>i</sub>h<sub>i</sub><sup>2</sup> + 2b<sub>i</sub>h<sub>i</sub> + c<sub>i</sub>\
b<sub>i+1</sub> = 3a<sub>i</sub>h<sub>i</sub><sup>2</sup> + 2b<sub>i</sub>\
整理一下可得 **Hb = y**\
![image](https://github.com/JrPhy/numerical/blob/master/interpolate/pic/spline.jpg)\
在此取 b<sub>0</sub> = b<sub>n</sub> = 0，為 Natural Cubic Spline，最後就可以得到\
d<sub>i</sub> = y<sub>i</sub>, $a_i = \dfrac{b_i+1-b_i}{3h_i}$, $c_i = \dfrac{y_{i+1}-y_i}{h_i} + \dfrac{(2b_{i+1}-b_i)h_i}{3}$
