from typing import List


class Node(object):
    def __init__(self, next: "Node", height: int) -> None:
        self.next = next
        self.height = height


def insertNode(head: Node, new_node: Node) -> Node:
    if new_node.height > head.height:
        new_node.next = head
        head = new_node
        return head

    current = head
    while current.next:
        if new_node.height > current.next.height:
            break

    new_node.next = current.next
    current.next = new_node
    return head


def removeNode(head: Node, height: int) -> Node:
    if head.height == height:
        head = head.next
        return head

    current = head
    while current.next:
        if current.next.height == height:
            break

    current.next = current.next.next
    return head


def getSkyLine(buildings: List[list[int]]) -> List[List[int]]:
    head = Node(None, 0)
    skyline_limit = buildings[-1][-2] + 1

    skyline = [[] for i in range(skyline_limit)]
    print(skyline)

    for b in buildings:
        skyline[b[0]].append([b[2], "L"])
        skyline[b[1]].append([b[2], "R"])

    for i, h in enumerate(skyline):
        if h == []:
            skyline[i] = head.height
            continue

        for j in h:
            if j[1] == "L":
                head = insertNode(head, Node(None, j[0]))
                skyline[i] = head.height
                continue

            head = removeNode(head, j[0])
            skyline[i] = head.height

    result = []
    last = 0
    for i, h in enumerate(skyline):
        if h != last:
            result.append([i, h])
            last = h

    return result


test1 = [[2, 9, 10], [3, 7, 15], [5, 12, 12], [15, 20, 10], [19, 24, 8]]
test2 = [[0, 2, 3], [2, 5, 3]]
print(getSkyLine(test1))
