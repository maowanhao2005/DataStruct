#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode {
    int val;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

// 创建新节点
AVLNode* createNode(int val) {
    AVLNode* newNode = (AVLNode*)malloc(sizeof(AVLNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1; // 新节点初始高度为1
    return newNode;
}

// 获取节点的高度
int getHeight(AVLNode* node) {
    if (node == NULL) return 0;
    return node->height;
}

// 更新节点的高度
void updateHeight(AVLNode* node) {
    if (node != NULL) {
        node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));
    }
}

// 获取平衡因子
int getBalanceFactor(AVLNode* node) {
    if (node == NULL) return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// 右旋
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

// 左旋
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

// 查找最小值节点
AVLNode* findMin(AVLNode* node) {
    while (node && node->left != NULL) {
        node = node->left;
    }
    return node;
}

// 删除节点
AVLNode* deleteNode(AVLNode* root, int key) {
    if (root == NULL) return root;

    if (key < root->val) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->val) {
        root->right = deleteNode(root->right, key);
    } else {
        // 没有子节点或只有一个子节点
        if (root->left == NULL) {
            AVLNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            AVLNode* temp = root->left;
            free(root);
            return temp;
        }

        // 有两个子节点，找到右子树的最小值节点
        AVLNode* temp = findMin(root->right);
        root->val = temp->val;
        root->right = deleteNode(root->right, temp->val);
    }

    // 如果树中只有一个节点，直接返回
    if (root == NULL) return root;

    // 更新高度
    updateHeight(root);

    // 获取平衡因子
    int balance = getBalanceFactor(root);

    // LL旋转
    if (balance > 1 && getBalanceFactor(root->left) >= 0) {
        return rightRotate(root);
    }

    // RR旋转
    if (balance < -1 && getBalanceFactor(root->right) <= 0) {
        return leftRotate(root);
    }

    // LR旋转
    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL旋转
    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// 中序遍历
void inorderTraversal(AVLNode* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->val);
        inorderTraversal(root->right);
    }
}

int main() {
    AVLNode* root = createNode(33);
    root->left = createNode(15);
    root->right = createNode(50);
    root->left->left = createNode(10);
    root->left->right = createNode(20);
    root->right->left = createNode(40);
    root->right->right = createNode(60);

    printf("原始树的中序遍历: ");
    inorderTraversal(root);
    printf("\n");

    root = deleteNode(root, 33); // 删除根节点

    printf("删除根节点后的中序遍历: ");
    inorderTraversal(root);
    printf("\n");

    return 0;
}