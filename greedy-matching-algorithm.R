#
# Sami Hossain
# 04/17/2021
# Approximate Maximal Matching algorithm (greedy) maximize weight cost
# Similar in technique to the scheduling problem
# guaranteed at least 50% of the true maximum


library(igraph)
nodes <- 10

graph <- erdos.renyi.game(nodes, .45, type = "gnp", directed = F) #random graph
E(graph)$weight <- sample(5:40,length(E(graph)), replace = T) #apply weights to edges
plot(graph) 

relabled <- sort(E(graph)$weight, decreasing = T, index.return = T)$ix  #sort the edges by highest cost
matching <- graph.empty(nodes, directed = FALSE)

for(i in relabled){
  temp <- ends(graph, E(graph)[i], names= T)[1,] #endpoints of the edge
  v1 <- temp[1]
  v2 <- temp[2]
  if( sum(matching[v1,]) == 0 && sum(matching[v2,]) == 0 ){
    matching[v1,v2] <- TRUE
  }
}

sum <- 0
#calculate edge costs
for(i in 1:nodes){ #to prevent double counting
  for(j in 1:nodes){ 
    if(matching[i,j] == 1){
      sum <- sum + graph[i,j]
    }
  }
}

plot(matching)
print(paste0("Approximate Max Weight Matching - Edge cost: ", sum))