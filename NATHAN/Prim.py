import heapq

class Solution:
    def minCostConnectPoints(self, points):
        n = len(points)
        if n == 1:
            return 0
        
        total_cost = 0
        visited = set()
        heap = []
        
        start = 0
        visited.add(start)
        
        for j in range(n):
            if j != start:
                x1, y1 = points[start]
                x2, y2 = points[j]
                distance = abs(x1 - x2) + abs(y1 - y2)
                heapq.heappush(heap, (distance, j))
        
        while heap and len(visited) < n:
            distance, point = heapq.heappop(heap)
            if point not in visited:
                visited.add(point)
                total_cost += distance
                for j in range(n):
                    if j != point and j not in visited:
                        x1, y1 = points[point]
                        x2, y2 = points[j]
                        new_distance = abs(x1 - x2) + abs(y1 - y2)
                        heapq.heappush(heap, (new_distance, j))
        
        return total_cost
