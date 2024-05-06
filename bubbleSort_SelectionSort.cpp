#include <iostream>
#include <chrono>
#include <random>
#include <cstdlib>

using namespace std;

typedef struct Node {
    int iPayload; 
    Node* ptrNext;
    Node* ptrPrev;
} Node;

// Funções para Lista
Node* createNode(int);
void displayList(Node*);
void insertEnd(Node**, int);
void deleteList(Node**);
void swapValue(Node**, Node**);
void listBubbleSort(Node**, int);
void optimizedListBubbleSort(Node**, int);
void listSelectionSort(Node**, int);
void optimizedListSelectionSort(Node**, int);

// Funções para array
void swapValue(int&, int&);
void printArray(int[], int);
void bubbleSort(int[], int);
void optimizationBubbleSort(int[], int);
void selectionSort(int[], int);
void optimizedSelectionSort(int[], int);

int main()
{
    srand(time(nullptr)); // Seed para números aleatórios

    // Tamanhos das listas a serem testadas
    int sizes[] = {1000, 5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000};

    cout << "Teste para algorítmo BubbleSort" << endl << endl;

    for (int size : sizes) {
        Node* head1 = nullptr;
        Node* head2 = nullptr;

        // Criar listas aleatórias
        for (int i = 0; i < size; i++) {
            int value = rand() % 1000 + 1; // Valor aleatório entre 1 e 1000
            insertEnd(&head1, value);
            insertEnd(&head2, value);
        }

        // Medir o tempo de execução para listBubbleSort
        auto start = chrono::high_resolution_clock::now();
        listBubbleSort(&head1, size);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "Tempo para listBubbleSort          com lista de tamanho " << size << ": " << duration.count() << " segundos" << endl;

        // Medir o tempo de execução para optimizedListBubbleSort
        start = chrono::high_resolution_clock::now();
        optimizedListBubbleSort(&head2, size);
        end = chrono::high_resolution_clock::now();
        duration = end - start;
        cout << "Tempo para optimizedListBubbleSort com lista de tamanho " << size << ": " << duration.count() << " segundos" << endl;
        
        cout << endl;

        // Limpar a memória alocada para as listas
        deleteList(&head1);
        deleteList(&head2);
    }

    cout << "#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#" << endl;
    cout << "Teste para algorítmo SelectionSort" << endl << endl;

    for (int size : sizes) {
        Node* head1 = nullptr;
        Node* head2 = nullptr;

        // Criar listas aleatórias
        for (int i = 0; i < size; i++) {
            int value = rand() % 1000 + 1; // Valor aleatório entre 1 e 1000
            insertEnd(&head1, value);
            insertEnd(&head2, value);
        }

        // Medir o tempo de execução para listBubbleSort
        auto start = chrono::high_resolution_clock::now();
        listSelectionSort(&head1, size);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;
        cout << "Tempo para listSelectionSort          com lista de tamanho " << size << ": " << duration.count() << " segundos" << endl;

        // Medir o tempo de execução para optimizedListBubbleSort
        start = chrono::high_resolution_clock::now();
        optimizedListSelectionSort(&head2, size);
        end = chrono::high_resolution_clock::now();
        duration = end - start;
        cout << "Tempo para optimizedListSelectionSort com lista de tamanho " << size << ": " << duration.count() << " segundos" << endl;
        
        cout << endl;

        // Limpar a memória alocada para as listas
        deleteList(&head1);
        deleteList(&head2);
    }
    
    return 0;
}

Node* createNode(int iValue) {
    Node* temp = (Node*)malloc(sizeof(Node)); // Manteve o uso de malloc
    temp->iPayload = iValue;
    temp->ptrNext = nullptr;
    temp->ptrPrev = nullptr;
    
    return temp;
}

void displayList(Node* node) {
    if (node == nullptr) {
        cout << "Lista vazia: não é possível realizar displayList" << endl;
        return;
    }
    
    // se receber um nó do meio, rejeito (um modo)
    if (node->ptrPrev != nullptr) {
        cout << "O elemento está no meio ou fim da lista: não é possível realizar displayList" << endl;
        return;
    }
    
    Node* temp = node;
    cout << "Payload: ";
    
    while (temp != nullptr) {
        cout <<  temp->iPayload << " ";
        temp = temp->ptrNext;
    }
    
    cout << endl;
}

void insertEnd(Node** head, int iValue) {
    Node* newNode = createNode(iValue);

    if (*head == nullptr) {
        *head = newNode; 
        return;
    }
    
    Node* temp = *head;
    while (temp->ptrNext != nullptr)
        temp = temp->ptrNext;
    
    newNode->ptrPrev = temp; // newnode aponta para o fim da lista
    temp->ptrNext = newNode; // antigo ultimo elemento aponta para o novo nó
}

void deleteList(Node** head) {
    Node* current = *head;
    Node* next;

    while (current != nullptr) {
        next = current->ptrNext;
        free(current); // Manteve o uso de free
        current = next;
    }

    *head = nullptr;
}

