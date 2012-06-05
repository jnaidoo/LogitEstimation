rm(list=ls()) # clear workspace
setwd("~/Documents/UChicago (Work)/2011-12/C++ Course/Problem Sets/Homework 3/hw3Naidoo")
data <-read.table("LogitData.txt",header=FALSE)
#colnames(data)<-c("y","x1","x2","x3","x4")
y = as.vector(data[,1])
X = as.matrix(data[,2:5])
G <- function(index){
  1/(exp(-index)+1)
} 

likelihood <- function(beta){
  tmpSum = 0
  for(ix in 1:100){
     tmpSum = tmpSum+y[ix]*log(G(beta%*%t(X[ix,])))+(1-y[ix])*log(G(-beta%*%t(X[ix,])))       
  }
  return(tmpSum)
}

score <-function(beta){
  tmpSum = c(0,0,0,0)
  for(ix in 1:100){
      tmpSum = tmpSum + (y[ix] - G(beta%*%t(X[ix,])))*X[ix,]
  }
  return(tmpSum)
}

hessian <-function(beta){
  tmpSum = matrix(rep(0,16),nrow=4)
  for(ix in 1:100){
    tmpSum = tmpSum + G(beta%*%t(X[ix,]))*(1-G(beta%*%t(X[ix,])))*as.matrix(X[ix,],mode="numeric",ncol=1)%*%as.vector(X[ix,],mode="numeric")
  }
  return(tmpSum)
}
