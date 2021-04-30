#
# Sami Hossain
# 04/04/2021
# Custom Implementation of the Hungarian Algorithm
#        Min-cost Perfect Bipartite Matching
#

############
### SETUP ##
############
library(igraph)
library(data.tree)
nodes <- 10

graph <-sample_bipartite(nodes, nodes, type= "gnp", .4) #random bipartite graph
E(graph)$weight <- sample(5:40,length(E(graph)), replace = T) #apply weights to edges

layout <- matrix(ncol = 2, nrow = nodes*2) #custom layout, retain node positions
layout[1:(nodes*2),1] <- rep(1:nodes, 2)
layout[1:(nodes*2),2] <- rep(2:1,each = nodes)
layout <- norm_coords(layout, ymin=-1, ymax=1, xmin=-1, xmax=1)

plot(graph, layout = layout[,c(2,1)]) 
date_time<-Sys.time()
while((as.numeric(Sys.time()) - as.numeric(date_time))<1.25){} #manual delay to observe bipartite graph
remove(date_time)

################
### ALGORITHM ##
################

#initialization
matching <- graph.empty((nodes*2), directed = FALSE)
V(graph)$price <- 0
visited <<- NULL

is_perfect <- function(matching){ #check whether every node has a matching
  for(i in 1:nodes){
    if(sum(matching[i,]) == 0){
      return(FALSE)
    }
  }
  return(TRUE)
}

bfs_search <- function(root){ #simple 1 layer bfs search
  queue <- c()
  neighbors <- which(graph[,root] != 0)  #get all neighboring nodes
  if(length(neighbors) == 0) { stop("No perfect matching exists") }  #edge case 
  
  for(i in 1:length(neighbors)){
    cost <- graph[neighbors[i],root] - V(graph)[root]$price - V(graph)[neighbors[i]]$price #calculate reduced cost between vertexes
    if(cost == 0 && !(neighbors[i] %in% visited)) {  #we only want to bfs on 'tight' edges, edges of reduced cost == 0
      queue <- c(queue, neighbors[i])  
      visited <<- c(visited, neighbors[i])
    }
  }
  return(queue)
}

alternating_bfs_tree <- function(roots) {
  if(length(roots) == 0) { return(NULL) } #stop condition
  
  queue <- list()
  if( (roots[[1]]$level-1) %% 2 == 1){ #alternating between bfs layers and matching layers, -1 compensation for head node
    for(X in roots){
      neighbors <- bfs_search(as.numeric(X$name)) #add bfs results to the tree and recurse on children
      for(i in neighbors){
        temp <- Node$new(i)
        X$AddChildNode(temp)
        queue[[length(queue)+1]] <- temp
      }
    }
  } else {
    for(X in roots){
      matched_node <- which(matching[as.numeric(X$name),] != 0)[1]  #matching search, by definition should only exist 1
      if(is.na(matched_node)){ #no matching and we generate a good path
        good_path <- c()
        temp_node <- X
        while(!is.null(temp_node$parent)){ #generate good path by traversing up the tree
          good_path <- c(good_path, temp_node)
          temp_node <- temp_node$parent
        }
        return(good_path)
      } else {  #matching exists and we append the child and recurse on it
        temp <- Node$new(matched_node)
        X$AddChildNode(temp)
        queue[[length(queue)+1]] <- temp
      }
    }
  }
  alternating_bfs_tree(queue) #recurse
}


while(!is_perfect(matching)){
  #bfs tree subroutine
  head_node <<- Node$new("head")
  
  for(i in 1:nodes){
    if(sum(matching[i,]) == 0){ #non perfect matching implies this condition to be true
      head_node$AddChild(i)  #bfs centered on an unmatched node
      break
    }
  }
  
  visited <<- NULL #reset on every new construction
  good_path <- alternating_bfs_tree(head_node$children) #recursively create a bfs tree with a twist
  
  date_time<-Sys.time()
  while((as.numeric(Sys.time()) - as.numeric(date_time))<.45){}  #manual delay to visualize plot changes
  plot(as.igraph(head_node, directed = TRUE, direction = "climb"), layout = layout_as_tree)
  
  if(is.null(good_path)){ #update vertex prices to progress to a new good path iteration, every iteration creates a new tight edge
    print("good set route")
    
    good_set_odd <- c() #even levels of the bfs tree
    good_set_even <- c() #odd levels of the bfs tree
    qq <- head_node$Get("level")
    for(i in 2:length(qq)){
      if(qq[[i]] %% 2 == 0){
        good_set_even <- c(good_set_even, as.numeric(names(qq)[i]))
      } else {
        good_set_odd <- c(good_set_odd, as.numeric(names(qq)[i]))
      }
    }
    
    delta <- Inf #largest possible value we can make to create a new tight edge between a node in S and a node in W %notin% N(S)
    for(i in good_set_even){
      indx <- setdiff(which(graph[i,] != 0) ,good_set_odd)#remove edges which endpoints lie in N(s) (odd set)
      
      temp7 <- graph[i,indx] - V(graph)[indx]$price - V(graph)[i]$price #calculate the reduced price to minimize over
      delta <- min(temp7, delta)
    }
    
    V(graph)[good_set_even]$price <- V(graph)[good_set_even]$price + delta #reduce S nodes by delta, equivalent exchange
    V(graph)[good_set_odd]$price <- V(graph)[good_set_odd]$price - delta #reduce N(S) nodes by delta to maintain their tight property
    
  } else { #existence of an unmatched, tight vertex - a new matching is made on every iteration
    print("good path route")
    
    full_path <- c()
    for(i in 1: (length(good_path)-1) ){ #method for creating an edgelist (igraph semantic)
      full_path <- c(full_path, as.numeric(good_path[[i]]$name), as.numeric(good_path[[i+1]]$name))
    }
    temp_graph <- graph(full_path, n = nodes*2, directed = FALSE) ##create a subgraph with edges encoding the calculated path
    
    t1 <- intersection(temp_graph, matching)  #xor part 1 - the overlap
    t2 <- union(temp_graph, matching) #xor part 2 - the leftover
    matching <- difference(t2,t1) # xor part 3 - the mask
  }
  
}

remove(visited, date_time, qq, temp7, indx, i, good_set_even, good_set_odd, good_path, delta, full_path, t1, t2, temp_graph)

################
### VISUALIZE ##
################

sum <- 0
#calculate edge costs
for(i in 1:nodes){ #to prevent double counting
  for(j in 1:(nodes*2)){ 
    if(matching[i,j] == 1){
      sum <- sum + graph[i,j]
    }
  }
}
remove(i ,j)

#convert matching into a bipartite igraph
V(matching)$type <- ifelse(1:20 >10, TRUE, FALSE)
plot(matching, layout = layout[,c(2,1)])
print(paste0("Min Cost Perfect Matching - Edge cost: ", sum))
