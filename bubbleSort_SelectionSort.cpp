#include <iostream>
#include <chrono>
#include <random>
#include <cstdlib> // Incluir a biblioteca cstdlib para o uso de malloc

using namespace std;

typedef struct Node 
{
    int iPayload; 
    Node* ptrNext;
    Node* ptrPrev;
} Node;

Node* createNode(int);
void displayList(Node*);
void insertEnd(Node**, int);
void deleteList(Node**);
void swapValue(Node**, Node**);
void bubbleSort(Node**, int);
void optimizationBubbleSort(Node**, int);

void swapValue(int&, int&);
void printArray(int[], int);
void bubbleSort(int[], int);
void optimizationBubbleSort(int[], int);

void selectionSort(int[], int);
void optimizedSelectionSort(int[], int);

int main()
{
    // Bubble com lista

    Node* head1 = nullptr;
    Node* head2 = nullptr;
    int iLength0 = 1000;

    for (int i = 0; i < iLength0; i++)
    {
        int iValue =  rand() % 1000 + 1; // Gera um número aleatório entre 1 e 1000
        insertEnd(&head1, iValue);  
        insertEnd(&head2, iValue);
    }
    
    // Ordenando a lista usando o Bubble Sort
    cout << "Lista original: ";
    displayList(head1);

    auto timeStart0 = chrono::high_resolution_clock::now();
    bubbleSort(&head1, iLength0);
    auto timeStop0 = chrono::high_resolution_clock::now();

    cout << "Lista ordenada: ";
    displayList(head1);
    
    auto timeDuration = chrono::duration_cast<chrono::nanoseconds>(timeStop0 - timeStart0);
    
    cout << "Tempo utilizado: " <<  timeDuration.count() << " nanosegundos" <<  endl;
    
    cout << endl;
    
    // Ordenando a lista usando o Bubble Sort otimizado

    cout << "Lista original: ";
    displayList(head2);
    
    auto timeStart1 = chrono::high_resolution_clock::now();
    optimizationBubbleSort(&head2,  iLength0);
    auto timeStop1 = chrono::high_resolution_clock::now();

    cout << "Lista ordenada: ";
    displayList(head2);
    
    auto timeDuration1 = chrono::duration_cast<chrono::nanoseconds>(timeStop1 - timeStart1);
    
    cout << "Tempo utilizado: " <<  timeDuration1.count() << " nanosegundos" <<  endl;

    // Limpando a memória alocada para as listas
    deleteList(&head1);
    deleteList(&head2);


    // Bubble com array
    
    int arriNumbers_1[] = {42, 4, 137, 24, 0, 9, 100, 67, 72, 431, 42, 40, 17, 14, 5, 94, 144, 671, 724, 4355};
    int iLenght1 = 20;
    cout << "Array original: ";
    printArray(arriNumbers_1, iLenght1);
    
    auto timeStart2 = chrono::high_resolution_clock::now();
    bubbleSort(arriNumbers_1, iLenght1);
    auto timeStop2 = chrono::high_resolution_clock::now();

    cout << "Array ordenado: ";
    printArray(arriNumbers_1, iLenght1);
    
    auto timeDuration2 = chrono::duration_cast<chrono::nanoseconds>(timeStop2 - timeStart2);
    
    cout << "Tempo utilizado: " <<  timeDuration2.count() << " nanosegundos" <<  endl;
    
    cout << endl;

    //Selection Sort com array
    int arriNumbers_2[] = {42, 4, 137, 24, 0, 9, 100, 67, 72, 431};
    int iLenght2 = 10;

    auto timeStart3 = chrono::high_resolution_clock::now();
    selectionSort(arriNumbers_2, iLenght2);
    auto timeStop3 = chrono::high_resolution_clock::now();

    cout << "Array ordenado: ";
    printArray(arriNumbers_2, iLenght2);
    auto timeDuration3 = chrono::duration_cast<chrono::nanoseconds>(timeStop3 - timeStart3);

    cout << "Tempo utilizado: " <<  timeDuration3.count() << " nanosegundos" <<  endl;
    cout << endl;

    cout << "Array original: ";
    printArray(arriNumbers_2, iLenght2);

    auto timeStart4 = chrono::high_resolution_clock::now();
    optimizedSelectionSort(arriNumbers_2, iLenght2);
    auto timeStop4 = chrono::high_resolution_clock::now();

    cout << "Array ordenado: ";
    printArray(arriNumbers_2, iLenght2);

    auto timeDuration4 = chrono::duration_cast<chrono::nanoseconds>(timeStop4 - timeStart4);
    cout << "Tempo utilizado: " <<  timeDuration4.count() << " nanosegundos" <<  endl;


    return 0;
}

