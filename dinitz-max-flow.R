#
# Sami Hossain
# 03/23/2021
# Custom Implementation of Dinitz's (Maximum Flow) Algorithm
#                         (Cherkassky Optimization)
#

############
### SETUP ##
############
library(igraph)
nodes <- 10

#generate a random network graph
graph <- erdos.renyi.game(nodes, .35, type = "gnp", directed = T)

plot(graph)

rand <- sample(1:nodes, 2, replace = F) #choose a source and sink
source <- rand[1]
sink <- rand[2]

for(i in 1:nodes){
  if(graph[from=i, to= source]){  #remove edges incoming to source
    graph[from=i, to= source] <- FALSE
  }
  if(graph[from=sink, to=i]){  #remove edges outgoing from sink
    graph[from=sink, to=i] <- FALSE
  }
}

E(graph)$weight <- sample(5:40,length(E(graph)), replace = T)

E(graph)$width <- E(graph)$weight/10
V(graph)$color <- "bisque3"
E(graph)$color <- "mistyrose2"
V(graph)[sink]$color <- "lightblue"
V(graph)[source]$color <- "lightblue"
graph$layout <- layout.fruchterman.reingold

plot(graph, edge.arrow.size = .75, edge.arrow.width= .75)

remove(i, rand)
graph2 <- graph
################
### ALGORITHM ##
################
flow <<- c()  #initialize global scope stack
MaxFlow <<- 0
flowEdges <<- matrix(0L, nrow = nodes, ncol= nodes)  #keep track of flow pushed to every edge for plotting purposes

dfs <- function(source, sink) {
  
  flow <<- c(flow, source)
  
  if(source == sink){
    return(sink)
  }
  
  # Recurse with all children
  children <- which(graph[source,] != 0)
  for(i in children) {

    if(V(graph)[source]$level+1 == V(graph)[i]$level  ){   #get all adjacent/uphill vertexes 
      #print(cat(source, i,  sink))

      result = dfs(i, sink)
      if (!is.null(result)) {
        return (result)
      }
    }
  }
  
  flow <<- flow[-length(flow)] #remove last element
  return (NULL)
}

augmentFlow <- function(flow) {
  minFlow <- Inf
  for(i in 1:length(flow)-1){
    #print(graph[flow[i],flow[i+1]])
    minFlow <- min(minFlow, graph[flow[i],flow[i+1]])
  }
  
  for(i in 1:(length(flow)-1)){  #pemdas is a bitch
    if(graph[flow[i],flow[i+1]] - minFlow == 0){
      graph[from= flow[i],to= flow[i+1]] <<- FALSE #delete the edge for simplicity
    }
    else{
      graph[flow[i],flow[i+1]] <<- graph[flow[i],flow[i+1]] - minFlow  #decrease flow on current edge
    }
    
    graph[flow[i+1],flow[i]] <<- graph[flow[i+1],flow[i]] + minFlow  #increase on inverse edge
    
    flowEdges[flow[i], flow[i+1]] <<- flowEdges[flow[i], flow[i+1]] + minFlow
  }
  
  #print(minFlow)
  MaxFlow <<- MaxFlow + minFlow
}

repeat{
  #BFS layered graph
  V(graph)$level <- bfs(graph, source, neimode = "out", dist = T, unreachable = FALSE)$dist 
  if(is.nan(V(graph)[sink]$level)){ break }  #sink is disconnected from source
  
  flow <<- c()  #reset every dfs iteration
  dfs(source,sink)  #dfs blocking path 
  if(length(flow) != 0) {
    augmentFlow(flow) 
    
    plot(graph, edge.arrow.size = .75, edge.arrow.width= .75)
    date_time<-Sys.time()
    while((as.numeric(Sys.time()) - as.numeric(date_time))<.75){}  #manual half second delay to process plot changes
  }
}

#simplify the flow matrix
for(i in 1:nodes){
  for(j in 1:nodes){
    if(flowEdges[i,j] >0 && flowEdges[j,i] > 0){  #if there was flow sent through both an edge and its inverse edge
      if(flowEdges[i,j] > flowEdges[j,i]){
        flowEdges[i,j] <- flowEdges[i,j] - flowEdges[j,i]
        flowEdges[j,i] <- 0
      }
      else{
        flowEdges[j,i] <- flowEdges[j,i] - flowEdges[i,j]
        flowEdges[i,j] <- 0
      }
    }
  }
}

for(i in 1:nodes){  #aggregate flow paths with the original graph
  for(j in 1:nodes){
    if(flowEdges[i,j]>0){
      graph2[i,j] <- flowEdges[i,j]
      edge <- get.edge.ids(graph2, c(i,j))
      E(graph2)[edge]$color <- "skyblue"
      V(graph2)[i]$color <- "skyblue"
      V(graph2)[j]$color <- "skyblue"
    }
  }
}

remove(i,j,date_time,edge,flow)

V(graph2)[sink]$color <- "azure"
V(graph2)[source]$color <- "azure"
E(graph2)$width <- E(graph2)$weight/10
plot(graph2)
print(paste0("Max flow value: ", MaxFlow))
