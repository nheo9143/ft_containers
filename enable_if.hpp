#ifndef  ENABLE_IF_HPP
# define  ENABLE_IF_HPP

namespace ft
{
	/* enable_if 기본형 선언 */
	template <bool, typename T>
	struct enable_if {};

	/* true가 들어왔을 때의 처리 */
	template <typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	/* is_integral 기본형 선언 */
	template<typename T>
	struct is_integral { static const bool value = false;};

	template<>
	struct is_integral<bool> {static const bool value = true;};

	template<>
	struct is_integral<char> {static const bool value = true;};

	template<>
	struct is_integral<signed char> {static const bool value = true;};

	template<>
	struct is_integral<wchar_t> {static const bool value = true;};

	template<>
	struct is_integral<short> {static const bool value = true;};

	template<>
	struct is_integral<int> {static const bool value = true;};

	template<>
	struct is_integral<long> {static const bool value = true;};

	template<>
	struct is_integral<unsigned char> {static const bool value = true;};

	template<>
	struct is_integral<unsigned short> {static const bool value = true;};

	template<>
	struct is_integral<unsigned int> {static const bool value = true;};

	template<>
	struct is_integral<unsigned long> {static const bool value = true;};
};

#endif
