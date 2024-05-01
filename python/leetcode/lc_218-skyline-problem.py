from typing import List
from sortedcontainers import SortedList

def getSkyLine(buildings: List[list[int]]) -> List[List[int]]:
    events = []
    for l, r, h in buildings:
        events.append([l, -h])
        events.append([r, h])    
    events.sort()

    result = []
    heights = SortedList()
    heights.add(0)
    
    last_h = 0
    for x, h in events:
        if h < 0:
            heights.add(-h)
        else:
            heights.remove(h)
        
        if heights[-1] != last_h:
            result.append([x, heights[-1]])
            last_h = heights[-1]
    return result


test1 = [[2, 9, 10], [3, 7, 15], [5, 12, 12], [15, 20, 10], [19, 24, 8]]
test2 = [[0, 2, 3], [2, 5, 3]]
test3 = [[1, 2, 1], [1, 2, 2], [1, 2, 3]]
print(getSkyLine(test1))
