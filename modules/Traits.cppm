module;

export module Traits;

import std;

namespace ciri
{

export {

    template <typename T>
    consteval bool contains_pointer()
    {
        if constexpr (std::is_class_v<T> == false) {
            if constexpr (std::is_pointer_v<T> == true) {
                return true;
            }

            else {
                return false;
            }
        }

        else {

            constexpr auto ctx = std::meta::access_context::unchecked();

            static constexpr auto nonstatic_members = std::define_static_array(std::meta::nonstatic_data_members_of(^^T, ctx));
            template for (constexpr auto member : nonstatic_members)
            {
                if constexpr (std::meta::is_pointer_type(std::meta::type_of(member))) {
                    return true;
                }
            }

            static constexpr auto static_members = std::define_static_array(std::meta::static_data_members_of(^^T, ctx));
            template for (constexpr auto member : static_members)
            {
                if constexpr (std::meta::is_pointer_type(std::meta::type_of(member))) {
                    return true;
                }
            }

            return false;
        }
    }

    template <typename T>
    concept Memcpyable = std::is_trivially_copyable_v<T> && contains_pointer<T>() == false;

    template <typename T>
    consteval auto getNonStaticFieldsInfo()
    {
        constexpr auto ctx = std::meta::access_context::unchecked();
        return std::define_static_array(std::meta::nonstatic_data_members_of(^^T, ctx));
    }
}

}