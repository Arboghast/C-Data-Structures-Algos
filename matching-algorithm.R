#
# Sami Hossain
# 02/26/2021
# Custom Implementation of the Gale-Shapley (Matching) Algorithm
#

############
### SETUP ##
############
library(igraph)

#Bipartite sets
set1 <- c(1:15) #vector set 1 (girls)
set2 <- c(16:30)  #vector set 2 (guys)

mat <- matrix(nrow = 30, ncol = 15) #matrix table of priority lists
for(i in 1:30){
  if(i %in% set1){
    mat[i,] <- sample(set2)
  }
  else{
    mat[i,] <- sample(set1)
  }
}

#dp arrays for simulating rounds
prevround<- vector(mode = "list", length = 15)
round<- vector(mode = "list", length = 15)

################
### ALGORITHM ##
################

#returns the girls best choice from the list of guys
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
  for(j in 16:30){  #loop through the set of all guys
    indx <- min(which(!is.na(mat[j,]))) #find the next girl on their lists
    round[[mat[j,indx]]] <- c(round[[mat[j,indx]]], j) # to visit tonight
  }
  
   
  for(k in 1:length(round)){  #iterate through the set of girls
    if(!is.null(round[[k]])){  #if there are guys at a certain girls home tonight
      best <- bestGuy(round[[k]],mat[k,])   #find the best guy
      for(m in round[[k]]){
        if(m != best){   #all other guys are rejected
          i <- min(which(!is.na(mat[m,])))  
          mat[m,i] <- NA   #they remove this girl from their own preference lists
        }
      }
    }
  }
  
  if(identical(prevround,round)){ #no one was rejected, implying a perfect matching
    break
  }
  
  prevround <- c(round)  #needed for a stop condition
  round <- vector(mode = "list", length = 15) #new night
}

################
### VISUALIZE ##
################

edges <- matrix(ncol = 2, nrow = 15)  #generate an edge list based on our matching
for(i in 16:30){
  ind <- min(which(!is.na(mat[i,])))
  edges[i-15,1] <- mat[i, ind]
  edges[i-15,2] <- i
}

colors <- ifelse(1:30 %in% set1, "pink", "red")  #separately color bipartite sets
shapes <- ifelse(1:30 %in% set1, "circle", "square") #seperately assign shapes
graph <- graph_from_edgelist(edges, directed= FALSE )
V(graph)$type <- 1:30 %in% set1
plot(graph, layout = layout_as_bipartite, 
     vertex.color= colors, vertex.shape = shapes, edge.width = 4)
