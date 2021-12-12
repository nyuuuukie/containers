#pragma once

#include <cstddef>

namespace ft {

	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag	: public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	// Iterator traits
	template< typename Iterator >
	struct iterator_traits {
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template< typename T >
	struct iterator_traits< T* > {
		typedef T*								pointer;
		typedef T&								reference;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	template< typename T >
	struct iterator_traits< const T* > {
		typedef const T*						pointer;
		typedef const T&						reference;
		typedef T								value_type;
		typedef ptrdiff_t						difference_type;
		typedef ft::random_access_iterator_tag	iterator_category;
	};

	// Iterator
	template <typename Category, typename T, typename Distance = std::ptrdiff_t, typename Pointer = T*, typename Reference = T&> 
	struct iterator {
		typedef Pointer		pointer;
		typedef Reference	reference;
		typedef T			value_type;
		typedef Distance	difference_type;
		typedef Category	iterator_category;		
	};

	// Normal iterator
	template< typename _Iterator, typename _Container>
	class normal_iterator
	{
		typedef iterator_traits<_Iterator>	__traits_type;

		protected:
			_Iterator _current;

		public:
			typedef _Iterator									iterator_type;
			typedef typename __traits_type::pointer   			pointer;
			typedef typename __traits_type::reference 			reference;
			typedef typename __traits_type::value_type			value_type;
			typedef typename __traits_type::difference_type 	difference_type;
			typedef typename __traits_type::iterator_category	iterator_category;

		normal_iterator() noexcept 
		: _current(_Iterator()) {}

		explicit normal_iterator(const _Iterator& iter) noexcept
		: _current(iter) {}

		template<typename _Iter>
       	normal_iterator(const normal_iterator<_Iter,
			typename __enable_if<
      	       (std::__are_same<_Iter, typename _Container::pointer>::__value),
		      _Container>::__type>& i) noexcept
        : _current(i.base()) { }

		reference operator*() const noexcept {
			return *_current;
		}

    	pointer operator->() const noexcept {
			return _current;
		}

		normal_iterator& operator++() noexcept {
			++_current;
			return *this;
    	}

		normal_iterator operator++(int) noexcept {
			return normal_iterator(_current++);
		}


    	// Bidirectional iterator requirements
      	normal_iterator& operator--() noexcept {
			--_current;
			return *this;
      	}

		normal_iterator operator--(int) noexcept {
			return normal_iterator(_current--);
		}


		// Random access iterator requirements
		reference operator[](difference_type n) const noexcept {
			return _current[n];
		}

		normal_iterator& operator+=(difference_type n) noexcept {
			_current += n;
			return *this;
		}

		normal_iterator operator+(difference_type n) const noexcept {
			return normal_iterator(_current + n);
		}

		normal_iterator& operator-=(difference_type n) noexcept {
			_current -= n;
			return *this;
		}

		normal_iterator operator-(difference_type n) const noexcept {
			return normal_iterator(_current - n);
		}

		const _Iterator& base() const noexcept {
			return _current;
		}
	};

