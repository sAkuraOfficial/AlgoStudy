#include<iostream>
#include<vector>

template <typename T>
struct ListNode
{
    T val;
    ListNode *next;
    ListNode(T x): val(x), next(nullptr) {}
};

template <typename T>
class linked_list
{
private:
    ListNode<T> *first=nullptr;
    ListNode<T> *last=nullptr;
    int node_count=0;

public:
    ListNode<T> *get_first() { return first; }
    ListNode<T> *get_last() { return last; }
    int get_count() { return node_count; }

    void push_back(T x) //插入到链表尾部
    {
        ListNode<T> *node = new ListNode(x);
        if (!last)
        {
            //若尾部为空，则说明链表为空
            last = first = node;
        }
        else
        {
            last = last->next = node;
        }
        node_count++; //计数增加
    }

    void push_front(T x) //插入到链表头部
    {
        ListNode<T> *node = new ListNode(x);
        if (!first)
        {
            //若头部为空，则说明链表为空
            last = first = node;
        }
        else
        {
            node->next = first; //将第一个作为新节点的next
            first = node; //将新节点设为first
        }
        node_count++; //计数器增加
    }

    bool insert(int index, T x) //插入节点到index位置，index从0开始
    {
        if (index < 0 || index > node_count - 1) //判断index是否合法
        {
            return false; //插入失败
        }
        try
        {
            ListNode<T> *temp_node = first;
            for (int i = 0; i < index - 1; i++, temp_node = temp_node->next); //一直循环直到找到index所在节点的前一个
            ListNode<T> *node = new ListNode<T>(x);
            node->next = temp_node->next; //将新node的下一个，设置为temp的下一个，
            temp_node->next = node; //将temp的下一个设置为node
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    bool remove(int index)
    {
        if (index < 0 || index > node_count - 1) //判断index是否合法
        {
            return false; //删除
        }
        try
        {
            ListNode<T> *temp_node = first;
            for (int i = 0; i < index - 1; i++, temp_node = temp_node->next); //一直循环直到找到index所在节点的前一个
            ListNode<T> *delete_node = temp_node->next; //待删除的节点
            temp_node->next = delete_node->next;
            delete delete_node;
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    bool update(int index, T x) //更新节点的值
    {
        if (index < 0 || index > node_count - 1) //判断index是否合法
        {
            return false; //更新失败
        }
        try
        {
            ListNode<T> *temp_node = first;
            for (int i = 0; i < index; i++, temp_node = temp_node->next); //一直循环直到找到index所在节点，这里与前面的循环操作不一样，少了-1
            temp_node->val = x;
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    bool value(int index, T &x) //获取值，参数形式返回
    {
        if (index < 0 || index > node_count - 1) //判断index是否合法
        {
            return false; //获取失败
        }
        try
        {
            ListNode<T> *temp_node = first;
            for (int i = 0; i < index; i++, temp_node = temp_node->next); //一直循环直到找到index所在节点，这里与前面的循环操作不一样，少了-1
            x = temp_node->val;
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    bool find_node_point(T *p, int &index) //使用node的指针，查找其index
    {
        if (!p || first == nullptr)
        {
            index = -1;
            return false;
        }
        try
        {
            ListNode<T> *node = first;
            index = 0; //初始化
            while (node != p)
            {
                if (node == last) //因为此时node与p不匹配。同时node又是最后一个，因此可以认为查找失败
                    return false;
                node = node->next;
                index++;
            }
            //循环之外，此时node与p匹配。
            return true; //index从参数返回
        }
        catch (...)
        {
            return false;
        }
    }

    bool find_node_index(int index, ListNode<T> *&node) //查找index位置上的节点，返回其指针
    {
        if (index < 0 || index > node_count - 1)
        {
            return false;
        }
        try
        {
            node = first;
            for (int i = 0; i < index; i++, node = node->next); //一直循环直到找到index所在节点，这里与前面的循环操作不一样，少了-1
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    bool find_node_value(T x, std::vector<int> &indexs)
    {
        try
        {
            ListNode<T> *temp = first;
            for (int i = 0; i < node_count; i++,temp=temp->next)
            {
                if (temp->val == x)
                {
                    indexs.push_back(i);
                }
            }
            return true;
        }
        catch (...)
        {
            return false;
        }
    }

    T &operator[](int index)
    {
        if (index < 0 || index > node_count - 1)
        {
            throw "越界";
        }
        ListNode<T> *temp = first;
        for (int i = 0; i < index; i++, temp = temp->next);
        return temp->val;

    }
};

int main()
{
    linked_list<int> list;

    // 插入元素
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_front(5);

    // 输出链表元素
    for (int i = 0; i < list.get_count(); i++)
    {
        std::cout << "Element at index " << i << ": " << list[i] << std::endl;
    }

    // 测试插入和删除
    list.insert(2, 15); // 在索引2处插入15
    list.remove(3);     // 删除索引3处的元素

    std::cout << "After insertion and deletion:" << std::endl;
    for (int i = 0; i < list.get_count(); i++)
    {
        std::cout << "Element at index " << i << ": " << list[i] << std::endl;
    }

    // 更新和查找
    list.update(1, 25); // 更新索引1处的值为25
    int value;
    if (list.value(1, value))
    {
        std::cout << "Value at index 1: " << value << std::endl;
    }

    // 查找值
    std::vector<int> indices;
    list.find_node_value(25, indices);
    std::cout << "Indices with value 25:";
    for (int i : indices)
    {
        std::cout << " " << i;
    }
    std::cout << std::endl;

    return 0;
}