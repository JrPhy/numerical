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

## 範例
