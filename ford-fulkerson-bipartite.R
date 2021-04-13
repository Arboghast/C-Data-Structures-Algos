#
# Sami Hossain
# 04/13/2021
# Ford Fulkerson's algorithm applied to a Bipartite Graph
# To find the maximum cardinality matching 

##############
###  SETUP  ##
##############
library(igraph)
nodes <- 10

graph <- sample_bipartite(nodes, nodes, type= "gnp", .20, directed = TRUE, mode = "out") %>% #random bipartite graph
          add_vertices(1, type= FALSE) %>%  #source
          add_vertices(1, type = TRUE)  #sink

format <- layout.bipartite(graph)
plot(graph, layout = format[,c(2,1)]) 

left <- V(graph)[which(V(graph)$type != TRUE)]
left <- left[-length(left)]
right <- V(graph)[which(V(graph)$type)]
right <- right[-length(right)]
source <- (nodes*2)+1
sink <- (nodes+1)*2

for(i in left){ #attach edges outgoing from source
    graph[source,i] <- TRUE
}

for(i in right){ #attach edges incoming to sink
  graph[i,sink] <- TRUE
}

V(graph)[c(sink,source)]$color <- "skyblue"
plot(graph,layout = format[,c(2,1)])
remove(i)

#################
###  ALGORITHM ##
#################
Maxflow <- 0  #source can output max 35 flow
flowEdges <- NULL

#repeat until no paths left
repeat{
  path <- suppressWarnings(shortest_paths(graph, source, sink, output = "both"))
  if(length(path$epath[[1]]) == 0) {break}
  
  Maxflow <- Maxflow+1   #increment by one
  
  #calculate the flow and adjust edge weights, creating altflows if necessary
  flowEdges <- c(flowEdges, path$vpath[1])
  vertexs <- as_ids(path$vpath[[1]])
  for(i in seq(1,length(vertexs)-1, 1) ){  #iterate over every edge in shortest path
    graph[vertexs[i], vertexs[i+1]] <- FALSE
  }
  
}
plot(graph,layout = format[,c(2,1)])


if(is.null(flowEdges)){
  print("no Flow exists between source and sink")
} else {
  
  graph2 <- sample_bipartite(nodes, nodes, type= "gnp", .00, directed = FALSE) %>% #random bipartite graph
    add_vertices(1, type= FALSE) %>%  #source
    add_vertices(1, type = TRUE)  #sink
  
  
  for(i in 1:length(flowEdges)){   #reassign the flow edges that were removed during calculations
    flow <- as_ids(flowEdges[[i]])
    edgelist <- NULL
    for(j in seq(1,length(flow)-1, 1)){
      edgelist <- c(edgelist, flow[j], flow[j+1])
    }
    graph2 <- add_edges(graph2, edgelist, color="skyblue", width=3) #color code max flow edges
  }
  
  V(graph2)[c(sink,source)]$color <- "skyblue"
  plot(graph2,layout = format[,c(2,1)], edge.arrow.size = .55, edge.arrow.width= .55)  
  print(paste0("Max Cardinality Matching Size: ", Maxflow))
}
