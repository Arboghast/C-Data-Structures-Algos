#
# Sami Hossain
# 02/26/2021
# Custom Implementation of the Gale-Shapley (Matching) Algorithm
#

############
### SETUP ##
############
library(igraph)
nodes <- 15

#Bipartite sets
set1 <- c(1:nodes) #vector set 1 (girls)
set2 <- c((nodes+1):(nodes*2))  #vector set 2 (guys)

mat <- matrix(nrow = nodes*2, ncol = nodes)
for(i in 1:(nodes*2)){ #generate preference lists
  if(i %in% set1){
    mat[i,] <- sample(set2, replace = FALSE)
  }
  else{
    mat[i,] <- sample(set1, replace = FALSE)
  }
}
remove(i)

################
### ALGORITHM ##
################

#dp arrays for simulating rounds
prevround<- vector(mode = "list", length = nodes)
round<- vector(mode = "list", length = nodes)

#returns the girls best choice from the list of guys that visited her tonight
bestGuy <- function(list, pref){
  max <- NA
  for(i in 1:length(pref)){
    if(pref[i] %in% list){
      max <- pref[i]
      break
    }
  }
  return(max)
}

repeat{ #every iteration represents a new night
  
  for(j in set2){  #loop through the set of all guys
    indx <- min(which(!is.na(mat[j,]))) #find the next girl on their lists
    round[[mat[j,indx]]] <- c(round[[mat[j,indx]]], j) # to visit tonight
  }
  
   
  for(k in 1:length(round)){  #iterate through the set of girls with at least 1 visitor tonight
    if(!is.null(round[[k]])){  #if there are guys at a certain girls home tonight
      best <- bestGuy(round[[k]],mat[k,])   #find the best guy
      for(m in round[[k]]){
        if(m != best){   #all other guys on the list are rejected
          i <- min(which(!is.na(mat[m,])))  
          mat[m,i] <- NA   #they remove the girl from their own preference lists
        }
      }
    }
  }
  
  if(identical(prevround,round)){ #no one was rejected, implying a perfect matching
    break #terminate with a stable perfect matching
  }
  
  prevround <- c(round)  #needed for a stop condition
  round <- vector(mode = "list", length = nodes) #next night
}
remove(i,j,indx,m,best,k)

################
### VISUALIZE ##
################

edges <- matrix(ncol = 2, nrow = nodes)  #generate an edge list based on our matching
for(i in set2){
  ind <- min(which(!is.na(mat[i,])))
  edges[i-nodes,1] <- mat[i, ind]
  edges[i-nodes,2] <- i
}
graph <- graph_from_edgelist(edges, directed= FALSE)

layout <- matrix(ncol = 2, nrow = nodes*2) #custom layout, retain node positions
layout[1:nodes,1] <- 1:nodes
layout[(nodes+1):(nodes*2),1] <- 1:nodes
layout[1:nodes,2] <- 1
layout[(nodes+1):(nodes*2),2] <- 2
layout <- norm_coords(layout, ymin=-1, ymax=1, xmin=-1, xmax=1)

V(graph)$color <- ifelse(1:(nodes*2) %in% set1, "orchid1", "cadetblue1")  #separately color bipartite sets
V(graph)$shape <- ifelse(1:(nodes*2) %in% set1, "circle", "square") #seperately assign shapes
V(graph)$type <- 1:(nodes*2) %in% set1
plot(graph, layout = layout, edge.width = 2,rescale=FALSE, vertex.size = 9)
remove(i,ind,layout,edges)
