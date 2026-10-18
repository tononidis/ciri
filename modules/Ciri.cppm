module;

#include <cassert>

export module Ciri;

import std;
import Traits;
import Buffer;

namespace ciri
{

export {
    /** @brief Serialize data into a buffer
     *
     * @tparam T Type of the first data to serialize
     * @tparam Ts Types of the rest of the data to serialize
     *
     * @param buffer The buffer to serialize the data into
     * @param first The first data item to serialize
     * @param rest The remaining data items to serialize
     *
     * @note Currently, only trivially copyable types, std::string and std::vector are supported for serialization. If a non-supported type is provided, a static assertion will fail at compile time.
     *
     * @return A Buffer object representing the remaining space in the buffer after serialization. If serialization fails assert false is raised.
     *
     */
    template <typename T, typename... Ts>
    Buffer serialize(const Buffer& buffer, const T& first, const Ts&... rest);

    /** @brief Deserialize data from a buffer
     *
     * @tparam T Type of the first data to deserialize
     * @tparam Ts Types of the rest of the data to deserialize
     *
     * @param buffer The buffer to deserialize the data from
     * @param first The first data item to deserialize
     * @param rest The remaining data items to deserialize
     *
     * @note Currently, only trivially copyable types, std::string and std::vector are supported for deserialization. If a non-supported type is provided, a static assertion will fail at compile time.
     *
     * @return A Buffer object representing the remaining space in the buffer after deserialization. If deserialization fails assert false is raised.
     *
     */
    template <typename T, typename... Ts>
    Buffer deserialize(const Buffer& buffer, T& first, Ts&... rest);
}

namespace detail
{
    template <typename T>
    struct Serialize {
        static Buffer serialize(const Buffer& buffer, const T& data_in)
        {
            if constexpr (Memcpyable<T>) {
                assert(buffer.pData != nullptr && buffer.size >= sizeof(T));

                std::memcpy(buffer.pData, &data_in, sizeof(data_in));
                return buffer.next(sizeof(data_in));
            }

            else {
                static constexpr auto fieldInfo = getNonStaticFieldsInfo<T>();
                auto res = buffer;
                template for (constexpr auto& field : fieldInfo)
                {

                    using MemberType = [:std::meta::type_of(field):];
                    const auto& fieldValue = data_in.[:field:];

                    if constexpr (std::meta::is_pointer_type(std::meta::type_of(field)) == true) {
                        assert(fieldValue != nullptr);
                        res = Serialize<std::remove_pointer_t<MemberType>>::serialize(res, *fieldValue);
                    }

                    else {
                        res = Serialize<MemberType>::serialize(res, fieldValue);
                    }
                }
                return res;
            }
        }
    };

    template <typename T>
    struct Deserialize {
        static Buffer deserialize(const Buffer& buffer, T& data_out)
        {
            if constexpr (Memcpyable<T>) {
                assert(buffer.pData != nullptr && buffer.size >= sizeof(T));

                std::memcpy(&data_out, buffer.pData, sizeof(data_out));
                return buffer.next(sizeof(data_out));
            }

            else {
                static constexpr auto fieldInfo = getNonStaticFieldsInfo<T>();
                auto res = buffer;
                template for (constexpr auto& field : fieldInfo)
                {
                    using MemberType = [:std::meta::type_of(field):];
                    auto& fieldValue = data_out.[:field:];

                    if constexpr (std::meta::is_pointer_type(std::meta::type_of(field)) == true) {
                        assert(fieldValue != nullptr);
                        res = Deserialize<std::remove_pointer_t<MemberType>>::deserialize(res, *fieldValue);
                    }

                    else {
                        res = Deserialize<MemberType>::deserialize(res, fieldValue);
                    }
                }
                return res;
            }
        }
    };

    template <>
    struct Serialize<std::string> {
        static Buffer serialize(const Buffer& buffer, const std::string& data_in)
        {
            decltype(data_in.size()) strLen = data_in.size();
            assert(buffer.pData != nullptr && buffer.size >= sizeof(strLen));

            auto res = Serialize<decltype(strLen)>::serialize(buffer, strLen);
            assert(res.pData != nullptr && res.size >= strLen);

            std::memcpy(res.pData, data_in.c_str(), strLen);
            return res.next(strLen);
        }
    };

    template <>
    struct Deserialize<std::string> {
        static Buffer deserialize(const Buffer& buffer, std::string& data_out)
        {
            decltype(data_out.size()) strLen = 0;
            assert(buffer.pData != nullptr && buffer.size >= sizeof(strLen));

            auto res = Deserialize<decltype(strLen)>::deserialize(buffer, strLen);
            assert(res.pData != nullptr && res.size >= strLen);

            data_out.assign(reinterpret_cast<char*>(res.pData), strLen);
            return res.next(strLen);
        }
    };

    template <typename T, typename Alloc>
    struct Serialize<std::vector<T, Alloc>> {
        static Buffer serialize(const Buffer& buffer, const std::vector<T, Alloc>& data_vec_in)
        {
            decltype(data_vec_in.size()) vecSize = data_vec_in.size();
            assert(buffer.pData != nullptr && buffer.size >= sizeof(vecSize));

            auto res = Serialize<decltype(vecSize)>::serialize(buffer, vecSize);
            for (const auto& item : data_vec_in) {
                res = Serialize<T>::serialize(res, item);
            }

            return res;
        }
    };

    template <typename T, typename Alloc>
    struct Deserialize<std::vector<T, Alloc>> {
        static Buffer deserialize(const Buffer& buffer, std::vector<T, Alloc>& data_vec_out)
        {
            decltype(data_vec_out.size()) vecSize = 0;
            assert(buffer.pData != nullptr && buffer.size >= sizeof(vecSize));

            auto res = Deserialize<decltype(vecSize)>::deserialize(buffer, vecSize);
            for (auto i = 0; i < vecSize; i++) {
                T item;
                res = Deserialize<T>::deserialize(res, item);
                data_vec_out.emplace_back(std::move(item));
            }

            return res;
        }
    };
}

template <typename T, typename... Ts>
Buffer serialize(const Buffer& buffer, const T& first, const Ts&... rest)
{
    auto res = detail::Serialize<T>::serialize(buffer, first);
    if constexpr (sizeof...(rest) == 0) {
        return res;
    }

    else {
        assert(res.isValid() == true);

        return serialize(res, rest...);
    }
}

template <typename T, typename... Ts>
Buffer deserialize(const Buffer& buffer, T& first, Ts&... rest)
{
    auto res = detail::Deserialize<T>::deserialize(buffer, first);
    if constexpr (sizeof...(rest) == 0) {
        return res;
    }

    else {
        assert(res.isValid() == true);

        return deserialize(res, rest...);
    }
}

}
