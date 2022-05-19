from collections import deque


class Node:
    def __init__(self, key):
        self.key = key
        self.left = None
        self.right = None
        self.height = 1


class AVLTree:
    def __init__(self):
        self.root = None

    def get_root(self):
        return self.root

    def insert(self, key):
        self.root = self._insert(self.root, key)

    # insert a key in the subtree rooted with "node"
    # returns the new root of the subtree
    def _insert(self, node: Node, key) -> Node:
        # Step 1. Perform the insertion like in simple Binary Search Trees.
        if node is None:
            return Node(key)

        if key < node.key:
            left_sub_root = self._insert(node.left, key)
            node.left = left_sub_root
        elif key > node.key:
            right_sub_root = self._insert(node.right, key)
            node.right = right_sub_root
        else:
            return node

        # Step 2. Update height of this ancestor
        node.height = self.get_max_height(node.left, node.right) + 1

        # Step 3. Check the balance factor of this ancestor
        balance_factor = self.get_balance_factor(node)

        # Step 4. If the subtree is unbalanced, check in which case we are, and balance!

        # Case 1. LEFT LEFT CASE
        if balance_factor > 1 and key < node.left.key:
            print("Case 1. LEFT LEFT")

            return self.right_rotate(node)

        # Case 2. LEFT RIGHT CASE
        if balance_factor > 1 and key > node.left.key:
            print("Case 2. LEFT RIGHT")

            node.left = self.left_rotate(node.left)
            return self.right_rotate(node)

        # Case 3. RIGHT RIGHT CASE
        if balance_factor < -1 and key > node.right.key:
            print("Case 3. RIGHT RIGHT")

            return self.left_rotate(node)

        # Case 4. RIGHT LEFT CASE
        if balance_factor < -1 and key < node.right.key:
            print("Case 4. RIGHT LEFT")

            node.right = self.right_rotate(node.right)
            return self.left_rotate(node)

        return node  # case when the node did not change

    def get_max_height(self, left: Node, right: Node) -> int:
        left_height, right_height = 0, 0
        if left is not None:
            left_height = left.height
        if right is not None:
            right_height = right.height
        return max(left_height, right_height)

    def get_balance_factor(self, node: Node) -> int:
        if node is None:
            return 0

        left_height, right_height = 0, 0
        if node.left:
            left_height = node.left.height
        if node.right:
            right_height = node.right.height
        return left_height - right_height

    def right_rotate(self, y: Node) -> Node:
        print("Right rotation in node", y.key)
        x = y.left
        t2 = x.right
        x.right = y
        y.left = t2
        y.height = self.get_max_height(y.left, y.right) + 1
        x.height = self.get_max_height(x.left, x.right) + 1
        return x

    def left_rotate(self, x: Node) -> Node:
        print("Left rotation in node", x.key)
        y = x.right
        t2 = y.left
        y.left = x
        x.right = t2
        x.height = self.get_max_height(x.left, x.right) + 1
        y.height = self.get_max_height(y.left, y.right) + 1
        return y


# Level Order: Prints the tree floor-by-floor
def level_order(my_tree: AVLTree):
    root = my_tree.get_root()
    if root is None:
        return
    queue = deque()
    queue.append(root)
    while len(queue):
        node = queue.popleft()
        print(node.key, end=' ')

        if node.left is not None:
            queue.append(node.left)

        if node.right is not None:
            queue.append(node.right)

    print()


awl_tree = AVLTree()
data = [90, 80, 70, 60, 50, 75]

for elem in data:
    print("INSERT", elem)
    awl_tree.insert(elem)
    level_order(awl_tree)
