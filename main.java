import java.util.Scanner;

class BinarySearchTree {

    class Node {
        Node left, right, parent;
        int key;
        String data;
        
        Node(int key) {
            this.key = key;
            this.left = this.right = this.parent = null;
        }
    }

    private Node root;

    public BinarySearchTree() {
        root = null;
    }

    public boolean isEmpty() {
        return root == null;
    }

    public void inOrderTreeWalk(Node x) {
        if (x != null) {
            inOrderTreeWalk(x.left);
            System.out.print(" " + x.key + " ");
            inOrderTreeWalk(x.right);
        }
    }

    public void treeInsert(int key) {
        Node z = new Node(key);
        Node y = null;
        Node x = root;
        while (x != null) {
            y = x;
            if (z.key < x.key)
                x = x.left;
            else
                x = x.right;
        }
        z.parent = y;
        if (y == null)
            root = z;
        else if (z.key < y.key)
            y.left = z;
        else
            y.right = z;
    }

    public void preOrderTreeWalk(Node x) {
        if (x != null) {
            System.out.println(x.key);
            preOrderTreeWalk(x.left);
            preOrderTreeWalk(x.right);
        }
    }

    public void postOrderTreeWalk(Node x) {
        if (x != null) {
            postOrderTreeWalk(x.left);
            postOrderTreeWalk(x.right);
            System.out.println(x.key);
        }
    }

    public Node maximum(Node x) {
        while (x.right != null) {
            x = x.right;
        }
        return x;
    }

    public void removeMax(Node x) {
        if (x != null) {
            Node maxNode = maximum(x);
            if (maxNode.parent != null) {
                if (maxNode.parent.right == maxNode) {
                    maxNode.parent.right = maxNode.left;
                } else {
                    maxNode.parent.left = maxNode.left;
                }
            } else {
                root = maxNode.left;
            }
            if (maxNode.left != null) {
                maxNode.left.parent = maxNode.parent;
            }
        }
    }

    public Node minimum(Node x) {
        while (x.left != null) {
            x = x.left;
        }
        return x;
    }

    public Node successor(Node x) {
        if (x == null)
            return null;
        if (x.right != null) {
            return minimum(x.right);
        }
        Node successor = null;
        Node current = root;
        while (current != null) {
            if (x.key < current.key) {
                successor = current;
                current = current.left;
            } else if (x.key > current.key) {
                current = current.right;
            } else {
                break;
            }
        }
        return successor;
    }

    public Node treeDelete(int key) {
        Node current = root;
        Node parent = null;
        while (current != null && current.key != key) {
            parent = current;
            if (key < current.key) {
                current = current.left;
            } else {
                current = current.right;
            }
        }
        if (current == null) {
            System.out.println("Node with key " + key + " not found.");
            return root;
        }
        if (current.left == null && current.right == null) {
            if (parent == null) {
                root = null;
            } else if (parent.left == current) {
                parent.left = null;
            } else {
                parent.right = null;
            }
        } else if (current.left == null || current.right == null) {
            Node child = (current.left != null) ? current.left : current.right;
            if (parent == null) {
                root = child;
            } else if (parent.left == current) {
                parent.left = child;
            } else {
                parent.right = child;
            }
        } else {
            Node successor = minimum(current.right);
            current.key = successor.key;
            current.data = successor.data;
            if (successor.parent.left == successor) {
                successor.parent.left = successor.right;
            } else {
                successor.parent.right = successor.right;
            }
        }
        return root;
    }

    public static void main(String[] args) {
        BinarySearchTree bst = new BinarySearchTree();
        Scanner sc = new Scanner(System.in);
        int choice, key;
        while (true) {
            System.out.println();
            System.out.println(" Binary Search Tree Example ");
            System.out.println(" ----------------------------- ");
            System.out.println(" 1. Insertion ");
            System.out.println(" 2. In-Order Traversal ");
            System.out.println(" 3. Pre-Order Traversal ");
            System.out.println(" 4. Post-Order Traversal ");
            System.out.println(" 5. Find Maximum ");
            System.out.println(" 6. Remove Maximum ");
            System.out.println(" 7. Find Minimum ");
            System.out.println(" 8. Find Successor ");
            System.out.println(" 9. Delete a node ");
            System.out.println(" 10. Exit ");
            System.out.print(" Enter your choice : ");
            choice = sc.nextInt();
            switch (choice) {
                case 1:
                    System.out.print(" Enter key (int value) to be inserted : ");
                    key = sc.nextInt();
                    bst.treeInsert(key);
                    break;
                case 2:
                    System.out.println();
                    System.out.println(" In-Order Traversal ");
                    System.out.println(" -------------------");
                    bst.inOrderTreeWalk(bst.root);
                    break;
                case 3:
                    System.out.println();
                    System.out.println(" Pre-Order Traversal ");
                    System.out.println(" -------------------");
                    bst.preOrderTreeWalk(bst.root);
                    break;
                case 4:
                    System.out.println();
                    System.out.println(" Post-Order Traversal ");
                    System.out.println(" -------------------");
                    bst.postOrderTreeWalk(bst.root);
                    break;
                case 5:
                    if (!bst.isEmpty()) {
                        Node maxNode = bst.maximum(bst.root);
                        System.out.println(" Maximum key: " + maxNode.key);
                    } else {
                        System.out.println(" The tree is empty.");
                    }
                    break;
                case 6:
                    bst.removeMax(bst.root);
                    System.out.println(" Maximum node removed.");
                    break;
                case 7:
                    if (!bst.isEmpty()) {
                        Node minNode = bst.minimum(bst.root);
                        System.out.println(" Minimum key: " + minNode.key);
                    } else {
                        System.out.println(" The tree is empty.");
                    }
                    break;
                case 8:
                    System.out.print(" Enter key to find the successor of: ");
                    key = sc.nextInt();
                    Node current = bst.root;
                    while (current != null && current.key != key) {
                        if (key < current.key)
                            current = current.left;
                        else
                            current = current.right;
                    }
                    if (current != null) {
                        Node successor = bst.successor(current);
                        if (successor != null) {
                            System.out.println(" Successor of " + key + " is " + successor.key);
                        } else {
                            System.out.println(" No successor found for " + key);
                        }
                    } else {
                        System.out.println(" Node with key " + key + " not found.");
                    }
                    break;
                case 9:
                    System.out.print(" Enter key to delete: ");
                    key = sc.nextInt();
                    bst.treeDelete(key);
                    break;
                case 10:
                    sc.close();
                    return;
                default:
                    System.out.println("Invalid choice");
            }
        }
    }
}

