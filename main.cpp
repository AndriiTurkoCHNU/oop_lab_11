#include <iostream>
#include <thread>



int main() {
    int num1 = 2, num2 = 3, num3 = 4;

    std::thread t1([num1]() {
        int result = num1 * num1;
        std::cout << "Square of " << num1 << " is " << result << std::endl;
    });

    std::thread t2([num2]() {
        int result = num2 * num2;
        std::cout << "Square of " << num2 << " is " << result << std::endl;
    });

    std::thread t3([num3]() {
        int result = num3 * num3;
        std::cout << "Square of " << num3 << " is " << result << std::endl;
    });

    t1.join();
    t2.join();
    t3.join();

    return 0;
}