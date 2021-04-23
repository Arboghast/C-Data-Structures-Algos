#
# Sami Hossain
# 04-22-2021
# Intuitive connected components algorithm for undirected edges
# using BFS

#############
### SETUP ###
#############
library(igraph)
nodes <- 20

graph <- erdos.renyi.game(nodes, 7*(nodes/10), type = "gnm", directed = F, loops = F)
plot(graph)

################
### ALGORITHM ##
################

visited <- c()
components <- list()

bfs <- function(verts) {
  neighbors <- c()
  for(i in verts) {
    temp <- setdiff(which(graph[i,] != 0), visited) #all neighbors that havent been visited yet
    neighbors <- c(neighbors, temp)
  }
  
  if(!is.null(neighbors)){
    visited <<- c(visited, verts) #add current nodes to visited before recursing
    bfs(neighbors)
  }
}

for(i in 1:nodes){
  if(!(i %in% visited)){
    bfs(c(i))
    if(length(components) == 0){
      components[[1]] <- visited #to keep a running total on the visited nodes
      components[[2]] <- visited
    } else {
      components[[length(components)+1]] <- setdiff(visited, components[[1]]) #diff between previous bfs's visited vector and curr
      components[[1]] <- visited
    }
  }
}

components <- components[-1] 
remove(i,neighbors,visited)
print(paste0("there are: ", length(components), " connected components"))
