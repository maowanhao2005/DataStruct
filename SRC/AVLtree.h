#include <stdio.h>
#include <stdlib.h>

/*AVL树删除节点的算法描述
AVL树是一种自平衡二叉搜索树，删除节点后需要重新平衡树以保持其高度平衡的特性。以下是删除节点的详细步骤：

查找并删除节点：

使用标准二叉搜索树的删除方法找到并删除目标节点。
如果目标节点没有子节点，直接删除。
如果目标节点有一个子节点，用该子节点替换目标节点。
如果目标节点有两个子节点，用右子树的最小节点（或左子树的最大节点）替换目标节点，并删除该最小节点。
更新高度：

从删除节点的位置开始，向上更新每个节点的高度。
重新平衡：

在更新高度的过程中，检查每个节点的平衡因子（左子树高度减去右子树高度）。
如果平衡因子不在[-1, 1]范围内，进行相应的旋转操作以恢复平衡：
LL旋转：左子树的左子树过重，进行单右旋。
RR旋转：右子树的右子树过重，进行单左旋。
LR旋转：左子树的右子树过重，先进行左旋再进行右旋。
RL旋转：右子树的左子树过重，先进行右旋再进行左旋。
*/

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
    } 
    else {
        // 没有子节点或只有一个子节点
        if (root->left == NULL) {
            AVLNode* temp = root->right;
            free(root);
            return temp;
        } 
        else if (root->right == NULL) {
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

// int main() {
//     AVLNode* root = createNode(33);
//     root->left = createNode(15);
//     root->right = createNode(50);
//     root->left->left = createNode(10);
//     root->left->right = createNode(20);
//     root->right->left = createNode(40);
//     root->right->right = createNode(60);

//     printf("原始树的中序遍历: ");
//     inorderTraversal(root);
//     printf("\n");

//     root = deleteNode(root, 33); // 删除根节点

//     printf("删除根节点后的中序遍历: ");
//     inorderTraversal(root);
//     printf("\n");

//     return 0;
// }

/*代码说明
创建新节点：createNode 函数用于创建一个新的AVL树节点。
获取高度：getHeight 函数返回节点的高度。
更新高度：updateHeight 函数更新节点的高度。
获取平衡因子：getBalanceFactor 函数计算节点的平衡因子。
旋转操作：rightRotate 和 leftRotate 函数分别实现右旋和左旋操作。
查找最小值节点：findMin 函数查找右子树中的最小值节点。
删除节点：deleteNode 函数实现删除节点并重新平衡树的操作。
中序遍历：inorderTraversal 函数用于中序遍历树，验证删除操作是否正确。
通过这些步骤和函数，可以确保在删除节点后AVL树仍然保持平衡。
*/