最小平方法在做回歸時是一個很常見的作法，在 n 維空間中得到 m 個資料點去看趨勢，也就是\
y<sub>1</sub>(x<sub>11</sub>, x<sub>12</sub>, ..., x<sub>1n</sub>)\
y<sub>2</sub>(x<sub>21</sub>, x<sub>22</sub>, ..., x<sub>2n</sub>)\
.\
.\
.\
y<sub>m</sub>(x<sub>m1</sub>, x<sub>m2</sub>, ..., x<sub>mn</sub>)\
其中要求 n < m，然後找一條曲線 y 使得 

error = E = sum(yi - y)<sup>2</sup>, i=1~n

為最小值。yi 為量測到的點，y 為回歸的方程式。

## 1. 數學理論
我們從最簡單的線性回歸下手，假設有 n 個量測點 (x<sub>1</sub>, y<sub>1</sub>), (x<sub>2</sub>, y<sub>2</sub>), ..., (x<sub>n</sub>, y<sub>n</sub>)，那麼寫成 n 條聯立方程
y<sub>1</sub> = bx<sub>1</sub> + a\
y<sub>2</sub> = bx<sub>2</sub> + a\
.\
.\
.\
y<sub>n</sub> = bx<sub>n</sub> + a\
接著再寫成矩陣表示 **Y = Ax**
Y<sup>T</sup> = [y<sub>1</sub> y<sub>2</sub> ... y<sub>2</sub>]\
A<sup>T</sup> = [[x<sub>1</sub> 1] [x<sub>2</sub> 1] ... [x<sub>n</sub> 1]]\
X<sup>T</sup> = [b a]\
其中 Y 原本為 n row 1 column 的向量，寫作 Y ∈ M<sub>n×1</sub>
(F )，為方便書寫轉置後為 1 row n column。注意到 (x<sub>i</sub>, y<sub>i</sub>) 是已知，(b, a) 才是未知，所以在這邊的 X 為 [b a]。因為有兩個未知數，所以最少要有兩個不重複的點才能有為一解。
#### Lemma 1
令 A ∈ M<sub>m×n</sub>(F), x ∈ F<sup>n</sup>, y ∈ F<sup>m</sup>，且 m ≧ n，則<Ax, y><sub>m</sub> = <x, ATy><sub>n</sub>, < , >: 為內積符號
#### Lemma 2
令 A ∈ M<sub>m×n</sub>(F), rank(A) = rank(A<sup>T</sup>A)
#### Corollary
令 A ∈ M<sub>m×n</sub>(F), rank(A) = n，則 A<sup>T</sup>A 為可逆。

其中 rank(A) = n 表示矩陣 M 中有 n 個線性獨立的向量。之後證明會用到以上引理及推論，其證明可閱讀線性代數的相關書籍。

## 2. 數學證明
最小平方近似定理陳述為\
令 A ∈ M<sub>m×n</sub>(F), m ≧ n, y ∈ F<sup>m</sup>，則存在一個 x<sub>0</sub> ∈ F<sup>n</sup> 使得\
(A<sup>T</sup>A)x<sub>0</sub> = A<sup>T</sup>y 且 || Ax<sub>0</sub> - y || ≤ || Ax - y ||, x ∈ F<sup>n</sup>。如果 Ax = y 有為一解，那麼就**唯一存在**一個最小平方近似的解 s
此外若 A 為 full rank，則 x<sub>0</sub> = (A<sup>T</sup>A)<sup>-1</sup>A<sup>T</sup>y
#### 證明(代數法)
< Ax, s > = < x, AA<sup>T</sup>> = < x, AA<sup>T</sup>(Ax<sub>0</sub> - y)> = 0 --> 對 x ≠ 0, (A<sup>T</sup>A)x<sub>0</sub> = A<sup>T</sup>y --> x<sub>0</sub> = (A<sup>T</sup>A)<sup>-1</sup>A<sup>T</sup>y
#### 證明(幾何法)
由向量可知 s = Ax<sub>0</sub> - y，此時可找到一條 s 垂直於 Ax<sub>0</sub>，即存在最小值 ||s||
![image](https://github.com/JrPhy/numerical/blob/master/least-square/pic/least_square.jpg)
#### 證明為最小值
將 y<sub>i</sub> = bx<sub>i</sub> + a 帶入誤差定義中\
E = sum(y<sub>i</sub> - y)<sup>2</sup> (i = 1, 2, ..., n) = sum(bx<sub>i</sub> + a - y)<sup>2</sup> (i = 1, 2, ..., n)\
為一個開口向上的拋物線，所以可知一階微分為 0 的點為最小值，所以分別對 b, a 微分得下方關係式(跟著箭頭方向)\
![image](https://github.com/JrPhy/numerical/blob/master/least-square/pic/solve_ab.jpg)\
對一個 m 階 n 維的多項式而言也可以有類似的作法，例如\
deg(f) = 3, f(x, y) = a<sub>0</sub> + a<sub>1</sub>x + a<sub>2</sub>y + a<sub>3</sub>x<sup>2</sup> + a<sub>4</sub>xy + a<sub>5</sub>y<sup>2</sup> + ... a<sub>9</sub>y<sup>3</sup>\
就去把 a<sub>0</sub> ~ a<sub>9</sub> 係數都解出來即可。

## 3. 數值方法
求解：x<sub>0</sub> = A<sup>T</sup>y, A ∈ M<sub>m×n</sub>(F)
x<sub>0</sub> = (A<sup>T</sup>A)<sup>-1</sup>A<sup>T</sup>y\
若要得到最小平方解，就需要用到上述式子，所以需要寫成矩陣的形式，這樣也可以直接給電腦算。給電腦算的例子通常矩陣都很大，而矩陣乘法最快也就是 O(n<sup>2.7~</sup>) 左右，當然也可以直接求解，以下介紹 LU, QR 與 SV 三種分解的殊值方法

#### 1. LU 分解
LU 分解式將方陣利用高斯消去法，將一**方陣**分解為一個上三角矩陣 U 與一個下三角矩陣 L 的乘積
1. 得到 B = AA<sup>T</sup>，這步求解就會很久
2. LU = B
3. x<sub>0</sub> = A<sup>-1</sup>y --> L(Ux) = L(c) = b = A<sup>T</sup>y
4. 解聯立得到解\

LU 分解除了計算量大與一定要方陣外，還有一個問題就是有病態條件的可能，例如\
400a-201b = 200  -->  a = -100\
-800a+401b = -200  -->  b = -200\
但若為浮點數的計算，則誤差有可能會累加成下方式子\
401a-201b = 200  -->  a = 40000\
-800a+401b = -200  -->  b = 79800\
此為矩陣的**病態條件 (ill-conditioned)**，所以有人想出了 QR 分解來避免這問題。

#### 2. QR 分解
https://www.youtube.com/watch?v=Sco6zCBtP3I

Here is the demo video

