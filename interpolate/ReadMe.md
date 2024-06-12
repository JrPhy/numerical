內插是一種在資料範圍內建立新資料的方法，有內插跟外插，不過外插不一定能跟原始資料類似。有以下四種內插方法
1. 線性內插
2. Lagrange 內插
3. Spline 內插
4. 最小平方法內插

## 1. 線性內插
這是最簡單的內插方式，從最簡單的一維開始，假設有兩個點 a, b，距離為 d = |a - b|, | | 為絕對值，中間有一點 c，|b - c| = t, |a - b| = d - t\
```
a-------------c---------------------b
|-------------|---------------------|
----- d - t ------------ t ----------
```
由距離比例可知 t/(d-t) = (b-c)/(c-a) --> c = (d-t)b + ta。若 d = 1, t = 0.5，則 c = 0.5a + 0.5b\
而在程式中只存資料點，做內插之後資料點會變多，所以要另外新開一個陣列。假設原本有 m 的資料點，要在每兩個點中間插一個值，也就是用中點內插，新陣列長度為\
```
(m-1)*(insert+1)+1
```
雖然線性內插很方便，但是誤差也是很大，所以有上面提到的另外三種方法\
![image](https://github.com/JrPhy/numerical/blob/master/interpolate/pic/interpolate.jpg)\
而二維內插就是直接去推廣，個別維度去做內插即可。

## 2. Lagrange 內插
如果有 m+1 個資料點，那麼最高可以得到 m 階的多項式\
f(x) = sum(a<sub>i</sub>x<sup>i</sup>), i=0, 1, 2, ..., m\
只需把 a<sub>i</sub> 全部解出來即可，可以寫成矩陣表示，此矩陣稱為 Vandermonde matrix\
|   |  |  |  |  |  |  |  |  |
| --- | --- | --- | --- | --- | --- | --- | --- | --- |
| 1 | x<sub>0</sub> | x<sub>0</sub><sup>2</sup> | ... | x<sub>0</sub><sup>m</sup> | | a<sub>0</sub> | | y<sub>0</sub> |
| 1 | x<sub>1</sub> | x<sub>1</sub><sup>2</sup> | ... | x<sub>1</sub><sup>m</sup> | | a<sub>1</sub> | | y<sub>1</sub> |
| . | . | . | . | . | | . | | . | | . |
| 1 | x<sub>m</sub> | x<sub>m</sub><sup>2</sup> | ... | x<sub>2</sub><sup>m</sup> | | a<sub>m</sub> | | y<sub>m</sub> |

而 Vandermonde matrix 是一個[病態條件](https://github.com/JrPhy/numerical/tree/master/least-square#1-lu-%E5%88%86%E8%A7%A3)的矩陣，所以通常不會直接去解，而是去展開解。假設有三個點要去找出二次式，那麼
P<sub>2</sub>(x) = sum(a<sub>i</sub>x<sup>i</sup>), i=0, 1, 2\
P<sub>2</sub>(x<sup>0</sup>) = f(x<sub>0</sub>)\
P<sub>2</sub>(x<sup>1</sup>) = f(x<sub>1</sub>)\
P<sub>2</sub>(x<sup>2</sup>) = f(x<sub>2</sub>)\
![image](https://github.com/JrPhy/numerical/blob/master/interpolate/pic/Lagrange_inter.jpg)\
將每個三階行列式做完基本列運算在做降階可得\
![image](https://github.com/JrPhy/numerical/blob/master/interpolate/pic/Lagrange_inter_sol.jpg)\
即可得到之前熟悉的形式。用連加與連乘符號即可化簡為\
![image](https://github.com/JrPhy/numerical/blob/master/interpolate/pic/Lagrange_poly.jpg)\
