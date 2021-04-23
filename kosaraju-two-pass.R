#
# Sami Hossain
# 04-23-2021
# Kosaraju's Two Pass Algorithm using DFS
# for identifying strongly connected components in a directed graph

############
### SETUP ##
############
library(igraph)
nodes <- 10

graph <- erdos.renyi.game(nodes, .15, type = "gnp", directed = T)
plot(graph)

################
### ALGORITHM ##
################
V(graph)$order <- 0
V(graph)$leader <- 0

visited <- c()
counter <- 1
leader <- NULL
sccs <- list()

dfs_inverted <- function(node){
  visited <<- c(visited, node)
  inv_neighbors <- which(graph[,node] != 0) #incoming edges
  for(edg in inv_neighbors){
    if(!(edg %in% visited)){
      dfs_inverted(edg)
    }
  }
  V(graph)$order[node] <<- counter
  counter <<- counter + 1
}

dfs <- function(node){
  visited <<- c(visited, node)
  V(graph)$leader[node] <<- leader #set its leader
  inv_neighbors <- which(graph[node,] != 0) #outgoing edges
  for(edg in inv_neighbors){
    if(!(edg %in% visited)){
      dfs(edg)
    }
  }
}


for(i in nodes:1){
  if(! i %in% visited){
    dfs_inverted(i)
  }
}

visited <<- c()

for(i in nodes:1){
  vert <- which(V(graph)$order == i)
  if(! vert %in% visited){
    leader <<- vert  #simply a way to keep track of the hgih level dfs calls, the number can be arbitrary but should be distinct
    dfs(vert) #every high level dfs(in this loop) will terminate with one new scc being discovered
    
    if(length(sccs) == 0){
      sccs[[1]] <- visited #to keep a running total on the visited nodes
      sccs[[2]] <- visited
    } else {
      sccs[[length(sccs)+1]] <- setdiff(visited, sccs[[1]]) #new nodes seen in this dfs
      sccs[[1]] <- visited
    }
  }
}
sccs <- sccs[-1]
remove(counter,i,leader,vert,visited)
################
### VISUALIZE ##
################

V(graph)$color <- rainbow(nodes)[V(graph)$leader] #assign distinct colors for each individual scc
plot(graph, mark.groups = split(1:nodes, V(graph)$leader))
print(paste0("there are: ", length(sccs), " strongly connected components in the graph"))
