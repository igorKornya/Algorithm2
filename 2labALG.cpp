#include <iostream>
#include "arr.cpp"
#include <locale>
#include <cstdlib>


int minrun(int n)
{
    int flag = 0;
    while (n >= 64)
    {
        flag |= n & 1;
        n >>= 1;
    }
    return n + flag;

}

int min_digit(int a, int b)
{
    int res;
    if (a > b)
    {
        res = b;
    }
    else
    {
        res = a;
    }

    return res;
}

void gallop(dynamic_arr<int>& arr, dynamic_arr<int>& left_arr, dynamic_arr<int>& right_arr, int& i, int& j, int& k, bool check)
{
    if (check)
    {
        int left = i;
        int right = left_arr.get_size();

        while (left < right)
        {
            int mid = (left + right) / 2;
            if (left_arr[mid] < right_arr[j]) 
            {
                for (int m = left; m <= mid; m++) 
                {
                    arr[k++] = left_arr[m];
                }
                left = mid;
                i = left;
            }
            else
            {
                right = mid;
            }
        }

    }
    else
    {
        int left = j;
        int right = right_arr.get_size();

        while (left < right)
        {
            int mid = (left + right) / 2;
            if (right_arr[mid] < left_arr[i])
            {
                for (int m = left; m <= mid; m++)
                {
                    arr[k++] = right_arr[m];
                }
                left = mid;
                j = left;
            }
            else
            {
                right = mid;
            }
        }
    }
}

void insert_sort(dynamic_arr<int>& run, int left, int right)
{
    {
        for (int i = left + 1; i < right; i++) {
            int temp = run[i];
            int j = i - 1;
            while (j >= left && run[j] > temp) {
                run[j + 1] = run[j];
                j--;
            }
            run[j + 1] = temp;
        }
    }
}

void merge(dynamic_arr<int>& arr, int left, int mid, int right)
{
    int cnt_l = 0;
    int cnt_r = 0;

    int left_arr_length = mid - left;
    int rigth_arr_length = right - mid;

    dynamic_arr<int> left_arr(left_arr_length);
    dynamic_arr<int> right_arr(rigth_arr_length);
    for (int i = 0; i < left_arr_length; i++)
        left_arr[i] = arr[left + i];
    for (int j = 0; j < rigth_arr_length; j++)
        right_arr[j] = arr[mid + j];

    int i = 0, j = 0, k = left;

    while (i < left_arr_length && j < rigth_arr_length) {
        if (left_arr[i] <= right_arr[j]) {
            arr[k++] = left_arr[i++];
            cnt_l++;
            cnt_r = 0;
        }
        else {
            arr[k++] = right_arr[j++];
            cnt_r++;
            cnt_l = 0;
        }
        if (cnt_l == 5)
        {
            gallop(arr, left_arr, right_arr, i, j, k, true);
            cnt_l = 0;
        }
        if (cnt_r == 5)
        {
            gallop(arr, left_arr, right_arr, i, j, k, false);
            cnt_r = 0;
        }
    }

    while (i < left_arr_length) arr[k++] = left_arr[i++];
    while (j < rigth_arr_length) arr[k++] = right_arr[j++];
}


void timsort(dynamic_arr<int>& arr, int mn)
{
    for (int i = 0, counter = 1; i < arr.get_size(); i += mn, counter++)
    {
        if (i + mn < arr.get_size())
            insert_sort(arr, i, i + mn);
        else
            insert_sort(arr, i, arr.get_size());
    }
    for (int size = mn; size < arr.get_size(); size = 2 * size)
    {
        for (int left = 0; left < arr.get_size(); left += 2 * size)
        {
            int mid = left + size;
            int right;
            if ((left + 2 * size) < (arr.get_size()))
                right = (left + 2 * size);
            else
                right = arr.get_size();
            if (mid < right)
                merge(arr, left, mid, right);
        }
    }
}

void array_menu() {
    dynamic_arr<int> arr;
    size_t arr_size = 0;
    char choice;
    bool running = true;

    while (running) {
        std::cout << "1 - Добавить элемент\n";
        std::cout << "2 - Удалить элемент\n";
        std::cout << "3 - Задать рандомный массив\n";
        std::cout << "4 - Вывести массив\n";
        std::cout << "5 - Timsort\n";
        std::cout << "6 - Выйти\n";
        std::cout << "> ";
        std::cin >> choice;

        switch (choice) {
        case '1': {
            int value;
            size_t pos;
            std::cout << "Введите значение: ";
            std::cin >> value;
            std::cout << "Введите позицию: ";
            std::cin >> pos;
            if (pos <= arr.get_size()) {
                arr.push(pos, value);
            }
            else {
                std::cout << "Некорректная позиция!\n";
            }
            break;
        }
        case '2': {
            size_t pos;
            std::cout << "Введите позицию для удаления: ";
            std::cin >> pos;
            if (pos < arr.get_size()) {
                arr.del_el(pos);
            }
            else {
                std::cout << "Некорректная позиция!\n";
            }
            break;
        }
        case '3': {
            std::cout << "Введите размер массива: ";
            std::cin >> arr_size;
            if (arr_size > 10000)
            {
                std::cout << "(0, 10000)" << std::endl;
                std::cin.fail();
                std::cin.clear();
                std::cin.ignore(10001, '\n');
            }
            srand(time(NULL));
            for (size_t i = 0; i < arr_size; i++)
            {
                arr.push(i, std::rand() % 1000);
            }
            break;
        }
        case '4': {
            std::cout << "Элементы массива: ";
            for (size_t i = 0; i < arr.get_size(); i++) {
                std::cout << arr.get_pos(i) << " ";
            }
            std::cout << std::endl;
            break;
        }
        case '5': {
            std::cout << "Старый массив: ";
            for (int i = 0; i < arr.get_size(); i++)
            {
                std::cout << " " << arr.get_pos(i);
            }
            std::cout << std::endl;
            timsort(arr, minrun(arr.get_size()));
            std::cout << "Отсорт.массив: ";
            for (int i = 0; i < arr.get_size(); i++)
            {
                std::cout << " " << arr.get_pos(i);
            }
            std::cout << std::endl;
            break;
        }
        case '6': {
            running = false;
            break;
        }
        default:
            std::cout << "Некорректный выбор!\n";
            break;
        }
    }
}


int main()
{
    setlocale(LC_ALL, "ru");
    dynamic_arr<int> arr;
    array_menu();
    return 0;
}