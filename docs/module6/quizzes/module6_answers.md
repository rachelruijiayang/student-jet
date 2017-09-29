# Module 6: Answers

1. What would be included in a map for a drone delivery robot that needs to transport packages?

  **location of package, location of destination, hazards or potential obstacles**

2. What differentiates planning for environments that involve many interacting agents from single agent planning?

  **When multiple agents are involved, the actions of each agent must be considered.  Oftentimes plans will need to be revised frequently to adjust to the repercussions of the other agent's actions.**

3. What is the term that describes artificially increasing the size of obstacles in a map?

  **Obstacle inflation or Obstacle expansion**

4. Briefly describe the trade-off that robots face when they have an incomplete map.

  **Exploration vs. Exploitation.  Robots can explore the un-mapped regions in hopes of finding a better path, or they can exploit the best known path in the mapped regions.  Often robots will combine exploration and exploitation.**

5. What is the requirement for a heuristic function to be admissible?

  **The function must never overestimate the cost (or length) to reach the goal.**

6. What can happen if a heuristic is in-admissible?

  **A\* can return a suboptimal path.**

7. How does A\* decide which node to explore?

  **It chooses the node in the open set that has the smallest sum of its distance from the start to the node and the heuristic estimate of the distance from the node to the goal.**

8. When will a node be added to the OpenSet in A\*?

  **when the node is a neighbor of the current node, it is safe to visit, and it is not already in the closed set or the open set.**

9. How is the path reconstructed after running A\*?

  **The current node is set to the goal node.  The process iterates by setting the current node to the node that the previous current node came from.  A map cameFrom is used to store what nodes were on the path to each node.  Each current node is added to a list which is returned as the path once the current node is the start node.**

10. What would happen if A\* only considered the heuristic function when deciding which node to explore?

  **This is equivalent to Best First Search, and it can return a suboptimal path.**
