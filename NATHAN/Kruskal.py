import sys

class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
        self.size = [1] * n
        self.num_components = n

    def find(self, i):
        if self.parent[i] == i:
            return i
        self.parent[i] = self.find(self.parent[i])
        return self.parent[i]

    def unite(self, i, j):
        root_i = self.find(i)
        root_j = self.find(j)
        if root_i != root_j:
            if self.size[root_i] < self.size[root_j]:
                root_i, root_j = root_j, root_i
            self.parent[root_j] = root_i
            self.size[root_i] += self.size[root_j]
            self.num_components -= 1
            return True
        return False

    def get_num_components(self):
        return self.num_components

class Solution:
    def get_mst_weight(self, n, all_edges, ignore_edge_idx=-1, force_edge_idx=-1):
        dsu = DSU(n)
        mst_weight = 0
        edges_count = 0

        if force_edge_idx != -1:
            forced_edge = None
            for edge in all_edges:
                if edge[3] == force_edge_idx:
                    forced_edge = edge
                    break
            if forced_edge:
                 u, v, w, _ = forced_edge
                 dsu.unite(u, v)
                 mst_weight += w
                 edges_count += 1
            else:
                 return float('inf')

        sorted_edges = sorted(all_edges, key=lambda x: x[2])

        for u, v, w, idx in sorted_edges:
            if idx == ignore_edge_idx:
                continue
            if idx == force_edge_idx:
                continue

            if dsu.unite(u, v):
                mst_weight += w
                edges_count += 1

        if dsu.get_num_components() == 1 and edges_count == n - 1:
            return mst_weight
        else:
            return float('inf')

    def findCriticalAndPseudoCriticalEdges(self, n, edges_input):
        edges_with_indices = []
        for i, edge in enumerate(edges_input):
            edges_with_indices.append(edge + [i])

        min_mst_weight = self.get_mst_weight(n, edges_with_indices)

        if min_mst_weight == float('inf'):
            return [[], []]

        critical_edges_indices = []
        pseudo_critical_edges_indices = []

        for i in range(len(edges_with_indices)):
            original_index = edges_with_indices[i][3]

            weight_without_edge = self.get_mst_weight(n, edges_with_indices, ignore_edge_idx=original_index)

            if weight_without_edge > min_mst_weight or weight_without_edge == float('inf'):
                critical_edges_indices.append(original_index)
            else:
                weight_with_forced_edge = self.get_mst_weight(n, edges_with_indices, force_edge_idx=original_index)
                if weight_with_forced_edge == min_mst_weight:
                    pseudo_critical_edges_indices.append(original_index)

        return [critical_edges_indices, pseudo_critical_edges_indices]