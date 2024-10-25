#include <iostream>
#include <thread>
#include <vector>
#include <cmath>

void task_1() {
    std::cout << "Hilo 1\n";
}

void task_2() {
    std::cout << "Hilo 2\n";
}

void ejemplo1_crear_hilos() {
    std::thread h1(task_1);
    std::thread h2;
    // ...
    h2 = std::thread(task_2);

    h1.join();
    h2.detach();
    std::this_thread::sleep_for(std::chrono::microseconds(100));
}


void task_3(const std::string& message) {
    std::cout << message;
}

void ejemplo2_crear_hilos_con_parametros_por_valor() {
    std::thread h1(task_3, "Hilo #3\n");
    h1.join();
}

void task_sum(int a, int b, int& result) {
    result  = a + b;
}

void ejemplo3_crear_hilos_con_parametros_por_referencia() {
    int total = 0;
    std::thread h1(task_sum, 10, 20, std::ref(total));
    h1.join();
    std::cout << total << std::endl;
}

void task_sum_ptr(int a, int b, int* result) {
    *result  = a + b;
}

void ejemplo4_crear_hilos_con_parametros_por_referencia_puntero() {
    int total = 0;
    std::thread h1(task_sum_ptr, 10, 20, &total);
    h1.join();
    std::cout << total << std::endl;
}

/*
 *
    Crear un programa que realice la sumatoria de valores de un vector

    std::vector v1 { 5, 8, 13, 20};

    h1 ==> retornar 1 + 2 + 3 + 4 + 5
    h2 ==> retornar 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8
    h3 ==> retornar 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 ... + 13
    h4 ==> retornar 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 ... + 20
 *
 */

void task_accumulate(int n, int& result) {
    result = 0;
    for (int i = 1; i <= n; ++i) result += i;
}

void ejercicio_1() {
    std::vector<int> v {5, 8, 13, 20};
    std::vector<int> r(v.size());
    std::thread h1(task_accumulate, v[0], std::ref(r[0]));
    std::thread h2(task_accumulate, v[1], std::ref(r[1]));
    std::thread h3(task_accumulate, v[2], std::ref(r[2]));
    std::thread h4(task_accumulate, v[3], std::ref(r[3]));
    h1.join();
    h2.join();
    h3.join();
    h4.join();
    for (const auto& item: r)
        std::cout << item << " ";
}

void ejercicio_2() {
    std::vector<int> vec{5, 8, 13, 20, 5};
    std::vector<int> res(vec.size());
    std::vector<std::thread> vh;
    vh.reserve(vec.size());
    for (int i = 0; i < vec.size(); ++i) {
        vh.emplace_back(task_accumulate, vec[i], std::ref(res[i]));
    }
    for (auto& h: vh) h.join();
    for (const auto& item: res)
        std::cout << item << " ";
}

/*
 *
    crear una variable double que acumule la suma de los primero
        100 valores de radianes de 0, cada cierto intervalo

    result = sin(0), sin(0 + inter) + sin(0 +2 * inter) ... sin( 0 + 99 * inter)

 *
 */

void task_accumulate_cos(double radian, double& total) {
    total += std::cos(radian);
}

void ejercicio_3() {
    double total = 0;
    double interval = 0.01;
    int n = 100;
    for (int i = 0; i < n; ++i) {
        total += std::cos(i*interval);
    }
    std::cout << total << std::endl;

    total = 0;
    std::vector<std::thread> vh;
    vh.reserve(n);
    for (int i = 0; i < n; ++i)
        vh.emplace_back(task_accumulate_cos, i*interval, std::ref(total));
    for (int i = 0; i < n; ++i)
        vh[i].join();
    std::cout << total << std::endl;
}


int main() {
//    std::cout << std::thread::hardware_concurrency() << std::endl;
//    ejemplo1_crear_hilos();
//    ejemplo1_crear_hilos_con_parametros_por_valor();
//    ejemplo2_crear_hilos_con_parametros_por_valor();
//    ejemplo3_crear_hilos_con_parametros_por_referencia();
//    ejemplo4_crear_hilos_con_parametros_por_referencia_puntero();
//    ejercicio_1();
//    ejercicio_2();
    ejercicio_3();
    return 0;
}
