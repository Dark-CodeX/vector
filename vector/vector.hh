/**
 * This header file is written to create vectors in C++.
 * Author: Tushar Chaurasia (https://github.com/Dark-CodeX/)
 * Commit to this repository at https://github.com/Dark-CodeX/vector.git
 * You can use this header file. Do not modify it locally, instead commit it on https://www.github.com
 * File: "vector.hh" under "vector" directory
 * vector version: 1.6.1
 * MIT License
 *
 * Copyright (c) 2022 Tushar Chaurasia
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifdef __cplusplus

#ifndef VECTOR_DEFINED
#define VECTOR_DEFINED

#if defined _WIN32 || defined _WIN64 || defined __CYGWIN__
#include <utility>
#else
#include <bits/functional_hash.h>
#include <bits/move.h>
#endif

#include <initializer_list>
#include <functional>
#include <cstdio>

#define vector_t_version "1.6.1"

namespace openutils
{
	template <typename T>
	class iter_vector_t;

	template <typename T>
	class vector_t
	{
	private:
		void resize();
		std::size_t len, cap;
		T *vec_data;
		friend class iter_vector_t<T>;

	public:
		vector_t();
		vector_t(T &&default_data, const std::size_t &capacity = 10);
		vector_t(const T &default_data, const std::size_t &capacity = 10);
		vector_t(const vector_t &vec);
		vector_t(vector_t &&other) noexcept;
		vector_t(std::initializer_list<T> __list);
		vector_t(const std::size_t &capacity);
		std::size_t length() const;
		std::size_t capacity() const;
		void add(T &&data);
		void add(const T &data);
		bool insert(T &&data, const std::size_t &nth);
		bool insert(const T &data, const std::size_t &nth);
		void remove();
		bool remove(const std::size_t &nth);
		bool empty() const;
		std::size_t hash() const;
		bool compare(const vector_t &vec) const;
		bool compare_hash(const vector_t &vec) const;
		void erase();
		void erase(T &&default_data, const std::size_t &capacity = 10);
		void erase(const T &default_data, const std::size_t &capacity = 10);
		const T &get(const std::size_t &nth) const;
		bool set(T &&data, const std::size_t &nth);
		bool set(const T &data, const std::size_t &nth);
		void reverse();
		std::size_t find(T &&data) const;
		std::size_t find(const T &data) const;
		bool swap(const std::size_t &x1, const std::size_t &x2);
		const T *&raw_data() const;
		T *&raw_data();
		typedef iter_vector_t<T> iter;
		iter iterator() const;
		iter reverse_iterator() const;

		template <typename comp>
		void sort(comp c)
		{
			std::sort(this->vec_data, this->vec_data + this->len, c);
		}

		void operator=(const vector_t &data);
		const T &operator[](const std::size_t &nth) const;
		T &operator[](const std::size_t &nth);
		bool operator==(const vector_t &vec) const;
		bool operator!=(const vector_t &vec) const;
		vector_t &operator=(vector_t &&__s) noexcept;
		void operator+=(const vector_t &data);
		void operator+=(T &&data);
		void operator+=(const T &data);
		void operator+=(std::initializer_list<T> __list);
		const std::size_t nerr = (std::size_t)-1;
		~vector_t();
	};

#ifndef EXIT_HEAP_FAIL
#define EXIT_HEAP_FAIL
	static inline void exit_heap_fail(const void *ptr)
	{
		if (!ptr)
		{
			std::fprintf(stderr, "err: can't allocate heap memory.\n");
			std::exit(EXIT_FAILURE);
		}
	}
#endif

	template <typename T>
	vector_t<T>::vector_t()
	{
		this->cap = 10;
		this->len = 0;
		this->vec_data = new T[this->cap]();
		exit_heap_fail(this->vec_data);
	}

	template <typename T>
	vector_t<T>::vector_t(T &&default_data, const std::size_t &capacity)
	{
		this->cap = capacity;
		this->len = 0;
		this->vec_data = new T[this->cap]();
		exit_heap_fail(this->vec_data);
		for (std::size_t i = 0; i < this->cap; i++)
		{
			this->vec_data[i] = default_data;
			this->len++;
		}
	}

	template <typename T>
	vector_t<T>::vector_t(const T &default_data, const std::size_t &capacity)
	{
		this->cap = capacity;
		this->len = 0;
		this->vec_data = new T[this->cap]();
		exit_heap_fail(this->vec_data);
		for (std::size_t i = 0; i < this->cap; i++)
		{
			this->vec_data[i] = default_data;
			this->len++;
		}
	}

	template <typename T>
	vector_t<T>::vector_t(const vector_t &vec)
	{
		this->len = vec.len;
		this->cap = vec.cap;
		this->vec_data = new T[this->cap]();
		exit_heap_fail(this->vec_data);
		for (std::size_t i = 0; i < vec.len; i++)
			this->vec_data[i] = vec.vec_data[i];
	}

	template <typename T>
	vector_t<T>::vector_t(vector_t &&other) noexcept : len(0), cap(0), vec_data(nullptr)
	{
		this->vec_data = other.vec_data;
		this->len = other.len;
		this->cap = other.cap;
		other.vec_data = nullptr;
		other.len = 0;
		other.cap = 10;
	}

	template <typename T>
	vector_t<T>::vector_t(std::initializer_list<T> __list)
	{
		this->len = 0;
		this->cap = __list.size();
		this->vec_data = new T[this->cap]();
		exit_heap_fail(this->vec_data);
		for (auto i = __list.begin(); i != __list.end(); i++, this->len++)
			this->vec_data[this->len] = *i;
	}

	template <typename T>
	vector_t<T>::vector_t(const std::size_t &capacity)
	{
		this->cap = capacity;
		this->len = 0;
		this->vec_data = new T[this->cap]();
		exit_heap_fail(this->vec_data);
	}

	template <typename T>
	void vector_t<T>::resize()
	{
		T *temp = new T[this->cap * 3]();
		exit_heap_fail(temp);
		for (std::size_t i = 0; i < this->cap; i++)
			temp[i] = this->vec_data[i];
		delete[] this->vec_data;
		this->cap *= 3;
		this->vec_data = temp;
	}

	template <typename T>
	std::size_t vector_t<T>::length() const { return this->len; }

	template <typename T>
	std::size_t vector_t<T>::capacity() const { return this->cap; }

	template <typename T>
	void vector_t<T>::add(T &&data)
	{
		if (this->len == this->cap)
			this->resize();
		this->vec_data[this->len++] = data;
	}

	template <typename T>
	void vector_t<T>::add(const T &data)
	{
		if (this->len == this->cap)
			this->resize();
		this->vec_data[this->len++] = data;
	}

	template <typename T>
	bool vector_t<T>::insert(T &&data, const std::size_t &nth)
	{
		if (nth <= this->len)
		{
			if (this->len == this->cap)
				this->resize();
			static T __t[1] = {};
			for (std::size_t i = this->len; i >= nth; i--)
			{
				this->vec_data[i + 1] = this->vec_data[i];
				this->vec_data[i] = __t[0];
				if (i == 0)
					break;
			}
			this->vec_data[nth] = data;
			this->len++;
			return true;
		}
		return false;
	}

	template <typename T>
	bool vector_t<T>::insert(const T &data, const std::size_t &nth)
	{
		return this->insert((T &&) data, nth);
	}

	template <typename T>
	void vector_t<T>::remove()
	{
		this->len--;
	}

	template <typename T>
	bool vector_t<T>::remove(const std::size_t &nth)
	{
		if (nth < this->len)
		{
			static T __t[1] = {};
			this->vec_data[nth] = __t[0];
			for (std::size_t i = nth; i < this->len - 1; i++)
			{
				this->vec_data[i] = this->vec_data[i + 1];
				this->vec_data[i + 1] = __t[0];
			}
			this->len--;
			return true;
		}
		return false;
	}

	template <typename T>
	bool vector_t<T>::empty() const
	{
		return (this->len == 0);
	}

	template <typename T>
	inline void hash_combine(std::size_t &seed, const T &v)
	{
		seed ^= std::hash<T>()(v) + static_cast<std::size_t>(0xc70f6907UL) + (seed << 7) + (seed >> 3);
	}

	template <typename T>
	std::size_t vector_t<T>::hash() const
	{
		std::size_t h = 0;
		for (std::size_t i = 0; i < this->len; i++)
			hash_combine(h, this->vec_data[i]);
		return h;
	}

	template <typename T>
	bool vector_t<T>::compare(const vector_t &vec) const
	{
		if (this->len != vec.len)
			return false;
		for (std::size_t i = 0; i < this->len; i++)
			if (this->vec_data[i] != vec.vec_data[i])
				return false;
		return true;
	}

	template <typename T>
	bool vector_t<T>::compare_hash(const vector_t &vec) const
	{
		return (this->hash() == vec.hash());
	}

	template <typename T>
	void vector_t<T>::erase()
	{
		delete[] this->vec_data;
		this->cap = 10;
		this->len = 0;
		this->vec_data = new T[this->cap]();
		exit_heap_fail(this->vec_data);
	}

	template <typename T>
	void vector_t<T>::erase(T &&default_data, const std::size_t &capacity)
	{
		delete[] this->vec_data;
		this->cap = capacity;
		this->len = 0;
		this->vec_data = new T[this->cap]();
		const std::size_t &it_heap_fail(this->vec_data);

		for (std::size_t i = 0; i < this->cap; i++)
		{
			this->vec_data[i] = default_data;
			this->len++;
		}
	}

	template <typename T>
	void vector_t<T>::erase(const T &default_data, const std::size_t &capacity)
	{
		this->erase((T &&) default_data, capacity);
	}

	template <typename T>
	const T &vector_t<T>::get(const std::size_t &nth) const
	{
		if (nth < this->len)
			return this->vec_data[nth];
		std::fprintf(stderr, "err: out-of-range\n");
		std::exit(EXIT_FAILURE);
	}

	template <typename T>
	bool vector_t<T>::set(T &&data, const std::size_t &nth)
	{
		if (nth < this->len)
		{
			this->vec_data[nth] = data;
			return true;
		}
		return false;
	}

	template <typename T>
	bool vector_t<T>::set(const T &data, const std::size_t &nth)
	{
		return this->set((T &&) data, nth);
	}

	template <typename T>
	void vector_t<T>::reverse()
	{
		T c;
		for (std::size_t i = 0; i < this->len / 2; i++)
		{
			c = this->vec_data[i];
			this->vec_data[i] = this->vec_data[this->len - i - 1];
			this->vec_data[this->len - i - 1] = c;
		}
	}

	template <typename T>
	std::size_t vector_t<T>::find(T &&data) const
	{
		for (std::size_t i = 0; i < this->len; i++)
			if (this->vec_data[i] == data)
				return i;
		return (std::size_t)-1;
	}

	template <typename T>
	std::size_t vector_t<T>::find(const T &data) const
	{
		return this->find((T &&) data);
	}

	template <typename T>
	bool vector_t<T>::swap(const std::size_t &x1, const std::size_t &x2)
	{
		if (x1 < this->len && x2 < this->len)
		{
			T x = T((T &&) this->vec_data[x1]);
			this->vec_data[x1] = this->vec_data[x2];
			this->vec_data[x2] = x;
			return true;
		}
		return false;
	}

	template <typename T>
	const T *&vector_t<T>::raw_data() const { return this->vec_data; }

	template <typename T>
	T *&vector_t<T>::raw_data() { return this->vec_data; }

	template <typename T>
	typename vector_t<T>::iter vector_t<T>::iterator() const
	{
		return vector_t<T>::iter(this, false);
	}

	template <typename T>
	typename vector_t<T>::iter vector_t<T>::reverse_iterator() const
	{
		return vector_t<T>::iter(this, true);
	}

	template <typename T>
	void vector_t<T>::operator=(const vector_t &data)
	{
		delete[] this->vec_data;
		this->len = data.len;
		this->cap = data.cap;
		this->vec_data = new T[data.cap]();
		exit_heap_fail(this->vec_data);
		for (std::size_t i = 0; i < data.len; i++)
			this->vec_data[i] = data.vec_data[i];
	}

	template <typename T>
	const T &vector_t<T>::operator[](const std::size_t &nth) const
	{
		if (nth < this->len)
			return this->vec_data[nth];
		std::fprintf(stderr, "err: out-of-range\n");
		std::exit(EXIT_FAILURE);
	}

	template <typename T>
	T &vector_t<T>::operator[](const std::size_t &nth)
	{
		if (nth < this->len)
			return this->vec_data[nth];
		std::fprintf(stderr, "err: out-of-range\n");
		std::exit(EXIT_FAILURE);
	}

	template <typename T>
	bool vector_t<T>::operator==(const vector_t &vec) const
	{
		return this->compare(vec);
	}

	template <typename T>
	bool vector_t<T>::operator!=(const vector_t &vec) const
	{
		return !this->compare(vec);
	}

	template <typename T>
	vector_t<T> &vector_t<T>::operator=(vector_t &&__s) noexcept
	{
		if (this != &__s)
		{
			delete[] this->vec_data;
			this->len = __s.len;
			this->cap = __s.cap;
			this->vec_data = new T[this->cap]();
			exit_heap_fail(this->vec_data);
			for (std::size_t i = 0; i < __s.len; i++)
				this->vec_data[i] = __s.vec_data[i];
		}
		return *this;
	}

	template <typename T>
	void vector_t<T>::operator+=(const vector_t &data)
	{
		for (std::size_t i = 0; i < data.len; i++)
			this->add(data.vec_data[i]);
	}

	template <typename T>
	void vector_t<T>::operator+=(T &&data)
	{
		this->add(std::move(data));
	}

	template <typename T>
	void vector_t<T>::operator+=(const T &data)
	{
		this->add(data);
	}

	template <typename T>
	void vector_t<T>::operator+=(std::initializer_list<T> __list)
	{
		for (auto &i : __list)
			this->add(i);
	}

	template <typename T>
	vector_t<T>::~vector_t()
	{
		this->len = 0;
		this->cap = 0;
		delete[] this->vec_data;
	}

	template <typename T>
	class iter_vector_t
	{
	private:
		vector_t<T> *vec;
		std::size_t ind;
		bool rev;

	public:
		iter_vector_t(const vector_t<T> *vec, bool reverse);
		bool c_loop() const;
		bool is_first() const;
		bool is_last() const;
		std::size_t index() const;
		T &operator->();
		const T &operator*() const;
		void next();
	};

	template <typename T>
	iter_vector_t<T>::iter_vector_t(const vector_t<T> *v, bool reverse)
	{
		this->vec = (vector_t<T> *)v;
		this->rev = reverse;
		if (reverse == true)
			this->ind = this->vec->len - 1;
		else
			this->ind = 0;
	}

	template <typename T>
	bool iter_vector_t<T>::c_loop() const
	{
		if (this->rev == true)
			return this->ind != (std::size_t)-1;
		return this->ind < this->vec->len;
	}

	template <typename T>
	bool iter_vector_t<T>::is_first() const
	{
		if (this->rev == true)
			return this->ind == this->vec->len - 1;
		return this->ind == 0;
	}

	template <typename T>
	bool iter_vector_t<T>::is_last() const
	{
		if (this->rev == true)
			return this->ind == (std::size_t)-1;
		return this->ind < this->vec->len - 1;
	}

	template <typename T>
	std::size_t iter_vector_t<T>::index() const
	{
		return this->ind;
	}

	template <typename T>
	T &iter_vector_t<T>::operator->()
	{
		return (T &)this->vec->get(this->ind);
	}

	template <typename T>
	const T &iter_vector_t<T>::operator*() const
	{
		return (const T &)this->vec->get(this->ind);
	}

	template <typename T>
	void iter_vector_t<T>::next()
	{
		if (this->rev == true)
			this->ind--;
		else
			this->ind++;
	}
};

namespace std
{
	template <typename T>
	struct hash<openutils::vector_t<T>>
	{
		std::size_t operator()(const openutils::vector_t<T> &vec) const
		{
			return vec.hash();
		}
	};
};

#endif
#endif