library(igraph)

set.seed(1022)
colors = sample(colors()) #randomize the colors array

g <-graph_from_atlas(sample(0:1252, 1))   #random graph from a graph library
vcolor <- rep(NA, length(V(g)))  #vertex colors

ordering <- sample(1:length(V(g))) #this will be our ordering for the vertices


for(vertex in ordering) {
  colorIndex = 1;
  while(is.na(vcolor[vertex])) {
    flag = TRUE
    color = colors[colorIndex]
    for(index in 1:length(V(g))){
      if(g[vertex][index] == 1 && !is.na(vcolor[index])){
        if(vcolor[index] == color) {
          flag = FALSE
          colorIndex = colorIndex + 1
          break
        }
      }
    }
    if(flag){
      vcolor[vertex] = color
    }
  }
}

plot(g, vertex.color = vcolor)
