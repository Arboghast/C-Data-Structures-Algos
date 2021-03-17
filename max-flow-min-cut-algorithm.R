#
# Sami Hossain
# 03/17/2021
# Custom Implementation of Edmonds-Karp's (Max Flow - Min Cut) Algorithm
#                         (Ford-fulkerson Method)
#

##############
###  SETUP  ##
##############

#generate a random network graph
graph <- rgraph(7,tp=10/11, mode="digraph") %>%
  matrix(nrow=7,ncol=7) %>%
  graph_from_adjacency_matrix(mode = "undirected", weighted = T) %>%
  as.directed(mode = "arbitrary")

plot(graph)

rand <- sample(1:7, 2, replace = F) #choose a source and sink
source <- rand[1]
sink <- rand[2]

for(i in 1:7){
  if(graph[from=i, to= source]){  #remove edges incoming to source
    graph[from=i, to= source] <- FALSE
  }
  if(graph[from=sink, to=i]){  #remove edges outgoing from sink
    graph[from=sink, to=i] <- FALSE
  }
}

for(i in 1:7){  #populate edges with random weights
  for(j in 1:7){
    if(graph[i,j]>0){
      graph[i,j, attr="weight"]<- sample(5:35,1)
    }
  }
}

E(graph)$width <- E(graph)$weight/10
V(graph)$color <- colors()[228]
E(graph)$color <- colors()[115]
V(graph)[sink]$color <- "royalblue"
V(graph)[source]$color <- "royalblue"
graph$layout <- layout.kamada.kawai

plot(graph)
#################
###  ALGORITHM ##
#################
Maxflow <- 0  #source can output max 35 flow
flowEdges <- NULL

#repeat until no paths left
repeat{
  path <- suppressWarnings(shortest_paths(graph, source, sink, output = "both"))
  if(length(path$epath[[1]]) == 0) {break}
  
  minFlow <- min(path$epath[[1]]$weight)   #maximum amount of flow for this path
  
  #calculate the flow and adjust edge weights, creating altflows if necessary
  flowEdges <- c(flowEdges, path$vpath[1])
  vertexs <- as_ids(path$vpath[[1]])
  for(i in seq(1,length(vertexs)-1, 1) ){  #iterate over every edge in shortest path
    graph[vertexs[i], vertexs[i+1]] <- graph[vertexs[i], vertexs[i+1]] - minFlow  #decrement capacity
    if(graph[vertexs[i], vertexs[i+1]] == 0){   #delete if no more capacity on the edge
      graph[vertexs[i], vertexs[i+1]] <- FALSE
    }
    if(graph[vertexs[i+1], vertexs[i]] >= 0){  #create altflow i
      graph[vertexs[i+1], vertexs[i]] <- graph[vertexs[i+1], vertexs[i]] + minFlow
    }
  }
  Maxflow <- Maxflow + minFlow  #maxflow assuming inifinite inflow
  
}
plot(graph)


if(is.null(flowEdges)){
  print("no Flow exists between source and sink")
} else {
  for(i in 1:length(flowEdges)){   #reassign the flow edges that were removed during calculations
    flow <- as_ids(flowEdges[[i]])
    edgelist <- NULL
    for(j in seq(1,length(flow)-1, 1)){
      edgelist <- c(edgelist, flow[j], flow[j+1])
    }
    graph <- add_edges(graph, edgelist, color="skyblue", width=3) #color code max flow edges
  }
  
  for(i in 1:7){   #remove antiflow edges to declutter graph !!possible bug!!
    for(j in 1:7){
      if(i>j){
        graph[i,j]<- FALSE
      }
    }
  }
  plot(graph, edge.arrow.size = .55, edge.arrow.width= .55)  
  print(paste0("Max flow value: ", Maxflow))
}
