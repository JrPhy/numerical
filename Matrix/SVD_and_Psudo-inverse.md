SVD 不論是在數學系或是其他工程學系，都是在線性代數的最後一章節，因為 SVD 包含線性代數的關鍵概念。不只是在教學，在應用上也很常使用，例如電腦視覺、統計學等。

## 定義
令 A ∈ M<sub>m×n</sub>(C)，唯一常數 σ<sub>1</sub>,  σ<sub>2</sub>, ... σ<sub>r</sub> 稱為 A 的奇異值。

## 奇異值分解定理
令 A ∈ M<sub>m×n</sub>(C)，且 rank(A) = r，有奇異值 σ<sub>1</sub> ≥ σ<sub>2</sub> ≥ ... σ<sub>r</sub>，則 A 可被分解為 

A = UΣV*

被稱為 A 的奇異值分解。U ∈ M<sub>m</sub>(C) 與 V ∈ M<sub>m</sub>(C) 為么正矩陣，Σ ∈ M<sub>m×n</sub>(C) 且 Σ<sub>ij</sub> = σ<sub>i</sub>δ<sub>ij</sub>

## 證明
∵ U, V 為么正矩陣，∴ AV = UΣV*V = UΣ。所以存在兩個正交基底 β = {v<sub>1</sub>, v<sub>2</sub>, ..., v<sub>n</sub>}, γ = {u<sub>1</sub>, u<sub>2</sub>, ..., u<sub>n</sub>}，分別為在有限維的內積空間 V, U 的基底，且有個 rank = r 的線性變換 T: F<sup>n</sup> -> F<sup>m</sup>，則 Σ 可寫成

| 1 ≤ i ≤ r | i > r |
| --- | --- |
| Σ<sub>ij</sub> = σ<sub>i</sub>δ<sub>ij</sub> | Σ<sub>ij</sub> = 0 |
| T(v<sub>i</sub>) = σ<sub>i</sub>u<sub>i</sub> | T(v<sub>i</sub>) = 0 |

所以 $$\ <u_{i}, u_{j}> = <\frac{T(v_{i})}{\sigma_{i}}, \frac{T(v_{j})}{\sigma_{j}}> = \frac{1}{\sigma_{i}\sigma_{j}}<T*T(v_{i}), v_{j}> = \frac{\sigma_{i}^2}{\sigma_{i}\sigma_{j}}<v_{i}, v_{j}> = \delta_{ij} $$

所以 σ<sub>ij</sub><sup>2</sup> 為 T*T 的特徵值，v<sub>i</sub> 為對應的特徵向量。

## 計算流程
1. 計算 A*A
2. 找 A*A 的正規特徵向量組成 V，以及其特徵值開根號組成 Σ
3. 計算 AV/σ<sub>i</sub> 得到 U

注意到不論是 AA* 或是 A* A 算出來的結果都一樣。由 SVD 定理可知 A = UΣV* \
A* = (UΣV*)* = VΣ*U * = VΣU* --> A*U = VΣ\
從線性轉換的觀點來看

$$\ <v_{i}, v_{j}> = <\frac{T*(u_{i})}{\sigma_{i}}, \frac{T*(u_{j})}{\sigma_{j}}> = \frac{1}{\sigma_{i}\sigma_{j}}<T*T(u_{i}), u_{j}> = \frac{\sigma_{i}^2}{\sigma_{i}\sigma_{j}}<u_{i}, u_{j}> = \delta_{ij} $$

## 範例 1
$$\begin{equation}
    \begin{matrix}
        x_{1} + x_{2} - x_{3} &=& 1\\
        x_{1} + x_{2} - x_{3} &=& 2
    \end{matrix}
    \rightarrow
    \begin{bmatrix}
        1&1&-1 \\
        1&1&-1 \\
    \end{bmatrix}
    \begin{bmatrix}
        x_{1} \\
        x_{2} \\
        x_{3} \\
    \end{bmatrix}
    =
    \begin{bmatrix}
        1 \\
        2 \\
    \end{bmatrix}
