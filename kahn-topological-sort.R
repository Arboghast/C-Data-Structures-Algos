#
# Sami Hossain
# 04-22-2021
# Kahn's Topological Sorting Algorithm
# Recursive graph reductions based on nodes of indegree 0

if (!requireNamespace("BiocManager", quietly = TRUE)){  #for pcalg library
  install.packages("BiocManager")
  library('BiocManager')
  BiocManager::install("RBGL")
}
############
### SETUP ##
############
library(pcalg)
library(igraph)
nodes <- 10

graph <- randomDAG(nodes, prob= 0.3, lB = 1, uB = 1) %>% #generating a random Directed Acyclic Graph
            graph_from_graphnel()

plot(graph)

################
### ALGORITHM ##
################
#by definition of DAG, there is at least one vertex with indegree[incoming edges] equal to 0

topo_ordering <<- c()



getNextVertex <- function(){
  for(i in nodes:1){
    if(sum(graph[,i]) == 0 && !(i %in% topo_ordering)){
      return (i)
    }
  }
  return (NULL)
}

repeat{
  v <- getNextVertex()
  if(is.null(v)){break} #no indegree edges left -> ordering is complete
  
  #rip out the vertex and its edges from the graph and add it to the topo ordering
  graph[v,] <- FALSE
  topo_ordering <- c(topo_ordering, v)
  graph[]
}

print(topo_ordering)
