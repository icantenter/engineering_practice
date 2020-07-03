#include "DataBase.h"
#define cerr(msg) std::cerr << "[" << __FILE__ << ":" << __LINE__ << msg << "]"
/**
*@File: DataBase.cpp
*@Description: DataBase类的函数
*@Author: 李希发
*@Date: 2020-06-02
*@LastEditors: 李希发
*@EditDescription: none
*@Version: 1.0
*/
DataBase::DataBase()
{
}

DataBase::~DataBase()
{
    PLAYER *prev = this->head, *next;
    while (prev)
    {
        next = prev->next;
        free(prev);
        prev = next;
    }
    
}


/*************************************************
  Function:push_back()       函数名称
  Description:向DataBase中添加新用户     函数功能、性能等的描述
  Input:新用户的账户(name),密码(password)  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:无          函数返回值的说明
  Others:无          其它说明
*************************************************/

void DataBase::push_back(ACCOUNT *new_account)
{
    Player *temp = this->head;

    if (this->head == NULL)
    {
        temp = (PLAYER *)malloc(sizeof(PLAYER));
        this->head = temp;
    }
    else
    {
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = (PLAYER *)malloc(sizeof(PLAYER));
        temp = temp->next;
    }
    strcpy_s(temp->account.name, new_account->name);
    strcpy_s(temp->account.password, new_account->password);
    temp->high_score = 0;
    temp->time = 0;
    temp->number = 0;
    temp->next = NULL;
    this->data_size++;
}

/*************************************************
  Function:find()       函数名称
  Description:在DataBase中查找用户     函数功能、性能等的描述
  Input:要查找用户的账户(name),密码(password)  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:返回查找用户在DataBase中的序号         函数返回值的说明
  Others:没有找到返回NOT_FIND          其它说明
*************************************************/

int DataBase::find(const std::string &search_name, int index = DATA_BEGIN)
{
    Player *temp = this->head;

    if (index < DATA_BEGIN || index >= this->data_size)
    {
        return NOT_FIND;
    }

    for (; index < this->data_size; index++)
    {
        if (temp->account.name == search_name)
        {
            return index;
        }
        temp = temp->next;
    }
    return NOT_FIND;
}


/*************************************************
  Function:get_player()       函数名称
  Description:返回DataBase中对应索引的用户     函数功能、性能等的描述
  Input:有效索引  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:返回DataBase中对应索引的用户的指针         函数返回值的说明
  Others:索引无效会抛出异常          其它说明
*************************************************/

PLAYER *DataBase::get_player(int index)
{
    PLAYER *temp = this->head;
    PLAYER des;

    try
    {
        if (index < 0 || index >= this->data_size)
        {
            throw error_msgs[ERROR_ARGUMENT];
        }
    }
    catch (const std::string msg)
    {
        //cerr(msg);
        exit(EXIT_FAILURE);
    }

    for (int i = DATA_BEGIN; i < index; i++)
    {
        temp = temp->next;
    }

    return temp;
}


/*************************************************
  Function:kill()       函数名称
  Description:删除DataBase中对应索引的用户     函数功能、性能等的描述
  Input:有效索引  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:无         函数返回值的说明
  Others:索引无效会抛出异常          其它说明
*************************************************/
void DataBase::kill(int index)
{
    Player *previous = this->head, *next = this->head;

    try
    {
        if (index < 0 || index >= this->data_size)
        {
            throw error_msgs[ERROR_ARGUMENT];
        }
    }
    catch (const std::string msg)
    {
        std::cerr << "DataBase: " << msg << '\n';
        exit(EXIT_FAILURE);
    }

    for (int i = DATA_BEGIN; i < index; i++)
    {
        previous = next;
        next = next->next;
    }
    if (next == this->head)
    {
        this->head = this->head->next;
    }
    else
    {
        previous->next = next->next;
    }
    free(next);
    this->data_size--;
}


/*************************************************
  Function:get_data_size()       函数名称
  Description:返回DataBase中的用户个数     函数功能、性能等的描述
  Input:无  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:DataBase中的用户个数         函数返回值的说明
  Others:这是一个访问器          其它说明
*************************************************/
int DataBase::get_data_size()
{
    return this->data_size;
}


