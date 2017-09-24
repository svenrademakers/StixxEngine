#ifndef HANDLE_EXPOSER_HPP
#define HANDLE_EXPOSER_HPP

namespace sx
{
	template<typename T>
	class HandleExposer
	{
	public:
		HandleExposer() = default;
		HandleExposer(const HandleExposer&) = delete;
		HandleExposer& operator = (const HandleExposer&) = delete;
		virtual ~HandleExposer() {};

		const T& operator*();

	protected:
		T handle;
	};

	template<typename T>
	const T& HandleExposer<T>::operator*()
	{
		return handle;
	}
}

#endif