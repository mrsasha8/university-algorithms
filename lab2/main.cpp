#include <vector>

class binomialHeap {
public:
    void insert(float data) {insertPrivate(data);}
    bool search(float data) {
        if(searchPrivate(data) == nullptr) return false;
        else return true;
    }
    void remove(float data) {removePrivate(data);}
    float findMin() {return findMinPrivate()->data;}
    void removeMin() {removeMinPrivate();}
private:
    struct node {
        float data = 0;
        int order = 0;
        node *parent = nullptr;
        std::vector<node *> children;
    };

    std::vector<node *> binomialHeapPrivate;

    bool insertPrivate(float data) {
        auto tempTree = new node;
        tempTree->data = data;
        for (int i = 0; i < binomialHeapPrivate.size(); i++) {
            if (binomialHeapPrivate[i] == nullptr) {
                binomialHeapPrivate[i] = tempTree;
                organizePrivate();
                return true;
            }
        }
        addTreePrivate(tempTree);
        organizePrivate();
        return true;
    }

    node *searchPrivate(float data) {
        for (int i = 0; i < binomialHeapPrivate.size(); i++) {
            if (binomialHeapPrivate[i] != nullptr) {
                auto temp = searchRecursive(data, binomialHeapPrivate[i]);
                if (temp != nullptr) return temp;
            }
        }
        return nullptr;
    }

    void removePrivate(float data) {
        auto nodeToRemove = searchPrivate(data);
        for(int i=0; i<nodeToRemove->children.size(); i++) {
            if(nodeToRemove->children[i] != nullptr) {
                nodeToRemove->children[i]->parent = nullptr;
                addTreePrivate(nodeToRemove->children[i]);
            }
        }
        if(nodeToRemove->parent != nullptr) {
            for(int i=0; i<nodeToRemove->parent->children.size(); i++) {
                if(nodeToRemove->parent->children[i] == nodeToRemove) {
                    nodeToRemove->parent->children[i] = nullptr;
                    break;
                }
            }
            fixTreeAfterRemovingElementRecursive(nodeToRemove->parent);
        }
        delete nodeToRemove;
        organizePrivate();
    }

    node *findMinPrivate() {
        auto tempNode = binomialHeapPrivate[0];
        float tempMin = binomialHeapPrivate[0]->data;
        for (int i = 1; i < binomialHeapPrivate.size(); i++) {
            if (binomialHeapPrivate[i] != nullptr) {
                if (binomialHeapPrivate[i]->data < tempMin) {
                    tempNode = binomialHeapPrivate[i];
                    tempMin = binomialHeapPrivate[i]->data;
                }
            }
        }
        return tempNode;
    }

    void removeMinPrivate() {
        auto nodeToRemove = findMinPrivate();
        for(int i=0; i<binomialHeapPrivate.size(); i++) {
            if(binomialHeapPrivate[i] == nodeToRemove) {
                binomialHeapPrivate[i] = nullptr;
                break;
            }
        }
        for(int i=0; i<nodeToRemove->children.size(); i++) {
            nodeToRemove->children[i]->parent = nullptr;
            addTreePrivate(nodeToRemove->children[i]);
        }
        delete nodeToRemove;
        organizePrivate();
    }

    node *searchRecursive(float data, node *root) {
        if(root == nullptr) return nullptr;
        else if(root->data == data) return root;
        else {
            for (int i = 0; i < root->children.size(); i++) {
                if (root->children[i] != nullptr) {
                    auto temp = searchRecursive(data, root->children[i]);
                    if(temp != nullptr) return temp;
                }
            }
            return nullptr;
        }
    }

    void fixTreeAfterRemovingElementRecursive(node *root) {
        for(int i=0; i<root->children.size(); i++) {
            if(root->children[i] != nullptr) {
                root->children[i]->parent = nullptr;
                addTreePrivate(root->children[i]);
            }
        }
        root->children.clear();
        if(root->parent != nullptr) {
            for(int i=0; i<root->parent->children.size(); i++) {
                if(root->parent->children[i] == root) {
                    root->parent->children[i] = nullptr;
                    break;
                }
            }
            fixTreeAfterRemovingElementRecursive(root->parent);
            root->parent = nullptr;
            addTreePrivate(root);
        }
        root->order = 0;
        organizePrivate();
    }

    node *mergeTreesPrivate(node *a, node *b) {
        if(a->data > b->data) std::swap(a, b);
        b->parent = a;
        for(int i=0; i<a->children.size(); i++) {
            if(a->children[i] == nullptr) {
                a->children[i] = b;
                a->order = a->order + 1;
                return a;
            }
        }
        a->children.push_back(b);
        a->order = a->order + 1;
        return a;
    }

    bool addTreePrivate(node *root) {
        for(int i=0; i<binomialHeapPrivate.size(); i++) {
            if(binomialHeapPrivate[i] == nullptr) {
                binomialHeapPrivate[i] = root;
                return true;
            }
        }
        binomialHeapPrivate.push_back(root);
        return true;
    }

    void organizePrivate() {
        while(true) {
            bool flag = false;
            if(binomialHeapPrivate.size() == 1) break;
            else {
                for(int i=0; i<binomialHeapPrivate.size(); i++) {
                    if(i == binomialHeapPrivate.size() - 1) break;
                    else if(binomialHeapPrivate[i] != nullptr) {
                        for(int y=i+1; y<binomialHeapPrivate.size(); y++) {
                            if(binomialHeapPrivate[y] != nullptr) {
                                if (binomialHeapPrivate[i]->order == binomialHeapPrivate[y]->order) {
                                    binomialHeapPrivate[i] = mergeTreesPrivate(binomialHeapPrivate[i], binomialHeapPrivate[y]);
                                    binomialHeapPrivate[y] = nullptr;
                                    flag = true;
                                }
                            }
                        }
                    }
                }
            }
            if(flag) continue;
            break;
        }
        while(true) {
            if(binomialHeapPrivate.back() == nullptr) binomialHeapPrivate.pop_back();
            else break;
        }
    }
};

int main() {
    binomialHeap testHeap;

    testHeap.insert(4);
    testHeap.insert(7.8);
    testHeap.insert(9.09);
    testHeap.insert(10);
    testHeap.insert(11.4567);
    testHeap.insert(5.6);
    testHeap.insert(4.3);
    testHeap.insert(4.1);
    testHeap.insert(123);

    bool testBool1 = testHeap.search(10);
    bool testBool2 = testHeap.search(5.6);
    bool testBool3 = testHeap.search(11);

    float testMin = testHeap.findMin();
    testHeap.removeMin();

    testHeap.remove(10);
    bool testBool4 = testHeap.search(10);

    return 0;
}
