# This program is written by R, just copy the following code and paste in the command windows of R,
# Or save this file as "Surface_Rgression.R", then execute "source("Surface_Rgression.R", echo = TRUE)"
# If you haven't installed "plotly", please install the packages at first time
# 

# source("Surface_Rgression.R", echo = TRUE) 
# install.packages("plotly")		# install "plotly" for first use
library(plotly)				          # use plotly if need
m <- read.table("test.csv", sep = ",")
m <- as.matrix(m)
# import data will be char, this step transfer m into numerical matrix
k = length(m)/3
# there are k row times 3 column, total length is k*3, so length divides by 3 is k
x <- matrix(nrow = k, ncol = 1)		# declare x as k*1 matrix
y <- matrix(nrow = k, ncol = 1)		# declare y as k*1 matrix
z <- matrix(nrow = k, ncol = 1)   # declare z as k*1 matrix
x[1:k,1] <- m[1:k,1]			# put m(1:k,1) data into x
y[1:k,1] <- m[1:k,2]			# put m(1:k,2) data into y
z[1:k,1] <- m[1:k,3]			# put m(1:k,3) data into z
A <- matrix(nrow = k, ncol = 15)	# declare A as k*15 matrix
A[1:k,1] = 1
A[1:k,2] = x
A[1:k,3] = y
A[1:k,4] = x*x
A[1:k,5] = x*y
A[1:k,6] = y*y
A[1:k,7] = x*x*x
A[1:k,8] = x*x*y
A[1:k,9] = x*y*y
A[1:k,10] = y*y*y
A[1:k,11] = x*x*x*x
A[1:k,12] = x*x*x*y
A[1:k,13] = x*x*y*y
A[1:k,14] = x*y*y*y
A[1:k,15] = y*y*y*y
z <- qr.fitted(qr(A), z, k = 15)
ii = 52015				# x coordinate unit(um)
jj = 64325				# y coordinate unti(um)
x <- seq(-ii, ii, 100)			# x coordinate from -ii to ii, and grid size is 100
y <- seq(-jj, jj, 100)			# y coordinate from -jj to jj, and grid size is 100
xx = floor(ii/100)*2+1
yy = floor(jj/100)*2+1
Reg_z <- matrix(nrow = yy, ncol = xx)
for (j in 1:yy)
{
	for (i in 1:xx)
	{
		Reg_z [j,i] = a[1] + a[2]*x[i] + a[3]*y[j] + a[4]*x[i]*x[i] + a[5]*x[i]*y[j] + a[6]*y[j]*y[j] + a[7]*x[i]*x[i]*x[i] + a[8]*x[i]*x[i]*y[j] + a[9]*x[i]*y[j]*y[j] + a[10]*y[j]*y[j]*y[j] + a[11]*x[i]*x[i]*x[i]*x[i] + a[12]*x[i]*x[i]*x[i]*y[j] + a[13]*x[i]*x[i]*y[j]*y[j] + a[14]*x[i]*y[j]*y[j]*y[j] + a[15]*y[j]*y[j]*y[j]*y[j]
	}
}
plot_ly(x = ~x, y = ~y, z = ~Reg_z, type = "contour")
