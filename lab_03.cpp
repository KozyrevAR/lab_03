// lab_03.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <math.h>
#include <conio.h>
#include <vector>
#include <string>
using namespace std;
vector<double>
input_numbers(size_t count) 
{
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}
void find_minmax(const vector<double>& numbers, double& min, double& max)
{
    min = numbers[0];
    max = numbers[0];
    for (double number : numbers)
    {
        if (min > number)
        {
            min = number;
        }
        else if (max < number)
        {
            max = number;
        }

    }
    return;
}
void make_histogram(size_t& bin_count, size_t& number_count, const vector<double>& numbers, vector <size_t>& bins, double& min, double& max)
{
    double bin_size = (max - min) / bin_count;
    for (size_t i = 0; i < number_count; i++)
    {
        bool found = false;
        for (size_t j = 0; j < (bin_count - 1) && !found; j++)
        {
            auto low = min + j * bin_size;
            auto high = min + (j + 1) * bin_size;
            if ((low <= numbers[i]) && (numbers[i] < high))
            {
                bins[j]++;
                found = true;
            }

        }
        if (!found)
        {
            bins[bin_count - 1]++;
        }

    }
}
void show_histogram_text(vector<size_t>&bins, size_t& bin_count, size_t& number_count)
{
    size_t max_bin = bins[0];
    for (size_t bin : bins)
        if (bin > max_bin)
            max_bin = bin;

    // вывод
    const size_t SCREEN_WIDTH = 80;
    const size_t MAX_ASTERISK = SCREEN_WIDTH - 3 - 1;
    for (size_t bin : bins)
    {
        size_t height = bin;
        if (max_bin > MAX_ASTERISK)
        {
            height = MAX_ASTERISK * (static_cast<double>(bin) / max_bin);
        }
        if (bin < 100)
            cout << " ";
        if (bin < 10)
            cout << " ";
        cout << bin << "|";
        
        for (size_t i = 0; i < bin; i++)
        {
            cout << '*';
        }
        cout << endl;
    }   
}
void
svg_begin(double width, double height) 
{
    cout << "<?xml version='1.0' encoding='UTF-8'?>\n";
    cout << "<svg ";
    cout << "width='" << width << "' ";
    cout << "height='" << height << "' ";
    cout << "viewBox='0 0 " << width << " " << height << "' ";
    cout << "xmlns='http://www.w3.org/2000/svg'>\n";
}
void
svg_end() 
{
    cout << "</svg>\n";
}
void
svg_text(double left, double baseline, string text) 
{
    cout << "<text x='" << left << "' y='" << baseline <<"' >"<< text <<"</text>";
}
void svg_rect(double x, double y, double width, double height, string stroke = "black", string fill = "black")
{
    cout << "<rect x='" << x << "' y='" << y << "' width='" << width << "' height='" << height << "' stroke='" << stroke << "' fill='" << fill << "'/>";
}
void
show_histogram_svg(const vector<size_t>& bins) {
    const auto IMAGE_WIDTH = 400;
    const auto IMAGE_HEIGHT = 300;
    const auto TEXT_LEFT = 20;
    const auto TEXT_BASELINE = 20;
    const auto TEXT_WIDTH = 50;
    const auto BIN_HEIGHT = 30;
    const auto BLOCK_WIDTH = 10;
    double top = 0;
    svg_begin(IMAGE_WIDTH, IMAGE_HEIGHT);
    for (size_t bin : bins) {
        const double bin_width = BLOCK_WIDTH * bin;
        svg_text(TEXT_LEFT, top + TEXT_BASELINE, to_string(bin));
        svg_rect(TEXT_WIDTH, top, bin_width, BIN_HEIGHT);
        top += BIN_HEIGHT;
    }
    svg_text(TEXT_LEFT, TEXT_BASELINE, to_string(bins[0]));
    svg_end();
    
}
int main()
{
    // ввод
    size_t number_count;
    cerr << "Enter number count: ";
    cin >> number_count;
    cerr << "Enter numbers: " << endl;
    const auto numbers = input_numbers(number_count);
    size_t bin_count;
    cerr << "Enter bin count: ";
    cin >> bin_count;
    // расчет гистограммы
    vector <size_t> bins(bin_count, 0);
    double min;
    double max;
    find_minmax(numbers, min, max);
    make_histogram(bin_count, number_count, numbers, bins, min, max);
    show_histogram_svg(bins);
   
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
