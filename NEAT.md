# NEAT

## Crossover


---

## Mutations

There are `5` mutation a offspring network can have performed to it. 

**Link/Connection**

Creates a new link/connection between `2` nodes with a random weight 
`-2 < w < 2`.

**Node**

Creates a new node on a connection (division of a current connection). The first
new connection weight will be set to `1` while the second connection weight will
be set to the previous node.

> Two new connections, one connection disabled.

**Enable/Disable Connection**

From a static percentage of connections to switch, randomly select that number
of connections and switch `enable -> disable` and `disable -> enable`.

**Weight Shifting**



**New Random Weight**

Choose a random connection and set the weight to a new one to `-2 < w < 2`.

---

## Selection

1. Sort into species
2. Order networks in species 
3. Cull 50%
4. 
