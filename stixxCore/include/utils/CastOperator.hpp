#ifndef CAST_OPERATOR_HPP
#define CAST_OPERATOR_HPP

namespace sx
{
    template<typename T>
    class CastOperator
    {
    public:
		constexpr CastOperator() = default;
        operator const T &() const;

    protected:
        T handle;
    };

    template<typename T>
    CastOperator<T>::operator const T &() const
    {
        return handle;
    }
}

#endif