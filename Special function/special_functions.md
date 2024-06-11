在解實際問題時常常會遇到許多的特殊函數，例如 Bessel's funtcion, Legendre funtions，這篇就來整理一下這些特殊函數的推導及數值實現。

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