void swapValue(Node** Value_1, Node** Value_2) {
    int temp = (*Value_1)->iPayload;
    (*Value_1)->iPayload = (*Value_2)->iPayload;
    (*Value_2)->iPayload = temp;
}

void listBubbleSort(Node** head, int iLength) {
    Node* current = *head;
    
    for (int iOuterLoop = 0; iOuterLoop < iLength - 1; iOuterLoop++) {
        current = *head; // Reinicializa o ponteiro current no início de cada iteração
        for (int iInnerLoop = 0; iInnerLoop < iLength - iOuterLoop - 1; iInnerLoop++) {
            if (current->iPayload > current->ptrNext->iPayload) {
                swapValue(&current, &(current->ptrNext));
            }
            current = current->ptrNext;
        }
    }
}

void optimizedListBubbleSort(Node** head, int iLength) {
    Node* current = *head;
    bool bUnordered = false;
    
    for (int iOuterLoop = 0; iOuterLoop < iLength - 1; iOuterLoop++) {
        current = *head; // Reinicializa o ponteiro current no início de cada iteração
        bUnordered = false;
        
        for (int iInnerLoop = 0; iInnerLoop < iLength - iOuterLoop - 1; iInnerLoop++) {
            if (current->iPayload > current->ptrNext->iPayload) {
                swapValue(&current, &(current->ptrNext));
                bUnordered = true;
            }
            current = current->ptrNext;
        }

        if (!bUnordered) {
            break;
        }
    }
}

void listSelectionSort(Node** head, int iLength) {
    for (int iOuterLoop = 0; iOuterLoop < iLength; iOuterLoop++) {
        Node* current = *head;

        for (int iInnerLoop = iOuterLoop + 1; iInnerLoop < iLength; iInnerLoop++) {
            if (current->iPayload > current->ptrNext->iPayload) {
                swapValue(&current, &(current->ptrNext));
            }
            current = current->ptrNext;
        }
    }
}

void optimizedListSelectionSort(Node** head, int iLength) {
    Node *current; 
    Node *min;

    for (int i = 0; i < iLength - 1; i++) {
        current = *head;
        min = current;

        for (int j = i + 1; j < iLength; j++) {
            if (current->iPayload > current->ptrNext->iPayload) {
                min = current->ptrNext;
            }
            current = current->ptrNext;
        }

        if (min != current) {
            swapValue(&min, &current);
        }
    }
}

void swapValue(int& irefValue_1, int& irefValue_2) {
    int iTemp = irefValue_1;
    irefValue_1 = irefValue_2;
    irefValue_2 = iTemp;
    
}

void printArray(int arriNumbers[], int iLenght) {
    for(int i = 0; i < iLenght; i++) cout<<arriNumbers[i] << " ";
    cout << endl;
}

void bubbleSort(int arriNumbers[], int iLenght) {
    
    for (int iOuterLoop = 0; iOuterLoop < iLenght-1; iOuterLoop++)
        for (int iInnerLoop = 0; iInnerLoop < iLenght-1; iInnerLoop++)
            if (arriNumbers[iInnerLoop] > arriNumbers[iInnerLoop+1])
                swapValue(arriNumbers[iInnerLoop], arriNumbers[iInnerLoop+1]);
}

void otimizationBubbleSort(int arriNumbers[], int iLenght) {
    bool bUnordered = false;
    
    for (int iOuterLoop = 0; iOuterLoop < iLenght-1; iOuterLoop++) {
        bUnordered = false;
        
        for (int iInnerLoop = 0; iInnerLoop < iLenght-1-iOuterLoop; iInnerLoop++) {
            if (arriNumbers[iInnerLoop] > arriNumbers[iInnerLoop+1]) {
                swapValue(arriNumbers[iInnerLoop], arriNumbers[iInnerLoop+1]);
                bUnordered = true;
            }    
            
            if(bUnordered == false)
                break;
        }

    }
}

void selectionSort(int arriNumbers[], int iLenght) {
    
    for (int iOuterLoop = 0; iOuterLoop < iLenght; iOuterLoop++)
        for (int iInnerLoop = iOuterLoop+1; iInnerLoop < iLenght; iInnerLoop++)
            if(arriNumbers[iOuterLoop] > arriNumbers[iInnerLoop])
                swapValue(arriNumbers[iOuterLoop], arriNumbers[iInnerLoop]);
}

void optimizedSelectionSort(int arriNumbers[], int iLenght) {
    int iminValue = 0;
    int iSwapIndex = 0;
    
    for (int iOuterLoop = 0; iOuterLoop < iLenght; iOuterLoop++) {
        iminValue = arriNumbers[iOuterLoop];
        iSwapIndex = iOuterLoop;
        
        for (int iInnerLoop = iOuterLoop+1; iInnerLoop < iLenght; iInnerLoop++) {
            if(iminValue > arriNumbers[iInnerLoop]) {
                iminValue = arriNumbers[iInnerLoop];
                iSwapIndex = iInnerLoop;
            }
        }
        
        swapValue(arriNumbers[iOuterLoop], arriNumbers[iSwapIndex]);
    }
}
