#
# Sami Hossain
# 04/18/2021
# Topological sort via DFS recursive approach
# Isolating groups of vertices that CAN depend on each other via DFS and
# compiling them together to get a topological ordering

############
### SETUP ##
############
library(igraph)
nodes <- 10

#generate a random network graph
graph <- erdos.renyi.game(nodes, .20, type = "gnp", directed = T, loops = F)

plot(graph, edge.arrow.size = .75, edge.arrow.width= .75, layout= layout.fruchterman.reingold)

visited <- c()
rank <- numeric(nodes)


dfs <- function(graph, sink) {
  visited <<- c(visited, sink)
  for(i in which(graph[1,]!=0)){ #neighbors of the node
    if(! (i %in% visited) ){
      dfs(graph, i)
    }
  }
  rank[sink] <<- nodes
  nodes <<- nodes - 1
}


for( i in 1:nodes){
  if(! (i %in% visited) ){
    dfs(graph, i)
  }
}

ordering <- order(rank)
print(ordering)
