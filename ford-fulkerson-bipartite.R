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
remove(i,left,right,format)

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
remove(path,i,vertexs)

################
### VISUALIZE ##
################

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
  
  layout <- matrix(ncol = 2, nrow = (nodes+1)*2) #custom layout, retain node positions
  layout[1:(nodes*2),1] <- rep(1:nodes, 2)
  layout[1:(nodes*2),2] <- rep(2:1,each = nodes)
  layout[21:22,1] <- 12
  layout[21,2] <- 2
  layout[22,2] <- 1
  layout <- norm_coords(layout, ymin=-1, ymax=1, xmin=-1, xmax=1)
  
  V(graph2)[c(sink,source)]$color <- "skyblue"
  plot(graph2,layout = layout[,c(2,1)], edge.arrow.size = .55, edge.arrow.width= .55)  
  print(paste0("Max Cardinality Matching Size: ", Maxflow))
  remove(edgelist,flow,i,j,flowEdges)
}
