#
# Sami Hossain
# 04-22-2021
# Custom algorithm to find all topological sort permutations
#   using Kahn's algorithm

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

lists <<-list()

getNextVertex <- function(ordering){
  temp <- c()
  for(i in nodes:1){
    temp2 <- ifelse(is.null(ordering), 0, sum(graph[ordering,i])) #account for deleted edges represented by the ordering
    if(!(i %in% ordering) && sum(graph[,i]) - temp2  == 0){
      temp <- c(temp,i)
    }
  }
  return (temp)
}

topo <- function(ordering){
  verts <- getNextVertex(ordering)
  
  if(is.null(verts)){
    lists[[length(lists)+1]] <<- ordering  #append to global scope permutation list
    
  } else {
    for(x in verts){
      topo(c(ordering, x))  #recurse on every possibility
    }
  }
}

topo(c()) #initialization

print(length(lists))
print(length(unique(lists)) == length(lists))
