### The intuition beind this is, once we find a maximum flow, our source and
### sink nodes in the residual graphs will be disconnected via (no s-t path existing)
### as a termination condition. Therefore all we have to do is take the redsidual graph and
### apply a bfs on the source and sink to find all vertexs that are reachable by both and place
### them into sepereate sets A, B

source("dinitz-max-flow.R")

plot(graph)

## the residual graph is 'graph'
scut <- bfs(graph, source, neimode = "out", dist = T, unreachable = FALSE) 
tcut <- bfs(graph, sink, neimode = "out" , dist = T, unreachable = FALSE) 
A <- V(graph)[which(!is.nan(tcut))]
B <- V(graph)[which(!is.nan(scut))]