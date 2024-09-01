費部納西數 F<sub>n</sub> 是由費式數列定義而來 F<sub>n+2</sub> = F<sub>n+1</sub> + F<sub>n</sub>，F<sub>0</sub> = 0、F<sub>1</sub> = 1、F<sub>2</sub> = 1。應用在相當多的領域，如電腦科學與數學等。也可將此形式用矩陣表式

$$\begin{equation}
    \begin{matrix}
        F_{k+2} \\
        F_{k+1}
    \end{matrix}
    =
    \begin{bmatrix}
        1&1 \\
        1&0 \\
    \end{bmatrix}
    \begin{bmatrix}
        F_{k+1} \\
        F_{k}
    \end{bmatrix}
    \rightarrow 
    \begin{bmatrix}
        F_{k+1} = F_{k}
    \end{bmatrix}
\end{equation}$$

特徵值與對應的特徵向量為 $$\ \lambda_{1, 2} = \frac{1\pm\sqrt{5}}{2}, \lambda_{1, 2}^T = (\frac{1\pm\sqrt{5}}{2}, 1) $$

## 一般形式
我們可以將 A 對角化 A = PDP<sup>-1</sup> --> F<sub>1</sub> = AF<sub>0</sub> --> F<sub>n+1</sub> = AF<sub>n</sub> = PD<sup>n</sup>P<sup>-1</sup>F<sub>0</sub>

$$\begin{equation}
    P = 
    \begin{bmatrix}
        \frac{1+\sqrt{5}}{2}&1 \\
        \frac{1-\sqrt{5}}{2}&1 \\
    \end{bmatrix}
    , D = 
    \begin{bmatrix}
        \frac{1+\sqrt{5}}{2}&1 \\
        0&\frac{1-\sqrt{5}}{2}&1 \\
    \end{bmatrix}
    P^{-1} = \frac{1}{\sqrt{5}}
    \begin{bmatrix}
        1&-\frac{1+\sqrt{5}}{2} \\
        -1&\frac{1+\sqrt{5}}{2} \\
    \end{bmatrix}
    F_{0} = 
    \begin{bmatrix}
        1&\\
        0&\\
    \end{bmatrix}
\end{equation}$$

$$\begin{equation}
    \begin{bmatrix}
        F_{n+1} \\
        F_{n} \\
    \end{bmatrix}
    = 
    \begin{bmatrix}
        \frac{1+\sqrt{5}}{2}&\frac{1-\sqrt{5}}{2} \\
        1&1 \\
    \end{bmatrix}
    \begin{bmatrix}
        (\frac{1+\sqrt{5}}{2})^n&0 \\
        0&(\frac{1-\sqrt{5}}{2})^n \\
    \end{bmatrix}
    \begin{bmatrix}
        1&-\frac{1+\sqrt{5}}{2} \\
        -1&\frac{1+\sqrt{5}}{2} \\
    \end{bmatrix}
    \begin{bmatrix}
        1 \\
        0 \\
    \end{bmatrix}
\end{equation}$$

$$\ F_{n} = frac{1}{\sqrt{5}}(\frac{1+\sqrt{5}}{2})^n - frac{1}{\sqrt{5}}(\frac{1-\sqrt{5}}{2})^n $$

## 程式碼
計算費式數列對於程式新手是一個很好學習遞迴的範例
```cpp
int F(int n) {
    if(n <= 0) return n;
    else return F(n-1)+F(n-2);
}
```
此算法為 top-down 的遞迴，例如當 n=5，我們要先算 F(4) 與 F(3)，F(3) 需要算 F(2) 與 F(1) 。其複雜度即為 $$\ O((\frac{1+\sqrt{5}}{2})^n) $$
![img](https://miro.medium.com/v2/resize:fit:1100/format:webp/1*bGJzheJAhePGVSkTCUw7IA.jpeg)\
[來源](https://medium.com/appworks-school/%E5%88%9D%E5%AD%B8%E8%80%85%E5%AD%B8%E6%BC%94%E7%AE%97%E6%B3%95-%E5%BE%9E%E8%B2%BB%E6%B0%8F%E6%95%B8%E5%88%97%E8%AA%8D%E8%AD%98%E4%BD%95%E8%AC%82%E9%81%9E%E8%BF%B4-dea15d2808a3)\
改用迭代寫法就可以降低複雜度
```cpp
int F(int n) {
    int f0 = 1, f1 = 1, f2 = 0;
    for(int i = 1; i < n; i++) {
        f2 = f1 + f0;
        f0 = f1;
        f1 = f2;
    }
    return f2;
}
```
複雜度就降到 O(n)。

When you use int to store the Fibonacci number, it’s bigger than 2^32 -1 as n = 48,
so it must use big number algorithm.
GMP is one of the solution for this issue, 
you can google it and build the environment to get all digit when n is bigger than 48.
