#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define deg 4
typedef struct Node {
    int array[deg];
    struct Node* children[deg+1];
    int keys;
}Node;

typedef struct temp {
    int n;
    Node* child1;
    Node* child2;
}temp;
Node* CreateNode(int n){
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->keys=1;
    newNode->array[0]=n;
    for (int i=0;i<deg+1;i++){
        newNode->children[i]=NULL;
    }
    return newNode;
}

temp* SplitNode(Node* root, Node* node){
    int n=node->array[0];
    Node* child1=(Node*)malloc(sizeof(Node));
    Node* child2=(Node*)malloc(sizeof(Node));
    for (int i=0;i<deg+1;i++){
        child2->children[i]=NULL;
        child1->children[i]=NULL;
    }
    int parentElement;
    if (n<root->array[0]){
        
        for (int i=0;i<(deg/2)-1;i++){
            child1->array[i+1]=root->array[i];
            child1->children[i+2]=root->children[i+1];
            child1->children[i+1]=root->children[i];
        }
        child1->keys=deg/2;
        parentElement=root->array[deg/2-1];
        for (int i=deg/2;i<deg;i++){
            child2->array[i-(deg/2)]=root->array[i];
            child2->children[i-(deg/2)]=root->children[i];
            child2->children[i-(deg/2)+1]=root->children[i+1];
        }
        child1->array[0]=n;
        child1->children[0]=node->children[0];
        child1->children[1]=node->children[1];
        child2->keys=deg/2;
    }
    else if (n>root->array[deg-1]){
        for (int i=0;i<deg/2;i++){
            child1->array[i]=root->array[i];
            child1->children[i]=root->children[i];
            child1->children[i+1]=root->children[i+1];
        }
        child1->keys=deg/2;
        parentElement=root->array[deg/2];
        for (int i=deg/2+1;i<deg;i++){
            child2->array[i-(deg/2+1)]=root->array[i];
            child2->children[i-(deg/2+1)]=root->children[i];
            child2->children[i-(deg/2+1)+1]=root->children[i+1];
        }
        child2->array[deg/2-1]=n;
        child2->children[deg/2-1]=node->children[0];
        child2->children[deg/2]=node->children[1];
        child2->keys=deg/2;
    }
    for (int i=0;i<deg/2-1;i++){
        if (n>root->array[i] && n<root->array[i+1]){
            int t=0;
            for (int j=0;j<deg/2;j++){
                child1->array[t]=root->array[j];
                child1->children[t]=root->children[j];
                child1->children[t+1]=root->children[j+1];
                if (t==i+1){
                    child1->array[t]=n;
                    child1->children[t]=node->children[0];
                    child1->children[t+1]=node->children[1];
                    if (j!=deg/2-1){
                        j--;
                    }
                }
                t++;
            }
            child1->keys=deg/2;
            parentElement=root->array[deg/2-1];
            for (int j=deg/2;j<deg;j++){
                child2->array[j-(deg/2)]=root->array[j];
                child2->children[j-(deg/2)]=root->children[j];
                child2->children[j-(deg/2)+1]=root->children[j+1];
            }
            child2->keys=deg/2;
        }
    }
    if (n>root->array[deg/2-1] && n<root->array[deg/2]){
        child1->keys=deg/2;
        for (int i=0;i<deg/2;i++){
            child1->array[i]=root->array[i];
            child1->children[i]=root->children[i];
            child1->children[i+1]=root->children[i+1];
        }
        for (int i=deg/2;i<deg;i++){
            child2->array[i-(deg/2)]=root->array[i];
            child2->children[i-(deg/2)]=root->children[i];
            child2->children[i-(deg/2)+1]=root->children[i+1];
        }
        child1->children[deg/2-1]=node->children[0];
        child2->children[0]=node->children[1];
        child2->keys=deg/2;
        parentElement=n;
    }
    for (int i=deg/2; i<deg-1;i++){
        if (n>root->array[i] && n<root->array[i+1]){
            int t=0;
            for (int j=deg/2;j<deg;j++){
                child2->array[t]=root->array[j];
                child2->children[t]=root->children[j];
                child2->children[t+1]=root->children[j+1];
                if (t==i-deg/2){
                    child2->array[t]=n;
                    child2->children[t]=node->children[0];
                    child2->children[t+1]=node->children[1];
                    if (j!=deg/2){
                        j--;
                    }
                }
                t++;
            }
            child2->keys=deg/2;
            parentElement=root->array[deg/2];
            for (int j=0;j<deg/2;j++){
                child1->array[j]=root->array[j];
                child1->children[j]=root->children[j];
                child1->children[j+1]=root->children[j+1];
            }
            child1->keys=deg/2;
        }
    }
    temp* result=(temp*)malloc(sizeof(temp));
    result->n=parentElement;
    result->child1=child1;
    result->child2=child2;
    return result;
}
int SearchElement(int n, Node* root){
    if (root==NULL){
        return 0;
    }
    int present=0;
    for (int i=0;i<root->keys;i++){
        if (root->array[i]==n){
            present=1;
            break;
        }
        else if (root->array[0]>n){
            if (root->children[0]!=NULL){
                present=SearchElement(n, root->children[0]);
                break;
            }
        }
        else if (i==root->keys-1){
            if (root->array[i]<n){
                if (root->children[i+1]!=NULL){
                    present=SearchElement(n, root->children[i+1]);
                    break;
                }
            }
        }
        else if (root->array[i+1]>n && root->array[i]<n){
            if (root->children[i+1]!=NULL){
                present=SearchElement(n, root->children[i+1]);
                break;
            }
        }
    }
    return present;
}

