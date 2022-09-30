
#ifndef _FT_NULLPTR_T_HPP
#define _FT_NULLPTR_T_HPP
namespace ft
{

	const class nullptr_t
	{
	public:
		template <class T>
		operator T *() const
		{
			return 0;
		}
		template <class C, class T>
		operator T C::*() const
		{
			return 0;
		}

	private:
		void operator&() const;

	} ft_nullptr = {};
}
#endif // ft