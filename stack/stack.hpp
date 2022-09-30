/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tweimer <tweimer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 10:23:57 by tweimer           #+#    #+#             */
/*   Updated: 2022/09/21 16:28:59 by tweimer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
#define STACK_HPP

#include "../vector/vector.hpp"

namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {
        
        public:
        typedef Container container_type;
        typedef typename Container::value_type value_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::reference reference;
        typedef typename Container::const_reference const_reference;
        
		protected:
        container_type c;
		public:
        explicit stack( const Container& cont = Container() );
        stack( const stack& other );
        ~stack();
        stack& operator=( const stack& other );
        reference top();
        const_reference top() const;
        bool empty(void) const;
        size_type size() const;
        void push( const value_type& value );
        void pop();
		template< class T1, class Container1 >
		friend bool operator==( const stack<T1,Container1>& lhs, const stack<T1,Container1>& rhs);
		template< class T1, class Container1 >
		friend  bool operator<( const ft::stack<T1,Container1>& lhs, const ft::stack<T1,Container1>& rhs );
		template< class T1, class Container1 >
		friend bool operator!=( const ft::stack<T1,Container1>& lhs, const ft::stack<T1,Container1>& rhs );
		template< class T1, class Container1 >
        friend bool operator>( const ft::stack<T1,Container1>& lhs, const ft::stack<T1,Container1>& rhs );
		template< class T1, class Container1 >
        friend bool operator>=( const ft::stack<T1,Container1>& lhs, const ft::stack<T1,Container1>& rhs );
		template< class T1, class Container1 >
        friend bool operator<=( const ft::stack<T1,Container1>& lhs, const ft::stack<T1,Container1>& rhs );
    };
template< class T, class Container >
ft::stack<T, Container>::stack(const Container& cont )
        :   c(cont) {}

template< class T, class Container >
ft::stack<T, Container>::stack( const stack& other )
        : c(other.c) {}

template< class T, class Container >
ft::stack<T, Container>& ft::stack<T, Container>::operator=(const stack& other )
{
    if (*this == other)
        return (*this);
    c = other.c;
    return (*this);
}

template< class T, class Container >
ft::stack<T, Container>::~stack(){}

template< class T, class Container >
typename ft::stack<T, Container>::reference ft::stack<T, Container>::top()
{
    return (c.back());
}

template< class T, class Container >
typename ft::stack<T, Container>::const_reference ft::stack<T, Container>::top() const
{
    return (c.back());
}

template< class T, class Container >
bool ft::stack<T, Container>::empty() const
{
    return (this->c.empty());
}

template< class T, class Container >
typename ft::stack<T, Container>::size_type ft::stack<T, Container>::size() const
{
    return(c.size());
}

template< class T, class Container >
void ft::stack<T, Container>::push( const value_type& value )
{
    c.push_back(value);
}

template< class T, class Container >
void ft::stack<T, Container>::pop()
{
   c.pop_back();
}

template< class T1, class Container1 >
bool operator==( const ft::stack<T1,Container1>& lhs, const ft::stack<T1,Container1>& rhs )
{
    return (lhs.c == rhs.c);
}
template< class T1, class Container1 >
bool operator!=( const ft::stack<T1,Container1>& lhs, const ft::stack<T1,Container1>& rhs )
{
    return !(lhs.c == rhs.c);
}
template< class T1, class Container1 >
 bool operator<( const ft::stack<T1,Container1>& lhs, const ft::stack<T1,Container1>& rhs )
{
    return (lhs.c < rhs.c);
}
template< class T1, class Container1 >
bool operator>( const ft::stack<T1,Container1>& lhs, const ft::stack<T1,Container1>& rhs )
{
    return (rhs.c < lhs.c);
}

template< class T1, class Container1 >
bool operator<=( const ft::stack<T1,Container1>& lhs, const ft::stack<T1,Container1>& rhs )
{
	
    return (lhs.c <= rhs.c);
}

template< class T1, class Container1 >
bool operator>=( const ft::stack<T1,Container1>& lhs, const ft::stack<T1,Container1>& rhs )
{
     return (lhs.c >= rhs.c);
}
}
#endif