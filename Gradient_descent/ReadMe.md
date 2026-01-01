梯度下降 (Gradient descent) 法在在 AI 的領域中是很常使用的算法，核心概念就是直接解他的差分方程並得到最小值，當然也可以用 QR 分解來求得，且能夠得到較精確的最小值，但是就需要花較多的時間，梯度下降則是捨去精度來換時間。其中又有共軛(conjugate)梯度法、隨機(stochastic)梯度法與調步(Adaptive)梯度法。接著從最基本的再逐一介紹。

## 1. 數學理論
在最佳化問題中就是利用微分去找極值，在此我們要找的是極(最)小值，在數學上的條件為 $\nabla f(x) = 0$ 且 $\nabla^2 f(x) > 0$。而二階微分在數值求解通常會算很久，所以多數只用一階微分來判斷，所以有時候並不知道是否存在一個非邊界點的極(最)小值。例如 $x^3$ 就沒有除了邊界以外的極值， $x^2 - y^2$ 則是有鞍點(saddle point)。在此我們就介紹一些數值方法來找極(最)小值。

## 2. 梯度下降法
對於一個有 Global/Local minimum 的函數而言，我們可以由一階微分來做尋找，並直接帶入原函數就可以比較出結果。例如\
f(x) = 2x<sup>2</sup> + 4x + 3, f'(x) = 4x + 4 --> f<sub>min</sub>(x*) = (-1, 1)\
而電腦無法算微分，所以轉為插分方程可得\
$f'(x) = \dfrac{df(x)}{dx} \sim \dfrac{ \Delta f(x)}{ \Delta x} = \dfrac{df(x_2) - df(x_1)}{x_2 - x_1}$\
所以就直接將 x 帶入去找到 x*\
$x_{n+1} = x_n - \lambda f'(x_n)$\
其中 $\lambda$ 就是每一步要跨多大步，在此稱為學習率，太大步有可能走不到最小值，但太小步又會跑太久，所以就有以上最後提到的方法。而實際問題是很多維的，所以只要分個別維度去做即可。

## 3. 梯度下降求解回歸
在求線性回歸時我們會利用一些矩陣分解的技巧求解，但是複雜度還是很高，其理論與算法在[這篇](https://github.com/JrPhy/numerical/tree/master/least-square)，所以就可以用梯度下降來求解，雖然解不如矩陣分解精確，但是效能可以提升很多。要求解 E 的最小值

$$\ E = \sum_{i=1}^{n} (y_{i} - (bx_{i}+a))^{2} $$

可以分別對 b 和 a 做偏微分得到極值

$$\ \frac{\partial E}{\partial b} = \frac{1}{n} \sum_{i=1}^{n} -2x_{i}(y_{i} - bx_{i} - a), \frac{\partial E}{\partial a} = \frac{1}{n} \sum_{i=1}^{n} -2(y_{i} - bx_{i} - a) $$

就可以套用梯度下降的算法

$$\ b_{i+1} = b_{i} - \frac{\lambda}{n} \sum_{i=1}^{n} -2x_{i}(y_{i} - bx_{i} - a), a_{i+1} = a_{i} - \frac{\lambda}{n} \sum_{i=1}^{n} -2(y_{i} - bx_{i} - a) $$

對於多項是回歸僅有誤差項不同而已

$$\ E = \sum_{i=1}^{n} (y_{i} - (\sum_{j=0}^{n}a_{j}x^{j}))^{2}, \frac{\partial E}{\partial a_{j}} = \frac{\lambda}{n} \sum_{i=1}^{n} (\sum_{j=1}^{n} -2ja_{j}x^{j-1})(y_{i} - (\sum_{j=0}^{n}a_{j}x^{j}))$$

$$\ a_{j, k+1} = a_{j, k} - \frac{\lambda}{n} \sum_{i=1}^{n} (\sum_{j=1}^{n} -2ja_{j, k}x^{j-1})(y_{i} - (\sum_{j=0}^{n}a_{j, k}x^{j}))$$

## 4.自適應梯度下降 Adaptive gradient descent
在隨機梯度下降中，學習率是固定的，如果太大就不會收斂，太小又跑太慢，所以此算法在每一步都會去調整學習率。

$$\ {\lambda}_ {k+1} = {\lambda}_ {k} - \frac{\eta \nabla f(x)}{\sqrt{\sum_{i=1}^{n} \frac{(\partial f(x_{i})}{\partial x_{i}})^{2}}} $$

所以對於一開始梯度很大的學習率也很大，而接近極值就會變得很小，實務上也會在分母加一項為小值避免為 0。

## 5. 
