在解實際問題時常常會遇到許多的特殊函數，例如 Bessel's funtcion, Legendre funtions，這篇就來整理一下這些特殊函數的推導及數值實現。

## 1. 電磁場的求解
在電磁學的問題都是從 Maxwell's eqs 出發，跟去實際條件去選擇坐標系，例如光纖會選圓柱座標，天線會選球座標，得到的電磁場就會有不同的解。假設電磁場在空間中傳播的形式以球座標，其形式為\
![image](https://github.com/JrPhy/numerical/blob/master/Special%20function/pic/EB_in_radial.jpg)\
從 Maxwell's eqs 可以得到 Helmholtz eq.\
![image](https://github.com/JrPhy/numerical/blob/master/Special%20function/pic/EB_in_Maxwell.jpg)\
其中為 Laplacian 算符。將其寫成球座標形式可得\
![image](https://github.com/JrPhy/numerical/blob/master/Special%20function/pic/Laplacian_in_spherical.jpg)\
接著就可以開始解微分方程，假設解可以變數分離，及 E(r,θ,φ) = R(r)Θ(θ)Φ(φ)，那麼可以先解出 Φ(φ) 方向的解為
![image](https://github.com/JrPhy/numerical/blob/master/Special%20function/pic/Phi_sol.jpg)\
所以就可以將 Helmholtz eq. 寫成
![image](https://github.com/JrPhy/numerical/blob/master/Special%20function/pic/after_solve_phi.jpg)\
再來求解 Θ(θ) 方向，其形式為 [associated Legendre](https://en.wikipedia.org/wiki/Associated_Legendre_polynomials)，令 x = cosθ，y = Φ，就可以把方程式改寫為\
(1-x<sup>2</sup>)y'' - 2xy' + [n(n+1) - m<sup>2</sup>/(1-x<sup>2</sup>)]\
其中  0 ≤ θ ≤ pi, -1 ≤ y ≤ 1, , -n ≤ m ≤ n。n 為正整數，其解為\
P<sup>m</sup><sub>n</sub> (cosθ)\
m 為第幾階，表示為幾次多項式，n 為第幾個根，可展開後看其形式。並利用歸一化條件可得到\
![image](https://github.com/JrPhy/numerical/blob/master/Special%20function/pic/associated_P.jpg)\
最後就把 Θ 與 Φ 的解帶入就可以去解 R 方向\
![image](https://github.com/JrPhy/numerical/blob/master/Special%20function/pic/R_sol.jpg)\
得到 Spherical Hankle's function h<sub>n</sub>(r)解\
h<sub>n</sub>(r) = j<sub>n</sub>(r) +/- iy<sub>n</sub>(r)\
其中 j 為 Spherical Bessel's function，y 為 Spherical Neumann's function，大寫的為普通的 Hankle/Bessel/Neumann
![image](https://github.com/JrPhy/numerical/blob/master/Special%20function/pic/Bessel_sol.jpg)\
最後帶回去就可以得到電場的形式為
E(r,θ,φ) = h<sub>n</sub>(r) *P*<sup>m</sup><sub>n</sub> (cosθ) e<sup>+/- imφ</sup> = *Y*<sup>m</sup><sub>n</sub> (cosθ)\
其中 Θ(θ)Φ(φ) 稱為 [Spherical Harmonic function](https://en.wikipedia.org/wiki/Spherical_harmonics)，也就是在角度方向上的解，其歸一化形式為\
![image](https://github.com/JrPhy/numerical/blob/master/Special%20function/pic/sperical_harmonic.jpg)

## 2. 特殊函數的數值解
上述所用到的特殊函數有許多的關係式，有些關係是在數值上求解比較穩定，所以需要根據其數值穩定性選擇

#### 1. Bessel and Neumann
參考[文獻資料](https://s3.amazonaws.com/nrbook.com/AandS-a4-v1-2.pdf)，在 9.1.27 有四個方程式，可以利用費氏數列 divide and conquer 法\
*f*<sub>n+1</sub> (z) = (2n/z)*f*<sub>n</sub> (z) - *f*<sub>n</sub> (z)\

#### 2. Associated Legendre
其中有兩個指標 m, n，一樣可以從最簡單的 m = 0, n = 0 去建構，先看 m = 1 = n 的形式\

然後計算 m ≤ n 的形式
(n-m)*P*<sup>m</sup><sub>n</sub> (x) = x(2n-1)*P*<sup>m</sup><sub>n-1</sub> (x) + (n+m-1)*P*<sup>m</sup><sub>n-2</sub> (x)\
整理一下可得
*P*<sup>m</sup><sub>n</sub> (x) = x((2n-1)/(n-m))*P*<sup>m</sup><sub>n-1</sub> (x) - ((n+m-1)/(n-m))*P*<sup>m</sup><sub>n-2</sub> (x)\
如此一來就得到 0 ≤ m 的形式。當 m 為負數時也可由下方關係得到
*P*<sup>-m</sup><sub>n</sub> (x) = (-1)<sup>m</sup>((n-m)!/(n+m)!)*P*<sup>m</sup><sub>n-1</sub> (x)
