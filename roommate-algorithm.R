#
# Sami Hossain
# 03/02/2021
# Custom Implementation of the Irving (Stable Roommates) Algorithm
#

############
### SETUP ##
############
library(igraph)
nodes <- 20

mat <- matrix(nrow = nodes, ncol = nodes-1)

for(i in 1:nodes){ #generate preference lists
  mat[i,] <- setdiff(sample(1:nodes, nodes), i) #exclude current number from the sampling
}
remove(i)

###########################
### PHASE 1A ELIMINATION ##
###########################

curr_choice <- rep(NA, nodes)  #first rounds matching, the ith person is matched with curr_choice[i]
stack <- rev(seq(nodes:1))

while(length(stack) > 0){ 
  curr_node <- stack[length(stack)] 
  for(j in 1:(nodes-1)){   #iterate through at most every node on its own preference list
    partner <- mat[curr_node,j]   #potential partner(pp) for curr node
    if(!is.na(curr_choice[partner])){  #if pp has a partner
      
      flag <- FALSE   
      for(k in 1:(nodes-1)){ #whichever if condition hits first implies it's higher on pp's priority list
        if(mat[partner,k] == curr_choice[partner]){  #if the partner is better than the current node
          break
        }
        if(mat[partner,k] == curr_node){  #if the current node is better than the partner
          flag <- TRUE
          stack <- stack[-length(stack)]    #pop stack
          stack <- c(stack, curr_choice[partner])   #push rejected node onto stack, to have them rematched to someone else
          curr_choice[partner] <- curr_node   #update new partner
          break
        }
      }
      if(flag){
        break
      }
    } else { #if pp has no partner
      curr_choice[partner] <- curr_node   #assign curr node as partner
      stack <- stack[-length(stack)]  #pop stack
      break
    }
    
    if(j == (nodes-1) && stack[length(stack)] == partner){  #if no possible matches for current node
      stack <- stack[-length(stack)]    #pop from stack to prevent infinite loop 
    }
  }
}
remove(j,k,partner,curr_node,stack,flag)

#########################
### PHASE 1B REDUCTION ##
#########################

if(length(curr_choice) != nodes){
  print("reduction is not possible")
}

## Corollary 1.3 (i & ii) inferred mutual crossouts
for(i in 1:nodes){   #loop through all the nodes
  choice <- curr_choice[i]
  flag <- FALSE
  for(j in 1:(nodes-1)){   #loop through the preference list for the current node
    if(flag){
      for(k in 1:(nodes-1)){
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
remove(i,j,k,choice,flag, curr_choice)

################################
### PHASE 2 CYCLE REDUCTIONS  ##
################################

`%notin%` <- Negate(`%in%`)

while(sum(is.na(mat))< (nodes*(nodes-2)) ){ #every row having one choice, 20*18
  for(d in 1:nodes){   #checks if any row is completely NA, implying no stable matching
    if(all(is.na(mat[d,]))){
      stop("No Stable Matching Exists")
    }
  }
  
  last <- numeric()   #keep track of the last elements
  second <- numeric()  #keep track of the 2nd elements
  indx <- 0
  for(i in 1:(nodes-1)){
    if(sum(is.na(mat[i,])) < nodes-2){ #more than one choice in their list
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
  }    #loop ends when an element in the last vector is repeated
  cycle_start <- match(last[length(last)], last)   #returns the index of the first duplicate
  last <- last[-1:-cycle_start]  #truncate list based on the cycle starting position
  second <- second[cycle_start:length(second)]  #same for this list aswell
  for(m in 1:length(last)){  #mutual crossouts among the nodes of the same index
    for(s in 1:(nodes-1)){
      if(!is.na(mat[last[m],s]) && mat[last[m],s] == second[m]){ #second crosses out last
        mat[last[m],s] <- NA
      }
      if(!is.na(mat[second[m],s]) && mat[second[m],s] == last[m]){ #last crosses out second
        mat[second[m],s] <- NA
      }
    }
  }
}
remove(cycle_start, d, i, indx, last, m , s, second, toggle, antiset)

################
### VISUALIZE ##
################

edges <- matrix(ncol = 2, nrow = (nodes/2))  #generate an edge list
w <- 1
for(i in 1:20){
  ind <- min(which(!is.na(mat[i,])))
  partner <- mat[i, ind]
  if(partner %notin% edges){ #to prevent duplicate edges in edgelist
    edges[w,1] <- partner
    edges[w,2] <- i 
    w <- w+1
  }
}
graph <- graph_from_edgelist(edges, directed= FALSE)

dimL <- ceiling(sqrt(nodes))
dimW <- nodes / dimL
layout <- matrix(ncol = 2, nrow = nodes) #custom layout, retain node positions
layout[1:nodes,1] <- rep(1:dimL, dimW)
layout[1:nodes,2] <- rep(1:dimW, dimL)
layout <- norm_coords(layout, ymin=-1, ymax=1, xmin=-1, xmax=1)

V(graph)$shape <- "square"
V(graph)$color <- "powderblue"
plot(graph, layout = layout, edge.width = 3)
remove(i,ind, partner, w, dimL, dimW, layout, edges)
