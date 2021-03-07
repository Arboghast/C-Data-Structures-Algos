#
# Sami Hossain
# 03/02/2021
# Custom Implementation of the Irving (Stable Roommates) Algorithm
#

############
### SETUP ##
############
library(igraph)

#rseed <- floor(runif(1, min = 1, max= 10000))

mat <- matrix(nrow = 20, ncol = 19)

for(i in 1:20){
  set1 <- setdiff(sample(1:20, 20), i) #excluding the current number from the distribution
  #set1 <- c(set1, i)  #for keeping track of no matches
  mat[i,] <- set1   #populate preference matrix
}

###############################
### PHASE 1 of the algorithm ##
###############################
curr_choice <- rep(NA, 20)  #first rounds choices
stack <- rev(seq(20:1))  #stack to keep track of the first round

while(length(stack) > 0){   #until everyone has been checked
  curr_node <- stack[length(stack)]   #the current node being processed
  for(j in 1:19){   #iterate through at most every node on its preference list
    partner <- mat[curr_node,j]   #the preference list node associated at j
    if(!is.na(curr_choice[partner])){  #if no current partner is chosen
      flag <- FALSE   #flag needed to brake out of the for loop from within
      for(k in 1:19){
        if(mat[partner,k] == curr_choice[partner]){  #if the partner is better than the current node
          break
        }
        if(mat[partner,k] == curr_node){  #if the current node is better than the partner
          flag <- TRUE
          stack <- stack[-length(stack)]    #pop stack
          stack <- c(stack, curr_choice[partner])   #push rejected node onto stack
          curr_choice[partner] <- curr_node   #update new partner
          break
        }
      }
      if(flag){
        break
      }
    } else {
      curr_choice[partner] <- curr_node   #assign curr node as partner
      stack <- stack[-length(stack)]  #pop stack
      break
    }
    
    if(j == 19 && stack[length(stack)] == partner){  #if no possible matches for current node
      stack <- stack[-length(stack)]    #pop from stack to prevent infinite loop 
    }
  }
}

########################
### PHASE 1 Reduction ##
########################
if(length(curr_choice) != 20){
  print("reduction is not possible")
}

## Corollary 1.3 (i & ii) inferred mutual crossouts
for(i in 1:20){   #loop through all the nodes
  choice <- curr_choice[i]
  flag <- FALSE
  for(j in 1:19){   #loop through the preference list for the current node
    if(flag){
      for(k in 1:19){
        if(!is.na(mat[mat[i,j],k]) && mat[mat[i,j],k] == i){ #find the nodes number in their list
          mat[mat[i,j],k] <- NA   #remove the choice from the preference list
          break
        }
      }
      mat[i,j] <- NA  #Mutual cross out, both cross each other of their lists
    }
    if(!is.na(mat[i,j]) && mat[i,j] == choice){ #loop until we see the target node
      flag <- TRUE
    }
  }
}

#####################################
### PHASE 2 Iterative Reductions ##
#####################################
`%notin%` <- Negate(`%in%`)

while(sum(is.na(mat))< 360){ #every row having one choice, 20*18
  for(d in 1:20){   #checks if any row is completely NA, implying no stable matching
    if(all(is.na(mat[d,]))){
      stop("No Stable Matching Exists")
    }
  }
  
  last <- numeric()   #keep track of the last elements
  second <- numeric()  #keep track of the 2nd elements
  indx <- 0
  for(i in 1:19){
    if(sum(is.na(mat[i,])) < 18){ #more than one choice in their list
      last <- c(last, i)   #setup process to begin looking for a cycle
      indx <- i
      break
    }
  }
  toggle <- TRUE
  while(TRUE %notin% duplicated(last)){ #cycle condition
    if(toggle){
      antiset <- which(!is.na(mat[indx,]))    #alternate between 2nd element
      second <- c(second, mat[indx,antiset[2]])
      indx <- mat[indx, antiset[2]]
      toggle <- FALSE
    } else {
      antiset <- which(!is.na(mat[indx,]))    #and the last element of each row
      last <- c(last, mat[indx,antiset[length(antiset)]])
      indx <- mat[indx, antiset[length(antiset)]]
      toggle <- TRUE
    }
  }    #loop ends when the first element in the last vector is repeated
  cycle_start <- match(last[length(last)], last)   #returns the index of the first duplicate
  last <- last[-1:-cycle_start]  #truncate list based on the cycle starting position
  second <- second[cycle_start:length(second)]  #same for this list aswell
  for(m in 1:length(last)){  #mutual crossouts among the nodes of the same index
    for(s in 1:19){
      if(!is.na(mat[last[m],s]) && mat[last[m],s] == second[m]){ #second crosses out last
        mat[last[m],s] <- NA
      }
      if(!is.na(mat[second[m],s]) && mat[second[m],s] == last[m]){ #last crosses out second
        mat[second[m],s] <- NA
      }
    }
  }
}

################
### VISUALIZE ##
################
edges <- matrix(ncol = 2, nrow = 10)  #generate an edge list
w <- 1
for(i in 1:20){
  ind <- min(which(!is.na(mat[i,])))
  partner <- mat[i, ind]
  if(partner %notin% edges){ #to reduce edgelist into a set of unique edges
    edges[w,1] <- partner
    edges[w,2] <- i 
    w <- w+1
  }
}
graph <- graph_from_edgelist(edges, directed= TRUE )
V(graph)$shape <- "square"
V(graph)$color <- "whitesmoke"
plot(graph)
