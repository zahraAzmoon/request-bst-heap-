#include <iostream>
#include <string>
using namespace std;

struct Node{
    int id;
    string name;
    Node* left;
    Node* right;
    Node* parent;

    Node(int id, string name){
       this->id=id;
        this->name=name;
        left=right=parent=nullptr;
    }

};

class Tree{
public:
    Node* root=nullptr;

      void tree_insert(Node* z){
          Node* y=nullptr;
          Node* x=root;
          while (x!=nullptr){
              y=x;
              if (z->id<x->id)
                  x=x->left;
              else
                  x=x->right;
          }
          z->parent= y;
          if (y == nullptr)
              root=z;
          else if (z->id<y->id)
              y->left=z;
          else
              y->right=z;
      }

      Node* tree_search(Node* x, int k) {
          if (x== nullptr||k == x->id)
              return x;
          if (k < x->id)
              return tree_search(x->left, k);
          else
              return tree_search(x->right, k);
      }

      Node* tree_minimum(Node* x) {
          while (x->left != nullptr)
              x=x->left;
          return x;
      }

      void transplant(Node* u, Node* v) {
          if (u->parent == nullptr)
              root = v;
          else if (u == u->parent->left)
              u->parent->left =v;
          else
              u->parent->right =v;
          if (v != nullptr)
              v->parent = u->parent;
      }

      void tree_delete(int id) {
          Node* z = tree_search(root, id);
          if (z == nullptr) return;
            //  cout << "empty"<<endl;
          if (z->left == nullptr)
              transplant(z, z->right);
          else if (z->right == nullptr)
              transplant(z, z->left);
          else {
              Node* y = tree_minimum(z->right);
              if (y->parent != z) {
                  transplant(y, y->right);
                  y->right = z->right;
                  y->right->parent = y;
              }
              transplant(z, y);
              y->left = z->left;
              y->left->parent = y;
          }
          delete z;
      }

      void preorder_traversal(Node* node) {
          if (node == nullptr) return;
          cout << "id : " << node->id << ", name: " << node->name <<endl;
          preorder_traversal(node->left);
          preorder_traversal(node->right);
      }

};

struct HeapNode { 
    int id; 
    int priority; 
    HeapNode(int id = -1, int priority = -1) {
        this->id = id;
        this->priority = priority;
    }

};

class MaxHeap {
public:
    HeapNode heap[100]; 
    int size=0;

      int parent(int i){
          return i/2;
      }
      int left(int i){ 
          return 2*i;
      }
      int right(int i){ 
          return 2*i+1;
      }

      void max_heapify(int i){
          int l=left(i);
          int r=right(i);
          int largest=i;

          if (l<=size && heap[l].priority>heap[largest].priority)
              largest=l;
          if (r<=size && heap[r].priority>heap[largest].priority)
              largest=r;

          if (largest!=i){
              swap(heap[i],heap[largest]);
              max_heapify(largest);
          }
      }

      void max_heap_insert(int id,int priority){
          size++;
          int i=size;
          heap[i].id=id;
          heap[i].priority=-1;
          heap_increase_key(i,priority);
      }

      void heap_increase_key(int i,int key){
          if (key < heap[i].priority) {
              cout <<"new key is smaller than current key"<<endl;
              return;
          }
          heap[i].priority=key;//?
          while(i>1 && heap[parent(i)].priority<heap[i].priority) {
              swap(heap[i],heap[parent(i)]);
              i=parent(i);
          }
      }

      HeapNode heap_extract_max(){
          if (size<1){
              cout << "heap undrerflow"<<endl;
              return {-1,-1};
          }
          HeapNode max=heap[1];
          heap[1]=heap[size];
          size--;
          max_heapify(1);
          return max;
      }

      bool is_empty(){
          return size==0;
      }

      void delete_by_id(int id){
          for (int i=1; i<=size;i++){
              if (heap[i].id==id) {
                  heap[i]=heap[size];
                  size--;
                  max_heapify(i);
                  break;
              }
          }
      }
      
      void print_max_heap(){
          for (int i=1; i<=size; i++){
              cout << "id: "<< heap[i].id<< "  Priority: "<<heap[i].priority<<endl;
          }
          cout<<endl;
      }

};

int main(){
    Tree bst;
    MaxHeap heap;

    int choice;
    while (true){
        cout << "a list of task" << endl;
        cout << "1- add request " << endl;
        cout << "2- search request " << endl;
        cout << "3- delete request " << endl;
        cout << "4- higher priority " << endl;
        cout << "5-show bst " << endl;
        cout << "6-show maxhap " << endl;
        cout << "7-exit " << endl;
        cout << "please enter a number between 1 to 7 : "<<endl;
        cout << "____________________________________________" << endl;
        cin >> choice;
        // امتحان میکنیم
        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000);
            cout << "pleas enter between 1 to 7" << endl;
            continue;
        }
        // تا اینجا
        if (choice == 7) break;
       
        int id, priority;
        string name;

        switch (choice){
        case 1:
            cout << "*isert*" << endl;
            cout << "id: ";
            cin >> id;
            cout << "name: ";
            cin.ignore();
            getline(cin, name);
            cout << "priority: ";
            cin >> priority;
            bst.tree_insert(new Node(id, name));
            heap.max_heap_insert(id, priority);
            cout << "_______________________" << endl;
            break;

        case 2:
            cout << "id for searching: ";
            cin >> id;
            {
            Node* searching = bst.tree_search(bst.root, id);
           // if (bst.tree_search(bst.root, id))
                 if (searching) {
                       cout << "request is founding" << endl;//oooo
                       cout << "id:" << searching->id << "   name:" << searching->name << endl;
                  }
                 else {
                      cout << "request not found" << endl;
                 }
            }
            cout << "_______________________" << endl;

                break;

        case 3:
            cout << "id foe delete: ";
            cin >> id;
            heap.delete_by_id(id);
            bst.tree_delete(id);
            break;
            cout << "_______________________" << endl;


        case 4:
            if (heap.is_empty()) {
                cout << "empty";
            }
            else {
                HeapNode max = heap.heap_extract_max();
                bst.tree_delete(max.id);
                cout << "id for higher priority = " << max.id << endl;
            }
            cout << "_______________________" << endl;

            break;

        case 5:
            cout << "bst:" << endl;
            bst.preorder_traversal(bst.root);
            cout << endl;
            cout << "_______________________" << endl;

            break;

        case 6:
            heap.print_max_heap();
            cout << "_______________________" << endl;

            break;
         
       // case 7:
         //   cout << "exiting" << endl;
          //  break;
        default:
            cout << "invalid" << endl;

        }
    }
}