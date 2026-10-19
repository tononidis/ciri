import std;
import Ciri;
import Traits;
import Buffer;

struct Test {
    int intData;
    int* pIntData;
    int* pIntData2;
    std::vector<int> vecIntData;
    char charData;
    std::vector<std::string> vecStrData;
    char charArrData[16];
    std::string strData;
};

int main()
{
    Test seri;
    seri.intData = 44;
    seri.charData = '4';
    seri.pIntData = new int(444);
    seri.pIntData2 = nullptr;
    seri.vecIntData = { 4, 4, 4 };
    seri.vecStrData = { "paok-vec-4", "paok-vec-44" };
    std::snprintf(seri.charArrData, sizeof(seri.charArrData), "paok-charArr");
    seri.strData = "paok-str";

    std::byte buf[1024];
    ciri::Buffer b;
    b.pData = buf;
    b.size = 1024;

    std::string localStr = "paok";
    std::vector<std::string> localStrVec = { "paok4", "paok44" };

    ciri::serialize(b, 1.0, seri, localStr, localStrVec);

    double localDouble;

    std::string localStrDeseri;
    std::vector<std::string> localStrVecDeseri;
    Test deseri;
    deseri.pIntData = new int(0); // Need to allocate memory for the pointer before deserialization
    auto res = ciri::deserialize(b, localDouble, deseri, localStrDeseri, localStrVecDeseri);

    std::cout << "localDouble: " << localDouble << std::endl;

    std::cout << "deseri.intData: " << deseri.intData << std::endl;
    std::cout << "deseri.pIntData: " << *deseri.pIntData << std::endl;
    std::cout << "deseri.pIntData2: " << deseri.pIntData2 << std::endl;

    for (const auto& item : deseri.vecIntData) {
        std::cout << "deseri.vecIntData: " << item << std::endl;
    }

    std::cout << "deseri.charData: " << deseri.charData << std::endl;
    std::cout << "deseri.charArrData: " << deseri.charArrData << std::endl;

    for (const auto& item : deseri.vecStrData) {
        std::cout << "deseri.vecStrData: " << item << std::endl;
    }

    std::cout << "deseri.strData: " << deseri.strData << std::endl;

    std::cout << "localStrDeseri: " << localStrDeseri << std::endl;

    for (const auto& item : localStrVecDeseri) {
        std::cout << "localStrVecDeseri: " << item << std::endl;
    }

    std::cout << "leftbuf size: " << res.size << std::endl;

    return 0;
}