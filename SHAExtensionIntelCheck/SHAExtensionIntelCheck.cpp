#include <iostream>
#include <array>
#include <string>
#include <intrin.h>
#include <conio.h>

class IntelSHAChecker
{
public:
    static bool IsIntelAndSupportsSHA()
    {
        std::array<int, 4> cpui;

        __cpuid(cpui.data(), 0);
        int nIds_ = cpui[0];

        char vendor[0x20] = { 0 };
        *reinterpret_cast<int*>(vendor) = cpui[1];
        *reinterpret_cast<int*>(vendor + 4) = cpui[3];
        *reinterpret_cast<int*>(vendor + 8) = cpui[2];

        std::string vendorStr = vendor;
        bool isIntel = (vendorStr == "GenuineIntel");

        if (isIntel && nIds_ >= 7)
        {
            __cpuidex(cpui.data(), 7, 0);
            return cpui[1] & (1 << 29);
        }

        return false;
    }
};

int main()
{
    std::cout << "Intel CPU with SHA Instruction: "
        << (IntelSHAChecker::IsIntelAndSupportsSHA() ? "Yes" : "No")
        << std::endl;
    std::cout << "Press any key to continue..." << std::endl;
    _getch(); 
    return 0;
}