Node* createNode(int iValue)
{
    Node* temp = (Node*)malloc(sizeof(Node)); // Manteve o uso de malloc
    temp->iPayload = iValue;
    temp->ptrNext = nullptr;
    temp->ptrPrev = nullptr;
    
    return temp;
}
void displayList(Node* node)
{
    if (node == nullptr)
    {
        cout << "Lista vazia: não é possível realizar displayList" << endl;
        return;
    }
    
    // se receber um nó do meio, rejeito (um modo)
    if (node->ptrPrev != nullptr)
    {
        cout << "O elemento está no meio ou fim da lista: não é possível realizar displayList" << endl;
        return;
    }
    
    Node* temp = node;

    cout << "Payload: ";
    
    while (temp != nullptr)
    {
        cout <<  temp->iPayload << " ";
        temp = temp->ptrNext;
    }
    
    cout << endl;
}
void insertEnd(Node** head, int iValue)
{
    Node* newNode = createNode(iValue);

    if (*head == nullptr) 
    {
        *head = newNode; 
        return;
    }
    
    Node* temp = *head;
    while (temp->ptrNext != nullptr)
    {
        temp = temp->ptrNext;
    }
    
    newNode->ptrPrev = temp; // newnode aponta para o fim da lista
    temp->ptrNext = newNode; // antigo ultimo elemento aponta para o novo nó
}
void deleteList(Node** head) 
{
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
void bubbleSort(Node** head, int iLength) 
{
    Node* current = *head;
    for (int iOuterLoop = 0; iOuterLoop < iLength - 1; iOuterLoop++)
    {
        current = *head; // Reinicializa o ponteiro current no início de cada iteração
        for (int iInnerLoop = 0; iInnerLoop < iLength - iOuterLoop - 1; iInnerLoop++)
        {
            if (current->iPayload > current->ptrNext->iPayload)
            {
                swapValue(&current, &(current->ptrNext));
            }
            current = current->ptrNext;
        }
    }
}
void optimizationBubbleSort(Node** head, int iLength) 
{
    Node* current = *head;
    bool bUnordered = false;
    
    for (int iOuterLoop = 0; iOuterLoop < iLength - 1; iOuterLoop++)
    {
        current = *head; // Reinicializa o ponteiro current no início de cada iteração
        bUnordered = false;
        
        for (int iInnerLoop = 0; iInnerLoop < iLength - iOuterLoop - 1; iInnerLoop++)
        {
            if (current->iPayload > current->ptrNext->iPayload)
            {
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

void swapValue(int& irefValue_1, int& irefValue_2)

{
    int iTemp = irefValue_1;
    irefValue_1 = irefValue_2;
    irefValue_2 = iTemp;
    
}
void printArray(int arriNumbers[], int iLenght)

{
    for(int i = 0; i < iLenght; i++) cout<<arriNumbers[i] << " ";
    cout << endl;
}
void bubbleSort(int arriNumbers[], int iLenght) 
{
    
    for (int iOuterLoop = 0; iOuterLoop < iLenght-1; iOuterLoop++)
    {
        for (int iInnerLoop = 0; iInnerLoop < iLenght-1; iInnerLoop++)
        {
            if (arriNumbers[iInnerLoop] > arriNumbers[iInnerLoop+1])
            {
                swapValue(arriNumbers[iInnerLoop], arriNumbers[iInnerLoop+1]);
            }    
        }

    }
}
void otimizationBubbleSort(int arriNumbers[], int iLenght) 
{
    bool bUnordered = false;
    
    for (int iOuterLoop = 0; iOuterLoop < iLenght-1; iOuterLoop++)
    {
        bUnordered = false;
        
        for (int iInnerLoop = 0; iInnerLoop < iLenght-1-iOuterLoop; iInnerLoop++)
        {
            if (arriNumbers[iInnerLoop] > arriNumbers[iInnerLoop+1])
            {
                swapValue(arriNumbers[iInnerLoop], arriNumbers[iInnerLoop+1]);
                bUnordered = true;
                
            }    
            
            if(bUnordered == false) {
                break;
            }
        }

    }
}

void selectionSort(int arriNumbers[], int iLenght)
{
    for (int iOuterLoop = 0; iOuterLoop < iLenght; iOuterLoop++)
    {
        for (int iInnerLoop = iOuterLoop+1; iInnerLoop < iLenght; iInnerLoop++)
        {
            if(arriNumbers[iOuterLoop] > arriNumbers[iInnerLoop])
            {
                swapValue(arriNumbers[iOuterLoop], arriNumbers[iInnerLoop]);
            }
        }

    }
}
void optimizedSelectionSort(int arriNumbers[], int iLenght)
{
    int iminValue = 0;
    int iSwapIndex = 0;
    
    for (int iOuterLoop = 0; iOuterLoop < iLenght; iOuterLoop++)
    {
        iminValue = arriNumbers[iOuterLoop];
        iSwapIndex = iOuterLoop;
        for (int iInnerLoop = iOuterLoop+1; iInnerLoop < iLenght; iInnerLoop++)
        {
            if(iminValue > arriNumbers[iInnerLoop])
            {
                iminValue = arriNumbers[iInnerLoop];
                iSwapIndex = iInnerLoop;
            }
        }
        // colocar if pra ver se iOuterLoop é diferente de iSwapIndex pra
        //não trocar um elemento com ele mesmo
        swapValue(arriNumbers[iOuterLoop], arriNumbers[iSwapIndex]);
    }
}
