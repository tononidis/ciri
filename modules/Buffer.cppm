module;

export module Buffer;

import std;

namespace ciri
{
export {

    /** @brief A simple buffer structure to hold a pointer to data and its size
     *
     *  @property pData_in Pointer to the data in the buffer
     *  @property size_in Size of the buffer
     */
    struct Buffer {
        std::byte* pData;
        std::size_t size;

        Buffer() = default;
        Buffer(std::byte* pData_in, std::size_t size_in)
            : pData(pData_in)
            , size(size_in) { };

        bool isValid()
        {
            return pData != nullptr && size != 0;
        }

        Buffer next(const std::size_t& offset) const
        {
            return Buffer { pData + offset, size - offset };
        }
    };
}

}
