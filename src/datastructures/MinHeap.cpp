#include"HuffmanNode"

class MinHeapTree
{
public:
    HuffmanNode* heap[1000];
    int size;

    MinHeapTree()
    {
        size=0;
    }

    void insert(HuffmanNode *currentNode)
    {
        heap[size]=currentNode;
        heapifyUp(size);
        size++;
    }

    HuffmanNode* extractMin()
    {
        if (size == 0)
        {
            return nullptr;
        }
        HuffmanNode* root = heap[0];
        heap[0] = heap[--size];
        heapifyDown(0);
        return root;

    }

    void swap(int i, int j)
    {
        HuffmanNode* temp = heap[i];
        heap[i] = heap[j];
        heap[j] = temp;
    }

    void heapifyDown(int i)
    {
        int smallest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // Check left child
        if (left < size)
        {
            if (heap[left]->freq == heap[smallest]->freq)
            {
                if (heap[left]->ch < heap[smallest]->ch)
                {
                    smallest = left;
                }
            }
            else if (heap[left]->freq < heap[smallest]->freq)
            {
                smallest = left;
            }
        }

        // Check right child
        if (right < size)
        {
            if (heap[right]->freq == heap[smallest]->freq)
            {
                if (heap[right]->ch < heap[smallest]->ch)
                {
                    smallest = right;
                }
            }
            else if (heap[right]->freq < heap[smallest]->freq)
            {
                smallest = right;
            }
        }

        if (smallest != i)
        {
            swap(i, smallest);
            heapifyDown(smallest);
        }
    }


    void heapifyUp(int i)
    {
        int parent = (i - 1) / 2;
        if (i && (
                    (heap[i]->freq < heap[parent]->freq) ||
                    (heap[i]->freq == heap[parent]->freq && heap[i]->ch < heap[parent]->ch)
                ))
        {
            swap(i, parent);
            heapifyUp(parent);
        }
    }


    int getSize()
    {
        return size;
    }


    void printHeap()
    {
        cout << "\nHeap contents (char, freq):\n";
        for (int i = 0; i < size; i++)
        {
            cout << "(" << heap[i]->ch << ", " << heap[i]->freq << ") ";
        }
        cout << endl;
    }

};