\end{equation}$$

$$\begin{equation}
    \begin{matrix}
        AA^T = 
    \end{matrix}
    \begin{bmatrix}
        1&1&-1 \\
        1&1&-1 \\
    \end{bmatrix}
    \begin{bmatrix}
        1&1 \\
        1&1 \\
        -1&-1 \\
    \end{bmatrix}
    =
    \begin{bmatrix}
        3&3 \\
        3&3 \\
    \end{bmatrix}
    \rightarrow
    \begin{vmatrix}
        3-\lambda&3 \\
        3&3-\lambda
    \end{vmatrix}
    = \lambda(6-\lambda) = 0
\end{equation}$$

$$\begin{equation}
    \begin{matrix}
        A^TA = 
    \end{matrix}
    \begin{bmatrix}
        1&1 \\
        1&1 \\
        -1&-1 \\
    \end{bmatrix}
    \begin{bmatrix}
        1&1&-1 \\
        1&1&-1 \\
    \end{bmatrix}
    =
    \begin{bmatrix}
        2&2&-2 \\
        2&2&-2 \\
        -2&-2&2 \\
    \end{bmatrix}
    \rightarrow
    \begin{vmatrix}
        2-\lambda&2 \\
        2&2-\lambda \\
        -2&-&2-\lambda \\
    \end{vmatrix}
    = \lambda^2(6-\lambda) = 0
\end{equation}$$

可知兩者的特徵值為 0, 6。

## 範例 2
∵ A = UΣV<sup>T</sup> --> A<sup>T</sup> = (UΣV<sup>T</sup>)<sup>T</sup> = VΣ<sup>T</sup>U<sup>T</sup>\
AA<sup>T</sup> = UΣV<sup>T</sup>VΣ<sup>T</sup>U<sup>T</sup> = UΣ<sup>2</sup>V<sup>T</sup>\
A<sup>T</sup>A = VΣ<sup>T</sup>U<sup>T</sup>UΣV<sup>T</sup> = VΣ<sup>2</sup>U<sup>T</sup>

## 範例 3
$$\begin{equation}
    \begin{matrix}
        AV = 
    \end{matrix}
    \begin{bmatrix}
        1&1&-1 \\
        1&1&-1 \\
    \end{bmatrix}
    \frac{1}{\sqrt{6}}
    \begin{bmatrix}
        \sqrt{2}&\sqrt{3}&1 \\
        \sqrt{2}&-\sqrt{3}&1 \\
        -\sqrt{2}&0&2 \\
    \end{bmatrix}
    =
    \begin{bmatrix}
        \sqrt{3}&0&0 \\
        \sqrt{3}&0&0 \\
    \end{bmatrix}
\end{equation}$$

U 為 M<sub>2</sub>(R)，所以

$$\begin{equation}
    \begin{matrix}
        u_{1} = \frac{Av_{1}}{\sigma_{1}} = \frac{1}{\sqrt{6}}
    \end{matrix}
    \begin{bmatrix}
        \sqrt{3} \\
        \sqrt{3} \\
    \end{bmatrix}
    = \frac{1}{\sqrt{2}}
    \begin{bmatrix}
        1 \\
        1 \\
    \end{bmatrix}
\end{equation}$$

$$\begin{equation}
    \begin{matrix}
        Av_{21} = \frac{1}{\sqrt{2}}, u_{2} = \frac{1}{\sqrt{2}}
    \end{matrix}
    \begin{bmatrix}
        1 \\
        -1 \\
    \end{bmatrix}
    \rightarrow U = \frac{1}{\sqrt{2}}
    \begin{bmatrix}
        1&1 \\
        1&-1 \\
    \end{bmatrix}
\end{equation}$$