	// Reverse iterator
	template< typename _Iterator>
	class reverse_iterator 
	: public iterator<
		typename iterator_traits<_Iterator>::iterator_category, 
		typename iterator_traits<_Iterator>::value_type,
		typename iterator_traits<_Iterator>::difference_type,
		typename iterator_traits<_Iterator>::pointer,
		typename iterator_traits<_Iterator>::reference > {
		
 		typedef iterator_traits<_Iterator>	__traits_type;

		protected:
	    	_Iterator _current;

    	public:
    		typedef _Iterator									iterator_type;
    		typedef typename __traits_type::pointer				pointer;
    		typedef typename __traits_type::reference			reference;
    		typedef typename __traits_type::value_type			value_type;
    		typedef typename __traits_type::difference_type		difference_type;
			typedef typename __traits_type::iterator_category	iterator_category;

			reverse_iterator() : _current() { }

			explicit 
			reverse_iterator(iterator_type x) : _current(x) { }

			reverse_iterator(const reverse_iterator& x)
		    : _current(x._current) { }

			template<class _Iter>
			reverse_iterator(const reverse_iterator<_Iter>& x)
			: _current(x.base()) { }

			~reverse_iterator() { }

			iterator_type base() const { 
				return _current;
			}

			reference operator*() const {
				_Iterator tmp = _current;
				return *--tmp;
			}

			pointer operator->() const {
				_Iterator tmp = _current;
				--tmp;
				return _S_to_pointer(tmp);
			}

			reverse_iterator& operator++() {
				--_current;
				return *this;
			}

			reverse_iterator operator++(int) {
				reverse_iterator tmp = *this;
				--_current;
				return tmp;
			}

			reverse_iterator& operator--() {
				++_current;
				return *this;
			}

			reverse_iterator operator--(int) {
				reverse_iterator tmp = *this;
				++_current;
				return tmp;
			}

			reverse_iterator operator+(difference_type n) const {
				return reverse_iterator(_current - n);
			}

			reverse_iterator& operator+=(difference_type n) {
				_current -= n;
				return *this;
			}

			reverse_iterator operator-(difference_type n) const {
				return reverse_iterator(_current + n);
			}

			reverse_iterator& operator-=(difference_type n) {
				_current += n;
				return *this;
			}

			reference operator[](difference_type n) const {
				return *(*this + n);
			}

		private:
			template<typename Tp>
			static _Tp* _S_to_pointer(Tp* p) {
				return p;
			}

			template<typename Tp> 
			static pointer _S_to_pointer(Tp t) {
				return t.operator->();
			}
   		};


	// Non-member comparison overloads	
	template< typename Iterator1, class Iterator2 >
	bool operator==( const reverse_iterator<Iterator1>& lhs,
                	const reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() == rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator!=( const reverse_iterator<Iterator1>& lhs,
                	const reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() != rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const reverse_iterator<Iterator1>& lhs,
                	const reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() < rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<=( const reverse_iterator<Iterator1>& lhs,
                	const reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() <= rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>( const reverse_iterator<Iterator1>& lhs,
                	const reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() > rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator>=( const reverse_iterator<Iterator1>& lhs,
                	const reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() >= rhs.base();
	}

	template< class Iterator1, class Iterator2 >
	bool operator<( const reverse_iterator<Iterator1>& lhs,
                	const reverse_iterator<Iterator2>& rhs ) {
		return lhs.base() < rhs.base();
	}

	template <class Iterator>
	bool operator==( const reverse_iterator<class Iterator>& lhs,
					 const reverse_iterator< class Iterator>& rhs ) {
		return lhs.base() == rhs.base();
	}

	template <class Iterator>
	bool operator!=( const reverse_iterator<class Iterator>& lhs,
					 const reverse_iterator< class Iterator>& rhs ) {
		return lhs.base() != rhs.base();
	}

	template <class Iterator>
	bool operator<( const reverse_iterator<class Iterator>& lhs,
					const reverse_iterator< class Iterator>& rhs ) {
		return lhs.base() < rhs.base();
	}

	template <class Iterator>
	bool operator>( const reverse_iterator<class Iterator>& lhs,
					const reverse_iterator< class Iterator>& rhs ) {
		return lhs.base() > rhs.base();
	}

	template <class Iterator>
	bool operator<=( const reverse_iterator<class Iterator>& lhs,
					const reverse_iterator< class Iterator>& rhs ) {
		return lhs.base() <= rhs.base();
	}

	template <class Iterator>
	bool operator>=( const reverse_iterator<class Iterator>& lhs,
					const reverse_iterator< class Iterator>& rhs ) {
		return lhs.base() >= rhs.base();
	}

	template< class _Iterator >
    inline typename reverse_iterator<_Iterator>::difference_type
    operator-(const reverse_iterator<_Iterator>& lhs, const reverse_iterator<_Iterator>& rhs) {
		return rhs.base() - lhs.base();
	}

	template< class _Iterator >
	inline reverse_iterator<_Iterator>
    operator+( typename reverse_iterator<_Iterator>::difference_type n,
               const reverse_iterator<_Iterator>& i ) {
		return reverse_iterator<_Iterator>(i.base() - n);
	}

}