在解實際問題時常常會遇到許多的特殊函數，例如 Bessel's funtcion, Legendre funtion，這篇就來整理一下這些特殊函數的推導及數值實現。

## 1. 電磁場的求解
在電磁學的問題都是從 Maxwell's eqs 出發，跟去實際條件去選擇坐標系，例如光纖會選圓柱座標，天線會選球座標，得到的電磁場就會有不同的解。假設電磁場在空間中傳播的形式以球座標，其形式為

$$\vec{E} = E_0(r, \theta, \phi)e^{ikr} \hat{r},  \vec{B} = B_0(r, \theta, \phi)e^{ikr} \hat{r}$$

從 Maxwell's eqs 可以得到 Helmholtz eq.

$$\nabla^2 \vec{E} = \frac{\partial^2 \vec{E}}{\partial t^2} \rightarrow (\nabla^2+k^2)\vec{E} = 0, \nabla^2 \vec{B} = \frac{\partial^2 \vec{B}}{\partial t^2} \rightarrow (\nabla^2+k^2)\vec{B} = 0$$

其中為 Laplacian 算符。將其寫成球座標形式可得

$$\nabla^2 = \frac{\partial^2 }{\partial x^2} + \frac{\partial^2 }{\partial y^2} + \frac{\partial^2 }{\partial z^2} = \frac{1}{r^2}\frac{\partial }{\partial r}(r^2\frac{\partial }{\partial r}) + \frac{1}{r^2sin\theta}\frac{\partial }{\partial \theta}(r^2\frac{\partial }{\partial \theta}) + \frac{1}{r^2sin^2\theta}\frac{\partial^2 }{\partial \phi^2}$$

接著就可以開始解微分方程，假設解可以變數分離，及 E(r,θ,φ) = R(r)Θ(θ)Φ(φ)，那麼可以先解出 Φ(φ) 方向的解為

$$\frac{1}{\Phi}\frac{\partial^2 \Phi}{\partial \phi^2} = -m^2 \rightarrow \Phi(\phi) = e^{-im\phi}$$

所以就可以將 Helmholtz eq. 寫成

$$[\frac{1}{R}\frac{d }{d r}(r^2\frac{d R}{d r}) + k^2r^2]+[\frac{1}{\Theta}\frac{d }{sin \theta d \theta}(sin \theta)\frac{d \Theta}{d \theta} - \frac{m^2}{sin^2 \theta}\ = 0$$

再來求解 Θ(θ) 方向，其形式為 [associated Legendre](https://en.wikipedia.org/wiki/Associated_Legendre_polynomials)，令 x = cosθ，y = Φ，就可以把方程式改寫為

$$(1-x^2)y'' - 2xy' +[n(n+1) - \frac{m^2}{1-x^2}] = 0$$

其中  0 ≤ θ ≤ pi, -1 ≤ y ≤ 1, , -n ≤ m ≤ n。n 為正整數，其解為 $P^m_n (cos \theta)$

m 為第幾階，表示為幾次多項式，n 為第幾個根，可展開後看其形式。並利用歸一化條件可得到

$$\tilde P^m_n (cos \theta) = \sqrt{\frac{2n+1}{2} \frac{(n-m)!}{(n+m)!}}P^m_n (cos \theta)$$
最後就把 Θ 與 Φ 的解帶入就可以去解 R 方向

$$[\frac{1}{R}\frac{d }{d r}(r^2\frac{d R}{d r}) + k^2r^2] - n(n+1)$$

得到 Spherical Hankle's function h<sub>n</sub>(r)解 $h_n (r) = j_n (r) \pm iy_n (r) $

其中 j 為 Spherical Bessel's function，y 為 Spherical Neumann's function，大寫的為普通的 Hankle/Bessel/Neumann

$$j_n(r) = \sqrt{\frac{\pi}{2r}} J_{n+1/2}(r), y_n(r) = \sqrt{\frac{\pi}{2r}} Y_{n+1/2}(r)$$

最後帶回去就可以得到電場的形式為

$$E(r, \theta, \phi) = h_n(r) P^m_n (cos \theta) e^{\pm im\phi} = h_n(r) Y^m_n (cos \theta) $$

其中 Θ(θ)Φ(φ) 稱為 [Spherical Harmonic function](https://en.wikipedia.org/wiki/Spherical_harmonics)，也就是在角度方向上的解，其歸一化形式為

$$\tilde Y^m_n (cos \theta) = \sqrt{\frac{2n+1}{4\pi} \frac{(n-|m|)!}{(n+|m|)!}}Y^m_n (cos \theta)$$

## 2. 特殊函數的數值解
上述所用到的特殊函數有許多的關係式，有些關係是在數值上求解比較穩定，所以需要根據其數值穩定性選擇

#### 1. Bessel and Neumann
參考[文獻資料](https://s3.amazonaws.com/nrbook.com/AandS-a4-v1-2.pdf)，在 9.1.27 有四個方程式，可以利用費氏數列 divide and conquer 法

$$f_{n+1} = \frac{2n}{z}f_{n}(z) - f_{n}(z)$$

#### 2. Associated Legendre
其中有兩個指標 m, n，一樣可以從最簡單的 m = 0, n = 0 去建構，先看 m = 1 = n 的形式

$$P^m_n (x) = \sqrt{(1-x^2)^m}\frac{d^m }{d x^m}P_n (x), P_n (x) = \frac{1}{2^n n!}\frac{d^n }{d x^n}(x^2 - 1)^n$$

$$P^m_m (x) = \sqrt{\frac{2n+1 }{2(2m)!}}(2m-1)!!\sqrt{(1-x^2)^m}$$

然後計算 m ≤ n 的形式

$$(n-m)P^m_n (x) = x(2n-1)P^m_{n-1} (x) + x(n+m-1)P^m_{n-2} (x)$$

整理一下可得

$$P^-m_n (x) = \frac{x(2n-1)}{(n-m)}P^m_{n-1} (x) + \frac{x(n+m-1)}{(n-m)}P^m_{n-2} (x)$$

如此一來就得到 0 ≤ m 的形式。當 m 為負數時也可由下方關係得到

$$P^m_n (x) = (-1)^m\frac{(n-m)!}{(n+m)!} P^m_{n-1} (x)$$

