#
# Sami Hossain
# 03/28/2021
# Custom Implementation of Goldmans's (Push-Relabel) Algorithm
#
# 

############
### SETUP ##
############
library(igraph)
nodes <- 8

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

graph2 <- graph
flow_graph <- graph
remove(i, rand)
################
### ALGORITHM ##
################
flow_graph[] <- 0 #for visualization purposes 

V(graph)$level <- 0 #initialize levels
V(graph)[source]$level <- nodes 
V(graph)$excess <- 0

#push all flow out from source, initialization step
for(i in 1:nodes){
  if(graph[source,i]){ #edge exists
    V(graph)[i]$excess <- graph[source,i]
    graph[i, source] <- graph[source, i]  #set edges incoming to source
    flow_graph[source,i] <- graph[source, i]
    graph[source, i] <- FALSE #remove edges outgoing from source
  }
}

#check if an edge exists between two nodes, and if so - do their levels meet a criteria
pushable <- function(node) {
  for(i in 1:nodes){
    if(graph[node,i]){ # if an edge exists between the two nodes
      if(V(graph)[node]$level >= (V(graph)[i]$level+1)){ #and level(height) contraint is met
        return (i);
      }
    }
  }
  return (NULL);
}

repeat{ # End result converges with a maximum flow value, all excess has been routed to either source or sink
  #print(sum(V(graph)$excess))
  if(sum(V(graph)[-c(sink,source)]$excess) <= 0){ break } ##while any non sink, source node has excess capacity.
  
  exc <- V(graph)[ V(graph)$excess != 0 ] #of the nodes with excess > 0
  exc2 <- intersection(exc, V(graph)[-c(sink,source)])  #of which are not source or sink nodes
  node <- as_ids(exc2[which.max(exc2$level)])  #choose the one with the largest level
  
  push_to <- pushable(node)
  if(!is.null(push_to)){ #Push subroutine
    #print("push")
    delta <-  min(V(graph)[node]$excess, graph[node,push_to]) #lower bound on maximum edge capacity and excess
    
    #push delta units of flow along edge (node, push_to)
    if(graph[node,push_to] == delta){  #delete if resid capacity is 0
      graph[node,push_to] <- FALSE
    } else {
      graph[node,push_to] <- graph[node,push_to] - delta
    }
    graph[push_to, node] <- graph[push_to,node] + delta
    flow_graph[node,push_to] <- flow_graph[node,push_to] + delta
    
    V(graph)[node]$excess <- V(graph)[node]$excess - delta  #update excess of the nodes involved
    V(graph)[push_to]$excess <- V(graph)[push_to]$excess + delta
  } else {  #Relabel subroutine
    #print("relabel")
    V(graph)[node]$level <- V(graph)[node]$level + 1  #increment level by one
  }
}

remove(exc, exc2, i, node, push_to, delta)
################
### VISUALIZE ##
################

for(i in 1:nodes){
  for(j in i:nodes){
    if(flow_graph[i,j] > 0 && flow_graph[j,i] > 0){  #equalize the edges with their reverse edges
      if(flow_graph[i,j] > flow_graph[j,i]){
        flow_graph[i,j] <- flow_graph[i,j] - flow_graph[j,i]
        flow_graph[j,i] <- FALSE
      } else {
        flow_graph[j,i] <- flow_graph[j,i] - flow_graph[i,j]
        flow_graph[i,j] <- FALSE
      }
    }
  }
}

for(i in 1:nodes){  #overlay flow paths over original graph
  for(j in 1:nodes){
    if(flow_graph[i,j] > 0){
      graph2[i,j] <- flow_graph[i,j]
      edge <- get.edge.ids(graph2, c(i,j))
      E(graph2)[edge]$color <- "skyblue"
      V(graph2)[i]$color <- "skyblue"
      V(graph2)[j]$color <- "skyblue"
    }
  }
}

remove(i,j,edge)
V(graph2)[sink]$color <- "azure"
V(graph2)[source]$color <- "azure"
E(graph2)$width <- E(graph2)$weight/10
plot(graph2, edge.arrow.size = .75, edge.arrow.width= .75)
print(paste0("Max flow value: ", V(graph)[sink]$excess))