$$\begin{equation}
    \begin{matrix}
        A = U\Sigma V^T = 
    \end{matrix}
    \begin{bmatrix}
        \frac{1}{\sqrt{2}}&\frac{1}{\sqrt{2}} \\
        \frac{1}{\sqrt{2}}&-\frac{1}{\sqrt{2}} \\
    \end{bmatrix}
    \begin{bmatrix}
        \sqrt{6}&0&0 \\
        0&0&0 \\
    \end{bmatrix}
    \begin{bmatrix}
        \frac{1}{\sqrt{3}}&\frac{1}{\sqrt{3}}&-\frac{1}{\sqrt{3}} \\
        \frac{1}{\sqrt{2}}&\frac{1}{\sqrt{2}}&0 \\
        \frac{1}{\sqrt{6}}&\frac{1}{\sqrt{6}}&-\frac{2}{\sqrt{6}} \\
    \end{bmatrix}
\end{equation}$$

由 Σ 內的元素可知，因為其餘部分乘起來為 0，所以只須關心不為零的元素

$$\begin{equation}
    \begin{matrix}
        A = U\Sigma V^T = 
    \end{matrix}
    \begin{bmatrix}
        \frac{1}{\sqrt{2}}&* \\
        \frac{1}{\sqrt{2}}&* \\
    \end{bmatrix}
    \begin{bmatrix}
        \sqrt{6}&0&0 \\
        0&0&0 \\
    \end{bmatrix}
    \begin{bmatrix}
        \frac{1}{\sqrt{3}}&\frac{1}{\sqrt{3}}&-\frac{1}{\sqrt{3}} \\
        *& *& * \\
        *& *& * \\
    \end{bmatrix}
\end{equation}$$

所以實際在計算時 Σ 為稀疏矩陣，就不需要存整個矩陣，就可以省下記憶體。

## 反矩陣
A 可逆 <--> A 式方陣且 det(A) ≠ 0。而可逆的定義為

若 A ∈ M<sub>m</sub>(R) 為可逆，則存在一個 B ∈ M<sub>m</sub>(R) 使得 AB = BA = I<sub>m</sub> --> AI = A(AB) = A(BA) = A，此可用來解最小平方問題。

## 偽逆矩陣
可看成一個一般化的逆矩陣。若 A ∈ M<sub>m×n</sub>(R) 且 A 為不可逆，但是存在其偽逆矩陣。在非 full-rank 的最小平方問題中就可使用此性質來求解。

#### 定義
令 A ∈ M<sub>m×n</sub>(R)，解 X 為 A 的偽逆矩陣滿足以下關係

1. AXA = A
2. XAX = X
3. (AX)* = XA
4. (XA)* = AX

此在最小平方問題的解如下：\
若 Ax = b 且 A 為 full-rank <--> x<sub>0</sub> = (A<sup>T</sup>A)<sup>-1</sup>A<sup>T</sup>b\
若 Ax = b 且 A 為 rank-deficient <--> x<sup>+</sup> = A<sup>+</sup>b\

## rank-deficient 的最小平方定理 1
A ∈ M<sub>m×n</sub>(R) 且 A = UΣV*，則 A<sub>+</sub>(A 的偽逆矩陣) = UΣ<sup>+</sup>V* ，Σ<sup>+</sup> 為 Σ
 的偽逆矩陣。Σ<sub>ij</sub> = σ<sub>i</sub>δ<sub>ij</sub>，Σ<sup>+</sup> = Σ<sub>ji</sub> = σ<sub>i</sub><sup>-1</sup>δ<sub>ij</sub>。注意到 AA<sup>+</sup> 且 A<sup>+</sup>A 不一定為 I

## rank-deficient 的最小平方定理 2
1. 若 Ax = b 且 A 為 full-rank，則存在一個解 z 且有最小的長度。[證明](https://github.com/JrPhy/numerical/tree/master/least-square)
2. 若 Ax = b 且 A 為 rank-deficient，則存在一個解 z 且最接近最小的長度。

#### 證明 2.
假設 x<sub>0</sub> 是 Ax = b 的最佳近似解，則 ||Ax - b|| ≥ ||Ax<sub>0</sub> - b||\
Ax - b = A(x-A<sup>+</sup>)b - (I - AA<sup>+</sup>)(-b)\
