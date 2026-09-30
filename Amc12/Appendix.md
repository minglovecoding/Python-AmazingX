### 韦达定理（AMC 12）

### 1. 一元二次方程

对于：

$$
Ax^2+Bx+C=0,\qquad A\ne0
$$

设两个根为 x_1,x_2，则：

$$
\boxed{x_1+x_2=-\frac BA}
$$

$$
\boxed{x_1x_2=\frac CA}
$$

### 示例

对于：

$$
2x^2-6x+4=0
$$

有：

$$
x_1+x_2=-\frac{-6}{2}=3
$$

$$
x_1x_2=\frac42=2
$$

实际上两个根是 1,2，确实满足：

$$
1+2=3,\qquad1\cdot2=2
$$

### 2. 二次韦达定理的推导

如果 x_1,x_2、 是多项式的两个根，根据因式定理：

$$
Ax^2+Bx+C=A(x-x_1)(x-x_2)
$$

展开右边：

$$
\begin{aligned}
A(x-x_1)(x-x_2)
&=A\left[x^2-(x_1+x_2)x+x_1x_2\right]\\
&=Ax^2-A(x_1+x_2)x+Ax_1x_2
\end{aligned}
$$

与原式 Ax^2+Bx+C 比较系数：

$$
-A(x_1+x_2)=B
$$

$$
Ax_1x_2=C
$$

因此：

$$
\boxed{x_1+x_2=-\frac BA},\qquad
\boxed{x_1x_2=\frac CA}
$$

### 3. 常见变形

知道两根的和与积后，可以计算很多对称式。

### 两根平方和

$$
x_1^2+x_2^2=(x_1+x_2)^2-2x_1x_2
$$

所以：

$$
\boxed{x_1^2+x_2^2=\frac{B^2-2AC}{A^2}}
$$

### 两根倒数和

$$
\frac1{x_1}+\frac1{x_2}
=\frac{x_1+x_2}{x_1x_2}
$$

所以：

$$
\boxed{\frac1{x_1}+\frac1{x_2}=-\frac BC}
$$

前提是 C != 0。

### 两根之差的平方

$$
(x_1-x_2)^2=(x_1+x_2)^2-4x_1x_2
$$

所以：

$$
\boxed{(x_1-x_2)^2=\frac{B^2-4AC}{A^2}}
$$

---

### 二. 一元三次方程

对于：

$$
Ax^3+Bx^2+Cx+D=0
$$

设三个根为 x_1,x_2,x_3，则：

$$
\boxed{x_1+x_2+x_3=-\frac BA}
$$

$$
\boxed{x_1x_2+x_1x_3+x_2x_3=\frac CA}
$$

$$
\boxed{x_1x_2x_3=-\frac DA}
$$

### 2. 三次韦达定理的推导

若三个根为 x_1,x_2,x_3，则：

$$
Ax^3+Bx^2+Cx+D=A(x-x_1)(x-x_2)(x-x_3)
$$

展开：

$$
\begin{aligned}
A(x-x_1)(x-x_2)(x-x_3)
=A[&x^3-(x_1+x_2+x_3)x^2\\
&+(x_1x_2+x_1x_3+x_2x_3)x\\
&-x_1x_2x_3]
\end{aligned}
$$

逐项比较系数，就得到三次韦达定理。

### 3. AMC 12第19题应用

设 a,b,c 是方程：

$$
x^3+kx+1=0
$$

的三个根。补出缺失的二次项：

$$
x^3+0x^2+kx+1=0
$$

由韦达定理：

$$
a+b+c=0
$$

$$
ab+bc+ca=k
$$

$$
abc=-1
$$

若要求：

$$
a^3b^2+a^2b^3+b^3c^2+b^2c^3+c^3a^2+c^2a^3
$$

先分组提取公因式：

$$
a^2b^2(a+b)+b^2c^2(b+c)+c^2a^2(c+a)
$$

因为 a+b+c=0：

$$
a+b=-c,\qquad b+c=-a,\qquad c+a=-b
$$

所以原式等于：

$$
\begin{aligned}
&-a^2b^2c-ab^2c^2-a^2bc^2\\
&=-abc(ab+bc+ca)\\
&=-(-1)k\\
&=\boxed{k}
\end{aligned}
$$

---

## 韦达核心公式汇总

### 二次方程

$$
Ax^2+Bx+C=0
$$

$$
\boxed{x_1+x_2=-\frac BA},\qquad
\boxed{x_1x_2=\frac CA}
$$

### 三次方程

$$
Ax^3+Bx^2+Cx+D=0
$$

$$
\boxed{x_1+x_2+x_3=-\frac BA}
$$

$$
\boxed{x_1x_2+x_1x_3+x_2x_3=\frac CA}
$$

$$
\boxed{x_1x_2x_3=-\frac DA}
$$

***

### 1. 普通棱台体积公式

$$
\boxed{V=\frac{h}{3}\left(S_1+S_2+\sqrt{S_1S_2}\right)}
$$

- h：棱台的高
- S_1：下底面积
- S_2：上底面积

适用于上下底面相似的标准棱台。

### 2. 拟柱体体积公式

$$
\boxed{V=\frac{h}{6}\left(S_1+4S_m+S_2\right)}
$$

- h：立体的高
- S_1：下底面积
- S_2：上底面积
- S_m：高度正中间处的截面面积

第20题使用的是拟柱体公式。

已知：

$$
h=12,\qquad S_1=13\times8=104
$$

中间截面为 10*4 的矩形：

$$
S_m=40
$$

顶部是一条线段，因此：

$$
S_2=0
$$

代入：

$$
\begin{aligned}
V&=\frac{12}{6}(104+4\times40+0)\\
&=2\times264\\
&=\boxed{528}
\end{aligned}
$$

> 注意：S_m 必须是高度一半处的截面面积。

***

### 二项式定理

### 基本公式

$$
\boxed{(a+b)^n=\sum_{k=0}^{n}\binom nk a^{n-k}b^k}
$$

$$
\boxed{\binom nk=\frac{n!}{k!(n-k)!}}
$$

### 第 k+1 项

$$
\boxed{T_{k+1}=\binom nk a^{n-k}b^k}
$$

### 常用结论

$$
\boxed{\sum_{k=0}^{n}\binom nk=2^n}
$$

$$
\boxed{\sum_{k=0}^{n}\binom nkx^k=(1+x)^n}
$$

$$
\boxed{\sum_{k\text{为偶数}}\binom nk
=\sum_{k\text{为奇数}}\binom nk=2^{n-1}}
\qquad(n\ge1)
$$

### 第23题应用

$$
\begin{aligned}
\sum_{n=1}^{9}\binom9n2^{n-1}
&=\frac12\sum_{n=1}^{9}\binom9n2^n\\
&=\frac{(1+2)^9-1}{2}\\
&=\boxed{9841}
\end{aligned}
$$

***

Burnside 引理可以简单概括为：

> **考虑旋转、翻转后，本质不同的方案数，等于各种对称操作下保持不变的方案数的平均值。**

公式：

17题中正方形有 \(8\) 种操作：

- 不变；
- 旋转 \(90度,180度,270度)；
- 水平、竖直翻转；
- 两条对角线翻转。

因此：{84+0+0+0+6+6+0+0}{8} =12

***