Node* InsertElement(int n, Node* root){
    Node* result;
    if (root==NULL){
        root=CreateNode(n);
        return root;
    }
    int leaf=1;
    for (int i=0;i<root->keys+1;i++){
        if (root->children[i]!=NULL){
            leaf=0;
            break;
        }
    }
    if (!leaf){
        if (n<root->array[0]){
            result=InsertElement(n,root->children[0]);
        }
        if (n>root->array[root->keys-1]){
            result=InsertElement(n,root->children[root->keys]);
        }
        for (int i=0;i<root->keys-1;i++){
            if (n>root->array[i] && n<root->array[i+1]){
                result=InsertElement(n, root->children[i+1]);
                break;
            }
        }
        if (result->keys==1){
            if (root->keys<deg){
                int ind=0;
                for (int i=0;i<root->keys+1;i++){
                    if (root->children[i]!=NULL){
                        ind=i;
                    }
                }
                root->children[ind]=result->children[0];
                root->children[ind+1]=result->children[1];
                root->array[root->keys]=result->array[0];
                root->keys++;
                result=root;
            }
            else {
                temp* newTemp=SplitNode(root, result);
                Node* child1=newTemp->child1;
                Node* child2=newTemp->child2;
                int parentElement=newTemp->n;
                Node* newNode=CreateNode(parentElement);
                newNode->children[0]=child1;
                newNode->children[1]=child2;
                newNode->keys=1;
                result=newNode;
            }
        }
        else {
            result=root;
        }
    }
    else {
        if (root->keys<deg){
            int k=n<root->array[0]?0:root->keys;
            for (int i=0;i<root->keys-1;i++){
                if (n>root->array[i] && n<root->array[i+1]){
                    k=i+1;
                    break; 
                }
            }
            for (int i=root->keys;i>k;i--){
                root->array[i]=root->array[i-1];
            }
            root->array[k]=n;
            root->keys++;
            result=root;
        }
        else {
            Node* tempNode=CreateNode(n);
            temp* newTemp=SplitNode(root, tempNode);
            int parentElement=newTemp->n;
            Node* newNode=CreateNode(parentElement);
            newNode->children[0]=newTemp->child1;
            newNode->children[1]=newTemp->child2;
            newNode->keys=1;
            result=newNode;
        }
    }   
    return result;
}

void levelOrder(Node* root) {
    if (root == NULL) return;

    Node* queue[1000];
    int level[1000];
    int front = 0, rear = 0;
    int currLevel = 0;

    queue[rear] = root;
    level[rear++] = 0;

    while (front < rear) {
        Node* curr = queue[front];
        int nodeLevel = level[front++];
        if (nodeLevel > currLevel) {
            printf("\n");
            currLevel = nodeLevel;
        }
        printf("|");
        for (int i = 0; i < curr->keys; i++)
            printf("%d ", curr->array[i]);
        printf("| ");

        for (int i = 0; i <= curr->keys; i++) {
            if (curr->children[i] != NULL) {
                queue[rear] = curr->children[i];
                level[rear++] = nodeLevel + 1;
            }
        }
    }
    printf("\n");
}


int main(){
    printf("1) Insert Element\n2) Search Element\n3) Print B-Tree\n4) Exit\n");
    Node*root=NULL;
    int choice, n;
    root = InsertElement(10, root);
    levelOrder(root);
    while (1) {
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter the element to insert: ");
                scanf("%d", &n);
                root = InsertElement(n, root);
                break;
            case 2:
                printf("Enter the element to search: ");
                scanf("%d", &n);
                if (SearchElement(n, root)) {
                    printf("Element %d found in the B-Tree.\n", n);
                } else {
                    printf("Element %d not found in the B-Tree.\n", n);
                }
                break;
            case 3:
                printf("B-Tree elements in level order: ");
                levelOrder(root);
                printf("\n");
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}