/*************************************************
  Function:append_from_file()       函数名称
  Description:从文件读取数据添加到DataBase中     函数功能、性能等的描述
  Input:文件名  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:是否文件中有数据         函数返回值的说明
  Others:这是一个访问器          其它说明
*************************************************/
bool DataBase::append_from_file(const std::string &append_path)
{
    std::ifstream fin(append_path.c_str(), std::ios_base::in | std::ios_base::binary);
    Player *previous = this->head, *next;
    try
    {
        if (!fin.is_open())
        {
            throw error_msgs[ERROR_FILE_OPERATION];
        }
    }
    catch (const std::string msg)
    {
        std::cerr << "DataBase: " << msg << '\n';
    }
    next = (PLAYER *)malloc(sizeof(PLAYER));
    fin.read((char *)next, sizeof(PLAYER));  
    if (fin.eof())
    {
        free(next);
        return false;
    }
    this->data_size++;
    if (previous)
    {
        while (previous->next)
        {
            previous = previous->next;
        }
        previous->next = next;
        previous = next;
    }
    else
    {
        previous = next;
        this->head = previous;
    }

    while (true)
    {
        next = (PLAYER *)malloc(sizeof(PLAYER));
        fin.read((char *)next, sizeof(PLAYER));
        if (fin.eof())
        {
            free(next);
            previous->next = NULL;
            break;
        }
        else
        {
            previous->next = next;
            previous = next;
            this->data_size++;
        }
    }

    fin.close();
    return true;
}



/*************************************************
  Function:save()       函数名称
  Description:把DataBase中的数据保存到文件中     函数功能、性能等的描述
  Input:文件名  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:void         函数返回值的说明
  Others:索引无效会抛出异常          其它说明
*************************************************/
void DataBase::save(const std::string &save_path)
{
    PLAYER *temp = this->head;
    std::ofstream fout;

    fout.open(save_path.c_str(), std::ios_base::out | std::ios_base::binary);
    try
    {
        while (temp)
        {
            /*caution*/
            fout.write((char *)temp, sizeof(PLAYER)) << std::flush;
            if (fout.fail())
            {
                throw error_msgs[ERROR_FILE_OPERATION];
            }
            temp = temp->next;
        }
    }
    catch (const std::string msg)
    {
        std::cerr << "DataBase: " << msg << std::endl;
        exit(EXIT_FAILURE);
    }
    fout.close(); //terminate association with score.dat
}


/*************************************************
  Function:sort()       函数名称
  Description:把DataBase中的数据排序     函数功能、性能等的描述
  Input:排序方式，升序还是降序  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:返回排序后的头节点         函数返回值的说明
  Others:void          其它说明
*************************************************/
PLAYER *DataBase::sort(int sort_type, bool descending_order = false)
{
    bool flag = true;
    PLAYER *players[this->data_size];
    PLAYER *temp = this->head;

    for (int i = 0; i < this->data_size; i++)
    {
        players[i] = temp;
        temp = temp->next;
    }
    for (int i = 0; i < this->data_size - 1; i++)
    {
        for (int j = 0; j < this->data_size - i - 1; j++)
        {
            if (sort_type == ACCORDING_ALPHA)
            {
                if (descending_order ^ (strcmp(players[j]->account.name, 
                    players[j + 1]->account.name) > 0))
                {
                    temp = players[i];
                    players[i] = players[j];
                    players[j] = temp;
                    flag = false;
                }
            }
            else
            {
                if (descending_order ^ (players[j]->high_score < 
                    players[j + 1]->high_score))
                {
                    temp = players[i];
                    players[i] = players[j];
                    players[j] = temp;
                    flag = false;
                }
            }
        }
        if (flag)
        {
            break;
        }
        flag = true;
    }
    this->head = players[0];
    temp = this->head;
    for (int i = 1; i < this->data_size; i++)
    {
        temp->next = players[i];
        temp = players[i];
    }
    temp->next = NULL;
    return this->head;
}


/*************************************************
  Function:get_highest_score()       函数名称
  Description:返回DataBase中的最高分     函数功能、性能等的描述
  Input:void  输入参数说明，包括每个参数的作
                   用、取值说明及参数间关系。
  Return:返回DataBase中的最高分         函数返回值的说明
  Others:void          其它说明
*************************************************/
int DataBase::get_highest_score()
{
    int highest_score = 0;
    PLAYER *temp = this->head;

    while (temp)
    {
        highest_score = std::max(highest_score, temp->high_score);
        temp = temp->next;
    }

    return highest_score;
}
